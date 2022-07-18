#ifndef PROJECT_CONFIG_HPP
#define PROJECT_CONFIG_HPP
#include <Arduino.h>
#include <preferencesAPI.hpp>

class Project_Config
{
public:
    Project_Config();
    virtual ~Project_Config();
    bool begin();
    void createConfig();
    bool loadConfig();
    void printConfig();

public:
    struct Config_t
    {
        const char *config_version;
        const char *project_name;
        const char *project_version;
        const char *project_author;
        const char *project_description;
        const char *project_url;
        const char *project_creator_email;
        const char *project_license;
        const char *project_copyright;
        const char *ssid;
        const char *password;
    };

    Config_t config_t;

private:
};

extern Project_Config project_config;

#endif // CONFIG_HPP