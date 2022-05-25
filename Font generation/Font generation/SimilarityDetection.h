#pragma once
#include <opencv2/opencv.hpp>
#include<stdexcept>
#include <opencv2/core/core.hpp>
#include <vector>
#include <winsock.h>
#include <stdio.h>
#include "mysql.h"
#include<iostream>
#include <opencv2/ximgproc.hpp>  
#include <math.h>
#include "jisuan.h"
#include "thinimage.h"
#include "mysqlconnect.h"
#include "tietu.h"
#include<algorithm>
#include <cmath>
using namespace std;
using namespace cv;


class SimilarityDetection
{
	
public:
	  //����
	Mat xihuamat;
	double zhongxin_x(Mat  src) {
		int width = src.cols;
		int height = src.rows;


		//��ȡһ�׼��ξغ���׼��ξ�
		double m10 = 0;
		double m01 = 0;
		double m00 = 0;

		for (int row = 0; row < height; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = 0; col < width; col++) {
				uchar q1 = q[col];
				m10 += pow(col, 1) * pow(row, 0) * (255 - q1);
				m01 += pow(col, 0) * pow(row, 1) * (255 - q1);
				m00 += pow(col, 0) * pow(row, 0) * (255 - q1);
			}

		}
		//������������
		//cout << m00 << endl;
		//cout << m10 << endl;
		//cout << m01 << endl;
		double x0 = m10 / m00;
		double y0 = m01 / m00;
		//cout << "x0--" << x0 << endl;
		//cout << "y0--" << y0 << endl;
		return x0;



	}
	double zhongxin_y(Mat  src) {
		int width = src.cols;
		int height = src.rows;


		//��ȡһ�׼��ξغ���׼��ξ�
		double m10 = 0;
		double m01 = 0;
		double m00 = 0;

		for (int row = 0; row < height; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = 0; col < width; col++) {
				uchar q1 = q[col];
				m10 += pow(col, 1) * pow(row, 0) * (255 - q1);
				m01 += pow(col, 0) * pow(row, 1) * (255 - q1);
				m00 += pow(col, 0) * pow(row, 0) * (255 - q1);
			}

		}
		//������������
		//cout << m00 << endl;
		//cout << m10 << endl;
		//cout << m01 << endl;
		double x0 = m10 / m00;
		double y0 = m01 / m00;
		//cout << "x0--" << x0 << endl;
		//cout << "y0--" << y0 << endl;
		return y0;

	}
	//����
	double hangqi(double zhongxin_x,double zxstandard) {
		return abs(zhongxin_x - zxstandard);
	     
	}


	//ƽ���ʿ�
	double StrokeWidth(Mat  src)
	{
		threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);
		Mat dst;
		double NPB = 0;//��ֵ�����ɫ����
		double NSP = 0;//�Ǽܵ���
		//imshow("test", test2);
		//printf("ͨ����%d\n", src.channels());
		int width = src.cols;
		int height = src.rows;

		for (int i = 0; i < height; ++i) {
			uchar * q = src.ptr<uchar>(i);
			for (int j = 0; j < width; ++j) {
				uchar q1 = q[j];
				if (q1 == 1) {

					NPB++;
				}


			}



		}
		printf("��ֵ����ĺ�ɫ��Ŀ%lf\n", NPB);



		/*for (int i = 0; i < gujia2_x.size(); i++) {
			test.at<uchar>(gujia2_y[i], gujia2_x[i]) =1;

		}*/

		src.copyTo(dst);
		vector<uchar *> mFlag; //���ڱ����Ҫɾ���ĵ�    
		while (true)
		{
			//����һ   
			for (int i = 0; i < height; ++i)
			{
				uchar * p = dst.ptr<uchar>(i);
				for (int j = 0; j < width; ++j)
				{
					//��þŸ������ע��߽�����
					uchar p1 = p[j];
					if (p1 != 1) continue;
					uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
					uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
					uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
					uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
					uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
					uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
					uchar p8 = (j == 0) ? 0 : *(p + j - 1);
					uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
					if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)//����1�ж�
					{
						//����2����
						int ap = 0;
						if (p2 == 0 && p3 == 1) ++ap;
						if (p3 == 0 && p4 == 1) ++ap;
						if (p4 == 0 && p5 == 1) ++ap;
						if (p5 == 0 && p6 == 1) ++ap;
						if (p6 == 0 && p7 == 1) ++ap;
						if (p7 == 0 && p8 == 1) ++ap;
						if (p8 == 0 && p9 == 1) ++ap;
						if (p9 == 0 && p2 == 1) ++ap;
						//����2��3��4�ж�
						int bp = 0;
						bp += p2;
						bp += p3 << 1;
						bp += p4 << 2;
						bp += p5 << 3;
						bp += p6 << 4;
						bp += p7 << 5;
						bp += p8 << 6;
						bp += p9 << 7;

						if (ap == 1 || bp == 65 || bp == 5 || bp == 20 || bp == 80 || bp == 13 || bp == 22 || bp == 52 || bp == 133 || bp == 141 || bp == 54) {



							if (p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)
							{
								mFlag.push_back(p + j);
							}
						}

					}
				}
			}
			//����ǵĵ�ɾ��    
			for (vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
			{
				**i = 0;
			}
			//ֱ��û�е����㣬�㷨����    
			if (mFlag.empty())
			{
				break;
			}
			else
			{
				mFlag.clear();//��mFlag���    
			}

			//���������������ò�����ԺͲ���һ��װ��һ���Ϊһ������
			for (int i = 0; i < height; ++i)
			{
				uchar * p = dst.ptr<uchar>(i);
				for (int j = 0; j < width; ++j)
				{
					//��������ĸ����������б��    
					//  p9 p2 p3    
					//  p8 p1 p4    
					//  p7 p6 p5    
					uchar p1 = p[j];
					if (p1 != 1) continue;
					uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
					uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
					uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
					uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
					uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
					uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
					uchar p8 = (j == 0) ? 0 : *(p + j - 1);
					uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
					if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
					{
						int ap = 0;
						if (p2 == 0 && p3 == 1) ++ap;
						if (p3 == 0 && p4 == 1) ++ap;
						if (p4 == 0 && p5 == 1) ++ap;
						if (p5 == 0 && p6 == 1) ++ap;
						if (p6 == 0 && p7 == 1) ++ap;
						if (p7 == 0 && p8 == 1) ++ap;
						if (p8 == 0 && p9 == 1) ++ap;
						if (p9 == 0 && p2 == 1) ++ap;
						if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)
						{
							//���    
							mFlag.push_back(p + j);
						}
					}
				}
			}
			//����ǵĵ�ɾ��    
			for (vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
			{
				//printf("%d",**i);
				**i = 0;
			}
			//ֱ��û�е����㣬�㷨����    
			if (mFlag.empty())
			{
				break;
			}
			else
			{
				mFlag.clear();//��mFlag���    
			}
		}
		dst = dst * 255;
		bitwise_not(dst, dst);
		dst.copyTo(xihuamat);
		imwrite("D:/����֮�ֿ�/xihua.jpg", dst);
		for (int i = 0; i < height; ++i) {
			uchar * q = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j) {
				uchar q1 = q[j];
				if (q1 == 1) {

					NSP++;
				}


			}



		}
		
		printf("ϸ����ĹǼ���Ŀ%lf\n", NSP);
		double StrokeWidth = NPB / NSP;
		return  StrokeWidth;

	}
	//�����
	double StrokeAspectRatio(Mat src) {
		threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);
		int width = src.cols;
		int height = src.rows;
		int minx = 500;
		int miny = 500;
		int maxx = 0;
		int maxy = 0;

		for (int i = 0; i < height; ++i) {
			uchar * q = src.ptr<uchar>(i);
			for (int j = 0; j < width; ++j) {
				uchar q1 = q[j];
				if (q1 == 1) {
					if (i < minx) {
						minx = i;
					}
					if (j < miny) {
						miny = j;
					}
					if (i > maxx) {
						maxx = i;
					}
					if (j > maxy) {
						maxy = j;
					}


				}


			}



		}
		double StrokeWidth = maxx - minx;
		double StrokeLength = maxy - miny;
		printf("�ʻ��߶�%f\n", StrokeWidth);
		printf("�ʻ����%f\n", StrokeLength);
		double strokeAspectRatio = StrokeLength / StrokeWidth;
		return strokeAspectRatio;



	}
	vector<int>jiaochadian_x;
	vector<int>jiaochadian_4x;
	vector<int>jiaochadian_y;
	vector<int>jiaochadian_4y;
	vector<int>guiji_x;
	vector<int>guiji_y;
	vector<int>gujia2_x;
	vector<int>gujia2_y;
	vector<int>jiaochadianfujin_x;
	vector<int>jiaochadianfujin_y;
	vector<int>duandian_x;
	vector<int>duandian_y;
	vector<int>jieshudian_x;
	vector<int>jieshudian_y;
	vector<int>guiji;
	void zuobiao(Mat & src, uchar *p, uchar *m, int i, int j) {

		int width = src.cols;//��
		int height = src.rows;//��
		uchar p1 = *p;
		uchar p2 = (i <= 0) ? 0 : *(p - src.step);
		uchar p3 = (i <= 0 || j >= width - 1) ? 0 : *(p - src.step + 1);
		uchar p4 = (j >= width - 1) ? 0 : *(p + 1);
		uchar p5 = (i >= height - 1 || j >= width - 1) ? 0 : *(p + src.step + 1);
		uchar p6 = (i >= height - 1) ? 0 : *(p + src.step);
		uchar p7 = (i >= height - 1 || j <= 0) ? 0 : *(p + src.step - 1);
		uchar p8 = (j <= 0) ? 0 : *(p - 1);
		uchar p9 = (i <= 0 || j <= 0) ? 0 : *(p - src.step - 1);
		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 2) {

			if (p2 == 1 && (p - src.step) != m) {
				printf("2");
				guiji_y.push_back(i);
				guiji_x.push_back(j);
				guiji.push_back(2);

				zuobiao(src, (p - src.step), p, i - 1, j);

			}
			if (p3 == 1 && (p - src.step + 1) != m) {
				printf("1");
				guiji_y.push_back(i);
				guiji_x.push_back(j);
				guiji.push_back(1);

				zuobiao(src, (p - src.step + 1), p, i - 1, j + 1);

			}

			if (p4 == 1 && (p + 1) != m) {
				printf("0");
				guiji_y.push_back(i);
				guiji_x.push_back(j);
				guiji.push_back(0);

				zuobiao(src, (p + 1), p, i, j + 1);
			}

			if (p5 == 1 && (p + src.step + 1) != m) {
				printf("7");
				guiji_y.push_back(i);
				guiji_x.push_back(j);
				guiji.push_back(7);

				zuobiao(src, (p + src.step + 1), p, i + 1, j + 1);

			}

			if (p6 == 1 && (p + src.step) != m) {
				printf("6");
				guiji_y.push_back(i);
				guiji_x.push_back(j);
				guiji.push_back(6);

				zuobiao(src, (p + src.step), p, i + 1, j);

			}

			if (p7 == 1 && (p + src.step - 1) != m) {
				printf("5");
				guiji_y.push_back(i);
				guiji_x.push_back(j);
				guiji.push_back(5);

				zuobiao(src, (p + src.step - 1), p, i + 1, j - 1);

			}

			if (p8 == 1 && (p - 1) != m) {
				printf("4");
				guiji_y.push_back(i);
				guiji_x.push_back(j);
				guiji.push_back(4);

				zuobiao(src, (p - 1), p, i, j - 1);

			}

			if (p9 == 1 && (p - src.step - 1) != m) {
				printf("3");
				guiji_y.push_back(i);
				guiji_x.push_back(j);
				guiji.push_back(3);

				zuobiao(src, (p - src.step - 1), p, i - 1, j - 1);

			}




		}
		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 1) {
			printf("9  ");
			printf("�����㣺(%d,%d)\n", j, i);
			guiji.push_back(9);
			guiji_y.push_back(i);
			guiji_x.push_back(j);
			jieshudian_x.push_back(j);
			jieshudian_y.push_back(i);


		}
		int biaoji = 0;
		for (int m = 0; m < jiaochadian_x.size(); m++) {

			if (jiaochadian_x[m] == j && jiaochadian_y[m] == i) {

				biaoji = 1;


			}

		}

		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 3 && biaoji == 1) {
			printf("9  ");
			printf("�����㣺(%d,%d)\n", j, i);
			guiji.push_back(9);
			guiji_y.push_back(i);
			guiji_x.push_back(j);
			jieshudian_x.push_back(j);
			jieshudian_y.push_back(i);


		}



		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 2 && biaoji != 1) {

			if (p2 == 1 && p - src.step != m) {
				printf("2");
				guiji.push_back(2);
				guiji_y.push_back(i);
				guiji_x.push_back(j);
				zuobiao(src, (p - src.step), p, i - 1, j);
			}
			if (p4 == 1 && p + 1 != m) {
				printf("0");
				guiji.push_back(0);
				guiji_y.push_back(i);
				guiji_x.push_back(j);


				zuobiao(src, (p + 1), p, i, j + 1);
			}
			if (p6 == 1 && p + src.step != m) {
				printf("6");
				guiji.push_back(6);
				guiji_y.push_back(i);
				guiji_x.push_back(j);

				zuobiao(src, (p + src.step), p, i + 1, j);

			}
			if (p8 == 1 && (p - 1) != m) {
				printf("4");
				guiji.push_back(4);
				guiji_y.push_back(i);
				guiji_x.push_back(j);

				zuobiao(src, (p - 1), p, i, j - 1);

			}


		}


	}
	//�ʻ��켣
	void bihuaguiji(Mat &src) {
		double zero = 1;
		double one = 1;
		double two = 1;
		double three = 1;
		double four = 1;
		double five = 1;
		double six = 1;
		double seven = 1;
		
     
		threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);//��ֵ����ǰ��Ϊ1������Ϊ0
		int dijibi = 1;
		int width = src.cols;//��
		int height = src.rows;//��

		for (int i = 0; i < height; ++i)
		{
			uchar * p = src.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				
				//��þŸ������ע��߽�����
				uchar p1 = p[j];
				if (p1 != 1) continue;
				uchar p2 = (i == 0) ? 0 : *(p - src.step + j);
				uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - src.step + j + 1);
				uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
				uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + src.step + j + 1);
				uchar p6 = (i == height - 1) ? 0 : *(p + src.step + j);
				uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + src.step + j - 1);
				uchar p8 = (j == 0) ? 0 : *(p + j - 1);
				uchar p9 = (i == 0 || j == 0) ? 0 : *(p - src.step + j - 1);
				int chongfu = 0;
				for (int k = 0; k < jieshudian_x.size(); k++) {
					if (jieshudian_x[k] == j && jieshudian_y[k] == i) {
						chongfu = 1;
					}

				}
				
				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 1) {
					if (p2 == 1 && chongfu == 0) {
						printf("��%d�ʡ�������", dijibi);
						dijibi++;
						printf("�˵㣺(%d , %d)", j, i);
						printf("�켣��");
						guiji.push_back(2);
						printf("2");
						guiji_y.push_back(i);
						guiji_x.push_back(j);
						duandian_x.push_back(j);
						duandian_y.push_back(i);
						zuobiao(src, (p - src.step + j), p + j, i - 1, j);

					}
					if (p3 == 1 && chongfu == 0) {
						printf("��%d�ʡ�������", dijibi);
						dijibi++;
						printf("�˵㣺(%d , %d)", j, i);
						printf("�켣��");
						guiji.push_back(1);
						printf("1");
						guiji_y.push_back(i);
						guiji_x.push_back(j);
						duandian_x.push_back(j);
						duandian_y.push_back(i);
						zuobiao(src, (p - src.step + j + 1), p + j, i - 1, j + 1);

					}

					if (p4 == 1 && chongfu == 0) {
						printf("��%d�ʡ�������", dijibi);
						dijibi++;
						printf("�˵㣺(%d , %d)", j, i);
						printf("�켣��");
						guiji.push_back(0);
						printf("0");
						guiji_y.push_back(i);
						guiji_x.push_back(j);
						duandian_x.push_back(j);
						duandian_y.push_back(i);
						zuobiao(src, (p + j + 1), p + j, i, j + 1);
					}

					if (p5 == 1 && chongfu == 0) {
						printf("��%d�ʡ�������", dijibi);
						dijibi++;
						printf("�˵㣺(%d , %d)", j, i);
						printf("�켣��");
						guiji.push_back(7);
						printf("7");
						guiji_y.push_back(i);
						guiji_x.push_back(j);
						duandian_x.push_back(j);
						duandian_y.push_back(i);
						zuobiao(src, (p + src.step + j + 1), p + j, i + 1, j + 1);

					}

					if (p6 == 1 && chongfu == 0) {
						printf("��%d�ʡ�������", dijibi);
						dijibi++;
						printf("�˵㣺(%d , %d)", j, i);
						printf("�켣��");
						guiji.push_back(6);
						printf("6");
						guiji_y.push_back(i);
						guiji_x.push_back(j);
						duandian_x.push_back(j);
						duandian_y.push_back(i);
						zuobiao(src, (p + src.step + j), p + j, i + 1, j);

					}

					if (p7 == 1 && chongfu == 0) {
						printf("��%d�ʡ�������", dijibi);
						dijibi++;
						printf("�˵㣺(%d , %d)", j, i);
						printf("�켣��");
						guiji.push_back(5);
						printf("5");
						guiji_y.push_back(i);
						guiji_x.push_back(j);
						duandian_x.push_back(j);
						duandian_y.push_back(i);
						zuobiao(src, (p + src.step + j - 1), p + j, i + 1, j - 1);

					}

					if (p8 == 1 && chongfu == 0) {
						printf("��%d�ʡ�������", dijibi);
						dijibi++;
						printf("�˵㣺(%d , %d)", j, i);
						printf("�켣��");
						guiji.push_back(4);
						printf("4");
						guiji_y.push_back(i);
						guiji_x.push_back(j);
						duandian_x.push_back(j);
						duandian_y.push_back(i);
						zuobiao(src, (p + j - 1), p + j, i, j - 1);

					}

					if (p9 == 1 && chongfu == 0) {
						printf("��%d�ʡ�������", dijibi);
						dijibi++;
						printf("�˵㣺(%d , %d)", j, i);
						printf("�켣��");
						guiji.push_back(3);
						printf("3");
						guiji_y.push_back(i);
						guiji_x.push_back(j);
						duandian_x.push_back(j);
						duandian_y.push_back(i);
						zuobiao(src, (p - src.step + j - 1), p + j, i - 1, j - 1);

					}






				}



			}
		}
		//�ʻ��켣ͳ��
		for (int i = 0; i < guiji.size();i++) {
			if (guiji[i]==0) {
				zero++;
			}
			if (guiji[i] == 1) {
				one++;
			}
			if (guiji[i] == 2) {
				two++;
			}
			if (guiji[i] == 3) {
				three++;
			}
			if (guiji[i] == 4) {
				four++;
			}
			if (guiji[i] == 5) {
				five++;
			}
			if (guiji[i] == 6) {
				six++;
			}
			if (guiji[i] == 7) {
				seven++;
			}
			
		}

		
          

		//ͳ�Ʊʻ���ʾ
		cout << "�켣0-" << zero << endl;
		cout << "�켣1-" << one << endl;
		cout << "�켣2-" << two << endl;
		cout << "�켣3-" << three << endl;
		cout << "�켣4-" << four << endl;
		cout << "�켣5-" << five << endl;
		cout << "�켣6-" << six << endl;
		cout << "�켣7-" << seven << endl;
		
		//����ʻ���sd
		double sd0 = zero / guiji.size();
		double sd1 = one / guiji.size();
		double sd2 = two / guiji.size();
		double sd3 = three / guiji.size();
		double sd4 = four / guiji.size();
		double sd5 = five / guiji.size();
		double sd6 = six / guiji.size();
		double sd7 = seven / guiji.size();
		
		//��ʾ�ʻ���sd
		cout << "�ܱʻ���" << guiji.size() << endl;
		cout << "sd0-" << sd0 << endl;
		cout << "sd1-" << sd1 << endl;
		cout << "sd2-" << sd2 << endl;
		cout << "sd3-" << sd3 << endl;
		cout << "sd4-" << sd4 << endl;
		cout << "sd5-" << sd5 << endl;
		cout << "sd6-" << sd6 << endl;
		cout << "sd7-" << sd7 << endl;

		//����ʻ���
		double Es = -(sd0 * log(sd0) + sd1 * log(sd1) + sd2 * log(sd2) + sd3 * log(sd3) + sd4 * log(sd4) + sd5 * log(sd5) +
			sd6 * log(sd6) + sd7 * log(sd7));
		double Es1 = -(sd0 * log(sd0));
		cout << "�ʻ���" << Es1;
		//�����ʻ���б��
		double start_x = guiji_x[0];
		double start_y = guiji_y[0];
		double end_x = guiji_x[guiji_x.size()-1];
		double end_y = guiji_y[guiji_y.size()-1];
		cout << "start_x-" << start_x << endl;
		cout << "start_y-" << start_y << endl;
		cout << "end_x-" << end_x << endl;
		cout << "end_y-" << end_y << endl;
		double xielv_k = (end_y - start_y) / (end_x - start_x);
		cout << "б��-" << xielv_k << endl;
		//����ʻ��ʼ���֮һб��
		double start_1_5x = guiji_x[guiji_x.size() / 5];
		double start_1_5y = guiji_y[guiji_y.size() / 5];
		double xielv_start = (start_1_5y - start_y) / (start_1_5x - start_x);
		cout << "�ʼ���֮һб��-" << xielv_start << endl;

		//����ʻ��������֮һб��
		double end_1_5x = guiji_x[guiji_x.size() / 5*4];
		double end_1_5y = guiji_y[guiji_y.size() / 5*4];
		double xielv_end = (end_y - end_1_5y) / (end_x - end_1_5x);
		cout << "�������֮һб��-" << xielv_end << endl;

		
		
	
	}
	void thicknesschange(Mat src,vector<double> &change ) {
		Mat copy;
		src.copyTo(copy);
		threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);
		Mat dst;
		double NPB = 0;//��ֵ�����ɫ����
		double NSP = 0;//�Ǽܵ���
		//imshow("test", test2);
		//printf("ͨ����%d\n", src.channels());
		int width = src.cols;
		int height = src.rows;

		for (int i = 0; i < height; ++i) {
			uchar * q = src.ptr<uchar>(i);
			for (int j = 0; j < width; ++j) {
				uchar q1 = q[j];
				if (q1 == 1) {

					NPB++;
				}


			}



		}
		//printf("��ֵ����ĺ�ɫ��Ŀ%lf\n", NPB);



		/*for (int i = 0; i < gujia2_x.size(); i++) {
			test.at<uchar>(gujia2_y[i], gujia2_x[i]) =1;

		}*/

		src.copyTo(dst);
		vector<uchar *> mFlag; //���ڱ����Ҫɾ���ĵ�    
		while (true)
		{
			//����һ   
			for (int i = 0; i < height; ++i)
			{
				uchar * p = dst.ptr<uchar>(i);
				for (int j = 0; j < width; ++j)
				{
					//��þŸ������ע��߽�����
					uchar p1 = p[j];
					if (p1 != 1) continue;
					uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
					uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
					uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
					uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
					uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
					uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
					uchar p8 = (j == 0) ? 0 : *(p + j - 1);
					uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
					if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)//����1�ж�
					{
						//����2����
						int ap = 0;
						if (p2 == 0 && p3 == 1) ++ap;
						if (p3 == 0 && p4 == 1) ++ap;
						if (p4 == 0 && p5 == 1) ++ap;
						if (p5 == 0 && p6 == 1) ++ap;
						if (p6 == 0 && p7 == 1) ++ap;
						if (p7 == 0 && p8 == 1) ++ap;
						if (p8 == 0 && p9 == 1) ++ap;
						if (p9 == 0 && p2 == 1) ++ap;
						//����2��3��4�ж�
						int bp = 0;
						bp += p2;
						bp += p3 << 1;
						bp += p4 << 2;
						bp += p5 << 3;
						bp += p6 << 4;
						bp += p7 << 5;
						bp += p8 << 6;
						bp += p9 << 7;

						if (ap == 1 || bp == 65 || bp == 5 || bp == 20 || bp == 80 || bp == 13 || bp == 22 || bp == 52 || bp == 133 || bp == 141 || bp == 54) {



							if (p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)
							{
								mFlag.push_back(p + j);
							}
						}

					}
				}
			}
			//����ǵĵ�ɾ��    
			for (vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
			{
				**i = 0;
			}
			//ֱ��û�е����㣬�㷨����    
			if (mFlag.empty())
			{
				break;
			}
			else
			{
				mFlag.clear();//��mFlag���    
			}

			//���������������ò�����ԺͲ���һ��װ��һ���Ϊһ������
			for (int i = 0; i < height; ++i)
			{
				uchar * p = dst.ptr<uchar>(i);
				for (int j = 0; j < width; ++j)
				{
					//��������ĸ����������б��    
					//  p9 p2 p3    
					//  p8 p1 p4    
					//  p7 p6 p5    
					uchar p1 = p[j];
					if (p1 != 1) continue;
					uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
					uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
					uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
					uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
					uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
					uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
					uchar p8 = (j == 0) ? 0 : *(p + j - 1);
					uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
					if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
					{
						int ap = 0;
						if (p2 == 0 && p3 == 1) ++ap;
						if (p3 == 0 && p4 == 1) ++ap;
						if (p4 == 0 && p5 == 1) ++ap;
						if (p5 == 0 && p6 == 1) ++ap;
						if (p6 == 0 && p7 == 1) ++ap;
						if (p7 == 0 && p8 == 1) ++ap;
						if (p8 == 0 && p9 == 1) ++ap;
						if (p9 == 0 && p2 == 1) ++ap;
						if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)
						{
							//���    
							mFlag.push_back(p + j);
						}
					}
				}
			}
			//����ǵĵ�ɾ��    
			for (vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
			{
				//printf("%d",**i);
				**i = 0;
			}
			//ֱ��û�е����㣬�㷨����    
			if (mFlag.empty())
			{
				break;
			}
			else
			{
				mFlag.clear();//��mFlag���    
			}
		}

		Mat a;
		dst.copyTo(a);
		dst = dst * 255;
		bitwise_not(dst, dst);
		dst.copyTo(xihuamat);
		//imwrite("D:/����֮�ֿ�/xihua.jpg", dst);
		//imshow("aaa", dst);
		//waitKey(0);
		/*imshow("aaa", src);
		waitKey(0);*/
		vector<int>xihuaguiji_x;
		vector<int>xihuaguiji_y;
		vector<double> cudu;
		//cout << "aaaa";
		for (int i = 0; i < height; ++i) {
			
			uchar * q = a.ptr<uchar>(i);
			for (int j = 0; j < width; ++j) {
				uchar q1 = q[j];
				if (q1 == 1) {
					xihuaguiji_x.push_back(j);
					xihuaguiji_y.push_back(i);
				//cout << "aaaa";
					
				}


			}



		}

		for (int i = 0; i < xihuaguiji_x.size();i++) {
			//cout << "aaaa";
			int radius = 1;
			double threshold = 1;
			while(threshold>=0.95) {
				double black = 0;
				double all = 0;
				int start_x = xihuaguiji_x[i]-radius;
				int end_x = xihuaguiji_x[i] + radius;
				int start_y = xihuaguiji_y[i] - radius;
				int end_y = xihuaguiji_y[i] + radius;
				if (start_x<=0) {
					start_x = 0;
				
				}
				if (end_x>=width) {
					end_x = width;
				}
				if (start_y <= 0) {
					start_y=0;
				}
				if (end_y >= height) {
					end_y = height;
				}
				for (int m = start_y; m < end_y;m++) {
					uchar * q = src.ptr<uchar>(m);
					for (int n = start_x; n < end_x;n++) {
						uchar q1 = q[n];
						if (((n-xihuaguiji_x[i])*(n - xihuaguiji_x[i])+(m-xihuaguiji_y[i])*(m - xihuaguiji_y[i]))<=radius*radius) {
							all++;
							if(q1==1) {
								black++;
							}
						
						}
					
					}
				
				
				}
				threshold = black / all;
				radius++;
			
			}

			cudu.push_back(radius);
		
		}
		//չʾ�ֶ�
		cout << "�ֶ�-";
		for (int i = 0; i < cudu.size(); i++) {
			cout << cudu[i] << ",";

		}
		cout << endl;
		sort(cudu.begin(), cudu.end());
		
		cout << endl;
		

		//����ƽ���ʻ�/*
		
		double cuduall = 0;
		for (int i = 0; i < cudu.size(); i++) {
			cuduall = cuduall + cudu[i];

		}
		double cuduavg = cuduall/cudu.size();
		//cout << "ƽ���ֶ�" << cuduavg << endl;
		//�ʻ���ȷ���
		double cudufangchaall=0;
		for (int i = 0; i < cudu.size(); i++) {
			cudufangchaall = cudufangchaall + (cudu[i] - cuduavg)*(cudu[i] - cuduavg);

		}
		//cout << "cuduall:" << cudufangchaall << endl;
		//cout << "geshu:" << cudu.size() << endl;
		double cudufangcha = cudufangchaall / cudu.size();
		//cout << "�ֶȷ���:" <<cudufangcha << endl;
		change.push_back(cuduavg);
		change.push_back(cudufangcha);
		//����ǰ���֮һ�ֶ�
		double preall = 0;
		cout << "ǰ���֮һ��ȣ�" << endl;
		for (int i = 0; i < cudu.size() / 5; i++) {
			cout << cudu[i];
			preall += cudu[i];

		}
		change.push_back(preall / (cudu.size() / 5));
		//��������֮һ�ֶ�
		cout << "�����֮һ��ȣ�" << endl;
		double afterall = 0;
		for (int i = cudu.size() / 5*4; i < cudu.size(); i++) {
			cout << cudu[i];
			afterall += cudu[i];

		}
		change.push_back(afterall / (cudu.size() / 5));

		
		
	
	
	}
	void Centralmoments(Mat & src,vector<double> & cenmoms) {

		//threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);
		int width = src.cols;
		int height = src.rows;


		//��ȡһ�׼��ξغ���׼��ξ�
		double m10 = 0;
		double m01 = 0;
		double m00 = 0;

		for (int row = 0; row < height; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = 0; col < width; col++) {
				uchar q1 = q[col];
				m10 += pow(col, 1) * pow(row, 0) * (255 - q1);
				m01 += pow(col, 0) * pow(row, 1) * (255 - q1);
				m00 += pow(col, 0) * pow(row, 0) * (255 - q1);
			}

		}
		//������������
		//cout << m00 << endl;
		//cout << m10 << endl;
		//cout << m01 << endl;
		double x0 = m10 / m00;
		double y0 = m01 / m00;
		cenmoms.push_back(x0);
		cenmoms.push_back(y0);
		
		//cout << "x0--" << x0 << endl;
		//cout << "y0--" << y0 << endl;
		//���� X ��ѹ���仯���� fstress_x
		long double xm30zheng=0;
		long double xm30fu=0;
		for (int row = 0; row < height; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = 0; col < width/2; col++) {
				uchar q1 = q[col];
				xm30zheng += pow((col - x0), 3) * pow((row - y0), 0) * (255 - q1);
			}

		}
		for (int row = 0; row < height; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = width / 2; col < width; col++) {
				uchar q1 = q[col];
				xm30fu += pow((col - x0), 3) * pow((row - y0), 0) * (255 - q1);
			}

		}
		//cout << xm30zheng + xm30fu << endl;
		long double fstress_x = xm30zheng/(xm30zheng + xm30fu);
		//cout << "xm30zheng:" << xm30zheng << endl;
		//cout << "xm30fu:" << xm30fu << endl;
		//cout << "fstress_x:" << fstress_x << endl;
		cenmoms.push_back(fstress_x);
		//���� Y ��ѹ���仯���� fstress_y
		double ym03zheng = 0;
		double ym03fu = 0;
		for (int row = 0; row < height/2; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = 0; col < width; col++) {
				uchar q1 = q[col];
				ym03zheng += pow((col - x0), 0) * pow((row - y0), 3) * (255 - q1);
			}


		}
		for (int row = height/2; row < height; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = 0; col < width; col++) {
				uchar q1 = q[col];
				ym03fu += pow((col - x0), 0) * pow((row - y0), 3) * (255 - q1);
			}


		}
		//double fstress_y = ym03zheng / (ym03zheng + ym03fu);
		double fstress_y = ym03zheng / (ym03zheng + ym03fu);
		//cout << "ym03zheng:" << ym03zheng << endl;
		//cout << "ym03fu:" << ym03fu << endl;
		//cout << "fstress_y:" << fstress_y << endl;
		cenmoms.push_back(fstress_y);
		//���� X ����бƽ�� fslant_x
		double xm21zheng = 0;
		double xm21fu = 0;
		double m21=0;
		for (int row = 0; row < height; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = 0; col < width/2; col++) {
				uchar q1 = q[col];
				xm21zheng += pow((col - x0), 2) * pow((row - y0), 1) * (255 - q1);
			}


		}
		for (int row = 0; row < height; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = width/2; col < width; col++) {
				uchar q1 = q[col];
				xm21fu += pow((col - x0), 2) * pow((row - y0), 1) * (255 - q1);
			}


		}
		
		double fslant_x = xm21zheng / (xm21zheng + xm21fu);
		//cout << "xm21zheng:" << xm21zheng << endl;
		//cout << "xm21fu:" << xm21fu << endl;
		
		//cout << "fslant_x:" << fslant_x << endl;
		cenmoms.push_back(fslant_x);
		//���� Y ����бƽ�� fslant_y
		
		double ym12zheng = 0;
		double ym12fu = 0;
		

		for (int row = 0; row < height/2; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = 0; col < width ; col++) {
				uchar q1 = q[col];
				ym12zheng += pow((col - x0), 1) * pow((row - y0), 2) * (255 - q1);
			}


		}
		for (int row = height/2; row < height ; row++) {

			uchar * q = src.ptr<uchar>(row);
			for (int col = 0; col < width; col++) {
				uchar q1 = q[col];
				ym12fu += pow((col - x0), 1) * pow((row - y0), 2) * (255 - q1);
			}


		}
		double fslant_y = ym12zheng / (ym12zheng + ym12fu);
		//cout << "ym12zheng:" << ym12zheng << endl;
		//cout << "ym12fu:" << ym12fu << endl;

		//cout << "fslant_y:" << fslant_y << endl;
		cenmoms.push_back(fslant_y);
	
	}
	
	
	

	
};