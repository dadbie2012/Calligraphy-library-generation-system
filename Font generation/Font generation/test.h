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
	ziku.push_back("��");
	ziku.push_back("��");
	ziku.push_back("һ");
	ziku.push_back("��");
	ziku.push_back("��");






	int num = 0;
	char txt[100];
	string input;
	ifstream infile1;
	infile1.open("D:\\�鷨������\\outtext.txt");

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
		//ifstream infile1("D:\\�鷨������\\outtext.txt", ios::in);
	  //  infile1 >> input;
		//cout << input;

		//cout << "������Ҫת��������ͣ�\n";
		//cout << "��ʾ�����������\n";
		//cout << "1-����֮���\n";
		//cout << "2-��������\n";
		//cout << "3-ŷ��ѯ���\n";
	int inputstylecopy;
	ifstream infile("D:\\�鷨������\\outstyle.txt", ios::in);
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
			String path = "D:/�鷨������/�����ֿ�/" + jj + ".jpg";
			Mat a = imread(path, IMREAD_GRAYSCALE);
			//imshow("ԭʼͼ��", a);
			Mat src, test;
			a.copyTo(src);
			a.copyTo(test);
			cv::threshold(test, test, 128, 255, cv::THRESH_BINARY);
			GaussianBlur(src, src, Size(7, 7), 0, 0);//��˹�˲�
			Mat dst;
			threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);//��ֵ����ǰ��Ϊ1������Ϊ0
			thinImage(src, dst);//ͼ��ϸ������������
			endPointAndintersectionPointDetection(dst, test);
			xunhuan(dst);
			src = src * 255;
			//imshow("ԭʼͼ��", a);
			dst = dst * 255;
			bitwise_not(dst, dst);

			//333333333333333333333imshow("ϸ��ͼ��", dst);
			//imwrite("D:/baocun2.jpg", dst);


			//waitKey(10000);

		}
		if (ifex == 0) {

			fstream f;
			//׷��д��,��ԭ�������ϼ���ios::app
			f.open("D:\\�鷨������\\ganorder.txt", ios::out | ios::app);
			//��������д�������
			f << shuchuorder << ',';
			f.close();


			//ofstream out("D:\\�鷨������\\ganorder.txt");
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
		src[j] = imread("D:/�鷨������/����ɹ�/" + shunxu + jj + ".jpg");
		//imshow("չʾ", src[j]);
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
		String path = "D:/�鷨������/����ɹ�/" + shunxu + jj + ".jpg";
		const char *gg = path.c_str();
		remove(gg);

		k++;
	}
	Mat img;
	if (inputstyle == 1) {
		img = imread("D:/�鷨������/����ֿ�/����֮/��ͷ����֮.jpg");
	}
	if (inputstyle == 2) {
		img = imread("D:/�鷨������/����ֿ�/������/��ͷ������.jpg");

	}
	if (inputstyle == 3) {
		img = imread("D:/�鷨������/����ֿ�/ŷ��ѯ/��ͷŷ��ѯ.jpg");

	}

	for (int i = 0; i < input.size() / 2; i++) {
		hconcat(img, src[i], img);

	}


	string style;
	if (inputstyle == 1) {
		style = "����֮";
	}
	if (inputstyle == 2) {
		style = "������";
	}
	if (inputstyle == 3) {
		style = "ŷ��ѯ";
	}
	imshow(style, img);
	waitKey(0);
	imwrite("D:/�鷨������/����ͼƬ/out.jpg", img);


	shuchuorder = 1;


	*/




