#include "lib.h"

#include <fmt/format.h>
#include <fmt/printf.h>

int main ()
{
    fmt::print(FMT_STRING("build {:d}\nHello, World!\n"), version());
    return 0;
}
