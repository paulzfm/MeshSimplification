#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Simplifier.h"

int main(int argc, char** argv)
{
    if (argc != 4 && argc != 5) {
        fprintf(stderr, "Usage: %s <input> <output> <percentage> [-mid]\n", argv[0]);
        exit(1);
    }

    bool middle = false;
    if (argc == 5 && strcmp(argv[4], "-mid") == 0) {
        middle = true;
    }
    Simplifier simplifier(std::string(argv[1]), atof(argv[3]), middle);
    simplifier.simplify();
    simplifier.output(std::string(argv[2]));

    return 0;
}