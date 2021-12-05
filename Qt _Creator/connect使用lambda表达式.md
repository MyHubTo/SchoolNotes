## 1.lambda表达式
`[=]`表示:以复制的形式捕获所有变量
```cpp
connect(ui->pushButton_2,&QPushButton::clicked,this,[=]{
        QString text= ui->lineEdit->text();
        qDebug()<<text;});
```