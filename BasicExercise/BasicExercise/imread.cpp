#include <opencv2/highgui.hpp>

int main()
{
	cv::Mat color_img = cv::imread("Lenna.png", cv::IMREAD_COLOR);
	cv::imshow("color_img", color_img);
	cv::waitKey();

	return 0;
}