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
                self.Left = 452
                self.Top = 208
                self.Caption = 'TIO_Configuration'
                self.ClientHeight = 503
                self.ClientWidth = 786
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
            self.pnlMain.Width = 786
            self.pnlMain.Height = 503
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
            self.pnlHeader.Width = 786
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
            self.pcMain.Width = 786
            self.pcMain.Height = 443
            self.pcMain.Cursor = crArrow
            self.pcMain.Align = "alClient"
            self.pcMain.Images = app.get_system_imagelist_16px()
            self.pcMain.MultiLine = True
            self.pcMain.TabHeight = 120
            self.pcMain.TabOrder = 1
            self.pcMain.TabPosition = "tpLeft"
            self.pcMain.TabWidth = 40
            # Create control: tabshtWSS = TabSheet(self)
            self.tabshtWSS = TabSheet(self)
            self.tabshtWSS.Name = "tabshtWSS"
            self.tabshtWSS.PageControl = self.pcMain
            self.tabshtWSS.Cursor = crArrow
            self.tabshtWSS.Caption = 'Sheet 1'
            self.tabshtWSS.ImageIndex = 2
            # Create control: pnlWSSHeader = Panel(self)
            self.pnlWSSHeader = Panel(self)
            self.pnlWSSHeader.Name = "pnlWSSHeader"
            self.pnlWSSHeader.Parent = self.tabshtWSS
            self.pnlWSSHeader.Left = 0
            self.pnlWSSHeader.Top = 0
            self.pnlWSSHeader.Width = 658
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
            self.lblBaseID.Width = 48
            self.lblBaseID.Height = 15
            self.lblBaseID.Cursor = crArrow
            self.lblBaseID.Caption = 'lblBaseID'
            # Create control: lblWSSType = Label(self)
            self.lblWSSType = Label(self)
            self.lblWSSType.Name = "lblWSSType"
            self.lblWSSType.Parent = self.pnlWSSHeader
            self.lblWSSType.Left = 328
            self.lblWSSType.Top = 16
            self.lblWSSType.Width = 60
            self.lblWSSType.Height = 15
            self.lblWSSType.Cursor = crArrow
            self.lblWSSType.Caption = 'lblWSSType'
            # Create control: lblInfo = Label(self)
            self.lblInfo = Label(self)
            self.lblInfo.Name = "lblInfo"
            self.lblInfo.Parent = self.pnlWSSHeader
            self.lblInfo.Left = 496
            self.lblInfo.Top = 16
            self.lblInfo.Width = 34
            self.lblInfo.Height = 15
            self.lblInfo.Cursor = crArrow
            self.lblInfo.Caption = 'lblInfo'
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
            self.edtBaseID.Text = 'edtBaseID'
            # Create control: cmbWSSType = ComboBox(self)
            self.cmbWSSType = ComboBox(self)
            self.cmbWSSType.Name = "cmbWSSType"
            self.cmbWSSType.Parent = self.pnlWSSHeader
            self.cmbWSSType.Left = 320
            self.cmbWSSType.Top = 40
            self.cmbWSSType.Width = 120
            self.cmbWSSType.Height = 23
            self.cmbWSSType.Cursor = crArrow
            self.cmbWSSType.TabOrder = 2
            self.cmbWSSType.Text = 'cmbWSSType'
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
            # Create control: pcWSSType = PageControl(self)
            self.pcWSSType = PageControl(self)
            self.pcWSSType.Name = "pcWSSType"
            self.pcWSSType.Parent = self.tabshtWSS
            self.pcWSSType.Left = 0
            self.pcWSSType.Top = 80
            self.pcWSSType.Width = 658
            self.pcWSSType.Height = 355
            self.pcWSSType.Cursor = crArrow
            self.pcWSSType.Align = "alClient"
            self.pcWSSType.Images = app.get_system_imagelist_16px()
            self.pcWSSType.TabOrder = 1
            # Create control: tbshtWSSType1 = TabSheet(self)
            self.tbshtWSSType1 = TabSheet(self)
            self.tbshtWSSType1.Name = "tbshtWSSType1"
            self.tbshtWSSType1.PageControl = self.pcWSSType
            self.tbshtWSSType1.Cursor = crArrow
            self.tbshtWSSType1.Caption = 'Type I'
            # Create control: tbshtWSSType2 = TabSheet(self)
            self.tbshtWSSType2 = TabSheet(self)
            self.tbshtWSSType2.Name = "tbshtWSSType2"
            self.tbshtWSSType2.PageControl = self.pcWSSType
            self.tbshtWSSType2.Cursor = crArrow
            self.tbshtWSSType2.Caption = 'Type II'
            # Create control: tbshtWSSType3 = TabSheet(self)
            self.tbshtWSSType3 = TabSheet(self)
            self.tbshtWSSType3.Name = "tbshtWSSType3"
            self.tbshtWSSType3.PageControl = self.pcWSSType
            self.tbshtWSSType3.Cursor = crArrow
            self.tbshtWSSType3.Caption = 'Type III'
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
# Auto Generated Python Code, do not modify START [MAIN] ------------
if __name__ == "__main__":
    try:
        TIO_Configuration().Show()
        Application.Run()
    except SystemExit:
        pass
# Auto Generated Python Code, do not modify END [MAIN] --------------
