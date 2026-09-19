#include <iostream>
#include <curl/curl.h>
#include <string>
#include "json.h"
#include "unpacking.h"

std::string install(std::string package)
{
    CURL* curl = curl_easy_init();

    if (!curl)
        return "1";

    std::cout << "Download: " <<  package << "...\n";

    std::string url = jsonUrl(package);

    std::string extension;

    if (url.find(".tar.gz") != std::string::npos)
        extension = ".tar.gz";
    else if (url.find(".tar.xz") != std::string::npos)
        extension = ".tar.xz";
    else if (url.find(".tar.bz2") != std::string::npos)
        extension = ".tar.bz2";
    else if (url.find(".zip") != std::string::npos)
        extension = ".zip";
    else if (url.find(".deb") != std::string::npos)
        extension = ".deb";
    else
        extension = ".tar.gz";

    std::string file_tar = package + extension;

    FILE* file = fopen(file_tar.c_str(), "wb");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    curl_easy_setopt(
    curl,
    CURLOPT_FOLLOWLOCATION,
    1L
    );

    curl_easy_setopt(
    curl,
    CURLOPT_USERAGENT,
    "vpm/0.1"
    );

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK)
    {
        printf("Error: %s\n",
               curl_easy_strerror(result));
    }
    else
        std::cout << "Download complete!\n";

    fclose(file);
    curl_easy_cleanup(curl);

    unpack(package);

    return "0";
}