#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("G://picture//66.jpg", 1);
	Mat dstMat, binMat,result;
	cvtColor(srcMat, dstMat, COLOR_BGR2GRAY);		//灰度化
	threshold(dstMat, result, 0, 255, THRESH_OTSU);		//二值化

	Mat stt = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(result, binMat, 2, stt, Point(-1, -1), 1, BORDER_CONSTANT, morphologyDefaultBorderValue());		//开运算

	imshow("bin", binMat);
	//通过findContours函数寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binMat, contours, RETR_LIST, CHAIN_APPROX_NONE);

	//绘制轮廓
	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		if (fabs(rbox.size.width * 1.0 / rbox.size.height - 1) < 0.1 && rbox.size.width > 20)		//筛选符合要求的外界四边形
		{
			drawContours(srcMat, contours, i, Scalar(0, 255, 255), 1, 8);		//绘制轮廓
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; ++j) {
				cv::line(srcMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 0, 255), 2, CV_AA);		//绘制外接四边形
			}
		}
	}
	imshow("src", srcMat);
	waitKey(0);
}
