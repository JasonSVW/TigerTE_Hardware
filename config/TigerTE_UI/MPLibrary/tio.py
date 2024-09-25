from ctypes import *
from TSMaster import *
u8 = c_uint8
pu8 = POINTER(c_uint8)
ppu8 = POINTER(pu8)
s8 = c_int8
ps8 = POINTER(c_int8)
pps8 = POINTER(ps8)
u16 = c_uint16
pu16 = POINTER(c_uint16)
ppu16 = POINTER(pu16)
s16 = c_int16
ps16 = POINTER(c_int16)
pps16 = POINTER(ps16)
u32 = c_uint32
pu32 = POINTER(c_uint32)
ppu32 = POINTER(pu32)
s32 = c_int32
ps32 = POINTER(c_int32)
pps32 = POINTER(ps32)
s64 = c_int64
ps64 = POINTER(c_int64)
pps64 = POINTER(ps64)
u64 = c_uint64
pu64 = POINTER(c_uint64)
ppu64 = POINTER(pu64)
double = c_double
pdouble = POINTER(c_double)
ppdouble = POINTER(pdouble)
pchar = c_char_p
ppchar = POINTER(c_char_p)
char = c_char
single = c_float
psingle = POINTER(c_float)
ppsingle = POINTER(psingle)
TObject = c_void_p
cbool = c_bool
pbool = POINTER(c_bool)
pvoid = c_void_p
ppvoid = POINTER(c_void_p)
size_t = c_size_t
psize_t = POINTER(size_t)
ppsize_t = POINTER(psize_t)
ppnative_int = ppsize_t
pnative_int = psize_t
native_int = size_t
_demo_function = CFUNCTYPE(s32,s32,s32,)
def demo_function(A1,A2):
    funcaddr,flag = app.retrieve_api_address('tio.demo_function')
    if funcaddr == 0:
        return None
    demo_function_ = cast(funcaddr,_demo_function)
    return demo_function_(A1,A2)
_servo_create = CFUNCTYPE(s32,)
def servo_create():
    funcaddr,flag = app.retrieve_api_address('tio.servo_create')
    if funcaddr == 0:
        return None
    servo_create_ = cast(funcaddr,_servo_create)
    return servo_create_()
_servo_destroy = CFUNCTYPE(s32,)
def servo_destroy():
    funcaddr,flag = app.retrieve_api_address('tio.servo_destroy')
    if funcaddr == 0:
        return None
    servo_destroy_ = cast(funcaddr,_servo_destroy)
    return servo_destroy_()
_servo_connect = CFUNCTYPE(s32,pchar,)
def servo_connect(AIPAddr):
    funcaddr,flag = app.retrieve_api_address('tio.servo_connect')
    if funcaddr == 0:
        return None
    servo_connect_ = cast(funcaddr,_servo_connect)
    return servo_connect_(AIPAddr)
_servo_disconnect = CFUNCTYPE(s32,)
def servo_disconnect():
    funcaddr,flag = app.retrieve_api_address('tio.servo_disconnect')
    if funcaddr == 0:
        return None
    servo_disconnect_ = cast(funcaddr,_servo_disconnect)
    return servo_disconnect_()
_servo_clear_fault = CFUNCTYPE(s32,)
def servo_clear_fault():
    funcaddr,flag = app.retrieve_api_address('tio.servo_clear_fault')
    if funcaddr == 0:
        return None
    servo_clear_fault_ = cast(funcaddr,_servo_clear_fault)
    return servo_clear_fault_()
_pedal_servo_limit = CFUNCTYPE(s32,single,single,single,)
def pedal_servo_limit(AMaxPositionMM,AMinPositionMM,AMaxSpeedMMpS):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_servo_limit')
    if funcaddr == 0:
        return None
    pedal_servo_limit_ = cast(funcaddr,_pedal_servo_limit)
    return pedal_servo_limit_(AMaxPositionMM,AMinPositionMM,AMaxSpeedMMpS)
_pedal_servo_on = CFUNCTYPE(s32,cbool,)
def pedal_servo_on(AEnable):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_servo_on')
    if funcaddr == 0:
        return None
    pedal_servo_on_ = cast(funcaddr,_pedal_servo_on)
    return pedal_servo_on_(AEnable)
_pedal_enable_run = CFUNCTYPE(s32,cbool,)
def pedal_enable_run(AEnable):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_enable_run')
    if funcaddr == 0:
        return None
    pedal_enable_run_ = cast(funcaddr,_pedal_enable_run)
    return pedal_enable_run_(AEnable)
_pedal_go_step_syn = CFUNCTYPE(s32,single,single,u32,)
def pedal_go_step_syn(ARelPositionMM,ASpeedMMpS,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_step_syn')
    if funcaddr == 0:
        return None
    pedal_go_step_syn_ = cast(funcaddr,_pedal_go_step_syn)
    return pedal_go_step_syn_(ARelPositionMM,ASpeedMMpS,ATimeout)
_pedal_go_step_asyn = CFUNCTYPE(s32,single,single,)
def pedal_go_step_asyn(ARelPositionMM,ASpeedMMpS):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_step_asyn')
    if funcaddr == 0:
        return None
    pedal_go_step_asyn_ = cast(funcaddr,_pedal_go_step_asyn)
    return pedal_go_step_asyn_(ARelPositionMM,ASpeedMMpS)
_pedal_go_position_syn = CFUNCTYPE(s32,single,single,u32,)
def pedal_go_position_syn(AAbsPositionMM,ASpeedMMpS,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_position_syn')
    if funcaddr == 0:
        return None
    pedal_go_position_syn_ = cast(funcaddr,_pedal_go_position_syn)
    return pedal_go_position_syn_(AAbsPositionMM,ASpeedMMpS,ATimeout)
_pedal_go_position_asyn = CFUNCTYPE(s32,single,single,)
def pedal_go_position_asyn(AAbsPositionMM,ASpeedMMpS):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_position_asyn')
    if funcaddr == 0:
        return None
    pedal_go_position_asyn_ = cast(funcaddr,_pedal_go_position_asyn)
    return pedal_go_position_asyn_(AAbsPositionMM,ASpeedMMpS)
_pedal_go_step_percent_syn = CFUNCTYPE(s32,single,single,u32,)
def pedal_go_step_percent_syn(ARelPositionPercent,ASpeedMMpS,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_step_percent_syn')
    if funcaddr == 0:
        return None
    pedal_go_step_percent_syn_ = cast(funcaddr,_pedal_go_step_percent_syn)
    return pedal_go_step_percent_syn_(ARelPositionPercent,ASpeedMMpS,ATimeout)
_pedal_go_step_percent_asyn = CFUNCTYPE(s32,single,single,)
def pedal_go_step_percent_asyn(ARelPositionPercent,ASpeedMMpS):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_step_percent_asyn')
    if funcaddr == 0:
        return None
    pedal_go_step_percent_asyn_ = cast(funcaddr,_pedal_go_step_percent_asyn)
    return pedal_go_step_percent_asyn_(ARelPositionPercent,ASpeedMMpS)
_pedal_go_position_percent_syn = CFUNCTYPE(s32,single,single,u32,)
def pedal_go_position_percent_syn(AAbsPositionPercent,ASpeedMMpS,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_position_percent_syn')
    if funcaddr == 0:
        return None
    pedal_go_position_percent_syn_ = cast(funcaddr,_pedal_go_position_percent_syn)
    return pedal_go_position_percent_syn_(AAbsPositionPercent,ASpeedMMpS,ATimeout)
_pedal_go_position_percent_asyn = CFUNCTYPE(s32,single,single,)
def pedal_go_position_percent_asyn(AAbsPositionPercent,ASpeedMMpS):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_position_percent_asyn')
    if funcaddr == 0:
        return None
    pedal_go_position_percent_asyn_ = cast(funcaddr,_pedal_go_position_percent_asyn)
    return pedal_go_position_percent_asyn_(AAbsPositionPercent,ASpeedMMpS)
_pedal_go_home_syn = CFUNCTYPE(s32,u32,)
def pedal_go_home_syn(ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_home_syn')
    if funcaddr == 0:
        return None
    pedal_go_home_syn_ = cast(funcaddr,_pedal_go_home_syn)
    return pedal_go_home_syn_(ATimeout)
_pedal_go_home_asyn = CFUNCTYPE(s32,)
def pedal_go_home_asyn():
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_home_asyn')
    if funcaddr == 0:
        return None
    pedal_go_home_asyn_ = cast(funcaddr,_pedal_go_home_asyn)
    return pedal_go_home_asyn_()
_pedal_set_home = CFUNCTYPE(s32,u32,)
def pedal_set_home(ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_set_home')
    if funcaddr == 0:
        return None
    pedal_set_home_ = cast(funcaddr,_pedal_set_home)
    return pedal_set_home_(ATimeout)
_pedal_go_auto_mode = CFUNCTYPE(s32,cbool,)
def pedal_go_auto_mode(AEnable):
    funcaddr,flag = app.retrieve_api_address('tio.pedal_go_auto_mode')
    if funcaddr == 0:
        return None
    pedal_go_auto_mode_ = cast(funcaddr,_pedal_go_auto_mode)
    return pedal_go_auto_mode_(AEnable)
_rotate_servo_limit = CFUNCTYPE(s32,single,single,single,)
def rotate_servo_limit(AMaxDegree,AMinDegree,AMaxSpeedDpS):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_servo_limit')
    if funcaddr == 0:
        return None
    rotate_servo_limit_ = cast(funcaddr,_rotate_servo_limit)
    return rotate_servo_limit_(AMaxDegree,AMinDegree,AMaxSpeedDpS)
_rotate_servo_on = CFUNCTYPE(s32,cbool,)
def rotate_servo_on(AEnable):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_servo_on')
    if funcaddr == 0:
        return None
    rotate_servo_on_ = cast(funcaddr,_rotate_servo_on)
    return rotate_servo_on_(AEnable)
_rotate_enable_run = CFUNCTYPE(s32,cbool,)
def rotate_enable_run(AEnable):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_enable_run')
    if funcaddr == 0:
        return None
    rotate_enable_run_ = cast(funcaddr,_rotate_enable_run)
    return rotate_enable_run_(AEnable)
_rotate_go_step_syn = CFUNCTYPE(s32,single,single,u32,)
def rotate_go_step_syn(ARelDegree,ASpeedDpS,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_step_syn')
    if funcaddr == 0:
        return None
    rotate_go_step_syn_ = cast(funcaddr,_rotate_go_step_syn)
    return rotate_go_step_syn_(ARelDegree,ASpeedDpS,ATimeout)
_rotate_go_step_asyn = CFUNCTYPE(s32,single,single,)
def rotate_go_step_asyn(ARelDegree,ASpeedDpS):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_step_asyn')
    if funcaddr == 0:
        return None
    rotate_go_step_asyn_ = cast(funcaddr,_rotate_go_step_asyn)
    return rotate_go_step_asyn_(ARelDegree,ASpeedDpS)
_rotate_go_position_syn = CFUNCTYPE(s32,single,single,u32,)
def rotate_go_position_syn(AAbsDegree,ASpeedDpS,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_position_syn')
    if funcaddr == 0:
        return None
    rotate_go_position_syn_ = cast(funcaddr,_rotate_go_position_syn)
    return rotate_go_position_syn_(AAbsDegree,ASpeedDpS,ATimeout)
_rotate_go_position_asyn = CFUNCTYPE(s32,single,single,)
def rotate_go_position_asyn(AAbsDegree,ASpeedDpS):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_position_asyn')
    if funcaddr == 0:
        return None
    rotate_go_position_asyn_ = cast(funcaddr,_rotate_go_position_asyn)
    return rotate_go_position_asyn_(AAbsDegree,ASpeedDpS)
_rotate_go_home_syn = CFUNCTYPE(s32,u32,)
def rotate_go_home_syn(ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_home_syn')
    if funcaddr == 0:
        return None
    rotate_go_home_syn_ = cast(funcaddr,_rotate_go_home_syn)
    return rotate_go_home_syn_(ATimeout)
_rotate_go_home_asyn = CFUNCTYPE(s32,)
def rotate_go_home_asyn():
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_home_asyn')
    if funcaddr == 0:
        return None
    rotate_go_home_asyn_ = cast(funcaddr,_rotate_go_home_asyn)
    return rotate_go_home_asyn_()
_rotate_set_home = CFUNCTYPE(s32,u32,)
def rotate_set_home(ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_set_home')
    if funcaddr == 0:
        return None
    rotate_set_home_ = cast(funcaddr,_rotate_set_home)
    return rotate_set_home_(ATimeout)
_rotate_go_slope_step_syn = CFUNCTYPE(s32,single,u32,)
def rotate_go_slope_step_syn(ARelGradPercent,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_slope_step_syn')
    if funcaddr == 0:
        return None
    rotate_go_slope_step_syn_ = cast(funcaddr,_rotate_go_slope_step_syn)
    return rotate_go_slope_step_syn_(ARelGradPercent,ATimeout)
_rotate_go_slope_step_asyn = CFUNCTYPE(s32,single,)
def rotate_go_slope_step_asyn(ARelGradPercent):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_slope_step_asyn')
    if funcaddr == 0:
        return None
    rotate_go_slope_step_asyn_ = cast(funcaddr,_rotate_go_slope_step_asyn)
    return rotate_go_slope_step_asyn_(ARelGradPercent)
_rotate_go_slope_syn = CFUNCTYPE(s32,single,u32,)
def rotate_go_slope_syn(AAbsGradPercent,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_slope_syn')
    if funcaddr == 0:
        return None
    rotate_go_slope_syn_ = cast(funcaddr,_rotate_go_slope_syn)
    return rotate_go_slope_syn_(AAbsGradPercent,ATimeout)
_rotate_go_slope_asyn = CFUNCTYPE(s32,single,)
def rotate_go_slope_asyn(AAbsGradPercent):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_slope_asyn')
    if funcaddr == 0:
        return None
    rotate_go_slope_asyn_ = cast(funcaddr,_rotate_go_slope_asyn)
    return rotate_go_slope_asyn_(AAbsGradPercent)
_rotate_go_mount_position_syn = CFUNCTYPE(s32,u32,)
def rotate_go_mount_position_syn(ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_mount_position_syn')
    if funcaddr == 0:
        return None
    rotate_go_mount_position_syn_ = cast(funcaddr,_rotate_go_mount_position_syn)
    return rotate_go_mount_position_syn_(ATimeout)
_rotate_go_mount_position_asyn = CFUNCTYPE(s32,)
def rotate_go_mount_position_asyn():
    funcaddr,flag = app.retrieve_api_address('tio.rotate_go_mount_position_asyn')
    if funcaddr == 0:
        return None
    rotate_go_mount_position_asyn_ = cast(funcaddr,_rotate_go_mount_position_asyn)
    return rotate_go_mount_position_asyn_()
_rotate_set_slope_speed = CFUNCTYPE(s32,single,)
def rotate_set_slope_speed(ASpeedDpS):
    funcaddr,flag = app.retrieve_api_address('tio.rotate_set_slope_speed')
    if funcaddr == 0:
        return None
    rotate_set_slope_speed_ = cast(funcaddr,_rotate_set_slope_speed)
    return rotate_set_slope_speed_(ASpeedDpS)
_air_cylinder_push_out = CFUNCTYPE(s32,)
def air_cylinder_push_out():
    funcaddr,flag = app.retrieve_api_address('tio.air_cylinder_push_out')
    if funcaddr == 0:
        return None
    air_cylinder_push_out_ = cast(funcaddr,_air_cylinder_push_out)
    return air_cylinder_push_out_()
_air_cylinder_push_back = CFUNCTYPE(s32,)
def air_cylinder_push_back():
    funcaddr,flag = app.retrieve_api_address('tio.air_cylinder_push_back')
    if funcaddr == 0:
        return None
    air_cylinder_push_back_ = cast(funcaddr,_air_cylinder_push_back)
    return air_cylinder_push_back_()
_air_cylinder_push_pressure = CFUNCTYPE(s32,single,)
def air_cylinder_push_pressure(ATargetPressureBar):
    funcaddr,flag = app.retrieve_api_address('tio.air_cylinder_push_pressure')
    if funcaddr == 0:
        return None
    air_cylinder_push_pressure_ = cast(funcaddr,_air_cylinder_push_pressure)
    return air_cylinder_push_pressure_(ATargetPressureBar)
_turntable_enable_control = CFUNCTYPE(s32,)
def turntable_enable_control():
    funcaddr,flag = app.retrieve_api_address('tio.turntable_enable_control')
    if funcaddr == 0:
        return None
    turntable_enable_control_ = cast(funcaddr,_turntable_enable_control)
    return turntable_enable_control_()
_turntable_disable_control = CFUNCTYPE(s32,)
def turntable_disable_control():
    funcaddr,flag = app.retrieve_api_address('tio.turntable_disable_control')
    if funcaddr == 0:
        return None
    turntable_disable_control_ = cast(funcaddr,_turntable_disable_control)
    return turntable_disable_control_()
_turntable_run_speed_rpm_asyn = CFUNCTYPE(s32,single,)
def turntable_run_speed_rpm_asyn(ATargetSpeedRPM):
    funcaddr,flag = app.retrieve_api_address('tio.turntable_run_speed_rpm_asyn')
    if funcaddr == 0:
        return None
    turntable_run_speed_rpm_asyn_ = cast(funcaddr,_turntable_run_speed_rpm_asyn)
    return turntable_run_speed_rpm_asyn_(ATargetSpeedRPM)
_turntable_run_speed_rpm_syn = CFUNCTYPE(s32,single,u32,)
def turntable_run_speed_rpm_syn(ATargetSpeedRPM,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.turntable_run_speed_rpm_syn')
    if funcaddr == 0:
        return None
    turntable_run_speed_rpm_syn_ = cast(funcaddr,_turntable_run_speed_rpm_syn)
    return turntable_run_speed_rpm_syn_(ATargetSpeedRPM,ATimeout)
_turntable_run_speed_dps_asyn = CFUNCTYPE(s32,single,)
def turntable_run_speed_dps_asyn(ATargetSpeedDPS):
    funcaddr,flag = app.retrieve_api_address('tio.turntable_run_speed_dps_asyn')
    if funcaddr == 0:
        return None
    turntable_run_speed_dps_asyn_ = cast(funcaddr,_turntable_run_speed_dps_asyn)
    return turntable_run_speed_dps_asyn_(ATargetSpeedDPS)
_turntable_run_speed_dps_syn = CFUNCTYPE(s32,single,u32,)
def turntable_run_speed_dps_syn(ATargetSpeedDPS,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.turntable_run_speed_dps_syn')
    if funcaddr == 0:
        return None
    turntable_run_speed_dps_syn_ = cast(funcaddr,_turntable_run_speed_dps_syn)
    return turntable_run_speed_dps_syn_(ATargetSpeedDPS,ATimeout)
_turntable_run_centrifugal_acc_asyn = CFUNCTYPE(s32,single,single,)
def turntable_run_centrifugal_acc_asyn(ATargetAccG,AArmLengthMM):
    funcaddr,flag = app.retrieve_api_address('tio.turntable_run_centrifugal_acc_asyn')
    if funcaddr == 0:
        return None
    turntable_run_centrifugal_acc_asyn_ = cast(funcaddr,_turntable_run_centrifugal_acc_asyn)
    return turntable_run_centrifugal_acc_asyn_(ATargetAccG,AArmLengthMM)
_turntable_run_centrifugal_acc_syn = CFUNCTYPE(s32,single,single,u32,)
def turntable_run_centrifugal_acc_syn(ATargetAccG,AArmLengthMM,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.turntable_run_centrifugal_acc_syn')
    if funcaddr == 0:
        return None
    turntable_run_centrifugal_acc_syn_ = cast(funcaddr,_turntable_run_centrifugal_acc_syn)
    return turntable_run_centrifugal_acc_syn_(ATargetAccG,AArmLengthMM,ATimeout)
_turntable_stop_run_asyn = CFUNCTYPE(s32,)
def turntable_stop_run_asyn():
    funcaddr,flag = app.retrieve_api_address('tio.turntable_stop_run_asyn')
    if funcaddr == 0:
        return None
    turntable_stop_run_asyn_ = cast(funcaddr,_turntable_stop_run_asyn)
    return turntable_stop_run_asyn_()
_turntable_stop_run_syn = CFUNCTYPE(s32,u32,)
def turntable_stop_run_syn(ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.turntable_stop_run_syn')
    if funcaddr == 0:
        return None
    turntable_stop_run_syn_ = cast(funcaddr,_turntable_stop_run_syn)
    return turntable_stop_run_syn_(ATimeout)
_ps_power_on = CFUNCTYPE(s32,u32,)
def ps_power_on(ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.ps_power_on')
    if funcaddr == 0:
        return None
    ps_power_on_ = cast(funcaddr,_ps_power_on)
    return ps_power_on_(ATimeout)
_ps_power_off = CFUNCTYPE(s32,u32,)
def ps_power_off(ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.ps_power_off')
    if funcaddr == 0:
        return None
    ps_power_off_ = cast(funcaddr,_ps_power_off)
    return ps_power_off_(ATimeout)
_ps_reset = CFUNCTYPE(s32,)
def ps_reset():
    funcaddr,flag = app.retrieve_api_address('tio.ps_reset')
    if funcaddr == 0:
        return None
    ps_reset_ = cast(funcaddr,_ps_reset)
    return ps_reset_()
_ps_set_pressure_asyn = CFUNCTYPE(s32,single,cbool,)
def ps_set_pressure_asyn(APressureBar,AEnableProtection):
    funcaddr,flag = app.retrieve_api_address('tio.ps_set_pressure_asyn')
    if funcaddr == 0:
        return None
    ps_set_pressure_asyn_ = cast(funcaddr,_ps_set_pressure_asyn)
    return ps_set_pressure_asyn_(APressureBar,AEnableProtection)
_ps_set_pressure_syn = CFUNCTYPE(s32,single,single,cbool,u32,)
def ps_set_pressure_syn(APressureBar,AMaxTolBar,AEnableProtection,ATimeout):
    funcaddr,flag = app.retrieve_api_address('tio.ps_set_pressure_syn')
    if funcaddr == 0:
        return None
    ps_set_pressure_syn_ = cast(funcaddr,_ps_set_pressure_syn)
    return ps_set_pressure_syn_(APressureBar,AMaxTolBar,AEnableProtection,ATimeout)
