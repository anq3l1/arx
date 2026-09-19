#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

std::string jsonUrl(std::string package_name)
{
    std::ifstream file("packages.json");

    if (!file.is_open())
    {
        std::cerr << "ERROR: Cannot open packages.json\n";
        return "";
    }

    json data;
    file >> data;

    if (!data.contains(package_name))
    {
        std::cerr << "ERROR: Package not found: "
                  << package_name << '\n';
        return "";
    }

    std::string url = data[package_name]["url"];

    return url;
}

std::string jsonNameAndVersion(std::string package_name)
{
    std::ifstream file("packages.json");

    if (!file.is_open())
    {
        std::cerr << "ERROR: Cannot open packages.json\n";
        return "";
    }

    json data;
    file >> data;

    if (!data.contains(package_name))
    {
        std::cerr << "ERROR: Package not found: "
                  << package_name << '\n';
        return "";
    }

    std::string name = data[package_name]["name"];
    std::string version = data[package_name]["version"];

    std::string nv = name + "-" + version;

    return nv;
}