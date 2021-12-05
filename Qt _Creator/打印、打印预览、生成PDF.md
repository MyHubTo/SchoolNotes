## 1. 打印文档
---

最简单的方式只需要使用一个QPainter类和一个打印对话框QPrintDialog类就可以完成文档的打印操作。
<font color=red>Qt Print Support</font>
---

### 1.1 添加QT +=printsupport
### 1.2 code

```cpp
    private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
private slots:
    void doPrint();//打印
    void doPrintPreview();//打印预览
    void printPreview(QPrinter *printer);//打印预览
    void creatPDF();//生成PDF
```

```cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QFileInfo>
#include <QMenu>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    textEdit=new QTextEdit(this);
//    textEdit->setMinimumSize(6400,4800);
    QMenu *eidt_memu=ui->menubar->addMenu(tr("文件(&F)"));

    QAction *act_print=new QAction(tr("打印"),this);
    QAction *act_printPreview=new QAction(tr("打印预览"),this);
    QAction *act_pdf=new QAction(tr("生成PDF"),this);

    //connect(act_print,&QAction::triggered,this,&QMainWindow::doPrint);
    connect(act_print,SIGNAL(triggered()),this,SLOT(doPrint()));
    connect(act_printPreview,SIGNAL(triggered()),this,SLOT(doPrintPreview()));
    connect(act_pdf,SIGNAL(triggered()),SLOT(creatPDF()));

//    ui->menubar->addAction(act_print);
//    ui->menubar->addAction(act_printPreview);
//    ui->menubar->addAction(act_pdf);
    eidt_memu->addAction(act_print);
    eidt_memu->addAction(act_printPreview);
    eidt_memu->addAction(act_pdf);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doPrint()
{
    QPrinter printer;//创建打印机对象
    QPrintDialog dlg(&printer);//创建打印对话框

    //如果编辑器中有选中区域，则打印选中区域
    if(ui->textEdit->textCursor().hasSelection())//判断是否被选中
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);

    if(dlg.exec()==QDialog::Accepted)//如果在对话框中按下打印按钮
         ui->textEdit->print(&printer);//则执行打印操作
}

void MainWindow::doPrintPreview()
{
    QPrinter printer;
    QPrintPreviewDialog preview(&printer);//创建打印预览对话框
    preview.setMinimumSize(1000,800);
    //当要生成预览页面时，发射PaintRequseted()信号
    connect(&preview,&QPrintPreviewDialog::paintRequested,this,&MainWindow::printPreview);
    preview.exec();
}

void MainWindow::printPreview(QPrinter *printer)
{
     ui->textEdit->print(printer);
}

void MainWindow::creatPDF()
{
    QString filename=QFileDialog::getSaveFileName(this,tr("导出PDF文件"),QString(),"*.pdf");
    if(!filename.isEmpty())
    {
        if(QFileInfo(filename).suffix().isEmpty())
        {
            filename.append(".pdf");//如果文件后缀为空，则默认使用.pdf
        }
    QPrinter printer;
    printer.setOutputFormat(QPrinter::OutputFormat::PdfFormat);//设置输出格式为PDF
    printer.setOutputFileName(filename);
    ui->textEdit->print(&printer);
    }
}
```