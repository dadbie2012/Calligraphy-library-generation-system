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
#include "SimilarityDetection.h"
#include "toolsclass.h"
#include "SimilarityCalculation.h"
#include "bihuafenge.h"
#include "fenggejieguo.h"
using namespace std;
using namespace cv;




int main(){
	
	



	vector<Mat> endimage;
	double frontwidth = 0;
	vector<double>danziziku;
	/*danziziku.push_back("若");
	danziziku.push_back("人");
	danziziku.push_back("生");
	danziziku.push_back("如");
	danziziku.push_back("初");
	bushoudanziziku.push_back("只");
	bushoudanziziku.push_back("过");*/
	string input;
	cout << "请输入要转换字：\n";
	cin >> input;


	for (int i = 0; i < input.size(); i++) {
		int num = i + 1;

		map<double, Mat> mapdanzi;
		string ch;
		ch += input[i];
		ch += input[i + 1];
		i = i + 1;
		cout << ch;
		if (ifdanziexist(ch) == 1) {//是否在单字库里存在
			String jj = ch.c_str();
			string ch1 = "'";
			string ch2 = "'";
			string ch3 = ch1 + ch + ch2;
			const char* sentence1 = ch3.data();
			MYSQL_ROW row;
			mysqlconnect *mysql = new mysqlconnect();

			const char *sentence2 = "select word.wordname, word.completewordcharacterid, completewordcharacter.authorid, completewordcharacter.workid, completewordcharacter.path from completewordcharacter, word where word.completewordcharacterid = completewordcharacter.characterid and word.wordname = ";

			//const char *sentence2 = "SELECT * from word where wordname=";
			std::string src1(sentence1);
			std::string src2(sentence2);
			string sentenceadd = src2 + src1;
			const char *sentence = sentenceadd.c_str();
			MYSQL_RES* res = mysql->mysql(sentence);
			while (row = mysql_fetch_row(res))

			{
				printf("信息************************\n");
				printf("%s ", row[0]);//wordname
				printf("%s ", row[1]);//completewordcharacterid
				printf("%s ", row[2]);//authorid
				printf("%s ", row[3]);//workid
				printf("%s ", row[4]);//path
				String path = row[4];

				cout << endl;
				Mat image = imread(path, IMREAD_GRAYSCALE);
				Mat afterheng;
				Mat dst, src;
				image.copyTo(src);
				GaussianBlur(src, src, Size(7, 7), 0, 0);//高斯滤波
				threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);
				//cv::imshow("gray_binary", image);//grar_binary为二值化后图片
				thinimage *ti = new thinimage();
				double StrokeWidth = ti->StrokeWidth(src, dst);
				printf("单字平均宽度：%f\n", StrokeWidth);

				mapdanzi.insert(pair<double, Mat>(StrokeWidth, image));

				dst = dst * 255;
				bitwise_not(dst, dst);
				//cv::imshow("gray_binary", dst);
				//waitKey(1000);

				//imshow("原始图像", a);

				//waitKey(1000);

			}
			map<double, Mat>::reverse_iterator   iter;

			if (num == 1 || num == 6) {
				double max = 0;

				for (iter = mapdanzi.rbegin(); iter != mapdanzi.rend(); iter++) {
					if (iter->first > max) {
						cout << iter->first;
						max = iter->first;
						cout << endl;
					}

				}
				cout << "宽度最大为：" << max;
				frontwidth = max;

				// mapdanzi.find(max)->second;
				endimage.push_back(mapdanzi.find(max)->second);
			}
			if (num != 1 && num != 6) {


				//double frontdouble = atoi(front.c_str());
				//cout << "ssss" << frontdouble;
				double key1 = 0;
				double key2 = 0;
				double minabs1 = 100;
				double minabs2 = -100;
				for (iter = mapdanzi.rbegin(); iter != mapdanzi.rend(); iter++) {
					if (iter->first - frontwidth > 0 && iter->first - frontwidth < minabs1) {

						minabs1 = iter->first - frontwidth;
						cout << "最小绝对值" << minabs1;
						key1 = iter->first;
						cout << endl;
					}
					if (iter->first - frontwidth <= 0 && iter->first - frontwidth > minabs2) {

						minabs2 = iter->first - frontwidth;
						cout << "最小绝对值" << minabs2;
						key2 = iter->first;
						cout << endl;
					}

				}
				if (abs(minabs2) < 4) {
					frontwidth = key2;

					endimage.push_back(mapdanzi.find(key2)->second);
				}

				if (abs(minabs2) > 4) {
					frontwidth = key1;

					endimage.push_back(mapdanzi.find(key1)->second);

				}

			}




		}

		if (ifbushoudanziexist(ch) == 1) {
			string ch1 = "'";
			string ch2 = "'";
			string ch3 = ch1 + ch + ch2;
			const char* sentence1 = ch3.data();
			MYSQL_ROW row;
			mysqlconnect *mysql = new mysqlconnect();
			const char *sentence2 = "select word.wordname,radicalcharacter.structureid,radicalcharacter.upperid,radicalcharacter.middleid,radicalcharacter.underid,radicalcharacter.upperleftid,radicalcharacter.upperrightid,radicalcharacter.middleleftid,radicalcharacter.middlerightid,radicalcharacter.underleftid,radicalcharacter.underrightid,radicalcharacter.replacepath from radicalcharacter,word where word.radicalwordcharacterid=radicalcharacter.characterid and  word.wordname=";

			std::string src1(sentence1);
			std::string src2(sentence2);
			string sentenceadd = src2 + src1;

			const char *sentence = sentenceadd.c_str();
			MYSQL_RES* res = mysql->mysql(sentence);
			String tihuanzipath;
			String shangbushou;
			String xiabushou;
			char* jiegouleixing = NULL;
			while (row = mysql_fetch_row(res))

			{
				printf("信息************************\n");
				printf("单字%s， ", row[0]);
				printf("结构类型%s， ", row[1]);
				printf("上部首%s， ", row[2]);
				printf("中部首%s， ", row[3]);
				printf("下部首%s， ", row[4]);
				printf("上左部首%s， ", row[6]);
				printf("上右部首%s， ", row[7]);
				printf("中左部首%s， ", row[8]);
				printf("中右部首%s， ", row[9]);
				printf("下左部首%s， ", row[10]);
				printf("下右部首%s， ", row[10]);
				printf("替换字存储地址%s ", row[11]);
				tihuanzipath = row[11];
				jiegouleixing = row[1];
				shangbushou = row[2];
				xiabushou = row[4];
			}

			string jiegouleixingend = jiegouleixing;
			//上下结构
			if (jiegouleixingend == "1") {

				Mat Originaldrawing = imread(tihuanzipath, IMREAD_GRAYSCALE);
				//imshow("Originaldrawing", Originaldrawing);
				waitKey(0);
				Mat imageShold;
				threshold(Originaldrawing, imageShold, 100, 255, THRESH_BINARY_INV);
				Mat labels;
				int n_comps = connectedComponents(imageShold, labels, 4, CV_16U);
				cout << "轮廓数" << n_comps << endl;
				int rows = Originaldrawing.rows;
				int cols = Originaldrawing.cols;
				Mat src_color;// = Mat::zeros(imageShold.size(), CV_8UC3);
				src_color.create(rows, cols, CV_8UC3);
				src_color = Scalar::all(0);
				for (int x = 0; x < rows; x++)
				{
					for (int y = 0; y < cols; y++)
					{
						int label = labels.at<__int16>(x, y);//注意labels是CV_16U类型
						if (label == 0)
						{
							src_color.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
							continue;
						}
						if (label == 1) {
							src_color.at<Vec3b>(x, y)[0] = 255;
							src_color.at<Vec3b>(x, y)[1] = 0;
							src_color.at<Vec3b>(x, y)[2] = 0;
						}
						if (label > 0 && label != 1) {
							src_color.at<Vec3b>(x, y)[0] = 0;//b
							src_color.at<Vec3b>(x, y)[1] = 255;//g
							src_color.at<Vec3b>(x, y)[2] = 0;//r
						}

					}
				}
				//imshow("liantongtu", src_color);
				//imwrite("D:/王羲之字库/colorimage.jpg", src_color);
				waitKey(0);

				//把上部首保存起来
				double shangbushouinformation[20][10];
				String shangbushoumysqlinformation[20][10];
				String xiabushoumysqlinformation[20][10];
				vector<Mat>shangbushouimagevector;
				string ch4 = "'";
				string ch5 = "'";
				string ch6 = ch4 + shangbushou + ch5;

				//const char* sentence3 = ch6.data();
				MYSQL_ROW row2;
				mysqlconnect *mysql2 = new mysqlconnect();
				const char *sentence4 = "select strokestables.workid,strokestables.authorid,strokestables.wordstructureid,strokestables.strokepositionid,strokestables.completestroke,strokestables.ContinuousSituation,strokestables.path  from word,radicalcharacter,strokestables where word.radicalwordcharacterid=radicalcharacter.characterid and word.wordname='只' and strokestables.strokeid=radicalcharacter.upperid;";
				//std::string src3(sentence3);
				std::string src4(sentence4);
				//string sentenceadd2 = src4 + src3;

				const char *sentence2 = src4.c_str();
				MYSQL_RES* res2 = mysql2->mysql(sentence2);
				int shangbihuaimagenum = 0;
				while (row2 = mysql_fetch_row(res2))

				{

					printf("上笔画信息************************\n");
					printf("作品id%s， ", row2[0]);//b
					printf("作者id%s， ", row2[1]);//
					printf("原字结构%s， ", row2[2]);//
					printf("部首位置%s， ", row2[3]);//b
					printf("是否完整%s， ", row2[4]);//b
					printf("有无连笔%s， ", row2[5]);//
					printf("存储位置%s， ", row2[6]);//


					//获取每一张上部首image
					String path = row2[6];
					Mat shangbushouimage = imread(path, IMREAD_GRAYSCALE);
					shangbushouimagevector.push_back(shangbushouimage);
					Mat dst, src;
					shangbushouimage.copyTo(src);
					GaussianBlur(src, src, Size(7, 7), 0, 0);//高斯滤波
					threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);
					//cv::imshow("gray_binary", shangbushouimage);//grar_binary为二值化后图片
					thinimage *ti = new thinimage();
					double RadicalCoarseness = ti->StrokeWidth(src, dst);
					printf("上部首粗度：%f\n", RadicalCoarseness);
					double Radicalwidth = ti->Radicalwidth(dst);
					printf("上部首长度：%f\n", Radicalwidth);
					double Radicalheight = ti->Radicalheight(src);
					printf("上部首宽度：%f\n", Radicalheight);
					double  RadicalAspectRatio = ti->RadicalAspectRatio(src);
					printf("上部首长宽比：%f\n", RadicalAspectRatio);
					cout << endl;
					dst = dst * 255;
					bitwise_not(dst, dst);
					//cv::imshow("gray_binary", dst);
					waitKey(0);

					shangbushouinformation[shangbihuaimagenum][0] = RadicalCoarseness;
					shangbushouinformation[shangbihuaimagenum][1] = Radicalwidth;
					shangbushouinformation[shangbihuaimagenum][2] = Radicalheight;
					shangbushouinformation[shangbihuaimagenum][3] = RadicalAspectRatio;
					shangbushoumysqlinformation[shangbihuaimagenum][0] = row2[0];
					shangbushoumysqlinformation[shangbihuaimagenum][1] = row2[1];
					shangbushoumysqlinformation[shangbihuaimagenum][2] = row2[2];
					shangbushoumysqlinformation[shangbihuaimagenum][3] = row2[3];
					shangbushoumysqlinformation[shangbihuaimagenum][4] = row2[4];
					shangbushoumysqlinformation[shangbihuaimagenum][5] = row2[5];
					shangbushoumysqlinformation[shangbihuaimagenum][6] = row2[6];


					shangbihuaimagenum++;

					//	imshow("shangbushouimage", shangbushouimage);
					//	waitKey(2000);
				}

				//把下部首保存起来

				double xiabushouinformation[20][10];
				vector<Mat>xiabushouimagevector;
				string ch7 = "'";
				string ch8 = "'";
				string ch9 = ch7 + xiabushou + ch8;

				const char* sentence5 = ch9.data();
				MYSQL_ROW row3;
				mysqlconnect *mysql3 = new mysqlconnect();
				const char *sentence6 = "select strokestables.workid,strokestables.authorid,strokestables.wordstructureid,strokestables.strokepositionid,strokestables.completestroke,strokestables.ContinuousSituation,strokestables.path  from word,radicalcharacter,strokestables where word.radicalwordcharacterid=radicalcharacter.characterid and word.wordname='只' and strokestables.strokeid=radicalcharacter.underid";
				//std::string src5(sentence5);
				std::string src6(sentence6);
				//string sentenceadd3 = src6 + src5;

				const char *sentence8 = src6.c_str();
				MYSQL_RES* res3 = mysql3->mysql(sentence8);
				int xiabihuaimagenum = 0;
				while (row3 = mysql_fetch_row(res3))

				{

					printf("下部首信息************************\n");
					printf("作品id%s， ", row3[0]);//b
					printf("作者id%s， ", row3[1]);//
					printf("原字结构%s， ", row3[2]);//
					printf("部首位置%s， ", row3[3]);//b
					printf("是否完整%s， ", row3[4]);//b
					printf("有无连笔%s， ", row3[5]);//
					printf("存储位置%s， ", row3[6]);//
					//获取每一张下部首image
					String path = row3[6];
					Mat xiabushouimage = imread(path, IMREAD_GRAYSCALE);
					xiabushouimagevector.push_back(xiabushouimage);
					Mat dst, src;
					xiabushouimage.copyTo(src);
					GaussianBlur(src, src, Size(7, 7), 0, 0);//高斯滤波
					threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);
					//cv::imshow("gray_binary", shangbushouimage);//grar_binary为二值化后图片
					thinimage *ti = new thinimage();
					double RadicalCoarseness = ti->StrokeWidth(src, dst);
					printf("下部首粗度：%f\n", RadicalCoarseness);
					double Radicalwidth = ti->Radicalwidth(dst);
					printf("下部首长度：%f\n", Radicalwidth);
					double Radicalheight = ti->Radicalheight(src);
					printf("下部首宽度：%f\n", Radicalheight);
					double  RadicalAspectRatio = ti->RadicalAspectRatio(src);
					printf("下部首长宽比：%f\n", RadicalAspectRatio);
					cout << endl;
					dst = dst * 255;
					bitwise_not(dst, dst);
					//cv::imshow("gray_binary", dst);
					waitKey(0);
					xiabushouinformation[xiabihuaimagenum][0] = RadicalCoarseness;
					xiabushouinformation[xiabihuaimagenum][1] = Radicalwidth;
					xiabushouinformation[xiabihuaimagenum][2] = Radicalheight;
					xiabushouinformation[xiabihuaimagenum][3] = RadicalAspectRatio;
					xiabushoumysqlinformation[xiabihuaimagenum][0] = row3[0];
					xiabushoumysqlinformation[xiabihuaimagenum][1] = row3[1];
					xiabushoumysqlinformation[xiabihuaimagenum][2] = row3[2];
					xiabushoumysqlinformation[xiabihuaimagenum][3] = row3[3];
					xiabushoumysqlinformation[xiabihuaimagenum][4] = row3[4];
					xiabushoumysqlinformation[xiabihuaimagenum][5] = row3[5];
					xiabushoumysqlinformation[xiabihuaimagenum][6] = row3[6];

					xiabihuaimagenum++;

					//	imshow("shangbushouimage", shangbushouimage);
					//	waitKey(2000);
				}




				//确定上部首与下部首中心位置
				cout << endl;
				cout << "**************上部首与下部首位置确定*********" << endl;
				CvScalar pixel_v;
				//IplImage *beijing;
				//beijing = cvLoadImage("D:/王羲之字库/colorimage.jpg", 1);
				IplImage *beijing = (IplImage *)&IplImage(src_color);
				double shangbushouwidth;
				double shangbushouheight;
				double shangbushouwidhei;
				double xiabushouwidth;
				double xiabushouheight;
				double xiabushouwidhei;
				int shangbushouwmin = 200;
				int shangbushouwmax = 0;
				int shangbushouhmin = 200;
				int shangbushouhmax = 0;
				int xiabushouwmin = 200;
				int xiabushouwmax = 0;
				int xiabushouhmin = 200;
				int xiabushouhmax = 0;
				for (int i = 0; i < beijing->height; i++)
				{
					for (int j = 0; j < beijing->width; j++)
					{
						pixel_v = cvGet2D(beijing, i, j);
						//计算上部首
						if (pixel_v.val[0] > pixel_v.val[1] && pixel_v.val[0] > pixel_v.val[2] && pixel_v.val[2] < 50 && pixel_v.val[1] < 50) {

							if (j < shangbushouwmin) {

								shangbushouwmin = j;
							}
						}
						if (pixel_v.val[0] > pixel_v.val[1] && pixel_v.val[0] > pixel_v.val[2] && pixel_v.val[2] < 50 && pixel_v.val[1] < 50) {
							if (j > shangbushouwmax) {
								shangbushouwmax = j;
							}
						}
						if (pixel_v.val[0] > pixel_v.val[1] && pixel_v.val[0] > pixel_v.val[2] && pixel_v.val[2] < 50 && pixel_v.val[1] < 50) {
							if (i < shangbushouhmin) {

								shangbushouhmin = i;
							}
						}
						if (pixel_v.val[0] > pixel_v.val[1] && pixel_v.val[0] > pixel_v.val[2] && pixel_v.val[2] < 50 && pixel_v.val[1] < 50) {
							if (i > shangbushouhmax) {
								shangbushouhmax = i;
							}
						}
						//计算下部首
						if (pixel_v.val[1] > pixel_v.val[0] && pixel_v.val[1] > pixel_v.val[0] && pixel_v.val[0] < 50 && pixel_v.val[2] < 50) {

							if (j < xiabushouwmin) {

								xiabushouwmin = j;
							}
						}
						if (pixel_v.val[1] > pixel_v.val[0] && pixel_v.val[1] > pixel_v.val[0] && pixel_v.val[0] < 50 && pixel_v.val[2] < 50) {
							if (j > xiabushouwmax) {
								xiabushouwmax = j;
							}
						}
						if (pixel_v.val[1] > pixel_v.val[0] && pixel_v.val[1] > pixel_v.val[0] && pixel_v.val[0] < 50 && pixel_v.val[2] < 50) {
							if (i < xiabushouhmin) {

								xiabushouhmin = i;
							}
						}
						if (pixel_v.val[1] > pixel_v.val[0] && pixel_v.val[1] > pixel_v.val[0] && pixel_v.val[0] < 50 && pixel_v.val[2] < 50) {
							if (i > xiabushouhmax) {
								xiabushouhmax = i;
							}
						}
					}
				}
				shangbushouwidth = shangbushouwmax - shangbushouwmin;
				shangbushouheight = shangbushouhmax - shangbushouhmin;
				shangbushouwidhei = double(shangbushouwidth) / double(shangbushouheight);
				xiabushouwidth = xiabushouwmax - xiabushouwmin;
				xiabushouheight = xiabushouhmax - xiabushouhmin;
				xiabushouwidhei = double(xiabushouwidth) / double(xiabushouheight);
				printf("原图上部首宽度:%f\n", shangbushouwidth);
				printf("原图上部首高度:%f\n", shangbushouheight);
				printf("原图上部首宽高比:%f\n", shangbushouwidhei);
				printf("原图下部首宽度:%f\n", xiabushouwidth);
				printf("原图下部首高度:%f\n", xiabushouheight);
				printf("原图下部首宽高比:%f\n", xiabushouwidhei);
				printf("原图上部首最小宽:%d\n", shangbushouwmin);
				printf("原图上部首最大宽:%d\n", shangbushouwmax);
				printf("原图上部首宽度中心位置:%d\n", (shangbushouwmax + shangbushouwmin) / 2);
				printf("原图上部首最小高:%d\n", shangbushouhmin);
				printf("原图上部首最大高:%d\n", shangbushouhmax);
				printf("原图上部首高度起始中心:%d\n", (shangbushouhmax + shangbushouhmin) / 2);
				printf("原图下部首最小宽:%d\n", xiabushouwmin);
				printf("原图下部首最大宽:%d\n", xiabushouwmax);
				printf("原图下部首宽度中心位置:%d\n", (xiabushouwmax + xiabushouwmin) / 2);
				printf("原图下部首最小高:%d\n", xiabushouhmin);
				printf("原图下部首最大高:%d\n", xiabushouhmax);
				printf("原图下部首高度起始中心:%d\n", (xiabushouhmax + xiabushouhmin) / 2);

				vector<double> shangbushougradevector;

				vector<Mat>shangbihualasttwo;//把上部首下部首的最大两张图片各自保存
				vector<Mat>xiabihualasttwo;
				vector<Mat>test;

				//显示上部首信息
				for (int i = 0; i < shangbushouimagevector.size(); i++) {
					double shangbushougrade = 0;
					printf("**************第%d张上部首图片**************\n", i + 1);
					cout << "--------上部首作品id:\n" << shangbushoumysqlinformation[i][0] << endl;
					cout << "--------上部首作者id:\n" << shangbushoumysqlinformation[i][1] << endl;



					cout << "--------上部首原字结构:\n" << shangbushoumysqlinformation[i][2] << endl;
					if (shangbushoumysqlinformation[i][2] == "1") {
						shangbushougrade = shangbushougrade + 10;
						cout << "原字结构加分" << endl;
					}

					cout << "--------上部首有无连笔：\n" << shangbushoumysqlinformation[i][5] << endl;
					cout << "--------上部首在原字中位置：\n" << shangbushoumysqlinformation[i][3] << endl;
					if (shangbushoumysqlinformation[i][3] == "1") {
						shangbushougrade = shangbushougrade + 10;
						cout << "部首位置加分" << endl;
					}
					if (shangbushoumysqlinformation[i][3] == "3") {
						shangbushougrade = shangbushougrade + 5;
						cout << "部首位置加分" << endl;
					}
					cout << "--------是否完整上部首：\n" << shangbushoumysqlinformation[i][4] << endl;

					if (shangbushoumysqlinformation[i][4] == "yes") {
						shangbushougrade = shangbushougrade + 10;
						cout << "完整笔画加分" << endl;
					}
					cout << "--------上部首存储位置:\n" << shangbushoumysqlinformation[i][6] << endl;


					for (int j = 0; j < 4; j++) {
						if (j == 0) {
							printf("上部首粗度：%f\n", shangbushouinformation[i][j]);
							double cudugrade = (1 - abs(shangbushouinformation[i][j] - frontwidth) / frontwidth) * 50;
							cout << "粗度得分：" << cudugrade << endl;
							shangbushougrade = shangbushougrade + cudugrade;
						}
						if (j == 1) {
							printf("上部首长度：%f\n", shangbushouinformation[i][j]);
							double changdugrade = (1 - abs(shangbushouinformation[i][j] - shangbushouwidth) / shangbushouwidth) * 15;
							cout << "长度得分：" << changdugrade << endl;
							shangbushougrade = shangbushougrade + changdugrade;
						}
						if (j == 2) {
							printf("上部首高度：%f\n", shangbushouinformation[i][j]);
							double gaodugrade = (1 - abs(shangbushouinformation[i][j] - shangbushouheight) / shangbushouheight) * 15;
							cout << "高度得分：" << gaodugrade << endl;
							shangbushougrade = shangbushougrade + gaodugrade;
						}
						if (j == 3) {
							printf("上部首长宽比：%f\n", shangbushouinformation[i][j]);
							double changkuanbigrade = (1 - abs(shangbushouinformation[i][j] - shangbushouwidhei) / shangbushouwidhei) * 50;
							cout << "长宽比得分：" << changkuanbigrade << endl;
							shangbushougrade = shangbushougrade + changkuanbigrade;
						}


						Mat a = shangbushouimagevector[i];
						//imshow("aaa", a);
						waitKey(0);

					}
					shangbushougradevector.push_back(shangbushougrade);
				}
				for (int i = 0; i < shangbushougradevector.size(); i++) {
					cout << "第" << i + 1 << "张上部首图片得分为：" << shangbushougradevector[i] << endl;


				}
				//取得上部首分最大的两张图片
				double shangbushoufirstwidth = 0;
				double shangbushoufirstheight = 0;
				double shangbushousecondwidth = 0;
				double shangbushousecondheight = 0;
				vector<double>shangbushougradevectorstart = shangbushougradevector;
				sort(shangbushougradevector.begin(), shangbushougradevector.end());
				double firstgrade = shangbushougradevector[shangbushougradevector.size() - 1];
				double secondgrade = shangbushougradevector[shangbushougradevector.size() - 2];
				cout << "最大的得分：" << shangbushougradevector[shangbushougradevector.size() - 1];
				cout << "第二大的得分：" << shangbushougradevector[shangbushougradevector.size() - 2];
				int firstnum = 0;
				int secondnum = 0;
				for (int i = 0; i < shangbushougradevector.size(); i++) {
					if (shangbushougradevectorstart[i] == firstgrade) {
						firstnum = i;
					}
					if (shangbushougradevectorstart[i] == secondgrade) {
						secondnum = i;
					}

				}
				for (int i = 0; i < shangbushougradevector.size(); i++) {


					if (i == firstnum) {
						shangbihualasttwo.push_back(shangbushouimagevector[i]);
						shangbushoufirstwidth = shangbushouinformation[i][1];
						shangbushoufirstheight = shangbushouinformation[i][2];
						//imshow("first",shangbushouimagevector[i]);
						//waitKey(1000);
					}
					if (i == secondnum) {
						shangbihualasttwo.push_back(shangbushouimagevector[i]);
						shangbushousecondwidth = shangbushouinformation[i][1];
						shangbushousecondheight = shangbushouinformation[i][2];
						//imshow("second", shangbushouimagevector[i]);
						//waitKey(1000);
					}

				}

				//显示下部首信息
				double xiabushougrade = 0;
				vector<double>xiabushougradevector;


				for (int i = 0; i < xiabushouimagevector.size(); i++) {
					double xiabushougrade = 0;
					printf("************第%d张下部首图片************\n", i + 1);
					cout << "--------下部首作品id:\n" << shangbushoumysqlinformation[i][0] << endl;
					cout << "--------下部首作者id:\n" << shangbushoumysqlinformation[i][1] << endl;


					cout << "--------下部首原字结构:\n" << xiabushoumysqlinformation[i][2] << endl;
					if (xiabushoumysqlinformation[i][2] == "1") {
						xiabushougrade = xiabushougrade + 10;
						cout << "原字结构加分" << endl;
					}
					cout << "--------下部首有无连笔：\n" << xiabushoumysqlinformation[i][5] << endl;
					cout << "--------下部首在原字中位置：\n" << xiabushoumysqlinformation[i][3] << endl;
					if (xiabushoumysqlinformation[i][3] == "3") {
						xiabushougrade = xiabushougrade + 10;
						cout << "部首位置加分" << endl;
					}
					if (xiabushoumysqlinformation[i][3] == "1") {
						xiabushougrade = xiabushougrade + 5;
						cout << "部首位置加分" << endl;
					}
					cout << "--------是否完整下部首：\n" << xiabushoumysqlinformation[i][4] << endl;
					if (xiabushoumysqlinformation[i][4] == "yes") {
						xiabushougrade = xiabushougrade + 10;
						cout << "完整笔画加分" << endl;
					}
					cout << "--------下部首存储位置:\n" << xiabushoumysqlinformation[i][6] << endl;

					for (int j = 0; j < 4; j++) {
						if (j == 0) {
							printf("下部首粗度：%f\n", xiabushouinformation[i][j]);
							double cudugrade = (1 - abs(xiabushouinformation[i][j] - frontwidth) / frontwidth) * 50;
							cout << "粗度得分：" << cudugrade << endl;
							xiabushougrade = xiabushougrade + cudugrade;
						}
						if (j == 1) {
							printf("下部首长度：%f\n", xiabushouinformation[i][j]);
							double changdugrade = (1 - abs(xiabushouinformation[i][j] - xiabushouwidth) / xiabushouwidth) * 15;
							cout << "长度得分：" << changdugrade << endl;
							xiabushougrade = xiabushougrade + changdugrade;
						}
						if (j == 2) {
							printf("下部首宽度：%f\n", xiabushouinformation[i][j]);
							double gaodugrade = (1 - abs(xiabushouinformation[i][j] - xiabushouheight) / xiabushouheight) * 15;
							cout << "高度得分：" << gaodugrade << endl;
							xiabushougrade = xiabushougrade + gaodugrade;
						}
						if (j == 3) {
							printf("下部首长宽比：%f\n", xiabushouinformation[i][j]);
							double changkuanbigrade = (1 - abs(shangbushouinformation[i][j] - xiabushouwidhei) / xiabushouwidhei) * 50;
							cout << "长宽比得分：" << changkuanbigrade << endl;
							xiabushougrade = xiabushougrade + changkuanbigrade;
						}

					}

					Mat a = xiabushouimagevector[i];
					//imshow("aaa", a);
					waitKey(0);

					xiabushougradevector.push_back(xiabushougrade);

				}
				for (int i = 0; i < xiabushougradevector.size(); i++) {
					cout << "第" << i + 1 << "张下部首图片得分为：" << xiabushougradevector[i] << endl;
					//选取合适的上部首

				}
				//取得下部首分最大的两张图片
				double xiabushoufirstwidth = 0;
				double xiabushoufirstheight = 0;
				double xiabushousecondwidth = 0;
				double xiabushousecondheight = 0;
				vector<double>xiabushougradevectorstart = xiabushougradevector;
				sort(xiabushougradevector.begin(), xiabushougradevector.end());
				double xiabushoufirstgrade = xiabushougradevector[xiabushougradevector.size() - 1];
				double xiabushousecondgrade = xiabushougradevector[xiabushougradevector.size() - 2];
				cout << "最大的得分：" << xiabushougradevector[xiabushougradevector.size() - 1] << endl;
				cout << "第二大的得分：" << xiabushougradevector[xiabushougradevector.size() - 2] << endl;
				int xiabushoufirstnum = 0;
				int xiabushousecondnum = 0;
				for (int i = 0; i < xiabushougradevector.size(); i++) {
					if (xiabushougradevectorstart[i] == xiabushoufirstgrade) {
						xiabushoufirstnum = i;
					}
					if (xiabushougradevectorstart[i] == xiabushousecondgrade) {
						xiabushousecondnum = i;
					}

				}
				for (int i = 0; i < xiabushougradevector.size(); i++) {
					if (i == xiabushoufirstnum) {
						xiabihualasttwo.push_back(xiabushouimagevector[i]);
						xiabushoufirstwidth = xiabushouinformation[i][1];
						xiabushoufirstheight = xiabushouinformation[i][2];
						//imshow("first", xiabushouimagevector[i]);
						//waitKey(1000);
					}
					if (i == xiabushousecondnum) {
						xiabihualasttwo.push_back(xiabushouimagevector[i]);
						xiabushousecondwidth = xiabushouinformation[i][1];
						xiabushousecondheight = xiabushouinformation[i][2];
						//imshow("second", xiabushouimagevector[i]);
						//waitKey(1000);
					}

				}

				//部首贴图	
				  //第一张图
				 //计算贴图位置点
				cout << "最大上部首长度：" << shangbushoufirstwidth << endl;
				cout << "最大上部首高度：" << shangbushoufirstheight << endl;
				cout << "第二大上部首长度：" << shangbushousecondwidth << endl;
				cout << "第二大上部首高度：" << shangbushousecondheight << endl;
				cout << "最大下部首长度：" << xiabushoufirstwidth << endl;
				cout << "最大下部首高度：" << xiabushoufirstheight << endl;
				cout << "第二大下部首长度：" << xiabushousecondwidth << endl;
				cout << "第二大下部首高度：" << xiabushousecondheight << endl;

				printf("原图上部首宽度中心位置:%d\n", (shangbushouwmax + shangbushouwmin) / 2);

				printf("原图上部首高度起始中心:%d\n", (shangbushouhmax + shangbushouhmin) / 2);

				printf("原图下部首宽度中心位置:%d\n", (xiabushouwmax + xiabushouwmin) / 2);

				printf("原图下部首高度起始中心:%d\n", (xiabushouhmax + xiabushouhmin) / 2);
				int shangbushouwidthcenter = (shangbushouwmax + shangbushouwmin) / 2 - shangbushoufirstwidth / 2;
				int shangbushouheightcenter = (shangbushouhmax + shangbushouhmin) / 2 - shangbushoufirstheight / 2;
				int xiabushouwidthcenter = (xiabushouwmax + xiabushouwmin) / 2 - xiabushoufirstwidth / 2;
				int xiabushouheightcenter = (xiabushouhmax + xiabushouhmin) / 2 - xiabushoufirstheight / 2;
				cout << "上部首宽度中心：" << shangbushouwidthcenter << endl;
				cout << "上部首高度中心：" << shangbushouheightcenter << endl;
				cout << "下部首宽度中心：" << xiabushouwidthcenter << endl;
				cout << "下部首宽高度中心：" << xiabushouheightcenter << endl;
				tietu *first = new tietu();
				tietu *first1 = new tietu();
				Mat firstbeijingtu = imread("D:/王羲之字库/输入单字.jjj.jpg");
				int shangbihuaweizhi = 0;
				int xiabihuaweizhi = 0;
				first->fangfatietu(shangbihualasttwo[0], xiabihualasttwo[0], src_color, shangbushouwidthcenter, shangbushouheightcenter, xiabushouwidthcenter, xiabushouheightcenter);








			}


		}












	}
	for (int i = 0; i < endimage.size(); i++) {
		cout << i;
		Mat a = endimage[i];
		imshow("aaa", a);
		waitKey(0);


	}




	




	
}
