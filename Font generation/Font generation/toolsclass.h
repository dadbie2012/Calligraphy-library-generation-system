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
using namespace std;
using namespace cv;
class toolsclass

{
public:
	//找取最接近某个值的元素
	double colsest(vector<double> &orgin,double num) {
		double min = 99999;
		double standard = 0;
		for (int i = 0; i < orgin.size();i++) {
			if (abs(orgin[i]-num)<min) {
				min = abs(orgin[i] - num);
				standard = orgin[i];
			
			}
		}

		return standard;
	}
};

