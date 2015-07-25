#include<iostream>
#include<opencv2/opencv.hpp>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<sstream>
#include<direct.h>//目录控制头

#include<Windows.h>

using namespace cv;
using namespace std;

#include "TakePhoto.h"

//#pragma  comment(lib,"D:\\opencv\\build\\x86\\vc11\\staticlib\\opencv_ts300.lib")//目前没有任何用途

string strFirstWindowsName="*****摆好知识,'按回车'关闭窗口,请切换到黑框,然后点X@冰刃科学家";

void MirrorTrans(const Mat &src, Mat &dst);//镜像函数



//////////////////////////////////////////////////////////////////////////
//**2015年7月25日 20:56:00
//**Author:dalerkd
//**use:TakePhoto use OpenCV.
//return:
//-2:Can open VideoCapture
//1:Success
int TakePhoto()

{	
	string strKZM="";
	string strCreateDirectName="照片在这里";
	char cCheckInput=0;

	VideoCapture objVCA(0);

	_mkdir(strCreateDirectName.c_str());//创建用于存放照片的目录

	if (!objVCA.isOpened())
	{
		MessageBox(NULL,TEXT("少年请让你杀软允许程序打开摄像头,不然怎么拍照?.或者你的电脑根本没有摄像头,这个就解决不了了."),TEXT("提示"),MB_OK|MB_ICONINFORMATION);
		return -2;
	}
	cout<<""<<endl;cout<<""<<endl;cout<<""<<endl;
	cout<<"          输入你想得到的照片的格式 前的 数字回车:"<<endl;
	cout<<"           1 jpg"<<endl;
	cout<<"           2 bmp"<<endl;	
	cout<<""<<endl;
	cout<<"         9 LowMode"<<endl;
	cout<<""<<endl;cout<<""<<endl;cout<<""<<endl;cout<<""<<endl;cout<<""<<endl;cout<<""<<endl;
	cout<<""<<endl;

	cin>>cCheckInput;

	switch (cCheckInput)
	{
	case '1':
		{
			strKZM ="jpg";
			break;
		}
	case '2':
		{
			strKZM ="bmp";
			break;
		}
	case '9':
		{
			cout <<"高级模式:"<<endl;
			cout <<"在这里你可以使用多达14种格式的扩展名,以生成相应的图片,后果是一旦输入错误,将会在拍完照片自动存储的时候崩溃,当然你可以重新运行本程序."<<endl;
			cout <<"请输入你希望得到照片的扩展名后回车:"<<endl;

			cin >>strKZM;
			if (""==strKZM)
			{	
				strKZM="jpg";
			}
			break;
		}
	default:
		{
			strKZM="jpg";
			break;
		}
	}


	Mat MatFirst;
	Mat MatempMirror;//镜像结果
	bool bResolution=1;//分辨率

	while(1)
	{
		objVCA.read(MatFirst);

		MatempMirror=MatFirst.clone();
		MirrorTrans(MatFirst,MatempMirror);

		imshow(strFirstWindowsName,MatempMirror);
		if (true==bResolution)
		{
			bResolution=false;
			cout<<"你的摄像头分辨率为:"<<MatFirst.cols<<"*"<<MatFirst.rows<<"="<<MatFirst.cols*MatFirst.rows<<endl;
		}

		if (13==waitKey(33))
		{	
			//拼组一个格式为:YearMonthDay_HourMinuteSecond的文件名.
			SYSTEMTIME stSys;
			stringstream stTimeStrTemp;
			string strFileName;		//最终文件名
			string strTimeNameTemp;

			strFileName=strCreateDirectName+"\\";//但是前面不能加"\\"
			
			GetLocalTime(&stSys);    /* 获取系统时间*/
			stTimeStrTemp<<stSys.wYear<<stSys.wMonth<<stSys.wDay;
			stTimeStrTemp>>strTimeNameTemp;
			strFileName+=strTimeNameTemp;
			strTimeNameTemp.clear();
			strFileName+="_";
			stTimeStrTemp.clear();
			stTimeStrTemp<<stSys.wHour<<stSys.wMinute<<stSys.wSecond;
			stTimeStrTemp>>strTimeNameTemp;
			strFileName+=strTimeNameTemp;

			strFileName+="."+strKZM;
			
			imwrite(strFileName,MatFirst);
			Mat MatSuc=imread(strFileName);

			destroyWindow(strFirstWindowsName);
			imshow("自拍成功,今天你有木有学习新知识?",MatSuc);

			system("cls");
			cout<<"生成的照片在本程序旁边的\""<<strCreateDirectName<<"\"文件夹"<<endl;
			
			ShellExecuteA(NULL,"Open",strCreateDirectName.c_str(),"",0,1);//Why use A not W?string is A;

			waitKey(0);

			return 1;//Success return
		}
	}

}


//本函数代码来自http://www.cnblogs.com/wangguchangqing/p/4039095.html ,作者:万古长青
void MirrorTrans(const Mat &src, Mat &dst)
{
	CV_Assert(src.depth() == CV_8U);
	dst.create(src.rows, src.cols, src.type());

	int rows = src.rows;
	int cols = src.cols;

	switch (src.channels())
	{
	case 1:
		const uchar *origal;
		uchar *p;
		for (int i = 0; i < rows; i++){
			origal = src.ptr<uchar>(i);
			p = dst.ptr<uchar>(i);
			for (int j = 0; j < cols; j++){
				p[j] = origal[cols - 1 - j];
			}
		}
		break;
	case 3:
		const Vec3b *origal3;
		Vec3b *p3;
		for (int i = 0; i < rows; i++) {
			origal3 = src.ptr<Vec3b>(i);
			p3 = dst.ptr<Vec3b>(i);
			for(int j = 0; j < cols; j++){
				p3[j] = origal3[cols - 1 - j];
			}
		}
		break;
	default:
		break;
	}

}