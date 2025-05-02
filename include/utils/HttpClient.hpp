#pragma once

#include <string>
#include <vector>
#include "json.hpp"

class HttpClient {
public:
    static nlohmann::json get(const std::string& url); 
    static nlohmann::json post(const std::string& url, const nlohmann::json& data);  
    static nlohmann::json post(const std::string& url, const nlohmann::json& data, const std::vector<std::string>& headers);  
};
