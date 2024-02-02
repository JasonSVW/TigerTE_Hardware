// GEN BLOCK BEGIN Include
#define TSMP_IMPL
#include "TSMaster.h"
#include "MPLibrary.h"
#include "Database.h"
#include "TSMasterBaseInclude.h"
#include "Configuration.h"
// GEN BLOCK END Include

// GEN BLOCK BEGIN Custom_Function
s32 demo_test(void);
// GEN BLOCK END Custom_Function

// CODE BLOCK BEGIN Custom_Function demo_test dm9pZA__
// 自定义函数 "demo_test"
s32 demo_test(void) { __try { // 自定义函数: 
test_log("information");

} __except (1) { log_nok("CRASH detected"); app.terminate_application(); return(IDX_ERR_MP_CODE_CRASH); }}
// CODE BLOCK END Custom_Function demo_test

// CODE BLOCK BEGIN Step_Function  NQ__
// 主step函数，执行周期 5 ms
void step(void) { __try { // 周期 = 5 ms

} __except (1) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END Step_Function 

