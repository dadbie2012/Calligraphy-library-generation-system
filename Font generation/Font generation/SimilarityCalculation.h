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
#include<algorithm>
#include <cmath>

using namespace std;
using namespace cv;
class SimilarityCalculation
{
public :
	double tezhengjunzhi(vector<double> & tezheng) {
		double all = 0;
		for (int i = 0; i < tezheng.size();i++) {
			all += tezheng[i];
		
		}
		return all / tezheng.size();
	}
	double biaozhuncha(double junzhi, vector<double> & tezheng) {
		double fangchaall = 0;
		for (int i = 0; i < tezheng.size();i++) {
			fangchaall += pow(tezheng[i] - junzhi, 2);
		}
		cout << "方差总和" << fangchaall << endl;
		double fangchajunzhi = 0;
		fangchajunzhi = fangchaall / tezheng.size();
		cout << "方差均值" << fangchajunzhi << endl;
		double biaozhuncha = sqrt(fangchajunzhi);
		return biaozhuncha;

	}
	void guiyihua(vector<double> &end,vector<double>& tezheng,double junzhi,double biaozhuncha) {
		for (int i = 0; i < tezheng.size();i++) {
			end.push_back((tezheng[i] - junzhi) / biaozhuncha);
		}
	}
	void simcal(vector<double> & shucunzai, vector<double> & hengcunzai,vector<double> & x0, vector<double> & y0, vector<double> & fstress_x, vector<double> & fstress_y, vector<double> & fslant_x, vector<double> & fslant_y, vector<double>&hangqi,vector<double> & strokewidth, vector<double> & strokemean, vector<double> & strokewidthpre, vector<double> & strokewidthafter, vector<double> & changkuanbi, vector <double> & shubihuashang, vector<double> & shu_xielv, vector<double> & shu_startxielv, vector<double> & shu_endxielv, vector<double> & shu_type, vector<double> & hengbihuashang, vector<double> & heng_xielv, vector<double> & heng_startxielv, vector<double> & heng_endxielv, vector<double> & heng_type ) {
	/*//把不存在横笔画竖笔画的数据取出
		vector<int>shubihuabiaoji;
		vector<int>hengbihuabiaoji;
		for (int i = 0; i < shubihuashang.size();i++) {
			if (shubihuashang[i]==0) {
				shubihuabiaoji.push_back(i);
				shubihuashang.pop_back();
				shu_xielv.pop_back();
				shu_startxielv.pop_back();
				shu_endxielv.pop_back();
			
			}
		
		}
		for (int i = 0; i < hengbihuashang.size(); i++) {
			if (hengbihuashang[i] == 0) {
				shubihuabiaoji.push_back(i);
				hengbihuashang.pop_back();
				heng_xielv.pop_back();
				heng_startxielv.pop_back();
				heng_endxielv.pop_back();

			}

		}*/
		
		//计算各特征值均值
		double ux0 = tezhengjunzhi(x0);
		cout << "ux0:" << ux0 << endl;
		double uy0 = tezhengjunzhi(y0);
		cout << "uy0:" << uy0 << endl;
		double ufstress_x = tezhengjunzhi(fstress_x);
		cout << "ufstress_x:" << ufstress_x << endl;
		double ufstress_y = tezhengjunzhi(fstress_y);
		cout << "ufstress_y:" << ufstress_y << endl;
		double ufslant_x = tezhengjunzhi(fslant_x);
		cout << "ufslant_x:" << ufslant_x << endl;
		double ufslant_y = tezhengjunzhi(fslant_y);
		cout << "ufslant_y:" << ufslant_y << endl;
		double uhangqi = tezhengjunzhi(hangqi);
		cout << "uhangqi:" << uhangqi << endl;
		double ustrokewidth = tezhengjunzhi(strokewidth);
		cout << "ustrokewidth:" << ustrokewidth << endl;
		double ustrokemean = tezhengjunzhi(strokemean);
		cout << "ustrokemean:" << ustrokemean << endl;
		double ustrokewidthpre = tezhengjunzhi(strokewidthpre);
		cout << "ustrokewidthpre:" << ustrokewidthpre << endl;
		double ustrokewidthafter = tezhengjunzhi(strokewidthafter);
		cout << "ustrokewidthafter:" << ustrokewidthafter << endl;
		double uchangkuanbi = tezhengjunzhi(changkuanbi);
		cout << "uchangkuanbi:" << uchangkuanbi << endl;

		double ushubihuashang = tezhengjunzhi(shubihuashang);
		cout << "ushubihuahshang:" << ushubihuashang << endl;
		double ushu_xielv = tezhengjunzhi(shu_xielv);
		cout << "ushu_xielv:" << ushu_xielv << endl;
		double ushu_startxielv = tezhengjunzhi(shu_startxielv);
		cout << "ushu_startxielv:" << ushu_startxielv << endl;
		double ushu_endxielv = tezhengjunzhi(shu_endxielv);
		cout << "ushu_endxielv:" << ushu_endxielv << endl;

		double uhengbihuashang = tezhengjunzhi(hengbihuashang);
		cout << "uhengbihuahshang:" << uhengbihuashang << endl;
		double uheng_xielv = tezhengjunzhi(heng_xielv);
		cout << "uheng_xielv:" << uheng_xielv << endl;
		double uheng_startxielv = tezhengjunzhi(heng_startxielv);
		cout << "uheng_startxielv:" << uheng_startxielv << endl;
		double uheng_endxielv = tezhengjunzhi(heng_endxielv);
		cout << "uheng_endxielv:" << uheng_endxielv << endl;
		//计算标准差
		double sx0 = biaozhuncha(ux0, x0);
		cout << "sx0：" << sx0 << endl;
		double sy0 = biaozhuncha(uy0, y0);
		cout << "sy0：" << sy0 << endl;
		double sfstress_x = biaozhuncha(ufstress_x, fstress_x);
		cout << "sfstress_x：" << sfstress_x << endl;
		double sfstress_y = biaozhuncha(ufstress_y, fstress_y);
		cout << "sfstress_y：" << sfstress_y << endl;
		double sfslant_x = biaozhuncha(ufslant_x, fslant_x);
		cout << "sfslant_x：" << sfslant_x << endl;
		double sfslant_y = biaozhuncha(ufslant_y, fslant_y);
		cout << "sfslant_y：" << sfslant_y << endl;
		double shangqi = biaozhuncha(uhangqi, hangqi);
		cout << "shangqi：" << shangqi << endl;
		double sstrokewidth = biaozhuncha(ustrokewidth, strokewidth);
		cout << "sstrokewidth：" << sstrokewidth << endl;
		double sstrokemean = biaozhuncha(ustrokemean, strokemean);
		cout << "sstrokemean：" << sstrokemean << endl;
		double sstrokewidthpre = biaozhuncha(ustrokewidthpre, strokewidthpre);
		cout << "sstrokewidthpre：" << sstrokewidthpre << endl;
		double sstrokewidthafter = biaozhuncha(ustrokewidthafter, x0);
		cout << "sstrokewidthafter：" << sstrokewidthafter << endl;
		double schangkuanbi = biaozhuncha(uchangkuanbi, x0);
		cout << "schangkuanbi：" << schangkuanbi << endl;
		
		double sshubihuashang = biaozhuncha(ushubihuashang, x0);
		cout << "sshubihuashang：" << sshubihuashang << endl;
		double sshu_xielv = biaozhuncha(ushu_xielv, x0);
		cout << "sshu_xielv：" << sshu_xielv << endl;
		double sshu_startxielv = biaozhuncha(ushu_startxielv, x0);
		cout << "sshu_startxielv：" << sshu_startxielv << endl;
		double sshu_endxielv = biaozhuncha(ushu_endxielv, x0);
		cout << "sshu_endxielv ：" << sshu_endxielv << endl;

		double shengbihuashang = biaozhuncha(uhengbihuashang, x0);
		cout << "shengbihuashang：" << shengbihuashang << endl;
		double sheng_xielv = biaozhuncha(uheng_xielv, x0);
		cout << "sheng_xielv：" << sheng_xielv << endl;
		double sheng_startxielv = biaozhuncha(uheng_startxielv, x0);
		cout << "sheng_startxielv：" << sheng_startxielv << endl;
		double sheng_endxielv = biaozhuncha(uheng_endxielv, x0);
		cout << "sheng_endxielv ：" << sheng_endxielv << endl;
		//归一化输出
		vector<double> endx0;
		guiyihua(endx0, x0, ux0, sx0);
		cout << "x0归一化输出" << endl;
		for (int i = 0; i < endx0.size();i++) {
			cout << endx0[i]<< endl;
		
		}
		vector<double> endy0;
		guiyihua(endy0, y0, uy0, sy0);
		cout << "y0归一化输出" << endl;
		for (int i = 0; i < endy0.size(); i++) {
			cout << endy0[i] << endl;

		}
		vector<double> endfstress_x;
		guiyihua(endfstress_x, fstress_x, ufstress_x, sfstress_x);
		cout << "fstress_x归一化输出" << endl;
		for (int i = 0; i < endfstress_x.size(); i++) {
			cout << endfstress_x[i] << endl;

		}
		vector<double> endfstress_y;
		guiyihua(endfstress_y, fstress_y, ufstress_y, sfstress_y);
		cout << "fstress_y归一化输出" << endl;
		for (int i = 0; i < endfstress_y.size(); i++) {
			cout << endfstress_y[i] << endl;

		}
		vector<double> endfslant_x;
		guiyihua(endfslant_x, fslant_x, ufslant_x, sfslant_x);
		cout << "fslant_x归一化输出" << endl;
		for (int i = 0; i < endfslant_x.size(); i++) {
			cout << endfslant_x[i] << endl;

		}
		vector<double> endfslant_y;
		guiyihua(endfslant_y, fslant_y, ufslant_y, sfslant_y);
		cout << "fslant_y归一化输出" << endl;
		for (int i = 0; i < endfslant_y.size(); i++) {
			cout << endfslant_y[i] << endl;

		}
		vector<double> endhangqi;
		guiyihua(endhangqi, hangqi, uhangqi, shangqi);
		cout << "行气归一化输出" << endl;
		for (int i = 0; i < endhangqi.size(); i++) {
			cout << endhangqi[i] << endl;

		}
		vector<double> endstrokewidth;
		guiyihua(endstrokewidth, strokewidth, ustrokewidth, sstrokewidth);
		cout << "笔宽归一化输出" << endl;
		for (int i = 0; i < endstrokewidth.size(); i++) {
			cout << endstrokewidth[i] << endl;

		}
		vector<double> endstrokemean;
		guiyihua(endstrokemean, strokemean, ustrokemean, sstrokemean);
		cout << "笔宽方差归一化输出" << endl;
		for (int i = 0; i < endstrokemean.size(); i++) {
			cout << endstrokemean[i] << endl;

		}
		vector<double> endstrokewidthpre;
		guiyihua(endstrokewidthpre, strokewidthpre, ustrokewidthpre, sstrokewidthpre);
		cout << "最小笔宽均值归一化输出" << endl;
		for (int i = 0; i < endstrokewidthpre.size(); i++) {
			cout << endstrokewidthpre[i] << endl;

		}
		vector<double> endstrokewidthafter;
		guiyihua(endstrokewidthafter, strokewidthafter, ustrokewidthafter, sstrokewidthafter);
		cout << "最小笔宽均值归一化输出" << endl;
		for (int i = 0; i < endstrokewidthafter.size(); i++) {
			cout << endstrokewidthafter[i] << endl;

		}
		vector<double> endchangkuanbi;
		guiyihua(endchangkuanbi, changkuanbi, uchangkuanbi, schangkuanbi);
		cout << "长宽比归一化输出" << endl;
		for (int i = 0; i < endchangkuanbi.size(); i++) {
			cout << endchangkuanbi[i] << endl;

		}
		vector<double> endshubihuashang;
		guiyihua(endshubihuashang, shubihuashang, ushubihuashang, sshubihuashang);
		//cout << "竖笔画熵归一化输出" << endl;
		double count1 = 0;
		for (int i = 0; i < endshubihuashang.size(); i++) {
			//cout << endshubihuashang[i] << endl;
			count1 += endshubihuashang[i];

		}
		vector<double> endshu_xielv;
		double count2 = 0;
		guiyihua(endshu_xielv, shu_xielv, ushu_xielv, sshu_xielv);
		//cout << "竖斜率归一化输出" << endl;
		for (int i = 0; i < endshu_xielv.size(); i++) {
			//cout << endshu_xielv[i] << endl;
			count2 += endshu_xielv[i];

		}
		vector<double> endshu_startxielv;
		double count3 = 0;
		guiyihua(endshu_startxielv, shu_startxielv, ushu_startxielv, sshu_startxielv);
		//cout << "竖开始斜率归一化输出" << endl;
		for (int i = 0; i < endshu_startxielv.size(); i++) {
			//cout << endshu_startxielv[i] << endl;
			count3 += endshu_startxielv[i];

		}
		vector<double> endshu_endxielv;
		double count4 = 0;
		guiyihua(endshu_endxielv, shu_endxielv, ushu_endxielv, sshu_endxielv);
		//cout << "竖结束斜率归一化输出" << endl;
		for (int i = 0; i < endshu_endxielv.size(); i++) {
			//cout << endshu_endxielv[i] << endl;
			count4 += endshu_endxielv[i];

		}
		vector<double> endhengbihuashang;
		double count5 = 0;
		guiyihua(endhengbihuashang, hengbihuashang, uhengbihuashang, shengbihuashang);
		//cout << "横笔画熵归一化输出" << endl;
		for (int i = 0; i < endhengbihuashang.size(); i++) {
			//cout << endhengbihuashang[i] << endl;
			count5 += endhengbihuashang[i];

		}
		vector<double> endheng_xielv;
		double count6 = 0;
		guiyihua(endheng_xielv, heng_xielv, uheng_xielv, sheng_xielv);
		//cout << "横斜率归一化输出" << endl;
		for (int i = 0; i < endheng_xielv.size(); i++) {
			//cout << endheng_xielv[i] << endl;
			count6 += endheng_xielv[i];

		}
		vector<double> endheng_startxielv;
		double count7 = 0;
		guiyihua(endheng_startxielv, heng_startxielv, uheng_startxielv, sheng_startxielv);
		//cout << "横开始斜率归一化输出" << endl;
		for (int i = 0; i < endheng_startxielv.size(); i++) {
			//cout << endheng_startxielv[i] << endl;
			count7 += endheng_startxielv[i];

		}
		vector<double> endheng_endxielv;
		double count8 = 0;
		guiyihua(endheng_endxielv, heng_endxielv, uheng_endxielv, sheng_endxielv);
		//cout << "横结束斜率归一化输出" << endl;
		for (int i = 0; i < endheng_endxielv.size(); i++) {
			//cout << heng_endxielv[i] << endl;
			count8 += endheng_endxielv[i];

		}
		int biaoji1 = 0;
		int biaoji2 = 0;
		int biaoji3 = 0;
		int biaoji4 = 0;
		vector<double> endshubihuashang2;
		vector<double> endshu_xielv2;
		vector<double> endshu_startxielv2;
		vector<double> endshu_endxielv2;
		vector<double> endhengbihuashang2;
		vector<double> endheng_xielv2;
		vector<double> endheng_startxielv2;
		vector<double> endheng_endxielv2;
		for (int i = 0; i < x0.size();i++) {
			if (shucunzai.size()!=0&&biaoji1<shucunzai.size() && i == shucunzai[biaoji1]) {
				endshubihuashang2.push_back(count1/ endshubihuashang.size());
				endshu_xielv2.push_back(count2 / endshubihuashang.size());
				endshu_startxielv2.push_back(count3 / endshubihuashang.size());
				endshu_endxielv2.push_back(count4 / endshubihuashang.size());
				biaoji1++;
			}
			else {
				endshubihuashang2.push_back(endshubihuashang[biaoji3]);
				endshu_xielv2.push_back(endshu_xielv[biaoji3]);
				endshu_startxielv2.push_back(endshu_startxielv[biaoji3]);
				endshu_endxielv2.push_back(endshu_endxielv[biaoji3]);
				biaoji3++;
			
			}

			if (hengcunzai.size()!=0&& biaoji2 < hengcunzai.size()&&i == hengcunzai[biaoji2]) {
				endhengbihuashang2.push_back(count5 / endhengbihuashang.size());
				endheng_xielv2.push_back(count6/ endhengbihuashang.size());
				endheng_startxielv2.push_back(count7 / endhengbihuashang.size());
				endheng_endxielv2.push_back(count8 / endhengbihuashang.size());
				biaoji2++;
			}
			else {
				endhengbihuashang2.push_back(endhengbihuashang[biaoji4]);
				endheng_xielv2.push_back(endheng_xielv[biaoji4]);
				endheng_startxielv2.push_back(endheng_startxielv[biaoji4]);
				endheng_endxielv2.push_back(endheng_endxielv[biaoji4]);
				biaoji4++;

			}
		}
		cout << "竖笔画熵归一化输出" << endl;
		
		for (int i = 0; i < endshubihuashang2.size(); i++) {
			cout << endshubihuashang2[i] << endl;
			

		}
		
		cout << "竖斜率归一化输出" << endl;
		for (int i = 0; i < endshu_xielv2.size(); i++) {
			cout << endshu_xielv2[i] << endl;
			

		}
		
		cout << "竖开始斜率归一化输出" << endl;
		for (int i = 0; i < endshu_startxielv2.size(); i++) {
			cout << endshu_startxielv2[i] << endl;
			

		}
	
		cout << "竖结束斜率归一化输出" << endl;
		for (int i = 0; i < endshu_endxielv2.size(); i++) {
			cout << endshu_endxielv2[i] << endl;
		

		}
		
		cout << "横笔画熵归一化输出" << endl;
		for (int i = 0; i < endhengbihuashang2.size(); i++) {
			cout << endhengbihuashang2[i] << endl;
			
		}
	
		cout << "横斜率归一化输出" << endl;
		for (int i = 0; i < endheng_xielv2.size(); i++) {
			cout << endheng_xielv2[i] << endl;
		

		}
		
		cout << "横开始斜率归一化输出" << endl;
		for (int i = 0; i < endheng_startxielv2.size(); i++) {
			cout << endheng_startxielv2[i] << endl;
			

		}
		
		cout << "横结束斜率归一化输出" << endl;
		for (int i = 0; i < endheng_endxielv2.size(); i++) {
			cout << endheng_endxielv2[i] << endl;
			

		}
		/*vector<double> & shucunzai, vector<double> & hengcunzai, vector<double> & x0, vector<double> & y0, vector<double> & fstress_x,
			vector<double> & fstress_y, vector<double> & fslant_x, vector<double> & fslant_y, vector<double>&hangqi, vector<double> & strokewidth,
			vector<double> & strokemean, vector<double> & strokewidthpre, vector<double> & strokewidthafter, vector<double> & changkuanbi, 
			vector <double> & shubihuashang, vector<double> & shu_xielv, vector<double> & shu_startxielv, vector<double> & shu_endxielv, 
			vector<double> & shu_type, vector<double> & hengbihuashang, vector<double> & heng_xielv, vector<double> & heng_startxielv, 
			vector<double> & heng_endxielv, vector<double> & heng_type) 
			
			vector<double> endshubihuashang2;
		vector<double> endshu_xielv2;
		vector<double> endshu_startxielv2;
		vector<double> endshu_endxielv2;
		vector<double> endhengbihuashang2;
		vector<double> endheng_xielv2;
		vector<double> endheng_startxielv2;
		vector<double> endheng_endxielv2;*/
			
		//计算总风格
		//(endx0[i]+1) * (endx0[j]+1) + (endy0[i]+1) * (endy0[j]+1) +(endhangqi[i] + 1) * (endhangqi[j] + 1) +
		//
		//(endshu_xielv2[i]+1) * (endshu_xielv2[j]+1)++ (endshu_startxielv2[i]+1) * (endshu_startxielv2[j]+1) + (endshu_endxielv2[i]+1) * (endshu_endxielv2[j]+1)
		//(endfstress_x[i] + 1) * (endfstress_x[i] + 1) + (endfstress_y[i] + 1) * (endfstress_y[i] + 1) + (endfslant_x[i] + 1) * (endfslant_x[i] + 1) + (endfslant_y[i] + 1) *(endfslant_y[i] + 1)
		//+ (endheng_xielv2[i]+1) * (endheng_xielv2[i]+1) + (endheng_startxielv2[i]+1) * (endheng_startxielv2[i]+1) +( endheng_endxielv2[i]+1) * (endheng_endxielv2[i]+1));
		//+ (endchangkuanbi[i] + 1) * (endchangkuanbi[j] + 1) + (endshubihuashang2[i] + 1) * (endshubihuashang2[j] + 1) +
		//+(endhengbihuashang2[i] + 1) * (endhengbihuashang2[j] + 1)
		double fenggecount = 0; 
			int fenggejishu = 1;
		for (int i = 0; i < x0.size()-1;i++) {
			for (int j = i + 1; j < x0.size();j++) {
				double shang = (endstrokewidth[i] ) * (endstrokewidth[j] ) + (endstrokemean[i] ) * (endstrokemean[j] ) + (endstrokewidthpre[i] ) * (endstrokewidthpre[j] ) +
					(endstrokewidthafter[i] ) * (endstrokewidthafter[j] ) ;
				
				double xiazuo = sqrt((endstrokewidth[i] ) * (endstrokewidth[i] ) + (endstrokemean[i] ) * (endstrokemean[i] ) + (endstrokewidthpre[i] ) * (endstrokewidthpre[i] ) +
					(endstrokewidthafter[i] ) * (endstrokewidthafter[i] ) );
					
				double xiayou = sqrt((endstrokewidth[j] ) * (endstrokewidth[j] ) + (endstrokemean[j] ) * (endstrokemean[j] ) + (endstrokewidthpre[j] ) * (endstrokewidthpre[j] ) +
					(endstrokewidthafter[j] ) * (endstrokewidthafter[j] ));
					
				double imagefengge = shang / (xiazuo * xiayou);
				cout << "shang：" << shang << "---" << "xiazuo :" << xiazuo << "----" << "xiayou:" << xiayou << "------" << "xiangcheng:" << xiazuo * xiayou << endl;
				cout << "第" << fenggejishu << "风格:" << imagefengge  <<endl;
				fenggecount += imagefengge;
				fenggejishu++;
			}
		
		}
		cout << "总风格 ： " << fenggecount << endl;

	     
	
	}
};

