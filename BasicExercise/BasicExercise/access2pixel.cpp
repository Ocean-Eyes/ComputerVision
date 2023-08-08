#include <iostream>
#include <opencv2/highgui.hpp>

cv::Mat cvtGray(cv::Mat src_img);

int main()
{
	cv::Mat img_orig = cv::imread("Lenna.png");
	cv::Mat img_gray;
	
	img_gray = cvtGray(img_orig);
	int i, j;

	// 1. Mat::at
	for (i = 0; i < img_gray.rows; i++)
	{
		for (j = 0; j < img_gray.cols; j++)
		{
			if (i == 25 && j == 25)
			{
				std::cout << "Mat::at result : " << static_cast<int>(img_gray.at<uchar>(i, j)) << std::endl;
			}
		}
	}

	// 2. Mat::ptr
	for (i = 0; i < img_gray.rows; i++)
	{
		uchar* pt = img_gray.ptr<uchar>(i);
		
		for (j = 0; j < img_gray.cols; j++)
		{
			if (i == 25 && j == 25)
			{
				std::cout << "Mat::ptr result : " << static_cast<int>(pt[j]) << std::endl;
			}
		}
	}

	// 3. Mat::data
	uchar* pt2 = img_gray.data;

	for (i = 0; i < img_gray.rows; i++)
	{
		for (j = 0; j < img_gray.cols; j++)
		{
			if (i == 25 && j == 25)
			{
				std::cout << "Mat::data result : " << static_cast<int>(pt2[img_gray.cols * i + j]) << std::endl;
			}
		}
	}

	cv::waitKey();
	cv::destroyAllWindows();
	
	return 0;
}

cv::Mat cvtGray(cv::Mat src_img)
{
	cv::Mat bgr[3];
	cv::Mat dst_img;

	cv::split(src_img, bgr);
	dst_img = bgr[0] * 0.299 + bgr[1] * 0.587 + bgr[2] * 0.114;

	return dst_img;
}