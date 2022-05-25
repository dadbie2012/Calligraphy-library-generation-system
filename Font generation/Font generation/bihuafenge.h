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
#include "SimilarityDetection.h"
#include "toolsclass.h"
#include "SimilarityCalculation.h"
using namespace std;
using namespace cv;
class bihuafenge
{
public:
	Mat xihuamat;
	int NPB = 0;//��ֵ�����ɫ����
	int NSP = 0;//�Ǽܵ���

	int shuchuorder = 1;
	int inputna = 0;
	int inputpie = 0;
	int inputheng = 0;
	int inputshu = 0;
	int iflast = 0;
	int inputstyle = 0;
	vector<int>jiaochadian_x;
	vector<int>jiaochadian_y;
	vector<int>gujia2_x;
	vector<int>gujia2_y;
	vector<int>guiji_x;
	vector<int>guiji_y;
	vector<int>guiji;
	vector<int>jieshudian_x;
	vector<int>jieshudian_y;
	vector<int>duandian_x;
	vector<int>duandian_y;
	vector<int>tem_guiji;
	int biaojishu = 0;
	int biaojinum = 0;
	int bihuaduanbiaoji = 0;
	vector<int>biaojiifshu;
	vector<int>biaojiifshu2;
	//�жϺ����������
	int houxubiaoji = 0;
	vector<double> houxuguiji;
	double bili(vector<double> & zuobiao) {
		double sum = 0;
		double zero = 0;
		double one = 0;
		double  two = 0;
		double  three = 0;
		double  four = 0;
		double  five = 0;
		double  six = 0;
		double  seven = 0;
		cout << "*****************" << endl;
		for (int i = 0; i < zuobiao.size();i++) {
			cout << zuobiao[i];
		}
		cout << "********************" << endl;
		
		for (int i = 0; i < zuobiao.size(); i++) {
			
			sum ++;
				if (zuobiao[i] == 0) {
					zero++;
				}
				if (zuobiao[i] == 1) {
					one++;
				}
				if (zuobiao[i] == 2) {
					two++;
				}
				if (zuobiao[i] == 3) {
					three++;
				}
				if (zuobiao[i] == 4) {
					four++;
				}
				if (zuobiao[i] == 5) {
					five++;
				}
				if (zuobiao[i] == 6) {
					six++;
				}
				if (zuobiao[i] == 7) {
					seven++;
				}
			}
		/*cout << "********************************" << endl;
		cout << zero << "," << one << "," << two << "," << three << "," << four << "," << five << "," << six << "," << seven <<"," << sum << endl;
		cout << "********************************" << endl;*/
		houxuguiji.clear();
		houxubiaoji = 0;
		if ((two > zero&&two > one&&two > three&&two > four&&two > five&&two > six&&two > seven )|| ((double(two + one) / sum > 0.7&&double(two) / sum > 0.3&&double(one) / sum > 0.3)) || (double(two + three) / sum > 0.7&&double(two) / sum > 0.3&&double(three) / sum > 0.3)) {
			return two/sum*50+one/sum*25+three/sum*25;
		}
		else if ((six > zero&&six > one&&six > three&&six > four&&six > five&&six > two&&six > seven) || (double(six + five) / sum > 0.7&&double(six) / sum > 0.3&&double(five) / sum > 0.3) || (double(six + seven) / sum > 0.7&&double(six) / sum > 0.3&&double(seven) / sum > 0.3)) {
			
			return six/ sum * 50 + five / sum * 25 + seven / sum * 25;
		}
		else {
			
			return 0;
		}
		
		
	}
	double bili2(vector<double> & zuobiao) {
		double sum = 0;
		double zero = 0;
		double one = 0;
		double  two = 0;
		double  three = 0;
		double  four = 0;
		double  five = 0;
		double  six = 0;
		double  seven = 0;
		cout << "*****************" << endl;
		for (int i = 0; i < zuobiao.size(); i++) {
			cout << zuobiao[i];
		}
		cout << "********************" << endl;

		for (int i = 0; i < zuobiao.size(); i++) {

			sum++;
			if (zuobiao[i] == 0) {
				zero++;
			}
			if (zuobiao[i] == 1) {
				one++;
			}
			if (zuobiao[i] == 2) {
				two++;
			}
			if (zuobiao[i] == 3) {
				three++;
			}
			if (zuobiao[i] == 4) {
				four++;
			}
			if (zuobiao[i] == 5) {
				five++;
			}
			if (zuobiao[i] == 6) {
				six++;
			}
			if (zuobiao[i] == 7) {
				seven++;
			}
		}
		/*cout << "********************************" << endl;
		cout << zero << "," << one << "," << two << "," << three << "," << four << "," << five << "," << six << "," << seven <<"," << sum << endl;
		cout << "********************************" << endl;*/
		houxuguiji.clear();
		houxubiaoji = 0;
		if ((zero > two&&zero > one&&zero > three&&zero > four&&zero > five&&zero > six&&zero > seven) || ((double(zero + one) / sum > 0.7&&double(zero) / sum > 0.3&&double(one) / sum > 0.3)) || (double(zero + seven) / sum > 0.7&&double(zero) / sum > 0.3&&double(seven) / sum > 0.3)) {
			return zero / sum * 50 + one / sum * 25 + seven / sum * 25;
		}
		else if ((four > zero&&four > one&&four > three&&four > six&&four > five&&four > two&&four > seven) || (double(four + five) / sum > 0.7&&double(four) / sum > 0.3&&double(five) / sum > 0.3) || (double(four + three) / sum > 0.7&&double(four) / sum > 0.3&&double(three) / sum > 0.3)) {

			return four / sum * 50 + five / sum * 25 + three / sum * 25;
		}
		else {

			return 0;
		}


	}
	double zuobiao3(Mat & src, uchar *p, uchar *m, int i, int j) {

		int width = src.cols;//��
		int height = src.rows;//��
		uchar p1 = *p; 
		if (p1!=1) {
			return 0;
		}
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
				//printf("2");
				houxuguiji.push_back(2);
				houxubiaoji++;

				if (houxubiaoji==10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p - src.step), p, i - 1, j);

			}
			if (p3 == 1 && (p - src.step + 1) != m) {
				//printf("1");
				houxuguiji.push_back(1);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p - src.step + 1), p, i - 1, j + 1);

			}

			if (p4 == 1 && (p + 1) != m) {
				//printf("0");
				houxuguiji.push_back(0);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}
				return zuobiao3(src, (p + 1), p, i, j + 1);
			}

			if (p5 == 1 && (p + src.step + 1) != m) {
				//printf("7");
				houxuguiji.push_back(7);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p + src.step + 1), p, i + 1, j + 1);

			}

			if (p6 == 1 && (p + src.step) != m) {
				//printf("6");
				houxuguiji.push_back(6);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}
				return zuobiao3(src, (p + src.step), p, i + 1, j);

			}

			if (p7 == 1 && (p + src.step - 1) != m) {
				//printf("5");
				houxuguiji.push_back(5);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p + src.step - 1), p, i + 1, j - 1);

			}

			if (p8 == 1 && (p - 1) != m) {
				houxuguiji.push_back(4);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p - 1), p, i, j - 1);

			}

			if (p9 == 1 && (p - src.step - 1) != m) {
				//printf("3");
				houxuguiji.push_back(3);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p - src.step - 1), p, i - 1, j - 1);

			}




		}
		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 1) {
			//printf("9  ");
			return bili(houxuguiji);
			
			


		}
		int biaoji = 0;
		for (int m = 0; m < jiaochadian_x.size(); m++) {

			if (jiaochadian_x[m] == j && jiaochadian_y[m] == i) {

				biaoji = 1;


			}

		}
		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 3 && biaoji == 1) {
			return bili(houxuguiji);
			


		}



		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 2 && biaoji != 1) {

			if (p2 == 1 && p - src.step != m) {

				//printf("2");
				houxuguiji.push_back(2);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p - src.step), p, i - 1, j);

			}
			if (p3 == 1 && (p - src.step + 1) != m && p2 != 1 && p4 != 1) {
				//printf("1");
				houxuguiji.push_back(1);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p - src.step + 1), p, i - 1, j + 1);

			}
			if (p4 == 1 && p + 1 != m) {
				//printf("0");
				houxuguiji.push_back(0);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}


				return zuobiao3(src, (p + 1), p, i, j + 1);

			}
			if (p5 == 1 && (p + src.step + 1) != m && p4 != 1 && p6 != 1) {
				//printf("7");
				houxuguiji.push_back(7);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p + src.step + 1), p, i + 1, j + 1);

			}
			if (p6 == 1 && p + src.step != m) {
				//printf("6");
				houxuguiji.push_back(6);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p + src.step), p, i + 1, j);


			}
			if (p7 == 1 && (p + src.step - 1) != m && p6 != 1 && p8 != 1) {
				//printf("5");
				houxuguiji.push_back(5);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}

				return zuobiao3(src, (p + src.step - 1), p, i + 1, j - 1);

			}
			if (p8 == 1 && (p - 1) != m) {
				//printf("4");
				houxuguiji.push_back(4);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}
				return zuobiao3(src, (p - 1), p, i, j - 1);


			}
			if (p9 == 1 && (p - src.step - 1) != m && p8 != 1 && p2 != 1) {
				//printf("3");
				houxuguiji.push_back(3);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili(houxuguiji);
				}
				return zuobiao3(src, (p - src.step - 1), p, i - 1, j - 1);

			}


		}
	}
	double zuobiao4(Mat & src, uchar *p, uchar *m, int i, int j) {

		int width = src.cols;//��
		int height = src.rows;//��
		uchar p1 = *p;
		if (p1 != 1) {
			return 0;
		}
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
				//printf("2");
				houxuguiji.push_back(2);
				houxubiaoji++;

				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p - src.step), p, i - 1, j);

			}
			if (p3 == 1 && (p - src.step + 1) != m) {
				//printf("1");
				houxuguiji.push_back(1);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p - src.step + 1), p, i - 1, j + 1);

			}

			if (p4 == 1 && (p + 1) != m) {
				//printf("0");
				houxuguiji.push_back(0);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}
				return zuobiao4(src, (p + 1), p, i, j + 1);
			}

			if (p5 == 1 && (p + src.step + 1) != m) {
				//printf("7");
				houxuguiji.push_back(7);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p + src.step + 1), p, i + 1, j + 1);

			}

			if (p6 == 1 && (p + src.step) != m) {
				//printf("6");
				houxuguiji.push_back(6);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}
				return zuobiao4(src, (p + src.step), p, i + 1, j);

			}

			if (p7 == 1 && (p + src.step - 1) != m) {
				//printf("5");
				houxuguiji.push_back(5);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p + src.step - 1), p, i + 1, j - 1);

			}

			if (p8 == 1 && (p - 1) != m) {
				houxuguiji.push_back(4);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p - 1), p, i, j - 1);

			}

			if (p9 == 1 && (p - src.step - 1) != m) {
				//printf("3");
				houxuguiji.push_back(3);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p - src.step - 1), p, i - 1, j - 1);

			}




		}
		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 1) {
			//printf("9  ");
			return bili2(houxuguiji);




		}
		int biaoji = 0;
		for (int m = 0; m < jiaochadian_x.size(); m++) {

			if (jiaochadian_x[m] == j && jiaochadian_y[m] == i) {

				biaoji = 1;


			}

		}
		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 3 && biaoji == 1) {
			return bili2(houxuguiji);



		}



		if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 2 && biaoji != 1) {

			if (p2 == 1 && p - src.step != m) {

				//printf("2");
				houxuguiji.push_back(2);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p - src.step), p, i - 1, j);

			}
			if (p3 == 1 && (p - src.step + 1) != m && p2 != 1 && p4 != 1) {
				//printf("1");
				houxuguiji.push_back(1);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p - src.step + 1), p, i - 1, j + 1);

			}
			if (p4 == 1 && p + 1 != m) {
				//printf("0");
				houxuguiji.push_back(0);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}


				return zuobiao4(src, (p + 1), p, i, j + 1);

			}
			if (p5 == 1 && (p + src.step + 1) != m && p4 != 1 && p6 != 1) {
				//printf("7");
				houxuguiji.push_back(7);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p + src.step + 1), p, i + 1, j + 1);

			}
			if (p6 == 1 && p + src.step != m) {
				//printf("6");
				houxuguiji.push_back(6);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p + src.step), p, i + 1, j);


			}
			if (p7 == 1 && (p + src.step - 1) != m && p6 != 1 && p8 != 1) {
				//printf("5");
				houxuguiji.push_back(5);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}

				return zuobiao4(src, (p + src.step - 1), p, i + 1, j - 1);

			}
			if (p8 == 1 && (p - 1) != m) {
				//printf("4");
				houxuguiji.push_back(4);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}
				return zuobiao4(src, (p - 1), p, i, j - 1);


			}
			if (p9 == 1 && (p - src.step - 1) != m && p8 != 1 && p2 != 1) {
				//printf("3");
				houxuguiji.push_back(3);
				houxubiaoji++;
				if (houxubiaoji == 10) {
					return bili2(houxuguiji);
				}
				return zuobiao4(src, (p - src.step - 1), p, i - 1, j - 1);

			}


		}
	}

	//�ж��ǲ�����
	int ifshu(vector<int> & guijii) {
		int zero = 0;
		int one = 0;
		int two = 0;
		int three = 0;
		int four = 0;
		int five = 0;
		int six = 0;
		int seven = 0;
		double sum = 0;
		
		for (int i = 0; i < guijii.size();i++) {
			sum++;
			if (guijii[i] == 0) {
				zero++;
			}
			if (guijii[i] == 1) {
				one++;
			}
			if (guijii[i] == 2) {
				two++;
			}
			if (guijii[i] == 3) {
				three++;
			}
			if (guijii[i] == 4) {
				four++;
			}
			if (guijii[i] == 5) {
				five++;
			}
			if (guijii[i] == 6) {
				six++;
			}
			if (guijii[i] == 7) {
				seven++;
			}
		}
		/*cout << "********************************" << endl;
		cout << zero << "," << one << "," << two << "," << three << "," << four << "," << five << "," << six << "," << seven << endl;
		cout << "********************************" << endl;*/
		if ((two>zero&&two>one&&two>three&&two>four&&two>five&&two>six&&two>seven&&guijii.size()>10)|| (two > zero&&two > one&&two > three&&two > four&&two > five&&two > six&&two > seven&&double(two)/sum>0.7)||(double(two+one)/sum>0.7&&double(two)/sum>0.3&&double(one)/sum>0.3) || (double(two + three) / sum > 0.7&&double(two) / sum > 0.3&&double(three) / sum > 0.3)) {
			return 2;
		}
		else if ((six > zero&&six > one&&six > three&&six > four&&six > five&&six > two&&six > seven&&guijii.size() > 10)|| (six > zero&&six > one&&six > three&&six > four&&six > five&&six > two&&six > seven&&double(six)/sum>0.7) || (double(six + five) / sum > 0.7&&double(six) / sum > 0.3&&double(five) / sum > 0.3) || (double(six + seven) / sum > 0.7&&double(six) / sum > 0.3&&double(seven) / sum > 0.3)) {
			return 6;
		}
		else {
			return 9;
		}
	}
	
	//�ж��ǲ��Ǻ�
	int ifheng(vector<int> & guijii) {
		int zero = 0;
		int one = 0;
		int two = 0;
		int three = 0;
		int four = 0;
		int five = 0;
		int six = 0;
		int seven = 0;
		double sum = 0;

		for (int i = 0; i < guijii.size(); i++) {
			sum++;
			if (guijii[i] == 0) {
				zero++;
			}
			if (guijii[i] == 1) {
				one++;
			}
			if (guijii[i] == 2) {
				two++;
			}
			if (guijii[i] == 3) {
				three++;
			}
			if (guijii[i] == 4) {
				four++;
			}
			if (guijii[i] == 5) {
				five++;
			}
			if (guijii[i] == 6) {
				six++;
			}
			if (guijii[i] == 7) {
				seven++;
			}
		}
		/*cout << "********************************" << endl;
		cout << zero << "," << one << "," << two << "," << three << "," << four << "," << five << "," << six << "," << seven << endl;
		cout << "********************************" << endl;*/
        if ((zero > two&&zero > one&&zero > three&&zero > four&&zero > five&&zero > six&&zero > seven&&guijii.size() > 10) || (zero > two&&zero > one&&zero > three&&zero > four&&zero > five&&zero > six&&zero > seven&&double(zero) / sum > 0.7) || (double(zero + one) / sum > 0.7&&double(zero) / sum > 0.4&&double(one) / sum > 0.3) || (double(zero + seven) / sum > 0.7&&double(zero) / sum > 0.4&&double(seven) / sum > 0.3)) {
			return 0;
		}
		else if ((four > zero&&four > one&&four > three&&four > six&&four > five&&four > two&&four > seven&&guijii.size() > 10) || (four > zero&&four > one&&four > three&&four > six&&four > five&&four > two&&four > seven&&double(four) / sum > 0.7) || (double(four + five) / sum > 0.7&&double(four) / sum > 0.4&&double(five) / sum > 0.3) || (double(four + three) / sum > 0.7&&double(four) / sum > 0.4&&double(three) / sum > 0.3)) {
			return 4;
		}
		else {
			return 9;
		}
		//���ֹ�С��

		/*if ((zero > two&&zero > one&&zero > three&&zero > four&&zero > five&&zero > six&&zero > seven&&guijii.size() > 10) || (zero > two&&zero > one&&zero > three&&zero > four&&zero > five&&zero > six&&zero > seven&&double(zero) / sum > 0.7&& guijii.size() > 6) || (double(zero + one) / sum > 0.7&&double(zero) / sum > 0.4&&double(one) / sum > 0.3&& guijii.size() > 6) || (double(zero + seven) / sum > 0.7&&double(zero) / sum > 0.4&&double(seven) / sum > 0.3&& guijii.size() > 6)) {
			return 0;
		}
		else if ((four > zero&&four > one&&four > three&&four > six&&four > five&&four > two&&four > seven&&guijii.size() > 10) || (four > zero&&four > one&&four > three&&four > six&&four > five&&four > two&&four > seven&&double(four) / sum > 0.7&& guijii.size() > 6) || (double(four + five) / sum > 0.7&&double(four) / sum > 0.4&&double(five) / sum > 0.3&& guijii.size() > 6) || (double(four + three) / sum > 0.7&&double(four) / sum > 0.4&&double(three) / sum > 0.3&& guijii.size() > 6)) {
			return 4;
		}
		else {
			return 9;
		}*/
	}
	
	Mat thinImage(Mat  src)
	{
		threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);
		Mat dst;
		
		int width = src.cols;
		int height = src.rows;

	


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
		//imshow("ϸ����ͼ��",dst);
		//waitKey(0);
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
		return dst;

		

	}
	//�жϽ������4��·����ʱ�� ���������·������һ����Ϊ����㣻
	int dian4jiaodianshu4(int i, int j, Mat &src) {
		int width = src.cols;//��
		int height = src.rows;//��
		uchar * p = src.ptr<uchar>(i);
		uchar p1 = p[j];
		if (p1 != 1) return 0;
		uchar p2 = (i == 0) ? 0 : *(p - src.step + j);
		uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - src.step + j + 1);
		uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
		uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + src.step + j + 1);
		uchar p6 = (i == height - 1) ? 0 : *(p + src.step + j);
		uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + src.step + j - 1);
		uchar p8 = (j == 0) ? 0 : *(p + j - 1);
		uchar p9 = (i == 0 || j == 0) ? 0 : *(p - src.step + j - 1);
		if ((p2 + p3 + p9) == 3) {
			return 1;

		}
		if ((p3 + p4 + p5) == 3) {
			return 1;

		}

		if ((p5 + p6 + p7) == 3) {
			return 1;

		}

		if ((p7 + p8 + p9) == 3) {
			return 1;

		}

		else return 0;



	}

	//�жϽ������3��·����ʱ�򣬱����������������������ڵ��Ѿ�Ϊ��������жϲ��ǽ����
	int dian3jiaochadianshu(int a, int b) {
		int count = 0;
		for (int i = 0; i < jiaochadian_x.size(); i++) {
			if (jiaochadian_x[i] == b && jiaochadian_y[i] == a) {
				count++;

			}
		}
		return count;

	}
	//�жϽ������3��·����ʱ�� ���������·������һ����Ϊ����㣻
	int dian3jiaochadianshu2(int i, int j, Mat &src) {
		int width = src.cols;//��
		int height = src.rows;//��
		uchar * p = src.ptr<uchar>(i);
		uchar p1 = p[j];
		if (p1 != 1) return 0;
		uchar p2 = (i == 0) ? 0 : *(p - src.step + j);
		uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - src.step + j + 1);
		uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
		uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + src.step + j + 1);
		uchar p6 = (i == height - 1) ? 0 : *(p + src.step + j);
		uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + src.step + j - 1);
		uchar p8 = (j == 0) ? 0 : *(p + j - 1);
		uchar p9 = (i == 0 || j == 0) ? 0 : *(p - src.step + j - 1);
		if ((p2 + p3) == 2) {
			return 1;

		}
		if ((p3 + p4) == 2) {
			return 1;

		}

		if ((p4 + p5) == 2) {
			return 1;

		}

		if ((p5 + p6) == 2) {
			return 1;

		}
		if ((p6 + p7) == 2) {
			return 1;

		}
		if ((p7 + p8) == 2) {
			return 1;

		}
		if ((p8 + p9) == 2) {
			return 1;

		}
		if ((p9 + p2) == 2) {
			return 1;

		}

		else return 0;



	}

	//�˵�ͽ����
	void endPointAndintersectionPointDetection(Mat & src, Mat & test)
	{
		
		threshold(src, src, 140, 1, cv::THRESH_BINARY_INV);
		int width = src.cols;//��
		int height = src.rows;//��
		vector<CvPoint> endpoint;
		vector<CvPoint> intersectionPoint;
		for (int i = 0; i < height; ++i) {
			uchar * r = src.ptr<uchar>(i);
			for (int j = 0; j < width; ++j) {
				uchar r1 = r[j];
				if (r1 == 1) {
					gujia2_x.push_back(j);
					gujia2_y.push_back(i);

				}


			}



		}
		for (int i = 0; i < height; ++i) {
			uchar * t = test.ptr<uchar>(i);
			for (int j = 0; j < width; ++j) {
				uchar t1 = t[j];
				if (t1 == 0) {
					test.at<uchar>(i, j) = 180;

				}


			}



		}
		for (int i = 0; i < gujia2_x.size(); i++) {
			test.at<uchar>(gujia2_y[i], gujia2_x[i]) = 1;

		}
		//111111111111111imshow("��ֵ����Ǽܺϲ�ͼ", test);
		//�������4��·���ж�
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
				//printf("%d", p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9);
				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 4)//�˵��ж�
				{
					printf("��4�����������صĵ㣺%d %d\n", j, i);
					int count4 = dian4jiaodianshu4(i, j, src);
					if (count4 == 0) {

						printf("�����4��%d %d\n", j, i);
						jiaochadian_x.push_back(j);
						jiaochadian_y.push_back(i);
					}

				}

			}
		}
		//���������·���ж�
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
				//printf("%d", p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9);
				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 3)//�˵��ж�
				{
					printf("��3�����������صĵ㣺%d %d\n", j, i);
					int count2 = dian3jiaochadianshu2(i, j, src);
					int count1 = dian3jiaochadianshu(i, j - 1) + dian3jiaochadianshu(i, j + 1) + dian3jiaochadianshu(i - 1, j) + dian3jiaochadianshu(i - 1, j + 1) + dian3jiaochadianshu(i - 1, j - 1) + dian3jiaochadianshu(i + 1, j) + dian3jiaochadianshu(i + 1, j - 1) + dian3jiaochadianshu(i + 1, j + 1);
					if (count1 == 0 && count2 == 0) {
						printf("�����3��%d %d\n", j, i);
						jiaochadian_x.push_back(j);
						jiaochadian_y.push_back(i);

					}

					//endpoint.push_back(cvPoint(j, i));
				}

			}
		}
		//�����˵�
		/*for (vector<CvPoint>::iterator i = endpoint.begin(); i != endpoint.end(); ++i)
		{
			circle(src, cvPoint(i->x, i->y), 5, Scalar(255), -1);
		}
		// ���������
		   for (vector<CvPoint>::iterator i = intersectionPoint.begin(); i != intersectionPoint.end(); ++i)
		   {
			   circle(src, cvPoint(i->x, i->y), 5, Scalar(255));
			   cvPoint(i->x, i->y) =255;
			   src.at<uchar>(i->x, i->y) = 255;
		   }*/
		   	endpoint.clear();//���ݻ���
			   intersectionPoint.clear();
			   for (int i = 0; i < jiaochadian_x.size(); i++) {
				   printf("���ս���㣺%d,%d\n", jiaochadian_x[i], jiaochadian_y[i]);

			   }
		   }
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
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(2);
					   tem_guiji.push_back(2);

					   zuobiao(src, (p - src.step), p, i - 1, j);

				   }
				   if (p3 == 1 && (p - src.step + 1) != m) {
					   printf("1");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(1);
					   tem_guiji.push_back(1);

					   zuobiao(src, (p - src.step + 1), p, i - 1, j + 1);

				   }

				   if (p4 == 1 && (p + 1) != m) {
					   printf("0");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(0);
					   tem_guiji.push_back(0);

					   zuobiao(src, (p + 1), p, i, j + 1);
				   }

				   if (p5 == 1 && (p + src.step + 1) != m) {
					   printf("7");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(7);
					   tem_guiji.push_back(7);

					   zuobiao(src, (p + src.step + 1), p, i + 1, j + 1);

				   }

				   if (p6 == 1 && (p + src.step) != m) {
					   printf("6");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(6);
					   tem_guiji.push_back(6);

					   zuobiao(src, (p + src.step), p, i + 1, j);

				   }

				   if (p7 == 1 && (p + src.step - 1) != m) {
					   printf("5");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(5);
					   tem_guiji.push_back(5);

					   zuobiao(src, (p + src.step - 1), p, i + 1, j - 1);

				   }

				   if (p8 == 1 && (p - 1) != m) {
					   printf("4");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(4);
					   tem_guiji.push_back(4);

					   zuobiao(src, (p - 1), p, i, j - 1);

				   }

				   if (p9 == 1 && (p - src.step - 1) != m) {
					   printf("3");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(3);
					   tem_guiji.push_back(3);

					   zuobiao(src, (p - src.step - 1), p, i - 1, j - 1);

				   }




			   }
			   if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 1) {
				   printf("9  ");
				   biaojishu++;
				   printf("�����㣺(%d,%d)\n", j, i);
				   guiji.push_back(9);
				   guiji_y.push_back(i);
				   guiji_x.push_back(j);
				   jieshudian_x.push_back(j);
				   jieshudian_y.push_back(i);
				   //�ж��ǲ�����
				   
				  
					   if (ifshu(tem_guiji) == 2) {
						   cout << "����" << endl;

						   biaojiifshu.push_back(biaojishu);
						   biaojiifshu2.push_back(1);


					   }
					   else if (ifshu(tem_guiji) == 6) {
						   cout << "����" << endl;

						   biaojiifshu.push_back(biaojishu);
						   biaojiifshu2.push_back(1);
					   }
					   else {
						   cout << "������" << endl;

						   biaojiifshu.push_back(biaojishu);
						   biaojiifshu2.push_back(0);

					   }
					   tem_guiji.clear();

				   
			   }
			   int biaoji = 0;
			   for (int m = 0; m < jiaochadian_x.size(); m++) {

				   if (jiaochadian_x[m] == j && jiaochadian_y[m] == i) {

					   biaoji = 1;


				   }

			   }
			   

			   if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 3 && biaoji == 1) {
				   
				 
				   if (ifshu(tem_guiji) == 9) {
					   printf("9  ");
					   biaojishu++;
					   printf("�����㣺(%d,%d)\n", j, i);
					   cout << "������" << endl;
					   tem_guiji.clear();
					   biaojiifshu2.push_back(0);
					   biaojiifshu.push_back(biaojishu);
					   guiji.push_back(9);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   jieshudian_x.push_back(j);
					   jieshudian_y.push_back(i);
				   }

				   //�ж��ǲ�����
				   else if (ifshu(tem_guiji) == 2) {
					   cout << "����" << endl;
					   bihuaduanbiaoji = 1;
					   tem_guiji.clear();

					   biaojiifshu2.push_back(1);
					   biaojiifshu.push_back(biaojishu);

					   if (p2 == 1 && (p - src.step) != m) {
						   printf("2");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(2);
						   tem_guiji.push_back(2);


						   zuobiao(src, (p - src.step), p, i - 1, j);

					   }
					   else if (p3 == 1 && (p - src.step + 1) != m && zuobiao3(src, (p - src.step + 1), p, i - 1, j + 1) > zuobiao3(src, (p - src.step - 1), p, i - 1, j - 1) && zuobiao3(src, (p - src.step + 1), p, i - 1, j + 1) > zuobiao3(src, (p - 1), p, i, j - 1)) {
						   printf("1");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(1);
						   tem_guiji.push_back(1);

						   zuobiao(src, (p - src.step + 1), p, i - 1, j + 1);
					   }
					   else  if (p9 == 1 && (p - src.step - 1) != m && zuobiao3(src, (p - src.step - 1), p, i - 1, j - 1) > zuobiao3(src, (p - src.step + 1), p, i - 1, j + 1) && zuobiao3(src, (p - src.step - 1), p, i - 1, j - 1) > zuobiao3(src, (p + 1), p, i, j + 1)) {

						   printf("3");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(3);
						   tem_guiji.push_back(3);

						   zuobiao(src, (p - src.step - 1), p, i - 1, j - 1);
					   }
					 
					   else {
						   printf("9  ");
						   biaojishu++;
						   printf("�����㣺(%d,%d)\n", j, i);

						   guiji.push_back(9);
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   jieshudian_x.push_back(j);
						   jieshudian_y.push_back(i);
					   }
				   }
				   else if (ifshu(tem_guiji) == 6) {
					 //cout << zuobiao3(src, (p + src.step - 1), p, i + 1, j - 1) << "-----" << zuobiao3(src, (p + src.step + 1), p, i + 1, j + 1) << "-----" << zuobiao3(src, (p + 1), p, i, j + 1) << endl;
					   cout << "����" << endl;
					   bihuaduanbiaoji = 1;
					   tem_guiji.clear();
					   biaojiifshu2.push_back(1);
					   biaojiifshu.push_back(biaojishu);
					   if (p6 == 1 && (p + src.step) != m) {
						   printf("6");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(6);
						   tem_guiji.push_back(6);

						   zuobiao(src, (p + src.step), p, i + 1, j);
					   }
				
					   else if (p7 == 1 && (p + src.step - 1) != m && zuobiao3(src, (p + src.step - 1), p, i + 1, j - 1) > zuobiao3(src, (p + src.step + 1), p, i + 1, j + 1) && zuobiao3(src, (p + src.step - 1), p, i + 1, j - 1) > zuobiao3(src, (p + 1), p, i, j + 1)) {
						   printf("5");
						   
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(5);
						   tem_guiji.push_back(5);

						   zuobiao(src, (p + src.step - 1), p, i + 1, j - 1);
					   }
					   else if (p5 == 1 && (p + src.step + 1) != m && zuobiao3(src, (p + src.step + 1), p, i + 1, j + 1) > zuobiao3(src, (p + src.step - 1), p, i + 1, j - 1) && zuobiao3(src, (p + src.step + 1), p, i + 1, j + 1) > zuobiao3(src, (p - 1), p, i, j - 1)) {
						   printf("7");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(7);
						   tem_guiji.push_back(7);

						   zuobiao(src, (p + src.step + 1), p, i + 1, j + 1);
					   }
					   /* else if (p5 == 1 && (p + src.step + 1) != m && p7 != 1 && p6 != 1) {
							printf("7");
							biaojishu++;
							guiji_y.push_back(i);
							guiji_x.push_back(j);
							guiji.push_back(7);
							tem_guiji.push_back(7);

							zuobiao(src, (p + src.step + 1), p, i + 1, j + 1);
						}*/
					   else {
						   printf("9  ");
						   biaojishu++;
						   printf("�����㣺(%d,%d)\n", j, i);
						   guiji.push_back(9);
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   jieshudian_x.push_back(j);
						   jieshudian_y.push_back(i);
					   }
				   }
				   else {
					   cout << "������" << endl;
					   biaojiifshu2.push_back(0);
					   biaojiifshu.push_back(biaojishu);
					   tem_guiji.clear();
				  }
			   
			   
			   }



			   if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 2 && biaoji != 1) {

				   if (p2 == 1 && p - src.step != m) {

					   printf("2");
					   biaojishu++;
					   guiji.push_back(2);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					  // guiji.push_back(2);
					   tem_guiji.push_back(2);
					   
					   zuobiao(src, (p - src.step), p, i - 1, j);
					   
				   }
				   if (p3 == 1 && (p - src.step + 1) != m&&p2!=1&&p4!=1) {
					   printf("1");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(1);
					   tem_guiji.push_back(1);

					   zuobiao(src, (p - src.step + 1), p, i - 1, j + 1);

				   }
				   if (p4 == 1 && p + 1 != m) {
					   printf("0");
					   biaojishu++;
					   guiji.push_back(0);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   //guiji.push_back(0);
					   tem_guiji.push_back(0);
                       

					   zuobiao(src, (p + 1), p, i, j + 1);
					   
				   }
				   if (p5 == 1 && (p + src.step + 1) != m&&p4!=1&&p6!=1) {
					   printf("7");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(7);
					   tem_guiji.push_back(7);

					   zuobiao(src, (p + src.step + 1), p, i + 1, j + 1);

				   }
				   if (p6 == 1 && p + src.step != m) {
					   printf("6");
					   biaojishu++;
					   guiji.push_back(6);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					  // guiji.push_back(6);
					   tem_guiji.push_back(6);
                      
					   zuobiao(src, (p + src.step), p, i + 1, j);
					   

				   }
				   if (p7 == 1 && (p + src.step - 1) != m&&p6!=1&&p8!=1) {
					   printf("5");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(5);
					   tem_guiji.push_back(5);

					   zuobiao(src, (p + src.step - 1), p, i + 1, j - 1);

				   }
				   if (p8 == 1 && (p - 1) != m) {
					   printf("4");
					   biaojishu++;
					   guiji.push_back(4);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					  // guiji.push_back(4);
					   tem_guiji.push_back(4);
                       //cout << "dd";
					   zuobiao(src, (p - 1), p, i, j - 1);
					   

				   }
				  if (p9 == 1 && (p - src.step - 1) != m&&p8!=1&&p2!=1) {
					  printf("3");
					  biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(3);
					   tem_guiji.push_back(3);
					   //cout << "dd";
					   zuobiao(src, (p - src.step - 1), p, i - 1, j - 1);

				   }


			   }


		   }
		   void xunhuan(Mat & src,Mat &dst,Mat & cloo,vector<double> & bihuaxinxi) {
			   Mat clo = cloo.clone();
			   threshold(clo, clo, 140, 1, cv::THRESH_BINARY_INV);

			   int dijibi = 1;
			   int width = src.cols;//��
			   int height = src.rows;//��
			   biaojiifshu.push_back(0);
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
							   //����Ǳʻ��ڼ��Σ���ͬ�Ķ��ò��ж����ķ���
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(2);
							   tem_guiji.push_back(2);
							   biaojishu++;
							   printf("2");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p - src.step + j), p + j, i - 1, j);

						   }
						   if (p3 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(1);
							   tem_guiji.push_back(1);
							   printf("1");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p - src.step + j + 1), p + j, i - 1, j + 1);

						   }

						   if (p4 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(0);
							   tem_guiji.push_back(0);
							   printf("0");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + j + 1), p + j, i, j + 1);
						   }

						   if (p5 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(7);
							   tem_guiji.push_back(7);
							   printf("7");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j + 1), p + j, i + 1, j + 1);

						   }

						   if (p6 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(6);
							   tem_guiji.push_back(6);
							   printf("6");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j), p + j, i + 1, j);

						   }

						   if (p7 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(5);
							   tem_guiji.push_back(5);
							   printf("5");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j - 1), p + j, i + 1, j - 1);

						   }

						   if (p8 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(4);
							   tem_guiji.push_back(4);
							   printf("4");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + j - 1), p + j, i, j - 1);

						   }

						   if (p9 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(3);
							   tem_guiji.push_back(3);
							   printf("3");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p - src.step + j - 1), p + j, i - 1, j - 1);

						   }






					   }



				   }
			   }
			   printf("*********************************************************************************************************************\n");
			   int bihua[4092][9];//{�ڼ��ʣ��켣���˵�x���˵�y��������x��������y,�켣x���켣y���ʻ����}
			   int  bihuaxuhao = 1;
			   int vectorxuhao = 0;
			   //guiji.push_back(8);
			   //guiji_x.push_back(8);
			   //guiji_y.push_back(8);



			   for (int i = 0; i < guiji.size(); i++) {
				   for (int j = 0; j < 9; j++) {



					   if (guiji[i] == 9 && j == 0) {


						   bihua[i][j] = bihuaxuhao;
						   bihuaxuhao++;

					   }
					   if (guiji[i] != 9 && j == 0) {
						   bihua[i][j] = bihuaxuhao;


					   }
					   if (j == 1) {
						   bihua[i][j] = guiji[i];
						   //printf("*%d", vectorxuhao);

						   vectorxuhao++;


					   }


					   if (j == 2) {
						   bihua[i][j] = 0;

					   }


					   if (j == 3) {
						   bihua[i][j] = 0;


					   }

					   if (j == 4) {
						   bihua[i][j] = 0;


					   }
					   if (j == 5) {
						   bihua[i][j] = 0;


					   }
					   if (j == 6) {

						   bihua[i][j] = guiji_x[i];

					   }
					   if (j == 7) {

						   bihua[i][j] = guiji_y[i];

					   }
					   if (j == 8) {

						   //bihua[i][j] = 0;

					   }



				   }
			   }
			   int bihuabiaoji = 0;
			   for (int j = 0; j < duandian_x.size(); j++) {
				   for (int i = 0; i < guiji.size(); i++) {
					   if (j + 1 == bihua[i][0]) {
						   bihua[i][2] = duandian_x[j];
						   bihua[i][3] = duandian_y[j];
						   bihua[i][4] = jieshudian_x[j];
						   bihua[i][5] = jieshudian_y[j];

					   }


				   }
			   }
			   for (int i = 0; i < biaojiifshu2.size();i++) {
				   if (biaojiifshu2[i]==1) {
					   for (int j = biaojiifshu[i]; j < biaojiifshu[i + 1];j++) {
						   bihua[j][8] = 1;
					   }
				   }
			   }
			   //�ѱʻ�����С��20��ȥ��
			  int bihuaxuhao2 = 1;
			   vector<int>bihuaduanxuhao;
			   bihuaduanxuhao.push_back(0);
			  // bihuaduanxuhao.push_back(guiji.size()-1);`
			   for (int i = 0; i < guiji.size();i++) {
				   if (bihua[i][1]==9) {
					   
					   bihuaduanxuhao.push_back(i+1);
				   }
			   }
			
			   for (int i = 1; i < bihuaduanxuhao.size(); i++) {
				   if (bihuaduanxuhao[i]-bihuaduanxuhao[i-1]<50) {
					   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i];j++) {   
						   bihua[j][8] = 0;
					   }
				   }
			          
			   }
			   //�ʻ���ת
			   for (int i = 1; i < bihuaduanxuhao.size(); i++) {
				   double zero = 1;
				   double one = 1;
				   double two = 1;
				   double three = 1;
				   double four = 1;
				   double five = 1;
				   double six = 1;
				   double seven = 1;
				  
				   if (bihua[bihuaduanxuhao[i-1]][8]==1) {
					   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i]; j++) {
						   if (bihua[j][1] == 0) {
							   zero++;
						   }
						   if (bihua[j][1] == 1) {
							   one++;
						   }
						   if (bihua[j][1] == 2) {
							   two++;
						   }
						   if (bihua[j][1] == 3) {
							   three++;
						   }
						   if (bihua[j][1] == 4) {
							   four++;
						   }
						   if (bihua[j][1] == 5) {
							   five++;
						   }
						   if (bihua[j][1] == 6) {
							   six++;
						   }
						   if (bihua[j][1] == 7) {
							   seven++;
						   }
					   }
					   if (two > six) {


						   int biaoji = 0;
						   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1] - 1) / 2; j++) {

							   for (int m = 0; m < 8; m++) {

								   int temp = bihua[j][m];
								   bihua[j][m] = bihua[bihuaduanxuhao[i] - 1 - biaoji][m];
								   bihua[bihuaduanxuhao[i] - 1 - biaoji][m] = temp;
							   }
							   biaoji++;
						   }
					   }
				   }

			   }

			 



			   for (int i = 0; i < guiji.size(); i++) {
				   printf("���-%d����%d�ʣ��켣��%d,�˵����꣨%d,%d��,���������꣨%d,%d��,�켣���꣨%d,%d�����ʻ����ţ���%d��\n",i, bihua[i][0], bihua[i][1], bihua[i][2], bihua[i][3], bihua[i][4], bihua[i][5], bihua[i][6], bihua[i][7], bihua[i][8]);
			   }

			   int ifcunzaiheng = 0;
			   for (int i = 0; i < guiji.size(); i++) {
				   if (bihua[i][8] == 1) {
					   ifcunzaiheng = 1;
					   break;
				   }

			   }
			   if (ifcunzaiheng == 1) {
				   //����ʻ��رʻ�б��
				   vector<double> bihuashang;
				   vector<double> xielv;
				   vector<double> start_xielv;
				   vector<double> end_xielv;

				   for (int i = 1; i < bihuaduanxuhao.size(); i++) {
					   double zero = 1;
					   double one = 1;
					   double two = 1;
					   double three = 1;
					   double four = 1;
					   double five = 1;
					   double six = 1;
					   double seven = 1;

					   if (bihua[bihuaduanxuhao[i - 1]][8] == 1) {
						   //����ʻ���
						   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i]; j++) {
							   if (bihua[j][1] == 0) {
								   zero++;
							   }
							   if (bihua[j][1] == 1) {
								   one++;
							   }
							   if (bihua[j][1] == 2) {
								   two++;
							   }
							   if (bihua[j][1] == 3) {
								   three++;
							   }
							   if (bihua[j][1] == 4) {
								   four++;
							   }
							   if (bihua[j][1] == 5) {
								   five++;
							   }
							   if (bihua[j][1] == 6) {
								   six++;
							   }
							   if (bihua[j][1] == 7) {
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
						   double sd0 = zero / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd1 = one / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd2 = two / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd3 = three / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd4 = four / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd5 = five / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd6 = six / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd7 = seven / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);

						   //��ʾ�ʻ���sd
						   cout << "�ܱʻ���" << bihuaduanxuhao[i] - bihuaduanxuhao[i - 1] << endl;
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
						   bihuashang.push_back(Es);
						   cout << "�ʻ���:" << Es << endl;
						   //���ʻ���б��
						   double start_x = bihua[bihuaduanxuhao[i - 1]][6];
						   double start_y = bihua[bihuaduanxuhao[i - 1]][7];;
						   double end_x = bihua[bihuaduanxuhao[i] - 1][6];;
						   double end_y = bihua[bihuaduanxuhao[i] - 1][7];;
						   cout << "start_x-" << start_x << endl;
						   cout << "start_y-" << start_y << endl;
						   cout << "end_x-" << end_x << endl;
						   cout << "end_y-" << end_y << endl;
						   double xielv_k = DBL_MAX;
						   if (end_x != start_x) {
							   xielv_k = (end_y - start_y) / (end_x - start_x);

						   }
						   xielv.push_back(xielv_k);
						   cout << "б��:" << xielv_k << endl;
						   //����ʻ��ʼ���֮һб��
						   double start_1_5x = bihua[bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5][6];
						   // cout << "----------" << bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5 <<endl;
						   double start_1_5y = bihua[bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5][7];

						   cout << "start_1_5x:" << start_1_5x << endl;
						   cout << "start_1_5y:" << start_1_5y << endl;
						   double xielv_start = DBL_MAX;
						   if (start_1_5x != start_x) {
							   xielv_start = (start_1_5y - start_y) / (start_1_5x - start_x);

						   }
						   start_xielv.push_back(xielv_start);
						   cout << "�ʼ���֮һб��:" << xielv_start << endl;

						   //����ʻ��������֮һб��
						   double end_1_5x = bihua[bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5 * 4][6];
						   double end_1_5y = bihua[bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5 * 4][7];

						   cout << "end_1_5x" << end_1_5x << endl;
						   cout << "end_1_5y" << end_1_5y << endl;
						   double xielv_end = DBL_MAX;
						   if (end_x != end_1_5x) {
							   xielv_end = (end_y - end_1_5y) / (end_x - end_1_5x);

						   }
						   end_xielv.push_back(xielv_end);
						   cout << "�������֮һб��:" << xielv_end << endl;


					   }
				   }
				   double bihuashang_count = 0;
				   double xielv_count = 0;
				   double start_xielv_count = 0;
				   double end_xielv_count = 0;
				   for (int i = 0; i < bihuashang.size(); i++) {
					   bihuashang_count += bihuashang[i];
					   xielv_count += xielv[i];
					   start_xielv_count += start_xielv[i];
					   end_xielv_count += end_xielv[i];

				   }
				   cout << "ƽ���ʻ���:" << bihuashang_count / bihuashang.size() << endl;
				   cout << "ƽ��б��:" << xielv_count / bihuashang.size() << endl;
				   cout << "ƽ����ʼб��:" << start_xielv_count / bihuashang.size() << endl;
				   cout << "ƽ������б��:" << end_xielv_count / bihuashang.size() << endl;
				   bihuaxinxi.push_back(bihuashang_count / bihuashang.size());
				   bihuaxinxi.push_back(xielv_count / bihuashang.size());
				   bihuaxinxi.push_back(start_xielv_count / bihuashang.size());
				   bihuaxinxi.push_back(end_xielv_count / bihuashang.size());


				   /* Mat show = Mat::zeros(Size(width, height), CV_8UC3);
					show = Scalar(255, 255, 255);
				   dst = dst * 255;
					bitwise_not(dst, dst);
					//threshold(dst, dst, 140, 1, cv::THRESH_BINARY_INV);*/

					//����ʻ��ֶ�������
				   int bihualeixinshuzu[4];
				   bihualeixinshuzu[0] = 0;
				   bihualeixinshuzu[1] = 0;
				   bihualeixinshuzu[2] = 0;
				   bihualeixinshuzu[3] = 0;
				   int shubihuaxuhao = 1;
				   double bihuatype = 0;
				   for (int i = 1; i < bihuaduanxuhao.size(); i++) {


					   if (bihua[bihuaduanxuhao[i - 1]][8] == 1) {
						   vector<int>xihuaguiji_x;
						   vector<int>xihuaguiji_y;

						   vector<double> cudu;
						   cout << "��" << shubihuaxuhao << "���ʻ�" << endl;
						   shubihuaxuhao++;
						   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i]; j++) {
							   xihuaguiji_x.push_back(bihua[j][6]);
							   xihuaguiji_y.push_back(bihua[j][7]);
						   }
						   for (int i = 0; i < xihuaguiji_x.size(); i++) {
							   //cout << "aaaa";
							   int radius = 1;
							   double threshold = 1;
							   while (threshold >= 0.95) {
								   double black = 0;
								   double all = 0;
								   int start_x = xihuaguiji_x[i] - radius;
								   int end_x = xihuaguiji_x[i] + radius;
								   int start_y = xihuaguiji_y[i] - radius;
								   int end_y = xihuaguiji_y[i] + radius;
								   if (start_x <= 0) {
									   start_x = 0;

								   }
								   if (end_x >= width) {
									   end_x = width;
								   }
								   if (start_y <= 0) {
									   start_y = 0;
								   }
								   if (end_y >= height) {
									   end_y = height;
								   }
								   for (int m = start_y; m < end_y; m++) {
									   uchar * q = clo.ptr<uchar>(m);
									   for (int n = start_x; n < end_x; n++) {
										   uchar q1 = q[n];
										   if (((n - xihuaguiji_x[i])*(n - xihuaguiji_x[i]) + (m - xihuaguiji_y[i])*(m - xihuaguiji_y[i])) <= radius * radius) {
											   all++;
											   if (q1 == 1) {
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
						   //ǰһ��ֶ�
						   double startcudu = 0;
						   double cudujishu = 0;
						   for (int i = 0; i < cudu.size() / 2; i++) {
							   cudujishu++;
							   cout << cudu[i] << ",";
							   startcudu += cudu[i];

						   }
						   cout << endl;
						   cout << "ǰһ��ֶ�:" << startcudu << "----" << cudujishu << "-----" << startcudu / cudujishu << endl;
						   //��һ��ֶ�
						   double endcudu = 0;
						   for (int i = cudu.size() / 2; i < cudu.size(); i++) {
							   cout << cudu[i] << ",";
							   endcudu += cudu[i];

						   }
						   cout << endl;
						   cout << "��һ��ֶ�:" << endcudu << "----" << cudujishu << "-----" << endcudu / cudujishu << endl;
						   //�жϺ󲿷ֱʻ�ϸ����x����������ʻ�x�������߻����ұ�
						   double end5_1_xihuaguijia_x = 0;
						   double xjisu = 0;
						   for (int i = xihuaguiji_x.size() / 5 * 4; i < xihuaguiji_x.size(); i++) {
							   xjisu++;
							   end5_1_xihuaguijia_x += xihuaguiji_x[i];

						   }
						   cout << "�����֮һxֵ��" << end5_1_xihuaguijia_x / xjisu << endl;

						   double end_xihuaguijia_x = 0;
						   for (int i = xihuaguiji_x.size() / 2; i < xihuaguiji_x.size(); i++) {
							   end_xihuaguijia_x += xihuaguiji_x[i];

						   }
						   cout << "��һ��xֵ��" << end_xihuaguijia_x / cudujishu << endl;
						   //�жϺ����֮һ�����Ƿ��𽥱�ϸ
						   double ifbianxi = 0;
						   double cudubianhua = 0;
						   double cudubianhuajishu = 0;
						   for (int i = cudu.size() / 6 * 5; i < cudu.size(); i++) {
							   cudubianhuajishu++;
							   if (cudu[i] < cudu[i - 1]) {
								   cudubianhua += 2;

							   }
							   else if (cudu[i] = cudu[i - 1]) {
								   cudubianhua += 1;
							   }
							   else {
								   cudubianhua -= 2;
							   }




						   }
						   if (cudubianhua > cudubianhuajishu&&cudu[cudu.size() - 1] <= 4) {
							   ifbianxi = 1;
						   }

						   cout << "�Ƿ��𽥱�ϸ:" << cudubianhua << "---------" << cudubianhuajishu << "----------" << ifbianxi << endl;

						   if (startcudu < endcudu&&end5_1_xihuaguijia_x / xjisu < end_xihuaguijia_x / cudujishu) {
							   bihuatype = 1;
							   bihualeixinshuzu[1]++;
							   cout << "��¶��" << endl;

						   }
						   else if (startcudu < endcudu&&end5_1_xihuaguijia_x / xjisu > end_xihuaguijia_x / cudujishu) {
							   bihuatype = 2;
							   bihualeixinshuzu[2]++;
							   cout << "�Ҵ�¶��" << endl;
						   }
						   else if (startcudu > endcudu&&ifbianxi == 1) {
							   bihuatype = 3;
							   bihualeixinshuzu[3]++;
							   cout << "������" << endl;
						   }
						   else {
							   cout << "ɶ�ʻ�������" << endl;
						   }



					   }
				   }
				   cout << bihualeixinshuzu[1] << "----" << bihualeixinshuzu[2] << "----" << bihualeixinshuzu[3];
				   if (bihualeixinshuzu[1] != 0 && bihualeixinshuzu[2] != 0 && bihualeixinshuzu[3] != 0) {
					   bihuaxinxi.push_back(6);
				   }
				   else if (bihualeixinshuzu[1] != 0 && bihualeixinshuzu[2] != 0) {
					   bihuaxinxi.push_back(5);
				   }
				   else if (bihualeixinshuzu[1] != 0 && bihualeixinshuzu[3] != 0) {
					   bihuaxinxi.push_back(4);
				   }
				   else if (bihualeixinshuzu[2] != 0 && bihualeixinshuzu[3] != 0) {
					   bihuaxinxi.push_back(3);
				   }
				   else if (bihualeixinshuzu[1] != 0) {
					   bihuaxinxi.push_back(2);

				   }
				   else if (bihualeixinshuzu[2] != 0) {
					   bihuaxinxi.push_back(1);

				   }
				   else if (bihualeixinshuzu[3] != 0) {
					   bihuaxinxi.push_back(0);

				   }
				   else {
					   bihuaxinxi.push_back(7);
				   }

			   }
			   else {
			   bihuaxinxi.push_back(0);
			   bihuaxinxi.push_back(0);
			   bihuaxinxi.push_back(0);
			   bihuaxinxi.push_back(0);
			   bihuaxinxi.push_back(7);
                     }
			   dst = dst * 255;
			   bitwise_not(dst, dst);
			   Mat three_channel = Mat::zeros(dst.rows, dst.cols, CV_8UC3);
			   vector<Mat> channels;
			   for (int i = 0; i < 3; i++)
			   {
				   channels.push_back(dst);
			   }
			   merge(channels, three_channel);
			
			  
			  
			 //  imshow("aaa", three_channel);
			 //  waitKey(0);

			   int color_1[3] = { 255,255,0 };
			   int color_2[3] = { 0,0,0 };
			  

			   for (int i = 0; i < guiji.size(); i++) {
				   if (bihua[i][8] == 1) {
					   three_channel.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_1[0];
					   three_channel.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_1[1];
					   three_channel.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_1[2];

				   }
				  /* if (bihua[i][8] != 1) {

					   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_2[0];
					   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_2[1];
					   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_2[2];

				   }*/
			   }
			   imshow("aaa", three_channel);
			   imwrite("D:/����֮�ֿ�/��ͨ��ͼ.jpg", three_channel);
			   waitKey(0);
		   }
		  
		   //�����*******************************************************
		   void zuobiao2(Mat & src, uchar *p, uchar *m, int i, int j) {

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
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(2);
					   tem_guiji.push_back(2);

					   zuobiao2(src, (p - src.step), p, i - 1, j);

				   }
				   if (p3 == 1 && (p - src.step + 1) != m) {
					   printf("1");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(1);
					   tem_guiji.push_back(1);

					   zuobiao2(src, (p - src.step + 1), p, i - 1, j + 1);

				   }

				   if (p4 == 1 && (p + 1) != m) {
					   printf("0");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(0);
					   tem_guiji.push_back(0);

					   zuobiao2(src, (p + 1), p, i, j + 1);
				   }

				   if (p5 == 1 && (p + src.step + 1) != m) {
					   printf("7");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(7);
					   tem_guiji.push_back(7);

					   zuobiao2(src, (p + src.step + 1), p, i + 1, j + 1);

				   }

				   if (p6 == 1 && (p + src.step) != m) {
					   printf("6");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(6);
					   tem_guiji.push_back(6);

					   zuobiao2(src, (p + src.step), p, i + 1, j);

				   }

				   if (p7 == 1 && (p + src.step - 1) != m) {
					   printf("5");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(5);
					   tem_guiji.push_back(5);

					   zuobiao2(src, (p + src.step - 1), p, i + 1, j - 1);

				   }

				   if (p8 == 1 && (p - 1) != m) {
					   printf("4");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(4);
					   tem_guiji.push_back(4);

					   zuobiao2(src, (p - 1), p, i, j - 1);

				   }

				   if (p9 == 1 && (p - src.step - 1) != m) {
					   printf("3");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(3);
					   tem_guiji.push_back(3);

					   zuobiao2(src, (p - src.step - 1), p, i - 1, j - 1);

				   }




			   }
			   if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 1) {
				   printf("9  ");
				   biaojishu++;
				   printf("�����㣺(%d,%d)\n", j, i);
				   guiji.push_back(9);
				   guiji_y.push_back(i);
				   guiji_x.push_back(j);
				   jieshudian_x.push_back(j);
				   jieshudian_y.push_back(i);
				   //�ж��ǲ�����


				   if (ifheng(tem_guiji) == 0) {
					   cout << "�Ǻ�" << endl;

					   biaojiifshu.push_back(biaojishu);
					   biaojiifshu2.push_back(1);


				   }
				   else if (ifheng(tem_guiji) == 4) {
					   cout << "�Ǻ�" << endl;

					   biaojiifshu.push_back(biaojishu);
					   biaojiifshu2.push_back(1);
				   }
				   else {
					   cout << "���Ǻ�" << endl;

					   biaojiifshu.push_back(biaojishu);
					   biaojiifshu2.push_back(0);

				   }
				   tem_guiji.clear();


			   }
			   int biaoji = 0;
			   for (int m = 0; m < jiaochadian_x.size(); m++) {

				   if (jiaochadian_x[m] == j && jiaochadian_y[m] == i) {

					   biaoji = 1;


				   }

			   }


			   if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 3 && biaoji == 1) {


				   if (ifheng(tem_guiji) == 9) {
					   printf("9  ");
					   biaojishu++;
					   printf("�����㣺(%d,%d)\n", j, i);
					   cout << "���Ǻ�" << endl;
					   tem_guiji.clear();
					   biaojiifshu2.push_back(0);
					   biaojiifshu.push_back(biaojishu);
					   guiji.push_back(9);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   jieshudian_x.push_back(j);
					   jieshudian_y.push_back(i);
				   }

				   //�ж��ǲ��Ǻ�
				   else if (ifheng(tem_guiji) == 0) {
					   cout << "�Ǻ�" << endl;
					   bihuaduanbiaoji = 1;
					   tem_guiji.clear();

					   biaojiifshu2.push_back(1);
					   biaojiifshu.push_back(biaojishu);

					   if (p4 == 1 && (p + 1) != m) {
						   printf("0");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(0);
						   tem_guiji.push_back(0);


						   zuobiao2(src, (p + 1), p, i, j + 1);

					   }
					   else if (p3 == 1 && (p - src.step + 1) != m && zuobiao4(src, (p - src.step + 1), p, i - 1, j + 1) > zuobiao4(src, (p + src.step + 1), p, i + 1, j + 1) && zuobiao4(src, (p - src.step + 1), p, i - 1, j + 1) > zuobiao4(src, (p + src.step), p, i + 1, j)) {
						   printf("1");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(1);
						   tem_guiji.push_back(1);

						   zuobiao2(src, (p - src.step + 1), p, i - 1, j + 1);
					   }
					   else  if (p5 == 1  && (p + src.step + 1) != m &&zuobiao4(src, (p + src.step + 1), p, i + 1, j + 1) > zuobiao4(src, (p - src.step), p, i - 1, j) && zuobiao4(src, (p + src.step + 1), p, i + 1, j + 1) > zuobiao4(src, (p - src.step + 1), p, i - 1, j + 1)) {

						   printf("7");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(7);
						   tem_guiji.push_back(7);

						   zuobiao2(src,  (p + src.step + 1), p, i + 1, j + 1);
					   }
					   else if (p2==1&& (p - src.step) != m&&p3!=1&&p5!=1&&zuobiao4(src, (p - src.step), p, i - 1, j)>zuobiao4(src, (p + src.step), p, i + 1, j)) {
					   printf("2");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(2);
					   tem_guiji.push_back(2);

					   zuobiao2(src, (p - src.step), p, i - 1, j);
                                 }
					   else if (p6 == 1 && (p+ src.step) != m && p3 != 1 && p5 != 1 && zuobiao4(src, (p - src.step), p, i - 1, j) < zuobiao4(src, (p + src.step), p, i + 1, j)) {
						   printf("6");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(6);
						   tem_guiji.push_back(6);

						   zuobiao2(src, (p + src.step), p, i + 1, j);
					   }

					   else {
						   printf("9  ");
						   biaojishu++;
						   printf("�����㣺(%d,%d)\n", j, i);

						   guiji.push_back(9);
						   guiji_y.push_back(i);
 						   guiji_x.push_back(j);
						   jieshudian_x.push_back(j);
						   jieshudian_y.push_back(i);
					   }
				   }
				   else if (ifheng(tem_guiji) == 4) {
					   //cout << zuobiao3(src, (p + src.step - 1), p, i + 1, j - 1) << "-----" << zuobiao3(src, (p + src.step + 1), p, i + 1, j + 1) << "-----" << zuobiao3(src, (p + 1), p, i, j + 1) << endl;
					   cout << "�Ǻ�" << endl;
					   bihuaduanbiaoji = 1;
					   tem_guiji.clear();
					   biaojiifshu2.push_back(1);
					   biaojiifshu.push_back(biaojishu);
					   if (p8 == 1 && (p - 1) != m) {
						   printf("4");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(4);
						   tem_guiji.push_back(4);

						   zuobiao2(src, (p - 1), p, i, j - 1);
					   }

					   else if (p7 == 1 && (p + src.step - 1) != m && zuobiao4(src, (p + src.step - 1), p, i + 1, j - 1) > zuobiao4(src, (p - src.step - 1), p, i - 1, j - 1) && zuobiao4(src, (p + src.step - 1), p, i + 1, j - 1) > zuobiao4(src, (p - src.step), p, i - 1, j)) {
						   printf("5");

						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(5);
						   tem_guiji.push_back(5);

						   zuobiao2(src, (p + src.step - 1), p, i + 1, j - 1);
					   }
					   else if (p9 == 1 && (p - src.step - 1) != m && zuobiao4(src, (p - src.step - 1), p, i - 1, j - 1) > zuobiao4(src, (p + src.step - 1), p, i + 1, j - 1) && zuobiao4(src, (p - src.step - 1), p, i - 1, j - 1) > zuobiao4(src, (p + src.step), p, i + 1, j)) {
						   printf("3");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(3);
						   tem_guiji.push_back(3);

						   zuobiao2(src, (p - src.step - 1), p, i - 1, j - 1);
					   }
					   else if (p2 == 1 && (p - src.step) != m && p7!= 1 && p9 != 1 && zuobiao4(src, (p - src.step), p, i - 1, j) > zuobiao4(src, (p + src.step), p, i + 1, j)) {
						   printf("2");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(2);
						   tem_guiji.push_back(2);

						   zuobiao2(src, (p - src.step), p, i - 1, j);
					   }
					   else if (p6 == 1 && (p + src.step) != m && p7 != 1 && p9 != 1 && zuobiao4(src, (p - src.step), p, i - 1, j) < zuobiao4(src, (p + src.step), p, i + 1, j)) {
						   printf("6");
						   biaojishu++;
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   guiji.push_back(6);
						   tem_guiji.push_back(6);

						   zuobiao2(src, (p + src.step), p, i + 1, j);
					   }
					   else {
						   printf("9  ");
						   biaojishu++;
						   printf("�����㣺(%d,%d)\n", j, i);
						   guiji.push_back(9);
						   guiji_y.push_back(i);
						   guiji_x.push_back(j);
						   jieshudian_x.push_back(j);
						   jieshudian_y.push_back(i);
					   }
				   }
				   else {
					   cout << "���Ǻ�" << endl;
					   biaojiifshu2.push_back(0);
					   biaojiifshu.push_back(biaojishu);
					   tem_guiji.clear();
				   }


			   }



			   if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 2 && biaoji != 1) {

				   if (p2 == 1 && p - src.step != m) {

					   printf("2");
					   biaojishu++;
					   guiji.push_back(2);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   // guiji.push_back(2);
					   tem_guiji.push_back(2);

					   zuobiao2(src, (p - src.step), p, i - 1, j);

				   }
				   if (p3 == 1 && (p - src.step + 1) != m && p2 != 1 && p4 != 1) {
					   printf("1");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(1);
					   tem_guiji.push_back(1);

					   zuobiao2(src, (p - src.step + 1), p, i - 1, j + 1);

				   }
				   if (p4 == 1 && p + 1 != m) {
					   printf("0");
					   biaojishu++;
					   guiji.push_back(0);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   //guiji.push_back(0);
					   tem_guiji.push_back(0);


					   zuobiao2(src, (p + 1), p, i, j + 1);

				   }
				   if (p5 == 1 && (p + src.step + 1) != m && p4 != 1 && p6 != 1) {
					   printf("7");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(7);
					   tem_guiji.push_back(7);

					   zuobiao2(src, (p + src.step + 1), p, i + 1, j + 1);

				   }
				   if (p6 == 1 && p + src.step != m) {
					   printf("6");
					   biaojishu++;
					   guiji.push_back(6);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   // guiji.push_back(6);
					   tem_guiji.push_back(6);

					   zuobiao2(src, (p + src.step), p, i + 1, j);


				   }
				   if (p7 == 1 && (p + src.step - 1) != m && p6 != 1 && p8 != 1) {
					   printf("5");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(5);
					   tem_guiji.push_back(5);

					   zuobiao2(src, (p + src.step - 1), p, i + 1, j - 1);

				   }
				   if (p8 == 1 && (p - 1) != m) {
					   printf("4");
					   biaojishu++;
					   guiji.push_back(4);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   // guiji.push_back(4);
					   tem_guiji.push_back(4);
					   //cout << "dd";
					   zuobiao2(src, (p - 1), p, i, j - 1);


				   }
				   if (p9 == 1 && (p - src.step - 1) != m && p8 != 1 && p2 != 1) {
					   printf("3");
					   biaojishu++;
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(3);
					   tem_guiji.push_back(3);
					   //cout << "dd";
					   zuobiao2(src, (p - src.step - 1), p, i - 1, j - 1);

				   }


			   }


		   }
		   void xunhuan2(Mat & src, Mat &dst, Mat &cloo, vector<double> & bihuaxinxi) {
			   Mat clo = cloo.clone();
			   threshold(clo, clo, 140, 1, cv::THRESH_BINARY_INV);

			   int dijibi = 1;
			   int width = src.cols;//��
			   int height = src.rows;//��
			   biaojiifshu.push_back(0);
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
							   //����Ǳʻ��ڼ��Σ���ͬ�Ķ��ò��ж����ķ���
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(2);
							   tem_guiji.push_back(2);
							   biaojishu++;
							   printf("2");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao2(src, (p - src.step + j), p + j, i - 1, j);

						   }
						   if (p3 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(1);
							   tem_guiji.push_back(1);
							   printf("1");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao2(src, (p - src.step + j + 1), p + j, i - 1, j + 1);

						   }

						   if (p4 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(0);
							   tem_guiji.push_back(0);
							   printf("0");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao2(src, (p + j + 1), p + j, i, j + 1);
						   }

						   if (p5 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(7);
							   tem_guiji.push_back(7);
							   printf("7");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao2(src, (p + src.step + j + 1), p + j, i + 1, j + 1);

						   }

						   if (p6 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(6);
							   tem_guiji.push_back(6);
							   printf("6");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao2(src, (p + src.step + j), p + j, i + 1, j);

						   }

						   if (p7 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(5);
							   tem_guiji.push_back(5);
							   printf("5");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao2(src, (p + src.step + j - 1), p + j, i + 1, j - 1);

						   }

						   if (p8 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(4);
							   tem_guiji.push_back(4);
							   printf("4");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao2(src, (p + j - 1), p + j, i, j - 1);

						   }

						   if (p9 == 1 && chongfu == 0) {
							   bihuaduanbiaoji = 0;
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   printf("�켣��");
							   guiji.push_back(3);
							   tem_guiji.push_back(3);
							   printf("3");
							   biaojishu++;
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao2(src, (p - src.step + j - 1), p + j, i - 1, j - 1);

						   }






					   }



				   }
			   }
			   printf("*********************************************************************************************************************\n");
			   int bihua[4092][9];//{�ڼ��ʣ��켣���˵�x���˵�y��������x��������y,�켣x���켣y���ʻ����}
			   int  bihuaxuhao = 1;
			   int vectorxuhao = 0;
			   //guiji.push_back(8);
			   //guiji_x.push_back(8);
			   //guiji_y.push_back(8);



			   for (int i = 0; i < guiji.size(); i++) {
				   for (int j = 0; j < 9; j++) {



					   if (guiji[i] == 9 && j == 0) {


						   bihua[i][j] = bihuaxuhao;
						   bihuaxuhao++;

					   }
					   if (guiji[i] != 9 && j == 0) {
						   bihua[i][j] = bihuaxuhao;


					   }
					   if (j == 1) {
						   bihua[i][j] = guiji[i];
						   //printf("*%d", vectorxuhao);

						   vectorxuhao++;


					   }


					   if (j == 2) {
						   bihua[i][j] = 0;

					   }


					   if (j == 3) {
						   bihua[i][j] = 0;


					   }

					   if (j == 4) {
						   bihua[i][j] = 0;


					   }
					   if (j == 5) {
						   bihua[i][j] = 0;


					   }
					   if (j == 6) {

						   bihua[i][j] = guiji_x[i];

					   }
					   if (j == 7) {

						   bihua[i][j] = guiji_y[i];

					   }
					   if (j == 8) {

						   //bihua[i][j] = 0;

					   }



				   }
			   }
			   int bihuabiaoji = 0;
			   for (int j = 0; j < duandian_x.size(); j++) {
				   for (int i = 0; i < guiji.size(); i++) {
					   if (j + 1 == bihua[i][0]) {
						   bihua[i][2] = duandian_x[j];
						   bihua[i][3] = duandian_y[j];
						   bihua[i][4] = jieshudian_x[j];
						   bihua[i][5] = jieshudian_y[j];

					   }


				   }
			   }
			   for (int i = 0; i < biaojiifshu2.size(); i++) {
				   if (biaojiifshu2[i] == 1) {
					   for (int j = biaojiifshu[i]; j < biaojiifshu[i + 1]; j++) {
						   bihua[j][8] = 1;
					   }
				   }
			   }
			   //�ѱʻ�����С��20��ȥ��
			   int bihuaxuhao2 = 1;
			   vector<int>bihuaduanxuhao;
			   bihuaduanxuhao.push_back(0);
			   for (int i = 0; i < guiji.size(); i++) {
				   if (bihua[i][1] == 9) {

					   bihuaduanxuhao.push_back(i + 1);
				   }
			   }
			   bihuaduanxuhao.push_back(guiji.size() - 1);

			
			   for (int i = 1; i < bihuaduanxuhao.size(); i++) {
				  
					 
						   int zero = 0;
						   int one = 0;
						   int two = 0;
						   int three = 0;
						   int four = 0;
						   int five = 0;
						   int six = 0;
						   int seven = 0;
						   double sum = 0;

						   for (int j = bihuaduanxuhao[i-1 ]; j < bihuaduanxuhao[i]; j++) {
							   sum++;
							   if (bihua[j][1] == 0) {
								   zero++;
							   }
							   if (bihua[j][1] == 1) {
								   one++;
							   }
							   if (bihua[j][1] == 2) {
								   two++;
							   }
							   if (bihua[j][1] == 3) {
								   three++;
							   }
							   if (bihua[j][1] == 4) {
								   four++;
							   }
							   if (bihua[j][1] == 5) {
								   five++;
							   }
							   if (bihua[j][1] == 6) {
								   six++;
							   }
							   if (bihua[j][1] == 7) {
								   seven++;
							   }
						   }
						   cout << "********************************��" <<i  << "��" << endl;
						   cout << zero << "," << one << "," << two << "," << three << "," << four << "," << five << "," << six << "," << seven << "," << sum << endl;
						   cout << "********************************" << endl;
						   if ((zero > two&&zero > one&&zero > three&&zero > four&&zero > five&&zero > six&&zero > seven&&double(zero)/sum>0.5)|| (four > zero&&four > one&&four > three&&four > six&&four > five&&four > two&&four > seven&&double(four) / sum > 0.5) ) {
							   cout << "�Ǻ�" << endl;
						   }
						   else {
							   cout << "���Ǻ�" << endl;
							   for (int m = bihuaduanxuhao[i - 1]; m < bihuaduanxuhao[i]; m++) {
								   bihua[m][8] = 0;
							   }
						   }
						  
					   
				   

			   }
			   for (int i = 1; i < bihuaduanxuhao.size(); i++) {
				   if (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1] < 50) {
					   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i]; j++) {
						   bihua[j][8] = 0;
					   }
				   }

			   }
			   //�ʻ���ת
			   for (int i = 1; i < bihuaduanxuhao.size(); i++) {
				   double zero = 1;
				   double one = 1;
				   double two = 1;
				   double three = 1;
				   double four = 1;
				   double five = 1;
				   double six = 1;
				   double seven = 1;

				   if (bihua[bihuaduanxuhao[i - 1]][8] == 1) {
					   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i]; j++) {
						   if (bihua[j][1] == 0) {
							   zero++;
						   }
						   if (bihua[j][1] == 1) {
							   one++;
						   }
						   if (bihua[j][1] == 2) {
							   two++;
						   }
						   if (bihua[j][1] == 3) {
							   three++;
						   }
						   if (bihua[j][1] == 4) {
							   four++;
						   }
						   if (bihua[j][1] == 5) {
							   five++;
						   }
						   if (bihua[j][1] == 6) {
							   six++;
						   }
						   if (bihua[j][1] == 7) {
							   seven++;
						   }
					   }
					   if (four > zero) {
						   cout << "---------------------";


						   int biaoji = 0;
						   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1] - 1) / 2; j++) {

							   for (int m = 0; m < 8; m++) {

								   int temp = bihua[j][m];
								   bihua[j][m] = bihua[bihuaduanxuhao[i] - 1 - biaoji][m];
								   bihua[bihuaduanxuhao[i] - 1 - biaoji][m] = temp;
							   }
							   biaoji++;
						   }
					   }
				   }

			   }






			   for (int i = 0; i < guiji.size(); i++) {
				   printf("��%d�ʣ��켣��%d,�˵����꣨%d,%d��,���������꣨%d,%d��,�켣���꣨%d,%d�����ʻ����ţ���%d��\n", bihua[i][0], bihua[i][1], bihua[i][2], bihua[i][3], bihua[i][4], bihua[i][5], bihua[i][6], bihua[i][7], bihua[i][8]);
			   }
			   int ifcunzaiheng = 0;
			   for (int i = 0; i < guiji.size();i++) {
				   if (bihua[i][8]==1) {
					   ifcunzaiheng = 1;
					   break;
				   }
			   
			   }
			   if (ifcunzaiheng == 1) {


				   //����ʻ��رʻ�б��
				   vector<double> bihuashang;
				   vector<double> xielv;
				   vector<double> start_xielv;
				   vector<double> end_xielv;

				   for (int i = 1; i < bihuaduanxuhao.size(); i++) {
					   double zero = 1;
					   double one = 1;
					   double two = 1;
					   double three = 1;
					   double four = 1;
					   double five = 1;
					   double six = 1;
					   double seven = 1;

					   if (bihua[bihuaduanxuhao[i - 1]][8] == 1) {
						   //����ʻ���
						   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i]; j++) {
							   if (bihua[j][1] == 0) {
								   zero++;
							   }
							   if (bihua[j][1] == 1) {
								   one++;
							   }
							   if (bihua[j][1] == 2) {
								   two++;
							   }
							   if (bihua[j][1] == 3) {
								   three++;
							   }
							   if (bihua[j][1] == 4) {
								   four++;
							   }
							   if (bihua[j][1] == 5) {
								   five++;
							   }
							   if (bihua[j][1] == 6) {
								   six++;
							   }
							   if (bihua[j][1] == 7) {
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
						   double sd0 = zero / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd1 = one / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd2 = two / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd3 = three / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd4 = four / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd5 = five / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd6 = six / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);
						   double sd7 = seven / (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]);

						   //��ʾ�ʻ���sd
						   cout << "�ܱʻ���" << bihuaduanxuhao[i] - bihuaduanxuhao[i - 1] << endl;
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
						   bihuashang.push_back(Es);
						   cout << "�ʻ���:" << Es << endl;
						   //���ʻ���б��
						   double start_x = bihua[bihuaduanxuhao[i - 1]][6];
						   double start_y = bihua[bihuaduanxuhao[i - 1]][7];;
						   double end_x = bihua[bihuaduanxuhao[i] - 1][6];;
						   double end_y = bihua[bihuaduanxuhao[i] - 1][7];;
						   cout << "start_x-" << start_x << endl;
						   cout << "start_y-" << start_y << endl;
						   cout << "end_x-" << end_x << endl;
						   cout << "end_y-" << end_y << endl;
						   double xielv_k = DBL_MAX;
						   if (end_x != start_x) {
							   xielv_k = (end_y - start_y) / (end_x - start_x);

						   }
						   xielv.push_back(xielv_k);
						   cout << "б��:" << xielv_k << endl;
						   //����ʻ��ʼ���֮һб��
						   double start_1_5x = bihua[bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5][6];
						   // cout << "----------" << bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5 <<endl;
						   double start_1_5y = bihua[bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5][7];

						   cout << "start_1_5x:" << start_1_5x << endl;
						   cout << "start_1_5y:" << start_1_5y << endl;
						   double xielv_start = DBL_MAX;
						   if (start_1_5x != start_x) {
							   xielv_start = (start_1_5y - start_y) / (start_1_5x - start_x);

						   }
						   start_xielv.push_back(xielv_start);
						   cout << "�ʼ���֮һб��:" << xielv_start << endl;

						   //����ʻ��������֮һб��
						   double end_1_5x = bihua[bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5 * 4][6];
						   double end_1_5y = bihua[bihuaduanxuhao[i - 1] + (bihuaduanxuhao[i] - bihuaduanxuhao[i - 1]) / 5 * 4][7];

						   cout << "end_1_5x" << end_1_5x << endl;
						   cout << "end_1_5y" << end_1_5y << endl;
						   double xielv_end = DBL_MAX;
						   if (end_x != end_1_5x) {
							   xielv_end = (end_y - end_1_5y) / (end_x - end_1_5x);

						   }
						   end_xielv.push_back(xielv_end);
						   cout << "�������֮һб��:" << xielv_end << endl;


					   }
				   }
				   double bihuashang_count = 0;
				   double xielv_count = 0;
				   double start_xielv_count = 0;
				   double end_xielv_count = 0;
				   for (int i = 0; i < bihuashang.size(); i++) {
					   bihuashang_count += bihuashang[i];
					   xielv_count += xielv[i];
					   start_xielv_count += start_xielv[i];
					   end_xielv_count += end_xielv[i];

				   }
				   cout << "ƽ���ʻ���:" << bihuashang_count / bihuashang.size() << endl;
				   cout << "ƽ��б��:" << xielv_count / bihuashang.size() << endl;
				   cout << "ƽ����ʼб��:" << start_xielv_count / bihuashang.size() << endl;
				   cout << "ƽ������б��:" << end_xielv_count / bihuashang.size() << endl;
				   bihuaxinxi.push_back(bihuashang_count / bihuashang.size());
				   bihuaxinxi.push_back(xielv_count / bihuashang.size());
				   bihuaxinxi.push_back(start_xielv_count / bihuashang.size());
				   bihuaxinxi.push_back(end_xielv_count / bihuashang.size());
				   /* Mat show = Mat::zeros(Size(width, height), CV_8UC3);
					show = Scalar(255, 255, 255);
				   dst = dst * 255;
					bitwise_not(dst, dst);
					//threshold(dst, dst, 140, 1, cv::THRESH_BINARY_INV);*/
					//����ʻ��ֶ�������
				   int bihualeixinshuzu[4];
				   bihualeixinshuzu[0] = 0;
				   bihualeixinshuzu[1] = 0;
				   bihualeixinshuzu[2] = 0;
				   bihualeixinshuzu[3] = 0;
				   int shubihuaxuhao = 1;
				   double bihuatype = 0;
				   for (int i = 1; i < bihuaduanxuhao.size(); i++) {


					   if (bihua[bihuaduanxuhao[i - 1]][8] == 1) {
						   vector<int>xihuaguiji_x;
						   vector<int>xihuaguiji_y;

						   vector<double> cudu;
						   cout << "��" << shubihuaxuhao << "��ʻ�" << endl;
						   shubihuaxuhao++;
						   for (int j = bihuaduanxuhao[i - 1]; j < bihuaduanxuhao[i]; j++) {
							   xihuaguiji_x.push_back(bihua[j][6]);
							   xihuaguiji_y.push_back(bihua[j][7]);
						   }
						   for (int i = 0; i < xihuaguiji_x.size(); i++) {
							   //cout << "aaaa";
							   int radius = 1;
							   double threshold = 1;
							   while (threshold >= 0.95) {
								   double black = 0;
								   double all = 0;
								   int start_x = xihuaguiji_x[i] - radius;
								   int end_x = xihuaguiji_x[i] + radius;
								   int start_y = xihuaguiji_y[i] - radius;
								   int end_y = xihuaguiji_y[i] + radius;
								   if (start_x <= 0) {
									   start_x = 0;

								   }
								   if (end_x >= width) {
									   end_x = width;
								   }
								   if (start_y <= 0) {
									   start_y = 0;
								   }
								   if (end_y >= height) {
									   end_y = height;
								   }
								   for (int m = start_y; m < end_y; m++) {
									   uchar * q = clo.ptr<uchar>(m);
									   for (int n = start_x; n < end_x; n++) {
										   uchar q1 = q[n];
										   if (((n - xihuaguiji_x[i])*(n - xihuaguiji_x[i]) + (m - xihuaguiji_y[i])*(m - xihuaguiji_y[i])) <= radius * radius) {
											   all++;
											   if (q1 == 1) {
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
						   double startcudu = 0;
						   double cudujishu = 0;
						   //ǰһ��ֶ�

						   for (int i = 0; i < cudu.size() / 3; i++) {
							   cudujishu++;
							   cout << cudu[i] << ",";
							   startcudu += cudu[i];

						   }
						   cout << endl;
						   cout << "ǰһ��ֶ�:" << startcudu << "----" << cudujishu << "-----" << startcudu / cudujishu << endl;
						   //�м�һ��ֶ�
						   double midcudu = 0;
						   for (int i = cudu.size() / 3; i < cudu.size() / 3 * 2; i++) {

							   cout << cudu[i] << ",";
							   midcudu += cudu[i];

						   }
						   cout << endl;
						   cout << "�м�ֶ�:" << midcudu << "----" << cudujishu << "-----" << midcudu / cudujishu << endl;
						   //��һ��ֶ�
						   double endcudu = 0;
						   for (int i = cudu.size() / 3 * 2; i < cudu.size(); i++) {
							   cout << cudu[i] << ",";
							   endcudu += cudu[i];

						   }
						   cout << endl;
						   cout << "��һ��ֶ�:" << endcudu << "----" << cudujishu << "-----" << endcudu / cudujishu << endl;




						   if (startcudu / cudujishu > midcudu / cudujishu && endcudu / cudujishu > midcudu / cudujishu) {
							   bihuatype = 1;
							   bihualeixinshuzu[1]++;
							   cout << "ϸ����" << endl;

						   }

						   else if (startcudu / cudujishu < midcudu / cudujishu && midcudu / cudujishu < endcudu / cudujishu) {
							   bihuatype = 2;
							   bihualeixinshuzu[2]++;
							   cout << "����" << endl;
						   }
						   else if (startcudu / cudujishu > midcudu / cudujishu && midcudu / cudujishu > endcudu / cudujishu) {
							   bihuatype = 3;
							   bihualeixinshuzu[3]++;
							   cout << "�Ҽ��" << endl;
						   }
						   else {
							   cout << "ɶ�ʻ�������" << endl;
						   }



					   }
				   }
				   cout << bihualeixinshuzu[1] << "----" << bihualeixinshuzu[2] << "----" << bihualeixinshuzu[3];
				   if (bihualeixinshuzu[1] != 0 && bihualeixinshuzu[2] != 0 && bihualeixinshuzu[3] != 0) {
					   bihuaxinxi.push_back(6);
				   }
				   else if (bihualeixinshuzu[1] != 0 && bihualeixinshuzu[2] != 0) {
					   bihuaxinxi.push_back(5);
				   }
				   else if (bihualeixinshuzu[1] != 0 && bihualeixinshuzu[3] != 0) {
					   bihuaxinxi.push_back(4);
				   }
				   else if (bihualeixinshuzu[2] != 0 && bihualeixinshuzu[3] != 0) {
					   bihuaxinxi.push_back(3);
				   }
				   else if (bihualeixinshuzu[1] != 0) {
					   bihuaxinxi.push_back(2);

				   }
				   else if (bihualeixinshuzu[2] != 0) {
					   bihuaxinxi.push_back(1);

				   }
				   else if (bihualeixinshuzu[3] != 0) {
					   bihuaxinxi.push_back(0);

				   }
				   else {
					   bihuaxinxi.push_back(7);
				   }
			   }
			   else {
			   bihuaxinxi.push_back(0);
			   bihuaxinxi.push_back(0);
			   bihuaxinxi.push_back(0);
			   bihuaxinxi.push_back(0);
			   bihuaxinxi.push_back(7);
                       }
			   dst = dst * 255;
			   bitwise_not(dst, dst);
			   Mat three_channel = Mat::zeros(dst.rows, dst.cols, CV_8UC3);
			   vector<Mat> channels;
			   for (int i = 0; i < 3; i++)
			   {
				   channels.push_back(dst);
			   }
			   merge(channels, three_channel);



			   //imshow("aaa", three_channel);
			  // waitKey(0);

			   int color_1[3] = { 255,0,0 };
			   int color_2[3] = { 0,0,0 };


			   for (int i = 0; i < guiji.size(); i++) {
				   if (bihua[i][8] == 1) {
					   three_channel.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_1[0];
					   three_channel.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_1[1];
					   three_channel.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_1[2];

				   }
				   /* if (bihua[i][8] != 1) {

						show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_2[0];
						show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_2[1];
						show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_2[2];

					}*/
			   }
			   imshow("aaa", three_channel);
			   waitKey(0);
		   }

		  
};

