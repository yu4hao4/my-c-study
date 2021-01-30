#include <opencv2\imgproc\types_c.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstring>
#include <opencv2\imgproc\imgproc.hpp>
#include<stack>
#include<numeric>


using namespace cv;
using namespace std;


void connectRe(const cv::Mat& _binImg, cv::Mat& _lableImg)
{


	if (_binImg.empty() ||
		_binImg.type() != CV_8UC1)
	{
		return;
	}

	_lableImg.release();
	_binImg.convertTo(_lableImg, CV_32SC1);

	int label = 1;  // start by 2

	int rows = _binImg.rows - 1;
	int cols = _binImg.cols - 1;
	for (int i = 1; i < rows - 1; i++)
	{
		int* data = _lableImg.ptr<int>(i);
		for (int j = 1; j < cols - 1; j++)
		{
			if (data[j] == 1)
			{
				stack<std::pair<int, int>> neighborPixels;
				neighborPixels.push(pair<int, int>(i, j));     // pixel position: <i,j>
				++label;  // begin with a new label
				while (!neighborPixels.empty())
				{
					pair<int, int> curPixel = neighborPixels.top();
					int curX = curPixel.first;
					int curY = curPixel.second;
					_lableImg.at<int>(curX, curY) = label;

					neighborPixels.pop();

					if (_lableImg.at<int>(curX, curY - 1) == 1)
					{
						neighborPixels.push(std::pair<int, int>(curX, curY - 1));
					}
					if (_lableImg.at<int>(curX, curY + 1) == 1)
					{
						neighborPixels.push(std::pair<int, int>(curX, curY + 1));
					}
					if (_lableImg.at<int>(curX - 1, curY) == 1)
					{
						neighborPixels.push(std::pair<int, int>(curX - 1, curY));
					}
					if (_lableImg.at<int>(curX + 1, curY) == 1)
					{
						neighborPixels.push(std::pair<int, int>(curX + 1, curY));
					}
				}
			}
		}
	}
}
void LargestConnecttedComponent(Mat srcImage, Mat &dstImage)
{
	Mat temp;
	Mat labels;
	srcImage.copyTo(temp);
	int n_comps = connectedComponents(temp, labels, 4, CV_16U);
	vector<int> histogram_of_labels;
	for (int i = 0; i < n_comps; i++)
	{
		histogram_of_labels.push_back(0);
	}

	int rows = labels.rows;
	int cols = labels.cols;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			histogram_of_labels.at(labels.at<unsigned short>(row, col)) += 1;
		}
	}
	histogram_of_labels.at(0) = 0;


	int maximum = 0;
	int max_idx = 0;
	for (int i = 0; i < n_comps; i++)
	{
		if (histogram_of_labels.at(i) > maximum)
		{
			maximum = histogram_of_labels.at(i);
			max_idx = i;
		}
	}


	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (labels.at<unsigned short>(row, col) == max_idx)
			{
				labels.at<unsigned short>(row, col) = 255;
			}
			else
			{
				labels.at<unsigned short>(row, col) = 0;
			}
		}
	}

	labels.convertTo(dstImage, CV_8U);
}

void fillHole(const Mat srcBw, Mat &dstBw)
{
	Size m_Size = srcBw.size();
	Mat Temp = Mat::zeros(m_Size.height + 2, m_Size.width + 2, srcBw.type());
	srcBw.copyTo(Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)));

	cv::floodFill(Temp, Point(0, 0), Scalar(255));

	Mat cutImg;
	Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)).copyTo(cutImg);

	dstBw = srcBw | (~cutImg);
}
double myOtsu(Mat&image, int startI, int endI) {
	int th = 0;
	float hist[256] = { 0 };
	uchar* data = image.data;
	double total = 0;

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			hist[data[i*image.step + j]]++;
			if (image.at<uchar>(i, j) != 0)
				total++;
		}
	}
	int s, e;
	s = startI > 0 ? startI : 0;
	e = endI < 255 ? endI : 255;

	double w0, w1, u0, u1;
	double varValue = 0;
	for (int i = s; i <= e; i++) {
		w1 = 0;		u1 = 0;		w0 = 0;		u0 = 0;
		for (int j = s; j <= i; j++) {
			w1 += hist[j];
			u1 += j * hist[j];
		}
		u1 = u1 / w1;
		w1 = w1 / total;
		for (int k = i + 1; k < e; k++)
		{
			w0 += hist[k];
			u0 += k * hist[k];
		}
		if (w0 == 0)
		{
			break;
		}
		u0 = u0 / w0;
		w0 = w0 / total;
		double varValueI = w0 * w1*(u1 - u0)*(u1 - u0);
		if (varValue < varValueI)
		{
			varValue = varValueI;
			th = i;
		}

	}
	return th;
}
string getLung(string filePath) {
	Mat pic = imread(filePath);
	Mat grayP, binarizedPic, largestC,bwfull,mask,newMask;
	Mat finalPic;
	string res = "pure";
	if (!pic.data) {
		exit(1);
	}
	//imshow("origin", pic);
	cvtColor(pic, grayP, CV_BGR2GRAY);

	threshold(grayP, binarizedPic, 150, 255, CV_THRESH_BINARY);
	//imshow("2", binarizedPic);
	LargestConnecttedComponent(binarizedPic, largestC);
	fillHole(largestC, bwfull);
	//imshow("full", bwfull);
	mask = bwfull - binarizedPic;
	//imshow("mask", mask);
	newMask = mask;
	for (int i = 0; i < newMask.rows; i++) {
		for (int j = 0; j < newMask.cols; j++) {
			if (newMask.at<uchar>(i, j) != 0)
				newMask.at<uchar>(i, j) = 1;
		}
	}
	finalPic = grayP.mul(newMask);
	int s=255;
	for (int i = 0; i < finalPic.rows; i++) {
		for (int j = 0; j < finalPic.cols; j++) {
			if (finalPic.at<uchar>(i, j) < s&&finalPic.at<uchar>(i, j) != 0)
				s = finalPic.at<uchar>(i, j);
		}
	}
	int th = myOtsu(finalPic, s, 255);
	for (int i = 0; i < finalPic.rows; i++) {
		for (int j = 0; j < finalPic.cols; j++) {
			if (finalPic.at<uchar>(i, j) > th)
				finalPic.at<uchar>(i, j) = 255;
		}
	}
	imshow("pic", finalPic);
	res.append(filePath);
	imwrite(res, finalPic);	
	return res;
}




int main() {
	string str=getLung("1.jpg");
	cvWaitKey(0);
	system("pause");
	return 0;

}