#include "unpacking.h"

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void unpack(const std::string package)
{
    std::string file = package + ".tar.gz";

    if(fs::exists(file))
    {

        std::string command_tar = "tar -xvf " + file + " > /dev/null 2>&1"; 

        system(command_tar.c_str());
    }
    else
        std::cerr << "Not find a tar file.\n";
}