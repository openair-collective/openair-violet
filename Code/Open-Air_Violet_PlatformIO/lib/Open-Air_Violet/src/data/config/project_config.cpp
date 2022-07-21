#include "project_config.hpp"

Config config("config", "nvs");

Project_Config::Project_Config() {}

Project_Config::~Project_Config() {}

bool Project_Config::begin()
{
    bool success = config.begin();
    if (!success)
    {
        log_e("Failed to begin config");
        return false;
    }
    return true;
}

void Project_Config::createConfig()
{
    copyRightInfo_t = {
        .project_version = "",
        .project_name = "",
        .project_author = "",
        .project_description = "",
        .project_url = "",
        .project_creator_email = "",
        .project_license = "",
        .project_copyright = "",
    };

    config_t = {
        .ssid = "",
        .password = "",
        .serverName = "",
    };
}

void Project_Config::saveConfig()
{
    config.write("project_config", config_t);

    config.write("config_version", "1.0");
    config.write("project_name", "OpenAir Violet");
    config.write("project_version", "1.0");
    config.write("project_author", "OpenAir-Collective");
    config.write("project_description", "OpenAir Violet CDR");
    config.write("project_url", "https://openaircollective.cc");
    config.write("project_creator_email", "zacariah@prometheontechnologies.com");
    config.write("project_license", "MIT");
    config.write("project_copyright", "Copyright (c) 2022 OpenAir-Collective");
}

bool Project_Config::loadConfig()
{
    if (!config.begin())
    {
        log_e("Failed to begin config");
        return false;
    }

    if (config.getValueLength("project_config") < 1)
    {
        log_e("Config not found");
        return false;
    }

    //config.read("project_config", config_t);

    config.read("project_name", copyRightInfo_t.project_name);
    config.read("project_version", copyRightInfo_t.project_version);
    config.read("project_author", copyRightInfo_t.project_author);
    config.read("project_description", copyRightInfo_t.project_description);
    config.read("project_url", copyRightInfo_t.project_url);
    config.read("project_creator_email", copyRightInfo_t.project_creator_email);
    config.read("project_license", copyRightInfo_t.project_license);
    config.read("project_copyright", copyRightInfo_t.project_copyright);

    return true;
}

void Project_Config::printConfig()
{
    Serial.printf("project_name: %s \n", copyRightInfo_t.project_name);
    Serial.printf("project_version: %s \n", copyRightInfo_t.project_version);
    Serial.printf("project_author: %s \n", copyRightInfo_t.project_author);
    Serial.printf("project_description: %s \n", copyRightInfo_t.project_description);
    Serial.printf("project_url: %s \n", copyRightInfo_t.project_url);
    Serial.printf("project_creator_email: %s \n", copyRightInfo_t.project_creator_email);
    Serial.printf("project_license: %s \n", copyRightInfo_t.project_license);
    Serial.printf("project_copyright: %s \n", copyRightInfo_t.project_copyright);
    
    Serial.printf("ssid: %s \n", config_t.ssid);
}

void Project_Config::eraseConfig()
{
    config.clear();
}

Project_Config project_config;