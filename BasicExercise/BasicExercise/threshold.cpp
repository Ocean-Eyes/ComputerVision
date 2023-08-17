#include <opencv2/highgui.hpp>

cv::Mat cvtGray(cv::Mat src_img);
<<<<<<< HEAD
cv::Mat threshImage(cv::Mat &img_gray);
=======
cv::Mat threshImage(cv::Mat& img_gray);
>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46

int main()
{
	cv::Mat img_orig = cv::imread("Lenna.png");
	cv::Mat img_gray;
	cv::Mat img_thresholded;

	// Show original image
	cv::imshow("Original Image", img_orig);
<<<<<<< HEAD
	
	// Convert into grayscale Image
	img_gray = cvtGray(img_orig);
	cv::imshow("Grayscale Image", img_gray);
	
	// Threshold image
	img_thresholded = threshImage(img_gray);	
=======

	// Convert into grayscale Image
	img_gray = cvtGray(img_orig);
	cv::imshow("Grayscale Image", img_gray);

	// Threshold image
	img_thresholded = threshImage(img_gray);
>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	cv::imshow("Thresholded Image", img_thresholded);

	cv::waitKey();
	cv::destroyAllWindows();
<<<<<<< HEAD
		
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	return 0;
}

cv::Mat cvtGray(cv::Mat src_img)
{
	// 1. make 2 empty Mat objects for storing 3 channel and destination image respectively
	cv::Mat bgr[3];
	cv::Mat dst_img;
<<<<<<< HEAD
	
	// 2. split the channel
	cv::split(src_img, bgr);
	
=======

	// 2. split the channel
	cv::split(src_img, bgr);

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	// 3. apply formulation
	dst_img = bgr[0] * 0.299 + bgr[1] * 0.587 + bgr[2] * 0.114;

	return dst_img;
}

<<<<<<< HEAD
cv::Mat threshImage(cv::Mat &img_gray)
=======
cv::Mat threshImage(cv::Mat& img_gray)
>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
{
	for (int i = 0; i < img_gray.rows; i++)
	{
		for (int j = 0; j < img_gray.cols; j++)
		{
			if (img_gray.at<uchar>(i, j) < 64)
			{
				img_gray.at<uchar>(i, j) = 64;
			}
			else if (img_gray.at<uchar>(i, j) < 128)
			{
				img_gray.at<uchar>(i, j) = 128;
			}
			else if (img_gray.at<uchar>(i, j) < 192)
			{
				img_gray.at<uchar>(i, j) = 192;
			}
			else
			{
				img_gray.at<uchar>(i, j) = 255;
			}
		}
	}

	return img_gray;
}