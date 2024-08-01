from TSMaster import *
import sys
blacklist = ["tkinter"] # modules such as tkinter will release GIL by itself, which is not allowed in TSMster Toolbox
for mod in blacklist:
    if sys.modules.get(mod):
        tmp_import = __import__ (mod)
        sys.modules[mod] = None

# Auto Generated Python Code, do not modify START [UI] --------------
class TIO_Configuration(frmTSForm):
    def __init__(self):
        # set type name internally
        self.ExternalTypeName = type(self).__name__
        try:
            # Form properties
            if not self.IsConfigurationLoaded:
                self.Left = 172
                self.Top = 195
                self.Caption = 'TIO_Configuration'
                self.ClientHeight = 601
                self.ClientWidth = 909
            self.Color = clBtnFace
            self.DoubleBuffered = True
            self.Font.Charset = DEFAULT_CHARSET
            self.Font.Color = clWindowText
            self.Font.Height = -12
            self.Font.Name = 'Segoe UI'
            self.Font.Style = []
            self.KeyPreview = True
            self.Position = "poDesigned"
            self.Visible = True
            self.TextHeight = 15
            # Create control: pnlMain = Panel(self)
            self.pnlMain = Panel(self)
            self.pnlMain.Name = "pnlMain"
            self.pnlMain.Parent = self
            self.pnlMain.Left = 0
            self.pnlMain.Top = 0
            self.pnlMain.Width = 909
            self.pnlMain.Height = 601
            self.pnlMain.Cursor = crArrow
            self.pnlMain.Align = "alClient"
            self.pnlMain.BevelEdges = []
            self.pnlMain.BevelOuter = "bvNone"
            self.pnlMain.Caption = 'pnlMain'
            self.pnlMain.ShowCaption = "False"
            self.pnlMain.TabOrder = 0
            # Create control: pnlHeader = Panel(self)
            self.pnlHeader = Panel(self)
            self.pnlHeader.Name = "pnlHeader"
            self.pnlHeader.Parent = self.pnlMain
            self.pnlHeader.Left = 0
            self.pnlHeader.Top = 0
            self.pnlHeader.Width = 909
            self.pnlHeader.Height = 60
            self.pnlHeader.Cursor = crArrow
            self.pnlHeader.Align = "alTop"
            self.pnlHeader.Caption = 'pnlHeader'
            self.pnlHeader.ShowCaption = "False"
            self.pnlHeader.TabOrder = 0
            # Create control: btnAddNew = TSSpeedButton(self)
            self.btnAddNew = TSSpeedButton(self)
            self.btnAddNew.Name = "btnAddNew"
            self.btnAddNew.Parent = self.pnlHeader
            self.btnAddNew.Left = 464
            self.btnAddNew.Top = 16
            self.btnAddNew.Width = 119
            self.btnAddNew.Height = 32
            self.btnAddNew.Cursor = crArrow
            self.btnAddNew.Caption = 'add new device'
            self.btnAddNew.ImageIndex = 70
            self.btnAddNew.Images = app.get_system_imagelist_16px()
            # Create control: btnDelete = TSSpeedButton(self)
            self.btnDelete = TSSpeedButton(self)
            self.btnDelete.Name = "btnDelete"
            self.btnDelete.Parent = self.pnlHeader
            self.btnDelete.Left = 632
            self.btnDelete.Top = 16
            self.btnDelete.Width = 128
            self.btnDelete.Height = 32
            self.btnDelete.Cursor = crArrow
            self.btnDelete.Caption = 'delete '
            self.btnDelete.ImageIndex = 5
            self.btnDelete.Images = app.get_system_imagelist_16px()
            # Create control: pcMain = PageControl(self)
            self.pcMain = PageControl(self)
            self.pcMain.Name = "pcMain"
            self.pcMain.Parent = self.pnlMain
            self.pcMain.Left = 0
            self.pcMain.Top = 60
            self.pcMain.Width = 909
            self.pcMain.Height = 541
            self.pcMain.Cursor = crArrow
            self.pcMain.Align = "alClient"
            self.pcMain.Images = app.get_system_imagelist_16px()
            self.pcMain.MultiLine = True
            self.pcMain.OwnerDraw = True
            self.pcMain.TabHeight = 120
            self.pcMain.TabOrder = 1
            self.pcMain.TabPosition = "tpLeft"
            self.pcMain.TabWidth = 40
            # Create control: tabshtWSS = TabSheet(self)
            self.tabshtWSS = TabSheet(self)
            self.tabshtWSS.Name = "tabshtWSS"
            self.tabshtWSS.PageControl = self.pcMain
            self.tabshtWSS.Cursor = crArrow
            self.tabshtWSS.Caption = 'Wheel Speed Simulator'
            self.tabshtWSS.ImageIndex = 2
            # Create control: pnlWSSHeader = Panel(self)
            self.pnlWSSHeader = Panel(self)
            self.pnlWSSHeader.Name = "pnlWSSHeader"
            self.pnlWSSHeader.Parent = self.tabshtWSS
            self.pnlWSSHeader.Left = 0
            self.pnlWSSHeader.Top = 0
            self.pnlWSSHeader.Width = 781
            self.pnlWSSHeader.Height = 80
            self.pnlWSSHeader.Cursor = crArrow
            self.pnlWSSHeader.Align = "alTop"
            self.pnlWSSHeader.Caption = 'ame'
            self.pnlWSSHeader.ShowCaption = "False"
            self.pnlWSSHeader.TabOrder = 0
            # Create control: lblCANChnl = Label(self)
            self.lblCANChnl = Label(self)
            self.lblCANChnl.Name = "lblCANChnl"
            self.lblCANChnl.Parent = self.pnlWSSHeader
            self.lblCANChnl.Left = 32
            self.lblCANChnl.Top = 16
            self.lblCANChnl.Width = 72
            self.lblCANChnl.Height = 15
            self.lblCANChnl.Cursor = crArrow
            self.lblCANChnl.Caption = 'CAN Channel'
            # Create control: lblBaseID = Label(self)
            self.lblBaseID = Label(self)
            self.lblBaseID.Name = "lblBaseID"
            self.lblBaseID.Parent = self.pnlWSSHeader
            self.lblBaseID.Left = 176
            self.lblBaseID.Top = 16
            self.lblBaseID.Width = 38
            self.lblBaseID.Height = 15
            self.lblBaseID.Cursor = crArrow
            self.lblBaseID.Caption = 'Base ID'
            # Create control: lblConfigKind = Label(self)
            self.lblConfigKind = Label(self)
            self.lblConfigKind.Name = "lblConfigKind"
            self.lblConfigKind.Parent = self.pnlWSSHeader
            self.lblConfigKind.Left = 328
            self.lblConfigKind.Top = 16
            self.lblConfigKind.Width = 108
            self.lblConfigKind.Height = 15
            self.lblConfigKind.Cursor = crArrow
            self.lblConfigKind.Caption = 'Configuration Mode'
            # Create control: lblInfo = Label(self)
            self.lblInfo = Label(self)
            self.lblInfo.Name = "lblInfo"
            self.lblInfo.Parent = self.pnlWSSHeader
            self.lblInfo.Left = 496
            self.lblInfo.Top = 16
            self.lblInfo.Width = 85
            self.lblInfo.Height = 15
            self.lblInfo.Cursor = crArrow
            self.lblInfo.Caption = 'Info: disconnect'
            # Create control: cmbCANChnl = ComboBox(self)
            self.cmbCANChnl = ComboBox(self)
            self.cmbCANChnl.Name = "cmbCANChnl"
            self.cmbCANChnl.Parent = self.pnlWSSHeader
            self.cmbCANChnl.Left = 32
            self.cmbCANChnl.Top = 40
            self.cmbCANChnl.Width = 120
            self.cmbCANChnl.Height = 23
            self.cmbCANChnl.Cursor = crArrow
            self.cmbCANChnl.ItemIndex = 0
            self.cmbCANChnl.TabOrder = 0
            self.cmbCANChnl.Text = 'CH1'
            self.cmbCANChnl.Items.Assign(['CH1','CH2','CH3','CH4','CH5','CH6'])
            # Create control: edtBaseID = Edit(self)
            self.edtBaseID = Edit(self)
            self.edtBaseID.Name = "edtBaseID"
            self.edtBaseID.Parent = self.pnlWSSHeader
            self.edtBaseID.Left = 176
            self.edtBaseID.Top = 40
            self.edtBaseID.Width = 120
            self.edtBaseID.Height = 23
            self.edtBaseID.Cursor = crArrow
            self.edtBaseID.NumbersOnly = True
            self.edtBaseID.TabOrder = 1
            self.edtBaseID.Text = '0x04x'
            # Create control: cmbConfigKind = ComboBox(self)
            self.cmbConfigKind = ComboBox(self)
            self.cmbConfigKind.Name = "cmbConfigKind"
            self.cmbConfigKind.Parent = self.pnlWSSHeader
            self.cmbConfigKind.Left = 320
            self.cmbConfigKind.Top = 40
            self.cmbConfigKind.Width = 120
            self.cmbConfigKind.Height = 23
            self.cmbConfigKind.Cursor = crArrow
            self.cmbConfigKind.ItemIndex = 0
            self.cmbConfigKind.TabOrder = 2
            self.cmbConfigKind.Text = 'Common Mode'
            self.cmbConfigKind.Items.Assign(['Common Mode','Individual Mode'])
            # Create control: btnConfig = Button(self)
            self.btnConfig = Button(self)
            self.btnConfig.Name = "btnConfig"
            self.btnConfig.Parent = self.pnlWSSHeader
            self.btnConfig.Left = 496
            self.btnConfig.Top = 40
            self.btnConfig.Width = 120
            self.btnConfig.Height = 25
            self.btnConfig.Cursor = crArrow
            self.btnConfig.Caption = 'Configuration'
            self.btnConfig.ImageIndex = 353
            self.btnConfig.Images = app.get_system_imagelist_16px()
            self.btnConfig.TabOrder = 3
            # Create control: pgcWSSControl = PageControl(self)
            self.pgcWSSControl = PageControl(self)
            self.pgcWSSControl.Name = "pgcWSSControl"
            self.pgcWSSControl.Parent = self.tabshtWSS
            self.pgcWSSControl.Left = 0
            self.pgcWSSControl.Top = 80
            self.pgcWSSControl.Width = 781
            self.pgcWSSControl.Height = 453
            self.pgcWSSControl.Cursor = crArrow
            self.pgcWSSControl.Align = "alClient"
            self.pgcWSSControl.Images = app.get_system_imagelist_16px()
            self.pgcWSSControl.TabOrder = 1
            # Create control: shtWSSConfig = TabSheet(self)
            self.shtWSSConfig = TabSheet(self)
            self.shtWSSConfig.Name = "shtWSSConfig"
            self.shtWSSConfig.PageControl = self.pgcWSSControl
            self.shtWSSConfig.Cursor = crArrow
            self.shtWSSConfig.Caption = 'Configuration'
            # Create control: Panel5 = Panel(self)
            self.Panel5 = Panel(self)
            self.Panel5.Name = "Panel5"
            self.Panel5.Parent = self.shtWSSConfig
            self.Panel5.Left = 0
            self.Panel5.Top = 0
            self.Panel5.Width = 773
            self.Panel5.Height = 56
            self.Panel5.Cursor = crArrow
            self.Panel5.Align = "alTop"
            self.Panel5.BevelOuter = "bvNone"
            self.Panel5.Caption = 'Panel4'
            self.Panel5.ShowCaption = "False"
            self.Panel5.TabOrder = 0
            # Create control: lblWheel = Label(self)
            self.lblWheel = Label(self)
            self.lblWheel.Name = "lblWheel"
            self.lblWheel.Parent = self.Panel5
            self.lblWheel.Left = 24
            self.lblWheel.Top = 16
            self.lblWheel.Width = 33
            self.lblWheel.Height = 15
            self.lblWheel.Cursor = crArrow
            self.lblWheel.Caption = 'Wheel'
            # Create control: lblRadius = Label(self)
            self.lblRadius = Label(self)
            self.lblRadius.Name = "lblRadius"
            self.lblRadius.Parent = self.Panel5
            self.lblRadius.Left = 104
            self.lblRadius.Top = 16
            self.lblRadius.Width = 54
            self.lblRadius.Height = 15
            self.lblRadius.Cursor = crArrow
            self.lblRadius.Caption = 'Radius(m)'
            # Create control: lblCount = Label(self)
            self.lblCount = Label(self)
            self.lblCount.Name = "lblCount"
            self.lblCount.Parent = self.Panel5
            self.lblCount.Left = 192
            self.lblCount.Top = 16
            self.lblCount.Width = 64
            self.lblCount.Height = 15
            self.lblCount.Cursor = crArrow
            self.lblCount.Caption = 'Teeth Count'
            # Create control: lblDirection = Label(self)
            self.lblDirection = Label(self)
            self.lblDirection.Name = "lblDirection"
            self.lblDirection.Parent = self.Panel5
            self.lblDirection.Left = 272
            self.lblDirection.Top = 16
            self.lblDirection.Width = 48
            self.lblDirection.Height = 15
            self.lblDirection.Cursor = crArrow
            self.lblDirection.Caption = 'Direction'
            # Create control: lblLongRange = Label(self)
            self.lblLongRange = Label(self)
            self.lblLongRange.Name = "lblLongRange"
            self.lblLongRange.Parent = self.Panel5
            self.lblLongRange.Left = 344
            self.lblLongRange.Top = 16
            self.lblLongRange.Width = 63
            self.lblLongRange.Height = 15
            self.lblLongRange.Cursor = crArrow
            self.lblLongRange.Caption = 'Long Range'
            # Create control: lblSLM = Label(self)
            self.lblSLM = Label(self)
            self.lblSLM.Name = "lblSLM"
            self.lblSLM.Parent = self.Panel5
            self.lblSLM.Left = 424
            self.lblSLM.Top = 16
            self.lblSLM.Width = 23
            self.lblSLM.Height = 15
            self.lblSLM.Cursor = crArrow
            self.lblSLM.Caption = 'SLM'
            # Create control: lblGDR = Label(self)
            self.lblGDR = Label(self)
            self.lblGDR.Name = "lblGDR"
            self.lblGDR.Parent = self.Panel5
            self.lblGDR.Left = 496
            self.lblGDR.Top = 16
            self.lblGDR.Width = 23
            self.lblGDR.Height = 15
            self.lblGDR.Cursor = crArrow
            self.lblGDR.Caption = 'GDR'
            # Create control: lblDR = Label(self)
            self.lblDR = Label(self)
            self.lblDR.Name = "lblDR"
            self.lblDR.Parent = self.Panel5
            self.lblDR.Left = 592
            self.lblDR.Top = 16
            self.lblDR.Width = 46
            self.lblDR.Height = 15
            self.lblDR.Cursor = crArrow
            self.lblDR.Caption = 'lblWheel'
            # Create control: shtWSSControl = TabSheet(self)
            self.shtWSSControl = TabSheet(self)
            self.shtWSSControl.Name = "shtWSSControl"
            self.shtWSSControl.PageControl = self.pgcWSSControl
            self.shtWSSControl.Cursor = crArrow
            self.shtWSSControl.Caption = 'Control'
            # Create control: TabSheet2 = TabSheet(self)
            self.TabSheet2 = TabSheet(self)
            self.TabSheet2.Name = "TabSheet2"
            self.TabSheet2.PageControl = self.pcMain
            self.TabSheet2.Cursor = crArrow
            self.TabSheet2.Caption = 'Sheet 2'
        finally:
            # End UI auto creation
            self.EndUIAutoCreation()
# Auto Generated Python Code, do not modify END [UI] ----------------
        # your init code starts here...
        self.log('this is tigerte form')
        def OnpcMainDrawTab(Control, TabIndex, Rect, Active):
            print('begin drawing tab')
            print(self.pcMain.ActivePageIndex)
            if TabIndex == self.pcMain.ActivePageIndex:
                self.pcMain.Canvas.Font.Color = clGreen
                # self.pcMain.Canvas.Brush.Color = clWhite
                print('green')
            else:
                self.pcMain.Canvas.Font.Color = clGray
                # self.pcMain.Canvas.Brush.Color = clGray
                print('clGray')
            DT_CENTER = 1
            DT_SINGLELINE = 32
            DT_VCENTER = 4
            # self.pcMain.Canvas.Font.Color = clRed
            s = self.pcMain.Pages[TabIndex].Caption
            rtl.draw_text(self.pcMain.Canvas.Handle, s, Rect.Left, Rect.Top, Rect.Right-Rect.Left, Rect.Bottom-Rect.Top, DT_CENTER + DT_SINGLELINE + DT_VCENTER)
            self.log_hint('On Draw Tab Index: ' + str(TabIndex) + ': ' + s + ', ' + str(self.pcMain.Canvas.Handle))
        self.pcMain.OnDrawTab = OnpcMainDrawTab
        def OnpcMainChange(sender):
            self.pcMain.OnChange = OnpcMainChange
# Auto Generated Python Code, do not modify START [MAIN] ------------
if __name__ == "__main__":
    try:
        TIO_Configuration().Show()
        Application.Run()
    except SystemExit:
        pass
# Auto Generated Python Code, do not modify END [MAIN] --------------
