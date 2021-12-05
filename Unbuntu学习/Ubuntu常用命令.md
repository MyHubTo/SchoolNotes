## 1. 文件操作
---
### 1.打开文本.txt

常见的基于控制台的文本编辑器有以下几种：
|编辑器名称|作用|
|-------|-----------|
|emacs  |        综合性的GNU emacs 编辑环境|
|nano   |          一个类似于经典的pico的文本编辑器，内置了一个pine邮件程序|
|vim    |           一个改进的vi文本编辑器|
注意并不是所有的文本编辑器都是基于控制台的，也就是说支持终端使用的。有一些文本编辑器被设计用来提供带有菜单栏，按钮，进度条等的图形界面。例如：
|编辑器名称|作用|
|-------|-----------|
|gedit   |            一个GUI的文本编辑器，Ubuntu默认安装|
|kate     |          一个简单的KDE文本编辑器|
|kedit     |         另外一个简单的KDE文本编辑器|
### 2.显示隐藏文件
* crtl+H 显示与隐藏文件

### 3. 删除文件即文件夹下的文件

```bash
rm [OPTION] [FILENAME]...
```
|命令参数|描述|
|---|---|
|-f, --force|在没有确认删除提示的下删除文件并忽略不存在的文件和参数|
|-i|删除文件前提示确认|
|-I|在删除三个以上的文件或递归删除文件之前提示确认，与 -i 选项相比，侵入性较小，同时提供防止频繁错误的保护。|
|-interactive [=WHEN]|根据指定的 WHEN 进行确认提示：never，once (-I)，always (-i)，如果此参数不加 WHEN 则总是提示|
|--one-file-system|递归删除一个层级时，跳过所有不符合命令行参数的文件系统上的文件|
|--no-preserve-root|不对根目录 '/' 进行任何特殊处理|
|--preserve-root [=all]|不对根目录 '/' 进行递归操作（默认启用）|
|-r, -R, -recursive|以递归方式删除目录及其内容|
|-d, --dir|不使用 -r/-R/-recursive 删除空目录，rm -dir 等同于 rmdir|
|-v, --verbose|显示正在进行的步骤|

可以通过```bash rm --help ```查看所有帮助信息

>[Linux rm 命令详解](https://www.zatp.com/post/rm-command-in-linux/)


## 2. 网络操作

### 1. wget 

具体看帮助:
```bash
wget http://test.com/testfile.zip ->下载指定文件到当前文件夹
wget -O wordpress.zip http://test.com/download ->指定保存名字
wget --limit-rate=300k http://www.linuxde.net/testfile.zip ->限制下载速度
wget -c http://www.linuxde.net/testfile.zip ->断点续传
wget -b http://www.linuxde.net/testfile.zip ->后台下载

# 设置使用指定浏览器下载（伪装下载）
wget --user-agent="Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.16 (KHTML, like Gecko) Chrome/10.0.648.204 Safari/534.16" http://www.linuxde.net/testfile.zip

wget --spider url ->测试下载
wget --tries=40 URL ->设置重试次数为40
wget -i filelist.txt ->从filelist.txt获取下载地址

# 镜像网站
# --miror开户镜像下载。
# -p下载所有为了html页面显示正常的文件。
# --convert-links下载后，转换成本地的链接。
# -P ./LOCAL保存所有文件和目录到本地指定目录
wget --mirror -p --convert-links -P ./LOCAL URL

wget --reject=gif ur ->下载一个网站，但你不希望下载图片，可以使用这条命令
wget -o download.log URL ->把下载信息存入日志文件
wget -Q5m -i filelist.txt ->限制总下载文件大小
wget -r -A.pdf url ->下载指定格式文件

# FTP下载
wget ftp-url
wget --ftp-user=USERNAME --ftp-password=PASSWORD url

```