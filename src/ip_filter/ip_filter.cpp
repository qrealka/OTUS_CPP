#include "ipv4.h"

#include <fmt/printf.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<ipv4> ip_pool;

    try {
        for (std::string line; std::getline(std::cin, line);) {
            auto tab_pos = line.find_first_not_of('\t');
            if (tab_pos == line.npos) {
                ip_pool.push_back(*ipv4::parse(line));
            } else {
                ip_pool.push_back(*ipv4::parse(std::string_view{ line.c_str(), tab_pos }));
            }
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), ipv4::descending);
        fmt::print("{}\n", fmt::join(ip_pool, "\n"));

        // first octet equals 1
        auto first_octet_is = [](ipv4 ip) { return ip.octets[0] == 1; };
        for(auto ip : ip_pool) {
            if (first_octet_is(ip)) {
                fmt::print("{}\n", ip);
            }
        }

        // first octet equals 46 & second octet equals 70
        auto first_second_is = [](ipv4 ip) { return ip.octets[0] == 46 && ip.octets[1] == 70; };
        for(auto ip : ip_pool) {
            if (first_second_is(ip)) {
                fmt::print("{}\n", ip);
            }
        }

        // any octet equals 46
        for(auto ip : ip_pool) {
            if (std::any_of(ip.octets.begin(), ip.octets.end(), 46)) {
                fmt::print("{}\n", ip);
            }
        }
    } catch (const std::bad_optional_access& parse_err) {
        fmt::print(std::cerr, "Wrong input data format: {:s}\n", parse_err.what());
    } catch (const std::exception& unexpected) {
        fmt::print(std::cerr, "Unexpected error: {:s}\n", unexpected.what());
    }
}
