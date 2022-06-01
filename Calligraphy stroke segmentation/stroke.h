//method.h
#include<iostream>
using namespace std;

#include<iostream>
#include <QFileDialog>
#include <QThread>
#include <QtDebug>

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

//定义结构体数组存储骨架笔画{起始点，终止点，8链码序列}
struct StrokesInfo {
    Point begin;
    Point end;
    int snake_length;//8链码序列长度
    vector<int> snake;//定义一个方向容器
    vector<Point> tem;//定义一个像素点容器
    int dir;//笔画方向
    int num;//存储数组内成员个数
    int com_mark;//合并笔画标记
    int com_mark_max;//标记com_mark的最大值

};

struct sfInfo {//定义结构体数组存储交叉点簇
    Point begin; // 交叉点簇起点
    Point end;// 交叉点簇终点
    Point Pc;// 交叉点簇中心点
    vector<Point> sf_info;//交叉点簇容器
};

//定义结构体数组存储“桥”笔画
struct qiaoInfo {
    Point begin;
    Point end;
    int flag_sfinfo = 0;//标记起点处于交叉点簇的位置
    int flag_sfinfo1 = 0;//标记终点处于交叉点簇的位置
    vector<int> snake;//定义一个方向容器
    vector<Point> tem;//定义一个像素点容器
    int dir;//笔画方向
    vector<Point> flag_sfvec;//“桥”起点容器：主要存储“桥”起点所在交叉簇的所有点
    vector<Point> flag_sfvec1;//“桥”终点容器：主要存储“桥”终点所在交叉簇的所有点

    vector<Point> begin_line_begin, begin_line_end;//“桥”起点容器连接的所有笔画段
    vector<Point> end_line_begin, end_line_end;//“桥”终点容器连接的所有笔画段
    vector<int> begin_line, end_line;//“桥”起终点连接的笔画段与“桥”的连接方式，0表示起点与桥相连，1表示终点与桥相连
    int link;//连接桥标记

};

//在头文件中声明函数
int max(int x, int y); 

//zhang细化改进算法
void zhang_thinimage_improve(Mat& srcimage);

//单通道转三通道
Mat channelSwitching(const Mat& src);

//找出3类像素点
void search_point(Mat& image, vector<Point>& se, vector<Point>& sf, vector<Point>& s, vector<Point>& sef, sfInfo* sfinfo);

//将骨架笔画存储进结构体数组strokesinfo (1026增加：笔画方向为0的可能需要调换起始点)
void Save_strokesinfo(int num, vector<Point>& newpoint_mark, vector<Point>& newpoint, StrokesInfo* strokesinfo, double strokes_ave);

//计算笔画段长度均值、标准差、中位数
void ave(StrokesInfo* strokesinfo, double strokes_ave, double variance, double* Median);

//获取骨架笔画{有注释}
void craw_stroke(Mat& image, vector<Point>& se, vector<Point>& sf,
	vector<Point>& s, vector<Point>& sef, vector<Point>& newpoint_mark, vector<Point>& newpoint, vector<int>& dir);

//获取骨架笔画 11.27新增：使用正确的newpoint_mark纠正错误的newpoint
void craw_stroke_new(Mat& image, vector<Point>& se, vector<Point>& sf, vector<Point>& s1,
	vector<Point>& s, vector<Point>& sef, vector<Point>& newpoint_mark, vector<Point>& newpoint, vector<int>& dir, StrokesInfo* strokesinfo, double strokes_ave);

//绘制未合并笔画之前的彩图
Mat draw_picture(Mat& image, vector<Point>& s1, StrokesInfo* strokesinfo);

//更正1026：使用遍历数组strokesinfo，找到合并笔画  
//合并笔画1：combine_point_mark存储找到一组四个点，表示两个可以合并笔画（但是包含重复的）
void combine1(Mat& image, int NPB, int NSP, StrokesInfo* strokesinfo, vector<Point>& combine_point_mark);

//1026添加：在去重合并笔画combine_point_mark_new的基础上，存储合并笔画进strokesinfo_com结构体
//11.13添加：加入无需合并笔画
void combine2_save(StrokesInfo* strokesinfo_com, StrokesInfo* strokesinfo);

//02.28新增：“短桥”的合并
void duanqiao(Mat& image, Mat& image1, int NPB, int NSP, StrokesInfo* strokesinfo, double Median, vector<Point>& se, qiaoInfo* qiaoinfo, sfInfo* sfinfo,
    vector<Point>& edge_center, vector<Point>& edge);

//“钩”型笔画差分改进进化：
void gou1(vector<Point>& S_0, vector<Point>& S_1, vector<Point>& S_2);

//1.21修改：特殊笔画处理-“钩”型笔画：
void gou(Mat& image, Mat& image1, StrokesInfo* strokesinfo, vector<Point>& point_gou_mark, sfInfo* sfinfo, vector<Point>& se,
    int one_x, int two_x, int three_x, int four_x, int five_x, int six_x, int seven_x, int one_y, int two_y, int three_y, int four_y, int five_y,
    int six_y, int seven_y, double Median, vector<Point>& S_0, vector<Point>& S_1, vector<Point>& S_2, vector<Point>& s1, vector<Point>& point_bezier_3);

void A_Combine(Mat& image, int NPB, int NSP, StrokesInfo* strokesinfo_com, double Median, vector<Point>& se, vector<Point>& sf, sfInfo* sfinfo);

//绘制合并笔画之后的彩图
Mat draw_picture1(Mat& image, vector<Point>& s1, StrokesInfo* strokesinfo_com, vector<Point>& point_bezier_2,
    vector<Point>& point_bezier_3, vector<Point>& S_2, int NPB, int NSP, sfInfo* sfinfo, vector<Point>& edge_center, vector<Point>& edge);


