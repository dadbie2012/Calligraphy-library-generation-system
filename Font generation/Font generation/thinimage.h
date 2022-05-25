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
using namespace std;
using namespace cv;
class thinimage
{
public:
	double StrokeWidth(Mat & src, Mat & dst)
	{
		double NPB = 0;//二值化后黑色点数
		double NSP = 0;//骨架点数
		//imshow("test", test2);
		//printf("通单数%d\n", src.channels());
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
		//printf("二值化后的黑色数目%lf", NPB);



		/*for (int i = 0; i < gujia2_x.size(); i++) {
			test.at<uchar>(gujia2_y[i], gujia2_x[i]) =1;

		}*/

		src.copyTo(dst);
		vector<uchar *> mFlag; //用于标记需要删除的点    
		while (true)
		{
			//步骤一   
			for (int i = 0; i < height; ++i)
			{
				uchar * p = dst.ptr<uchar>(i);
				for (int j = 0; j < width; ++j)
				{
					//获得九个点对象，注意边界问题
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
					if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)//条件1判断
					{
						//条件2计算
						int ap = 0;
						if (p2 == 0 && p3 == 1) ++ap;
						if (p3 == 0 && p4 == 1) ++ap;
						if (p4 == 0 && p5 == 1) ++ap;
						if (p5 == 0 && p6 == 1) ++ap;
						if (p6 == 0 && p7 == 1) ++ap;
						if (p7 == 0 && p8 == 1) ++ap;
						if (p8 == 0 && p9 == 1) ++ap;
						if (p9 == 0 && p2 == 1) ++ap;
						//条件2、3、4判断
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
			//将标记的点删除    
			for (vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
			{
				**i = 0;
			}
			//直到没有点满足，算法结束    
			if (mFlag.empty())
			{
				break;
			}
			else
			{
				mFlag.clear();//将mFlag清空    
			}

			//步骤二，根据情况该步骤可以和步骤一封装在一起成为一个函数
			for (int i = 0; i < height; ++i)
			{
				uchar * p = dst.ptr<uchar>(i);
				for (int j = 0; j < width; ++j)
				{
					//如果满足四个条件，进行标记    
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
							//标记    
							mFlag.push_back(p + j);
						}
					}
				}
			}
			//将标记的点删除    
			for (vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
			{
				//printf("%d",**i);
				**i = 0;
			}
			//直到没有点满足，算法结束    
			if (mFlag.empty())
			{
				break;
			}
			else
			{
				mFlag.clear();//将mFlag清空    
			}
		}
		

		for (int i = 0; i < height; ++i) {
			uchar * q = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j) {
				uchar q1 = q[j];
				if (q1 == 1) {

					NSP++;
				}


			}



		}
		//printf("细化后的骨架数目%lf", NSP);
		double StrokeWidth = NPB/NSP;
		return  StrokeWidth;

	}
	double StrokeLength(Mat &src) {
		int width = src.cols;
		int height = src.rows;
		double NPB = 0;
		for (int i = 0; i < height; ++i) {
			uchar * q = src.ptr<uchar>(i);
			for (int j = 0; j < width; ++j) {
				uchar q1 = q[j];
				if (q1 == 1) {

					NPB++;
				}


			}



		}
		//printf("二值化后的黑色数目%lf", NPB);
		return NPB;
	}
	double StrokeAspectRatio(Mat &src) {
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
					if(i<minx){
						minx= i;
					}
					if (j<miny) {
						miny = j;
					}
					if (i>maxx) {
						maxx = i;
					}
					if (j>maxy) {
						maxy = j;
					}

					
				}


			}



		}
		double StrokeWidth = maxx - minx;
		double StrokeLength = maxy - miny;
		printf("笔画高度%f", StrokeWidth);
		printf("笔画宽度%f", StrokeLength);
		double strokeAspectRatio = StrokeLength / StrokeWidth;
		return strokeAspectRatio;
		
	
	
	}

	  double Radicalwidth(Mat &src){
	   double width = src.cols;
		double height = src.rows;
		return width;
	}
	  double Radicalheight(Mat &src) {
		  double width = src.cols;
		  double height = src.rows;
		  return height;
	  }
	  double RadicalAspectRatio(Mat &src) {
		  double width = src.cols;
		  double height = src.rows;

		  return width/height;
	  }
};

