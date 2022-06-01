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

int max(int x, int y) //在源文件中实现函数方法
{
	return x > y ? x : y;
}

//输入两个点，返回欧氏距离
int distance(Point& a, Point& b) {
    int dis1 = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return dis1;
}

//zhang细化改进算法
void zhang_thinimage_improve(Mat& srcimage)//单通道、二值化后的图像  
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
                        //得到1的个数，目标点像素值为1
                        whitepointtotal = whitepointtotal + Zhangmude[k];
                    }
                    if ((whitepointtotal >= 2) && (whitepointtotal <= 6))
                    {
                        //得到01的个数
                        int ap = 0;
                        if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;
                        if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;
                        if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;
                        if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;
                        if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;
                        if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;
                        if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;
                        if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;
                        //计算bp
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
                                deletelist1.push_back(Point(i, j));  //满足条件，去除该点
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

//单通道转三通道
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

//找出3类像素点和交叉点簇
void search_point(Mat& image, vector<Point>& se, vector<Point>& sf,vector<Point>& s, vector<Point>& sef, sfInfo* sfinfo) {

    int eightmude[9];
    int nl = image.rows;
    int nc = image.cols;
    se.clear();//端点容器清空
    sf.clear();//交叉点容器清空
    s.clear();//普通点
    sef.clear();//端点＋交叉点
    //s1.clear();//二值化后的黑点
    //清空交叉簇
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
            //对像素点为黑，即0，进行8邻域判断点的类型
            if (data[j] == 0) {
                if (data[j + 1] == 0) eightmude[0] = 1;//1表示存在像素点为黑
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
                int blacktotal = 0;//计算邻居总数
                for (int i = 0; i < 8; i++) {
                    blacktotal = blacktotal + eightmude[i];
                }
                //判断点的类型：普通点、端点、交叉点
                if (blacktotal == 1) {
                    se.push_back(Point(i, j));  //满足条件为端点
                    sef.push_back(Point(i, j));
                }
                else if (blacktotal >= 3) {
                    sf.push_back(Point(i, j));  //满足条件为交叉点
                    sef.push_back(Point(i, j));
                }
                else {
                    s.push_back(Point(i, j));  //满足条件为普通点
                }
            }
        }
    }
    //输出端点、交叉点
    cout << "端点：" << endl;
    for (int i = 0; i < se.size(); i++) {
        cout << "(" << se[i].x << "," << se[i].y << ")" << endl;
    }
    cout << "交叉点：" << endl;
    for (int i = 0; i < sf.size(); i++) {
        cout << "(" << sf[i].x << "," << sf[i].y << ")" << endl;
    }
    cout << "交叉点簇：" << endl;
    int flag = 0;
    //遍历交叉点，若后一个交叉点和前一个相邻，则将前一个交叉点，不相邻则另起
    for (int i = 0; i < sf.size() - 1; i++) {
        //若当前交叉点和后一个相邻，则将当前交叉点存储进sfInfo
        if (sqrt((sf[i].x - sf[i + 1].x) * (sf[i].x - sf[i + 1].x) + (sf[i].y - sf[i + 1].y) * (sf[i].y - sf[i + 1].y)) < 2) {
            sfinfo[flag].sf_info.push_back(Point(sf[i].x, sf[i].y));
            cout << "(" << sf[i].x << "," << sf[i].y << ")" << endl;
        }
        else
        {
            //若当前交叉点和后一个不相邻，但与前一个相邻，则将当前交叉点存储进sfInfo
            if ((i > 0) && (sqrt((sf[i].x - sf[i - 1].x) * (sf[i].x - sf[i - 1].x) + (sf[i].y - sf[i - 1].y) * (sf[i].y - sf[i - 1].y)) < 2)) {
                sfinfo[flag].sf_info.push_back(Point(sf[i].x, sf[i].y));
                cout << "(" << sf[i].x << "," << sf[i].y << ")" << endl;
                cout << endl;
                flag++;
            }
        }
    }
    //还要加上最后一个交叉点
    if ((sqrt((sf[sf.size() - 1].x - sf[sf.size() - 2].x) * (sf[sf.size() - 1].x - sf[sf.size() - 2].x) + (sf[sf.size() - 1].y - sf[sf.size() - 2].y) * (sf[sf.size() - 1].y - sf[sf.size() - 2].y)) < 2)) {
        sfinfo[flag].sf_info.push_back(Point(sf[sf.size() - 1].x, sf[sf.size() - 1].y));
        cout << "(" << sf[sf.size() - 1].x << "," << sf[sf.size() - 1].y << ")" << endl;
    }

    //计算交叉点簇中心
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
        cout << "交叉点簇中心：(" << sfinfo[i].Pc.x << "," << sfinfo[i].Pc.y << ")" << endl;
    }
}

//输入起点和终点，返回方向值|| 新增：“横折”为方向5、“竖折”为方向6
int direction_combine(Point& start, Point& end, StrokesInfo* strokesinfo, double strokes_ave) {
    int zero = 0, one = 0, two = 0, three = 0;//方向
    int x_plus = 0, x_sub = 0, y_plus = 0, y_sub = 0;//辅助方向
    int flag = 0;//方向值
    int count = 0;//笔画长度
    Point cur, next;

    vector<int> x_Plus;//x正方向，不移动存0
    vector<int> x_Sub;//x负方向，不移动存0
    vector<int> y_Plus;//y正方向，不移动存0
    vector<int> y_Sub;//y负方向，不移动存0

    //清空
    x_Plus.clear();
    x_Sub.clear();
    y_Plus.clear();
    y_Sub.clear();

    //在数组strokesinfo中找方向
    for (int flag_direction = 0; flag_direction < 20; flag_direction++) {
        if ((start.x == strokesinfo[flag_direction].begin.x && start.y == strokesinfo[flag_direction].begin.y)
            && (end.x == strokesinfo[flag_direction].end.x && end.y == strokesinfo[flag_direction].end.y)) {
            //flag = strokesinfo[flag_direction].dir;
            for (int flag_l = 0; flag_l < strokesinfo[flag_direction].snake_length; flag_l++) {
                //方向0：当前点同一行，故x不变；当前点下一列，+y的计数自增1；
                if (strokesinfo[flag_direction].snake[flag_l] == 0) {
                    y_plus++;
                    count++;
                    zero++;
                    //添加附加判断容器
                    x_Plus.push_back(0);
                    x_Sub.push_back(0);
                    y_Plus.push_back(1);
                    y_Sub.push_back(0);
                }
                //方向1：当前点上一行，-x的计数自增1；当前点下一列，+y的计数自增1；
                if (strokesinfo[flag_direction].snake[flag_l] == 1) {
                    x_sub++;
                    y_plus++;
                    count++;
                    one++;
                    //添加附加判断容器
                    x_Plus.push_back(0);
                    x_Sub.push_back(1);
                    y_Plus.push_back(1);
                    y_Sub.push_back(0);
                }
                //方向2：当前点上一行，-x的计数自增1；当前点同一列，不变；
                if (strokesinfo[flag_direction].snake[flag_l] == 2) {
                    x_sub++;
                    count++;
                    two++;
                    //添加附加判断容器
                    x_Plus.push_back(0);
                    x_Sub.push_back(1);
                    y_Plus.push_back(0);
                    y_Sub.push_back(0);
                }
                //方向3：当前点上一行，-x的计数自增1；当前点上一列，-y的计数自增1；
                if (strokesinfo[flag_direction].snake[flag_l] == 3) {
                    x_sub++;
                    y_sub++;
                    count++;
                    three++;
                    //添加附加判断容器
                    x_Plus.push_back(0);
                    x_Sub.push_back(1);
                    y_Plus.push_back(0);
                    y_Sub.push_back(1);
                }
                //方向4：当前点同一行，故x不变；当前点上一列，-y的计数自增1；
                if (strokesinfo[flag_direction].snake[flag_l] == 4) {
                    y_sub++;
                    count++;
                    zero++;
                    //添加附加判断容器
                    x_Plus.push_back(0);
                    x_Sub.push_back(0);
                    y_Plus.push_back(0);
                    y_Sub.push_back(1);
                }
                //方向5：当前点下一行，+x的计数自增1；当前点上一列，-y的计数自增1；
                if (strokesinfo[flag_direction].snake[flag_l] == 5) {
                    x_plus++;
                    y_sub++;
                    count++;
                    one++;
                    //添加附加判断容器
                    x_Plus.push_back(1);
                    x_Sub.push_back(0);
                    y_Plus.push_back(0);
                    y_Sub.push_back(1);
                }
                //方向6：当前点下一行，+x的计数自增1；当前点同一列，不变；
                if (strokesinfo[flag_direction].snake[flag_l] == 6) {
                    x_plus++;
                    count++;
                    two++;
                    //添加附加判断容器
                    x_Plus.push_back(1);
                    x_Sub.push_back(0);
                    y_Plus.push_back(0);
                    y_Sub.push_back(0);
                }
                //方向7：当前点下一行，+x的计数自增1；当前点下一列，+y的计数自增1；
                if (strokesinfo[flag_direction].snake[flag_l] == 7) {
                    x_plus++;
                    y_plus++;
                    count++;
                    three++;
                    //添加附加判断容器
                    x_Plus.push_back(1);
                    x_Sub.push_back(0);
                    y_Plus.push_back(1);
                    y_Sub.push_back(0);
                }
            }
            int flag_dir = 0;
            //找四个数中最大的
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

            ////通过辅助笔画区分“横0”和“横折5”      
            //cout << "辅助方向+x=" << x_plus << endl;
            //cout << "辅助方向-x=" << x_sub << endl;
            //cout << "辅助方向+y=" << y_plus << endl;
            //cout << "辅助方向-y=" << y_sub << endl;
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
            //cout << "=======count:笔画长度===========" << count << endl;

            if (count > strokes_ave) {
                //判断 + x辅助方向
                int x_Plus_count_before0 = 0;//判断标志：+x辅助方向前半段基本为0
                int x_Plus_count_after0 = 0;//判断标志：+x辅助方向前半段基本为0

                int x_Plus_count_before1 = 0;//判断标志：+x辅助方向前半段基本为1
                int x_Plus_count_after1 = 0;//判断标志：+x辅助方向后半段基本为1

                int x_Plus_flag = 0;//判断标志
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
                    x_Plus_flag = 1;//表示横折的一部分成立
                }
                if ((x_Plus_count_before1 >= count * 0.4 * 0.5) && (x_Plus_count_after0 >= count * 0.4 * 0.5)) {
                    x_Plus_flag = 2;//表示竖折的一部分成立
                }
                //判断 +y 辅助方向
                int y_Plus_count_before0 = 0;//判断+y辅助方向前半段基本为0
                int y_Plus_count_before1 = 0;//判断+y辅助方向前半段基本为1
                int y_Plus_count_after0 = 0;//判断+y辅助方向后半段基本为0
                int y_Plus_count_after1 = 0;//判断+y辅助方向后半段基本为1
                int y_Plus_flag = 0;//判断标志

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

                //横折笔画==5
                if ((x_Plus_flag == 1) && (y_Plus_flag == 1)) {
                    flag = 5;
                    cout << "方向修改为5" << endl;
                    cout << endl;
                }

                //竖折笔画==6
                if ((x_Plus_flag == 2) && (y_Plus_flag == 2)) {
                    flag = 6;
                    cout << "方向修改为6" << endl;
                    cout << endl;
                }
            }
        }
    }
    return flag;
}

//将骨架笔画存储进结构体数组strokesinfo (1026增加：笔画方向为0的可能需要调换起始点)
void Save_strokesinfo(int num, vector<Point>& newpoint_mark, vector<Point>& newpoint, StrokesInfo* strokesinfo, double strokes_ave) {

    //初始化结构体数组strokesinfo
    for (int index = 0; index < 20; index++)
    {
        strokesinfo[index].begin.x = strokesinfo[index].begin.y = 0;
        strokesinfo[index].end.x = strokesinfo[index].end.y = 0;
        strokesinfo[index].snake_length = 0;
        strokesinfo[index].snake.clear();
        strokesinfo[index].dir = 0;
        strokesinfo[index].tem.clear();
        strokesinfo[index].num = 0;//存储数组内成员个数
        strokesinfo[index].com_mark = 0;//合并笔画标记
        strokesinfo[index].com_mark_max = 0;//标记com_mark的最大值
    }
    //存储起始点、终止点
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

    //存储8链码序列
    int flag_b = -1;//起点位置
    int length = 0;//8链码长度

    for (int index = 0; index < num; index++)
    {

        strokesinfo[index].snake_length = 0;
        strokesinfo[index].com_mark = 0;//合并笔画标记初始化0
        for (size_t j = flag_b + length + 1; j < newpoint.size(); j++) {
            int mark = 0;
            int zero = 0, one = 0, two = 0, three = 0;//计数变量

            if (strokesinfo[index].begin.x == newpoint[j].x && strokesinfo[index].begin.y == newpoint[j].y) {
                //存储起始点：
               /* cout << "起始点：(" << strokesinfo[index].begin.x << "," << strokesinfo[index].begin.y << ")" << endl;
                cout << "起始点的后一个点为：(" << newpoint[j+1].x << "," << newpoint[j + 1].y << ")" << endl;
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
                    cout << "newpoint[]===：(" << newpoint[i].x << "," << newpoint[i].y << ")" << endl;
                    //存储像素点
                    strokesinfo[index].tem.push_back(newpoint[i]);
                    //通过后一个点和当前点比较，判断方向
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
                        cout << "终止点：(" << strokesinfo[index].end.x << "," << strokesinfo[index].end.y << ")" << endl;
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
    //存储数组内成员个数
    strokesinfo[0].num = num;

    //笔画方向
    for (int index = 0; index < num; index++) {
        int flag = direction_combine(strokesinfo[index].begin, strokesinfo[index].end, strokesinfo, strokes_ave);
        strokesinfo[index].dir = flag;
    }
    //(1026增加：笔画方向为0的可能需要调换起始点)
    for (int index = 0; index < num; index++) {
        if (strokesinfo[index].dir == 0) {
            //cout << "strokesinfo[index].dir == 0" << endl;
            if (strokesinfo[index].begin.y > strokesinfo[index].end.y) {
                //起始点反过来
                //cout<< "strokesinfo[index].begin.y > strokesinfo[index].end.y" << endl;
                Point begin_ver = strokesinfo[index].begin;
                Point end_ver = strokesinfo[index].end;
                strokesinfo[index].begin = end_ver;
                strokesinfo[index].end = begin_ver;
                /* cout << "begin==(" << strokesinfo[index].begin.x << "," << strokesinfo[index].begin.y << ")" << endl;
                 cout << "end==(" << strokesinfo[index].end.x << "," << strokesinfo[index].end.y << ")" << endl;*/
                 //方向容器反过来
                vector<int> snake_ver;
                for (int i = strokesinfo[index].snake_length - 1; i >= 0; i--) {
                    snake_ver.push_back((strokesinfo[index].snake[i] + 4) % 8);
                }
                strokesinfo[index].snake.clear();
                for (int i = 0; i < snake_ver.size(); i++) {
                    strokesinfo[index].snake.push_back(snake_ver[i]);
                    //cout << snake_ver[i];
                }
                //像素点容器反过来
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

    cout << " 将骨架笔画存储进结构体数组 " << endl;
    for (int index = 0; index < num; index++)
    {
        cout << endl;
        cout << "begin==(" << strokesinfo[index].begin.x << "," << strokesinfo[index].begin.y << ")" << endl;
        cout << "end==(" << strokesinfo[index].end.x << "," << strokesinfo[index].end.y << ")" << endl;
        cout << "存储8链码序列长度==" << strokesinfo[index].snake_length << endl;
        for (int i = 0; i < strokesinfo[index].snake_length; i++) {
            cout << strokesinfo[index].snake[i];
        }
        cout << "笔画方向==" << strokesinfo[index].dir << endl;
        cout << "笔画像素点：" << endl;
        for (int i = 0; i <= strokesinfo[index].snake_length; i++) {
            cout << "(" << strokesinfo[index].tem[i].x << "," << strokesinfo[index].tem[i].y << ") ";
        }
        cout << endl;
    }
}

//3.3计算笔画宽度,需要笔画像素点的坐标和灰度图像
int width_new(Point& center, Mat& image, int uw) {
    //以center为中心，检查四个角落
    Point mark1, mark2, mark3, mark4;
    //cout << "center点:(" << center.x << "," << center.y << ")" << endl;
    int shortdis = 100;//最短距离

    for (int i = 0; i < 5 * uw; i++) {//圈数
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

//计算笔画段长度均值、标准差、中位数
void ave(StrokesInfo* strokesinfo, double strokes_ave, double variance, double* Median) {
    //求8链码序列的均值、方差
    int sum = 0, num = 0;
    vector <int> maopao;//冒泡排序容器
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
    //找中位数
    for (int i = 0; i < num - 1; ++i) {
        for (int j = i + 1; j < num; ++j) {
            if (maopao[i] > maopao[j]) {
                swap(maopao[i], maopao[j]);
            }
        }
    }
    *Median = maopao[num / 2];
    cout << "均值========" << ave << endl;
    cout << "方差===================" << variance1 << endl;
    cout << "标准差===================" << sqrt(variance1) << endl;
    cout << "中位数===================" << Median << endl;
    cout << endl;
}

//获取骨架笔画{有注释}
void craw_stroke(Mat& image, vector<Point>& se, vector<Point>& sf,
    vector<Point>& s, vector<Point>& sef, vector<Point>& newpoint_mark, vector<Point>& newpoint, vector<int>& dir) {
    Mat image1 = image.clone();//11.27更新，image1用于过去笔画的更新算法
    Point tem, cur, p, q, front;

    int flag = 0;
    int count = 0;
    //从端点或交叉点出发,找出当前点的8邻域中下一个点的方向
    for (size_t i = 0; i < sef.size(); i++)
    {
        tem = sef[i];
        q.y = cur.y = tem.y;//初始化点
        q.x = cur.x = tem.x;
        cout << endl;
        cout << "预想起始点" << "(" << tem.x << "," << tem.y << ")" << endl;
        newpoint_mark.push_back(Point(tem.x, tem.y));//起点标记
        flag = 0;
        int flag1 = 0;
        count = 0;
        while (flag == 0) {
            //更新cur的值
            cur.y = q.y;
            cur.x = q.x;

            if (image.at<uchar>(cur.x, cur.y) == 0) {//判断当前点没有标记，若标记则为255，没有标记则为0

                if (flag == 0 && (image.at<uchar>(cur.x, cur.y + 1) == 0)) {//0方向邻居点为黑点

                    newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                    image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                    cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y + 1;//坐标右更新
                    q.x = cur.x;
                    cout << 0;
                    dir.push_back(0);

                    //判断下一个点是否是端点、交叉点
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//下一个点是端点、交叉点
                        cout << "终止点：" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//记录的每一次更新的坐标
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //判断当前点是否是交叉点，如果是的话，不需要存储方向
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "不存储" << endl;

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

                        //判断当前点是否是端点，如果是的话，跳出循环
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //将cur点更新为起始点，继续逆时针遍历路径
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//标记已经被访问了的cur点；变成白点255
                        cout << "起始点" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//起点标记
                        if (flag == 1) {
                            cout << "count == 1不存储" << endl;
                            newpoint_mark.pop_back();
                        }
                    }

                    if (flag1 == 0) {//下一个点是普通点
                        //更新cur的值
                        cur.y = q.y;
                        cur.x = q.x;
                    }
                }
                if (flag == 0 && (image.at<uchar>(cur.x - 1, cur.y + 1) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                    image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                    cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y + 1;//坐标1更新
                    q.x = cur.x - 1;
                    cout << 1;
                    dir.push_back(1);

                    //判断下一个点是否是端点、交叉点
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//下一个点是端点、交叉点

                        cout << "终止点：" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//记录的每一次更新的坐标
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //判断当前点是否是交叉点，如果是的话，不需要存储方向
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "不存储" << endl;

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

                        //判断当前点是否是端点，如果是的话，跳出循环
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //将cur点更新为起始点，继续逆时针遍历路径
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//标记已经被访问了的cur点；变成白点255
                        cout << "起始点" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//起点标记
                        if (flag == 1) {
                            cout << "flag == 1不存储" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//下一个点是普通点
                        //更新cur的值
                        cur.y = q.y;
                        cur.x = q.x;
                    }


                }
                if (flag == 0 && (image.at<uchar>(cur.x - 1, cur.y) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                    image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                    cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y;//向2更新
                    q.x = cur.x - 1;
                    cout << 2;
                    dir.push_back(2);

                    //判断下一个点是否是端点、交叉点
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//下一个点是端点、交叉点

                        cout << "终止点：" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//记录的每一次更新的坐标
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //判断当前点是否是交叉点，如果是的话，不需要存储方向
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "不存储" << endl;

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

                        //判断当前点是否是端点，如果是的话，跳出循环
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //将cur点更新为起始点，继续逆时针遍历路径
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//标记已经被访问了的cur点；变成白点255
                        cout << "起始点" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//起点标记
                        if (flag == 1) {
                            cout << "flag == 1不存储" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//下一个点是普通点
                        //更新cur的值
                        cur.y = q.y;
                        cur.x = q.x;
                    }

                }
                if (flag == 0 && (image.at<uchar>(cur.x - 1, cur.y - 1) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                    image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                    cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y - 1;//方向3更新
                    q.x = cur.x - 1;
                    cout << 3;
                    dir.push_back(3);

                    //判断下一个点是否是端点、交叉点
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//下一个点是端点、交叉点

                        cout << "终止点：" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//记录的每一次更新的坐标
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //判断当前点是否是交叉点，如果是的话，不需要存储方向
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "不存储" << endl;

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


                        //判断当前点是否是端点，如果是的话，跳出循环
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }
                        //将cur点更新为起始点，继续逆时针遍历路径
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//标记已经被访问了的cur点；变成白点255
                        cout << "起始点" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//起点标记
                        if (flag == 1) {
                            cout << "flag == 1不存储" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//下一个点是普通点
                        //更新cur的值
                        cur.y = q.y;
                        cur.x = q.x;
                    }


                }
                if (flag == 0 && (image.at<uchar>(cur.x, cur.y - 1) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                    image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                    cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y - 1;//坐标4更新
                    q.x = cur.x;
                    cout << 4;
                    dir.push_back(4);

                    //判断下一个点是否是端点、交叉点
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//下一个点是端点、交叉点

                        cout << "终止点：" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//记录的每一次更新的坐标
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //判断当前点是否是交叉点，如果是的话，不需要存储方向
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "不存储" << endl;

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

                        //判断当前点是否是端点，如果是的话，跳出循环
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //将cur点更新为起始点，继续逆时针遍历路径
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//标记已经被访问了的cur点；变成白点255
                        cout << "起始点" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//起点标记
                        if (flag == 1) {
                            cout << "flag == 1不存储" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//下一个点是普通点
                        //更新cur的值
                        cur.y = q.y;
                        cur.x = q.x;
                    }

                }
                if (flag == 0 && (image.at<uchar>(cur.x + 1, cur.y - 1) == 0)) {
                    newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                    image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                    cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;


                    q.y = cur.y - 1;//坐标5更新
                    q.x = cur.x + 1;
                    cout << 5;
                    dir.push_back(5);

                    //判断下一个点是否是端点、交叉点
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//下一个点是端点、交叉点

                        cout << "终止点：" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//记录的每一次更新的坐标
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //判断当前点是否是交叉点，如果是的话，不需要存储方向
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "不存储" << endl;

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

                        //判断当前点是否是端点，如果是的话，跳出循环
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //将cur点更新为起始点，继续逆时针遍历路径
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//标记已经被访问了的cur点；变成白点255
                        cout << "起始点" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//起点标记
                        if (flag == 1) {

                            cout << "flag == 1不存储" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//下一个点是普通点
                        //更新cur的值
                        cur.y = q.y;
                        cur.x = q.x;
                    }

                }
                if (flag == 0 && (image.at<uchar>(cur.x + 1, cur.y) == 0)) {
                    newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标

                    image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                    cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;


                    q.y = cur.y;//坐标6更新
                    q.x = cur.x + 1;
                    cout << 6;
                    dir.push_back(6);


                    //判断下一个点是否是端点、交叉点
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//下一个点是端点、交叉点

                        cout << "终止点：" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//记录的每一次更新的坐标
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //判断当前点是否是交叉点，如果是的话，不需要存储方向
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "不存储" << endl;

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

                        //判断当前点是否是端点，如果是的话，跳出循环
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //将cur点更新为起始点，继续逆时针遍历路径
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//标记已经被访问了的cur点；变成白点255
                        cout << "起始点" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//起点标记
                        if (flag == 1) {
                            cout << "flag == 1不存储" << endl;
                            newpoint_mark.pop_back();
                        }
                    }

                    if (flag1 == 0) {//下一个点是普通点
                        //更新cur的值
                        cur.y = q.y;
                        cur.x = q.x;
                    }

                }
                if (flag == 0 && (image.at<uchar>(cur.x + 1, cur.y + 1) == 0)) {

                    newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                    image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                    cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                    q.y = cur.y + 1;//坐标7更新
                    q.x = cur.x + 1;
                    cout << 7;
                    dir.push_back(7);

                    //判断下一个点是否是端点、交叉点
                    flag1 = 0;
                    for (size_t j = 0; j < sef.size(); j++) {
                        p = sef[j];
                        if (q.y == p.y && q.x == p.x) {
                            flag1 = 1;
                        }
                    }

                    if (flag1 == 1) {//下一个点是端点、交叉点

                        cout << "终止点：" << "(" << q.x << "," << q.y << ")" << endl;
                        newpoint.push_back(Point(q.x, q.y));//记录的每一次更新的坐标
                        newpoint_mark.push_back(Point(q.x, q.y));

                        //判断当前点是否是交叉点，如果是的话，不需要存储方向
                        for (size_t k = 0; k < sf.size(); k++) {
                            front = sf[k];
                            if (cur.x == front.x && cur.y == front.y) {
                                dir.pop_back();
                                newpoint.pop_back();
                                newpoint.pop_back();
                                newpoint_mark.pop_back();
                                newpoint_mark.pop_back();
                                cout << "不存储" << endl;

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

                        //判断当前点是否是端点，如果是的话，跳出循环
                        for (size_t k = 0; k < se.size(); k++) {
                            if (cur.x == se[k].x && cur.y == se[k].y) {
                                flag = 1;
                            }
                        }

                        //将cur点更新为起始点，继续逆时针遍历路径
                        q.x = tem.x;
                        q.y = tem.y;
                        image.at<uchar>(tem.x, tem.y) = 0;//标记已经被访问了的cur点；变成白点255
                        cout << "起始点" << "(" << tem.x << "," << tem.y << ")" << endl;
                        newpoint_mark.push_back(Point(tem.x, tem.y));//起点标记
                        if (flag == 1) {
                            cout << "flag == 1不存储" << endl;
                            newpoint_mark.pop_back();
                        }

                    }

                    if (flag1 == 0) {//下一个点是普通点
                        //更新cur的值
                        cur.y = q.y;
                        cur.x = q.x;
                    }


                }

                //当前点为孤立点
                if ((image.at<uchar>(cur.x, cur.y) == 0
                    && image.at<uchar>(cur.x - 1, cur.y + 1) == 255)
                    && (image.at<uchar>(cur.x - 1, cur.y) == 255)
                    && (image.at<uchar>(cur.x - 1, cur.y - 1) == 255)
                    && (image.at<uchar>(cur.x, cur.y - 1) == 255)
                    && (image.at<uchar>(cur.x + 1, cur.y - 1) == 255)
                    && (image.at<uchar>(cur.x + 1, cur.y) == 255)
                    && (image.at<uchar>(cur.x + 1, cur.y + 1) == 255)
                    && (image.at<uchar>(cur.x, cur.y + 1) == 255)) {

                    cout << "孤立点为" << "(" << cur.x << "," << cur.y << ")" << endl;
                    cout << "不存储" << endl;
                    cout << endl;
                    flag = 1;
                    newpoint.pop_back();
                    newpoint_mark.pop_back();
                }

            }
            else {//发现为孤立点
                flag = 1;
                dir.push_back(-1);
                cout << "去掉起始点" << "(" << cur.x << "," << cur.y << ")" << endl;
                newpoint.pop_back();
                newpoint_mark.pop_back();
                cout << "不存储" << endl;
                cout << endl;
            }

        }
    }

    //cout << "笔画像素点" << endl;;
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
    cout << "笔画起始点" << endl;
    for (size_t j = 0; j < newpoint_mark.size(); j++)
    {
        cout << "(" << newpoint_mark[j].x << "," << newpoint_mark[j].y << ")" << endl;
    }
    cout << endl;
    cout << endl;
    //cout << "笔画newpoint点" << endl;
    //for (size_t j = 0; j < newpoint.size(); j++)
    //{
    //    cout << "(" << newpoint[j].x << "," << newpoint[j].y << ")" << endl;
    //}
}

//获取骨架笔画 11.27新增：使用正确的newpoint_mark纠正错误的newpoint
void craw_stroke_new(Mat& image, vector<Point>& se, vector<Point>& sf,vector<Point>& s1,
    vector<Point>& s, vector<Point>& sef, vector<Point>& newpoint_mark, vector<Point>& newpoint, vector<int>& dir, StrokesInfo* strokesinfo, double strokes_ave) {
    Point cur;//当前点
    Point start;//笔画起点
    Point end;//笔画终点
    Point q;
    newpoint.clear();
    for (size_t i = 0; i < newpoint_mark.size(); i++)
    {
        if (i % 2 == 0) {

            start = newpoint_mark[i];
            end = newpoint_mark[i + 1];
            q.y = cur.y = start.y;//初始化点
            q.x = cur.x = start.x;
            cout << "初始化点：(" << cur.x << "," << cur.y << ")" << endl;
            int flag_sf = 0;//判断邻居点是否为交叉点
            int flag_end = 0;//判断下一个点是否是终止点
            int flag_if = 0;//判断下一个点是需要点，并跳出if
            while (flag_end == 0) {

                if (flag_if == 0 && (image.at<uchar>(cur.x, cur.y + 1) == 0)) {//0方向邻居点为黑点
                    //0方向邻居点属于交叉点
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x == sf[j].x && cur.y + 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //当前交叉点为终止点
                        if (cur.x == end.x && cur.y + 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    //0方向邻居点不属于交叉点
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                        image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                        cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y + 1;//坐标右更新
                        q.x = cur.x;
                        cout << 0;
                        flag_if = 1;//跳出后面的if
                        //判断下一个点是终止点
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//记录终点
                        }
                        if (flag_end == 0) {
                            //下一个点不是终止点,则更新cur的值
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0改回来方便后续判断
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x - 1, cur.y + 1) == 0)) {//1方向邻居点为黑点
                    //1方向邻居点不属于交叉点
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x - 1 == sf[j].x && cur.y + 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //当前交叉点为终止点
                        if (cur.x - 1 == end.x && cur.y + 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                        image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                        cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y + 1;//坐标1方向更新
                        q.x = cur.x - 1;
                        cout << 1;
                        flag_if = 1;//跳出后面的if
                        //判断下一个点是否是终止点
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//记录终点
                        }
                        if (flag_end == 0) {
                            //下一个点不是终止点,则更新cur的值
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0改回来方便后续判断
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x - 1, cur.y) == 0)) {
                    //2方向邻居点不属于交叉点
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x - 1 == sf[j].x && cur.y == sf[j].y) {
                            flag_sf = 1;
                        }
                        //当前交叉点为终止点
                        if (cur.x - 1 == end.x && cur.y == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                        image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                        cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y;//坐标2方向更新
                        q.x = cur.x - 1;
                        cout << 2;
                        flag_if = 1;//跳出后面的if
                        //判断下一个点是否是终止点
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//记录终点
                        }
                        if (flag_end == 0) {
                            //下一个点不是终止点,则更新cur的值
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0改回来方便后续判断
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x - 1, cur.y - 1) == 0)) {
                    //3方向邻居点不属于交叉点
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x - 1 == sf[j].x && cur.y - 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //当前交叉点为终止点
                        if (cur.x - 1 == end.x && cur.y - 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                        image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                        cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y - 1;//坐标3方向更新
                        q.x = cur.x - 1;
                        cout << 3;
                        flag_if = 1;//跳出后面的if
                        //判断下一个点是否是终止点
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//记录终点
                        }
                        if (flag_end == 0) {
                            //下一个点不是终止点,则更新cur的值
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0改回来方便后续判断
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x, cur.y - 1) == 0)) {
                    //4方向邻居点不属于交叉点
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x == sf[j].x && cur.y - 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //当前交叉点为终止点
                        if (cur.x == end.x && cur.y - 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                        image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                        cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y - 1;//坐标4方向更新
                        q.x = cur.x;
                        cout << 4;
                        flag_if = 1;//跳出后面的if

                        //判断下一个点是否是终止点
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//记录终点
                        }
                        if (flag_end == 0) {
                            //下一个点不是终止点,则更新cur的值
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0改回来方便后续判断
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x + 1, cur.y - 1) == 0)) {
                    //5方向邻居点不属于交叉点
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x + 1 == sf[j].x && cur.y - 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //当前交叉点为终止点
                        if (cur.x + 1 == end.x && cur.y - 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                        image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                        cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y - 1;//坐标5方向更新
                        q.x = cur.x + 1;
                        cout << 5;
                        flag_if = 1;//跳出后面的if
                        //判断下一个点是否是终止点
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//记录终点
                        }
                        if (flag_end == 0) {
                            //下一个点不是终止点,则更新cur的值
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0改回来方便后续判断
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x + 1, cur.y) == 0)) {
                    //6方向邻居点属于交叉点
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x + 1 == sf[j].x && cur.y == sf[j].y) {
                            flag_sf = 1;
                        }
                        //当前交叉点为终止点
                        if (cur.x + 1 == end.x && cur.y == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                        image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                        cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y;//坐标6方向更新
                        q.x = cur.x + 1;
                        cout << 6;
                        flag_if = 1;//跳出后面的if
                        //判断下一个点是否是终止点
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//记录终点
                        }
                        if (flag_end == 0) {
                            //下一个点不是终止点,则更新cur的值
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0改回来方便后续判断
                }
                if (flag_if == 0 && (image.at<uchar>(cur.x + 1, cur.y + 1) == 0)) {
                    //7方向邻居点属于交叉点
                    for (size_t j = 0; j < sf.size(); j++) {
                        if (cur.x + 1 == sf[j].x && cur.y + 1 == sf[j].y) {
                            flag_sf = 1;
                        }
                        //当前交叉点为终止点
                        if (cur.x + 1 == end.x && cur.y + 1 == end.y) {
                            flag_sf = 0;
                        }
                    }
                    if (flag_sf == 0) {
                        newpoint.push_back(Point(cur.x, cur.y));//记录当前坐标
                        image.at<uchar>(cur.x, cur.y) = 255;//标记已经被访问了的cur点；变成白点255
                        cout << "访问：(" << cur.x << "," << cur.y << ")" << endl;

                        q.y = cur.y + 1;//坐标7方向更新
                        q.x = cur.x + 1;
                        cout << 7;
                        flag_if = 1;//跳出后面的if
                        //判断下一个点是否是终止点
                        if (end.x == q.x && end.y == q.y) {
                            flag_end = 1;
                            newpoint.push_back(Point(q.x, q.y));//记录终点
                        }
                        if (flag_end == 0) {
                            //下一个点不是终止点,则更新cur的值
                            cur.y = q.y;
                            cur.x = q.x;
                        }
                    }
                    flag_sf = 0; //flag_sf = 0改回来方便后续判断
                }

                //对当前点循环了一次之后，肯定找到了下一个点的坐标，故需要对flag_if置0
                flag_if = 0;
            }

        }
    }
    cout << "笔画像素点" << endl;
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

//绘制未合并笔画之前的彩图
Mat draw_picture(Mat& image, vector<Point>& s1, StrokesInfo* strokesinfo) {

    int a = 1;
    int b = 1;
    int c = 1;
    //复制转化为彩色图像
    Mat draw = channelSwitching(image);
    //新建白底图像
    for (int i = 0; i < draw.rows; i++)
    {
        for (int j = 0; j < draw.cols; j++)
        {

            draw.at<Vec3b>(i, j)[0] = 255;
            draw.at<Vec3b>(i, j)[1] = 255;
            draw.at<Vec3b>(i, j)[2] = 255;
        }
    }

    //做出二值化灰点
    for (size_t i = 0; i < s1.size(); i++)
    {
        Point tems;
        tems = s1[i];
        draw.at<Vec3b>(tems.x, tems.y)[0] = 200;
        draw.at<Vec3b>(tems.x, tems.y)[1] = 200;
        draw.at<Vec3b>(tems.x, tems.y)[2] = 200;
    }

    //绘制未合并笔画之前的彩图
    //for (size_t i = 0; i < newpoint.size(); i++)
    //{
    //    Point tems;
    //    tems = newpoint[i];
    //    for (size_t j = 0; j < newpoint_mark.size(); j++)
    //    {
    //        Point tem;
    //        tem = newpoint_mark[j];
    //        if (tems.x == tem.x && tems.y == tem.y && j % 2 == 0) {
    //            //cout << "改颜色" << endl;
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

    //修正1026：绘制未合并笔画之前的彩图
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

//combine1中调用的趋势判断函数，需要输入strokesinfo[i]的i,uw，以及是正向判断或者是逆向判断
int judge_qushi(int i, int uw, int select, StrokesInfo* strokesinfo) {
    if (select == 0) {//正向判断趋势
        int zero = 0, one = 0, two = 0, three = 0;//方向
        for (int i23 = 0; i23 < uw && i23 < strokesinfo[i].snake.size(); i23++) {
            //cout << strokesinfo[i].snake[i23];
            if (strokesinfo[i].snake[i23] == 0 || strokesinfo[i].snake[i23] == 4)zero++;
            if (strokesinfo[i].snake[i23] == 1 || strokesinfo[i].snake[i23] == 5)one++;
            if (strokesinfo[i].snake[i23] == 2 || strokesinfo[i].snake[i23] == 6)two++;
            if (strokesinfo[i].snake[i23] == 3 || strokesinfo[i].snake[i23] == 7)three++;
        }
        int flag_dir = 0;
        //找四个数中最大的
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
    if (select == 1) {//逆向判断趋势
        int zero = 0, one = 0, two = 0, three = 0;//方向
        for (int i23 = strokesinfo[i].snake.size() - 1; i23 > strokesinfo[i].snake.size() - 1 - uw && i23 > 0; i23--) {
            //cout << strokesinfo[i].snake[i23];
            if (strokesinfo[i].snake[i23] == 0 || strokesinfo[i].snake[i23] == 4)zero++;
            if (strokesinfo[i].snake[i23] == 1 || strokesinfo[i].snake[i23] == 5)one++;
            if (strokesinfo[i].snake[i23] == 2 || strokesinfo[i].snake[i23] == 6)two++;
            if (strokesinfo[i].snake[i23] == 3 || strokesinfo[i].snake[i23] == 7)three++;
        }
        int flag_dir = 0;
        //找四个数中最大的
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

//更正1026：使用遍历数组strokesinfo，找到合并笔画  
//合并笔画1：combine_point_mark存储找到一组四个点，表示两个可以合并笔画（但是包含重复的）
void combine1(Mat& image, int NPB, int NSP, StrokesInfo* strokesinfo, vector<Point>& combine_point_mark) {

    int uw = NPB / NSP;
    int diri = 0, dirj = 0;
    int flag = 0, flag1 = 0;
    int com_mark = 0;
    //1024订正：遍历数组strokesinfo找满足条件的两个点
    for (size_t i = 0; i < strokesinfo[0].num; i++) {
        for (size_t j = 0; j < strokesinfo[0].num; j++) {
            Point start, end;
            Point start1, end1;
            if (i != j) {
                //给点赋值；
                start = strokesinfo[i].begin;
                end = strokesinfo[i].end;
                start1 = strokesinfo[j].begin;
                end1 = strokesinfo[j].end;

                //判断方向
                if (start.x != 0 && start1.x != 0) {
                    //计算最短距离
                    int dis = 0;//最短距离容器
                    int dis0 = sqrt((start.x - start1.x) * (start.x - start1.x) + (start.y - start1.y) * (start.y - start1.y));
                    int dis1 = sqrt((start.x - end1.x) * (start.x - end1.x) + (start.y - end1.y) * (start.y - end1.y));
                    int dis2 = sqrt((end.x - start1.x) * (end.x - start1.x) + (end.y - start1.y) * (end.y - start1.y));
                    int dis3 = sqrt((end.x - end1.x) * (end.x - end1.x) + (end.y - end1.y) * (end.y - end1.y));

                    //找四个数中最小的
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
                        int oneline = 0, twoline = 0;//表示两个笔画段分别的趋势
                        //通过最短距离判断趋势：分为4种情况

                        if (dis == dis0) {//说明start.x和start1.x最近，则两边全部正序
                            oneline = judge_qushi(i, uw, 0, strokesinfo);
                            twoline = judge_qushi(j, uw, 0, strokesinfo);
                        }

                        if (dis == dis1) {//说明start.x和end1.x最近，则前正序，后逆序
                            oneline = judge_qushi(i, uw, 0, strokesinfo);
                            twoline = judge_qushi(j, uw, 1, strokesinfo);
                        }

                        if (dis == dis2) {//说明end.x和start1.x最近，则前逆序，后正序
                            oneline = judge_qushi(i, uw, 1, strokesinfo);
                            twoline = judge_qushi(j, uw, 0, strokesinfo);
                        }

                        if (dis == dis3) {//说明end.x和end1.x最近，则两边全部逆序
                            oneline = judge_qushi(i, uw, 1, strokesinfo);
                            twoline = judge_qushi(j, uw, 1, strokesinfo);
                        }

                        if (oneline == twoline) {//strokesinfo[i].dir == strokesinfo[j].dir || 

                            //判断笔画是否合并过
                            //若两个笔画的com_mark均为0,即未合并过
                            if (strokesinfo[i].com_mark == 0 && strokesinfo[j].com_mark == 0) {
                                com_mark++;
                                strokesinfo[0].com_mark_max = com_mark;
                                strokesinfo[i].com_mark = com_mark;
                                strokesinfo[j].com_mark = com_mark;
                            }
                            //若有一笔画合并过
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

//1026添加：在去重合并笔画combine_point_mark_new的基础上，存储合并笔画进strokesinfo_com结构体
//11.13添加：加入无需合并笔画
void combine2_save(StrokesInfo* strokesinfo_com, StrokesInfo* strokesinfo) {


    //for (size_t i = 0; i < combine_point_mark_new.size(); i++) {
    //    Point tem;
    //    tem = combine_point_mark_new[i];
    //    if (i % 4 == 0)cout << endl;
    //    cout << "(" << tem.x << "," << tem.y << ")" << endl;
    //}
    /*cout << endl;
    cout << "==================合并笔画前==================" << endl;
    for (int index = 0; index < strokesinfo[0].num; index++)
    {
        cout << "begin==(" << strokesinfo[index].begin.x << "," << strokesinfo[index].begin.y << ")" << endl;
        cout << "end==(" << strokesinfo[index].end.x << "," << strokesinfo[index].end.y << ")" << endl;
        cout << "存储8链码序列长度==" << strokesinfo[index].snake_length << endl;
        for (int i = 0; i < strokesinfo[index].snake_length; i++) {
            cout << strokesinfo[index].snake[i];
        }
        cout << "笔画方向==" << strokesinfo[index].dir << endl;
        cout << "笔画像素点：" << endl;
        for (int i = 0; i <= strokesinfo[index].snake_length; i++) {
            cout << "(" << strokesinfo[index].tem[i].x << "," << strokesinfo[index].tem[i].y << ") ";
        }
        cout << "com_mark==" << strokesinfo[index].com_mark << endl;
        cout << endl;
    }*/

    //初始化结构体数组strokesinfo_com
    for (int index = 0; index < 20; index++)
    {
        strokesinfo_com[index].begin.x = strokesinfo_com[index].begin.y = 0;
        strokesinfo_com[index].end.x = strokesinfo_com[index].end.y = 0;
        strokesinfo_com[index].snake_length = 0;
        strokesinfo_com[index].snake.clear();
        strokesinfo_com[index].dir = 0;
        strokesinfo_com[index].tem.clear();
        strokesinfo_com[index].num = 0;//存储数组内成员个数
        strokesinfo_com[index].com_mark = 0;//合并笔画标记
        strokesinfo_com[index].com_mark_max = 0;//标记com_mark的最大值
    }

    //cout << "strokesinfo[0].com_mark_max=" << strokesinfo[0].com_mark_max << endl;
    int flag = strokesinfo[0].com_mark_max + 1;//作为未合并笔画的起点标记
    //将com_mark不为0的笔画段合并:方向为0的笔画段需要重新排序，存储到strokesinfo_com[20]中
    //从合并标记为1开始
    for (int com_mark = 1; com_mark < strokesinfo[0].num; com_mark++) {
        //初始化
        strokesinfo_com[com_mark].begin.x = 0;
        strokesinfo_com[com_mark].begin.y = 0;
        //遍历strokesinfo数组
        for (int index = 0; index < strokesinfo[0].num; index++) {
            if (strokesinfo[index].com_mark == com_mark) {
                if (strokesinfo[index].dir != 0) {//方向不为0
                    strokesinfo_com[com_mark].dir = strokesinfo[index].dir;//存储方向
                    if (strokesinfo[index].begin.x < strokesinfo_com[com_mark].begin.x) {
                        //合并在前面                    
                        strokesinfo_com[com_mark].begin = strokesinfo[index].begin;
                        vector<Point> tem1;//临时容器
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
                        //合并在后面
                        strokesinfo_com[com_mark].end = strokesinfo[index].end;
                        for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                            strokesinfo_com[com_mark].tem.push_back(strokesinfo[index].tem[i]);
                        }
                        strokesinfo_com[com_mark].begin = strokesinfo_com[com_mark].tem[0];
                    }
                }

                if (strokesinfo[index].dir == 0) {//方向为0
                    strokesinfo_com[com_mark].dir = strokesinfo[index].dir;//存储方向
                    if (strokesinfo[index].begin.y < strokesinfo_com[com_mark].begin.y) {//用y方向比较大小
                        //合并在前面                    
                        strokesinfo_com[com_mark].begin = strokesinfo[index].begin;
                        vector<Point> tem1;//临时容器
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
                        //合并在后面
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

    //存储笔画长度=像素点个数-1
    for (int index = 1; index < 20; index++)
    {
        strokesinfo_com[index].snake_length = strokesinfo_com[index].tem.size() - 1;
    }

    //添加未合并笔画com_mark==0
    for (int index = 0; index < strokesinfo[0].num; index++) {
        if (strokesinfo[index].com_mark == 0) {
            flag++;
            //cout << "flag=" << flag << endl;
            strokesinfo_com[flag].begin = strokesinfo[index].begin;//存储起始点
            strokesinfo_com[flag].end = strokesinfo[index].end;//存储终止点
            strokesinfo_com[flag].dir = strokesinfo[index].dir;//存储方向
            //存储8链码序列长度
            strokesinfo_com[flag].snake_length = strokesinfo[index].snake_length;
            //存储8链码序列
            for (int i = 0; i < strokesinfo[index].snake_length; i++) {
                strokesinfo_com[flag].snake.push_back(strokesinfo[index].snake[i]);
            }
            //存储笔画像素点
            for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                strokesinfo_com[flag].tem.push_back(strokesinfo[index].tem[i]);
            }
            //未合并笔画的com_mark==0
            strokesinfo_com[flag].com_mark = strokesinfo[index].com_mark;
        }
    }

    cout << endl;
    cout << "=============合并笔画后strokesinfo_com=============" << endl;
    for (int index = 1; index < 20; index++)
    {
        cout << endl;
        cout << "begin==(" << strokesinfo_com[index].begin.x << "," << strokesinfo_com[index].begin.y << ")" << endl;
        cout << "end==(" << strokesinfo_com[index].end.x << "," << strokesinfo_com[index].end.y << ")" << endl;
        cout << "存储8链码序列长度==" << strokesinfo_com[index].tem.size() << endl;
        cout << "笔画方向==" << strokesinfo_com[index].dir << endl;
        cout << "笔画像素点：" << endl;
        for (int i = 0; i < strokesinfo_com[index].tem.size(); i++) {
            cout << "(" << strokesinfo_com[index].tem[i].x << "," << strokesinfo_com[index].tem[i].y << ") ";
        }
        //cout << "com_mark==" << strokesinfo_com[index].com_mark << endl;
        cout << endl;
    }
}

//二阶贝塞尔曲线
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
        //去重
        for (size_t i = 0; i < point_bezier_2.size() - 1; i++) {
            if (x == point_bezier_2[i].x && y == point_bezier_2[i].y) {
                point_bezier_2.pop_back();
            }
        }
    }
    /*for (size_t i = 0; i < point_bezier_2.size(); i++) {
        cout << "第" << i << "个贝塞尔点为：(" << point_bezier_2[i].x << "," << point_bezier_2[i].y << ")" << endl;
 }*/
}

//修正桥连接的十字型笔画
void correct_qiao(Mat& image, Mat& image1, int i, int uw, qiaoInfo* qiaoinfo, vector<Point>& edge_center, vector<Point>& edge, StrokesInfo* strokesinfo) {
    //交叉区边缘与二值化后像素交点            
    int pf_x = 0;
    int pf_y = 0;
    pf_x = (qiaoinfo[i].begin.x + qiaoinfo[i].end.x) / 2;
    pf_y = (qiaoinfo[i].begin.y + qiaoinfo[i].end.y) / 2;
    cout << "中心点为：(" << pf_x << "," << pf_y << ")" << endl;
    Point center;
    center.x = pf_x;
    center.y = pf_y;
    edge_center.push_back(Point(pf_x, pf_y));

    //cout << "当前桥为：(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
    //cout << "“桥”起点连接笔画段:" << endl;
    //for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
    //    cout << "(" << qiaoinfo[i].begin_line_begin[j1].x << "," << qiaoinfo[i].begin_line_begin[j1].y << ")--("
    //        << qiaoinfo[i].begin_line_end[j1].x << "," << qiaoinfo[i].begin_line_end[j1].y << ")" << endl;
    //    //cout <<"“桥”起终点连接的笔画段与“桥”的连接方式，0表示起点与桥相连，1表示终点与桥相连"<< qiaoinfo[i].begin_line[j1] << endl;
    //}
    //cout << "“桥”终点连接笔画段:" << endl;
    //for (int j1 = 0; j1 < qiaoinfo[i].end_line_begin.size(); j1++) {
    //    cout << "(" << qiaoinfo[i].end_line_begin[j1].x << "," << qiaoinfo[i].end_line_begin[j1].y << ")--("
    //        << qiaoinfo[i].end_line_end[j1].x << "," << qiaoinfo[i].end_line_end[j1].y << ")" << endl;
    //    //cout << "“桥”起终点连接的笔画段与“桥”的连接方式，0表示起点与桥相连，1表示终点与桥相连" << qiaoinfo[i].end_line[j1] << endl;
    //}
    Point down, up, left, right;
    //下边
    down.x = center.x + 2 * uw;//初始化交点坐标
    down.y = center.y;
    for (int i1 = -2 * uw; i1 <= 2 * uw; i1++) {
        Point crosspoint;
        crosspoint.x = center.x + 2 * uw;
        crosspoint.y = center.y + i1;
        int color = image1.at<uchar>(crosspoint.x, crosspoint.y);
        if (color == 0) {
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                int sit1 = 0;//位置记号符
                for (int j2 = 0; j2 < 20; j2++) {
                    if ((strokesinfo[j2].begin.x == qiaoinfo[i].begin_line_begin[j1].x) && (strokesinfo[j2].begin.y == qiaoinfo[i].begin_line_begin[j1].y)
                        && (strokesinfo[j2].end.x == qiaoinfo[i].begin_line_end[j1].x) && (strokesinfo[j2].end.y == qiaoinfo[i].begin_line_end[j1].y)) {
                        sit1 = j2;
                    }
                }
                for (int j3 = 0; j3 < strokesinfo[sit1].tem.size(); j3++) {
                    if (strokesinfo[sit1].tem[j3].x == crosspoint.x && strokesinfo[sit1].tem[j3].y == crosspoint.y) {
                        down.x = crosspoint.x;//交点坐标
                        down.y = crosspoint.y;
                        cout << "下边相交于(" << down.x << "," << down.y << ")" << endl;

                    }
                }
            }

        }

    }
    //上边
    up.x = center.x - 2 * uw;//初始化交点坐标
    up.y = center.y;
    for (int i2 = -2 * uw; i2 <= 2 * uw; i2++) {
        Point crosspoint;
        crosspoint.x = center.x - 2 * uw;
        crosspoint.y = center.y + i2;
        int color = image1.at<uchar>(crosspoint.x, crosspoint.y);
        if (color == 0) {
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                int sit1 = 0;//位置记号符
                for (int j2 = 0; j2 < 20; j2++) {
                    if ((strokesinfo[j2].begin.x == qiaoinfo[i].begin_line_begin[j1].x) && (strokesinfo[j2].begin.y == qiaoinfo[i].begin_line_begin[j1].y)
                        && (strokesinfo[j2].end.x == qiaoinfo[i].begin_line_end[j1].x) && (strokesinfo[j2].end.y == qiaoinfo[i].begin_line_end[j1].y)) {
                        sit1 = j2;
                    }
                }
                for (int j3 = 0; j3 < strokesinfo[sit1].tem.size(); j3++) {
                    if (strokesinfo[sit1].tem[j3].x == crosspoint.x && strokesinfo[sit1].tem[j3].y == crosspoint.y) {
                        up.x = crosspoint.x;//交点坐标
                        up.y = crosspoint.y;
                        cout << "上边相交于(" << up.x << "," << up.y << ")" << endl;

                    }
                }
            }
        }

    }
    //右边
    right.x = center.x;//初始化交点坐标
    right.y = center.y + 2 * uw;
    for (int i3 = -2 * uw; i3 <= 2 * uw; i3++) {
        Point crosspoint;
        crosspoint.x = center.x + i3;
        crosspoint.y = center.y + 2 * uw;
        int color = image1.at<uchar>(crosspoint.x, crosspoint.y);
        if (color == 0) {
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                int sit1 = 0;//位置记号符
                for (int j2 = 0; j2 < 20; j2++) {
                    if ((strokesinfo[j2].begin.x == qiaoinfo[i].begin_line_begin[j1].x) && (strokesinfo[j2].begin.y == qiaoinfo[i].begin_line_begin[j1].y)
                        && (strokesinfo[j2].end.x == qiaoinfo[i].begin_line_end[j1].x) && (strokesinfo[j2].end.y == qiaoinfo[i].begin_line_end[j1].y)) {
                        sit1 = j2;
                    }
                }
                for (int j3 = 0; j3 < strokesinfo[sit1].tem.size(); j3++) {
                    if (strokesinfo[sit1].tem[j3].x == crosspoint.x && strokesinfo[sit1].tem[j3].y == crosspoint.y) {
                        right.x = crosspoint.x;//交点坐标
                        right.y = crosspoint.y;
                        cout << "右边相交于(" << right.x << "," << right.y << ")" << endl;

                    }
                }
            }
        }

    }
    //左边
    left.x = center.x;//初始化交点坐标
    left.y = center.y - 2 * uw;
    for (int i4 = -2 * uw; i4 <= 2 * uw; i4++) {
        Point crosspoint;
        crosspoint.x = center.x + i4;
        crosspoint.y = center.y - 2 * uw;
        int color = image1.at<uchar>(crosspoint.x, crosspoint.y);
        if (color == 0) {
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                int sit1 = 0;//位置记号符
                for (int j2 = 0; j2 < 20; j2++) {
                    if ((strokesinfo[j2].begin.x == qiaoinfo[i].begin_line_begin[j1].x) && (strokesinfo[j2].begin.y == qiaoinfo[i].begin_line_begin[j1].y)
                        && (strokesinfo[j2].end.x == qiaoinfo[i].begin_line_end[j1].x) && (strokesinfo[j2].end.y == qiaoinfo[i].begin_line_end[j1].y)) {
                        sit1 = j2;
                    }
                }
                for (int j3 = 0; j3 < strokesinfo[sit1].tem.size(); j3++) {
                    if (strokesinfo[sit1].tem[j3].x == crosspoint.x && strokesinfo[sit1].tem[j3].y == crosspoint.y) {
                        left.x = crosspoint.x;//初始化交点坐标
                        left.y = crosspoint.y;
                        cout << "左边相交于(" << left.x << "," << left.y << ")" << endl;

                    }
                }
            }
        }

    }

    //计算角度：
    Point2f pt1, pt2;
    //计算pt1与pt2之间的角度
    pt1.x = center.x;
    pt1.y = center.y;
    cout << "center:(" << center.x << "," << center.y << ")" << endl;
    cout << "down:(" << down.x << "," << down.y << ")" << endl;
    pt2.x = down.x;
    pt2.y = down.y;
    float radian = atan2((pt2.y - pt1.y), (pt2.x - pt1.x));//弧度   该函数返回值范围是[-pi,pi]
    float down_angle = radian * 180 / 3.1415926;//角度
    cout << "radian:" << radian << endl;
    cout << "down_angle" << down_angle << endl;

    pt2.x = up.x;
    pt2.y = up.y;
    radian = atan2((pt2.y - pt1.y), (pt2.x - pt1.x));//弧度   该函数返回值范围是[-pi,pi]
    float up_angle = radian * 180 / 3.1415926;//角度
    cout << "radian:" << radian << endl;
    cout << "up_angle" << up_angle << endl;

    pt2.x = left.x;
    pt2.y = left.y;
    radian = atan2((pt2.y - pt1.y), (pt2.x - pt1.x));//弧度   该函数返回值范围是[-pi,pi]
    float left_angle = radian * 180 / 3.1415926;//角度
    cout << "radian:" << radian << endl;
    cout << "left_angle" << left_angle << endl;

    pt2.x = right.x;
    pt2.y = right.y;
    radian = atan2((pt2.y - pt1.y), (pt2.x - pt1.x));//弧度   该函数返回值范围是[-pi,pi]
    float right_angle = radian * 180 / 3.1415926;//角度
    cout << "radian:" << radian << endl;
    cout << "right_angle" << right_angle << endl;


    Point first_qua;//第一象限的边缘点：
    vector<Point> first_edge;//第一象限的边缘点：
    int first_dis_s = 100;
    Point first_qua_s;//第一象限的最短距离点：
    for (int i = 1; i < 2 * uw; i++) {
        for (int j = 1; j < 2 * uw; j++) {
            first_qua.x = center.x - i;
            first_qua.y = center.y + j;
            int color1 = image.at<uchar>(first_qua.x, first_qua.y);
            if (color1 == 0) {//当前点为黑点
                if ((image.at<uchar>(first_qua.x, first_qua.y + 1) == 255) || (image.at<uchar>(first_qua.x, first_qua.y - 1) == 255)
                    || (image.at<uchar>(first_qua.x + 1, first_qua.y) == 255) || (image.at<uchar>(first_qua.x + 1, first_qua.y - 1) == 255) || (image.at<uchar>(first_qua.x + 1, first_qua.y + 1) == 255)
                    || (image.at<uchar>(first_qua.x - 1, first_qua.y) == 255) || (image.at<uchar>(first_qua.x - 1, first_qua.y - 1) == 255) || (image.at<uchar>(first_qua.x - 1, first_qua.y + 1) == 255)) {
                    //当前点为边缘点
                    //cout << "当前点为边缘点:(" << first_qua.x << "," << first_qua.y << ")" << endl;
                    //first_edge.push_back(Point(first_qua.x, first_qua.y));
                    int first_dis = distance(first_qua, center);
                    //cout << "first_dis:" << first_dis << endl;

                    //新增角度判断：右边和上边
                    Point2f pt3;
                    pt3.x = first_qua.x;
                    pt3.y = first_qua.y;
                    float radian = atan2((pt3.y - pt1.y), (pt3.x - pt1.x));//弧度   该函数返回值范围是[-pi,pi]
                    float one_angle = radian * 180 / 3.1415926;//角度
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

    Point second_qua;//第二象限的边缘点：
    vector<Point> second_edge;//第二象限的边缘点：
    int second_dis_s = 100;
    Point second_qua_s;//第二象限的最短距离点：
    for (int i = 1; i < 2 * uw; i++) {
        for (int j = 1; j < 2 * uw; j++) {
            second_qua.x = center.x - i;
            second_qua.y = center.y - j;
            int color1 = image.at<uchar>(second_qua.x, second_qua.y);
            if (color1 == 0) {//当前点为黑点
                if ((image.at<uchar>(second_qua.x, second_qua.y + 1) == 255) || (image.at<uchar>(second_qua.x, second_qua.y - 1) == 255)
                    || (image.at<uchar>(second_qua.x + 1, second_qua.y) == 255) || (image.at<uchar>(second_qua.x + 1, second_qua.y - 1) == 255) || (image.at<uchar>(second_qua.x + 1, second_qua.y + 1) == 255)
                    || (image.at<uchar>(second_qua.x - 1, second_qua.y) == 255) || (image.at<uchar>(second_qua.x - 1, second_qua.y - 1) == 255) || (image.at<uchar>(second_qua.x - 1, second_qua.y + 1) == 255)) {
                    //当前点为边缘点
                    //cout << "当前点为边缘点:(" << second_qua.x << "," << second_qua.y << ")" << endl;
                    //first_edge.push_back(Point(first_qua.x, first_qua.y));
                    int second_dis = distance(second_qua, center);
                    //cout << "second_dis:(" << second_dis << endl;

                    //新增角度判断：左边和上边
                    Point2f pt3;
                    pt3.x = second_qua.x;
                    pt3.y = second_qua.y;
                    float radian = atan2((pt3.y - pt1.y), (pt3.x - pt1.x));//弧度   该函数返回值范围是[-pi,pi]
                    float two_angle = radian * 180 / 3.1415926;//角度
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

    Point third_qua;//第三象限的边缘点：
    vector<Point> third_edge;//第三象限的边缘点：
    int third_dis_s = 100;
    Point third_qua_s;//第三象限的最短距离点：
    for (int i = 1; i < 2 * uw; i++) {
        for (int j = 1; j < 2 * uw; j++) {
            third_qua.x = center.x + i;
            third_qua.y = center.y - j;
            int color1 = image.at<uchar>(third_qua.x, third_qua.y);
            if (color1 == 0) {//当前点为黑点
                if ((image.at<uchar>(third_qua.x, third_qua.y + 1) == 255) || (image.at<uchar>(third_qua.x, third_qua.y - 1) == 255)
                    || (image.at<uchar>(third_qua.x + 1, third_qua.y) == 255) || (image.at<uchar>(third_qua.x + 1, third_qua.y - 1) == 255) || (image.at<uchar>(third_qua.x + 1, third_qua.y + 1) == 255)
                    || (image.at<uchar>(third_qua.x - 1, third_qua.y) == 255) || (image.at<uchar>(third_qua.x - 1, third_qua.y - 1) == 255) || (image.at<uchar>(third_qua.x - 1, third_qua.y + 1) == 255)) {
                    //当前点为边缘点
                    //cout << "当前点为边缘点:(" << third_qua.x << "," << third_qua.y << ")" << endl;
                    //first_edge.push_back(Point(first_qua.x, first_qua.y));
                    int third_dis = distance(third_qua, center);
                    //cout << "third_dis:(" << third_dis << endl;

                    //新增角度判断：左边和下边
                    Point2f pt3;
                    pt3.x = third_qua.x;
                    pt3.y = third_qua.y;
                    float radian = atan2((pt3.y - pt1.y), (pt3.x - pt1.x));//弧度   该函数返回值范围是[-pi,pi]
                    float third_angle = radian * 180 / 3.1415926;//角度
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

    Point four_qua;//第四象限的边缘点：
    vector<Point> four_edge;//第四象限的边缘点：
    int four_dis_s = 100;
    Point four_qua_s;//第四象限的最短距离点：
    for (int i = 1; i <= 2 * uw; i++) {
        for (int j = 1; j <= 2 * uw; j++) {
            four_qua.x = center.x + i;
            four_qua.y = center.y + j;
            int color1 = image.at<uchar>(four_qua.x, four_qua.y);
            if (color1 == 0) {//当前点为黑点
                if ((image.at<uchar>(four_qua.x, four_qua.y + 1) == 255) || (image.at<uchar>(four_qua.x, four_qua.y - 1) == 255)
                    || (image.at<uchar>(four_qua.x + 1, four_qua.y) == 255) || (image.at<uchar>(four_qua.x + 1, four_qua.y - 1) == 255) || (image.at<uchar>(four_qua.x + 1, four_qua.y + 1) == 255)
                    || (image.at<uchar>(four_qua.x - 1, four_qua.y) == 255) || (image.at<uchar>(four_qua.x - 1, four_qua.y - 1) == 255) || (image.at<uchar>(four_qua.x - 1, four_qua.y + 1) == 255)) {
                    //当前点为边缘点
                    //cout << "当前点为边缘点:(" << four_qua.x << "," << four_qua.y << ")" << endl;
                    //first_edge.push_back(Point(first_qua.x, first_qua.y));
                    int four_dis = distance(four_qua, center);
                    //cout << "four_dis:(" << four_dis << endl;
                     //新增角度判断：右边和下边
                    Point2f pt3;
                    pt3.x = four_qua.x;
                    pt3.y = four_qua.y;
                    float radian = atan2((pt3.y - pt1.y), (pt3.x - pt1.x));//弧度   该函数返回值范围是[-pi,pi]
                    float four_angle = radian * 180 / 3.1415926;//角度
                    if (four_angle < right_angle && four_dis < four_dis_s) {
                        four_qua_s.x = four_qua.x;
                        four_qua_s.y = four_qua.y;
                        four_dis_s = four_dis;
                    }
                }
            }
        }
    }

    cout << "第一象限的最短距离点：(" << first_qua_s.x << "," << first_qua_s.y << ")" << endl;
    cout << "第二象限的最短距离点：(" << second_qua_s.x << "," << second_qua_s.y << ")" << endl;
    cout << "第三象限的最短距离点：(" << third_qua_s.x << "," << third_qua_s.y << ")" << endl;
    cout << "第四象限的最短距离点：(" << four_qua_s.x << "," << four_qua_s.y << ")" << endl;

    edge.push_back(Point(first_qua_s.x, first_qua_s.y));
    edge.push_back(Point(second_qua_s.x, second_qua_s.y));
    edge.push_back(Point(third_qua_s.x, third_qua_s.y));
    edge.push_back(Point(four_qua_s.x, four_qua_s.y));

    //找到贝塞尔曲线的起始点P1、P2 : P1由2、3连线相交
    Point Poin1, Poin2, Poin;
    Poin.x = center.x;
    Poin.y = center.y;
    vector<Point> qiao_bezier_2;//桥修正贝塞尔
    cout << endl;
    double k1 = (double)(third_qua_s.y - second_qua_s.y) / (third_qua_s.x - second_qua_s.x);
    for (int i = third_qua_s.x; i >= second_qua_s.x; i--) {
        int Y = second_qua_s.y;//作为初始值
        int Y1 = k1 * ((double)i - (double)second_qua_s.x) + (double)second_qua_s.y;
        int color = image1.at<uchar>(i, Y);
        if (color == 0) {
            //cout << "P1初始值点：(" << i << "," << Y << ")" << endl;
            Poin1.x = i;
            Poin1.y = Y;


        }
        color = image1.at<uchar>(i, Y1);
        if (color == 0) {
            //cout << "P1点：(" << i << "," << Y1 << ")" << endl;
            Poin1.x = i;
            Poin1.y = Y1;

        }
    }

    // P2由1、4连线相交
    double k2 = (double)(four_qua_s.y - first_qua_s.y) / (four_qua_s.x - first_qua_s.x);
    for (int i = four_qua_s.x; i >= first_qua_s.x; i--) {
        int Y3 = first_qua_s.y;//作为初始值
        int Y2 = k2 * ((double)i - (double)first_qua_s.x) + (double)first_qua_s.y;
        int color = image1.at<uchar>(i, Y3);
        if (color == 0) {
            //cout << "P2初始值点：(" << i << "," << Y3 << ")" << endl;
            Poin2.x = i;
            Poin2.y = Y3;
        }
        color = image1.at<uchar>(i, Y2);
        if (color == 0) {
            //cout << "P2点：(" << i << "," << Y2 << ")" << endl;
            Poin2.x = i;
            Poin2.y = Y2;
        }
    }
    //拟合贝塞尔
    double p[3][2] = { Poin1.x,Poin1.y,Poin.x,Poin.y,Poin2.x,Poin2.y };
    bezier_2(p, qiao_bezier_2);

    vector<Point> qiao_xiuzheng;//桥修正的临时容器
    qiao_xiuzheng.clear();
    int qiao_xiuzheng1 = 0;//标记符
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
    int mark_child = 0;//标记位
    //修改笔段前面的像素点
    for (int i = 0; i < strokesinfo[qiao_xiuzheng1].tem.size(); i++) {
        if (Poin1.x == strokesinfo[qiao_xiuzheng1].tem[i].x && Poin1.y == strokesinfo[qiao_xiuzheng1].tem[i].y) {
            mark_child = i;
        }
    }
    for (int j = 0; j < mark_child; j++) {
        qiao_xiuzheng.push_back(Point(strokesinfo[qiao_xiuzheng1].tem[j].x, strokesinfo[qiao_xiuzheng1].tem[j].y));
    }

    //修改笔段的像素点qiao_bezier_2
    for (int i = 0; i < qiao_bezier_2.size(); i++) {
        qiao_xiuzheng.push_back(Point(qiao_bezier_2[i].x, qiao_bezier_2[i].y));
    }
    //后面的像素点
    mark_child = 0;//标记位
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

//02.28新增：“短桥”的合并
void duanqiao(Mat& image, Mat& image1, int NPB, int NSP, StrokesInfo* strokesinfo, double Median, vector<Point>& se, qiaoInfo* qiaoinfo,sfInfo* sfinfo, 
    vector<Point>& edge_center, vector<Point>& edge) {
    int uw = NPB / NSP;//平均笔画宽度
    int qiao_count = -1;
    //找出笔画段中的“短桥”并存储进结构体中
    for (size_t index = 0; index < 20; index++) {
        //“桥”的长度小于uw
        if (strokesinfo[index].begin.x != 0 && strokesinfo[index].tem.size() <= Median) {//1.2 * uw

            //“桥”的两端不能有端点
            int flag = 0;
            for (size_t i = 0; i < se.size(); i++) {
                if ((strokesinfo[index].begin.x == se[i].x && strokesinfo[index].begin.y == se[i].y) ||
                    (strokesinfo[index].end.x == se[i].x && strokesinfo[index].end.y == se[i].y)) {
                    flag = 1;
                }
            }
            //“桥”笔画段输出
            if (flag == 0) {
                qiao_count++;
                //将“桥”笔画存储进“桥”结构体中
                qiaoinfo[qiao_count].begin.x = strokesinfo[index].begin.x;
                qiaoinfo[qiao_count].begin.y = strokesinfo[index].begin.y;
                qiaoinfo[qiao_count].end.x = strokesinfo[index].end.x;
                qiaoinfo[qiao_count].end.y = strokesinfo[index].end.y;
                qiaoinfo[qiao_count].dir = strokesinfo[index].dir;
                for (int i = 0; i < strokesinfo[index].tem.size(); i++) {
                    qiaoinfo[qiao_count].tem.push_back(Point(strokesinfo[index].tem[i].x, strokesinfo[index].tem[i].y));
                }

                //判断“桥”起点是否处于交叉点簇中，若处于，则说明起点连接的不只一条笔画段，
                int flag_sfinfo = 0;//标记起点处于交叉点簇的位置
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
                //当“桥”起点处于交叉点簇中, 查找“桥”起点处于的交叉点簇的笔画段并存储进容器中
                if (flag_sfinfo >= 0) {
                    for (int k = 0; k < sfinfo[flag_sfinfo].sf_info.size(); k++) {
                        qiaoinfo[qiao_count].flag_sfvec.push_back(Point(sfinfo[flag_sfinfo].sf_info[k].x, sfinfo[flag_sfinfo].sf_info[k].y));
                        //cout << "“桥”起点处于的交叉点簇" << "(" << sfinfo[flag_sfinfo].sf_info[k].x << "," << sfinfo[flag_sfinfo].sf_info[k].y << ")" << endl;
                    }
                }//当“桥”起点不处于交叉点簇中, “桥”起点存储进容器中
                else   qiaoinfo[qiao_count].flag_sfvec.push_back(Point(strokesinfo[index].begin.x, strokesinfo[index].begin.y));


                //判断“桥”终点是否处于交叉点簇中，若处于，则说明起点连接的不只一条笔画段
                int flag_sfinfo1 = 0;//标记终点处于交叉点簇的位置
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
                //当“桥”终点处于交叉点簇中, 查找“桥”终点处于的交叉点簇的笔画段并存储进容器中
                if (flag_sfinfo1 >= 0) {
                    for (int k = 0; k < sfinfo[flag_sfinfo1].sf_info.size(); k++) {
                        qiaoinfo[qiao_count].flag_sfvec1.push_back(Point(sfinfo[flag_sfinfo1].sf_info[k].x, sfinfo[flag_sfinfo1].sf_info[k].y));
                    }
                }//当“桥”终点不处于交叉点簇中, “桥”终点存储进容器中
                else   qiaoinfo[qiao_count].flag_sfvec1.push_back(Point(strokesinfo[index].end.x, strokesinfo[index].end.y));
            }
        }
    }

    //判断“桥”中是否有连接，若有连接，则link标记
    //for (int i = 0; i < 20 && qiaoinfo[i].begin.x != 0; i++) {
    //    for (int j = 0; j < 20 && qiaoinfo[j].begin.x != 0; j++) {
    //        if (i != j) {
    //            if (qiaoinfo[j].flag_sfinfo == qiaoinfo[i].flag_sfinfo1 || qiaoinfo[i].flag_sfinfo == qiaoinfo[j].flag_sfinfo1) {
    //                qiaoinfo[i].link = j;
    //                qiaoinfo[j].link = i;//桥i和桥j互为连接
    //            }
    //        }
    //    }
    //}

    //遍历“桥”起、终点容器中连接的所有笔画段，注意一个点可能会存在多个笔画段，存入结构体
    for (int index = 0; index < 20 && qiaoinfo[index].begin.x != 0; index++) {
        for (int j1 = 0; j1 < qiaoinfo[index].flag_sfvec.size(); j1++) {
            int flag_start = 0;//“桥”起点连接的笔画段
            cout << "“桥”起点容器==(" << qiaoinfo[index].flag_sfvec[j1].x << "," << qiaoinfo[index].flag_sfvec[j1].y << ")" << endl;
            for (int index1 = 0; index1 < 20; index1++) {
                //首先去除所有桥
                int fouding = 0;//去除桥自身的判断符
                if ((strokesinfo[index1].begin.x == qiaoinfo[index].begin.x && strokesinfo[index1].begin.y == qiaoinfo[index].begin.y &&
                    (strokesinfo[index1].end.x == qiaoinfo[index].end.x && strokesinfo[index1].end.y == qiaoinfo[index].end.y))) {
                    fouding = 1;
                }
                if (fouding == 0) {
                    if ((strokesinfo[index1].begin.x == qiaoinfo[index].flag_sfvec[j1].x && strokesinfo[index1].begin.y == qiaoinfo[index].flag_sfvec[j1].y) ||
                        (strokesinfo[index1].end.x == qiaoinfo[index].flag_sfvec[j1].x && strokesinfo[index1].end.y == qiaoinfo[index].flag_sfvec[j1].y)) {
                        flag_start = index1;
                        cout << endl;
                        cout << "“桥”起点连接的flag_start的笔画：" << endl;
                        cout << "(" << strokesinfo[flag_start].begin.x << "," << strokesinfo[flag_start].begin.y << ")--(" << strokesinfo[flag_start].end.x << "," << strokesinfo[flag_start].end.y << ")" << endl;
                        cout << "8领域：" << endl;
                        for (int i23 = 0; i23 < strokesinfo[flag_start].snake.size(); i23++) {
                            cout << strokesinfo[flag_start].snake[i23];
                        }
                        cout << endl;
                        //将笔画段存入begin_line
                        qiaoinfo[index].begin_line_begin.push_back(Point(strokesinfo[flag_start].begin.x, strokesinfo[flag_start].begin.y));
                        qiaoinfo[index].begin_line_end.push_back(Point(strokesinfo[flag_start].end.x, strokesinfo[flag_start].end.y));

                        //“桥”起终点连接的笔画段与“桥”的连接方式，0表示起点与桥相连，1表示终点与桥相连
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
            int flag_start = 0;//“桥”终点连接的笔画段
            cout << "“桥”终点容器==(" << qiaoinfo[index].flag_sfvec1[j1].x << "," << qiaoinfo[index].flag_sfvec1[j1].y << ")" << endl;
            for (int index1 = 1; index1 < 20; index1++) {
                //首先去除所有桥
                int fouding = 0;//去除桥自身的判断符
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
                        cout << "“桥”终点连接的flag_start的笔画：" << endl;
                        cout << "(" << strokesinfo[flag_start].begin.x << "," << strokesinfo[flag_start].begin.y << ")--(" << strokesinfo[flag_start].end.x << "," << strokesinfo[flag_start].end.y << ")" << endl;
                        cout << "8领域：" << endl;
                        for (int i23 = 0; i23 < strokesinfo[flag_start].snake.size(); i23++) {
                            cout << strokesinfo[flag_start].snake[i23];
                        }
                        cout << endl;
                        //将笔画段存入end_line
                        qiaoinfo[index].end_line_begin.push_back(Point(strokesinfo[flag_start].begin.x, strokesinfo[flag_start].begin.y));
                        qiaoinfo[index].end_line_end.push_back(Point(strokesinfo[flag_start].end.x, strokesinfo[flag_start].end.y));

                        //“桥”起终点连接的笔画段与“桥”的连接方式，0表示起点与桥相连，1表示终点与桥相连
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

    //输出“桥”结构体
    for (int i = 0; i < 20; i++) {
        if (qiaoinfo[i].begin.x != 0) {
            cout << endl;
            cout << "桥begin==(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")" << endl;
            cout << "桥end==(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
            cout << "笔画方向==" << qiaoinfo[i].dir << endl;
            cout << "笔画长度==" << qiaoinfo[i].tem.size() << endl;
            cout << "笔画像素点：" << endl;
            for (int j = 0; j < qiaoinfo[i].tem.size(); j++) {
                cout << "(" << qiaoinfo[i].tem[j].x << "," << qiaoinfo[i].tem[j].y << ") ";
            }
            cout << endl;
            cout << "起点处于交叉点簇的位置==" << qiaoinfo[i].flag_sfinfo << endl;
            cout << "终点处于交叉点簇的位置==" << qiaoinfo[i].flag_sfinfo1 << endl;

            for (int j1 = 0; j1 < qiaoinfo[i].flag_sfvec.size(); j1++) {
                cout << "“桥”起点容器==(" << qiaoinfo[i].flag_sfvec[j1].x << "," << qiaoinfo[i].flag_sfvec[j1].y << ")" << endl;
            }
            for (int j1 = 0; j1 < qiaoinfo[i].flag_sfvec1.size(); j1++) {
                cout << "“桥”终点容器==(" << qiaoinfo[i].flag_sfvec1[j1].x << "," << qiaoinfo[i].flag_sfvec1[j1].y << ")" << endl;
            }
            cout << "“桥”起点连接笔画段:" << endl;
            for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
                cout << "(" << qiaoinfo[i].begin_line_begin[j1].x << "," << qiaoinfo[i].begin_line_begin[j1].y << ")--("
                    << qiaoinfo[i].begin_line_end[j1].x << "," << qiaoinfo[i].begin_line_end[j1].y << ")" << endl;
                //cout <<"“桥”起终点连接的笔画段与“桥”的连接方式，0表示起点与桥相连，1表示终点与桥相连"<< qiaoinfo[i].begin_line[j1] << endl;
            }
            cout << "“桥”终点连接笔画段:" << endl;
            for (int j1 = 0; j1 < qiaoinfo[i].end_line_begin.size(); j1++) {
                cout << "(" << qiaoinfo[i].end_line_begin[j1].x << "," << qiaoinfo[i].end_line_begin[j1].y << ")--("
                    << qiaoinfo[i].end_line_end[j1].x << "," << qiaoinfo[i].end_line_end[j1].y << ")" << endl;
                //cout << "“桥”起终点连接的笔画段与“桥”的连接方式，0表示起点与桥相连，1表示终点与桥相连" << qiaoinfo[i].end_line[j1] << endl;

            }
            cout << endl;
        }
    }

    //遍历“桥”里面的begin_line和end_line，合并笔画
    for (int i = 0; i < 20 && qiaoinfo[i].begin.x != 0; i++) {

        int count = 0;//判断当前桥有几组笔画段合并
        cout << endl;
        cout << "当前桥为：(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
        cout << "“桥”起点连接笔画段:" << endl;
        for (int j1 = 0; j1 < qiaoinfo[i].begin_line_begin.size(); j1++) {
            cout << "(" << qiaoinfo[i].begin_line_begin[j1].x << "," << qiaoinfo[i].begin_line_begin[j1].y << ")--("
                << qiaoinfo[i].begin_line_end[j1].x << "," << qiaoinfo[i].begin_line_end[j1].y << ")" << endl;
            //cout <<"“桥”起终点连接的笔画段与“桥”的连接方式，0表示起点与桥相连，1表示终点与桥相连"<< qiaoinfo[i].begin_line[j1] << endl;
        }
        cout << "“桥”终点连接笔画段:" << endl;
        for (int j1 = 0; j1 < qiaoinfo[i].end_line_begin.size(); j1++) {
            cout << "(" << qiaoinfo[i].end_line_begin[j1].x << "," << qiaoinfo[i].end_line_begin[j1].y << ")--("
                << qiaoinfo[i].end_line_end[j1].x << "," << qiaoinfo[i].end_line_end[j1].y << ")" << endl;
            //cout << "“桥”起终点连接的笔画段与“桥”的连接方式，0表示起点与桥相连，1表示终点与桥相连" << qiaoinfo[i].end_line[j1] << endl;

        }

        //遍历“桥”起点连接的笔画段
        for (int begin_i = 0; begin_i < qiaoinfo[i].begin_line_begin.size() && qiaoinfo[i].begin_line_begin[begin_i].x != 0; begin_i++) {
            //判断笔画段方向
            int flag_trend = 0, flag_trend_start = 0, flag_trend_end = 0;//趋势的判断符

            //找到strokesinfo中的对应位置
            int sit = 0;//位置记号符
            for (int j = 0; j < 20; j++) {
                if ((strokesinfo[j].begin.x == qiaoinfo[i].begin_line_begin[begin_i].x) && (strokesinfo[j].begin.y == qiaoinfo[i].begin_line_begin[begin_i].y)
                    && (strokesinfo[j].end.x == qiaoinfo[i].begin_line_end[begin_i].x) && (strokesinfo[j].end.y == qiaoinfo[i].begin_line_end[begin_i].y)) {
                    sit = j;
                }
            }
            cout << endl;
            cout << "遍历“桥”起点连接的笔画段:(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--("
                << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

            //“桥”起点连接的笔画段的起点与桥的起点相邻，正序判断趋势
            if (qiaoinfo[i].begin_line[begin_i] == 0) {
                int zero = 0, one = 0, two = 0, three = 0;//方向
                for (int i23 = 0; i23 < uw && i23 < strokesinfo[sit].snake.size(); i23++) {
                    //cout << strokesinfo[sit].snake[i23];
                    if (strokesinfo[sit].snake[i23] == 0 || strokesinfo[sit].snake[i23] == 4)zero++;
                    if (strokesinfo[sit].snake[i23] == 1 || strokesinfo[sit].snake[i23] == 5)one++;
                    if (strokesinfo[sit].snake[i23] == 2 || strokesinfo[sit].snake[i23] == 6)two++;
                    if (strokesinfo[sit].snake[i23] == 3 || strokesinfo[sit].snake[i23] == 7)three++;
                }
                int flag_dir = 0;
                //找四个数中最大的
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
            //“桥”起点连接的笔画段的终点与桥的起点相邻，逆序判断趋势
            if (qiaoinfo[i].begin_line[begin_i] == 1) {
                int zero = 0, one = 0, two = 0, three = 0;//方向
                for (int i23 = strokesinfo[sit].snake.size() - 1; i23 > strokesinfo[sit].snake.size() - 1 - uw && i23 > 0; i23--) {
                    //cout << endl;
                    //cout << strokesinfo[sit].snake[i23];
                    if (strokesinfo[sit].snake[i23] == 0 || strokesinfo[sit].snake[i23] == 4)zero++;
                    if (strokesinfo[sit].snake[i23] == 1 || strokesinfo[sit].snake[i23] == 5)one++;
                    if (strokesinfo[sit].snake[i23] == 2 || strokesinfo[sit].snake[i23] == 6)two++;
                    if (strokesinfo[sit].snake[i23] == 3 || strokesinfo[sit].snake[i23] == 7)three++;
                }
                int flag_dir = 0;
                //找四个数中最大的
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


            //遍历“桥”终点连接的笔画段
            for (int end_i = 0; end_i < qiaoinfo[i].end_line_begin.size() && qiaoinfo[i].end_line_begin[end_i].x != 0; end_i++) {
                //找到strokesinfo中的对应位置

                int sit1 = 0;//位置记号符
                for (int j1 = 0; j1 < 20; j1++) {
                    if ((strokesinfo[j1].begin.x == qiaoinfo[i].end_line_begin[end_i].x) && (strokesinfo[j1].begin.y == qiaoinfo[i].end_line_begin[end_i].y)
                        && (strokesinfo[j1].end.x == qiaoinfo[i].end_line_end[end_i].x) && (strokesinfo[j1].end.y == qiaoinfo[i].end_line_end[end_i].y)) {
                        sit1 = j1;
                    }
                }
                cout << endl;
                cout << "遍历“桥”终点连接的笔画段:(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--("
                    << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

                //“桥”终点连接的笔画段的起点与桥的起点相邻，正序判断趋势
                if (qiaoinfo[i].end_line[end_i] == 0) {
                    int zero = 0, one = 0, two = 0, three = 0;//方向
                    for (int i24 = 0; i24 < uw && i24 < strokesinfo[sit1].snake.size(); i24++) {
                        //cout << strokesinfo[sit1].snake[i24];
                        if (strokesinfo[sit1].snake[i24] == 0 || strokesinfo[sit1].snake[i24] == 4)zero++;
                        if (strokesinfo[sit1].snake[i24] == 1 || strokesinfo[sit1].snake[i24] == 5)one++;
                        if (strokesinfo[sit1].snake[i24] == 2 || strokesinfo[sit1].snake[i24] == 6)two++;
                        if (strokesinfo[sit1].snake[i24] == 3 || strokesinfo[sit1].snake[i24] == 7)three++;
                    }
                    int flag_dir = 0;
                    //找四个数中最大的
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
                //“桥”终点连接的笔画段的起点与桥的终点相邻，逆序判断趋势
                if (qiaoinfo[i].end_line[end_i] == 1) {
                    int zero = 0, one = 0, two = 0, three = 0;//方向
                    for (int i24 = strokesinfo[sit1].snake.size() - 1; i24 > strokesinfo[sit1].snake.size() - 1 - uw && i24 > 0; i24--) {
                        //cout << strokesinfo[sit1].snake[i24];
                        if (strokesinfo[sit1].snake[i24] == 0 || strokesinfo[sit1].snake[i24] == 4)zero++;
                        if (strokesinfo[sit1].snake[i24] == 1 || strokesinfo[sit1].snake[i24] == 5)one++;
                        if (strokesinfo[sit1].snake[i24] == 2 || strokesinfo[sit1].snake[i24] == 6)two++;
                        if (strokesinfo[sit1].snake[i24] == 3 || strokesinfo[sit1].snake[i24] == 7)three++;
                    }
                    int flag_dir = 0;
                    //找四个数中最大的
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

                //除去相同的笔画段和桥本身
                int flagk = 0;
                if (strokesinfo[sit].begin.x == strokesinfo[sit1].begin.x && strokesinfo[sit].begin.y == strokesinfo[sit1].begin.y &&
                    strokesinfo[sit].end.x == strokesinfo[sit1].end.x && strokesinfo[sit].end.y == strokesinfo[sit1].end.y) {
                    flagk = 1;
                }
                //再一次检查桥连接笔画段是否跟桥的端点在同一个交叉点簇中，使用欧氏距离判断
                if (distance(strokesinfo[sit].begin, qiaoinfo[i].begin) > uw && distance(strokesinfo[sit].end, qiaoinfo[i].begin) > uw) {
                    flagk = 1;
                }
                if (distance(strokesinfo[sit1].begin, qiaoinfo[i].end) > uw && distance(strokesinfo[sit1].end, qiaoinfo[i].end) > uw) {
                    flagk = 1;
                }

                if (flagk == 0) {
                    if (flag_trend_start == flag_trend_end || strokesinfo[sit].dir == strokesinfo[sit1].dir || abs(flag_trend_end - flag_trend_start) <= 1) {//
                        cout << endl;
                        cout << "==================================合并笔画================================：" << endl;
                        cout << "flag_trend_start=" << flag_trend_start << endl;
                        cout << "flag_trend_end=" << flag_trend_end << endl;

                        cout << "(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;
                        cout << "(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;
                        cout << endl;

                        count++;
                        Point replace_begin = strokesinfo[sit].begin;//前一个合并笔画的起点
                        Point replace_end = strokesinfo[sit].end;//前一个合并笔画的终点
                        Point replace1_begin = strokesinfo[sit1].begin;//后一个合并笔画的起点
                        Point replace1_end = strokesinfo[sit1].end;//后一个合并笔画的终点

                        //合并两个笔画段
                        if (strokesinfo[sit].dir == 0) {
                            if (strokesinfo[sit].begin.y < strokesinfo[sit1].begin.y) {//sit1在后面
                                strokesinfo[sit].end.x = strokesinfo[sit1].end.x;
                                strokesinfo[sit].end.y = strokesinfo[sit1].end.y;
                                strokesinfo[sit1].begin.x = strokesinfo[sit1].begin.y = 0;
                                strokesinfo[sit1].end.x = strokesinfo[sit1].end.y = 0;
                                //清除当前桥在strokesinfo中
                                //cout << "当前桥为：(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
                                for (int cl = 0; cl < 20; cl++) {
                                    if ((strokesinfo[cl].begin.x == qiaoinfo[i].begin.x) && (strokesinfo[cl].begin.y == qiaoinfo[i].begin.y)
                                        && (strokesinfo[cl].end.x == qiaoinfo[i].end.x) && (strokesinfo[cl].end.y == qiaoinfo[i].end.y)) {
                                        strokesinfo[cl].begin.x = strokesinfo[cl].begin.y = 0;
                                        strokesinfo[cl].end.x = strokesinfo[cl].end.y = 0;
                                        strokesinfo[cl].tem.clear();

                                    }
                                }
                                //添加桥的像素点
                                for (int tem_i = 0; tem_i < qiaoinfo[i].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(qiaoinfo[i].tem[tem_i]));
                                }
                                //将后面笔画段的像素点加到前面的
                                for (int tem_i = 0; tem_i < strokesinfo[sit1].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(strokesinfo[sit1].tem[tem_i]));
                                }
                                //清空后面笔画段的像素点容器和桥的像素点
                                strokesinfo[sit1].tem.clear();

                                //替换“桥”结构体的笔画段
                                for (int rei = 0; rei < 20; rei++) {
                                    if (qiaoinfo[rei].begin.x != 0) {
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].begin_line_begin.size(); rej1++) {
                                            //替换已合并笔画段：
                                            if (replace_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;
                                            }
                                            if (replace1_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace1_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }

                                        }
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].end_line_begin.size(); rej1++) {
                                            //替换已合并笔画段：
                                            if (replace_begin == qiaoinfo[rei].end_line_begin[rej1] && replace_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit].end;
                                                // cout << "替换后的笔画段为：(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].end_line_begin[rej1] && replace1_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit].end;
                                                //cout << "替换后的笔画段为：(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }
                                        }
                                    }
                                }

                            }
                            if (strokesinfo[sit].begin.y > strokesinfo[sit1].begin.y) {//sit在后面
                                strokesinfo[sit1].end.x = strokesinfo[sit].end.x;
                                strokesinfo[sit1].end.y = strokesinfo[sit].end.y;
                                strokesinfo[sit].begin.x = strokesinfo[sit].begin.y = 0;
                                strokesinfo[sit].end.x = strokesinfo[sit].end.y = 0;
                                //清除当前桥在strokesinfo中
                                //cout << "当前桥为：(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
                                for (int cl = 0; cl < 20; cl++) {
                                    if ((strokesinfo[cl].begin.x == qiaoinfo[i].begin.x) && (strokesinfo[cl].begin.y == qiaoinfo[i].begin.y)
                                        && (strokesinfo[cl].end.x == qiaoinfo[i].end.x) && (strokesinfo[cl].end.y == qiaoinfo[i].end.y)) {
                                        strokesinfo[cl].begin.x = strokesinfo[cl].begin.y = 0;
                                        strokesinfo[cl].end.x = strokesinfo[cl].end.y = 0;
                                        strokesinfo[cl].tem.clear();

                                    }
                                }
                                //添加桥的像素点
                                for (int tem_i = 0; tem_i < qiaoinfo[i].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(qiaoinfo[i].tem[tem_i]));
                                }
                                //将后面笔画段的像素点加到前面的
                                for (int tem_i = 0; tem_i < strokesinfo[sit].tem.size(); tem_i++) {
                                    strokesinfo[sit1].tem.push_back(Point(strokesinfo[sit].tem[tem_i]));
                                }
                                //清空后面笔画段的像素点容器和桥的像素点
                                strokesinfo[sit].tem.clear();

                                //替换“桥”结构体的笔画段
                                for (int rei = 0; rei < 20; rei++) {
                                    if (qiaoinfo[rei].begin.x != 0) {
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].begin_line_begin.size(); rej1++) {
                                            //替换已合并笔画段：
                                            if (replace_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit1].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit1].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace1_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit1].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit1].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

                                            }

                                        }
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].end_line_begin.size(); rej1++) {
                                            //替换已合并笔画段：
                                            if (replace_begin == qiaoinfo[rei].end_line_begin[rej1] && replace_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit1].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit1].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].end_line_begin[rej1] && replace1_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit1].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit1].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit1].begin.x << "," << strokesinfo[sit1].begin.y << ")--(" << strokesinfo[sit1].end.x << "," << strokesinfo[sit1].end.y << ")" << endl;

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
                                //清除当前桥在strokesinfo中
                                //cout << "当前桥为：(" << qiaoinfo[i].begin.x << "," << qiaoinfo[i].begin.y << ")--(" << qiaoinfo[i].end.x << "," << qiaoinfo[i].end.y << ")" << endl;
                                for (int cl = 0; cl < 20; cl++) {
                                    if ((strokesinfo[cl].begin.x == qiaoinfo[i].begin.x) && (strokesinfo[cl].begin.y == qiaoinfo[i].begin.y)
                                        && (strokesinfo[cl].end.x == qiaoinfo[i].end.x) && (strokesinfo[cl].end.y == qiaoinfo[i].end.y)) {
                                        strokesinfo[cl].begin.x = strokesinfo[cl].begin.y = 0;
                                        strokesinfo[cl].end.x = strokesinfo[cl].end.y = 0;
                                        strokesinfo[cl].tem.clear();
                                    }
                                }


                                //添加桥
                                for (int tem_i = 0; tem_i < qiaoinfo[i].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(qiaoinfo[i].tem[tem_i]));
                                }
                                //将后面笔画段的像素点加到前面的
                                for (int tem_i = 0; tem_i < strokesinfo[sit1].tem.size(); tem_i++) {
                                    strokesinfo[sit].tem.push_back(Point(strokesinfo[sit1].tem[tem_i]));
                                }
                                //清空后面笔画段的像素点容器和桥的像素点
                                strokesinfo[sit1].tem.clear();

                                //替换“桥”结构体的笔画段
                                for (int rei = 0; rei < 20; rei++) {
                                    if (qiaoinfo[rei].begin.x != 0) {
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].begin_line_begin.size(); rej1++) {
                                            //替换已合并笔画段：
                                            if (replace_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].begin_line_begin[rej1] && replace1_end == qiaoinfo[rei].begin_line_end[rej1]) {
                                                qiaoinfo[rei].begin_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].begin_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }

                                        }
                                        for (int rej1 = 0; rej1 < qiaoinfo[rei].end_line_begin.size(); rej1++) {
                                            //替换已合并笔画段：
                                            if (replace_begin == qiaoinfo[rei].end_line_begin[rej1] && replace_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

                                            }
                                            if (replace1_begin == qiaoinfo[rei].end_line_begin[rej1] && replace1_end == qiaoinfo[rei].end_line_end[rej1]) {
                                                qiaoinfo[rei].end_line_begin[rej1] = strokesinfo[sit].begin;
                                                qiaoinfo[rei].end_line_end[rej1] = strokesinfo[sit].end;
                                                cout << "替换后的笔画段为：(" << strokesinfo[sit].begin.x << "," << strokesinfo[sit].begin.y << ")--(" << strokesinfo[sit].end.x << "," << strokesinfo[sit].end.y << ")" << endl;

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
            //判断当前“桥”属于“十”字型交叉区，并计算出共享区的中心点
            cout << "当前“桥”属于“十”字型交叉区" << endl;
            //调用“桥”笔画修正算法
            correct_qiao(image, image1, i, uw, qiaoinfo, edge_center, edge, strokesinfo);
        }
    }

}

//三阶贝塞尔曲线
void bezier_3(double p[4][2], vector<Point>& point_bezier_3)
{
    double t, t1, t2, xt, yt;
    int rate = 200, x, y;
    int count = 0;
    //setcolor(color);
    //moveto(p[0][0], p[0][1]);
    //cout << "贝塞尔点为" << endl;
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
         cout << "第" << count << "个贝塞尔点为：(" << x << "," << y << ")" << endl;*/
        point_bezier_3.push_back(Point(x, y));

        //去重
        for (size_t i = 0; i < point_bezier_3.size() - 1; i++) {
            if (x == point_bezier_3[i].x && y == point_bezier_3[i].y) {
                point_bezier_3.pop_back();
            }
        }
    }
    /*   for (size_t i = 0; i < point_bezier_3.size(); i++) {
           cout << "第" << i << "个贝塞尔点为：(" << point_bezier_3[i].x << "," << point_bezier_3[i].y << ")" << endl;
       }*/
}

//“钩”型笔画差分改进进化：
void gou1(vector<Point>& S_0, vector<Point>& S_1, vector<Point>& S_2) {
      for (size_t i = 0; i < S_0.size(); i++) {
          cout << "第" << i << "个S_0点为：(" << S_0[i].x << "," << S_0[i].y << ")" << endl;
      }
      cout << endl;
      for (size_t i = 0; i < S_1.size(); i++) {
          cout << "第" << i << "个S_1点为：(" << S_1[i].x << "," << S_1[i].y << ")" << endl;
      }
      cout << endl;

      //S_0为点1开始的原始钩型笔画点，S_1为第一次贝塞尔拟合后的点
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
            cout << "第" << i << "个S_2点为：(" << S_2[i].x << "," << S_2[i].y << ")" << endl;
        }*/

        //定义一个临时容器
        vector<Point> S_2_temp;
        S_2_temp.push_back(Point(S_2[0].x, S_2[0].y));

        //判断S_2点是否连续，若不连续，添加像素点
        for (size_t i = 1; i < S_2.size(); i++) {
            Point tem;
            tem = S_2[i];
            cout << endl;
            /*cout << "fabs(tem.x - S_2[i - 1].x======" << fabs(tem.x - S_2[i - 1].x) << endl;
            cout << "fabs(tem.y - S_2[i - 1].y======" << fabs(tem.y - S_2[i - 1].y) << endl;*/
            if (tem.x != S_2[i - 1].x || tem.y != S_2[i - 1].y) {
                //判断当前点不在上一个点的八领域中
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
                        //在x方向不相邻，需要补相应的像素点
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
                        //在y方向不相邻，需要补相应的像素点
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

        //cout << "S_2_temp点" << endl;
        //for (size_t i = 0; i < S_2_temp.size(); i++) {
        //    
        //    cout << "第" << i << "个S_2_temp点为=========：(" << S_2_temp[i].x << "," << S_2_temp[i].y << ")" << endl;
        //}

        S_2.clear();
        for (size_t i = 0; i < S_2_temp.size(); i++) {
            S_2.push_back(Point(S_2_temp[i].x, S_2_temp[i].y));
        }
    }
}

//1.21修改：特殊笔画处理-“钩”型笔画：
void gou(Mat& image, Mat& image1, StrokesInfo* strokesinfo, vector<Point>& point_gou_mark, sfInfo* sfinfo, vector<Point>& se,
    int one_x, int two_x, int three_x, int four_x, int five_x, int six_x, int seven_x, int one_y, int two_y, int three_y, int four_y, int five_y,
    int six_y, int seven_y, double Median, vector<Point>& S_0, vector<Point>& S_1, vector<Point>& S_2, vector<Point>& s1,vector<Point>& point_bezier_3) {
    cout << endl;
    cout << "1.21修改：特殊笔画处理 - “钩”型笔画：" << endl;
    cout << "=====找到方向为2的笔画段====" << endl;
    for (size_t i = 0; i < 20; i++) {
        if (strokesinfo[i].dir == 2 || strokesinfo[i].dir == 5) {
            cout << "方向为2或5的笔画段：(" << strokesinfo[i].begin.x << "," << strokesinfo[i].begin.y << ")--(" << strokesinfo[i].end.x << "," << strokesinfo[i].end.y << ")" << endl;

            //笔画长度==60
            if (strokesinfo[i].snake_length > 60) {
                //判断终止点（即点7）附近是否存在两个端点（即点3、点2）//1.21修改：判断点7所在的交叉点簇是否只有两个短笔段连接,并且这两个笔画段都有一个为端点
                int count = 0;
                point_gou_mark.clear();

                //判断“点7”是否处于交叉点簇中，若处于，则说明起点连接的不只一条笔画段，
                int flag_7 = 0;//标记起点处于交叉点簇的位置
                vector<Point> flag_7vec;
                for (int j = 0; j < 20; j++) {
                    for (int j1 = 0; j1 < sfinfo[j].sf_info.size(); j1++) {
                        if (sfinfo[j].sf_info[j1].x == strokesinfo[i].end.x && sfinfo[j].sf_info[j1].y == strokesinfo[i].end.y) {
                            flag_7 = j;
                            cout << "“点7”处于交叉点簇中 flag_7 = " << flag_7 << endl;
                        }
                    }
                }
                //当“点7”处于交叉点簇中, 查找“点7”起点处于的交叉点簇的笔画段并存储进容器中
                if (flag_7 != 0) {
                    for (int k = 0; k < sfinfo[flag_7].sf_info.size(); k++) {
                        flag_7vec.push_back(Point(sfinfo[flag_7].sf_info[k].x, sfinfo[flag_7].sf_info[k].y));
                        cout << "“点7”处于交叉点簇中" << endl;
                        cout << "(" << sfinfo[flag_7].sf_info[k].x << "," << sfinfo[flag_7].sf_info[k].y << ")" << endl;
                    }
                }
                for (int j12 = 0; j12 < flag_7vec.size(); j12++) {
                    cout << "(" << flag_7vec[j12].x << "," << flag_7vec[j12].y << ")" << endl;

                }
                //1.21修改：判断点7所在的交叉点簇是否只有两个短笔段连接
                int mark6 = 0;//作为控制点6所在笔画段的标记符
                int mark3 = 0;//作为控制点3所在笔画段的标记符
                for (int j12 = 0; j12 < flag_7vec.size(); j12++) {
                    for (int index1 = 1; index1 < 20; index1++) {

                        //笔画段起点在交叉簇中，终点为端点
                        if (strokesinfo[index1].begin.x == flag_7vec[j12].x && strokesinfo[index1].begin.y == flag_7vec[j12].y && strokesinfo[index1].snake_length < Median) {

                            for (int j2 = 0; j2 < se.size(); j2++) {
                                if (strokesinfo[index1].end.x == se[j2].x && strokesinfo[index1].end.y == se[j2].y) {
                                    count++;
                                    cout << "count==" << count << endl;
                                    cout << "笔画段起点在交叉簇中，终点为端点" << endl;
                                    cout << "(" << strokesinfo[index1].end.x << "," << strokesinfo[index1].end.y << ")" << endl;
                                    //控制点2：
                                    two_x = strokesinfo[index1].end.x;
                                    two_y = strokesinfo[index1].end.y;

                                    mark6 = index1;
                                }
                            }
                        }
                        //笔画段终点在交叉簇中，起点为端点
                        if (strokesinfo[index1].end.x == flag_7vec[j12].x && strokesinfo[index1].end.y == flag_7vec[j12].y && strokesinfo[index1].snake_length < Median) {
                            for (int j2 = 0; j2 < se.size(); j2++) {
                                if (strokesinfo[index1].begin.x == se[j2].x && strokesinfo[index1].begin.y == se[j2].y) {
                                    count++;
                                    cout << "count==" << count << endl;
                                    cout << "笔画段终点在交叉簇中，起点为端点" << endl;
                                    cout << "(" << strokesinfo[index1].begin.x << "," << strokesinfo[index1].begin.y << ")" << endl;
                                    //控制点3：
                                    three_x = strokesinfo[index1].begin.x;
                                    three_y = strokesinfo[index1].begin.y;

                                    mark3 = index1;
                                }
                            }
                        }
                    }
                }

                //若满足条件的短笔画数为2个
                if (count == 2) {
                    cout << "count==2" << endl;

                    //控制点7：
                    seven_x = strokesinfo[i].end.x;
                    seven_y = strokesinfo[i].end.y;

                    //控制点1：
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

                    //点6的x:2和7的平均
                    six_x = (seven_x + two_x) / 2;
                    for (int mark1 = 0; mark1 < strokesinfo[mark6].snake_length; mark1++) {
                        if (six_x == strokesinfo[mark6].tem[mark1].x) {
                            six_y = strokesinfo[mark6].tem[mark1].y;
                        }
                    }
                    //控制点4
                    four_x = two_x;
                    //控制点5
                    five_y = one_y;
                    //点4和点5：需要在二值化后的黑点中找到，需要修改的限制条件？？
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
                            // cout << "第" << i << "个贝塞尔点为：(" << point_bezier_3[i].x << "," << point_bezier_3[i].y << ")" << endl;
                            S_1.push_back(Point(point_bezier_3[i].x, point_bezier_3[i].y));
                        }

                        static double p1[4][2] = { two_x,two_y,six_x,six_y,seven_x,seven_y,three_x,three_y };
                        bezier_3(p1, point_bezier_3);

                    }

                    //进行二次贝塞尔曲线拟合：
                    gou1(S_0,S_1, S_2);

                    //修改strokesinfo结构体存储的笔画段，将“钩”型的贝塞尔点加上
                    vector<Point> zan;//像素点暂存器
                    vector<int> zan_8;//8邻域暂存器

                    //向strokesinfo结构体中存储点1之前的像素点
                    for (size_t mg = 0; mg < strokesinfo[i].tem.size(); mg++) {
                        zan.push_back(Point(strokesinfo[i].tem[mg].x, strokesinfo[i].tem[mg].y));
                        zan_8.push_back(strokesinfo[i].snake[mg]);
                        if (strokesinfo[i].tem[mg].x == one_x && strokesinfo[i].tem[mg].y == one_y) {
                            //zan.pop_back();
                            break;
                        }
                    }
                    //向strokesinfo结构体中存储点1之后的S_2像素点
                    for (size_t mg1 = 0; mg1 < S_2.size(); mg1++) {
                        //cout << "第" << mg1 << "个贝塞尔点为：(" << point_bezier_3[mg1].x << "," << point_bezier_3[mg1].y << ")" << endl;
                        zan.push_back(Point(S_2[mg1].x, S_2[mg1].y));
                        //更新8链码
                            //通过后一个点和当前点比较，判断方向
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


                    //向strokesinfo结构体中存储S_2之后的剩余像素点
                    for (size_t mg1 = S_1.size(); mg1 < point_bezier_3.size(); mg1++) {
                        //cout << "第" << mg1 << "个贝塞尔点为：(" << point_bezier_3[mg1].x << "," << point_bezier_3[mg1].y << ")" << endl;
                        zan.push_back(Point(point_bezier_3[mg1].x, point_bezier_3[mg1].y));
                        //更新8链码
                            //通过后一个点和当前点比较，判断方向
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
                    //清除不需要的两个短笔画段
                    strokesinfo[mark6].tem.clear();
                    strokesinfo[mark3].tem.clear();
                    strokesinfo[mark6].begin.x = 0, strokesinfo[mark6].begin.y = 0;
                    strokesinfo[mark6].end.x = 0, strokesinfo[mark6].end.y = 0;
                    strokesinfo[mark3].begin.x = 0, strokesinfo[mark3].begin.y = 0;
                    strokesinfo[mark3].end.x = 0, strokesinfo[mark3].end.y = 0;
                    strokesinfo[mark6].snake_length = 0;
                    strokesinfo[mark3].snake_length = 0;
                    //像素点替换更新
                    for (size_t mg2 = 0; mg2 < zan.size(); mg2++) {
                        strokesinfo[i].tem.push_back(Point(zan[mg2].x, zan[mg2].y));
                    }
                    //8邻域替换更新
                    for (size_t mg2 = 0; mg2 < zan_8.size(); mg2++) {
                        strokesinfo[i].snake.push_back(zan_8[mg2]);
                    }
                }
            }
        }
    }

}

//找出A类短笔画中需要合并的笔画进行合并
void A_Combine(Mat& image, int NPB, int NSP,StrokesInfo* strokesinfo_com, double Median, vector<Point>& se, vector<Point>& sf,sfInfo* sfinfo) {
    int uw = NPB / NSP;
    Mat Aimage = image.clone();
    for (int i = 0; i < 20; i++)
    {
        if (strokesinfo_com[i].begin.x != 0 && strokesinfo_com[i].tem.size() < Median) {
            cout << "A类短笔画：(" << strokesinfo_com[i].begin.x << "," << strokesinfo_com[i].begin.y << ")--(" << strokesinfo_com[i].end.x << "," << strokesinfo_com[i].end.y << ")" << endl;
            /*int color = Aimage.at<uchar>((strokesinfo_com[i].begin.x, strokesinfo_com[i].begin.y));
            cout << "图像二值点为：" << color << endl;*/
            int jiaochadian = 0, duandian = 0;
            //找到端点se
            for (int k = 0; k < se.size(); k++) {
                if (strokesinfo_com[i].begin == se[k]) {
                    duandian = width_new(strokesinfo_com[i].begin, Aimage, uw);
                    cout << "端点的笔宽为：" << duandian << endl;
                }
                if (strokesinfo_com[i].end == se[k]) {
                    duandian = width_new(strokesinfo_com[i].end, Aimage, uw);
                    cout << "端点的笔宽为：" << duandian << endl;
                }
            }
            //找到交叉点sf
            for (int k = 0; k < sf.size(); k++) {
                if (strokesinfo_com[i].begin == sf[k]) {
                    jiaochadian = width_new(strokesinfo_com[i].begin, Aimage, uw);
                    cout << "交叉点的笔宽为：" << jiaochadian << endl;
                }
                if (strokesinfo_com[i].end == sf[k]) {
                    jiaochadian = width_new(strokesinfo_com[i].end, Aimage, uw);
                    cout << "交叉点的笔宽为：" << jiaochadian << endl;
                }
            }
            //判断笔画是否需要合并：从端点到交叉点的笔宽长度是从细到粗
            //这里判断端点笔宽<交叉点笔宽
            if (duandian < jiaochadian) {
                //判断交叉点所处的交叉点簇
                for (int j = 0; j < 20; j++) {
                    for (int n = 0; n < sfinfo[j].sf_info.size(); n++) {
                        //笔画begin在交叉簇中
                        if (strokesinfo_com[i].begin == sfinfo[j].sf_info[n]) {
                            //合并短笔画，与其交叉点簇相连的方向为2的笔画进行合并
                            for (int n1 = 0; n1 < sfinfo[j].sf_info.size(); n1++) {
                                if (n1 != n) {
                                    for (int i1 = 0; i1 < 20; i1++)
                                    {
                                        if (strokesinfo_com[i1].begin == sfinfo[j].sf_info[n1] && strokesinfo_com[i1].dir == 2) {
                                            cout << "存在方向为2的笔画:短笔画begin在交叉簇；2笔画begin在交叉簇" << endl;
                                            cout << strokesinfo_com[i1].begin.x << "," << strokesinfo_com[i1].begin.y << ")--(" << strokesinfo_com[i1].end.x << "," << strokesinfo_com[i1].end.y << ")" << endl;
                                        }
                                        if (strokesinfo_com[i1].end == sfinfo[j].sf_info[n1] && strokesinfo_com[i1].dir == 2) {
                                            cout << "存在方向为2的笔画:短笔画begin在交叉簇；2笔画end在交叉簇" << endl;
                                            cout << strokesinfo_com[i1].begin.x << "," << strokesinfo_com[i1].begin.y << ")--(" << strokesinfo_com[i1].end.x << "," << strokesinfo_com[i1].end.y << ")" << endl;

                                        }
                                    }
                                }
                            }
                        }
                        //笔画end在交叉簇中
                        if (strokesinfo_com[i].end == sfinfo[j].sf_info[n]) {
                            //合并短笔画，与其交叉点簇相连的方向为2的笔画进行合并
                            for (int n1 = 0; n1 < sfinfo[j].sf_info.size(); n1++) {
                                if (n1 != n) {
                                    for (int i1 = 0; i1 < 20; i1++)
                                    {
                                        if (strokesinfo_com[i1].begin == sfinfo[j].sf_info[n1] && strokesinfo_com[i1].dir == 2) {
                                            cout << "存在方向为2的笔画:短笔画end在交叉簇；2笔画begin在交叉簇" << endl;
                                            cout << strokesinfo_com[i1].begin.x << "," << strokesinfo_com[i1].begin.y << ")--(" << strokesinfo_com[i1].end.x << "," << strokesinfo_com[i1].end.y << ")" << endl;
                                            //合并strokesinfo_com并更新
                                            strokesinfo_com[i].end = strokesinfo_com[i1].end;
                                            strokesinfo_com[i1].begin = strokesinfo_com[i1].end = Point(0, 0);
                                            for (int i2 = 0; i2 < strokesinfo_com[i1].tem.size(); i2++) {
                                                strokesinfo_com[i].tem.push_back(strokesinfo_com[i1].tem[i2]);
                                            }
                                            strokesinfo_com[i1].tem.clear();

                                        }
                                        if (strokesinfo_com[i1].end == sfinfo[j].sf_info[n1] && strokesinfo_com[i1].dir == 2) {
                                            cout << "存在方向为2的笔画:短笔画end在交叉簇；2笔画end在交叉簇" << endl;
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


//绘制合并笔画之后的彩图，1.16加入“桥”的合并
Mat draw_picture1(Mat& image, vector<Point>& s1, StrokesInfo* strokesinfo_com, vector<Point>& point_bezier_2,
    vector<Point>& point_bezier_3, vector<Point>& S_2, int NPB, int NSP, sfInfo* sfinfo, vector<Point>& edge_center, vector<Point>& edge) {
    int uw = NPB / NSP;//平均笔画宽度
    int a = 1;
    int b = 1;
    int c = 1;
    //复制转化为彩色图像
    Mat draw1 = channelSwitching(image);
    //新建白底图像
    for (int i = 0; i < draw1.rows; i++)
    {
        for (int j = 0; j < draw1.cols; j++)
        {

            draw1.at<Vec3b>(i, j)[0] = 255;
            draw1.at<Vec3b>(i, j)[1] = 255;
            draw1.at<Vec3b>(i, j)[2] = 255;
        }
    }
    //做出二值化灰点
    for (size_t i = 0; i < s1.size(); i++)
    {
        Point tems;
        tems = s1[i];
        draw1.at<Vec3b>(tems.x, tems.y)[0] = 200;
        draw1.at<Vec3b>(tems.x, tems.y)[1] = 200;
        draw1.at<Vec3b>(tems.x, tems.y)[2] = 200;
    }

    //修正1026：绘制合并笔画之后的彩图，使用strokesinfo_com
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

    //11.13画出“山”的横折笔画：笔画方向为6
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

    //画出交叉点簇中心
    for (int i = 0; i <= 20; i++) {
        draw1.at<Vec3b>(sfinfo[i].Pc.x, sfinfo[i].Pc.y)[0] = 57;
        draw1.at<Vec3b>(sfinfo[i].Pc.x, sfinfo[i].Pc.y)[1] = 33;
        draw1.at<Vec3b>(sfinfo[i].Pc.x, sfinfo[i].Pc.y)[2] = 110;
    }
    ////画出交叉区中心
    //for (int i = 0; i < edge_center.size(); i++) {
    //    draw1.at<Vec3b>(edge_center[i].x, edge_center[i].y)[0] = 255;
    //    draw1.at<Vec3b>(edge_center[i].x, edge_center[i].y)[1] = 0;
    //    draw1.at<Vec3b>(edge_center[i].x, edge_center[i].y)[2] = 0;
    //    //画出交叉区
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
    //第一象限最短点edge
    for (int i = 0; i < edge.size(); i++) {
        cout << "edge最短距离点：(" << edge[i].x << "," << edge[i].y << ")" << endl;
        draw1.at<Vec3b>(edge[i].x, edge[i].y)[0] = 255;
        draw1.at<Vec3b>(edge[i].x, edge[i].y)[1] = 390;
        draw1.at<Vec3b>(edge[i].x, edge[i].y)[2] = 110;
    }

    return draw1;
}

