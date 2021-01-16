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

static_assert(sizeof(ipv4) == 4);
static_assert(std::is_trivially_copyable_v<ipv4>);