/*
 * Copyright (c) 2016 Sebastian Weber, Henri Menke. All rights reserved.
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

#ifndef HAMILTONIAN_TWO_H
#define HAMILTONIAN_TWO_H

#include "Basisnames.h"
#include "ConfParser.h"
#include "Hamiltonian.h"
#include "HamiltonianOne.h"
#include "MatrixElements.h"
#include "SQLite.h"
#include "dtypes.h"

#include <boost/algorithm/hex.hpp>
#include <boost/math/special_functions/binomial.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <cmath>
#include <experimental/filesystem>
#include <iostream>
#include <memory>

class HamiltonianTwo : public Hamiltonian<BasisnamesTwo> {
public:
    HamiltonianTwo(const Configuration &config, std::experimental::filesystem::path &path_cache,
                   const std::shared_ptr<HamiltonianOne> &hamiltonian_one);
    HamiltonianTwo(const Configuration &config, std::experimental::filesystem::path &path_cache,
                   std::shared_ptr<HamiltonianOne> hamiltonian_one1,
                   std::shared_ptr<HamiltonianOne> hamiltonian_one2);
    void calculate(const Configuration &conf_tot);

private:
    std::shared_ptr<HamiltonianOne> hamiltonian_one1; // TODO const HamiltonianOne
    std::shared_ptr<HamiltonianOne> hamiltonian_one2;
    double deltaE;
    int deltaN;
    int deltaL;
    int deltaJ;
    int deltaM;
    size_t nSteps_two;
    std::string species1, species2;
    double min_R, max_R;
    int multipoleexponent;
    bool samebasis;
    std::experimental::filesystem::path path_cache;
};

#endif // HAMILTONIAN_TWO_H
