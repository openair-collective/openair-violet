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
    void saveConfig();
    void createConfig();
    bool loadConfig();
    void printConfig();
    void eraseConfig();

public:
    struct Config_t
    {
        char *ssid;
        char *password;
        char *hostname;
        char *serverName;
        byte numTempSensors;
    };

    struct CopyRightInfo_t
    {
        char *project_version;
        char *project_name;
        char *project_author;
        char *project_description;
        char *project_url;
        char *project_creator_email;
        char *project_license;
        char *project_copyright;
    };

    CopyRightInfo_t copyRightInfo_t;

    Config_t config_t;

private:
};

extern Project_Config project_config;

#endif // CONFIG_HPP