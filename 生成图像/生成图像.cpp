// ����ͼ��.cpp : �������̨Ӧ�ó������ڵ㡣
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
��������
*/
char base[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\��־��\\�γ�\\������Ӿ�\\����ҵ\\ʵ������\\Images\\";
char trainSetPath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\��־��\\�γ�\\������Ӿ�\\����ҵ\\ʵ������\\Feature\\trainSet.csv";
char trainSetXPath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\��־��\\�γ�\\������Ӿ�\\����ҵ\\ʵ������\\Feature\\trainSetX.csv";
char trainSetYPath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\��־��\\�γ�\\������Ӿ�\\����ҵ\\ʵ������\\Feature\\trainSetY.csv";
char codePath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\��־��\\�γ�\\������Ӿ�\\����ҵ\\ʵ������\\Code\\";
char codeLabelPath[200] = "C:\\Users\\zhangzhizhi\\Documents\\Everyone\\��־��\\�γ�\\������Ӿ�\\����ҵ\\ʵ������\\CodeLabel\\label.txt";
char letterSet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int fontType[6] = { 0, 2, 3, 4, 6, 7 };
/**
����ѵ����
*/
void produceTrainSet()
{
	// ����ԭʼͼƬ��ֵ
	Mat M(3240, 785, CV_8UC1, Scalar::all(255));	//ȫ��
	Mat Mx(3240, 784, CV_8UC1, Scalar::all(255));	//ֻ��x
	Mat My(3240, 1, CV_8UC1, Scalar::all(255));	//ֻ��y
	// ������ͬ���
	int total = -1;
	for (int i = 0; i < 36; i++)
	{
		int count = 0;
		// ������������
		for (int j = 0; j < 6; j++)
		{
			// ���ò�ͬ��ϸ
			for (int k = 1; k <= 3; k++)
			{
				// ���ò�ͬ�����С
				for (int l = 0; l < 5; l++)
				{
					char path[200];
					sprintf(path, "%s%d_%d.jpg", base, i, count++);
					// ����ͼƬ
					Mat Img(28, 28, CV_8UC1, Scalar::all(255));
					char value[1];
					sprintf(value, "%c", letterSet[i]);
					// ���������С
					int baseline = 0;
					Size textSize = getTextSize(value, fontType[j], 0.1*l + 0.8, k, &baseline);
					baseline += k;
					// �ı�����
					Point textOrg((Img.cols - textSize.width) / 2, (Img.rows + textSize.height) / 2);
					putText(Img, value, textOrg, fontType[j], 0.1*l + 0.8, CV_RGB(0, 0, 0), k, 6, false);
					// д��ͼƬ
					imwrite(path, Img);

					//// ����ͼƬ
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
	//// ��CSV��ʽд��
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
������֤��
*/
void produceCode()
{
	Mat label(100, 4, CV_8UC1, Scalar::all(255));	//��ǩ
	// �������100����֤��
	for (int i = 0; i < 100; i++)
	{
		// ͼƬ·��
		char path[200];
		sprintf(path, "%s%d.jpg", codePath, i);
		// �������
		srand((unsigned)i);
		// ����ͼƬ���������
		Mat Img(46, 128, CV_8UC3, Scalar::all(rand() % 20 + 225));
		uchar* labelptr = label.ptr<uchar>(i);
		for (int j = 0; j < 4; j++)
		{
			//���λ�ã�����ַ���������壬�����ϸ�������С,�����ɫ
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
	// ��CSV��ʽд��
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