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

//����ṹ������洢�Ǽܱʻ�{��ʼ�㣬��ֹ�㣬8��������}
struct StrokesInfo {
    Point begin;
    Point end;
    int snake_length;//8�������г���
    vector<int> snake;//����һ����������
    vector<Point> tem;//����һ�����ص�����
    int dir;//�ʻ�����
    int num;//�洢�����ڳ�Ա����
    int com_mark;//�ϲ��ʻ����
    int com_mark_max;//���com_mark�����ֵ

};

struct sfInfo {//����ṹ������洢������
    Point begin; // ���������
    Point end;// �������յ�
    Point Pc;// ���������ĵ�
    vector<Point> sf_info;//����������
};

//����ṹ������洢���š��ʻ�
struct qiaoInfo {
    Point begin;
    Point end;
    int flag_sfinfo = 0;//�����㴦�ڽ����ص�λ��
    int flag_sfinfo1 = 0;//����յ㴦�ڽ����ص�λ��
    vector<int> snake;//����һ����������
    vector<Point> tem;//����һ�����ص�����
    int dir;//�ʻ�����
    vector<Point> flag_sfvec;//���š������������Ҫ�洢���š�������ڽ���ص����е�
    vector<Point> flag_sfvec1;//���š��յ���������Ҫ�洢���š��յ����ڽ���ص����е�

    vector<Point> begin_line_begin, begin_line_end;//���š�����������ӵ����бʻ���
    vector<Point> end_line_begin, end_line_end;//���š��յ��������ӵ����бʻ���
    vector<int> begin_line, end_line;//���š����յ����ӵıʻ����롰�š������ӷ�ʽ��0��ʾ�������������1��ʾ�յ���������
    int link;//�����ű��

};

//��ͷ�ļ�����������
int max(int x, int y); 

//zhangϸ���Ľ��㷨
void zhang_thinimage_improve(Mat& srcimage);

//��ͨ��ת��ͨ��
Mat channelSwitching(const Mat& src);

//�ҳ�3�����ص�
void search_point(Mat& image, vector<Point>& se, vector<Point>& sf, vector<Point>& s, vector<Point>& sef, sfInfo* sfinfo);

//���Ǽܱʻ��洢���ṹ������strokesinfo (1026���ӣ��ʻ�����Ϊ0�Ŀ�����Ҫ������ʼ��)
void Save_strokesinfo(int num, vector<Point>& newpoint_mark, vector<Point>& newpoint, StrokesInfo* strokesinfo, double strokes_ave);

//����ʻ��γ��Ⱦ�ֵ����׼���λ��
void ave(StrokesInfo* strokesinfo, double strokes_ave, double variance, double* Median);

//��ȡ�Ǽܱʻ�{��ע��}
void craw_stroke(Mat& image, vector<Point>& se, vector<Point>& sf,
	vector<Point>& s, vector<Point>& sef, vector<Point>& newpoint_mark, vector<Point>& newpoint, vector<int>& dir);

//��ȡ�Ǽܱʻ� 11.27������ʹ����ȷ��newpoint_mark���������newpoint
void craw_stroke_new(Mat& image, vector<Point>& se, vector<Point>& sf, vector<Point>& s1,
	vector<Point>& s, vector<Point>& sef, vector<Point>& newpoint_mark, vector<Point>& newpoint, vector<int>& dir, StrokesInfo* strokesinfo, double strokes_ave);

//����δ�ϲ��ʻ�֮ǰ�Ĳ�ͼ
Mat draw_picture(Mat& image, vector<Point>& s1, StrokesInfo* strokesinfo);

//����1026��ʹ�ñ�������strokesinfo���ҵ��ϲ��ʻ�  
//�ϲ��ʻ�1��combine_point_mark�洢�ҵ�һ���ĸ��㣬��ʾ�������Ժϲ��ʻ������ǰ����ظ��ģ�
void combine1(Mat& image, int NPB, int NSP, StrokesInfo* strokesinfo, vector<Point>& combine_point_mark);

//1026��ӣ���ȥ�غϲ��ʻ�combine_point_mark_new�Ļ����ϣ��洢�ϲ��ʻ���strokesinfo_com�ṹ��
//11.13��ӣ���������ϲ��ʻ�
void combine2_save(StrokesInfo* strokesinfo_com, StrokesInfo* strokesinfo);

//02.28�����������š��ĺϲ�
void duanqiao(Mat& image, Mat& image1, int NPB, int NSP, StrokesInfo* strokesinfo, double Median, vector<Point>& se, qiaoInfo* qiaoinfo, sfInfo* sfinfo,
    vector<Point>& edge_center, vector<Point>& edge);

//�������ͱʻ���ָĽ�������
void gou1(vector<Point>& S_0, vector<Point>& S_1, vector<Point>& S_2);

//1.21�޸ģ�����ʻ�����-�������ͱʻ���
void gou(Mat& image, Mat& image1, StrokesInfo* strokesinfo, vector<Point>& point_gou_mark, sfInfo* sfinfo, vector<Point>& se,
    int one_x, int two_x, int three_x, int four_x, int five_x, int six_x, int seven_x, int one_y, int two_y, int three_y, int four_y, int five_y,
    int six_y, int seven_y, double Median, vector<Point>& S_0, vector<Point>& S_1, vector<Point>& S_2, vector<Point>& s1, vector<Point>& point_bezier_3);

void A_Combine(Mat& image, int NPB, int NSP, StrokesInfo* strokesinfo_com, double Median, vector<Point>& se, vector<Point>& sf, sfInfo* sfinfo);

//���ƺϲ��ʻ�֮��Ĳ�ͼ
Mat draw_picture1(Mat& image, vector<Point>& s1, StrokesInfo* strokesinfo_com, vector<Point>& point_bezier_2,
    vector<Point>& point_bezier_3, vector<Point>& S_2, int NPB, int NSP, sfInfo* sfinfo, vector<Point>& edge_center, vector<Point>& edge);


