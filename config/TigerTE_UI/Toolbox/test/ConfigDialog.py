from TSMaster import *
import sys

# Auto Generated Python Code, do not modify START [UI] --------------
class ConfigDialogForm(Form):
    def __init__(self, Parent):
        try:
            # Form properties
            self.ClientHeight = 176
            self.ClientWidth = 285
            self.Caption = 'Config Dialog'
            self.Color = clBtnFace
            self.DoubleBuffered = True
            self.Font.Charset = DEFAULT_CHARSET
            self.Font.Color = clWindowText
            self.Font.Height = -12
            self.Font.Name = 'Segoe UI'
            self.Font.Style = []
            self.KeyPreview = True
            self.Position = "poMainFormCenter"
            self.Visible = True
            self.TextHeight = 15
            # Create control: lblValue = Label(self)
            self.lblValue = Label(self)
            self.lblValue.Name = "lblValue"
            self.lblValue.Parent = self
            self.lblValue.Left = 40
            self.lblValue.Top = 64
            self.lblValue.Width = 28
            self.lblValue.Height = 15
            self.lblValue.Cursor = crArrow
            self.lblValue.Caption = 'Value'
            # Create control: Button1 = Button(self)
            self.Button1 = Button(self)
            self.Button1.Name = "Button1"
            self.Button1.Parent = self
            self.Button1.AlignWithMargins = True
            self.Button1.Left = 12
            self.Button1.Top = 139
            self.Button1.Width = 261
            self.Button1.Height = 25
            self.Button1.Cursor = crArrow
            self.Button1.Margins.Left = 12
            self.Button1.Margins.Top = 12
            self.Button1.Margins.Right = 12
            self.Button1.Margins.Bottom = 12
            self.Button1.Align = "alBottom"
            self.Button1.Caption = 'Button1'
            self.Button1.Images = app.get_system_imagelist_16px()
            self.Button1.TabOrder = 0
            # Create control: edtValue = Edit(self)
            self.edtValue = Edit(self)
            self.edtValue.Name = "edtValue"
            self.edtValue.Parent = self
            self.edtValue.Left = 104
            self.edtValue.Top = 59
            self.edtValue.Width = 121
            self.edtValue.Height = 23
            self.edtValue.Cursor = crArrow
            self.edtValue.TabOrder = 1
            self.edtValue.TextHint = 'Input a value...'
        finally:
            # End UI auto creation
            def on_btn_click(sender):
                self.Close()
            self.Button1.OnClick = on_btn_click
            
# Auto Generated Python Code, do not modify END [UI] ----------------
        # your init code starts here...
        