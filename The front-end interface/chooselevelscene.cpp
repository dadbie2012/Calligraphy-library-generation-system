#include "chooselevelscene.h"
#include <QTextEdit>
#include <QLabel>
#include <QRadioButton>
#include <QProcess>
#include <QDesktopServices>
//#include <QSound>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QTextCodec>
#include <QFileInfo>
#include <QStandardItem>
#include <QMutex>
#include <QWaitCondition>


ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{//配置选择关卡场景
    this->setFixedSize(1200,688);

    //设置图标
    this->setWindowIcon(QPixmap("D:/system/image1.jpg"));
   // this->setWindowIcon(QPixmap("D/system/jiemian2.jpg"));

    //设置标题

    this->setWindowTitle("书法字转换界面");
    //创建菜单栏
    QMenuBar * bar = menuBar();

    setMenuBar(bar);



    //创建开始菜单
    QMenu * startMenu = bar->addMenu("菜单");
    QMenu * startMenu1 = bar->addMenu("选项");
    QMenu * startMenu2 = bar->addMenu("布局");
    QMenu * startMenu3 = bar->addMenu("工具");
    QMenu * startMenu4 = bar->addMenu("版本");

    //创建退出 菜单项
    QAction *  quitAction = startMenu->addAction("退出");
    //返回按钮
    MyPushButton * backBtn = new MyPushButton("D:/denglu.jpg" , "D:/denglu.jpg");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug() << "点击了返回按钮";
        //告诉主场景 我返回了，主场景监听ChooseLevelScene的返回按钮
        //延时返回

        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });

    //开始按钮
    MyPushButton * startBtn = new MyPushButton("D:/denglu.jpg");
    startBtn->setParent(this);
    startBtn->move( this->width() * 0.5 - startBtn->width() * 0.5 ,this->height() *0.92 );
    connect(startBtn,&MyPushButton::clicked,[=]()
    {
        qDebug() << "点击了开始";
        // startSound->play(); //开始音效
        //做弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

    });
    //输入框
    QTextEdit *bbb= new QTextEdit(this);
    bbb->setParent(this);
    bbb->resize(300,50);

    bbb->move(450,140);



    //显示框
    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->move(250,320);
    QFont ft;

    label->setFixedSize(700,300);
    ft.setPointSize(29);
    label->setFont(ft);
    label->setText("书法字转换成功显示区");
    //label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    //风格按钮
    QRadioButton *rb1=new QRadioButton("王羲之",this);
    QRadioButton *rb2=new QRadioButton("欧阳询",this);
    QRadioButton *rb3=new QRadioButton("颜真卿",this);
    QFont ft1;
    ft1.setPointSize(15);
    rb1->move(420,290);
    rb2->move(540,290);
    rb3->move(660,290);
    rb1->setFont(ft1);
    rb2->setFont(ft1);
    rb3->setFont(ft1);
    //利用QLabel显示图片

      connect( rb1 ,& QRadioButton::clicked,[=](){
          qDebug() << "点击了王羲之";

          QFile file("D:\\书法字生成\\outstyle.txt");
          file.open(QIODevice::Append); //用追加方式进行写
          file.write("1");




          file.close();






       });
      connect( rb2 ,& QRadioButton::clicked,[=](){
          qDebug() << "点击了欧阳询";
          QFile file("D:\\书法字生成\\outstyle.txt");
          file.open(QIODevice::Append); //用追加方式进行写
          file.write("2");
          file.close();


       });

      connect( rb3 ,& QRadioButton::clicked,[=](){
          qDebug() << "点击了颜真卿";
          QFile file("D:\\书法字生成\\outstyle.txt");
          file.open(QIODevice::Append); //用追加方式进行写
          file.write("3");
          file.close();


      });



      connect( startBtn ,& MyPushButton::clicked,[=](){
          QString str = bbb->toPlainText();



          qDebug() << str;


          QFile file("D:\\书法字生成\\outtext.txt");
          file.open(QIODevice::Append); //用追加方式进行写
          file.write(str.toUtf8());
          file.close();



          QProcess *pProces = new QProcess(this);
         // pProces->start("C:\\Users\\35843\\source\\repos\\bihuafenge\\x64\\Debug\\笔画分割3.exe");
         pProces->execute("C:\\Users\\35843\\source\\repos\\bihuafenge\\x64\\Debug\\笔画分割3.exe");
          qDebug()<<"调用c++结束";







          //           QProcess myProcess(this);
          //           QString program =  "C:\\Users\\35843\\source\\repos\\bihuafenge\\x64\\Debug\\bihuafenge3.exe";

          //           QStringList arguments;
          //           arguments<<"1";//传递到exe的参数
          //           myProcess.start(program);


        //  QProcess::execute（"C:\\Users\\35843\\Desktop\\Handwritten_CycleGAN\\demo.py");

//          QString local_path = QString("C:/Users/35843/Desktop/Handwritten_CycleGAN/demo.py"); //修改为自己的路径
//          QString path1 = QString("file:///") + local_path;
//         bool is_open = QDesktopServices::openUrl(QUrl(path1,QUrl::TolerantMode));



//          QProcess p(0);
//            p.start("cmd", QStringList()<<"/c"<<"ping www.baidu.com");
//            p.waitForStarted();
//            p.waitForFinished();
//            QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());
// qDebug() << strTemp;


          //调用python

          QProcess p(0);
          p.setWorkingDirectory("C:/Users/35843/Desktop/Handwritten_CycleGAN");//指定进程的工作目录
          QString command = "python demo.py";


          p.start(command);

          p.waitForFinished();
          qDebug()<<QString::fromLocal8Bit(p.readAllStandardError());


          qDebug()<<"调用python结束";
          QMutex mutex;
          QWaitCondition sleep;
          mutex.lock();
          sleep.wait(&mutex, 1000);
          mutex.unlock();

          //显示图片
          QString path="D:/书法字生成/最终图片/finall.jpg";
          QPixmap img(path);
          label->setPixmap(img);
          //label->setScaledContents(true);
          //label->resize(label->width(),label->height());
          //        QImage image;
          //        image.load("D:/test.png");
          //        QPainter painter(&image);
          //        QImage resultImg=image.scaled(label->size(),
          //                                      Qt::KeepAspectRatio,
          //                                      Qt::SmoothTransformation);

          //        label->setPixmap(QPixmap::fromImage(resultImg));
          //        //label->show();









    });






}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load("D:/system/jiemian2.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load("D:/system/biaoti4.png");
    painter.drawPixmap( (this->width() - pix.width())*0.9,200,pix.width(),pix.height(),pix);

    pix.load("D:/system/biaoti5.png");
    painter.drawPixmap( (this->width() - pix.width())*0.9,30,pix.width(),pix.height(),pix);
}
