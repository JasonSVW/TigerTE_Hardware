#include "TSMasterBaseInclude.h"
#include <string>
#include <vector>
#define MP_NAME "tio"

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

std::string base64_encode(const std::string& input) {
    std::string encoded;
    int val = 0, valb = -6;
    for (unsigned char c : input) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            encoded.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) encoded.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (encoded.size() % 4) encoded.push_back('=');
    return encoded;
}

DLLEXPORT void __stdcall write_api_document_auto(const void* AOpaque, const TWriteAPIDocumentFunc AAPIFunc, const TWriteAPIParaFunc AParaFunc){
  AAPIFunc(AOpaque, "demo_function", "tio", "bmV3IGRlbW8_", "", 2);
  AParaFunc(AOpaque, 0, "demo_function", "A1", false, "s32", "czMyIGlucHV0MSBmb3IgbmV3IGRlbW8_");
  AParaFunc(AOpaque, 1, "demo_function", "A2", false, "s32", "czMyIGlucHV0MiBmb3IgbmV3IGRlbW8_");

  //servo
  AAPIFunc(AOpaque, "servo_create", MP_NAME, base64_encode("create servo object to control servo device, when GUI is used, no need to create servo object").c_str(), base64_encode("tio.servo_create; //create servo object to control servo device,  when GUI is used, no need to create servo object").c_str(), 0);

  AAPIFunc(AOpaque, "servo_destroy", MP_NAME, base64_encode("destroy servo object, when GUI is used, do not destory servo object").c_str(), base64_encode("tio.servo_destroy; //destroy servo object, when GUI is used, do not destory servo object").c_str(), 0);

  AAPIFunc(AOpaque, "servo_disconnect", MP_NAME, base64_encode("disconnect servo device").c_str(), base64_encode("tio.servo_disconnect; //disconnect servo device").c_str(), 1);
  AParaFunc(AOpaque, 0, "servo_disconnect", "AIPAddr", true, "char *", base64_encode("servo Device IP").c_str());

  AAPIFunc(AOpaque, "servo_clear_fault", MP_NAME, base64_encode("clear device fault").c_str(), base64_encode("tio.servo_clear_fault; //clear device fault").c_str(), 0);

  AAPIFunc(AOpaque, "pedal_servo_limit", MP_NAME, base64_encode("set pedal servo limit").c_str(), base64_encode("tio.pedal_servo_limit(60,0,300); //set max position limit 40mm, min position 0mm,mas speed limit 300mm/s").c_str(), 3);
  AParaFunc(AOpaque, 0, "pedal_servo_limit", "AMaxPositionMM", true, "float", base64_encode("pedal max position limit(mm)").c_str());
  AParaFunc(AOpaque, 1, "pedal_servo_limit", "AMinPositionMM", true, "float", base64_encode("pedal min position limit(mm)").c_str());
  AParaFunc(AOpaque, 2, "pedal_servo_limit", "AMaxSpeedMMpS", true, "float", base64_encode("pedal max speed limit(mm/s)").c_str());

  AAPIFunc(AOpaque, "pedal_servo_on", MP_NAME, base64_encode("enable or disable pedal servo on").c_str(), base64_encode("tio.pedal_servo_on(true); //enable pedal servo on").c_str(), 1);
  AParaFunc(AOpaque, 0, "pedal_servo_on", "AEnable", true, "bool", base64_encode("enable or disable servo on").c_str());

  AAPIFunc(AOpaque, "pedal_enable_run", MP_NAME, base64_encode("enable or disable pedal servo run").c_str(), base64_encode("tio.pedal_enable_run(true); //enable pedal servo run").c_str(), 1);
  AParaFunc(AOpaque, 0, "pedal_enable_run", "AEnable", true, "bool", base64_encode("enable or disable servo run").c_str());

  AAPIFunc(AOpaque, "pedal_go_step_syn", MP_NAME, base64_encode("go step forward/backward relative with current position synchronouslly").c_str(), base64_encode("tio.pedal_go_step_syn(30,10,5000); //go 30mm forward with speed 10mm/s synchronouslly, time out is 5000ms").c_str(), 3);
  AParaFunc(AOpaque, 0, "pedal_go_step_syn", "ARelPositionMM", true, "float", base64_encode("pedal step (mm)").c_str());
  AParaFunc(AOpaque, 1, "pedal_go_step_syn", "ASpeedMMpS", true, "float", base64_encode("pedal speed(mm/s)").c_str());
  AParaFunc(AOpaque, 2, "pedal_go_step_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "pedal_go_step_asyn", MP_NAME, base64_encode("go step forward/backward relative with current position asynchronouslly").c_str(), base64_encode("tio.pedal_go_step_asyn(30,10); //go 30mm forward with speed 10mm/s synchronouslly").c_str(), 2);
  AParaFunc(AOpaque, 0, "pedal_go_step_asyn", "ARelPositionMM", true, "float", base64_encode("pedal step (mm)").c_str());
  AParaFunc(AOpaque, 1, "pedal_go_step_asyn", "ASpeedMMpS", true, "float", base64_encode("pedal speed(mm/s)").c_str());

  AAPIFunc(AOpaque, "pedal_go_position_syn", MP_NAME, base64_encode("go to position synchronouslly").c_str(), base64_encode("tio.pedal_go_position_syn(30,10,5000); //go to 30mm with speed 10mm/s synchronouslly, time out is 5000ms").c_str(), 3);
  AParaFunc(AOpaque, 0, "pedal_go_position_syn", "AAbsPositionMM", true, "float", base64_encode("pedal position (mm)").c_str());
  AParaFunc(AOpaque, 1, "pedal_go_position_syn", "ASpeedMMpS", true, "float", base64_encode("pedal speed(mm/s)").c_str());
  AParaFunc(AOpaque, 2, "pedal_go_position_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "pedal_go_position_asyn", MP_NAME, base64_encode("go to position asynchronouslly").c_str(), base64_encode("tio.pedal_go_position_asyn(30,10); //go 30mm forward with speed 10mm/s asynchronouslly").c_str(), 2);
  AParaFunc(AOpaque, 0, "pedal_go_position_asyn", "AAbsPositionMM", true, "float", base64_encode("pedal position (mm)").c_str());
  AParaFunc(AOpaque, 1, "pedal_go_position_asyn", "ASpeedMMpS", true, "float", base64_encode("pedal speed(mm/s)").c_str());

  AAPIFunc(AOpaque, "pedal_go_step_percent_syn", MP_NAME, base64_encode("go step forward/backward relative with current position synchronouslly").c_str(), base64_encode("tio.pedal_go_step_percent_syn(5,10,5000); //go 5% forward with speed 10mm/s synchronouslly, time out is 5000ms").c_str(), 3);
  AParaFunc(AOpaque, 0, "pedal_go_step_percent_syn", "ARelPositionPercent", true, "float", base64_encode("pedal step (%), the step(mm) is ARelPositionPercent * MaxPosition").c_str());
  AParaFunc(AOpaque, 1, "pedal_go_step_percent_syn", "ASpeedMMpS", true, "float", base64_encode("pedal speed(mm/s)").c_str());
  AParaFunc(AOpaque, 2, "pedal_go_step_percent_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "pedal_go_step_percent_asyn", MP_NAME, base64_encode("go step forward/backward relative with current position asynchronouslly").c_str(), base64_encode("tio.pedal_go_step_percent_asyn(5,10); //go 5% forward with speed 10mm/s synchronouslly").c_str(), 2);
  AParaFunc(AOpaque, 0, "pedal_go_step_percent_asyn", "ARelPositionPercent", true, "float", base64_encode("pedal step (%), the step(mm) is ARelPositionPercent * MaxPosition").c_str());
  AParaFunc(AOpaque, 1, "pedal_go_step_percent_asyn", "ASpeedMMpS", true, "float", base64_encode("pedal speed(mm/s)").c_str());

  AAPIFunc(AOpaque, "pedal_go_position_percent_syn", MP_NAME, base64_encode("go to position synchronouslly").c_str(), base64_encode("tio.pedal_go_position_percent_syn(30,10,5000); //go to 30% with speed 10mm/s synchronouslly, time out is 5000ms").c_str(), 3);
  AParaFunc(AOpaque, 0, "pedal_go_position_percent_syn", "AAbsPositionPercent", true, "float", base64_encode("pedal position (%), the position(mm) is AAbsPositionPercent * MaxPosition").c_str());
  AParaFunc(AOpaque, 1, "pedal_go_position_percent_syn", "ASpeedMMpS", true, "float", base64_encode("pedal speed(mm/s)").c_str());
  AParaFunc(AOpaque, 2, "pedal_go_position_percent_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "pedal_go_position_percent_asyn", MP_NAME, base64_encode("go to position asynchronouslly").c_str(), base64_encode("tio.pedal_go_position_percent_asyn(30,10); //go 30% forward with speed 10mm/s asynchronouslly").c_str(), 2);
  AParaFunc(AOpaque, 0, "pedal_go_position_percent_asyn", "AAbsPositionPercent", true, "float", base64_encode("pedal position (%), the position(mm) is AAbsPositionPercent * MaxPosition").c_str());
  AParaFunc(AOpaque, 1, "pedal_go_position_percent_asyn", "ASpeedMMpS", true, "float", base64_encode("pedal speed(mm/s)").c_str());

  AAPIFunc(AOpaque, "pedal_go_home_syn", MP_NAME, base64_encode("go to home synchronouslly").c_str(), base64_encode("tio.pedal_go_home_syn(5000); //go to home synchronouslly, time out is 5000ms").c_str(), 1);
  AParaFunc(AOpaque, 0, "pedal_go_home_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "pedal_go_home_asyn", MP_NAME, base64_encode("go to home asynchronouslly").c_str(), base64_encode("tio.pedal_go_home_asyn; //go to home asynchronouslly").c_str(), 0);

  AAPIFunc(AOpaque, "pedal_set_home", MP_NAME, base64_encode("set pedal zero point with timeout").c_str(), base64_encode("tio.pedal_set_home(5000); //set pedal zero point with timeout 5000ms").c_str(), 1);
  AParaFunc(AOpaque, 0, "pedal_set_home", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "pedal_go_auto_mode", MP_NAME, base64_encode("enable/disable pedal controlled by tio.PedalTargetPosition/PedalTargetPercent and tio.PedalTargetSpeed").c_str(), base64_encode("tio.pedal_go_auto_mode(true); //enable pedal controlled by system varialbe").c_str(), 1);
  AParaFunc(AOpaque, 0, "pedal_go_auto_mode", "AEnable", true, "bool", base64_encode("enable/disable pedal controlled by system varialbe").c_str());

  AAPIFunc(AOpaque, "rotate_servo_limit", MP_NAME, base64_encode("set rotate servo limit").c_str(), base64_encode("tio.rotate_servo_limit(30,-30,10); //set max position limit 30deg, min position -30deg,max speed limit 10deg/s").c_str(), 3);
  AParaFunc(AOpaque, 0, "rotate_servo_limit", "AMaxDegree", true, "float", base64_encode("max position limit(deg)").c_str());
  AParaFunc(AOpaque, 1, "rotate_servo_limit", "AMinDegree", true, "float", base64_encode("min position limit(deg)").c_str());
  AParaFunc(AOpaque, 2, "rotate_servo_limit", "AMaxSpeedDpS", true, "float", base64_encode("max speed limit(deg/s)").c_str());

  AAPIFunc(AOpaque, "rotate_servo_on", MP_NAME, base64_encode("enable or disable rotate servo on").c_str(), base64_encode("tio.rotate_servo_on(true); //enable rotate servo on").c_str(), 1);
  AParaFunc(AOpaque, 0, "rotate_servo_on", "AEnable", true, "bool", base64_encode("enable or disable servo on").c_str());

  AAPIFunc(AOpaque, "rotate_enable_run", MP_NAME, base64_encode("enable or disable rotate servo run").c_str(), base64_encode("tio.rotate_enable_run(true); //enable rotate servo run").c_str(), 1);
  AParaFunc(AOpaque, 0, "rotate_enable_run", "AEnable", true, "bool", base64_encode("enable or disable servo run").c_str());

  AAPIFunc(AOpaque, "rotate_go_step_syn", MP_NAME, base64_encode("go step forward/backward relative with current position synchronouslly").c_str(), base64_encode("tio.rotate_go_step_syn(10,10,5000); //go 10deg forward with speed 10deg/s synchronouslly, time out is 5000ms").c_str(), 3);
  AParaFunc(AOpaque, 0, "rotate_go_step_syn", "ARelDegree", true, "float", base64_encode("relative step(deg)").c_str());
  AParaFunc(AOpaque, 1, "rotate_go_step_syn", "ASpeedDpS", true, "float", base64_encode("rotate speed(deg/s)").c_str());
  AParaFunc(AOpaque, 2, "rotate_go_step_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "rotate_go_step_asyn", MP_NAME, base64_encode("go step forward/backward relative with current position asynchronouslly").c_str(), base64_encode("tio.rotate_go_step_asyn(10,10); //go 10deg forward with speed 10deg/s synchronouslly").c_str(), 2);
  AParaFunc(AOpaque, 0, "rotate_go_step_asyn", "ARelDegree", true, "float", base64_encode("relative step(deg)").c_str());
  AParaFunc(AOpaque, 1, "rotate_go_step_asyn", "ASpeedDpS", true, "float", base64_encode("rotate speed(deg/s)").c_str());

  AAPIFunc(AOpaque, "rotate_go_position_syn", MP_NAME, base64_encode("go to position synchronouslly").c_str(), base64_encode("tio.rotate_go_position_syn(30,10,5000); //go to 30deg with speed 10deg/s synchronouslly, time out is 5000ms").c_str(), 3);
  AParaFunc(AOpaque, 0, "rotate_go_position_syn", "AAbsDegree", true, "float", base64_encode("absolute position (deg)").c_str());
  AParaFunc(AOpaque, 1, "rotate_go_position_syn", "ASpeedDpS", true, "float", base64_encode("run speed(deg/s)").c_str());
  AParaFunc(AOpaque, 2, "rotate_go_position_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "rotate_go_position_asyn", MP_NAME, base64_encode("go to position asynchronouslly").c_str(), base64_encode("tio.rotate_go_position_asyn(10,10); //go 10deg forward with speed 10deg/s asynchronouslly").c_str(), 2);
  AParaFunc(AOpaque, 0, "rotate_go_position_asyn", "AAbsDegree", true, "float", base64_encode("absolute position (deg)").c_str());
  AParaFunc(AOpaque, 1, "rotate_go_position_asyn", "ASpeedDpS", true, "float", base64_encode("run speed(deg/s)").c_str());

  AAPIFunc(AOpaque, "rotate_go_home_syn", MP_NAME, base64_encode("go to home synchronouslly").c_str(), base64_encode("tio.rotate_go_home_syn(5000); //go to home synchronouslly, time out is 5000ms").c_str(), 1);
  AParaFunc(AOpaque, 0, "rotate_go_home_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "rotate_go_home_asyn", MP_NAME, base64_encode("go to home asynchronouslly").c_str(), base64_encode("tio.rotate_go_home_asyn; //go to home asynchronouslly").c_str(), 0);

  AAPIFunc(AOpaque, "rotate_set_home", MP_NAME, base64_encode("set rotate servo zero point with timeout").c_str(), base64_encode("tio.rotate_set_home(5000); //set rotate servo zero point with timeout 5000ms").c_str(), 1);
  AParaFunc(AOpaque, 0, "rotate_set_home", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "rotate_go_slope_step_syn", MP_NAME, base64_encode("go a step slope relatively synchronouslly").c_str(), base64_encode("tio.rotate_go_slope_step_syn(10,5000); //go to 10% forward synchronouslly, time out is 5000ms").c_str(), 2);
  AParaFunc(AOpaque, 0, "rotate_go_slope_step_syn", "ARelGradPercent", true, "float", base64_encode("relative step (%)").c_str());
  AParaFunc(AOpaque, 1, "rotate_go_slope_step_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "rotate_go_slope_step_asyn", MP_NAME, base64_encode("go a step slope relatively synchronouslly").c_str(), base64_encode("tio.rotate_go_slope_step_asyn(10); //go to 10% forward asynchronouslly").c_str(), 1);
  AParaFunc(AOpaque, 0, "rotate_go_slope_step_asyn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "rotate_go_slope_syn", MP_NAME, base64_encode("go to absolutley slope synchronouslly").c_str(), base64_encode("tio.rotate_go_slope_syn(10,5000); //go to the postition of absolute slope 10% synchronouslly, time out is 5000ms").c_str(), 2);
  AParaFunc(AOpaque, 0, "rotate_go_slope_syn", "AAbsGradPercent", true, "float", base64_encode("absolute slope (%)").c_str());
  AParaFunc(AOpaque, 1, "rotate_go_slope_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "rotate_go_slope_asyn", MP_NAME, base64_encode("ggo to absolutley slope asynchronouslly").c_str(), base64_encode("tio.rotate_go_slope_asyn(10); //go to the postition of absolute slope 10% asynchronouslly").c_str(), 1);
  AParaFunc(AOpaque, 0, "rotate_go_slope_asyn", "AAbsGradPercent", true, "float", base64_encode("absolute slope (%)").c_str());

  AAPIFunc(AOpaque, "rotate_go_mount_position_syn", MP_NAME, base64_encode("go to the mounting position synchronouslly").c_str(), base64_encode("tio.rotate_go_mount_position_syn(5000); //back to the mounting postition synchronouslly, time out is 5000ms").c_str(), 1);
  AParaFunc(AOpaque, 0, "rotate_go_mount_position_syn", "ATimeout", true, "u32", base64_encode("timeout(ms)").c_str());

  AAPIFunc(AOpaque, "rotate_go_mount_position_asyn", MP_NAME, base64_encode("go to the mounting position asynchronouslly").c_str(), base64_encode("tio.rotate_go_mount_position_asyn(); //back to the mounting postition asynchronouslly").c_str(), 0);

  AAPIFunc(AOpaque, "rotate_set_slope_speed", MP_NAME, base64_encode("set the running speed of rotate servo in slope set mode").c_str(), base64_encode("tio.rotate_set_slope_speed(5); //set the rotate speed is 5 degree/s when run to set slope").c_str(), 1);
  AParaFunc(AOpaque, 0, "rotate_set_slope_speed", "ASpeedDpS", true, "float", base64_encode("rotate speed (deg/s)").c_str());

  AAPIFunc(AOpaque, "air_cylinder_push_out", MP_NAME, base64_encode("air cylinder push out").c_str(), base64_encode("tio.air_cylinder_push_out(); //push out").c_str(), 0);

  AAPIFunc(AOpaque, "air_cylinder_push_back", MP_NAME, base64_encode("air cylinder push back").c_str(), base64_encode("tio.air_cylinder_push_back(); //push back").c_str(), 0);

  AAPIFunc(AOpaque, "air_cylinder_push_pressure", MP_NAME, base64_encode("air cylinder push back").c_str(), base64_encode("tio.air_cylinder_push_pressure(50); //set push pressure 50 bar").c_str(), 1);
  AParaFunc(AOpaque, 0, "air_cylinder_push_pressure", "ATargetPressureBar", true, "float", base64_encode("the target pressure(bar)").c_str());

  AAPIFunc(AOpaque, "turntable_enable_control", MP_NAME, base64_encode("enable turntable control").c_str(), base64_encode("tio.turntable_enable_control(); //turntable control: enable").c_str(), 0);

  AAPIFunc(AOpaque, "turntable_disable_control", MP_NAME, base64_encode("disable turntable control").c_str(), base64_encode("tio.turntable_disable_control(); //turntable control: disable").c_str(), 0);

  AAPIFunc(AOpaque, "turntable_run_speed_rpm_asyn", MP_NAME, base64_encode("set turntable speed asynchronouslly").c_str(), base64_encode("tio.turntable_run_speed_rpm_asyn(20); //set turntable speed 20 rpm asynchronouslly").c_str(), 1);
  AParaFunc(AOpaque, 0, "turntable_run_speed_rpm_asyn", "ATargetSpeedRPM", true, "float", base64_encode("the target run speed (uinit: rpm)").c_str());

  AAPIFunc(AOpaque, "turntable_run_speed_rpm_syn", MP_NAME, base64_encode("set turntable speed synchronouslly, unit: rpm").c_str(), base64_encode("tio.turntable_run_speed_rpm_syn(20, 2000); //set turntable speed 20 rpm synchronouslly, timeout is 2000ms").c_str(), 2);
  AParaFunc(AOpaque, 0, "turntable_run_speed_rpm_syn", "ATargetSpeedRPM", true, "float", base64_encode("the target run speed (uinit: rpm)").c_str());
  AParaFunc(AOpaque, 1, "turntable_run_speed_rpm_syn", "ATimeout", true, "u32", base64_encode("timeout set(ms)").c_str());

  AAPIFunc(AOpaque, "turntable_run_speed_dps_asyn", MP_NAME, base64_encode("set turntable speed asynchronouslly, unit: deg/s").c_str(), base64_encode("tio.turntable_run_speed_dps_asyn(20); //set turntable speed 20 deg/s asynchronouslly: ").c_str(), 1);
  AParaFunc(AOpaque, 0, "turntable_run_speed_dps_asyn", "ATargetSpeedDPS", true, "float", base64_encode("the target run speed (uinit: deg/s)").c_str());

  AAPIFunc(AOpaque, "turntable_run_speed_dps_syn", MP_NAME, base64_encode("set turntable speed synchronouslly, unit: deg/s").c_str(), base64_encode("tio.turntable_run_speed_dps_syn(20, 2000); //set turntable speed 20 deg/s synchronouslly, timeout is 2000ms").c_str(), 2);
  AParaFunc(AOpaque, 0, "turntable_run_speed_dps_syn", "ATargetSpeedDPS", true, "float", base64_encode("the target run speed (uinit: deg/s)").c_str());
  AParaFunc(AOpaque, 1, "turntable_run_speed_dps_syn", "ATimeout", true, "u32", base64_encode("timeout set(ms)").c_str());

  AAPIFunc(AOpaque, "turntable_run_centrifugal_acc_asyn", MP_NAME, base64_encode("set turntable centrifugal acceleration asynchronouslly, unit: g").c_str(), base64_encode("tio.turntable_run_centrifugal_acc_asyn(1.2, 100); //set turntable centrifugal acceleration 1.2g at arm length 100mm asynchronouslly").c_str(), 2);
  AParaFunc(AOpaque, 0, "turntable_run_centrifugal_acc_asyn", "ATargetAccG", true, "float", base64_encode("the target centrifugal acceleration (uinit: g)").c_str());
  AParaFunc(AOpaque, 1, "turntable_run_centrifugal_acc_asyn", "AArmLengthMM", true, "float", base64_encode("the arm length (uinit: mm)").c_str());

  AAPIFunc(AOpaque, "turntable_run_centrifugal_acc_syn", MP_NAME, base64_encode("set turntable centrifugal acceleration synchronouslly, unit: g").c_str(), base64_encode("tio.turntable_run_centrifugal_acc_syn(1.2, 100, 2000); //set turntable centrifugal acceleration 1.2g in at arm length 100mm synchronouslly, timeout is 2000ms").c_str(), 3);
  AParaFunc(AOpaque, 0, "turntable_run_centrifugal_acc_syn", "ATargetAccG", true, "float", base64_encode("the target centrifugal acceleration (uinit: g)").c_str());
  AParaFunc(AOpaque, 1, "turntable_run_centrifugal_acc_syn", "AArmLengthMM", true, "float", base64_encode("the arm length (uinit: mm)").c_str());
  AParaFunc(AOpaque, 2, "turntable_run_centrifugal_acc_syn", "ATimeout", true, "u32", base64_encode("timeout set(ms)").c_str());

  AAPIFunc(AOpaque, "turntable_stop_run_asyn", MP_NAME, base64_encode("set turntable speed to zero").c_str(), base64_encode("tio.turntable_stop_run_asyn(); //set turntable speed to zero").c_str(), 0);

  AAPIFunc(AOpaque, "turntable_stop_run_syn", MP_NAME, base64_encode("set turntable speed to zero synchronouslly").c_str(), base64_encode("tio.turntable_stop_run_syn(); //set turntable speed to zero synchronouslly").c_str(), 1);
  AParaFunc(AOpaque, 0, "turntable_stop_run_syn", "ATimeout", true, "u32", base64_encode("timeout set(ms)").c_str());

}
