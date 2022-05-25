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
using namespace std;
using namespace cv;
class tietu
{
public:
	void fangfatietu(Mat &shangbushouimage,Mat &xiabushouimage,Mat &beijingtu,int shangbushouwidth,int shangbushouheight,int xiabushouwidth,int xiabushouheight) {
		
			CvMat bk1; IplImage *pImg2;


			IplImage *pBK1;

			pBK1 = (IplImage *)&IplImage(beijingtu);
			Mat three_channelshangbushou = Mat::zeros(shangbushouimage.rows, shangbushouimage.cols, CV_8UC3);
			vector<Mat> channels;
			for (int m = 0; m < 3; m++)
			{
				channels.push_back(shangbushouimage);
			}
			merge(channels, three_channelshangbushou);
			IplImage *shangbushou = (IplImage *)&IplImage(three_channelshangbushou);
			Mat three_channelxiabushou = Mat::zeros(xiabushouimage.rows, xiabushouimage.cols, CV_8UC3);
			vector<Mat> channels2;
			for (int n = 0; n < 3; n++)
			{
				channels2.push_back(xiabushouimage);
			}
			merge(channels2, three_channelxiabushou);

			IplImage *xiabushou = (IplImage *)&IplImage(three_channelxiabushou);

			//上部首加载
			cvGetSubRect(pBK1, &bk1, cvRect(52, shangbushouheight+22, shangbushou->width, shangbushou->height));
			pImg2 = cvCreateImage(cvSize(shangbushou->width, shangbushou->height), IPL_DEPTH_8U, 1);

			//hhenglenth = pImg1->height;
			//whenglenth = pImg1->width;
			cvCvtColor(shangbushou, pImg2, CV_RGB2GRAY); //rgb转换为灰度图
			for (int j = 0; j < pImg2->height; j++)
			{

				uchar* ptr = (uchar*)(pImg2->imageData + j * pImg2->widthStep);
				uchar* ptr1 = (uchar*)(shangbushou->imageData + j * shangbushou->widthStep);
				uchar* ptr2 = (uchar*)(bk1.data.ptr + j * bk1.step);
				for (int i = 0; i < pImg2->width; i++)
				{

					if (ptr[i] < 250)  //像素值小于250的保留下来 并显示到背景图上 即白色部分被去除 
					{
						ptr2[i * 3] = ptr1[i * 3];
						ptr2[i * 3 + 1] = ptr1[i * 3 + 1];
						ptr2[i * 3 + 2] = ptr1[i * 3 + 2];
					}
				}
			}
			//下部首加载
			cvGetSubRect(pBK1, &bk1, cvRect(45, xiabushouheight-22, xiabushou->width, xiabushou->height));
			pImg2 = cvCreateImage(cvSize(xiabushou->width, xiabushou->height), IPL_DEPTH_8U, 1);

			//hshulenth = pImg1->height;
			//wshulenth = pImg1->width;
			cvCvtColor(xiabushou, pImg2, CV_RGB2GRAY); //rgb转换为灰度图
			for (int j = 0; j < pImg2->height; j++)
			{
				uchar* ptr = (uchar*)(pImg2->imageData + j * pImg2->widthStep);
				uchar* ptr1 = (uchar*)(xiabushou->imageData + j * xiabushou->widthStep);
				uchar* ptr2 = (uchar*)(bk1.data.ptr + j * bk1.step);
				for (int i = 0; i < pImg2->width; i++)
				{
					if (ptr[i] < 250)  //像素值小于250的保留下来 并显示到背景图上 即白色部分被去除 
					{
						ptr2[i * 3] = ptr1[i * 3];
						ptr2[i * 3 + 1] = ptr1[i * 3 + 1];
						ptr2[i * 3 + 2] = ptr1[i * 3 + 2];
					}
				}
			}


			
			CvScalar pixel_v;
			for (int i = 0; i < pBK1->height; i++)
			{
				for (int j = 0; j < pBK1->width; j++)
				{
					pixel_v = cvGet2D(pBK1, i, j);
					if ((pixel_v.val[0] > pixel_v.val[1] && pixel_v.val[0] > pixel_v.val[2] && pixel_v.val[2] < 50 && pixel_v.val[1] < 50)|| (pixel_v.val[1] > pixel_v.val[0] && pixel_v.val[1] > pixel_v.val[2] && pixel_v.val[0] < 50 && pixel_v.val[2] < 50)) {
						pixel_v.val[0] = 255;//B
						pixel_v.val[1] = 255;//G
						pixel_v.val[2] = 255;//R
						cvSet2D(pBK1, i, j, pixel_v);
					}

				}
			}
			cvNamedWindow("fish", 1);
			cvShowImage("fish", pBK1);
			cvWaitKey(0);
			cvReleaseImage(&pImg2);
		
	}
};

