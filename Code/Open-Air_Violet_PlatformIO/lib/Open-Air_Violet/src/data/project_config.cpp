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

    if (!config.contains("config_version"))
    {
        log_e("Config version not found");
        return false;
    }
    
    config.read("config_version", config_t.config_version);
    config.read("project_name", config_t.project_name);
    config.read("project_version", config_t.project_version);
    config.read("project_author", config_t.project_author);
    config.read("project_description", config_t.project_description);
    config.read("project_url", config_t.project_url);
    config.read("project_creator_email", config_t.project_creator_email);
    config.read("project_license", config_t.project_license);
    config.read("project_copyright", config_t.project_copyright);
}

void Project_Config::printConfig()
{
    log_i("config_version: %s", config_t.config_version);
    log_i("project_name: %s", config_t.project_name);
    log_i("project_version: %s", config_t.project_version);
    log_i("project_author: %s", config_t.project_author);
    log_i("project_description: %s", config_t.project_description);
    log_i("project_url: %s", config_t.project_url);
    log_i("project_creator_email: %s", config_t.project_creator_email);
    log_i("project_license: %s", config_t.project_license);
    log_i("project_copyright: %s", config_t.project_copyright);
}







Project_Config project_config;