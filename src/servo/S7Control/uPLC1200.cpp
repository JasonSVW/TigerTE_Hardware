#include "uPLC1200.h"

TServo* vServoObj = nullptr;
TThreadHeartbeat* vHeartbeatThread = nullptr;
TThreadGetData* vGetDataThread = nullptr;

const TDataRecord AddrSetHandShake = { S7AreaDB, 50, 0, 1, S7WLBit };
const TDataRecord AddrSetS1ServoOn = { S7AreaDB, 50, 1, 1, S7WLBit };
const TDataRecord AddrSetS1Start = { S7AreaDB, 50, 2, 1, S7WLBit };
const TDataRecord AddrSetS1Stop = { S7AreaDB, 50, 3, 1, S7WLBit };
const TDataRecord AddrSetS1JogF = { S7AreaDB, 50, 4, 1, S7WLBit };
const TDataRecord AddrSetS1JogB = { S7AreaDB, 50, 5, 1, S7WLBit };
const TDataRecord AddrSetS1GoZero = { S7AreaDB, 50, 6, 1, S7WLBit };
const TDataRecord AddrSetS1SetZero = { S7AreaDB, 50, 7, 1, S7WLBit };
const TDataRecord AddrSetS2ServoOn = { S7AreaDB, 50, 8, 1, S7WLBit };
const TDataRecord AddrSetS2Start = { S7AreaDB, 50, 9, 1, S7WLBit };
const TDataRecord AddrSetS2Stop = { S7AreaDB, 50, 10, 1, S7WLBit };
const TDataRecord AddrSetS2JogF = { S7AreaDB, 50, 11, 1, S7WLBit };
const TDataRecord AddrSetS2JogB = { S7AreaDB, 50, 12, 1, S7WLBit };
const TDataRecord AddrSetS2GoZero = { S7AreaDB, 50, 13, 1, S7WLBit };
const TDataRecord AddrSetS2SetZero = { S7AreaDB, 50, 14, 1, S7WLBit };
const TDataRecord AddrSetS7Reset = { S7AreaDB, 50, 15, 1, S7WLBit };
const TDataRecord AddrSetS1APos = { S7AreaDB, 50, 2, 1, S7WLReal };
const TDataRecord AddrSetS1ASpd = { S7AreaDB, 50, 6, 1, S7WLReal };
const TDataRecord AddrSetS1APosSpd = { S7AreaDB, 50, 2, 2, S7WLReal };
const TDataRecord AddrSetS1MPos = { S7AreaDB, 50, 10, 1, S7WLReal };
const TDataRecord AddrSetS1MSpd = { S7AreaDB, 50, 14, 1, S7WLReal };
const TDataRecord AddrSetS1MPosSpd = { S7AreaDB, 50, 10, 2, S7WLReal };
const TDataRecord AddrSetS2APos = { S7AreaDB, 50, 18, 1, S7WLReal };
const TDataRecord AddrSetS2ASpd = { S7AreaDB, 50, 22, 1, S7WLReal };
const TDataRecord AddrSetS2APosSpd = { S7AreaDB, 50, 18, 2, S7WLReal };
const TDataRecord AddrSetS2MPos = { S7AreaDB, 50, 26, 1, S7WLReal };
const TDataRecord AddrSetS2MSpd = { S7AreaDB, 50, 30, 1, S7WLReal };
const TDataRecord AddrSetS2MPosSpd = { S7AreaDB, 50, 26, 2, S7WLReal };
const TDataRecord AddrGetS7IsHandShake = { S7AreaDB, 51, 0, 1, S7WLBit };
const TDataRecord AddrGetS7IsPowerOn = { S7AreaDB, 51, 1, 1, S7WLBit };
const TDataRecord AddrGetS7IsAutoMode = { S7AreaDB, 51, 2, 1, S7WLBit };
const TDataRecord AddrGetS7IsFault = { S7AreaDB, 51, 3, 1, S7WLBit };
const TDataRecord AddrGetS1IsServoOn = { S7AreaDB, 51, 4, 1, S7WLBit };
const TDataRecord AddrGetS1ZeroExisted = { S7AreaDB, 51, 5, 1, S7WLBit };
const TDataRecord AddrGetS1IsReady = { S7AreaDB, 51, 6, 1, S7WLBit };
const TDataRecord AddrGetS1RunFinished = { S7AreaDB, 51, 7, 1, S7WLBit };
const TDataRecord AddrGetS1IsFault = { S7AreaDB, 51, 8, 1, S7WLBit };
const TDataRecord AddrGetS2IsServoOn = { S7AreaDB, 51, 9, 1, S7WLBit };
const TDataRecord AddrGetS2ZeroExisted = { S7AreaDB, 51, 10, 1, S7WLBit };
const TDataRecord AddrGetS2IsReady = { S7AreaDB, 51, 11, 1, S7WLBit };
const TDataRecord AddrGetS2RunFinished = { S7AreaDB, 51, 12, 1, S7WLBit };
const TDataRecord AddrGetS2IsFault = { S7AreaDB, 51, 13, 1, S7WLBit };
const TDataRecord AddrGetS1ActPosition = { S7AreaDB, 51, 2, 1, S7WLReal };
const TDataRecord AddrGetS1ActSpeed = { S7AreaDB, 51, 6, 1, S7WLReal };
const TDataRecord AddrGetS2ActPosition = { S7AreaDB, 51, 10, 1, S7WLReal };
const TDataRecord AddrGetS2ActSpeed = { S7AreaDB, 51, 14, 1, S7WLReal };
const TDataRecord AddrGetAllData = { S7AreaDB, 51, 0, 18, S7WLByte };
const TDataRecord AddrSetS3GoOut = { S7AreaDB, 50, 11, 1, S7WLBit };
const TDataRecord AddrSetS3GoIn = { S7AreaDB, 50, 12, 1, S7WLBit };
const TDataRecord AddrSetS3Current = { S7AreaDB, 50, 18, 1, S7WLReal };

/* class TThreadHeartbeat */
TThreadHeartbeat::TThreadHeartbeat() : terminated(false), suspended(false), errorCount(0), exitCount(0) {
    heartbeatThread = std::thread(&TThreadHeartbeat::Execute, this);
}

TThreadHeartbeat::~TThreadHeartbeat() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        terminated = true;
        condition.notify_all();
    }
    if(heartbeatThread.joinable()) {
        heartbeatThread.join();
    }
}

void TThreadHeartbeat::HeartbeatResume() {
    std::unique_lock<std::mutex> lock(mutex);
    if(suspended) {
        suspended = false;
        condition.notify_all();
        vLog("HeartbeatResume: Heartbeat thread resumed.", LVL_INFO);
    }
    else {
        vLog("HeartbeatResume: Heartbeat thread not suspended.", LVL_INFO);
    }
}

void TThreadHeartbeat::HeartbeatSuspend() {
    std::unique_lock<std::mutex> lock(mutex);
    if(suspended) {
        vLog("HeartbeatSuspend: Heartbeat thread already suspended.", LVL_INFO);
    }
    else {
        suspended = true;
        vLog("HeartbeatSuspend: Heartbeat thread suspended.", LVL_INFO);
    }
}

void TThreadHeartbeat::Heartbeatexit() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        terminated = true;
        condition.notify_all();
    }
    exitCount = 0;
    while(!finished) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        exitCount++;
        if(exitCount > 5000) {
            vLog("Heartbeatexit: wait Heartbeat thread exit timeout.", LVL_ERROR);
            break;
        }
    }
}

void TThreadHeartbeat::Execute() {
    while(!terminated) {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [this] { return !suspended || terminated; });
        if(terminated) break;

        if(S7_Heartbeat() == 0) {
            errorCount = 0;
        }
        else {
            errorCount++;
            if(errorCount > 10) {
                vLog("TThreadHeartbeat Execute: Heartbeat thread persistent error, Suspended self, Handshake again to restart", LVL_ERROR);
                HeartbeatSuspend();
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    vLog("TThreadHeartbeat Execute: Heartbeat thread exit.", LVL_INFO);
    finished = true;
}

int TThreadHeartbeat::S7_Heartbeat() {
    if(vServoObj == nullptr) {
        vLog("S7_Heartbeat: vServoObj is not exist", LVL_ERROR);
        return -1;
    }

    if(!vServoObj->FS7IsConnected) {
        vLog("S7_Heartbeat: servo not connected", LVL_ERROR);
        return -1;
    }

    unsigned char AWriteByte = 1;
    if(vServoObj->S7Write(AddrSetHandShake, &AWriteByte, false) != 0) {
        vLog("S7_Heartbeat: S7 Write heartbeat address error.", LVL_ERROR);
        return -2;
    }

    return 0;
}

void TThreadHeartbeat::vLog(const std::string& message, int level) {
    std::cout << message << std::endl;
}

/* class TThreadGetData */
TThreadGetData::TThreadGetData() : terminated(false), suspended(false), errorCount(0), exitCount(0) {
    getDataThread = std::thread(&TThreadGetData::Execute, this);
}

TThreadGetData::~TThreadGetData() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        terminated = true;
        condition.notify_all();
    }
    if(getDataThread.joinable()) {
        getDataThread.join();
    }
}

void TThreadGetData::GetDataResume() {
    std::unique_lock<std::mutex> lock(mutex);
    if(suspended) {
        suspended = false;
        condition.notify_all();
        vLog("GetDataResume: Getdata thread resumed", LVL_INFO);
    }
    else {
        vLog("GetDataResume: Getdata thread not suspended", LVL_INFO);
    }
}

void TThreadGetData::GetDataSuspend() {
    std::unique_lock<std::mutex> lock(mutex);
    if(suspended) {
        vLog("GetDataSuspend: Getdata thread already suspended", LVL_INFO);
    }
    else {
        suspended = true;
        vLog("GetDataSuspend: Getdata thread suspended", LVL_INFO);
    }
}

void TThreadGetData::GetDataexit() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        terminated = true;
        condition.notify_all();
    }
    exitCount = 0;
    while(!finished) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        exitCount++;
        if(exitCount > 5000) {
            vLog("GetDataexit: Error: wait getdata thread exit timeout", LVL_ERROR);
            break;
        }
    }
}

void TThreadGetData::Execute() {
    while(!terminated) {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [this] { return !suspended || terminated; });
        if(terminated) break;

        if(S7_GetData() == 0) {
            errorCount = 0;
        }
        else {
            errorCount++;
            if(errorCount > 10) {
                vLog("TThreadGetData Execute: Getdata thread persistent error, suspended self, connected again to restart", LVL_ERROR);
                GetDataSuspend();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    vLog("TThreadGetData Execute: Getdata thread exit.", LVL_INFO);
    finished = true;
}

int TThreadGetData::S7_GetData() {
    if(vServoObj == nullptr) {
        vLog("S7_GetData: Error: vServoObj is not exist", LVL_ERROR);
        return -1;
    }
    return vServoObj->S7_GetAllData();
}

void TThreadGetData::vLog(const std::string& message, int level) {
    std::cout << message << std::endl;
}





/* export function */
int servo_check() {
    if(vServoObj == nullptr) {
        std::cerr << "Created servo object failed" << std::endl;
        return -1;
    }
    return 0;
}

int servo_create() {
    if(vServoObj == nullptr) {
        vServoObj = new TServo(true);
    }

    if(!vServoObj->FSnap7IsLoaded) {
        delete vServoObj;
        vServoObj = nullptr;
        std::cerr << "Servo DLL Load Failed" << std::endl;
        return -3;
    }
    return 0;
}

int servo_destroy() {
    if(vServoObj == nullptr) {
        std::cout << "no servo object existed" << std::endl;
        return 0;
    }
    else {
        delete vServoObj;
        vServoObj = nullptr;
        std::cout << "Servo object destroyed" << std::endl;
        return 0;
    }
}

int servo_connect(const char* AIPAddr) {
    vServoObj->FRemoteAddress = AIPAddr;

    int result = servo_check();
    if(result != 0)
        return result;

    if(vServoObj->S7_Connection() != 0) {
        std::cerr << "can not connect with servo system, check IP Address" << std::endl;
        return -3;
    }
    if(vServoObj->S7_HandsShake(true, 10000) != 0) {
        std::cerr << "handshake with servo system failed" << std::endl;
        return -4;
    }

    std::cout << "MP API: Servo connected successfully" << std::endl;
    return 0;
}

int servo_disconnect() {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FS7IsConnected) {
        result = vServoObj->S7_Disconnection();
        if(result != 0)
            std::cout << "disconnect succeffully failed" << std::endl;
        else
            std::cout << "disconnect succeffully" << std::endl;
        return result;
    }
    else {
        std::cout << "no connection with servo system" << std::endl;
        return 0;
    }
}

int servo_clear_fault() {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S7_ClearFault();
}

int pedal_servo_limit(float AMaxPositionMM, float AMinPositionMM, float AMaxSpeedMMpS) {
    int result = servo_check();
    if(result != 0)
        return result;
    vServoObj->FS1MaxPosition = AMaxPositionMM;
    vServoObj->FS1MinPosition = AMinPositionMM;
    vServoObj->FS1MaxSpeed = AMaxSpeedMMpS;
    return 0;
}

int pedal_servo_on(bool AEnable) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(!vServoObj->FS7IsAutoMode) {
        std::cerr << "Servo control mode is manual mode, switch the mode on the door first" << std::endl;
        return -3;
    }

    if(AEnable) {
        if(vServoObj->S1_ServoON(true, 5000) != 0) {
            std::cerr << "Pedal Servo On Failed" << std::endl;
            return -4;
        }
    }
    else {
        if(vServoObj->S1_ServoON(false, 5000) != 0) {
            std::cerr << "Pedal Servo On Failed" << std::endl;
            return -4;
        }
    }
    return 0;
}

int pedal_enable_run(bool AEnable) {
    int result = servo_check();
    if(result != 0)
        return result;

    if(!vServoObj->FS7IsAutoMode) {
        std::cerr << "Servo control mode is manual mode, switch the mode on the door first" << std::endl;
        return -3;
    }

    if(AEnable) {
        if(vServoObj->S1_Run_On() != 0) {
            std::cerr << "Pedal Servo Enable Run Failed" << std::endl;
            return -4;
        }
    }
    else {
        if(vServoObj->S1_Run_Off() != 0) {
            std::cerr << "Pedal Servo Disable Run Failed" << std::endl;
            return -5;
        }
    }
    return 0;
}

int pedal_go_step_syn(float ARelPositionMM, float ASpeedMMpS, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_step_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoRelPos_AutoMode_Syn(ARelPositionMM, ASpeedMMpS, ATimeout);
    }
}

int pedal_go_step_asyn(float ARelPositionMM, float ASpeedMMpS) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_step_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoRelPos_AutoMode_Asyn(ARelPositionMM, ASpeedMMpS);
    }
}

int pedal_go_position_syn(float AAbsPositionMM, float ASpeedMMpS, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_position_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoAbsPos_AutoMode_Syn(AAbsPositionMM, ASpeedMMpS, ATimeout);
    }
}

int pedal_go_position_asyn(float AAbsPositionMM, float ASpeedMMpS) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_position_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoAbsPos_AutoMode_Asyn(AAbsPositionMM, ASpeedMMpS);
    }
}

int pedal_sys_position_asyn(float AAbsPositionMM, float ASpeedMMpS) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FPedalIsSysMode)
        return vServoObj->S1_GoAbsPos_AutoMode_Asyn(AAbsPositionMM, ASpeedMMpS);
    else {
        std::cerr << "pedal_sys_position_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent is not actived, using pedal_position_auto_mode(true) to enable first" << std::endl;
        return -20;
    }
}

int pedal_go_step_percent_syn(float ARelPositionPercent, float ASpeedMMpS, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;

    float AStepMM = ARelPositionPercent * vServoObj->FS1MaxPosition / 100;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_step_percent_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoRelPos_AutoMode_Syn(AStepMM, ASpeedMMpS, ATimeout);
    }
}

int pedal_go_step_percent_asyn(float ARelPositionPercent, float ASpeedMMpS) {
    int result = servo_check();
    if(result != 0)
        return result;

    float AStepMM = ARelPositionPercent * vServoObj->FS1MaxPosition / 100;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_step_percent_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoRelPos_AutoMode_Asyn(AStepMM, ASpeedMMpS);
    }
}

int pedal_go_position_percent_syn(float AAbsPositionPercent, float ASpeedMMpS, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;

    float AAbsPositionMM = AAbsPositionPercent * vServoObj->FS1MaxPosition / 100;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_position_percent_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoAbsPos_AutoMode_Syn(AAbsPositionMM, ASpeedMMpS, ATimeout);
    }
}

int pedal_go_position_percent_asyn(float AAbsPositionPercent, float ASpeedMMpS) {
    int result = servo_check();
    if(result != 0)
        return result;

    float AAbsPositionMM = AAbsPositionPercent * vServoObj->FS1MaxPosition / 100;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_position_percent_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoAbsPos_AutoMode_Asyn(AAbsPositionMM, ASpeedMMpS);
    }
}

int pedal_sys_position_percent_asyn(float AAbsPositionPercent, float ASpeedMMpS) {
    int result = servo_check();
    if(result != 0)
        return result;
    float AAbsPositionMM = AAbsPositionPercent * vServoObj->FS1MaxPosition / 100;
    if(vServoObj->FPedalIsSysMode)
        return vServoObj->S1_GoAbsPos_AutoMode_Asyn(AAbsPositionMM, ASpeedMMpS);
    else {
        std::cerr << "pedal_sys_position_percent_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent is not actived, using pedal_position_auto_mode(true) to enable first" << std::endl;
        return -20;
    }
}

int pedal_go_home_syn(int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_home_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoZero_Syn(ATimeout);
    }
}

int pedal_go_home_asyn() {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FPedalIsSysMode) {
        std::cerr << "pedal_go_home_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first" << std::endl;
        return -20;
    }
    else {
        return vServoObj->S1_GoZero_Asyn();
    }
}

int pedal_set_home(int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S1_SetZero(ATimeout);
}

int pedal_go_auto_mode(bool AEanble) {
    int result = servo_check();
    if(result != 0)
        return result;
    vServoObj->FPedalIsSysMode = AEanble;
    return 0;
}

int rotate_servo_limit(float AMaxDegree, float AMinDegree, float AMaxSpeedDpS) {
    int result = servo_check();
    if(result != 0)
        return result;

    vServoObj->FS2MaxPosition = AMaxDegree;
    vServoObj->FS2MinPosition = AMinDegree;
    vServoObj->FS2MaxSpeed = AMaxSpeedDpS;
    return 0;
}

int rotate_servo_on(bool AEnable) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(!vServoObj->FS7IsAutoMode) {
        std::cerr << "Servo control mode is manual mode, switch the mode on the door first" << std::endl;
        return -3;
    }

    if(AEnable) {
        if(vServoObj->S2_ServoON(true, 5000) != 0) {
            std::cerr << "slope Servo On Failed" << std::endl;
            return -4;
        }
    }
    else {
        if(vServoObj->S2_ServoON(false, 5000) != 0) {
            std::cerr << "slope Servo On Failed" << std::endl;
            return -4;
        }
    }
    return 0;
}

int rotate_enable_run(bool AEnable) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(!vServoObj->FS7IsAutoMode) {
        std::cerr << "Servo control mode is manual mode, switch the mode on the door first" << std::endl;
        return -3;
    }

    if(AEnable) {
        if(vServoObj->S2_Run_On() != 0) {
            std::cerr << "slope Servo Enable Run Failed" << std::endl;
            return -4;
        }
    }
    else {
        if(vServoObj->S2_Run_Off() != 0) {
            std::cerr << "slope Servo Disable Run Failed" << std::endl;
            return -5;
        }
    }
    return 0;
}

int rotate_go_step_syn(float ARelDegree, float ASpeedDpS, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoRelPos_AutoMode_Syn(ARelDegree, ASpeedDpS, ATimeout);
}

int rotate_go_step_asyn(float ARelDegree, float ASpeedDpS) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoRelPos_AutoMode_Asyn(ARelDegree, ASpeedDpS);
}

int rotate_go_position_syn(float AAbsDegree, float ASpeedDpS, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoAbsPos_AutoMode_Syn(AAbsDegree, ASpeedDpS, ATimeout);
}

int rotate_go_position_asyn(float AAbsDegree, float ASpeedDpS) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoAbsPos_AutoMode_Asyn(AAbsDegree, ASpeedDpS);
}

int rotate_go_home_syn(int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoZero_Syn(ATimeout);
}

int rotate_go_home_asyn() {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoZero_Asyn();
}

int rotate_set_home(int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_SetZero(ATimeout);
}

int rotate_go_slope_step_syn(float ARelGradPercent, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoRelSlopGrad_AutoMode_Syn(ARelGradPercent, ATimeout);
}

int rotate_go_slope_step_asyn(float ARelGradPercent) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoRelSlopGrad_AutoMode_Asyn(ARelGradPercent);
}

int rotate_go_slope_syn(float AAbsGradPercent, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoAbsSlopGrad_AutoMode_Syn(AAbsGradPercent, ATimeout);
}

int rotate_go_slope_asyn(float AAbsGradPercent) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoRelSlopGrad_AutoMode_Asyn(AAbsGradPercent);
}

int rotate_go_mount_position_syn(int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoMountPos_AutoMode_Syn(ATimeout);
}

int rotate_go_mount_position_asyn() {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S2_GoMountPos_AutoMode_ASyn();
}

int rotate_set_slope_speed(float ASpeedDpS) {
    int result = servo_check();
    if(result != 0)
        return result;
    if((ASpeedDpS < 0) || (ASpeedDpS > 10)) {
        std::cerr << "The rotate servo slope run speed need in range [0,10], current setting is " << ASpeedDpS << " deg/s" << std::endl;
        return -2;
    }

    vServoObj->FS2SlopSpeed = ASpeedDpS;
    return 0;
}

int air_cylinder_push_out() {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S3_Go_Out();
}

int air_cylinder_push_back() {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S3_Go_In();
}

int air_cylinder_push_pressure(float ATargetPressureBar) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S3_Set_Target_Pressure(ATargetPressureBar);
}

int turntable_enable_control() {
    if(vServoObj == nullptr) {
        vServoObj = new TServo(true);
    }

    if(!vServoObj->FSnap7IsLoaded) {
        delete vServoObj;
        vServoObj = nullptr;
        std::cerr << "Servo DLL Load Failed" << std::endl;
        return -1;
    }

    if(vServoObj->S7_Connection() != 0) {
        std::cerr << "can not connect with servo system" << std::endl;
        return -2;
    }

    if(vServoObj->S7_HandsShake(true, 10000) != 0) {
        std::cerr << "handshake with servo system failed" << std::endl;
        return -3;
    }

    if(vServoObj->S1_ServoON(true, 5000) != 0) {
        std::cerr << "servo on failed" << std::endl;
        return -4;
    }

    if(vServoObj->S1_Run_On() != 0) {
        std::cerr << "servo on failed" << std::endl;
        return -5;
    }
    std::cout << "enable turntable successfully" << std::endl;
    return 0;
}

int turntable_disable_control() {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FS7IsConnected) {
        if(vServoObj->FS7IsFault) {
            if(vServoObj->S7_ClearFault() != 0)
                std::cerr << "Servo has fault and cannot be cleared" << std::endl;
        }

        if(vServoObj->FS1IsServoOn) {
            if(vServoObj->S1_RunSpd_AutoMode_Syn(0, 2000) != 0)
                std::cerr << "set speed zero failed" << std::endl;

            if(vServoObj->S1_ServoON(false, 5000) != 0)
                std::cerr << "servo off failed" << std::endl;
        }
        if(vServoObj->S7_Disconnection() != 0)
            std::cerr << "disconnection wit servo failed" << std::endl;
    }
    if(vServoObj != nullptr) {
        delete vServoObj;
        vServoObj = nullptr;
    }
    std::cout << "disable turntable successfully" << std::endl;
    return 0;
}

int turntable_run_speed_rpm_asyn(float ATargetSpeedRPM) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S1_RunSpd_AutoMode_Asyn(ATargetSpeedRPM);
}

int turntable_run_speed_rpm_syn(float ATargetSpeedRPM, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S1_RunSpd_AutoMode_Syn(ATargetSpeedRPM, ATimeout);
}

int turntable_run_speed_dps_asyn(float ATargetSpeedDPS) {
    int result = servo_check();
    if(result != 0)
        return result;
    float ASpeedRPM = ATargetSpeedDPS / 6.0;
    return vServoObj->S1_RunSpd_AutoMode_Asyn(ASpeedRPM);
}

int turntable_run_speed_dps_syn(float ATargetSpeedDPS, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    float ASpeedRPM = ATargetSpeedDPS / 6.0;
    return vServoObj->S1_RunSpd_AutoMode_Syn(ASpeedRPM, ATimeout);
}

int turntable_run_centrifugal_acc_asyn(float ATargetAccelerationG, float AArmLengthMM) {
    int result = servo_check();
    if(result != 0)
        return result;
    if((AArmLengthMM < 90) || (AArmLengthMM > 160)) {
        std::cerr << "the arm lengthen should in rang [90, 160]mm" << std::endl;
        return -10;
    }
    if(ATargetAccelerationG < 0) {
        std::cerr << "the set g should greater than zero" << std::endl;
        return -10;
    }

    float ASpeedRPM = sqrt(ATargetAccelerationG * 9.8 / (AArmLengthMM / 1000.0)) * 30.0 / pi;
    return vServoObj->S1_RunSpd_AutoMode_Asyn(ASpeedRPM);
}

int turntable_run_centrifugal_acc_syn(float ATargetAccelerationG, float AArmLengthMM, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    if((AArmLengthMM < 90) || (AArmLengthMM > 160)) {
        std::cerr << "the arm lengthen should in rang [90, 160]mm" << std::endl;
        return -10;
    }
    if(ATargetAccelerationG < 0) {
        std::cerr << "the set g should greater than zero" << std::endl;
        return -10;
    }

    float ASpeedRPM = sqrt(ATargetAccelerationG * 9.8 / (AArmLengthMM / 1000.0)) * 30.0 / pi;
    return vServoObj->S1_RunSpd_AutoMode_Syn(ASpeedRPM, ATimeout);
}

int turntable_stop_run_asyn() {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S1_RunSpd_AutoMode_Asyn(0);
}

int turntable_stop_run_syn(int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    return vServoObj->S1_RunSpd_AutoMode_Syn(0, ATimeout);
}

TServo::TServo(bool AOnlyPedalServo)
    : FS7IsOnlyPedal(AOnlyPedalServo), FSnap7IsLoaded(false), FS7Client(nullptr), FS7IsConnected(false), FS7IsHandShaked(false), FS7IsPowerOn(false), FS7IsAutoMode(false), FS7IsFault(false), FS7IsOnlyPedal(false), FS7WithAirCylinder(false), FS1IsServoOn(false), FS1ZeroExisted(false), FS1IsReady(false), FS1RunFinished(false), FS1IsFault(false), FS2IsServoOn(false), FS2ZeroExisted(false), FS2IsReady(false), FS2RunFinished(false), FS2IsFault(false), FS1ActPosition(0.0f), FS1ActSpeed(0.0f), FS2ActPosition(0.0f), FS2ActPositionGrad(0.0f), FS2ActSpeed(0.0f), FS1MaxSpeed(500.0f), FS1MaxPosition(60.0f), FS1MinPosition(-10.0f), FS2MaxSpeed(10.0f), FS2MaxPosition(20.0f), FS2MinPosition(-20.0f), FS2MountPosition(0.0f), FS2SlopSpeed(0.0f), FS3TargetCurrent(0.0f), FS1TargetPositionManual(0.0f), FS1TargetSpeedManual(0.0f), FS2TargetPositionManual(0.0f), FS2TargetSpeedManual(0.0f), FS1TargetPositionAuto(0.0f), FS1TargetSpeedAuto(0.0f), FS2TargetPositionAuto(0.0f), FS2TargetSpeedAuto(0.0f), FPedalIsSysMode(false), FS3MCMaxPressure(0.0f), FS3P2AFactor(0.0f), FS3P2AOffset(0.0f) {
    if(InitializeSnap7Api()) {
        std::cout << "Load Snap7 successful" << std::endl;
        FSnap7IsLoaded = true;
    }
    else {
        std::cerr << "Load Snap7 failed" << std::endl;
        FSnap7IsLoaded = false;
    }
    RegisterSystemVars();

    // FS7Client = new TS7Client();
    // S7 = new TS7Helper();
    FS7IsConnected = false;
    FS7IsHandShaked = false;

    vHeartbeatThread = new TThreadHeartbeat();
    std::cout << "TServo.Create: Servo Object is created" << std::endl;
    FS1MaxSpeed = 500.0f;
    FS1MaxPosition = 60.0f;
    FS1MinPosition = -10.0f;
    FS2MaxSpeed = 10.0f;
    FS2MaxPosition = 20.0f;
    FS2MinPosition = -20.0f;
    FS2SlopSpeed = 0.0f;
    FS2MountPosition = 0.0f;
    FRemoteAddress = "192.168.1.1";
    FPedalIsSysMode = false;
    FS3MCMaxPressure = 0.0f;
    FS3P2AFactor = 0.0f;
    FS3P2AOffset = 0.0f;

    vGetDataThread = new TThreadGetData();
}

TServo::~TServo() {
    if(FS7IsConnected) {
        if(FS1IsReady)
            S1_Run_Off();
        if(FS1IsServoOn)
            S1_ServoON(false, 2000);
        if(!FS7IsOnlyPedal) {
            if(FS2IsReady)
                S2_Run_Off();
            if(FS2IsServoOn)
                S2_ServoON(false, 2000);
        }
        if(FS7IsHandShaked)
            S7_HandsShake(false, 2000);
        S7_Disconnection();
    }

    if(S7 != nullptr) {
        delete S7;
        S7 = nullptr;
    }

    if(FS7Client != nullptr) {
        delete FS7Client;
        FS7Client = nullptr;
    }

    if(vHeartbeatThread != nullptr) {
        vHeartbeatThread->Heartbeatexit();
        delete vHeartbeatThread;
        vHeartbeatThread = nullptr;
    }

    if(vGetDataThread != nullptr) {
        vGetDataThread->GetDataexit();
        delete vGetDataThread;
        vGetDataThread = nullptr;
    }

    UnregisterSystemVars();

    FinalizeSnap7Api();
}

void TServo::RegisterSystemVars() {
    // RegisterInternalVar("PedalSpeed", "Servo Pedal Speed", true, svtDouble);
    // RegisterInternalVar("PedalPosition", "Servo Pedal Position", true, svtDouble);
    // RegisterInternalVar("RotateDegree", "Servo Slope Rotate Degree", true, svtDouble);
    // RegisterInternalVar("SlopeGrad", "Servo Slope Gradient", true, svtDouble);
}

void TServo::UnregisterSystemVars() {
    // UnRegisterInternalVar("PedalSpeed");
    // UnRegisterInternalVar("PedalPosition");
    // UnRegisterInternalVar("RotateDegree");
    // UnRegisterInternalVar("SlopeGrad");
}

int TServo::S7_ClearFault(int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS7IsHandShaked) {
        std::cerr << "S7_ClearFault: HandShake needed before Servo On" << std::endl;
        return -1;
    }
    if(!FS7IsPowerOn) {
        std::cerr << "S7_ClearFault: Power is off" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS7Reset, &AWriteByte, false) != 0) {
        std::cerr << "S7_ClearFault: S7 Write servo reset address error" << std::endl;
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(!FS1IsFault) {
            std::cout << "S7_ClearFault: clear fault Successful" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S7_ClearFault: Clear fault timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S7_Connection() {
    int PingTime = 0;
    FS7LastError = FS7Client->SetParam(p_i32_PingTimeout, &PingTime);
    if(FS7LastError != 0) {
        return -1;
    }

    FS7Client->SetConnectionType(1);
    FS7LastError = FS7Client->ConnectTo(FRemoteAddress.c_str(), 0, 0);
    Sleep(50);
    if(FS7LastError != 0) {
        std::cerr << "S7_Connection: Servo Connect error, can not find device under IP: " << FRemoteAddress << std::endl;
        FS7IsConnected = false;
    }
    else {
        std::cout << "S7_Connection: Servo Connect Successful, device IP is: " << FRemoteAddress << std::endl;
        vGetDataThread = new TThreadGetData();
        FS7IsConnected = true;
    }
    return FS7LastError;
}

int TServo::S7_Disconnection() {
    if(vGetDataThread != nullptr) {
        vGetDataThread->GetDataexit();
        delete vGetDataThread;
        vGetDataThread = nullptr;
    }
    FS7LastError = FS7Client->Disconnect();
    if(FS7LastError != 0) {
        std::cerr << "S7_Disconnection: Servo disconnect error" << std::endl;
    }
    else {
        std::cout << "S7_Disconnection: Servo disconnect Successful. Device IP is:" << FRemoteAddress << std::endl;
    }

    FS7IsConnected = false;
    return FS7LastError;
}

int TServo::S7_GetAllData() {
    if(!FS7IsConnected) {
        std::cerr << "S7_GetAllData: Connected is needed" << std::endl;
        return -1;
    }

    if(S7Read(AddrGetAllData, &FS7Buffer, false) == 0) {
        FS7IsHandShaked = (FS7Buffer[0] & 0x01) != 0;
        FS7IsPowerOn = (FS7Buffer[0] & 0x02) != 0;
        FS7IsAutoMode = (FS7Buffer[0] & 0x04) != 0;
        FS7IsFault = (FS7Buffer[0] & 0x08) != 0;
        FS1IsServoOn = (FS7Buffer[0] & 0x10) != 0;
        FS1ZeroExisted = (FS7Buffer[0] & 0x20) != 0;
        FS1IsReady = (FS7Buffer[0] & 0x40) != 0;
        FS1RunFinished = (FS7Buffer[0] & 0x80) != 0;
        FS1IsFault = (FS7Buffer[1] & 0x01) != 0;
        FS2IsServoOn = (FS7Buffer[1] & 0x02) != 0;
        FS2ZeroExisted = (FS7Buffer[1] & 0x04) != 0;
        FS2IsReady = (FS7Buffer[1] & 0x08) != 0;
        FS2RunFinished = (FS7Buffer[1] & 0x10) != 0;
        FS2IsFault = (FS7Buffer[1] & 0x20) != 0;
        FS1ActPosition = *(float*) (FS7Buffer + 2);
        FS1ActSpeed = *(float*) (FS7Buffer + 6);
        FS2ActPosition = *(float*) (FS7Buffer + 10);
        FS2ActSpeed = *(float*) (FS7Buffer + 14);
        return 0;
    }
    else {
        return -1;
    }
}

int TServo::S7_HandsShake(bool AEnable, int ATimeout) {
    unsigned char AWriteByte = 0;

    if(!FS7IsConnected) {
        std::cerr << "S7_HandsShake: servo not connected" << std::endl;
        return -1;
    }

    if(AEnable) {
        AWriteByte |= 0x01;
    }

    if(S7Write(AddrSetHandShake, &AWriteByte, false) != 0) {
        std::cerr << "S7_HandsShake: S7 Write Handshake address error" << std::endl;
        return -2;
    }

    int ATime = 0;

    if(AEnable) {
        while(true) {
            if(FS7IsHandShaked) {
                std::cout << "S7_HandsShake: Servo Handshake Set Success" << std::endl;
                return 0;
            }

            Sleep(1);
            ATime++;
            if(ATime > ATimeout) {
                std::cerr << "S7_HandsShake: Servo Handshake is Timeout, timeout setting is " << ATimeout << "ms" << std::endl;
                return -3;
            }
        }
    }
    else {
        vHeartbeatThread->HeartbeatSuspend();
        std::cout << "S7_HandsShake: Servo Handshake Reset Success" << std::endl;
        return 0;
    }
}

int TServo::S7Read(const TDataRecord& AField, void* pData, bool Async) {
    std::lock_guard<std::mutex> lock(FMonitorObj);
    if(Async)
        FS7LastError = FS7Client->AsReadArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);
    else
        FS7LastError = FS7Client->ReadArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);

    if(FS7LastError == 0) {
        if(Async)
            S7WaitCompletion();
    }
    else {
        std::cerr << "S7Read: Servo Read Action Error" << std::endl;
    }
    return FS7LastError;
}

int TServo::S1_GoAbsPos_AutoMode_Asyn(float AAbsPosMM, float ASpeedMMS) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        std::cerr << "S1_GoAbsPos_AutoMode_Asyn: Servo 1 is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S1_GoAbsPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetPosition = AAbsPosMM;
    if(AAbsPosMM > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        std::cerr << "S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is greater than the max value(" << FS1MaxPosition << "), and the target value used the max value instead" << std::endl;
    }
    else if(AAbsPosMM < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        std::cerr << "S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is smaller than the min value(" << FS1MinPosition << "), and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        std::cerr << "S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is greater than the max value(" << FS1MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        std::cerr << "S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionAuto = ASetPosition;
    FS1TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_GoAbsPos_AutoMode_Asyn: S1 auto mode goto abs. position write error" << std::endl;
        return -2;
    }
    else {
        if(!FPedalIsSysMode)
            std::cout << "S1_GoAbsPos_AutoMode_Asyn: S1 auto mode goto abs. position send out" << std::endl;
        return 0;
    }
}

int TServo::S1_GoAbsPos_AutoMode_Syn(float AAbsPosMM, float ASpeedMMS, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        std::cerr << "S1_GoAbsPos_AutoMode_Syn: Servo 1 is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S1_GoAbsPos_AutoMode_Syn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetPosition = AAbsPosMM;
    if(AAbsPosMM > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        std::cerr << "S1_GoAbsPos_AutoMode_Syn: S1 Set positon is greater than the max value(" << FS1MaxPosition << "), and the target value used the max value instead" << std::endl;
    }
    else if(AAbsPosMM < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        std::cerr << "S1_GoAbsPos_AutoMode_Syn: S1 Set positon is smaller than the min value(" << FS1MinPosition << "), and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        std::cerr << "S1_GoAbsPos_AutoMode_Syn: S1 Set positon is greater than the max value(" << FS1MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        std::cerr << "S1_GoAbsPos_AutoMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionAuto = ASetPosition;
    FS1TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_GoAbsPos_AutoMode_Syn: S1 auto mode goto abs. position write error" << std::endl;
        return -2;
    }

    FS1RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS1RunFinished && fabs(FS1TargetPositionAuto - FS1ActPosition) < PositionMaxTol) {
            std::cout << "S1_GoAbsPos_AutoMode_Syn: S1 auto mode goto abs. position finished" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S1_GoAbsPos_AutoMode_Syn: go abs position timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S1_RunSpd_AutoMode_Asyn(float ASpeedRPM) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        ```cpp
            std::cerr << "S1_RunSpd_AutoMode_Asyn: Servo 1 is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S1_RunSpd_AutoMode_Asyn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetSpeed = ASpeedRPM;
    if(ASpeedRPM > 450) {
        ASetSpeed = 450;
        std::cerr << "S1_RunSpd_AutoMode_Asyn: S1 Set speed is greater than the max value(450 rpm), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedRPM < -450) {
        ASetSpeed = -450;
        std::cerr << "S1_RunSpd_AutoMode_Asyn: S1 Set positon is smaller than the min value(-450 rpm), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionAuto = 0;
    FS1TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = 0;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_RunSpd_AutoMode_Asyn: S1 auto mode run speed write error" << std::endl;
        return -2;
    }
    return 0;
}

int TServo::S1_RunSpd_AutoMode_Syn(float ASpeedRPM, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        std::cerr << "S1_RunSpd_AutoMode_Syn: Servo 1 is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S1_RunSpd_AutoMode_Syn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetSpeed = ASpeedRPM;
    if(ASpeedRPM > 450) {
        ASetSpeed = 450;
        std::cerr << "S1_RunSpd_AutoMode_Syn: S1 Set speed is greater than the max value(450 rpm), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedRPM < -450) {
        ASetSpeed = -450;
        std::cerr << "S1_RunSpd_AutoMode_Syn: S1 Set speed is smaller than the min value(-450 rpm), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionAuto = 0;
    FS1TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = 0;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_RunSpd_AutoMode_Syn: S1 auto mode run target speed write error" << std::endl;
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(fabs(FS1TargetSpeedAuto - FS1ActSpeed) < 0.1) {
            std::cout << "S1_RunSpd_AutoMode_Syn: S1 auto mode run target speed finished" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S1_RunSpd_AutoMode_Syn: S1 auto mode run to target speed timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S1_GoAbsPos_MMode_Asyn(float AAbsPosMM, float ASpeedMMS) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        std::cerr << "S1_GoAbsPostion_MMode_Asyn: Servo 1 is not ready" << std::endl;
        return -1;
    }

    if(FS7IsAutoMode) {
        std::cerr << "S1_GoAbsPostion_MMode_Asyn: Servo is in auto mode, switch to manual first" << std::endl;
        return -1;
    }

    float ASetPosition = AAbsPosMM;
    if(AAbsPosMM > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        std::cerr << "S1_GoAbsPostion_MMode_Asyn: S1 Set positon is greater than the max value(" << FS1MaxPosition << "), and the target value used the max value instead" << std::endl;
    }
    else if(AAbsPosMM < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        std::cerr << "S1_GoAbsPostion_MMode_Asyn: S1 Set positon is smaller than the min value(" << FS1MinPosition << "), and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        std::cerr << "S1_GoAbsPostion_MMode_Asyn: S1 Set positon is greater than the max value(" << FS1MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        std::cerr << "S1_GoAbsPostion_MMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionManual = ASetPosition;
    FS1TargetSpeedManual = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1MPosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_GoAbsPostion_MMode_Asyn: S1 manual mode goto abs. position write error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S1_GoAbsPostion_MMode_Asyn: S1 manual mode goto abs. position send out" << std::endl;
        return 0;
    }
}

int TServo::S1_GoAbsPos_MMode_Syn(float AAbsPosMM, float ASpeedMMS, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        std::cerr << "S1_GoAbsPostion_MMode_Syn: Servo 1 is not ready" << std::endl;
        return -1;
    }

    if(FS7IsAutoMode) {
        std::cerr << "S1_GoAbsPostion_MMode_Syn: Servo is in auto mode, switch to manual first" << std::endl;
        return -1;
    }

    float ASetPosition = AAbsPosMM;
    if(AAbsPosMM > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        std::cerr << "S1_GoAbsPostion_MMode_Syn: S1 Set positon is greater than the max value(" << FS1MaxPosition << "), and the target value used the max value instead" << std::endl;
    }
    else if(AAbsPosMM < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        std::cerr << "S1_GoAbsPostion_MMode_Syn: S1 Set positon is smaller than the min value(" << FS1MinPosition << "), and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        std::cerr << "S1_GoAbsPostion_MMode_Syn: S1 Set positon is greater than the max value(" << FS1MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        std::cerr << "S1_GoAbsPostion_MMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionManual = ASetPosition;
    FS1TargetSpeedManual = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1MPosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_GoAbsPostion_MMode_Syn: S1 manual mode goto abs. position write error" << std::endl;
        return -2;
    }

    FS1RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS1RunFinished && fabs(FS1TargetPositionManual - FS1ActPosition) < PositionMaxTol) {
            std::cout << "S1_GoAbsPostion_MMode_Syn: S1 manual mode goto abs. position finished" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S1_GoAbsPostion_MMode_Syn: go abs position timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S1_GoZero_Asyn() {
    unsigned char AWriteByte = 0;
    if(!FS1IsReady) {
        std::cerr << "S1_GoZero_Asyn: S1 not ready" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS1GoZero, &AWriteByte, false) != 0) {
        std::cerr << "S1_GoZero_Asyn: S7 Write go zero error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S1_GoZero_Asyn: S1 go zero comand send out" << std::endl;
        return 0;
    }
}

int TServo::S1_GoZero_Syn(int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS1IsReady) {
        std::cerr << "S1_GoZero_Syn: S1 not ready" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS1GoZero, &AWriteByte, false) != 0) {
        std::cerr << "S1_GoZero_Syn: S7 Write S1 go zero address error" << std::endl;
        return -2;
    }

    FS1RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS1RunFinished && fabs(FS1ActPosition) < PositionMaxTol)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S1_GoZero_Syn: Servo Go Zero Timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S1_Manual_JogIn() {
    unsigned char AWriteByte = 0;
    if(!FS1IsReady) {
        std::cerr << "S1_Manual_JogIn: S1 is not ready" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS1JogB, &AWriteByte, false) != 0) {
        std::cerr << "S1_Manual_JogIn: S7 Write bit error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S1_Manual_JogIn: S1 Jog In" << std::endl;
        return 0;
    }
}

int TServo::S1_Manual_JogOut() {
    unsigned char AWriteByte = 0;

    if(!FS1IsReady) {
        std::cerr << "S1_Manual_JogOut: S1 is not ready" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS1JogF, &AWriteByte, false) != 0) {
        std::cerr << "S1_Manual_JogOut: S7 Write bit error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S1_Manual_JogOut: S1 Jog Out" << std::endl;
        return 0;
    }
}

int TServo::S1_GoRelPos_AutoMode_Asyn(float ARelPosMM, float ASpeedMMS) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        std::cerr << "S1_GoRelPos_AutoMode_Asyn: Servo is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S1_GoRelPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetPosition = FS1ActPosition + ARelPosMM;

    if(ASetPosition > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        std::cerr << "S1_GoRelPos_AutoMode_Asyn: S1 Set positon is greater than the max value, and the target value used the max value instead" << std::endl;
    }
    else if(ASetPosition < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        std::cerr << "S1_GoRelPos_AutoMode_Asyn: S1 Set positon is smaller than the min value, and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        std::cerr << "S1_GoRelPos_AutoMode_Asyn: S1 Set positon is greater than the max value(" << FS1MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        std::cerr << "S1_GoRelPos_AutoMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionAuto = ASetPosition;
    FS1TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_GoRelPos_AutoMode_Asyn: S1 auto mode write speed error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S1_GoRelPos_AutoMode_Asyn: S1 auto mode goto rel. position send out" << std::endl;
        return 0;
    }
}

int TServo::S1_GoRelPos_AutoMode_Syn(float ARelPosMM, float ASpeedMMS, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        std::cerr << "S1_GoRelPos_AutoMode_Syn: Servo is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S1_GoRelPos_AutoMode_Syn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetPosition = FS1ActPosition + ARelPosMM;

    if(ASetPosition > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        std::cerr << "S1_GoRelPos_AutoMode_Syn: S1 Set positon is greater than the max value, and the target value used the max value instead" << std::endl;
    }
    else if(ASetPosition < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        std::cerr << "S1_GoRelPos_AutoMode_Syn: S1 Set positon is smaller than the min value, and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        std::cerr << "S1_GoRelPos_AutoMode_Syn: S1 Set positon is greater than the max value(" << FS1MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        std::cerr << "S1_GoRelPos_AutoMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionAuto = ASetPosition;
    FS1TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_GoRelPos_AutoMode_Syn: S1 auto mode write speed error" << std::endl;
        return -2;
    }

    FS1RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS1RunFinished && fabs(FS1TargetPositionAuto - FS1ActPosition) < PositionMaxTol) {
            std::cout << "S1_GoRelPos_AutoMode_Syn: S1 auto mode goto rel. position finished" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S1_GoRelPos_AutoMode_Syn: go rel. position timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S1_GoRelPos_MMode_Asyn(float ARelPosMM, float ASpeedMMS) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        std::cerr << "S1_GoRelPos_MMode_Asyn: Servo is not ready" << std::endl;
        return -1;
    }

    if(FS7IsAutoMode) {
        std::cerr << "S1_GoRelPos_MMode_Asyn: Servo is in auto mode, switch to manual first" << std::endl;
        return -1;
    }

    float ASetPosition = FS1ActPosition + ARelPosMM;

    if(ASetPosition > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        std::cerr << "S1_GoRelPos_MMode_Asyn: S1 Set positon is greater than the max value, and the target value used the max value instead" << std::endl;
    }
    else if(ASetPosition < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        std::cerr << "S1_GoRelPos_MMode_Asyn: S1 Set positon is smaller than the min value, and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        std::cerr << "S1_GoRelPos_MMode_Asyn: S1 Set positon is greater than the max value(" << FS1MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        std::cerr << "S1_GoRelPos_MMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionManual = ASetPosition;
    FS1TargetSpeedManual = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1MPosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_GoRelPos_MMode_Asyn: S1 manual mode write speed error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S1_GoRelPos_MMode_Asyn: S1 manual mode goto rel. position send out" << std::endl;
        return 0;
    }
}

int TServo::S1_GoRelPos_MMode_Syn(float ARelPosMM, float ASpeedMMS, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        std::cerr << "S1_GoRelPos_MMode_Syn: Servo is not ready" << std::endl;
        return -1;
    }

    if(FS7IsAutoMode) {
        std::cerr << "S1_GoRelPos_MMode_Syn: Servo is in auto mode, switch to manual first" << std::endl;
        return -1;
    }

    float ASetPosition = FS1ActPosition + ARelPosMM;

    if(ASetPosition > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        std::cerr << "S1_GoRelPos_MMode_Syn: S1 Set positon is greater than the max value, and the target value used the max value instead" << std::endl;
    }
    else if(ASetPosition < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        std::cerr << "S1_GoRelPos_MMode_Syn: S1 Set positon is smaller than the min value, and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        std::cerr << "S1_GoRelPos_MMode_Syn: S1 Set positon is greater than the max value(" << FS1MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        std::cerr << "S1_GoRelPos_MMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS1TargetPositionManual = ASetPosition;
    FS1TargetSpeedManual = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1MPosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S1_GoRelPos_MMode_Syn: S1 manual mode write speed error" << std::endl;
        return -2;
    }

    FS1RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS1RunFinished && fabs(FS1TargetPositionManual - FS1ActPosition) < PositionMaxTol) {
            std::cout << "S1_GoRelPos_MMode_Syn: S1 manual mode goto rel. position finished" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S1_GoRelPos_MMode_Syn: go rel. position timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S1_Run_On(int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS1IsServoOn) {
        std::cerr << "S1_Run_Syn: S1 need Servo On First" << std::endl;
        return -1;
    }

    FPedalIsSysMode = false;

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS1Start, &AWriteByte, false) != 0) {
        std::cerr << "S1_Run_Syn: S7 Write S1 start address error" << std::endl;
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(FS1IsReady)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S1_Run_Syn: Servo Start Timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S1_ServoON(bool AEnable, int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS7IsHandShaked) {
        std::cerr << "S1_ServoON: HandShake needed before Servo On" << std::endl;
        return -1;
    }

    if(!FS7IsPowerOn) {
        std::cerr << "S1_ServoON: Power is off" << std::endl;
        return -1;
    }

    if(AEnable) {
        AWriteByte |= 0x01;
    }

    if(S7Write(AddrSetS1ServoOn, &AWriteByte, false) != 0) {
        std::cerr << "S1_ServoON: S7 Write S1 servo on address error" << std::endl;
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(FS1IsServoOn == AEnable) {
            if(AEnable)
                std::cout << "S1_ServoON: Servo On Successful" << std::endl;
            else
                std::cout << "S1_ServoON: Servo Off Successful" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S1_ServoON: Servo On/Off Timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S1_SetZero(int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS1IsServoOn) {
        std::cerr << "S1_SetZero: S1 need Servo On First" << std::endl;
        return -1;
    }

    if(!FS1RunFinished) {
        std::cerr << "S1_SetZero: S1 is running, cannot set zero" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS1SetZero, &AWriteByte, false) != 0) {
        std::cerr << "S1_SetZero: S7 Write S1 set zero address error" << std::endl;
        return -2;
    }

    FS1ZeroExisted = false;

    int ATime = 0;
    while(true) {
        if(FS1ZeroExisted && FS1RunFinished)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S1_SetZero: Servo Set Zero Timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S2_GoAbsPos_AutoMode_Asyn(float AAbsPosDeg, float ASpeedDegS) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        std::cerr << "S2_GoAbsPos_AutoMode_Asyn: Servo 1 is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S2_GoAbsPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetPosition = AAbsPosDeg;
    if(AAbsPosDeg > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        std::cerr << "S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is greater than the max value(" << FS2MaxPosition << "), and the target value used the max value instead" << std::endl;
    }
    else if(AAbsPosDeg < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        std::cerr << "S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is smaller than the min value(" << FS2MinPosition << "), and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        std::cerr << "S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is greater than the max value(" << FS2MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        std::cerr << "S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS2TargetPositionAuto = ASetPosition;
    FS2TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position write error" << std::endl;
        ```cpp
            return -2;
    }
    else {
        std::cout << "S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position send out" << std::endl;
        return 0;
    }
}

int TServo::S2_GoAbsPos_AutoMode_Syn(float AAbsPosDeg, float ASpeedDegS, int ATimeout) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        std::cerr << "S2_GoAbsPos_AutoMode_Syn: Servo 2 is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S2_GoAbsPos_AutoMode_Syn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetPosition = AAbsPosDeg;
    if(AAbsPosDeg > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        std::cerr << "S2_GoAbsPos_AutoMode_Syn: S2 Set positon is greater than the max value(" << FS2MaxPosition << "), and the target value used the max value instead" << std::endl;
    }
    else if(AAbsPosDeg < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        std::cerr << "S2_GoAbsPos_AutoMode_Syn: S2 Set positon is smaller than the min value(" << FS2MinPosition << "), and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        std::cerr << "S2_GoAbsPos_AutoMode_Syn: S2 Set positon is greater than the max value(" << FS2MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        std::cerr << "S2_GoAbsPos_AutoMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS2TargetPositionAuto = ASetPosition;
    FS2TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S2_GoAbsPos_AutoMode_Syn: S2 auto mode goto abs. position write error" << std::endl;
        return -2;
    }

    FS2RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS2RunFinished && fabs(FS2TargetPositionAuto - FS2ActPosition) < PositionMaxTol) {
            std::cout << "S2_GoAbsPos_AutoMode_Syn: S2 auto mode goto abs. position finished" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S2_GoAbsPos_AutoMode_Syn: go abs position timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S2_GoAbsPos_MMode_Asyn(float AAbsPosDeg, float ASpeedDegS) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        std::cerr << "S2_GoAbsPostion_MMode_Asyn: Servo 2 is not ready" << std::endl;
        return -1;
    }

    if(FS7IsAutoMode) {
        std::cerr << "S2_GoAbsPostion_MMode_Asyn: Servo is in auto mode, switch to manual first" << std::endl;
        return -1;
    }

    float ASetPosition = AAbsPosDeg;
    if(AAbsPosDeg > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        std::cerr << "S2_GoAbsPostion_MMode_Asyn: S2 Set positon is greater than the max value(" << FS2MaxPosition << "), and the target value used the max value instead" << std::endl;
    }
    else if(AAbsPosDeg < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        std::cerr << "S2_GoAbsPostion_MMode_Asyn: S2 Set positon is smaller than the min value(" << FS2MinPosition << "), and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        std::cerr << "S2_GoAbsPostion_MMode_Asyn: S2 Set positon is greater than the max value(" << FS2MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        std::cerr << "S2_GoAbsPostion_MMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS2TargetPositionManual = ASetPosition;
    FS2TargetSpeedManual = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2MPosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S2_GoAbsPostion_MMode_Asyn: S2 manual mode goto abs. position write error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S2_GoAbsPostion_MMode_Asyn: S2 manual mode goto abs. position send out" << std::endl;
        return 0;
    }
}

int TServo::S2_GoAbsSlopGrad_AutoMode_Asyn(float AAbsGradPercent) {
    if(fabs(AAbsGradPercent) > 30) {
        std::cerr << "Max Slop is 30%, Current Setting is " << AAbsGradPercent << "%" << std::endl;
        return -1;
    }
    float ADegree = atan(AAbsGradPercent / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_AutoMode_Asyn(ADegree, FS2SlopSpeed);
}

int TServo::S2_GoAbsSlopGrad_AutoMode_Syn(float AAbsGradPercent, int ATimeout) {
    if(fabs(AAbsGradPercent) > 30) {
        std::cerr << "Max Slop is 30%, Current Setting is " << AAbsGradPercent << "%" << std::endl;
        return -1;
    }
    float ADegree = atan(AAbsGradPercent / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_AutoMode_Syn(ADegree, FS2SlopSpeed, ATimeout);
}

int TServo::S2_GoAbsSlopGrad_MMode_Asyn(float AAbsGradPercent) {
    if(fabs(AAbsGradPercent) > 30) {
        std::cerr << "Max Slop is 30%, Current Setting is " << AAbsGradPercent << "%" << std::endl;
        return -1;
    }

    float ADegree = atan(AAbsGradPercent / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_MMode_asyn(ADegree, FS2SlopSpeed);
}

int TServo::S2_GoAbsSlopGrad_MMode_Syn(float AAbsGradPercent, int ATimeout) {
    if(fabs(AAbsGradPercent) > 30) {
        std::cerr << "Max Slop is 30%, Current Setting is " << AAbsGradPercent << "%" << std::endl;
        return -1;
    }
    float ADegree = atan(AAbsGradPercent / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_MMode_syn(ADegree, FS2SlopSpeed, ATimeout);
}

int TServo::S2_GoMountPos_AutoMode_Asyn() {
    return S2_GoAbsPos_AutoMode_Asyn(FS2MountPosition, FS2SlopSpeed);
}

int TServo::S2_GoMountPos_AutoMode_Syn(int ATimeout) {
    return S2_GoAbsPos_AutoMode_Syn(FS2MountPosition, FS2SlopSpeed, ATimeout);
}

int TServo::S2_GoMountPos_MMode_Asyn() {
    return S2_GoAbsPos_MMode_Asyn(FS2MountPosition, FS2SlopSpeed);
}

int TServo::S2_GoMountPos_MMode_Syn(int ATimeout) {
    return S2_GoAbsPos_MMode_Syn(FS2MountPosition, FS2SlopSpeed, ATimeout);
}

int TServo::S2_GoAbsPos_MMode_Syn(float AAbsPosDeg, float ASpeedDegS, int ATimeout) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        std::cerr << "S2_GoAbsPostion_MMode_Syn: Servo 2 is not ready" << std::endl;
        return -1;
    }

    if(FS7IsAutoMode) {
        std::cerr << "S2_GoAbsPostion_MMode_Syn: Servo is in auto mode, switch to manual first" << std::endl;
        return -1;
    }

    float ASetPosition = AAbsPosDeg;
    if(AAbsPosDeg > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        std::cerr << "S2_GoAbsPostion_MMode_Syn: S2 Set positon is greater than the max value(" << FS2MaxPosition << "), and the target value used the max value instead" << std::endl;
    }
    else if(AAbsPosDeg < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        std::cerr << "S2_GoAbsPostion_MMode_Syn: S2 Set positon is smaller than the min value(" << FS2MinPosition << "), and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        std::cerr << "S2_GoAbsPostion_MMode_Syn: S2 Set positon is greater than the max value(" << FS2MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        std::cerr << "S2_GoAbsPostion_MMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS2TargetPositionManual = ASetPosition;
    FS2TargetSpeedManual = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2MPosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S2_GoAbsPostion_MMode_Syn: S2 manual mode goto abs. position write error" << std::endl;
        return -2;
    }

    FS2RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS2RunFinished && fabs(FS2TargetPositionManual - FS2ActPosition) < PositionMaxTol) {
            std::cout << "S2_GoAbsPostion_MMode_Syn: S2 manual mode goto abs. position finished" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S2_GoAbsPostion_MMode_Syn: go abs position timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S2_GoZero_Asyn() {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsReady) {
        std::cerr << "S2_GoZero_Asyn: S2 not ready" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS2GoZero, &AWriteByte, false) != 0) {
        std::cerr << "S2_GoZero_Asyn: S7 Write go zero error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S2_GoZero_Asyn: S2 go zero comand send out" << std::endl;
        return 0;
    }
}

int TServo::S2_GoZero_Syn(int ATimeout) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsReady) {
        std::cerr << "S2_GoZero_Syn: S2 not ready" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS2GoZero, &AWriteByte, false) != 0) {
        std::cerr << "S2_GoZero_Syn: S7 Write S2 go zero address error" << std::endl;
        return -2;
    }

    FS2RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS2RunFinished && fabs(FS2ActPosition) < PositionMaxTol)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S2_GoZero_Syn: Servo Go Zero Timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S2_Manual_JogIn() {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsReady) {
        std::cerr << "S2_Manual_JogIn: S2 is not ready" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS2JogB, &AWriteByte, false) != 0) {
        std::cerr << "S2_Manual_JogIn: S7 Write bit error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S2_Manual_JogIn: S2 Jog In" << std::endl;
        return 0;
    }
}

int TServo::S2_Manual_JogOut() {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsReady) {
        std::cerr << "S2_Manual_JogOut: S2 is not ready" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS2JogF, &AWriteByte, false) != 0) {
        std::cerr << "S2_Manual_JogOut: S7 Write bit error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S2_Manual_JogOut: S2 Jog Out" << std::endl;
        return 0;
    }
}

int TServo::S2_GoRelPos_AutoMode_Asyn(float ARelPosDeg, float ASpeedDegS) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        std::cerr << "S2_GoRelPos_AutoMode_Asyn: Servo is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S2_GoRelPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetPosition = FS2ActPosition + ARelPosDeg;

    if(ASetPosition > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        std::cerr << "S2_GoRelPos_AutoMode_Asyn: S2 Set positon is greater than the max value, and the target value used the max value instead" << std::endl;
    }
    else if(ASetPosition < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        std::cerr << "S2_GoRelPos_AutoMode_Asyn: S2 Set positon is smaller than the min value, and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        std::cerr << "S2_GoRelPos_AutoMode_Asyn: S2 Set positon is greater than the max value(" << FS2MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        std::cerr << "S2_GoRelPos_AutoMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS2TargetPositionAuto = ASetPosition;
    FS2TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S2_GoRelPos_AutoMode_Asyn: S2 auto mode write speed error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S2_GoRelPos_AutoMode_Asyn: S2 auto mode goto rel. position send out" << std::endl;
        return 0;
    }
}

int TServo::S2_GoRelPos_AutoMode_Syn(float ARelPosDeg, float ASpeedDegS, int ATimeout) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        std::cerr << "S2_GoRelPos_AutoMode_Syn: Servo is not ready" << std::endl;
        return -1;
    }

    if(!FS7IsAutoMode) {
        std::cerr << "S2_GoRelPos_AutoMode_Syn: Servo is in manual mode, switch to auto first" << std::endl;
        return -1;
    }

    float ASetPosition = FS2ActPosition + ARelPosDeg;

    if(ASetPosition > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        std::cerr << "S2_GoRelPos_AutoMode_Syn: S2 Set positon is greater than the max value, and the target value used the max value instead" << std::endl;
    }
    else if(ASetPosition < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        std::cerr << "S2_GoRelPos_AutoMode_Syn: S2 Set positon is smaller than the min value, and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        std::cerr << "S2_GoRelPos_AutoMode_Syn: S2 Set positon is greater than the max value(" << FS2MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        std::cerr << "S2_GoRelPos_AutoMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS2TargetPositionAuto = ASetPosition;
    FS2TargetSpeedAuto = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2APosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S2_GoRelPos_AutoMode_Syn: S2 auto mode write speed error" << std::endl;
        return -2;
    }

    FS2RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS2RunFinished && fabs(FS2TargetPositionAuto - FS2ActPosition) < PositionMaxTol) {
            std::cout << "S2_GoRelPos_AutoMode_Syn: S2 auto mode goto rel. position finished" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S2_GoRelPos_AutoMode_Syn: go rel. position timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S2_GoRelPos_MMode_Asyn(float ARelPosDeg, float ASpeedDegS) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        std::cerr << "S2_GoRelPos_MMode_Asyn: Servo is not ready" << std::endl;
        return -1;
    }

    if(FS7IsAutoMode) {
        std::cerr << "S2_GoRelPos_MMode_Asyn: Servo is in auto mode, switch to manual first" << std::endl;
        return -1;
    }

    float ASetPosition = FS2ActPosition + ARelPosDeg;

    if(ASetPosition > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        std::cerr << "S2_GoRelPos_MMode_Asyn: S2 Set positon is greater than the max value, and the target value used the max value instead" << std::endl;
    }
    else if(ASetPosition < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        std::cerr << "S2_GoRelPos_MMode_Asyn: S2 Set positon is smaller than the min value, and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        std::cerr << "S2_GoRelPos_MMode_Asyn: S2 Set positon is greater than the max value(" << FS2MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        std::cerr << "S2_GoRelPos_MMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS2TargetPositionManual = ASetPosition;
    FS2TargetSpeedManual = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2MPosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S2_GoRelPos_MMode_Asyn: S2 manual mode write speed error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S2_GoRelPos_MMode_Asyn: S2 manual mode goto rel. position send out" << std::endl;
        return 0;
    }
}

int TServo::S2_GoRelPos_MMode_Syn(float ARelPosDeg, float ASpeedDegS, int ATimeout) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        std::cerr << "S2_GoRelPos_MMode_Syn: Servo is not ready" << std::endl;
        return -1;
    }

    if(FS7IsAutoMode) {
        std::cerr << "S2_GoRelPos_MMode_Syn: Servo is in auto mode, switch to manual first" << std::endl;
        return -1;
    }

    float ASetPosition = FS2ActPosition + ARelPosDeg;

    if(ASetPosition > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        std::cerr << "S2_GoRelPos_MMode_Syn: S2 Set positon is greater than the max value, and the target value used the max value instead" << std::endl;
    }
    else if(ASetPosition < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        std::cerr << "S2_GoRelPos_MMode_Syn: S2 Set positon is smaller than the min value, and the target value used the min value instead" << std::endl;
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        std::cerr << "S2_GoRelPos_MMode_Syn: S2 Set positon is greater than the max value(" << FS2MaxSpeed << "), and the target value used the max value instead" << std::endl;
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        std::cerr << "S2_GoRelPos_MMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead" << std::endl;
    }

    FS2TargetPositionManual = ASetPosition;
    FS2TargetSpeedManual = ASetSpeed;

    *(float*) AWriteByte.data() = ASetPosition;
    *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2MPosSpd, AWriteByte.data(), false) != 0) {
        std::cerr << "S2_GoRelPos_MMode_Syn: S2 manual mode write speed error" << std::endl;
        return -2;
    }

    FS2RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS2RunFinished && fabs(FS2TargetPositionManual - FS2ActPosition) < PositionMaxTol) {
            std::cout << "S2_GoRelPos_MMode_Syn: S2 manual mode goto rel. position finished" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S2_GoRelPos_MMode_Syn: go rel. position timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S2_GoRelSlopGrad_AutoMode_Asyn(float ARelGradPercent) {
    float AGrad = FS2ActPositionGrad + ARelGradPercent;
    if(fabs(AGrad) > 30) {
        std::cerr << "Max Slop is 30%, Current Setting is " << AGrad << "%" << std::endl;
        return -1;
    }
    float ADegree = atan(AGrad / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_AutoMode_ASyn(ADegree, FS2SlopSpeed);
}

int TServo::S2_GoRelSlopGrad_AutoMode_Syn(float ARelGradPercent, int ATimeout) {
    float AGrad = FS2ActPositionGrad + ARelGradPercent;
    if(fabs(AGrad) > 30) {
        std::cerr << "Max Slop is 30%, Current Setting is " << AGrad << "%" << std::endl;
        return -1;
    }
    float ADegree = atan(AGrad / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_AutoMode_Syn(ADegree, FS2SlopSpeed, ATimeout);
}

int TServo::S2_GoRelSlopGrad_MMode_Asyn(float ARelGradPercent) {
    float AGrad = FS2ActPositionGrad + ARelGradPercent;
    if(fabs(AGrad) > 30) {
        std::cerr << "Max Slop is 30%, Current Setting is " << AGrad << "%" << std::endl;
        return -1;
    }
    float ADegree = atan(AGrad / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_MMode_Asyn(ADegree, FS2SlopSpeed);
}

```cpp
int TServo::S2_GoRelSlopGrad_MMode_Syn(float ARelGradPercent, int ATimeout) {
    float AGrad = FS2ActPositionGrad + ARelGradPercent;
    if(fabs(AGrad) > 30) {
        std::cerr << "Max Slop is 30%, Current Setting is " << AGrad << "%" << std::endl;
        return -1;
    }
    float ADegree = atan(AGrad / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_MMode_Syn(ADegree, FS2SlopSpeed, ATimeout);
}

int TServo::S2_Run_On(int ATimeout) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_Run_On: S2 is invalid" << std::endl;
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsServoOn) {
        std::cerr << "S2_Run_On: S2 need Servo On First" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS2Start, &AWriteByte, false) != 0) {
        std::cerr << "S2_Run_On: S7 Write S2 start address error" << std::endl;
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(FS2IsReady)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S2_Run_On: Servo Start Timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S2_ServoON(bool AEnable, int ATimeout) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_ServoON: S2 is invalid" << std::endl;
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS7IsHandShaked) {
        std::cerr << "S2_ServoON: HandShake needed before Servo On" << std::endl;
        return -1;
    }

    if(!FS7IsPowerOn) {
        std::cerr << "S2_ServoON: Power is off" << std::endl;
        return -1;
    }

    if(AEnable) {
        AWriteByte |= 0x01;
    }

    if(S7Write(AddrSetS2ServoOn, &AWriteByte, false) != 0) {
        std::cerr << "S2_ServoON: S7 Write S2 servo on address error" << std::endl;
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(FS2IsServoOn == AEnable) {
            if(AEnable)
                std::cout << "S2_ServoON: Servo On Successful" << std::endl;
            else
                std::cout << "S2_ServoON: Servo Off Successful" << std::endl;
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S2_ServoON: Servo On/Off Timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S2_SetZero(int ATimeout) {
    if(FS7IsOnlyPedal) {
        std::cerr << "S2_SetZero: S2 is invalid" << std::endl;
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsServoOn) {
        std::cerr << "S2_SetZero: S2 need Servo On First" << std::endl;
        return -1;
    }

    if(!FS2RunFinished) {
        std::cerr << "S2_SetZero: S2 is running, cannot set zero" << std::endl;
        return -1;
    }

    AWriteByte |= 0x01;

    if(S7Write(AddrSetS2SetZero, &AWriteByte, false) != 0) {
        std::cerr << "S2_SetZero: S7 Write S2 set zero address error" << std::endl;
        return -2;
    }

    FS2ZeroExisted = false;

    int ATime = 0;
    while(true) {
        if(FS2ZeroExisted && FS2RunFinished)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            std::cerr << "S2_SetZero: Servo Set Zero Timeout, timeout setting is " << ATimeout << "ms" << std::endl;
            return -3;
        }
    }
}

int TServo::S3_Go_In() {
    if(!FS7WithAirCylinder) {
        std::cerr << "S3_Go_In: Air Cylinder is invalid" << std::endl;
        return -10;
    }
    unsigned char AWriteByte = 0;
    AWriteByte |= 0x01;

    if(S7Write(AddrSetS3GoIn, &AWriteByte, false) != 0) {
        std::cerr << "S3_Go_In: S7 Write S3 go in address error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S3_Go_In: Air Cylinder Go In Successful" << std::endl;
        return 0;
    }
}

int TServo::S3_Go_Out() {
    if(!FS7WithAirCylinder) {
        std::cerr << "S3_Go_Out: Air Cylinder is invalid" << std::endl;
        return -10;
    }
    unsigned char AWriteByte = 0;
    AWriteByte |= 0x01;

    if(S7Write(AddrSetS3GoOut, &AWriteByte, false) != 0) {
        std::cerr << "S3_Go_Out: S7 Write S3 go out address error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S3_Go_Out: Air Cylinder Go Out Successful" << std::endl;
        return 0;
    }
}

int TServo::S3_Set_Target_Pressure(float ATargetPressureBar) {
    if(!FS7WithAirCylinder) {
        std::cerr << "S3_Set_Target_Pressure: Air Cylinder is invalid" << std::endl;
        return -10;
    }
    std::array<unsigned char, 4> AWriteByte = {0};
    if(ATargetPressureBar > FS3MCMaxPressure) {
        std::cerr << "S3_Set_Target_Pressure: Target Pressure is greater than the max pressure(" << FS3MCMaxPressure << " bar)" << std::endl;
        return -1;
    }

    float ASetPressure = (ATargetPressureBar - FS3P2AOffset) / FS3P2AFactor;
    *(float*) AWriteByte.data() = ASetPressure;

    if(S7Write(AddrSetS3TargetPressure, AWriteByte.data(), false) != 0) {
        std::cerr << "S3_Set_Target_Pressure: S7 Write S3 target pressure address error" << std::endl;
        return -2;
    }
    else {
        std::cout << "S3_Set_Target_Pressure: Set Target Pressure Successful" << std::endl;
        return 0;
    }
}

int TServo::S7Write(const TDataRecord& AField, void* pData, bool Async) {
    std::lock_guard<std::mutex> lock(FMonitorObj);
    if(Async)
        FS7LastError = FS7Client->AsWriteArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);
    else
        FS7LastError = FS7Client->WriteArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);

    if(FS7LastError == 0) {
        if(Async)
            S7WaitCompletion();
    }
    else {
        std::cerr << "S7Write: Servo Write Action Error" << std::endl;
    }
    return FS7LastError;
}

bool TServo::InitializeSnap7Api() {
    // Placeholder for Snap7 API initialization code
    // This should include loading the Snap7 library and initializing any necessary handles
    // Return true if initialization is successful, false otherwise
    return true;
}

void TServo::FinalizeSnap7Api() {
    // Placeholder for Snap7 API finalization code
    // This should include releasing any handles and unloading the Snap7 library
}

void TServo::S7WaitCompletion() {
    // Placeholder for waiting for the completion of asynchronous Snap7 operations
    // This should include checking the status of the operation and waiting until it completes
}

TServo::TThreadHeartbeat::TThreadHeartbeat() {
    // Placeholder for heartbeat thread constructor
    // This should include initializing any necessary variables and starting the heartbeat thread
}

TServo::TThreadHeartbeat::~TThreadHeartbeat() {
    // Placeholder for heartbeat thread destructor
    // This should include stopping the heartbeat thread and cleaning up any resources
}

void TServo::TThreadHeartbeat::HeartbeatSuspend() {
    // Placeholder for suspending the heartbeat thread
    // This should include pausing the heartbeat thread until it is resumed
}

void TServo::TThreadHeartbeat::Heartbeatexit() {
    // Placeholder for exiting the heartbeat thread
    // This should include gracefully terminating the heartbeat thread
}

TServo::TThreadGetData::TThreadGetData() {
    // Placeholder for data retrieval thread constructor
    // This should include initializing any necessary variables and starting the data retrieval thread
}

TServo::TThreadGetData::~TThreadGetData() {
    // Placeholder for data retrieval thread destructor
    // This should include stopping the data retrieval thread and cleaning up any resources
}

void TServo::TThreadGetData::GetDataexit() {
    // Placeholder for exiting the data retrieval thread
    // This should include gracefully terminating the data retrieval thread
}

// Additional helper functions and classes can be defined here as needed
