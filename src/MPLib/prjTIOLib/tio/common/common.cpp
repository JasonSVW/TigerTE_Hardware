#include "common.h"
#include "TSMaster.h"
#include <windows.h>
#include <string>
#include <filesystem>

TTIOConfig vTIOConfig;
std::string vMP_Name = "tio";

#define INI_FILE "TIO\\TIOConfiguration.ini"

std::string WideCharToMultiByte(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

std::string GetCurrentModuleName()
{
    wchar_t path[MAX_PATH];
    HMODULE hModule = NULL;

    // 使用 GetModuleHandleExW 代替 GetModuleHandleEx
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCWSTR)GetCurrentModuleName,
        &hModule) == 0)
    {
        // 处理错误
        return "tio";
    }

    // 使用 GetModuleFileNameW 代替 GetModuleFileName
    if (GetModuleFileNameW(hModule, path, MAX_PATH) == 0)
    {
        // 处理错误
        return "tio";
    }

    //std::filesystem::path p(path);
    //return p.filename().wstring();
    std::filesystem::path p(path);
    std::wstring filename = p.filename().wstring();

    // 找到最后一个点号的位置
    size_t pos = filename.find_last_of(L'.');
    if (pos != std::wstring::npos)
    {
        // 提取不带后缀的名称
        return WideCharToMultiByte(filename.substr(0, pos));
    }
    return WideCharToMultiByte(filename);
}

void TTIOConfig::SaveConfig() {
    if (FConfigIniFile.empty()) {
        log_nok("Configuration file is not specified.");
        return;
    }
    std::ofstream file(FConfigIniFile);
    if (!file.is_open()) {
        log_nok("Failed to open config file for writing"); // LVL_ERROR
        return;
    }

    std::string currentSection;

    try {
        WriteBoolean(file, "TIO_CONFIG", "SERVO_FORM", FServoFormIsActive, currentSection);
        WriteBoolean(file, "TIO_CONFIG", "MAPPING_FORM", FMappingFormIsActive, currentSection);
        WriteBoolean(file, "TIO_CONFIG", "DELTA_FORM", FDeltaPowerFormIsActive, currentSection);
        WriteBoolean(file, "TIO_CONFIG", "ITECH_FORM", FITechPowerFormIsActive, currentSection);
        WriteBoolean(file, "TIO_CONFIG", "AMP_FORM", FAMPPowerFormIsActive, currentSection);
        WriteString(file, "DELTA_POWER_CONFIG", "DELTA_POWER_IP", FDeltaPowerIP, currentSection);
        WriteInteger(file, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT", FDeltaPowerPort, currentSection);
        WriteBoolean(file, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT", FDeltaPowerAutoConnect, currentSection);
        WriteFloat(file, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE", FDeltaPowerMaxVoltage, currentSection);
        WriteString(file, "ITECH_POWER_CONFIG", "ITECH_POWER_IP", FITechPowerIP, currentSection);
        WriteInteger(file, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT", FITechPowerPort, currentSection);
        WriteInteger(file, "ITECH_POWER_CONFIG", "ITECH_TYPE", FITechType, currentSection);
        WriteBoolean(file, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT", FITechPowerAutoConnect, currentSection);
        WriteFloat(file, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE", FITechPowerProtectVoltage, currentSection);
        WriteFloat(file, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT", FItechPowerMaxCurrent, currentSection);
        WriteFloat(file, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT", FItechPowerMinCurrent, currentSection);
        WriteString(file, "AMP_POWER_CONFIG", "AMP_POWER_IP", FAMPPowerIP, currentSection);
        WriteInteger(file, "AMP_POWER_CONFIG", "AMP_POWER_PORT", FAMPPowerPort, currentSection);
        WriteBoolean(file, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT", FAMPPowerAutoConnect, currentSection);
        WriteBoolean(file, "AMP_POWER_CONFIG", "AMP_POWER_AVAILABLE", FAMPPowerAvailabe, currentSection);
        WriteString(file, "AMP_LOAD_CONFIG", "AMP_LOAD_IP", FAMPLoadIP, currentSection);
        WriteInteger(file, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT", FAMPLoadPort, currentSection);
        WriteBoolean(file, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT", FAMPLoadAutoConnect, currentSection);
        WriteBoolean(file, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE", FAMPLoadAvailabe, currentSection);
        WriteBoolean(file, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE", FRotateServoIsAvailable, currentSection);
        WriteBoolean(file, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE", FAirCylinderAvailable, currentSection);
        WriteBoolean(file, "SERVO_CONFIG", "SERVO_AUTO_CONNECT", FServoAutoConnect, currentSection);
        WriteFloat(file, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE", FServo2MountAngle, currentSection);
        WriteFloat(file, "SERVO_CONFIG", "SERVO2_SPEED", FServo2Speed, currentSection);
        WriteFloat(file, "SERVO_CONFIG", "SERVO1_MAX_POSITION", FServo1MaxPosition, currentSection);
        WriteFloat(file, "SERVO_CONFIG", "SERVO1_MIN_POSITION", FServo1MinPosition, currentSection);
        WriteString(file, "SERVO_CONFIG", "S7_IP", FS7IPAddress, currentSection);
        WriteFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_MAX", FMCMaxPressure, currentSection);
        WriteFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR", FPressure2CurrentFactor, currentSection);
        WriteFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET", FPressure2CurrentOffset, currentSection);
        WriteFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX", FAirValveMaxCurrent, currentSection);
        WriteFloat(file, "SERVO_CONFIG", "PUMP_STATION_PRESSURE_MAX", FPSMaxPressure, currentSection);
    }
    catch (const std::exception& e) {
        log_nok(std::string(e.what()).c_str()); // LVL_ERROR
    }

    file.close();
}

bool TTIOConfig::GetConfigFile() {
    std::string AConfigFolder;
    char* s;
    if (app.get_configuration_file_path(&s) == 0) {
        AConfigFolder = std::string(s);
        FConfigIniFile = AConfigFolder + INI_FILE;
        return true;
    }
    else {
        return false;
    }
}

void TTIOConfig::LoadConfigValue() {
    if (FConfigIniFile.empty()) {
        log_nok("Configuration file is not specified.");
        return;
    }
    std::ifstream file(FConfigIniFile);
    if (!file.is_open()) {
        log_nok("Failed to open config file for reading"); // LVL_ERROR
        return;
    }

    try {
        // form
        FServoFormIsActive = ReadBoolean(file, "TIO_CONFIG", "SERVO_FORM", false);
        FDeltaPowerFormIsActive = ReadBoolean(file, "TIO_CONFIG", "DELTA_FORM", false);
        FITechPowerFormIsActive = ReadBoolean(file, "TIO_CONFIG", "ITECH_FORM", false);
        FAMPPowerFormIsActive = ReadBoolean(file, "TIO_CONFIG", "AMP_FORM", false);
        FMappingFormIsActive = ReadBoolean(file, "TIO_CONFIG", "MAPPING_FORM", false);
        // delta
        FDeltaPowerIP = ReadString(file, "DELTA_POWER_CONFIG", "DELTA_POWER_IP", "192.168.1.101");
        FDeltaPowerPort = ReadInteger(file, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT", 8462);
        FDeltaPowerAutoConnect = ReadBoolean(file, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT", false);
        FDeltaPowerMaxVoltage = ReadFloat(file, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE", 20);
        // itech
        FITechPowerIP = ReadString(file, "ITECH_POWER_CONFIG", "ITECH_POWER_IP", "192.168.1.11");
        FITechPowerPort = ReadInteger(file, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT", 30000);
        FITechType = ReadInteger(file, "ITECH_POWER_CONFIG", "ITECH_TYPE", 0);
        FITechPowerAutoConnect = ReadBoolean(file, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT", false);
        FITechPowerProtectVoltage = ReadFloat(file, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE", 16);
        FItechPowerMaxCurrent = ReadFloat(file, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT", 1);
        FItechPowerMinCurrent = ReadFloat(file, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT", -1);
        // amp power related
        FAMPPowerIP = ReadString(file, "AMP_POWER_CONFIG", "AMP_POWER_IP", "192.168.1.100");
        FAMPPowerPort = ReadInteger(file, "AMP_POWER_CONFIG", "AMP_POWER_PORT", 2001);
        FAMPPowerAutoConnect = ReadBoolean(file, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT", false);
        FAMPPowerAvailabe = ReadBoolean(file, "AMP_POWER_CONFIG", "AMP_POWER_AVAILABLE", false);
        // amp load related
        FAMPLoadIP = ReadString(file, "AMP_LOAD_CONFIG", "AMP_LOAD_IP", "192.168.1.100");
        FAMPLoadPort = ReadInteger(file, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT", 2001);
        FAMPLoadAutoConnect = ReadBoolean(file, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT", false);
        FAMPLoadAvailabe = ReadBoolean(file, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE", false);
        // servo related
        FRotateServoIsAvailable = ReadBoolean(file, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE", false);
        FAirCylinderAvailable = ReadBoolean(file, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE", false);
        FServoAutoConnect = ReadBoolean(file, "SERVO_CONFIG", "SERVO_AUTO_CONNECT", false);
        FServo2MountAngle = ReadFloat(file, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE", 0);
        FServo2Speed = ReadFloat(file, "SERVO_CONFIG", "SERVO2_SPEED", 2);
        FServo1MaxPosition = ReadFloat(file, "SERVO_CONFIG", "SERVO1_MAX_POSITION", 20);
        FServo1MinPosition = ReadFloat(file, "SERVO_CONFIG", "SERVO1_MIN_POSITION", 0);
        FS7IPAddress = ReadString(file, "SERVO_CONFIG", "S7_IP", "192.168.1.1");
        FMCMaxPressure = ReadFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_MAX", 150);
        FPressure2CurrentFactor = ReadFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR", 0.0597f);
        FPressure2CurrentOffset = ReadFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET", 0);
        FAirValveMaxCurrent = ReadFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX", 20);
        FAirValveMinCurrent = ReadFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN", 0);
        FPSMaxPressure = ReadFloat(file, "SERVO_CONFIG", "PUMP_STATION_PRESSURE_MAX", 300.0f);
    }
    catch (const std::exception& e) {
        log_nok(std::string(e.what()).c_str()); // LVL_ERROR
    }

    file.close();
}

void TTIOConfig::InitIniFile() {
    if (!GetConfigFile()) {
        log_nok("Can not get TSMaster project configuration path.");
        return;
    }
    std::ifstream readFile(FConfigIniFile);
    if (!readFile.is_open()) {
        log_hint("Failed to open config file for initialization, new config file will be created."); // LVL_ERROR

        // 尝试创建文件所在的文件夹
        try {
            std::filesystem::path filePath(FConfigIniFile);
            std::filesystem::path directory = filePath.parent_path();
            if (!std::filesystem::exists(directory)) {
                std::filesystem::create_directories(directory);
            }
        }
        catch (const std::filesystem::filesystem_error& e) {
            log_nok(std::string("Failed to create directory for config file: ").append(e.what()).c_str()); // LVL_ERROR
            return;
        }

        // 尝试创建新的ini文件
        std::ofstream newFile(FConfigIniFile);
        if (!newFile.is_open()) {
            log_nok("Failed to create new config file"); // LVL_ERROR
            return;
        }
        newFile.close();

        // 重新打开文件进行读写
        readFile.open(FConfigIniFile);
        if (!readFile.is_open()) {
            log_nok("Failed to reopen newly created config file"); // LVL_ERROR
            return;
        }
    }

    std::ofstream writeFile(FConfigIniFile, std::ios::app); // 使用 std::ios::app 追加模式打开文件
    if (!writeFile.is_open()) {
        log_nok("Failed to open config file for writing"); // LVL_ERROR
        return;
    }


    std::string currentSection;

    try {
        // form related
        if (!ValueExists(readFile, "TIO_CONFIG", "MAPPING_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "MAPPING_FORM", true, currentSection);
        if (!ValueExists(readFile, "TIO_CONFIG", "DELTA_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "DELTA_FORM", true, currentSection);
        if (!ValueExists(readFile, "TIO_CONFIG", "ITECH_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "ITECH_FORM", true, currentSection);
        if (!ValueExists(readFile, "TIO_CONFIG", "AMP_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "AMP_FORM", true, currentSection);
        if (!ValueExists(readFile, "TIO_CONFIG", "SERVO_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "SERVO_FORM", true, currentSection);
        // delta power related
        if (!ValueExists(readFile, "DELTA_POWER_CONFIG", "DELTA_POWER_IP"))
            WriteString(writeFile, "DELTA_POWER_CONFIG", "DELTA_POWER_IP", "192.168.1.101", currentSection);
        if (!ValueExists(readFile, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT"))
            WriteInteger(writeFile, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT", 8462, currentSection);
        if (!ValueExists(readFile, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT"))
            WriteBoolean(writeFile, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT", false, currentSection);
        if (!ValueExists(readFile, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE"))
            WriteFloat(writeFile, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE", 20, currentSection);
        // itech power related
        if (!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_IP"))
            WriteString(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_IP", "192.168.1.11", currentSection);
        if (!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT"))
            WriteInteger(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT", 30000, currentSection);
        if (!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_TYPE"))
            WriteInteger(writeFile, "ITECH_POWER_CONFIG", "ITECH_TYPE", 0, currentSection);
        if (!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT"))
            WriteBoolean(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT", false, currentSection);
        if (!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE"))
            WriteFloat(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE", 16, currentSection);
        if (!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT"))
            WriteFloat(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT", 1, currentSection);
        if (!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT"))
            WriteFloat(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT", -1, currentSection);
        // amp power related
        if (!ValueExists(readFile, "AMP_POWER_CONFIG", "AMP_POWER_IP"))
            WriteString(writeFile, "AMP_POWER_CONFIG", "AMP_POWER_IP", "192.168.1.100", currentSection);
        if (!ValueExists(readFile, "AMP_POWER_CONFIG", "AMP_POWER_PORT"))
            WriteInteger(writeFile, "AMP_POWER_CONFIG", "AMP_POWER_PORT", 2001, currentSection);
        if (!ValueExists(readFile, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT"))
            WriteBoolean(writeFile, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT", false, currentSection);
        // amp load related
        if (!ValueExists(readFile, "AMP_LOAD_CONFIG", "AMP_LOAD_IP"))
            WriteString(writeFile, "AMP_LOAD_CONFIG", "AMP_LOAD_IP", "192.168.1.100", currentSection);
        if (!ValueExists(readFile, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT"))
            WriteInteger(writeFile, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT", 2001, currentSection);
        if (!ValueExists(readFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT"))
            WriteBoolean(writeFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT", false, currentSection);
        if (!ValueExists(readFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE"))
            WriteBoolean(writeFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE", false, currentSection);
        // servo related
        if (!ValueExists(readFile, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE"))
            WriteBoolean(writeFile, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE", false, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE"))
            WriteBoolean(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE", false, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "SERVO_AUTO_CONNECT"))
            WriteBoolean(writeFile, "SERVO_CONFIG", "SERVO_AUTO_CONNECT", false, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE"))
            WriteFloat(writeFile, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE", 0, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "SERVO2_SPEED"))
            WriteFloat(writeFile, "SERVO_CONFIG", "SERVO2_SPEED", 2, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "SERVO1_MAX_POSITION"))
            WriteFloat(writeFile, "SERVO_CONFIG", "SERVO1_MAX_POSITION", 20, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "SERVO1_MIN_POSITION"))
            WriteFloat(writeFile, "SERVO_CONFIG", "SERVO1_MIN_POSITION", 0, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "S7_IP"))
            WriteString(writeFile, "SERVO_CONFIG", "S7_IP", "192.168.1.1", currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_MAX"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_MAX", 150, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR", 0.0597f, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET", 4, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX", 20, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN", 0, currentSection);
        if (!ValueExists(readFile, "SERVO_CONFIG", "PUMP_STATION_PRESSURE_MAX"))
            WriteFloat(writeFile, "SERVO_CONFIG", "PUMP_STATION_PRESSURE_MAX", 300.0f, currentSection);
    }

    catch (const std::exception& e) {
        log_nok(std::string(e.what()).c_str()); // LVL_ERROR
    }

    readFile.close();
    writeFile.close();
}

void TTIOConfig::WriteBoolean(std::ofstream& file, const std::string& section, const std::string& key, bool value, std::string& currentSection) {
    if (currentSection != section) {
        file << "[" << section << "]" << std::endl;
        currentSection = section;
    }
    file << key << "=" << (value ? "true" : "false") << std::endl;
}

void TTIOConfig::WriteString(std::ofstream& file, const std::string& section, const std::string& key, const std::string& value, std::string& currentSection) {
    if (currentSection != section) {
        file << "[" << section << "]" << std::endl;
        currentSection = section;
    }
    file << key << "=" << value << std::endl;
}

void TTIOConfig::WriteInteger(std::ofstream& file, const std::string& section, const std::string& key, int32_t value, std::string& currentSection) {
    if (currentSection != section) {
        file << "[" << section << "]" << std::endl;
        currentSection = section;
    }
    file << key << "=" << value << std::endl;
}

void TTIOConfig::WriteFloat(std::ofstream& file, const std::string& section, const std::string& key, float value, std::string& currentSection) {
    if (currentSection != section) {
        file << "[" << section << "]" << std::endl;
        currentSection = section;
    }
    file << key << "=" << value << std::endl;
}

bool TTIOConfig::ReadBoolean(std::ifstream& file, const std::string& section, const std::string& key, bool defaultValue) {
    std::string line;
    std::string currentSection;
    while (std::getline(file, line)) {
        if (line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if (currentSection == section) {
            size_t pos = line.find('=');
            if (pos != std::string::npos && line.substr(0, pos) == key) {
                std::string value = line.substr(pos + 1);
                return value == "true" || value == "1";
            }
        }
    }
    return defaultValue;
}

std::string TTIOConfig::ReadString(std::ifstream& file, const std::string& section, const std::string& key, const std::string& defaultValue) {
    std::string line;
    std::string currentSection;
    while (std::getline(file, line)) {
        if (line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if (currentSection == section) {
            size_t pos = line.find('=');
            if (pos != std::string::npos && line.substr(0, pos) == key) {
                return line.substr(pos + 1);
            }
        }
    }
    return defaultValue;
}

int32_t TTIOConfig::ReadInteger(std::ifstream& file, const std::string& section, const std::string& key, int32_t defaultValue) {
    std::string line;
    std::string currentSection;
    while (std::getline(file, line)) {
        if (line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if (currentSection == section) {
            size_t pos = line.find('=');
            if (pos != std::string::npos && line.substr(0, pos) == key) {
                return std::stoi(line.substr(pos + 1));
            }
        }
    }
    return defaultValue;
}

float TTIOConfig::ReadFloat(std::ifstream& file, const std::string& section, const std::string& key, float defaultValue) {
    std::string line;
    std::string currentSection;
    while (std::getline(file, line)) {
        if (line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if (currentSection == section) {
            size_t pos = line.find('=');
            if (pos != std::string::npos && line.substr(0, pos) == key) {
                return std::stof(line.substr(pos + 1));
            }
        }
    }
    return defaultValue;
}

bool TTIOConfig::ValueExists(std::ifstream& file, const std::string& section, const std::string& key) {
    std::string line;
    std::string currentSection;
    while (std::getline(file, line)) {
        if (line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if (currentSection == section) {
            size_t pos = line.find('=');
            if (pos != std::string::npos && line.substr(0, pos) == key) {
                return true;
            }
        }
    }
    return false;
}