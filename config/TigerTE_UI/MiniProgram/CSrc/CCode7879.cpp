// GEN BLOCK BEGIN Include
#define TSMP_IMPL
#include "TSMaster.h"
#include "MPLibrary.h"
#include "Database.h"
#include "TSMasterBaseInclude.h"
#include "Configuration.h"
// GEN BLOCK END Include

// CODE BLOCK BEGIN Step_Function  NQ__
// 主step函数，执行周期 5 ms
void step(void) { __try { // 周期 = 5 ms

} __except (1) { log_nok("CRASH detected"); app.terminate_application(); }}
// CODE BLOCK END Step_Function 

