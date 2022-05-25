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
using namespace std;
using namespace cv;
/*int imagenum = 0;
	ziku.push_back("王");
	ziku.push_back("任");
	ziku.push_back("一");
	ziku.push_back("二");
	ziku.push_back("三");






	int num = 0;
	char txt[100];
	string input;
	ifstream infile1;
	infile1.open("D:\\书法字生成\\outtext.txt");

	if (!infile1.is_open())
	{
		cout << "" << endl;
		exit(0);
	}

	while (!infile1.eof())
	{
		infile1.getline(txt, 100);
		input = UTF8ToGB(txt);
		cout << input << endl;

	}

	infile1.close();
	//getchar();





		//string input;
		//ifstream infile1("D:\\书法字生成\\outtext.txt", ios::in);
	  //  infile1 >> input;
		//cout << input;

		//cout << "请输入要转换风格类型：\n";
		//cout << "提示：输入风格代号\n";
		//cout << "1-王羲之风格\n";
		//cout << "2-颜真卿风格\n";
		//cout << "3-欧阳询风格\n";
	int inputstylecopy;
	ifstream infile("D:\\书法字生成\\outstyle.txt", ios::in);
	//cin >> inputstylecopy;
	infile >> inputstylecopy;
	inputstyle = inputstylecopy;


	for (int i = 0; i < input.size(); i++) {
		if (i == input.size() - 2) {
			iflast = 1;
		}
		string ch;
		ch += input[i];
		ch += input[i + 1];
		i = i + 1;
		cout << ch;

		int ifex = ifexist(ch);
		if (ifex==1) {
			String jj = ch.c_str();
			String path = "D:/书法字生成/输入字库/" + jj + ".jpg";
			Mat a = imread(path, IMREAD_GRAYSCALE);
			//imshow("原始图像", a);
			Mat src, test;
			a.copyTo(src);
			a.copyTo(test);
			cv::threshold(test, test, 128, 255, cv::THRESH_BINARY);
			GaussianBlur(src, src, Size(7, 7), 0, 0);//高斯滤波
			Mat dst;
			threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);//二值化，前景为1，背景为0
			thinImage(src, dst);//图像细化（骨骼化）
			endPointAndintersectionPointDetection(dst, test);
			xunhuan(dst);
			src = src * 255;
			//imshow("原始图像", a);
			dst = dst * 255;
			bitwise_not(dst, dst);

			//333333333333333333333imshow("细化图像", dst);
			//imwrite("D:/baocun2.jpg", dst);


			//waitKey(10000);

		}
		if (ifex == 0) {

			fstream f;
			//追加写入,在原来基础上加了ios::app
			f.open("D:\\书法字生成\\ganorder.txt", ios::out | ios::app);
			//输入你想写入的内容
			f << shuchuorder << ',';
			f.close();


			//ofstream out("D:\\书法字生成\\ganorder.txt");
			//out << shuchuorder;
			//out.close();
			shuchuorder++;
			imagenum++;
			continue;


		}






	}*/
	/*
	vector<Mat> src(input.size() / 2);
	int j = 0;
	for (int i = 0; i < input.size(); i++) {

		string ch;
		ch += input[i];
		ch += input[i + 1];
		i = i + 1;
		cout << ch;
		String jj = ch.c_str();
		string shunxu = to_string(j + 1);
		src[j] = imread("D:/书法字生成/输出成果/" + shunxu + jj + ".jpg");
		//imshow("展示", src[j]);
		//waitKey(1000);
		j++;
	}



	int k = 0;
	for (int i = 0; i < input.size(); i++) {

		string ch;
		ch += input[i];
		ch += input[i + 1];
		i = i + 1;
		cout << ch;
		String jj = ch.c_str();
		String shunxu = to_string(k + 1);
		String path = "D:/书法字生成/输出成果/" + shunxu + jj + ".jpg";
		const char *gg = path.c_str();
		remove(gg);

		k++;
	}
	Mat img;
	if (inputstyle == 1) {
		img = imread("D:/书法字生成/输出字库/王羲之/开头王羲之.jpg");
	}
	if (inputstyle == 2) {
		img = imread("D:/书法字生成/输出字库/颜真卿/开头颜真卿.jpg");

	}
	if (inputstyle == 3) {
		img = imread("D:/书法字生成/输出字库/欧阳询/开头欧阳询.jpg");

	}

	for (int i = 0; i < input.size() / 2; i++) {
		hconcat(img, src[i], img);

	}


	string style;
	if (inputstyle == 1) {
		style = "王羲之";
	}
	if (inputstyle == 2) {
		style = "颜真卿";
	}
	if (inputstyle == 3) {
		style = "欧阳询";
	}
	imshow(style, img);
	waitKey(0);
	imwrite("D:/书法字生成/最终图片/out.jpg", img);


	shuchuorder = 1;


	*/




