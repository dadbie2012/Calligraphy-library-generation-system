#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include <QTextEdit>

#include <QPainter>

#include <QDebug>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置固定大小
    setFixedSize(1200,688);

    //设置图标
    setWindowIcon(QIcon("D:/system/image1.jpg"));

    //设置标题
    setWindowTitle("书法字转换登录界面");
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        this->close();


    });

    MyPushButton * startBtn = new MyPushButton("D:/denglu.jpg");
    startBtn->setParent(this);
    startBtn->move( this->width() * 0.58 - startBtn->width() * 0.5 ,this->height() * 0.27 );
    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;
    //监听选择关卡的返回按钮的信号
        connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
            chooseScene->hide(); //将选择关卡场景 隐藏掉
            this->setGeometry(chooseScene->geometry());
            this->show(); //重新显示主场景
        });

    connect(startBtn,&MyPushButton::clicked,[=]()
    {
        qDebug() << "点击了开始";
       // startSound->play(); //开始音效
        //做弹起特效
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500,this,[=]()
            {
                //自身隐藏
                this->hide();
                //显示选择关卡场景
                chooseScene->setGeometry((this->geometry()));
                chooseScene->show();



        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    QPixmap pix2;
    pix.load("D:/system/beijing.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景左上角上图标
    pix2.load("D:/system/biaoti1.png");
    //painter.drawPixmap(0,0,pix2);

    pix2 = pix2.scaled( pix2.width() *1.5 , pix2.height() * 1.5);
    painter.drawPixmap(200,15,pix2);
}
