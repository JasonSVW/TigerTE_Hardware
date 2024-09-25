#include "TSMaster.h"
#include "MPLibrary.h"
#include "Configuration.h"
#include "TSMasterBaseInclude.h"
#include <memory>
#include <string>
#include <vector>
#include "common.h"
#include "uPLC1200.h"

#define LIB_VERSION "2024.09.23"

// Variables definition
TTSApp app;
TTSCOM com;
TTSTest test;

// Templates Instantiation
template <>
void output<TCAN>(TCAN* canMsg) {
  com.transmit_can_async(canMsg);
}

template <>
void output<TLIN>(TLIN* linMsg) {
  com.transmit_lin_async(linMsg);
}

template <>
void output<TFlexRay>(TFlexRay* frMsg) {
  com.transmit_flexray_async(frMsg);
}

template <>
void output<TEthernetHeader>(TEthernetHeader* ethMsg) {
  com.transmit_ethernet_async(ethMsg);
}

// logger functions definition
#define TEMP_STR_LEN 1024
typedef char* va_list;
#ifndef __va_rounded_size
#define __va_rounded_size(TYPE) (((sizeof(TYPE)+sizeof(int)-1)/sizeof(int))*sizeof(int))
#endif

#ifndef va_start
#define va_start(AP, LASTARG)   (AP = ((char *)& (LASTARG) + __va_rounded_size(LASTARG)))
#endif

#ifndef va_arg
#define va_arg(AP, TYPE)        (AP += __va_rounded_size(TYPE), *((TYPE *)(AP - __va_rounded_size(TYPE))))
#endif

#ifndef va_end
#define va_end(AP)              (AP = (va_list)0 )
#endif

// Utility functions definition
void internal_log(const char* AFile, const char* AFunc, const s32 ALine, const TLogLevel ALevel, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  std::vector<char> buf(1024);
  int ret;
#if __cplusplus == 201103L
  while((ret = vsnprintf_s(&buf[0], buf.size(), fmt, ap)) == -1) {
#else
  // in VC++ version is 199711L, log("__cplusplus: %d\n", __cplusplus);
  while((ret = vsnprintf_s(&buf[0], buf.size(), buf.size(), fmt, ap)) == -1) {
#endif
    buf.resize(buf.size() * 2);
  }
  va_end(ap);
  if(ret == static_cast<int>(buf.size())) {
    buf[buf.size() - 1] = '\0';
  }
  app.debug_log(AFile, AFunc, ALine, &buf[0], ALevel);
}

void internal_test_log(const char* AFile, const char* AFunc, const s32 ALine, const TLogLevel ALevel, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  std::vector<char> buf(1024);
  int ret;
#if __cplusplus == 201103L
  while((ret = vsnprintf_s(&buf[0], buf.size(), fmt, ap)) == -1) {
#else
  while((ret = vsnprintf_s(&buf[0], buf.size(), buf.size(), fmt, ap)) == -1) {
#endif
    buf.resize(buf.size() * 2);
  }
  va_end(ap);
  if(ret == static_cast<int>(buf.size())) {
    buf[buf.size() - 1] = '\0';
  }
  test.debug_log_info(AFile, AFunc, ALine, &buf[0], ALevel);
}

void test_logCAN(const char* ADesc, PCAN ACAN, const TLogLevel ALevel) {
  char s[TEMP_STR_LEN];
  // channel, id, dlc, [data]
  if(ACAN->is_tx) {
    if(ACAN->is_data) {
      sprintf(s, "%s %d %03X Tx d %d [%02X %02X %02X %02X %02X %02X %02X %02X]", ADesc, ACAN->FIdxChn, ACAN->FIdentifier, ACAN->FDLC, ACAN->FData[0], ACAN->FData[1], ACAN->FData[2], ACAN->FData[3], ACAN->FData[4], ACAN->FData[5], ACAN->FData[6], ACAN->FData[7]);
    }
    else {
      sprintf(s, "%s %d %03X Tx r %d", ADesc, ACAN->FIdxChn, ACAN->FIdentifier, ACAN->FDLC);
    }
  }
  else {
    if(ACAN->is_data) {
      sprintf(s, "%s %d %03X Rx d %d [%02X %02X %02X %02X %02X %02X %02X %02X]", ADesc, ACAN->FIdxChn, ACAN->FIdentifier, ACAN->FDLC, ACAN->FData[0], ACAN->FData[1], ACAN->FData[2], ACAN->FData[3], ACAN->FData[4], ACAN->FData[5], ACAN->FData[6], ACAN->FData[7]);
    }
    else {
      sprintf(s, "%s %d %03X Rx r %d", ADesc, ACAN->FIdxChn, ACAN->FIdentifier, ACAN->FDLC);
    }
  }
  test.log_info(s, ALevel);
}

DLLEXPORT s32 __stdcall initialize_miniprogram(const PTSMasterConfiguration AConf) {
  app = AConf->FTSApp;
  com = AConf->FTSCOM;
  test = AConf->FTSTest;
  //load configuration files
  std::string vVersion = ".version";
  vMP_Name = GetCurrentModuleName();
  vVersion = vMP_Name + vVersion;
  vTIOConfig.InitConfigFile();
  vTIOConfig.LoadConfigFile();
  if(0 != app.set_system_var_string(vVersion.c_str(), LIB_VERSION)) {
    app.create_system_var(vVersion.c_str(), svtString, LIB_VERSION, "mp lib version.");
  }
  mp_initialize_servo_lib_initialize();
  return 0;

}

DLLEXPORT s32 __stdcall finalize_miniprogram(void) {
  //test_log("finalize_miniprogram");
  if(nullptr != vServoObj) {
    delete vServoObj;
    vServoObj = nullptr;
  }
  vTIOConfig.UpdateConfigFile();
  return 0;

}

// MP library functions definition

// Variables defintions
extern TMPVarDouble demoVar;

// Timers defintions
extern TMPTimerMS DemoTimer;

// Retrieve TSMP abilities
typedef s32(__stdcall* TRegTSMasterFunction)(const void* AObj, const char* AFuncType, const char* AFuncName, const char* AData, const void* AFuncPointer, const char* ADescription);
extern void step(void);
extern void on_can_rx_On_CAN_Rx_Demo(const TCAN * ACAN);
extern void on_can_tx_On_CAN_Tx_Demo(const TCAN * ACAN);
extern void on_can_pretx_On_CAN_PreTx_Demo(const PCAN ACAN);
extern void on_var_change_On_Var_Change_demoVar(void);
extern void on_timer_On_DemoTimer(void);
extern void on_start_On_Start(void);
extern void on_stop_On_Stop(void);
extern s32 demo_function(s32 A1, s32 A2);
DLLEXPORT s32 __stdcall retrieve_mp_abilities(const void* AObj, const TRegTSMasterFunction AReg) {
#define TSMASTER_VERSION "2024.7.30.1156"
  if(!AReg(AObj, "check_mp_internal", "version", TSMASTER_VERSION, 0, "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_app", (void*) sizeof(TTSMasterConfiguration), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tcan", (void*) sizeof(TCAN), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tcanfd", (void*) sizeof(TCANFD), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tlin", (void*) sizeof(TLIN), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tflexray", (void*) sizeof(TFlexRay), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tethernetheader", (void*) sizeof(TEthernetHeader), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarInt", (void*) sizeof(TMPVarInt), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarDouble", (void*) sizeof(TMPVarDouble), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarString", (void*) sizeof(TMPVarString), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarCAN", (void*) sizeof(TMPVarCAN), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarCANFD", (void*) sizeof(TMPVarCANFD), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarLIN", (void*) sizeof(TMPVarLIN), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TLIBTSMapping", (void*) sizeof(TLIBTSMapping), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TLIBSystemVarDef", (void*) sizeof(TLIBSystemVarDef), "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "auto_start", "0", 0, "")) return -1;
  if(!AReg(AObj, "check_mp_internal", "addr_conf", "app", &app, "")) return -1;
  if(!AReg(AObj, "step_function", "step", "1", reinterpret_cast<const void*>(&step), "")) return -1;
  if(!AReg(AObj, "var", "demoVar", "1,MA__,", reinterpret_cast<const void*>(&demoVar), "")) return -1;
  if(!AReg(AObj, "timer", "DemoTimer", "100", reinterpret_cast<const void*>(&DemoTimer), "")) return -1;
  if(!AReg(AObj, "on_can_rx_callback", "on_can_rx_On_CAN_Rx_Demo", "291,-1,0", reinterpret_cast<const void*>(&on_can_rx_On_CAN_Rx_Demo), "")) return -1;
  if(!AReg(AObj, "on_can_tx_callback", "on_can_tx_On_CAN_Tx_Demo", "291,-1,0", reinterpret_cast<const void*>(&on_can_tx_On_CAN_Tx_Demo), "")) return -1;
  if(!AReg(AObj, "on_can_pretx_callback", "on_can_pretx_On_CAN_PreTx_Demo", "291,-1,0", reinterpret_cast<const void*>(&on_can_pretx_On_CAN_PreTx_Demo), "")) return -1;
  if(!AReg(AObj, "on_var_change_callback", "on_var_change_On_Var_Change_demoVar", "demoVar", reinterpret_cast<const void*>(&on_var_change_On_Var_Change_demoVar), "")) return -1;
  if(!AReg(AObj, "on_timer_callback", "on_timer_On_DemoTimer", "DemoTimer", reinterpret_cast<const void*>(&on_timer_On_DemoTimer), "")) return -1;
  if(!AReg(AObj, "on_start_callback", "on_start_On_Start", "", reinterpret_cast<const void*>(&on_start_On_Start), "")) return -1;
  if(!AReg(AObj, "on_stop_callback", "on_stop_On_Stop", "", reinterpret_cast<const void*>(&on_stop_On_Stop), "")) return -1;
  if(!AReg(AObj, "on_custom_callback", "demo_function", "s32 A1, s32 A2", reinterpret_cast<const void*>(&demo_function), "new demo")) return -1;

  // servo
  if(!AReg(AObj, "on_custom_callback", "servo_create", "void", reinterpret_cast<const void*>(&servo_create), "create servo object"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "servo_destroy", "void", reinterpret_cast<const void*>(&servo_destroy), "destroy servo object"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "servo_connect", "const char* AIPAddr", reinterpret_cast<const void*>(&servo_connect), "connect with servo device"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "servo_disconnect", "void", reinterpret_cast<const void*>(&servo_disconnect), "disconnect with servo device"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "servo_clear_fault", "void", reinterpret_cast<const void*>(&servo_clear_fault), "clear servo fault"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_servo_limit", "const float AMaxPositionMM, const float AMinPositionMM, const float AMaxSpeedMMpS", reinterpret_cast<const void*>(&pedal_servo_limit), "set servo limit"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_servo_on", "const bool AEnable", reinterpret_cast<const void*>(&pedal_servo_on), "enable/disable pedal servo"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_enable_run", "const bool AEnable", reinterpret_cast<const void*>(&pedal_enable_run), "enable/disable pedal servo run"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_step_syn", "const float ARelPositionMM, const float ASpeedMMpS, const u32 ATimeout", reinterpret_cast<const void*>(&pedal_go_step_syn), "pedal step synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_step_asyn", "const float ARelPositionMM, const float ASpeedMMpS", reinterpret_cast<const void*>(&pedal_go_step_asyn), "pedal step asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_position_syn", "const float AAbsPositionMM, const float ASpeedMMpS, const u32 ATimeout", reinterpret_cast<const void*>(&pedal_go_position_syn), "pedal go synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_position_asyn", "const float AAbsPositionMM, const float ASpeedMMpS ", reinterpret_cast<const void*>(&pedal_go_position_asyn), "pedal go asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_position_manual_mode_asyn", "const float AAbsPositionMM, const float ASpeedMMpS ", reinterpret_cast<const void*>(&pedal_go_position_manual_mode_asyn), "pedal go asynchronouslly in manual mode(used for UI control)"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_step_percent_syn", "const float ARelPositionPercent, const float ASpeedMMpS, const u32 ATimeout", reinterpret_cast<const void*>(&pedal_go_step_percent_syn), "pedal percent step synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_step_percent_asyn", "const float ARelPositionPercent, const float ASpeedMMpS", reinterpret_cast<const void*>(&pedal_go_step_percent_asyn), "pedal percent step asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_position_percent_syn", "const float AAbsPositionPercent, const float ASpeedMMpS, const u32 ATimeout", reinterpret_cast<const void*>(&pedal_go_position_percent_syn), "pedal go percent position synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_position_percent_asyn", "const float AAbsPositionPercent, const float ASpeedMMpS ", reinterpret_cast<const void*>(&pedal_go_position_percent_asyn), "pedal go percent position asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_home_syn", "const u32 ATimeout", reinterpret_cast<const void*>(&pedal_go_home_syn), "pedal go to zero synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_home_asyn", "void", reinterpret_cast<const void*>(&pedal_go_home_asyn), "pedal go to zero synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_set_home", "const u32 ATimeout", reinterpret_cast<const void*>(&pedal_set_home), "set pedal zero position synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_go_auto_mode", "const bool AEnable", reinterpret_cast<const void*>(&pedal_go_auto_mode), "enable/disable pedal controlled by system varialbe tio.PedalTargetPosition or tio.PedalTargetPercent and tio.PedalTargetSpeed"))  return -1;

  if(!AReg(AObj, "on_custom_callback", "rotate_servo_limit", "const float AMaxDegree, const float AMinDegree, const float AMaxSpeedDpS", reinterpret_cast<const void*>(&rotate_servo_limit), "set servo limit"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_servo_on", "const bool AEnable", reinterpret_cast<const void*>(&rotate_servo_on), "enable/disable rotate servo"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_enable_run", "const bool AEnable", reinterpret_cast<const void*>(&rotate_enable_run), "enable/disable rotate servo run"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_step_syn", "const float ARelDegree, const float ASpeedDpS, const u32 ATimeout", reinterpret_cast<const void*>(&rotate_go_step_syn), "rotate step synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_step_asyn", "const float ARelDegree, const float ASpeedDpS", reinterpret_cast<const void*>(&rotate_go_step_asyn), "rotate step asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_position_syn", "const float AAbsDegree, const float ASpeedDpS, const u32 ATimeout", reinterpret_cast<const void*>(&rotate_go_position_syn), "rotate go synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_position_asyn", "const float AAbsDegree, const float ASpeedDpS ", reinterpret_cast<const void*>(&rotate_go_position_asyn), "rotate go asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_home_syn", "const u32 ATimeout", reinterpret_cast<const void*>(&rotate_go_home_syn), "rotate go to zero synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_home_asyn", "void", reinterpret_cast<const void*>(&rotate_go_home_asyn), "rotate go to zero synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_set_home", "const u32 ATimeout", reinterpret_cast<const void*>(&rotate_set_home), "set rotate zero position synchronouslly"))  return -1;

  if(!AReg(AObj, "on_custom_callback", "rotate_go_slope_step_syn", "const float ARelGradPercent,const u32 ATimeout", reinterpret_cast<const void*>(&rotate_go_slope_step_syn), "go a step slope relatively synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_slope_step_asyn", "const float ARelGradPercent", reinterpret_cast<const void*>(&rotate_go_slope_step_asyn), "go a step slope relatively asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_slope_syn", "const float AAbsGradPercent,const u32 ATimeout", reinterpret_cast<const void*>(&rotate_go_slope_syn), "go to absolutley slope synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_slope_asyn", "const float AAbsGradPercent", reinterpret_cast<const void*>(&rotate_go_slope_asyn), "go to absolutley slope asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_mount_position_syn", "const u32 ATimeout", reinterpret_cast<const void*>(&rotate_go_mount_position_syn), "go to the mounting position synchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_go_mount_position_asyn", "void", reinterpret_cast<const void*>(&rotate_go_mount_position_asyn), "go to the mounting position asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "rotate_set_slope_speed", "const float ASpeedDpS", reinterpret_cast<const void*>(&rotate_set_slope_speed), "set the running speed of rotate servo in slope set mode"))  return -1;

  if(!AReg(AObj, "on_custom_callback", "air_cylinder_push_out", "void", reinterpret_cast<const void*>(&air_cylinder_push_out), "air cylinder push out"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "air_cylinder_push_back", "void", reinterpret_cast<const void*>(&air_cylinder_push_back), "air cylinder push back"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "air_cylinder_push_pressure", "const float ATargetPressureBar", reinterpret_cast<const void*>(&air_cylinder_push_pressure), "set air cylinder pressure"))  return -1;

  if(!AReg(AObj, "on_custom_callback", "turntable_enable_control", "void", reinterpret_cast<const void*>(&turntable_enable_control), "enable turntable controlled by api"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "turntable_disable_control", "void", reinterpret_cast<const void*>(&turntable_disable_control), "disable turntable controlled by api"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "turntable_run_speed_rpm_asyn", "const float ATargetSpeedRPM", reinterpret_cast<const void*>(&turntable_run_speed_rpm_asyn), "set and run turntable with target speed asynchronouslly, unit: rpm"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "turntable_run_speed_rpm_syn", "const float ATargetSpeedRPM, const u32 ATimeout", reinterpret_cast<const void*>(&turntable_run_speed_rpm_syn), "set and run turntable with target speed synchronouslly, unit: rpm"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "turntable_run_speed_dps_asyn", "const float ATargetSpeedDPS", reinterpret_cast<const void*>(&turntable_run_speed_dps_asyn), "set and run turntable with target speed asynchronouslly, unit: deg/s"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "turntable_run_speed_dps_syn", "const float ATargetSpeedDPS, const u32 ATimeout", reinterpret_cast<const void*>(&turntable_run_speed_dps_syn), "set and run turntable with target speed synchronouslly, unit: deg/s"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "turntable_run_centrifugal_acc_asyn", "const float ATargetAccG, const float AArmLengthMM", reinterpret_cast<const void*>(&turntable_run_centrifugal_acc_asyn), "set and run turntable with target acc asynchronouslly, unit: g"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "turntable_run_centrifugal_acc_syn", "const float ATargetAccG, const float AArmLengthMM, const u32 ATimeout", reinterpret_cast<const void*>(&turntable_run_centrifugal_acc_syn), "set and run turntable with target acc synchronouslly, unit: g"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "turntable_stop_run_asyn", "void", reinterpret_cast<const void*>(&turntable_stop_run_asyn), "set turntable speed to zero asynchronouslly"))  return -1;
  if(!AReg(AObj, "on_custom_callback", "turntable_stop_run_syn", "const u32 ATimeout", reinterpret_cast<const void*>(&turntable_stop_run_syn), "set turntable speed to zero synchronouslly"))  return -1;
  // pump station
  if(!AReg(AObj, "on_custom_callback", "ps_power_on", "const u32 ATimeout", reinterpret_cast<const void*>(&ps_power_on), "synchronouslly set pump station system to power on."))  return -1;
  if(!AReg(AObj, "on_custom_callback", "ps_power_off", "const u32 ATimeout", reinterpret_cast<const void*>(&ps_power_off), "synchronouslly set pump station system to power off."))  return -1;
  if(!AReg(AObj, "on_custom_callback", "ps_reset", "void", reinterpret_cast<const void*>(&ps_reset), "reset pump station control system."))  return -1;
  if(!AReg(AObj, "on_custom_callback", "ps_set_pressure_asyn", "const float APressureBar, bool AEnableProtection", reinterpret_cast<const void*>(&ps_set_pressure_asyn), "set pump station out pressure to target asynchronouslly."))  return -1;
  if(!AReg(AObj, "on_custom_callback", "ps_set_pressure_syn", "const float APressureBar, const float AMaxTolBar, bool AEnableProtection, const u32 ATimeout", reinterpret_cast<const void*>(&ps_set_pressure_syn), "set pump station out pressure to target pressure with tollerance synchronouslly."))  return -1;

  // pedal force control//
  // 5
  if(!AReg(AObj, "on_custom_callback", "pedal_force_apllied_syn", "const float AForceN, const float ASpeedMMpS, const int ATimeout", reinterpret_cast<const void*>(&pedal_force_apllied_syn), "synchronouslly apllied force to target with target speed, api used in auto mode."))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_force_apllied_asyn", "const float AForceN, const float ASpeedMMpS", reinterpret_cast<const void*>(&pedal_force_apllied_asyn), "Asynchronouslly apllied force to target with target speed, api used in auto mode."))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_force_manual_mode_apllied_syn", "const float AForceN, const float ASpeedMMpS, const int ATimeout", reinterpret_cast<const void*>(&pedal_force_manual_mode_apllied_syn), "synchronouslly apllied force to target with target speed, api used in manual mode."))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_force_manual_mode_apllied_asyn", "const float AForceN, const float ASpeedMMpS", reinterpret_cast<const void*>(&pedal_force_manual_mode_apllied_asyn), "Asynchronouslly apllied force to target with target speed, api used in manual mode."))  return -1;
  if(!AReg(AObj, "on_custom_callback", "pedal_force_excute_calibration", "const float APostionStepMM, const float ASpeedMMpS", reinterpret_cast<const void*>(&pedal_force_excute_calibration), "Calibrated the relation 1-D table of MC Pressure vs pedal postion."))  return -1;
  // MP library functions
  // return 66;
  return 72;
}
