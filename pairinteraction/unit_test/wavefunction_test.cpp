/*
 * Copyright (c) 2017 Sebastian Weber, Henri Menke. All rights reserved.
 *
 * This file is part of the pairinteraction library.
 *
 * The pairinteraction library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The pairinteraction library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the pairinteraction library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "QuantumDefect.h"
#include "SQLite.h"
#include "Wavefunction.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <iostream>

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

template <int l>
struct Fixture {
    QuantumDefect qd;
    Fixture() : qd("Rb", 79, l, 1.5){};
};

TEMPLATE_TEST_CASE_METHOD_SIG(Fixture, "model_potentials", "[qd]", ((int V), V), 1, 2) // NOLINT
{
    using T = Fixture<V>;
    // There could be better coverage
    CHECK(std::isnan(model_potential::V(T::qd, 0)));
    CHECK(std::isnan(model_potential::g(T::qd, 0)));
}

TEMPLATE_TEST_CASE_METHOD_SIG(Fixture, "numerovs_method", "[qd]", ((int V), V), 1, 2) // NOLINT
{
    using T = Fixture<V>;
    Numerov N(T::qd);
    auto const &xy = N.integrate();

    // Check for correct number of integration steps
    CHECK(xy.rows() == 12087);

    // Check for correct upper bound and decay to zero
    CHECK(xy(xy.rows() - 1, 0) <= std::sqrt(2 * T::qd.n * (T::qd.n + 15)));
    CHECK_THAT(xy(xy.rows() - 1, 1), WithinAbs(0.0, 1e-6));
}

#ifdef WITH_GSL
TEMPLATE_TEST_CASE_METHOD_SIG(Fixture, "coulomb_functions", "[qd]", ((int V), V), 1, 2) // NOLINT
{
    using T = Fixture<V>;
    Whittaker W(T::qd);
    auto const &xy = W.integrate();

    // Check for correct number of integration steps
    CHECK(xy.rows() == 12087);

    // Check for correct upper bound and decay to zero
    CHECK(xy(xy.rows() - 1, 0) <= 2 * T::qd.n * (T::qd.n + 15));
    CHECK_THAT(xy(xy.rows() - 1, 1), WithinAbs(0.0, 1e-6));
}

TEMPLATE_TEST_CASE_METHOD_SIG(Fixture, "method_comparison", "[qd]", ((int V), V), 1, 2) // NOLINT
{
    using T = Fixture<V>;
    Numerov N(T::qd);
    Whittaker W(T::qd);
    auto const &nxy = N.integrate();
    auto const &wxy = W.integrate();

    // Check whether both have the same number of points
    CHECK(nxy.rows() == wxy.rows());
    size_t n = nxy.rows();

    // Compare pointwise
    for (size_t i = 0; i < n; ++i) {
        CHECK_THAT(std::sqrt(nxy(i, 0)) * nxy(i, 1) - wxy(i, 1), WithinAbs(0.0, 1e-2));
    }
}
TEMPLATE_TEST_CASE_METHOD_SIG(Fixture, "integration", "[qd]", ((int V), V), 1, 2) // NOLINT
{
    using T = Fixture<V>;
    double mu_n = IntegrateRadialElement<Numerov>(T::qd, 1, T::qd);
    double mu_w = IntegrateRadialElement<Whittaker>(T::qd, 1, T::qd);
    CHECK_THAT(mu_n, WithinRel(mu_w, 1e-3)); // corresponds to 0.1% deviation
}
#endif
