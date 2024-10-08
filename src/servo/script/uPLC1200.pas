unit uPLC1200;

interface

uses
  windows, sysutils, classes, uinclibtsmaster, System.Generics.Collections,
  Vcl.Forms, uMPHeader_tio, uTSMasterInternal_tio, System.StrUtils,
  uLibSnap7_x86, SyncObjs, Vcl.ExtCtrls, uSystemVarMgmt;

const
  amPolling = 0;
  amEvent = 1;
  amCallBack = 2;
  DefaultTimeout = 1000;
  PositionMaxTol = 0.1;

type
  TDataRecord = packed record
    Area: integer;
    DBNum: integer;
    Start: integer;
    Amount: integer;
    WordLen: integer;
  end;

  PDataRecord = ^TDataRecord;

  TThreadHeartbeat = class(TThread)
  private
    FErrorCount: s32;
    FExitCount: s32;
//    FRunningCount: s32;
    function S7_Heartbeat: s32;
  protected
    procedure Execute; override;
  public
    procedure HeartbeatResume;
    procedure HeartbeatSuspend;
    procedure Heartbeatexit;
  end;

  TThreadGetData = class(TThread)
  private
    FErrorCount: s32;
    FExitCount: s32;
//    FRunningCount: s32;
    function S7_GetData: s32;
  protected
    procedure Execute; override;
  public
    procedure GetDataResume;
    procedure GetDatatSuspend;
    procedure GetDataexit;
  end;

  TServo = class(TObject)
  private
    FMonitorObj: TObject;
    FS7Client: TS7Client;
//    FS7ClientRead: TS7Client;
    FS7Buffer: TS7Buffer;
    // OpData: TDataRecord;
    // FS7DataItem: TS7DataItem;
    // FS7DataItems: TS7DataItems;
    FS7LastError: integer; // S1200 communication error
    FS7IsConnected: boolean; // S1200 Connected
    { PLC DB51 Status }
    FS7IsHandShaked: boolean; // s1200 HandShakeState
    FS7IsPowerOn: boolean; // S1200 --S1 and S2 Power Status
    FS7IsAutoMode: boolean;
    FS7IsFault: boolean; // S1200 --S1 and S2 Device Fault
    FS7IsOnlyPedal: boolean;
    FS7WithAirCylinder: boolean;
    FS1IsServoOn: boolean;
    FS1ZeroExisted: boolean;
    FS1IsReady: boolean;
    // FS1Running: Boolean;
    FS1RunFinished: boolean;
    // FS1AutoMode: Boolean;
    FS1IsFault: boolean;
    FS2IsServoOn: boolean;
    FS2ZeroExisted: boolean;
    FS2IsReady: boolean;
    // FS2Running: Boolean;
    FS2RunFinished: boolean;
    // FS2AutoMode: Boolean;
    FS2IsFault: boolean;
    FS1ActPosition: Single;
    FS1ActSpeed: Single;
    FS2ActPosition: Single;
    FS2ActPositionGrad: Single;
    FS2ActSpeed: Single;
    FS1MaxSpeed: Single;
    FS1MaxPosition: Single;
    FS1MinPosition: Single;
    FS2MaxSpeed: Single;
    FS2MaxPosition: Single;
    FS2MinPosition: Single;
    FS2MountPosition: Single;
    FS2SlopSpeed: Single;
    FS3TargetCurrent: Single;
    { Internal Status }
    FS1TargetPositionManual: Single;
    FS1TargetSpeedManual: Single;
    FS2TargetPositionManual: Single;
    FS2TargetSpeedManual: Single;
    FS1TargetPositionAuto: Single;
    FS1TargetSpeedAuto: Single;
    FS2TargetPositionAuto: Single;
    FS2TargetSpeedAuto: Single;
    FPedalIsSysMode: boolean;
    FS3MCMaxPressure: Single;
    FS3P2AFactor: Single;
    FS3P2AOffset: Single;
    procedure SetFS7LastError(const Value: integer);
    procedure SetFS7IsConnected(const Value: boolean);
    function S7Write(const AField: TDataRecord; const pData: Pointer; const Async: boolean): s32;
    function S7Read(const AField: TDataRecord; const pData: Pointer; const Async: boolean): s32;
//    function S7SetBoolSyn(const AWriteField, AReadField: TDataRecord; const ASetBool, ACorrectBool: boolean; const ATimeout: integer = 1000): s32;
//    function S7ReadBool(const AReadField: TDataRecord; const pGetBool: pBoolean): s32;
//    function S7WriteBool(const AWriteField: TDataRecord; const ASetBool: boolean): s32;
//    function S7WriteRealSyn(const AWriteField, AReadField: TDataRecord; const ASetReal, ACorrectReal: Single; const ATimeout: integer = 1000): s32;
    procedure S7WaitCompletion(const ATimeout: u32 = DefaultTimeout);
//    procedure TimeElapse;
  private
    procedure SetFS1IsFault(const Value: boolean);
    procedure SetFS1IsReady(const Value: boolean);
    procedure SetFS1RunFinished(const Value: boolean);
    // procedure SetFS1AutoMode(const Value: Boolean);
    // procedure SetFS1Running(const Value: Boolean);
    procedure SetFS1IsServoOn(const Value: boolean);
    procedure SetFS1ZeroExisted(const Value: boolean);
    procedure SetFS2IsFault(const Value: boolean);
    procedure SetFS2IsReady(const Value: boolean);
    procedure SetFS2RunFinished(const Value: boolean);
    // procedure SetFS2AutoMode(const Value: Boolean);
    // procedure SetFS2Running(const Value: Boolean);
    procedure SetFS2IsServoOn(const Value: boolean);
    procedure SetFS2ZeroExisted(const Value: boolean);
    procedure SetFS7IsFault(const Value: boolean);
    procedure SetFS7IsHandShaked(const Value: boolean);
    procedure SetFS7IsPowerOn(const Value: boolean);
    procedure SetFS1ActPosition(const Value: Single);
    procedure SetFS1ActSpeed(const Value: Single);
    procedure SetFS2ActPosition(const Value: Single);
    procedure SetFS2ActPositionGrad(const Value: Single);
    procedure SetFS2ActSpeed(const Value: Single);
//    procedure SetFS7PowerOff(const Value: boolean);
    procedure SetFS1TargetPositionAuto(const Value: Single);
    procedure SetFS1TargetPositionManual(const Value: Single);
    procedure SetFS1TargetSpeedAuto(const Value: Single);
    procedure SetFS1TargetSpeedManual(const Value: Single);
    procedure SetFS2TargetPositionAuto(const Value: Single);
    procedure SetFS2TargetPositionManual(const Value: Single);
    procedure SetFS2TargetSpeedAuto(const Value: Single);
    procedure SetFS2TargetSpeedManual(const Value: Single);
    procedure SetFS7IsAutoMode(const Value: boolean);
    procedure SetFS1MaxSpeed(const Value: Single);
    procedure SetFS1MaxPosition(const Value: Single);
    procedure SetFS1MinPosition(const Value: Single);
    procedure SetFS2MaxSpeed(const Value: Single);
    procedure SetFS2MaxPosition(const Value: Single);
    procedure SetFS2MinPosition(const Value: Single);
    procedure SetFS2MountPosition(const Value: Single);
    procedure SetFS2SlopSpeed(const Value: Single);
    procedure SetFS7IsOnlyPedal(const Value: Boolean);
    procedure SetFS7WithAirCylinder(const Value: Boolean);
    procedure SetFPedalIsSysMode(const AEnable: boolean);
    procedure SetFS3MCMaxPressure(const Value: Single);
    procedure SetFS3P2AFactor(const Value: Single);
    procedure SetFS3P2AOffset(const Value: Single);
    //function S1_GoAbsPos_AutoMode(const APostionMM, ASpeedMMS: Single): s32;
    //system var
    procedure RegisterSystemVars;
    procedure UnregisterSystemVars;
    function RegisterInternalVar(const AName: string; const AComments: string; const AIsReadOnly: boolean; const AType: TSystemVarType): tsystemvar;
    procedure UnRegisterInternalVar(const AName: string);
    procedure SetFS3TargetCurrent(const Value: Single);
//    procedure OnSystemVarChanged_Int32(const AVar: TSystemVar);
//    procedure OnSystemVarChanged_Str(const AVar: TSystemVar);

  public
    FRemoteAddress: AnsiString;
    FSnap7IsLoaded: BOOL;
    // FObjIsCreatedGUI: BOOL;
    constructor Create(const AOnlyPedalServo: Boolean);
    destructor Destroy; override;
  public
    property S7LastError: integer read FS7LastError write SetFS7LastError;
    property S7IsConnected: boolean read FS7IsConnected write SetFS7IsConnected;
    property S7IsHandShaked: boolean read FS7IsHandShaked write SetFS7IsHandShaked;
    property S7IsPowerOn: boolean read FS7IsPowerOn write SetFS7IsPowerOn;
    property S7IsAutoMode: boolean read FS7IsAutoMode write SetFS7IsAutoMode;
    // property S7PowerOff: Boolean read FS7IsAutoMode write SetFS7PowerOff;
    property S7IsFault: boolean read FS7IsFault write SetFS7IsFault;
    property S7IsOnlyPedal: boolean read FS7IsOnlyPedal write SetFS7IsOnlyPedal;
    property S7WithAirCylinder: boolean read FS7WithAirCylinder write SetFS7WithAirCylinder;
    property S1IsServoOn: boolean read FS1IsServoOn write SetFS1IsServoOn;
    property S1ZeroExisted: boolean read FS1ZeroExisted write SetFS1ZeroExisted;
    property S1IsReady: boolean read FS1IsReady write SetFS1IsReady;
    // property S1Running: Boolean read FS1Running write SetFS1Running;
    property S1RunFinished: boolean read FS1RunFinished write SetFS1RunFinished;
    // property S1AutoMode: Boolean read FS1AutoMode write SetFS1AutoMode;
    property S1IsFault: boolean read FS1IsFault write SetFS1IsFault;
    property S2IsServoOn: boolean read FS2IsServoOn write SetFS2IsServoOn;
    property S2ZeroExisted: boolean read FS2ZeroExisted write SetFS2ZeroExisted;
    property S2IsReady: boolean read FS2IsReady write SetFS2IsReady;
    // property S2Running: Boolean read FS2Running write SetFS2Running;
    property S2RunFinished: boolean read FS2RunFinished write SetFS2RunFinished;
    // property S2AutoMode: Boolean read FS2AutoMode write SetFS2AutoMode;
    property S2IsFault: boolean read FS2IsFault write SetFS2IsFault;
    property S1ActPostion: Single read FS1ActPosition write SetFS1ActPosition;
    property S1ActSpeed: Single read FS1ActSpeed write SetFS1ActSpeed;
    property S2ActPostion: Single read FS2ActPosition write SetFS2ActPosition;
    property S2ActPositionGrad: Single read FS2ActPositionGrad write SetFS2ActPositionGrad;
    property S2ActSpeed: Single read FS2ActSpeed write SetFS2ActSpeed;
    property S1TargetPositionManual: Single read FS1TargetPositionManual write SetFS1TargetPositionManual;
    property S1TargetSpeedManual: Single read FS1TargetSpeedManual write SetFS1TargetSpeedManual;
    property S2TargetPositionManual: Single read FS2TargetPositionManual write SetFS2TargetPositionManual;
    property S2TargetSpeedManual: Single read FS2TargetSpeedManual write SetFS2TargetSpeedManual;
    property S1TargetPositionAuto: Single read FS1TargetPositionAuto write SetFS1TargetPositionAuto;
    property S1TargetSpeedAuto: Single read FS1TargetSpeedAuto write SetFS1TargetSpeedAuto;
    property S2TargetPositionAuto: Single read FS2TargetPositionAuto write SetFS2TargetPositionAuto;
    property S2TargetSpeedAuto: Single read FS2TargetSpeedAuto write SetFS2TargetSpeedAuto;
    property S1MaxSpeed: Single read FS1MaxSpeed write SetFS1MaxSpeed;
    property S1MaxPosition: Single read FS1MaxPosition write SetFS1MaxPosition;
    property S1MinPosition: Single read FS1MinPosition write SetFS1MinPosition;
    property S2MaxSpeed: Single read FS2MaxSpeed write SetFS2MaxSpeed;
    property S2MaxPosition: Single read FS2MaxPosition write SetFS2MaxPosition;
    property S2MinPosition: Single read FS2MinPosition write SetFS2MinPosition;
    property S2MountPosition: Single read FS2MountPosition write SetFS2MountPosition;
    property S2SlopSpeed: Single read FS2SlopSpeed write SetFS2SlopSpeed;
    property PedalIsSysMode: boolean read FPedalIsSysMode write SetFPedalIsSysMode;
    property S3TargetCurrent: Single read FS3TargetCurrent write SetFS3TargetCurrent;
    property S3MCMaxPressure: Single read FS3MCMaxPressure write SetFS3MCMaxPressure;
    property S3P2AFactor: Single read FS3P2AFactor write SetFS3P2AFactor;
    property S3P2AOffset: Single read FS3P2AOffset write SetFS3P2AOffset;
  public    // set action
    function S7_Connection: s32;
    function S7_Disconnection: s32;
    function S7_ClearFault(const ATimeout: u32 = DefaultTimeout): s32;
    function S7_HandsShake(const AEnable: boolean; const ATimeout: u32 = DefaultTimeout): s32;

    function S1_ServoON(const AEnable: boolean; const ATimeout: u32 = DefaultTimeout): s32;
    function S1_Run_On(const ATimeout: u32 = DefaultTimeout): s32;
    function S1_Run_Off(const ATimeout: u32 = DefaultTimeout): s32;
    function S1_Manual_JogOut: s32;
    function S1_Manual_JogIn: s32;
    function S1_GoZero_Asyn: s32;
    function S1_GoZero_Syn(const ATimeout: u32 = DefaultTimeout): s32;
    function S1_SetZero(const ATimeout: u32 = DefaultTimeout): s32;
    function S1_GoAbsPos_AutoMode_Asyn(const AAbsPosMM, ASpeedMMS: Single): s32;
    function S1_GoAbsPos_AutoMode_Syn(const AAbsPosMM, ASpeedMMS: Single; const ATimeout: u32 = DefaultTimeout): s32;
    function S1_RunSpd_AutoMode_Asyn(const ASpeedRPM: Single): s32;
    function S1_RunSpd_AutoMode_Syn(const ASpeedRPM: Single; const ATimeout: u32 = DefaultTimeout): s32;
    function S1_GoRelPos_AutoMode_Asyn(const ARelPosMM, ASpeedMMS: Single): s32;
    function S1_GoRelPos_AutoMode_Syn(const ARelPosMM, ASpeedMMS: Single; const ATimeout: u32 = DefaultTimeout): s32;
    function S1_GoAbsPos_MMode_Asyn(const AAbsPosMM, ASpeedMMS: Single): s32;
    function S1_GoAbsPos_MMode_Syn(const AAbsPosMM, ASpeedMMS: Single; const ATimeout: u32): s32;
    function S1_GoRelPos_MMode_Asyn(const ARelPosMM, ASpeedMMS: Single): s32;
    function S1_GoRelPos_MMode_Syn(const ARelPosMM, ASpeedMMS: Single; const ATimeout: u32 = DefaultTimeout): s32;

    function S2_ServoON(const AEnable: boolean; const ATimeout: u32 = DefaultTimeout): s32;
    function S2_Run_On(const ATimeout: u32 = DefaultTimeout): s32;
    function S2_Run_Off(const ATimeout: u32 = DefaultTimeout): s32;
    function S2_Manual_JogOut: s32;
    function S2_Manual_JogIn: s32;
    function S2_GoZero_Asyn: s32;
    function S2_GoZero_Syn(const ATimeout: u32 = DefaultTimeout): s32;
    function S2_SetZero(const ATimeout: u32 = DefaultTimeout): s32;
    function S2_GoAbsPos_AutoMode_Asyn(const AAbsPosDeg, ASpeedDegS: Single): s32;
    function S2_GoAbsPos_AutoMode_Syn(const AAbsPosDeg, ASpeedDegS: Single; const ATimeout: u32 = DefaultTimeout): s32;
    function S2_GoRelPos_AutoMode_Asyn(const ARelPosDeg, ASpeedDegS: Single): s32;
    function S2_GoRelPos_AutoMode_Syn(const ARelPosDeg, ASpeedDegS: Single; const ATimeout: u32 = DefaultTimeout): s32;
    function S2_GoAbsPos_MMode_Asyn(const AAbsPosDeg, ASpeedDegS: Single): s32;
    function S2_GoAbsPos_MMode_Syn(const AAbsPosDeg, ASpeedDegS: Single; const ATimeout: u32): s32;
    function S2_GoRelPos_MMode_Asyn(const ARelPosDeg, ASpeedDegS: Single): s32;
    function S2_GoRelPos_MMode_Syn(const ARelPosDeg, ASpeedDegS: Single; const ATimeout: u32 = DefaultTimeout): s32;

    function S2_GoMountPos_AutoMode_Asyn: s32;
    function S2_GoMountPos_AutoMode_Syn(const ATimeout: u32 = DefaultTimeout): s32;
    function S2_GoAbsSlopGrad_AutoMode_Asyn(const AAbsGradPercent: Single): s32;
    function S2_GoAbsSlopGrad_AutoMode_Syn(const AAbsGradPercent: Single; const ATimeout: u32 = DefaultTimeout): s32;
    function S2_GoRelSlopGrad_AutoMode_Asyn(const ARelGradPercent: Single): s32;
    function S2_GoRelSlopGrad_AutoMode_Syn(const ARelGradPercent: Single; const ATimeout: u32 = DefaultTimeout): s32;
    function S2_GoMountPos_MMode_Asyn: s32;
    function S2_GoMountPos_MMode_Syn(const ATimeout: u32 = DefaultTimeout): s32;
    function S2_GoAbsSlopGrad_MMode_Asyn(const AAbsGradPercent: Single): s32;
    function S2_GoAbsSlopGrad_MMode_Syn(const AAbsGradPercent: Single; const ATimeout: u32): s32;
    function S2_GoRelSlopGrad_MMode_Asyn(const ARelGradPercent: Single): s32;
    function S2_GoRelSlopGrad_MMode_Syn(const ARelGradPercent: Single; const ATimeout: u32 = DefaultTimeout): s32;

    function S3_Go_Out: s32;
    function S3_Go_In: s32;
    function S3_Set_Current(const ACurrentA: Single): s32;
    function S3_Set_Target_Pressure(const ATargetPressureBar: Single): s32;
    function S3_Pressure_Current(const APressure: Single): Single;

    function S7_GetAllData: s32;

  end;

var
  vServoObj: TServo;
  vHeartbeatThread: TThreadHeartbeat;
  vGetDataThread: TThreadGetData;

const
  { set Address }
  {$REGION 'PLCAddress'}
  AddrSetHandShake: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 0;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS1ServoOn: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 1;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS1Start: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 2;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS1Stop: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 3;
    Amount: 1;
    WordLen: S7WLBit
  );
  // AddrSetS1Mode: TDataRecord = (
  // Area: S7AreaDB;
  // DBNum: 50;
  // Start: 19;
  // Amount: 1;
  // WordLen: S7WLBit
  // );
  AddrSetS1JogF: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 4;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS1JogB: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 5;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS1GoZero: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 6;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS1SetZero: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 7;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS2ServoOn: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 8;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS2Start: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 9;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS2Stop: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 10;
    Amount: 1;
    WordLen: S7WLBit
  );
  // AddrSetS2Mode: TDataRecord = (
  // Area: S7AreaDB;
  // DBNum: 50;
  // Start: 27;
  // Amount: 1;
  // WordLen: S7WLBit
  // );
  AddrSetS2JogF: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 11;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS2JogB: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 12;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS2GoZero: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 13;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS2SetZero: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 14;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS7Reset: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 15;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS1APos: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 2;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrSetS1ASpd: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 6;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrSetS1APosSpd: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 2;
    Amount: 2;
    WordLen: S7WLReal
  );
  AddrSetS1MPos: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 10;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrSetS1MSpd: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 14;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrSetS1MPosSpd: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 10;
    Amount: 2;
    WordLen: S7WLReal
  );
  AddrSetS2APos: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 18;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrSetS2ASpd: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 22;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrSetS2APosSpd: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 18;
    Amount: 2;
    WordLen: S7WLReal
  );
  AddrSetS2MPos: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 26;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrSetS2MSpd: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 30;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrSetS2MPosSpd: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 26;
    Amount: 2;
    WordLen: S7WLReal
  );
  { get Address }
  AddrGetS7IsHandShake: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 0;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS7IsPowerOn: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 1;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS7IsAutoMode: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 2;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS7IsFault: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 3;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS1IsServoOn: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 4;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS1ZeroExisted: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 5;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS1IsReady: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 6;
    Amount: 1;
    WordLen: S7WLBit
  );
  // AddrGetS1Runing: TDataRecord = (
  // Area: S7AreaDB;
  // DBNum: 51;
  // Start: 22;
  // Amount: 1;
  // WordLen: S7WLBit
  // );
  AddrGetS1RunFinished: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 7;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS1IsFault: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 8;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS2IsServoOn: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 9;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS2ZeroExisted: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 10;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS2IsReady: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 11;
    Amount: 1;
    WordLen: S7WLBit
  );
  // AddrGetS2Runing: TDataRecord = (
  // Area: S7AreaDB;
  // DBNum: 51;
  // Start: 28;
  // Amount: 1;
  // WordLen: S7WLBit
  // );
  AddrGetS2RunFinished: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 12;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS2IsFault: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 13;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrGetS1ActPosition: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 2;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrGetS1ActSpeed: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 6;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrGetS2ActPosition: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 10;
    Amount: 1;
    WordLen: S7WLReal
  );
  AddrGetS2ActSpeed: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 14;
    Amount: 1;
    WordLen: S7WLReal
  );
  // todo correct the address is needed
  // AddrGetS1Mode: TDataRecord = (
  // Area: S7AreaDB;
  // DBNum: 51;
  // Start: 23;
  // Amount: 1;
  // WordLen: S7WLBit
  // );
  // AddrGetS2Mode: TDataRecord = (
  // Area: S7AreaDB;
  // DBNum: 51;
  // Start: 23;
  // Amount: 1;
  // WordLen: S7WLBit
  // );
  AddrGetAllData: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 51;
    Start: 0;
    Amount: 18;
    WordLen: S7WLByte
  );
  AddrSetS3GoOut: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 11;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS3GoIn: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 12;
    Amount: 1;
    WordLen: S7WLBit
  );
  AddrSetS3Current: TDataRecord = (
    Area: S7AreaDB;
    DBNum: 50;
    Start: 18;
    Amount: 1;
    WordLen: S7WLReal
  );
  {$ENDREGION}


{mp api}
{$REGION 'mp lib'}

function servo_check: s32; cdecl;

function servo_create: s32; cdecl;

function servo_destroy: s32; cdecl;

function servo_connect(const AIPAddr: PAnsiChar): s32; cdecl;

function servo_disconnect: s32; cdecl;

function servo_clear_fault: s32; cdecl;

function pedal_servo_limit(const AMaxPositionMM: float32; const AMinPositionMM: float32; const AMaxSpeedMMpS: float32): s32; cdecl;

function pedal_servo_on(const AEnable: Boolean): s32; cdecl;

function pedal_enable_run(const AEnable: Boolean): s32; cdecl;

function pedal_go_step_syn(const ARelPositionMM: float32; const ASpeedMMpS: float32; const ATimeout: u32): s32; cdecl;

function pedal_go_step_asyn(const ARelPositionMM: float32; const ASpeedMMpS: float32): s32; cdecl;

function pedal_go_position_syn(const AAbsPositionMM: float32; const ASpeedMMpS: float32; const ATimeout: u32): s32; cdecl;

function pedal_go_position_asyn(const AAbsPositionMM: float32; const ASpeedMMpS: float32): s32; cdecl;

function pedal_sys_position_asyn(const AAbsPositionMM: float32; const ASpeedMMpS: float32): s32; cdecl;

function pedal_go_step_percent_syn(const ARelPositionPercent: float32; const ASpeedMMpS: float32; const ATimeout: u32): s32; cdecl;

function pedal_go_step_percent_asyn(const ARelPositionPercent: float32; const ASpeedMMpS: float32): s32; cdecl;

function pedal_go_position_percent_syn(const AAbsPositionPercent: float32; const ASpeedMMpS: float32; const ATimeout: u32): s32; cdecl;

function pedal_go_position_percent_asyn(const AAbsPositionPercent: float32; const ASpeedMMpS: float32): s32; cdecl;

function pedal_sys_position_percent_asyn(const AAbsPositionPercent: float32; const ASpeedMMpS: float32): s32; cdecl;

function pedal_go_home_syn(const ATimeout: u32): s32; cdecl;

function pedal_go_home_asyn: s32; cdecl;

function pedal_set_home(const ATimeout: u32): s32; cdecl;

function pedal_go_auto_mode(const AEanble: Boolean): s32; cdecl;

function rotate_servo_limit(const AMaxDegree: float32; const AMinDegree: float32; const AMaxSpeedDpS: float32): s32; cdecl;

function rotate_servo_on(const AEnable: Boolean): s32; cdecl;

function rotate_enable_run(const AEnable: Boolean): s32; cdecl;

function rotate_go_step_syn(const ARelDegree: float32; const ASpeedDpS: float32; const ATimeout: u32): s32; cdecl;

function rotate_go_step_asyn(const ARelDegree: float32; const ASpeedDpS: float32): s32; cdecl;

function rotate_go_position_syn(const AAbsDegree: float32; const ASpeedDpS: float32; const ATimeout: u32): s32; cdecl;

function rotate_go_position_asyn(const AAbsDegree: float32; const ASpeedDpS: float32): s32; cdecl;

function rotate_go_home_syn(const ATimeout: u32): s32; cdecl;

function rotate_go_home_asyn: s32; cdecl;

function rotate_set_home(const ATimeout: u32): s32; cdecl;

function rotate_go_slope_step_syn(const ARelGradPercent: float32; const ATimeout: u32): s32; cdecl;

function rotate_go_slope_step_asyn(const ARelGradPercent: float32): s32; cdecl;

function rotate_go_slope_syn(const AAbsGradPercent: float32; const ATimeout: u32): s32; cdecl;

function rotate_go_slope_asyn(const AAbsGradPercent: float32): s32; cdecl;

function rotate_go_mount_position_syn(const ATimeout: u32): s32; cdecl;

function rotate_go_mount_position_asyn: s32; cdecl;

function rotate_set_slope_speed(const ASpeedDpS: float32): s32; cdecl;

function air_cylinder_push_out: s32; cdecl;

function air_cylinder_push_back: s32; cdecl;

function air_cylinder_push_pressure(const ATargetPressureBar: single): s32; cdecl;

function turntable_enable_control: s32; cdecl;

function turntable_disable_control: s32; cdecl;

function turntable_run_speed_rpm_asyn(const ATargetSpeedRPM: single): s32; cdecl;

function turntable_run_speed_rpm_syn(const ATargetSpeedRPM: single; const ATimeout: u32): s32; cdecl;

function turntable_run_speed_dps_asyn(const ATargetSpeedDPS: single): s32; cdecl;

function turntable_run_speed_dps_syn(const ATargetSpeedDPS: single; const ATimeout: u32): s32; cdecl;

function turntable_run_centrifugal_acc_asyn(const ATargetAccelerationG: single; const AArmLengthMM: single): s32; cdecl;

function turntable_run_centrifugal_acc_syn(const ATargetAccelerationG: single; const AArmLengthMM: single; const ATimeout: u32): s32; cdecl;

function turntable_stop_run_asyn: s32; cdecl;

function turntable_stop_run_syn(const ATimeout: u32): s32; cdecl;
{$ENDREGION}

implementation

uses
  uTSBaseUtils, uHighresTimerDispatcher, uMultiLang, uUtilsTIO;

const
  LANG_ERROR__REG_SYSTEM_VAR_FAILED = 'Error: reg system var failed';
  LANG_WARNING__REMOVE_SYSTEM_VAR_FAILED = 'Warning: remove system var failed';
  GROUP_NAME_SERVO = 'servo';


 {$REGION 'mp lib implementation'}
function servo_check: s32; cdecl;
begin
  if vServoObj = nil then
  begin
    vlog('Created servo object failed', LVL_ERROR);
    Exit(-1);
  end;

  Result := 0;
end;

function servo_create: s32; cdecl;
begin
  if nil = vServoObj then
  begin
    vServoObj := TServo.Create(true);
  end;

  if not vServoObj.FSnap7IsLoaded then
  begin
    vServoObj.free;
    vServoObj := nil;
    vLog('Servo DLL Load Failed', LVL_ERROR);
    Exit(-3);
  end;
  Result := 0;
end;
//

function servo_destroy: s32; cdecl;
begin
  if nil = vServoObj then
  begin
    vLog('no servo object existed', LVL_INFO);
    Exit(0);
  end
  else
  begin

    vServoObj.free;
    vServoObj := nil;
    vLog('Servo object destroyed', LVL_INFO);
    Exit(0);

  end;
end;

function servo_connect(const AIPAddr: PAnsiChar): s32; cdecl;
begin

  vServoObj.FRemoteAddress := AIPAddr;

  result := servo_check;
  if result <> 0 then
    Exit(result);

  if 0 <> vServoObj.S7_Connection then
  begin
    vlog('can not connect with servo system, check IP Address', LVL_ERROR);
    Exit(-3);
  end;
  if 0 <> vServoObj.S7_HandsShake(true, 10000) then
  begin
    vlog('handshake with servo system failed', LVL_ERROR);
    Exit(-4);
  end;

  vLog('MP API: Servo connected successfully', LVL_OK);
  Result := 0;
end;

function servo_disconnect: s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if vServoObj.S7IsConnected then
  begin
    Result := vServoObj.S7_Disconnection;
    if Result <> 0 then
      vLog('disconnect succeffully failed', LVL_INFO)
    else
      vLog('disconnect succeffully', LVL_INFO);
    Exit(Result);
  end
  else
  begin
    vLog('no connection with servo system', LVL_INFO);
    Exit(0);
  end;
end;

function servo_clear_fault: s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S7_ClearFault;
end;

function pedal_servo_limit(const AMaxPositionMM: float32; const AMinPositionMM: float32; const AMaxSpeedMMpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  vServoObj.S1MaxPosition := AMaxPositionMM;
  vServoObj.S1MinPosition := AMinPositionMM;
  vServoObj.S1MaxSpeed := AMaxSpeedMMpS;
  Result := 0;
end;

function pedal_servo_on(const AEnable: Boolean): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if not vServoObj.S7IsAutoMode then
  begin
    vlog('Servo control mode is manual mode, switch the mode on the door first', LVL_ERROR);
    Exit(-3);
  end;

  if AEnable then
  begin
    if 0 <> vServoObj.S1_ServoON(true, 5000) then
    begin
      vlog('Pedal Servo On Failed', LVL_ERROR);
      Exit(-4);
    end;
  end
  else
  begin
    if 0 <> vServoObj.S1_ServoON(false, 5000) then
    begin
      vlog('Pedal Servo On Failed', LVL_ERROR);
      Exit(-4);
    end;
  end;
end;

function pedal_enable_run(const AEnable: Boolean): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);

  if not vServoObj.S7IsAutoMode then
  begin
    vlog('Servo control mode is manual mode, switch the mode on the door first', LVL_ERROR);
    Exit(-3);
  end;

  if AEnable then
  begin
    if 0 <> vServoObj.S1_Run_On() then
    begin
      vlog('Pedal Servo Enable Run Failed', LVL_ERROR);
      Exit(-4);
    end;
  end
  else
  begin
    if 0 <> vServoObj.S1_Run_Off() then
    begin
      vlog('Pedal Servo Disable Run Failed', LVL_ERROR);
      Exit(-5);
    end;
  end;
end;

function pedal_go_step_syn(const ARelPositionMM: float32; const ASpeedMMpS: float32; const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_step_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoRelPos_AutoMode_Syn(ARelPositionMM, ASpeedMMpS, ATimeout);
  end;

end;

function pedal_go_step_asyn(const ARelPositionMM: float32; const ASpeedMMpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_step_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoRelPos_AutoMode_Asyn(ARelPositionMM, ASpeedMMpS);
  end;

end;

function pedal_go_position_syn(const AAbsPositionMM: float32; const ASpeedMMpS: float32; const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_position_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoAbsPos_AutoMode_Syn(AAbsPositionMM, ASpeedMMpS, ATimeout);
  end;

end;

function pedal_go_position_asyn(const AAbsPositionMM: float32; const ASpeedMMpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_position_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoAbsPos_AutoMode_Asyn(AAbsPositionMM, ASpeedMMpS);
  end;

end;

function pedal_sys_position_asyn(const AAbsPositionMM: float32; const ASpeedMMpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if vServoObj.PedalIsSysMode then
    result := vServoObj.S1_GoAbsPos_AutoMode_Asyn(AAbsPositionMM, ASpeedMMpS)
  else
  begin
    vLog('pedal_sys_position_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent is not actived, using pedal_position_auto_mode(true) to enable first', LVL_ERROR);
    Result := -20;
  end;
end;

function pedal_go_step_percent_syn(const ARelPositionPercent: float32; const ASpeedMMpS: float32; const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);

  var AStepMM: Single := ARelPositionPercent * vServoObj.S1MaxPosition / 100;
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_step_percent_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoRelPos_AutoMode_Syn(AStepMM, ASpeedMMpS, ATimeout);
  end;

end;

function pedal_go_step_percent_asyn(const ARelPositionPercent: float32; const ASpeedMMpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);

  var AStepMM: Single := ARelPositionPercent * vServoObj.S1MaxPosition / 100;
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_step_percent_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoRelPos_AutoMode_Asyn(AStepMM, ASpeedMMpS);
  end;

end;

function pedal_go_position_percent_syn(const AAbsPositionPercent: float32; const ASpeedMMpS: float32; const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);

  var AAbsPositionMM: Single := AAbsPositionPercent * vServoObj.S1MaxPosition / 100;
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_position_percent_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoAbsPos_AutoMode_Syn(AAbsPositionMM, ASpeedMMpS, ATimeout);
  end

end;

function pedal_go_position_percent_asyn(const AAbsPositionPercent: float32; const ASpeedMMpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);

  var AAbsPositionMM: Single := AAbsPositionPercent * vServoObj.S1MaxPosition / 100;
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_position_percent_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoAbsPos_AutoMode_Asyn(AAbsPositionMM, ASpeedMMpS);
  end;
end;

function pedal_sys_position_percent_asyn(const AAbsPositionPercent: float32; const ASpeedMMpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  var AAbsPositionMM: Single := AAbsPositionPercent * vServoObj.S1MaxPosition / 100;
  if vServoObj.PedalIsSysMode then
    result := vServoObj.S1_GoAbsPos_AutoMode_Asyn(AAbsPositionMM, ASpeedMMpS)
  else
  begin
    vLog('pedal_sys_position_percent_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent is not actived, using pedal_position_auto_mode(true) to enable first', LVL_ERROR);
    Result := -20;
  end;
end;

function pedal_go_home_syn(const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_home_syn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoZero_Syn(ATimeout);
  end;
end;

function pedal_go_home_asyn: s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if vServoObj.PedalIsSysMode then
  begin
    vLog('pedal_go_home_asyn: pedal controlled by tio.PedalTargetPosition/PedalTargetPercent, using pedal_position_auto_mode(false) to disable first', LVL_ERROR);
    Result := -20;
  end
  else
  begin
    result := vServoObj.S1_GoZero_Asyn;
  end;
end;

function pedal_set_home(const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S1_SetZero(ATimeout);
end;

function pedal_go_auto_mode(const AEanble: Boolean): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  vServoObj.PedalIsSysMode := AEanble;
  result := 0;
end;

function rotate_servo_limit(const AMaxDegree: float32; const AMinDegree: float32; const AMaxSpeedDpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);

  vServoObj.S2MaxPosition := AMaxDegree;
  vServoObj.S2MinPosition := AMinDegree;
  vServoObj.S2MaxSpeed := AMaxSpeedDpS;
  Result := 0;
end;

function rotate_servo_on(const AEnable: Boolean): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if not vServoObj.S7IsAutoMode then
  begin
    vlog('Servo control mode is manual mode, switch the mode on the door first', LVL_ERROR);
    Exit(-3);
  end;

  if AEnable then
  begin
    if 0 <> vServoObj.S2_ServoON(true, 5000) then
    begin
      vlog('slope Servo On Failed', LVL_ERROR);
      Exit(-4);
    end;
  end
  else
  begin
    if 0 <> vServoObj.S2_ServoON(false, 5000) then
    begin
      vlog('slope Servo On Failed', LVL_ERROR);
      Exit(-4);
    end;
  end;
end;

function rotate_enable_run(const AEnable: Boolean): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if not vServoObj.S7IsAutoMode then
  begin
    vlog('Servo control mode is manual mode, switch the mode on the door first', LVL_ERROR);
    Exit(-3);
  end;

  if AEnable then
  begin
    if 0 <> vServoObj.S2_Run_On() then
    begin
      vlog('slope Servo Enable Run Failed', LVL_ERROR);
      Exit(-4);
    end;
  end
  else
  begin
    if 0 <> vServoObj.S2_Run_Off() then
    begin
      vlog('slope Servo Disable Run Failed', LVL_ERROR);
      Exit(-5);
    end;
  end;
end;

function rotate_go_step_syn(const ARelDegree: float32; const ASpeedDpS: float32; const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoRelPos_AutoMode_Syn(ARelDegree, ASpeedDpS, ATimeout);
end;

function rotate_go_step_asyn(const ARelDegree: float32; const ASpeedDpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoRelPos_AutoMode_Asyn(ARelDegree, ASpeedDpS);
end;

function rotate_go_position_syn(const AAbsDegree: float32; const ASpeedDpS: float32; const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoAbsPos_AutoMode_Syn(AAbsDegree, ASpeedDpS, ATimeout);
end;

function rotate_go_position_asyn(const AAbsDegree: float32; const ASpeedDpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoAbsPos_AutoMode_Asyn(AAbsDegree, ASpeedDpS);
end;

function rotate_go_home_syn(const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoZero_Syn(ATimeout);
end;

function rotate_go_home_asyn: s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoZero_Asyn;
end;

function rotate_set_home(const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_SetZero(ATimeout);
end;

function rotate_go_slope_step_syn(const ARelGradPercent: float32; const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoRelSlopGrad_AutoMode_Syn(ARelGradPercent, ATimeout);
end;

function rotate_go_slope_step_asyn(const ARelGradPercent: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoRelSlopGrad_AutoMode_Asyn(ARelGradPercent);
end;

function rotate_go_slope_syn(const AAbsGradPercent: float32; const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoAbsSlopGrad_AutoMode_Syn(AAbsGradPercent, ATimeout);
end;

function rotate_go_slope_asyn(const AAbsGradPercent: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoRelSlopGrad_AutoMode_Asyn(AAbsGradPercent);
end;

function rotate_go_mount_position_syn(const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoMountPos_AutoMode_Syn(ATimeout);
end;

function rotate_go_mount_position_asyn: s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S2_GoMountPos_AutoMode_ASyn;
end;

function rotate_set_slope_speed(const ASpeedDpS: float32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if (ASpeedDpS < 0) and (ASpeedDpS > 10) then
  begin
    vlog('The rotate servo slope run speed need in range [0,10], current setting is ' + ASpeedDpS.ToString + ' deg/s', lvl_error);
    exit(-2);
  end;

  vServoObj.S2SlopSpeed := ASpeedDpS;
  result := 0;
end;

function air_cylinder_push_out: s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S3_Go_Out;
end;

function air_cylinder_push_back: s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S3_Go_In;
end;

function air_cylinder_push_pressure(const ATargetPressureBar: single): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S3_Set_Target_Pressure(ATargetPressureBar);
end;

function turntable_enable_control: s32; cdecl;
begin
  if nil = vServoObj then
  begin
    vServoObj := TServo.Create(true);
  end;

  if not vServoObj.FSnap7IsLoaded then
  begin
    vServoObj.free;
    vServoObj := nil;
    vLog('Servo DLL Load Failed', LVL_ERROR);
    Exit(-1);
  end;

  if 0 <> vServoObj.S7_Connection then
  begin
    vlog('can not connect with servo system', LVL_ERROR);
    Exit(-2);
  end;

  if 0 <> vServoObj.S7_HandsShake(true, 10000) then
  begin
    vlog('handshake with servo system failed', LVL_ERROR);
    Exit(-3);
  end;

  if 0 <> vServoObj.S1_ServoON(true, 5000) then
  begin
    vlog('servo on failed', LVL_ERROR);
    Exit(-4);
  end;

  if 0 <> vServoObj.S1_Run_On() then
  begin
    vlog('servo on failed', LVL_ERROR);
    Exit(-5);
  end;
  vlog('enable turntable successfully', LVL_OK);
  Exit(0);
end;

function turntable_disable_control: s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  with vServoObj do
  begin
    if S7IsConnected then
    begin
      if S7IsFault then
      begin
        if 0 <> S7_ClearFault then
          vlog('Servo has fault and cannot be cleared', LVL_ERROR);
      end;

      if S1IsServoOn then
      begin
        if 0 <> S1_RunSpd_AutoMode_Syn(0, 2000) then
          vlog('set speed zero failed', LVL_ERROR);

        if 0 <> S1_ServoON(false, 5000) then
          vlog('servo off failed', LVL_ERROR);
      end;
      if 0 <> S7_Disconnection then
        vlog('disconnection wit servo failed', LVL_ERROR);
    end;
  end;
  if nil <> vServoObj then
  begin
    vServoObj.Free;
    vServoObj := nil;
  end;
  vlog('disable turntable successfully', LVL_OK);
  Exit(0);
end;

function turntable_run_speed_rpm_asyn(const ATargetSpeedRPM: single): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S1_RunSpd_AutoMode_Asyn(ATargetSpeedRPM);
end;

function turntable_run_speed_rpm_syn(const ATargetSpeedRPM: single; const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  result := vServoObj.S1_RunSpd_AutoMode_Syn(ATargetSpeedRPM, ATimeout);
end;

function turntable_run_speed_dps_asyn(const ATargetSpeedDPS: single): s32; cdecl;
var
  ASpeedRPM: Single;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  ASpeedRPM := ATargetSpeedDPS / 6.0;
  result := vServoObj.S1_RunSpd_AutoMode_Asyn(ASpeedRPM);
end;

function turntable_run_speed_dps_syn(const ATargetSpeedDPS: single; const ATimeout: u32): s32; cdecl;
var
  ASpeedRPM: Single;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  ASpeedRPM := ATargetSpeedDPS / 6.0;
  result := vServoObj.S1_RunSpd_AutoMode_Syn(ASpeedRPM, ATimeout);

end;

function turntable_run_centrifugal_acc_asyn(const ATargetAccelerationG: single; const AArmLengthMM: single): s32; cdecl;
var
  ASpeedRPM: Single;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if (AArmLengthMM < 90) or (AArmLengthMM > 160) then
  begin
    vLog('the arm lengthen should in rang [90, 160]mm', lvl_error);
    Exit(-10);
  end;
  if ATargetAccelerationG < 0 then
  begin
    vLog('the set g should greater than zero', lvl_error);
    Exit(-10);
  end;

  ASpeedRPM := Sqrt(ATargetAccelerationG * 9.8 / (AArmLengthMM / 1000.0)) * 30.0 / pi;
  result := vServoObj.S1_RunSpd_AutoMode_Asyn(ASpeedRPM);

end;

function turntable_run_centrifugal_acc_syn(const ATargetAccelerationG: single; const AArmLengthMM: single; const ATimeout: u32): s32; cdecl;
var
  ASpeedRPM: Single;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  if (AArmLengthMM < 90) or (AArmLengthMM > 160) then
  begin
    vLog('the arm lengthen should in rang [90, 160]mm', lvl_error);
    Exit(-10);
  end;
  if ATargetAccelerationG < 0 then
  begin
    vLog('the set g should greater than zero', lvl_error);
    Exit(-10);
  end;

  ASpeedRPM := Sqrt(ATargetAccelerationG * 9.8 / (AArmLengthMM / 1000.0)) * 30.0 / pi;
  result := vServoObj.S1_RunSpd_AutoMode_Syn(ASpeedRPM, ATimeout);

end;

function turntable_stop_run_asyn: s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  begin
    result := vServoObj.S1_RunSpd_AutoMode_Asyn(0);
  end;
end;

function turntable_stop_run_syn(const ATimeout: u32): s32; cdecl;
begin
  result := servo_check;
  if result <> 0 then
    Exit(result);
  begin
    result := vServoObj.S1_RunSpd_AutoMode_Syn(0, ATimeout);
  end;
end;

 {$ENDREGION}


{ TServo }

constructor TServo.Create(const AOnlyPedalServo: Boolean);
begin
  inherited Create;
  S7IsOnlyPedal := AOnlyPedalServo;

  if InitializeSnap7Api then
  begin
    vLog('Load Snap7 successful', LVL_OK);
    FSnap7IsLoaded := True;
  end
  else
  begin
    vLog('Load Snap7 failed', LVL_ERROR);
    FSnap7IsLoaded := false;
  end;
  RegisterSystemVars;

  FS7Client := TS7Client.Create;
  S7 := TS7Helper.Create;
  FS7IsConnected := false;
  FS7IsHandShaked := false;
//  FObjIsCreatedGUI := AIsCreatedGUI;

  FMonitorObj := TObject.Create;
  vHeartbeatThread := TThreadHeartbeat.Create(true);
//  if FObjIsCreatedGUI then
//    vLog('Servo Object is created by GUI', LVL_INFO)
//  else
//    vLog('Servo Object is created by MP API', LVL_INFO);
  vLog('TServo.Create: Servo Object is created', LVL_INFO);
  S1MaxSpeed := 500;
  S1MaxPosition := vTIOConfig.FServo1MaxPosition;
  S1MinPosition := vTIOConfig.FServo1MinPosition;
  S2MaxSpeed := 10;
  S2MaxPosition := 20;
  S2MinPosition := -20;
  FS2SlopSpeed := vTIOConfig.FServo2Speed;
  FS2MountPosition := vTIOConfig.FServo2MountAngle;
  //  vServoObj.FRemoteAddress := '192.168.1.1';
  FRemoteAddress := ansistring(vTIOConfig.FS7IPAddress);
  FPedalIsSysMode := False;
  S3MCMaxPressure := vTIOConfig.FMCMaxPressure;
  S3P2AFactor := vTIOConfig.FPressure2CurrentFactor;
  S3P2AOffset := vTIOConfig.FPressure2CurrentOffset;

//  vGetDataThread := TThreadGetData.Create(true);
end;

destructor TServo.Destroy;
begin
  if S7IsConnected then
  begin
    if S1IsReady then
      S1_Run_Off();
    if S1IsServoOn then
      S1_ServoON(false, 2000);
    if not S7IsOnlyPedal then
    begin
      if S2IsReady then
        S2_Run_Off();
      if S2IsServoOn then
        S2_ServoON(False, 2000);
    end;
    if S7IsHandShaked then
      S7_HandsShake(false, 2000);
    S7_Disconnection;
  end;

  if S7 <> nil then
  begin
    S7.Free;
    S7 := nil;
  end;

  if FS7Client <> nil then
  begin
    FS7Client.Free;
    FS7Client := nil;
  end;

//  FS7IsConnected := false;
//  FS7IsHandShaked := false;

  if FMonitorObj <> nil then
  begin
    FMonitorObj.Free;
    FMonitorObj := nil;
  end;

  if vHeartbeatThread <> nil then
  begin
    vHeartbeatThread.Heartbeatexit;
    vHeartbeatThread.Free;
    vHeartbeatThread := nil;
  end;

  if vGetDataThread <> nil then
  begin
    vGetDataThread.GetDataexit;
    vGetDataThread.Free;
    vGetDataThread := nil;
  end;

  UnregisterSystemVars;

  FinalizeSnap7Api;

  inherited;
end;

//procedure TServo.OnSystemVarChanged_Int32(const AVar: TSystemVar);
//begin
//   vLog('Int32 changed: ' + avar.Value);
//end;
//
//procedure TServo.OnSystemVarChanged_Str(const AVar: TSystemVar);
//begin
//  vLog('String changed: ' + avar.Value);
//end;

function TServo.RegisterInternalVar(const AName, AComments: string; const AIsReadOnly: boolean; const AType: TSystemVarType): tsystemvar;
begin
  result := TSystemVar.CreateWithProperties(AName, GROUP_NAME_SERVO, AComments, 'TIO Plugin', AType, AIsReadOnly, 0, 1);
  if not vSystemVarManager.AddInternalVar(result) then
  begin
    vLog(GetTopStackInfo + vlang.GetLang(LANG_ERROR__REG_SYSTEM_VAR_FAILED, 'Utils') + ': ' + result.CompleteName, LVL_ERROR);
    Result.Free;
    Result := nil;
  end;
end;

procedure TServo.RegisterSystemVars;
begin
  if RegisterInternalVar('PedalSpeed', 'Servo Pedal Speed', true, svtDouble) <> nil then
  begin

    //vSystemVarManager.RegisterOnVarChangedEvent(GROUP_NAME_DEMO + '.i32', OnSystemVarChanged_Int32);
  end;
  if RegisterInternalVar('PedalPosition', 'Servo Pedal Position', true, svtDouble) <> nil then
  begin

    //vSystemVarManager.RegisterOnVarChangedEvent(GROUP_NAME_DEMO + '.i32', OnSystemVarChanged_Int32);
  end;
  if RegisterInternalVar('RotateDegree', 'Servo Slope Rotate Degree', true, svtDouble) <> nil then
  begin

    //vSystemVarManager.RegisterOnVarChangedEvent(GROUP_NAME_DEMO + '.i32', OnSystemVarChanged_Int32);
  end;
  if RegisterInternalVar('SlopeGrad', 'Servo Slope Gradient', true, svtDouble) <> nil then
  begin

    //vSystemVarManager.RegisterOnVarChangedEvent(GROUP_NAME_DEMO + '.i32', OnSystemVarChanged_Int32);
  end;
end;

function TServo.S7_ClearFault(const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  AWriteByte := 0;
  if not S7IsHandShaked then
  begin
    vLog('S7_ClearFault: HandShake needed before Servo On', LVL_ERROR);
    exit(-1);
  end;
  // todo when to get power status

  if not S7IsPowerOn then
  begin
    vLog('S7_ClearFault: Power is off', LVL_ERROR);
    exit(-1);
  end;

  // todo when to get Device Fault Status

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS7Reset, @AWriteByte, false) then
  begin
    vLog('S7_ClearFault: S7 Write servo reset address error', LVL_ERROR);
    exit(-2);
  end;

  ATime := 0;
  while true do
  begin
    if not S1IsFault then
    begin
      vLog('S7_ClearFault: clear fault Successful', LVL_OK);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S7_ClearFault: Clear fault timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S7_Connection: s32;
var
  PingTime: integer;
begin
  PingTime := 0;
  S7LastError := FS7Client.SetParam(p_i32_PingTimeout, @PingTime);
  if S7LastError <> 0 then
  begin
    exit(-1);
  end;

  FS7Client.SetConnectionType(1);
  S7LastError := FS7Client.ConnectTo(FRemoteAddress, 0, 0);
  Sleep(50);
  // Elapse;
  if S7LastError <> 0 then
  begin
    vLog('S7_Connection: Servo Connect error, can not find device under IP: ' + string(FRemoteAddress), LVL_ERROR);
    S7IsConnected := False;
  end
  else
  begin
    vLog('S7_Connection: Servo Connect Successful, device IP is: ' + string(FRemoteAddress), LVL_OK);
    vGetDataThread := TThreadGetData.Create(false);  //to check
    S7IsConnected := True;
  end;
  Result := S7LastError;
end;

function TServo.S7_Disconnection: s32;
begin
  // todo         handshake
  if vGetDataThread <> nil then
  begin
    vGetDataThread.GetDataexit;
    vGetDataThread.Free;
    vGetDataThread := nil;
  end;
  S7LastError := FS7Client.Disconnect;
  if S7LastError <> 0 then
  begin
    vLog('S7_Disconnection: Servo disconnect error', LVL_ERROR);
  end
  else
  begin
    vLog('S7_Disconnection: Servo disconnect Successful. Device IP is:' + string(FRemoteAddress), LVL_OK);
  end;

  S7IsConnected := false;
  Result := S7LastError;
end;

function TServo.S7_GetAllData: s32;
//var
//  AData: u16;
begin
  if not S7IsConnected then
  begin
    vLog('S7_GetAllData: Connected is needed', LVL_ERROR);
    exit(-1);
  end;

  if 0 = S7Read(AddrGetAllData, @FS7Buffer, false) then
  begin
    // todo alldata
//    AData := S7.ValWord[@FS7Buffer[0]];
//    // AData := S7.ValInt[@FS7Buffer[0]];
//    if AData = $00FF then
//      S7IsHandShaked := true
//    else
//      S7IsHandShaked := false;
////    vLog('AData is ' + IntToStr(AData),LVL_INFO);
    S7IsHandShaked := S7.ValBit[@FS7Buffer[0], 0];
    S7IsPowerOn := S7.ValBit[@FS7Buffer[0], 1];
    S7IsAutoMode := S7.ValBit[@FS7Buffer[0], 2];
    S7IsFault := S7.ValBit[@FS7Buffer[0], 3];
    S1IsServoOn := S7.ValBit[@FS7Buffer[0], 4];
    S1ZeroExisted := S7.ValBit[@FS7Buffer[0], 5];
    S1IsReady := S7.ValBit[@FS7Buffer[0], 6];
    // S1Running := S7.ValBit[@FS7Buffer[2], 6];
    S1RunFinished := S7.ValBit[@FS7Buffer[0], 7];
    S1IsFault := S7.ValBit[@FS7Buffer[1], 0];
    // todo check the address
    // S1AutoMode := S7.ValBit[@FS7Buffer[3], 7];
    // S2AutoMode := S7.ValBit[@FS7Buffer[3], 8];

    S1ActPostion := S7.ValReal[@FS7Buffer[2]];
    S1ActSpeed := S7.ValReal[@FS7Buffer[6]];
    if not S7IsOnlyPedal then
    begin
      S2IsServoOn := S7.ValBit[@FS7Buffer[1], 1];
      S2ZeroExisted := S7.ValBit[@FS7Buffer[1], 2];
      S2IsReady := S7.ValBit[@FS7Buffer[1], 3];
    // S2Running := S7.ValBit[@FS7Buffer[3], 4];
      S2RunFinished := S7.ValBit[@FS7Buffer[1], 4];
      S2IsFault := S7.ValBit[@FS7Buffer[1], 5];
      S2ActPostion := S7.ValReal[@FS7Buffer[10]];
      S2ActSpeed := S7.ValReal[@FS7Buffer[14]];
    end;

    Result := 0;
  end
  else
  begin
    Result := -1;
  end;
end;

function TServo.S7_HandsShake(const AEnable: boolean; const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u16;
begin
  AWriteByte := 0;

  if not S7IsConnected then
  begin
    vLog('S7_HandsShake: servo not connected', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := AEnable;

  if 0 <> S7Write(AddrSetHandShake, @AWriteByte, false) then
  begin
    vLog('S7_HandsShake: S7 Write Handshake address error', LVL_ERROR);
    exit(-2);
  end;

  ATime := 0;

  if AEnable then
  begin
    while true do
    begin

      if S7IsHandShaked then
      begin
        vLog('S7_HandsShake: Servo Handshake Set Success', LVL_OK);
        exit(0);
      end;

      Sleep(1);
      ATime := ATime + 1;
      if (ATime > ATimeout) then
      begin
        vLog('S7_HandsShake: Servo Handshake is Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
        exit(-3);
      end;
    end;
  end
  else
  begin
    vHeartbeatThread.HeartbeatSuspend;
    vLog('S7_HandsShake: Servo Handshake Reset Success', LVL_OK);
    exit(0);
  end;
end;

function TServo.S7Read(const AField: TDataRecord; const pData: Pointer; const Async: boolean): s32;
begin
  if System.TMonitor.Enter(FMonitorObj, 1000) then
  begin

    try
      if Async then
        S7LastError := FS7Client.AsReadArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData)
      else
        S7LastError := FS7Client.ReadArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);

      if S7LastError = 0 then
      begin
        if Async then
          S7WaitCompletion;
        // TimeElapse;
      end
      else // TimeElapse;
        vLog('S7Read: Servo Read Action Error', LVL_ERROR);
      Result := S7LastError;
    finally
      System.TMonitor.exit(FMonitorObj);
    end;
  end
  else
  begin
    vLog('S7Read: try to read action timeout,can not get MonitorObj', LVL_ERROR);
    exit(-1);
  end;
end;

//function TServo.S7ReadBool(const AReadField: TDataRecord; const pGetBool: pBoolean): s32;
//var
//  AReadByte: Byte;
//begin
//  AReadByte := 0;
//  if not S7IsHandShaked then
//  begin
//    vLog('S7ReadBool: Handshake is needed', LVL_ERROR);
//    exit(-1);
//  end;
//  if 0 <> S7Read(AReadField, @AReadByte, false) then
//  begin
//    vLog('S7ReadBool: S7 read bit error', LVL_ERROR);
//    exit(-2);
//  end
//  else
//  begin
//    pGetBool^ := S7.ValBit[@AReadByte, 0];
//    exit(0);
//  end;
//end;


{S1 Action}
function TServo.S1_GoAbsPos_AutoMode_Asyn(const AAbsPosMM, ASpeedMMS: Single): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_GoAbsPos_AutoMode_Asyn: Servo 1 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S1_GoAbsPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  if AAbsPosMM > S1MaxPosition then
  begin
    ASetPosition := S1MaxPosition;
    vLog('S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is greater than the max value(' + S1MaxPosition.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if AAbsPosMM < S1MinPosition then
  begin
    ASetPosition := S1MinPosition;
    vLog('S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is smaller than the min value(' + S1MinPosition.ToString + '), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := AAbsPosMM;

  if ASpeedMMS > S1MaxSpeed then
  begin
    ASetSpeed := S1MaxSpeed;
    vLog('S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is greater than the max value(' + S1MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedMMS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S1_GoAbsPos_AutoMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedMMS;

  S1TargetPositionAuto := ASetPosition;
  S1TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_GoAbsPos_AutoMode_Asyn: S1 auto mode goto abs. position write error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    if not PedalIsSysMode then
      vLog('S1_GoAbsPos_AutoMode_Asyn: S1 auto mode goto abs. position send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S1_GoAbsPos_AutoMode_Syn(const AAbsPosMM, ASpeedMMS: Single; const ATimeout: u32): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  ATime: u16;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_GoAbsPos_AutoMode_Syn: Servo 1 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S1_GoAbsPos_AutoMode_Syn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  if AAbsPosMM > S1MaxPosition then
  begin
    ASetPosition := S1MaxPosition;
    vLog('S1_GoAbsPos_AutoMode_Syn: S1 Set positon is greater than the max value(' + S1MaxPosition.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if AAbsPosMM < S1MinPosition then
  begin
    ASetPosition := S1MinPosition;
    vLog('S1_GoAbsPos_AutoMode_Syn: S1 Set positon is smaller than the min value(' + S1MinPosition.ToString + '), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := AAbsPosMM;

  if ASpeedMMS > S1MaxSpeed then
  begin
    ASetSpeed := S1MaxSpeed;
    vLog('S1_GoAbsPos_AutoMode_Syn: S1 Set positon is greater than the max value(' + S1MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedMMS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S1_GoAbsPos_AutoMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedMMS;

  S1TargetPositionAuto := ASetPosition;
  S1TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_GoAbsPos_AutoMode_Syn: S1 auto mode goto abs. position write error', LVL_ERROR);
    exit(-2);
  end;

  S1RunFinished := False;
  ATime := 0;
  while true do
  begin
    if S1RunFinished and (abs(S1TargetPositionAuto - S1ActPostion) < PositionMaxTol) then
    begin
      vLog('S1_GoAbsPos_AutoMode_Syn: S1 auto mode goto abs. position finished', LVL_INFO);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_GoAbsPos_AutoMode_Syn: go abs position timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S1_RunSpd_AutoMode_Asyn(const ASpeedRPM: Single): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetSpeed: Single;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_RunSpd_AutoMode_Asyn: Servo 1 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S1_RunSpd_AutoMode_Asyn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  if ASpeedRPM > 450 then
  begin
    ASetSpeed := 450;
    vLog('S1_RunSpd_AutoMode_Asyn: S1 Set speed is greater than the max value(450 rpm), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedRPM < -450 then
  begin
    ASetSpeed := -450;
    vLog('S1_RunSpd_AutoMode_Asyn: S1 Set positon is smaller than the min value(-450 rpm), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedRPM;

  S1TargetPositionAuto := 0;
  S1TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := 0;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_RunSpd_AutoMode_Asyn: S1 auto mode run speed write error', LVL_ERROR);
    exit(-2);
  end;
  Exit(0);
//  else
//  begin
//    if not PedalIsSysMode then
//      vLog('S1_RunSpd_AutoMode_Asyn: S1 auto mode run speed send out', LVL_INFO);
//    exit(0);
//  end;
end;

function TServo.S1_RunSpd_AutoMode_Syn(const ASpeedRPM: Single; const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetSpeed: Single;
  ATime: u16;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_RunSpd_AutoMode_Syn: Servo 1 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S1_RunSpd_AutoMode_Syn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  if ASpeedRPM > 450 then
  begin
    ASetSpeed := 450;
    vLog('S1_RunSpd_AutoMode_Syn: S1 Set speed is greater than the max value(450 rpm), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedRPM < -450 then
  begin
    ASetSpeed := -450;
    vLog('S1_RunSpd_AutoMode_Syn: S1 Set speed is smaller than the min value(-450 rpm), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedRPM;

  S1TargetPositionAuto := 0;
  S1TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := 0;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_RunSpd_AutoMode_Syn: S1 auto mode run target speed write error', LVL_ERROR);
    exit(-2);
  end;

  ATime := 0;
  while true do
  begin
    if (abs(S1TargetSpeedAuto - S1ActSpeed) < 0.1) then
    begin
      vLog('S1_RunSpd_AutoMode_Syn: S1 auto mode run target speed finished', LVL_INFO);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_RunSpd_AutoMode_Syn: S1 auto mode run to target speed timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;

end;

function TServo.S1_GoAbsPos_MMode_Asyn(const AAbsPosMM, ASpeedMMS: Single): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_GoAbsPostion_MMode_Asyn: Servo 1 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if S7IsAutoMode then
  begin
    vLog('S1_GoAbsPostion_MMode_Asyn: Servo is in auto mode, switch to manual first', LVL_ERROR);
    exit(-1);
  end;

  if AAbsPosMM > S1MaxPosition then
  begin
    ASetPosition := S1MaxPosition;
    vLog('S1_GoAbsPostion_MMode_Asyn: S1 Set positon is greater than the max value(' + S1MaxPosition.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if AAbsPosMM < S1MinPosition then
  begin
    ASetPosition := S1MinPosition;
    vLog('S1_GoAbsPostion_MMode_Asyn: S1 Set positon is smaller than the min value(' + S1MinPosition.ToString + '), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := AAbsPosMM;

  if ASpeedMMS > S1MaxSpeed then
  begin
    ASetSpeed := S1MaxSpeed;
    vLog('S1_GoAbsPostion_MMode_Asyn: S1 Set positon is greater than the max value(' + S1MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedMMS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S1_GoAbsPostion_MMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedMMS;

  S1TargetPositionManual := ASetPosition;
  S1TargetSpeedManual := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1MPosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_GoAbsPostion_MMode_Asyn: S1 manual mode goto abs. position write error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S1_GoAbsPostion_MMode_Asyn: S1 manual mode goto abs. position send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S1_GoAbsPos_MMode_Syn(const AAbsPosMM, ASpeedMMS: Single; const ATimeout: u32): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  ATime: u16;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_GoAbsPostion_MMode_Syn: Servo 1 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if S7IsAutoMode then
  begin
    vLog('S1_GoAbsPostion_MMode_Syn: Servo is in auto mode, switch to manual first', LVL_ERROR);
    exit(-1);
  end;

  if AAbsPosMM > S1MaxPosition then
  begin
    ASetPosition := S1MaxPosition;
    vLog('S1_GoAbsPostion_MMode_Syn: S1 Set positon is greater than the max value(' + S1MaxPosition.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if AAbsPosMM < S1MinPosition then
  begin
    ASetPosition := S1MinPosition;
    vLog('S1_GoAbsPostion_MMode_Syn: S1 Set positon is smaller than the min value(' + S1MinPosition.ToString + '), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := AAbsPosMM;

  if ASpeedMMS > S1MaxSpeed then
  begin
    ASetSpeed := S1MaxSpeed;
    vLog('S1_GoAbsPostion_MMode_Syn: S1 Set positon is greater than the max value(' + S1MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedMMS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S1_GoAbsPostion_MMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedMMS;

  S1TargetPositionManual := ASetPosition;
  S1TargetSpeedManual := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1MPosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_GoAbsPostion_MMode_Syn: S1 manual mode goto abs. position write error', LVL_ERROR);
    exit(-2);
  end;

  S1RunFinished := False;
  ATime := 0;
  while true do
  begin
    if S1RunFinished and (abs(S1TargetPositionManual - S1ActPostion) < PositionMaxTol) then
    begin
      vLog('S1_GoAbsPostion_MMode_Syn: S1 manual mode goto abs. position finished', LVL_INFO);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_GoAbsPostion_MMode_Syn: go abs position timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

// function TServo.S1_GetAutoPosition(const pPosition: PSingle): s32;
// begin
//
// end;
//
// function TServo.S1_GetAutoSpeed(const pSpeed: PSingle): s32;
// begin
//
// end;
//
// function TServo.S1_GetManualPosition(const pPosition: PSingle): s32;
// begin
//
// end;
//
// function TServo.S1_GetManualSpeed(const pSpeed: PSingle): s32;
// begin
//
// end;
//
// function TServo.S1_GetReadyStatus(const pReadyStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S1_GetRunFinishedStatus(const pRunFinishedStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S1_GetRunningStatus(const pRunningStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S1_GetServoFaultStatus(const pServoFaultStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S1_GetServoMode(const pIsAutoMode: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S1_GetServoStatus(const pServoStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S1_GetZeroExisted(const pZeroExisted: PBoolean): s32;
// begin
//
// end;

function TServo.S1_GoZero_Asyn: s32;
var
  AWriteByte: Byte;
begin
  AWriteByte := 0;
  if not S1IsReady then
  begin
    vLog('S1_GoZero_Asyn: S1 not ready', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS1GoZero, @AWriteByte, false) then
  begin
    vLog('S1_GoZero_Asyn: S7 Write go zero error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S1_GoZero_Asyn: S1 go zero comand send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S1_GoZero_Syn(const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  AWriteByte := 0;
  if not S1IsReady then
  begin
    vLog('S1_GoZero_Syn: S1 not ready', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS1GoZero, @AWriteByte, false) then
  begin
    vLog('S1_GoZero_Syn: S7 Write S1 go zero address error', LVL_ERROR);
    exit(-2);
  end;

  //to check
  S1RunFinished := False;

  ATime := 0;
  while true do
  begin
    if S1RunFinished and (abs(S1ActPostion) < PositionMaxTol) then
      exit(0);

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_GoZero_Syn: Servo Go Zero Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S1_Manual_JogIn: s32;
var
  AWriteByte: Byte;
begin
  AWriteByte := 0;
  if not S1IsReady then
  begin
    vLog('S1_Manual_JogIn: S1 is not ready', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS1JogB, @AWriteByte, false) then
  begin
    vLog('S1_Manual_JogIn: S7 Write bit error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S1_Manual_JogIn: S1 Jog In', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S1_Manual_JogOut: s32;
var
  AWriteByte: Byte;
begin
  AWriteByte := 0;

  if not S1IsReady then
  begin
    vLog('S1_Manual_JogOut: S1 is not ready', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS1JogF, @AWriteByte, false) then
  begin
    vLog('S1_Manual_JogOut: S7 Write bit error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S1_Manual_JogOut: S1 Jog Out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S1_GoRelPos_AutoMode_Asyn(const ARelPosMM, ASpeedMMS: Single): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_GoRelPos_AutoMode_Asyn: Servo is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S1_GoRelPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  ASetPosition := S1ActPostion + ARelPosMM;

  if ASetPosition > S1MaxPosition then
  begin
    ASetPosition := S1MaxPosition;
    vLog('S1_GoRelPos_AutoMode_Asyn: S1 Set positon is greater than the max value, and the target value used the max value instead', LVL_WARNING);
  end
  else if ASetPosition < S1MinPosition then
  begin
    ASetPosition := S1MinPosition;
    vLog('S1_GoRelPos_AutoMode_Asyn: S1 Set positon is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := ASetPosition;

  if ASpeedMMS > S1MaxSpeed then
  begin
    ASetSpeed := S1MaxSpeed;
    vLog('S1_GoRelPos_AutoMode_Asyn: S1 Set positon is greater than the max value(' + S1MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedMMS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S1_GoRelPos_AutoMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedMMS;

  S1TargetPositionAuto := ASetPosition;
  S1TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_GoRelPos_AutoMode_Asyn: S1 auto mode write speed error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S1_GoRelPos_AutoMode_Asyn: S1 auto mode goto rel. position send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S1_GoRelPos_AutoMode_Syn(const ARelPosMM, ASpeedMMS: Single; const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  ATime: u16;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_GoRelPos_AutoMode_Syn: Servo is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S1_GoRelPos_AutoMode_Syn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  ASetPosition := S1ActPostion + ARelPosMM;

  if ASetPosition > S1MaxPosition then
  begin
    ASetPosition := S1MaxPosition;
    vLog('S1_GoRelPos_AutoMode_Syn: S1 Set positon is greater than the max value, and the target value used the max value instead', LVL_WARNING);
  end
  else if ASetPosition < S1MinPosition then
  begin
    ASetPosition := S1MinPosition;
    vLog('S1_GoRelPos_AutoMode_Syn: S1 Set positon is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := ASetPosition;

  if ASpeedMMS > S1MaxSpeed then
  begin
    ASetSpeed := S1MaxSpeed;
    vLog('S1_GoRelPos_AutoMode_Syn: S1 Set positon is greater than the max value(' + S1MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedMMS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S1_GoRelPos_AutoMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedMMS;

  S1TargetPositionAuto := ASetPosition;
  S1TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_GoRelPos_AutoMode_Syn: S1 auto mode write speed error', LVL_ERROR);
    exit(-2);
  end;

  S1RunFinished := False;
  ATime := 0;
  while true do
  begin
    if S1RunFinished and (abs(S1TargetPositionAuto - S1ActPostion) < PositionMaxTol) then
    begin
      vLog('S1_GoRelPos_AutoMode_Syn: S1 auto mode goto rel. position finished', LVL_INFO);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_GoRelPos_AutoMode_Syn: go rel. position timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S1_GoRelPos_MMode_Asyn(const ARelPosMM, ASpeedMMS: Single): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_GoRelPos_MMode_Asyn: Servo is not ready', LVL_ERROR);
    exit(-1);
  end;

  if S7IsAutoMode then
  begin
    vLog('S1_GoRelPos_MMode_Asyn: Servo is in auto mode, switch to manual first', LVL_ERROR);
    exit(-1);
  end;

  ASetPosition := S1ActPostion + ARelPosMM;

  if ASetPosition > S1MaxPosition then
  begin
    ASetPosition := S1MaxPosition;
    vLog('S1_GoRelPos_MMode_Asyn: S1 Set positon is greater than the max value, and the target value used the max value instead', LVL_WARNING);
  end
  else if ASetPosition < S1MinPosition then
  begin
    ASetPosition := S1MinPosition;
    vLog('S1_GoRelPos_MMode_Asyn: S1 Set positon is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := ASetPosition;

  if ASpeedMMS > S1MaxSpeed then
  begin
    ASetSpeed := S1MaxSpeed;
    vLog('S1_GoRelPos_MMode_Asyn: S1 Set positon is greater than the max value(' + S1MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedMMS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S1_GoRelPos_MMode_Asyn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedMMS;

  S1TargetPositionManual := ASetPosition;
  S1TargetSpeedManual := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1MPosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_GoRelPos_MMode_Asyn: S1 manual mode write speed error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S1_GoRelPos_MMode_Asyn: S1 manual mode goto rel. position send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S1_GoRelPos_MMode_Syn(const ARelPosMM, ASpeedMMS: Single; const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  ATime: u16;
  i: Integer;
begin
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S1IsReady then
  begin
    vLog('S1_GoRelPos_MMode_Syn: Servo is not ready', LVL_ERROR);
    exit(-1);
  end;

  if S7IsAutoMode then
  begin
    vLog('S1_GoRelPos_MMode_Syn: Servo is in auto mode, switch to manual first', LVL_ERROR);
    exit(-1);
  end;

  ASetPosition := S1ActPostion + ARelPosMM;

  if ASetPosition > S1MaxPosition then
  begin
    ASetPosition := S1MaxPosition;
    vLog('S1_GoRelPos_MMode_Syn: S1 Set positon is greater than the max value, and the target value used the max value instead', LVL_WARNING);
  end
  else if ASetPosition < S1MinPosition then
  begin
    ASetPosition := S1MinPosition;
    vLog('S1_GoRelPos_MMode_Syn: S1 Set positon is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := ASetPosition;

  if ASpeedMMS > S1MaxSpeed then
  begin
    ASetSpeed := S1MaxSpeed;
    vLog('S1_GoRelPos_MMode_Syn: S1 Set positon is greater than the max value(' + S1MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedMMS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S1_GoRelPos_MMode_Syn: S1 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedMMS;

  S1TargetPositionManual := ASetPosition;
  S1TargetSpeedManual := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS1MPosSpd, @AWriteByte[0], false) then
  begin
    vLog('S1_GoRelPos_MMode_Syn: S1 manual mode write speed error', LVL_ERROR);
    exit(-2);
  end;

  S1RunFinished := False;
  ATime := 0;
  while true do
  begin
    if S1RunFinished and (abs(S1TargetPositionManual - S1ActPostion) < PositionMaxTol) then
    begin
      vLog('S1_GoRelPos_MMode_Syn: S1 manual mode goto rel. position finished', LVL_INFO);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_GoRelPos_MMode_Syn: go rel. position timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

//function TServo.S1_Run_Asyn: s32;
//var
//  AWriteByte: Byte;
//  ATime: s32;
//begin
//  // if not S7IsPowerOn then
//  // begin
//  // vLog('Power is off', LVL_ERROR);
//  // Exit(-1);
//  // end;
//  //
//  // //todo check status
//
//  if S7IsFault then
//  begin
//    vLog('S1_Run_Asyn: Device has fault', LVL_ERROR);
//    exit(-1);
//  end;
//
//  if not S1IsServoOn then
//  begin
//    vLog('S1_Run_Asyn: S1 need Servo On First', LVL_ERROR);
//    exit(-1);
//  end;
//
//  if not S1ZeroExisted then
//  begin
//    vLog('S1_Run_Asyn: S1 not ready', LVL_ERROR);
//    exit(-1);
//  end;
//
//  if S1IsFault then
//  begin
//    vLog('S1_Run_Asyn: S1 has fault', LVL_ERROR);
//    exit(-1);
//  end;
//
//  S7.ValBit[@AWriteByte, 0] := true;
//
//  if 0 <> S7Write(AddrSetS1Start, @AWriteByte, false) then
//  begin
//    vLog('S1_Run_Asyn: S7 Write S1 start address error', LVL_ERROR);
//    exit(-2);
//  end
//  else
//  begin
//    vLog('S1_Run_Asyn: S7 Send Start Comand', LVL_INFO);
//    exit(0);
//  end;
//
//end;

function TServo.S1_Run_On(const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  AWriteByte := 0;
  if not S1IsServoOn then
  begin
    vLog('S1_Run_Syn: S1 need Servo On First', LVL_ERROR);
    exit(-1);
  end;

  PedalIsSysMode := False;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS1Start, @AWriteByte, false) then
  begin
    vLog('S1_Run_Syn: S7 Write S1 start address error', LVL_ERROR);
    exit(-2);
  end;

  ATime := 0;
  while true do
  begin
    if S1IsReady then
      exit(0);

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_Run_Syn: Servo Start Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S1_ServoON(const AEnable: boolean; const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  AWriteByte := 0;
  if not S7IsHandShaked then
  begin
    vLog('S1_ServoON: HandShake needed before Servo On', LVL_ERROR);
    exit(-1);
  end;
  // todo when to get power status

  if not S7IsPowerOn then
  begin
    vLog('S1_ServoON: Power is off', LVL_ERROR);
    exit(-1);
  end;

  // todo when to get Device Fault Status
  {
  if S7IsFault then
  begin
    vLog('S1_ServoON: Device has fault', LVL_ERROR);
    exit(-1);
  end;
  }
  S7.ValBit[@AWriteByte, 0] := AEnable;

  if 0 <> S7Write(AddrSetS1ServoOn, @AWriteByte, false) then
  begin
    vLog('S1_ServoON: S7 Write S1 servo on address error', LVL_ERROR);
    exit(-2);
  end;

  ATime := 0;
  while true do
  begin
    if S1IsServoOn = AEnable then
    begin
      if AEnable then
        vLog('S1_ServoON: Servo On Successful', LVL_OK)
      else
        vLog('S1_ServoON: Servo Off Successful', LVL_OK);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_ServoON: Servo On/Off Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S1_SetZero(const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  AWriteByte := 0;
  if not S1IsServoOn then
  begin
    vLog('S1_SetZero: S1 need Servo On First', LVL_ERROR);
    exit(-1);
  end;

  if not S1RunFinished then
  begin
    vLog('S1_SetZero: S1 is running, cannot set zero', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS1SetZero, @AWriteByte, false) then
  begin
    vLog('S1_SetZero: S7 Write S1 set zero address error', LVL_ERROR);
    exit(-2);
  end;

  //to check
  S1ZeroExisted := False;

  ATime := 0;
  while true do
  begin
    if S1ZeroExisted and S1RunFinished then
      exit(0);

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_SetZero: Servo Set Zero Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

//function TServo.S1_Speed_AutoMode(const APostionMMS: Single): s32;
//var
//  AWriteByte: packed array[0..3] of Byte;
//  ASetSpeed: Single;
//begin
//  if not S7IsConnected then
//  begin
//    vLog('S1_Speed_AutoMode: Servo connect needed ', LVL_ERROR);
//    exit(-1);
//  end;
//
//  if APostionMMS > S1MaxSpeed then
//  begin
//    ASetSpeed := S1MaxSpeed;
//    vLog('S1_Speed_AutoMode: S1 Set speed is greater than the max value, and the target value used the max value instead', LVL_WARNING);
//  end
//  else if APostionMMS < 0 then
//  begin
//    ASetSpeed := 0;
//    vLog('S1_Speed_AutoMode: S1 Set speed is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
//  end
//  else
//    ASetSpeed := APostionMMS;
//
//  S7.ValReal[@AWriteByte] := ASetSpeed;
//
//  if 0 <> S7Write(AddrSetS1ASpd, @AWriteByte[0], false) then
//  begin
//    vLog('S1_Speed_AutoMode: S1 auto mode write speed error', LVL_ERROR);
//    exit(-2);
//  end
//  else
//  begin
//    S1TargetSpeedAuto := ASetSpeed;
//    exit(0);
//  end;
//
//end;

//function TServo.S1_Speed_ManualMode(const APostionMMS: Single): s32;
//var
//  AWriteByte: packed array[0..3] of Byte;
//  ASetSpeed: Single;
//begin
//  if not S7IsConnected then
//  begin
//    vLog('S1_Speed_ManualMode: Servo connect needed ', LVL_ERROR);
//    exit(-1);
//  end;
//
//  if APostionMMS > S1MaxSpeed then
//  begin
//    ASetSpeed := S1MaxSpeed;
//    vLog('S1_Speed_ManualMode: S1 Set speed is greater than the max value, and the target value used the max value instead', LVL_WARNING);
//  end
//  else if APostionMMS < 0 then
//  begin
//    ASetSpeed := 0;
//    vLog('S1_Speed_ManualMode: S1 Set speed is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
//  end
//  else
//    ASetSpeed := APostionMMS;
//
//  S7.ValReal[@AWriteByte] := ASetSpeed;
//
//  if 0 <> S7Write(AddrSetS1MSpd, @AWriteByte[0], false) then
//  begin
//    vLog('S1_Speed_ManualMode: S1 manual mode write speed error', LVL_ERROR);
//    exit(-2);
//  end
//  else
//  begin
//    S1TargetSpeedManual := ASetSpeed;
//    exit(0);
//  end;
//
//end;

//function TServo.S1_Stop_Asyn: s32;
//var
//  AWriteByte: Byte;
//begin
//  if not S1IsServoOn then
//  begin
//    vLog('S1_Stop_Asyn: S1 need Servo On First', LVL_ERROR);
//    exit(-1);
//  end;
//
//  S7.ValBit[@AWriteByte, 0] := true;
//
//  if 0 <> S7Write(AddrSetS1Stop, @AWriteByte, false) then
//  begin
//    vLog('S1_Stop_Asyn: S7 Write S1 stop address error', LVL_ERROR);
//    exit(-2);
//  end
//  else
//  begin
//    vLog('S1_Stop_Asyn: S7 Send Stop Comand', LVL_INFO);
//    exit(0);
//  end;
//
//end;

function TServo.S1_Run_Off(const ATimeout: u32): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  AWriteByte := 0;
  if not S1IsServoOn then
  begin
    vLog('S1_Stop_Syn: S1 is already Servo off', LVL_INFO);
    exit(0);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS1Stop, @AWriteByte, false) then
  begin
    vLog('S1_Stop_Syn: S7 Write S1 stop address error', LVL_ERROR);
    exit(-2);
  end;

  // to check

  ATime := 0;
  while true do
  begin
    if not S1IsReady then
      exit(0);

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S1_Stop_Syn: Servo Stop Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

{S2 Action}
function TServo.S2_GoAbsPos_AutoMode_Asyn(const AAbsPosDeg, ASpeedDegS: Single): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  i: Integer;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S2IsReady then
  begin
    vLog('S2_GoAbsPos_AutoMode_Asyn: Servo 1 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S2_GoAbsPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  if AAbsPosDeg > S2MaxPosition then
  begin
    ASetPosition := S2MaxPosition;
    vLog('S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is greater than the max value(' + S2MaxPosition.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if AAbsPosDeg < S2MinPosition then
  begin
    ASetPosition := S2MinPosition;
    vLog('S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is smaller than the min value(' + S2MinPosition.ToString + '), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := AAbsPosDeg;

  if ASpeedDegS > S2MaxSpeed then
  begin
    ASetSpeed := S2MaxSpeed;
    vLog('S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is greater than the max value(' + S2MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedDegS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S2_GoAbsPos_AutoMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedDegS;

  S2TargetPositionAuto := ASetPosition;
  S2TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS2APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position write error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S2_GoAbsPos_AutoMode_Syn(const AAbsPosDeg, ASpeedDegS: Single; const ATimeout: u32): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  ATime: u16;
  i: Integer;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S2IsReady then
  begin
    vLog('S2_GoAbsPos_AutoMode_Syn: Servo 2 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S2_GoAbsPos_AutoMode_Syn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  if AAbsPosDeg > S2MaxPosition then
  begin
    ASetPosition := S2MaxPosition;
    vLog('S2_GoAbsPos_AutoMode_Syn: S2 Set positon is greater than the max value(' + S2MaxPosition.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if AAbsPosDeg < S2MinPosition then
  begin
    ASetPosition := S2MinPosition;
    vLog('S2_GoAbsPos_AutoMode_Syn: S2 Set positon is smaller than the min value(' + S2MinPosition.ToString + '), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := AAbsPosDeg;

  if ASpeedDegS > S2MaxSpeed then
  begin
    ASetSpeed := S2MaxSpeed;
    vLog('S2_GoAbsPos_AutoMode_Syn: S2 Set positon is greater than the max value(' + S2MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedDegS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S2_GoAbsPos_AutoMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedDegS;

  S2TargetPositionAuto := ASetPosition;
  S2TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS2APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S2_GoAbsPos_AutoMode_Syn: S2 auto mode goto abs. position write error', LVL_ERROR);
    exit(-2);
  end;

  S2RunFinished := False;
  ATime := 0;
  while true do
  begin
    if S2RunFinished and (abs(S2TargetPositionAuto - S2ActPostion) < PositionMaxTol) then
    begin
      vLog('S2_GoAbsPos_AutoMode_Syn: S2 auto mode goto abs. position finished', LVL_INFO);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S2_GoAbsPos_AutoMode_Syn: go abs position timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S2_GoAbsPos_MMode_Asyn(const AAbsPosDeg, ASpeedDegS: Single): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  i: Integer;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S2IsReady then
  begin
    vLog('S2_GoAbsPostion_MMode_Asyn: Servo 2 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if S7IsAutoMode then
  begin
    vLog('S2_GoAbsPostion_MMode_Asyn: Servo is in auto mode, switch to manual first', LVL_ERROR);
    exit(-1);
  end;

  if AAbsPosDeg > S2MaxPosition then
  begin
    ASetPosition := S2MaxPosition;
    vLog('S2_GoAbsPostion_MMode_Asyn: S2 Set positon is greater than the max value(' + S2MaxPosition.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if AAbsPosDeg < S2MinPosition then
  begin
    ASetPosition := S2MinPosition;
    vLog('S2_GoAbsPostion_MMode_Asyn: S2 Set positon is smaller than the min value(' + S2MinPosition.ToString + '), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := AAbsPosDeg;

  if ASpeedDegS > S2MaxSpeed then
  begin
    ASetSpeed := S2MaxSpeed;
    vLog('S2_GoAbsPostion_MMode_Asyn: S2 Set positon is greater than the max value(' + S2MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedDegS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S2_GoAbsPostion_MMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedDegS;

  S2TargetPositionManual := ASetPosition;
  S2TargetSpeedManual := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS2MPosSpd, @AWriteByte[0], false) then
  begin
    vLog('S2_GoAbsPostion_MMode_Asyn: S2 manual mode goto abs. position write error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_GoAbsPostion_MMode_Asyn: S2 manual mode goto abs. position send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S2_GoAbsSlopGrad_AutoMode_Asyn(const AAbsGradPercent: Single): s32;
var
  ADegree: Single;
begin
  if Abs(AAbsGradPercent) > 30 then
  begin
    vLog('Max Slop is 30%, Current Setting is ' + AAbsGradPercent.ToString + '%', LVL_ERROR);
    Exit(-1);
  end;
  ADegree := ArcTan(AAbsGradPercent / 100) * 180 / pi + S2MountPosition;
  result := S2_GoAbsPos_AutoMode_Asyn(ADegree, S2SlopSpeed);
end;

function TServo.S2_GoAbsSlopGrad_AutoMode_Syn(const AAbsGradPercent: Single; const ATimeout: u32): s32;
var
  ADegree: Single;
begin
  if Abs(AAbsGradPercent) > 30 then
  begin
    vLog('Max Slop is 30%, Current Setting is ' + AAbsGradPercent.ToString + '%', LVL_ERROR);
    Exit(-1);
  end;
  ADegree := ArcTan(AAbsGradPercent / 100) * 180 / pi + S2MountPosition;
  result := S2_GoAbsPos_AutoMode_Syn(ADegree, S2SlopSpeed, ATimeout);
end;

function TServo.S2_GoAbsSlopGrad_MMode_Asyn(const AAbsGradPercent: Single): s32;
var
  ADegree: Single;
begin
  if Abs(AAbsGradPercent) > 30 then
  begin
    vLog('Max Slop is 30%, Current Setting is ' + AAbsGradPercent.ToString + '%', LVL_ERROR);
    Exit(-1);
  end;

  ADegree := ArcTan(AAbsGradPercent / 100) * 180 / pi + S2MountPosition;
  result := S2_GoAbsPos_MMode_asyn(ADegree, S2SlopSpeed);
end;

function TServo.S2_GoAbsSlopGrad_MMode_Syn(const AAbsGradPercent: Single; const ATimeout: u32): s32;
var
  ADegree: Single;
begin
  if Abs(AAbsGradPercent) > 30 then
  begin
    vLog('Max Slop is 30%, Current Setting is ' + AAbsGradPercent.ToString + '%', LVL_ERROR);
    Exit(-1);
  end;
  ADegree := ArcTan(AAbsGradPercent / 100) * 180 / pi + S2MountPosition;
  result := S2_GoAbsPos_MMode_syn(ADegree, S2SlopSpeed, ATimeout);
end;

function TServo.S2_GoMountPos_AutoMode_Asyn: s32;
begin
  result := S2_GoAbsPos_AutoMode_Asyn(S2MountPosition, S2SlopSpeed);
end;

function TServo.S2_GoMountPos_AutoMode_Syn(const ATimeout: u32): s32;
begin
  result := S2_GoAbsPos_AutoMode_Syn(S2MountPosition, S2SlopSpeed, ATimeout);
end;

function TServo.S2_GoMountPos_MMode_Asyn: s32;
begin
  result := S2_GoAbsPos_MMode_Asyn(S2MountPosition, S2SlopSpeed);
end;

function TServo.S2_GoMountPos_MMode_Syn(const ATimeout: u32): s32;
begin
  result := S2_GoAbsPos_MMode_Syn(S2MountPosition, S2SlopSpeed, ATimeout);
end;

function TServo.S2_GoAbsPos_MMode_Syn(const AAbsPosDeg, ASpeedDegS: Single; const ATimeout: u32): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  ATime: u16;
  i: Integer;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S2IsReady then
  begin
    vLog('S2_GoAbsPostion_MMode_Syn: Servo 2 is not ready', LVL_ERROR);
    exit(-1);
  end;

  if S7IsAutoMode then
  begin
    vLog('S2_GoAbsPostion_MMode_Syn: Servo is in auto mode, switch to manual first', LVL_ERROR);
    exit(-1);
  end;

  if AAbsPosDeg > S2MaxPosition then
  begin
    ASetPosition := S2MaxPosition;
    vLog('S2_GoAbsPostion_MMode_Syn: S2 Set positon is greater than the max value(' + S2MaxPosition.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if AAbsPosDeg < S2MinPosition then
  begin
    ASetPosition := S2MinPosition;
    vLog('S2_GoAbsPostion_MMode_Syn: S2 Set positon is smaller than the min value(' + S2MinPosition.ToString + '), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := AAbsPosDeg;

  if ASpeedDegS > S2MaxSpeed then
  begin
    ASetSpeed := S2MaxSpeed;
    vLog('S2_GoAbsPostion_MMode_Syn: S2 Set positon is greater than the max value(' + S2MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedDegS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S2_GoAbsPostion_MMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedDegS;

  S2TargetPositionManual := ASetPosition;
  S2TargetSpeedManual := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS2MPosSpd, @AWriteByte[0], false) then
  begin
    vLog('S2_GoAbsPostion_MMode_Syn: S2 manual mode goto abs. position write error', LVL_ERROR);
    exit(-2);
  end;

  S2RunFinished := False;
  ATime := 0;
  while true do
  begin
    if S2RunFinished and (abs(S2TargetPositionManual - S2ActPostion) < PositionMaxTol) then
    begin
      vLog('S2_GoAbsPostion_MMode_Syn: S2 manual mode goto abs. position finished', LVL_INFO);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S2_GoAbsPostion_MMode_Syn: go abs position timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

// function TServo.S2_GetAutoPosition(const pPosition: PSingle): s32;
// begin
//
// end;
//
// function TServo.S2_GetAutoSpeed(const pSpeed: PSingle): s32;
// begin
//
// end;
//
// function TServo.S2_GetManualPosition(const pPosition: PSingle): s32;
// begin
//
// end;
//
// function TServo.S2_GetManualSpeed(const pSpeed: PSingle): s32;
// begin
//
// end;
//
// function TServo.S2_GetReadyStatus(const pReadyStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S2_GetRunFinishedStatus(const pRunFinishedStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S2_GetRunningStatus(const pRunningStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S2_GetServoFaultStatus(const pServoFaultStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S2_GetServoMode(const pIsAutoMode: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S2_GetServoStatus(const pServoStatus: PBoolean): s32;
// begin
//
// end;
//
// function TServo.S2_GetZeroExisted(const pZeroExisted: PBoolean): s32;
// begin
//
// end;

function TServo.S2_GoZero_Asyn: s32;
var
  AWriteByte: Byte;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  AWriteByte := 0;
  if not S2IsReady then
  begin
    vLog('S2_GoZero_Asyn: S2 not ready', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS2GoZero, @AWriteByte, false) then
  begin
    vLog('S2_GoZero_Asyn: S7 Write go zero error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_GoZero_Asyn: S2 go zero comand send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S2_GoZero_Syn(const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  AWriteByte := 0;
  if not S2IsReady then
  begin
    vLog('S2_GoZero_Syn: S2 not ready', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS2GoZero, @AWriteByte, false) then
  begin
    vLog('S2_GoZero_Syn: S7 Write S2 go zero address error', LVL_ERROR);
    exit(-2);
  end;

  //to check
  S2RunFinished := False;

  ATime := 0;
  while true do
  begin
    if S2RunFinished and (abs(S2ActPostion) < PositionMaxTol) then
      exit(0);

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S2_GoZero_Syn: Servo Go Zero Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S2_Manual_JogIn: s32;
var
  AWriteByte: Byte;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  AWriteByte := 0;
  if not S2IsReady then
  begin
    vLog('S2_Manual_JogIn: S2 is not ready', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS2JogB, @AWriteByte, false) then
  begin
    vLog('S2_Manual_JogIn: S7 Write bit error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_Manual_JogIn: S2 Jog In', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S2_Manual_JogOut: s32;
var
  AWriteByte: Byte;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  AWriteByte := 0;
  if not S2IsReady then
  begin
    vLog('S2_Manual_JogOut: S2 is not ready', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS2JogF, @AWriteByte, false) then
  begin
    vLog('S2_Manual_JogOut: S7 Write bit error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_Manual_JogOut: S2 Jog Out', LVL_INFO);
    exit(0);
  end;
end;

// function TServo.S2_Mode(const AManaulMode: Boolean; const ATimeout: u32 = DefaultTimeout): s32;
// var
// AWriteByte: byte;
// ATime: u32;
// begin
// if not S2ServoStatus then
// begin
// vLog('S2 need Servo On First', LVL_ERROR);
// Exit(-1);
// end;
//
// S7.ValBit[@AWriteByte, 0] := AManaulMode;
//
// if 0 <> S7Write(AddrSetS2Mode, @AWriteByte, false) then
// begin
// vLog('S7 Write S2 servo on address error', LVL_ERROR);
// Exit(-2);
// end;
//
// ATime := 0;
// while true do
// begin
// if S2AutoMode = AManaulMode then
// Exit(0);
// Sleep(1);
// ATime := ATime + 1;
// if (ATime > ATimeout) then
// begin
// vLog('Servo Start Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
// Exit(-3);
// end;
// end;
// end;

function TServo.S2_GoRelPos_AutoMode_Asyn(const ARelPosDeg, ASpeedDegS: Single): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  i: Integer;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S2IsReady then
  begin
    vLog('S2_GoRelPos_AutoMode_Asyn: Servo is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S2_GoRelPos_AutoMode_Asyn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  ASetPosition := S2ActPostion + ARelPosDeg;

  if ASetPosition > S2MaxPosition then
  begin
    ASetPosition := S2MaxPosition;
    vLog('S2_GoRelPos_AutoMode_Asyn: S2 Set positon is greater than the max value, and the target value used the max value instead', LVL_WARNING);
  end
  else if ASetPosition < S2MinPosition then
  begin
    ASetPosition := S2MinPosition;
    vLog('S2_GoRelPos_AutoMode_Asyn: S2 Set positon is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := ASetPosition;

  if ASpeedDegS > S2MaxSpeed then
  begin
    ASetSpeed := S2MaxSpeed;
    vLog('S2_GoRelPos_AutoMode_Asyn: S2 Set positon is greater than the max value(' + S2MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedDegS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S2_GoRelPos_AutoMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedDegS;

  S2TargetPositionAuto := ASetPosition;
  S2TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS2APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S2_GoRelPos_AutoMode_Asyn: S2 auto mode write speed error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_GoRelPos_AutoMode_Asyn: S2 auto mode goto rel. position send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S2_GoRelPos_AutoMode_Syn(const ARelPosDeg, ASpeedDegS: Single; const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  ATime: u16;
  i: Integer;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S2IsReady then
  begin
    vLog('S2_GoRelPos_AutoMode_Syn: Servo is not ready', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsAutoMode then
  begin
    vLog('S2_GoRelPos_AutoMode_Syn: Servo is in manual mode, switch to auto first', LVL_ERROR);
    exit(-1);
  end;

  ASetPosition := S2ActPostion + ARelPosDeg;

  if ASetPosition > S2MaxPosition then
  begin
    ASetPosition := S2MaxPosition;
    vLog('S2_GoRelPos_AutoMode_Syn: S2 Set positon is greater than the max value, and the target value used the max value instead', LVL_WARNING);
  end
  else if ASetPosition < S2MinPosition then
  begin
    ASetPosition := S2MinPosition;
    vLog('S2_GoRelPos_AutoMode_Syn: S2 Set positon is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := ASetPosition;

  if ASpeedDegS > S2MaxSpeed then
  begin
    ASetSpeed := S2MaxSpeed;
    vLog('S2_GoRelPos_AutoMode_Syn: S2 Set positon is greater than the max value(' + S2MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedDegS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S2_GoRelPos_AutoMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedDegS;

  S2TargetPositionAuto := ASetPosition;
  S2TargetSpeedAuto := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS2APosSpd, @AWriteByte[0], false) then
  begin
    vLog('S2_GoRelPos_AutoMode_Syn: S2 auto mode write speed error', LVL_ERROR);
    exit(-2);
  end;

  S2RunFinished := False;
  ATime := 0;
  while true do
  begin
    if S2RunFinished and (abs(S2TargetPositionAuto - S2ActPostion) < PositionMaxTol) then
    begin
      vLog('S2_GoRelPos_AutoMode_Syn: S2 auto mode goto rel. position finished', LVL_INFO);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S2_GoRelPos_AutoMode_Syn: go rel. position timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S2_GoRelPos_MMode_Asyn(const ARelPosDeg, ASpeedDegS: Single): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  i: Integer;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S2IsReady then
  begin
    vLog('S2_GoRelPos_MMode_Asyn: Servo is not ready', LVL_ERROR);
    exit(-1);
  end;

  if S7IsAutoMode then
  begin
    vLog('S2_GoRelPos_MMode_Asyn: Servo is in auto mode, switch to manual first', LVL_ERROR);
    exit(-1);
  end;

  ASetPosition := S2ActPostion + ARelPosDeg;

  if ASetPosition > S2MaxPosition then
  begin
    ASetPosition := S2MaxPosition;
    vLog('S2_GoRelPos_MMode_Asyn: S2 Set positon is greater than the max value, and the target value used the max value instead', LVL_WARNING);
  end
  else if ASetPosition < S2MinPosition then
  begin
    ASetPosition := S2MinPosition;
    vLog('S2_GoRelPos_MMode_Asyn: S2 Set positon is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := ASetPosition;

  if ASpeedDegS > S2MaxSpeed then
  begin
    ASetSpeed := S2MaxSpeed;
    vLog('S2_GoRelPos_MMode_Asyn: S2 Set positon is greater than the max value(' + S2MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedDegS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S2_GoRelPos_MMode_Asyn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedDegS;

  S2TargetPositionManual := ASetPosition;
  S2TargetSpeedManual := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS2MPosSpd, @AWriteByte[0], false) then
  begin
    vLog('S2_GoRelPos_MMode_Asyn: S2 manual mode write speed error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_GoRelPos_MMode_Asyn: S2 manual mode goto rel. position send out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S2_GoRelPos_MMode_Syn(const ARelPosDeg, ASpeedDegS: Single; const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: packed array[0..7] of Byte;
  ASetPosition, ASetSpeed: Single;
  ATime: u16;
  i: Integer;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  for i := 0 to 7 do
  begin
    AWriteByte[i] := 0;
  end;

  if not S2IsReady then
  begin
    vLog('S2_GoRelPos_MMode_Syn: Servo is not ready', LVL_ERROR);
    exit(-1);
  end;

  if S7IsAutoMode then
  begin
    vLog('S2_GoRelPos_MMode_Syn: Servo is in auto mode, switch to manual first', LVL_ERROR);
    exit(-1);
  end;

  ASetPosition := S2ActPostion + ARelPosDeg;

  if ASetPosition > S2MaxPosition then
  begin
    ASetPosition := S2MaxPosition;
    vLog('S2_GoRelPos_MMode_Syn: S2 Set positon is greater than the max value, and the target value used the max value instead', LVL_WARNING);
  end
  else if ASetPosition < S2MinPosition then
  begin
    ASetPosition := S2MinPosition;
    vLog('S2_GoRelPos_MMode_Syn: S2 Set positon is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetPosition := ASetPosition;

  if ASpeedDegS > S2MaxSpeed then
  begin
    ASetSpeed := S2MaxSpeed;
    vLog('S2_GoRelPos_MMode_Syn: S2 Set positon is greater than the max value(' + S2MaxSpeed.ToString + '), and the target value used the max value instead', LVL_WARNING);
  end
  else if ASpeedDegS < 0 then
  begin
    ASetSpeed := 0;
    vLog('S2_GoRelPos_MMode_Syn: S2 Set positon is smaller than the min value(0), and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetSpeed := ASpeedDegS;

  S2TargetPositionManual := ASetPosition;
  S2TargetSpeedManual := ASetSpeed;

  S7.ValReal[@AWriteByte[0]] := ASetPosition;
  S7.ValReal[@AWriteByte[4]] := ASetSpeed;

  if 0 <> S7Write(AddrSetS2MPosSpd, @AWriteByte[0], false) then
  begin
    vLog('S2_GoRelPos_MMode_Syn: S2 manual mode write speed error', LVL_ERROR);
    exit(-2);
  end;

  S2RunFinished := False;
  ATime := 0;
  while true do
  begin
    if S2RunFinished and (abs(S2TargetPositionManual - S2ActPostion) < PositionMaxTol) then
    begin
      vLog('S2_GoRelPos_MMode_Syn: S2 manual mode goto rel. position finished', LVL_INFO);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S2_GoRelPos_MMode_Syn: go rel. position timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S2_GoRelSlopGrad_AutoMode_Asyn(const ARelGradPercent: Single): s32;
var
  ADegree, AGrad: Single;
begin
  AGrad := S2ActPositionGrad + ARelGradPercent;
  if Abs(AGrad) > 30 then
  begin
    vLog('Max Slop is 30%, Current Setting is ' + AGrad.ToString + '%', LVL_ERROR);
    Exit(-1);
  end;
  ADegree := ArcTan(AGrad / 100) * 180 / pi + S2MountPosition;
  result := S2_GoAbsPos_AutoMode_ASyn(ADegree, S2SlopSpeed);
end;

function TServo.S2_GoRelSlopGrad_AutoMode_Syn(const ARelGradPercent: Single; const ATimeout: u32): s32;
var
  ADegree, AGrad: Single;
begin
  AGrad := S2ActPositionGrad + ARelGradPercent;
  if Abs(AGrad) > 30 then
  begin
    vLog('Max Slop is 30%, Current Setting is ' + AGrad.ToString + '%', LVL_ERROR);
    Exit(-1);
  end;
  ADegree := ArcTan(AGrad / 100) * 180 / pi + S2MountPosition;
  result := S2_GoAbsPos_AutoMode_Syn(ADegree, S2SlopSpeed, ATimeout);
end;

function TServo.S2_GoRelSlopGrad_MMode_Asyn(const ARelGradPercent: Single): s32;
var
  ADegree, AGrad: Single;
begin
  AGrad := S2ActPositionGrad + ARelGradPercent;
  if Abs(AGrad) > 30 then
  begin
    vLog('Max Slop is 30%, Current Setting is ' + AGrad.ToString + '%', LVL_ERROR);
    Exit(-1);
  end;
  ADegree := ArcTan(AGrad / 100) * 180 / pi + S2MountPosition;
  result := S2_GoAbsPos_MMode_Asyn(ADegree, S2SlopSpeed);
end;

function TServo.S2_GoRelSlopGrad_MMode_Syn(const ARelGradPercent: Single; const ATimeout: u32): s32;
var
  ADegree, AGrad: Single;
begin
  AGrad := S2ActPositionGrad + ARelGradPercent;
  if Abs(AGrad) > 30 then
  begin
    vLog('Max Slop is 30%, Current Setting is ' + AGrad.ToString + '%', LVL_ERROR);
    Exit(-1);
  end;
  ADegree := ArcTan(AGrad / 100) * 180 / pi + S2MountPosition;
  result := S2_GoAbsPos_MMode_syn(ADegree, S2SlopSpeed, ATimeout);

end;

function TServo.S2_Run_On(const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  AWriteByte := 0;
  if not S2IsServoOn then
  begin
    vLog('S2_Run_Syn: S2 need Servo On First', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS2Start, @AWriteByte, false) then
  begin
    vLog('S2_Run_Syn: S7 Write S2 start address error', LVL_ERROR);
    exit(-2);
  end;

  ATime := 0;
  while true do
  begin
    if S2IsReady then
      exit(0);

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S2_Run_Syn: Servo Start Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S2_ServoON(const AEnable: boolean; const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  AWriteByte := 0;
  if not S7IsHandShaked then
  begin
    vLog('S2_ServoON: HandShake needed before Servo On', LVL_ERROR);
    exit(-1);
  end;
  // todo when to get power status

  if not S7IsPowerOn then
  begin
    vLog('S2_ServoON: Power is off', LVL_ERROR);
    exit(-1);
  end;

  // todo when to get Device Fault Status
  {
  if S7IsFault then
  begin
    vLog('S2_ServoON: Device has fault', LVL_ERROR);
    exit(-1);
  end;
  }
  S7.ValBit[@AWriteByte, 0] := AEnable;

  if 0 <> S7Write(AddrSetS2ServoOn, @AWriteByte, false) then
  begin
    vLog('S2_ServoON: S7 Write S2 servo on address error', LVL_ERROR);
    exit(-2);
  end;

  ATime := 0;
  while true do
  begin
    if S2IsServoOn = AEnable then
    begin
      if AEnable then
        vLog('S2_ServoON: Servo On Successful', LVL_OK)
      else
        vLog('S2_ServoON: Servo Off Successful', LVL_OK);
      exit(0);
    end;

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S2_ServoON: Servo On/Off Timeout, timeout setting is ' + ATimeout.ToString + 'ms.', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S2_SetZero(const ATimeout: u32 = DefaultTimeout): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  AWriteByte := 0;
  if not S2IsServoOn then
  begin
    vLog('S2_SetZero: S2 need Servo On First', LVL_ERROR);
    exit(-1);
  end;

  if not S2RunFinished then
  begin
    vLog('S2_SetZero: S2 is running, cannot set zero', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS2SetZero, @AWriteByte, false) then
  begin
    vLog('S2_SetZero: S7 Write S2 set zero address error', LVL_ERROR);
    exit(-2);
  end;

  //to check
  S2ZeroExisted := False;

  ATime := 0;
  while true do
  begin
    if S2ZeroExisted and S2RunFinished then
      exit(0);

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S2_SetZero: Servo Set Zero Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

function TServo.S3_Go_In: s32;
var
  AWriteByte: Byte;
begin
  if not S7WithAirCylinder then
  begin
    vLog('air cylinder is not activated', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsOnlyPedal then
  begin
    vLog('rotate servo is actived, can not use air cylinder', LVL_ERROR);
    exit(-1);
  end;
  AWriteByte := 0;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS3GoIn, @AWriteByte, false) then
  begin
    vLog('S2_Manual_JogIn: S7 Write bit error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_Manual_JogIn: S2 Jog In', LVL_INFO);
    exit(0);
  end;

end;

function TServo.S3_Go_Out: s32;
var
  AWriteByte: Byte;
begin
  if not S7WithAirCylinder then
  begin
    vLog('air cylinder is not activated', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsOnlyPedal then
  begin
    vLog('rotate servo is actived, can not use air cylinder', LVL_ERROR);
    exit(-1);
  end;
  AWriteByte := 0;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS3GoOut, @AWriteByte, false) then
  begin
    vLog('S2_Manual_JogOut: S7 Write bit error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_Manual_JogOut: S2 Jog Out', LVL_INFO);
    exit(0);
  end;
end;

function TServo.S3_Pressure_Current(const APressure: Single): Single;
var
  ACurrent: Single;
begin
  vLog('Target Pressure is ' + APressure.ToString + 'Bar.');
//  vLog('S3P2AFactor is '+S3P2AFactor.ToString + ', S3P2AOffset is ' + S3P2AOffset.ToString);
  ACurrent := S3P2AFactor * APressure + S3P2AOffset;
  if ACurrent < vTIOConfig.FAirValveMinCurrent then
    ACurrent := vTIOConfig.FAirValveMinCurrent
  else if ACurrent > vTIOConfig.FAirValveMaxCurrent then
    ACurrent := vTIOConfig.FAirValveMaxCurrent;
  vLog('Target Current is ' + ACurrent.ToString + 'mA.');
  Result := ACurrent;
end;

function TServo.S3_Set_Current(const ACurrentA: Single): s32;
var
  AWriteByte: packed array[0..3] of Byte;
  ASetCurrent: Single;
  i: Integer;
begin
  if not S7WithAirCylinder then
  begin
    vLog('air cylinder is not activated', LVL_ERROR);
    exit(-1);
  end;

  if not S7IsOnlyPedal then
  begin
    vLog('rotate servo is actived, can not use air cylinder', LVL_ERROR);
    exit(-1);
  end;

  for i := 0 to 3 do
  begin
    AWriteByte[i] := 0;
  end;

  if ACurrentA > vTIOConfig.FAirValveMaxCurrent then
  begin
    ASetCurrent := vTIOConfig.FAirValveMaxCurrent;
    vLog('S3_Set_Push_Force: Set Force is greater than 20 mA, and the target value used the max value instead', LVL_WARNING);
  end
  else if ACurrentA < vTIOConfig.FAirValveMinCurrent then
  begin
    ASetCurrent := vTIOConfig.FAirValveMinCurrent;
    vLog('S3_Set_Push_Force: Set Force is smaller than  0 mA, and the target value used the min value instead', LVL_WARNING);
  end
  else
    ASetCurrent := ACurrentA;

  S3TargetCurrent := ASetCurrent;

  S7.ValReal[@AWriteByte[0]] := ASetCurrent;

  if 0 <> S7Write(AddrSetS3Current, @AWriteByte[0], false) then
  begin
    vLog('S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position write error', LVL_ERROR);
    exit(-2);
  end
  else
  begin
    vLog('S2_GoAbsPos_AutoMode_Asyn: S2 auto mode goto abs. position send out', LVL_INFO);
    exit(0);
  end;

end;

function TServo.S3_Set_Target_Pressure(const ATargetPressureBar: Single): s32;
var
  ACurrent: Single;
begin
  if ATargetPressureBar < 0 then
  begin
    vLog('S3_Set_Target_Pressure: Target Pressure must be greater than 0 Bar', LVL_ERROR);
    exit(-1);
  end
  else if ATargetPressureBar > 250 then
  begin
    vLog('S3_Set_Target_Pressure: Target Pressure must be smaller than 250 Bar', LVL_ERROR);
    exit(-2);
  end;

  ACurrent := S3_Pressure_Current(ATargetPressureBar);

  Result := S3_Set_Current(ACurrent);
end;

//function TServo.S2_Speed_AutoMode(const APostionMMS: Single): s32;
//var
//  AWriteByte: packed array[0..3] of Byte;
//  ASetSpeed: Single;
//begin
//  if not S7IsConnected then
//  begin
//    vLog('S2_Speed_AutoMode: Servo connect needed ', LVL_ERROR);
//    exit(-1);
//  end;
//
//  if APostionMMS > S2MaxSpeed then
//  begin
//    ASetSpeed := S2MaxSpeed;
//    vLog('S2_Speed_AutoMode: S2 Set speed is greater than the max value, and the target value used the max value instead', LVL_WARNING);
//  end
//  else if APostionMMS < 0 then
//  begin
//    ASetSpeed := 0;
//    vLog('S2_Speed_AutoMode: S2 Set speed is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
//  end
//  else
//    ASetSpeed := APostionMMS;
//
//  S7.ValReal[@AWriteByte] := ASetSpeed;
//
//  if 0 <> S7Write(AddrSetS2ASpd, @AWriteByte[0], false) then
//  begin
//    vLog('S2_Speed_AutoMode: S2 auto mode write speed error', LVL_ERROR);
//    exit(-2);
//  end
//  else
//  begin
//    S2TargetSpeedAuto := ASetSpeed;
//    exit(0);
//  end;
//
//end;

//function TServo.S2_Speed_ManualMode(const APostionMMS: Single): s32;
//var
//  AWriteByte: packed array[0..3] of Byte;
//  ASetSpeed: Single;
//begin
//  if not S7IsConnected then
//  begin
//    vLog('S2_Speed_ManualMode: Servo connect needed ', LVL_ERROR);
//    exit(-1);
//  end;
//
//  if APostionMMS > S2MaxSpeed then
//  begin
//    ASetSpeed := S2MaxSpeed;
//    vLog('S2_Speed_ManualMode: S2 Set speed is greater than the max value, and the target value used the max value instead', LVL_WARNING);
//  end
//  else if APostionMMS < 0 then
//  begin
//    ASetSpeed := 0;
//    vLog('S2_Speed_ManualMode: S2 Set speed is smaller than the min value, and the target value used the min value instead', LVL_WARNING);
//  end
//  else
//    ASetSpeed := APostionMMS;
//
//  S7.ValReal[@AWriteByte] := ASetSpeed;
//
//  if 0 <> S7Write(AddrSetS2MSpd, @AWriteByte[0], false) then
//  begin
//    vLog('S2_Speed_ManualMode: S2 manual mode write speed error', LVL_ERROR);
//    exit(-2);
//  end
//  else
//  begin
//    S2TargetSpeedManual := ASetSpeed;
//    exit(0);
//  end;
//
//end;

//function TServo.S2_Stop_Asyn: s32;
//var
//  AWriteByte: Byte;
//begin
//  if not S2IsServoOn then
//  begin
//    vLog('S2_Stop_Asyn: S2 need Servo On First', LVL_ERROR);
//    exit(-1);
//  end;
//
//  S7.ValBit[@AWriteByte, 0] := true;
//
//  if 0 <> S7Write(AddrSetS2Stop, @AWriteByte, false) then
//  begin
//    vLog('S2_Stop_Asyn: S7 Write S2 stop address error', LVL_ERROR);
//    exit(-2);
//  end
//  else
//  begin
//    vLog('S2_Stop_Asyn: S7 Send Stop Comand', LVL_INFO);
//    exit(0);
//  end;
//
//end;

function TServo.S2_Run_Off(const ATimeout: u32): s32;
var
  AWriteByte: Byte;
  ATime: u32;
begin
  if S7IsOnlyPedal then
  begin
    vLog('S2_Run_On: S2 is invalid', LVL_ERROR);
    exit(-10);
  end;
  AWriteByte := 0;
  if not S2IsServoOn then
  begin
    vLog('S2_Stop_Syn: S2 is already Servo off', LVL_INFO);
    exit(0);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> S7Write(AddrSetS2Stop, @AWriteByte, false) then
  begin
    vLog('S2_Stop_Syn: S7 Write S2 stop address error', LVL_ERROR);
    exit(-2);
  end;

  // to check

  ATime := 0;
  while true do
  begin
    if not S2IsReady then
      exit(0);

    Sleep(1);
    ATime := ATime + 1;
    if (ATime > ATimeout) then
    begin
      vLog('S2_Stop_Syn: Servo Stop Timeout, timeout setting is ' + ATimeout.ToString + 'ms', LVL_ERROR);
      exit(-3);
    end;
  end;
end;

procedure TServo.SetFS1ActPosition(const Value: Single);
begin
  FS1ActPosition := Value;
  app.set_system_var_double(GROUP_NAME_SERVO + '.PedalPosition', Value);
end;

procedure TServo.SetFS1ActSpeed(const Value: Single);
begin
  FS1ActSpeed := Value;
  app.set_system_var_double(GROUP_NAME_SERVO + '.PedalSpeed', Value);
end;

procedure TServo.SetFPedalIsSysMode(const AEnable: boolean);
begin
  FPedalIsSysMode := AEnable;
  if FPedalIsSysMode then
  begin
    vLog('TServo.SetFPedalIsSysMode: Pedal is controlled by system variable tio.PedalTargetPosition/PedalTargetPercent and tio.PedalTargetSpeed, set speed first and then set position to enable run', LVL_INFO)
  end
  else
  begin
    vLog('TServo.SetFPedalIsSysMode:Pedal is controlled by api', LVL_INFO);
  end;
end;

procedure TServo.SetFS1IsFault(const Value: boolean);
begin
  if FS1IsFault <> Value then
  begin
    if Value then
      vLog('SetFS1IsFault: Servo 1 Fault', LVL_ERROR)
    else
      vLog('SetFS1IsFault: Servo 1 Fault Cleared', LVL_INFO);
  end;

  FS1IsFault := Value;
end;

procedure TServo.SetFS1IsReady(const Value: boolean);
begin
  if FS1IsReady <> Value then
  begin
    if Value then
      vLog('SetFS1IsReady: Servo 1 is ready', LVL_INFO)
    else
      vLog('SetFS1IsReady: Servo 1 not ready', LVL_INFO);
  end;
  FS1IsReady := Value;
end;

procedure TServo.SetFS1RunFinished(const Value: boolean);
begin
//  if FS1RunFinished <> Value then
//  begin
//    if Value then
//      vLog('SetFS1RunFinished: Servo 1 run action finished', LVL_INFO)
//    else
//      vLog('SetFS1RunFinished: Servo 1 run action not finished', LVL_INFO);
//  end;
  FS1RunFinished := Value;
end;

// procedure TServo.SetFS1AutoMode(const Value: Boolean);
// begin
// if FS1AutoMode <> Value then
// begin
// if Value then
// vlog('Servo 1 Auto Mode Enable', lvl_info)
// else
// vlog('Servo 1 Manual Mode Enable', lvl_info);
// end;
// FS1AutoMode := Value;
// end;

// procedure TServo.SetFS1Running(const Value: Boolean);
// begin
// if FS1Running <> Value then
// begin
// if Value then
// vlog('Servo 1 is running', lvl_info)
// else
// vlog('Servo 1 is stopped', lvl_info);
// end;
//
// FS1Running := Value;
//
// end;

procedure TServo.SetFS1IsServoOn(const Value: boolean);
begin
  if FS1IsServoOn <> Value then
  begin
    if Value then
      vLog('SetFS1IsServoOn: Servo 1 servo on', LVL_INFO)
    else
      vLog('SetFS1IsServoOn: Servo 1 servo off', LVL_INFO);
  end;

  FS1IsServoOn := Value;
end;

procedure TServo.SetFS1MaxPosition(const Value: Single);
begin
  if Value >= 60 then
  begin
    FS1MaxPosition := 60;
    vLog('SetFS1MaxPosition: Set position is: ' + Value.ToString + 'mm, out of range, the max value set 60 mm', LVL_ERROR);
  end
  else if Value < 0 then
  begin
    FS1MaxPosition := 0;
    vLog('SetFS1MaxPosition: Set position is: ' + Value.ToString + 'mm, out of range, the max value set 0 mm', LVL_INFO);
  end
  else
  begin
    FS1MaxPosition := Value;
    vLog('SetFS1MaxPosition: Servo 1 maxium set position is: ' + Value.ToString + 'mm', LVL_INFO);
  end;
  vTIOConfig.FServo1MaxPosition := FS1MaxPosition;
end;

procedure TServo.SetFS1MaxSpeed(const Value: Single);
begin
  FS1MaxSpeed := Value;
  vLog('SetFS1MaxSpeed: Servo 1 maxium set speed is: ' + Value.ToString + 'mm/s', LVL_INFO);
end;

procedure TServo.SetFS1MinPosition(const Value: Single);
begin
  if Value > 0 then
  begin
    FS1MinPosition := 0;
    vLog('SetFS1MinPosition: Set position is: ' + Value.ToString + 'mm, out of range, the min value set 0 mm', LVL_ERROR);
  end
  else if Value < -10 then
  begin
    FS1MinPosition := -10;
    vLog('SetFS1MinPosition: Set position is: ' + Value.ToString + 'mm, out of range, the min value set 0 mm', LVL_INFO);
  end
  else
  begin
    FS1MinPosition := Value;
    vLog('SetFS1MinPosition: Servo 1 min set position is: ' + Value.ToString + 'mm', LVL_INFO);
  end;
  vTIOConfig.FServo1MinPosition := FS1MinPosition;
end;

procedure TServo.SetFS1TargetPositionAuto(const Value: Single);
begin
  FS1TargetPositionAuto := Value;
  if not PedalIsSysMode then
    vLog('SetFS1TargetPositionAuto: Servo 1 auto mode target position is: ' + Value.ToString + 'mm', LVL_INFO);
end;

procedure TServo.SetFS1TargetPositionManual(const Value: Single);
begin
  FS1TargetPositionManual := Value;
  vLog('SetFS1TargetPositionAuto: Servo 1 manual mode target position is: ' + Value.ToString + 'mm', LVL_INFO);
end;

procedure TServo.SetFS1TargetSpeedAuto(const Value: Single);
begin
  FS1TargetSpeedAuto := Value;
  if not PedalIsSysMode then
    vLog('SetFS1TargetSpeedAuto: Servo 1 auto mode target speed is: ' + Value.ToString + 'mm/s', LVL_INFO);
end;

procedure TServo.SetFS1TargetSpeedManual(const Value: Single);
begin
  FS1TargetSpeedManual := Value;
  vLog('SetFS1TargetSpeedManual: Servo 1 manual mode target speed is: ' + Value.ToString + 'mm/s', LVL_INFO);
end;

procedure TServo.SetFS1ZeroExisted(const Value: boolean);
begin
  if FS1ZeroExisted <> Value then
  begin
    if Value then
      vLog('SetFS1ZeroExisted: Servo 1 has Zero Point', LVL_INFO)
    else
      vLog('SetFS1ZeroExisted: Servo 1 no Zero Point', LVL_INFO);
  end;
  FS1ZeroExisted := Value;
end;

procedure TServo.SetFS2ActPosition(const Value: Single);
begin
  FS2ActPosition := Value;
  S2ActPositionGrad := Tangent((FS2ActPosition - FS2MountPosition) * pi / 180) * 100;
  app.set_system_var_double(GROUP_NAME_SERVO + '.RotateDegree', Value);
end;

procedure TServo.SetFS2ActPositionGrad(const Value: Single);
begin
  FS2ActPositionGrad := Value;
  app.set_system_var_double(GROUP_NAME_SERVO + '.SlopeGrad', Value);
end;

procedure TServo.SetFS2ActSpeed(const Value: Single);
begin
  FS2ActSpeed := Value;
end;

procedure TServo.SetFS2IsFault(const Value: boolean);
begin
  if FS2IsFault <> Value then
  begin
    if Value then
      vLog('SetFS2IsFault: Servo 2 Fault', LVL_ERROR)
    else
      vLog('SetFS2IsFault: Servo 2 Fault Cleared', LVL_INFO);
  end;

  FS2IsFault := Value;
end;

procedure TServo.SetFS2IsReady(const Value: boolean);
begin
  if FS2IsReady <> Value then
  begin
    if Value then
      vLog('SetFS2IsReady: Servo 2 is ready', LVL_INFO)
    else
      vLog('SetFS2IsReady: Servo 2 not ready', LVL_INFO);
  end;

  FS2IsReady := Value;
end;

procedure TServo.SetFS2RunFinished(const Value: boolean);
begin
//  if FS2RunFinished <> Value then
//  begin
//    if Value then
//      vLog('SetFS2RunFinished: Servo 2 run action finished', LVL_INFO)
//    else
//      vLog('SetFS2RunFinished: Servo 2 run action not finished', LVL_INFO);
//  end;

  FS2RunFinished := Value;
end;

procedure TServo.SetFS2SlopSpeed(const Value: Single);
begin
  if (Value > S2MaxSpeed) or (Value < 0) then
  begin
    vLog('SetFS2SlopSpeed: Servo 2 slop run speed is set value not in valid range: [0,' + S2MaxSpeed.ToString + '] ��/s', LVL_ERROR);
    Exit;
  end;

  FS2SlopSpeed := Value;
  vTIOConfig.FServo2Speed := FS2SlopSpeed;
  vLog('SetFS2SlopSpeed: Servo 2 slop run speed is set to: ' + Value.ToString + '��/s', LVL_INFO);

end;

procedure TServo.SetFS2IsServoOn(const Value: boolean);
begin
  if FS2IsServoOn <> Value then
  begin
    if Value then
      vLog('SetFS2IsServoOn: Servo 2 servo on', LVL_INFO)
    else
      vLog('SetFS2IsServoOn: Servo 2 servo off', LVL_INFO);
  end;

  FS2IsServoOn := Value;
end;

procedure TServo.SetFS2MaxPosition(const Value: Single);
begin
  FS2MaxPosition := Value;
  vLog('SetFS2MaxPosition: Servo 2 maxium set position is: ' + Value.ToString + '��', LVL_INFO);
end;

procedure TServo.SetFS2MaxSpeed(const Value: Single);
begin
  FS2MaxSpeed := Value;
  vLog('SetFS2MaxSpeed: Servo 2 maxium set slope is: ' + Value.ToString + '��', LVL_INFO);
end;

procedure TServo.SetFS2MinPosition(const Value: Single);
begin
  FS2MinPosition := Value;
  vLog('SetFS2MinPosition: Servo 2 min set slope is: ' + Value.ToString + '��', LVL_INFO);
end;

procedure TServo.SetFS2MountPosition(const Value: Single);
begin
  FS2MountPosition := Value;
  vTIOConfig.FServo2MountAngle := Value;
  vLog('SetFS2MountPosition: Servo 2 DUT Mounting Angle is set: ' + Value.ToString + '��', LVL_INFO);
end;

procedure TServo.SetFS2TargetPositionAuto(const Value: Single);
begin
  FS2TargetPositionAuto := Value;
  vLog('SetFS2TargetPositionAuto: Servo 2 auto mode target position is: ' + Value.ToString + 'mm', LVL_INFO);
end;

procedure TServo.SetFS2TargetPositionManual(const Value: Single);
begin
  FS2TargetPositionManual := Value;
  vLog('SetFS2TargetPositionManual: Servo 2 manual mode target position is: ' + Value.ToString + 'mm', LVL_INFO);
end;

procedure TServo.SetFS2TargetSpeedAuto(const Value: Single);
begin
  FS2TargetSpeedAuto := Value;
  vLog('SetFS2TargetSpeedAuto: Servo 2 auto mode target speed is: ' + Value.ToString + 'mm/s', LVL_INFO);
end;

procedure TServo.SetFS2TargetSpeedManual(const Value: Single);
begin
  FS2TargetSpeedManual := Value;
  vLog('SetFS2TargetSpeedManual: Servo 2 manaul mode target speed is: ' + Value.ToString + 'mm/s', LVL_INFO);
end;

procedure TServo.SetFS2ZeroExisted(const Value: boolean);
begin
  if FS2ZeroExisted <> Value then
  begin
    if Value then
      vLog('SetFS2ZeroExisted: Servo 2 has Zero Point', LVL_INFO)
    else
      vLog('SetFS2ZeroExisted: Servo 2 no Zero Point', LVL_INFO);
  end;

  FS2ZeroExisted := Value;
end;

procedure TServo.SetFS3MCMaxPressure(const Value: Single);
begin
  if Value >= 250 then
  begin
    FS3MCMaxPressure := 250;
    vLog('SetFS3MCMaxPressure: Set Pressure is: ' + Value.ToString + 'Bar, out of range, the max value set 250 Bar', LVL_ERROR);
  end
  else if Value < 0 then
  begin
    FS3MCMaxPressure := 0;
    vLog('SetFS3MCMaxPressure: Set Pressure is: ' + Value.ToString + 'Bar, out of range, the min value set 0 Bar', LVL_INFO);
  end
  else
  begin
    FS3MCMaxPressure := Value;
    vLog('SetFS3MCMaxPressure: maxium set MC Pressure is: ' + Value.ToString + 'Bar', LVL_INFO);
  end;
  vTIOConfig.FMCMaxPressure := FS3MCMaxPressure;
end;

procedure TServo.SetFS3P2AFactor(const Value: Single);
begin
  if Value >= 1 then
  begin
    FS3P2AFactor := 1;
    vLog('SetFS3P2AFactor: Set Pressure convert current factor is: ' + Value.ToString + ', out of range, the max value set 1', LVL_ERROR);
  end
  else if Value < 0 then
  begin
    FS3P2AFactor := 0;
    vLog('SetFS3P2AFactor: Set Pressure convert current factor is: ' + Value.ToString + 'Bar, out of range, the min value set 0', LVL_INFO);
  end
  else
  begin
    FS3P2AFactor := Value;
    vLog('SetFS3P2AFactor: Set Pressure convert current factor is: ' + Value.ToString, LVL_INFO);
  end;
  vTIOConfig.FPressure2CurrentFactor := FS3P2AFactor;
end;

procedure TServo.SetFS3P2AOffset(const Value: Single);
begin
  if Value >= vTIOConfig.FAirValveMaxCurrent then
  begin
    FS3P2AOffset := vTIOConfig.FAirValveMaxCurrent;
    vLog('SetFS3P2AFactor: Set Pressure convert current offset is: ' + Value.ToString + ', out of range, the max value set ' + vTIOConfig.FAirValveMaxCurrent.tostring, LVL_ERROR);
  end
  else if Value < vTIOConfig.FAirValveMinCurrent then
  begin
    FS3P2AOffset := vTIOConfig.FAirValveMinCurrent;
    vLog('SetFS3P2AFactor: Set Pressure convert current offset is: ' + Value.ToString + 'Bar, out of range, the min value set ' + vTIOConfig.FAirValveMinCurrent.tostring, LVL_INFO);
  end
  else
  begin
    FS3P2AOffset := Value;
    vLog('SetFS3P2AFactor: Set Pressure convert current offset is: ' + Value.ToString, LVL_INFO);
  end;
  vTIOConfig.FPressure2CurrentOffset := FS3P2AOffset;
end;

procedure TServo.SetFS3TargetCurrent(const Value: Single);
begin
  FS3TargetCurrent := Value;
  vLog('SetFS3TargetForce: air cylinder target current is: ' + Value.ToString + 'mA', LVL_INFO);
end;

procedure TServo.SetFS7IsFault(const Value: boolean);
begin
  if FS7IsFault <> Value then
  begin
    if Value then
      vLog('SetFS7IsFault: Servo has fault', LVL_ERROR)
    else
      vLog('SetFS7IsFault: Servo fault cleared', LVL_INFO);
  end;

  FS7IsFault := Value;
end;

procedure TServo.SetFS7IsHandShaked(const Value: boolean);
begin
  if FS7IsHandShaked <> Value then
  begin
    if Value then
    begin
      vHeartbeatThread.HeartbeatResume;
      vLog('SetFS7IsHandShaked: Servo Handshake created, Heartbeat thread resumed', LVL_INFO);
    end
    else
    begin
      vHeartbeatThread.HeartbeatSuspend;
      vLog('SetFS7IsHandShaked: Servo handshake free, Heartbeat thread suspended', LVL_INFO);
    end;
  end;

  FS7IsHandShaked := Value;
end;

procedure TServo.SetFS7IsOnlyPedal(const Value: Boolean);
begin
  FS7IsOnlyPedal := Value;
  if Value then
    vlog('Only Pedal Servo is used')
  else
    vlog('Pedal and Slope Servo are used');
end;

procedure TServo.SetFS7LastError(const Value: integer);
begin
  FS7LastError := Value;

  if FS7LastError <> 0 then
    vLog('SetFS7LastError: Error Code is: ' + FS7LastError.ToString + ', Error Message is: ' + CliErrorText(FS7LastError), LVL_ERROR);
end;

procedure TServo.SetFS7WithAirCylinder(const Value: Boolean);
begin
  FS7WithAirCylinder := Value;
  if Value then
    vlog('Air Cylinder is activated.')
  else
    vlog('Air Cylinder is deactivated.');
end;

//procedure TServo.SetFS7PowerOff(const Value: boolean);
//begin
//  FS7IsAutoMode := Value;
//end;

procedure TServo.SetFS7IsPowerOn(const Value: boolean);
begin
  if FS7IsPowerOn <> Value then
  begin
    if Value then
      vLog('SetFS7IsPowerOn: Servo power is on', LVL_HINT)
    else
      vLog('SetFS7IsPowerOn: Servo power is off', LVL_HINT);
  end;

  FS7IsPowerOn := Value;
end;

procedure TServo.SetFS7IsAutoMode(const Value: boolean);
begin
  if FS7IsAutoMode <> Value then
  begin
    if Value then
      vLog('SetFS7IsAutoMode: Servo Auto Mode is on', LVL_HINT)
    else
      vLog('SetFS7IsAutoMode: Servo Manual Mode is on', LVL_HINT);
  end;
  FS7IsAutoMode := Value;
end;

procedure TServo.SetFS7IsConnected(const Value: boolean);
begin
  FS7IsConnected := Value;

  if vGetDataThread = nil then
    Exit;
  if FS7IsConnected then
  begin
    vGetDataThread.GetDataResume;
    vLog('SetFS7IsConnected: Servo is connected, Getdata thread resumed', LVL_HINT);
  end
  else
  begin
    vGetDataThread.GetDatatSuspend;
    vLog('SetFS7IsConnected: Servo is disconnected, Getdata thread suspended', LVL_HINT);
  end;
end;

//procedure TServo.TimeElapse;
//begin
//  vLog('TimeElapse: Last communication operation Time is' + IntToStr(FS7Client.Time) + 'ms', LVL_INFO);
//end;

procedure TServo.UnRegisterInternalVar(const AName: string);
begin
  if not vSystemVarManager.DeleteInternalVarByName(GROUP_NAME_SERVO, AName) then
  begin
    vLog(vlang.GetLang(LANG_WARNING__REMOVE_SYSTEM_VAR_FAILED, 'Utils') + ': ' + AName, LVL_WARNING);
  end;
end;

procedure TServo.UnregisterSystemVars;
begin
  //vSystemVarManager.UnRegisterOnVarChangedEvent(GROUP_NAME_SERVO + '.i32', OnSystemVarChanged_Int32);
  //vSystemVarManager.UnRegisterOnVarChangedEvent(GROUP_NAME_SERVO + '.str', OnSystemVarChanged_Int32);
  UnRegisterInternalVar('PedalSpeed');
  UnRegisterInternalVar('PedalPosition');
  UnRegisterInternalVar('RotateDegree');
  UnRegisterInternalVar('SlopeGrad');
end;

procedure TServo.S7WaitCompletion(const ATimeout: u32 = DefaultTimeout);
var
  Result: integer;
  AsMode: u8;
begin
  AsMode := 0;
  Application.ProcessMessages;
  case AsMode of
    amPolling, amCallBack:

      repeat
        Application.ProcessMessages;
      until FS7Client.CheckAsCompletion(Result);
    amEvent:
      Result := FS7Client.WaitAsCompletion(DefaultTimeout);
    (*
      amCallBack : begin
      // in our callback we setted evJob
      if evJob.WaitFor(Timeout)=wrSignaled then
      Result:=AsOpResult
      else
      Result:=errCliJobTimeout;
      end;
    *)
  end;

  S7LastError := Result;
end;

function TServo.S7Write(const AField: TDataRecord; const pData: Pointer; const Async: boolean): s32;
begin
  if System.TMonitor.Enter(FMonitorObj, 1000) then
  begin

    try
      if Async then
        S7LastError := FS7Client.AsWriteArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData)
      else
        S7LastError := FS7Client.WriteArea(AField.Area, AField.DBNum, AField.Start, AField.Amount, AField.WordLen, pData);

      if S7LastError = 0 then
      begin
        if Async then
          S7WaitCompletion;
        // Elapse;
      end
      else // Elapse;
        vLog('S7Write: Servo Write Action Error', LVL_ERROR);
      Result := S7LastError;
    finally
      System.TMonitor.exit(FMonitorObj);
    end;
  end
  else
  begin
    vLog('S7Write: try to write action timeout,can not get MonitorObj', LVL_ERROR);
    exit(-1);
  end;
end;

//function TServo.S7WriteBool(const AWriteField: TDataRecord; const ASetBool: boolean): s32;
//var
//  AWriteByte: Byte;
//begin
//  AWriteByte := 0;
//  if not S7IsHandShaked then
//  begin
//    vLog('S7WriteBool: Handshake is needed', LVL_ERROR);
//    exit(-1);
//  end;
//
//  S7.ValBit[@AWriteByte, 0] := ASetBool;
//
//  if 0 <> S7Write(AWriteField, @AWriteByte, false) then
//  begin
//    vLog('S7WriteBool: S7 Write bit error', LVL_ERROR);
//    exit(-2);
//  end;
//  Result := 0;
//end;

//function TServo.S7SetBoolSyn(const AWriteField, AReadField: TDataRecord; const ASetBool, ACorrectBool: boolean; const ATimeout: integer = 1000): s32;
//var
//  ATime: u16;
//  AWriteByte: Byte;
//  AReadByte: Byte;
//  AReadBool: boolean;
//begin
//  AWriteByte := 0;
//  AReadByte := 0;
//  AReadBool := False;
//  if not FS7IsHandShaked then
//  begin
//    vLog('S7SetBoolSyn: Handshake is needed', LVL_ERROR);
//    exit(-1);
//  end;
//
//  S7.ValBit[@AWriteByte, 0] := ASetBool;
//  if 0 <> S7Write(AWriteField, @AWriteByte, false) then
//  begin
//    vLog('S7SetBoolSyn: S7 Write bit error', LVL_ERROR);
//    exit(-2);
//  end;
//
//  ATime := 0;
//  while true do
//  begin
//    if 0 <> S7Read(AReadField, @AReadByte, false) then
//    begin
//      vLog('S7SetBoolSyn: S7 read bit error', LVL_ERROR);
//      exit(-2);
//    end
//    else
//    begin
//      AReadBool := S7.ValBit[@AReadByte, 0];
//      if AReadBool = ACorrectBool then
//      begin
//        vLog('S7SetBoolSyn: S7 Set bit Successful', LVL_INFO);
//        exit(0);
//      end;
//      // else
//      // begin
//      // vLog('S7 Read bit error', LVL_ERROR);
//      // Exit(-3);
//      // end;
//    end;
//    Sleep(20);
//    ATime := ATime + 20;
//    if (ATime > ATimeout) then
//    begin
//      vLog('S7SetBoolSyn: Servo waitting correct response is Timeout, timeout setting is' + ATimeout.ToString, LVL_ERROR);
//      exit(-4);
//    end;
//  end;
//end;

//function TServo.S7WriteRealSyn(const AWriteField, AReadField: TDataRecord; const ASetReal, ACorrectReal: Single; const ATimeout: integer = 1000): s32;
//begin
//
//end;

{ TThreadHeartbeat }

procedure TThreadHeartbeat.Execute;
begin
  inherited;
  while not Terminated do
  begin
    if S7_Heartbeat = 0 then
    begin
      FErrorCount := 0;
    end
    else
    begin
      FErrorCount := FErrorCount + 1;
      if FErrorCount > 10 then
      begin
        vLog('TThreadHeartbeat Execute: Heartbeat thread persistent error, Suspended self, Handshake again to restart', LVL_ERROR);
        HeartbeatSuspend;
//        Break;
      end;
    end;
    Sleep(1000);

//    Inc(FRunningCount);
//    if FRunningCount > 10 then
//    begin
//      FRunningCount := 0;
//      vLog('TThreadHeartbeat Execute: Heartbeat thread run.', LVL_INFO);
//    end;
  end;
  vLog('TThreadHeartbeat Execute: Heartbeat thread exit.', LVL_INFO);
end;

procedure TThreadHeartbeat.Heartbeatexit;
begin
  Terminate;
  FExitCount := 0;
  while not Finished do
  begin
    if Suspended then
    begin
      Resume;
    end;
    Sleep(1);
    Inc(FExitCount);
    if FExitCount > 5000 then
    begin
      vLog('Heartbeatexit: wait Heartbeat thread exit timeout.', LVL_ERROR);
      Break;
    end;
  end;
end;

procedure TThreadHeartbeat.HeartbeatResume;
begin
  if Suspended then
  begin
    Resume;
    vLog('HeartbeatResume: Heartbeat thread resume.', LVL_INFO);
  end
  else
  begin
    vLog('HeartbeatResume: Heartbeat thread not suspended.', LVL_INFO);
  end;
end;

procedure TThreadHeartbeat.HeartbeatSuspend;
begin
  if Suspended then
  begin
    vLog('HeartbeatSuspend: Heartbeat thread already suspended.', LVL_INFO);
  end
  else
  begin
    Suspend;
    vLog('HeartbeatSuspend: Heartbeat thread suspended.', LVL_INFO);
  end;
end;

function TThreadHeartbeat.S7_Heartbeat: s32;
var
  AWriteByte: Byte;
begin
  if vServoObj = nil then
  begin
    vLog('S7_Heartbeat: vServoObj is not exist', LVL_ERROR);
    exit(-1);
  end;

  if not vServoObj.S7IsConnected then
  begin
    vLog('S7_Heartbeat: servo not connected', LVL_ERROR);
    exit(-1);
  end;

  S7.ValBit[@AWriteByte, 0] := true;

  if 0 <> vServoObj.S7Write(AddrSetHandShake, @AWriteByte, false) then
  begin
    vLog('S7_Heartbeat: S7 Write heartbeat address error.', LVL_ERROR);
    exit(-2);
  end;

  exit(0);
end;

{ TThreadGetData }

procedure TThreadGetData.Execute;
begin
  inherited;
  tthread.NameThreadForDebugging('TThreadGetData');

  while not Terminated do
  begin
    if S7_GetData = 0 then
    begin
      FErrorCount := 0;
    end
    else
    begin
      FErrorCount := FErrorCount + 1;
      if FErrorCount > 10 then
      begin
        vLog('TThreadGetData Execute: Getdata thread persistent error, suspended self, connected again to restart', LVL_ERROR);
        GetDatatSuspend;
//        Break;
      end;
    end;
//    Sleep(1);
    Sleep(10);
//    Inc(FRunningCount);
//    if FRunningCount > 500 then
//    begin
//      FRunningCount := 0;
//      vLog('TThreadGetData Execute: Getdata thread run.', LVL_INFO);
//    end;
  end;
  vLog('TThreadGetData Execute: Getdata thread exit.', LVL_INFO);
end;

procedure TThreadGetData.GetDataexit;
begin
  Terminate;
  FExitCount := 0;
  while not Finished do
  begin
    if Suspended then
    begin
      Resume;
    end;
    Sleep(100);
    Inc(FExitCount);
    if FExitCount > 5000 then
    begin
      vLog('GetDataexit: Error: wait getdata thread exit timeout', LVL_ERROR);
      Break;
    end;
  end;
end;

procedure TThreadGetData.GetDataResume;
begin
  if Suspended then
  begin
    Resume;
    vLog('GetDataResume: Getdata thread resume', LVL_INFO);
  end
  else
  begin
    vLog('GetDataResume: Getdata thread not suspended', LVL_INFO);
  end;
end;

procedure TThreadGetData.GetDatatSuspend;
begin
  if Suspended then
  begin
    vLog('GetDatatSuspend: Getdata thread already suspended', LVL_INFO);
  end
  else
  begin
    Suspend;
    vLog('GetDatatSuspend: Getdata thread suspended', LVL_INFO);
  end;
end;

function TThreadGetData.S7_GetData: s32;
begin

  if vServoObj = nil then
  begin
    vLog('S7_GetData: Error: vServoObj is not exist', LVL_ERROR);
    exit(-1);
  end;

  // Result := 0;
  Result := vServoObj.S7_GetAllData;
end;

initialization

end.

