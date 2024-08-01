#include "uPLC1200.h"
#include "TSMaster.h"
#include "common.h"
#include <windows.h>
TServo* vServoObj = nullptr;
TThreadHeartbeat* vHeartbeatThread = nullptr;
TThreadGetData* vGetDataThread = nullptr;

const TDataRecord AddrSetHandShake = {S7AreaDB, 50, 0, 1, S7WLBit};
const TDataRecord AddrSetS1ServoOn = {S7AreaDB, 50, 1, 1, S7WLBit};
const TDataRecord AddrSetS1Start = {S7AreaDB, 50, 2, 1, S7WLBit};
const TDataRecord AddrSetS1Stop = {S7AreaDB, 50, 3, 1, S7WLBit};
const TDataRecord AddrSetS1JogF = {S7AreaDB, 50, 4, 1, S7WLBit};
const TDataRecord AddrSetS1JogB = {S7AreaDB, 50, 5, 1, S7WLBit};
const TDataRecord AddrSetS1GoZero = {S7AreaDB, 50, 6, 1, S7WLBit};
const TDataRecord AddrSetS1SetZero = {S7AreaDB, 50, 7, 1, S7WLBit};
const TDataRecord AddrSetS2ServoOn = {S7AreaDB, 50, 8, 1, S7WLBit};
const TDataRecord AddrSetS2Start = {S7AreaDB, 50, 9, 1, S7WLBit};
const TDataRecord AddrSetS2Stop = {S7AreaDB, 50, 10, 1, S7WLBit};
const TDataRecord AddrSetS2JogF = {S7AreaDB, 50, 11, 1, S7WLBit};
const TDataRecord AddrSetS2JogB = {S7AreaDB, 50, 12, 1, S7WLBit};
const TDataRecord AddrSetS2GoZero = {S7AreaDB, 50, 13, 1, S7WLBit};
const TDataRecord AddrSetS2SetZero = {S7AreaDB, 50, 14, 1, S7WLBit};
const TDataRecord AddrSetS7Reset = {S7AreaDB, 50, 15, 1, S7WLBit};
const TDataRecord AddrSetS1APos = {S7AreaDB, 50, 2, 1, S7WLReal};
const TDataRecord AddrSetS1ASpd = {S7AreaDB, 50, 6, 1, S7WLReal};
const TDataRecord AddrSetS1APosSpd = {S7AreaDB, 50, 2, 2, S7WLReal};
const TDataRecord AddrSetS1MPos = {S7AreaDB, 50, 10, 1, S7WLReal};
const TDataRecord AddrSetS1MSpd = {S7AreaDB, 50, 14, 1, S7WLReal};
const TDataRecord AddrSetS1MPosSpd = {S7AreaDB, 50, 10, 2, S7WLReal};
const TDataRecord AddrSetS2APos = {S7AreaDB, 50, 18, 1, S7WLReal};
const TDataRecord AddrSetS2ASpd = {S7AreaDB, 50, 22, 1, S7WLReal};
const TDataRecord AddrSetS2APosSpd = {S7AreaDB, 50, 18, 2, S7WLReal};
const TDataRecord AddrSetS2MPos = {S7AreaDB, 50, 26, 1, S7WLReal};
const TDataRecord AddrSetS2MSpd = {S7AreaDB, 50, 30, 1, S7WLReal};
const TDataRecord AddrSetS2MPosSpd = {S7AreaDB, 50, 26, 2, S7WLReal};
const TDataRecord AddrGetS7IsHandShake = {S7AreaDB, 51, 0, 1, S7WLBit};
const TDataRecord AddrGetS7IsPowerOn = {S7AreaDB, 51, 1, 1, S7WLBit};
const TDataRecord AddrGetS7IsAutoMode = {S7AreaDB, 51, 2, 1, S7WLBit};
const TDataRecord AddrGetS7IsFault = {S7AreaDB, 51, 3, 1, S7WLBit};
const TDataRecord AddrGetS1IsServoOn = {S7AreaDB, 51, 4, 1, S7WLBit};
const TDataRecord AddrGetS1ZeroExisted = {S7AreaDB, 51, 5, 1, S7WLBit};
const TDataRecord AddrGetS1IsReady = {S7AreaDB, 51, 6, 1, S7WLBit};
const TDataRecord AddrGetS1RunFinished = {S7AreaDB, 51, 7, 1, S7WLBit};
const TDataRecord AddrGetS1IsFault = {S7AreaDB, 51, 8, 1, S7WLBit};
const TDataRecord AddrGetS2IsServoOn = {S7AreaDB, 51, 9, 1, S7WLBit};
const TDataRecord AddrGetS2ZeroExisted = {S7AreaDB, 51, 10, 1, S7WLBit};
const TDataRecord AddrGetS2IsReady = {S7AreaDB, 51, 11, 1, S7WLBit};
const TDataRecord AddrGetS2RunFinished = {S7AreaDB, 51, 12, 1, S7WLBit};
const TDataRecord AddrGetS2IsFault = {S7AreaDB, 51, 13, 1, S7WLBit};
const TDataRecord AddrGetS1ActPosition = {S7AreaDB, 51, 2, 1, S7WLReal};
const TDataRecord AddrGetS1ActSpeed = {S7AreaDB, 51, 6, 1, S7WLReal};
const TDataRecord AddrGetS2ActPosition = {S7AreaDB, 51, 10, 1, S7WLReal};
const TDataRecord AddrGetS2ActSpeed = {S7AreaDB, 51, 14, 1, S7WLReal};
const TDataRecord AddrGetAllData = {S7AreaDB, 51, 0, 18, S7WLByte};
const TDataRecord AddrSetS3GoOut = {S7AreaDB, 50, 11, 1, S7WLBit};
const TDataRecord AddrSetS3GoIn = {S7AreaDB, 50, 12, 1, S7WLBit};
const TDataRecord AddrSetS3Current = {S7AreaDB, 50, 18, 1, S7WLReal};


void ProcessMessages() {
    MSG msg;
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
/* class TS7Helper */
bool TS7Helper::GetBit(void* pval, int BitIndex) {
    static const uint8_t Mask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
    if(BitIndex < 0) BitIndex = 0;
    if(BitIndex > 7) BitIndex = 7;
    return (*static_cast<uint8_t*>(pval) & Mask[BitIndex]) != 0;
}

std::tm TS7Helper::GetDateTime(void* pval) {
    struct S7DT {
        uint8_t data[8];
    };
    S7DT* buffer = static_cast<S7DT*>(pval);
    uint16_t YY, MM, DD, HH, NN, SS, MS;
    int C, D, U;

    auto BCD = [](uint8_t B) -> uint16_t {
        return (B & 0x0F) + ((B >> 4) * 10);
        };

    YY = buffer->data[0];
    if(YY > 137) // 137 dec = 89 BCD
        YY = 1900 + BCD(YY);
    else
        YY = 2000 + BCD(YY);

    MM = BCD(buffer->data[1]);
    DD = BCD(buffer->data[2]);
    HH = BCD(buffer->data[3]);
    NN = BCD(buffer->data[4]);
    SS = BCD(buffer->data[5]);

    // Millisec
    MS = buffer->data[6];
    MS = (MS << 8) + buffer->data[7];
    // Last 4 bit are Day of Week
    MS = MS >> 4;

    // Hex to Int
    C = ((MS & 0x0F00) >> 8) * 100;
    D = ((MS & 0x00F0) >> 4) * 10;
    U = (MS & 0x000F);

    MS = C + D + U;

    std::tm result = {};
    result.tm_year = YY - 1900;
    result.tm_mon = MM - 1;
    result.tm_mday = DD;
    result.tm_hour = HH;
    result.tm_min = NN;
    result.tm_sec = SS;
    // result.tm_isdst = -1; // Not set in Delphi code
    return result;
}

int32_t TS7Helper::GetDInt(void* pval) {
    int32_t result;
    uint8_t* DW = reinterpret_cast<uint8_t*>(&result);
    DW[0] = *static_cast<uint8_t*>(pval);
    DW[1] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1);
    DW[2] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 2);
    DW[3] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 3);
    return result;
}

uint32_t TS7Helper::GetDWord(void* pval) {
    uint32_t result;
    uint8_t* DW = reinterpret_cast<uint8_t*>(&result);
    DW[0] = *static_cast<uint8_t*>(pval);
    DW[1] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1);
    DW[2] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 2);
    DW[3] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 3);
    return result;
}

int16_t TS7Helper::GetInt(void* pval) {
    int16_t result;
    uint8_t* BW = reinterpret_cast<uint8_t*>(&result);
    BW[0] = *static_cast<uint8_t*>(pval);
    BW[1] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1);
    return result;
}

float TS7Helper::GetReal(void* pval) {
    float result;
    uint8_t* DW = reinterpret_cast<uint8_t*>(&result);
    DW[0] = *static_cast<uint8_t*>(pval);
    DW[1] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1);
    DW[2] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 2);
    DW[3] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 3);
    return result;
}

uint16_t TS7Helper::GetWord(void* pval) {
    uint16_t result;
    uint8_t* BW = reinterpret_cast<uint8_t*>(&result);
    BW[0] = *static_cast<uint8_t*>(pval);
    BW[1] = *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1);
    return result;
}

void TS7Helper::Reverse(void* pval, int S7Type) {
    std::tm DT;
    switch(S7Type) {
    case 0: // S7Int
    case 1: // S7Word
        SetWord(pval, *static_cast<uint16_t*>(pval));
        break;
    case 2: // S7DInt
    case 3: // S7DWord
    case 4: // S7Real
        SetDWord(pval, *static_cast<uint32_t*>(pval));
        break;
    case 5: // S7DT_To_DateTime
        *static_cast<std::tm*>(pval) = GetDateTime(pval);
        break;
    case 6: // DateTime_To_S7DT
        DT = *static_cast<std::tm*>(pval);
        SetDateTime(pval, DT);
        break;
    }
}

void TS7Helper::SetBit(void* pval, int BitIndex, bool value) {
    static const uint8_t Mask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
    if(BitIndex < 0) BitIndex = 0;
    if(BitIndex > 7) BitIndex = 7;
    if(value)
        *static_cast<uint8_t*>(pval) |= Mask[BitIndex];
    else
        *static_cast<uint8_t*>(pval) &= ~Mask[BitIndex];
}

void TS7Helper::SetDateTime(void* pval, const std::tm& value) {
    struct DATE_AND_TIME {
        uint8_t data[8];
    };
    DATE_AND_TIME* DT = static_cast<DATE_AND_TIME*>(pval);
    uint16_t MsDOW, AYear, AMonth, ADay, AHour, AMinute, ASecond, AMilliSecond;

    auto BCD = [](uint16_t Value) -> uint8_t {
        return ((Value / 10) << 4) | (Value % 10);
        };

    auto BCDW = [](uint16_t Value) -> uint16_t {
        uint16_t AppC = (Value / 100);
        Value -= AppC * 100;
        uint16_t AppD = (Value / 10);
        Value -= AppD * 10;
        return (AppC << 8) + (AppD << 4) + Value;
        };

    AYear = value.tm_year + 1900;
    AMonth = value.tm_mon + 1;
    ADay = value.tm_mday;
    AHour = value.tm_hour;
    AMinute = value.tm_min;
    ASecond = value.tm_sec;
    AMilliSecond = 0; // Not available in std::tm

    if(AYear > 1999)
        AYear -= 2000;
    else
        AYear -= 1900;

    DT->data[0] = BCD(AYear);
    DT->data[1] = BCD(AMonth);
    DT->data[2] = BCD(ADay);
    DT->data[3] = BCD(AHour);
    DT->data[4] = BCD(AMinute);
    DT->data[5] = BCD(ASecond);
    MsDOW = (BCDW(AMilliSecond) << 4) + value.tm_wday + 1;
    DT->data[6] = (MsDOW >> 8) & 0xFF;
    DT->data[7] = MsDOW & 0xFF;
}

void TS7Helper::SetDInt(void* pval, int32_t value) {
    uint8_t* DW = reinterpret_cast<uint8_t*>(&value);
    *static_cast<uint8_t*>(pval) = DW[3];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1) = DW[2];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 2) = DW[1];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 3) = DW[0];
}

void TS7Helper::SetDWord(void* pval, uint32_t value) {
    uint8_t* DW = reinterpret_cast<uint8_t*>(&value);
    *static_cast<uint8_t*>(pval) = DW[3];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1) = DW[2];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 2) = DW[1];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 3) = DW[0];
}

void TS7Helper::SetInt(void* pval, int16_t value) {
    uint8_t* BW = reinterpret_cast<uint8_t*>(&value);
    *static_cast<uint8_t*>(pval) = BW[1];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1) = BW[0];
}

void TS7Helper::SetReal(void* pval, float value) {
    uint8_t* DW = reinterpret_cast<uint8_t*>(&value);
    *static_cast<uint8_t*>(pval) = DW[3];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1) = DW[2];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 2) = DW[1];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 3) = DW[0];
}

void TS7Helper::SetWord(void* pval, uint16_t value) {
    uint8_t* BW = reinterpret_cast<uint8_t*>(&value);
    *static_cast<uint8_t*>(pval) = BW[1];
    *static_cast<uint8_t*>(static_cast<uint8_t*>(pval) + 1) = BW[0];
}

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
        log("HeartbeatResume: Heartbeat thread resumed.");
    }
    else {
        log("HeartbeatResume: Heartbeat thread not suspended.");
    }
}

void TThreadHeartbeat::HeartbeatSuspend() {
    std::unique_lock<std::mutex> lock(mutex);
    if(suspended) {
        log("HeartbeatSuspend: Heartbeat thread already suspended.");
    }
    else {
        suspended = true;
        log("HeartbeatSuspend: Heartbeat thread suspended.");
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
            log_nok("Heartbeatexit: wait Heartbeat thread exit timeout.");
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
                log_nok("TThreadHeartbeat Execute: Heartbeat thread persistent error, Suspended self, Handshake again to restart");
                HeartbeatSuspend();
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    log("TThreadHeartbeat Execute: Heartbeat thread exit.");
    finished = true;
}

int TThreadHeartbeat::S7_Heartbeat() {
    if(vServoObj == nullptr) {
        log_nok("S7_Heartbeat: vServoObj is not exist");
        return -1;
    }

    if(!vServoObj->FS7IsConnected) {
        log_nok("S7_Heartbeat: servo not connected");
        return -1;
    }

    unsigned char AWriteByte = 1;
    if(vServoObj->S7Write(AddrSetHandShake, &AWriteByte, false) != 0) {
        log_nok("S7_Heartbeat: S7 Write heartbeat address error.");
        return -2;
    }

    return 0;
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
        log("GetDataResume: Getdata thread resumed");
    }
    else {
        log("GetDataResume: Getdata thread not suspended");
    }
}

void TThreadGetData::GetDataSuspend() {
    std::unique_lock<std::mutex> lock(mutex);
    if(suspended) {
        log("GetDataSuspend: Getdata thread already suspended");
    }
    else {
        suspended = true;
        log("GetDataSuspend: Getdata thread suspended");
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
            log_nok("GetDataexit: Error: wait getdata thread exit timeout");
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
                log_nok("TThreadGetData Execute: Getdata thread persistent error, suspended self, connected again to restart");
                GetDataSuspend();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    log("TThreadGetData Execute: Getdata thread exit.");
    finished = true;
}

int TThreadGetData::S7_GetData() {
    if(vServoObj == nullptr) {
        log_nok("S7_GetData: Error: vServoObj is not exist");
        return -1;
    }
    return vServoObj->S7_GetAllData();
}



/* export function */
int servo_check() {
    if(vServoObj == nullptr) {
        log_nok("Created servo object failed");
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
        log_nok("Servo DLL Load Failed");
        return -3;
    }
    return 0;
}

int servo_destroy() {
    if(vServoObj == nullptr) {
        log("no servo object existed");
        return 0;
    }
    else {
        delete vServoObj;
        vServoObj = nullptr;
        log("Servo object destroyed");
        return 0;
    }
}

int servo_connect(const char* AIPAddr) {
    vServoObj->FRemoteAddress = AIPAddr;

    int result = servo_check();
    if(result != 0)
        return result;

    if(vServoObj->S7_Connection() != 0) {
        log_nok("can not connect with servo system, check IP Address");
        return -3;
    }
    if(vServoObj->S7_HandsShake(true, 10000) != 0) {
        log_nok("handshake with servo system failed");
        return -4;
    }

    log_ok("MP API: Servo connected successfully");
    return 0;
}

int servo_disconnect() {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FS7IsConnected) {
        result = vServoObj->S7_Disconnection();
        if(result != 0)
            log("disconnect succeffully failed");
        else
            log("disconnect succeffully");
        return result;
    }
    else {
        log("no connection with servo system");
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
        log_nok("Servo control mode is manual mode, switch the mode on the door first");
        return -3;
    }

    if(AEnable) {
        if(vServoObj->S1_ServoON(true, 5000) != 0) {
            log_nok("Pedal Servo On Failed");
            return -4;
        }
    }
    else {
        if(vServoObj->S1_ServoON(false, 5000) != 0) {
            log_nok("Pedal Servo On Failed");
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
        log_nok("Servo control mode is manual mode, switch the mode on the door first");
        return -3;
    }

    if(AEnable) {
        if(vServoObj->S1_Run_On() != 0) {
            log_nok("Pedal Servo Enable Run Failed");
            return -4;
        }
    }
    else {
        if(vServoObj->S1_Run_Off() != 0) {
            log_nok("Pedal Servo Disable Run Failed");
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
        log_nok("pedal_go_step_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("pedal_go_step_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("pedal_go_position_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("pedal_go_position_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("pedal_sys_position_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent is not actived, using pedal_position_auto_mode(true) to enable first");
        return -20;
    }
}

int pedal_go_step_percent_syn(float ARelPositionPercent, float ASpeedMMpS, int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;

    float AStepMM = ARelPositionPercent * vServoObj->FS1MaxPosition / 100;
    if(vServoObj->FPedalIsSysMode) {
        log_nok("pedal_go_step_percent_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("pedal_go_step_percent_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("pedal_go_position_percent_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("pedal_go_position_percent_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("pedal_sys_position_percent_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent is not actived, using pedal_position_auto_mode(true) to enable first");
        return -20;
    }
}

int pedal_go_home_syn(int ATimeout) {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FPedalIsSysMode) {
        log_nok("pedal_go_home_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("pedal_go_home_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first");
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
        log_nok("Servo control mode is manual mode, switch the mode on the door first");
        return -3;
    }

    if(AEnable) {
        if(vServoObj->S2_ServoON(true, 5000) != 0) {
            log_nok("slope Servo On Failed");
            return -4;
        }
    }
    else {
        if(vServoObj->S2_ServoON(false, 5000) != 0) {
            log_nok("slope Servo On Failed");
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
        log_nok("Servo control mode is manual mode, switch the mode on the door first");
        return -3;
    }

    if(AEnable) {
        if(vServoObj->S2_Run_On() != 0) {
            log_nok("slope Servo Enable Run Failed");
            return -4;
        }
    }
    else {
        if(vServoObj->S2_Run_Off() != 0) {
            log_nok("slope Servo Disable Run Failed");
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
    return vServoObj->S2_GoMountPos_AutoMode_Asyn();
}

int rotate_set_slope_speed(float ASpeedDpS) {
    int result = servo_check();
    if(result != 0)
        return result;
    if((ASpeedDpS < 0) || (ASpeedDpS > 10)) {
        log_nok("The rotate servo slope run speed need in range [0,10], current setting is %f deg/s", ASpeedDpS);
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
        log_nok("Servo DLL Load Failed");
        return -1;
    }

    if(vServoObj->S7_Connection() != 0) {
        log_nok("can not connect with servo system");
        return -2;
    }

    if(vServoObj->S7_HandsShake(true, 10000) != 0) {
        log_nok("handshake with servo system failed");
        return -3;
    }

    if(vServoObj->S1_ServoON(true, 5000) != 0) {
        log_nok("servo on failed");
        return -4;
    }

    if(vServoObj->S1_Run_On() != 0) {
        log_nok("servo on failed");
        return -5;
    }
    log_ok("enable turntable successfully");
    return 0;
}

int turntable_disable_control() {
    int result = servo_check();
    if(result != 0)
        return result;
    if(vServoObj->FS7IsConnected) {
        if(vServoObj->FS7IsFault) {
            if(vServoObj->S7_ClearFault() != 0)
                log_nok("Servo has fault and cannot be cleared");
        }

        if(vServoObj->FS1IsServoOn) {
            if(vServoObj->S1_RunSpd_AutoMode_Syn(0, 2000) != 0)
                log_nok("set speed zero failed");

            if(vServoObj->S1_ServoON(false, 5000) != 0)
                log_nok("servo off failed");
        }
        if(vServoObj->S7_Disconnection() != 0)
            log_nok("disconnection wit servo failed");
    }
    if(vServoObj != nullptr) {
        delete vServoObj;
        vServoObj = nullptr;
    }
    log_ok("disable turntable successfully");
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
        log_nok("the arm lengthen should in rang [90, 160]mm");
        return -10;
    }
    if(ATargetAccelerationG < 0) {
        log_nok("the set g should greater than zero");
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
        log_nok("the arm lengthen should in rang [90, 160]mm");
        return -10;
    }
    if(ATargetAccelerationG < 0) {
        log_nok("the set g should greater than zero");
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
/* class TServo */
TServo::TServo(bool AOnlyPedalServo)
    : FS7IsOnlyPedal(AOnlyPedalServo), FSnap7IsLoaded(false), FS7IsConnected(false), FS7IsHandShaked(false), FS7IsPowerOn(false), FS7IsAutoMode(false), FS7IsFault(false), FS7WithAirCylinder(false), FS1IsServoOn(false), FS1ZeroExisted(false), FS1IsReady(false), FS1RunFinished(false), FS1IsFault(false), FS2IsServoOn(false), FS2ZeroExisted(false), FS2IsReady(false), FS2RunFinished(false), FS2IsFault(false), FS1ActPosition(0.0f), FS1ActSpeed(0.0f), FS2ActPosition(0.0f), FS2ActPositionGrad(0.0f), FS2ActSpeed(0.0f), FS1MaxSpeed(500.0f), FS1MaxPosition(60.0f), FS1MinPosition(-10.0f), FS2MaxSpeed(10.0f), FS2MaxPosition(20.0f), FS2MinPosition(-20.0f), FS2MountPosition(0.0f), FS2SlopSpeed(0.0f), FS3TargetCurrent(0.0f), FS1TargetPositionManual(0.0f), FS1TargetSpeedManual(0.0f), FS2TargetPositionManual(0.0f), FS2TargetSpeedManual(0.0f), FS1TargetPositionAuto(0.0f), FS1TargetSpeedAuto(0.0f), FS2TargetPositionAuto(0.0f), FS2TargetSpeedAuto(0.0f), FPedalIsSysMode(false), FS3MCMaxPressure(0.0f), FS3P2AFactor(0.0f), FS3P2AOffset(0.0f) {
    // if(InitializeSnap7Api()) {
    //     log_ok("Load Snap7 successful");
    //     FSnap7IsLoaded = true;
    // }
    // else {
    //     log_nok("Load Snap7 failed");
    //     FSnap7IsLoaded = false;
    // }
    RegisterSystemVars();

    //FS7Client = new TS7Client();
    //S7 = new TS7Helper();
    FS7IsConnected = false;
    FS7IsHandShaked = false;

    // FMonitorObj: = TObject.Create;
    vHeartbeatThread = new TThreadHeartbeat();
    log("TServo.Create: Servo Object is created");
    FS1MaxSpeed = 500.0f;
    FS1MaxPosition = 60.0f;
    FS1MinPosition = -10.0f;
    FS2MaxSpeed = 10.0f;
    FS2MaxPosition = 20.0f;
    FS2MinPosition = -20.0f;
    FS2SlopSpeed = 0.0f;
    FS2MountPosition = 0.0f;
    // todo: vTIOConfig
    // FS2MountPosition: = vTIOConfig.FServo2MountAngle;
    FRemoteAddress = "192.168.1.1";
    FPedalIsSysMode = false;
    // todo:vTIOConfig
    // S3MCMaxPressure: = vTIOConfig.FMCMaxPressure;
    // S3P2AFactor: = vTIOConfig.FPressure2CurrentFactor;
    // S3P2AOffset: = vTIOConfig.FPressure2CurrentOffset;
    FS3MCMaxPressure = 0.0f;
    FS3P2AFactor = 0.0f;
    FS3P2AOffset = 0.0f;

    // vGetDataThread = new TThreadGetData();
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

    //if(S7 != nullptr) {
    //    delete S7;
    //    S7 = nullptr;
    //}

    //if(FS7Client != nullptr) {
    //    delete FS7Client;
    //    FS7Client = nullptr;
    //}

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

    // FinalizeSnap7Api();
}

void TServo::RegisterSystemVars() {
    // todo: need set property or not
    app.create_system_var("tio.PedalSpeed", svtDouble, 0, "Servo Pedal Speed");
    app.create_system_var("tio.PedalPosition", svtDouble, 0, "Servo Pedal Position");
    app.create_system_var("tio.RotateDegree", svtDouble, 0, "Servo Slope Rotate Degree");
    app.create_system_var("tio.SlopeGrad", svtDouble, 0, "Servo Slope Gradient");
}

void TServo::UnregisterSystemVars() {
    app.delete_system_var("PedalSpeed");
    app.delete_system_var("PedalPosition");
    app.delete_system_var("RotateDegree");
    app.delete_system_var("SlopeGrad");
}

int TServo::S7_ClearFault(int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS7IsHandShaked) {
        log_nok("S7_ClearFault: HandShake needed before Servo On");
        return -1;
    }
    if(!FS7IsPowerOn) {
        log_nok("S7_ClearFault: Power is off");
        return -1;
    }
    S7.ValBit(&AWriteByte, 0, true);
    // AWriteByte |= 0x01;

    if(S7Write(AddrSetS7Reset, &AWriteByte, false) != 0) {
        log_nok("S7_ClearFault: S7 Write servo reset address error");
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(!FS1IsFault) {
            log_ok("S7_ClearFault: clear fault Successful");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S7_ClearFault: Clear fault timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S7_Connection() {
    int PingTime = 0;
    FS7LastError = FS7Client.SetParam(p_i32_PingTimeout, &PingTime);
    if(FS7LastError != 0) {
        return -1;
    }

    FS7Client.SetConnectionType(1);
    FS7LastError = FS7Client.ConnectTo(FRemoteAddress.c_str(), 0, 0);
    Sleep(50);
    if(FS7LastError != 0) {
        log_nok("S7_Connection: Servo Connect error, can not find device under IP: ");
        FS7IsConnected = false;
    }
    else {
        log_ok("S7_Connection: Servo Connect Successful, device IP is: ");
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
    FS7LastError = FS7Client.Disconnect();
    if(FS7LastError != 0) {
        log_nok("S7_Disconnection: Servo disconnect error");
    }
    else {
        log_ok("S7_Disconnection: Servo disconnect Successful. Device IP is:");
    }

    FS7IsConnected = false;
    return FS7LastError;
}

int TServo::S7_GetAllData() {
    if(!FS7IsConnected) {
        log_nok("S7_GetAllData: Connected is needed");
        return -1;
    }

    if(S7Read(AddrGetAllData, &FS7Buffer, false) == 0) {

        FS7IsHandShaked = S7.ValBit(&FS7Buffer[0], 0);
        FS7IsPowerOn = S7.ValBit(&FS7Buffer[0], 1);
        FS7IsAutoMode = S7.ValBit(&FS7Buffer[0], 2);
        FS7IsFault = S7.ValBit(&FS7Buffer[0], 3);
        FS1IsServoOn = S7.ValBit(&FS7Buffer[0], 4);
        FS1ZeroExisted = S7.ValBit(&FS7Buffer[0], 5);
        FS1IsReady = S7.ValBit(&FS7Buffer[0], 6);
        // FS1Running = S7.ValBit(&FS7Buffer[2], 6);
        FS1RunFinished = S7.ValBit(&FS7Buffer[0], 7);
        FS1IsFault = S7.ValBit(&FS7Buffer[1], 0);
        // todo check the address
        // FS1AutoMode = S7.ValBit(&FS7Buffer[3], 7);
        // FS2AutoMode = S7.ValBit(&FS7Buffer[3], 8);

        FS1ActPosition = S7.ValReal(&FS7Buffer[2]);
        FS1ActSpeed = S7.ValReal(&FS7Buffer[6]);
        if(!FS7IsOnlyPedal) {
            FS2IsServoOn = S7.ValBit(&FS7Buffer[1], 1);
            FS2ZeroExisted = S7.ValBit(&FS7Buffer[1], 2);
            FS2IsReady = S7.ValBit(&FS7Buffer[1], 3);
            // FS2Running = S7.ValBit(&FS7Buffer[3], 4);
            FS2RunFinished = S7.ValBit(&FS7Buffer[1], 4);
            FS2IsFault = S7.ValBit(&FS7Buffer[1], 5);
            FS2ActPosition = S7.ValReal(&FS7Buffer[10]);
            FS2ActSpeed = S7.ValReal(&FS7Buffer[14]);
        }
        // FS7IsHandShaked = (FS7Buffer[0] & 0x01) != 0;
        // FS7IsPowerOn = (FS7Buffer[0] & 0x02) != 0;
        // FS7IsAutoMode = (FS7Buffer[0] & 0x04) != 0;
        // FS7IsFault = (FS7Buffer[0] & 0x08) != 0;
        // FS1IsServoOn = (FS7Buffer[0] & 0x10) != 0;
        // FS1ZeroExisted = (FS7Buffer[0] & 0x20) != 0;
        // FS1IsReady = (FS7Buffer[0] & 0x40) != 0;
        // FS1RunFinished = (FS7Buffer[0] & 0x80) != 0;
        // FS1IsFault = (FS7Buffer[1] & 0x01) != 0;
        // FS2IsServoOn = (FS7Buffer[1] & 0x02) != 0;
        // FS2ZeroExisted = (FS7Buffer[1] & 0x04) != 0;
        // FS2IsReady = (FS7Buffer[1] & 0x08) != 0;
        // FS2RunFinished = (FS7Buffer[1] & 0x10) != 0;
        // FS2IsFault = (FS7Buffer[1] & 0x20) != 0;
        // FS1ActPosition = *(float*) (FS7Buffer + 2);
        // FS1ActSpeed = *(float*) (FS7Buffer + 6);
        // FS2ActPosition = *(float*) (FS7Buffer + 10);
        // FS2ActSpeed = *(float*) (FS7Buffer + 14);
        return 0;
    }
    else {
        return -1;
    }
}

int TServo::S7_HandsShake(bool AEnable, int ATimeout) {
    unsigned char AWriteByte = 0;

    if(!FS7IsConnected) {
        log_nok("S7_HandsShake: servo not connected");
        return -1;
    }

    if(AEnable) {
        S7.ValBit(&AWriteByte, 0, AEnable);
        // AWriteByte |= 0x01;
    }

    if(S7Write(AddrSetHandShake, &AWriteByte, false) != 0) {
        log_nok("S7_HandsShake: S7 Write Handshake address error");
        return -2;
    }

    int ATime = 0;

    if(AEnable) {
        while(true) {
            if(FS7IsHandShaked) {
                log_ok("S7_HandsShake: Servo Handshake Set Success");
                return 0;
            }

            Sleep(1);
            ATime++;
            if(ATime > ATimeout) {
                log_nok("S7_HandsShake: Servo Handshake is Timeout, timeout setting is %d ms", ATimeout);
                return -3;
            }
        }
    }
    else {
        vHeartbeatThread->HeartbeatSuspend();
        log_ok("S7_HandsShake: Servo Handshake Reset Success");
        return 0;
    }
}

// todo: 原始代码中设置了最长互锁时长
int TServo::S7Read(const TDataRecord& AField, void* pData, bool Async) {
    std::lock_guard<std::mutex> lock(FMonitorObj);
    if(Async)
        FS7LastError = FS7Client.AsReadArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);
    else
        FS7LastError = FS7Client.ReadArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);

    if(FS7LastError == 0) {
        if(Async)
            S7WaitCompletion();
    }
    else {
        log_nok("S7Read: Servo Read Action Error");
    }
    return FS7LastError;
}

int TServo::S1_GoAbsPos_AutoMode_Asyn(float AAbsPosMM, float ASpeedMMS) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_GoAbsPos_AutoMode_Asyn: Servo 1 is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S1_GoAbsPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetPosition = AAbsPosMM;
    if(AAbsPosMM > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        log_nok("S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is greater than the max value(%f), and the target value used the max value instead", FS1MaxPosition);
    }
    else if(AAbsPosMM < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        log_nok("S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is smaller than the min value(%f), and the target value used the min value instead", FS1MinPosition);
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        log_nok("S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is greater than the max value(%f), and the target value used the max value instead", FS1MaxSpeed);
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        log_nok("S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS1TargetPositionAuto = ASetPosition;
    FS1TargetSpeedAuto = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    // // if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
    if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_GoAbsPos_AutoMode_Asyn: S1 auto mode goto abs. position write error");
        return -2;
    }
    else {
        if(!FPedalIsSysMode)
            log("S1_GoAbsPos_AutoMode_Asyn: S1 auto mode goto abs. position send out");
        return 0;
    }
}

int TServo::S1_GoAbsPos_AutoMode_Syn(float AAbsPosMM, float ASpeedMMS, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_GoAbsPos_AutoMode_Syn: Servo 1 is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S1_GoAbsPos_AutoMode_Syn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetPosition = AAbsPosMM;
    if(AAbsPosMM > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        log_nok("S1_GoAbsPos_AutoMode_Syn: S1 Set positon is greater than the max value(%f), and the target value used the max value instead", FS1MaxPosition);
    }
    else if(AAbsPosMM < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        log_nok("S1_GoAbsPos_AutoMode_Syn: S1 Set positon is smaller than the min value(%f), and the target value used the min value instead", FS1MinPosition);
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        log_nok("S1_GoAbsPos_AutoMode_Syn: S1 Set positon is greater than the max value(%f), and the target value used the max value instead", FS1MaxSpeed);
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        log_nok("S1_GoAbsPos_AutoMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS1TargetPositionAuto = ASetPosition;
    FS1TargetSpeedAuto = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    // if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
    if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_GoAbsPos_AutoMode_Syn: S1 auto mode goto abs. position write error");
        return -2;
    }

    FS1RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS1RunFinished && fabs(FS1TargetPositionAuto - FS1ActPosition) < PositionMaxTol) {
            log("S1_GoAbsPos_AutoMode_Syn: S1 auto mode goto abs. position finished");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S1_GoAbsPos_AutoMode_Syn: go abs position timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S1_RunSpd_AutoMode_Asyn(float ASpeedRPM) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_RunSpd_AutoMode_Asyn: Servo 1 is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S1_RunSpd_AutoMode_Asyn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetSpeed = ASpeedRPM;
    if(ASpeedRPM > 450) {
        ASetSpeed = 450;
        log_nok("S1_RunSpd_AutoMode_Asyn: S1 Set speed is greater than the max value(450 rpm), and the target value used the max value instead");
    }
    else if(ASpeedRPM < -450) {
        ASetSpeed = -450;
        log_nok("S1_RunSpd_AutoMode_Asyn: S1 Set positon is smaller than the min value(-450 rpm), and the target value used the min value instead");
    }

    FS1TargetPositionAuto = 0;
    FS1TargetSpeedAuto = ASetSpeed;

    // *(float*) AWriteByte.data() = 0;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;
    S7.ValReal(&AWriteByte[0], 0);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
    if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_RunSpd_AutoMode_Asyn: S1 auto mode run speed write error");
        return -2;
    }
    return 0;
}

int TServo::S1_RunSpd_AutoMode_Syn(float ASpeedRPM, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_RunSpd_AutoMode_Syn: Servo 1 is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S1_RunSpd_AutoMode_Syn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetSpeed = ASpeedRPM;
    if(ASpeedRPM > 450) {
        ASetSpeed = 450;
        log_nok("S1_RunSpd_AutoMode_Syn: S1 Set speed is greater than the max value(450 rpm), and the target value used the max value instead");
    }
    else if(ASpeedRPM < -450) {
        ASetSpeed = -450;
        log_nok("S1_RunSpd_AutoMode_Syn: S1 Set speed is smaller than the min value(-450 rpm), and the target value used the min value instead");
    }

    FS1TargetPositionAuto = 0;
    FS1TargetSpeedAuto = ASetSpeed;

    // *(float*) AWriteByte.data() = 0;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;
    S7.ValReal(&AWriteByte[0], 0);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
    if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_RunSpd_AutoMode_Syn: S1 auto mode run target speed write error");
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(fabs(FS1TargetSpeedAuto - FS1ActSpeed) < 0.1) {
            log("S1_RunSpd_AutoMode_Syn: S1 auto mode run target speed finished");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S1_RunSpd_AutoMode_Syn: S1 auto mode run to target speed timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S1_GoAbsPos_MMode_Asyn(float AAbsPosMM, float ASpeedMMS) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_GoAbsPostion_MMode_Asyn: Servo 1 is not ready");
        return -1;
    }

    if(FS7IsAutoMode) {
        log_nok("S1_GoAbsPostion_MMode_Asyn: Servo is in auto mode, switch to manual first");
        return -1;
    }

    float ASetPosition = AAbsPosMM;
    if(AAbsPosMM > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        log_nok("S1_GoAbsPostion_MMode_Asyn: S1 Set positon is greater than the max value(%f), and the target value used the max value instead", FS1MaxPosition);
    }
    else if(AAbsPosMM < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        log_nok("S1_GoAbsPostion_MMode_Asyn: S1 Set positon is smaller than the min value(%f), and the target value used the min value instead", FS1MinPosition);
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        log_nok("S1_GoAbsPostion_MMode_Asyn: S1 Set positon is greater than the max value( %d ), and the target value used the max value instead", FS1MaxSpeed);
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        log_nok("S1_GoAbsPostion_MMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS1TargetPositionManual = ASetPosition;
    FS1TargetSpeedManual = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1MPosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_GoAbsPostion_MMode_Asyn: S1 manual mode goto abs. position write error");
        return -2;
    }
    else {
        log("S1_GoAbsPostion_MMode_Asyn: S1 manual mode goto abs. position send out");
        return 0;
    }
}

int TServo::S1_GoAbsPos_MMode_Syn(float AAbsPosMM, float ASpeedMMS, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_GoAbsPostion_MMode_Syn: Servo 1 is not ready");
        return -1;
    }

    if(FS7IsAutoMode) {
        log_nok("S1_GoAbsPostion_MMode_Syn: Servo is in auto mode, switch to manual first");
        return -1;
    }

    float ASetPosition = AAbsPosMM;
    if(AAbsPosMM > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        log_nok("S1_GoAbsPostion_MMode_Syn: S1 Set positon is greater than the max value(%f), and the target value used the max value instead", FS1MaxPosition);
    }
    else if(AAbsPosMM < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        log_nok("S1_GoAbsPostion_MMode_Syn: S1 Set positon is smaller than the min value(%f), and the target value used the min value instead", FS1MinPosition);
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        log_nok("S1_GoAbsPostion_MMode_Syn: S1 Set positon is greater than the max value( %d ), and the target value used the max value instead", FS1MaxSpeed);
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        log_nok("S1_GoAbsPostion_MMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS1TargetPositionManual = ASetPosition;
    FS1TargetSpeedManual = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1MPosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_GoAbsPostion_MMode_Syn: S1 manual mode goto abs. position write error");
        return -2;
    }

    FS1RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS1RunFinished && fabs(FS1TargetPositionManual - FS1ActPosition) < PositionMaxTol) {
            log("S1_GoAbsPostion_MMode_Syn: S1 manual mode goto abs. position finished");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S1_GoAbsPostion_MMode_Syn: go abs position timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S1_GoZero_Asyn() {
    unsigned char AWriteByte = 0;
    if(!FS1IsReady) {
        log_nok("S1_GoZero_Asyn: S1 not ready");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS1GoZero, &AWriteByte, false) != 0) {
        log_nok("S1_GoZero_Asyn: S7 Write go zero error");
        return -2;
    }
    else {
        log("S1_GoZero_Asyn: S1 go zero comand send out");
        return 0;
    }
}

int TServo::S1_GoZero_Syn(int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS1IsReady) {
        log_nok("S1_GoZero_Syn: S1 not ready");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS1GoZero, &AWriteByte, false) != 0) {
        log_nok("S1_GoZero_Syn: S7 Write S1 go zero address error");
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
            log_nok("S1_GoZero_Syn: Servo Go Zero Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S1_Manual_JogIn() {
    unsigned char AWriteByte = 0;
    if(!FS1IsReady) {
        log_nok("S1_Manual_JogIn: S1 is not ready");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS1JogB, &AWriteByte, false) != 0) {
        log_nok("S1_Manual_JogIn: S7 Write bit error");
        return -2;
    }
    else {
        log("S1_Manual_JogIn: S1 Jog In");
        return 0;
    }
}

int TServo::S1_Manual_JogOut() {
    unsigned char AWriteByte = 0;

    if(!FS1IsReady) {
        log_nok("S1_Manual_JogOut: S1 is not ready");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS1JogF, &AWriteByte, false) != 0) {
        log_nok("S1_Manual_JogOut: S7 Write bit error");
        return -2;
    }
    else {
        log("S1_Manual_JogOut: S1 Jog Out");
        return 0;
    }
}

int TServo::S1_GoRelPos_AutoMode_Asyn(float ARelPosMM, float ASpeedMMS) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_GoRelPos_AutoMode_Asyn: Servo is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S1_GoRelPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetPosition = FS1ActPosition + ARelPosMM;

    if(ASetPosition > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        log_nok("S1_GoRelPos_AutoMode_Asyn: S1 Set positon is greater than the max value, and the target value used the max value instead");
    }
    else if(ASetPosition < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        log_nok("S1_GoRelPos_AutoMode_Asyn: S1 Set positon is smaller than the min value, and the target value used the min value instead");
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        log_nok("S1_GoRelPos_AutoMode_Asyn: S1 Set positon is greater than the max value(%f), and the target value used the max value instead", FS1MaxSpeed);
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        log_nok("S1_GoRelPos_AutoMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS1TargetPositionAuto = ASetPosition;
    FS1TargetSpeedAuto = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    // if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
    if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_GoRelPos_AutoMode_Asyn: S1 auto mode write speed error");
        return -2;
    }
    else {
        log("S1_GoRelPos_AutoMode_Asyn: S1 auto mode goto rel. position send out");
        return 0;
    }
}

int TServo::S1_GoRelPos_AutoMode_Syn(float ARelPosMM, float ASpeedMMS, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_GoRelPos_AutoMode_Syn: Servo is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S1_GoRelPos_AutoMode_Syn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetPosition = FS1ActPosition + ARelPosMM;

    if(ASetPosition > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        log_nok("S1_GoRelPos_AutoMode_Syn: S1 Set positon is greater than the max value, and the target value used the max value instead");
    }
    else if(ASetPosition < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        log_nok("S1_GoRelPos_AutoMode_Syn: S1 Set positon is smaller than the min value, and the target value used the min value instead");
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        log_nok("S1_GoRelPos_AutoMode_Syn: S1 Set positon is greater than the max value( %d ), and the target value used the max value instead", FS1MaxSpeed);
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        log_nok("S1_GoRelPos_AutoMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS1TargetPositionAuto = ASetPosition;
    FS1TargetSpeedAuto = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    // if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
    if(S7Write(AddrSetS1APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_GoRelPos_AutoMode_Syn: S1 auto mode write speed error");
        return -2;
    }

    FS1RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS1RunFinished && fabs(FS1TargetPositionAuto - FS1ActPosition) < PositionMaxTol) {
            log("S1_GoRelPos_AutoMode_Syn: S1 auto mode goto rel. position finished");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S1_GoRelPos_AutoMode_Syn: go rel. position timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S1_GoRelPos_MMode_Asyn(float ARelPosMM, float ASpeedMMS) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_GoRelPos_MMode_Asyn: Servo is not ready");
        return -1;
    }

    if(FS7IsAutoMode) {
        log_nok("S1_GoRelPos_MMode_Asyn: Servo is in auto mode, switch to manual first");
        return -1;
    }

    float ASetPosition = FS1ActPosition + ARelPosMM;

    if(ASetPosition > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        log_nok("S1_GoRelPos_MMode_Asyn: S1 Set positon is greater than the max value, and the target value used the max value instead");
    }
    else if(ASetPosition < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        log_nok("S1_GoRelPos_MMode_Asyn: S1 Set positon is smaller than the min value, and the target value used the min value instead");
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        log_nok("S1_GoRelPos_MMode_Asyn: S1 Set positon is greater than the max value( %d ), and the target value used the max value instead", FS1MaxSpeed);
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        log_nok("S1_GoRelPos_MMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS1TargetPositionManual = ASetPosition;
    FS1TargetSpeedManual = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1MPosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_GoRelPos_MMode_Asyn: S1 manual mode write speed error");
        return -2;
    }
    else {
        log("S1_GoRelPos_MMode_Asyn: S1 manual mode goto rel. position send out");
        return 0;
    }
}

int TServo::S1_GoRelPos_MMode_Syn(float ARelPosMM, float ASpeedMMS, int ATimeout) {
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS1IsReady) {
        log_nok("S1_GoRelPos_MMode_Syn: Servo is not ready");
        return -1;
    }

    if(FS7IsAutoMode) {
        log_nok("S1_GoRelPos_MMode_Syn: Servo is in auto mode, switch to manual first");
        return -1;
    }

    float ASetPosition = FS1ActPosition + ARelPosMM;

    if(ASetPosition > FS1MaxPosition) {
        ASetPosition = FS1MaxPosition;
        log_nok("S1_GoRelPos_MMode_Syn: S1 Set positon is greater than the max value, and the target value used the max value instead");
    }
    else if(ASetPosition < FS1MinPosition) {
        ASetPosition = FS1MinPosition;
        log_nok("S1_GoRelPos_MMode_Syn: S1 Set positon is smaller than the min value, and the target value used the min value instead");
    }

    float ASetSpeed = ASpeedMMS;
    if(ASpeedMMS > FS1MaxSpeed) {
        ASetSpeed = FS1MaxSpeed;
        log_nok("S1_GoRelPos_MMode_Syn: S1 Set positon is greater than the max value( %d ), and the target value used the max value instead", FS1MaxSpeed);
    }
    else if(ASpeedMMS < 0) {
        ASetSpeed = 0;
        log_nok("S1_GoRelPos_MMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS1TargetPositionManual = ASetPosition;
    FS1TargetSpeedManual = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS1MPosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S1_GoRelPos_MMode_Syn: S1 manual mode write speed error");
        return -2;
    }

    FS1RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS1RunFinished && fabs(FS1TargetPositionManual - FS1ActPosition) < PositionMaxTol) {
            log("S1_GoRelPos_MMode_Syn: S1 manual mode goto rel. position finished");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S1_GoRelPos_MMode_Syn: go rel. position timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S1_Run_On(int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS1IsServoOn) {
        log_nok("S1_Run_Syn: S1 need Servo On First");
        return -1;
    }

    FPedalIsSysMode = false;

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS1Start, &AWriteByte, false) != 0) {
        log_nok("S1_Run_Syn: S7 Write S1 start address error");
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(FS1IsReady)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S1_Run_Syn: Servo Start Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S1_ServoON(bool AEnable, int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS7IsHandShaked) {
        log_nok("S1_ServoON: HandShake needed before Servo On");
        return -1;
    }

    if(!FS7IsPowerOn) {
        log_nok("S1_ServoON: Power is off");
        return -1;
    }

    // if(AEnable) {
        // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, AEnable);
    // }

    if(S7Write(AddrSetS1ServoOn, &AWriteByte, false) != 0) {
        log_nok("S1_ServoON: S7 Write S1 servo on address error");
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(FS1IsServoOn == AEnable) {
            if(AEnable)
                log_ok("S1_ServoON: Servo On Successful");
            else
                log_ok("S1_ServoON: Servo Off Successful");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S1_ServoON: Servo On/Off Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S1_SetZero(int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS1IsServoOn) {
        log_nok("S1_SetZero: S1 need Servo On First");
        return -1;
    }

    if(!FS1RunFinished) {
        log_nok("S1_SetZero: S1 is running, cannot set zero");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS1SetZero, &AWriteByte, false) != 0) {
        log_nok("S1_SetZero: S7 Write S1 set zero address error");
        return -2;
    }

    FS1ZeroExisted = false;

    int ATime = 0;
    while(true) {
        // todo: set 函数
        if(FS1ZeroExisted && FS1RunFinished)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S1_SetZero: Servo Set Zero Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}
int TServo::S1_Run_Off(int ATimeout) {
    unsigned char AWriteByte = 0;
    if(!FS1IsServoOn) {
        log_nok("S1_Stop_Syn: S1 need Servo On First");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS1Stop, &AWriteByte, false) != 0) {
        log_nok("S1_Stop_Syn: S7 Write S1 stop address error");
        return -2;
    }

    int ATime = 0;
    while(true) {
        // todo: set 函数
        if(FS1IsReady)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S1_Stop_Syn: Servo Stop Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}
int TServo::S2_GoAbsPos_AutoMode_Asyn(float AAbsPosDeg, float ASpeedDegS) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        log_nok("S2_GoAbsPos_AutoMode_Asyn: Servo 1 is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S2_GoAbsPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetPosition = AAbsPosDeg;
    if(AAbsPosDeg > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        log_nok("S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxPosition);
    }
    else if(AAbsPosDeg < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        log_nok("S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is smaller than the min value(%f), and the target value used the min value instead", FS2MinPosition);
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        log_nok("S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxSpeed);
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        log_nok("S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS2TargetPositionAuto = ASetPosition;
    FS2TargetSpeedAuto = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position write error");
        return -2;
    }
    else {
        log("S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position send out");
        return 0;
    }
}

int TServo::S2_GoAbsPos_AutoMode_Syn(float AAbsPosDeg, float ASpeedDegS, int ATimeout) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        log_nok("S2_GoAbsPos_AutoMode_Syn: Servo 2 is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S2_GoAbsPos_AutoMode_Syn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetPosition = AAbsPosDeg;
    if(AAbsPosDeg > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        log_nok("S2_GoAbsPos_AutoMode_Syn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxPosition);
    }
    else if(AAbsPosDeg < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        log_nok("S2_GoAbsPos_AutoMode_Syn: S2 Set positon is smaller than the min value(%f), and the target value used the min value instead", FS2MinPosition);
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        log_nok("S2_GoAbsPos_AutoMode_Syn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxSpeed);
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        log_nok("S2_GoAbsPos_AutoMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS2TargetPositionAuto = ASetPosition;
    FS2TargetSpeedAuto = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S2_GoAbsPos_AutoMode_Syn: S2 auto mode goto abs. position write error");
        return -2;
    }

    FS2RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS2RunFinished && fabs(FS2TargetPositionAuto - FS2ActPosition) < PositionMaxTol) {
            log("S2_GoAbsPos_AutoMode_Syn: S2 auto mode goto abs. position finished");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S2_GoAbsPos_AutoMode_Syn: go abs position timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S2_GoAbsPos_MMode_Asyn(float AAbsPosDeg, float ASpeedDegS) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        log_nok("S2_GoAbsPostion_MMode_Asyn: Servo 2 is not ready");
        return -1;
    }

    if(FS7IsAutoMode) {
        log_nok("S2_GoAbsPostion_MMode_Asyn: Servo is in auto mode, switch to manual first");
        return -1;
    }

    float ASetPosition = AAbsPosDeg;
    if(AAbsPosDeg > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        log_nok("S2_GoAbsPostion_MMode_Asyn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxPosition);
    }
    else if(AAbsPosDeg < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        log_nok("S2_GoAbsPostion_MMode_Asyn: S2 Set positon is smaller than the min value(%f), and the target value used the min value instead", FS2MinPosition);
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        log_nok("S2_GoAbsPostion_MMode_Asyn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxSpeed);
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        log_nok("S2_GoAbsPostion_MMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS2TargetPositionManual = ASetPosition;
    FS2TargetSpeedManual = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2MPosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S2_GoAbsPostion_MMode_Asyn: S2 manual mode goto abs. position write error");
        return -2;
    }
    else {
        log("S2_GoAbsPostion_MMode_Asyn: S2 manual mode goto abs. position send out");
        return 0;
    }
}

int TServo::S2_GoAbsSlopGrad_AutoMode_Asyn(float AAbsGradPercent) {
    if(fabs(AAbsGradPercent) > 30) {
        log_nok("Max Slop is 30%, Current Setting is %f%", AAbsGradPercent);
        return -1;
    }
    float ADegree = atan(AAbsGradPercent / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_AutoMode_Asyn(ADegree, FS2SlopSpeed);
}

int TServo::S2_GoAbsSlopGrad_AutoMode_Syn(float AAbsGradPercent, int ATimeout) {
    if(fabs(AAbsGradPercent) > 30) {
        log_nok("Max Slop is 30%, Current Setting is %f%", AAbsGradPercent);
        return -1;
    }
    float ADegree = atan(AAbsGradPercent / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_AutoMode_Syn(ADegree, FS2SlopSpeed, ATimeout);
}

int TServo::S2_GoAbsSlopGrad_MMode_Asyn(float AAbsGradPercent) {
    if(fabs(AAbsGradPercent) > 30) {
        log_nok("Max Slop is 30%, Current Setting is %f%", AAbsGradPercent);
        return -1;
    }

    float ADegree = atan(AAbsGradPercent / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_MMode_Asyn(ADegree, FS2SlopSpeed);
}

int TServo::S2_GoAbsSlopGrad_MMode_Syn(float AAbsGradPercent, int ATimeout) {
    if(fabs(AAbsGradPercent) > 30) {
        log_nok("Max Slop is 30%, Current Setting is %f%", AAbsGradPercent);
        return -1;
    }
    float ADegree = atan(AAbsGradPercent / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_MMode_Syn(ADegree, FS2SlopSpeed, ATimeout);
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
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        log_nok("S2_GoAbsPostion_MMode_Syn: Servo 2 is not ready");
        return -1;
    }

    if(FS7IsAutoMode) {
        log_nok("S2_GoAbsPostion_MMode_Syn: Servo is in auto mode, switch to manual first");
        return -1;
    }

    float ASetPosition = AAbsPosDeg;
    if(AAbsPosDeg > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        log_nok("S2_GoAbsPostion_MMode_Syn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxPosition);
    }
    else if(AAbsPosDeg < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        log_nok("S2_GoAbsPostion_MMode_Syn: S2 Set positon is smaller than the min value(%f), and the target value used the min value instead", FS2MinPosition);
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        log_nok("S2_GoAbsPostion_MMode_Syn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxSpeed);
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        log_nok("S2_GoAbsPostion_MMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS2TargetPositionManual = ASetPosition;
    FS2TargetSpeedManual = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2MPosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S2_GoAbsPostion_MMode_Syn: S2 manual mode goto abs. position write error");
        return -2;
    }

    FS2RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS2RunFinished && fabs(FS2TargetPositionManual - FS2ActPosition) < PositionMaxTol) {
            log("S2_GoAbsPostion_MMode_Syn: S2 manual mode goto abs. position finished");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S2_GoAbsPostion_MMode_Syn: go abs position timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S2_GoZero_Asyn() {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsReady) {
        log_nok("S2_GoZero_Asyn: S2 not ready");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS2GoZero, &AWriteByte, false) != 0) {
        log_nok("S2_GoZero_Asyn: S7 Write go zero error");
        return -2;
    }
    else {
        log("S2_GoZero_Asyn: S2 go zero comand send out");
        return 0;
    }
}

int TServo::S2_GoZero_Syn(int ATimeout) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsReady) {
        log_nok("S2_GoZero_Syn: S2 not ready");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS2GoZero, &AWriteByte, false) != 0) {
        log_nok("S2_GoZero_Syn: S7 Write S2 go zero address error");
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
            log_nok("S2_GoZero_Syn: Servo Go Zero Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S2_Manual_JogIn() {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsReady) {
        log_nok("S2_Manual_JogIn: S2 is not ready");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS2JogB, &AWriteByte, false) != 0) {
        log_nok("S2_Manual_JogIn: S7 Write bit error");
        return -2;
    }
    else {
        log("S2_Manual_JogIn: S2 Jog In");
        return 0;
    }
}

int TServo::S2_Manual_JogOut() {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsReady) {
        log_nok("S2_Manual_JogOut: S2 is not ready");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS2JogF, &AWriteByte, false) != 0) {
        log_nok("S2_Manual_JogOut: S7 Write bit error");
        return -2;
    }
    else {
        log("S2_Manual_JogOut: S2 Jog Out");
        return 0;
    }
}

int TServo::S2_GoRelPos_AutoMode_Asyn(float ARelPosDeg, float ASpeedDegS) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        log_nok("S2_GoRelPos_AutoMode_Asyn: Servo is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S2_GoRelPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetPosition = FS2ActPosition + ARelPosDeg;

    if(ASetPosition > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        log_nok("S2_GoRelPos_AutoMode_Asyn: S2 Set positon is greater than the max value, and the target value used the max value instead");
    }
    else if(ASetPosition < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        log_nok("S2_GoRelPos_AutoMode_Asyn: S2 Set positon is smaller than the min value, and the target value used the min value instead");
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        log_nok("S2_GoRelPos_AutoMode_Asyn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxSpeed);
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        log_nok("S2_GoRelPos_AutoMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS2TargetPositionAuto = ASetPosition;
    FS2TargetSpeedAuto = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S2_GoRelPos_AutoMode_Asyn: S2 auto mode write speed error");
        return -2;
    }
    else {
        log("S2_GoRelPos_AutoMode_Asyn: S2 auto mode goto rel. position send out");
        return 0;
    }
}

int TServo::S2_GoRelPos_AutoMode_Syn(float ARelPosDeg, float ASpeedDegS, int ATimeout) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        log_nok("S2_GoRelPos_AutoMode_Syn: Servo is not ready");
        return -1;
    }

    if(!FS7IsAutoMode) {
        log_nok("S2_GoRelPos_AutoMode_Syn: Servo is in manual mode, switch to auto first");
        return -1;
    }

    float ASetPosition = FS2ActPosition + ARelPosDeg;

    if(ASetPosition > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        log_nok("S2_GoRelPos_AutoMode_Syn: S2 Set positon is greater than the max value, and the target value used the max value instead");
    }
    else if(ASetPosition < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        log_nok("S2_GoRelPos_AutoMode_Syn: S2 Set positon is smaller than the min value, and the target value used the min value instead");
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        log_nok("S2_GoRelPos_AutoMode_Syn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxSpeed);
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        log_nok("S2_GoRelPos_AutoMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS2TargetPositionAuto = ASetPosition;
    FS2TargetSpeedAuto = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2APosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S2_GoRelPos_AutoMode_Syn: S2 auto mode write speed error");
        return -2;
    }

    FS2RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS2RunFinished && fabs(FS2TargetPositionAuto - FS2ActPosition) < PositionMaxTol) {
            log("S2_GoRelPos_AutoMode_Syn: S2 auto mode goto rel. position finished");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S2_GoRelPos_AutoMode_Syn: go rel. position timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S2_GoRelPos_MMode_Asyn(float ARelPosDeg, float ASpeedDegS) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        log_nok("S2_GoRelPos_MMode_Asyn: Servo is not ready");
        return -1;
    }

    if(FS7IsAutoMode) {
        log_nok("S2_GoRelPos_MMode_Asyn: Servo is in auto mode, switch to manual first");
        return -1;
    }

    float ASetPosition = FS2ActPosition + ARelPosDeg;

    if(ASetPosition > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        log_nok("S2_GoRelPos_MMode_Asyn: S2 Set positon is greater than the max value, and the target value used the max value instead");
    }
    else if(ASetPosition < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        log_nok("S2_GoRelPos_MMode_Asyn: S2 Set positon is smaller than the min value, and the target value used the min value instead");
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        log_nok("S2_GoRelPos_MMode_Asyn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxSpeed);
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        log_nok("S2_GoRelPos_MMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS2TargetPositionManual = ASetPosition;
    FS2TargetSpeedManual = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2MPosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S2_GoRelPos_MMode_Asyn: S2 manual mode write speed error");
        return -2;
    }
    else {
        log("S2_GoRelPos_MMode_Asyn: S2 manual mode goto rel. position send out");
        return 0;
    }
}

int TServo::S2_GoRelPos_MMode_Syn(float ARelPosDeg, float ASpeedDegS, int ATimeout) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    std::array<unsigned char, 8> AWriteByte = {0};

    if(!FS2IsReady) {
        log_nok("S2_GoRelPos_MMode_Syn: Servo is not ready");
        return -1;
    }

    if(FS7IsAutoMode) {
        log_nok("S2_GoRelPos_MMode_Syn: Servo is in auto mode, switch to manual first");
        return -1;
    }

    float ASetPosition = FS2ActPosition + ARelPosDeg;

    if(ASetPosition > FS2MaxPosition) {
        ASetPosition = FS2MaxPosition;
        log_nok("S2_GoRelPos_MMode_Syn: S2 Set positon is greater than the max value, and the target value used the max value instead");
    }
    else if(ASetPosition < FS2MinPosition) {
        ASetPosition = FS2MinPosition;
        log_nok("S2_GoRelPos_MMode_Syn: S2 Set positon is smaller than the min value, and the target value used the min value instead");
    }

    float ASetSpeed = ASpeedDegS;
    if(ASpeedDegS > FS2MaxSpeed) {
        ASetSpeed = FS2MaxSpeed;
        log_nok("S2_GoRelPos_MMode_Syn: S2 Set positon is greater than the max value(%f), and the target value used the max value instead", FS2MaxSpeed);
    }
    else if(ASpeedDegS < 0) {
        ASetSpeed = 0;
        log_nok("S2_GoRelPos_MMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead");
    }

    FS2TargetPositionManual = ASetPosition;
    FS2TargetSpeedManual = ASetSpeed;

    S7.ValReal(&AWriteByte[0], ASetPosition);
    S7.ValReal(&AWriteByte[4], ASetSpeed);

    // *(float*) AWriteByte.data() = ASetPosition;
    // *(float*) (AWriteByte.data() + 4) = ASetSpeed;

    if(S7Write(AddrSetS2MPosSpd, &AWriteByte[0], false) != 0) {
        log_nok("S2_GoRelPos_MMode_Syn: S2 manual mode write speed error");
        return -2;
    }

    FS2RunFinished = false;
    int ATime = 0;
    while(true) {
        if(FS2RunFinished && fabs(FS2TargetPositionManual - FS2ActPosition) < PositionMaxTol) {
            log("S2_GoRelPos_MMode_Syn: S2 manual mode goto rel. position finished");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S2_GoRelPos_MMode_Syn: go rel. position timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S2_GoRelSlopGrad_AutoMode_Asyn(float ARelGradPercent) {
    float AGrad = FS2ActPositionGrad + ARelGradPercent;
    if(fabs(AGrad) > 30) {
        log_nok("Max Slop is 30%, Current Setting is %f%", AGrad);
        return -1;
    }
    float ADegree = atan(AGrad / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_AutoMode_Asyn(ADegree, FS2SlopSpeed);
}

int TServo::S2_GoRelSlopGrad_AutoMode_Syn(float ARelGradPercent, int ATimeout) {
    float AGrad = FS2ActPositionGrad + ARelGradPercent;
    if(fabs(AGrad) > 30) {
        log_nok("Max Slop is 30%, Current Setting is %f%", AGrad);
        return -1;
    }
    float ADegree = atan(AGrad / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_AutoMode_Syn(ADegree, FS2SlopSpeed, ATimeout);
}

int TServo::S2_GoRelSlopGrad_MMode_Asyn(float ARelGradPercent) {
    float AGrad = FS2ActPositionGrad + ARelGradPercent;
    if(fabs(AGrad) > 30) {
        log_nok("Max Slop is 30%, Current Setting is %f%", AGrad);
        return -1;
    }
    float ADegree = atan(AGrad / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_MMode_Asyn(ADegree, FS2SlopSpeed);
}


int TServo::S2_GoRelSlopGrad_MMode_Syn(float ARelGradPercent, int ATimeout) {
    float AGrad = FS2ActPositionGrad + ARelGradPercent;
    if(fabs(AGrad) > 30) {
        log_nok("Max Slop is 30%, Current Setting is %f%", AGrad);
        return -1;
    }
    float ADegree = atan(AGrad / 100) * 180 / pi + FS2MountPosition;
    return S2_GoAbsPos_MMode_Syn(ADegree, FS2SlopSpeed, ATimeout);
}

int TServo::S2_Run_On(int ATimeout) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsServoOn) {
        log_nok("S2_Run_On: S2 need Servo On First");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS2Start, &AWriteByte, false) != 0) {
        log_nok("S2_Run_On: S7 Write S2 start address error");
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(FS2IsReady)
            return 0;

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S2_Run_On: Servo Start Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S2_ServoON(bool AEnable, int ATimeout) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_ServoON: S2 is invalid");
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS7IsHandShaked) {
        log_nok("S2_ServoON: HandShake needed before Servo On");
        return -1;
    }

    if(!FS7IsPowerOn) {
        log_nok("S2_ServoON: Power is off");
        return -1;
    }

    if(AEnable) {
        // AWriteByte |= 0x01;
        S7.ValBit(&AWriteByte, 0, true);
    }

    if(S7Write(AddrSetS2ServoOn, &AWriteByte, false) != 0) {
        log_nok("S2_ServoON: S7 Write S2 servo on address error");
        return -2;
    }

    int ATime = 0;
    while(true) {
        if(FS2IsServoOn == AEnable) {
            if(AEnable)
                log_ok("S2_ServoON: Servo On Successful");
            else
                log_ok("S2_ServoON: Servo Off Successful");
            return 0;
        }

        Sleep(1);
        ATime++;
        if(ATime > ATimeout) {
            log_nok("S2_ServoON: Servo On/Off Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S2_SetZero(int ATimeout) {
    if(FS7IsOnlyPedal) {
        log_nok("S2_SetZero: S2 is invalid");
        return -10;
    }
    unsigned char AWriteByte = 0;
    if(!FS2IsServoOn) {
        log_nok("S2_SetZero: S2 need Servo On First");
        return -1;
    }

    if(!FS2RunFinished) {
        log_nok("S2_SetZero: S2 is running, cannot set zero");
        return -1;
    }

    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS2SetZero, &AWriteByte, false) != 0) {
        log_nok("S2_SetZero: S7 Write S2 set zero address error");
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
            log_nok("S2_SetZero: Servo Set Zero Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }
}

int TServo::S3_Go_In() {
    if(!FS7WithAirCylinder) {
        log_nok("S3_Go_In: Air Cylinder is invalid");
        return -10;
    }
    unsigned char AWriteByte = 0;
    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS3GoIn, &AWriteByte, false) != 0) {
        log_nok("S3_Go_In: S7 Write S3 go in address error");
        return -2;
    }
    else {
        log_ok("S3_Go_In: Air Cylinder Go In Successful");
        return 0;
    }
}

int TServo::S3_Go_Out() {
    if(!FS7WithAirCylinder) {
        log_nok("S3_Go_Out: Air Cylinder is invalid");
        return -10;
    }
    unsigned char AWriteByte = 0;
    // AWriteByte |= 0x01;
    S7.ValBit(&AWriteByte, 0, true);

    if(S7Write(AddrSetS3GoOut, &AWriteByte, false) != 0) {
        log_nok("S3_Go_Out: S7 Write S3 go out address error");
        return -2;
    }
    else {
        log_ok("S3_Go_Out: Air Cylinder Go Out Successful");
        return 0;
    }
}
float TServo::S3_Pressure_Current(float APressure) {
    float ACurrent;
    log("Target Pressure is %f Bar.", APressure);
    // vLog("S3P2AFactor is " + std::to_string(S3P2AFactor) + ", S3P2AOffset is " + std::to_string(S3P2AOffset));
    ACurrent = FS3P2AFactor * APressure + FS3P2AOffset;
    // todo: vTIOConfig 限制
    if(ACurrent < vTIOConfig.FAirValveMinCurrent)
        ACurrent = vTIOConfig.FAirValveMinCurrent;
    else if(ACurrent > vTIOConfig.FAirValveMaxCurrent)
        ACurrent = vTIOConfig.FAirValveMaxCurrent;
    log("Target Current is %f mA.", ACurrent);
    return ACurrent;
}

int TServo::S3_Set_Current(float ACurrentA) {
    unsigned char AWriteByte[4] = {0};
    float ASetCurrent;
    int i;

    if(!FS7WithAirCylinder) {
        log_nok("air cylinder is not activated"); // LVL_ERROR
        return -1;
    }

    if(!FS7IsOnlyPedal) {
        log_nok("rotate servo is actived, can not use air cylinder"); // LVL_ERROR
        return -1;
    }
    ASetCurrent = ACurrentA;
    // todo:  vTIOConfig 限制
    if(ACurrentA > vTIOConfig.FAirValveMaxCurrent) {
        ASetCurrent = vTIOConfig.FAirValveMaxCurrent;
        log_warning("S3_Set_Push_Force: Set Force is greater than 20 mA, and the target value used the max value instead"); // LVL_WARNING
    }
    else if(ACurrentA < vTIOConfig.FAirValveMinCurrent) {
        ASetCurrent = vTIOConfig.FAirValveMinCurrent;
        log_warning("S3_Set_Push_Force: Set Force is smaller than  0 mA, and the target value used the min value instead"); // LVL_WARNING
    }
    else {
        ASetCurrent = ACurrentA;
    }

    SetFS3TargetCurrent(ASetCurrent);

    S7.ValReal(&AWriteByte[0], ASetCurrent);

    if(S7Write(AddrSetS3Current, AWriteByte, false) != 0) {
        log_nok("S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position write error"); // LVL_ERROR
        return -2;
    }
    else {
        log("S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position send out"); // LVL_INFO
        return 0;
    }
}

int TServo::S3_Set_Target_Pressure(float ATargetPressureBar) {
    if(ATargetPressureBar < 0) {
        log_nok("S3_Set_Target_Pressure: Target Pressure must be greater than 0 Bar");
        return -1;
    }
    else if(ATargetPressureBar > 250) {
        log_nok("S3_Set_Target_Pressure: Target Pressure must be smaller than 250 Bar");
        return -2;
    }
    float ACurrent = S3_Pressure_Current(ATargetPressureBar);

    return S3_Set_Current(ACurrent);
}

int TServo::S2_Run_Off(const int ATimeout) {
    unsigned char AWriteByte;
    int ATime = 0;
    if(FS7IsOnlyPedal) {
        log_nok("S2_Run_On: S2 is invalid");
        return -10;
    }
    AWriteByte = 0;
    if(!FS2IsServoOn) {
        log("S2_Stop_Syn: S2 is already Servo off");
        return 0;
    }

    S7.ValBit(&AWriteByte, 0, true);

    if(0 != S7Write(AddrSetS2Stop, &AWriteByte, false)) {
        log_nok("S2_Stop_Syn: S7 Write S2 stop address error");
        return -2;
    }
    // to check

    ATime = 0;
    while(true) {
        if(!FS2IsReady)
            return 0;
        Sleep(1);
        ATime = ATime++;
        if(ATime > ATimeout) {
            log_nok("S2_Stop_Syn: Servo Stop Timeout, timeout setting is %d ms", ATimeout);
            return -3;
        }
    }

}


void TServo::SetFS1ActPosition(float Value) {
    FS1ActPosition = Value;
    app.set_system_var_double("tio.PedalPosition", Value);
}

void TServo::SetFS1ActSpeed(float Value) {
    FS1ActSpeed = Value;
    app.set_system_var_double("tio.PedalSpeed", Value);
}

void TServo::SetFPedalIsSysMode(bool AEnable) {
    FPedalIsSysMode = AEnable;
    if(FPedalIsSysMode) {
        log("TServo.SetFPedalIsSysMode: Pedal is controlled by system variable tio.PedalTargetPosition/PedalTargetPercent and tio.PedalTargetSpeed, set speed first and then set position to enable run"); // LVL_INFO
    }
    else {
        log("TServo.SetFPedalIsSysMode: Pedal is controlled by api"); // LVL_INFO
    }
}

void TServo::SetFS1IsFault(bool Value) {
    if(FS1IsFault != Value) {
        if(Value)
            log_nok("SetFS1IsFault: Servo 1 Fault"); // LVL_ERROR
        else
            log("SetFS1IsFault: Servo 1 Fault Cleared"); // LVL_INFO
    }
    FS1IsFault = Value;
}

void TServo::SetFS1IsReady(bool Value) {
    if(FS1IsReady != Value) {
        if(Value)
            log("SetFS1IsReady: Servo 1 is ready"); // LVL_INFO
        else
            log("SetFS1IsReady: Servo 1 not ready"); // LVL_INFO
    }
    FS1IsReady = Value;
}

void TServo::SetFS1RunFinished(bool Value) {
    FS1RunFinished = Value;
}

void TServo::SetFS1IsServoOn(bool Value) {
    if(FS1IsServoOn != Value) {
        if(Value)
            log("SetFS1IsServoOn: Servo 1 servo on"); // LVL_INFO
        else
            log("SetFS1IsServoOn: Servo 1 servo off"); // LVL_INFO
    }
    FS1IsServoOn = Value;
}

void TServo::SetFS1MaxPosition(float Value) {
    if(Value >= 60) {
        FS1MaxPosition = 60;
        log_nok("SetFS1MaxPosition: Set position is: %f mm, out of range, the max value set 60 mm", Value); // LVL_ERROR
    }
    else if(Value < 0) {
        FS1MaxPosition = 0;
        log("SetFS1MaxPosition: Set position is: %f mm, out of range, the max value set 0 mm", Value); // LVL_INFO
    }
    else {
        FS1MaxPosition = Value;
        log("SetFS1MaxPosition: Servo 1 maxium set position is: %f mm", Value); // LVL_INFO
    }
    vTIOConfig.FServo1MaxPosition = FS1MaxPosition;
}

void TServo::SetFS1MaxSpeed(float Value) {
    FS1MaxSpeed = Value;
    log("SetFS1MaxSpeed: Servo 1 maxium set speed is: %f mm/s", Value); // LVL_INFO
}

void TServo::SetFS1MinPosition(float Value) {
    if(Value > 0) {
        FS1MinPosition = 0;
        log_nok("SetFS1MinPosition: Set position is: %f mm, out of range, the min value set 0 mm", Value); // LVL_ERROR
    }
    else if(Value < -10) {
        FS1MinPosition = -10;
        log("SetFS1MinPosition: Set position is: %f mm, out of range, the min value set 0 mm", Value); // LVL_INFO
    }
    else {
        FS1MinPosition = Value;
        log("SetFS1MinPosition: Servo 1 min set position is: %f mm", Value); // LVL_INFO
    }
    vTIOConfig.FServo1MinPosition = FS1MinPosition;
}

void TServo::SetFS1TargetPositionAuto(float Value) {
    FS1TargetPositionAuto = Value;
    if(!FPedalIsSysMode)
        log("SetFS1TargetPositionAuto: Servo 1 auto mode target position is: %f mm", Value); // LVL_INFO
}

void TServo::SetFS1TargetPositionManual(float Value) {
    FS1TargetPositionManual = Value;
    log("SetFS1TargetPositionAuto: Servo 1 manual mode target position is: %f mm", Value); // LVL_INFO
}

void TServo::SetFS1TargetSpeedAuto(float Value) {
    FS1TargetSpeedAuto = Value;
    if(!FPedalIsSysMode)
        log("SetFS1TargetSpeedAuto: Servo 1 auto mode target speed is: %f mm/s", Value); // LVL_INFO
}

void TServo::SetFS1TargetSpeedManual(float Value) {
    FS1TargetSpeedManual = Value;
    log("SetFS1TargetSpeedManual: Servo 1 manual mode target speed is: %f mm/s", Value); // LVL_INFO
}

void TServo::SetFS1ZeroExisted(bool Value) {
    if(FS1ZeroExisted != Value) {
        if(Value)
            log("SetFS1ZeroExisted: Servo 1 has Zero Point"); // LVL_INFO
        else
            log("SetFS1ZeroExisted: Servo 1 no Zero Point"); // LVL_INFO
    }
    FS1ZeroExisted = Value;
}

void TServo::SetFS2ActPosition(float Value) {
    FS2ActPosition = Value;
    FS2ActPositionGrad = std::tan((FS2ActPosition - FS2MountPosition) * pi / 180) * 100;
    app.set_system_var_double("tio.RotateDegree", Value);
}

void TServo::SetFS2ActPositionGrad(float Value) {
    FS2ActPositionGrad = Value;
    app.set_system_var_double("tio.SlopeGrad", Value);
}

void TServo::SetFS2ActSpeed(float Value) {
    FS2ActSpeed = Value;
}

void TServo::SetFS2IsFault(bool Value) {
    if(FS2IsFault != Value) {
        if(Value)
            log_nok("SetFS2IsFault: Servo 2 Fault"); // LVL_ERROR
        else
            log("SetFS2IsFault: Servo 2 Fault Cleared"); // LVL_INFO
    }
    FS2IsFault = Value;
}

void TServo::SetFS2IsReady(bool Value) {
    if(FS2IsReady != Value) {
        if(Value)
            log("SetFS2IsReady: Servo 2 is ready"); // LVL_INFO
        else
            log("SetFS2IsReady: Servo 2 not ready"); // LVL_INFO
    }
    FS2IsReady = Value;
}

void TServo::SetFS2RunFinished(bool Value) {
    FS2RunFinished = Value;
}

void TServo::SetFS2SlopSpeed(float Value) {
    if(Value > FS2MaxSpeed || Value < 0) {
        log_nok("SetFS2SlopSpeed: Servo 2 slop run speed is set value not in valid range: [0, %f] °/s", FS2MaxSpeed); // LVL_ERROR
        return;
    }
    FS2SlopSpeed = Value;
    vTIOConfig.FServo2Speed = FS2SlopSpeed;
    log("SetFS2SlopSpeed: Servo 2 slop run speed is set to: %f °/s", Value); // LVL_INFO
}

void TServo::SetFS2IsServoOn(bool Value) {
    if(FS2IsServoOn != Value) {
        if(Value)
            log("SetFS2IsServoOn: Servo 2 servo on"); // LVL_INFO
        else
            log("SetFS2IsServoOn: Servo 2 servo off"); // LVL_INFO
    }
    FS2IsServoOn = Value;
}

void TServo::SetFS2MaxPosition(float Value) {
    FS2MaxPosition = Value;
    log("SetFS2MaxPosition: Servo 2 maxium set position is: %f °", Value); // LVL_INFO
}

void TServo::SetFS2MaxSpeed(float Value) {
    FS2MaxSpeed = Value;
    log("SetFS2MaxSpeed: Servo 2 maxium set slope is: %f °", Value); // LVL_INFO
}

void TServo::SetFS2MinPosition(float Value) {
    FS2MinPosition = Value;
    log("SetFS2MinPosition: Servo 2 min set slope is: %f °", Value); // LVL_INFO
}

void TServo::SetFS2MountPosition(float Value) {
    FS2MountPosition = Value;
    vTIOConfig.FServo2MountAngle = Value;
    log("SetFS2MountPosition: Servo 2 DUT Mounting Angle is set: %f °", Value); // LVL_INFO
}

void TServo::SetFS2TargetPositionAuto(float Value) {
    FS2TargetPositionAuto = Value;
    log("SetFS2TargetPositionAuto: Servo 2 auto mode target position is: %f mm", Value); // LVL_INFO
}

void TServo::SetFS2TargetPositionManual(float Value) {
    FS2TargetPositionManual = Value;
    log("SetFS2TargetPositionManual: Servo 2 manual mode target position is: %f mm", Value); // LVL_INFO
}

void TServo::SetFS2TargetSpeedAuto(float Value) {
    FS2TargetSpeedAuto = Value;
    log("SetFS2TargetSpeedAuto: Servo 2 auto mode target speed is: %f mm/s", Value); // LVL_INFO
}

void TServo::SetFS2TargetSpeedManual(float Value) {
    FS2TargetSpeedManual = Value;
    log("SetFS2TargetSpeedManual: Servo 2 manaul mode target speed is: %f mm/s", Value); // LVL_INFO
}

void TServo::SetFS2ZeroExisted(bool Value) {
    if(FS2ZeroExisted != Value) {
        if(Value)
            log("SetFS2ZeroExisted: Servo 2 has Zero Point"); // LVL_INFO
        else
            log("SetFS2ZeroExisted: Servo 2 no Zero Point"); // LVL_INFO
    }
    FS2ZeroExisted = Value;
}

void TServo::SetFS3MCMaxPressure(float Value) {
    if(Value >= 250) {
        FS3MCMaxPressure = 250;
        log_nok("SetFS3MCMaxPressure: Set Pressure is: %f Bar, out of range, the max value set 250 Bar", Value); // LVL_ERROR
    }
    else if(Value < 0) {
        FS3MCMaxPressure = 0;
        log("SetFS3MCMaxPressure: Set Pressure is: %f Bar, out of range, the min value set 0 Bar", Value); // LVL_INFO
    }
    else {
        FS3MCMaxPressure = Value;
        log("SetFS3MCMaxPressure: maxium set MC Pressure is: %f Bar", Value); // LVL_INFO
    }
    vTIOConfig.FMCMaxPressure = FS3MCMaxPressure;
}

void TServo::SetFS3P2AFactor(float Value) {
    if(Value >= 1) {
        FS3P2AFactor = 1;
        log_nok("SetFS3P2AFactor: Set Pressure convert current factor is: %f , out of range, the max value set 1", Value); // LVL_ERROR
    }
    else if(Value < 0) {
        FS3P2AFactor = 0;
        log("SetFS3P2AFactor: Set Pressure convert current factor is: %f Bar, out of range, the min value set 0", Value); // LVL_INFO
    }
    else {
        FS3P2AFactor = Value;
        log("SetFS3P2AFactor: Set Pressure convert current factor is: ",Value); // LVL_INFO
    }
    vTIOConfig.FPressure2CurrentFactor = FS3P2AFactor;
}

void TServo::SetFS3P2AOffset(float Value) {
    if(Value >= vTIOConfig.FAirValveMaxCurrent) {
        FS3P2AOffset = vTIOConfig.FAirValveMaxCurrent;
        log_nok("SetFS3P2AFactor: Set Pressure convert current offset is: %f , out of range, the max value set ", Value, vTIOConfig.FAirValveMaxCurrent); // LVL_ERROR
    }
    else if(Value < vTIOConfig.FAirValveMinCurrent) {
        FS3P2AOffset = vTIOConfig.FAirValveMinCurrent;
        log("SetFS3P2AFactor: Set Pressure convert current offset is: %f Bar, out of range, the min value set ", Value, vTIOConfig.FAirValveMinCurrent); // LVL_INFO
    }
    else {
        FS3P2AOffset = Value;
        log("SetFS3P2AFactor: Set Pressure convert current offset is: %f", Value); // LVL_INFO
    }
    vTIOConfig.FPressure2CurrentOffset = FS3P2AOffset;
}

void TServo::SetFS3TargetCurrent(float Value) {
    FS3TargetCurrent = Value;
    log("SetFS3TargetForce: air cylinder target current is: %f mA", Value); // LVL_INFO
}

void TServo::SetFS7IsFault(bool Value) {
    if(FS7IsFault != Value) {
        if(Value)
            log_nok("SetFS7IsFault: Servo has fault"); // LVL_ERROR
        else
            log("SetFS7IsFault: Servo fault cleared"); // LVL_INFO
    }
    FS7IsFault = Value;
}

void TServo::SetFS7IsHandShaked(bool Value) {
    if(FS7IsHandShaked != Value) {
        if(Value) {
            vHeartbeatThread->HeartbeatResume();
            log("SetFS7IsHandShaked: Servo Handshake created, Heartbeat thread resumed"); // LVL_INFO
        }
        else {
            vHeartbeatThread->HeartbeatSuspend();
            log("SetFS7IsHandShaked: Servo handshake free, Heartbeat thread suspended"); // LVL_INFO
        }
    }
    FS7IsHandShaked = Value;
}

void TServo::SetFS7IsOnlyPedal(bool Value) {
    FS7IsOnlyPedal = Value;
    if(Value)
        log("Only Pedal Servo is used");
    else
        log("Pedal and Slope Servo are used");
}

void TServo::SetFS7LastError(int Value) {
    FS7LastError = Value;
    if(FS7LastError != 0)
        log_nok("SetFS7LastError: Error Code is: %d, Error Message is: %s" , FS7LastError, CliErrorText(FS7LastError)); // LVL_ERROR
}

void TServo::SetFS7WithAirCylinder(bool Value) {
    FS7WithAirCylinder = Value;
    if(Value)
        log("Air Cylinder is activated.");
    else
        log("Air Cylinder is deactivated.");
}

void TServo::SetFS7IsPowerOn(bool Value) {
    if(FS7IsPowerOn != Value) {
        if(Value)
            log_hint("SetFS7IsPowerOn: Servo power is on"); // LVL_HINT
        else
            log_hint("SetFS7IsPowerOn: Servo power is off"); // LVL_HINT
    }
    FS7IsPowerOn = Value;
}

void TServo::SetFS7IsAutoMode(bool Value) {
    if(FS7IsAutoMode != Value) {
        if(Value)
            log_hint("SetFS7IsAutoMode: Servo Auto Mode is on"); // LVL_HINT
        else
            log_hint("SetFS7IsAutoMode: Servo Manual Mode is on"); // LVL_HINT
    }
    FS7IsAutoMode = Value;
}

void TServo::SetFS7IsConnected(bool Value) {
    FS7IsConnected = Value;
    if(vGetDataThread == nullptr)
        return;
    if(FS7IsConnected) {
        vGetDataThread->GetDataResume();
        log_hint("SetFS7IsConnected: Servo is connected, Getdata thread resumed"); // LVL_HINT
    }
    else {
        vGetDataThread->GetDataSuspend();
        log_hint("SetFS7IsConnected: Servo is disconnected, Getdata thread suspended"); // LVL_HINT
    }
}


int TServo::S7Write(const TDataRecord& AField, void* pData, bool Async) {
    std::lock_guard<std::mutex> lock(FMonitorObj);
    if(Async)
        FS7LastError = FS7Client.AsWriteArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);
    else
        FS7LastError = FS7Client.WriteArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);

    if(FS7LastError == 0) {
        if(Async)
            S7WaitCompletion();
    }
    else {
        log_nok("S7Write: Servo Write Action Error");
    }
    return FS7LastError;
}

// bool TServo::InitializeSnap7Api() {
//     // Placeholder for Snap7 API initialization code
//     // This should include loading the Snap7 library and initializing any necessary handles
//     // Return true if initialization is successful, false otherwise
//     return true;
// }

// void TServo::FinalizeSnap7Api() {
//     // Placeholder for Snap7 API finalization code
//     // This should include releasing any handles and unloading the Snap7 library
// }

void TServo::S7WaitCompletion(int ATimeout) {
    int Result;
    uint8_t AsMode = 0;

    ProcessMessages();

    switch(AsMode) {
    case amPolling:
    case amCallBack:
        do {
            ProcessMessages();
        }
        while(!FS7Client.CheckAsCompletion(&Result));
        break;
    case amEvent:
        Result = FS7Client.WaitAsCompletion(DefaultTimeout);
        break;
        // case amCallBack: // This case is commented out in the original Delphi code
        //     if (evJob.WaitFor(Timeout) == wrSignaled)
        //         Result = AsOpResult;
        //     else
        //         Result = errCliJobTimeout;
        //     break;
    }

    SetFS7LastError(Result);
}

//TServo::TThreadHeartbeat::TThreadHeartbeat() {
//    // Placeholder for heartbeat thread constructor
//    // This should include initializing any necessary variables and starting the heartbeat thread
//}
//
//TServo::TThreadHeartbeat::~TThreadHeartbeat() {
//    // Placeholder for heartbeat thread destructor
//    // This should include stopping the heartbeat thread and cleaning up any resources
//}
//
//void TServo::TThreadHeartbeat::HeartbeatSuspend() {
//    // Placeholder for suspending the heartbeat thread
//    // This should include pausing the heartbeat thread until it is resumed
//}
//
//void TServo::TThreadHeartbeat::Heartbeatexit() {
//    // Placeholder for exiting the heartbeat thread
//    // This should include gracefully terminating the heartbeat thread
//}
//
//TServo::TThreadGetData::TThreadGetData() {
//    // Placeholder for data retrieval thread constructor
//    // This should include initializing any necessary variables and starting the data retrieval thread
//}
//
//TServo::TThreadGetData::~TThreadGetData() {
//    // Placeholder for data retrieval thread destructor
//    // This should include stopping the data retrieval thread and cleaning up any resources
//}
//
//void TServo::TThreadGetData::GetDataexit() {
//    // Placeholder for exiting the data retrieval thread
//    // This should include gracefully terminating the data retrieval thread
//}

// Additional helper functions and classes can be defined here as needed
