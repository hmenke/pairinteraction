#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "utils.h"

// clang-format off
#if defined(WITH_BOOST_FILESYSTEM)
#    include <boost/filesystem.hpp>
#elif defined(__has_include)
#    if __has_include(<filesystem>)
#        include <filesystem>
#        define cxx17_filesystem 2
#    elif __has_include(<experimental/filesystem>)
#        include <experimental/filesystem>
#        define cxx17_filesystem 1
#    else
#        error "Compiler does not support <filesystem> or <experimental/filesystem>"
#    endif
#else
#    error "Compiler does not support __has_include"
#endif
// clang-format on

namespace fs {

#if defined(WITH_BOOST_FILESYSTEM)
using namespace boost::filesystem;
#elif cxx17_filesystem == 2
using namespace std::filesystem;
#elif cxx17_filesystem == 1
using namespace std::experimental::filesystem;
#else
#error "Compiler does not support <filesystem> or <experimental/filesystem>"
#endif

/// \brief Generate a unique path
///
/// Actually this path is not unique, but just a random string of four groups
/// of hex digits.  This is supposed to mirror Boost.Filesystem, but I'm not
/// sure whether it does that.  If you don't call this function too often it
/// should do for most cases.
///
/// \param p   path template to be filled with randomness ('%' is the replacement char)
/// \returns random path based on the template \p p
inline path unique_path(path const &p = "%%%%-%%%%-%%%%-%%%%") {
    path::string_type s(p.native());

    char const hex[] = "0123456789abcdef";
    auto end = sizeof(hex) - 2;
    decltype(end) begin = 0;
    char const percent = '%';

    for (auto &i : s) {
        if (s[i] == percent) {
            size_t idx = utils::randint(begin, end);
            i = hex[idx];
        }
    }

    return s;
}

} // namespace fs

#endif // FILESYSTEM_H
