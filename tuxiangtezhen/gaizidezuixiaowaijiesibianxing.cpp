#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("G://picture//77.jpg", 1);
	Mat dstMat, binMat;
	cvtColor(srcMat, dstMat, COLOR_BGR2HSV);
	vector<Mat> channels;
	split(dstMat, channels);
	//namedWindow("H", WINDOW_NORMAL);//WINDOW_NORMAL�����û�������������
	//imshow("H", channels.at(0));
	namedWindow("S", WINDOW_NORMAL);//WINDOW_NORMAL�����û�������������
	imshow("S", channels.at(1));
	//namedWindow("V", WINDOW_NORMAL);//WINDOW_NORMAL�����û�������������
	//imshow("V", channels.at(2));
	//��Sͨ����ͼ���ƣ�Ȼ����
	Mat S_Mat;
	channels.at(1).copyTo(S_Mat);
	//namedWindow("S", WINDOW_NORMAL);//WINDOW_NORMAL�����û�������������
	//imshow("S", S_Mat);
	threshold(S_Mat, binMat, 120, 255, THRESH_BINARY);
	namedWindow("bin", WINDOW_NORMAL);//WINDOW_NORMAL�����û�������������
	imshow("bin", binMat);
	//ͨ��findContours����Ѱ����ͨ��
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binMat, contours, RETR_LIST, CHAIN_APPROX_NONE);

	//��������
	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		if (fabs(rbox.size.width * 1.0 / rbox.size.height - 1) < 0.3 && rbox.size.width > 10)
		{
			drawContours(srcMat, contours, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; ++j) {
				cv::line(srcMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(255, 255, 255), 2, LINE_AA);
			}
		}
	}
	namedWindow("topic1", WINDOW_NORMAL);//WINDOW_NORMAL�����û�������������
	imshow("topic1", srcMat);
	waitKey(0);
	return 0;

}