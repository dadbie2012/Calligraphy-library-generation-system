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
		if (mysql_real_connect(&mysql, "localhost", "root", "111", "王羲之字库", 3306, NULL, 0) == NULL) {
			cout << (mysql_error(&mysql));
	  }
		mysql_query(&mysql, sentence);
		res = mysql_store_result(&mysql);
		return res;
	}


};

