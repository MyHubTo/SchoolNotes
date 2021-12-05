## 1.QProcess
>#include \<QProcess>

<font color=blue>作用：</font>可以用来启动外部程序，并与它们交互。
要启动一个进程，通过调用start()来进行，参数包含程序的名称和命令行参数，参数作为一个QStringList的单个字符串。

```cpp
QProcess process(this);
    QStringList args;
    args<<"/c"<<"shutdown -s -t "+Time; //其中"/c"不可省略，否则无法解析
    // for(int i=0;i<args.size();i++)
    // {
    //     qDebug()<<args.at(i)<<"";
    // }
    /*void start(const QString &program, const QStringList &arguments, OpenMode mode = ReadWrite);
    *  @param program：执行外部程序的绝对路径；
    */
    process.start("C:/Windows/System32/cmd.exe",args);
    
    process.waitForStarted(500);
    process.waitForFinished(500);
```

---