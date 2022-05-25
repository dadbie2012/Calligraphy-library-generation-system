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
using namespace std;
using namespace cv;
class mysqlconnect
{public:
	MYSQL_RES*  mysql(const char *sentence) {
	
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
		if (mysql_real_connect(&mysql, "localhost", "root", "111", "����֮�ֿ�", 3306, NULL, 0) == NULL) {
			cout << (mysql_error(&mysql));
	  }
		mysql_query(&mysql, sentence);
		res = mysql_store_result(&mysql);
		return res;
	}


};

