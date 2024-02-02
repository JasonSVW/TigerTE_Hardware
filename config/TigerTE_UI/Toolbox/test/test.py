from TSMaster import *
import sys
sys.path.append(app.get_current_toolbox_path('test'))
import ConfigDialog
blacklist = ["tkinter"] # modules such as tkinter will release GIL by itself, which is not allowed in TSMster Toolbox
for mod in blacklist:
    if sys.modules.get(mod):
        tmp_import = __import__ (mod)
        sys.modules[mod] = None

# Auto Generated Python Code, do not modify START [UI] --------------
class test(frmTSForm):
    def __init__(self):
        # set type name internally
        self.ExternalTypeName = type(self).__name__
        try:
            # Form properties
            if not self.IsConfigurationLoaded:
                self.Left = 208
                self.Top = 208
                self.Caption = 'test'
                self.ClientHeight = 502
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
            # Create control: Button1 = Button(self)
            self.Button1 = Button(self)
            self.Button1.Name = "Button1"
            self.Button1.Parent = self
            self.Button1.Left = 192
            self.Button1.Top = 208
            self.Button1.Width = 440
            self.Button1.Height = 88
            self.Button1.Cursor = crArrow
            self.Button1.Caption = 'Button1'
            self.Button1.Images = app.get_system_imagelist_16px()
            self.Button1.TabOrder = 0
        finally:
            # End UI auto creation
            self.EndUIAutoCreation()
# Auto Generated Python Code, do not modify END [UI] ----------------
        # your init code starts here...
        def onclick(sender):
            frm = ConfigDialog.ConfigDialogForm(self)
            frm.Hide()
            frm.ShowModal()
            frm = None
        self.Button1.OnClick = onclick
        
# Auto Generated Python Code, do not modify START [MAIN] ------------
if __name__ == "__main__":
    try:
        test().Show()
        Application.Run()
    except SystemExit:
        pass
# Auto Generated Python Code, do not modify END [MAIN] --------------
