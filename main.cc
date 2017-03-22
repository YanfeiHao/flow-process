#include "utility/ScopeTools.hpp"
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    auto p = malloc (100);

    SCOPE_EXIT { ::free (p); };
    return 0;
}
