#pragma once
class start
{

	/*//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��1.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);

	//Mat a = imread("D:/����֮�ֿ�/��/ͤ.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	//Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);*/
	/*	Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  bihuafenge *fenge=new bihuafenge();
	  vector<double> aaa;
	  Mat aaaa = a.clone();
	  Mat b=fenge->thinImage(a);
	  Mat c = b;
	  fenge->endPointAndintersectionPointDetection(b,a);
	  fenge->xunhuan2(b,c,aaaa,aaa);
	  cout << "-----------" <<aaa[4] << endl;*/


	  //����Դ
	 /* Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  //Mat  = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat b = imread("D:/����֮�ֿ�/��/��1.jpg", IMREAD_GRAYSCALE);
	  Mat c = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat d = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat e = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat f = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);

	  Mat g = imread("D:/����֮�ֿ�/��/ͤ.jpg", IMREAD_GRAYSCALE);
	  Mat h = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat i = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat j = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat k = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat l = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);*/
	  /*Mat a = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat b = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat c = imread("D:/����֮�ֿ�/��/��3.jpg", IMREAD_GRAYSCALE);
	  Mat d = imread("D:/����֮�ֿ�/��/��.jpg", IMREAD_GRAYSCALE);
	  Mat e = imread("D:/����֮�ֿ�/��/��1.jpg", IMREAD_GRAYSCALE);
	  Mat l = imread("D:/����֮�ֿ�/��/ͤ.jpg", IMREAD_GRAYSCALE);
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



	   //�ʻ����㣨�켣���ʻ��أ��ʻ�б�ʣ���ʼб�ʣ�����б�ʣ�
	   //first->bihuaguiji(b);


	/*int NPB = 0;//��ֵ�����ɫ����
	int NSP = 0;//�Ǽܵ���

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




		/*for (int i = 0; i < gujia2_x.size(); i++) {
			test.at<uchar>(gujia2_y[i], gujia2_x[i]) =1;

		}*/

		/*src.copyTo(dst);
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
		}*/
		// ���������
		   /*for (vector<CvPoint>::iterator i = intersectionPoint.begin(); i != intersectionPoint.end(); ++i)
		   {
			   circle(src, cvPoint(i->x, i->y), 5, Scalar(255));
			   //cvPoint(i->x, i->y) =255;
			   //src.at<uchar>(i->x, i->y) = 255;
		   }*/
		   /*	endpoint.clear();//���ݻ���
			   intersectionPoint.clear();
			   for (int i = 0; i < jiaochadian_x.size(); i++) {
				   printf("���ս���㣺%d,%d\n", jiaochadian_x[i], jiaochadian_y[i]);

			   }
		   }
		   void zuobiao(Mat & src,uchar *p, uchar *m,int i,int j) {

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
				   printf("�����㣺(%d,%d)\n", j, i);
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
				   printf("�����㣺(%d,%d)\n",j,i);
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
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   guiji.push_back(2);
							   printf("�켣��");
							   printf("2");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p - src.step + j), p + j, i - 1, j);

						   }
						   if (p3 == 1 && biaoji3 == 0) {
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   guiji.push_back(1);
							   printf("�켣��");
							   printf("1");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p - src.step + j + 1), p + j, i - 1, j + 1);

						   }

						   if (p4 == 1 && biaoji4 == 0) {
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   guiji.push_back(0);
							   printf("�켣��");
							   printf("0");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + j + 1), p + j, i, j + 1);
						   }

						   if (p5 == 1 && biaoji5 == 0) {
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

						   if (p6 == 1 && biaoji6 == 0) {
							   printf("��%d�ʡ�������", dijibi);
							   dijibi++;
							   printf("�˵㣺(%d , %d)", j, i);
							   guiji.push_back(6);
							   printf("�켣��");
							   printf("6");
							   guiji_y.push_back(i);
							   guiji_x.push_back(j);
							   duandian_x.push_back(j);
							   duandian_y.push_back(i);
							   zuobiao(src, (p + src.step + j), p + j, i + 1, j);

						   }

						   if (p7 == 1 && biaoji7 == 0) {
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

						   if (p8 == 1 && biaoji8 == 0) {
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

						   if (p9 == 1 && biaoji9 == 0) {
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




			   //int NS = duandianbiaoji;//�ʻ���Ŀ
			   //double canshu1 = 0.3333;

			   printf("%d\n", NPB);//��ֵ�����ɫ����
			   printf("%d\n", guiji.size());//�Ǽܵ����


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
				   printf("��%d�ʣ�0ռ��%lf��1ռ��%lf��2ռ��%lf��3ռ��%lf��4ռ��%lf��5ռ��%lf��6ռ��%lf��7ռ��%lf\n��", puanduanbihua, count0 / countALL, count1 / countALL, count2 / countALL, count3 / countALL, count4 / countALL, count5 / countALL, count6 / countALL, count7 / countALL);
				   //��
				   if (count0 / countALL > 0.7 || count4 / countALL > 0.7) {

					   for (int i = 0; i < guiji.size(); i++) {
						   if (bihua[i][0] == puanduanbihua) {

							   bihua[i][8] = 1;
						   }
					   }
				   }


				   //��
				   if (count2 / countALL > 0.7 || count6 / countALL > 0.7) {

					   for (int i = 0; i < guiji.size(); i++) {
						   if (bihua[i][0] == puanduanbihua) {
							   bihua[i][8] = 2;
						   }
					   }
				   }

				   //Ʋ
				   if (count5 / countALL > 0.3 || count1 / countALL > 0.3 || (count0 / countALL > 0.6&&count1 / countALL > 0.088) || (count4 / countALL > 0.6&&count5 / countALL > 0.088)) {

					   for (int i = 0; i < guiji.size(); i++) {

						   if (bihua[i][0] == puanduanbihua) {


							   bihua[i][8] = 3;
						   }
					   }


				   }
				   //��
				   if (count3 / countALL > 0.3 || count7 / countALL > 0.3) {

					   for (int i = 0; i < guiji.size(); i++) {
						   if (bihua[i][0] == puanduanbihua) {
							   bihua[i][8] = 4;
						   }
					   }


				   }
				   //����
				   /*if (count0 / countALL > 0.3 && count6 / countALL > 0.3) {

					   for (int i = 0; i < guiji.size() ; i++) {
						   if (bihua[i][0] == puanduanbihua) {
							   bihua[i][8] = 5;
						   }
					   }


				   }*/
				   //����
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




				   /*	//�жϷ���1
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

					   //�жϷ���2
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
					   /*//�ѱʻ������еıʻ��źã�������1357������1234
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
						   //2222222222222222222222imshow("�ʻ��ṹ", show);
						   //imwrite("D:/�ʻ��ṹ.jpg", show);


						   for (int i = 0; i < guiji.size(); i++) {
							   printf("��%d�ʣ��켣��%d,�˵����꣨%d,%d��,���������꣨%d,%d��,�켣���꣨%d,%d�����ʻ����ţ���%d��\n", bihua[i][0], bihua[i][1], bihua[i][2], bihua[i][3], bihua[i][4], bihua[i][5], bihua[i][6], bihua[i][7], bihua[i][8]);
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
										   printf("��%d��:", bihuadaihao3);
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
											   printf("��ʼ��:��%d��%d��", duandian__x[biaoji1], duandian__y[biaoji1]);
											   printf("������:��%d��%d��", duandian__x[biaoji2], duandian__y[biaoji2]);

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
											   printf("��ʼ��:��%d��%d��", duandian__x[biaoji1], duandian__y[biaoji1]);
											   printf("������:��%d��%d��", duandian__x[biaoji2], duandian__y[biaoji2]);

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
											   printf("��ʼ��:��%d��%d��", duandian__x[biaoji2], duandian__y[biaoji2]);
											   printf("������:��%d��%d��", duandian__x[biaoji1], duandian__y[biaoji1]);

										   }
										   printf("�켣����");
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
							   printf("�ʻ����ţ���%d��", bihuadaihao);
							   if (bihuadaihao == 1) {
								   printf("���ıʻ������ᣩ\n");
								   printf("*********************************************************\n");
								   inputheng++;

							   }
							   if (bihuadaihao == 2) {
								   printf("���ıʻ���������\n");
								   printf("*********************************************************\n");
								   inputshu++;

							   }
							   if (bihuadaihao == 3) {
								   printf("���ıʻ�����Ʋ��\n");
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

						   MYSQL mysql; //һ�����ݿ�ṹ��
						   MYSQL_RES* res; //һ��������ṹ��
						   MYSQL_ROW row; //char** ��ά���飬���һ������¼
						   //��ʼ�����ݿ�
						   mysql_init(&mysql);
						   //���ñ��뷽ʽ
						   mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
						   //�������ݿ�
						   //�ж��������ʧ�ܾͰ�����ʧ�ܵ���Ϣ��ʾ���������Ǻý��ж�Ӧ�޸ġ�
						   // mysql_real_connect������2.���ص�ַ 3.���mysql�û��� 4.���mysql���� 5.���ݿ����� 6.�˿ں�
						   if (mysql_real_connect(&mysql, "localhost", "root", "111", "�鷨���ֿ�", 3306, NULL, 0) == NULL) {
							   cout << (mysql_error(&mysql));
						   }
						   //��ѯ����

						   if (inputstyle == 1) {
							   mysql_query(&mysql, "SELECT * from ����֮�ֿ�");
						   }
							if (inputstyle == 2) {
							   mysql_query(&mysql, "SELECT * from �������ֿ�");
						   }
						   if (inputstyle == 3) {
							   mysql_query(&mysql, "SELECT * from ŷ��ѯ�ֿ�");
						   }

						   //printf("asdasda%d", inputstyle);
						   //��ȡ�����
						   res = mysql_store_result(&mysql);
						   //��ʾ����
						   //��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�



						   while (row = mysql_fetch_row(res))

						   {
							   printf("��Ϣ************************");
							   printf("%s ", row[0]);//��ӡID
							   printf("%s ", row[1]);//��ӡID
							   printf("%s ", row[2]);//��ӡID
							   printf("%s ", row[3]);//��ӡID
							   printf("%s ", row[4]);//��ӡID
							   printf("%s ", row[5]);//��ӡID
							   printf("%d", inputna);
							   printf("%d", inputpie);
							   printf("%d", inputshu);
							   printf("%d", inputheng);

							   cout << endl;

							   if (*row[1] - 48 == inputna && *row[2] - 48 == inputpie && *row[3] - 48 == inputshu && *row[4] - 48 == inputheng) {



								   String path2 = row[5];

								   Mat output = imread(path2, IMREAD_GRAYSCALE);
								   //imshow("���ͼ��", output);
								   string outpathname = row[0];
								   string strorder = to_string(shuchuorder);
								   shuchuorder++;
								   imwrite("D:/�鷨������/����ɹ�/"+strorder+outpathname+".jpg", output);
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
									   //��ʼ��
										NPB = 0;//��ֵ�����ɫ����
										NSP = 0;//�Ǽܵ���
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







									   //�ͷŽ����
									   //mysql_free_result(res);
									   //�ر����ݿ�
									   //mysql_close(&mysql);
									   //ͣ���ȴ�
									   //getchar();




								   }
								   string UTF8ToGB(const char* str)
								   {
									   string result;
									   WCHAR *strSrc;
									   LPSTR szRes;

									   //�����ʱ�����Ĵ�С
									   int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
									   strSrc = new WCHAR[i + 1];
									   MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

									   //�����ʱ�����Ĵ�С
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

