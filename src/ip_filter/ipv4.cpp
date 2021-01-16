#include "ipv4.h"

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/array.hpp> // adapt array to tuple for x3::parse

namespace x3 = boost::spirit::x3;

std::optional<ipv4> ipv4::parse(std::string_view line)
{
    if (line.size() < 7UL) {
        return std::nullopt;
    }
    std::uint8_t octets[4] = {};

    // these iterators should be l-value, b/c the first parse argument pass by reference
    auto first = line.cbegin();
    auto last = line.cend();
    auto octet = x3::uint_parser<std::uint8_t>{};
    auto result = x3::parse(first, last,
                            octet >> '.' >> octet >> '.' >> octet >> '.' >> octet,
                            octets);

    if (!result || first != last) {
        return std::nullopt;
    }
    return ipv4{octets[0], octets[1], octets[2], octets[3]};
}

// ipv4 sizeof  should be less than 2-3 machine words
// and trivial copyable - ABI said that registers should be used
// pass by value more optimal than pass by reference for this case
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f16-for-in-parameters-pass-cheaply-copied-types-by-value-and-others-by-reference-to-const
static_assert(sizeof(ipv4) <= sizeof(std::int32_t), "Size ipv4 address should be less than 3 machine words");
// https://wiki.osdev.org/System_V_ABI
static_assert(std::is_trivially_copyable_v<ipv4>, "Intel x86-64 ABI: 3.2.3 Parameter passing: Classification of aggregates");