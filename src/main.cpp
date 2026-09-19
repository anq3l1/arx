#include <iostream>
#include "handlers.h"

int main(int argc, char* argv[])
{
    if (argc > 1 && std::string(argv[1]) == "-S")
    {
        install(argv[2]);

        std::cout << "Install: " << argv[2] << " succefully!\n";
    }

    return 0;
}