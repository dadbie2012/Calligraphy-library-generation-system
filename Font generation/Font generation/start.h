#pragma once
class start
{

	/*//Mat a = imread("D:/王羲之字库/竖/年.jpg", IMREAD_GRAYSCALE);
	Mat a = imread("D:/王羲之字库/竖/带.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/竖/随1.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/竖/古.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/竖/其.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/竖/向.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/竖/悟.jpg", IMREAD_GRAYSCALE);

	//Mat a = imread("D:/王羲之字库/横/亭.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/横/所.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/横/春.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/横/其.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/横/悟.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/王羲之字库/横/兴.jpg", IMREAD_GRAYSCALE);*/
	/*	Mat a = imread("D:/王羲之字库/横/兴.jpg", IMREAD_GRAYSCALE);
	  bihuafenge *fenge=new bihuafenge();
	  vector<double> aaa;
	  Mat aaaa = a.clone();
	  Mat b=fenge->thinImage(a);
	  Mat c = b;
	  fenge->endPointAndintersectionPointDetection(b,a);
	  fenge->xunhuan2(b,c,aaaa,aaa);
	  cout << "-----------" <<aaa[4] << endl;*/


	  //数据源
	 /* Mat a = imread("D:/王羲之字库/竖/年.jpg", IMREAD_GRAYSCALE);
	  //Mat  = imread("D:/王羲之字库/竖/带.jpg", IMREAD_GRAYSCALE);
	  Mat b = imread("D:/王羲之字库/竖/随1.jpg", IMREAD_GRAYSCALE);
	  Mat c = imread("D:/王羲之字库/竖/古.jpg", IMREAD_GRAYSCALE);
	  Mat d = imread("D:/王羲之字库/竖/其.jpg", IMREAD_GRAYSCALE);
	  Mat e = imread("D:/王羲之字库/竖/向.jpg", IMREAD_GRAYSCALE);
	  Mat f = imread("D:/王羲之字库/竖/悟.jpg", IMREAD_GRAYSCALE);

	  Mat g = imread("D:/王羲之字库/横/亭.jpg", IMREAD_GRAYSCALE);
	  Mat h = imread("D:/王羲之字库/横/所.jpg", IMREAD_GRAYSCALE);
	  Mat i = imread("D:/王羲之字库/横/春.jpg", IMREAD_GRAYSCALE);
	  Mat j = imread("D:/王羲之字库/横/其.jpg", IMREAD_GRAYSCALE);
	  Mat k = imread("D:/王羲之字库/横/悟.jpg", IMREAD_GRAYSCALE);
	  Mat l = imread("D:/王羲之字库/横/兴.jpg", IMREAD_GRAYSCALE);*/
	  /*Mat a = imread("D:/王羲之字库/横/兴.jpg", IMREAD_GRAYSCALE);
	  Mat b = imread("D:/王羲之字库/竖/古.jpg", IMREAD_GRAYSCALE);
	  Mat c = imread("D:/王羲之字库/横/年3.jpg", IMREAD_GRAYSCALE);
	  Mat d = imread("D:/王羲之字库/横/其.jpg", IMREAD_GRAYSCALE);
	  Mat e = imread("D:/王羲之字库/竖/随1.jpg", IMREAD_GRAYSCALE);
	  Mat l = imread("D:/王羲之字库/横/亭.jpg", IMREAD_GRAYSCALE);
	  vector<Mat> src;
	  src.push_back(a);
	  src.push_back(b);
	  src.push_back(c);
	  src.push_back(d);
	  src.push_back(e);
	  src.push_back(l);

	  //src.push_back(b);
	  vector<double>result;
	  fenggejieguo * jieguo=new fenggejieguo();
	  jieguo->fenggejieguodaochu(result, src);
	   */

	   /*SimilarityCalculation *similcal=new SimilarityCalculation();
	   similcal->simcal(x0, y0, fstress_x, fstress_y, fslant_x, fslant_y, hangqii, strokewidth, strokemean, strokewidthpre, strokewidthafter, changkuanbi);*/



	   //笔画计算（轨迹，笔画熵，笔画斜率，开始斜率，结束斜率）
	   //first->bihuaguiji(b);


	/*int NPB = 0;//二值化后黑色点数
	int NSP = 0;//骨架点数

	int shuchuorder = 1;
	int inputna = 0;
	int inputpie = 0;
	int inputheng = 0;
	int inputshu = 0;
	int iflast = 0;
	int inputstyle = 0;*/
	/*void thinImage(Mat & src, Mat & dst)
	{

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




		/*for (int i = 0; i < gujia2_x.size(); i++) {
			test.at<uchar>(gujia2_y[i], gujia2_x[i]) =1;

		}*/

		/*src.copyTo(dst);
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
	}
	//判断交叉点有4条路径的时候， 如果有三条路劲连在一起则不为交叉点；
	int dian4jiaodianshu4(int i, int j, Mat &src) {
		int width = src.cols;//列
		int height = src.rows;//行
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

	//判断交叉点有3条路径的时候，遍历交叉点数组如果他的相邻点已经为交叉点则判断不是交叉点
	int dian3jiaochadianshu(int a, int b) {
		int count = 0;
		for (int i = 0; i < jiaochadian_x.size(); i++) {
			if (jiaochadian_x[i] == b && jiaochadian_y[i] == a) {
				count++;

			}
		}
		return count;

	}
	//判断交叉点有3条路径的时候， 如果有两条路劲连在一起则不为交叉点；
	int dian3jiaochadianshu2(int i, int j, Mat &src) {
		int width = src.cols;//列
		int height = src.rows;//行
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

	//端点和交叉点
	void endPointAndintersectionPointDetection(Mat & src, Mat & test)
	{
		int width = src.cols;//列
		int height = src.rows;//行
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
		//111111111111111imshow("二值化与骨架合并图", test);
		//交叉点有4条路径判断
		for (int i = 0; i < height; ++i)
		{
			uchar * p = src.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				//获得九个点对象，注意边界问题
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
				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 4)//端点判断
				{
					printf("有4个方向有像素的点：%d %d\n", j, i);
					int count4 = dian4jiaodianshu4(i, j, src);
					if (count4 == 0) {

						printf("交叉点4：%d %d\n", j, i);
						jiaochadian_x.push_back(j);
						jiaochadian_y.push_back(i);
					}

				}

			}
		}
		//交叉点三条路径判断
		for (int i = 0; i < height; ++i)
		{
			uchar * p = src.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				//获得九个点对象，注意边界问题
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
				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 3)//端点判断
				{
					printf("有3个方向有像素的点：%d %d\n", j, i);
					int count2 = dian3jiaochadianshu2(i, j, src);
					int count1 = dian3jiaochadianshu(i, j - 1) + dian3jiaochadianshu(i, j + 1) + dian3jiaochadianshu(i - 1, j) + dian3jiaochadianshu(i - 1, j + 1) + dian3jiaochadianshu(i - 1, j - 1) + dian3jiaochadianshu(i + 1, j) + dian3jiaochadianshu(i + 1, j - 1) + dian3jiaochadianshu(i + 1, j + 1);
					if (count1 == 0 && count2 == 0) {
						printf("交叉点3：%d %d\n", j, i);
						jiaochadian_x.push_back(j);
						jiaochadian_y.push_back(i);

					}

					//endpoint.push_back(cvPoint(j, i));
				}

			}
		}
		//画出端点
		/*for (vector<CvPoint>::iterator i = endpoint.begin(); i != endpoint.end(); ++i)
		{
			circle(src, cvPoint(i->x, i->y), 5, Scalar(255), -1);
		}*/
		// 画出交叉点
		   /*for (vector<CvPoint>::iterator i = intersectionPoint.begin(); i != intersectionPoint.end(); ++i)
		   {
			   circle(src, cvPoint(i->x, i->y), 5, Scalar(255));
			   //cvPoint(i->x, i->y) =255;
			   //src.at<uchar>(i->x, i->y) = 255;
		   }*/
		   /*	endpoint.clear();//数据回收
			   intersectionPoint.clear();
			   for (int i = 0; i < jiaochadian_x.size(); i++) {
				   printf("最终交叉点：%d,%d\n", jiaochadian_x[i], jiaochadian_y[i]);

			   }
		   }
		   void zuobiao(Mat & src,uchar *p, uchar *m,int i,int j) {

			   int width = src.cols;//列
			   int height = src.rows;//行
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

				   if (p2 == 1&&(p - src.step) != m) {
					   printf("2");
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(2);

					   zuobiao(src, (p - src.step ),p, i - 1, j);

				   }
				   if (p3 == 1 && (p - src.step + 1) != m) {
					   printf("1");
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(1);

					   zuobiao(src, (p - src.step + 1),p, i - 1, j + 1);

				   }

				   if (p4 == 1 && (p + 1) != m) {
					   printf("0");
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(0);

					   zuobiao(src, (p + 1),p, i, j + 1);
				   }

				   if (p5 == 1&&(p + src.step + 1) != m) {
					   printf("7");
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(7);

					   zuobiao(src, (p + src.step + 1), p,i + 1, j + 1);

				   }

				   if (p6 == 1 && (p + src.step) != m) {
					   printf("6");
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(6);

					   zuobiao(src, (p + src.step) ,p,i + 1, j);

				   }

				   if (p7 == 1&&(p + src.step - 1) != m) {
					   printf("5");
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(5);

					   zuobiao(src, (p + src.step - 1),p, i + 1, j - 1);

				   }

				   if (p8 == 1 && (p - 1) != m) {
					   printf("4");
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(4);

					   zuobiao(src, (p - 1), p,i, j - 1);

				   }

				   if (p9 == 1 && (p - src.step - 1) != m) {
					   printf("3");
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);
					   guiji.push_back(3);

					   zuobiao(src, (p - src.step - 1),p, i - 1, j - 1);

				   }




			   }
			   if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) ==1 ) {
				   printf("9  ");
				   printf("结束点：(%d,%d)\n", j, i);
				   guiji.push_back(9);
				   guiji_y.push_back(i);
				   guiji_x.push_back(j);
				   jieshudian_x.push_back(j);
				   jieshudian_y.push_back(i);


			   }
			   int biaoji = 0;
			   for (int m = 0; m < jiaochadian_x.size(); m++) {

				   if (jiaochadian_x[m] == j && jiaochadian_y[m]==i) {

					   biaoji = 1;


				   }

			   }

			   if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >=3&&biaoji==1) {
				   printf("9  ");
				   printf("结束点：(%d,%d)\n",j,i);
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
					   zuobiao(src, (p - src.step ), p, i - 1, j);
				   }
				   if (p4 == 1&& p + 1!=m) {
					   printf("0");
					   guiji.push_back(0);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);


					   zuobiao(src, (p + 1), p, i, j + 1);
				   }
				   if (p6 == 1&& p +src.step != m) {
					   printf("6");
					   guiji.push_back(6);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);

					   zuobiao(src, (p + src.step), p, i + 1, j);

				   }
				   if (p8 == 1&& (p - 1)!=m) {
					   printf("4");
					   guiji.push_back(4);
					   guiji_y.push_back(i);
					   guiji_x.push_back(j);

					   zuobiao(src, (p - 1), p, i, j - 1);

				   }


			   }


		   }
		   void xunhuan(Mat & src) {

			   int dijibi = 1;
			   int width = src.cols;//列
			   int height = src.rows;//行
			   for (int i = 0; i < height; ++i)
			   {
				   uchar * p = src.ptr<uchar>(i);
				   for (int j = 0; j < width; ++j)
				   {
					   //获得九个点对象，注意边界问题
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
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(2);
							   printf("2");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p - src.step + j), p + j, i - 1, j);

						   }
						   if (p3 == 1 && chongfu == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(1);
							   printf("1");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p - src.step + j + 1), p + j, i - 1, j + 1);

						   }

						   if (p4 == 1 && chongfu == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(0);
							   printf("0");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + j + 1), p + j, i, j + 1);
						   }

						   if (p5 == 1 && chongfu == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(7);
							   printf("7");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j + 1), p + j, i + 1, j + 1);

						   }

						   if (p6 == 1 && chongfu == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(6);
							   printf("6");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j), p + j, i + 1, j);

						   }

						   if (p7 == 1 && chongfu == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(5);
							   printf("5");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j - 1), p + j, i + 1, j - 1);

						   }

						   if (p8 == 1 && chongfu == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(4);
							   printf("4");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + j - 1), p + j, i, j - 1);

						   }

						   if (p9 == 1 && chongfu == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
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
			   for (int i = 0; i < height; ++i)
			   {
				   uchar * p = src.ptr<uchar>(i);
				   for (int j = 0; j < width; ++j)
				   {
					   int biaoji = 0;
					   for (int m = 0; m < jiaochadian_x.size(); m++) {

						   if (jiaochadian_x[m] == j && jiaochadian_y[m] == i) {

							   biaoji = 1;


						   }

					   }
					   if (biaoji == 1) {
						   //获得九个点对象，注意边界问题
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


						   int biaoji2 = 0;
						   int biaoji3 = 0;
						   int biaoji4 = 0;
						   int biaoji5 = 0;
						   int biaoji6 = 0;
						   int biaoji7 = 0;
						   int biaoji8 = 0;
						   int biaoji9 = 0;
						   for (int m = 0; m < guiji_x.size(); m++) {

							   if (guiji_x[m] == j && guiji_y[m] == i - 1) {

								   biaoji2 = 1;


							   }

						   }
						   for (int m = 0; m < guiji_x.size(); m++) {

							   if (guiji_x[m] == j + 1 && guiji_y[m] == i - 1) {

								   biaoji3 = 1;


							   }

						   }
						   for (int m = 0; m < guiji_x.size(); m++) {

							   if (guiji_x[m] == j + 1 && guiji_y[m] == i) {

								   biaoji4 = 1;


							   }

						   }for (int m = 0; m < guiji_x.size(); m++) {

							   if (guiji_x[m] == j + 1 && guiji_y[m] == i + 1) {

								   biaoji5 = 1;


							   }

						   }for (int m = 0; m < guiji_x.size(); m++) {

							   if (guiji_x[m] == j && guiji_y[m] == i + 1) {

								   biaoji6 = 1;


							   }

						   }for (int m = 0; m < guiji_x.size(); m++) {

							   if (guiji_x[m] == j - 1 && guiji_y[m] == i + 1) {

								   biaoji7 = 1;


							   }

						   }for (int m = 0; m < guiji_x.size(); m++) {

							   if (guiji_x[m] == j - 1 && guiji_y[m] == i) {

								   biaoji8 = 1;


							   }

						   }
						   for (int m = 0; m < guiji_x.size(); m++) {

							   if (guiji_x[m] == j - 1 && guiji_y[m] == i - 1) {

								   biaoji9 = 1;


							   }

						   }
						   if (p2 == 1 && biaoji2 == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   guiji.push_back(2);
							   printf("轨迹：");
							   printf("2");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p - src.step + j), p + j, i - 1, j);

						   }
						   if (p3 == 1 && biaoji3 == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   guiji.push_back(1);
							   printf("轨迹：");
							   printf("1");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p - src.step + j + 1), p + j, i - 1, j + 1);

						   }

						   if (p4 == 1 && biaoji4 == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   guiji.push_back(0);
							   printf("轨迹：");
							   printf("0");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + j + 1), p + j, i, j + 1);
						   }

						   if (p5 == 1 && biaoji5 == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(7);
							   printf("7");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j + 1), p + j, i + 1, j + 1);

						   }

						   if (p6 == 1 && biaoji6 == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   guiji.push_back(6);
							   printf("轨迹：");
							   printf("6");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j), p + j, i + 1, j);

						   }

						   if (p7 == 1 && biaoji7 == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(5);
							   printf("5");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j - 1), p + j, i + 1, j - 1);

						   }

						   if (p8 == 1 && biaoji8 == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
							   guiji.push_back(4);
							   printf("4");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + j - 1), p + j, i, j - 1);

						   }

						   if (p9 == 1 && biaoji9 == 0) {
							   printf("第%d笔————", dijibi);
							   dijibi++;
							   printf("端点：(%d , %d)", j, i);
							   printf("轨迹：");
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
			   printf("*********************************************************************************************************************\n");
			   int bihua[4092][9];//{第几笔，轨迹，端点x，端点y，结束点x，结束点y,轨迹x，轨迹y，笔画标记}
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




			   //int NS = duandianbiaoji;//笔画数目
			   //double canshu1 = 0.3333;

			   printf("%d\n", NPB);//二值化后黑色点数
			   printf("%d\n", guiji.size());//骨架点个数


			   int puanduanbihua = 1;
			   while (puanduanbihua <= duandian_x.size()) {

				   int count0 = 0;
				   int count1 = 0;
				   int count2 = 0;
				   int count3 = 0;
				   int count4 = 0;
				   int count5 = 0;
				   int count6 = 0;
				   int count7 = 0;
				   for (int i = 0; i < guiji.size(); i++) {
					   if (puanduanbihua == bihua[i][0]) {
						   if (bihua[i][1] == 0) {

							   count0++;
						   }
						   if (bihua[i][1] == 1) {

							   count1++;
						   }
						   if (bihua[i][1] == 2) {

							   count2++;
						   }
						   if (bihua[i][1] == 3) {

							   count3++;
						   }
						   if (bihua[i][1] == 4) {

							   count4++;
						   }
						   if (bihua[i][1] == 5) {

							   count5++;
						   }
						   if (bihua[i][1] == 6) {

							   count6++;
						   }
						   if (bihua[i][1] == 7) {

							   count7++;
						   }

					   }




				   }


				   double countALL = count0 + count1 + count2 + count3 + count4 + count5 + count6 + count7;
				   printf("第%d笔：0占比%lf，1占比%lf，2占比%lf，3占比%lf，4占比%lf，5占比%lf，6占比%lf，7占比%lf\n，", puanduanbihua, count0 / countALL, count1 / countALL, count2 / countALL, count3 / countALL, count4 / countALL, count5 / countALL, count6 / countALL, count7 / countALL);
				   //横
				   if (count0 / countALL > 0.7 || count4 / countALL > 0.7) {

					   for (int i = 0; i < guiji.size(); i++) {
						   if (bihua[i][0] == puanduanbihua) {

							   bihua[i][8] = 1;
						   }
					   }
				   }


				   //竖
				   if (count2 / countALL > 0.7 || count6 / countALL > 0.7) {

					   for (int i = 0; i < guiji.size(); i++) {
						   if (bihua[i][0] == puanduanbihua) {
							   bihua[i][8] = 2;
						   }
					   }
				   }

				   //撇
				   if (count5 / countALL > 0.3 || count1 / countALL > 0.3 || (count0 / countALL > 0.6&&count1 / countALL > 0.088) || (count4 / countALL > 0.6&&count5 / countALL > 0.088)) {

					   for (int i = 0; i < guiji.size(); i++) {

						   if (bihua[i][0] == puanduanbihua) {


							   bihua[i][8] = 3;
						   }
					   }


				   }
				   //捺
				   if (count3 / countALL > 0.3 || count7 / countALL > 0.3) {

					   for (int i = 0; i < guiji.size(); i++) {
						   if (bihua[i][0] == puanduanbihua) {
							   bihua[i][8] = 4;
						   }
					   }


				   }
				   //横折
				   /*if (count0 / countALL > 0.3 && count6 / countALL > 0.3) {

					   for (int i = 0; i < guiji.size() ; i++) {
						   if (bihua[i][0] == puanduanbihua) {
							   bihua[i][8] = 5;
						   }
					   }


				   }*/
				   //竖钩
				   /*if ((count2 / countALL > 0.3 &&count7 / countALL > 0.08&&count0 / countALL > 0.1)|| (count6 / countALL > 0.3 &&count3 / countALL > 0.08&&count4 / countALL > 0.1)) {

					   for (int i = 0; i < guiji.size() ; i++) {
						   if (bihua[i][0] == puanduanbihua) {
							   bihua[i][8] = 6;
						   }
					   }




				   }*/
				   /*	puanduanbihua++;


				   }


				   /*for (int i = 0; i < duandian_x.size() ; i++) {
							   int bihuaxuhao = 0;

								int duandianx1 = duandian_x[i];
							   int duandiany1 = duandian_y[i];
							   int jieshudianx1 = jieshudian_x[i];
							   int jieshudiany1 = jieshudian_y[i];
							   int count = 0;
							   int chongfus_x = 0;
							   int chongfus_y = 0;
							   int chongfue_x = 0;
							   int chongfue_y = 0;
							   int ifshishu = 0;
							   for (int j = 0; j < guiji.size(); j++) {
								   if ((duandianx1 == bihua[j][2]) && (duandiany1 == bihua[j][3]) && (jieshudianx1 == bihua[j][3]) && (jieshudiany1 == bihua[j][4])) {

									   bihuaxuhao = bihua[j][0];
									   ifshishu = bihua[j][8];
									   break;
								   }

							   }
							   printf("wwww%d",ifshishu);
							   if (ifshishu == 2) {

								   for (int j = 0; j < guiji.size(); j++) {

									   int ifyuandian = 0;
									   if ((duandianx1 == bihua[j][2]) && (duandiany1 == bihua[j][3]) && (jieshudianx1 == bihua[j][4]) && (jieshudiany1 == bihua[j][5])) {

										   ifyuandian = 1;
									   }

									   int ifchongfu = 0;

									   if ((chongfus_x == bihua[j][2]) && (chongfus_y == bihua[j][3]) && (chongfue_x == bihua[j][4]) && (chongfue_x == bihua[j][5])) {
										   ifchongfu = 1;


									   }

									   if (((duandianx1 == bihua[j][2] && duandiany1 == bihua[j][3]) || (duandianx1 == bihua[j][4] && duandiany1 == bihua[j][5]) || (jieshudianx1 == bihua[j][2] && jieshudiany1 == bihua[j][3]) || (jieshudianx1 == bihua[j][4] && jieshudiany1 == bihua[j][5])) && ifyuandian == 0 && ifchongfu == 0 && bihua[j][8] == 2) {

										   int chongfus_x = bihua[j][2];
										   int chongfus_y = bihua[j][3];
										   int chongfue_x = bihua[j][4];
										   int chongfue_y = bihua[j][5];
										   count++;

									   }



								   }
							   }

							   printf("zzzz%d", count);
				   }
				   */




				   /*	//判断方法1
					   double canshu2 = NPB * 0.5 / guiji.size();
					   printf("canshu2%lf\n", canshu2);
					   for (int i = 0; i < duandian_x.size() - 1; i++) {
						   for (int j = i; j < duandian_x.size() - 1; j++) {
							   int bihuadaihao = 9;
							   int bihuaxuhao = 0;
							   int duandianx1 = duandian_x[i];
							   int duandiany1 = duandian_y[i];
							   int jieshudianx1 = jieshudian_x[i];
							   int jieshudiany1 = jieshudian_y[i];
							   for (int m = 0; m < guiji.size(); m++) {
								   if (bihua[m][2] == duandianx1 && bihua[m][3] == duandiany1 && bihua[m][4] == jieshudianx1 && bihua[m][5] == jieshudiany1) {
									   bihuadaihao = bihua[m][8];
									   bihuaxuhao = bihua[m][0];
								   }



							   }

							   int duandianx2 = duandian_x[j + 1];
							   int duandiany2 = duandian_y[j + 1];
							   int jieshudianx2 = jieshudian_x[j + 1];
							   int jieshudiany2 = jieshudian_y[j + 1];
							   double result1 = sqrt(abs(duandianx1 - duandianx2)*abs(duandianx1 - duandianx2) + abs(duandiany1 - duandiany2)*abs(duandiany1 - duandiany2));
							   printf("result1  %lf", result1);
							   double result2 = sqrt(abs(duandianx1 - jieshudianx2)*abs(duandianx1 - jieshudianx2) + abs(duandiany1 - jieshudiany2)*abs(duandiany1 - jieshudiany2));
							   printf("result2  %lf", result2);
							   double result3 = sqrt(abs(jieshudianx1 - duandianx2)*abs(jieshudianx1 - duandianx2) + abs(jieshudiany1 - duandiany2)*abs(jieshudiany1 - duandiany2));
							   printf("result3  %lf", result3);
							   double result4 = sqrt(abs(jieshudianx1 - jieshudianx2)*abs(jieshudianx1 - jieshudianx2) + abs(jieshudiany1 - jieshudiany2)*abs(jieshudiany1 - jieshudiany2));
							   printf("result4  %lf\n", result4);
							   if (result1 < canshu2 || result2 < canshu2 || result3 < canshu2 || result4 < canshu2) {


								   for (int m = 0; m < guiji.size(); m++) {


									   if (bihua[m][0] == j + 2 && bihua[m][8] == bihuadaihao) {
										   int biaoji4 = 1;
										   int biaoji5 = 1;

										   for (int i1 = 0; i < guiji.size(); i1++) {
											   if (bihua[i1][2] == duandian_x[i] && bihua[i1][3] == duandian_y[i]) {
												   biaoji4 = bihua[i1][0];
												   break;
											   }

										   }

										   bihua[m][0] = bihuaxuhao;


									   }

								   }


							   }


						   }



					   }

					   //判断方法2
					   /*int pd5 = 0;
					   int duandian5_x = 0;
					   int duandian5_y = 0;
					   int jieshudian5_x = 0;
					   int jieshudian5_y = 0;
					   int bihua5biaoji;
					   for (int i = 0; i < guiji.size() -1; i++) {
						   if (bihua[i][4] == 5) {
							   bihua5biaoji = bihua[i][0];
							   duandian5_x = bihua[i][2];
							   duandian5_y = bihua[i][3];
							   jieshudian5_x = bihua[i][5];
							   jieshudian5_x = bihua[i][6];
							   pd5 = 1;
							   break;

						   }


					   }
					   if (pd5 == 1) {

						   for (int i = 0; i < guiji.size()  - 1; i++) {

							   int duandian5next_x = bihua[i][2];
							   int duandian5next_y = bihua[i][3];
							   int jieshudian5next_x = bihua[i][5];
							   int jieshudian5next_y = bihua[i][6];
							   double result5test1 = sqrt(abs(duandian5_x - jieshudian5next_x)*abs(duandian5_x - jieshudian5next_x) + abs(duandian5_y - jieshudian5next_y)*abs(duandian5_y - jieshudian5next_y));
							   double result5test2 = sqrt(abs(duandian5_x - duandian5next_x)*abs(duandian5_x - duandian5next_x) + abs(duandian5_y - duandian5next_y)*abs(duandian5_y - duandian5next_y));
							   double result5test3 = sqrt(abs(jieshudian5_x - jieshudian5next_x)*abs(jieshudian5_x - jieshudian5next_x) + abs(jieshudian5_y - jieshudian5next_y)*abs(jieshudian5_y - jieshudian5next_y));
							   double result5test4 = sqrt(abs(jieshudian5_x - duandian5next_x)*abs(jieshudian5_x - duandian5next_x) + abs(jieshudian5_y - duandian5next_y)*abs(jieshudian5_y - duandian5next_y));
							   printf("result1  %lf", result5test1);
							   printf("result2  %lf", result5test2);
							   printf("result3  %lf", result5test3);
							   printf("result4  %lf", result5test4);
							   if ((result5test1 < canshu2 || result5test2 < canshu2 || result5test3 < canshu2 || result5test4 < canshu2) && (bihua[i][4] == 1 || bihua[i][4] == 6)) {
								   bihua[i][0] = bihua5biaoji;


							   }


						   }


					   }*/
					   /*//把笔画数组中的笔画排好，不能是1357，而是1234
					   int bihuabiaoji2 = bihua[0][0];
					   int bihuashuliang = 0;
					   for (int i = 0; i < guiji.size(); i++) {
						   if (bihua[i][0] == bihuabiaoji2) {
							   bihuashuliang++;
							   break;

						   }
						   if (bihua[i][0] != bihuabiaoji2) {
							   bihuabiaoji2 = bihua[i][0];
							   break;

						   }


					   }
					   printf("zzzz%d", bihuashuliang);


					   */
					   /*	Mat show = Mat::zeros(Size(800, 800), CV_8UC3);
						   show = Scalar(255, 255, 255);

						   int color_1[3] = { 255,255,0 };
						   int color_2[3] = { 255,153,18 };
						   int color_3[3] = { 255,97,0 };
						   int color_4[3] = { 160, 32, 240 };
						   int color_5[3] = { 255,0,0 };
						   int color_6[3] = { 255,0,255 };
						   int color_7[3] = { 0,0,255 };
						   int color_8[3] = { 3,168,158 };
						   int color_9[3] = { 25,25,112 };
						   int color_10[3] = { 0,255,0 };
						   int color_11[3] = { 128,42,42 };
						   int color_12[3] = { 255,99,71 };
						   int color_13[3] = { 210,164,96 };
						   int color_14[3] = { 46,139,87 };
						   int color_15[3] = { 46,139,87 };
						   int color_16[3] = { 46,139,87 };
						   int color_17[3] = { 46,139,87 };
						   int color_18[3] = { 46,139,87 };
						   int color_19[3] = { 46,139,87 };

						   for (int i = 0; i < guiji.size(); i++) {
							   if (bihua[i][0] == 1) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_1[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_1[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_1[2];

							   }
							   if (bihua[i][0] == 2) {
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_2[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_2[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_2[2];


							   }
							   if (bihua[i][0] == 3) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_3[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_3[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_3[2];
							   }
							   if (bihua[i][0] == 4) {
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_4[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_4[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_4[2];

							   }
							   if (bihua[i][0] == 5) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_5[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_5[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_5[2];
							   }
							   if (bihua[i][0] == 6) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_6[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_6[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_6[2];
							   }
							   if (bihua[i][0] == 7) {
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_7[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_7[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_7[2];


							   }
							   if (bihua[i][0] == 8) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_8[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_8[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_8[2];

							   }
							   if (bihua[i][0] == 9) {
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_9[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_9[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_9[2];


							   }
							   if (bihua[i][0] == 10) {
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_10[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_10[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_10[2];

							   }
							   if (bihua[i][0] == 11) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_11[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_11[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_11[2];

							   }

							   if (bihua[i][0] == 12) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_12[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_12[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_12[2];

							   }
							   if (bihua[i][0] == 13) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_13[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_13[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_13[2];

							   }
							   if (bihua[i][0] == 14) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_14[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_14[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_14[2];

							   }
							   if (bihua[i][0] == 15) {

								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[0] = color_15[0];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[1] = color_15[1];
								   show.at<Vec3b>(guiji_y[i], guiji_x[i])[2] = color_15[2];

							   }




						   }
						   //2222222222222222222222imshow("笔画结构", show);
						   //imwrite("D:/笔画结构.jpg", show);


						   for (int i = 0; i < guiji.size(); i++) {
							   printf("第%d笔，轨迹：%d,端点坐标（%d,%d）,结束点坐标（%d,%d）,轨迹坐标（%d,%d），笔画代号：（%d）\n", bihua[i][0], bihua[i][1], bihua[i][2], bihua[i][3], bihua[i][4], bihua[i][5], bihua[i][6], bihua[i][7], bihua[i][8]);
						   }





						   int bihuadaihao3 = 1;
						   int bihuadaihao = 0;
						   int bihuadaihao2 = 1;
						   for (int i = 0; i < duandian_x.size(); i++) {
							   vector<int>guijifanzhuan;
							   vector<int>duandian__x;
							   vector<int>duandian__y;

							   for (int j = 0; j < guiji.size(); j++) {
								   if (bihua[j][0] == bihuadaihao2) {
									   duandian__x.push_back(bihua[j][2]);
									   duandian__y.push_back(bihua[j][3]);
									   duandian__x.push_back(bihua[j][4]);
									   duandian__y.push_back(bihua[j][5]);
								   }


							   }
							   /*for (int j = 0; j < duandian__x.size(); j++) {
								   printf("%d", duandian__x[j]);
								   printf("%d\n", duandian__y[j]);

							   }*/
							   /*int ifchongfu = 0;
							   for (int j = 0; j < guiji.size(); j++) {
								   if (bihua[j][0] == bihuadaihao2) {
									   if (ifchongfu == 0) {
										   printf("第%d笔:", bihuadaihao3);
										   bihuadaihao3++;
										   int min = 0;
										   int max = 0;
										   int biaoji1 = 0;
										   int biaoji2 = 0;
										   if (bihua[j][8] == 2) {
											   int min = duandian__y[0];

											   for (int k = 1; k < duandian__y.size(); k++) {
												   if (duandian__y[k] < min) {
													   min = duandian__y[k];
													   biaoji1 = k;
												   }
											   }
											   int max = duandian__y[0];
											   for (int k = 1; k < duandian__y.size(); k++) {
												   if (duandian__y[k] >max) {
													   max = duandian__y[k];
													   biaoji2 = k;
												   }
											   }
											   printf("开始点:（%d，%d）", duandian__x[biaoji1], duandian__y[biaoji1]);
											   printf("结束点:（%d，%d）", duandian__x[biaoji2], duandian__y[biaoji2]);

										   }
										   if (bihua[j][8] == 1) {
											   int min = duandian__x[0];

											   for (int k = 1; k < duandian__x.size(); k++) {
												   if (duandian__x[k] < min) {
													   min = duandian__x[k];
													   biaoji1 = k;
												   }
											   }
											   int max = duandian__x[0];
											   for (int k = 1; k < duandian__x.size(); k++) {
												   if (duandian__x[k] > max) {
													   max = duandian__x[k];
													   biaoji2 = k;
												   }
											   }
											   printf("开始点:（%d，%d）", duandian__x[biaoji1], duandian__y[biaoji1]);
											   printf("结束点:（%d，%d）", duandian__x[biaoji2], duandian__y[biaoji2]);

										   }
										   if (bihua[j][8] == 3) {
											   int min = duandian__x[0];

											   for (int k = 1; k < duandian__x.size(); k++) {
												   if (duandian__x[k] < min) {
													   min = duandian__x[k];
													   biaoji1 = k;
												   }
											   }
											   int max = duandian__x[0];
											   for (int k = 1; k < duandian__x.size(); k++) {
												   if (duandian__x[k] > max) {
													   max = duandian__x[k];
													   biaoji2 = k;
												   }
											   }
											   printf("开始点:（%d，%d）", duandian__x[biaoji2], duandian__y[biaoji2]);
											   printf("结束点:（%d，%d）", duandian__x[biaoji1], duandian__y[biaoji1]);

										   }
										   printf("轨迹：（");
										   ifchongfu = 1;
									   }

									   if (bihua[j][8] == 1) {
										   bihuadaihao = 1;
										   if (bihua[j][1] == 2) {
											   //printf("6");
											   guijifanzhuan.push_back(6);
										   }
										   if (bihua[j][1] == 3) {
											   //printf("7");
											   guijifanzhuan.push_back(7);
										   }
										   if (bihua[j][1] == 4) {
											   //printf("0");
											   guijifanzhuan.push_back(0);
										   }
										   if (bihua[j][1] == 5) {
											   //printf("1");
											   guijifanzhuan.push_back(1);
										   }
										   if (bihua[j][1] == 9) {
											   //printf("9");
											   guijifanzhuan.push_back(9);
										   }
										   if (bihua[j][1] == 1|| bihua[j][1] == 0 || bihua[j][1] == 7 || bihua[j][1] == 6 ) {
											   printf("%d",bihua[j][1]);
										   }



									   }
									   if (bihua[j][8] == 2) {
										   bihuadaihao = 2;
										   if (bihua[j][1] == 2) {
											   guijifanzhuan.push_back(6);
											   //printf("6");
										   }
										   if (bihua[j][1] == 1) {
											   guijifanzhuan.push_back(5);
											   //printf("5");
										   }
										   if (bihua[j][1] == 3) {
											   guijifanzhuan.push_back(7);
											   //printf("7");
										   }
										   if (bihua[j][1] == 9) {
											   guijifanzhuan.push_back(9);
											   //printf("9");
										   }
										   if (bihua[j][1] == 4) {
											   guijifanzhuan.push_back(0);
											   //printf("9");
										   }

										   if ( bihua[j][1] == 7 || bihua[j][1] == 6 || bihua[j][1] == 5) {
											   printf("%d", bihua[j][1]);
										   }
									   }
									   if (bihua[j][8] == 3) {
										   bihuadaihao = 3;
										   if (bihua[j][1] == 1) {
											   guijifanzhuan.push_back(5);
											   //printf("5");
										   }
										   if (bihua[j][1] == 9) {
											   guijifanzhuan.push_back(9);
											   //printf("9");
										   }
										   if (bihua[j][1] == 2) {
											   guijifanzhuan.push_back(6);
											   //printf("6");
										   }
										   if (bihua[j][1] == 0) {
											   guijifanzhuan.push_back(4);
											   //printf("4");
										   }
										   if (bihua[j][1] == 7) {
											   guijifanzhuan.push_back(3);
											   //printf("4");
										   }

										   if (  bihua[j][1] == 4 || bihua[j][1] == 6 || bihua[j][1] == 5) {
											   printf("%d", bihua[j][1]);

										   }
									   }
								   }


							   }
							   int xuhao = 0;
							   for (int m = 0; m < guijifanzhuan.size(); m++) {
								   if (guijifanzhuan[guijifanzhuan.size() - xuhao - 1] != 9) {
									   printf("%d", guijifanzhuan[guijifanzhuan.size() - xuhao - 1]);
								   }
								   xuhao++;
							   }


							   if (guijifanzhuan.size() > 0) {
							   printf(")  ");
							   printf("笔画代号：（%d）", bihuadaihao);
							   if (bihuadaihao == 1) {
								   printf("中文笔画：（横）\n");
								   printf("*********************************************************\n");
								   inputheng++;

							   }
							   if (bihuadaihao == 2) {
								   printf("中文笔画：（竖）\n");
								   printf("*********************************************************\n");
								   inputshu++;

							   }
							   if (bihuadaihao == 3) {
								   printf("中文笔画：（撇）\n");
								   printf("*********************************************************\n");
								   inputpie++;
							   }
							   }


							   bihuadaihao2++;


						   }
						   //printf("%d",inputna);
						   //printf("%d", inputpie);
						   //printf("%d", inputheng);
						   //printf("%d", inputshu);

						   MYSQL mysql; //一个数据库结构体
						   MYSQL_RES* res; //一个结果集结构体
						   MYSQL_ROW row; //char** 二维数组，存放一条条记录
						   //初始化数据库
						   mysql_init(&mysql);
						   //设置编码方式
						   mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
						   //连接数据库
						   //判断如果连接失败就把连接失败的信息显示出来，我们好进行对应修改。
						   // mysql_real_connect参数：2.本地地址 3.你的mysql用户名 4.你的mysql密码 5.数据库名字 6.端口号
						   if (mysql_real_connect(&mysql, "localhost", "root", "111", "书法字字库", 3306, NULL, 0) == NULL) {
							   cout << (mysql_error(&mysql));
						   }
						   //查询数据

						   if (inputstyle == 1) {
							   mysql_query(&mysql, "SELECT * from 王羲之字库");
						   }
							if (inputstyle == 2) {
							   mysql_query(&mysql, "SELECT * from 颜真卿字库");
						   }
						   if (inputstyle == 3) {
							   mysql_query(&mysql, "SELECT * from 欧阳询字库");
						   }

						   //printf("asdasda%d", inputstyle);
						   //获取结果集
						   res = mysql_store_result(&mysql);
						   //显示数据
						   //给ROW赋值，判断ROW是否为空，不为空就打印数据。



						   while (row = mysql_fetch_row(res))

						   {
							   printf("信息************************");
							   printf("%s ", row[0]);//打印ID
							   printf("%s ", row[1]);//打印ID
							   printf("%s ", row[2]);//打印ID
							   printf("%s ", row[3]);//打印ID
							   printf("%s ", row[4]);//打印ID
							   printf("%s ", row[5]);//打印ID
							   printf("%d", inputna);
							   printf("%d", inputpie);
							   printf("%d", inputshu);
							   printf("%d", inputheng);

							   cout << endl;

							   if (*row[1] - 48 == inputna && *row[2] - 48 == inputpie && *row[3] - 48 == inputshu && *row[4] - 48 == inputheng) {



								   String path2 = row[5];

								   Mat output = imread(path2, IMREAD_GRAYSCALE);
								   //imshow("输出图像", output);
								   string outpathname = row[0];
								   string strorder = to_string(shuchuorder);
								   shuchuorder++;
								   imwrite("D:/书法字生成/输出成果/"+strorder+outpathname+".jpg", output);
								   int waittime = 1000;
								   /*if (iflast == 0) {

										waittime = 1000;
								   }
								   if (iflast == 1) {
									   waittime = 1000;
								   }
								   waitKey(waittime);*/
								   /*		}

									   }
									   //初始化
										NPB = 0;//二值化后黑色点数
										NSP = 0;//骨架点数
									   jiaochadian_x.clear();
									   jiaochadian_4x.clear();
									   jiaochadian_y.clear();
									   jiaochadian_4y.clear();
									   guiji_x.clear();
									   guiji_y.clear();
									   gujia2_x.clear();
									   gujia2_y.clear();
									   jiaochadianfujin_x.clear();
									   jiaochadianfujin_y.clear();
									   duandian_x.clear();
									   duandian_y.clear();
									   jieshudian_x.clear();
									   jieshudian_y.clear();
									   guiji.clear();

									   inputna = 0;
										inputpie = 0;
										inputheng = 0;
										inputshu = 0;







									   //释放结果集
									   //mysql_free_result(res);
									   //关闭数据库
									   //mysql_close(&mysql);
									   //停留等待
									   //getchar();




								   }
								   string UTF8ToGB(const char* str)
								   {
									   string result;
									   WCHAR *strSrc;
									   LPSTR szRes;

									   //获得临时变量的大小
									   int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
									   strSrc = new WCHAR[i + 1];
									   MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

									   //获得临时变量的大小
									   i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
									   szRes = new CHAR[i + 1];
									   WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

									   result = szRes;
									   delete[]strSrc;
									   delete[]szRes;

									   return result;
								   }

								   vector<string>danziziku;
								   vector<string>bushoudanziziku;

								   int ifdanziexist(string word) {
									   int a = 0;
									   for (int i = 0; i < danziziku.size();i++) {
										   if (word == danziziku[i]) {
											   a = 1;

											   break;
										   }




									   }
									   return a;


								   }
								   int ifbushoudanziexist(string word) {
									   int a = 0;
									   for (int i = 0; i < bushoudanziziku.size(); i++) {
										   if (word == bushoudanziziku[i]) {
											   a = 1;

											   break;
										   }




									   }
									   return a;


								   }*/
};

