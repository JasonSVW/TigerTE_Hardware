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
#include <cstddef> 
#include <chrono>
// for std::size_t
#include <cstdint>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "snap7.h"

const double pi = 3.14159265358979323846f;
const std::size_t TS7BufferSize = 0xFFFF + 1;

typedef unsigned char TS7Buffer[TS7BufferSize];
typedef unsigned char* PS7Buffer;

const int amPolling = 0;
const int amEvent = 1;
const int amCallBack = 2;
const int DefaultTimeout = 1000;
const float PositionMaxTol = 0.1f;

typedef enum { plcPedal = 1, plcPedalSlope = 2, plcPedalCylinder = 3, plcTurnTable = 4, plcPumpStation = 5 } TPLCType;

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

class TServo {
private:
    std::mutex FMonitorObj;
    TS7Client FS7Client;
    TS7Helper S7;
    TS7Buffer FS7Buffer;
    TPLCType FPLCType;
    int FS7LastError;
    bool FS7IsHandShaked;
    bool FS7IsPowerOn;
    bool FS7IsOnlyPedal;
    bool FS7WithAirCylinder;
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
    float FS2MountPosition;
    float FS3TargetCurrent;
    float FS1TargetPositionManual;
    float FS1TargetSpeedManual;
    float FS2TargetPositionManual;
    float FS2TargetSpeedManual;
    float FS1TargetPositionAuto;
    float FS1TargetSpeedAuto;
    float FS2TargetPositionAuto;
    float FS2TargetSpeedAuto;
    float FS3MCMaxPressure;
    float FS3P2AFactor;
    float FS3P2AOffset;
    //add for pump station
    float FPSTargetPressure;
    float FPSMaxPressure;
    float FPSActPressure;
    float FPSActFlow;
    float FPSPumpPressure;
    float FPSReserviorPressure;
    bool FPSIsPowerOn;
    bool FPSIsFault;
    bool FPSIsPumpRunning;
    bool FPSIsReliefValvePowerOn;
    bool FPSIsReserviorValvePowerOn;
    bool FPSIsProportionalValvePowerOn;
    bool FPSIsFanRunning;
    // related with multithread
    std::thread HeartbeatThread;
    std::atomic<bool> HeartbeatRunning;
    //std::atomic<bool> HeartbeatConnected;
    std::atomic<int> HeartbeatFailedReads;
    std::mutex heartbeat_mutex;
    std::condition_variable heartbeat_cv;
    std::thread GetDataThread;
    std::atomic<bool> GetDataRunning;
    //std::atomic<bool> GetDataConnected;
    std::atomic<int> GetDataFailedReads;
    std::mutex getdata_mutex;
    std::condition_variable getdata_cv;

public:
    //bool FSnap7IsLoaded;
    std::string FRemoteAddress;
    bool FS7IsConnected;
    float FS1MaxSpeed;
    float FS1MaxPosition;
    float FS1MinPosition;
    float FS2MaxSpeed;
    float FS2MaxPosition;
    float FS2MinPosition;
    bool FPedalIsSysMode;
    bool FS7IsAutoMode;
    bool FS7IsFault;
    float FS2SlopSpeed;
    bool FS1IsServoOn;

private:
    //int S7Write(const TDataRecord& AField, const void* pData, bool Async);
    void HeartbeatStartThread();
    void HeartbeatStopThread();
    void HeartbeatThreadProcess();
    void GetDataStartThread();
    void GetDataStopThread();
    void GetDataThreadProcess();
    int S7Write(const TDataRecord& AField, void* pData, bool Async);
    int S7Read(const TDataRecord& AField, void* pData, bool Async);
    void S7WaitCompletion(int ATimeout = DefaultTimeout);
    void RegisterSystemVars(void);
    void UnregisterSystemVars(void);
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
    //add for Pump Control
    void SetFPSTargetPressure(float Value);
    void SetFPSMaxPressure(float Value);
    void SetFPSActPressure(float Value);
    void SetFPSActFlow(float Value);
    void SetFPSPumpPressure(float Value);
    void SetFPSReserviorPressure(float Value);
    void SetFPSIsPowerOn(bool AEnable);
    void SetFPSIsFault(bool AEnable);
    void SetFPSIsPumpRunning(bool AEnable);
    void SetFPSIsReliefValvePowerOn(bool AEnable);
    void SetFPSIsReserviorValvePowerOn(bool AEnable);
    void SetFPSIsProportionalValvePowerOn(bool AEnable);
    void SetFPSIsFanRunning(bool AEnable);


public:
    TServo(TPLCType APLCType, bool AOnlyPedalServo);
    ~TServo();
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
    //add for pump servo
    int PS_Set_Pressure_Asyn(float APressureBar);
    int PS_Set_Pressure_Syn(float APressureBar, float AMaxTol, int ATimeout);
    int PS_PowerOn(int ATimeout);
    int PS_PowerOff(int ATimeout);
    int PS_Reset();

    int S7_GetAllData();
};

extern TServo* vServoObj;
/*mp run initialize function*/
void mp_initialize_servo_lib_initialize(void);

/*mp api function*/
int servo_check();
int servo_create();
int servo_destroy();
int servo_connect(const char* AIPAddr);
int servo_disconnect();
int servo_clear_fault();
int pedal_servo_limit(float AMaxPositionMM, float AMinPositionMM, float AMaxSpeedMMpS);
int pedal_servo_on(bool AEnable);
int pedal_enable_run(bool AEnable);
int pedal_go_step_syn(float ARelPositionMM, float ASpeedMMpS, int ATimeout);
int pedal_go_step_asyn(float ARelPositionMM, float ASpeedMMpS);
int pedal_go_position_syn(float AAbsPositionMM, float ASpeedMMpS, int ATimeout);
int pedal_go_position_asyn(float AAbsPositionMM, float ASpeedMMpS);
int pedal_sys_position_asyn(float AAbsPositionMM, float ASpeedMMpS);
int pedal_go_step_percent_syn(float ARelPositionPercent, float ASpeedMMpS, int ATimeout);
int pedal_go_step_percent_asyn(float ARelPositionPercent, float ASpeedMMpS);
int pedal_go_position_percent_syn(float AAbsPositionPercent, float ASpeedMMpS, int ATimeout);
int pedal_go_position_percent_asyn(float AAbsPositionPercent, float ASpeedMMpS);
int pedal_sys_position_percent_asyn(float AAbsPositionPercent, float ASpeedMMpS);
int pedal_go_home_syn(int ATimeout);
int pedal_go_home_asyn();
int pedal_set_home(int ATimeout);
int pedal_go_auto_mode(bool AEanble);
int rotate_servo_limit(float AMaxDegree, float AMinDegree, float AMaxSpeedDpS);
int rotate_servo_on(bool AEnable);
int rotate_enable_run(bool AEnable);
int rotate_go_step_syn(float ARelDegree, float ASpeedDpS, int ATimeout);
int rotate_go_step_asyn(float ARelDegree, float ASpeedDpS);
int rotate_go_position_syn(float AAbsDegree, float ASpeedDpS, int ATimeout);
int rotate_go_position_asyn(float AAbsDegree, float ASpeedDpS);
int rotate_go_home_syn(int ATimeout);
int rotate_go_home_asyn();
int rotate_set_home(int ATimeout);
int rotate_go_slope_step_syn(float ARelGradPercent, int ATimeout);
int rotate_go_slope_step_asyn(float ARelGradPercent);
int rotate_go_slope_syn(float AAbsGradPercent, int ATimeout);
int rotate_go_slope_asyn(float AAbsGradPercent);
int rotate_go_mount_position_syn(int ATimeout);
int rotate_go_mount_position_asyn();
int rotate_set_slope_speed(float ASpeedDpS);
int air_cylinder_push_out();
int air_cylinder_push_back();
int air_cylinder_push_pressure(float ATargetPressureBar);
int turntable_enable_control();
int turntable_disable_control();
int turntable_run_speed_rpm_asyn(float ATargetSpeedRPM);
int turntable_run_speed_rpm_syn(float ATargetSpeedRPM, int ATimeout);
int turntable_run_speed_dps_asyn(float ATargetSpeedDPS);
int turntable_run_speed_dps_syn(float ATargetSpeedDPS, int ATimeout);
int turntable_run_centrifugal_acc_asyn(float ATargetAccelerationG, float AArmLengthMM);
int turntable_run_centrifugal_acc_syn(float ATargetAccelerationG, float AArmLengthMM, int ATimeout);
int turntable_stop_run_asyn();
int turntable_stop_run_syn(int ATimeout);
//add for pump servo
int ps_power_on(int ATimeout);
int ps_power_off(int ATimeout);
int ps_reset();
int ps_set_pressure_asyn(float APressureBar);
int ps_set_pressure_syn(float APressureBar, float AMaxTol, int ATimeout);

