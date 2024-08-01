#pragma once
#include <windows.h>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream>
#include <cmath>
#include <array>
#include "snap7.h"
#include <cstddef> 
#include <chrono>
// for std::size_t

#include <cstdint>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>




const double pi = 3.14159265358979323846;
const std::size_t TS7BufferSize = 0xFFFF + 1;

typedef unsigned char TS7Buffer[TS7BufferSize];
typedef unsigned char* PS7Buffer;

const int amPolling = 0;
const int amEvent = 1;
const int amCallBack = 2;
const int DefaultTimeout = 1000;
const float PositionMaxTol = 0.1;

struct TDataRecord {
    int Area;
    int DBNum;
    int Start;
    int Amount;
    int WordLen;
};

class TS7Helper {
private:
    int16_t GetInt(void* pval);
    void SetInt(void* pval, int16_t value);
    uint16_t GetWord(void* pval);
    void SetWord(void* pval, uint16_t value);
    int32_t GetDInt(void* pval);
    void SetDInt(void* pval, int32_t value);
    uint32_t GetDWord(void* pval);
    void SetDWord(void* pval, uint32_t value);
    std::tm GetDateTime(void* pval);
    void SetDateTime(void* pval, const std::tm& value);
    float GetReal(void* pval);
    void SetReal(void* pval, float value);
    bool GetBit(void* pval, int BitIndex);
    void SetBit(void* pval, int BitIndex, bool value);

public:
    void Reverse(void* pval, int S7Type);
    bool ValBit(void* pval, int BitIndex) { return GetBit(pval, BitIndex); }
    void ValBit(void* pval, int BitIndex, bool value) { SetBit(pval, BitIndex, value); }
    int16_t ValInt(void* pval) { return GetInt(pval); }
    void ValInt(void* pval, int16_t value) { SetInt(pval, value); }
    int32_t ValDInt(void* pval) { return GetDInt(pval); }
    void ValDInt(void* pval, int32_t value) { SetDInt(pval, value); }
    uint16_t ValWord(void* pval) { return GetWord(pval); }
    void ValWord(void* pval, uint16_t value) { SetWord(pval, value); }
    uint32_t ValDWord(void* pval) { return GetDWord(pval); }
    void ValDWord(void* pval, uint32_t value) { SetDWord(pval, value); }
    float ValReal(void* pval) { return GetReal(pval); }
    void ValReal(void* pval, float value) { SetReal(pval, value); }
    std::tm ValDateTime(void* pval) { return GetDateTime(pval); }
    void ValDateTime(void* pval, const std::tm& value) { SetDateTime(pval, value); }
};

class TThreadHeartbeat {
public:
    TThreadHeartbeat();
    ~TThreadHeartbeat();

    void HeartbeatResume();
    void HeartbeatSuspend();
    void Heartbeatexit();

private:
    void Execute();
    int S7_Heartbeat();

    std::thread heartbeatThread;
    std::mutex mutex;
    std::condition_variable condition;
    std::atomic<bool> terminated;
    std::atomic<bool> suspended;
    std::atomic<bool> finished;
    std::atomic<int> errorCount;
    std::atomic<int> exitCount;
    // Assuming vServoObj and other dependencies are defined elsewhere
    // Example:
    // TServo* vServoObj;
    // int AddrSetHandShake;
};



class TThreadGetData {
public:
    TThreadGetData();
    ~TThreadGetData();

    void GetDataResume();
    void GetDataSuspend();
    void GetDataexit();

private:
    void Execute();
    int S7_GetData();

    std::thread getDataThread;
    std::mutex mutex;
    std::condition_variable condition;
    std::atomic<bool> terminated;
    std::atomic<bool> suspended;
    std::atomic<bool> finished;
    std::atomic<int> errorCount;
    std::atomic<int> exitCount;
    // Assuming vServoObj and other dependencies are defined elsewhere
    // Example:
    // TServo* vServoObj;
};

class TServo {
public:
    std::mutex FMonitorObj;
    TS7Client FS7Client;
    TS7Helper S7;
    TS7Buffer FS7Buffer;
    int FS7LastError;
    bool FS7IsConnected;
    bool FS7IsHandShaked;
    bool FS7IsPowerOn;
    bool FS7IsAutoMode;
    bool FS7IsFault;
    bool FS7IsOnlyPedal;
    bool FS7WithAirCylinder;
    bool FS1IsServoOn;
    bool FS1ZeroExisted;
    bool FS1IsReady;
    bool FS1RunFinished;
    bool FS1IsFault;
    bool FS2IsServoOn;
    bool FS2ZeroExisted;
    bool FS2IsReady;
    bool FS2RunFinished;
    bool FS2IsFault;
    float FS1ActPosition;
    float FS1ActSpeed;
    float FS2ActPosition;
    float FS2ActPositionGrad;
    float FS2ActSpeed;
    float FS1MaxSpeed;
    float FS1MaxPosition;
    float FS1MinPosition;
    float FS2MaxSpeed;
    float FS2MaxPosition;
    float FS2MinPosition;
    float FS2MountPosition;
    float FS2SlopSpeed;
    float FS3TargetCurrent;
    float FS1TargetPositionManual;
    float FS1TargetSpeedManual;
    float FS2TargetPositionManual;
    float FS2TargetSpeedManual;
    float FS1TargetPositionAuto;
    float FS1TargetSpeedAuto;
    float FS2TargetPositionAuto;
    float FS2TargetSpeedAuto;
    bool FPedalIsSysMode;
    float FS3MCMaxPressure;
    float FS3P2AFactor;
    float FS3P2AOffset;

    //int S7Write(const TDataRecord& AField, const void* pData, bool Async);
    int S7Write(const TDataRecord& AField, void* pData, bool Async);
    int S7Read(const TDataRecord& AField, void* pData, bool Async);
    void S7WaitCompletion(int ATimeout = DefaultTimeout);
    void RegisterSystemVars(void);
    void UnregisterSystemVars(void);


public:
    std::string FRemoteAddress;
    bool FSnap7IsLoaded;

    TServo(bool AOnlyPedalServo);
    ~TServo();
    void SetFS7LastError(int Value);
    void SetFS7IsConnected(bool Value);
    void SetFS1IsFault(bool Value);
    void SetFS1IsReady(bool Value);
    void SetFS1RunFinished(bool Value);
    void SetFS1IsServoOn(bool Value);
    void SetFS1ZeroExisted(bool Value);
    void SetFS2IsFault(bool Value);
    void SetFS2IsReady(bool Value);
    void SetFS2RunFinished(bool Value);
    void SetFS2IsServoOn(bool Value);
    void SetFS2ZeroExisted(bool Value);
    void SetFS7IsFault(bool Value);
    void SetFS7IsHandShaked(bool Value);
    void SetFS7IsPowerOn(bool Value);
    void SetFS1ActPosition(float Value);
    void SetFS1ActSpeed(float Value);
    void SetFS2ActPosition(float Value);
    void SetFS2ActPositionGrad(float Value);
    void SetFS2ActSpeed(float Value);
    void SetFS1TargetPositionAuto(float Value);
    void SetFS1TargetPositionManual(float Value);
    void SetFS1TargetSpeedAuto(float Value);
    void SetFS1TargetSpeedManual(float Value);
    void SetFS2TargetPositionAuto(float Value);
    void SetFS2TargetPositionManual(float Value);
    void SetFS2TargetSpeedAuto(float Value);
    void SetFS2TargetSpeedManual(float Value);
    void SetFS7IsAutoMode(bool Value);
    void SetFS1MaxSpeed(float Value);
    void SetFS1MaxPosition(float Value);
    void SetFS1MinPosition(float Value);
    void SetFS2MaxSpeed(float Value);
    void SetFS2MaxPosition(float Value);
    void SetFS2MinPosition(float Value);
    void SetFS2MountPosition(float Value);
    void SetFS2SlopSpeed(float Value);
    void SetFS7IsOnlyPedal(bool Value);
    void SetFS7WithAirCylinder(bool Value);
    void SetFPedalIsSysMode(bool AEnable);
    void SetFS3MCMaxPressure(float Value);
    void SetFS3P2AFactor(float Value);
    void SetFS3P2AOffset(float Value);
    void SetFS3TargetCurrent(float Value);

    int S7_Connection();
    int S7_Disconnection();
    int S7_ClearFault(int ATimeout = DefaultTimeout);
    int S7_HandsShake(bool AEnable, int ATimeout = DefaultTimeout);
    int S1_ServoON(bool AEnable, int ATimeout = DefaultTimeout);
    int S1_Run_On(int ATimeout = DefaultTimeout);
    int S1_Run_Off(int ATimeout = DefaultTimeout);
    int S1_Manual_JogOut();
    int S1_Manual_JogIn();
    int S1_GoZero_Asyn();
    int S1_GoZero_Syn(int ATimeout = DefaultTimeout);
    int S1_SetZero(int ATimeout = DefaultTimeout);
    int S1_GoAbsPos_AutoMode_Asyn(float AAbsPosMM, float ASpeedMMS);
    int S1_GoAbsPos_AutoMode_Syn(float AAbsPosMM, float ASpeedMMS, int ATimeout = DefaultTimeout);
    int S1_RunSpd_AutoMode_Asyn(float ASpeedRPM);
    int S1_RunSpd_AutoMode_Syn(float ASpeedRPM, int ATimeout = DefaultTimeout);
    int S1_GoRelPos_AutoMode_Asyn(float ARelPosMM, float ASpeedMMS);
    int S1_GoRelPos_AutoMode_Syn(float ARelPosMM, float ASpeedMMS, int ATimeout = DefaultTimeout);
    int S1_GoAbsPos_MMode_Asyn(float AAbsPosMM, float ASpeedMMS);
    int S1_GoAbsPos_MMode_Syn(float AAbsPosMM, float ASpeedMMS, int ATimeout);
    int S1_GoRelPos_MMode_Asyn(float ARelPosMM, float ASpeedMMS);
    int S1_GoRelPos_MMode_Syn(float ARelPosMM, float ASpeedMMS, int ATimeout = DefaultTimeout);
    int S2_ServoON(bool AEnable, int ATimeout = DefaultTimeout);
    int S2_Run_On(int ATimeout = DefaultTimeout);
    int S2_Run_Off(int ATimeout = DefaultTimeout);
    int S2_Manual_JogOut();
    int S2_Manual_JogIn();
    int S2_GoZero_Asyn();
    int S2_GoZero_Syn(int ATimeout = DefaultTimeout);
    int S2_SetZero(int ATimeout = DefaultTimeout);
    int S2_GoAbsPos_AutoMode_Asyn(float AAbsPosDeg, float ASpeedDegS);
    int S2_GoAbsPos_AutoMode_Syn(float AAbsPosDeg, float ASpeedDegS, int ATimeout = DefaultTimeout);
    int S2_GoRelPos_AutoMode_Asyn(float ARelPosDeg, float ASpeedDegS);
    int S2_GoRelPos_AutoMode_Syn(float ARelPosDeg, float ASpeedDegS, int ATimeout = DefaultTimeout);
    int S2_GoAbsPos_MMode_Asyn(float AAbsPosDeg, float ASpeedDegS);
    int S2_GoAbsPos_MMode_Syn(float AAbsPosDeg, float ASpeedDegS, int ATimeout);
    int S2_GoRelPos_MMode_Asyn(float ARelPosDeg, float ASpeedDegS);
    int S2_GoRelPos_MMode_Syn(float ARelPosDeg, float ASpeedDegS, int ATimeout = DefaultTimeout);
    int S2_GoMountPos_AutoMode_Asyn();
    int S2_GoMountPos_AutoMode_Syn(int ATimeout = DefaultTimeout);
    int S2_GoAbsSlopGrad_AutoMode_Asyn(float AAbsGradPercent);
    int S2_GoAbsSlopGrad_AutoMode_Syn(float AAbsGradPercent, int ATimeout = DefaultTimeout);
    int S2_GoRelSlopGrad_AutoMode_Asyn(float ARelGradPercent);
    int S2_GoRelSlopGrad_AutoMode_Syn(float ARelGradPercent, int ATimeout = DefaultTimeout);
    int S2_GoMountPos_MMode_Asyn();
    int S2_GoMountPos_MMode_Syn(int ATimeout = DefaultTimeout);
    int S2_GoAbsSlopGrad_MMode_Asyn(float AAbsGradPercent);
    int S2_GoAbsSlopGrad_MMode_Syn(float AAbsGradPercent, int ATimeout);
    int S2_GoRelSlopGrad_MMode_Asyn(float ARelGradPercent);
    int S2_GoRelSlopGrad_MMode_Syn(float ARelGradPercent, int ATimeout = DefaultTimeout);
    int S3_Go_Out();
    int S3_Go_In();
    int S3_Set_Current(float ACurrentA);
    int S3_Set_Target_Pressure(float ATargetPressureBar);
    float S3_Pressure_Current(float APressure);
    int S7_GetAllData();
};

extern TServo* vServoObj;

