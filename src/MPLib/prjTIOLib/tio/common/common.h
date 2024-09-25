#pragma once
#include "TSMaster.h"
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
    native_int hConfigFile = NULL;
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
    // servo pedal force control(FPC)
    bool FPFCPosVSPresIsCalibrated;
    bool FPFCPresVSForceIsCalibrated;
    std::string FPFCPosVSPresPosition;
    std::string FPFCPosVSPresPressure;
    std::string FPFCPresVSForcePressure;
    std::string FPFCPresVSForceForce;
    float FPFCMCMaxPressure;
    float FPFCMCMinForce;

    bool GetConfigFile();
    void InitConfigFile();
    void LoadConfigFile();
    void UpdateConfigFile();

};

extern TTIOConfig vTIOConfig;
extern std::string vMP_Name;

std::string GetCurrentModuleName();