// 21_Smooth_skin.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);

	double scale = 0.5;

	double i_minH = 9;
	double i_maxH = 20;

	double i_minS = 60;
	double i_maxS = 255;

	double i_minV = 66;
	double i_maxV = 255;

	while (1)
	{
		cv::Mat frame;
		cv::Mat hsvMat;
		cv::Mat detectMat;
		cv::Mat smoothMat;

		cap >> frame;
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		rFrame.copyTo(smoothMat);
		int ksize = 3;//����˳ߴ�
		int height = detectMat.rows; //����
		int width = detectMat.cols; //ÿ��Ԫ�ص���Ԫ������
		for (int j = 0; j<height; j++)
		{
			for (int i = 0; i<width; i++)
			{
				if (detectMat.at<uchar>(j, i) == 255)
				{
					for (int t = 0; t < 3; t++)//�ֶ���ֵ�˲�
					{
						float average=0;
						for (int y = 0; y < ksize; y++)
						{
							for (int x = 0; x < ksize; x++)
							{
								average += rFrame.at<Vec3b>(j-1+y, i-1+x)[t];
							}
						}
						average = average/(ksize*ksize);
						smoothMat.at<Vec3b>(j, i)[t] = (int)average;
					}
				}
				//-------------�������ش���------------------------
			} //���д������
		}

		cv::imshow("whie: in the range", detectMat);
		cv::imshow("frame", rFrame);
		cv::imshow("smooth", smoothMat);

		waitKey(30);
	}
}
