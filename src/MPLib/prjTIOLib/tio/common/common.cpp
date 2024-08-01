#include "common.h"
#include "TSMaster.h"

TTIOConfig vTIOConfig;

#define INI_FILE "TIO\TIOConfiguration.ini"
void TTIOConfig::SaveConfig() {
    std::ofstream file(FConfigIniFile);
    if(!file.is_open()) {
        log_nok("Failed to open config file for writing"); // LVL_ERROR
        return;
    }

    try {
        WriteBoolean(file, "TIO_CONFIG", "SERVO_FORM", FServoFormIsActive);
        WriteBoolean(file, "TIO_CONFIG", "MAPPING_FORM", FMappingFormIsActive);
        WriteBoolean(file, "TIO_CONFIG", "DELTA_FORM", FDeltaPowerFormIsActive);
        WriteBoolean(file, "TIO_CONFIG", "ITECH_FORM", FITechPowerFormIsActive);
        WriteBoolean(file, "TIO_CONFIG", "AMP_FORM", FAMPPowerFormIsActive);
        WriteString(file, "DELTA_POWER_CONFIG", "DELTA_POWER_IP", FDeltaPowerIP);
        WriteInteger(file, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT", FDeltaPowerPort);
        WriteBoolean(file, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT", FDeltaPowerAutoConnect);
        WriteFloat(file, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE", FDeltaPowerMaxVoltage);
        WriteString(file, "ITECH_POWER_CONFIG", "ITECH_POWER_IP", FITechPowerIP);
        WriteInteger(file, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT", FITechPowerPort);
        WriteInteger(file, "ITECH_POWER_CONFIG", "ITECH_TYPE", FITechType);
        WriteBoolean(file, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT", FITechPowerAutoConnect);
        WriteFloat(file, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE", FITechPowerProtectVoltage);
        WriteFloat(file, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT", FItechPowerMaxCurrent);
        WriteFloat(file, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT", FItechPowerMinCurrent);
        WriteString(file, "AMP_POWER_CONFIG", "AMP_POWER_IP", FAMPPowerIP);
        WriteInteger(file, "AMP_POWER_CONFIG", "AMP_POWER_PORT", FAMPPowerPort);
        WriteBoolean(file, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT", FAMPPowerAutoConnect);
        WriteBoolean(file, "AMP_POWER_CONFIG", "AMP_POWER_AVAILABLE", FAMPPowerAvailabe);
        WriteString(file, "AMP_LOAD_CONFIG", "AMP_LOAD_IP", FAMPLoadIP);
        WriteInteger(file, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT", FAMPLoadPort);
        WriteBoolean(file, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT", FAMPLoadAutoConnect);
        WriteBoolean(file, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE", FAMPLoadAvailabe);
        WriteBoolean(file, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE", FRotateServoIsAvailable);
        WriteBoolean(file, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE", FAirCylinderAvailable);
        WriteBoolean(file, "SERVO_CONFIG", "SERVO_AUTO_CONNECT", FServoAutoConnect);
        WriteFloat(file, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE", FServo2MountAngle);
        WriteFloat(file, "SERVO_CONFIG", "SERVO2_SPEED", FServo2Speed);
        WriteFloat(file, "SERVO_CONFIG", "SERVO1_MAX_POSITION", FServo1MaxPosition);
        WriteFloat(file, "SERVO_CONFIG", "SERVO1_MIN_POSITION", FServo1MinPosition);
        WriteString(file, "SERVO_CONFIG", "S7_IP", FS7IPAddress);
        WriteFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_MAX", FMCMaxPressure);
        WriteFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR", FPressure2CurrentFactor);
        WriteFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET", FPressure2CurrentOffset);
        WriteFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX", FAirValveMaxCurrent);
        WriteFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN", FAirValveMinCurrent);
    }
    catch(const std::exception& e) {
        log_nok(std::string(e.what()).c_str()); // LVL_ERROR
    }

    file.close();
}

bool TTIOConfig::GetConfigFile() {
    std::string AConfigFolder;
    char* s;
    if(app.get_configuration_file_path(&s) == 0) {
        AConfigFolder = std::string(s);
        FConfigIniFile = AConfigFolder + INI_FILE;
        log(FConfigIniFile.c_str());
        return true;
    }
    else {
        return false;
    }
}

void TTIOConfig::LoadConfigValue() {
    std::ifstream file(FConfigIniFile);
    if(!file.is_open()) {
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
        FPressure2CurrentFactor = ReadFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR", 0.0597);
        FPressure2CurrentOffset = ReadFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET", 0);
        FAirValveMaxCurrent = ReadFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX", 20);
        FAirValveMinCurrent = ReadFloat(file, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN", 0);
    }
    catch(const std::exception& e) {
        log_nok(std::string(e.what()).c_str()); // LVL_ERROR
    }

    file.close();
}

void TTIOConfig::InitIniFile() {
    std::ifstream readFile(FConfigIniFile);
    if(!readFile.is_open()) {
        log_nok("Failed to open config file for initialization"); // LVL_ERROR
        return;
    }

    std::ofstream writeFile(FConfigIniFile, std::ios::app); // 使用 std::ios::app 追加模式打开文件
    if(!writeFile.is_open()) {
        log_nok("Failed to open config file for writing"); // LVL_ERROR
        return;
    }

    try {
        // form related
        if(!ValueExists(readFile, "TIO_CONFIG", "MAPPING_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "MAPPING_FORM", true);
        if(!ValueExists(readFile, "TIO_CONFIG", "DELTA_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "DELTA_FORM", true);
        if(!ValueExists(readFile, "TIO_CONFIG", "ITECH_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "ITECH_FORM", true);
        if(!ValueExists(readFile, "TIO_CONFIG", "AMP_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "AMP_FORM", true);
        if(!ValueExists(readFile, "TIO_CONFIG", "SERVO_FORM"))
            WriteBoolean(writeFile, "TIO_CONFIG", "SERVO_FORM", true);
        // delta power related
        if(!ValueExists(readFile, "DELTA_POWER_CONFIG", "DELTA_POWER_IP"))
            WriteString(writeFile, "DELTA_POWER_CONFIG", "DELTA_POWER_IP", "192.168.1.101");
        if(!ValueExists(readFile, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT"))
            WriteInteger(writeFile, "DELTA_POWER_CONFIG", "DELTA_POWER_PORT", 8462);
        if(!ValueExists(readFile, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT"))
            WriteBoolean(writeFile, "DELTA_POWER_CONFIG", "DELTA_POWER_AUTO_CONNECT", false);
        if(!ValueExists(readFile, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE"))
            WriteFloat(writeFile, "DELTA_POWER_CONFIG", "DELTA_POWER_MAX_VOLTAGE", 20);
        // itech power related
        if(!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_IP"))
            WriteString(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_IP", "192.168.1.11");
        if(!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT"))
            WriteInteger(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PORT", 30000);
        if(!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_TYPE"))
            WriteInteger(writeFile, "ITECH_POWER_CONFIG", "ITECH_TYPE", 0);
        if(!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT"))
            WriteBoolean(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_AUTO_CONNECT", false);
        if(!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE"))
            WriteFloat(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_PROTECT_VOLTAGE", 16);
        if(!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT"))
            WriteFloat(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MAX_CURRENT", 1);
        if(!ValueExists(readFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT"))
            WriteFloat(writeFile, "ITECH_POWER_CONFIG", "ITECH_POWER_MIN_CURRENT", -1);
        // amp power related
        if(!ValueExists(readFile, "AMP_POWER_CONFIG", "AMP_POWER_IP"))
            WriteString(writeFile, "AMP_POWER_CONFIG", "AMP_POWER_IP", "192.168.1.100");
        if(!ValueExists(readFile, "AMP_POWER_CONFIG", "AMP_POWER_PORT"))
            WriteInteger(writeFile, "AMP_POWER_CONFIG", "AMP_POWER_PORT", 2001);
        if(!ValueExists(readFile, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT"))
            WriteBoolean(writeFile, "AMP_POWER_CONFIG", "AMP_POWER_AUTO_CONNECT", false);
        // amp load related
        if(!ValueExists(readFile, "AMP_LOAD_CONFIG", "AMP_LOAD_IP"))
            WriteString(writeFile, "AMP_LOAD_CONFIG", "AMP_LOAD_IP", "192.168.1.100");
        if(!ValueExists(readFile, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT"))
            WriteInteger(writeFile, "AMP_LOAD_CONFIG", "AMP_LOAD_PORT", 2001);
        if(!ValueExists(readFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT"))
            WriteBoolean(writeFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AUTO_CONNECT", false);
        if(!ValueExists(readFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE"))
            WriteBoolean(writeFile, "AMP_LOAD_CONFIG", "AMP_LOAD_AVAILABLE", false);
        // servo related
        if(!ValueExists(readFile, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE"))
            WriteBoolean(writeFile, "SERVO_CONFIG", "ROTATE_SERVO_AVAILABLE", false);
        if(!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE"))
            WriteBoolean(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_AVAILABLE", false);
        if(!ValueExists(readFile, "SERVO_CONFIG", "SERVO_AUTO_CONNECT"))
            WriteBoolean(writeFile, "SERVO_CONFIG", "SERVO_AUTO_CONNECT", false);
        if(!ValueExists(readFile, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE"))
            WriteFloat(writeFile, "SERVO_CONFIG", "SERVO2_MOUNT_ANGLE", 0);
        if(!ValueExists(readFile, "SERVO_CONFIG", "SERVO2_SPEED"))
            WriteFloat(writeFile, "SERVO_CONFIG", "SERVO2_SPEED", 2);
        if(!ValueExists(readFile, "SERVO_CONFIG", "SERVO1_MAX_POSITION"))
            WriteFloat(writeFile, "SERVO_CONFIG", "SERVO1_MAX_POSITION", 20);
        if(!ValueExists(readFile, "SERVO_CONFIG", "SERVO1_MIN_POSITION"))
            WriteFloat(writeFile, "SERVO_CONFIG", "SERVO1_MIN_POSITION", 0);
        if(!ValueExists(readFile, "SERVO_CONFIG", "S7_IP"))
            WriteString(writeFile, "SERVO_CONFIG", "S7_IP", "192.168.1.1");
        if(!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_MAX"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_MAX", 150);
        if(!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_FACTOR", 0.0597);
        if(!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_OFFSET", 4);
        if(!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MAX", 20);
        if(!ValueExists(readFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN"))
            WriteFloat(writeFile, "SERVO_CONFIG", "AIR_CYLINDER_CURRENT_MIN", 0);
    }
    catch(const std::exception& e) {
        log_nok(std::string(e.what()).c_str()); // LVL_ERROR
    }

    readFile.close();
    writeFile.close();
}

void TTIOConfig::WriteBoolean(std::ofstream& file, const std::string& section, const std::string& key, bool value) {
    file << "[" << section << "]" << std::endl;
    file << key << "=" << (value ? "true" : "false") << std::endl;
}

void TTIOConfig::WriteString(std::ofstream& file, const std::string& section, const std::string& key, const std::string& value) {
    file << "[" << section << "]" << std::endl;
    file << key << "=" << value << std::endl;
}

void TTIOConfig::WriteInteger(std::ofstream& file, const std::string& section, const std::string& key, int32_t value) {
    file << "[" << section << "]" << std::endl;
    file << key << "=" << value << std::endl;
}

void TTIOConfig::WriteFloat(std::ofstream& file, const std::string& section, const std::string& key, float value) {
    file << "[" << section << "]" << std::endl;
    file << key << "=" << value << std::endl;
}

bool TTIOConfig::ReadBoolean(std::ifstream& file, const std::string& section, const std::string& key, bool defaultValue) {
    std::string line;
    std::string currentSection;
    while(std::getline(file, line)) {
        if(line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if(currentSection == section) {
            size_t pos = line.find('=');
            if(pos != std::string::npos && line.substr(0, pos) == key) {
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
    while(std::getline(file, line)) {
        if(line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if(currentSection == section) {
            size_t pos = line.find('=');
            if(pos != std::string::npos && line.substr(0, pos) == key) {
                return line.substr(pos + 1);
            }
        }
    }
    return defaultValue;
}

int32_t TTIOConfig::ReadInteger(std::ifstream& file, const std::string& section, const std::string& key, int32_t defaultValue) {
    std::string line;
    std::string currentSection;
    while(std::getline(file, line)) {
        if(line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if(currentSection == section) {
            size_t pos = line.find('=');
            if(pos != std::string::npos && line.substr(0, pos) == key) {
                return std::stoi(line.substr(pos + 1));
            }
        }
    }
    return defaultValue;
}

float TTIOConfig::ReadFloat(std::ifstream& file, const std::string& section, const std::string& key, float defaultValue) {
    std::string line;
    std::string currentSection;
    while(std::getline(file, line)) {
        if(line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if(currentSection == section) {
            size_t pos = line.find('=');
            if(pos != std::string::npos && line.substr(0, pos) == key) {
                return std::stof(line.substr(pos + 1));
            }
        }
    }
    return defaultValue;
}

bool TTIOConfig::ValueExists(std::ifstream& file, const std::string& section, const std::string& key) {
    std::string line;
    std::string currentSection;
    while(std::getline(file, line)) {
        if(line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if(currentSection == section) {
            size_t pos = line.find('=');
            if(pos != std::string::npos && line.substr(0, pos) == key) {
                return true;
            }
        }
    }
    return false;
}