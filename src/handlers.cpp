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

    std::string file_tar = package + ".tar.gz";

    FILE* file = fopen(file_tar.c_str(), "wb");

    std::string url = parsingJsonUrl(package);

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