#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include<iostream>
#include <QFileDialog>
#include <QThread>
#include <QtDebug>

#include <stdio.h>
#include <string.h>
#include <WinSock.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>

using namespace std;
using namespace cv;




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;
};
