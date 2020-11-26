#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("G:/picture/55.png", 1);
	Mat dstMat, binMat;
	cvtColor(srcMat, dstMat, COLOR_BGR2GRAY);
	threshold(dstMat, binMat, 0, 255, THRESH_OTSU);
	imshow("bin", binMat);
	//通过findContours函数寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binMat, contours, RETR_LIST,CHAIN_APPROX_NONE);

	//绘制轮廓,内填充
	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		if (fabs(rbox.size.width * 1.0 / rbox.size.height - 1) < 0.1 && rbox.size.width > 10)
			drawContours(srcMat, contours, i, Scalar(0, 255, 255), -1, 8);
	}
	imshow("rim", srcMat);
	waitKey(0);
}