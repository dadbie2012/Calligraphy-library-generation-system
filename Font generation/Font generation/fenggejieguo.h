#pragma once

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
#include "bihuafenge.h"
using namespace std;
using namespace cv;
class fenggejieguo
{
public:
	//����������
	vector <double> zhongxin_x;
	vector <double> hangqi;
	vector <double> avgwidth;
	vector <double> aspectratio;
	vector<Mat> image;

	vector<double> x0;
	vector<double>y0;
	vector<double>fstress_x;
	vector<double>fstress_y;
	vector<double>fslant_x;
	vector<double>fslant_y;
	vector<double>strokewidth;
	vector<double>strokemean;
	vector<double>strokewidthpre;
	vector<double>strokewidthafter;
	vector<double>changkuanbi;
	vector<double>hangqii;
	vector<double>bihuashang;
	vector<double>xielv;
	vector<double>start_xielv;
	vector<double>end_xielv;
	vector<double>bihuashang2;
	vector<double>xielv2;
	vector<double>start_xielv2;
	vector<double>end_xielv2;
	vector<double>shubihualeixing;
	vector<double>hengbihualeixing;

	void fenggejieguodaochu(vector<double> & fenggezhi, vector<Mat> & src) {
		SimilarityDetection *first = new SimilarityDetection();
		toolsclass *tool = new toolsclass();
		for (int i = 0; i < src.size(); i++) {
			cout << "**************��" << i + 1 << "��ͼƬ******************" << endl;
			Mat copy = src[i].clone();
			Mat copyy =src[i].clone();
			Mat copyyy = src[i].clone();
			Mat copyyyy = src[i].clone();
			Mat copyyyyy = src[i].clone();
			
			
			//����ʻ���Ϣ
			vector<double> bihuaxinxi;
			vector<double> bihuaxinxi2;
			//���ʻ�
			bihuafenge *fenge = new bihuafenge();
			Mat b = fenge->thinImage(copyy);
			Mat d = b.clone();
			Mat c = b;
			Mat e = d;
			fenge->endPointAndintersectionPointDetection(b, copyy);
			fenge->xunhuan(b, c,copy,bihuaxinxi);
			fenge->endPointAndintersectionPointDetection(d, copyy);
			fenge->xunhuan2(d, e, copy,bihuaxinxi2);
			//�������ľ�,����
  			vector<double> cenmoms;
			first->Centralmoments(copyyy, cenmoms);
			/*cout << "x0--" << cenmoms[0] << endl;
			cout << "y0--" << cenmoms[1] << endl;
			cout << "fstress_x:" << cenmoms[2] << endl;
			cout << "fstress_y:" << cenmoms[3] << endl;
			cout << "fslant_x:" << cenmoms[4] << endl;
			cout << "fslant_y:" << cenmoms[5] << endl;*/
			
			//����ʻ���ȱ仯
			vector<double> thickchvec;
			first->thicknesschange(copyyyy, thickchvec);
			cout << "�ʿ�" << thickchvec[0] << endl;
			cout << "�ʿ���" << thickchvec[1] << endl;
			cout << "ǰ���֮һ�ʿ�" << thickchvec[2] << endl;
			cout << "�����֮һ�ʿ�" << thickchvec[3] << endl;
			//����ȼ���
			double strokeAspectRatio = first->StrokeAspectRatio(copyyyyy);
			cout << "����ȣ�" << strokeAspectRatio << endl;
		


			x0.push_back(cenmoms[0]);
			y0.push_back(cenmoms[1]);
			fstress_x.push_back(cenmoms[2]);
			fstress_y.push_back(cenmoms[3]);
			fslant_x.push_back(cenmoms[4]);
			fslant_y.push_back(cenmoms[5]);
			strokewidth.push_back(thickchvec[0]);
			strokemean.push_back(thickchvec[1]);
			strokewidthpre.push_back(thickchvec[2]);
			strokewidthafter.push_back(thickchvec[3]);
			changkuanbi.push_back(strokeAspectRatio);
			bihuashang.push_back(bihuaxinxi[0]);
			xielv.push_back(bihuaxinxi[1]);
			start_xielv.push_back(bihuaxinxi[2]);
			end_xielv.push_back(bihuaxinxi[3]);
			shubihualeixing.push_back(bihuaxinxi[4]);
			bihuashang2.push_back(bihuaxinxi2[0]);
			xielv2.push_back(bihuaxinxi2[1]);
			start_xielv2.push_back(bihuaxinxi2[2]);
			end_xielv2.push_back(bihuaxinxi2[3]);
			hengbihualeixing.push_back(bihuaxinxi2[4]);
		}
		///�����ܺ�
		double sum = 0;
		for (int i = 0; i < x0.size(); i++) {
			cout << "�����У�" << x0[i] << endl;
			sum = sum + x0[i];
		}
		//����ƽ��ֵ�������
		double avg = sum / x0.size();
		cout << "����xƽ��ֵ" << avg << endl;
		//���ı�׼
		double standard = tool->colsest(x0, avg);
		cout << "���ı�׼" << standard << endl;
		//��������+����
		for (int i = 0; i < x0.size(); i++) {
			hangqi.push_back(first->hangqi(x0[i], standard));
			cout << "����" << "---" << hangqi[i] << endl;
			hangqii.push_back(hangqi[i]);
		}

		//���ݴ������
		for (int i = 0; i < x0.size(); i++) {
			cout << "**************��" << i + 1 << "��ͼƬ******************" << endl;
			cout << "x0��" << x0[i] << endl;
			cout << "y0��" << y0[i] << endl;
			cout << "fstress_x:" << fstress_x[i] << endl;
			cout << "fstress_y:" << fstress_y[i] << endl;
			cout << "fslant_x:" << fslant_x[i] << endl;
			cout << "fslant_y:" << fslant_y[i] << endl;
			cout << "������:" << hangqii[i] << endl;
			cout << "�ʿ�" << strokewidth[i] << endl;
			cout << "�ʿ���" << strokemean[i] << endl;
			cout << "��С�ʿ��ֵ" << strokewidthpre[i] << endl;
			cout << "��С�ʿ��ֵ" << strokewidthafter[i] << endl;
			cout << "����ȣ�" << changkuanbi[i] << endl;
			cout << "���ʻ���:" << bihuashang[i] << endl;
			cout << "��б��:" << xielv[i] << endl;
			cout << "����ʼб��:" << start_xielv[i] << endl;
			cout << "������б��:" << end_xielv[i] << endl;
			cout << "���ʻ�����:" << shubihualeixing[i] << endl;
			cout << "��ʻ���:" << bihuashang2[i] << endl;
			cout << "��б��:" << xielv2[i] << endl;
			cout << "�Ὺʼб��:" << start_xielv2[i] << endl;
			cout << "�����б��:" << end_xielv2[i] << endl;
			cout << "��ʻ�����:" << hengbihualeixing[i] << endl;

		}
		vector<double>bihuashang3;
		vector<double>xielv3;
		vector<double>start_xielv3;
		vector<double>end_xielv3;
		vector<double>bihuashang4;
		vector<double>xielv4;
		vector<double>start_xielv4;
		vector<double>end_xielv4;
		vector<double>shucunzai;
		vector<double>hengcunzai;

		for (int i = 0; i < x0.size();i++) {
			if (bihuashang[i]!=0) {
				bihuashang3.push_back(bihuashang[i]);
				xielv3.push_back(xielv[i]);
				start_xielv3.push_back(start_xielv[i]);
				end_xielv3.push_back(end_xielv[i]);
			}else{
				shucunzai.push_back(i);
			}
			if (bihuashang2[i] != 0) {
				bihuashang4.push_back(bihuashang2[i]);
				xielv4.push_back(xielv2[i]);
				start_xielv4.push_back(start_xielv2[i]);
				end_xielv4.push_back(end_xielv2[i]);
			}
			else {
				hengcunzai.push_back(i);
			}
		
		}
		SimilarityCalculation *similcal = new SimilarityCalculation();
		similcal->simcal(shucunzai, hengcunzai, x0, y0, fstress_x, fstress_y, fslant_x, fslant_y, hangqii, strokewidth, strokemean, strokewidthpre, strokewidthafter, changkuanbi, bihuashang3, xielv3, start_xielv3, end_xielv3, shubihualeixing, bihuashang4, xielv4, start_xielv4, end_xielv4, hengbihualeixing);




	}
};

