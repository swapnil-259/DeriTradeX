#pragma once
#include <string>
#include "json.hpp"

class HttpClient {
public:
    static nlohmann::json get(const std::string& url);
    static nlohmann::json post(const std::string& url, const nlohmann::json& data);
};
