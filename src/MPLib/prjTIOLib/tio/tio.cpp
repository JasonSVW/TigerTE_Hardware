// GEN BLOCK BEGIN Include
#define TSMP_IMPL
#include "TSMaster.h"
#include "MPLibrary.h"
#include "Database.h"
#include "TSMasterBaseInclude.h"
#include "Configuration.h"
#include "snap7.h"
#include "common.h"
#include "uPLC1200.h"
// GEN BLOCK END Include

//TS7Client* FS7Client = nullptr;


// CODE BLOCK BEGIN Variable demoVar MSwwLCw_
// 变量文档 "demoVar"
TMPVarDouble demoVar;
// CODE BLOCK END Variable demoVar

// CODE BLOCK BEGIN Timer DemoTimer MTAw
// 定时器文档 "DemoTimer"
TMPTimerMS DemoTimer;
// CODE BLOCK END Timer DemoTimer

// GEN BLOCK BEGIN Custom_Function
s32 demo_function(s32 A1, s32 A2);
// GEN BLOCK END Custom_Function

// CODE BLOCK BEGIN On_CAN_Rx On_CAN_Rx_Demo MCwtMSwyOTE_
// CAN报文接收事件 "On_CAN_Rx_Demo" 针对标识符 = 0x123
void on_can_rx_On_CAN_Rx_Demo(const TCAN* ACAN) { try {  // 针对标识符 = 0x123
// if (ACAN->FIdxChn != CH1) return; // if you want to filter channel

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_CAN_Rx On_CAN_Rx_Demo

// CODE BLOCK BEGIN On_CAN_Tx On_CAN_Tx_Demo MCwtMSwyOTE_
// CAN报文发送成功事件 "On_CAN_Tx_Demo" 针对标识符 = 0x123
void on_can_tx_On_CAN_Tx_Demo(const TCAN* ACAN) { try {  // 针对标识符 = 0x123
// if (ACAN->FIdxChn != CH1) return; // if you want to filter channel

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_CAN_Tx On_CAN_Tx_Demo

// CODE BLOCK BEGIN On_CAN_PreTx On_CAN_PreTx_Demo MCwtMSwyOTE_
// CAN报文预发送事件 "On_CAN_PreTx_Demo" 针对标识符 = 0x123
void on_can_pretx_On_CAN_PreTx_Demo(const PCAN ACAN) { try {  // 针对标识符 = 0x123
// if (ACAN->FIdxChn != CH1) return; // if you want to filter channel

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_CAN_PreTx On_CAN_PreTx_Demo

// CODE BLOCK BEGIN On_Var_Change On_Var_Change_demoVar ZGVtb1ZhciwtMQ__
// 变量变化事件 "On_Var_Change_demoVar" 针对变量 "demoVar" [On Written]
void on_var_change_On_Var_Change_demoVar(void) { try { // 变量 = demoVar

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Var_Change On_Var_Change_demoVar

// CODE BLOCK BEGIN On_Timer On_DemoTimer RGVtb1RpbWVy
// 定时器触发事件 "On_DemoTimer" for Timer DemoTimer
void on_timer_On_DemoTimer(void) { try { // 定时器 = DemoTimer

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Timer On_DemoTimer

// CODE BLOCK BEGIN On_Start On_Start
// 启动事件 "On_Start"
void on_start_On_Start(void) { try { // 程序启动事件
	//FS7Client = new TS7Client();
    vTIOConfig.GetConfigFile();
    vTIOConfig.InitIniFile();
    vTIOConfig.LoadConfigValue();

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Start On_Start

// CODE BLOCK BEGIN On_Stop On_Stop
// 停止事件 "On_Stop"
void on_stop_On_Stop(void) { try { // 程序停止事件
    if (nullptr != vServoObj) {
        app.ui_watchdog_enable(false);
        delete vServoObj;
        vServoObj = nullptr;
        app.ui_watchdog_enable(true);
    }
    //if (FS7Client != nullptr) {
    //    delete FS7Client;
    //    FS7Client = nullptr;
    //    log_ok("delete FS7Client");
    //}
    vTIOConfig.SaveConfig();
} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Stop On_Stop

// CODE BLOCK BEGIN Custom_Function demo_function czMyIEExLCBzMzIgQTI_
// 自定义函数 "demo_function"
s32 demo_function(s32 A1, s32 A2) { try { // 自定义函数: new demo
  return IDX_ERR_OK;
} catch (...) { log_nok("CRASH detected"); app.terminate_application(); return(IDX_ERR_MP_CODE_CRASH); }}
// CODE BLOCK END Custom_Function demo_function

// CODE BLOCK BEGIN Step_Function  MQ__
// 主step函数，执行周期 1 ms
void step(void) { try { // 周期 = 1 ms

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END Step_Function 

