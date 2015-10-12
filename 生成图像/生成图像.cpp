// 生成图像.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace cv;
using namespace std;
/**
公共变量
*/
char base[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\张志智\\课程\\计算机视觉\\大作业\\实验数据\\Images\\";
char trainSetPath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\张志智\\课程\\计算机视觉\\大作业\\实验数据\\Feature\\trainSet.csv";
char trainSetXPath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\张志智\\课程\\计算机视觉\\大作业\\实验数据\\Feature\\trainSetX.csv";
char trainSetYPath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\张志智\\课程\\计算机视觉\\大作业\\实验数据\\Feature\\trainSetY.csv";
char codePath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\张志智\\课程\\计算机视觉\\大作业\\实验数据\\Code\\";
char codeLabelPath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\张志智\\课程\\计算机视觉\\大作业\\实验数据\\CodeLabel\\label.txt";
char letterSet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int fontType[6] = { 0, 2, 3, 4, 6, 7 };
/**
产生训练集
*/
void produceTrainSet()
{
	// 定义原始图片的值
	Mat M(3240, 785, CV_8UC1, Scalar::all(255));	//全部
	Mat Mx(3240, 784, CV_8UC1, Scalar::all(255));	//只有x
	Mat My(3240, 1, CV_8UC1, Scalar::all(255));	//只有y
	// 遍历不同类别
	int total = -1;
	for (int i = 0; i < 36; i++)
	{
		int count = 0;
		// 设置字体类型
		for (int j = 0; j < 6; j++)
		{
			// 设置不同粗细
			for (int k = 1; k <= 3; k++)
			{
				// 设置不同字体大小
				for (int l = 0; l < 5; l++)
				{
					char path[200];
					sprintf(path, "%s%d_%d.jpg", base, i, count++);
					// 创建图片
					Mat Img(28, 28, CV_8UC1, Scalar::all(255));
					char value[1];
					sprintf(value, "%c", letterSet[i]);
					// 计算字体大小
					int baseline = 0;
					Size textSize = getTextSize(value, fontType[j], 0.1*l + 0.8, k, &baseline);
					baseline += k;
					// 文本居中
					Point textOrg((Img.cols - textSize.width) / 2, (Img.rows + textSize.height) / 2);
					putText(Img, value, textOrg, fontType[j], 0.1*l + 0.8, CV_RGB(0, 0, 0), k, 6, false);
					// 写入图片
					imwrite(path, Img);

					//// 遍历图片
					//uchar* totalptr = M.ptr<uchar>(++total);
					//uchar* totalptrx = Mx.ptr<uchar>(total);
					//uchar* totalptry = My.ptr<uchar>(total);
					//uchar* p;
					//for (int ii = 0; ii < 28; ii++)
					//{
					//	p = Img.ptr<uchar>(ii);
					//	for (int jj = 0; jj < 28; jj++)
					//	{
					//		totalptr[28 * ii + jj] = p[jj]/255;
					//		totalptrx[28 * ii + jj] = p[jj]/255;
					//	}
					//}
					//totalptr[784] = i;
					//totalptry[0] = i;
				}
			}
		}
	}
	//// 以CSV格式写入
	//ofstream ofile;
	//ofile.open(trainSetPath);
	//ofile << format(M, "csv");
	//ofile.close();
	//ofile.open(trainSetXPath);
	//ofile << format(Mx, "csv");
	//ofile.close();
	//ofile.open(trainSetYPath);
	//ofile << format(My, "csv");
	//ofile.close();
}
/**
产生验证码
*/
void produceCode()
{
	Mat label(100, 4, CV_8UC1, Scalar::all(255));	//标签
	// 随机生成100张验证码
	for (int i = 0; i < 100; i++)
	{
		// 图片路径
		char path[200];
		sprintf(path, "%s%d.jpg", codePath, i);
		// 随机种子
		srand((unsigned)i);
		// 创建图片，随机背景
		Mat Img(46, 128, CV_8UC3, Scalar::all(rand() % 20 + 225));
		uchar* labelptr = label.ptr<uchar>(i);
		for (int j = 0; j < 4; j++)
		{
			//随机位置，随机字符，随机字体，随机粗细，随机大小,随机颜色
			int randX = 28 + rand() % 10;
			int randY = 32*j +2+ rand() % 4;
			int randCh = rand() % 36;
			int randFont = rand() % 6;
			int randThick = 1+ rand() % 3;
			int randSize = rand() % 5;
			int randR = rand() % 255;
			int randG = rand() % 255;
			int randB = rand() % 255;
			char value[1];
			sprintf(value, "%c", letterSet[randCh]);
			labelptr[j] = randCh;
			putText(Img, value, Point(randY, randX), fontType[randFont], 0.1*randSize + 0.8, CV_RGB(randR, randG, randB), randThick, 6, false);
		}
		imwrite(path, Img);
	}
	// 以CSV格式写入
	ofstream ofile;
	ofile.open(codeLabelPath);
	ofile << format(label, "csv");
	ofile.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
	produceTrainSet();
	//produceCode();
	waitKey(0);
	return 0;
}