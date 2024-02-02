from TSMaster import *
app.tsmp_load(r'bin\demoapp.mp', True , True)
if app.is_tsmaster_host(): # only vaid in TSMaster App
    import TSMaster.demoapp as demoapp

# Auto Generated Python Code, do not modify START [UI] --------------
class demo(frmTSForm):
    def __init__(self):
        # set type name internally
        self.ExternalTypeName = type(self).__name__
        try:
            # Form properties
            if not self.IsConfigurationLoaded:
                self.Left = 130
                self.Top = 130
                self.Caption = 'demo'
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
            self.Button1.Left = 80
            self.Button1.Top = 104
            self.Button1.Width = 75
            self.Button1.Height = 25
            self.Button1.Cursor = crArrow
            self.Button1.Caption = 'Button1'
            self.Button1.Images = app.get_system_imagelist_16px()
            self.Button1.TabOrder = 0
        finally:
            # End UI auto creation
            self.EndUIAutoCreation()
# Auto Generated Python Code, do not modify END [UI] ----------------
        # your init code starts here...
        def ButtonOnClick(sender):
            demoapp.demo_test()
            app.tsmp_load(r'bin\testmp.mp', True , True)
            myfun = app.tsmp_get_function_prototype('testmp', 'testfunc1')
            print(myfun)
            
        self.Button1.OnClick = ButtonOnClick
        
# Auto Generated Python Code, do not modify START [MAIN] ------------
if __name__ == "__main__":
    try:
        demo().Show()
        Application.Run()
    except SystemExit:
        pass
# Auto Generated Python Code, do not modify END [MAIN] --------------
