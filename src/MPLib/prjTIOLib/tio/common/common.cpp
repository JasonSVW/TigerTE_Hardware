#include "common.h"
#include "TSMaster.h"
#include <windows.h>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
namespace fs = std::filesystem;

TTIOConfig vTIOConfig;
std::string vMP_Name = "tio";

#define INI_FILE "TIO\\TIOConfiguration.ini"

int update_config_from_configure_file() {
    vTIOConfig.LoadConfigFile();
    return 0;
}

bool ensureFileExists(const std::string& filePath) {
    bool IsFileExist = false;
    fs::path pathObj(filePath);

    // 检查文件是否存在
    if(fs::exists(pathObj)) {
        log_hint("File already exists: %s", filePath.c_str());
        IsFileExist = true;
    }
    else {
        // 检查父路径是否存在，不存在则创建
        fs::path parentPath = pathObj.parent_path();
        if(!fs::exists(parentPath)) {
            std::cout << "Directory does not exist. Creating: " << parentPath << std::endl;
            fs::create_directories(parentPath);
        }

        // 创建文件
        std::ofstream file(filePath);
        if(file) {
            log_hint("File already exists: %s", filePath.c_str());
            IsFileExist = true;

        }
        else {
            log_nok("File already exists: %s", filePath.c_str());
            IsFileExist = false;
        }
        file.close();
    }
    return IsFileExist;
}

std::string WideCharToMultiByte(const std::wstring& wstr) {
    if(wstr.empty()) return std::string();

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int) wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int) wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

std::string GetCurrentModuleName() {
    wchar_t path[MAX_PATH];
    HMODULE hModule = NULL;

    // 使用 GetModuleHandleExW 代替 GetModuleHandleEx
    if(GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCWSTR) GetCurrentModuleName,
        &hModule) == 0) {
        // 处理错误
        return "tio";
    }

    // 使用 GetModuleFileNameW 代替 GetModuleFileName
    if(GetModuleFileNameW(hModule, path, MAX_PATH) == 0) {
        // 处理错误
        return "tio";
    }

    //std::filesystem::path p(path);
    //return p.filename().wstring();
    std::filesystem::path p(path);
    std::wstring filename = p.filename().wstring();

    // 找到最后一个点号的位置
    size_t pos = filename.find_last_of(L'.');
    if(pos != std::wstring::npos) {
        // 提取不带后缀的名称
        return WideCharToMultiByte(filename.substr(0, pos));
    }
    return WideCharToMultiByte(filename);
}

void TTIOConfig::UpdateConfigFile() {
    if(!GetConfigFile()) {
        log_nok("Can not get TSMaster project configuration path.");
        return;
    }
    if(FConfigIniFile.empty()) {
        log_nok("Configuration file is not specified.");
        return;
    }
    if(0 == app.ini_create(FConfigIniFile.c_str(), &hConfigFile)) {
        log("ini object created: %x", hConfigFile);
    }
    else {
        log_nok("ini object creation failed.");
        return;
    }

    app.ini_write_bool(hConfigFile, "TIO_CONFIG", "SERVO_FORM", FServoFormIsActive);
    app.ini_write_bool(hConfigFile, "TIO_CONFIG", "MAPPING_FORM", FMappingFormIsActive);
    app.ini_write_bool(hConfigFile, "TIO_CONFIG", "DELTA_FORM", FDeltaPowerFormIsActive);
    app.ini_write_bool(hConfigFile, "TIO_CONFIG", "ITECH_FORM", FITechPowerFormIsActive);
    app.ini_write_bool(hConfigFile, "TIO_CONFIG", "AMP_FORM", FAMPPowerFormIsActive);
    app.ini_write_string(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_IP", FDeltaPowerIP.c_str());
    app.ini_write_int32(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT", FDeltaPowerPort);
    app.ini_write_bool(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT", FDeltaPowerAutoConnect);
    app.ini_write_float(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE", FDeltaPowerMaxVoltage);
    app.ini_write_string(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_IP", FITechPowerIP.c_str());
    app.ini_write_int32(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT", FITechPowerPort);
    app.ini_write_int32(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_TYPE", FITechType);
    app.ini_write_bool(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT", FITechPowerAutoConnect);
    app.ini_write_float(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE", FITechPowerProtectVoltage);
    app.ini_write_float(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT", FItechPowerMaxCurrent);
    app.ini_write_float(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT", FItechPowerMinCurrent);
    app.ini_write_string(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_IP", FAMPPowerIP.c_str());
    app.ini_write_int32(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_PORT", FAMPPowerPort);
    app.ini_write_bool(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT", FAMPPowerAutoConnect);
    app.ini_write_bool(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_AVAILABLE", FAMPPowerAvailabe);
    app.ini_write_string(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_IP", FAMPLoadIP.c_str());
    app.ini_write_int32(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT", FAMPLoadPort);
    app.ini_write_bool(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT", FAMPLoadAutoConnect);
    app.ini_write_bool(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE", FAMPLoadAvailabe);
    app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE", FRotateServoIsAvailable);
    app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE", FAirCylinderAvailable);
    app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "SERVO_AUTO_CONNECT", FServoAutoConnect);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE", FServo2MountAngle);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "SERVO2_SPEED", FServo2Speed);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "SERVO1_MAX_POSITION", FServo1MaxPosition);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "SERVO1_MIN_POSITION", FServo1MinPosition);
    app.ini_write_string(hConfigFile, "SERVO_CONFIG", "S7_IP", FS7IPAddress.c_str());
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_MAX", FMCMaxPressure);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR", FPressure2CurrentFactor);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET", FPressure2CurrentOffset);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX", FAirValveMaxCurrent);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PUMP_STATION_PRESSURE_MAX", FPSMaxPressure);
    // add for pedal force control
    app.ini_write_string(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_POSITION", FPFCPosVSPresPosition.c_str());
    app.ini_write_string(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_PRESSURE", FPFCPosVSPresPressure.c_str());
    app.ini_write_string(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_PRESSURE", FPFCPresVSForcePressure.c_str());
    app.ini_write_string(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_FORCE", FPFCPresVSForceForce.c_str());
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MAX_PRESSURE", FPFCMCMaxPressure);
    app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_CALIBRATED", FPFCPosVSPresIsCalibrated);
    app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_CALIBRATED", FPFCPresVSForceIsCalibrated);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MIN_FORCE", FPFCMCMinForce);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_IDLE_STROKE", FPFCMCIdleStroke);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MAX_PRESSURE_DOWN_LIMIT", FPFCMCMaxPressureDownLimit);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MAX_CALIBRATED_FORCE", FFPCMCMaxCalibratedForce);
    app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MIN_CALIBRATED_FORCE", FFPCMCMinCalibratedForce);

    if(0 == app.ini_close(hConfigFile)) {
        log("config file updated");
        hConfigFile = NULL;
    }

}

bool TTIOConfig::GetConfigFile() {
    std::string AConfigFolder;
    char* s;
    if(app.get_configuration_file_path(&s) == 0) {
        AConfigFolder = std::string(s);
        FConfigIniFile = AConfigFolder + INI_FILE;
        return true;
    }
    else {
        return false;
    }
}

void TTIOConfig::LoadConfigFile() {
    if(!GetConfigFile()) {
        log_nok("Can not get TSMaster project configuration path.");
        return;
    }
    if(FConfigIniFile.empty()) {
        log_nok("Configuration file is not specified.");
        return;
    }
    if(0 == app.ini_create(FConfigIniFile.c_str(), &hConfigFile)) {
        log("ini object created: %x", hConfigFile);
    }
    else {
        log_nok("ini object creation failed.");
        return;
    }
    bool aReadBoolValue = false;
    int aReadIntValue = 0;
    double aReadFloatValue = 0.0f;
    char aReadStringValue[1000] = {};
    int aStringLength = 1000;

    if(0 == app.ini_read_bool(hConfigFile, "TIO_CONFIG", "SERVO_FORM", &aReadBoolValue, false)) FServoFormIsActive = aReadBoolValue;
    if(0 == app.ini_read_bool(hConfigFile, "TIO_CONFIG", "DELTA_FORM", &aReadBoolValue, false)) FDeltaPowerFormIsActive = aReadBoolValue;
    if(0 == app.ini_read_bool(hConfigFile, "TIO_CONFIG", "ITECH_FORM", &aReadBoolValue, false)) FITechPowerFormIsActive = aReadBoolValue;
    if(0 == app.ini_read_bool(hConfigFile, "TIO_CONFIG", "AMP_FORM", &aReadBoolValue, false)) FAMPPowerFormIsActive = aReadBoolValue;
    if(0 == app.ini_read_bool(hConfigFile, "TIO_CONFIG", "MAPPING_FORM", &aReadBoolValue, false)) FMappingFormIsActive = aReadBoolValue;
    // delta
    aStringLength = 1000;
    if(0 == app.ini_read_string(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_IP", aReadStringValue, &aStringLength, "192.168.1.101")) FDeltaPowerIP = std::string(aReadStringValue);
    if(0 == app.ini_read_int32(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT", &aReadIntValue, 8462)) FDeltaPowerPort = aReadIntValue;
    if(0 == app.ini_read_bool(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT", &aReadBoolValue, false)) FDeltaPowerAutoConnect = aReadBoolValue;
    if(0 == app.ini_read_float(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE", &aReadFloatValue, 20)) FDeltaPowerMaxVoltage = float(aReadFloatValue);
    // itech
    aStringLength = 1000;
    if(0 == app.ini_read_string(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_IP", aReadStringValue, &aStringLength, "192.168.1.11")) FITechPowerIP = std::string(aReadStringValue);
    if(0 == app.ini_read_int32(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT", &aReadIntValue, 30000)) FITechPowerPort = aReadIntValue;
    if(0 == app.ini_read_int32(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_TYPE", &aReadIntValue, 0)) FITechType = aReadIntValue;
    if(0 == app.ini_read_bool(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT", &aReadBoolValue, false)) FITechPowerAutoConnect = aReadBoolValue;
    if(0 == app.ini_read_float(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE", &aReadFloatValue, 16)) FITechPowerProtectVoltage = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT", &aReadFloatValue, 1)) FItechPowerMaxCurrent = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT", &aReadFloatValue, -1)) FItechPowerMinCurrent = float(aReadFloatValue);
    // amp power related
    aStringLength = 1000;
    if(0 == app.ini_read_string(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_IP", aReadStringValue, &aStringLength, "192.168.1.100")) FAMPPowerIP = std::string(aReadStringValue);
    if(0 == app.ini_read_int32(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_PORT", &aReadIntValue, 2001)) FAMPPowerPort = aReadIntValue;
    if(0 == app.ini_read_bool(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT", &aReadBoolValue, false)) FAMPPowerAutoConnect = aReadBoolValue;
    if(0 == app.ini_read_bool(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_AVAILABLE", &aReadBoolValue, false)) FAMPPowerAvailabe = aReadBoolValue;
    // amp load related
    aStringLength = 1000;
    if(0 == app.ini_read_string(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_IP", aReadStringValue, &aStringLength, "192.168.1.100")) FAMPLoadIP = std::string(aReadStringValue);
    if(0 == app.ini_read_int32(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT", &aReadIntValue, 2001)) FAMPLoadPort = aReadIntValue;
    if(0 == app.ini_read_bool(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT", &aReadBoolValue, false)) FAMPLoadAutoConnect = aReadBoolValue;
    if(0 == app.ini_read_bool(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE", &aReadBoolValue, false)) FAMPLoadAvailabe = aReadBoolValue;
    // servo related
    if(0 == app.ini_read_bool(hConfigFile, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE", &aReadBoolValue, false)) FRotateServoIsAvailable = aReadBoolValue;
    if(0 == app.ini_read_bool(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE", &aReadBoolValue, false)) FAirCylinderAvailable = aReadBoolValue;
    if(0 == app.ini_read_bool(hConfigFile, "SERVO_CONFIG", "SERVO_AUTO_CONNECT", &aReadBoolValue, false)) FServoAutoConnect = aReadBoolValue;
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE", &aReadFloatValue, 0)) FServo2MountAngle = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "SERVO2_SPEED", &aReadFloatValue, 2)) FServo2Speed = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "SERVO1_MAX_POSITION", &aReadFloatValue, 20)) FServo1MaxPosition = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "SERVO1_MIN_POSITION", &aReadFloatValue, 0)) FServo1MinPosition = float(aReadFloatValue);
    aStringLength = 1000;
    if(0 == app.ini_read_string(hConfigFile, "SERVO_CONFIG", "S7_IP", aReadStringValue, &aStringLength, "192.168.1.1")) FS7IPAddress = std::string(aReadStringValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_MAX", &aReadFloatValue, 150)) FMCMaxPressure = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR", &aReadFloatValue, 0.0597f)) FPressure2CurrentFactor = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET", &aReadFloatValue, 0)) FPressure2CurrentOffset = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX", &aReadFloatValue, 20)) FAirValveMaxCurrent = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN", &aReadFloatValue, 0)) FAirValveMinCurrent = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "PUMP_STATION_PRESSURE_MAX", &aReadFloatValue, 300.0f)) FPSMaxPressure = float(aReadFloatValue);
    // add for pedal force control
    aStringLength = 1000;
    if(0 == app.ini_read_string(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_POSITION", aReadStringValue, &aStringLength, "2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,39")) FPFCPosVSPresPosition = std::string(aReadStringValue);
    aStringLength = 1000;
    if(0 == app.ini_read_string(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_PRESSURE", aReadStringValue, &aStringLength, "0,4.61,12.32,21.72,30.83,40.87,52.45,62.913,74.826,87.937,97.975,109.684,123.429,133.466,145.334,158.626,168.975,180.509,191.315,194.547")) FPFCPosVSPresPressure = std::string(aReadStringValue);
    aStringLength = 1000;
    if(0 == app.ini_read_string(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_PRESSURE", aReadStringValue, &aStringLength, "0,4.61,12.32,21.72,30.83,40.87,52.45,62.913,74.826,87.937,97.975,109.684,123.429,133.466,145.334,158.626,168.975,180.509,191.315,194.547")) FPFCPresVSForcePressure = std::string(aReadStringValue);
    aStringLength = 1000;
    if(0 == app.ini_read_string(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_FORCE", aReadStringValue, &aStringLength, "821,2042,4950.5,8512,11862.5,15861,20109,24206,28814,33759.5,37602.5,42190,47237.5,51013.5,55599,60658,64566,68975.5,73010.5,74257.5")) FPFCPresVSForceForce = std::string(aReadStringValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "PFC_MAX_PRESSURE", &aReadFloatValue, 0.0f)) FPFCMCMaxPressure = float(aReadFloatValue);
    if(0 == app.ini_read_bool(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_CALIBRATED", &aReadBoolValue, false)) FPFCPosVSPresIsCalibrated = aReadBoolValue;
    if(0 == app.ini_read_bool(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_CALIBRATED", &aReadBoolValue, false)) FPFCPresVSForceIsCalibrated = aReadBoolValue;
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "PFC_MIN_FORCE", &aReadFloatValue, 0.0f)) FPFCMCMinForce = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "PFC_IDLE_STROKE", &aReadFloatValue, 3.0f)) FPFCMCIdleStroke = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "PFC_MAX_PRESSURE_DOWN_LIMIT", &aReadFloatValue, 3.0f)) FPFCMCMaxPressureDownLimit = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "PFC_MAX_CALIBRATED_FORCE", &aReadFloatValue, 80000.0f)) FFPCMCMaxCalibratedForce = float(aReadFloatValue);
    if(0 == app.ini_read_float(hConfigFile, "SERVO_CONFIG", "PFC_MIN_CALIBRATED_FORCE", &aReadFloatValue, 20000.0f)) FFPCMCMinCalibratedForce = float(aReadFloatValue);

    if(0 == app.ini_close(hConfigFile)) {
        log("config file loaded");
        hConfigFile = NULL;
    }

}

void TTIOConfig::InitConfigFile() {
    if(!GetConfigFile()) {
        log_nok("Can not get TSMaster project configuration path.");
        return;
    }
    if(ensureFileExists(FConfigIniFile)) {
        if(0 == app.ini_create(FConfigIniFile.c_str(), &hConfigFile)) {
            log("ini object created: %x", hConfigFile);
        }
        else {
            log_nok("ini object creation failed.");
            return;
        }

        // form related
        if(app.ini_key_exists(hConfigFile, "TIO_CONFIG", "MAPPING_FORM"))
            app.ini_write_bool(hConfigFile, "TIO_CONFIG", "MAPPING_FORM", true);
        if(app.ini_key_exists(hConfigFile, "TIO_CONFIG", "DELTA_FORM"))
            app.ini_write_bool(hConfigFile, "TIO_CONFIG", "DELTA_FORM", true);
        if(app.ini_key_exists(hConfigFile, "TIO_CONFIG", "ITECH_FORM"))
            app.ini_write_bool(hConfigFile, "TIO_CONFIG", "ITECH_FORM", true);
        if(app.ini_key_exists(hConfigFile, "TIO_CONFIG", "AMP_FORM"))
            app.ini_write_bool(hConfigFile, "TIO_CONFIG", "AMP_FORM", true);
        if(app.ini_key_exists(hConfigFile, "TIO_CONFIG", "SERVO_FORM"))
            app.ini_write_bool(hConfigFile, "TIO_CONFIG", "SERVO_FORM", true);
        // delta power related
        if(app.ini_key_exists(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_IP"))
            app.ini_write_string(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_IP", "192.168.1.101");
        if(app.ini_key_exists(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT"))
            app.ini_write_int32(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT", 8462);
        if(app.ini_key_exists(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT"))
            app.ini_write_bool(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT", false);
        if(app.ini_key_exists(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE"))
            app.ini_write_float(hConfigFile, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE", 20);
        // itech power related
        if(app.ini_key_exists(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_IP"))
            app.ini_write_string(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_IP", "192.168.1.11");
        if(app.ini_key_exists(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT"))
            app.ini_write_int32(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT", 30000);
        if(app.ini_key_exists(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_TYPE"))
            app.ini_write_int32(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_TYPE", 0);
        if(app.ini_key_exists(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT"))
            app.ini_write_bool(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT", false);
        if(app.ini_key_exists(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE"))
            app.ini_write_float(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE", 16);
        if(app.ini_key_exists(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT"))
            app.ini_write_float(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT", 1);
        if(app.ini_key_exists(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT"))
            app.ini_write_float(hConfigFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT", -1);
        // amp power related
        if(app.ini_key_exists(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_IP"))
            app.ini_write_string(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_IP", "192.168.1.100");
        if(app.ini_key_exists(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_PORT"))
            app.ini_write_int32(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_PORT", 2001);
        if(app.ini_key_exists(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT"))
            app.ini_write_bool(hConfigFile, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT", false);
        // amp load related
        if(app.ini_key_exists(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_IP"))
            app.ini_write_string(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_IP", "192.168.1.100");
        if(app.ini_key_exists(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT"))
            app.ini_write_int32(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT", 2001);
        if(app.ini_key_exists(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT"))
            app.ini_write_bool(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT", false);
        if(app.ini_key_exists(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE"))
            app.ini_write_bool(hConfigFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE", false);
        // servo related
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE"))
            app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE", false);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE"))
            app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE", false);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "SERVO_AUTO_CONNECT"))
            app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "SERVO_AUTO_CONNECT", false);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE", 0);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "SERVO2_SPEED"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "SERVO2_SPEED", 2);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "SERVO1_MAX_POSITION"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "SERVO1_MAX_POSITION", 20);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "SERVO1_MIN_POSITION"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "SERVO1_MIN_POSITION", 0);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "S7_IP"))
            app.ini_write_string(hConfigFile, "SERVO_CONFIG", "S7_IP", "192.168.1.1");
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_MAX"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_MAX", 150);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR", 0.0597f);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET", 4);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX", 20);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN", 0);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PUMP_STATION_PRESSURE_MAX"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PUMP_STATION_PRESSURE_MAX", 300.0f);
        // add for pedal force control
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_POSITION"))
            app.ini_write_string(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_POSITION", "2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,39");
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_PRESSURE"))
            app.ini_write_string(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_PRESSURE", "0,4.61,12.32,21.72,30.83,40.87,52.45,62.913,74.826,87.937,97.975,109.684,123.429,133.466,145.334,158.626,168.975,180.509,191.315,194.547");
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_PRESSURE"))
            app.ini_write_string(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_PRESSURE", "0,4.61,12.32,21.72,30.83,40.87,52.45,62.913,74.826,87.937,97.975,109.684,123.429,133.466,145.334,158.626,168.975,180.509,191.315,194.547");
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_FORCE"))
            app.ini_write_string(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_FORCE", "821,2042,4950.5,8512,11862.5,15861,20109,24206,28814,33759.5,37602.5,42190,47237.5,51013.5,55599,60658,64566,68975.5,73010.5,74257.5");
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_MAX_PRESSURE"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MAX_PRESSURE", 200.0f);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_CALIBRATED"))
            app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "PFC_MM2BAR_CALIBRATED", false);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_CALIBRATED"))
            app.ini_write_bool(hConfigFile, "SERVO_CONFIG", "PFC_BAR2N_CALIBRATED", false);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_MIN_FORCE"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MIN_FORCE", 2000.0f);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_IDLE_STROKE"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_IDLE_STROKE", 3.0f);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_MAX_PRESSURE_DOWN_LIMIT"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MAX_PRESSURE_DOWN_LIMIT", 150.0f);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_MAX_CALIBRATED_FORCE"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MAX_CALIBRATED_FORCE", 80000.0f);
        if(app.ini_key_exists(hConfigFile, "SERVO_CONFIG", "PFC_MIN_CALIBRATED_FORCE"))
            app.ini_write_float(hConfigFile, "SERVO_CONFIG", "PFC_MIN_CALIBRATED_FORCE", 20000.0f);

        if(0 == app.ini_close(hConfigFile)) {
            log("config file initilized");
            hConfigFile = NULL;
        }
    }

}
