#include "MainWindow.h"
#include <QFileDialog>
#include <QThread>
#include <QtDebug>
#include"stroke.h"
#include "string.h"

#include <stdio.h>
#include <string.h>
#include <WinSock.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>

#include <QTextStream>
#include <stdio.h>

using namespace std;
using namespace cv;

vector<Point> se;//端点
vector<Point> sf;//交叉点

sfInfo sfinfo[20];//交叉点簇
vector<Point> edge;//边缘点：
vector<Point> edge_center;//交叉区中心点：

vector<Point> s;//普通点
vector<Point> sef;//端点＋交叉点
vector<Point> s1;//二值化后的黑点

vector<Point> newpoint;//记录的每一次更新的坐标
vector<Point> newpoint_mark;//起点标记

vector<string> vec;//定义个一个字符串容器,存储数据库中的路径
vector<string> pic_id;//定义个一个字符串容器,存储数据库中的图像名称
String picId;
vector<int> dir;//定义一个方向容器

vector<Point> combine_point;//存储合并后所有点的坐标
vector<Point> combine_point_new;//存储合并后所有点的坐标_新点集
vector<Point> combine_point_mark;//存储需要合并的起始点、终点的坐标
vector<Point> combine_point_mark_new;//存储需要合并的起始点、终点的坐标_新点集
//combine3
vector<Point> combine3_point_mark;//存储需要合并的起始点、终点的坐标_新点集

//特殊笔画处理-“钩”型笔画：
vector<Point> point_gou;//存储笔画
vector<Point> point_gou_mark;//存储7个控制点
vector<Point> point_bezier_3;//贝塞尔点
//特殊笔画处理-“山”型笔画：
vector<Point> point_bezier_2;//二阶贝塞尔点
//“钩”型笔画的进一步处理：

vector<Point> S_0;//原笔画S_0点：由点1-7段、点2-7段组成
vector<Point> S_1;//新笔画S_1点：由点1、4、5、2贝塞尔组成
vector<Point> S_2;//差分笔画S_2点：由中和点组成
int one_x = 0;
int two_x = 0;
int three_x = 0;
int four_x = 0;
int five_x = 0;
int six_x = 0;
int seven_x = 0;

int one_y = 0;
int two_y = 0;
int three_y = 0;
int four_y = 0;
int five_y = 0;
int six_y = 0;
int seven_y = 0;


StrokesInfo strokesinfo[20];//定义了一个名为 strokesinfo 的数组，它有 20 个元素，每个元素都是一个 StrokesInfo 结构体
StrokesInfo strokesinfo_com[20]; //存储去重后的合并笔画
double strokes_ave;//笔画均值
double variance;//笔画方差
double Median;//中位数


qiaoInfo qiaoinfo[20];//存储笔画中的桥

//Mat-->QImage
static QImage cvMat_to_QImage(const cv::Mat& mat) {
    switch (mat.type())
    {
        // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }

    // 8-bit, 1 channel
    case CV_8UC1:
    {
        static QVector<QRgb>  sColorTable;
        // only create our color table once
        if (sColorTable.isEmpty())
        {
            for (int i = 0; i < 256; ++i)
                sColorTable.push_back(qRgb(i, i, i));
        }
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        image.setColorTable(sColorTable);
        return image;
    }

    default:
        qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
        break;
    }
    return QImage();
}

//Mat-->QPixmap
static QPixmap cvMatToQPixmap(const cv::Mat& inMat)
{
    return QPixmap::fromImage(cvMat_to_QImage(inMat));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
   
    //选择图片按钮响应
    connect(ui.selectBtn, &QPushButton::clicked, this, [=]()
    {
        qDebug() << "select a pic!";
        QString curDir = QDir::currentPath();//选择文件
        QString filename = QFileDialog::getOpenFileName(this, "select Image", curDir,
            "Images (*.png *.bmp *.jpg *.tif *.GIF )");
        if (filename.isEmpty())
        {
            return;
        }
        QImage* img = new QImage;
        if (!(img->load(filename))) //加载图像
        {
            qDebug()<<"false!";
            delete img;
            return;
        }

        qDebug() << "success!";

        *img = img->convertToFormat(QImage::Format_RGB32);
        //srcImage = QImage2cvMat(*img);

        ui.show_label->setPixmap(QPixmap::fromImage(*img));
        ui.show_label->setScaledContents(true);

        // QLineEdit 是一个单行文本编辑框
        ui.picAddEdit->setText(filename);


    });

    //细化按钮响应
    connect(ui.dst2Btn, &QPushButton::clicked, this, [=]()
    {
        //首先从图像地址栏读取地址信息
        QString picAdd = ui.picAddEdit->text();//QString转换String
        string name = picAdd.toStdString();
        
        Mat src = imread(name);
        Mat image;

        //转为灰度图像
        cvtColor(src, image, CV_BGR2GRAY);

        //读取灰度图像image的行和列
        int rows = image.rows;
        int cols = image.cols;

        //使用大津法对图像进行二值化
        double  Otsu = 0;
        cv::Mat dst2;
        Otsu = cv::threshold(image, dst2, Otsu, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
        //std::cout << "OpenCVthresh=" << Otsu << std::endl;

        //二值化后的dst2图像
        image = dst2.clone();

        //计算NPB,经过二值化处理之后的书法字黑色像素点数：
        int NPB = 0;
        s1.clear();
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (image.at<uchar>(row, col) == 0) {
                    s1.push_back(Point(row, col));
                    NPB++;
                }
            }
        }

        //单通道图像的反色
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //细化
        zhang_thinimage_improve(image);

        //单通道图像的反色
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //计算骨架点数目：
        int NSP = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (image.at<uchar>(row, col) == 0) {
                    NSP++;
                }
            }
        }

        //进行笔画提取，找出像素值为0的端点和交叉点
        search_point(image, se, sf, s, sef, sfinfo);

        //复制细化后的图像
        Mat dst_temp = image;
        Mat img = image.clone();//用于提取骨架笔画

        //复制转化为彩色图像
        Mat mask = channelSwitching(dst_temp);

        //绘制mask图像并显示：
        //新建白底图像
        for (int i = 0; i < mask.rows; i++)
        {
            for (int j = 0; j < mask.cols; j++)
            {

                mask.at<Vec3b>(i, j)[0] = 255;
                mask.at<Vec3b>(i, j)[1] = 255;
                mask.at<Vec3b>(i, j)[2] = 255;
            }
        }
        //画出端点
        for (size_t i = 0; i < se.size(); i++)
        {
            Point tem;
            tem = se[i];
            mask.at<Vec3b>(tem.x, tem.y)[0] = 255;
            mask.at<Vec3b>(tem.x, tem.y)[1] = 0;
            mask.at<Vec3b>(tem.x, tem.y)[2] = 0;
        }

        //画出平常点
        for (size_t i = 0; i < s.size(); i++)
        {
            Point tems;
            tems = s[i];
            mask.at<Vec3b>(tems.x, tems.y)[0] = 0;
            mask.at<Vec3b>(tems.x, tems.y)[1] = 0;
            mask.at<Vec3b>(tems.x, tems.y)[2] = 0;
        }
        //画出交叉点
        for (size_t i = 0; i < sf.size(); i++)
        {
            Point tems;
            tems = sf[i];
            mask.at<Vec3b>(tems.x, tems.y)[0] = 0;
            mask.at<Vec3b>(tems.x, tems.y)[1] = 0;
            mask.at<Vec3b>(tems.x, tems.y)[2] = 255;
        }


        //将Mat图像转化为Qpixmap，并显示
        QPixmap dst2img = cvMatToQPixmap(mask);
        ui.masklabel->setPixmap(dst2img);
        ui.masklabel->setScaledContents(true);

    });

    //提取骨架笔画按钮响应
    connect(ui.extractBtn, &QPushButton::clicked, this, [=]()
    {
        //首先从图像地址栏读取地址信息
        QString picAdd = ui.picAddEdit->text();//QString转换String
        string name = picAdd.toStdString();

        Mat src = imread(name);
        Mat image;

        //转为灰度图像
        cvtColor(src, image, CV_BGR2GRAY);

        //读取灰度图像image的行和列
        int rows = image.rows;
        int cols = image.cols;

        //使用大津法对图像进行二值化
        double  Otsu = 0;
        cv::Mat dst2;
        Otsu = cv::threshold(image, dst2, Otsu, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
        //std::cout << "OpenCVthresh=" << Otsu << std::endl;

        //二值化后的dst2图像
        image = dst2.clone();

        //计算NPB,经过二值化处理之后的书法字黑色像素点数：
        int NPB = 0;
        s1.clear();
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (image.at<uchar>(row, col) == 0) {
                    s1.push_back(Point(row, col));
                    NPB++;
                }
            }
        }

        //单通道图像的反色
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //细化
        zhang_thinimage_improve(image);

        //单通道图像的反色
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //计算骨架点数目：
        int NSP = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (image.at<uchar>(row, col) == 0) {
                    NSP++;
                }
            }
        }

        //进行笔画提取，找出像素值为0的端点和交叉点
        search_point(image, se, sf, s, sef, sfinfo);

        //复制细化后的图像
        Mat dst_temp = image;
        Mat draw_pic = image; //绘制未合并笔画之前的彩图
        Mat img = image.clone();//用于提取骨架笔画
        Mat img_new = image.clone();//更新获取骨架笔画

        //获取骨架笔画
        craw_stroke(img, se, sf, s, sef, newpoint_mark, newpoint, dir);
        craw_stroke_new(img_new, se, sf, s1, s, sef, newpoint_mark, newpoint, dir, strokesinfo, strokes_ave);
        Save_strokesinfo(newpoint_mark.size() / 2, newpoint_mark, newpoint, strokesinfo, strokes_ave);

        //绘制未合并笔画之前的彩图
        Mat extractPic = draw_picture(draw_pic,s1,strokesinfo);

        //将Mat图像转化为Qpixmap，并显示
        QPixmap extractimg = cvMatToQPixmap(extractPic);
        ui.extractlabel->setPixmap(extractimg);
        ui.extractlabel->setScaledContents(true);

    });

    //合并骨架笔画按钮响应
    connect(ui.combineBtn, &QPushButton::clicked, this, [=]()
    {
        se.clear();//端点
        sf.clear();//交叉点
        s.clear();//普通点
        sef.clear();//端点＋交叉点
        s1.clear();//二值化后的黑点
        newpoint.clear();//记录的每一次更新的坐标
        newpoint_mark.clear();//起点标记
        dir.clear();//定义一个方向容器

        combine_point.clear();//存储合并后所有点的坐标
        combine_point_new.clear();//存储合并后所有点的坐标_新点集
        combine_point_mark.clear();//存储需要合并的起始点、终点的坐标
        combine_point_mark_new.clear();//存储需要合并的起始点、终点的坐标_新点集
        //combine3
        combine3_point_mark.clear();//存储需要合并的起始点、终点的坐标_新点集

        //特殊笔画处理-“钩”型笔画：
        point_gou.clear();//存储笔画
        point_gou_mark.clear();//存储7个控制点
        point_bezier_3.clear();//贝塞尔点
        S_0.clear();//原笔画S_0点：由点1-7段、点2-7段组成
        S_1.clear();//新笔画S_1点：由点1、4、5、2贝塞尔组成
        S_2.clear();//差分笔画S_2点：由中和点组成

        //首先从图像地址栏读取地址信息
        QString picAdd = ui.picAddEdit->text();//QString转换String
        string name = picAdd.toStdString();

        Mat src = imread(name);
        Mat image;

        //转为灰度图像
        cvtColor(src, image, CV_BGR2GRAY);

        //读取灰度图像image的行和列
        int rows = image.rows;
        int cols = image.cols;

        //使用大津法对图像进行二值化
        double  Otsu = 0;
        cv::Mat dst2;
        Otsu = cv::threshold(image, dst2, Otsu, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
        //std::cout << "OpenCVthresh=" << Otsu << std::endl;

        //二值化后的dst2图像
        image = dst2.clone();
        Mat img_gou = dst2.clone();//二值化图像用于钩型笔画处理（11.27换成大津法）
        Mat img_edge = dst2.clone();  //二值化图像用于交叉区边缘像素点
        Mat img_Acombine = dst2.clone();  //二值化图像用于A型笔画combine

        //计算NPB,经过二值化处理之后的书法字黑色像素点数：
        int NPB = 0;
        s1.clear();
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (image.at<uchar>(row, col) == 0) {
                    s1.push_back(Point(row, col));
                    NPB++;
                }
            }
        }

        //单通道图像的反色
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //细化
        zhang_thinimage_improve(image);
        //Mat img_gou1 = image;//细化后图像用于钩型笔画
        //Mat img_edge1 = image.clone();  //细化图像用于交叉区边缘斜率判定

        //单通道图像的反色
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //计算骨架点数目：
        int NSP = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (image.at<uchar>(row, col) == 0) {
                    NSP++;
                }
            }
        }

        //进行笔画提取，找出像素值为0的端点和交叉点
        search_point(image, se,sf, s, sef, sfinfo);

        //复制细化后的图像
        Mat draw_pic = image;
        Mat draw_pic1 = image;
        Mat img = image.clone();//提取骨架笔画
        Mat img_new = image.clone();//更新获取骨架笔画
        Mat img_gou1 = image;//细化后图像用于钩型笔画
        Mat img_edge1 = image.clone();  //细化图像用于交叉区边缘斜率判定

        //获取骨架笔画
        craw_stroke(img, se, sf, s, sef, newpoint_mark, newpoint, dir);
        craw_stroke_new(img_new, se, sf, s1, s, sef, newpoint_mark, newpoint, dir, strokesinfo, strokes_ave);

        ave(strokesinfo, strokes_ave, variance, &Median);
        //“钩”型笔画处理
        gou(img_gou, img_gou1, strokesinfo, point_gou_mark, sfinfo, se, one_x, two_x, three_x, four_x, five_x, six_x, seven_x, one_y, two_y, three_y, four_y, five_y,
            six_y, seven_y, Median, S_0, S_1, S_2, s1, point_bezier_3);

        cout << "桥笔画合并==Median=" << Median << endl;
        //“桥”笔画合并
        duanqiao(img_edge, img_edge1, NPB,  NSP, strokesinfo,  Median, se, qiaoinfo,sfinfo,edge_center, edge);

        //合并笔画
        combine1(draw_pic, NPB, NSP,strokesinfo,combine3_point_mark);
        combine2_save(strokesinfo_com, strokesinfo);

        //找出A类短笔画中需要合并的笔画进行合并
        A_Combine(img_Acombine, NPB, NSP,strokesinfo_com,  Median, se, sf, sfinfo);

        //绘制合并笔画之后的彩图
        Mat combinePic = draw_picture1(draw_pic1, s1, strokesinfo_com, point_bezier_2, point_bezier_3, S_2, NPB, NSP, sfinfo, edge_center, edge);

        //将Mat图像转化为Qpixmap，并显示
        QPixmap extractimg = cvMatToQPixmap(combinePic);
        ui.combinelabel->setPixmap(extractimg);
        ui.combinelabel->setScaledContents(true);

    });

}
