#include<iostream>
#include<opencv2/opencv.hpp>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<sstream>
#include<direct.h>//Ŀ¼����ͷ

#include<Windows.h>

using namespace cv;
using namespace std;

#include "TakePhoto.h"

//#pragma  comment(lib,"D:\\opencv\\build\\x86\\vc11\\staticlib\\opencv_ts300.lib")//Ŀǰû���κ���;

string strFirstWindowsName="*****�ں�֪ʶ,'���س�'�رմ���,���л����ڿ�,Ȼ���X@���п�ѧ��";

void MirrorTrans(const Mat &src, Mat &dst);//������



//////////////////////////////////////////////////////////////////////////
//**2015��7��25�� 20:56:00
//**Author:dalerkd
//**use:TakePhoto use OpenCV.
//return:
//-2:Can open VideoCapture
//1:Success
int TakePhoto()

{	
	string strKZM="";
	string strCreateDirectName="��Ƭ������";
	char cCheckInput=0;

	VideoCapture objVCA(0);

	_mkdir(strCreateDirectName.c_str());//�������ڴ����Ƭ��Ŀ¼

	if (!objVCA.isOpened())
	{
		MessageBox(NULL,TEXT("����������ɱ��������������ͷ,��Ȼ��ô����?.������ĵ��Ը���û������ͷ,����ͽ��������."),TEXT("��ʾ"),MB_OK|MB_ICONINFORMATION);
		return -2;
	}
	cout<<""<<endl;cout<<""<<endl;cout<<""<<endl;
	cout<<"          ��������õ�����Ƭ�ĸ�ʽ ǰ�� ���ֻس�:"<<endl;
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
			cout <<"�߼�ģʽ:"<<endl;
			cout <<"�����������ʹ�ö��14�ָ�ʽ����չ��,��������Ӧ��ͼƬ,�����һ���������,������������Ƭ�Զ��洢��ʱ�����,��Ȼ������������б�����."<<endl;
			cout <<"��������ϣ���õ���Ƭ����չ����س�:"<<endl;

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
	Mat MatempMirror;//������
	bool bResolution=1;//�ֱ���

	while(1)
	{
		objVCA.read(MatFirst);

		MatempMirror=MatFirst.clone();
		MirrorTrans(MatFirst,MatempMirror);

		imshow(strFirstWindowsName,MatempMirror);
		if (true==bResolution)
		{
			bResolution=false;
			cout<<"�������ͷ�ֱ���Ϊ:"<<MatFirst.cols<<"*"<<MatFirst.rows<<"="<<MatFirst.cols*MatFirst.rows<<endl;
		}

		if (13==waitKey(33))
		{	
			//ƴ��һ����ʽΪ:YearMonthDay_HourMinuteSecond���ļ���.
			SYSTEMTIME stSys;
			stringstream stTimeStrTemp;
			string strFileName;		//�����ļ���
			string strTimeNameTemp;

			strFileName=strCreateDirectName+"\\";//����ǰ�治�ܼ�"\\"
			
			GetLocalTime(&stSys);    /* ��ȡϵͳʱ��*/
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
			imshow("���ĳɹ�,��������ľ��ѧϰ��֪ʶ?",MatSuc);

			system("cls");
			cout<<"���ɵ���Ƭ�ڱ������Աߵ�\""<<strCreateDirectName<<"\"�ļ���"<<endl;
			
			ShellExecuteA(NULL,"Open",strCreateDirectName.c_str(),"",0,1);//Why use A not W?string is A;

			waitKey(0);

			return 1;//Success return
		}
	}

}


//��������������http://www.cnblogs.com/wangguchangqing/p/4039095.html ,����:��ų���
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