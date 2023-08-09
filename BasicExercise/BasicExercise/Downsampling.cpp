#include <opencv2/highgui.hpp>


cv::Mat cvtGray(cv::Mat src_img);

int main()
{
	cv::Mat img_orig = cv::imread("Lenna.png");
	cv::Mat img_gray;

	// Original Image
	cv::imshow("Original Image", img_orig);

	// Grayscale Image
	img_gray = cvtGray(img_orig);
	cv::imshow("Grayscale Image", img_gray);

	// Downsampled Image
	int scale = 4;
	int row = static_cast<int>(img_gray.rows / scale);
	int col = static_cast<int>(img_gray.cols / scale);

	cv::Mat img_downsampled(row, col, CV_8UC1);
	
	for (int i = 0; i < img_gray.rows; i+=4)
	{
		uchar* ptr_downsampled = img_downsampled.ptr<uchar>(static_cast<int>(i / 4));
		uchar* ptr_gray = img_gray.ptr<uchar>(i);

		for (int j = 0; j < img_gray.cols; j+=4)
		{
			ptr_downsampled[static_cast<int>(j / 4)] = ptr_gray[j];
		}
	}
	cv::namedWindow("Downsampled Image", cv::WINDOW_NORMAL);
	cv::resizeWindow("Downsampled Image", img_gray.rows ,img_gray.cols);
	cv::imshow("Downsampled Image", img_downsampled);

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