#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <filesystem> // 需要包含filesystem头文件


class TTIOConfig {
public:
    std::string FConfigIniFile = "";
    // form
    bool FServoFormIsActive;
    bool FMappingFormIsActive;
    bool FDeltaPowerFormIsActive;
    bool FITechPowerFormIsActive;
    bool FAMPPowerFormIsActive;
    // delta power
    std::string FDeltaPowerIP;
    int32_t FDeltaPowerPort;
    bool FDeltaPowerAutoConnect;
    float FDeltaPowerMaxVoltage;
    // itech power
    std::string FITechPowerIP;
    int32_t FITechPowerPort;
    int32_t FITechType;
    bool FITechPowerAutoConnect;
    float FITechPowerProtectVoltage;
    float FItechPowerMaxCurrent;
    float FItechPowerMinCurrent;
    // amp power
    std::string FAMPPowerIP;
    int32_t FAMPPowerPort;
    bool FAMPPowerAutoConnect;
    bool FAMPPowerAvailabe;
    // amp load
    std::string FAMPLoadIP;
    int32_t FAMPLoadPort;
    bool FAMPLoadAutoConnect;
    bool FAMPLoadAvailabe;
    // servo
    bool FRotateServoIsAvailable;
    bool FAirCylinderAvailable;
    bool FServoAutoConnect;
    float FServo2Speed;
    float FServo2MountAngle;
    float FServo1MaxPosition;
    float FServo1MinPosition;
    std::string FS7IPAddress;
    float FMCMaxPressure;
    float FPressure2CurrentFactor;
    float FPressure2CurrentOffset;
    float FAirValveMaxCurrent;
    float FAirValveMinCurrent;
    float FPSMaxPressure;

    bool GetConfigFile();
    void InitIniFile();
    void LoadConfigValue();
    void SaveConfig();

private:
    void WriteBoolean(std::ofstream& file, const std::string& section, const std::string& key, bool value, std::string& currentSection);
    void WriteString(std::ofstream& file, const std::string& section, const std::string& key, const std::string& value, std::string& currentSection);
    void WriteInteger(std::ofstream& file, const std::string& section, const std::string& key, int32_t value, std::string& currentSection);
    void WriteFloat(std::ofstream& file, const std::string& section, const std::string& key, float value, std::string& currentSection);
    bool ReadBoolean(std::ifstream& file, const std::string& section, const std::string& key, bool defaultValue);
    std::string ReadString(std::ifstream& file, const std::string& section, const std::string& key, const std::string& defaultValue);
    int32_t ReadInteger(std::ifstream& file, const std::string& section, const std::string& key, int32_t defaultValue);
    float ReadFloat(std::ifstream& file, const std::string& section, const std::string& key, float defaultValue);
    bool ValueExists(std::ifstream& file, const std::string& section, const std::string& key);
};

extern TTIOConfig vTIOConfig;
extern std::string vMP_Name;

std::string GetCurrentModuleName();