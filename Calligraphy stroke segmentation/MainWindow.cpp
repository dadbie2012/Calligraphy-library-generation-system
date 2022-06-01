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

vector<Point> se;//�˵�
vector<Point> sf;//�����

sfInfo sfinfo[20];//������
vector<Point> edge;//��Ե�㣺
vector<Point> edge_center;//���������ĵ㣺

vector<Point> s;//��ͨ��
vector<Point> sef;//�˵㣫�����
vector<Point> s1;//��ֵ����ĺڵ�

vector<Point> newpoint;//��¼��ÿһ�θ��µ�����
vector<Point> newpoint_mark;//�����

vector<string> vec;//�����һ���ַ�������,�洢���ݿ��е�·��
vector<string> pic_id;//�����һ���ַ�������,�洢���ݿ��е�ͼ������
String picId;
vector<int> dir;//����һ����������

vector<Point> combine_point;//�洢�ϲ������е������
vector<Point> combine_point_new;//�洢�ϲ������е������_�µ㼯
vector<Point> combine_point_mark;//�洢��Ҫ�ϲ�����ʼ�㡢�յ������
vector<Point> combine_point_mark_new;//�洢��Ҫ�ϲ�����ʼ�㡢�յ������_�µ㼯
//combine3
vector<Point> combine3_point_mark;//�洢��Ҫ�ϲ�����ʼ�㡢�յ������_�µ㼯

//����ʻ�����-�������ͱʻ���
vector<Point> point_gou;//�洢�ʻ�
vector<Point> point_gou_mark;//�洢7�����Ƶ�
vector<Point> point_bezier_3;//��������
//����ʻ�����-��ɽ���ͱʻ���
vector<Point> point_bezier_2;//���ױ�������
//�������ͱʻ��Ľ�һ������

vector<Point> S_0;//ԭ�ʻ�S_0�㣺�ɵ�1-7�Ρ���2-7�����
vector<Point> S_1;//�±ʻ�S_1�㣺�ɵ�1��4��5��2���������
vector<Point> S_2;//��ֱʻ�S_2�㣺���к͵����
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


StrokesInfo strokesinfo[20];//������һ����Ϊ strokesinfo �����飬���� 20 ��Ԫ�أ�ÿ��Ԫ�ض���һ�� StrokesInfo �ṹ��
StrokesInfo strokesinfo_com[20]; //�洢ȥ�غ�ĺϲ��ʻ�
double strokes_ave;//�ʻ���ֵ
double variance;//�ʻ�����
double Median;//��λ��


qiaoInfo qiaoinfo[20];//�洢�ʻ��е���

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
   
    //ѡ��ͼƬ��ť��Ӧ
    connect(ui.selectBtn, &QPushButton::clicked, this, [=]()
    {
        qDebug() << "select a pic!";
        QString curDir = QDir::currentPath();//ѡ���ļ�
        QString filename = QFileDialog::getOpenFileName(this, "select Image", curDir,
            "Images (*.png *.bmp *.jpg *.tif *.GIF )");
        if (filename.isEmpty())
        {
            return;
        }
        QImage* img = new QImage;
        if (!(img->load(filename))) //����ͼ��
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

        // QLineEdit ��һ�������ı��༭��
        ui.picAddEdit->setText(filename);


    });

    //ϸ����ť��Ӧ
    connect(ui.dst2Btn, &QPushButton::clicked, this, [=]()
    {
        //���ȴ�ͼ���ַ����ȡ��ַ��Ϣ
        QString picAdd = ui.picAddEdit->text();//QStringת��String
        string name = picAdd.toStdString();
        
        Mat src = imread(name);
        Mat image;

        //תΪ�Ҷ�ͼ��
        cvtColor(src, image, CV_BGR2GRAY);

        //��ȡ�Ҷ�ͼ��image���к���
        int rows = image.rows;
        int cols = image.cols;

        //ʹ�ô�򷨶�ͼ����ж�ֵ��
        double  Otsu = 0;
        cv::Mat dst2;
        Otsu = cv::threshold(image, dst2, Otsu, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
        //std::cout << "OpenCVthresh=" << Otsu << std::endl;

        //��ֵ�����dst2ͼ��
        image = dst2.clone();

        //����NPB,������ֵ������֮����鷨�ֺ�ɫ���ص�����
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

        //��ͨ��ͼ��ķ�ɫ
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //ϸ��
        zhang_thinimage_improve(image);

        //��ͨ��ͼ��ķ�ɫ
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //����Ǽܵ���Ŀ��
        int NSP = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (image.at<uchar>(row, col) == 0) {
                    NSP++;
                }
            }
        }

        //���бʻ���ȡ���ҳ�����ֵΪ0�Ķ˵�ͽ����
        search_point(image, se, sf, s, sef, sfinfo);

        //����ϸ�����ͼ��
        Mat dst_temp = image;
        Mat img = image.clone();//������ȡ�Ǽܱʻ�

        //����ת��Ϊ��ɫͼ��
        Mat mask = channelSwitching(dst_temp);

        //����maskͼ����ʾ��
        //�½��׵�ͼ��
        for (int i = 0; i < mask.rows; i++)
        {
            for (int j = 0; j < mask.cols; j++)
            {

                mask.at<Vec3b>(i, j)[0] = 255;
                mask.at<Vec3b>(i, j)[1] = 255;
                mask.at<Vec3b>(i, j)[2] = 255;
            }
        }
        //�����˵�
        for (size_t i = 0; i < se.size(); i++)
        {
            Point tem;
            tem = se[i];
            mask.at<Vec3b>(tem.x, tem.y)[0] = 255;
            mask.at<Vec3b>(tem.x, tem.y)[1] = 0;
            mask.at<Vec3b>(tem.x, tem.y)[2] = 0;
        }

        //����ƽ����
        for (size_t i = 0; i < s.size(); i++)
        {
            Point tems;
            tems = s[i];
            mask.at<Vec3b>(tems.x, tems.y)[0] = 0;
            mask.at<Vec3b>(tems.x, tems.y)[1] = 0;
            mask.at<Vec3b>(tems.x, tems.y)[2] = 0;
        }
        //���������
        for (size_t i = 0; i < sf.size(); i++)
        {
            Point tems;
            tems = sf[i];
            mask.at<Vec3b>(tems.x, tems.y)[0] = 0;
            mask.at<Vec3b>(tems.x, tems.y)[1] = 0;
            mask.at<Vec3b>(tems.x, tems.y)[2] = 255;
        }


        //��Matͼ��ת��ΪQpixmap������ʾ
        QPixmap dst2img = cvMatToQPixmap(mask);
        ui.masklabel->setPixmap(dst2img);
        ui.masklabel->setScaledContents(true);

    });

    //��ȡ�Ǽܱʻ���ť��Ӧ
    connect(ui.extractBtn, &QPushButton::clicked, this, [=]()
    {
        //���ȴ�ͼ���ַ����ȡ��ַ��Ϣ
        QString picAdd = ui.picAddEdit->text();//QStringת��String
        string name = picAdd.toStdString();

        Mat src = imread(name);
        Mat image;

        //תΪ�Ҷ�ͼ��
        cvtColor(src, image, CV_BGR2GRAY);

        //��ȡ�Ҷ�ͼ��image���к���
        int rows = image.rows;
        int cols = image.cols;

        //ʹ�ô�򷨶�ͼ����ж�ֵ��
        double  Otsu = 0;
        cv::Mat dst2;
        Otsu = cv::threshold(image, dst2, Otsu, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
        //std::cout << "OpenCVthresh=" << Otsu << std::endl;

        //��ֵ�����dst2ͼ��
        image = dst2.clone();

        //����NPB,������ֵ������֮����鷨�ֺ�ɫ���ص�����
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

        //��ͨ��ͼ��ķ�ɫ
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //ϸ��
        zhang_thinimage_improve(image);

        //��ͨ��ͼ��ķ�ɫ
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //����Ǽܵ���Ŀ��
        int NSP = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (image.at<uchar>(row, col) == 0) {
                    NSP++;
                }
            }
        }

        //���бʻ���ȡ���ҳ�����ֵΪ0�Ķ˵�ͽ����
        search_point(image, se, sf, s, sef, sfinfo);

        //����ϸ�����ͼ��
        Mat dst_temp = image;
        Mat draw_pic = image; //����δ�ϲ��ʻ�֮ǰ�Ĳ�ͼ
        Mat img = image.clone();//������ȡ�Ǽܱʻ�
        Mat img_new = image.clone();//���»�ȡ�Ǽܱʻ�

        //��ȡ�Ǽܱʻ�
        craw_stroke(img, se, sf, s, sef, newpoint_mark, newpoint, dir);
        craw_stroke_new(img_new, se, sf, s1, s, sef, newpoint_mark, newpoint, dir, strokesinfo, strokes_ave);
        Save_strokesinfo(newpoint_mark.size() / 2, newpoint_mark, newpoint, strokesinfo, strokes_ave);

        //����δ�ϲ��ʻ�֮ǰ�Ĳ�ͼ
        Mat extractPic = draw_picture(draw_pic,s1,strokesinfo);

        //��Matͼ��ת��ΪQpixmap������ʾ
        QPixmap extractimg = cvMatToQPixmap(extractPic);
        ui.extractlabel->setPixmap(extractimg);
        ui.extractlabel->setScaledContents(true);

    });

    //�ϲ��Ǽܱʻ���ť��Ӧ
    connect(ui.combineBtn, &QPushButton::clicked, this, [=]()
    {
        se.clear();//�˵�
        sf.clear();//�����
        s.clear();//��ͨ��
        sef.clear();//�˵㣫�����
        s1.clear();//��ֵ����ĺڵ�
        newpoint.clear();//��¼��ÿһ�θ��µ�����
        newpoint_mark.clear();//�����
        dir.clear();//����һ����������

        combine_point.clear();//�洢�ϲ������е������
        combine_point_new.clear();//�洢�ϲ������е������_�µ㼯
        combine_point_mark.clear();//�洢��Ҫ�ϲ�����ʼ�㡢�յ������
        combine_point_mark_new.clear();//�洢��Ҫ�ϲ�����ʼ�㡢�յ������_�µ㼯
        //combine3
        combine3_point_mark.clear();//�洢��Ҫ�ϲ�����ʼ�㡢�յ������_�µ㼯

        //����ʻ�����-�������ͱʻ���
        point_gou.clear();//�洢�ʻ�
        point_gou_mark.clear();//�洢7�����Ƶ�
        point_bezier_3.clear();//��������
        S_0.clear();//ԭ�ʻ�S_0�㣺�ɵ�1-7�Ρ���2-7�����
        S_1.clear();//�±ʻ�S_1�㣺�ɵ�1��4��5��2���������
        S_2.clear();//��ֱʻ�S_2�㣺���к͵����

        //���ȴ�ͼ���ַ����ȡ��ַ��Ϣ
        QString picAdd = ui.picAddEdit->text();//QStringת��String
        string name = picAdd.toStdString();

        Mat src = imread(name);
        Mat image;

        //תΪ�Ҷ�ͼ��
        cvtColor(src, image, CV_BGR2GRAY);

        //��ȡ�Ҷ�ͼ��image���к���
        int rows = image.rows;
        int cols = image.cols;

        //ʹ�ô�򷨶�ͼ����ж�ֵ��
        double  Otsu = 0;
        cv::Mat dst2;
        Otsu = cv::threshold(image, dst2, Otsu, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
        //std::cout << "OpenCVthresh=" << Otsu << std::endl;

        //��ֵ�����dst2ͼ��
        image = dst2.clone();
        Mat img_gou = dst2.clone();//��ֵ��ͼ�����ڹ��ͱʻ�����11.27���ɴ�򷨣�
        Mat img_edge = dst2.clone();  //��ֵ��ͼ�����ڽ�������Ե���ص�
        Mat img_Acombine = dst2.clone();  //��ֵ��ͼ������A�ͱʻ�combine

        //����NPB,������ֵ������֮����鷨�ֺ�ɫ���ص�����
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

        //��ͨ��ͼ��ķ�ɫ
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //ϸ��
        zhang_thinimage_improve(image);
        //Mat img_gou1 = image;//ϸ����ͼ�����ڹ��ͱʻ�
        //Mat img_edge1 = image.clone();  //ϸ��ͼ�����ڽ�������Եб���ж�

        //��ͨ��ͼ��ķ�ɫ
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                image.at<uchar>(row, col) = 255 - image.at<uchar>(row, col);
            }
        }

        //����Ǽܵ���Ŀ��
        int NSP = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (image.at<uchar>(row, col) == 0) {
                    NSP++;
                }
            }
        }

        //���бʻ���ȡ���ҳ�����ֵΪ0�Ķ˵�ͽ����
        search_point(image, se,sf, s, sef, sfinfo);

        //����ϸ�����ͼ��
        Mat draw_pic = image;
        Mat draw_pic1 = image;
        Mat img = image.clone();//��ȡ�Ǽܱʻ�
        Mat img_new = image.clone();//���»�ȡ�Ǽܱʻ�
        Mat img_gou1 = image;//ϸ����ͼ�����ڹ��ͱʻ�
        Mat img_edge1 = image.clone();  //ϸ��ͼ�����ڽ�������Եб���ж�

        //��ȡ�Ǽܱʻ�
        craw_stroke(img, se, sf, s, sef, newpoint_mark, newpoint, dir);
        craw_stroke_new(img_new, se, sf, s1, s, sef, newpoint_mark, newpoint, dir, strokesinfo, strokes_ave);

        ave(strokesinfo, strokes_ave, variance, &Median);
        //�������ͱʻ�����
        gou(img_gou, img_gou1, strokesinfo, point_gou_mark, sfinfo, se, one_x, two_x, three_x, four_x, five_x, six_x, seven_x, one_y, two_y, three_y, four_y, five_y,
            six_y, seven_y, Median, S_0, S_1, S_2, s1, point_bezier_3);

        cout << "�űʻ��ϲ�==Median=" << Median << endl;
        //���š��ʻ��ϲ�
        duanqiao(img_edge, img_edge1, NPB,  NSP, strokesinfo,  Median, se, qiaoinfo,sfinfo,edge_center, edge);

        //�ϲ��ʻ�
        combine1(draw_pic, NPB, NSP,strokesinfo,combine3_point_mark);
        combine2_save(strokesinfo_com, strokesinfo);

        //�ҳ�A��̱ʻ�����Ҫ�ϲ��ıʻ����кϲ�
        A_Combine(img_Acombine, NPB, NSP,strokesinfo_com,  Median, se, sf, sfinfo);

        //���ƺϲ��ʻ�֮��Ĳ�ͼ
        Mat combinePic = draw_picture1(draw_pic1, s1, strokesinfo_com, point_bezier_2, point_bezier_3, S_2, NPB, NSP, sfinfo, edge_center, edge);

        //��Matͼ��ת��ΪQpixmap������ʾ
        QPixmap extractimg = cvMatToQPixmap(combinePic);
        ui.combinelabel->setPixmap(extractimg);
        ui.combinelabel->setScaledContents(true);

    });

}
