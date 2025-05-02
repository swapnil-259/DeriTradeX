// HttpClient.cpp
#include "utils/HttpClient.hpp"
#include <curl/curl.h>
#include <stdexcept>
#include <iostream>

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

json HttpClient::get(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string responseStr;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStr);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            throw std::runtime_error("CURL GET failed: " + std::string(curl_easy_strerror(res)));
        }
    }

    return json::parse(responseStr);
}

json HttpClient::post(const std::string& url, const json& data) {
    return post(url, data, {"Content-Type: application/json"});
}

json HttpClient::post(const std::string& url, const json& data, const std::vector<std::string>& headers) {
    CURL* curl = curl_easy_init();
    std::string responseStr;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        std::string jsonData = data.dump();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        struct curl_slist* curlHeaders = nullptr;
        for (const auto& header : headers) {
            curlHeaders = curl_slist_append(curlHeaders, header.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStr);

        CURLcode res = curl_easy_perform(curl);
        curl_slist_free_all(curlHeaders);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            throw std::runtime_error("CURL POST failed: " + std::string(curl_easy_strerror(res)));
        }
    }

    return json::parse(responseStr);
}
