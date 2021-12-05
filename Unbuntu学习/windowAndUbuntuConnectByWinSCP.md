# 1.只需要在Windows上下载安装WinSCP
[下载地址](https://winscp.net/eng/download.php)
# 2.获取linux系统的IP地址 主机名 以及 开机密码

# 3.出现问题：
1. WinScp连接被拒绝
   1. 开启|关闭防火墙（这里需要关闭）(打开enable|)
      sudo ufw disable
   2. 开启远程服务
      在终端界面输入：service sshd start。
      出现 failed to start ssh.service. unit ssh.service not found
      解决办法： 安装 open ssh:  sudo apt-get install openssh-server
   3. 重新执行第二步。成功！