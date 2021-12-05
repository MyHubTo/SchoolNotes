## 1.setAttribute

用于设置各种窗口小部件（widget）的属性。使用QWidget :: setAttribute（）<font color=blue>设置和清除</font>属性，并使用QWidget :: testAttribute（）进行查询，尽管有些具有下面提到的特殊便利功能。
* Qt::WA_AcceptDrops	允许将拖放操作中的数据拖放到窗口小部件上（请参阅QWidget :: setAcceptDrops（））。
* Qt::WA_AlwaysShowToolTips	为非活动窗口启用工具提示。
* Qt::WA_DeleteOnClose	当窗口小部件接受close事件时，Qt删除此窗口小部件（请参阅QWidget :: closeEvent（））。
* Qt::WA_Disabled	表示窗口小部件已禁用，即它不接收任何鼠标或键盘事件。还有一个getter函数QWidget :: isEnabled（）。这由Qt内核设置/清除。
* Qt::WA_DontShowOnScreen	表示窗口小部件已隐藏或不是可查看桌面的一部分。
* Qt::WA_MouseTracking	表示窗口小部件已启用鼠标跟踪。请参阅QWidget :: mouseTracking。
* Qt::WA_NoMouseReplay	用于弹出窗口小部件(popup)。指示弹出窗口小部件关闭时不应重播最近的鼠标按下事件。该标志由小部件的作者设置，并在每次小部件接收到新的鼠标事件时由Qt内核清除。
* Qt::WA_TranslucentBackground	表示窗口小部件应具有半透明背景，即窗口小部件的任何非不透明区域将是半透明的（因为窗口小部件将具有Alpha通道。）设置此标志会导致设置WA_NoSystemBackground。在Windows上，窗口小部件还需要设置Qt :: FramelessWindowHint窗口标志。该标志由小部件的作者设置或清除。
