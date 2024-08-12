import sys
import os
# 获取当前脚本所在的目录
current_dir = os.path.dirname(os.path.abspath(__file__))
# 将当前目录添加到sys.path
sys.path.append(current_dir)
import tio_ui_res
print(tio_ui_res.ui_svg_Connect[1])