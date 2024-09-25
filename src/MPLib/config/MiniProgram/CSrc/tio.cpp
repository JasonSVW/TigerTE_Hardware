// GEN BLOCK BEGIN Include
#define TSMP_IMPL
#include "TSMaster.h"
#include "MPLibrary.h"
#include "Database.h"
#include "TSMasterBaseInclude.h"
#include "Configuration.h"
// GEN BLOCK END Include

// CODE BLOCK BEGIN Variable demoVar MSwwLCw_
// Variable Comment for "demoVar"
TMPVarDouble demoVar;
// CODE BLOCK END Variable demoVar

// CODE BLOCK BEGIN Timer DemoTimer MTAw
// Timer Comment for "DemoTimer"
TMPTimerMS DemoTimer;
// CODE BLOCK END Timer DemoTimer

// GEN BLOCK BEGIN Custom_Function
s32 demo_function(s32 A1, s32 A2);
// GEN BLOCK END Custom_Function

// CODE BLOCK BEGIN On_CAN_Rx On_CAN_Rx_Demo MCwtMSwyOTE_
// On CAN message reception handler "On_CAN_Rx_Demo" for identifier = 0x123
void on_can_rx_On_CAN_Rx_Demo(const TCAN* ACAN) { try {  // for identifier = 0x123
// if (ACAN->FIdxChn != CH1) return; // if you want to filter channel

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_CAN_Rx On_CAN_Rx_Demo

// CODE BLOCK BEGIN On_CAN_Tx On_CAN_Tx_Demo MCwtMSwyOTE_
// On CAN message transmission handler "On_CAN_Tx_Demo" for identifier = 0x123
void on_can_tx_On_CAN_Tx_Demo(const TCAN* ACAN) { try {  // for identifier = 0x123
// if (ACAN->FIdxChn != CH1) return; // if you want to filter channel

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_CAN_Tx On_CAN_Tx_Demo

// CODE BLOCK BEGIN On_CAN_PreTx On_CAN_PreTx_Demo MCwtMSwyOTE_
// On CAN message pre-transmission hack handler "On_CAN_PreTx_Demo" for identifier = 0x123
void on_can_pretx_On_CAN_PreTx_Demo(const PCAN ACAN) { try {  // for identifier = 0x123
// if (ACAN->FIdxChn != CH1) return; // if you want to filter channel

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_CAN_PreTx On_CAN_PreTx_Demo

// CODE BLOCK BEGIN On_Var_Change On_Var_Change_demoVar ZGVtb1ZhciwtMQ__
// On variable change handler "On_Var_Change_demoVar" for variable "demoVar" [On Written]
void on_var_change_On_Var_Change_demoVar(void) { try { // variable = demoVar

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Var_Change On_Var_Change_demoVar

// CODE BLOCK BEGIN On_Timer On_DemoTimer RGVtb1RpbWVy
// Timer event handler "On_DemoTimer" for Timer DemoTimer
void on_timer_On_DemoTimer(void) { try { // timer = DemoTimer

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Timer On_DemoTimer

// CODE BLOCK BEGIN On_Start On_Start
// On start handler "On_Start"
void on_start_On_Start(void) { try { // on start event

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Start On_Start

// CODE BLOCK BEGIN On_Stop On_Stop
// On stop handler "On_Stop"
void on_stop_On_Stop(void) { try { // on stop event

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END On_Stop On_Stop

// CODE BLOCK BEGIN Custom_Function demo_function czMyIEExLCBzMzIgQTI_
// Custom Function "demo_function"
s32 demo_function(s32 A1, s32 A2) { try { // Custom Function: new demo
  return IDX_ERR_OK;

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); return(IDX_ERR_MP_CODE_CRASH); }}
// CODE BLOCK END Custom_Function demo_function

// CODE BLOCK BEGIN Step_Function  MQ__
// Main step function being executed every 1 ms
void step(void) { try { // interval = 1 ms

} catch (...) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END Step_Function 

