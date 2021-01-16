#pragma once
#include <fmt/format.h>

#include <array>
#include <cstdint>
#include <optional>
#include <string_view>

struct alignas(4) ipv4 {
    std::array<std::uint8_t,4> octets;

    ipv4() : octets{{0,0,0,0}} {}
    ipv4(std::uint8_t n1, std::uint8_t n2, std::uint8_t n3, std::uint8_t n4) : octets{{n1,n2,n3,n4}} {}

    static std::optional<ipv4> parse(std::string_view line);

    friend bool operator==(ipv4 lhs, ipv4 rhs) noexcept {
        return lhs.octets == rhs.octets;
    }

    /**
     * Predicate for std::sort to specify lexicographical order
     * @param lhs
     * @param rhs
     * @return true if lhs < rhs
     */
    static bool ascending(ipv4 lhs, ipv4 rhs) noexcept {
        return lhs.octets < rhs.octets;
    }

    /**
     * Predicate for std::sort to specify reverse lexicographical order
     * @param lhs
     * @param rhs
     * @return true if rhs < lhs
     */
    static bool descending(const ipv4& lhs, const ipv4& rhs) noexcept {
        return rhs.octets < lhs.octets;
    }
};

template <> struct fmt::formatter<ipv4>: formatter<string_view> {
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(ipv4 adr, FormatContext& ctx) {
        // auto format(const point &p, FormatContext &ctx) -> decltype(ctx.out()) // c++11
        return format_to(ctx.out(), "{}", fmt::join(adr.octets, "."));
    }
};
