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
        char ssid[32];
        char password[50];
        char hostname[100];
        char serverName[100];
        byte numTempSensors;
    };

    struct CopyRightInfo_t
    {
        char project_version[10];
        char project_name[32];
        char project_author[50];
        char project_description[300];
        char project_url[1000];
        char project_creator_email[1000];
        char project_license[10];
        char project_copyright[1000];
    };

    CopyRightInfo_t copyRightInfo_t;

    Config_t config_t;

private:
};

extern Project_Config project_config;

#endif // CONFIG_HPP