#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Simplifier.h"

int main(int argc, char** argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input> <output> <percentage>\n", argv[0]);
        exit(1);
    }

    Simplifier simplifier(std::string(argv[1]), atof(argv[3]));
    simplifier.simplify();
    simplifier.output(std::string(argv[2]));

    return 0;
}