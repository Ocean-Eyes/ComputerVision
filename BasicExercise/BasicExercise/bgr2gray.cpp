#include <opencv2/highgui.hpp>

cv::Mat cvtGray(cv::Mat img_bgr);

int main()
{
	cv::Mat img_bgr = cv::imread("Lenna.png");
	cv::Mat img_gray;
	img_gray = cvtGray(img_bgr);
	cv::imshow("grayscale image", img_gray);

	cv::waitKey();
	return 0;
}

cv::Mat cvtGray(cv::Mat img_bgr)
{
	// 1. split bgr channel
	cv::Mat bgr[3];
	cv::split(img_bgr, bgr);

	// 2. apply a formula
	cv::Mat img_gray;
	img_gray = bgr[0] * 0.299 + bgr[1] * 0.587 + bgr[2] * 0.114;

	// 3. return grayscale image
	return img_gray;
}