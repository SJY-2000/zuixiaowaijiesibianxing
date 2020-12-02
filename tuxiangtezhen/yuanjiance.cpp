#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("G:/picture/55.png", 1);
	Mat dstMat, binMat;
	cvtColor(srcMat, dstMat, COLOR_BGR2GRAY);		//灰度化
	threshold(dstMat, binMat, 0, 255, THRESH_OTSU);			//二值化
	
	imshow("bin", binMat);
	//通过findContours函数寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binMat, contours, RETR_LIST,CHAIN_APPROX_NONE);

	//绘制轮廓,内填充
	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);		//获取最小外接四边形
		if (fabs(rbox.size.width * 1.0 / rbox.size.height - 1) < 0.1 && rbox.size.width > 10)		//筛选符合要求的外界四边形
			drawContours(srcMat, contours, i, Scalar(0, 255, 255), -1, 8);		//绘制轮廓，-1绘制实心圆
	}
	imshow("src", srcMat);
	waitKey(0);
}