#include "lib.h"

#include <fmt/format.h>

int main ()
{
    fmt::print(FMT_STRING("build {:d}\nHello, World!\n"), version());
    return 0;
}
