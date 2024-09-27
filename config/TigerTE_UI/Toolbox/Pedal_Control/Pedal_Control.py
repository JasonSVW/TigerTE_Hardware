from TSMaster import *
import sys
blacklist = ["tkinter"] # modules such as tkinter will release GIL by itself, which is not allowed in TSMster Toolbox
for mod in blacklist:
    if sys.modules.get(mod):
        tmp_import = __import__ (mod)
        sys.modules[mod] = None
if app.is_tsmaster_host(): # only vaid in TSMaster App
    import TSMaster.tio as tio

#region global definition
vArmed = False

def debug_print(AObject):
    # logging.debug(f'debug info: {AObject}')
    pass
    # print(f'debug info: {AObject}')
       
#endregion global definition
# Auto Generated Python Code, do not modify START [UI] --------------
class Pedal_Control(frmTSForm):
    def __init__(self):
        # set type name internally
        self.ExternalTypeName = type(self).__name__
        if hasattr(self, "on_before_ui_creation"):
            method = getattr(self, "on_before_ui_creation")
            method()
        try:
            # Form properties
            if not self.IsConfigurationLoaded:
                self.Left = 195
                self.Top = 193
                self.Caption = 'Pedal_Control'
                self.ClientHeight = 659
                self.ClientWidth = 1303
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
            # Create control: pnlGround = Panel(self)
            self.pnlGround = Panel(self)
            self.pnlGround.Name = "pnlGround"
            self.pnlGround.Parent = self
            self.pnlGround.Left = 0
            self.pnlGround.Top = 0
            self.pnlGround.Width = 1303
            self.pnlGround.Height = 659
            self.pnlGround.Cursor = crArrow
            self.pnlGround.Align = "alClient"
            self.pnlGround.Caption = 'pnlGround'
            self.pnlGround.ParentBackground = False
            self.pnlGround.ShowCaption = "False"
            self.pnlGround.TabOrder = 0
            # Create control: pnlTop = Panel(self)
            self.pnlTop = Panel(self)
            self.pnlTop.Name = "pnlTop"
            self.pnlTop.Parent = self.pnlGround
            self.pnlTop.Left = 1
            self.pnlTop.Top = 1
            self.pnlTop.Width = 1301
            self.pnlTop.Height = 44
            self.pnlTop.Cursor = crArrow
            self.pnlTop.Align = "alTop"
            self.pnlTop.BevelEdges = ["beTop", "beBottom"]
            self.pnlTop.BevelKind = "bkFlat"
            self.pnlTop.BevelOuter = "bvNone"
            self.pnlTop.Caption = 'pnlTop'
            self.pnlTop.ParentBackground = False
            self.pnlTop.ShowCaption = "False"
            self.pnlTop.TabOrder = 0
            # Create control: svgbtnStart = TSSvgImageButton(self)
            self.svgbtnStart = TSSvgImageButton(self)
            self.svgbtnStart.Name = "svgbtnStart"
            self.svgbtnStart.Parent = self.pnlTop
            self.svgbtnStart.Left = 0
            self.svgbtnStart.Top = 0
            self.svgbtnStart.Width = 70
            self.svgbtnStart.Height = 40
            self.svgbtnStart.Cursor = crArrow
            self.svgbtnStart.Align = "alLeft"
            self.svgbtnStart.Caption = 'Start'
            self.svgbtnStart.TabOrder = 0
            self.svgbtnStart.VerticalAlignment = "taAlignBottom"
            self.svgbtnStart.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_start.svg'
            self.svgbtnStart.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMxMTczNzUzOTI1IiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjM3Njk0IiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgd2lkdGg9IjEyOCIgaGVpZ2h0PSIxMjgiPjxkZWZzPjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+PC9zdHlsZT48L2RlZnM+PHBhdGggZD0iTTUxMiA1MTJtLTUxMiAwYTUxMiA1MTIgMCAxIDAgMTAyNCAwIDUxMiA1MTIgMCAxIDAtMTAyNCAwWiIgZmlsbD0iIzEyOTZkYiIgcC1pZD0iMzc2OTUiIGRhdGEtc3BtLWFuY2hvci1pZD0iYTMxM3guNzc4MTA2OS4wLmk0NCIgY2xhc3M9InNlbGVjdGVkIj48L3BhdGg+PHBhdGggZD0iTTY5MS45NjggNTkxLjIwNjRsLTEyMy45MDQtNjMuMzg1NmEzNy40Nzg0IDM3LjQ3ODQgMCAwIDAtMTQuNzQ1Ni0zLjA3Mkg1MzIuNDhWMzU2LjUwNTZhNDEuNDcyIDQxLjQ3MiAwIDAgMC00MS4wMTEyLTQyLjA4NjQgNDEuNDcyIDQxLjQ3MiAwIDAgMC00MC45NiA0Mi4wODY0djMwMS4xNTg0bC05My42OTYtMjAuMTcyOGMtMi4yMDE2LTAuMjU2LTQuMDk2LTAuODcwNC02LjUwMjQtMC44NzA0YTMwLjAwMzIgMzAuMDAzMiAwIDAgMC0yMS41NTUyIDkuMzE4NEwzMDcuMiA2NjguMzEzNmwxMzQuODYwOCAxMzguNDk2QTQwLjY1MjggNDAuNjUyOCAwIDAgMCA0NzEuMDQgODE5LjJoMTg1LjM0NGMyMC40OCAwIDM2LjM1Mi0xNS40NjI0IDM5LjM3MjgtMzUuODRsMjAuNDgtMTQ3Ljg2NTZjMC4yNTYtMS45NDU2IDAuNTYzMi0zLjg5MTIgMC41NjMyLTUuNTI5NmE0Mi4wODY0IDQyLjA4NjQgMCAwIDAtMjQuODMyLTM4Ljc1ODRNNDIzLjI3MDQgNDYxLjMxMlYzNTYuNTU2OGMwLTM4LjcwNzIgMzAuNjE3Ni03MC4wOTI4IDY4LjI0OTYtNzAuMDkyOHM2OC4yNDk2IDMxLjM4NTYgNjguMjQ5NiA3MC4wOTI4djEwNC44NTc2YTEyNi43MiAxMjYuNzIgMCAwIDAgNTQuNTc5Mi0xMDQuODU3NkM2MTQuNCAyODYuNzIgNTU5LjUxMzYgMjMwLjQgNDkxLjUyIDIzMC40Yy02Ny45NDI0IDAtMTIyLjc3NzYgNTYuMzItMTIyLjc3NzYgMTI2LjE1NjggMCA0My43MjQ4IDIxLjUwNCA4Mi4xNzYgNTQuNTc5MiAxMDQuODU3NiIgZmlsbD0iI0ZGRkZGRiIgcC1pZD0iMzc2OTYiPjwvcGF0aD48L3N2Zz4NCg__'
            self.svgbtnStart.ImageIndex = -1
            self.svgbtnStart.ImageStretch = False
            self.svgbtnStart.ReadOnly = False
            # Create control: svgbtnStop = TSSvgImageButton(self)
            self.svgbtnStop = TSSvgImageButton(self)
            self.svgbtnStop.Name = "svgbtnStop"
            self.svgbtnStop.Parent = self.pnlTop
            self.svgbtnStop.Left = 70
            self.svgbtnStop.Top = 0
            self.svgbtnStop.Width = 71
            self.svgbtnStop.Height = 40
            self.svgbtnStop.Cursor = crArrow
            self.svgbtnStop.Align = "alLeft"
            self.svgbtnStop.Caption = 'Stop'
            self.svgbtnStop.TabOrder = 1
            self.svgbtnStop.VerticalAlignment = "taAlignBottom"
            self.svgbtnStop.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_stop.svg'
            self.svgbtnStop.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMxMTc0MzE3MDU4IiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9Ijc4MTQ4IiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgd2lkdGg9IjEyOCIgaGVpZ2h0PSIxMjgiPjxkZWZzPjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+PC9zdHlsZT48L2RlZnM+PHBhdGggZD0iTTY2Ny44ODY5MzMgMzk4LjQzODRoLTMxMS43NzM4NjZhNDUuNzcyOCA0NS43NzI4IDAgMSAxIDAtOTEuNTc5NzMzaDMxMS43NzM4NjZhNDUuODA2OTMzIDQ1LjgwNjkzMyAwIDAgMSAwIDkxLjU3OTczM00wIDUxMmMwIDI4Mi43NjA1MzMgMjI5LjIzOTQ2NyA1MTIgNTEyIDUxMiA1Ny4yNzU3MzMgMCAxMTIuMjk4NjY3LTkuNTU3MzMzIDE2My43MDM0NjctMjYuODk3MDY3LTMuNzU0NjY3LTUuMDE3Ni02MS41NDI0LTE3Ni45ODEzMzMtNzUuOTEyNTM0LTIyMS40OTEyLTE0LjM3MDEzMy00NC41MDk4NjcgMTYuNjU3MDY3LTczLjI1MDEzMyAzNy40NDQyNjctODQuMDM2MjY2IDIwLjgyMTMzMy0xMC43ODYxMzMgNjEuNzgxMzMzLTEwLjc4NjEzMyA3OC4xNjUzMzMgOC44MDY0bC0wLjE3MDY2Ni0xNTEuMjQ0OGMwLTAuODUzMzMzIDAuMDY4MjY3LTEuNzA2NjY3IDAuMTcwNjY2LTIuNTk0MTM0IDUuMzI0OC0zOS45MzYgMjkuNjI3NzMzLTYyLjcwMjkzMyA2OC4xOTg0LTYyLjcwMjkzM3M2Mi44Mzk0NjcgMjIuNzY2OTMzIDY4LjE2NDI2NyA2Mi43MDI5MzNjMC4xMDI0IDAuODUzMzMzIDAuMTcwNjY3IDEuNzA2NjY3IDAuMTcwNjY3IDIuNTk0MTM0djE3Ny4zNTY4bDExNy44MjgyNjYgMTQuNzc5NzMzQTUwOS42Nzg5MzMgNTA5LjY3ODkzMyAwIDAgMCAxMDI0IDUxMmMwLTI4Mi43NjA1MzMtMjI5LjIzOTQ2Ny01MTItNTEyLTUxMkMyMjkuMjM5NDY3IDAgMCAyMjkuMjM5NDY3IDAgNTEyeiIgZmlsbD0iI2Q4MWUwNiIgcC1pZD0iNzgxNDkiIGRhdGEtc3BtLWFuY2hvci1pZD0iYTMxM3guNzc4MTA2OS4wLmk1NSIgY2xhc3M9InNlbGVjdGVkIj48L3BhdGg+PHBhdGggZD0iTTc1NC4yNzg0IDc3OS45NDY2NjdjMCAyMS4yOTkyLTI5LjI1MjI2NyAyNy4yMDQyNjctMzcuNTQ2NjY3IDcuNTc3Ni0xMS43NzYtMTkuNDkwMTMzLTIxLjE2MjY2Ny0zNC4wOTkyLTI4LjIyODI2Ni00My43OTMwNjctMTAuNTgxMzMzLTE0LjU0MDgtMjAuMDM2MjY3LTE4LjQ2NjEzMy0zMy43NTc4NjctMTIuNjI5MzMzLTEzLjY4NzQ2NyA1Ljg3MDkzMy0xOC41MzQ0IDE2LjQ1MjI2Ny0xNC4yNjc3MzMgMzEuOTQ4OCA0LjI2NjY2NyAxNS40OTY1MzMgNTAuODU4NjY3IDE3OC43MjIxMzMgNjAuODI1NiAyMDAuOTQyOTMzIDcuMTY4IDE1LjkwNjEzMyAxNi4wNDI2NjcgMjEuMTk2OCAzMC43ODgyNjYgMTkuMTgyOTMzYTIwLjgyMTMzMyAyMC44MjEzMzMgMCAwIDEgMi42NjI0LTAuMjA0OGgxNzcuMDE1NDY3YzAuMzQxMzMzIDAgMS4xMjY0IDAgMi4xODQ1MzMtMC4wNjgyNjZhMjA2LjQ3MjUzMyAyMDYuNDcyNTMzIDAgMCAwIDE2LjM4NC0xLjcwNjY2N2M0LjUzOTczMy0wLjY4MjY2NyA4LjY2OTg2Ny0xLjQzMzYgMTIuMDgzMi0yLjI4NjkzMyAyLjY2MjQtMC42ODI2NjcgNC42NzYyNjctMS4zMzEyIDUuNzM0NC0xLjc3NDkzNGExNS4yNTc2IDE1LjI1NzYgMCAwIDAgMS43MDY2NjctMi45Njk2IDc0LjQxMDY2NyA3NC40MTA2NjcgMCAwIDAgNS4wMTc2LTE4LjM2MzczM2wyNi44NjI5MzMtMTI4LjE3MDY2N2ExNy44MTc2IDE3LjgxNzYgMCAwIDEgMC41MTItMS45Nzk3MzNjNS42MzItMTcuNTEwNCA1LjYzMi0yOC4yMjgyNjcgMi42NjI0LTMyLjQyNjY2Ny00LjMzNDkzMy02LjE0NC0xMS4wMjUwNjctMTAuNTgxMzMzLTIwLjgyMTMzMy0xMy4zMTJsLTEzNC4xNDQtMTYuNzkzNmExOS41MjQyNjcgMTkuNTI0MjY3IDAgMCAxLTE3LjA2NjY2Ny0xOS4zODc3MzN2LTE4My4xMjUzMzNjLTIuOTY5Ni0yMC4xMzg2NjctMTEuMjY0LTI3LjYxMzg2Ny0yOS4yODY0LTI3LjYxMzg2Ny0xOC4wNTY1MzMgMC0yNi4zNTA5MzMgNy40NDEwNjctMjkuMzIwNTMzIDI3LjYxMzg2N3YyMTkuMzQwOHoiIGZpbGw9IiNkODFlMDYiIHAtaWQ9Ijc4MTUwIiBkYXRhLXNwbS1hbmNob3ItaWQ9ImEzMTN4Ljc3ODEwNjkuMC5pNTYiIGNsYXNzPSJzZWxlY3RlZCI+PC9wYXRoPjwvc3ZnPg0K'
            self.svgbtnStop.ImageIndex = -1
            self.svgbtnStop.ImageStretch = False
            self.svgbtnStop.ReadOnly = False
            # Create control: svgbtnInit = TSSvgImageButton(self)
            self.svgbtnInit = TSSvgImageButton(self)
            self.svgbtnInit.Name = "svgbtnInit"
            self.svgbtnInit.Parent = self.pnlTop
            self.svgbtnInit.Left = 141
            self.svgbtnInit.Top = 0
            self.svgbtnInit.Width = 69
            self.svgbtnInit.Height = 40
            self.svgbtnInit.Cursor = crArrow
            self.svgbtnInit.Align = "alLeft"
            self.svgbtnInit.Caption = 'Initialize'
            self.svgbtnInit.TabOrder = 2
            self.svgbtnInit.VerticalAlignment = "taAlignBottom"
            self.svgbtnInit.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_init.svg'
            self.svgbtnInit.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMyMzg4NjM0NzczIiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjU4NzQiIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMTI4IiBoZWlnaHQ9IjEyOCI+PGRlZnM+PHN0eWxlIHR5cGU9InRleHQvY3NzIj48L3N0eWxlPjwvZGVmcz48cGF0aCBkPSJNNTEzLjAxMiA2MS45NzljLTI0NS4zNi0wLjQ4NS00NTAuMzg3IDIwMS44ODEtNDUxLjAxIDQ0NS4xNTctMC42NDIgMjUwLjUyIDE5OS44ODEgNDU0LjA2NyA0NDguMTI3IDQ1NC44ODQgMjQ1LjkwNyAwLjgwOSA0NTIuMjg0LTIwNC4wMDggNDUxLjg3MS00NDguNDU1LTAuNDE5LTI0Ny4wODgtMjAzLjI1Ny00NTEuMS00NDguOTg4LTQ1MS41ODZ6IG0xMzEuMjQxIDYwMi45MThjLTM2LjY4NSAxMC43NzMtNzEuNjU4LTAuMTczLTEwMy4yOTYtMTYuOTkzLTIwLjkyOC0xMS4xMjYtMzEuNTA2LTUuODM5LTQ2LjExNSA5LjIzMi01OC45NDIgNjAuODA2LTEyMC4xOTEgMTE5LjQwMi0xNzguMzQzIDE4MC45MzUtMTguNjM1IDE5LjcxOS0zMC44MTIgMTguOTctNTAuMTcyIDMuMjY5LTMyLjI0NC0yNi4xNTEtNjAuODY1LTU1LjI0NS04Ni41MzktODcuODM3LTEzLjA2OC0xNi41ODktMTMuMzI5LTI2LjgwMiAyLjgxNi00Mi40MzlDMjQ1Ljc3MyA2NDkuODg3IDMwNi44NzYgNTg2LjU4MSAzNjkuNjYzIDUyNWMxMi45MzQtMTIuNjg2IDE0LjkxMi0yMS40MjggNi4zOS0zOC40NzQtNDAuMzU5LTgwLjcyNi0yMi45NTItMTQyLjczOSA1MS45MTItMTkzLjQwOSA0Ni42MzMtMzEuNTYyIDk3LjcxLTUxLjA4NCAxNTQuMTUyLTU0LjczOCAxMi42NTEtMC44MTkgMjYuMjYyLTIuNDMyIDQwLjUxMyA4LjkwOC0zMS41MzYgMzEuNTE1LTYxLjYwOSA2MS4xNTItOTEuMTk4IDkxLjI2My0yNi41MTQgMjYuOTgyLTI2LjkzMiA0MS45NzctMC43MTMgNjkuMDI1IDI5LjQ2OCAzMC40MDEgNTkuOTc3IDU5Ljc5MSA4OS45NjMgODkuNjkyIDIxLjEwNyAyMS4wNDcgNDEuNjA3IDIwLjA0NSA2MS44NzMtMS4yMjMgMzAuNTc0LTMyLjA4NSA2MS4yMjgtNjQuMDk0IDkxLjY0Mi05NS45MTkgNS4xOTUgNC43NjcgNi40NTkgNS4zNjEgNi43MjkgNi4yNTUgMjUuNDQgODQuMjIyLTUzLjQyNSAyMzQuMDctMTM2LjY3MyAyNTguNTE3eiIgZmlsbD0iIzEyOTZkYiIgcC1pZD0iNTg3NSI+PC9wYXRoPjwvc3ZnPg0K'
            self.svgbtnInit.ImageIndex = -1
            self.svgbtnInit.ImageStretch = False
            self.svgbtnInit.ReadOnly = False
            # Create control: svgbtnJogIn = TSSvgImageButton(self)
            self.svgbtnJogIn = TSSvgImageButton(self)
            self.svgbtnJogIn.Name = "svgbtnJogIn"
            self.svgbtnJogIn.Parent = self.pnlTop
            self.svgbtnJogIn.Left = 210
            self.svgbtnJogIn.Top = 0
            self.svgbtnJogIn.Width = 71
            self.svgbtnJogIn.Height = 40
            self.svgbtnJogIn.Cursor = crArrow
            self.svgbtnJogIn.Align = "alLeft"
            self.svgbtnJogIn.Caption = 'Jog In'
            self.svgbtnJogIn.TabOrder = 3
            self.svgbtnJogIn.VerticalAlignment = "taAlignBottom"
            self.svgbtnJogIn.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_jog_in.svg'
            self.svgbtnJogIn.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMyMzg0MTYyMjY3IiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjMzOTIiIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMTI4IiBoZWlnaHQ9IjEyOCI+PGRlZnM+PHN0eWxlIHR5cGU9InRleHQvY3NzIj48L3N0eWxlPjwvZGVmcz48cGF0aCBkPSJNNTk3LjMzMzMzMyA4NS4zMzMzMzN2ODUzLjMzMzMzNGg0Mi42NjY2NjdjNDcuMDE4NjY3IDAgODUuMzMzMzMzLTM4LjMxNDY2NyA4NS4zMzMzMzMtODUuMzMzMzM0di0yMTMuMzMzMzMzaDIxMy4zMzMzMzRWMzg0aC0yMTMuMzMzMzM0VjE3MC42NjY2NjdjMC00Ny4wMTg2NjctMzguMzE0NjY3LTg1LjMzMzMzMy04NS4zMzMzMzMtODUuMzMzMzM0ek0yNTYgMzg0bC0xNzAuNjY2NjY3IDEyOCAxNzAuNjY2NjY3IDEyOHYtODUuMzMzMzMzaDI1NnYtODUuMzMzMzM0SDI1NnoiIGZpbGw9IiMxMjk2ZGIiIHAtaWQ9IjMzOTMiPjwvcGF0aD48L3N2Zz4NCg__'
            self.svgbtnJogIn.ImageIndex = -1
            self.svgbtnJogIn.ImageStretch = False
            self.svgbtnJogIn.ReadOnly = False
            # Create control: svgbtnJogOut = TSSvgImageButton(self)
            self.svgbtnJogOut = TSSvgImageButton(self)
            self.svgbtnJogOut.Name = "svgbtnJogOut"
            self.svgbtnJogOut.Parent = self.pnlTop
            self.svgbtnJogOut.Left = 281
            self.svgbtnJogOut.Top = 0
            self.svgbtnJogOut.Width = 70
            self.svgbtnJogOut.Height = 40
            self.svgbtnJogOut.Cursor = crArrow
            self.svgbtnJogOut.Align = "alLeft"
            self.svgbtnJogOut.Caption = 'Jog Out'
            self.svgbtnJogOut.TabOrder = 4
            self.svgbtnJogOut.VerticalAlignment = "taAlignBottom"
            self.svgbtnJogOut.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_jog_out.svg'
            self.svgbtnJogOut.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMyMzg0MTY5NTExIiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjM1ODciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMTI4IiBoZWlnaHQ9IjEyOCI+PGRlZnM+PHN0eWxlIHR5cGU9InRleHQvY3NzIj48L3N0eWxlPjwvZGVmcz48cGF0aCBkPSJNMzg0IDg1LjMzMzMzM2MtNDcuMDE4NjY3IDAtODUuMzMzMzMzIDM4LjMxNDY2Ny04NS4zMzMzMzMgODUuMzMzMzM0djIxMy4zMzMzMzNIODUuMzMzMzMzdjI1NmgyMTMuMzMzMzM0djIxMy4zMzMzMzNjMCA0Ny4wMTg2NjcgMzguMzE0NjY3IDg1LjMzMzMzMyA4NS4zMzMzMzMgODUuMzMzMzM0aDQyLjY2NjY2N1Y4NS4zMzMzMzN6IG0zODQgMjk4LjY2NjY2N3Y4NS4zMzMzMzNoLTI1NnY4NS4zMzMzMzRoMjU2djg1LjMzMzMzM2wxNzAuNjY2NjY3LTEyOHoiIGZpbGw9IiMxMjk2ZGIiIHAtaWQ9IjM1ODgiPjwvcGF0aD48L3N2Zz4NCg__'
            self.svgbtnJogOut.ImageIndex = -1
            self.svgbtnJogOut.ImageStretch = False
            self.svgbtnJogOut.ReadOnly = False
            # Create control: svgbtnSetZero = TSSvgImageButton(self)
            self.svgbtnSetZero = TSSvgImageButton(self)
            self.svgbtnSetZero.Name = "svgbtnSetZero"
            self.svgbtnSetZero.Parent = self.pnlTop
            self.svgbtnSetZero.Left = 351
            self.svgbtnSetZero.Top = 0
            self.svgbtnSetZero.Width = 70
            self.svgbtnSetZero.Height = 40
            self.svgbtnSetZero.Cursor = crArrow
            self.svgbtnSetZero.Align = "alLeft"
            self.svgbtnSetZero.Caption = 'Set Zero'
            self.svgbtnSetZero.TabOrder = 5
            self.svgbtnSetZero.VerticalAlignment = "taAlignBottom"
            self.svgbtnSetZero.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_set_zero.svg'
            self.svgbtnSetZero.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMxNDQ5NDA1MTMxIiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjMxMjkzIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgd2lkdGg9IjEyOCIgaGVpZ2h0PSIxMjgiPjxkZWZzPjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+PC9zdHlsZT48L2RlZnM+PHBhdGggZD0iTTgzNi4yNjY2NjcgMEgxODcuNzMzMzMzQTE4Ny43MzMzMzMgMTg3LjczMzMzMyAwIDAgMCAwIDE4Ny43MzMzMzN2NjQ4LjUzMzMzNGExODcuNzMzMzMzIDE4Ny43MzMzMzMgMCAwIDAgMTg3LjczMzMzMyAxODcuNzMzMzMzaDY0OC41MzMzMzRhMTg3LjczMzMzMyAxODcuNzMzMzMzIDAgMCAwIDE4Ny43MzMzMzMtMTg3LjczMzMzM1YxODcuNzMzMzMzQTE4Ny43MzMzMzMgMTg3LjczMzMzMyAwIDAgMCA4MzYuMjY2NjY3IDB6IG04NS4zMzMzMzMgODM2LjI2NjY2N2E4NS4zMzMzMzMgODUuMzMzMzMzIDAgMCAxLTg1LjMzMzMzMyA4NS4zMzMzMzNIMTg3LjczMzMzM2E4NS4zMzMzMzMgODUuMzMzMzMzIDAgMCAxLTg1LjMzMzMzMy04NS4zMzMzMzNWMTg3LjczMzMzM2E4NS4zMzMzMzMgODUuMzMzMzMzIDAgMCAxIDg1LjMzMzMzMy04NS4zMzMzMzNoNjQ4LjUzMzMzNGE4NS4zMzMzMzMgODUuMzMzMzMzIDAgMCAxIDg1LjMzMzMzMyA4NS4zMzMzMzN6IiBmaWxsPSIjMTI5NmRiIiBwLWlkPSIzMTI5NCI+PC9wYXRoPjxwYXRoIGQ9Ik01MTcuOTczMzMzIDI1NnE5MS4xMzYgMCAxNDcuMjg1MzM0IDgzLjYyNjY2N2EzMTguMjkzMzMzIDMxOC4yOTMzMzMgMCAwIDEgNTEuMiAxODEuOTMwNjY2IDI4MS4yNTg2NjcgMjgxLjI1ODY2NyAwIDAgMS00OS40OTMzMzQgMTcwLjY2NjY2N0ExODAuMjI0IDE4MC4yMjQgMCAwIDEgNTEyIDc2OGExNzkuNTQxMzMzIDE3OS41NDEzMzMgMCAwIDEtMTUzLjYtNzkuNzAxMzMzIDI5MC4xMzMzMzMgMjkwLjEzMzMzMyAwIDAgMS01MS4yLTE3NC41OTIgMjkyLjAxMDY2NyAyOTIuMDEwNjY3IDAgMCAxIDUyLjkwNjY2Ny0xNzcuMzIyNjY3QTE4NC42NjEzMzMgMTg0LjY2MTMzMyAwIDAgMSA1MTcuOTczMzMzIDI1NnpNNTEyIDM2Ny40NDUzMzNhNzUuOTQ2NjY3IDc1Ljk0NjY2NyAwIDAgMC02OC4yNjY2NjcgNDYuMDggMjExLjk2OCAyMTEuOTY4IDAgMCAwLTIyLjM1NzMzMyAxMDEuMzc2QTIxMC43NzMzMzMgMjEwLjc3MzMzMyAwIDAgMCA0NDMuNzMzMzMzIDYxNS43NjUzMzNhNzcuODI0IDc3LjgyNCAwIDAgMCA2OS40NjEzMzQgNDUuNTY4cTM5Ljc2NTMzMyAwIDY0LTQ4LjEyOGEyMzAuOTEyIDIzMC45MTIgMCAwIDAgMjEuODQ1MzMzLTEwNC4xMDY2NjYgMjAyLjA2OTMzMyAyMDIuMDY5MzMzIDAgMCAwLTIxLjE2MjY2Ny05Ny42MjEzMzRBNzIuODc0NjY3IDcyLjg3NDY2NyAwIDAgMCA1MTIgMzY3LjQ0NTMzM3oiIGZpbGw9IiMxMjk2ZGIiIHAtaWQ9IjMxMjk1Ij48L3BhdGg+PC9zdmc+DQo_'
            self.svgbtnSetZero.ImageIndex = -1
            self.svgbtnSetZero.ImageStretch = False
            self.svgbtnSetZero.ReadOnly = False
            # Create control: svgbtnExhaust = TSSvgImageButton(self)
            self.svgbtnExhaust = TSSvgImageButton(self)
            self.svgbtnExhaust.Name = "svgbtnExhaust"
            self.svgbtnExhaust.Parent = self.pnlTop
            self.svgbtnExhaust.Left = 421
            self.svgbtnExhaust.Top = 0
            self.svgbtnExhaust.Width = 72
            self.svgbtnExhaust.Height = 40
            self.svgbtnExhaust.Cursor = crArrow
            self.svgbtnExhaust.Align = "alLeft"
            self.svgbtnExhaust.Caption = 'Exhaust'
            self.svgbtnExhaust.TabOrder = 6
            self.svgbtnExhaust.VerticalAlignment = "taAlignBottom"
            self.svgbtnExhaust.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_exhaust.svg'
            self.svgbtnExhaust.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjQ5NDEwNTA3NzgxIiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjU5NzYiIGRhdGEtZGFya3JlYWRlci1pbmxpbmUtZmlsbD0iIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgd2lkdGg9IjIwMCIgaGVpZ2h0PSIyMDAiPjxkZWZzPjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+QGZvbnQtZmFjZSB7IGZvbnQtZmFtaWx5OiBmZWVkYmFjay1pY29uZm9udDsgc3JjOiB1cmwoIi8vYXQuYWxpY2RuLmNvbS90L2ZvbnRfMTAzMTE1OF91Njl3OHloeGR1LndvZmYyP3Q9MTYzMDAzMzc1OTk0NCIpIGZvcm1hdCgid29mZjIiKSwgdXJsKCIvL2F0LmFsaWNkbi5jb20vdC9mb250XzEwMzExNThfdTY5dzh5aHhkdS53b2ZmP3Q9MTYzMDAzMzc1OTk0NCIpIGZvcm1hdCgid29mZiIpLCB1cmwoIi8vYXQuYWxpY2RuLmNvbS90L2ZvbnRfMTAzMTE1OF91Njl3OHloeGR1LnR0Zj90PTE2MzAwMzM3NTk5NDQiKSBmb3JtYXQoInRydWV0eXBlIik7IH0NCjwvc3R5bGU+PC9kZWZzPjxwYXRoIGQ9Ik0xNjAgMjg4SDEyOFY5NmgzMnYzMmgzMmExMjggMTI4IDAgMCAxIDEyOCAxMjh2MzUySDE5MlYyODhjMC0zMiAwLTMyLTMyLTMydjMyeiBtNTEyIDYwOGg2NHYzMmgtNjR2LTMyeiBtOTYgMGg2NHYzMmgtNjR2LTMyeiBtOTYgMGg2NHYzMmgtNjR2LTMyeiBtMC02NGgzMnYzMmgtMTkydi0zMmgzMnYtMjg4aDEyOHYyODh6TTQxNiA0MTZoMTI4djI3MmExNzYgMTc2IDAgMCAxLTM1MiAwdi00OC41MTJoMTMxLjcxMnY1MC4zNjhhNDYuMTQ0IDQ2LjE0NCAwIDAgMCA5Mi4yODggMFY0MTZ6IG0zMiAyNzMuODU2YTc4LjE0NCA3OC4xNDQgMCAxIDEtMTU2LjI4OCAwdi0xOC4zNjhIMjI0djE2LjUxMmExNDQgMTQ0IDAgMSAwIDI4OCAwVjQ0OGgtNjR2MjQxLjg1NnpNNzM2IDM4NHYtMzJjMC0zMiAwLTMyLTMyLTMyaC0xMjhjLTMyIDAtMzIgMC0zMiAzMnYzMmgtMTI4di02NGExMjggMTI4IDAgMCAxIDEyOC0xMjhoMTkyYTEyOCAxMjggMCAwIDEgMTI4IDEyOHY2NGgtMTI4eiBtOTYtMzJ2LTMyYTk2IDk2IDAgMCAwLTk2LTk2aC0xOTJhOTYgOTYgMCAwIDAtOTYgOTZ2MzJoNjRjMC00OS42NjQgMTQuMzM2LTY0IDY0LTY0aDEyOGM0OS42NjQgMCA2NCAxNC4zMzYgNjQgNjRoNjR6IG0tMTI4IDY0aDE5MnY5NmgtMTkydi05NnogbTMyIDMydjMyaDEyOHYtMzJoLTEyOHogbTMyIDEyOHYyNTZoNjR2LTI1NmgtNjR6TTI4OCAyNTZhOTYgOTYgMCAwIDAtOTYtOTZIMTYwdjY0aDMyYTMyIDMyIDAgMCAxIDMyIDMydjMyMGg2NFYyNTZ6IiBwLWlkPSI1OTc3IiBmaWxsPSIjMTI5NmRiIiBkYXRhLWRhcmtyZWFkZXItaW5saW5lLWZpbGw9IiIgc3R5bGU9Ii0tZGFya3JlYWRlci1pbmxpbmUtZmlsbDojMGU3OGFmOyI+PC9wYXRoPjwvc3ZnPg0K'
            self.svgbtnExhaust.ImageIndex = -1
            self.svgbtnExhaust.ImageStretch = False
            self.svgbtnExhaust.ReadOnly = False
            # Create control: Panel23 = Panel(self)
            self.Panel23 = Panel(self)
            self.Panel23.Name = "Panel23"
            self.Panel23.Parent = self.pnlTop
            self.Panel23.Left = 565
            self.Panel23.Top = 0
            self.Panel23.Width = 227
            self.Panel23.Height = 40
            self.Panel23.Cursor = crArrow
            self.Panel23.Align = "alLeft"
            self.Panel23.BevelEdges = []
            self.Panel23.BevelKind = "bkFlat"
            self.Panel23.BevelOuter = "bvNone"
            self.Panel23.Caption = 'pnlCenter'
            self.Panel23.ShowCaption = "False"
            self.Panel23.TabOrder = 7
            # Create control: svgShowConnected = TSSvgImageButton(self)
            self.svgShowConnected = TSSvgImageButton(self)
            self.svgShowConnected.Name = "svgShowConnected"
            self.svgShowConnected.Parent = self.pnlTop
            self.svgShowConnected.Left = 792
            self.svgShowConnected.Top = 0
            self.svgShowConnected.Width = 72
            self.svgShowConnected.Height = 40
            self.svgShowConnected.Cursor = crArrow
            self.svgShowConnected.Align = "alLeft"
            self.svgShowConnected.Caption = 'Connected'
            self.svgShowConnected.TabOrder = 8
            self.svgShowConnected.VerticalAlignment = "taAlignBottom"
            self.svgShowConnected.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_connected.svg'
            self.svgShowConnected.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMxMDg3NjAwNzM0IiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjExOTMxNiIgZGF0YS1zcG0tYW5jaG9yLWlkPSJhMzEzeC43NzgxMDY5LjAuaTUxIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgd2lkdGg9IjEyOCIgaGVpZ2h0PSIxMjgiPjxkZWZzPjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+PC9zdHlsZT48L2RlZnM+PHBhdGggZD0iTTUxMi4wMDM0MTMgMTAyMC41ODY2NjdjLTEzNi4zMjE3MDcgMC0yNjQuMTcxNTItNTIuNzczNTQ3LTM1OS45OTQwMjYtMTQ4LjU5MjY0QzU2LjE4MzQ2NyA3NzYuMTcxNTIgMy40MTMzMzMgNjQ4LjMyMTcwNyAzLjQxMzMzMyA1MTIuMDAzNDEzYzAtMTM2LjMyMTcwNyA1Mi43NzAxMzMtMjY0LjE3MTUyIDE0OC41OTYwNTQtMzU5Ljk5NDAyNkMyNDcuODMxODkzIDU2LjE4MzQ2NyAzNzUuNjgxNzA3IDMuNDEzMzMzIDUxMi4wMDM0MTMgMy40MTMzMzNzMjY0LjE2ODEwNyA1Mi43NzAxMzMgMzU5Ljk5MDYxNCAxNDguNTk2MDU0Qzk2Ny44MTMxMiAyNDcuODMxODkzIDEwMjAuNTg2NjY3IDM3NS42ODE3MDcgMTAyMC41ODY2NjcgNTEyLjAwMzQxM3MtNTIuNzczNTQ3IDI2NC4xNjgxMDctMTQ4LjU5MjY0IDM1OS45OTA2MTRDNzc2LjE3MTUyIDk2Ny44MTMxMiA2NDguMzIxNzA3IDEwMjAuNTg2NjY3IDUxMi4wMDM0MTMgMTAyMC41ODY2Njd6IG0tNjAuNTQ5MTItNjAxLjEzNTc4N2MtOC4zNTI0MjcgMC0xNi4zMzI4IDMuMzg2MDI3LTIyLjQ3NjggOS41MjY2MTMtNTMuNjIzNDY3IDU1Ljk1NDc3My01My41NTE3ODcgMTQ0LjkyMzMwNyAwLjAwMzQxNCAxOTguNDgxOTJsMTQwLjU1NDI0IDE0MC41NTA4MjdjMjcuMTk3NDQgMjYuMDcxMDQgNjIuNjcyMjEzIDQwLjM0MjE4NyAxMDAuMDUxNjI2IDQwLjM0MjE4NyAzNy40NTc5MiAwIDcyLjQxMzg2Ny0xNC4zMjU3NiA5OC40MjY4OC00MC4zNDIxODcgNTMuNjI2ODgtNTUuOTUxMzYgNTMuNTU1Mi0xNDQuOTE5ODkzIDAtMTk4LjQ3NTA5M2wtODAuMDA1MTItODAuMDA4NTM0Yy02LjE0NzQxMy02LjE0MDU4Ny0xNC4xMjc3ODctOS41MzAwMjctMjIuNDc2OC05LjUzMDAyNi04LjM0NTYgMC0xNi4zMjkzODcgMy4zODYwMjctMjIuNDczMzg2IDkuNTMwMDI2LTYuMTQ3NDEzIDYuMTQwNTg3LTkuNTMwMDI3IDE0LjEyNDM3My05LjUzMDAyNyAyMi40NzMzODcgMCA4LjM0OTAxMyAzLjM4MjYxMyAxNi4zMzI4IDkuNTMwMDI3IDIyLjQ3NjhsODAuMDA1MTIgODAuMDAxNzA3YzE0Ljc2OTQ5MyAxNC43NzI5MDcgMjIuOTA2ODggMzQuMDU4MjQgMjIuOTA2ODggNTQuMjg5MDY2IDAgMjAuMjQxMDY3LTguMTM3Mzg3IDM5LjUxNjE2LTIyLjkwNjg4IDU0LjI4OTA2Ny0xNC43NzYzMiAxNC43NzI5MDctMzQuMDU0ODI3IDIyLjkxMDI5My01NC4yODkwNjcgMjIuOTEwMjkzLTIwLjIzNDI0IDAtMzkuNTEyNzQ3LTguMTM3Mzg3LTU0LjI4NTY1My0yMi45MTAyOTNsLTE0MC41NTA4MjctMTQwLjU1NDI0Yy0xNC43NzYzMi0xNC43NzI5MDctMjIuOTEwMjkzLTM0LjA1MTQxMy0yMi45MTAyOTMtNTQuMjg1NjUzIDAtMjAuMjM0MjQgOC4xMzM5NzMtMzkuNTE2MTYgMjIuOTEwMjkzLTU0LjI4NTY1NCAxMi41OTg2MTMtMTIuNjEyMjY3IDEyLjU5ODYxMy0zMi4zNTQ5ODcgMC00NC45NTcwMTMtNi4xNTA4MjctNi4xMzcxNzMtMTQuMTMxMi05LjUyMzItMjIuNDgzNjI3LTkuNTIzMnpNMzMzLjYwNTU0NyAyNTYuNDA5NmMyMC4yMzQyNCAwIDM5LjUxOTU3MyA4LjEzMzk3MyA1NC4yOTI0OCAyMi45MDY4OGwxNDAuNTU0MjQgMTQwLjU1NDI0YzMwLjQ0MDEwNyAzMC40NDAxMDcgMzAuNDQwMTA3IDc4LjEzNDYxMyAwIDEwOC41ODE1NDctNi4xNDQgNi4xNDA1ODctOS41MzAwMjcgMTQuMTIwOTYtOS41MzAwMjcgMjIuNDc2OCAwIDguMzQ1NiAzLjM4NjAyNyAxNi4zMzI4IDkuNTMzNDQgMjIuNDczMzg2IDYuMTM3MTczIDYuMTQwNTg3IDE0LjEyMDk2IDkuNTI2NjEzIDIyLjQ2OTk3MyA5LjUyNjYxNCA4LjM0NTYgMCAxNi4zMzI4LTMuMzgyNjEzIDIyLjQ3MzM4Ny05LjUzMDAyNyA1My42MzAyOTMtNTUuOTUxMzYgNTMuNTU4NjEzLTE0NC45MTk4OTMgMC0xOTguNDc1MDkzTDQzMi44NDQ4IDIzNC4zNjYyOTNjLTI3LjE5NzQ0LTI2LjA3MTA0LTYyLjY3MjIxMy00MC4zNDIxODctMTAwLjA0ODIxMy00MC4zNDIxODYtMzcuNDU3OTIgMC03Mi40MTM4NjcgMTQuMzI1NzYtOTguNDI2ODggNDAuMzQyMTg2LTUzLjYyNjg4IDU1Ljk1MTM2LTUzLjU1ODYxMyAxNDQuOTE5ODkzIDAgMTk4LjQ3ODUwN2w4MC4wMDg1MzMgODAuMDA4NTMzYzYuMTQwNTg3IDYuMTQ0IDE0LjEyMDk2IDkuNTMwMDI3IDIyLjQ3MzM4NyA5LjUzMDAyN3MxNi4zMzYyMTMtMy4zODYwMjcgMjIuNDc2OC05LjUzMDAyN2MxMi41OTg2MTMtMTIuNjA1NDQgMTIuNTk4NjEzLTMyLjM1MTU3MyAwLTQ0Ljk1MDE4NmwtODAuMDExOTQ3LTgwLjAwODUzNGMtMjguNDMzMDY3LTMwLjMzNDI5My0yOC40MzMwNjctNzguMjQwNDI3IDAuMjMyMTA3LTEwOC44MTcwNjYgMTQuNTQwOC0xNC41MzM5NzMgMzMuODE5MzA3LTIyLjY2Nzk0NyA1NC4wNTY5Ni0yMi42Njc5NDd6IiBmaWxsPSIjMWFmYTI5IiBwLWlkPSIxMTkzMTciIGRhdGEtc3BtLWFuY2hvci1pZD0iYTMxM3guNzc4MTA2OS4wLmk1MCIgY2xhc3M9InNlbGVjdGVkIj48L3BhdGg+PC9zdmc+DQo_'
            self.svgShowConnected.ImageIndex = -1
            self.svgShowConnected.ImageStretch = False
            self.svgShowConnected.ReadOnly = True
            # Create control: svgShowPower = TSSvgImageButton(self)
            self.svgShowPower = TSSvgImageButton(self)
            self.svgShowPower.Name = "svgShowPower"
            self.svgShowPower.Parent = self.pnlTop
            self.svgShowPower.Left = 864
            self.svgShowPower.Top = 0
            self.svgShowPower.Width = 72
            self.svgShowPower.Height = 40
            self.svgShowPower.Cursor = crArrow
            self.svgShowPower.Align = "alLeft"
            self.svgShowPower.Caption = 'Power'
            self.svgShowPower.TabOrder = 9
            self.svgShowPower.VerticalAlignment = "taAlignBottom"
            self.svgShowPower.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_power_on.svg'
            self.svgShowPower.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMxMTcyNTU2NDMwIiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjIzODgwIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgd2lkdGg9IjEyOCIgaGVpZ2h0PSIxMjgiPjxkZWZzPjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+PC9zdHlsZT48L2RlZnM+PHBhdGggZD0iTTYyOS43NiAyMDkuOTJjMjMuMDQgMCAzOS42OC0xNy45MiAzOS42OC00MC45NlY4Ny4wNGMwLTIzLjA0LTE2LjY0LTQwLjk2LTM5LjY4LTQwLjk2UzU5MC4wOCA2NCA1OTAuMDggODcuMDR2ODEuOTJjMCAyMC40OCAxNi42NCA0MC45NiAzOS42OCA0MC45NnpNMzkxLjY4IDgxNy45MmgzOS42OHYxNjMuODRoMTU4LjcyVjgxNy45MmgzOS42OHYtNDAuOTZIMzk0LjI0djQwLjk2aC0yLjU2eiBtMC02MDhjMjMuMDQgMCAzOS42OC0xNy45MiAzOS42OC00MC45NlY4Ny4wNGMwLTIzLjA0LTE2LjY0LTQwLjk2LTM5LjY4LTQwLjk2UzM1MiA2NCAzNTIgODcuMDR2ODEuOTJjMCAyMC40OCAxOS4yIDQwLjk2IDM5LjY4IDQwLjk2eiBtLTExNi40OCA0MC45NnYzNjYuMDhjMCA2Ny44NCA1My43NiAxMjIuODggMTE5LjA0IDEyMi44OGgyMzUuNTJjNjUuMjggMCAxMTkuMDQtNTUuMDQgMTE5LjA0LTEyMi44OFYyNTAuODhoLTQ3My42eiBtMTk1Ljg0IDQwNS43NlY0OTIuOGgtNzkuMzZMNTUwLjQgMzI4Ljk2djE2My44NGg3OS4zNkw0NzEuMDQgNjU2LjY0eiIgZmlsbD0iIzFhZmEyOSIgcC1pZD0iMjM4ODEiPjwvcGF0aD48L3N2Zz4NCg__'
            self.svgShowPower.ImageIndex = -1
            self.svgShowPower.ImageStretch = False
            self.svgShowPower.ReadOnly = True
            # Create control: svgShowServoOn = TSSvgImageButton(self)
            self.svgShowServoOn = TSSvgImageButton(self)
            self.svgShowServoOn.Name = "svgShowServoOn"
            self.svgShowServoOn.Parent = self.pnlTop
            self.svgShowServoOn.Left = 936
            self.svgShowServoOn.Top = 0
            self.svgShowServoOn.Width = 72
            self.svgShowServoOn.Height = 40
            self.svgShowServoOn.Cursor = crArrow
            self.svgShowServoOn.Align = "alLeft"
            self.svgShowServoOn.Caption = 'Servo On'
            self.svgShowServoOn.TabOrder = 10
            self.svgShowServoOn.VerticalAlignment = "taAlignBottom"
            self.svgShowServoOn.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_servo_on.svg'
            self.svgShowServoOn.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMxMTYwNDYwMzQzIiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjE0NDkxIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgd2lkdGg9IjEyOCIgaGVpZ2h0PSIxMjgiPjxkZWZzPjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+PC9zdHlsZT48L2RlZnM+PHBhdGggZD0iTTAgNTA0LjE5MmE1MDQuMTkyIDUwMy4yOTYgOTAgMSAwIDEwMDYuNTkyIDAgNTA0LjE5MiA1MDMuMjk2IDkwIDEgMC0xMDA2LjU5MiAwWiIgZmlsbD0iIzFhZmEyOSIgcC1pZD0iMTQ0OTIiIGRhdGEtc3BtLWFuY2hvci1pZD0iYTMxM3guNzc4MTA2OS4wLmkyOCIgY2xhc3M9InNlbGVjdGVkIj48L3BhdGg+PHBhdGggZD0iTTY3MiAxOTJhNjQgNjQgMCAwIDEgNjQgNjR2NDE2YTY0IDY0IDAgMCAxLTY0IDY0aC0zMjBhNjQgNjQgMCAwIDEtNjQtNjRWMjU2YTY0IDY0IDAgMCAxIDY0LTY0ek01NzQuMzM2IDMzMi44aC05MC4yNGMtMy44NCAwLTcuNDI0IDEuOTItOS4xNTIgNS4xMmwtNTcuODU2IDEwNC41NzZjLTAuNTEyIDAuOTYgMC4yNTYgMi4xMTIgMS40MDggMi4xMTJoNTAuMTEyYzIuNDk2IDAgNC4zNTIgMi4xMTIgMy44NCA0LjM1MmwtMzEuMzYgMTQ1LjI4IDE2Ny4yOTYtMTkzLjA4OGMxLjI4LTEuNTM2IDAuMTI4LTMuNzc2LTEuOTItMy43NzZoLTYzLjM2Yy0yLjQzMiAwLTMuOTY4LTIuNDMyLTIuNzUyLTQuNDhsMzUuODQtNTcuMDg4YzAuODk2LTEuMjgtMC4xOTItMy4wMDgtMS45Mi0zLjAwOHpNMjU2IDc2OGg1MTJhMzIgMzIgMCAwIDEgMCA2NEgyNTZhMzIgMzIgMCAwIDEgMC02NHogbTU0NC00NDhhMzIgMzIgMCAwIDEgMzIgMzJWNTc2YTMyIDMyIDAgMCAxLTY0IDBWMzUyYTMyIDMyIDAgMCAxIDMyLTMyeiBtLTU3NiAwYTMyIDMyIDAgMCAxIDMyIDMyVjU3NmEzMiAzMiAwIDEgMS02NCAwVjM1MmEzMiAzMiAwIDAgMSAzMi0zMnoiIGZpbGw9IiMwNjM4NTgiIHAtaWQ9IjE0NDkzIj48L3BhdGg+PC9zdmc+DQo_'
            self.svgShowServoOn.ImageIndex = -1
            self.svgShowServoOn.ImageStretch = False
            self.svgShowServoOn.ReadOnly = True
            # Create control: svgShowFault = TSSvgImageButton(self)
            self.svgShowFault = TSSvgImageButton(self)
            self.svgShowFault.Name = "svgShowFault"
            self.svgShowFault.Parent = self.pnlTop
            self.svgShowFault.Left = 1008
            self.svgShowFault.Top = 0
            self.svgShowFault.Width = 72
            self.svgShowFault.Height = 40
            self.svgShowFault.Cursor = crArrow
            self.svgShowFault.Align = "alLeft"
            self.svgShowFault.Caption = 'Fault'
            self.svgShowFault.TabOrder = 11
            self.svgShowFault.VerticalAlignment = "taAlignBottom"
            self.svgShowFault.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_fault.svg'
            self.svgShowFault.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjMxMDg1ODU3MTY1IiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjM3NzkxIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgd2lkdGg9IjEyOCIgaGVpZ2h0PSIxMjgiPjxkZWZzPjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+PC9zdHlsZT48L2RlZnM+PHBhdGggZD0iTTg1LjMzMyA5NjUuOTczaDg1My4zMzRjMzAuNzIgMCA1OC4wMjYtMTcuMDY2IDcxLjY4LTQwLjk2IDEzLjY1My0yNy4zMDYgMTMuNjUzLTU4LjAyNiAwLTg1LjMzM0w1ODMuNjggOTguOTg3Yy0xMy42NTMtMjcuMzA3LTQ0LjM3My00MC45Ni03MS42OC00MC45NnMtNTguMDI3IDE3LjA2Ni03MS42OCA0MC45NkwxMy42NTMgODM5LjY4QzMuNDEzIDg1My4zMzMgMCA4NjYuOTg3IDAgODgwLjY0djMuNDEzYzAgMTMuNjU0IDMuNDEzIDI3LjMwNyAxMC4yNCA0MC45NiAxNy4wNjcgMjcuMzA3IDQ0LjM3MyA0MC45NiA3NS4wOTMgNDAuOTZ6IG0zODkuMTItNjE3LjgxM2MwLTIwLjQ4IDE3LjA2Ny00MC45NiAzNy41NDctNDAuOTZzMzcuNTQ3IDE3LjA2NyAzNy41NDcgMzcuNTQ3djMwMy43ODZjMCAyMC40OC0xNy4wNjcgMzcuNTQ3LTM3LjU0NyAzNy41NDdzLTM3LjU0Ny0xNy4wNjctMzcuNTQ3LTM3LjU0N1YzNDguMTZ6IG0xMy42NTQgMzk1Ljk0N2MxMy42NTMtNi44MjcgMzQuMTMzLTYuODI3IDQ3Ljc4NiAwIDEzLjY1NCA2LjgyNiAyMy44OTQgMjMuODkzIDIzLjg5NCA0MC45NnMtMTAuMjQgMzAuNzItMjMuODk0IDQwLjk2Yy0xMy42NTMgNi44MjYtMzQuMTMzIDYuODI2LTQ3Ljc4NiAwLTEzLjY1NC02LjgyNy0yMy44OTQtMjMuODk0LTIzLjg5NC00MC45NnMxMC4yNC0zMC43MiAyMy44OTQtNDAuOTZ6IiBmaWxsPSIjZDgxZTA2IiBwLWlkPSIzNzc5MiI+PC9wYXRoPjwvc3ZnPg0K'
            self.svgShowFault.ImageIndex = -1
            self.svgShowFault.ImageStretch = False
            self.svgShowFault.ReadOnly = False
            # Create control: svgbtnCalibrate = TSSvgImageButton(self)
            self.svgbtnCalibrate = TSSvgImageButton(self)
            self.svgbtnCalibrate.Name = "svgbtnCalibrate"
            self.svgbtnCalibrate.Parent = self.pnlTop
            self.svgbtnCalibrate.Left = 493
            self.svgbtnCalibrate.Top = 0
            self.svgbtnCalibrate.Width = 72
            self.svgbtnCalibrate.Height = 40
            self.svgbtnCalibrate.Cursor = crArrow
            self.svgbtnCalibrate.Align = "alLeft"
            self.svgbtnCalibrate.Caption = 'Calibrate'
            self.svgbtnCalibrate.TabOrder = 12
            self.svgbtnCalibrate.VerticalAlignment = "taAlignBottom"
            self.svgbtnCalibrate.SvgFileName = 'D:/Projects/TigerTe/Projects/2023-12_TigerTE_Hardware/res/tio_servo_exhaust.svg'
            self.svgbtnCalibrate.SvgFileContent = 'PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNjQ5NDEwNTA3NzgxIiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjU5NzYiIGRhdGEtZGFya3JlYWRlci1pbmxpbmUtZmlsbD0iIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgd2lkdGg9IjIwMCIgaGVpZ2h0PSIyMDAiPjxkZWZzPjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+QGZvbnQtZmFjZSB7IGZvbnQtZmFtaWx5OiBmZWVkYmFjay1pY29uZm9udDsgc3JjOiB1cmwoIi8vYXQuYWxpY2RuLmNvbS90L2ZvbnRfMTAzMTE1OF91Njl3OHloeGR1LndvZmYyP3Q9MTYzMDAzMzc1OTk0NCIpIGZvcm1hdCgid29mZjIiKSwgdXJsKCIvL2F0LmFsaWNkbi5jb20vdC9mb250XzEwMzExNThfdTY5dzh5aHhkdS53b2ZmP3Q9MTYzMDAzMzc1OTk0NCIpIGZvcm1hdCgid29mZiIpLCB1cmwoIi8vYXQuYWxpY2RuLmNvbS90L2ZvbnRfMTAzMTE1OF91Njl3OHloeGR1LnR0Zj90PTE2MzAwMzM3NTk5NDQiKSBmb3JtYXQoInRydWV0eXBlIik7IH0NCjwvc3R5bGU+PC9kZWZzPjxwYXRoIGQ9Ik0xNjAgMjg4SDEyOFY5NmgzMnYzMmgzMmExMjggMTI4IDAgMCAxIDEyOCAxMjh2MzUySDE5MlYyODhjMC0zMiAwLTMyLTMyLTMydjMyeiBtNTEyIDYwOGg2NHYzMmgtNjR2LTMyeiBtOTYgMGg2NHYzMmgtNjR2LTMyeiBtOTYgMGg2NHYzMmgtNjR2LTMyeiBtMC02NGgzMnYzMmgtMTkydi0zMmgzMnYtMjg4aDEyOHYyODh6TTQxNiA0MTZoMTI4djI3MmExNzYgMTc2IDAgMCAxLTM1MiAwdi00OC41MTJoMTMxLjcxMnY1MC4zNjhhNDYuMTQ0IDQ2LjE0NCAwIDAgMCA5Mi4yODggMFY0MTZ6IG0zMiAyNzMuODU2YTc4LjE0NCA3OC4xNDQgMCAxIDEtMTU2LjI4OCAwdi0xOC4zNjhIMjI0djE2LjUxMmExNDQgMTQ0IDAgMSAwIDI4OCAwVjQ0OGgtNjR2MjQxLjg1NnpNNzM2IDM4NHYtMzJjMC0zMiAwLTMyLTMyLTMyaC0xMjhjLTMyIDAtMzIgMC0zMiAzMnYzMmgtMTI4di02NGExMjggMTI4IDAgMCAxIDEyOC0xMjhoMTkyYTEyOCAxMjggMCAwIDEgMTI4IDEyOHY2NGgtMTI4eiBtOTYtMzJ2LTMyYTk2IDk2IDAgMCAwLTk2LTk2aC0xOTJhOTYgOTYgMCAwIDAtOTYgOTZ2MzJoNjRjMC00OS42NjQgMTQuMzM2LTY0IDY0LTY0aDEyOGM0OS42NjQgMCA2NCAxNC4zMzYgNjQgNjRoNjR6IG0tMTI4IDY0aDE5MnY5NmgtMTkydi05NnogbTMyIDMydjMyaDEyOHYtMzJoLTEyOHogbTMyIDEyOHYyNTZoNjR2LTI1NmgtNjR6TTI4OCAyNTZhOTYgOTYgMCAwIDAtOTYtOTZIMTYwdjY0aDMyYTMyIDMyIDAgMCAxIDMyIDMydjMyMGg2NFYyNTZ6IiBwLWlkPSI1OTc3IiBmaWxsPSIjMTI5NmRiIiBkYXRhLWRhcmtyZWFkZXItaW5saW5lLWZpbGw9IiIgc3R5bGU9Ii0tZGFya3JlYWRlci1pbmxpbmUtZmlsbDojMGU3OGFmOyI+PC9wYXRoPjwvc3ZnPg0K'
            self.svgbtnCalibrate.ImageIndex = -1
            self.svgbtnCalibrate.ImageStretch = False
            self.svgbtnCalibrate.ReadOnly = False
            # Create control: pnlInfo = Panel(self)
            self.pnlInfo = Panel(self)
            self.pnlInfo.Name = "pnlInfo"
            self.pnlInfo.Parent = self.pnlGround
            self.pnlInfo.Left = 1
            self.pnlInfo.Top = 45
            self.pnlInfo.Width = 1301
            self.pnlInfo.Height = 91
            self.pnlInfo.Cursor = crArrow
            self.pnlInfo.Align = "alTop"
            self.pnlInfo.Caption = 'pnlInfo'
            self.pnlInfo.ShowCaption = "False"
            self.pnlInfo.TabOrder = 1
            # Create control: pnlErrorInfo = Panel(self)
            self.pnlErrorInfo = Panel(self)
            self.pnlErrorInfo.Name = "pnlErrorInfo"
            self.pnlErrorInfo.Parent = self.pnlInfo
            self.pnlErrorInfo.Left = 704
            self.pnlErrorInfo.Top = 1
            self.pnlErrorInfo.Width = 596
            self.pnlErrorInfo.Height = 89
            self.pnlErrorInfo.Cursor = crArrow
            self.pnlErrorInfo.Align = "alClient"
            self.pnlErrorInfo.BevelEdges = []
            self.pnlErrorInfo.BevelKind = "bkFlat"
            self.pnlErrorInfo.BevelOuter = "bvNone"
            self.pnlErrorInfo.Caption = 'pnlCenter'
            self.pnlErrorInfo.ShowCaption = "False"
            self.pnlErrorInfo.TabOrder = 0
            # Create control: edtShowErrorCode = LabeledEdit(self)
            self.edtShowErrorCode = LabeledEdit(self)
            self.edtShowErrorCode.Name = "edtShowErrorCode"
            self.edtShowErrorCode.Parent = self.pnlErrorInfo
            self.edtShowErrorCode.Left = 40
            self.edtShowErrorCode.Top = 32
            self.edtShowErrorCode.Width = 128
            self.edtShowErrorCode.Height = 23
            self.edtShowErrorCode.Cursor = crArrow
            self.edtShowErrorCode.EditLabel.Width = 56
            self.edtShowErrorCode.EditLabel.Height = 15
            self.edtShowErrorCode.EditLabel.Caption = 'Error Code'
            self.edtShowErrorCode.Enabled = False
            self.edtShowErrorCode.NumbersOnly = True
            self.edtShowErrorCode.ReadOnly = True
            self.edtShowErrorCode.TabOrder = 0
            self.edtShowErrorCode.Text = '0'
            # Create control: pnlMainInfo = Panel(self)
            self.pnlMainInfo = Panel(self)
            self.pnlMainInfo.Name = "pnlMainInfo"
            self.pnlMainInfo.Parent = self.pnlInfo
            self.pnlMainInfo.Left = 1
            self.pnlMainInfo.Top = 1
            self.pnlMainInfo.Width = 703
            self.pnlMainInfo.Height = 89
            self.pnlMainInfo.Cursor = crArrow
            self.pnlMainInfo.Align = "alLeft"
            self.pnlMainInfo.BevelEdges = []
            self.pnlMainInfo.BevelKind = "bkFlat"
            self.pnlMainInfo.BevelOuter = "bvNone"
            self.pnlMainInfo.Caption = 'pnlCenter'
            self.pnlMainInfo.ShowCaption = "False"
            self.pnlMainInfo.TabOrder = 1
            # Create control: edtShowPosition = LabeledEdit(self)
            self.edtShowPosition = LabeledEdit(self)
            self.edtShowPosition.Name = "edtShowPosition"
            self.edtShowPosition.Parent = self.pnlMainInfo
            self.edtShowPosition.Left = 19
            self.edtShowPosition.Top = 32
            self.edtShowPosition.Width = 136
            self.edtShowPosition.Height = 30
            self.edtShowPosition.Cursor = crArrow
            self.edtShowPosition.TabStop = False
            self.edtShowPosition.Alignment = "taRightJustify"
            self.edtShowPosition.Color = 4210752
            self.edtShowPosition.EditLabel.Width = 105
            self.edtShowPosition.EditLabel.Height = 15
            self.edtShowPosition.EditLabel.Caption = 'Pedal Position(mm)'
            self.edtShowPosition.Font.Charset = DEFAULT_CHARSET
            self.edtShowPosition.Font.Color = clLime
            self.edtShowPosition.Font.Height = -18
            self.edtShowPosition.Font.Name = 'Consolas'
            self.edtShowPosition.Font.Style = ["fsBold"]
            self.edtShowPosition.NumbersOnly = True
            self.edtShowPosition.ParentFont = False
            self.edtShowPosition.ReadOnly = True
            self.edtShowPosition.TabOrder = 0
            self.edtShowPosition.Text = '10.00'
            # Create control: edtShowSpeed = LabeledEdit(self)
            self.edtShowSpeed = LabeledEdit(self)
            self.edtShowSpeed.Name = "edtShowSpeed"
            self.edtShowSpeed.Parent = self.pnlMainInfo
            self.edtShowSpeed.Left = 200
            self.edtShowSpeed.Top = 32
            self.edtShowSpeed.Width = 136
            self.edtShowSpeed.Height = 30
            self.edtShowSpeed.Cursor = crArrow
            self.edtShowSpeed.TabStop = False
            self.edtShowSpeed.Alignment = "taRightJustify"
            self.edtShowSpeed.Color = 4210752
            self.edtShowSpeed.EditLabel.Width = 104
            self.edtShowSpeed.EditLabel.Height = 15
            self.edtShowSpeed.EditLabel.Caption = 'Pedal Speed(mm/s)'
            self.edtShowSpeed.Font.Charset = DEFAULT_CHARSET
            self.edtShowSpeed.Font.Color = clLime
            self.edtShowSpeed.Font.Height = -18
            self.edtShowSpeed.Font.Name = 'Consolas'
            self.edtShowSpeed.Font.Style = ["fsBold"]
            self.edtShowSpeed.NumbersOnly = True
            self.edtShowSpeed.ParentFont = False
            self.edtShowSpeed.ReadOnly = True
            self.edtShowSpeed.TabOrder = 1
            self.edtShowSpeed.Text = '10.00'
            # Create control: edtShowPressure = LabeledEdit(self)
            self.edtShowPressure = LabeledEdit(self)
            self.edtShowPressure.Name = "edtShowPressure"
            self.edtShowPressure.Parent = self.pnlMainInfo
            self.edtShowPressure.Left = 378
            self.edtShowPressure.Top = 32
            self.edtShowPressure.Width = 136
            self.edtShowPressure.Height = 30
            self.edtShowPressure.Cursor = crArrow
            self.edtShowPressure.TabStop = False
            self.edtShowPressure.Alignment = "taRightJustify"
            self.edtShowPressure.Color = 4210752
            self.edtShowPressure.EditLabel.Width = 91
            self.edtShowPressure.EditLabel.Height = 15
            self.edtShowPressure.EditLabel.Caption = 'MC Pressure(bar)'
            self.edtShowPressure.Font.Charset = DEFAULT_CHARSET
            self.edtShowPressure.Font.Color = clLime
            self.edtShowPressure.Font.Height = -18
            self.edtShowPressure.Font.Name = 'Consolas'
            self.edtShowPressure.Font.Style = ["fsBold"]
            self.edtShowPressure.NumbersOnly = True
            self.edtShowPressure.ParentFont = False
            self.edtShowPressure.ReadOnly = True
            self.edtShowPressure.TabOrder = 2
            self.edtShowPressure.Text = '10.00'
            # Create control: edtShowForce = LabeledEdit(self)
            self.edtShowForce = LabeledEdit(self)
            self.edtShowForce.Name = "edtShowForce"
            self.edtShowForce.Parent = self.pnlMainInfo
            self.edtShowForce.Left = 557
            self.edtShowForce.Top = 32
            self.edtShowForce.Width = 136
            self.edtShowForce.Height = 30
            self.edtShowForce.Cursor = crArrow
            self.edtShowForce.TabStop = False
            self.edtShowForce.Alignment = "taRightJustify"
            self.edtShowForce.Color = 4210752
            self.edtShowForce.EditLabel.Width = 103
            self.edtShowForce.EditLabel.Height = 15
            self.edtShowForce.EditLabel.Caption = 'Calibrated Force(N)'
            self.edtShowForce.Font.Charset = DEFAULT_CHARSET
            self.edtShowForce.Font.Color = clLime
            self.edtShowForce.Font.Height = -18
            self.edtShowForce.Font.Name = 'Consolas'
            self.edtShowForce.Font.Style = ["fsBold"]
            self.edtShowForce.NumbersOnly = True
            self.edtShowForce.ParentFont = False
            self.edtShowForce.ReadOnly = True
            self.edtShowForce.TabOrder = 3
            self.edtShowForce.Text = '10.00'
            # Create control: pnlCalibrate = Panel(self)
            self.pnlCalibrate = Panel(self)
            self.pnlCalibrate.Name = "pnlCalibrate"
            self.pnlCalibrate.Parent = self.pnlGround
            self.pnlCalibrate.Left = 1
            self.pnlCalibrate.Top = 374
            self.pnlCalibrate.Width = 1301
            self.pnlCalibrate.Height = 216
            self.pnlCalibrate.Cursor = crArrow
            self.pnlCalibrate.Align = "alTop"
            self.pnlCalibrate.BevelEdges = ["beBottom"]
            self.pnlCalibrate.BevelKind = "bkFlat"
            self.pnlCalibrate.BevelOuter = "bvNone"
            self.pnlCalibrate.Caption = 'pnlCalibrate'
            self.pnlCalibrate.ShowCaption = "False"
            self.pnlCalibrate.TabOrder = 2
            # Create control: Label1 = Label(self)
            self.Label1 = Label(self)
            self.Label1.Name = "Label1"
            self.Label1.Parent = self.pnlCalibrate
            self.Label1.Left = 67
            self.Label1.Top = 32
            self.Label1.Width = 134
            self.Label1.Height = 15
            self.Label1.Cursor = crArrow
            self.Label1.Caption = 'Table Position to Pressure'
            self.Label1.Layout = "tlCenter"
            # Create control: Label2 = Label(self)
            self.Label2 = Label(self)
            self.Label2.Name = "Label2"
            self.Label2.Parent = self.pnlCalibrate
            self.Label2.Left = 75
            self.Label2.Top = 128
            self.Label2.Width = 120
            self.Label2.Height = 15
            self.Label2.Cursor = crArrow
            self.Label2.Caption = 'Table Pressure to Force'
            self.Label2.Layout = "tlCenter"
            # Create control: Label5 = Label(self)
            self.Label5 = Label(self)
            self.Label5.Name = "Label5"
            self.Label5.Parent = self.pnlCalibrate
            self.Label5.Left = 11
            self.Label5.Top = 8
            self.Label5.Width = 133
            self.Label5.Height = 15
            self.Label5.Cursor = crArrow
            self.Label5.Caption = 'Pedal Calibration Control'
            self.Label5.Layout = "tlCenter"
            # Create control: btnExcuteCalibration = Button(self)
            self.btnExcuteCalibration = Button(self)
            self.btnExcuteCalibration.Name = "btnExcuteCalibration"
            self.btnExcuteCalibration.Parent = self.pnlCalibrate
            self.btnExcuteCalibration.Left = 900
            self.btnExcuteCalibration.Top = 24
            self.btnExcuteCalibration.Width = 192
            self.btnExcuteCalibration.Height = 32
            self.btnExcuteCalibration.Cursor = crArrow
            self.btnExcuteCalibration.Caption = 'Excute Position Calibration'
            self.btnExcuteCalibration.ImageIndex = 20
            self.btnExcuteCalibration.Images = app.get_system_imagelist_16px()
            self.btnExcuteCalibration.TabOrder = 0
            # Create control: StringGrid1 = StringGrid(self)
            self.StringGrid1 = StringGrid(self)
            self.StringGrid1.Name = "StringGrid1"
            self.StringGrid1.Parent = self.pnlCalibrate
            self.StringGrid1.Left = 67
            self.StringGrid1.Top = 56
            self.StringGrid1.Width = 1024
            self.StringGrid1.Height = 50
            self.StringGrid1.Cursor = crArrow
            self.StringGrid1.ColCount = 10
            self.StringGrid1.RowCount = 2
            self.StringGrid1.ScrollBars = "ssNone"
            self.StringGrid1.TabOrder = 1
            # Create control: btnApplyNewPosVSPressTable = Button(self)
            self.btnApplyNewPosVSPressTable = Button(self)
            self.btnApplyNewPosVSPressTable.Name = "btnApplyNewPosVSPressTable"
            self.btnApplyNewPosVSPressTable.Parent = self.pnlCalibrate
            self.btnApplyNewPosVSPressTable.Left = 634
            self.btnApplyNewPosVSPressTable.Top = 24
            self.btnApplyNewPosVSPressTable.Width = 179
            self.btnApplyNewPosVSPressTable.Height = 32
            self.btnApplyNewPosVSPressTable.Cursor = crArrow
            self.btnApplyNewPosVSPressTable.Caption = 'Apply New Value'
            self.btnApplyNewPosVSPressTable.ImageIndex = 20
            self.btnApplyNewPosVSPressTable.Images = app.get_system_imagelist_16px()
            self.btnApplyNewPosVSPressTable.TabOrder = 2
            # Create control: btnEnableForceCalibration = Button(self)
            self.btnEnableForceCalibration = Button(self)
            self.btnEnableForceCalibration.Name = "btnEnableForceCalibration"
            self.btnEnableForceCalibration.Parent = self.pnlCalibrate
            self.btnEnableForceCalibration.Left = 894
            self.btnEnableForceCalibration.Top = 120
            self.btnEnableForceCalibration.Width = 197
            self.btnEnableForceCalibration.Height = 32
            self.btnEnableForceCalibration.Cursor = crArrow
            self.btnEnableForceCalibration.Caption = 'Enable Force Calibration'
            self.btnEnableForceCalibration.ImageIndex = 20
            self.btnEnableForceCalibration.Images = app.get_system_imagelist_16px()
            self.btnEnableForceCalibration.TabOrder = 3
            # Create control: edtPositionVSPressureTableSize = LabeledEdit(self)
            self.edtPositionVSPressureTableSize = LabeledEdit(self)
            self.edtPositionVSPressureTableSize.Name = "edtPositionVSPressureTableSize"
            self.edtPositionVSPressureTableSize.Parent = self.pnlCalibrate
            self.edtPositionVSPressureTableSize.Left = 335
            self.edtPositionVSPressureTableSize.Top = 32
            self.edtPositionVSPressureTableSize.Width = 70
            self.edtPositionVSPressureTableSize.Height = 23
            self.edtPositionVSPressureTableSize.Cursor = crArrow
            self.edtPositionVSPressureTableSize.EditLabel.Width = 50
            self.edtPositionVSPressureTableSize.EditLabel.Height = 23
            self.edtPositionVSPressureTableSize.EditLabel.Caption = 'Table Size'
            self.edtPositionVSPressureTableSize.LabelPosition = "lpLeft"
            self.edtPositionVSPressureTableSize.NumbersOnly = True
            self.edtPositionVSPressureTableSize.TabOrder = 4
            self.edtPositionVSPressureTableSize.Text = '10'
            # Create control: edtPresVSForceTableSize = LabeledEdit(self)
            self.edtPresVSForceTableSize = LabeledEdit(self)
            self.edtPresVSForceTableSize.Name = "edtPresVSForceTableSize"
            self.edtPresVSForceTableSize.Parent = self.pnlCalibrate
            self.edtPresVSForceTableSize.Left = 335
            self.edtPresVSForceTableSize.Top = 128
            self.edtPresVSForceTableSize.Width = 70
            self.edtPresVSForceTableSize.Height = 23
            self.edtPresVSForceTableSize.Cursor = crArrow
            self.edtPresVSForceTableSize.EditLabel.Width = 50
            self.edtPresVSForceTableSize.EditLabel.Height = 23
            self.edtPresVSForceTableSize.EditLabel.Caption = 'Table Size'
            self.edtPresVSForceTableSize.LabelPosition = "lpLeft"
            self.edtPresVSForceTableSize.NumbersOnly = True
            self.edtPresVSForceTableSize.TabOrder = 5
            self.edtPresVSForceTableSize.Text = '10'
            # Create control: StringGrid4 = StringGrid(self)
            self.StringGrid4 = StringGrid(self)
            self.StringGrid4.Name = "StringGrid4"
            self.StringGrid4.Parent = self.pnlCalibrate
            self.StringGrid4.Left = 67
            self.StringGrid4.Top = 152
            self.StringGrid4.Width = 1024
            self.StringGrid4.Height = 51
            self.StringGrid4.Cursor = crArrow
            self.StringGrid4.ColCount = 10
            self.StringGrid4.RowCount = 2
            self.StringGrid4.ScrollBars = "ssNone"
            self.StringGrid4.TabOrder = 6
            # Create control: pnlMainControl = Panel(self)
            self.pnlMainControl = Panel(self)
            self.pnlMainControl.Name = "pnlMainControl"
            self.pnlMainControl.Parent = self.pnlGround
            self.pnlMainControl.Left = 1
            self.pnlMainControl.Top = 136
            self.pnlMainControl.Width = 1301
            self.pnlMainControl.Height = 120
            self.pnlMainControl.Cursor = crArrow
            self.pnlMainControl.Align = "alTop"
            self.pnlMainControl.BevelEdges = ["beBottom"]
            self.pnlMainControl.BevelKind = "bkFlat"
            self.pnlMainControl.BevelOuter = "bvNone"
            self.pnlMainControl.ShowCaption = "False"
            self.pnlMainControl.TabOrder = 3
            # Create control: pnlManualControl = Panel(self)
            self.pnlManualControl = Panel(self)
            self.pnlManualControl.Name = "pnlManualControl"
            self.pnlManualControl.Parent = self.pnlMainControl
            self.pnlManualControl.Left = 0
            self.pnlManualControl.Top = 0
            self.pnlManualControl.Width = 704
            self.pnlManualControl.Height = 118
            self.pnlManualControl.Cursor = crArrow
            self.pnlManualControl.Align = "alLeft"
            self.pnlManualControl.BevelEdges = []
            self.pnlManualControl.BevelKind = "bkFlat"
            self.pnlManualControl.BevelOuter = "bvNone"
            self.pnlManualControl.Caption = 'pnlCenter'
            self.pnlManualControl.ShowCaption = "False"
            self.pnlManualControl.TabOrder = 0
            # Create control: Label4 = Label(self)
            self.Label4 = Label(self)
            self.Label4.Name = "Label4"
            self.Label4.Parent = self.pnlManualControl
            self.Label4.Left = 11
            self.Label4.Top = 8
            self.Label4.Width = 115
            self.Label4.Height = 15
            self.Label4.Cursor = crArrow
            self.Label4.Caption = 'Pedal Manual Control'
            self.Label4.Layout = "tlCenter"
            # Create control: btnGotoTargetPosition = Button(self)
            self.btnGotoTargetPosition = Button(self)
            self.btnGotoTargetPosition.Name = "btnGotoTargetPosition"
            self.btnGotoTargetPosition.Parent = self.pnlManualControl
            self.btnGotoTargetPosition.Left = 378
            self.btnGotoTargetPosition.Top = 72
            self.btnGotoTargetPosition.Width = 141
            self.btnGotoTargetPosition.Height = 32
            self.btnGotoTargetPosition.Cursor = crArrow
            self.btnGotoTargetPosition.Caption = 'Goto Target Position'
            self.btnGotoTargetPosition.ImageIndex = 20
            self.btnGotoTargetPosition.Images = app.get_system_imagelist_16px()
            self.btnGotoTargetPosition.TabOrder = 0
            # Create control: btnGotoTargetForce = Button(self)
            self.btnGotoTargetForce = Button(self)
            self.btnGotoTargetForce.Name = "btnGotoTargetForce"
            self.btnGotoTargetForce.Parent = self.pnlManualControl
            self.btnGotoTargetForce.Left = 557
            self.btnGotoTargetForce.Top = 72
            self.btnGotoTargetForce.Width = 141
            self.btnGotoTargetForce.Height = 32
            self.btnGotoTargetForce.Cursor = crArrow
            self.btnGotoTargetForce.Caption = 'Goto Target Force'
            self.btnGotoTargetForce.ImageIndex = 20
            self.btnGotoTargetForce.Images = app.get_system_imagelist_16px()
            self.btnGotoTargetForce.TabOrder = 1
            # Create control: btnGoHome = Button(self)
            self.btnGoHome = Button(self)
            self.btnGoHome.Name = "btnGoHome"
            self.btnGoHome.Parent = self.pnlManualControl
            self.btnGoHome.Tag = 10485779
            self.btnGoHome.Left = 200
            self.btnGoHome.Top = 72
            self.btnGoHome.Width = 141
            self.btnGoHome.Height = 32
            self.btnGoHome.Cursor = crArrow
            self.btnGoHome.Caption = 'Go Home'
            self.btnGoHome.ImageIndex = 20
            self.btnGoHome.Images = app.get_system_imagelist_16px()
            self.btnGoHome.TabOrder = 2
            # Create control: edtTargetSpeed = LabeledEdit(self)
            self.edtTargetSpeed = LabeledEdit(self)
            self.edtTargetSpeed.Name = "edtTargetSpeed"
            self.edtTargetSpeed.Parent = self.pnlManualControl
            self.edtTargetSpeed.Tag = 7667731
            self.edtTargetSpeed.Left = 200
            self.edtTargetSpeed.Top = 30
            self.edtTargetSpeed.Width = 141
            self.edtTargetSpeed.Height = 23
            self.edtTargetSpeed.Cursor = crArrow
            self.edtTargetSpeed.Alignment = "taRightJustify"
            self.edtTargetSpeed.EditLabel.Width = 107
            self.edtTargetSpeed.EditLabel.Height = 15
            self.edtTargetSpeed.EditLabel.Caption = 'Target Speed(mm/s)'
            self.edtTargetSpeed.NumbersOnly = True
            self.edtTargetSpeed.TabOrder = 3
            self.edtTargetSpeed.Text = '5'
            # Create control: edtTargetPosition = LabeledEdit(self)
            self.edtTargetPosition = LabeledEdit(self)
            self.edtTargetPosition.Name = "edtTargetPosition"
            self.edtTargetPosition.Parent = self.pnlManualControl
            self.edtTargetPosition.Tag = 7143622
            self.edtTargetPosition.Left = 378
            self.edtTargetPosition.Top = 30
            self.edtTargetPosition.Width = 141
            self.edtTargetPosition.Height = 23
            self.edtTargetPosition.Cursor = crArrow
            self.edtTargetPosition.Alignment = "taRightJustify"
            self.edtTargetPosition.EditLabel.Width = 108
            self.edtTargetPosition.EditLabel.Height = 15
            self.edtTargetPosition.EditLabel.Caption = 'Target Position(mm)'
            self.edtTargetPosition.NumbersOnly = True
            self.edtTargetPosition.TabOrder = 4
            self.edtTargetPosition.Text = '0'
            # Create control: edtTargetForce = LabeledEdit(self)
            self.edtTargetForce = LabeledEdit(self)
            self.edtTargetForce.Name = "edtTargetForce"
            self.edtTargetForce.Parent = self.pnlManualControl
            self.edtTargetForce.Left = 557
            self.edtTargetForce.Top = 30
            self.edtTargetForce.Width = 141
            self.edtTargetForce.Height = 23
            self.edtTargetForce.Cursor = crArrow
            self.edtTargetForce.Alignment = "taRightJustify"
            self.edtTargetForce.EditLabel.Width = 81
            self.edtTargetForce.EditLabel.Height = 15
            self.edtTargetForce.EditLabel.Caption = 'Target Force(N)'
            self.edtTargetForce.NumbersOnly = True
            self.edtTargetForce.TabOrder = 5
            self.edtTargetForce.Text = '0'
            # Create control: pnlConfig = Panel(self)
            self.pnlConfig = Panel(self)
            self.pnlConfig.Name = "pnlConfig"
            self.pnlConfig.Parent = self.pnlMainControl
            self.pnlConfig.Left = 704
            self.pnlConfig.Top = 0
            self.pnlConfig.Width = 597
            self.pnlConfig.Height = 118
            self.pnlConfig.Cursor = crArrow
            self.pnlConfig.Align = "alClient"
            self.pnlConfig.BevelEdges = []
            self.pnlConfig.BevelKind = "bkFlat"
            self.pnlConfig.BevelOuter = "bvNone"
            self.pnlConfig.Caption = 'pnlConfig'
            self.pnlConfig.ShowCaption = "False"
            self.pnlConfig.TabOrder = 1
            # Create control: edtMinPosition = LabeledEdit(self)
            self.edtMinPosition = LabeledEdit(self)
            self.edtMinPosition.Name = "edtMinPosition"
            self.edtMinPosition.Parent = self.pnlConfig
            self.edtMinPosition.Left = 40
            self.edtMinPosition.Top = 30
            self.edtMinPosition.Width = 141
            self.edtMinPosition.Height = 23
            self.edtMinPosition.Cursor = crArrow
            self.edtMinPosition.Alignment = "taRightJustify"
            self.edtMinPosition.EditLabel.Width = 129
            self.edtMinPosition.EditLabel.Height = 15
            self.edtMinPosition.EditLabel.Caption = 'Pedal Min Position(mm)'
            self.edtMinPosition.NumbersOnly = True
            self.edtMinPosition.TabOrder = 0
            self.edtMinPosition.Text = '-10.00'
            # Create control: btnSetPedalRange = Button(self)
            self.btnSetPedalRange = Button(self)
            self.btnSetPedalRange.Name = "btnSetPedalRange"
            self.btnSetPedalRange.Parent = self.pnlConfig
            self.btnSetPedalRange.Left = 40
            self.btnSetPedalRange.Top = 72
            self.btnSetPedalRange.Width = 141
            self.btnSetPedalRange.Height = 32
            self.btnSetPedalRange.Cursor = crArrow
            self.btnSetPedalRange.Caption = 'Set Pedal Range'
            self.btnSetPedalRange.ImageIndex = 20
            self.btnSetPedalRange.Images = app.get_system_imagelist_16px()
            self.btnSetPedalRange.TabOrder = 1
            # Create control: edtMaxPosition = LabeledEdit(self)
            self.edtMaxPosition = LabeledEdit(self)
            self.edtMaxPosition.Name = "edtMaxPosition"
            self.edtMaxPosition.Parent = self.pnlConfig
            self.edtMaxPosition.Left = 243
            self.edtMaxPosition.Top = 30
            self.edtMaxPosition.Width = 141
            self.edtMaxPosition.Height = 23
            self.edtMaxPosition.Cursor = crArrow
            self.edtMaxPosition.Alignment = "taRightJustify"
            self.edtMaxPosition.EditLabel.Width = 131
            self.edtMaxPosition.EditLabel.Height = 15
            self.edtMaxPosition.EditLabel.Caption = 'Pedal Max Position(mm)'
            self.edtMaxPosition.NumbersOnly = True
            self.edtMaxPosition.TabOrder = 2
            self.edtMaxPosition.Text = '40.00'
            # Create control: edtMaxSpeed = LabeledEdit(self)
            self.edtMaxSpeed = LabeledEdit(self)
            self.edtMaxSpeed.Name = "edtMaxSpeed"
            self.edtMaxSpeed.Parent = self.pnlConfig
            self.edtMaxSpeed.Left = 243
            self.edtMaxSpeed.Top = 78
            self.edtMaxSpeed.Width = 141
            self.edtMaxSpeed.Height = 23
            self.edtMaxSpeed.Cursor = crArrow
            self.edtMaxSpeed.Alignment = "taRightJustify"
            self.edtMaxSpeed.EditLabel.Width = 130
            self.edtMaxSpeed.EditLabel.Height = 15
            self.edtMaxSpeed.EditLabel.Caption = 'Pedal Max Speed(mm/s)'
            self.edtMaxSpeed.NumbersOnly = True
            self.edtMaxSpeed.TabOrder = 3
            self.edtMaxSpeed.Text = '300'
            # Create control: pnlExhaust = Panel(self)
            self.pnlExhaust = Panel(self)
            self.pnlExhaust.Name = "pnlExhaust"
            self.pnlExhaust.Parent = self.pnlGround
            self.pnlExhaust.Left = 1
            self.pnlExhaust.Top = 256
            self.pnlExhaust.Width = 1301
            self.pnlExhaust.Height = 118
            self.pnlExhaust.Cursor = crArrow
            self.pnlExhaust.Align = "alTop"
            self.pnlExhaust.BevelEdges = ["beBottom"]
            self.pnlExhaust.BevelKind = "bkFlat"
            self.pnlExhaust.BevelOuter = "bvNone"
            self.pnlExhaust.Caption = 'Panel11'
            self.pnlExhaust.ShowCaption = "False"
            self.pnlExhaust.TabOrder = 4
            # Create control: Label3 = Label(self)
            self.Label3 = Label(self)
            self.Label3.Name = "Label3"
            self.Label3.Parent = self.pnlExhaust
            self.Label3.Left = 11
            self.Label3.Top = 8
            self.Label3.Width = 116
            self.Label3.Height = 15
            self.Label3.Cursor = crArrow
            self.Label3.Caption = 'Pedal Exhaust Control'
            self.Label3.Layout = "tlCenter"
            # Create control: edtExhaustPosition = LabeledEdit(self)
            self.edtExhaustPosition = LabeledEdit(self)
            self.edtExhaustPosition.Name = "edtExhaustPosition"
            self.edtExhaustPosition.Parent = self.pnlExhaust
            self.edtExhaustPosition.Left = 384
            self.edtExhaustPosition.Top = 68
            self.edtExhaustPosition.Width = 141
            self.edtExhaustPosition.Height = 23
            self.edtExhaustPosition.Cursor = crArrow
            self.edtExhaustPosition.Alignment = "taRightJustify"
            self.edtExhaustPosition.EditLabel.Width = 73
            self.edtExhaustPosition.EditLabel.Height = 15
            self.edtExhaustPosition.EditLabel.Caption = 'Position(mm)'
            self.edtExhaustPosition.NumbersOnly = True
            self.edtExhaustPosition.TabOrder = 0
            self.edtExhaustPosition.Text = '-10'
            # Create control: btnExhaust = Button(self)
            self.btnExhaust = Button(self)
            self.btnExhaust.Name = "btnExhaust"
            self.btnExhaust.Parent = self.pnlExhaust
            self.btnExhaust.Left = 200
            self.btnExhaust.Top = 60
            self.btnExhaust.Width = 141
            self.btnExhaust.Height = 32
            self.btnExhaust.Cursor = crArrow
            self.btnExhaust.Caption = 'Exhaust'
            self.btnExhaust.ImageIndex = 20
            self.btnExhaust.Images = app.get_system_imagelist_16px()
            self.btnExhaust.TabOrder = 1
            # Create control: edtExhaustSpeed = LabeledEdit(self)
            self.edtExhaustSpeed = LabeledEdit(self)
            self.edtExhaustSpeed.Name = "edtExhaustSpeed"
            self.edtExhaustSpeed.Parent = self.pnlExhaust
            self.edtExhaustSpeed.Left = 557
            self.edtExhaustSpeed.Top = 68
            self.edtExhaustSpeed.Width = 141
            self.edtExhaustSpeed.Height = 23
            self.edtExhaustSpeed.Cursor = crArrow
            self.edtExhaustSpeed.Alignment = "taRightJustify"
            self.edtExhaustSpeed.EditLabel.Width = 72
            self.edtExhaustSpeed.EditLabel.Height = 15
            self.edtExhaustSpeed.EditLabel.Caption = 'Speed(mm/s)'
            self.edtExhaustSpeed.NumbersOnly = True
            self.edtExhaustSpeed.TabOrder = 2
            self.edtExhaustSpeed.Text = '40'
            # Create control: edtExhaustCount = LabeledEdit(self)
            self.edtExhaustCount = LabeledEdit(self)
            self.edtExhaustCount.Name = "edtExhaustCount"
            self.edtExhaustCount.Parent = self.pnlExhaust
            self.edtExhaustCount.Left = 747
            self.edtExhaustCount.Top = 68
            self.edtExhaustCount.Width = 141
            self.edtExhaustCount.Height = 23
            self.edtExhaustCount.Cursor = crArrow
            self.edtExhaustCount.Alignment = "taRightJustify"
            self.edtExhaustCount.EditLabel.Width = 65
            self.edtExhaustCount.EditLabel.Height = 15
            self.edtExhaustCount.EditLabel.Caption = 'Cycle Count'
            self.edtExhaustCount.NumbersOnly = True
            self.edtExhaustCount.TabOrder = 3
            self.edtExhaustCount.Text = '40'
            # Create control: cbHoldExhaust = CheckBox(self)
            self.cbHoldExhaust = CheckBox(self)
            self.cbHoldExhaust.Name = "cbHoldExhaust"
            self.cbHoldExhaust.Parent = self.pnlExhaust
            self.cbHoldExhaust.Left = 200
            self.cbHoldExhaust.Top = 24
            self.cbHoldExhaust.Width = 152
            self.cbHoldExhaust.Height = 17
            self.cbHoldExhaust.Cursor = crArrow
            self.cbHoldExhaust.Caption = 'Pedal Hold after Exhaust'
            self.cbHoldExhaust.TabOrder = 4
        finally:
            # End UI auto creation
            self.EndUIAutoCreation()
# Auto Generated Python Code, do not modify END [UI] ----------------
        # your init code starts here...
        
        #region system button
        self.sysbtnConnect = self.RegisterToolbarButton('Connect', 194, False)
        self.sysbtnConnect.OnClick = self.OnConnectClick
        self.sysbtnDisconnect = self.RegisterToolbarButton('Disconnect', 195, False)
        self.sysbtnDisconnect.OnClick = self.OnDisconnectClick
        self.sysbtnUpdateConfigFile = self.RegisterToolbarButton('update config value', 55, True)
        self.sysbtnUpdateConfigFile.OnClick = self.OnUpdateConfigFileClick
        self.sysbtnImportConfigFile = self.RegisterToolbarButton('import config file from...', 57, True)
        self.sysbtnImportConfigFile.OnClick = self.OnImportConfigFileClick
        self.sysbtnExportConfigFile = self.RegisterToolbarButton('export config file to...', 50, False)
        self.sysbtnExportConfigFile.OnClick = self.OnExportConfigFileClick
        self.sysbtnSystemMsgs = self.RegisterToolbarButton('System Messages', 217, True)
        def OnMeasurementStart():
            self.OnConnectedCheck(True)
        def OnMeasurementStop():
            self.OnConnectedCheck(False)
        def OnSystemMsgsClick(sender):
            app.show_window_system_messages()
            # frm = app.show_window_system_messages()
            # frm.Left = self.Left + self.Width
            # frm.Top = self.Top
        self.sysbtnSystemMsgs.OnClick = OnSystemMsgsClick
        if(app.is_connected()):
            self.OnConnectedCheck(True)
        else:
            self.OnConnectedCheck(False)
        #endregion system button
        
        #region system events
        self.OnMeasurementStartedEvent = OnMeasurementStart
        self.OnMeasurementStoppedEvent = OnMeasurementStop
        # self.OnMeasurementStartedEvent = self.OnMeasurementStartStoped
        # self.OnMeasurementStoppedEvent = self.OnMeasurementStartStoped
        # self.OnMeasurementPreStopEvent = self.OnMeasurementPreStoped
        self.OnRefreshEvent = self.UIRefreshEvent
        # self.OnResize = self.OnFormResizeEvent
        
        #endregion system events
        
        #region initialize
        self.ProjectPath = app.get_configuration_file_path()
        self.FConfigFile = self.ProjectPath + r'\TIO\TIOConfiguration.ini'
        print(self.FConfigFile)
        self.svgbtnStart.Enabled = True
        self.svgbtnStop.Enabled = False
        self.svgbtnInit.Enabled = False
        self.svgbtnSetZero.Enabled = False
        self.svgbtnJogOut.Enabled = False
        self.svgbtnJogIn.Enabled = False
        self.svgbtnExhaust.Enabled = False
        self.svgbtnCalibrate.Enabled = False
        
        self.svgShowConnected.Enabled = False
        self.svgShowPower.Enabled = False
        self.svgShowServoOn.Enabled = False
        self.svgShowFault.Enabled = False
        
        
        self.UI_Servo_Stop()
        #endregion initialize
        
        #region button action
        def OnStartClick(sender):
            if 0 == tio.servo_create():
                if 0 == tio.servo_connect('192.168.1.1'):
                    if 0 == tio.pedal_servo_on(True) and 0 == tio.pedal_enable_run(True):
                        self.UI_Servo_Start()
                    else:
                        tio.servo_disconnect()
                        tio.servo_destroy()
                        self.UI_Servo_Stop()
                        app.make_toast('Error: Can not servo on, please check', lvlError)
                else:
                    tio.servo_destroy()
                    self.UI_Servo_Stop()
                    app.make_toast('Error: Can not connect with servo, please check', lvlError)
            else:
                self.UI_Servo_Stop()
                app.make_toast('Error: create servo failed', lvlError)
        self.svgbtnStart.OnClick = OnStartClick
        
        def OnStopClick(sender):
            tio.servo_disconnect()
            tio.servo_destroy()
            self.UI_Servo_Stop()
        self.svgbtnStop.OnClick = OnStopClick
        
        self.InInitializeState = False
        def OnInitializeClick(sender):
            if self.InInitializeState:
                self.UI_Servo_Start()
                self.InInitializeState = False
            else:
                self.UI_Servo_Initialize()
                self.InInitializeState = True
        self.svgbtnInit.OnClick = OnInitializeClick
        
        self.InExhasutState = False
        def OnExhaustClick(sender):
            if self.InExhasutState:
                self.UI_Servo_Start()
                self.InExhasutState = False
            else:
                self.UI_Servo_Exhaust()
                self.InExhasutState = True
        self.svgbtnExhaust.OnClick = OnExhaustClick
        
        self.InCalibrateState = False
        def OnCalibrateClick(sender):
            if self.InCalibrateState:
                self.UI_Servo_Start()
                self.InCalibrateState = False
            else:
                self.UI_Servo_Calibrate()
                self.InCalibrateState = True
        self.svgbtnCalibrate.OnClick = OnCalibrateClick
        
        # main control begin
        def OnGoHomeClick(sender):
            tio.pedal_go_home_asyn()
        self.btnGoHome.OnClick = OnGoHomeClick
        
        def OnGotoTargetForce(sender):
            # tio.pedal_goto_target_force(self.edtTargetForce.Value)
            AForce = float(self.edtTargetForce.Text)
            ASpeed = float(self.edtTargetSpeed.Text)
            if (ASpeed > 0 and ASpeed < 350) and (AForce >= 0 and AForce < 70000):
                tio.pedal_force_apply_asyn(AForce, ASpeed)
            else:
                app.make_toast('Error: Force or Speed out of range', lvlError)
        self.btnGotoTargetForce = OnGotoTargetForce
        
        def OnGotoTargetPosition(sender):
            # tio.pedal_goto_target_force(self.edtTargetForce.Value)
            APosition = float(self.edtTargetPosition.Text)
            ASpeed = float(self.edtTargetSpeed.Text)
            if (ASpeed > 0 and ASpeed < 350) and (APosition >= -10 and APosition < 40):
                tio.pedal_go_position_asyn(APosition, ASpeed)
            else:
                app.make_toast('Error: Position or Speed out of range', lvlError)
        self.btnGotoTargetPosition = OnGotoTargetPosition
        
        # config begin
        def OnSetZeroClick(sender):
            tio.pedal_set_home()
        self.svgbtnSetZero.OnClick = OnSetZeroClick
        
        def OnJogInClick(sender):
            tio.pedal_jog_in()
        self.svgbtnJogIn.OnClick = OnJogInClick
        
        def OnJogOutClick(sender):
            tio.pedal_jog_out()
        self.svgbtnJogOut.OnClick = OnJogOutClick
        
        def OnSetPedalRange(sender):
            AMinPosition = float(self.edtMinPosition.Text)
            AMaxPosition = float(self.edtMaxPosition.Text)
            ASpeed = float(self.edtMaxSpeed.Text)
            if (AMinPosition >= -10 and AMinPosition < 40) and (AMaxPosition >= -10 and AMaxPosition < 40) and (AMinPosition < AMaxPosition) and (ASpeed > 10 and ASpeed <= 350):
                tio.pedal_servo_limit(AMaxPosition, AMinPosition, ASpeed)
            else:
                app.make_toast('Error: Position or Speed out of range', lvlError)
        self.btnSetPedalRange.OnClick = OnSetPedalRange
        
        def OnExhaustClick(sender):
            AHoldEnable = self.cbHoldExhaust.Checked
            AExhaustPosition = float(self.edtExhaustPosition.Text)
            AExhaustSpeed = float(self.edtExhaustSpeed.Text)
            AExhaustCycle = float(self.edtExhaustCount.Text)
            if (AExhaustPosition > 0 and AExhaustPosition < 40) and (AExhaustSpeed > 10 and AExhaustSpeed <= 350) and (AExhaustCycle > 0 and AExhaustCycle <= 100):
                pass
        self.btnExhaust.OnClick = OnExhaustClick
        
        def OnExcuteCalibrateClick(sender):
            pass
        self.btnExcuteCalibration.OnClick = OnExcuteCalibrateClick
        
        #endregion button action
        
        
        #region using close License Dialog
        def OnActiveFormChange(sender):
            handle, clsName, caption = app.ui_get_active_form_info()
            app.log_text(clsName +',' + caption, lvlInfo)
            if clsName == 'TfrmToolboxLicense':
                WM_CLOSE = 16
                app.ui_post_message(handle, WM_CLOSE, 0, 0)
            if caption == 'LicenseDialog':
                WM_CLOSE = 16
                app.ui_post_message(handle, WM_CLOSE, 0, 0)            
        def OnFinalize():
            Screen.OnActiveFormChange = None    
        global vArmed
        if not vArmed:
            vArmed = True            
            Screen.OnActiveFormChange = OnActiveFormChange
            self.OnFinalizationEvent = OnFinalize
        #endregion  using close License Dialog
    #region UI Change Control
    def UI_Servo_Start(self):
        for AControl in self.pnlMainInfo.Controls:
                AControl.Enabled = True
        for AControl in self.pnlErrorInfo.Controls:
                AControl.Enabled = False
        for AControl in self.pnlManualControl.Controls:
                AControl.Enabled = True
        for AControl in self.pnlConfig.Controls:
                AControl.Enabled = False
        for AControl in self.pnlExhaust.Controls:
                AControl.Enabled = False
        for AControl in self.pnlCalibrate.Controls:
                AControl.Enabled = False
        
        self.svgbtnStart.Enabled = False
        self.svgbtnStop.Enabled = True
        self.svgbtnInit.Enabled = True
        self.svgbtnSetZero.Enabled = False
        self.svgbtnJogOut.Enabled = False
        self.svgbtnJogIn.Enabled = False
        self.svgbtnExhaust.Enabled = True
        self.svgbtnCalibrate.Enabled = True
        
                
    def UI_Servo_Stop(self):
        for AControl in self.pnlMainInfo.Controls:
                AControl.Enabled = False
        for AControl in self.pnlErrorInfo.Controls:
                AControl.Enabled = False
        for AControl in self.pnlManualControl.Controls:
                AControl.Enabled = False
        for AControl in self.pnlConfig.Controls:
                AControl.Enabled = False
        for AControl in self.pnlExhaust.Controls:
                AControl.Enabled = False
        for AControl in self.pnlCalibrate.Controls:
                AControl.Enabled = False
        
        self.svgbtnStart.Enabled = True
        self.svgbtnStop.Enabled = False
        self.svgbtnInit.Enabled = False
        self.svgbtnSetZero.Enabled = False
        self.svgbtnJogOut.Enabled = False
        self.svgbtnJogIn.Enabled = False
        self.svgbtnExhaust.Enabled = False
        self.svgbtnCalibrate.Enabled = False
                
    def UI_Servo_Initialize(self):
        for AControl in self.pnlMainInfo.Controls:
                AControl.Enabled = True
        for AControl in self.pnlErrorInfo.Controls:
                AControl.Enabled = False
        for AControl in self.pnlManualControl.Controls:
                AControl.Enabled = False
        for AControl in self.pnlConfig.Controls:
                AControl.Enabled = True
        for AControl in self.pnlExhaust.Controls:
                AControl.Enabled = False
        for AControl in self.pnlCalibrate.Controls:
                AControl.Enabled = False
        
        self.svgbtnStart.Enabled = False
        self.svgbtnStop.Enabled = True
        self.svgbtnInit.Enabled = True
        self.svgbtnSetZero.Enabled = True
        self.svgbtnJogOut.Enabled = True
        self.svgbtnJogIn.Enabled = True
        self.svgbtnExhaust.Enabled = False
        self.svgbtnCalibrate.Enabled = False
                
    def UI_Servo_Exhaust(self):
        for AControl in self.pnlMainInfo.Controls:
                AControl.Enabled = True
        for AControl in self.pnlErrorInfo.Controls:
                AControl.Enabled = False
        for AControl in self.pnlManualControl.Controls:
                AControl.Enabled = False
        for AControl in self.pnlConfig.Controls:
                AControl.Enabled = False
        for AControl in self.pnlExhaust.Controls:
                AControl.Enabled = True
        for AControl in self.pnlCalibrate.Controls:
                AControl.Enabled = False
        
        self.svgbtnStart.Enabled = False
        self.svgbtnStop.Enabled = True
        self.svgbtnInit.Enabled = False
        self.svgbtnSetZero.Enabled = False
        self.svgbtnJogOut.Enabled = False
        self.svgbtnJogIn.Enabled = False
        self.svgbtnExhaust.Enabled = True
        self.svgbtnCalibrate.Enabled = False
                
    def UI_Servo_Calibrate(self):
        for AControl in self.pnlMainInfo.Controls:
                AControl.Enabled = True
        for AControl in self.pnlErrorInfo.Controls:
                AControl.Enabled = False
        for AControl in self.pnlManualControl.Controls:
                AControl.Enabled = False
        for AControl in self.pnlConfig.Controls:
                AControl.Enabled = False
        for AControl in self.pnlExhaust.Controls:
                AControl.Enabled = False
        for AControl in self.pnlCalibrate.Controls:
                AControl.Enabled = True
        
        self.svgbtnStart.Enabled = False
        self.svgbtnStop.Enabled = True
        self.svgbtnInit.Enabled = False
        self.svgbtnSetZero.Enabled = False
        self.svgbtnJogOut.Enabled = False
        self.svgbtnJogIn.Enabled = False
        self.svgbtnExhaust.Enabled = False
        self.svgbtnCalibrate.Enabled = True
    
    #endregion UI Change Control
        
    #region system Event
    def OnConnectClick(self, Sender):
        debug_print(f'OnConnectClick {Sender}')
        if 0 == app.connect():          
            self.OnConnectedCheck(True)
            app.make_toast('Application Connected !', lvlOK)
    def OnDisconnectClick(self, Sender):
        debug_print(f'OnDisconnectClick {Sender}')
        if 0 == app.disconnect():         
            self.OnConnectedCheck(False)
            app.make_toast('Application Disconnected !', 3)
            
    def OnUpdateConfigFileClick(self, Sender):
        pass
    def OnImportConfigFileClick(self, Sender):
        pass
        # AFile = app.ui_show_open_file_dialog("Import Air Spring configuration parameters...", "configuration file", "*.ini", "")
        # if AFile == '':
        #     print('import configuration file canceled')
        #     return
        # if self.is_cofig_valid(AFile):
        #     if(0 == app.show_confirm_dialog("confirm import a new configuration file:", "if YES, then new file will be imported; if NO, import action will be canceled","", 0, False)):
        #         with open(AFile, 'r') as file:
        #             content = file.read()
        #         with open(self.FConfigFileFullName, 'w') as file:
        #             file.write(content)
        #         self.Load_Configfile()
        #         self.update_ui_show_after_load_config()
        #         app.make_toast('configuration file import finished', lvlOK)
        #     else:
        #         print('import configuration file canceled')
        # else:
        #     print('import file invalid, import failed')
        # app.open_directory_and_select_file(app.get_configuration_file_path() + 'conf\TestBench.ini')
    def OnExportConfigFileClick(self, Sender):
        pass
        # file_path = app.get_configuration_file_path() + 'conf\TestBench.ini'
        # file_name = 'TestBench_' + str(datetime.datetime.now().date())
        # save_path = app.ui_show_save_file_dialog("Export Air Spring configuration parameters...", "configuration file", "*.ini", file_name)
        # if save_path == '':
        #     print('export configuration file canceled')
        #     return
        # if not os.path.exists(self.FConfigFileFullName):
        #     app.make_toast('configuration file not exist', lvlError)
        #     return
        # with open(self.FConfigFileFullName, 'r') as file:
        #     content = file.read()
        # with open(save_path, 'w') as file:
        #     file.write(content)
        # app.make_toast('configuration file export finished', lvlOK)

    def OnConnectedCheck(self, is_connected):
        debug_print(f'OnConnectedCheck')
        if is_connected:
            self.FNeedRefresh = True
            self.sysbtnConnect.Enabled = False
            self.sysbtnDisconnect.Enabled = True
            self.log('Measurement started')
        else:
            self.FNeedRefresh = False
            self.sysbtnConnect.Enabled = True
            self.sysbtnDisconnect.Enabled = False
            self.log('Measurement stopped')
    def UIRefreshEvent(self):
        self.FNeedRefresh = True
        if self.FNeedRefresh:
            ResultTuple = app.get_system_var_value('tio.pedal_speed')
            if 2 == len(ResultTuple): 
                self.edtShowSpeed.Text = f'{ResultTuple[1]:.2f}'
            else:
                self.edtShowSpeed.Text = '0.00'
            ResultTuple= app.get_system_var_value('tio.pedal_position')
            if 2 == len(ResultTuple): 
                self.edtShowPosition.Text = f'{ResultTuple[1]:.2f}'
            else:
                self.edtShowPosition.Text = '0.00'
            ResultTuple = app.get_system_var_value('tio.pedal_is_connected')
            if 2 == len(ResultTuple) and 1 == ResultTuple[1]: 
                self.svgShowConnected.Enabled = True
            else:
                self.svgShowConnected.Enabled = False
            ResultTuple = app.get_system_var_value('tio.pedal_is_power_on')
            if 2 == len(ResultTuple) and 1 == ResultTuple[1]: 
                self.svgShowPower.Enabled = True
            else:
                self.svgShowPower.Enabled = False
            ResultTuple = app.get_system_var_value('tio.pedal_is_servo_on')
            if 2 == len(ResultTuple) and 1 == ResultTuple[1]: 
                self.svgShowServoOn.Enabled = True
            else:
                self.svgShowServoOn.Enabled = False
            ResultTuple = app.get_system_var_value('tio.pedal_has_fault')
            if 2 == len(ResultTuple) and 1 == ResultTuple[1]: 
                self.svgShowFault.Enabled = True
            else:
                self.svgShowFault.Enabled = False
            ResultTuple= app.get_system_var_value('tio.pedal_fault_code')
            if 2 == len(ResultTuple): 
                self.edtShowErrorCode.Text = f'{ResultTuple[1]:.2f}'
            else:
                self.edtShowErrorCode.Text = '0'


    # def OnMeasurementStartStoped(self):     
# Auto Generated Python Code, do not modify START [MAIN] ------------
if __name__ == "__main__":
    try:
        Pedal_Control().Show()
        Application.Run()
    except SystemExit:
        pass
# Auto Generated Python Code, do not modify END [MAIN] --------------
