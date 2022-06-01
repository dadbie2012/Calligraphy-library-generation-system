//method.cpp
#include<iostream>
#include <QFileDialog>
#include <QThread>
#include <QtDebug>
#include"stroke.h"

#include <stdio.h>
#include <string.h>
#include <WinSock.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>

using namespace std;
using namespace cv;

int max(int x, int y) //��Դ�ļ���ʵ�ֺ�������
{
	return x > y ? x : y;
}

//���������㣬����ŷ�Ͼ���
int distance(Point& a, Point& b) {
    int dis1 = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return dis1;
}

//zhangϸ���Ľ��㷨
void zhang_thinimage_improve(Mat& srcimage)//��ͨ������ֵ�����ͼ��  
{
    vector<Point> deletelist1;
    int Zhangmude[9];
    int nl = srcimage.rows;
    int nc = srcimage.cols;
    while (true)
    {
        for (int j = 1; j < (nl - 1); j++)
        {
            uchar* data_last = srcimage.ptr<uchar>(j - 1);
            uchar* data = srcimage.ptr<uchar>(j);
            uchar* data_next = srcimage.ptr<uchar>(j + 1);
            for (int i = 1; i < (nc - 1); i++)
            {
                if (data[i] == 255)
                {
                    Zhangmude[0] = 1;
                    if (data_last[i] == 255) Zhangmude[1] = 1;
                    else  Zhangmude[1] = 0;
                    if (data_last[i + 1] == 255) Zhangmude[2] = 1;
                    else  Zhangmude[2] = 0;
                    if (data[i + 1] == 255) Zhangmude[3] = 1;
                    else  Zhangmude[3] = 0;
                    if (data_next[i + 1] == 255) Zhangmude[4] = 1;
                    else  Zhangmude[4] = 0;
                    if (data_next[i] == 255) Zhangmude[5] = 1;
                    else  Zhangmude[5] = 0;
                    if (data_next[i - 1] == 255) Zhangmude[6] = 1;
                    else  Zhangmude[6] = 0;
                    if (data[i - 1] == 255) Zhangmude[7] = 1;
                    else  Zhangmude[7] = 0;
                    if (data_last[i - 1] == 255) Zhangmude[8] = 1;
                    else  Zhangmude[8] = 0;
                    int whitepointtotal = 0;
                    for (int k = 1; k < 9; k++)
                    {
                        //�õ�1�ĸ�����Ŀ�������ֵΪ1
                        whitepointtotal = whitepointtotal + Zhangmude[k];
                    }
                    if ((whitepointtotal >= 2) && (whitepointtotal <= 6))
                    {
                        //�õ�01�ĸ���
                        int ap = 0;
                        if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;
                        if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;
                        if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;
                        if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;
                        if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;
                        if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;
                        if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;
                        if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;
                        //����bp
                        int bp = 0;
                        bp += Zhangmude[1];
                        bp += Zhangmude[2] << 1;
                        bp += Zhangmude[3] << 2;
                        bp += Zhangmude[4] << 3;
                        bp += Zhangmude[5] << 4;
                        bp += Zhangmude[6] << 5;
                        bp += Zhangmude[7] << 6;
                        bp += Zhangmude[8] << 7;

                        if (ap == 1 || bp == 65 || bp == 5 || bp == 20 || bp == 80 || bp == 13 || bp == 22 || bp == 52 || bp == 133 || bp == 141 || bp == 54)
                        {
                            if ((Zhangmude[1] * Zhangmude[7] * Zhangmude[5] == 0) && (Zhangmude[3] * Zhangmude[5] * Zhangmude[7] == 0))
                            {
                                deletelist1.push_back(Point(i, j));  //����������ȥ���õ�
                            }
                        }
                    }
                }
            }
        }
        if (deletelist1.size() == 0) break;
        for (size_t i = 0; i < deletelist1.size(); i++)
        {
            Point tem;
            tem = deletelist1[i];
            uchar* data = srcimage.ptr<uchar>(tem.y);
            data[tem.x] = 0;
        }
        deletelist1.clear();


        for (int j = 1; j < (nl - 1); j++)
        {
            uchar* data_last = srcimage.ptr<uchar>(j - 1);
            uchar* data = srcimage.ptr<uchar>(j);
            uchar* data_next = srcimage.ptr<uchar>(j + 1);
            for (int i = 1; i < (nc - 1); i++)
            {
                if (data[i] == 255)
                {
                    Zhangmude[0] = 1;
                    if (data_last[i] == 255) Zhangmude[1] = 1;
                    else  Zhangmude[1] = 0;
                    if (data_last[i + 1] == 255) Zhangmude[2] = 1;
                    else  Zhangmude[2] = 0;
                    if (data[i + 1] == 255) Zhangmude[3] = 1;
                    else  Zhangmude[3] = 0;
                    if (data_next[i + 1] == 255) Zhangmude[4] = 1;
                    else  Zhangmude[4] = 0;
                    if (data_next[i] == 255) Zhangmude[5] = 1;
                    else  Zhangmude[5] = 0;
                    if (data_next[i - 1] == 255) Zhangmude[6] = 1;
                    else  Zhangmude[6] = 0;
                    if (data[i - 1] == 255) Zhangmude[7] = 1;
                    else  Zhangmude[7] = 0;
                    if (data_last[i - 1] == 255) Zhangmude[8] = 1;
                    else  Zhangmude[8] = 0;
                    int whitepointtotal = 0;
                    for (int k = 1; k < 9; k++)
                    {
                        whitepointtotal = whitepointtotal + Zhangmude[k];
                    }
                    if ((whitepointtotal >= 2) && (whitepointtotal <= 6))
                    {
                        int ap = 0;
                        if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;
                        if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;
                        if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;
                        if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;
                        if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;
                        if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;
                        if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;
                        if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;
                        int bp = 0;
                        bp += Zhangmude[1];
                        bp += Zhangmude[2] << 1;
                        bp += Zhangmude[3] << 2;
                        bp += Zhangmude[4] << 3;
                        bp += Zhangmude[5] << 4;
                        bp += Zhangmude[6] << 5;
                        bp += Zhangmude[7] << 6;
                        bp += Zhangmude[8] << 7;
                        if (ap == 1 || bp == 65 || bp == 5 || bp == 20 || bp == 80 || bp == 13 || bp == 22 || bp == 52 || bp == 133 || bp == 141 || bp == 54)
                        {
                            if ((Zhangmude[1] * Zhangmude[3] * Zhangmude[5] == 0) && (Zhangmude[3] * Zhangmude[1] * Zhangmude[7] == 0))
                            {
                                deletelist1.push_back(Point(i, j));
                            }
                        }
                    }
                }
            }
        }
        if (deletelist1.size() == 0) break;
        for (size_t i = 0; i < deletelist1.size(); i++)
        {
            Point tem;
            tem = deletelist1[i];
            uchar* data = srcimage.ptr<uchar>(tem.y);
            data[tem.x] = 0;
        }
        deletelist1.clear();
    }
}

//��ͨ��ת��ͨ��
Mat channelSwitching(const Mat& src)
{
    Mat three_channel = Mat::zeros(src.rows, src.cols, CV_8UC3);
    vector<Mat> channels;
    if (src.channels() == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            channels.push_back(src);
        }
        merge(&channels[0], channels.size(), three_channel);
    }

    return three_channel;
}

//�ҳ�3�����ص�ͽ�����
void search_point(Mat& image, vector<Point>& se, vector<Point>& sf,vector<Point>& s, vector<Point>& sef, sfInfo* sfinfo) {

    int eightmude[9];
    int nl = image.rows;
    int nc = image.cols;
    se.clear();//�˵��������
    sf.clear();//������������
    s.clear();//��ͨ��
    sef.clear();//�˵㣫�����
    //s1.clear();//��ֵ����ĺڵ�
    //��ս����
    for (int i = 0; i < 20; i++) {
        sfinfo[i].begin.x = 0;
        sfinfo[i].begin.y = 0;
        sfinfo[i].end.x = 0;
        sfinfo[i].end.y = 0;
        sfinfo[i].Pc.x = 0;
        sfinfo[i].Pc.y = 0;
        sfinfo[i].sf_info.clear();
    }


    for (int i = 1; i < (nl - 1); i++) {
        uchar* data_last = image.ptr<uchar>(i - 1);
        uchar* data = image.ptr<uchar>(i);
        uchar* data_next = image.ptr<uchar>(i + 1);
        for (int j = 1; j < (nc - 1); j++) {
            //�����ص�Ϊ�ڣ���0������8�����жϵ������
            if (data[j] == 0) {
                if (data[j + 1] == 0) eightmude[0] = 1;//1��ʾ�������ص�Ϊ��
                else eightmude[0] = 0;
                if (data_last[j + 1] == 0) eightmude[1] = 1;
                else eightmude[1] = 0;
                if (data_last[j] == 0) eightmude[2] = 1;
                else eightmude[2] = 0;
                if (data_last[j - 1] == 0) eightmude[3] = 1;
                else eightmude[3] = 0;
                if (data[j - 1] == 0) eightmude[4] = 1;
                else eightmude[4] = 0;
                if (data_next[j - 1] == 0) eightmude[5] = 1;
                else eightmude[5] = 0;
                if (data_next[j] == 0) eightmude[6] = 1;
                else eightmude[6] = 0;
                if (data_next[j + 1] == 0) eightmude[7] = 1;
                else eightmude[7] = 0;
                int blacktotal = 0;//�����ھ�����
                for (int i = 0; i < 8; i++) {
                    blacktotal = blacktotal + eightmude[i];
                }
                //�жϵ�����ͣ���ͨ�㡢�˵㡢�����
                if (blacktotal == 1) {
                    se.push_back(Point(i, j));  //��������Ϊ�˵�
                    sef.push_back(Point(i, j));
                }
                else if (blacktotal >= 3) {
                    sf.push_back(Point(i, j));  //��������Ϊ�����
                    sef.push_back(Point(i, j));
                }
                else {
                    s.push_back(Point(i, j));  //��������Ϊ��ͨ��
                }
            }
        }
    }
    //����˵㡢�����
    cout << "�˵㣺" << endl;
    for (int i = 0; i < se.size(); i++) {
        cout << "(" << se[i].x << "," << se[i].y << ")" << endl;
    }
    cout << "����㣺" << endl;
    for (int i = 0; i < sf.size(); i++) {
        cout << "(" << sf[i].x << "," << sf[i].y << ")" << endl;
    }
    cout << "�����أ�" << endl;
    int flag = 0;
    //��������㣬����һ��������ǰһ�����ڣ���ǰһ������㣬������������
    for (int i = 0; i < sf.size() - 1; i++) {
        //����ǰ�����ͺ�һ�����ڣ��򽫵�ǰ�����洢��sfInfo
        if (sqrt((sf[i].x - sf[i + 1].x) * (sf[i].x - sf[i + 1].x) + (sf[i].y - sf[i + 1].y) * (sf[i].y - sf[i + 1].y)) < 2) {
            sfinfo[flag].sf_info.push_back(Point(sf[i].x, sf[i].y));
            cout << "(" << sf[i].x << "," << sf[i].y << ")" << endl;
        }
        else
        {
            //����ǰ�����ͺ�һ�������ڣ�����ǰһ�����ڣ��򽫵�ǰ�����洢��sfInfo
            if ((i > 0) && (sqrt((sf[i].x - sf[i - 1].x) * (sf[i].x - sf[i - 1].x) + (sf[i].y - sf[i - 1].y) * (sf[i].y - sf[i - 1].y)) < 2)) {
                sfinfo[flag].sf_info.push_back(Point(sf[i].x, sf[i].y));
                cout << "(" << sf[i].x << "," << sf[i].y << ")" << endl;
                cout << endl;
                flag++;
            }
        }
    }
    //��Ҫ�������һ�������
    if ((sqrt((sf[sf.size() - 1].x - sf[sf.size() - 2].x) * (sf[sf.size() - 1].x - sf[sf.size() - 2].x) + (sf[sf.size() - 1].y - sf[sf.size() - 2].y) * (sf[sf.size() - 1].y - sf[sf.size() - 2].y)) < 2)) {
        sfinfo[flag].sf_info.push_back(Point(sf[sf.size() - 1].x, sf[sf.size() - 1].y));
        cout << "(" << sf[sf.size() - 1].x << "," << sf[sf.size() - 1].y << ")" << endl;
    }

    //���㽻��������
    for (int i = 0; i <= flag; i++) {
        cout << endl;
        int Pc_x = 0;
        int Pc_y = 0;
        for (int j = 0; j < sfinfo[i].sf_info.size(); j++) {
            //cout << "(" << sfinfo[i].sf_info[j].x << "," << sfinfo[i].sf_info[j].y << ")" << endl;
            Pc_x += sfinfo[i].sf_info[j].x;
            Pc_y += sfinfo[i].sf_info[j].y;
        }
        sfinfo[i].Pc.x = Pc_x / sfinfo[i].sf_info.size();
        sfinfo[i].Pc.y = Pc_y / sfinfo[i].sf_info.size();

    }


    for (int i = 0; i <= flag; i++) {
        cout << endl;
        for (int j = 0; j < sfinfo[i].sf_info.size(); j++) {
            cout << "(" << sfinfo[i].sf_info[j].x << "," << sfinfo[i].sf_info[j].y << ")" << endl;
        }
        cout << "���������ģ�(" << sfinfo[i].Pc.x << "," << sfinfo[i].Pc.y << ")" << endl;
    }
}

//���������յ㣬���ط���ֵ|| �����������ۡ�Ϊ����5�������ۡ�Ϊ����6
int direction_combine(Point& start, Point& end, StrokesInfo* strokesinfo, double strokes_ave) {
    int zero = 0, one = 0, two = 0, three = 0;//����
    int x_plus = 0, x_sub = 0, y_plus = 0, y_sub = 0;//��������
    int flag = 0;//����ֵ
    int count = 0;//�ʻ�����
    Point cur, next;

    vector<int> x_Plus;//x�����򣬲��ƶ���0
    vector<int> x_Sub;//x�����򣬲��ƶ���0
    vector<int> y_Plus;//y�����򣬲��ƶ���0
    vector<int> y_Sub;//y�����򣬲��ƶ���0

    //���
    x_Plus.clear();
    x_Sub.clear();
    y_Plus.clear();
    y_Sub.clear();

    //������strokesinfo���ҷ���
    for (int flag_direction = 0; flag_direction < 20; flag_direction++) {
        if ((start.x == strokesinfo[flag_direction].begin.x && start.y == strokesinfo[flag_direction].begin.y)
            && (end.x == strokesinfo[flag_direction].end.x && end.y == strokesinfo[flag_direction].end.y)) {
            //flag = strokesinfo[flag_direction].dir;
            for (int flag_l = 0; flag_l < strokesinfo[flag_direction].snake_length; flag_l++) {
                //����0����ǰ��ͬһ�У���x���䣻��ǰ����һ�У�+y�ļ�������1��
                if (strokesinfo[flag_direction].snake[flag_l] == 0) {
                    y_plus++;
                    count++;
                    zero++;
                    //��Ӹ����ж�����
                    x_Plus.push_back(0);
                    x_Sub.push_back(0);
                    y_Plus.push_back(1);
                    y_Sub.push_back(0);
                }
                //����1����ǰ����һ�У�-x�ļ�������1����ǰ����һ�У�+y�ļ�������1��
                if (strokesinfo[flag_direction].snake[flag_l] == 1) {
                    x_sub++;
                    y_plus++;
                    count++;
                    one++;
                    //��Ӹ����ж�����
                    x_Plus.push_back(0);
                    x_Sub.push_back(1);
                    y_Plus.push_back(1);
                    y_Sub.push_back(0);
                }
                //����2����ǰ����һ�У�-x�ļ�������1����ǰ��ͬһ�У����䣻
                if (strokesinfo[flag_direction].snake[flag_l] == 2) {
                    x_sub++;
                    count++;
                    two++;
                    //��Ӹ����ж�����
                    x_Plus.push_back(0);
                    x_Sub.push_back(1);
                    y_Plus.push_back(0);
                    y_Sub.push_back(0);
                }
                //����3����ǰ����һ�У�-x�ļ�������1����ǰ����һ�У�-y�ļ�������1��
                if (strokesinfo[flag_direction].snake[flag_l] == 3) {
                    x_sub++;
                    y_sub++;
                    count++;
                    three++;
                    //��Ӹ����ж�����
                    x_Plus.push_back(0);
                    x_Sub.push_back(1);
                    y_Plus.push_back(0);
                    y_Sub.push_back(1);
                }
                //����4����ǰ��ͬһ�У���x���䣻��ǰ����һ�У�-y�ļ�������1��
                if (strokesinfo[flag_direction].snake[flag_l] == 4) {
                    y_sub++;
                    count++;
                    zero++;
                    //��Ӹ����ж�����
                    x_Plus.push_back(0);
                    x_Sub.push_back(0);
                    y_Plus.push_back(0);
                    y_Sub.push_back(1);
                }
                //����5����ǰ����һ�У�+x�ļ�������1����ǰ����һ�У�-y�ļ�������1��
                if (strokesinfo[flag_direction].snake[flag_l] == 5) {
                    x_plus++;
                    y_sub++;
                    count++;
                    one++;
                    //��Ӹ����ж�����
                    x_Plus.push_back(1);
                    x_Sub.push_back(0);
                    y_Plus.push_back(0);
                    y_Sub.push_back(1);
                }
                //����6����ǰ����һ�У�+x�ļ�������1����ǰ��ͬһ�У����䣻
                if (strokesinfo[flag_direction].snake[flag_l] == 6) {
                    x_plus++;
                    count++;
                    two++;
                    //��Ӹ����ж�����
                    x_Plus.push_back(1);
                    x_Sub.push_back(0);
                    y_Plus.push_back(0);
                    y_Sub.push_back(0);
                }
                //����7����ǰ����һ�У�+x�ļ�������1����ǰ����һ�У�+y�ļ�������1��
                if (strokesinfo[flag_direction].snake[flag_l] == 7) {
                    x_plus++;
                    y_plus++;
                    count++;
                    three++;
                    //��Ӹ����ж�����
                    x_Plus.push_back(1);
                    x_Sub.push_back(0);
                    y_Plus.push_back(1);
                    y_Sub.push_back(0);
                }
            }
            int flag_dir = 0;
            //���ĸ���������
            if (zero >= one)
            {
                flag_dir = 0;
                if (two >= zero) {
                    flag_dir = 2;
                    if (three >= two)flag_dir = 3;
                }
            }
            if (one >= zero) {
                flag_dir = 1;
                if (two >= one) {
                    flag_dir = 2;
                    if (three >= two)flag_dir = 3;
                }
            }
            flag = flag_dir;

            ////ͨ�������ʻ����֡���0���͡�����5��      
            //cout << "��������+x=" << x_plus << endl;
            //cout << "��������-x=" << x_sub << endl;
            //cout << "��������+y=" << y_plus << endl;
            //cout << "��������-y=" << y_sub << endl;
            //cout << "x_Plus===" << "";
            //for (int k = 0; k < x_Plus.size(); k++) {
            //    cout << x_Plus[k];
            //}
            //cout << endl;
            //cout << "x_Sub===" << "";
            //for (int k = 0; k < x_Sub.size(); k++) {
            //    cout << x_Sub[k];
            //}
            //cout << endl;
            //cout << "y_Plus===" << "";
            //for (int k = 0; k < y_Plus.size(); k++) {
            //    cout << y_Plus[k];
            //}
            //cout << endl;
            //cout << "y_Sub===" << "";
            //for (int k = 0; k < y_Sub.size(); k++) {
            //    cout << y_Sub[k];
            //}
            //cout << endl;
            //cout << "=======count:�ʻ�����===========" << count << endl;

            if (count > strokes_ave) {
                //�ж� + x��������
                int x_Plus_count_before0 = 0;//�жϱ�־��+x��������ǰ��λ���Ϊ0
                int x_Plus_count_after0 = 0;//�жϱ�־��+x��������ǰ��λ���Ϊ0

                int x_Plus_count_before1 = 0;//�жϱ�־��+x��������ǰ��λ���Ϊ1
                int x_Plus_count_after1 = 0;//�жϱ�־��+x����������λ���Ϊ1

                int x_Plus_flag = 0;//�жϱ�־
                for (int g = 0; g < x_Plus.size() / 2; g++) {
                    if (x_Plus[g] == 0) {
                        x_Plus_count_before0++;
                    }
                    if (x_Plus[g] == 1) {
                        x_Plus_count_before1++;
                    }
                }
                for (int g = x_Plus.size() / 2; g < x_Plus.size(); g++) {
                    if (x_Plus[g] == 1) {
                        x_Plus_count_after1++;
                    }
                    if (x_Plus[g] == 0) {
                        x_Plus_count_after0++;
                    }
                }

                //cout << "x_Plus_count_before0=" << x_Plus_count_before0 << endl;
                //cout << "x_Plus_count_after1=" << x_Plus_count_after1 << endl;
                //cout << "count * 0.4 * 0.5=" << count * 0.4 * 0.5 << endl;
                if ((x_Plus_count_before0 >= count * 0.4 * 0.5) && (x_Plus_count_after1 >= count * 0.4 * 0.5)) {
                    x_Plus_flag = 1;//��ʾ���۵�һ���ֳ���
                }
                if ((x_Plus_count_before1 >= count * 0.4 * 0.5) && (x_Plus_count_after0 >= count * 0.4 * 0.5)) {
                    x_Plus_flag = 2;//��ʾ���۵�һ���ֳ���
                }
                //�ж� +y ��������
                int y_Plus_count_before0 = 0;//�ж�+y��������ǰ��λ���Ϊ0
                int y_Plus_count_before1 = 0;//�ж�+y��������ǰ��λ���Ϊ1
                int y_Plus_count_after0 = 0;//�ж�+y����������λ���Ϊ0
                int y_Plus_count_after1 = 0;//�ж�+y����������λ���Ϊ1
                int y_Plus_flag = 0;//�жϱ�־

                for (int g = 0; g < y_Plus.size() / 2; g++) {
                    if (y_Plus[g] == 1) {
                        y_Plus_count_before1++;
                    }
                    if (y_Plus[g] == 0) {
                        y_Plus_count_before0++;
                    }
                }
                for (int g = y_Plus.size() / 2; g < y_Plus.size(); g++) {
                    if (y_Plus[g] == 0) {
                        y_Plus_count_after0++;
                    }
                    if (y_Plus[g] == 1) {
                        y_Plus_count_after1++;
                    }
                }
                //cout << "y_Plus_count_before1=" << y_Plus_count_before1 << endl;
                //cout << "y_Plus_count_after0=" << y_Plus_count_after0 << endl;
                //cout << "count * 0.4 * 0.5=" << count * 0.4 * 0.5 << endl;

                if ((y_Plus_count_before1 >= count * 0.4 * 0.5) && (y_Plus_count_after0 >= count * 0.4 * 0.5)) {
                    y_Plus_flag = 1;
                }
                if ((y_Plus_count_before0 >= count * 0.4 * 0.5) && (y_Plus_count_after1 >= count * 0.4 * 0.5)) {
                    y_Plus_flag = 2;
                }

                //���۱ʻ�==5
                if ((x_Plus_flag == 1) && (y_Plus_flag == 1)) {
                    flag = 5;
                    cout << "�����޸�Ϊ5" << endl;
                    cout << endl;
                }

                //���۱ʻ�==6
                if ((x_Plus_flag == 2) && (y_Plus_flag == 2)) {
                    flag = 6;
                    cout << "�����޸�Ϊ6" << endl;
                    cout << endl;
                }
            }
        }
    }
    return flag;
}

//���Ǽܱʻ��洢���ṹ������strokesinfo (1026���ӣ��ʻ�����Ϊ0�Ŀ�����Ҫ������ʼ��)
void Save_strokesinfo(int num, vector<Point>& newpoint_mark, vector<Point>& newpoint, StrokesInfo* strokesinfo, double strokes_ave) {

    //��ʼ���ṹ������strokesinfo
    for (int index = 0; index < 20; index++)
    {
        strokesinfo[index].begin.x = strokesinfo[index].begin.y = 0;
        strokesinfo[index].end.x = strokesinfo[index].end.y = 0;
        strokesinfo[index].snake_length = 0;
        strokesinfo[index].snake.clear();
        strokesinfo[index].dir = 0;
        strokesinfo[index].tem.clear();
        strokesinfo[index].num = 0;//�洢�����ڳ�Ա����
        strokesinfo[index].com_mark = 0;//�ϲ��ʻ����
        strokesinfo[index].com_mark_max = 0;//���com_mark�����ֵ
    }
    //�洢��ʼ�㡢��ֹ��
    int flag = 0;
    for (size_t i = 0; i < newpoint_mark.size(); i++) {
        if (i % 2 == 0) {
            strokesinfo[flag].begin.x = newpoint_mark[i].x;
            strokesinfo[flag].begin.y = newpoint_mark[i].y;
            strokesinfo[flag].end.x = newpoint_mark[i + 1].x;
            strokesinfo[flag].end.y = newpoint_mark[i + 1].y;
            flag++;
        }
    }

    //�洢8��������
    int flag_b = -1;//���λ��
    int length = 0;//8���볤��

    for (int index = 0; index < num; index++)
    {

        strokesinfo[index].snake_length = 0;
        strokesinfo[index].com_mark = 0;//�ϲ��ʻ���ǳ�ʼ��0
        for (size_t j = flag_b + length + 1; j < newpoint.size(); j++) {
            int mark = 0;
            int zero = 0, one = 0, two = 0, three = 0;//��������

            if (strokesinfo[index].begin.x == newpoint[j].x && strokesinfo[index].begin.y == newpoint[j].y) {
                //�洢��ʼ�㣺
               /* cout << "��ʼ�㣺(" << strokesinfo[index].begin.x << "," << strokesinfo[index].begin.y << ")" << endl;
                cout << "��ʼ��ĺ�һ����Ϊ��(" << newpoint[j+1].x << "," << newpoint[j + 1].y << ")" << endl;
                cout << "index=" << index << endl;
                cout << "num=" << num << endl;*/
                strokesinfo[index].tem.push_back(newpoint[j]);
                flag_b = j;
                //cout << "flag_b=" << flag_b << endl;
                mark = 1;
                length = 0;
            }
            if (mark == 1) {
                for (size_t i = flag_b + 1; i < newpoint.size(); i++) {
                    cout << "newpoint[]===��(" << newpoint[i].x << "," << newpoint[i].y << ")" << endl;
                    //�洢���ص�
                    strokesinfo[index].tem.push_back(newpoint[i]);
                    //ͨ����һ����͵�ǰ��Ƚϣ��жϷ���
                    if (newpoint[i].x - newpoint[i - 1].x == 0 && newpoint[i].y - newpoint[i - 1].y == 1) {
                        strokesinfo[index].snake.push_back(0);
                        strokesinfo[index].snake_length++;
                    }
                    if (newpoint[i].x - newpoint[i - 1].x == -1 && newpoint[i].y - newpoint[i - 1].y == 1) {
                        strokesinfo[index].snake.push_back(1);
                        strokesinfo[index].snake_length++;
                    }
                    if (newpoint[i].x - newpoint[i - 1].x == -1 && newpoint[i].y - newpoint[i - 1].y == 0) {
                        strokesinfo[index].snake.push_back(2);
                        strokesinfo[index].snake_length++;
                    }
                    if (newpoint[i].x - newpoint[i - 1].x == -1 && newpoint[i].y - newpoint[i - 1].y == -1) {
                        strokesinfo[index].snake.push_back(3);
                        strokesinfo[index].snake_length++;
                    }
                    if (newpoint[i].x - newpoint[i - 1].x == 0 && newpoint[i].y - newpoint[i - 1].y == -1) {
                        strokesinfo[index].snake.push_back(4);
                        strokesinfo[index].snake_length++;
                    }
                    if (newpoint[i].x - newpoint[i - 1].x == 1 && newpoint[i].y - newpoint[i - 1].y == -1) {
                        strokesinfo[index].snake.push_back(5);
                        strokesinfo[index].snake_length++;
                    }
                    if (newpoint[i].x - newpoint[i - 1].x == 1 && newpoint[i].y - newpoint[i - 1].y == 0) {
                        strokesinfo[index].snake.push_back(6);
                        strokesinfo[index].snake_length++;
                    }
                    if (newpoint[i].x - newpoint[i - 1].x == 1 && newpoint[i].y - newpoint[i - 1].y == 1) {
                        strokesinfo[index].snake.push_back(7);
                        strokesinfo[index].snake_length++;
                    }

                    if (strokesinfo[index].end.x == newpoint[i].x && strokesinfo[index].end.y == newpoint[i].y) {
                        cout << "��ֹ�㣺(" << strokesinfo[index].end.x << "," << strokesinfo[index].end.y << ")" << endl;
                        length = strokesinfo[index].snake_length;
                        break;
                    }
                }

                if (length != 0) {
                    break;
                }
            }
        }
    }
    //�洢�����ڳ�Ա����
    strokesinfo[0].num = num;

    //�ʻ�����
    for (int index = 0; index < num; index++) {
        int flag = direction_combine(strokesinfo[index].begin, strokesinfo[index].end, strokesinfo, strokes_ave);
        strokesinfo[index].dir = flag;
    }
    //(1026���ӣ��ʻ�����Ϊ0�Ŀ�����Ҫ������ʼ��)
    for (int index = 0; index < num; index++) {
        if (strokesinfo[index].dir == 0) {
            //cout << "strokesinfo[index].dir == 0" << endl;
            if (strokesinfo[index].begin.y > strokesinfo[index].end.y) {
                //��ʼ�㷴����
                //cout<< "strokesinfo[index].begin.y > strokesinfo[index].end.y" << endl;
                Point begin_ver = strokesinfo[index].begin;
                Point end_ver = strokesinfo[index].end;
                strokesinfo[index].begin = end_ver;
                strokesinfo[index].end = begin_ver;
                /* cout << "begin==(" << strokesinfo[index].begin.x << "," << strokesinfo[index].begin.y << ")" << endl;
                 cout << "end==(" << strokesinfo[index].end.x << "," << strokesinfo[index].end.y << ")" << endl;*/
                 //��������������
                vector<int> snake_ver;
                for (int i = strokesinfo[index].snake_length - 1; i >= 0; i--) {
                    snake_ver.push_back((strokesinfo[index].snake[i] + 4) % 8);
                }
                strokesinfo[index].snake.clear();
                for (int i = 0; i < snake_ver.size(); i++) {
                    strokesinfo[index].snake.push_back(snake_ver[i]);
                    //cout << snake_ver[i];
                }
                //���ص�����������
                vector<Point> tem_ver;
                for (int i = strokesinfo[index].snake_length; i >= 0; i--) {
                    tem_ver.push_back(strokesinfo[index].tem[i]);
                }
                strokesinfo[index].tem.clear();
                for (int i = 0; i < tem_ver.size(); i++) {
                    strokesinfo[index].tem.push_back(tem_ver[i]);
                }
            }
        }
    }

    cout << " ���Ǽܱʻ��洢���ṹ������ " << endl;
    for (int index = 0; index < num; index++)
    {
        cout << endl;
        cout << "begin==(" << strokesinfo[index].begin.x << "," << strokesinfo[index].begin.y << ")" << endl;
        cout << "end==(" << strokesinfo[index].end.x << "," << strokesinfo[index].end.y << ")" << endl;
        cout << "�洢8�������г���==" << strokesinfo[index].snake_length << endl;
        for (int i = 0; i < strokesinfo[index].snake_length; i++) {
            cout << strokesinfo[index].snake[i];
        }
        cout << "�ʻ�����==" << strokesinfo[index].dir << endl;
        cout << "�ʻ����ص㣺" << endl;
        for (int i = 0; i <= strokesinfo[index].snake_length; i++) {
            cout << "(" << strokesinfo[index].tem[i].x << "," << strokesinfo[index].tem[i].y << ") ";
        }
        cout << endl;
    }
}

//3.3����ʻ����,��Ҫ�ʻ����ص������ͻҶ�ͼ��
int width_new(Point& center, Mat& image, int uw) {
    //��centerΪ���ģ�����ĸ�����
    Point mark1, mark2, mark3, mark4;
    //cout << "center��:(" << center.x << "," << center.y << ")" << endl;
    int shortdis = 100;//��̾���

    for (int i = 0; i < 5 * uw; i++) {//Ȧ��
        mark1.x = center.x - i;
        mark1.y = center.y + i;
        int color1 = image.at<uchar>(mark1.x, mark1.y);
        mark2.x = center.x - i;
        mark2.y = center.y - i;
        int color2 = image.at<uchar>(mark2.x, mark2.y);
        mark3.x = center.x + i;
        mark3.y = center.y - i;
        int color3 = image.at<uchar>(mark3.x, mark3.y);
        mark4.x = center.x + i;
        mark4.y = center.y + i;
        int color4 = image.at<uchar>(mark4.x, mark4.y);

        if (color1 == 255 || color2 == 255 || color3 == 255 || color4 == 255) {
            shortdis = i;
            //cout << "shortdis=:" << shortdis << endl;
            break;
        }
    }
    return shortdis;
}

//����ʻ��γ��Ⱦ�ֵ����׼���λ��
void ave(StrokesInfo* strokesinfo, double strokes_ave, double variance, double* Median) {
    //��8�������еľ�ֵ������
    int sum = 0, num = 0;
    vector <int> maopao;//ð����������
    for (int i = 0; i < 20; i++) {
        if (strokesinfo[i].snake.size() != 0) {
            sum += strokesinfo[i].snake.size();
            maopao.push_back(strokesinfo[i].snake.size());
            num++;
        }
    }
    double ave;
    ave = sum * 1.0 / num;
    strokes_ave = ave;
    for (int i = 0; i < num; i++)
    {
        variance += pow((strokesinfo[i].snake.size() - ave), 2);
    }
    double variance1 = variance / num;
    variance = variance1;
    //����λ��
    for (int i = 0; i < num - 1; ++i) {
        for (int j = i + 1; j < num; ++j) {
            if (maopao[i] > maopao[j]) {
                swap(maopao[i], maopao[j]);
            }
        }
    }
    *Median = maopao[num / 2];
    cout << "��ֵ========" << ave << endl;
    cout << "����===================" << variance1 << endl;
    cout << "��׼��===================" << sqrt(variance1) << endl;
    cout << "��λ��===================" << Median << endl;
    cout << endl;
}

//��ȡ�Ǽܱʻ�{��ע��}
void craw_stroke(Mat& image, vector<Point>& se, vector<Point>& sf,
    vector<Point>& s, vector<Point>& sef, vector<Point>& newpoint_mark, vector<Point>& newpoint, vector<int>& dir) {
    Mat image1 = image.clone();//11.27���£�image1���ڹ�ȥ�ʻ��ĸ����㷨
    Point tem, cur, p, q, front;

    int flag = 0;
    int count = 0;
    //�Ӷ˵�򽻲�����,�ҳ���ǰ���8��������һ����ķ���
    for (size_t i = 0; i < sef.size(); i++)
    {
        tem = sef[i];
        q.y = cur.y = tem.y;//��ʼ����
        q.x = cur.x = tem.x;
        cout << endl;
        cout << "Ԥ����ʼ��" << "(" << tem.x << "," << tem.y << ")" << endl;
        newpoint_mark.push_back(Point(tem.x, tem.y));//�����
        flag = 0;
        int flag1 = 0;
        count = 0;
        while (flag == 0) {
            //����cur��ֵ
            cur.y = q.y;
            cur.x = q.x;

            if (image.at<uchar>(cur.x, cur.y) == 0) {//�жϵ�ǰ��û�б�ǣ��������Ϊ255��û�б����Ϊ0

                if (flag == 0 && (image.at<uchar>(cur.x, cur.y + 1) == 0)) {//0�����ھӵ�Ϊ�ڵ�

                    newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                    image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                    cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y + 1;//�����Ҹ���
                    q.x = cur.x;
                    cout << 0;
                    dir.push_back(0);

                    //�ж���һ�����Ƿ��Ƕ˵㡢�����
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//��һ�����Ƕ˵㡢�����
                        cout << "��ֹ�㣺" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//��¼��ÿһ�θ��µ�����
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //�жϵ�ǰ���Ƿ��ǽ���㣬����ǵĻ�������Ҫ�洢����
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "���洢" << endl;

                                cout << "count=" << count << endl;
                                cout << endl;
                                if (count == 8) {
                                    flag = 1;
                                    count = 0;
                                }
                                count++;
                                cout << "flag=" << flag << endl;

                            }
                        }
                        dir.push_back(-1);

                        //�жϵ�ǰ���Ƿ��Ƕ˵㣬����ǵĻ�������ѭ��
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //��cur�����Ϊ��ʼ�㣬������ʱ�����·��
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "��ʼ��" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//�����
                        if (flag == 1) {
                            cout << "count == 1���洢" << endl;
                            newpoint_mark.pop_back();
                        }
                    }

                    if (flag1 == 0) {//��һ��������ͨ��
                        //����cur��ֵ
                        cur.y = q.y;
                        cur.x = q.x;
                    }
                }
                if (flag == 0 && (image.at<uchar>(cur.x - 1, cur.y + 1) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                    image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                    cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y + 1;//����1����
                    q.x = cur.x - 1;
                    cout << 1;
                    dir.push_back(1);

                    //�ж���һ�����Ƿ��Ƕ˵㡢�����
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//��һ�����Ƕ˵㡢�����

                        cout << "��ֹ�㣺" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//��¼��ÿһ�θ��µ�����
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //�жϵ�ǰ���Ƿ��ǽ���㣬����ǵĻ�������Ҫ�洢����
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "���洢" << endl;

                                cout << "count=" << count << endl;
                                cout << endl;
                                if (count == 8) {
                                    flag = 1;
                                    count = 0;
                                }
                                count++;
                                cout << "flag=" << flag << endl;

                            }
                        }
                        dir.push_back(-1);

                        //�жϵ�ǰ���Ƿ��Ƕ˵㣬����ǵĻ�������ѭ��
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //��cur�����Ϊ��ʼ�㣬������ʱ�����·��
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "��ʼ��" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//�����
                        if (flag == 1) {
                            cout << "flag == 1���洢" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//��һ��������ͨ��
                        //����cur��ֵ
                        cur.y = q.y;
                        cur.x = q.x;
                    }


                }
                if (flag == 0 && (image.at<uchar>(cur.x - 1, cur.y) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                    image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                    cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y;//��2����
                    q.x = cur.x - 1;
                    cout << 2;
                    dir.push_back(2);

                    //�ж���һ�����Ƿ��Ƕ˵㡢�����
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//��һ�����Ƕ˵㡢�����

                        cout << "��ֹ�㣺" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//��¼��ÿһ�θ��µ�����
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //�жϵ�ǰ���Ƿ��ǽ���㣬����ǵĻ�������Ҫ�洢����
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "���洢" << endl;

                                cout << "count=" << count << endl;
                                cout << endl;
                                if (count == 8) {
                                    flag = 1;
                                    count = 0;
                                }
                                count++;
                                cout << "flag=" << flag << endl;

                            }
                        }
                        dir.push_back(-1);

                        //�жϵ�ǰ���Ƿ��Ƕ˵㣬����ǵĻ�������ѭ��
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //��cur�����Ϊ��ʼ�㣬������ʱ�����·��
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "��ʼ��" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//�����
                        if (flag == 1) {
                            cout << "flag == 1���洢" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//��һ��������ͨ��
                        //����cur��ֵ
                        cur.y = q.y;
                        cur.x = q.x;
                    }

                }
                if (flag == 0 && (image.at<uchar>(cur.x - 1, cur.y - 1) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                    image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                    cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y - 1;//����3����
                    q.x = cur.x - 1;
                    cout << 3;
                    dir.push_back(3);

                    //�ж���һ�����Ƿ��Ƕ˵㡢�����
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//��һ�����Ƕ˵㡢�����

                        cout << "��ֹ�㣺" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//��¼��ÿһ�θ��µ�����
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //�жϵ�ǰ���Ƿ��ǽ���㣬����ǵĻ�������Ҫ�洢����
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "���洢" << endl;

                                cout << "count=" << count << endl;
                                cout << endl;
                                if (count == 8) {
                                    flag = 1;
                                    count = 0;
                                }
                                count++;
                                cout << "flag=" << flag << endl;

                            }
                        }
                        dir.push_back(-1);


                        //�жϵ�ǰ���Ƿ��Ƕ˵㣬����ǵĻ�������ѭ��
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }
                        //��cur�����Ϊ��ʼ�㣬������ʱ�����·��
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "��ʼ��" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//�����
                        if (flag == 1) {
                            cout << "flag == 1���洢" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//��һ��������ͨ��
                        //����cur��ֵ
                        cur.y = q.y;
                        cur.x = q.x;
                    }


                }
                if (flag == 0 && (image.at<uchar>(cur.x, cur.y - 1) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                    image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                    cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y - 1;//����4����
                    q.x = cur.x;
                    cout << 4;
                    dir.push_back(4);

                    //�ж���һ�����Ƿ��Ƕ˵㡢�����
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//��һ�����Ƕ˵㡢�����

                        cout << "��ֹ�㣺" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//��¼��ÿһ�θ��µ�����
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //�жϵ�ǰ���Ƿ��ǽ���㣬����ǵĻ�������Ҫ�洢����
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "���洢" << endl;

                                cout << "count=" << count << endl;
                                cout << endl;
                                if (count == 8) {
                                    flag = 1;
                                    count = 0;
                                }
                                count++;
                                cout << "flag=" << flag << endl;

                            }
                        }
                        dir.push_back(-1);

                        //�жϵ�ǰ���Ƿ��Ƕ˵㣬����ǵĻ�������ѭ��
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //��cur�����Ϊ��ʼ�㣬������ʱ�����·��
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "��ʼ��" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//�����
                        if (flag == 1) {
                            cout << "flag == 1���洢" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//��һ��������ͨ��
                        //����cur��ֵ
                        cur.y = q.y;
                        cur.x = q.x;
                    }

                }
                if (flag == 0 && (image.at<uchar>(cur.x + 1, cur.y - 1) == 0)) {
                    newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                    image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                    cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;


                    q.y = cur.y - 1;//����5����
                    q.x = cur.x + 1;
                    cout << 5;
                    dir.push_back(5);

                    //�ж���һ�����Ƿ��Ƕ˵㡢�����
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//��һ�����Ƕ˵㡢�����

                        cout << "��ֹ�㣺" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//��¼��ÿһ�θ��µ�����
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //�жϵ�ǰ���Ƿ��ǽ���㣬����ǵĻ�������Ҫ�洢����
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "���洢" << endl;

                                cout << "count=" << count << endl;
                                cout << endl;
                                if (count == 8) {
                                    flag = 1;
                                    count = 0;
                                }
                                count++;
                                cout << "flag=" << flag << endl;

                            }
                        }
                        dir.push_back(-1);

                        //�жϵ�ǰ���Ƿ��Ƕ˵㣬����ǵĻ�������ѭ��
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //��cur�����Ϊ��ʼ�㣬������ʱ�����·��
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "��ʼ��" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//�����
                        if (flag == 1) {

                            cout << "flag == 1���洢" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//��һ��������ͨ��
                        //����cur��ֵ
                        cur.y = q.y;
                        cur.x = q.x;
                    }

                }
                if (flag == 0 && (image.at<uchar>(cur.x + 1, cur.y) == 0)) {
                    newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����

                    image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                    cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;


                    q.y = cur.y;//����6����
                    q.x = cur.x + 1;
                    cout << 6;
                    dir.push_back(6);


                    //�ж���һ�����Ƿ��Ƕ˵㡢�����
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//��һ�����Ƕ˵㡢�����

                        cout << "��ֹ�㣺" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//��¼��ÿһ�θ��µ�����
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //�жϵ�ǰ���Ƿ��ǽ���㣬����ǵĻ�������Ҫ�洢����
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "���洢" << endl;

                                cout << "count=" << count << endl;
                                cout << endl;
                                if (count == 8) {
                                    flag = 1;
                                    count = 0;
                                }
                                count++;
                                cout << "flag=" << flag << endl;

                            }
                        }
                        dir.push_back(-1);

                        //�жϵ�ǰ���Ƿ��Ƕ˵㣬����ǵĻ�������ѭ��
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //��cur�����Ϊ��ʼ�㣬������ʱ�����·��
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "��ʼ��" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//�����
                        if (flag == 1) {
                            cout << "flag == 1���洢" << endl;
                            newpoint_mark.pop_back();
                        }
                    }

                    if (flag1 == 0) {//��һ��������ͨ��
                        //����cur��ֵ
                        cur.y = q.y;
                        cur.x = q.x;
                    }

                }
                if (flag == 0 && (image.at<uchar>(cur.x + 1, cur.y + 1) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                    image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                    cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y + 1;//����7����
                    q.x = cur.x + 1;
                    cout << 7;
                    dir.push_back(7);

                    //�ж���һ�����Ƿ��Ƕ˵㡢�����
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//��һ�����Ƕ˵㡢�����

                        cout << "��ֹ�㣺" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//��¼��ÿһ�θ��µ�����
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //�жϵ�ǰ���Ƿ��ǽ���㣬����ǵĻ�������Ҫ�洢����
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "���洢" << endl;

                                cout << "count=" << count << endl;
                                cout << endl;
                                if (count == 8) {
                                    flag = 1;
                                    count = 0;
                                }
                                count++;
                                cout << "flag=" << flag << endl;


                            }
                        }
                        dir.push_back(-1);

                        //�жϵ�ǰ���Ƿ��Ƕ˵㣬����ǵĻ�������ѭ��
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //��cur�����Ϊ��ʼ�㣬������ʱ�����·��
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "��ʼ��" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//�����
                        if (flag == 1) {
                            cout << "flag == 1���洢" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//��һ��������ͨ��
                        //����cur��ֵ
                        cur.y = q.y;
                        cur.x = q.x;
                    }


                }

                //��ǰ��Ϊ������
                if ((image.at<uchar>(cur.x, cur.y) == 0
                    && image.at<uchar>(cur.x - 1, cur.y + 1) == 255)
                    && (image.at<uchar>(cur.x - 1, cur.y) == 255)
                    && (image.at<uchar>(cur.x - 1, cur.y - 1) == 255)
                    && (image.at<uchar>(cur.x, cur.y - 1) == 255)
                    && (image.at<uchar>(cur.x + 1, cur.y - 1) == 255)
                    && (image.at<uchar>(cur.x + 1, cur.y) == 255)
                    && (image.at<uchar>(cur.x + 1, cur.y + 1) == 255)
                    && (image.at<uchar>(cur.x, cur.y + 1) == 255)) {

                    cout << "������Ϊ" << "(" << cur.x << "," << cur.y << ")" << endl;
                    cout << "���洢" << endl;
                    cout << endl;
                    flag = 1;
                    newpoint.pop_back();
                    newpoint_mark.pop_back();
                }

            }
            else {//����Ϊ������
                flag = 1;
                dir.push_back(-1);
                cout << "ȥ����ʼ��" << "(" << cur.x << "," << cur.y << ")" << endl;
                newpoint.pop_back();
                newpoint_mark.pop_back();
                cout << "���洢" << endl;
                cout << endl;
            }

        }
    }

    //cout << "�ʻ����ص�" << endl;;
    //for (size_t i = 0; i < newpoint.size(); i++)
    //{
    //    Point tems;
    //    tems = newpoint[i];
    //    for (size_t j = 0; j < newpoint_mark.size(); j++)
    //    {
    //        Point tem;
    //        tem = newpoint_mark[j];
    //        if (tems.x == tem.x && tems.y == tem.y && j % 2 == 0) {
    //            cout << endl;
    //            cout << endl;
    //        }
    //    }
    //    cout << "(" << tems.x << "," << tems.y << ")";
    //}
    cout << endl;
    cout << "�ʻ���ʼ��" << endl;
    for (size_t j = 0; j < newpoint_mark.size(); j++)
    {
        cout << "(" << newpoint_mark[j].x << "," << newpoint_mark[j].y << ")" << endl;
    }
    cout << endl;
    cout << endl;
    //cout << "�ʻ�newpoint��" << endl;
    //for (size_t j = 0; j < newpoint.size(); j++)
    //{
    //    cout << "(" << newpoint[j].x << "," << newpoint[j].y << ")" << endl;
    //}
}

//��ȡ�Ǽܱʻ� 11.27������ʹ����ȷ��newpoint_mark���������newpoint
void craw_stroke_new(Mat& image, vector<Point>& se, vector<Point>& sf,vector<Point>& s1,
    vector<Point>& s, vector<Point>& sef, vector<Point>& newpoint_mark, vector<Point>& newpoint, vector<int>& dir, StrokesInfo* strokesinfo, double strokes_ave) {
    Point cur;//��ǰ��
    Point start;//�ʻ����
    Point end;//�ʻ��յ�
    Point q;
    newpoint.clear();
    for (size_t i = 0; i < newpoint_mark.size(); i++)
    {
        if (i % 2 == 0) {

            start = newpoint_mark[i];
            end = newpoint_mark[i + 1];
            q.y = cur.y = start.y;//��ʼ����
            q.x = cur.x = start.x;
            cout << "��ʼ���㣺(" << cur.x << "," << cur.y << ")" << endl;
            int flag_sf = 0;//�ж��ھӵ��Ƿ�Ϊ�����
            int flag_end = 0;//�ж���һ�����Ƿ�����ֹ��
            int flag_if = 0;//�ж���һ��������Ҫ�㣬������if
            while (flag_end == 0) {

                if (flag_if == 0 && (image.at<uchar>(cur.x, cur.y + 1) == 0)) {//0�����ھӵ�Ϊ�ڵ�
                    //0�����ھӵ����ڽ����
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x == sf[j].x && cur.y + 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //��ǰ�����Ϊ��ֹ��
                        if (cur.x == end.x && cur.y + 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    //0�����ھӵ㲻���ڽ����
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                        image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y + 1;//�����Ҹ���
                        q.x = cur.x;
                        cout << 0;
                        flag_if = 1;//���������if
                        //�ж���һ��������ֹ��
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//��¼�յ�
                        }
                        if (flag_end == 0) {
                            //��һ���㲻����ֹ��,�����cur��ֵ
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0�Ļ�����������ж�
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x - 1, cur.y + 1) == 0)) {//1�����ھӵ�Ϊ�ڵ�
                    //1�����ھӵ㲻���ڽ����
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x - 1 == sf[j].x && cur.y + 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //��ǰ�����Ϊ��ֹ��
                        if (cur.x - 1 == end.x && cur.y + 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                        image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y + 1;//����1�������
                        q.x = cur.x - 1;
                        cout << 1;
                        flag_if = 1;//���������if
                        //�ж���һ�����Ƿ�����ֹ��
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//��¼�յ�
                        }
                        if (flag_end == 0) {
                            //��һ���㲻����ֹ��,�����cur��ֵ
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0�Ļ�����������ж�
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x - 1, cur.y) == 0)) {
                    //2�����ھӵ㲻���ڽ����
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x - 1 == sf[j].x && cur.y == sf[j].y) {
                            flag_sf = 1;
                        }
                        //��ǰ�����Ϊ��ֹ��
                        if (cur.x - 1 == end.x && cur.y == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                        image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y;//����2�������
                        q.x = cur.x - 1;
                        cout << 2;
                        flag_if = 1;//���������if
                        //�ж���һ�����Ƿ�����ֹ��
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//��¼�յ�
                        }
                        if (flag_end == 0) {
                            //��һ���㲻����ֹ��,�����cur��ֵ
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0�Ļ�����������ж�
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x - 1, cur.y - 1) == 0)) {
                    //3�����ھӵ㲻���ڽ����
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x - 1 == sf[j].x && cur.y - 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //��ǰ�����Ϊ��ֹ��
                        if (cur.x - 1 == end.x && cur.y - 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                        image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y - 1;//����3�������
                        q.x = cur.x - 1;
                        cout << 3;
                        flag_if = 1;//���������if
                        //�ж���һ�����Ƿ�����ֹ��
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//��¼�յ�
                        }
                        if (flag_end == 0) {
                            //��һ���㲻����ֹ��,�����cur��ֵ
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0�Ļ�����������ж�
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x, cur.y - 1) == 0)) {
                    //4�����ھӵ㲻���ڽ����
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x == sf[j].x && cur.y - 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //��ǰ�����Ϊ��ֹ��
                        if (cur.x == end.x && cur.y - 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                        image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y - 1;//����4�������
                        q.x = cur.x;
                        cout << 4;
                        flag_if = 1;//���������if

                        //�ж���һ�����Ƿ�����ֹ��
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//��¼�յ�
                        }
                        if (flag_end == 0) {
                            //��һ���㲻����ֹ��,�����cur��ֵ
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0�Ļ�����������ж�
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x + 1, cur.y - 1) == 0)) {
                    //5�����ھӵ㲻���ڽ����
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x + 1 == sf[j].x && cur.y - 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //��ǰ�����Ϊ��ֹ��
                        if (cur.x + 1 == end.x && cur.y - 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                        image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y - 1;//����5�������
                        q.x = cur.x + 1;
                        cout << 5;
                        flag_if = 1;//���������if
                        //�ж���һ�����Ƿ�����ֹ��
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//��¼�յ�
                        }
                        if (flag_end == 0) {
                            //��һ���㲻����ֹ��,�����cur��ֵ
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0�Ļ�����������ж�
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x + 1, cur.y) == 0)) {
                    //6�����ھӵ����ڽ����
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x + 1 == sf[j].x && cur.y == sf[j].y) {
                            flag_sf = 1;
                        }
                        //��ǰ�����Ϊ��ֹ��
                        if (cur.x + 1 == end.x && cur.y == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                        image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y;//����6�������
                        q.x = cur.x + 1;
                        cout << 6;
                        flag_if = 1;//���������if
                        //�ж���һ�����Ƿ�����ֹ��
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//��¼�յ�
                        }
                        if (flag_end == 0) {
                            //��һ���㲻����ֹ��,�����cur��ֵ
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0�Ļ�����������ж�
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x + 1, cur.y + 1) == 0)) {
                    //7�����ھӵ����ڽ����
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x + 1 == sf[j].x && cur.y + 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //��ǰ�����Ϊ��ֹ��
                        if (cur.x + 1 == end.x && cur.y + 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//��¼��ǰ����
                        image.at<uchar>(cur.x, cur.y) = 255;//����Ѿ��������˵�cur�㣻��ɰ׵�255
                        cout << "���ʣ�(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y + 1;//����7�������
                        q.x = cur.x + 1;
                        cout << 7;
                        flag_if = 1;//���������if
                        //�ж���һ�����Ƿ�����ֹ��
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//��¼�յ�
                        }
                        if (flag_end == 0) {
                            //��һ���㲻����ֹ��,�����cur��ֵ
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0�Ļ�����������ж�
                }

                //�Ե�ǰ��ѭ����һ��֮�󣬿϶��ҵ�����һ��������꣬����Ҫ��flag_if��0
                flag_if = 0;
            }

        }
    }
    cout << "�ʻ����ص�" << endl;
    for (size_t i = 0; i < newpoint.size(); i++)
    {
        Point tems;
        tems = newpoint[i];
        for (size_t j = 0; j < newpoint_mark.size(); j++)
        {
            Point tem;
            tem = newpoint_mark[j];
            if (tems.x == tem.x && tems.y == tem.y && j % 2 == 0) {
                cout << endl;
                cout << endl;
            }
        }
        cout << "(" << tems.x << "," << tems.y << ")";
    }
    cout << endl;

    Save_strokesinfo(newpoint_mark.size() / 2, newpoint_mark, newpoint,strokesinfo,  strokes_ave);
}

//����δ�ϲ��ʻ�֮ǰ�Ĳ�ͼ
Mat draw_picture(Mat& image, vector<Point>& s1, StrokesInfo* strokesinfo) {

    int a = 1;
    int b = 1;
    int c = 1;
    //����ת��Ϊ��ɫͼ��
    Mat draw = channelSwitching(image);
    //�½��׵�ͼ��
    for (int i = 0; i < draw.rows; i++)
    {
        for (int j = 0; j < draw.cols; j++)
        {

            draw.at<Vec3b>(i, j)[0] = 255;
            draw.at<Vec3b>(i, j)[1] = 255;
            draw.at<Vec3b>(i, j)[2] = 255;
        }
    }

    //������ֵ���ҵ�
    for (size_t i = 0; i < s1.size(); i++)
    {
        Point tems;
        tems = s1[i];
        draw.at<Vec3b>(tems.x, tems.y)[0] = 200;
        draw.at<Vec3b>(tems.x, tems.y)[1] = 200;
        draw.at<Vec3b>(tems.x, tems.y)[2] = 200;
    }

    //����δ�ϲ��ʻ�֮ǰ�Ĳ�ͼ
    //for (size_t i = 0; i < newpoint.size(); i++)
    //{
    //    Point tems;
    //    tems = newpoint[i];
    //    for (size_t j = 0; j < newpoint_mark.size(); j++)
    //    {
    //        Point tem;
    //        tem = newpoint_mark[j];
    //        if (tems.x == tem.x && tems.y == tem.y && j % 2 == 0) {
    //            //cout << "����ɫ" << endl;
    //            //cout << endl;
    //            a += 27;
    //            b += 103;
    //            c += 279;
    //        }
    //    }
    //    //cout << "(" << tems.x << "," << tems.y << ")";
    //    draw.at<Vec3b>(tems.x, tems.y)[0] = a;
    //    draw.at<Vec3b>(tems.x, tems.y)[1] = b;
    //    draw.at<Vec3b>(tems.x, tems.y)[2] = c;
    //}

    //����1026������δ�ϲ��ʻ�֮ǰ�Ĳ�ͼ
    for (size_t i = 0; i < strokesinfo[0].num; i++)
    {
        a += 27;
        b += 103;
        c += 279;
        for (size_t j = 0; j <= strokesinfo[i].snake_length; j++)
        {
            Point tems;
            tems = strokesinfo[i].tem[j];
            draw.at<Vec3b>(tems.x, tems.y)[0] = a;
            draw.at<Vec3b>(tems.x, tems.y)[1] = b;
            draw.at<Vec3b>(tems.x, tems.y)[2] = c;

        }
    }
    return draw;
}

//combine1�е��õ������жϺ�������Ҫ����strokesinfo[i]��i,uw���Լ��������жϻ����������ж�
int judge_qushi(int i, int uw, int select, StrokesInfo* strokesinfo) {
    if (select == 0) {//�����ж�����
        int zero = 0, one = 0, two = 0, three = 0;//����
        for (int i23 = 0; i23 < uw && i23 < strokesinfo[i].snake.size(); i23++) {
            //cout << strokesinfo[i].snake[i23];
            if (strokesinfo[i].snake[i23] == 0 || strokesinfo[i].snake[i23] == 4)zero++;
            if (strokesinfo[i].snake[i23] == 1 || strokesinfo[i].snake[i23] == 5)one++;
            if (strokesinfo[i].snake[i23] == 2 || strokesinfo[i].snake[i23] == 6)two++;
            if (strokesinfo[i].snake[i23] == 3 || strokesinfo[i].snake[i23] == 7)three++;
        }
        int flag_dir = 0;
        //���ĸ���������
        if (zero >= one)
        {
            flag_dir = 0;
            if (two >= zero && two >= three) {
                flag_dir = 2;
            }
            if (three >= zero && three >= two) {
                flag_dir = 3;
            }
        }
        if (one >= zero) {
            flag_dir = 1;
            if (two >= one && two >= three) {
                flag_dir = 2;
            }
            if (three >= one && three >= two) {
                flag_dir = 3;
            }
        }
        return flag_dir;
    }
    if (select == 1) {//�����ж�����
        int zero = 0, one = 0, two = 0, three = 0;//����
        for (int i23 = strokesinfo[i].snake.size() - 1; i23 > strokesinfo[i].snake.size() - 1 - uw && i23 > 0; i23--) {
            //cout << strokesinfo[i].snake[i23];
            if (strokesinfo[i].snake[i23] == 0 || strokesinfo[i].snake[i23] == 4)zero++;
            if (strokesinfo[i].snake[i23] == 1 || strokesinfo[i].snake[i23] == 5)one++;
            if (strokesinfo[i].snake[i23] == 2 || strokesinfo[i].snake[i23] == 6)two++;
            if (strokesinfo[i].snake[i23] == 3 || strokesinfo[i].snake[i23] == 7)three++;
        }
        int flag_dir = 0;
        //���ĸ���������
        if (zero >= one)
        {
            flag_dir = 0;
            if (two >= zero && two >= three) {
                flag_dir = 2;
            }
            if (three >= zero && three >= two) {
                flag_dir = 3;
            }
        }
        if (one >= zero) {
            flag_dir = 1;
            if (two >= one && two >= three) {
                flag_dir = 2;
            }
            if (three >= one && three >= two) {
                flag_dir = 3;
            }
        }
        return flag_dir;
    }
}

//����1026��ʹ�ñ�������strokesinfo���ҵ��ϲ��ʻ�  
//�ϲ��ʻ�1��combine_point_mark�洢�ҵ�һ���ĸ��㣬��ʾ�������Ժϲ��ʻ������ǰ����ظ��ģ�
void combine1(Mat& image, int NPB, int NSP, StrokesInfo* strokesinfo, vector<Point>& combine_point_mark) {

    int uw = NPB / NSP;
    int diri = 0, dirj = 0;
    int flag = 0, flag1 = 0;
    int com_mark = 0;
    //1024��������������strokesinfo������������������
    for (size_t i = 0; i < strokesinfo[0].num; i++) {
        for (size_t j = 0; j < strokesinfo[0].num; j++) {
            Point start, end;
            Point start1, end1;
            if (i != j) {
                //���㸳ֵ��
                start = strokesinfo[i].begin;
                end = strokesinfo[i].end;
                start1 = strokesinfo[j].begin;
                end1 = strokesinfo[j].end;

                //�жϷ���
                if (start.x != 0 && start1.x != 0) {
                    //������̾���
                    int dis = 0;//��̾�������
                    int dis0 = sqrt((start.x - start1.x) * (start.x - start1.x) + (start.y - start1.y) * (start.y - start1.y));
                    int dis1 = sqrt((start.x - end1.x) * (start.x - end1.x) + (start.y - end1.y) * (start.y - end1.y));
                    int dis2 = sqrt((end.x - start1.x) * (end.x - start1.x) + (end.y - start1.y) * (end.y - start1.y));
                    int dis3 = sqrt((end.x - end1.x) * (end.x - end1.x) + (end.y - end1.y) * (end.y - end1.y));

                    //���ĸ�������С��
                    if (dis0 >= dis1)
                    {
                        dis = dis1;
                        if (dis1 >= dis2 && dis3 >= dis2) {
                            dis = dis2;
                        }
                        if (dis1 >= dis3 && dis2 >= dis3) {
                            dis = dis3;
                        }
                    }
                    if (dis1 >= dis0)
                    {
                        dis = dis0;
                        if (dis0 >= dis2 && dis3 >= dis2) {
                            dis = dis2;
                        }
                        if (dis0 >= dis3 && dis2 >= dis3) {
                            dis = dis3;
                        }
                    }

                    if (dis <= uw / 2) {
                        int oneline = 0, twoline = 0;//��ʾ�����ʻ��ηֱ������
                        //ͨ����̾����ж����ƣ���Ϊ4�����

                        if (dis == dis0) {//˵��start.x��start1.x�����������ȫ������
                            oneline = judge_qushi(i, uw, 0, strokesinfo);
                            twoline = judge_qushi(j, uw, 0, strokesinfo);
                        }

                        if (dis == dis1) {//˵��start.x��end1.x�������ǰ���򣬺�����
                            oneline = judge_qushi(i, uw, 0, strokesinfo);
                            twoline = judge_qushi(j, uw, 1, strokesinfo);
                        }

                        if (dis == dis2) {//˵��end.x��start1.x�������ǰ���򣬺�����
                            oneline = judge_qushi(i, uw, 1, strokesinfo);
                            twoline = judge_qushi(j, uw, 0, strokesinfo);
                        }

                        if (dis == dis3) {//˵��end.x��end1.x�����������ȫ������
                            oneline = judge_qushi(i, uw, 1, strokesinfo);
                            twoline = judge_qushi(j, uw, 1, strokesinfo);
                        }

                        if (oneline == twoline) {//strokesinfo[i].dir == strokesinfo[j].dir || 

                            //�жϱʻ��Ƿ�ϲ���
                            //�������ʻ���com_mark��Ϊ0,��δ�ϲ���
                            if (strokesinfo[i].com_mark == 0 && strokesinfo[j].com_mark == 0) {
                                com_mark++;
                                strokesinfo[0].com_mark_max = com_mark;
                                strokesinfo[i].com_mark = com_mark;
                                strokesinfo[j].com_mark = com_mark;
                            }
                            //����һ�ʻ��ϲ���
                            if (strokesinfo[i].com_mark != 0 && strokesinfo[j].com_mark == 0) {
                                strokesinfo[j].com_mark = strokesinfo[i].com_mark;
                            }
                            if (strokesinfo[i].com_mark == 0 && strokesinfo[j].com_mark != 0) {
                                strokesinfo[i].com_mark = strokesinfo[j].com_mark;
                            }
                        }

                    }
                }
            }
        }
    }
}

//1026��ӣ���ȥ�غϲ��ʻ�combine_point_mark_new�Ļ����ϣ��洢�ϲ��ʻ���strokesinfo_com�ṹ��
//11.13��ӣ���������ϲ��ʻ�
void combine2_save(StrokesInfo* strokesinfo_com, StrokesInfo* strokesinfo) {


    //for (size_t i = 0; i < combine_point_mark_new.size(); i++) {
    //    Point tem;
    //    tem = combine_point_mark_new[i];
    //    if (i % 4 == 0)cout << endl;
    //    cout << "(" << tem.x << "," << tem.y << ")" << endl;
    //}
    /*cout << endl;
    cout << "==================�ϲ��ʻ�ǰ==================" << endl;
    for (int index = 0; index < strokesinfo[0].num; index++)
    {
        cout << "begin==(" << strokesinfo[index].begin.x << "," << strokesinfo[index].begin.y << ")" << endl;
        cout << "end==(" << strokesinfo[index].end.x << "," << strokesinfo[index].end.y << ")" << endl;
        cout << "�洢8�������г���==" << strokesinfo[index].snake_length << endl;
        for (int i = 0; i < strokesinfo[index].snake_length; i++) {
            cout << strokesinfo[index].snake[i];
        }
        cout << "�ʻ�����==" << strokesinfo[index].dir << endl;
        cout << "�ʻ����ص㣺" << endl;
        for (int i = 0; i <= strokesinfo[index].snake_length; i++) {
            cout << "(" << strokesinfo[index].tem[i].x << "," << strokesinfo[index].tem[i].y << ") ";
        }
        cout << "com_mark==" << strokesinfo[index].com_mark << endl;
        cout << endl;
    }*/

    //��ʼ���ṹ������strokesinfo_com
    for (int index = 0; index < 20; index++)
    {
        strokesinfo_com[index].begin.x = strokesinfo_com[index].begin.y = 0;
        strokesinfo_com[index].end.x = strokesinfo_com[index].end.y = 0;
        strokesinfo_com[index].snake_length = 0;
        strokesinfo_com[index].snake.clear();
        strokesinfo_com[index].dir = 0;
        strokesinfo_com[index].tem.clear();
        strokesinfo_com[index].num = 0;//�洢�����ڳ�Ա����
        strokesinfo_com[index].com_mark = 0;//�ϲ��ʻ����
        strokesinfo_com[index].com_mark_max = 0;//���com_mark�����ֵ
    }

    //cout << "strokesinfo[0].com_mark_max=" << strokesinfo[0].com_mark_max << endl;
    int flag = strokesinfo[0].com_mark_max + 1;//��Ϊδ�ϲ��ʻ��������
    //��com_mark��Ϊ0�ıʻ��κϲ�:����Ϊ0�ıʻ�����Ҫ�������򣬴洢��strokesinfo_com[20]��
    //�Ӻϲ����Ϊ1��ʼ
    for (int com_mark = 1; com_mark < strokesinfo[0].num; com_mark++) {
        //��ʼ��
        strokesinfo_com[com_mark].begin.x = 0;
        strokesinfo_com[com_mark].begin.y = 0;
        //����strokesinfo����
        for (int index = 0; index < strokesinfo[0].num; index++) {
            if (strokesinfo[index].com_mark == com_mark) {
                if (strokesinfo[index].dir != 0) {//����Ϊ0
                    strokesinfo_com[com_mark].dir = strokesinfo[index].dir;//�洢����
                    if (strokesinfo[index].begin.x < strokesinfo_com[com_mark].begin.x) {
                        //�ϲ���ǰ��                    
                        strokesinfo_com[com_mark].begin = strokesinfo[index].begin;
                        vector<Point> tem1;//��ʱ����
                        for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                            tem1.push_back(strokesinfo[index].tem[i]);
                        }
                        for (int i = 0; i < strokesinfo_com[com_mark].tem.size(); i++) {
                            tem1.push_back(strokesinfo_com[com_mark].tem[i]);
                        }
                        strokesinfo_com[com_mark].tem.clear();
                        for (int i = 0; i < tem1.size(); i++) {
                            strokesinfo_com[com_mark].tem.push_back(tem1[i]);
                        }

                    }
                    else {
                        //�ϲ��ں���
                        strokesinfo_com[com_mark].end = strokesinfo[index].end;
                        for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                            strokesinfo_com[com_mark].tem.push_back(strokesinfo[index].tem[i]);
                        }
                        strokesinfo_com[com_mark].begin = strokesinfo_com[com_mark].tem[0];
                    }
                }

                if (strokesinfo[index].dir == 0) {//����Ϊ0
                    strokesinfo_com[com_mark].dir = strokesinfo[index].dir;//�洢����
                    if (strokesinfo[index].begin.y < strokesinfo_com[com_mark].begin.y) {//��y����Ƚϴ�С
                        //�ϲ���ǰ��                    
                        strokesinfo_com[com_mark].begin = strokesinfo[index].begin;
                        vector<Point> tem1;//��ʱ����
                        for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                            tem1.push_back(strokesinfo[index].tem[i]);
                        }
                        for (int i = 0; i < strokesinfo_com[com_mark].tem.size(); i++) {
                            tem1.push_back(strokesinfo_com[com_mark].tem[i]);
                        }
                        strokesinfo_com[com_mark].tem.clear();
                        for (int i = 0; i < tem1.size(); i++) {
                            strokesinfo_com[com_mark].tem.push_back(tem1[i]);
                        }

                    }
                    else {
                        //�ϲ��ں���
                        strokesinfo_com[com_mark].end = strokesinfo[index].end;
                        for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                            strokesinfo_com[com_mark].tem.push_back(strokesinfo[index].tem[i]);
                        }
                        strokesinfo_com[com_mark].begin = strokesinfo_com[com_mark].tem[0];
                    }
                }
            }
        }
    }

    //�洢�ʻ�����=���ص����-1
    for (int index = 1; index < 20; index++)
    {
        strokesinfo_com[index].snake_length = strokesinfo_com[index].tem.size() - 1;
    }

    //���δ�ϲ��ʻ�com_mark==0
    for (int index = 0; index < strokesinfo[0].num; index++) {
        if (strokesinfo[index].com_mark == 0) {
            flag++;
            //cout << "flag=" << flag << endl;
            strokesinfo_com[flag].begin = strokesinfo[index].begin;//�洢��ʼ��
            strokesinfo_com[flag].end = strokesinfo[index].end;//�洢��ֹ��
            strokesinfo_com[flag].dir = strokesinfo[index].dir;//�洢����
            //�洢8�������г���
            strokesinfo_com[flag].snake_length = strokesinfo[index].snake_length;
            //�洢8��������
            for (int i = 0; i < strokesinfo[index].snake_length; i++) {
                strokesinfo_com[flag].snake.push_back(strokesinfo[index].snake[i]);
            }
            //�洢�ʻ����ص�
            for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                strokesinfo_com[flag].tem.push_back(strokesinfo[index].tem[i]);
            }
            //δ�ϲ��ʻ���com_mark==0
            strokesinfo_com[flag].com_mark = strokesinfo[index].com_mark;
        }
    }

    cout << endl;
    cout << "=============�ϲ��ʻ���strokesinfo_com=============" << endl;
    for (int index = 1; index < 20; index++)
    {
        cout << endl;
        cout << "begin==(" << strokesinfo_com[index].begin.x << "," << strokesinfo_com[index].begin.y << ")" << endl;
        cout << "end==(" << strokesinfo_com[index].end.x << "," << strokesinfo_com[index].end.y << ")" << endl;
        cout << "�洢8�������г���==" << strokesinfo_com[index].tem.size() << endl;
        cout << "�ʻ�����==" << strokesinfo_com[index].dir << endl;
        cout << "�ʻ����ص㣺" << endl;
        for (int i = 0; i < strokesinfo_com[index].tem.size(); i++) {
            cout << "(" << strokesinfo_com[index].tem[i].x << "," << strokesinfo_com[index].tem[i].y << ") ";
        }
        //cout << "com_mark==" << strokesinfo_com[index].com_mark << endl;
        cout << endl;
    }
}

//���ױ���������
void bezier_2(double p[3][2], vector<Point>& point_bezier_2)
{
    /*cout << "p[3][2]==(" << p[0][0] << "," << p[0][1] << ")" << endl;
    cout <<p[1][0] << "," << p[1][1] << ")" << endl;
    cout << p[2][0] << "," << p[2][1] << ")" << endl;*/
    double t, t1, t2, xt, yt;
    int rate = 200, x, y;
    int count = 0;

    point_bezier_2.clear();
    for (t = 0; t <= 1; t += 1.0 / rate)
    {
        yt = 1 - t;
        t1 = yt;
        t2 = 2 * yt * t;
        xt = p[0][0] * t1 * yt + p[1][0] * t2 + p[2][0] * t * t;
        yt = p[0][1] * t1 * yt + p[1][1] * t2 + p[2][1] * t * t;
        x = (int)(xt);
        y = (int)(yt);
        point_bezier_2.push_back(Point(x, y));
        //ȥ��
        for (size_t i = 0; i < point_bezier_2.size() - 1; i++) {
            if (x == point_bezier_2[i].x && y == point_bezier_2[i].y) {
                point_bezier_2.pop_back();
            }
        }
    }
    /*for (size_t i = 0; i < point_bezier_2.size(); i++) {
        cout << "��" << i << "����������Ϊ��(" << point_bezier_2[i].x << "," << point_bezier_2[i].y << ")" << endl;
 }*/
}

//���������ӵ�ʮ���ͱʻ�
void correct_qiao(Mat& image, Mat& image1, int i, int uw, qiaoInfo* qiaoinfo, vector<Point>& edge_center, vector<Point>& edge, StrokesInfo* strokesinfo) {
    //��������Ե���ֵ�������ؽ���            
    int pf_x = 0;
    int pf_y = 0;
    pf_x = (qiaoinfo[i].begin.x + qiaoinfo[i].end.x) / 2;
    pf_y = (qiaoinfo[i].begin.y + qiaoinfo[i].end.y) / 2;
    cout << "���ĵ�Ϊ��(" << pf_x << "," << pf_y << ")" << endl;
    Point center;
    center.x = pf_x;
    center.y = pf_y;
    edge_center.push_back(Point(pf_x, pf_y));

    //cout << "��ǰ��Ϊ��(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
    //cout << "���š�������ӱʻ���:" << endl;
    //for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
    //    cout << "(" << qiaoinfo[i].begin_line_begin[j1].x << "," << qiaoinfo[i].begin_line_begin[j1].y << ")--("
    //        << qiaoinfo[i].begin_line_end[j1].x << "," << qiaoinfo[i].begin_line_end[j1].y << ")" << endl;
    //    //cout <<"���š����յ����ӵıʻ����롰�š������ӷ�ʽ��0��ʾ�������������1��ʾ�յ���������"<< qiaoinfo[i].begin_line[j1] << endl;
    //}
    //cout << "���š��յ����ӱʻ���:" << endl;
    //for (int j1 = 0; j1 < qiaoinfo[i].end_line_begin.size(); j1++) {
    //    cout << "(" << qiaoinfo[i].end_line_begin[j1].x << "," << qiaoinfo[i].end_line_begin[j1].y << ")--("
    //        << qiaoinfo[i].end_line_end[j1].x << "," << qiaoinfo[i].end_line_end[j1].y << ")" << endl;
    //    //cout << "���š����յ����ӵıʻ����롰�š������ӷ�ʽ��0��ʾ�������������1��ʾ�յ���������" << qiaoinfo[i].end_line[j1] << endl;
    //}
    Point down, up, left, right;
    //�±�
    down.x = center.x + 2 * uw;//��ʼ����������
    down.y = center.y;
    for (int i1 = -2 * uw; i1 <= 2 * uw; i1++) {
        Point crosspoint;
        crosspoint.x = center.x + 2 * uw;
        crosspoint.y = center.y + i1;
        int color = image1.at<uchar>(crosspoint.x, crosspoint.y);
        if (color == 0) {
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                int sit1 = 0;//λ�üǺŷ�
                for (int j2 = 0; j2 < 20; j2++) {
                    if ((strokesinfo[j2].begin.x == qiaoinfo[i].begin_line_begin[j1].x) && (strokesinfo[j2].begin.y == qiaoinfo[i].begin_line_begin[j1].y)
                        && (strokesinfo[j2].end.x == qiaoinfo[i].begin_line_end[j1].x) && (strokesinfo[j2].end.y == qiaoinfo[i].begin_line_end[j1].y)) {
                        sit1 = j2;
                    }
                }
                for (int j3 = 0; j3 < strokesinfo[sit1].tem.size(); j3++) {
                    if (strokesinfo[sit1].tem[j3].x == crosspoint.x && strokesinfo[sit1].tem[j3].y == crosspoint.y) {
                        down.x = crosspoint.x;//��������
                        down.y = crosspoint.y;
                        cout << "�±��ཻ��(" << down.x << "," << down.y << ")" << endl;

                    }
                }
            }

        }

    }
    //�ϱ�
    up.x = center.x - 2 * uw;//��ʼ����������
    up.y = center.y;
    for (int i2 = -2 * uw; i2 <= 2 * uw; i2++) {
        Point crosspoint;
        crosspoint.x = center.x - 2 * uw;
        crosspoint.y = center.y + i2;
        int color = image1.at<uchar>(crosspoint.x, crosspoint.y);
        if (color == 0) {
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                int sit1 = 0;//λ�üǺŷ�
                for (int j2 = 0; j2 < 20; j2++) {
                    if ((strokesinfo[j2].begin.x == qiaoinfo[i].begin_line_begin[j1].x) && (strokesinfo[j2].begin.y == qiaoinfo[i].begin_line_begin[j1].y)
                        && (strokesinfo[j2].end.x == qiaoinfo[i].begin_line_end[j1].x) && (strokesinfo[j2].end.y == qiaoinfo[i].begin_line_end[j1].y)) {
                        sit1 = j2;
                    }
                }
                for (int j3 = 0; j3 < strokesinfo[sit1].tem.size(); j3++) {
                    if (strokesinfo[sit1].tem[j3].x == crosspoint.x && strokesinfo[sit1].tem[j3].y == crosspoint.y) {
                        up.x = crosspoint.x;//��������
                        up.y = crosspoint.y;
                        cout << "�ϱ��ཻ��(" << up.x << "," << up.y << ")" << endl;

                    }
                }
            }
        }

    }
    //�ұ�
    right.x = center.x;//��ʼ����������
    right.y = center.y + 2 * uw;
    for (int i3 = -2 * uw; i3 <= 2 * uw; i3++) {
        Point crosspoint;
        crosspoint.x = center.x + i3;
        crosspoint.y = center.y + 2 * uw;
        int color = image1.at<uchar>(crosspoint.x, crosspoint.y);
        if (color == 0) {
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                int sit1 = 0;//λ�üǺŷ�
                for (int j2 = 0; j2 < 20; j2++) {
                    if ((strokesinfo[j2].begin.x == qiaoinfo[i].begin_line_begin[j1].x) && (strokesinfo[j2].begin.y == qiaoinfo[i].begin_line_begin[j1].y)
                        && (strokesinfo[j2].end.x == qiaoinfo[i].begin_line_end[j1].x) && (strokesinfo[j2].end.y == qiaoinfo[i].begin_line_end[j1].y)) {
                        sit1 = j2;
                    }
                }
                for (int j3 = 0; j3 < strokesinfo[sit1].tem.size(); j3++) {
                    if (strokesinfo[sit1].tem[j3].x == crosspoint.x && strokesinfo[sit1].tem[j3].y == crosspoint.y) {
                        right.x = crosspoint.x;//��������
                        right.y = crosspoint.y;
                        cout << "�ұ��ཻ��(" << right.x << "," << right.y << ")" << endl;

                    }
                }
            }
        }

    }
    //���
    left.x = center.x;//��ʼ����������
    left.y = center.y - 2 * uw;
    for (int i4 = -2 * uw; i4 <= 2 * uw; i4++) {
        Point crosspoint;
        crosspoint.x = center.x + i4;
        crosspoint.y = center.y - 2 * uw;
        int color = image1.at<uchar>(crosspoint.x, crosspoint.y);
        if (color == 0) {
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                int sit1 = 0;//λ�üǺŷ�
                for (int j2 = 0; j2 < 20; j2++) {
                    if ((strokesinfo[j2].begin.x == qiaoinfo[i].begin_line_begin[j1].x) && (strokesinfo[j2].begin.y == qiaoinfo[i].begin_line_begin[j1].y)
                        && (strokesinfo[j2].end.x == qiaoinfo[i].begin_line_end[j1].x) && (strokesinfo[j2].end.y == qiaoinfo[i].begin_line_end[j1].y)) {
                        sit1 = j2;
                    }
                }
                for (int j3 = 0; j3 < strokesinfo[sit1].tem.size(); j3++) {
                    if (strokesinfo[sit1].tem[j3].x == crosspoint.x && strokesinfo[sit1].tem[j3].y == crosspoint.y) {
                        left.x = crosspoint.x;//��ʼ����������
                        left.y = crosspoint.y;
                        cout << "����ཻ��(" << left.x << "," << left.y << ")" << endl;

                    }
                }
            }
        }

    }

    //����Ƕȣ�
    Point2f pt1, pt2;
    //����pt1��pt2֮��ĽǶ�
    pt1.x = center.x;
    pt1.y = center.y;
    cout << "center:(" << center.x << "," << center.y << ")" << endl;
    cout << "down:(" << down.x << "," << down.y << ")" << endl;
    pt2.x = down.x;
    pt2.y = down.y;
    float radian = atan2((pt2.y - pt1.y), (pt2.x - pt1.x));//����   �ú�������ֵ��Χ��[-pi,pi]
    float down_angle = radian * 180 / 3.1415926;//�Ƕ�
    cout << "radian:" << radian << endl;
    cout << "down_angle" << down_angle << endl;

    pt2.x = up.x;
    pt2.y = up.y;
    radian = atan2((pt2.y - pt1.y), (pt2.x - pt1.x));//����   �ú�������ֵ��Χ��[-pi,pi]
    float up_angle = radian * 180 / 3.1415926;//�Ƕ�
    cout << "radian:" << radian << endl;
    cout << "up_angle" << up_angle << endl;

    pt2.x = left.x;
    pt2.y = left.y;
    radian = atan2((pt2.y - pt1.y), (pt2.x - pt1.x));//����   �ú�������ֵ��Χ��[-pi,pi]
    float left_angle = radian * 180 / 3.1415926;//�Ƕ�
    cout << "radian:" << radian << endl;
    cout << "left_angle" << left_angle << endl;

    pt2.x = right.x;
    pt2.y = right.y;
    radian = atan2((pt2.y - pt1.y), (pt2.x - pt1.x));//����   �ú�������ֵ��Χ��[-pi,pi]
    float right_angle = radian * 180 / 3.1415926;//�Ƕ�
    cout << "radian:" << radian << endl;
    cout << "right_angle" << right_angle << endl;


    Point first_qua;//��һ���޵ı�Ե�㣺
    vector<Point> first_edge;//��һ���޵ı�Ե�㣺
    int first_dis_s = 100;
    Point first_qua_s;//��һ���޵���̾���㣺
    for (int i = 1; i < 2 * uw; i++) {
        for (int j = 1; j < 2 * uw; j++) {
            first_qua.x = center.x - i;
            first_qua.y = center.y + j;
            int color1 = image.at<uchar>(first_qua.x, first_qua.y);
            if (color1 == 0) {//��ǰ��Ϊ�ڵ�
                if ((image.at<uchar>(first_qua.x, first_qua.y + 1) == 255) || (image.at<uchar>(first_qua.x, first_qua.y - 1) == 255)
                    || (image.at<uchar>(first_qua.x + 1, first_qua.y) == 255) || (image.at<uchar>(first_qua.x + 1, first_qua.y - 1) == 255) || (image.at<uchar>(first_qua.x + 1, first_qua.y + 1) == 255)
                    || (image.at<uchar>(first_qua.x - 1, first_qua.y) == 255) || (image.at<uchar>(first_qua.x - 1, first_qua.y - 1) == 255) || (image.at<uchar>(first_qua.x - 1, first_qua.y + 1) == 255)) {
                    //��ǰ��Ϊ��Ե��
                    //cout << "��ǰ��Ϊ��Ե��:(" << first_qua.x << "," << first_qua.y << ")" << endl;
                    //first_edge.push_back(Point(first_qua.x, first_qua.y));
                    int first_dis = distance(first_qua, center);
                    //cout << "first_dis:" << first_dis << endl;

                    //�����Ƕ��жϣ��ұߺ��ϱ�
                    Point2f pt3;
                    pt3.x = first_qua.x;
                    pt3.y = first_qua.y;
                    float radian = atan2((pt3.y - pt1.y), (pt3.x - pt1.x));//����   �ú�������ֵ��Χ��[-pi,pi]
                    float one_angle = radian * 180 / 3.1415926;//�Ƕ�
                    if (one_angle > right_angle && one_angle < up_angle && first_dis < first_dis_s) {
                        cout << "one_angle" << one_angle << endl;
                        first_qua_s.x = first_qua.x;
                        first_qua_s.y = first_qua.y;
                        first_dis_s = first_dis;
                    }
                }
            }
        }
    }

    Point second_qua;//�ڶ����޵ı�Ե�㣺
    vector<Point> second_edge;//�ڶ����޵ı�Ե�㣺
    int second_dis_s = 100;
    Point second_qua_s;//�ڶ����޵���̾���㣺
    for (int i = 1; i < 2 * uw; i++) {
        for (int j = 1; j < 2 * uw; j++) {
            second_qua.x = center.x - i;
            second_qua.y = center.y - j;
            int color1 = image.at<uchar>(second_qua.x, second_qua.y);
            if (color1 == 0) {//��ǰ��Ϊ�ڵ�
                if ((image.at<uchar>(second_qua.x, second_qua.y + 1) == 255) || (image.at<uchar>(second_qua.x, second_qua.y - 1) == 255)
                    || (image.at<uchar>(second_qua.x + 1, second_qua.y) == 255) || (image.at<uchar>(second_qua.x + 1, second_qua.y - 1) == 255) || (image.at<uchar>(second_qua.x + 1, second_qua.y + 1) == 255)
                    || (image.at<uchar>(second_qua.x - 1, second_qua.y) == 255) || (image.at<uchar>(second_qua.x - 1, second_qua.y - 1) == 255) || (image.at<uchar>(second_qua.x - 1, second_qua.y + 1) == 255)) {
                    //��ǰ��Ϊ��Ե��
                    //cout << "��ǰ��Ϊ��Ե��:(" << second_qua.x << "," << second_qua.y << ")" << endl;
                    //first_edge.push_back(Point(first_qua.x, first_qua.y));
                    int second_dis = distance(second_qua, center);
                    //cout << "second_dis:(" << second_dis << endl;

                    //�����Ƕ��жϣ���ߺ��ϱ�
                    Point2f pt3;
                    pt3.x = second_qua.x;
                    pt3.y = second_qua.y;
                    float radian = atan2((pt3.y - pt1.y), (pt3.x - pt1.x));//����   �ú�������ֵ��Χ��[-pi,pi]
                    float two_angle = radian * 180 / 3.1415926;//�Ƕ�
                    if (two_angle < left_angle && second_dis < second_dis_s) {
                        cout << "two_angle" << two_angle << endl;
                        second_qua_s.x = second_qua.x;
                        second_qua_s.y = second_qua.y;
                        second_dis_s = second_dis;
                    }
                }
            }
        }
    }

    Point third_qua;//�������޵ı�Ե�㣺
    vector<Point> third_edge;//�������޵ı�Ե�㣺
    int third_dis_s = 100;
    Point third_qua_s;//�������޵���̾���㣺
    for (int i = 1; i < 2 * uw; i++) {
        for (int j = 1; j < 2 * uw; j++) {
            third_qua.x = center.x + i;
            third_qua.y = center.y - j;
            int color1 = image.at<uchar>(third_qua.x, third_qua.y);
            if (color1 == 0) {//��ǰ��Ϊ�ڵ�
                if ((image.at<uchar>(third_qua.x, third_qua.y + 1) == 255) || (image.at<uchar>(third_qua.x, third_qua.y - 1) == 255)
                    || (image.at<uchar>(third_qua.x + 1, third_qua.y) == 255) || (image.at<uchar>(third_qua.x + 1, third_qua.y - 1) == 255) || (image.at<uchar>(third_qua.x + 1, third_qua.y + 1) == 255)
                    || (image.at<uchar>(third_qua.x - 1, third_qua.y) == 255) || (image.at<uchar>(third_qua.x - 1, third_qua.y - 1) == 255) || (image.at<uchar>(third_qua.x - 1, third_qua.y + 1) == 255)) {
                    //��ǰ��Ϊ��Ե��
                    //cout << "��ǰ��Ϊ��Ե��:(" << third_qua.x << "," << third_qua.y << ")" << endl;
                    //first_edge.push_back(Point(first_qua.x, first_qua.y));
                    int third_dis = distance(third_qua, center);
                    //cout << "third_dis:(" << third_dis << endl;

                    //�����Ƕ��жϣ���ߺ��±�
                    Point2f pt3;
                    pt3.x = third_qua.x;
                    pt3.y = third_qua.y;
                    float radian = atan2((pt3.y - pt1.y), (pt3.x - pt1.x));//����   �ú�������ֵ��Χ��[-pi,pi]
                    float third_angle = radian * 180 / 3.1415926;//�Ƕ�
                    if (third_angle > left_angle && third_angle < down_angle && third_dis < third_dis_s) {
                        cout << "third_angle" << third_angle << endl;
                        third_qua_s.x = third_qua.x;
                        third_qua_s.y = third_qua.y;
                        third_dis_s = third_dis;
                    }
                }
            }
        }
    }

    Point four_qua;//�������޵ı�Ե�㣺
    vector<Point> four_edge;//�������޵ı�Ե�㣺
    int four_dis_s = 100;
    Point four_qua_s;//�������޵���̾���㣺
    for (int i = 1; i <= 2 * uw; i++) {
        for (int j = 1; j <= 2 * uw; j++) {
            four_qua.x = center.x + i;
            four_qua.y = center.y + j;
            int color1 = image.at<uchar>(four_qua.x, four_qua.y);
            if (color1 == 0) {//��ǰ��Ϊ�ڵ�
                if ((image.at<uchar>(four_qua.x, four_qua.y + 1) == 255) || (image.at<uchar>(four_qua.x, four_qua.y - 1) == 255)
                    || (image.at<uchar>(four_qua.x + 1, four_qua.y) == 255) || (image.at<uchar>(four_qua.x + 1, four_qua.y - 1) == 255) || (image.at<uchar>(four_qua.x + 1, four_qua.y + 1) == 255)
                    || (image.at<uchar>(four_qua.x - 1, four_qua.y) == 255) || (image.at<uchar>(four_qua.x - 1, four_qua.y - 1) == 255) || (image.at<uchar>(four_qua.x - 1, four_qua.y + 1) == 255)) {
                    //��ǰ��Ϊ��Ե��
                    //cout << "��ǰ��Ϊ��Ե��:(" << four_qua.x << "," << four_qua.y << ")" << endl;
                    //first_edge.push_back(Point(first_qua.x, first_qua.y));
                    int four_dis = distance(four_qua, center);
                    //cout << "four_dis:(" << four_dis << endl;
                     //�����Ƕ��жϣ��ұߺ��±�
                    Point2f pt3;
                    pt3.x = four_qua.x;
                    pt3.y = four_qua.y;
                    float radian = atan2((pt3.y - pt1.y), (pt3.x - pt1.x));//����   �ú�������ֵ��Χ��[-pi,pi]
                    float four_angle = radian * 180 / 3.1415926;//�Ƕ�
                    if (four_angle < right_angle && four_dis < four_dis_s) {
                        four_qua_s.x = four_qua.x;
                        four_qua_s.y = four_qua.y;
                        four_dis_s = four_dis;
                    }
                }
            }
        }
    }

    cout << "��һ���޵���̾���㣺(" << first_qua_s.x << "," << first_qua_s.y << ")" << endl;
    cout << "�ڶ����޵���̾���㣺(" << second_qua_s.x << "," << second_qua_s.y << ")" << endl;
    cout << "�������޵���̾���㣺(" << third_qua_s.x << "," << third_qua_s.y << ")" << endl;
    cout << "�������޵���̾���㣺(" << four_qua_s.x << "," << four_qua_s.y << ")" << endl;

    edge.push_back(Point(first_qua_s.x, first_qua_s.y));
    edge.push_back(Point(second_qua_s.x, second_qua_s.y));
    edge.push_back(Point(third_qua_s.x, third_qua_s.y));
    edge.push_back(Point(four_qua_s.x, four_qua_s.y));

    //�ҵ����������ߵ���ʼ��P1��P2 : P1��2��3�����ཻ
    Point Poin1, Poin2, Poin;
    Poin.x = center.x;
    Poin.y = center.y;
    vector<Point> qiao_bezier_2;//������������
    cout << endl;
    double k1 = (double)(third_qua_s.y - second_qua_s.y) / (third_qua_s.x - second_qua_s.x);
    for (int i = third_qua_s.x; i >= second_qua_s.x; i--) {
        int Y = second_qua_s.y;//��Ϊ��ʼֵ
        int Y1 = k1 * ((double)i - (double)second_qua_s.x) + (double)second_qua_s.y;
        int color = image1.at<uchar>(i, Y);
        if (color == 0) {
            //cout << "P1��ʼֵ�㣺(" << i << "," << Y << ")" << endl;
            Poin1.x = i;
            Poin1.y = Y;


        }
        color = image1.at<uchar>(i, Y1);
        if (color == 0) {
            //cout << "P1�㣺(" << i << "," << Y1 << ")" << endl;
            Poin1.x = i;
            Poin1.y = Y1;

        }
    }

    // P2��1��4�����ཻ
    double k2 = (double)(four_qua_s.y - first_qua_s.y) / (four_qua_s.x - first_qua_s.x);
    for (int i = four_qua_s.x; i >= first_qua_s.x; i--) {
        int Y3 = first_qua_s.y;//��Ϊ��ʼֵ
        int Y2 = k2 * ((double)i - (double)first_qua_s.x) + (double)first_qua_s.y;
        int color = image1.at<uchar>(i, Y3);
        if (color == 0) {
            //cout << "P2��ʼֵ�㣺(" << i << "," << Y3 << ")" << endl;
            Poin2.x = i;
            Poin2.y = Y3;
        }
        color = image1.at<uchar>(i, Y2);
        if (color == 0) {
            //cout << "P2�㣺(" << i << "," << Y2 << ")" << endl;
            Poin2.x = i;
            Poin2.y = Y2;
        }
    }
    //��ϱ�����
    double p[3][2] = { Poin1.x,Poin1.y,Poin.x,Poin.y,Poin2.x,Poin2.y };
    bezier_2(p, qiao_bezier_2);

    vector<Point> qiao_xiuzheng;//����������ʱ����
    qiao_xiuzheng.clear();
    int qiao_xiuzheng1 = 0;//��Ƿ�
    for (int index = 0; index < 20; index++) {
        if (strokesinfo[index].begin.x != 0) {
            for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                if (Poin1.x == strokesinfo[index].tem[i].x && Poin1.y == strokesinfo[index].tem[i].y) {
                    qiao_xiuzheng1 = index;
                    break;
                }
            }
        }
    }
    int mark_child = 0;//���λ
    //�޸ıʶ�ǰ������ص�
    for (int i = 0; i < strokesinfo[qiao_xiuzheng1].tem.size(); i++) {
        if (Poin1.x == strokesinfo[qiao_xiuzheng1].tem[i].x && Poin1.y == strokesinfo[qiao_xiuzheng1].tem[i].y) {
            mark_child = i;
        }
    }
    for (int j = 0; j < mark_child; j++) {
        qiao_xiuzheng.push_back(Point(strokesinfo[qiao_xiuzheng1].tem[j].x, strokesinfo[qiao_xiuzheng1].tem[j].y));
    }

    //�޸ıʶε����ص�qiao_bezier_2
    for (int i = 0; i < qiao_bezier_2.size(); i++) {
        qiao_xiuzheng.push_back(Point(qiao_bezier_2[i].x, qiao_bezier_2[i].y));
    }
    //��������ص�
    mark_child = 0;//���λ
    for (int i = 0; i < strokesinfo[qiao_xiuzheng1].tem.size(); i++) {
        if (Poin2.x == strokesinfo[qiao_xiuzheng1].tem[i].x && Poin2.y == strokesinfo[qiao_xiuzheng1].tem[i].y) {
            mark_child = i;
        }
    }
    for (int j = mark_child; j < strokesinfo[qiao_xiuzheng1].tem.size(); j++) {
        qiao_xiuzheng.push_back(Point(strokesinfo[qiao_xiuzheng1].tem[j].x, strokesinfo[qiao_xiuzheng1].tem[j].y));
    }
    strokesinfo[qiao_xiuzheng1].tem.clear();
    for (int i = 0; i < qiao_xiuzheng.size(); i++) {
        strokesinfo[qiao_xiuzheng1].tem.push_back(Point(qiao_xiuzheng[i].x, qiao_xiuzheng[i].y));
    }

}

//02.28�����������š��ĺϲ�
void duanqiao(Mat& image, Mat& image1, int NPB, int NSP, StrokesInfo* strokesinfo, double Median, vector<Point>& se, qiaoInfo* qiaoinfo,sfInfo* sfinfo, 
    vector<Point>& edge_center, vector<Point>& edge) {
    int uw = NPB / NSP;//ƽ���ʻ����
    int qiao_count = -1;
    //�ҳ��ʻ����еġ����š����洢���ṹ����
    for (size_t index = 0; index < 20; index++) {
        //���š��ĳ���С��uw
        if (strokesinfo[index].begin.x != 0 && strokesinfo[index].tem.size() <= Median) {//1.2 * uw

            //���š������˲����ж˵�
            int flag = 0;
            for (size_t i = 0; i < se.size(); i++) {
                if ((strokesinfo[index].begin.x == se[i].x && strokesinfo[index].begin.y == se[i].y) ||
                    (strokesinfo[index].end.x == se[i].x && strokesinfo[index].end.y == se[i].y)) {
                    flag = 1;
                }
            }
            //���š��ʻ������
            if (flag == 0) {
                qiao_count++;
                //�����š��ʻ��洢�����š��ṹ����
                qiaoinfo[qiao_count].begin.x = strokesinfo[index].begin.x;
                qiaoinfo[qiao_count].begin.y = strokesinfo[index].begin.y;
                qiaoinfo[qiao_count].end.x = strokesinfo[index].end.x;
                qiaoinfo[qiao_count].end.y = strokesinfo[index].end.y;
                qiaoinfo[qiao_count].dir = strokesinfo[index].dir;
                for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                    qiaoinfo[qiao_count].tem.push_back(Point(strokesinfo[index].tem[i].x, strokesinfo[index].tem[i].y));
                }

                //�жϡ��š�����Ƿ��ڽ������У������ڣ���˵��������ӵĲ�ֻһ���ʻ��Σ�
                int flag_sfinfo = 0;//�����㴦�ڽ����ص�λ��
                vector<Point> flag_sfvec;
                for (int j = 0; j < 20; j++) {
                    for (int j1 = 0; j1 < sfinfo[j].sf_info.size(); j1++) {
                        if (sfinfo[j].sf_info[j1].x == strokesinfo[index].begin.x && sfinfo[j].sf_info[j1].y == strokesinfo[index].begin.y) {
                            flag_sfinfo = j;
                            //cout << "flag_sfinfo = " << j << endl;
                            qiaoinfo[qiao_count].flag_sfinfo = j;
                        }
                    }
                }
                //�����š���㴦�ڽ�������, ���ҡ��š���㴦�ڵĽ����صıʻ��β��洢��������
                if (flag_sfinfo >= 0) {
                    for (int k = 0; k < sfinfo[flag_sfinfo].sf_info.size(); k++) {
                        qiaoinfo[qiao_count].flag_sfvec.push_back(Point(sfinfo[flag_sfinfo].sf_info[k].x, sfinfo[flag_sfinfo].sf_info[k].y));
                        //cout << "���š���㴦�ڵĽ�����" << "(" << sfinfo[flag_sfinfo].sf_info[k].x << "," << sfinfo[flag_sfinfo].sf_info[k].y << ")" << endl;
                    }
                }//�����š���㲻���ڽ�������, ���š����洢��������
                else   qiaoinfo[qiao_count].flag_sfvec.push_back(Point(strokesinfo[index].begin.x, strokesinfo[index].begin.y));


                //�жϡ��š��յ��Ƿ��ڽ������У������ڣ���˵��������ӵĲ�ֻһ���ʻ���
                int flag_sfinfo1 = 0;//����յ㴦�ڽ����ص�λ��
                vector<Point> flag_sfvec1;
                for (int j = 0; j < 20; j++) {
                    for (int j1 = 0; j1 < sfinfo[j].sf_info.size(); j1++) {
                        if (sfinfo[j].sf_info[j1].x == strokesinfo[index].end.x && sfinfo[j].sf_info[j1].y == strokesinfo[index].end.y) {
                            flag_sfinfo1 = j;
                            //cout << " flag_sfinfo1 = " << j << endl;
                            qiaoinfo[qiao_count].flag_sfinfo1 = j;
                        }
                    }
                }
                //�����š��յ㴦�ڽ�������, ���ҡ��š��յ㴦�ڵĽ����صıʻ��β��洢��������
                if (flag_sfinfo1 >= 0) {
                    for (int k = 0; k < sfinfo[flag_sfinfo1].sf_info.size(); k++) {
                        qiaoinfo[qiao_count].flag_sfvec1.push_back(Point(sfinfo[flag_sfinfo1].sf_info[k].x, sfinfo[flag_sfinfo1].sf_info[k].y));
                    }
                }//�����š��յ㲻���ڽ�������, ���š��յ�洢��������
                else   qiaoinfo[qiao_count].flag_sfvec1.push_back(Point(strokesinfo[index].end.x, strokesinfo[index].end.y));
            }
        }
    }

    //�жϡ��š����Ƿ������ӣ��������ӣ���link���
    //for (int i = 0; i < 20 && qiaoinfo[i].begin.x != 0; i++) {
    //    for (int j = 0; j < 20 && qiaoinfo[j].begin.x != 0; j++) {
    //        if (i != j) {
    //            if (qiaoinfo[j].flag_sfinfo == qiaoinfo[i].flag_sfinfo1 || qiaoinfo[i].flag_sfinfo == qiaoinfo[j].flag_sfinfo1) {
    //                qiaoinfo[i].link = j;
    //                qiaoinfo[j].link = i;//��i����j��Ϊ����
    //            }
    //        }
    //    }
    //}

    //�������š����յ����������ӵ����бʻ��Σ�ע��һ������ܻ���ڶ���ʻ��Σ�����ṹ��
    for (int index = 0; index < 20 && qiaoinfo[index].begin.x != 0; index++) {
        for (int j1 = 0; j1 < qiaoinfo[index].flag_sfvec.size(); j1++) {
            int flag_start = 0;//���š�������ӵıʻ���
            cout << "���š��������==(" << qiaoinfo[index].flag_sfvec[j1].x << "," << qiaoinfo[index].flag_sfvec[j1].y << ")" << endl;
            for (int index1 = 0; index1 < 20; index1++) {
                //����ȥ��������
                int fouding = 0;//ȥ����������жϷ�
                if ((strokesinfo[index1].begin.x == qiaoinfo[index].begin.x && strokesinfo[index1].begin.y == qiaoinfo[index].begin.y &&
                    (strokesinfo[index1].end.x == qiaoinfo[index].end.x && strokesinfo[index1].end.y == qiaoinfo[index].end.y))) {
                    fouding = 1;
                }
                if (fouding == 0) {
                    if ((strokesinfo[index1].begin.x == qiaoinfo[index].flag_sfvec[j1].x && strokesinfo[index1].begin.y == qiaoinfo[index].flag_sfvec[j1].y) ||
                        (strokesinfo[index1].end.x == qiaoinfo[index].flag_sfvec[j1].x && strokesinfo[index1].end.y == qiaoinfo[index].flag_sfvec[j1].y)) {
                        flag_start = index1;
                        cout << endl;
                        cout << "���š�������ӵ�flag_start�ıʻ���" << endl;
                        cout << "(" << strokesinfo[flag_start].begin.x << "," << strokesinfo[flag_start].begin.y << ")--(" << strokesinfo[flag_start].end.x << "," << strokesinfo[flag_start].end.y << ")" << endl;
                        cout << "8����" << endl;
                        for (int i23 = 0; i23 < strokesinfo[flag_start].snake.size(); i23++) {
                            cout << strokesinfo[flag_start].snake[i23];
                        }
                        cout << endl;
                        //���ʻ��δ���begin_line
                        qiaoinfo[index].begin_line_begin.push_back(Point(strokesinfo[flag_start].begin.x, strokesinfo[flag_start].begin.y));
                        qiaoinfo[index].begin_line_end.push_back(Point(strokesinfo[flag_start].end.x, strokesinfo[flag_start].end.y));

                        //���š����յ����ӵıʻ����롰�š������ӷ�ʽ��0��ʾ�������������1��ʾ�յ���������
                        if (strokesinfo[index1].begin.x == qiaoinfo[index].flag_sfvec[j1].x && strokesinfo[index1].begin.y == qiaoinfo[index].flag_sfvec[j1].y) {
                            qiaoinfo[index].begin_line.push_back(0);
                        }
                        if (strokesinfo[index1].end.x == qiaoinfo[index].flag_sfvec[j1].x && strokesinfo[index1].end.y == qiaoinfo[index].flag_sfvec[j1].y) {
                            qiaoinfo[index].begin_line.push_back(1);
                        }
                    }
                }

            }
        }

        for (int j1 = 0; j1 < qiaoinfo[index].flag_sfvec1.size(); j1++) {
            int flag_start = 0;//���š��յ����ӵıʻ���
            cout << "���š��յ�����==(" << qiaoinfo[index].flag_sfvec1[j1].x << "," << qiaoinfo[index].flag_sfvec1[j1].y << ")" << endl;
            for (int index1 = 1; index1 < 20; index1++) {
                //����ȥ��������
                int fouding = 0;//ȥ����������жϷ�
                if ((strokesinfo[index1].begin.x == qiaoinfo[index].begin.x && strokesinfo[index1].begin.y == qiaoinfo[index].begin.y &&
                    (strokesinfo[index1].end.x == qiaoinfo[index].end.x && strokesinfo[index1].end.y == qiaoinfo[index].end.y))) {
                    fouding = 1;
                }
                /*for (int i = 0; i < 20 && qiaoinfo[i].begin.x != 0; i++) {
                    if ((strokesinfo[index1].begin.x == qiaoinfo[i].begin.x && strokesinfo[index1].begin.y == qiaoinfo[i].begin.y &&
                        (strokesinfo[index1].end.x == qiaoinfo[i].end.x && strokesinfo[index1].end.y == qiaoinfo[i].end.y))) {
                        fouding = 1;
                    }
                }*/
                if (fouding == 0) {
                    if ((strokesinfo[index1].begin.x == qiaoinfo[index].flag_sfvec1[j1].x && strokesinfo[index1].begin.y == qiaoinfo[index].flag_sfvec1[j1].y) ||
                        (strokesinfo[index1].end.x == qiaoinfo[index].flag_sfvec1[j1].x && strokesinfo[index1].end.y == qiaoinfo[index].flag_sfvec1[j1].y)) {
                        flag_start = index1;
                        cout << endl;
                        cout << "���š��յ����ӵ�flag_start�ıʻ���" << endl;
                        cout << "(" << strokesinfo[flag_start].begin.x << "," << strokesinfo[flag_start].begin.y << ")--(" << strokesinfo[flag_start].end.x << "," << strokesinfo[flag_start].end.y << ")" << endl;
                        cout << "8����" << endl;
                        for (int i23 = 0; i23 < strokesinfo[flag_start].snake.size(); i23++) {
                            cout << strokesinfo[flag_start].snake[i23];
                        }
                        cout << endl;
                        //���ʻ��δ���end_line
                        qiaoinfo[index].end_line_begin.push_back(Point(strokesinfo[flag_start].begin.x, strokesinfo[flag_start].begin.y));
                        qiaoinfo[index].end_line_end.push_back(Point(strokesinfo[flag_start].end.x, strokesinfo[flag_start].end.y));

                        //���š����յ����ӵıʻ����롰�š������ӷ�ʽ��0��ʾ�������������1��ʾ�յ���������
                        if (strokesinfo[index1].begin.x == qiaoinfo[index].flag_sfvec1[j1].x && strokesinfo[index1].begin.y == qiaoinfo[index].flag_sfvec1[j1].y) {
                            qiaoinfo[index].end_line.push_back(0);
                        }
                        if (strokesinfo[index1].end.x == qiaoinfo[index].flag_sfvec1[j1].x && strokesinfo[index1].end.y == qiaoinfo[index].flag_sfvec1[j1].y) {
                            qiaoinfo[index].end_line.push_back(1);
                        }
                    }
                }
            }
        }
    }

    //������š��ṹ��
    for (int i = 0; i < 20; i++) {
        if (qiaoinfo[i].begin.x != 0) {
            cout << endl;
            cout << "��begin==(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")" << endl;
            cout << "��end==(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
            cout << "�ʻ�����==" << qiaoinfo[i].dir << endl;
            cout << "�ʻ�����==" << qiaoinfo[i].tem.size() << endl;
            cout << "�ʻ����ص㣺" << endl;
            for (int j = 0; j < qiaoinfo[i].tem.size(); j++) {
                cout << "(" << qiaoinfo[i].tem[j].x << "," << qiaoinfo[i].tem[j].y << ") ";
            }
            cout << endl;
            cout << "��㴦�ڽ����ص�λ��==" << qiaoinfo[i].flag_sfinfo << endl;
            cout << "�յ㴦�ڽ����ص�λ��==" << qiaoinfo[i].flag_sfinfo1 << endl;

            for (int j1 = 0; j1 < qiaoinfo[i].flag_sfvec.size(); j1++) {
                cout << "���š��������==(" << qiaoinfo[i].flag_sfvec[j1].x << "," << qiaoinfo[i].flag_sfvec[j1].y << ")" << endl;
            }
            for (int j1 = 0; j1 < qiaoinfo[i].flag_sfvec1.size(); j1++) {
                cout << "���š��յ�����==(" << qiaoinfo[i].flag_sfvec1[j1].x << "," << qiaoinfo[i].flag_sfvec1[j1].y << ")" << endl;
            }
            cout << "���š�������ӱʻ���:" << endl;
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                cout << "(" << qiaoinfo[i].begin_line_begin[j1].x << "," << qiaoinfo[i].begin_line_begin[j1].y << ")--("
                    << qiaoinfo[i].begin_line_end[j1].x << "," << qiaoinfo[i].begin_line_end[j1].y << ")" << endl;
                //cout <<"���š����յ����ӵıʻ����롰�š������ӷ�ʽ��0��ʾ�������������1��ʾ�յ���������"<< qiaoinfo[i].begin_line[j1] << endl;
            }
            cout << "���š��յ����ӱʻ���:" << endl;
            for (int j1 = 0; j1 < qiaoinfo[i].end_line_begin.size(); j1++) {
                cout << "(" << qiaoinfo[i].end_line_begin[j1].x << "," << qiaoinfo[i].end_line_begin[j1].y << ")--("
                    << qiaoinfo[i].end_line_end[j1].x << "," << qiaoinfo[i].end_line_end[j1].y << ")" << endl;
                //cout << "���š����յ����ӵıʻ����롰�š������ӷ�ʽ��0��ʾ�������������1��ʾ�յ���������" << qiaoinfo[i].end_line[j1] << endl;

            }
            cout << endl;
        }
    }

    //�������š������begin_line��end_line���ϲ��ʻ�
    for (int i = 0; i < 20 && qiaoinfo[i].begin.x != 0; i++) {

        int count = 0;//�жϵ�ǰ���м���ʻ��κϲ�
        cout << endl;
        cout << "��ǰ��Ϊ��(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
        cout << "���š�������ӱʻ���:" << endl;
        for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
            cout << "(" << qiaoinfo[i].begin_line_begin[j1].x << "," << qiaoinfo[i].begin_line_begin[j1].y << ")--("
                << qiaoinfo[i].begin_line_end[j1].x << "," << qiaoinfo[i].begin_line_end[j1].y << ")" << endl;
            //cout <<"���š����յ����ӵıʻ����롰�š������ӷ�ʽ��0��ʾ�������������1��ʾ�յ���������"<< qiaoinfo[i].begin_line[j1] << endl;
        }
        cout << "���š��յ����ӱʻ���:" << endl;
        for (int j1 = 0; j1 < qiaoinfo[i].end_line_begin.size(); j1++) {
            cout << "(" << qiaoinfo[i].end_line_begin[j1].x << "," << qiaoinfo[i].end_line_begin[j1].y << ")--("
                << qiaoinfo[i].end_line_end[j1].x << "," << qiaoinfo[i].end_line_end[j1].y << ")" << endl;
            //cout << "���š����յ����ӵıʻ����롰�š������ӷ�ʽ��0��ʾ�������������1��ʾ�յ���������" << qiaoinfo[i].end_line[j1] << endl;

        }

        //�������š�������ӵıʻ���
        for (int begin_i = 0; begin_i < qiaoinfo[i].begin_line_begin.size() && qiaoinfo[i].begin_line_begin[begin_i].x != 0; begin_i++) {
            //�жϱʻ��η���
            int flag_trend = 0, flag_trend_start = 0, flag_trend_end = 0;//���Ƶ��жϷ�

            //�ҵ�strokesinfo�еĶ�Ӧλ��
            int sit = 0;//λ�üǺŷ�
            for (int j = 0; j < 20; j++) {
                if ((strokesinfo[j].begin.x == qiaoinfo[i].begin_line_begin[begin_i].x) && (strokesinfo[j].begin.y == qiaoinfo[i].begin_line_begin[begin_i].y)
                    && (strokesinfo[j].end.x == qiaoinfo[i].begin_line_end[begin_i].x) && (strokesinfo[j].end.y == qiaoinfo[i].begin_line_end[begin_i].y)) {
                    sit = j;
                }
            }
            cout << endl;
            cout << "�������š�������ӵıʻ���:(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--("
                << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

            //���š�������ӵıʻ��ε�������ŵ�������ڣ������ж�����
            if (qiaoinfo[i].begin_line[begin_i] == 0) {
                int zero = 0, one = 0, two = 0, three = 0;//����
                for (int i23 = 0; i23 < uw && i23 < strokesinfo[sit].snake.size(); i23++) {
                    //cout << strokesinfo[sit].snake[i23];
                    if (strokesinfo[sit].snake[i23] == 0 || strokesinfo[sit].snake[i23] == 4)zero++;
                    if (strokesinfo[sit].snake[i23] == 1 || strokesinfo[sit].snake[i23] == 5)one++;
                    if (strokesinfo[sit].snake[i23] == 2 || strokesinfo[sit].snake[i23] == 6)two++;
                    if (strokesinfo[sit].snake[i23] == 3 || strokesinfo[sit].snake[i23] == 7)three++;
                }
                int flag_dir = 0;
                //���ĸ���������
                if (zero >= one)
                {
                    flag_dir = 0;
                    if (two >= zero && two >= three) {
                        flag_dir = 2;
                    }
                    if (three >= zero && three >= two) {
                        flag_dir = 3;
                    }
                }
                if (one >= zero) {
                    flag_dir = 1;
                    if (two >= one && two >= three) {
                        flag_dir = 2;
                    }
                    if (three >= one && three >= two) {
                        flag_dir = 3;
                    }
                }
                flag_trend_start = flag_dir;
            }
            //���š�������ӵıʻ��ε��յ����ŵ�������ڣ������ж�����
            if (qiaoinfo[i].begin_line[begin_i] == 1) {
                int zero = 0, one = 0, two = 0, three = 0;//����
                for (int i23 = strokesinfo[sit].snake.size() - 1; i23 > strokesinfo[sit].snake.size() - 1 - uw && i23 > 0; i23--) {
                    //cout << endl;
                    //cout << strokesinfo[sit].snake[i23];
                    if (strokesinfo[sit].snake[i23] == 0 || strokesinfo[sit].snake[i23] == 4)zero++;
                    if (strokesinfo[sit].snake[i23] == 1 || strokesinfo[sit].snake[i23] == 5)one++;
                    if (strokesinfo[sit].snake[i23] == 2 || strokesinfo[sit].snake[i23] == 6)two++;
                    if (strokesinfo[sit].snake[i23] == 3 || strokesinfo[sit].snake[i23] == 7)three++;
                }
                int flag_dir = 0;
                //���ĸ���������
                if (zero >= one)
                {
                    flag_dir = 0;
                    if (two >= zero && two >= three) {
                        flag_dir = 2;
                    }
                    if (three >= zero && three >= two) {
                        flag_dir = 3;
                    }
                }
                if (one >= zero) {
                    flag_dir = 1;
                    if (two >= one && two >= three) {
                        flag_dir = 2;
                    }
                    if (three >= one && three >= two) {
                        flag_dir = 3;
                    }
                }
                flag_trend_start = flag_dir;
            }


            //�������š��յ����ӵıʻ���
            for (int end_i = 0; end_i < qiaoinfo[i].end_line_begin.size() && qiaoinfo[i].end_line_begin[end_i].x != 0; end_i++) {
                //�ҵ�strokesinfo�еĶ�Ӧλ��

                int sit1 = 0;//λ�üǺŷ�
                for (int j1 = 0; j1 < 20; j1++) {
                    if ((strokesinfo[j1].begin.x == qiaoinfo[i].end_line_begin[end_i].x) && (strokesinfo[j1].begin.y == qiaoinfo[i].end_line_begin[end_i].y)
                        && (strokesinfo[j1].end.x == qiaoinfo[i].end_line_end[end_i].x) && (strokesinfo[j1].end.y == qiaoinfo[i].end_line_end[end_i].y)) {
                        sit1 = j1;
                    }
                }
                cout << endl;
                cout << "�������š��յ����ӵıʻ���:(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--("
                    << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

                //���š��յ����ӵıʻ��ε�������ŵ�������ڣ������ж�����
                if (qiaoinfo[i].end_line[end_i] == 0) {
                    int zero = 0, one = 0, two = 0, three = 0;//����
                    for (int i24 = 0; i24 < uw && i24 < strokesinfo[sit1].snake.size(); i24++) {
                        //cout << strokesinfo[sit1].snake[i24];
                        if (strokesinfo[sit1].snake[i24] == 0 || strokesinfo[sit1].snake[i24] == 4)zero++;
                        if (strokesinfo[sit1].snake[i24] == 1 || strokesinfo[sit1].snake[i24] == 5)one++;
                        if (strokesinfo[sit1].snake[i24] == 2 || strokesinfo[sit1].snake[i24] == 6)two++;
                        if (strokesinfo[sit1].snake[i24] == 3 || strokesinfo[sit1].snake[i24] == 7)three++;
                    }
                    int flag_dir = 0;
                    //���ĸ���������
                    if (zero >= one)
                    {
                        flag_dir = 0;
                        if (two >= zero && two >= three) {
                            flag_dir = 2;
                        }
                        if (three >= zero && three >= two) {
                            flag_dir = 3;
                        }
                    }
                    if (one >= zero) {
                        flag_dir = 1;
                        if (two >= one && two >= three) {
                            flag_dir = 2;
                        }
                        if (three >= one && three >= two) {
                            flag_dir = 3;
                        }
                    }
                    flag_trend_end = flag_dir;
                }
                //���š��յ����ӵıʻ��ε�������ŵ��յ����ڣ������ж�����
                if (qiaoinfo[i].end_line[end_i] == 1) {
                    int zero = 0, one = 0, two = 0, three = 0;//����
                    for (int i24 = strokesinfo[sit1].snake.size() - 1; i24 > strokesinfo[sit1].snake.size() - 1 - uw && i24 > 0; i24--) {
                        //cout << strokesinfo[sit1].snake[i24];
                        if (strokesinfo[sit1].snake[i24] == 0 || strokesinfo[sit1].snake[i24] == 4)zero++;
                        if (strokesinfo[sit1].snake[i24] == 1 || strokesinfo[sit1].snake[i24] == 5)one++;
                        if (strokesinfo[sit1].snake[i24] == 2 || strokesinfo[sit1].snake[i24] == 6)two++;
                        if (strokesinfo[sit1].snake[i24] == 3 || strokesinfo[sit1].snake[i24] == 7)three++;
                    }
                    int flag_dir = 0;
                    //���ĸ���������
                    if (zero >= one)
                    {
                        flag_dir = 0;
                        if (two >= zero && two >= three) {
                            flag_dir = 2;
                        }
                        if (three >= zero && three >= two) {
                            flag_dir = 3;
                        }
                    }
                    if (one >= zero) {
                        flag_dir = 1;
                        if (two >= one && two >= three) {
                            flag_dir = 2;
                        }
                        if (three >= one && three >= two) {
                            flag_dir = 3;
                        }
                    }
                    flag_trend_end = flag_dir;
                }

                //��ȥ��ͬ�ıʻ��κ��ű���
                int flagk = 0;
                if (strokesinfo[sit].begin.x == strokesinfo[sit1].begin.x && strokesinfo[sit].begin.y == strokesinfo[sit1].begin.y &&
                    strokesinfo[sit].end.x == strokesinfo[sit1].end.x && strokesinfo[sit].end.y == strokesinfo[sit1].end.y) {
                    flagk = 1;
                }
                //��һ�μ�������ӱʻ����Ƿ���ŵĶ˵���ͬһ���������У�ʹ��ŷ�Ͼ����ж�
                if (distance(strokesinfo[sit].begin, qiaoinfo[i].begin) > uw && distance(strokesinfo[sit].end, qiaoinfo[i].begin) > uw) {
                    flagk = 1;
                }
                if (distance(strokesinfo[sit1].begin, qiaoinfo[i].end) > uw && distance(strokesinfo[sit1].end, qiaoinfo[i].end) > uw) {
                    flagk = 1;
                }

                if (flagk == 0) {
                    if (flag_trend_start == flag_trend_end || strokesinfo[sit].dir == strokesinfo[sit1].dir || abs(flag_trend_end - flag_trend_start) <= 1) {//
                        cout << endl;
                        cout << "==================================�ϲ��ʻ�================================��" << endl;
                        cout << "flag_trend_start=" << flag_trend_start << endl;
                        cout << "flag_trend_end=" << flag_trend_end << endl;

                        cout << "(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;
                        cout << "(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;
                        cout << endl;

                        count++;
                        Point replace_begin = strokesinfo[sit].begin;//ǰһ���ϲ��ʻ������
                        Point replace_end = strokesinfo[sit].end;//ǰһ���ϲ��ʻ����յ�
                        Point replace1_begin = strokesinfo[sit1].begin;//��һ���ϲ��ʻ������
                        Point replace1_end = strokesinfo[sit1].end;//��һ���ϲ��ʻ����յ�

                        //�ϲ������ʻ���
                        if (strokesinfo[sit].dir == 0) {
                            if (strokesinfo[sit].begin.y < strokesinfo[sit1].begin.y) {//sit1�ں���
                                strokesinfo[sit].end.x = strokesinfo[sit1].end.x;
                                strokesinfo[sit].end.y = strokesinfo[sit1].end.y;
                                strokesinfo[sit1].begin.x = strokesinfo[sit1].begin.y = 0;
                                strokesinfo[sit1].end.x = strokesinfo[sit1].end.y = 0;
                                //�����ǰ����strokesinfo��
                                //cout << "��ǰ��Ϊ��(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
                                for (int cl = 0; cl < 20; cl++) {
                                    if ((strokesinfo[cl].begin.x == qiaoinfo[i].begin.x) && (strokesinfo[cl].begin.y == qiaoinfo[i].begin.y)
                                        && (strokesinfo[cl].end.x == qiaoinfo[i].end.x) && (strokesinfo[cl].end.y == qiaoinfo[i].end.y)) {
                                        strokesinfo[cl].begin.x = strokesinfo[cl].begin.y = 0;
                                        strokesinfo[cl].end.x = strokesinfo[cl].end.y = 0;
                                        strokesinfo[cl].tem.clear();

                                    }
                                }
                                //����ŵ����ص�
                                for (int tem_i = 0; tem_i < qiaoinfo[i].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(qiaoinfo[i].tem[tem_i]));
                                }
                                //������ʻ��ε����ص�ӵ�ǰ���
                                for (int tem_i = 0; tem_i < strokesinfo[sit1].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(strokesinfo[sit1].tem[tem_i]));
                                }
                                //��պ���ʻ��ε����ص��������ŵ����ص�
                                strokesinfo[sit1].tem.clear();

                                //�滻���š��ṹ��ıʻ���
                                for (int rei = 0; rei < 20; rei++) {
                                    if (qiaoinfo[rei].begin.x != 0) {
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].begin_line_begin.size(); rej1++) {
                                            //�滻�Ѻϲ��ʻ��Σ�
                                            if (replace_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;
                                            }
                                            if (replace1_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace1_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }

                                        }
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].end_line_begin.size(); rej1++) {
                                            //�滻�Ѻϲ��ʻ��Σ�
                                            if (replace_begin == qiaoinfo[rei].end_line_begin[rej1] && replace_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit].end;
                                                // cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].end_line_begin[rej1] && replace1_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit].end;
                                                //cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }
                                        }
                                    }
                                }

                            }
                            if (strokesinfo[sit].begin.y > strokesinfo[sit1].begin.y) {//sit�ں���
                                strokesinfo[sit1].end.x = strokesinfo[sit].end.x;
                                strokesinfo[sit1].end.y = strokesinfo[sit].end.y;
                                strokesinfo[sit].begin.x = strokesinfo[sit].begin.y = 0;
                                strokesinfo[sit].end.x = strokesinfo[sit].end.y = 0;
                                //�����ǰ����strokesinfo��
                                //cout << "��ǰ��Ϊ��(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
                                for (int cl = 0; cl < 20; cl++) {
                                    if ((strokesinfo[cl].begin.x == qiaoinfo[i].begin.x) && (strokesinfo[cl].begin.y == qiaoinfo[i].begin.y)
                                        && (strokesinfo[cl].end.x == qiaoinfo[i].end.x) && (strokesinfo[cl].end.y == qiaoinfo[i].end.y)) {
                                        strokesinfo[cl].begin.x = strokesinfo[cl].begin.y = 0;
                                        strokesinfo[cl].end.x = strokesinfo[cl].end.y = 0;
                                        strokesinfo[cl].tem.clear();

                                    }
                                }
                                //����ŵ����ص�
                                for (int tem_i = 0; tem_i < qiaoinfo[i].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(qiaoinfo[i].tem[tem_i]));
                                }
                                //������ʻ��ε����ص�ӵ�ǰ���
                                for (int tem_i = 0; tem_i < strokesinfo[sit].tem.size(); tem_i++) {
                                    strokesinfo[sit1].tem.push_back(Point(strokesinfo[sit].tem[tem_i]));
                                }
                                //��պ���ʻ��ε����ص��������ŵ����ص�
                                strokesinfo[sit].tem.clear();

                                //�滻���š��ṹ��ıʻ���
                                for (int rei = 0; rei < 20; rei++) {
                                    if (qiaoinfo[rei].begin.x != 0) {
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].begin_line_begin.size(); rej1++) {
                                            //�滻�Ѻϲ��ʻ��Σ�
                                            if (replace_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit1].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit1].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace1_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit1].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit1].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

                                            }

                                        }
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].end_line_begin.size(); rej1++) {
                                            //�滻�Ѻϲ��ʻ��Σ�
                                            if (replace_begin == qiaoinfo[rei].end_line_begin[rej1] && replace_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit1].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit1].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].end_line_begin[rej1] && replace1_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit1].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit1].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            if (strokesinfo[sit].begin.x < strokesinfo[sit1].begin.x) {
                                strokesinfo[sit].end.x = strokesinfo[sit1].end.x;
                                strokesinfo[sit].end.y = strokesinfo[sit1].end.y;
                                strokesinfo[sit1].begin.x = strokesinfo[sit1].begin.y = 0;
                                strokesinfo[sit1].end.x = strokesinfo[sit1].end.y = 0;
                                //�����ǰ����strokesinfo��
                                //cout << "��ǰ��Ϊ��(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
                                for (int cl = 0; cl < 20; cl++) {
                                    if ((strokesinfo[cl].begin.x == qiaoinfo[i].begin.x) && (strokesinfo[cl].begin.y == qiaoinfo[i].begin.y)
                                        && (strokesinfo[cl].end.x == qiaoinfo[i].end.x) && (strokesinfo[cl].end.y == qiaoinfo[i].end.y)) {
                                        strokesinfo[cl].begin.x = strokesinfo[cl].begin.y = 0;
                                        strokesinfo[cl].end.x = strokesinfo[cl].end.y = 0;
                                        strokesinfo[cl].tem.clear();
                                    }
                                }


                                //�����
                                for (int tem_i = 0; tem_i < qiaoinfo[i].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(qiaoinfo[i].tem[tem_i]));
                                }
                                //������ʻ��ε����ص�ӵ�ǰ���
                                for (int tem_i = 0; tem_i < strokesinfo[sit1].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(strokesinfo[sit1].tem[tem_i]));
                                }
                                //��պ���ʻ��ε����ص��������ŵ����ص�
                                strokesinfo[sit1].tem.clear();

                                //�滻���š��ṹ��ıʻ���
                                for (int rei = 0; rei < 20; rei++) {
                                    if (qiaoinfo[rei].begin.x != 0) {
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].begin_line_begin.size(); rej1++) {
                                            //�滻�Ѻϲ��ʻ��Σ�
                                            if (replace_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace1_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }

                                        }
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].end_line_begin.size(); rej1++) {
                                            //�滻�Ѻϲ��ʻ��Σ�
                                            if (replace_begin == qiaoinfo[rei].end_line_begin[rej1] && replace_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].end_line_begin[rej1] && replace1_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "�滻��ıʻ���Ϊ��(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }

        if (count == 2) {
            //�жϵ�ǰ���š����ڡ�ʮ�����ͽ�������������������������ĵ�
            cout << "��ǰ���š����ڡ�ʮ�����ͽ�����" << endl;
            //���á��š��ʻ������㷨
            correct_qiao(image, image1, i, uw, qiaoinfo, edge_center, edge, strokesinfo);
        }
    }

}

//���ױ���������
void bezier_3(double p[4][2], vector<Point>& point_bezier_3)
{
    double t, t1, t2, xt, yt;
    int rate = 200, x, y;
    int count = 0;
    //setcolor(color);
    //moveto(p[0][0], p[0][1]);
    //cout << "��������Ϊ" << endl;
    //point_bezier_3.clear();
    for (t = 0; t <= 1; t += 1.0 / rate)
    {
        yt = 1 - t;
        t1 = yt * yt;
        t2 = 3 * yt * t;
        xt = p[0][0] * t1 * yt + p[1][0] * t2 * yt + p[2][0] * t2 * t + p[3][0] * t * t * t;
        yt = p[0][1] * yt * t1 + p[1][1] * t2 * yt + p[2][1] * t2 * t + p[3][1] * t * t * t;
        x = (int)(xt);
        y = (int)(yt);

        /* count++;
         cout << "��" << count << "����������Ϊ��(" << x << "," << y << ")" << endl;*/
        point_bezier_3.push_back(Point(x, y));

        //ȥ��
        for (size_t i = 0; i < point_bezier_3.size() - 1; i++) {
            if (x == point_bezier_3[i].x && y == point_bezier_3[i].y) {
                point_bezier_3.pop_back();
            }
        }
    }
    /*   for (size_t i = 0; i < point_bezier_3.size(); i++) {
           cout << "��" << i << "����������Ϊ��(" << point_bezier_3[i].x << "," << point_bezier_3[i].y << ")" << endl;
       }*/
}

//�������ͱʻ���ָĽ�������
void gou1(vector<Point>& S_0, vector<Point>& S_1, vector<Point>& S_2) {
      for (size_t i = 0; i < S_0.size(); i++) {
          cout << "��" << i << "��S_0��Ϊ��(" << S_0[i].x << "," << S_0[i].y << ")" << endl;
      }
      cout << endl;
      for (size_t i = 0; i < S_1.size(); i++) {
          cout << "��" << i << "��S_1��Ϊ��(" << S_1[i].x << "," << S_1[i].y << ")" << endl;
      }
      cout << endl;

      //S_0Ϊ��1��ʼ��ԭʼ���ͱʻ��㣬S_1Ϊ��һ�α�������Ϻ�ĵ�
    if (S_1.size() > 0 && S_0.size() > 0) {

        int t_count = 0;
        double t = 1.0 / S_1.size();
        for (size_t i = 0; i < S_1.size(); i++) {
            int flag = 0;
            Point tem;
            for (size_t j = 0; j < S_0.size(); j++) {
                if (S_1[i].x == S_0[j].x) {
                    tem.x = S_1[i].x;
                    tem.y = S_1[i].y * (1.0 - t * t_count) + S_0[j].y * t * t_count;
                    t_count++;
                    /* cout << "t_count=" << t_count << endl;
                     cout << "t=" << t << endl;
                     cout << "t*t_count=" << t * t_count << endl;
                     cout << endl;*/
                    S_2.push_back(Point(tem.x, tem.y));
                    flag = 1;
                }
            }
            if (flag == 0) {
                tem.x = S_1[i].x;
                tem.y = S_1[i].y * (1.0 - t * t_count) + S_0[S_0.size() - 1].y * t * t_count;
                S_2.push_back(Point(tem.x, tem.y));
            }
        }

        /*for (size_t i = 0; i < S_2.size(); i++) {
            cout << "��" << i << "��S_2��Ϊ��(" << S_2[i].x << "," << S_2[i].y << ")" << endl;
        }*/

        //����һ����ʱ����
        vector<Point> S_2_temp;
        S_2_temp.push_back(Point(S_2[0].x, S_2[0].y));

        //�ж�S_2���Ƿ�����������������������ص�
        for (size_t i = 1; i < S_2.size(); i++) {
            Point tem;
            tem = S_2[i];
            cout << endl;
            /*cout << "fabs(tem.x - S_2[i - 1].x======" << fabs(tem.x - S_2[i - 1].x) << endl;
            cout << "fabs(tem.y - S_2[i - 1].y======" << fabs(tem.y - S_2[i - 1].y) << endl;*/
            if (tem.x != S_2[i - 1].x || tem.y != S_2[i - 1].y) {
                //�жϵ�ǰ�㲻����һ����İ�������
                int flag = 0;
                if (fabs(tem.x - S_2[i - 1].x) <= 1) {
                    if (fabs(tem.y - S_2[i - 1].y) <= 1) {
                        flag = 1;
                        //cout << "flag=1" << endl;

                        S_2_temp.push_back(Point(tem.x, tem.y));
                        //cout << "("<<tem.x << "," << tem.y << ")" << endl;
                    }
                }
                if (flag == 0) {
                    //cout << "flag=0" << endl;
                    if ((fabs(tem.x - S_2[i - 1].x) > 1) && (fabs(tem.y - S_2[i - 1].y) <= 1)) {
                        //��x�������ڣ���Ҫ����Ӧ�����ص�
                        if (tem.x > S_2[i - 1].x) {
                            int count = tem.x - S_2[i - 1].x;
                            for (int j = 1; j < count; j++) {
                                S_2_temp.push_back(Point(S_2[i - 1].x + j, S_2[i - 1].y));
                                S_2_temp.push_back(Point(tem.x, tem.y));
                            }

                        }

                        if (tem.x < S_2[i - 1].x) {
                            int count = S_2[i - 1].x - tem.x;
                            for (int j = 1; j < count; j++) {
                                S_2_temp.push_back(Point(tem.x + j, tem.y));
                                S_2_temp.push_back(Point(tem.x, tem.y));
                            }

                        }

                    }

                    if ((fabs(tem.y - S_2[i - 1].y) > 1) && (fabs(tem.x - S_2[i - 1].x) <= 1)) {
                        //��y�������ڣ���Ҫ����Ӧ�����ص�
                        if (tem.y > S_2[i - 1].y) {
                            int count = tem.y - S_2[i - 1].y;
                            for (int j = 1; j < count; j++) {
                                S_2_temp.push_back(Point(tem.x, S_2[i - 1].y + j));
                                S_2_temp.push_back(Point(tem.x, tem.y));
                            }

                        }

                        if (tem.y < S_2[i - 1].y) {
                            int count = S_2[i - 1].y - tem.y;
                            for (int j = 1; j < count; j++) {
                                S_2_temp.push_back(Point(tem.x, tem.y + j));
                                S_2_temp.push_back(Point(tem.x, tem.y));
                            }
                        }
                    }
                }
            }
        }

        //cout << "S_2_temp��" << endl;
        //for (size_t i = 0; i < S_2_temp.size(); i++) {
        //    
        //    cout << "��" << i << "��S_2_temp��Ϊ=========��(" << S_2_temp[i].x << "," << S_2_temp[i].y << ")" << endl;
        //}

        S_2.clear();
        for (size_t i = 0; i < S_2_temp.size(); i++) {
            S_2.push_back(Point(S_2_temp[i].x, S_2_temp[i].y));
        }
    }
}

//1.21�޸ģ�����ʻ�����-�������ͱʻ���
void gou(Mat& image, Mat& image1, StrokesInfo* strokesinfo, vector<Point>& point_gou_mark, sfInfo* sfinfo, vector<Point>& se,
    int one_x, int two_x, int three_x, int four_x, int five_x, int six_x, int seven_x, int one_y, int two_y, int three_y, int four_y, int five_y,
    int six_y, int seven_y, double Median, vector<Point>& S_0, vector<Point>& S_1, vector<Point>& S_2, vector<Point>& s1,vector<Point>& point_bezier_3) {
    cout << endl;
    cout << "1.21�޸ģ�����ʻ����� - �������ͱʻ���" << endl;
    cout << "=====�ҵ�����Ϊ2�ıʻ���====" << endl;
    for (size_t i = 0; i < 20; i++) {
        if (strokesinfo[i].dir == 2 || strokesinfo[i].dir == 5) {
            cout << "����Ϊ2��5�ıʻ��Σ�(" << strokesinfo[i].begin.x << "," << strokesinfo[i].begin.y << ")--(" << strokesinfo[i].end.x << "," << strokesinfo[i].end.y << ")" << endl;

            //�ʻ�����==60
            if (strokesinfo[i].snake_length > 60) {
                //�ж���ֹ�㣨����7�������Ƿ���������˵㣨����3����2��//1.21�޸ģ��жϵ�7���ڵĽ������Ƿ�ֻ�������̱ʶ�����,�����������ʻ��ζ���һ��Ϊ�˵�
                int count = 0;
                point_gou_mark.clear();

                //�жϡ���7���Ƿ��ڽ������У������ڣ���˵��������ӵĲ�ֻһ���ʻ��Σ�
                int flag_7 = 0;//�����㴦�ڽ����ص�λ��
                vector<Point> flag_7vec;
                for (int j = 0; j < 20; j++) {
                    for (int j1 = 0; j1 < sfinfo[j].sf_info.size(); j1++) {
                        if (sfinfo[j].sf_info[j1].x == strokesinfo[i].end.x && sfinfo[j].sf_info[j1].y == strokesinfo[i].end.y) {
                            flag_7 = j;
                            cout << "����7�����ڽ������� flag_7 = " << flag_7 << endl;
                        }
                    }
                }
                //������7�����ڽ�������, ���ҡ���7����㴦�ڵĽ����صıʻ��β��洢��������
                if (flag_7 != 0) {
                    for (int k = 0; k < sfinfo[flag_7].sf_info.size(); k++) {
                        flag_7vec.push_back(Point(sfinfo[flag_7].sf_info[k].x, sfinfo[flag_7].sf_info[k].y));
                        cout << "����7�����ڽ�������" << endl;
                        cout << "(" << sfinfo[flag_7].sf_info[k].x << "," << sfinfo[flag_7].sf_info[k].y << ")" << endl;
                    }
                }
                for (int j12 = 0; j12 < flag_7vec.size(); j12++) {
                    cout << "(" << flag_7vec[j12].x << "," << flag_7vec[j12].y << ")" << endl;

                }
                //1.21�޸ģ��жϵ�7���ڵĽ������Ƿ�ֻ�������̱ʶ�����
                int mark6 = 0;//��Ϊ���Ƶ�6���ڱʻ��εı�Ƿ�
                int mark3 = 0;//��Ϊ���Ƶ�3���ڱʻ��εı�Ƿ�
                for (int j12 = 0; j12 < flag_7vec.size(); j12++) {
                    for (int index1 = 1; index1 < 20; index1++) {

                        //�ʻ�������ڽ�����У��յ�Ϊ�˵�
                        if (strokesinfo[index1].begin.x == flag_7vec[j12].x && strokesinfo[index1].begin.y == flag_7vec[j12].y && strokesinfo[index1].snake_length < Median) {

                            for (int j2 = 0; j2 < se.size(); j2++) {
                                if (strokesinfo[index1].end.x == se[j2].x && strokesinfo[index1].end.y == se[j2].y) {
                                    count++;
                                    cout << "count==" << count << endl;
                                    cout << "�ʻ�������ڽ�����У��յ�Ϊ�˵�" << endl;
                                    cout << "(" << strokesinfo[index1].end.x << "," << strokesinfo[index1].end.y << ")" << endl;
                                    //���Ƶ�2��
                                    two_x = strokesinfo[index1].end.x;
                                    two_y = strokesinfo[index1].end.y;

                                    mark6 = index1;
                                }
                            }
                        }
                        //�ʻ����յ��ڽ�����У����Ϊ�˵�
                        if (strokesinfo[index1].end.x == flag_7vec[j12].x && strokesinfo[index1].end.y == flag_7vec[j12].y && strokesinfo[index1].snake_length < Median) {
                            for (int j2 = 0; j2 < se.size(); j2++) {
                                if (strokesinfo[index1].begin.x == se[j2].x && strokesinfo[index1].begin.y == se[j2].y) {
                                    count++;
                                    cout << "count==" << count << endl;
                                    cout << "�ʻ����յ��ڽ�����У����Ϊ�˵�" << endl;
                                    cout << "(" << strokesinfo[index1].begin.x << "," << strokesinfo[index1].begin.y << ")" << endl;
                                    //���Ƶ�3��
                                    three_x = strokesinfo[index1].begin.x;
                                    three_y = strokesinfo[index1].begin.y;

                                    mark3 = index1;
                                }
                            }
                        }
                    }
                }

                //�����������Ķ̱ʻ���Ϊ2��
                if (count == 2) {
                    cout << "count==2" << endl;

                    //���Ƶ�7��
                    seven_x = strokesinfo[i].end.x;
                    seven_y = strokesinfo[i].end.y;

                    //���Ƶ�1��
                    one_x = three_x - (two_x - three_x);
                    int S_0_flag = 0;
                    for (int mark1 = 0; mark1 < strokesinfo[i].snake_length; mark1++) {
                        if (one_x == strokesinfo[i].tem[mark1].x) {
                            one_y = strokesinfo[i].tem[mark1].y;
                            S_0_flag = 1;
                        }
                        if (S_0_flag == 1) {
                            S_0.push_back(Point(strokesinfo[i].tem[mark1].x, strokesinfo[i].tem[mark1].y));
                        }
                    }

                    //��6��x:2��7��ƽ��
                    six_x = (seven_x + two_x) / 2;
                    for (int mark1 = 0; mark1 < strokesinfo[mark6].snake_length; mark1++) {
                        if (six_x == strokesinfo[mark6].tem[mark1].x) {
                            six_y = strokesinfo[mark6].tem[mark1].y;
                        }
                    }
                    //���Ƶ�4
                    four_x = two_x;
                    //���Ƶ�5
                    five_y = one_y;
                    //��4�͵�5����Ҫ�ڶ�ֵ����ĺڵ����ҵ�����Ҫ�޸ĵ�������������
                    for (size_t i = 0; i < s1.size(); i++) {
                        if (four_x == s1[i].x) {
                            if (image.at<uchar>(s1[i].x, s1[i].y + 1) == 255) {
                                four_y = s1[i].y;
                                //cout << "four_y=" << four_y << endl;
                            }
                        }
                    }
                    for (size_t i = 0; i < s1.size(); i++) {
                        if (five_y == s1[i].y) {
                            if (image.at<uchar>(s1[i].x + 1, s1[i].y) == 255) {
                                five_x = s1[i].x;
                                //cout << "five_x=" << five_x << endl;
                            }
                        }
                    }

                    if (one_x != 0 && one_y != 0 && two_x != 0 && two_y != 0 && three_x != 0 && three_y != 0 &&
                        four_x != 0 && four_y != 0 && five_x != 0 && five_y != 0 && six_x != 0 && six_y != 0 &&
                        seven_x != 0 && seven_y != 0) {
                        static double p[4][2] = { one_x,one_y,four_x,four_y,five_x,five_y,two_x,two_y };
                        bezier_3(p, point_bezier_3);
                        for (size_t i = 0; i < point_bezier_3.size(); i++) {
                            // cout << "��" << i << "����������Ϊ��(" << point_bezier_3[i].x << "," << point_bezier_3[i].y << ")" << endl;
                            S_1.push_back(Point(point_bezier_3[i].x, point_bezier_3[i].y));
                        }

                        static double p1[4][2] = { two_x,two_y,six_x,six_y,seven_x,seven_y,three_x,three_y };
                        bezier_3(p1, point_bezier_3);

                    }

                    //���ж��α�����������ϣ�
                    gou1(S_0,S_1, S_2);

                    //�޸�strokesinfo�ṹ��洢�ıʻ��Σ����������͵ı����������
                    vector<Point> zan;//���ص��ݴ���
                    vector<int> zan_8;//8�����ݴ���

                    //��strokesinfo�ṹ���д洢��1֮ǰ�����ص�
                    for (size_t mg = 0; mg < strokesinfo[i].tem.size(); mg++) {
                        zan.push_back(Point(strokesinfo[i].tem[mg].x, strokesinfo[i].tem[mg].y));
                        zan_8.push_back(strokesinfo[i].snake[mg]);
                        if (strokesinfo[i].tem[mg].x == one_x && strokesinfo[i].tem[mg].y == one_y) {
                            //zan.pop_back();
                            break;
                        }
                    }
                    //��strokesinfo�ṹ���д洢��1֮���S_2���ص�
                    for (size_t mg1 = 0; mg1 < S_2.size(); mg1++) {
                        //cout << "��" << mg1 << "����������Ϊ��(" << point_bezier_3[mg1].x << "," << point_bezier_3[mg1].y << ")" << endl;
                        zan.push_back(Point(S_2[mg1].x, S_2[mg1].y));
                        //����8����
                            //ͨ����һ����͵�ǰ��Ƚϣ��жϷ���
                        if (mg1 > 0) {
                            if (S_2[mg1].x - S_2[mg1 - 1].x == 0 && S_2[mg1].y - S_2[mg1 - 1].y == 1) {
                                zan_8.push_back(0);
                            }
                            if (S_2[mg1].x - S_2[mg1 - 1].x == -1 && S_2[mg1].y - S_2[mg1 - 1].y == 1) {
                                zan_8.push_back(1);
                            }
                            if (S_2[mg1].x - S_2[mg1 - 1].x == -1 && S_2[mg1].y - S_2[mg1 - 1].y == 0) {
                                zan_8.push_back(2);
                            }
                            if (S_2[mg1].x - S_2[mg1 - 1].x == -1 && S_2[mg1].y - S_2[mg1 - 1].y == -1) {
                                zan_8.push_back(3);
                            }
                            if (S_2[mg1].x - S_2[mg1 - 1].x == 0 && S_2[mg1].y - S_2[mg1 - 1].y == -1) {
                                zan_8.push_back(4);
                            }
                            if (S_2[mg1].x - S_2[mg1 - 1].x == 1 && S_2[mg1].y - S_2[mg1 - 1].y == -1) {
                                zan_8.push_back(5);
                            }
                            if (S_2[mg1].x - S_2[mg1 - 1].x == 1 && S_2[mg1].y - S_2[mg1 - 1].y == 0) {
                                zan_8.push_back(6);
                            }
                            if (S_2[mg1].x - S_2[mg1 - 1].x == 1 && S_2[mg1].y - S_2[mg1 - 1].y == 1) {
                                zan_8.push_back(7);
                            }
                        }
                    }


                    //��strokesinfo�ṹ���д洢S_2֮���ʣ�����ص�
                    for (size_t mg1 = S_1.size(); mg1 < point_bezier_3.size(); mg1++) {
                        //cout << "��" << mg1 << "����������Ϊ��(" << point_bezier_3[mg1].x << "," << point_bezier_3[mg1].y << ")" << endl;
                        zan.push_back(Point(point_bezier_3[mg1].x, point_bezier_3[mg1].y));
                        //����8����
                            //ͨ����һ����͵�ǰ��Ƚϣ��жϷ���
                        if (mg1 > 0) {
                            if (point_bezier_3[mg1].x - point_bezier_3[mg1 - 1].x == 0 && point_bezier_3[mg1].y - point_bezier_3[mg1 - 1].y == 1) {
                                zan_8.push_back(0);
                            }
                            if (point_bezier_3[mg1].x - point_bezier_3[mg1 - 1].x == -1 && point_bezier_3[mg1].y - point_bezier_3[mg1 - 1].y == 1) {
                                zan_8.push_back(1);
                            }
                            if (point_bezier_3[mg1].x - point_bezier_3[mg1 - 1].x == -1 && point_bezier_3[mg1].y - point_bezier_3[mg1 - 1].y == 0) {
                                zan_8.push_back(2);
                            }
                            if (point_bezier_3[mg1].x - point_bezier_3[mg1 - 1].x == -1 && point_bezier_3[mg1].y - point_bezier_3[mg1 - 1].y == -1) {
                                zan_8.push_back(3);
                            }
                            if (point_bezier_3[mg1].x - point_bezier_3[mg1 - 1].x == 0 && point_bezier_3[mg1].y - point_bezier_3[mg1 - 1].y == -1) {
                                zan_8.push_back(4);
                            }
                            if (point_bezier_3[mg1].x - point_bezier_3[mg1 - 1].x == 1 && point_bezier_3[mg1].y - point_bezier_3[mg1 - 1].y == -1) {
                                zan_8.push_back(5);
                            }
                            if (point_bezier_3[mg1].x - point_bezier_3[mg1 - 1].x == 1 && point_bezier_3[mg1].y - point_bezier_3[mg1 - 1].y == 0) {
                                zan_8.push_back(6);
                            }
                            if (point_bezier_3[mg1].x - point_bezier_3[mg1 - 1].x == 1 && point_bezier_3[mg1].y - point_bezier_3[mg1 - 1].y == 1) {
                                zan_8.push_back(7);
                            }
                        }
                    }

                    strokesinfo[i].tem.clear();
                    strokesinfo[i].snake.clear();
                    strokesinfo[i].end.x = strokesinfo[mark3].begin.x;
                    strokesinfo[i].end.y = strokesinfo[mark3].begin.y;
                    //�������Ҫ�������̱ʻ���
                    strokesinfo[mark6].tem.clear();
                    strokesinfo[mark3].tem.clear();
                    strokesinfo[mark6].begin.x = 0, strokesinfo[mark6].begin.y = 0;
                    strokesinfo[mark6].end.x = 0, strokesinfo[mark6].end.y = 0;
                    strokesinfo[mark3].begin.x = 0, strokesinfo[mark3].begin.y = 0;
                    strokesinfo[mark3].end.x = 0, strokesinfo[mark3].end.y = 0;
                    strokesinfo[mark6].snake_length = 0;
                    strokesinfo[mark3].snake_length = 0;
                    //���ص��滻����
                    for (size_t mg2 = 0; mg2 < zan.size(); mg2++) {
                        strokesinfo[i].tem.push_back(Point(zan[mg2].x, zan[mg2].y));
                    }
                    //8�����滻����
                    for (size_t mg2 = 0; mg2 < zan_8.size(); mg2++) {
                        strokesinfo[i].snake.push_back(zan_8[mg2]);
                    }
                }
            }
        }
    }

}

//�ҳ�A��̱ʻ�����Ҫ�ϲ��ıʻ����кϲ�
void A_Combine(Mat& image, int NPB, int NSP,StrokesInfo* strokesinfo_com, double Median, vector<Point>& se, vector<Point>& sf,sfInfo* sfinfo) {
    int uw = NPB / NSP;
    Mat Aimage = image.clone();
    for (int i = 0; i < 20; i++)
    {
        if (strokesinfo_com[i].begin.x != 0 && strokesinfo_com[i].tem.size() < Median) {
            cout << "A��̱ʻ���(" << strokesinfo_com[i].begin.x << "," << strokesinfo_com[i].begin.y << ")--(" << strokesinfo_com[i].end.x << "," << strokesinfo_com[i].end.y << ")" << endl;
            /*int color = Aimage.at<uchar>((strokesinfo_com[i].begin.x, strokesinfo_com[i].begin.y));
            cout << "ͼ���ֵ��Ϊ��" << color << endl;*/
            int jiaochadian = 0, duandian = 0;
            //�ҵ��˵�se
            for (int k = 0; k < se.size(); k++) {
                if (strokesinfo_com[i].begin == se[k]) {
                    duandian = width_new(strokesinfo_com[i].begin, Aimage, uw);
                    cout << "�˵�ıʿ�Ϊ��" << duandian << endl;
                }
                if (strokesinfo_com[i].end == se[k]) {
                    duandian = width_new(strokesinfo_com[i].end, Aimage, uw);
                    cout << "�˵�ıʿ�Ϊ��" << duandian << endl;
                }
            }
            //�ҵ������sf
            for (int k = 0; k < sf.size(); k++) {
                if (strokesinfo_com[i].begin == sf[k]) {
                    jiaochadian = width_new(strokesinfo_com[i].begin, Aimage, uw);
                    cout << "�����ıʿ�Ϊ��" << jiaochadian << endl;
                }
                if (strokesinfo_com[i].end == sf[k]) {
                    jiaochadian = width_new(strokesinfo_com[i].end, Aimage, uw);
                    cout << "�����ıʿ�Ϊ��" << jiaochadian << endl;
                }
            }
            //�жϱʻ��Ƿ���Ҫ�ϲ����Ӷ˵㵽�����ıʿ����Ǵ�ϸ����
            //�����ж϶˵�ʿ�<�����ʿ�
            if (duandian < jiaochadian) {
                //�жϽ���������Ľ�����
                for (int j = 0; j < 20; j++) {
                    for (int n = 0; n < sfinfo[j].sf_info.size(); n++) {
                        //�ʻ�begin�ڽ������
                        if (strokesinfo_com[i].begin == sfinfo[j].sf_info[n]) {
                            //�ϲ��̱ʻ������佻���������ķ���Ϊ2�ıʻ����кϲ�
                            for (int n1 = 0; n1 < sfinfo[j].sf_info.size(); n1++) {
                                if (n1 != n) {
                                    for (int i1 = 0; i1 < 20; i1++)
                                    {
                                        if (strokesinfo_com[i1].begin == sfinfo[j].sf_info[n1] && strokesinfo_com[i1].dir == 2) {
                                            cout << "���ڷ���Ϊ2�ıʻ�:�̱ʻ�begin�ڽ���أ�2�ʻ�begin�ڽ����" << endl;
                                            cout << strokesinfo_com[i1].begin.x << "," << strokesinfo_com[i1].begin.y << ")--(" << strokesinfo_com[i1].end.x << "," << strokesinfo_com[i1].end.y << ")" << endl;
                                        }
                                        if (strokesinfo_com[i1].end == sfinfo[j].sf_info[n1] && strokesinfo_com[i1].dir == 2) {
                                            cout << "���ڷ���Ϊ2�ıʻ�:�̱ʻ�begin�ڽ���أ�2�ʻ�end�ڽ����" << endl;
                                            cout << strokesinfo_com[i1].begin.x << "," << strokesinfo_com[i1].begin.y << ")--(" << strokesinfo_com[i1].end.x << "," << strokesinfo_com[i1].end.y << ")" << endl;

                                        }
                                    }
                                }
                            }
                        }
                        //�ʻ�end�ڽ������
                        if (strokesinfo_com[i].end == sfinfo[j].sf_info[n]) {
                            //�ϲ��̱ʻ������佻���������ķ���Ϊ2�ıʻ����кϲ�
                            for (int n1 = 0; n1 < sfinfo[j].sf_info.size(); n1++) {
                                if (n1 != n) {
                                    for (int i1 = 0; i1 < 20; i1++)
                                    {
                                        if (strokesinfo_com[i1].begin == sfinfo[j].sf_info[n1] && strokesinfo_com[i1].dir == 2) {
                                            cout << "���ڷ���Ϊ2�ıʻ�:�̱ʻ�end�ڽ���أ�2�ʻ�begin�ڽ����" << endl;
                                            cout << strokesinfo_com[i1].begin.x << "," << strokesinfo_com[i1].begin.y << ")--(" << strokesinfo_com[i1].end.x << "," << strokesinfo_com[i1].end.y << ")" << endl;
                                            //�ϲ�strokesinfo_com������
                                            strokesinfo_com[i].end = strokesinfo_com[i1].end;
                                            strokesinfo_com[i1].begin = strokesinfo_com[i1].end = Point(0, 0);
                                            for (int i2 = 0; i2 < strokesinfo_com[i1].tem.size(); i2++) {
                                                strokesinfo_com[i].tem.push_back(strokesinfo_com[i1].tem[i2]);
                                            }
                                            strokesinfo_com[i1].tem.clear();

                                        }
                                        if (strokesinfo_com[i1].end == sfinfo[j].sf_info[n1] && strokesinfo_com[i1].dir == 2) {
                                            cout << "���ڷ���Ϊ2�ıʻ�:�̱ʻ�end�ڽ���أ�2�ʻ�end�ڽ����" << endl;
                                            cout << strokesinfo_com[i1].begin.x << "," << strokesinfo_com[i1].begin.y << ")--(" << strokesinfo_com[i1].end.x << "," << strokesinfo_com[i1].end.y << ")" << endl;

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


//���ƺϲ��ʻ�֮��Ĳ�ͼ��1.16���롰�š��ĺϲ�
Mat draw_picture1(Mat& image, vector<Point>& s1, StrokesInfo* strokesinfo_com, vector<Point>& point_bezier_2,
    vector<Point>& point_bezier_3, vector<Point>& S_2, int NPB, int NSP, sfInfo* sfinfo, vector<Point>& edge_center, vector<Point>& edge) {
    int uw = NPB / NSP;//ƽ���ʻ����
    int a = 1;
    int b = 1;
    int c = 1;
    //����ת��Ϊ��ɫͼ��
    Mat draw1 = channelSwitching(image);
    //�½��׵�ͼ��
    for (int i = 0; i < draw1.rows; i++)
    {
        for (int j = 0; j < draw1.cols; j++)
        {

            draw1.at<Vec3b>(i, j)[0] = 255;
            draw1.at<Vec3b>(i, j)[1] = 255;
            draw1.at<Vec3b>(i, j)[2] = 255;
        }
    }
    //������ֵ���ҵ�
    for (size_t i = 0; i < s1.size(); i++)
    {
        Point tems;
        tems = s1[i];
        draw1.at<Vec3b>(tems.x, tems.y)[0] = 200;
        draw1.at<Vec3b>(tems.x, tems.y)[1] = 200;
        draw1.at<Vec3b>(tems.x, tems.y)[2] = 200;
    }

    //����1026�����ƺϲ��ʻ�֮��Ĳ�ͼ��ʹ��strokesinfo_com
    for (size_t i = 0; i < 20; i++)
    {
        a += 57;
        b += 97;
        c += 119;
        for (size_t j = 0; j < strokesinfo_com[i].tem.size(); j++)
        {
            Point tems;
            tems = strokesinfo_com[i].tem[j];
            draw1.at<Vec3b>(tems.x, tems.y)[0] = a;
            draw1.at<Vec3b>(tems.x, tems.y)[1] = b;
            draw1.at<Vec3b>(tems.x, tems.y)[2] = c;
        }
    }

    //11.13������ɽ���ĺ��۱ʻ����ʻ�����Ϊ6
    for (size_t i = 0; i < 20; i++) {
        if (strokesinfo_com[i].dir == 6) {
            for (size_t j = 0; j < strokesinfo_com[i].tem.size(); j++)
            {
                Point tems;
                tems = strokesinfo_com[i].tem[j];
                draw1.at<Vec3b>(tems.x, tems.y)[0] = 57;
                draw1.at<Vec3b>(tems.x, tems.y)[1] = 33;
                draw1.at<Vec3b>(tems.x, tems.y)[2] = 108;
            }
        }
    }

    S_2.clear();

    //��������������
    for (int i = 0; i <= 20; i++) {
        draw1.at<Vec3b>(sfinfo[i].Pc.x, sfinfo[i].Pc.y)[0] = 57;
        draw1.at<Vec3b>(sfinfo[i].Pc.x, sfinfo[i].Pc.y)[1] = 33;
        draw1.at<Vec3b>(sfinfo[i].Pc.x, sfinfo[i].Pc.y)[2] = 110;
    }
    ////��������������
    //for (int i = 0; i < edge_center.size(); i++) {
    //    draw1.at<Vec3b>(edge_center[i].x, edge_center[i].y)[0] = 255;
    //    draw1.at<Vec3b>(edge_center[i].x, edge_center[i].y)[1] = 0;
    //    draw1.at<Vec3b>(edge_center[i].x, edge_center[i].y)[2] = 0;
    //    //����������
    //    for (int i1 = -2 * uw; i1 <= 2 * uw; i1++) {
    //        Point crosspoint;
    //        crosspoint.x = edge_center[i].x + 2 * uw;
    //        crosspoint.y = edge_center[i].y + i1;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[0] = 255;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[1] = 0;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[2] = 22;
    //    }
    //    for (int i2 = -2 * uw; i2 <= 2 * uw; i2++) {
    //        Point crosspoint;
    //        crosspoint.x = edge_center[i].x - 2 * uw;
    //        crosspoint.y = edge_center[i].y + i2;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[0] = 255;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[1] = 0;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[2] = 22;
    //    }
    //    for (int i3 = -2 * uw; i3 <= 2 * uw; i3++) {
    //        Point crosspoint;
    //        crosspoint.x = edge_center[i].x + i3;
    //        crosspoint.y = edge_center[i].y + 2 * uw;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[0] = 255;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[1] = 0;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[2] = 22;
    //    }
    //    for (int i4 = -2 * uw; i4 <= 2 * uw; i4++) {
    //        Point crosspoint;
    //        crosspoint.x = edge_center[i].x + i4;
    //        crosspoint.y = edge_center[i].y - 2 * uw;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[0] = 255;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[1] = 0;
    //        draw1.at<Vec3b>(crosspoint.x, crosspoint.y)[2] = 22;
    //    }
    //}
    //��һ������̵�edge
    for (int i = 0; i < edge.size(); i++) {
        cout << "edge��̾���㣺(" << edge[i].x << "," << edge[i].y << ")" << endl;
        draw1.at<Vec3b>(edge[i].x, edge[i].y)[0] = 255;
        draw1.at<Vec3b>(edge[i].x, edge[i].y)[1] = 390;
        draw1.at<Vec3b>(edge[i].x, edge[i].y)[2] = 110;
    }

    return draw1;
}

