// GEN BLOCK BEGIN Include
#define TSMP_IMPL
#include "TSMaster.h"
#include "MPLibrary.h"
#include "Database.h"
#include "TSMasterBaseInclude.h"
#include "Configuration.h"
// GEN BLOCK END Include

// CODE BLOCK BEGIN Global_Definitions 

#include <windows.h>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

// 判断文件是否存在
bool fileExists(const std::string& filename) {
    DWORD attributes = GetFileAttributesA(filename.c_str());
    return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}

// 创建文件
bool createFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file.close();
    return true;
}

// 创建路径
bool createPath(const std::string& path) {
    std::string currentPath;
    size_t pos = 0;
    while ((pos = path.find('\\', pos)) != std::string::npos) {
        currentPath = path.substr(0, pos);
        if (!CreateDirectoryA(currentPath.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
            return false;
        }
        pos++;
    }
    return true;
}
#define INI_FILE "TIO\\TIOConfiguration.ini"
std::string FConfigIniFile = "";

native_int h = 0;

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void ensureFileExists(const std::string& filePath) {
    fs::path pathObj(filePath);

    // 检查文件是否存在
    if (fs::exists(pathObj)) {
        std::cout << "File already exists: " << filePath << std::endl;
    } else {
        // 检查父路径是否存在，不存在则创建
        fs::path parentPath = pathObj.parent_path();
        if (!fs::exists(parentPath)) {
            std::cout << "Directory does not exist. Creating: " << parentPath << std::endl;
            fs::create_directories(parentPath);
        }

        // 创建文件
        std::ofstream file(filePath);
        if (file) {
            std::cout << "File created: " << filePath << std::endl;
        } else {
            std::cerr << "Failed to create file: " << filePath << std::endl;
        }
        file.close();
    }
}
// CODE BLOCK END Global_Definitions 

// CODE BLOCK BEGIN On_Shortcut init MTY0NjY_
// On shortcut "init" with shortcut = Ctrl+R
void on_shortcut_init(const s32 AShortcut) { try { // On shortcut = Ctrl+R
 if (0 == app.ini_key_exists(h, "sec1", "val1")){
  log("val1 exists in sec1");
  app.ini_write_bool(h, "sec1", "val1", false);
} else {
  log("val1 not exists in sec1");
  app.ini_write_bool(h, "sec1", "val1", true);
  
}

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Shortcut init

// CODE BLOCK BEGIN On_Shortcut load MTY0Njg_
// On shortcut "load" with shortcut = Ctrl+T
void on_shortcut_load(const s32 AShortcut) { try { // On shortcut = Ctrl+T

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Shortcut load

// CODE BLOCK BEGIN On_Shortcut write MTY0Njk_
// On shortcut "write" with shortcut = Ctrl+U
void on_shortcut_write(const s32 AShortcut) { try { // On shortcut = Ctrl+U

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Shortcut write

// CODE BLOCK BEGIN On_Start NewOn_Start1
// On start handler "NewOn_Start1"
void on_start_NewOn_Start1(void) { try { // on start event
   std::string AConfigFolder;
   char* s;
   if(app.get_configuration_file_path(&s) == 0) {
       AConfigFolder = std::string(s);
       FConfigIniFile = AConfigFolder + INI_FILE;

   }
   ensureFileExists(FConfigIniFile);
   
//    // 判断文件是否存在
//     if (!fileExists(FConfigIniFile)) {
//         test_log("文件不存在，创建文件: " );
//         
//         // 创建路径
// //         std::string path = FConfigIniFile.substr(0, FConfigIniFile.find_last_of('\\'));
//         if (!createPath(AConfigFolder)) {
//             test_log( "无法创建路径: " );
//         }
//         
//         if (!createFile(FConfigIniFile)) {
//             test_log( "无法创建文件: ");
// 
//         }
//     } else {
//        test_log( "文件已存在: ");
//     }
    if (0 == app.ini_create(FConfigIniFile.c_str(), &h)){
  log("ini object created: %x", h);
}
} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Start NewOn_Start1

// CODE BLOCK BEGIN On_Stop NewOn_Stop1
// On stop handler "NewOn_Stop1"
void on_stop_NewOn_Stop1(void) { try { // on stop event
if (0 == app.ini_close(h)) {
  log("ini object closed: %x", h);
}

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Stop NewOn_Stop1

// CODE BLOCK BEGIN Step_Function  NQ__
// Main step function being executed every 5 ms
void step(void) { try { // interval = 5 ms

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END Step_Function 

