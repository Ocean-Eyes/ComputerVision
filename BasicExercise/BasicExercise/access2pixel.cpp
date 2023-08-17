#include <iostream>
#include <opencv2/highgui.hpp>

cv::Mat cvtGray(cv::Mat src_img);

int main()
{
	cv::Mat img_orig = cv::imread("Lenna.png");
	cv::Mat img_gray;
<<<<<<< HEAD
	
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	// 1. Grayscale(1-channel)
	img_gray = cvtGray(img_orig);
	int i, j;

	std::cout << "Grayscale results" << std::endl;

	// 1-1) Mat::at
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

	// 1-2) Mat::ptr
	for (i = 0; i < img_gray.rows; i++)
	{
		uchar* pt = img_gray.ptr<uchar>(i);
<<<<<<< HEAD
		
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
		for (j = 0; j < img_gray.cols; j++)
		{
			if (i == 25 && j == 25)
			{
				std::cout << "Mat::ptr result : " << static_cast<int>(pt[j]) << std::endl;
			}
		}
	}

	// 1-3) Mat::data
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

	// 2. BGR(3-channel)

	std::cout << "\nBGR results:" << std::endl;

	// 2-1) Mat::at
	for (i = 0; i < img_orig.rows; i++)
	{
		for (j = 0; j < img_orig.cols; j++)
		{
			uchar b = img_orig.at<cv::Vec3b>(i, j)[0];
			uchar g = img_orig.at<cv::Vec3b>(i, j)[1];
			uchar r = img_orig.at<cv::Vec3b>(i, j)[2];

			if (i == 25 && j == 25)
			{
				std::cout << "Mat::at result : " << static_cast<int>(b) << " " << static_cast<int>(g) << " " << static_cast<int>(r) << std::endl;
			}
		}
	}

	// 2-2) Mat::ptr
	for (i = 0; i < img_orig.rows; i++)
	{
		uchar* ptr = img_orig.ptr<uchar>(i);

		for (j = 0; j < img_orig.cols; j++)
		{
			uchar b = ptr[j * 3];
			uchar g = ptr[j * 3 + 1];
			uchar r = ptr[j * 3 + 2];
<<<<<<< HEAD
		
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
			if (i == 25 && j == 25)
			{
				std::cout << "Mat::ptr result : " << static_cast<int>(b) << " " << static_cast<int>(g) << " " << static_cast<int>(r) << std::endl;
			}
		}
	}

	// 2-3) Mat::data
	uchar* data = img_orig.data;

	for (i = 0; i < img_orig.rows; i++)
	{
		for (j = 0; j < img_orig.cols; j++)
		{
			uchar b = data[i * img_orig.cols * 3 + j * 3];
			uchar g = data[i * img_orig.cols * 3 + j * 3 + 1];
			uchar r = data[i * img_orig.cols * 3 + j * 3 + 2];
<<<<<<< HEAD
		
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
			if (i == 25 && j == 25)
			{
				std::cout << "Mat::data result : " << static_cast<int>(b) << " " << static_cast<int>(g) << " " << static_cast<int>(r) << std::endl;
			}
		}
	}

	cv::waitKey();
	cv::destroyAllWindows();
<<<<<<< HEAD
	
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
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