#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("G://picture//77.jpg", 1);
	Mat dstMat, binMat;
	cvtColor(srcMat, dstMat, COLOR_BGR2HSV);		//RGB转化HSV
	vector<Mat> channels;
	split(dstMat, channels);		//分离通道

	//namedWindow("S", WINDOW_NORMAL);			//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("S", channels.at(1));
	
	//将S通道的图像复制，然后处理
	Mat S_Mat;
	channels.at(1).copyTo(S_Mat);
	
	threshold(S_Mat, binMat, 120, 255, THRESH_BINARY);		//二值化
	//namedWindow("bin", WINDOW_NORMAL);		//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("bin", binMat);
	//通过findContours函数寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binMat, contours, RETR_LIST, CHAIN_APPROX_NONE);

	//绘制轮廓
	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);		//获取外界四边形
		if (fabs(rbox.size.width * 1.0 / rbox.size.height - 1) < 0.3 && rbox.size.width > 10)		//筛选
		{			
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; ++j) {
				cv::line(srcMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(255, 255, 0), 1, LINE_AA);		//绘制外接四边形
			}
		}
	}
	//namedWindow("topic1", WINDOW_NORMAL);			//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("topic1", srcMat);
	waitKey(0);
	return 0;
}