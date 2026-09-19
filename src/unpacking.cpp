#include "unpacking.h"

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;


std::string fileEx(const std::string& package)
{
    if (package.ends_with(".tar.gz") || package.ends_with(".tgz"))
        return "tar -xzf \"" + package + "\" > /dev/null 2>&1";

    if (package.ends_with(".tar.xz"))
        return "tar -xJf \"" + package + "\" > /dev/null 2>&1";

    if (package.ends_with(".tar.bz2"))
        return "tar -xjf \"" + package + "\" > /dev/null 2>&1";

    if (package.ends_with(".tar.zst"))
        return "tar --zstd -xf \"" + package + "\" > /dev/null 2>&1";

    if (package.ends_with(".tar"))
        return "tar -xf \"" + package + "\" > /dev/null 2>&1";

    if (package.ends_with(".deb"))
    {
        std::string command_deb =
            "ar -x \"" + package + "\" > /dev/null 2>&1";

        system(command_deb.c_str());

        // Ищем data.tar.*
        for (const auto& entry : fs::directory_iterator("."))
        {
            if (!entry.is_regular_file())
                continue;

            std::string filename =
                entry.path().filename().string();

            if (filename == "data.tar.xz" ||
                filename == "data.tar.gz" ||
                filename == "data.tar.zst")
            {
                return fileEx(filename);
            }
        }

        return "";
    }

    return "";
}


void unpack(const std::string& package)
{
    std::string file;
    
    for (const auto& entry : fs::directory_iterator("."))
    {
        if (!entry.is_regular_file())
            continue;

        std::string filename =
            entry.path().filename().string();

        if (filename.rfind(package + ".", 0) == 0)
        {
            file = entry.path().string();
            break;
        }
    }

    if (file.empty())
    {
        std::cerr << "Package not found.\n";
        return;
    }

    std::cout << "Found: " << file << '\n';

    std::string command = fileEx(file);

    if (command.empty())
    {
        std::cerr << "Unknown package format.\n";
        return;
    }

    system(command.c_str());
}