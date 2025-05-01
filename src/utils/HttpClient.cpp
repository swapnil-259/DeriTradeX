#include "utils/HttpClient.hpp"
#include <curl/curl.h>
#include <sstream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

nlohmann::json HttpClient::get(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string responseStr;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStr);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return nlohmann::json::parse(responseStr);
}

nlohmann::json HttpClient::post(const std::string& url, const nlohmann::json& data) {
    CURL* curl = curl_easy_init();
    std::string responseStr;

    if (curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        std::string payload = data.dump();

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStr);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return nlohmann::json::parse(responseStr);
}

