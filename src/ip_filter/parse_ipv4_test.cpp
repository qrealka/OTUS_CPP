#include "ipv4.h"
#include <catch2/catch.hpp>

using namespace std::string_view_literals;

TEST_CASE("Parse valid IP", "[ip_filter]")
{
    REQUIRE(ipv4{1,1,1,1} == *ipv4::parse("1.1.1.1"sv));
    REQUIRE(ipv4{255,255,255,255} == *ipv4::parse("255.255.255.255"sv));
    REQUIRE(ipv4{0,0,0,0} == *ipv4::parse("0.0.0.0"sv));
    REQUIRE(ipv4{0,1,2,3} == *ipv4::parse("000000000.000000000000000001.02.00000000000000000000000000003"sv));
}

TEST_CASE("Parse invalid IP", "[ip_filter]")
{
    SECTION("Short strings")
    {
        REQUIRE(std::nullopt == ipv4::parse(""sv));
        REQUIRE(std::nullopt == ipv4::parse("1"sv));
        REQUIRE(std::nullopt == ipv4::parse("."sv));
        REQUIRE(std::nullopt == ipv4::parse("\n"sv));
        REQUIRE(std::nullopt == ipv4::parse("\t"sv));
        REQUIRE(std::nullopt == ipv4::parse("0x0"sv));
        REQUIRE(std::nullopt == ipv4::parse("1.1.1."sv));
    }

    SECTION("Leading & trailing spaces")
    {
        REQUIRE(std::nullopt == ipv4::parse("1.1.1.1 "sv));
        REQUIRE(std::nullopt == ipv4::parse(" 1.1.1.1"sv));
    }

    SECTION("Long strings")
    {
        REQUIRE(std::nullopt == ipv4::parse("1.1.1.1.1"sv));
        REQUIRE(std::nullopt == ipv4::parse("1.1.1.1..........."sv));
        REQUIRE(std::nullopt == ipv4::parse("11111111"sv));
        REQUIRE(std::nullopt == ipv4::parse("                       "sv));
    }

    SECTION("More than byte")
    {
        REQUIRE(std::nullopt == ipv4::parse("256.256.256.256"sv));
        REQUIRE(std::nullopt == ipv4::parse("1000000000000.999999999999999999999999999999.8888888888888.0"sv));
        REQUIRE(std::nullopt == ipv4::parse("300.300.300.300"sv));
        REQUIRE(std::nullopt == ipv4::parse("-1.-2.-3.-4"sv));
    }
}