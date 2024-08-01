#include "TSMasterBaseInclude.h"

DLLEXPORT void __stdcall write_api_document_auto(const void* AOpaque, const TWriteAPIDocumentFunc AAPIFunc, const TWriteAPIParaFunc AParaFunc){
  AAPIFunc(AOpaque, "demo_function", "tio", "bmV3IGRlbW8_", "", 2);
  AParaFunc(AOpaque, 0, "demo_function", "A1", false, "s32", "czMyIGlucHV0MSBmb3IgbmV3IGRlbW8_");
  AParaFunc(AOpaque, 1, "demo_function", "A2", false, "s32", "czMyIGlucHV0MiBmb3IgbmV3IGRlbW8_");
}
