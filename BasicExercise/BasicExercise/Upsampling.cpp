#include <iostream>
#include <math.h>
#include <opencv2/highgui.hpp>


int getBicubic(int p0, int p1, int p2, int p3, int x);

int main()
{

	// Show original Image
	cv::Mat img_orig = cv::imread("Lenna.png");
	cv::imshow("Original Image", img_orig);

	// Define scale factors
	int scale = 2;
	int row = img_orig.rows * scale;
	int col = img_orig.cols * scale;

	//// without interpolation
	cv::Mat img_upsampled_woLPF = cv::Mat::zeros(row, col, CV_8UC3);

	for (int i = 0; i < img_orig.rows; i++)
	{
		uchar* ptr_orig = img_orig.ptr<uchar>(i);
		uchar* ptr_woLPF = img_upsampled_woLPF.ptr<uchar>(i * scale);

		for (int j = 0; j < img_orig.cols; j++)
		{
			ptr_woLPF[j * scale * 3] = ptr_orig[j * 3];
			ptr_woLPF[j * scale * 3 + 1] = ptr_orig[j * 3 + 1];
			ptr_woLPF[j * scale * 3 + 2] = ptr_orig[j * 3 + 2];
		}
	}

	//// Nearest Neighbor interpolation

	// 1) Horizontal interpolation

	// Make empty image with doubled width
	cv::Mat img_up_hor_NN = cv::Mat::zeros(img_orig.rows, col, CV_8UC3);

	// Copy original image into empty image with empty space at a time horizontally
	for (int i = 0; i < img_orig.rows; i++)
	{
		uchar* ptr_src = img_orig.ptr<uchar>(i);
		uchar* ptr_dst = img_up_hor_NN.ptr<uchar>(i);

		for (int j = 0; j < img_orig.cols; j++)
		{
			ptr_dst[j * scale * 3] = ptr_src[j * 3];
			ptr_dst[j * scale * 3 + 1] = ptr_src[j * 3 + 1];
			ptr_dst[j * scale * 3 + 2] = ptr_src[j * 3 + 2];
		}
	}

	// Fill the empty pixel by Nearest Neighbor interpolation
	for (int i = 0; i < img_orig.rows; i++)
	{
		uchar* ptr = img_up_hor_NN.ptr<uchar>(i);

		for (int j = 0; j < img_orig.cols; j++)
		{
			ptr[j * scale * 3 + 3] = ptr[j * scale * 3];
			ptr[j * scale * 3 + 4] = ptr[j * scale * 3 + 1];
			ptr[j * scale * 3 + 5] = ptr[j * scale * 3 + 2];
		}
	}

	// 2) vertical interpolation

	// Make empty image with doubled height
	cv::Mat img_up_ver_NN = cv::Mat::zeros(row, col, CV_8UC3);

	// Copy image with empty space at a time vertically
	for (int i = 0; i < img_up_hor_NN.rows; i++)
	{
		uchar* ptr_src = img_up_hor_NN.ptr<uchar>(i);
		uchar* ptr_dst = img_up_ver_NN.ptr<uchar>(i * scale);

		for (int j = 0; j < img_up_hor_NN.cols; j++)
		{
			ptr_dst[j * 3] = ptr_src[j * 3];
			ptr_dst[j * 3 + 1] = ptr_src[j * 3 + 1];
			ptr_dst[j * 3 + 2] = ptr_src[j * 3 + 2];
		}
	}

	// Fill the empty pixel with NN interpolation

	for (int i = 0; i < img_up_hor_NN.rows - 1; i++)
	{
		uchar* ptr_src = img_up_hor_NN.ptr<uchar>(i);
		uchar* ptr_dst = img_up_ver_NN.ptr<uchar>(i * scale + 3);
		for (int j = 0; j < img_up_hor_NN.cols; j++)
		{
			ptr_dst[j * 3] = ptr_src[j * 3];
			ptr_dst[j * 3 + 1] = ptr_src[j * 3 + 1];
			ptr_dst[j * 3 + 2] = ptr_src[j * 3 + 2];
		}
	}

	cv::imshow("Image with Nearest Neighbor Interpolation", img_up_ver_NN);

	//// Bilinear interpolation
	cv::Mat img_up_hor_BL = cv::Mat::zeros(img_orig.rows, col, CV_8UC3);

	// 1. Horizontal Interpolation

	// Copy image into empty object
	for (int i = 0; i < img_orig.rows; i++)
	{
		uchar* ptr_src = img_orig.ptr<uchar>(i);
		uchar* ptr_dst = img_up_hor_BL.ptr<uchar>(i);

		for (int j = 0; j < img_orig.cols; j++)
		{
			ptr_dst[j * scale * 3] = ptr_src[j * 3];
			ptr_dst[j * scale * 3 + 1] = ptr_src[j * 3 + 1];
			ptr_dst[j * scale * 3 + 2] = ptr_src[j * 3 + 2];
		}
	}

	// Fill the empty pixel

	for (int i = 0; i < img_orig.rows; i++)
	{
		uchar* ptr_src = img_orig.ptr<uchar>(i);
		uchar* ptr_dst = img_up_hor_BL.ptr<uchar>(i);
		for (int j = 0; j < img_orig.cols - 1; j++)
		{
			ptr_dst[j * scale * 3 + 3] = (ptr_src[j * 3] + ptr_src[(j + 2) * 3]) / 2;
			ptr_dst[j * scale * 3 + 4] = (ptr_src[j * 3 + 1] + ptr_src[(j + 2) * 3 + 1]) / 2;
			ptr_dst[j * scale * 3 + 5] = (ptr_src[j * 3 + 2] + ptr_src[(j + 2) * 3 + 2]) / 2;
		}
	}

	// 2. Vertical Interpolation

	// Make empty image for storing vertically interpolated image
	cv::Mat img_up_ver_BL = cv::Mat::zeros(row, col, CV_8UC3);


	// Copy image into empty image with empty space at a time vertically
	for (int i = 0; i < img_up_hor_BL.rows; i++)
	{
		uchar* ptr_src = img_up_hor_BL.ptr<uchar>(i);
		uchar* ptr_dst = img_up_ver_BL.ptr<uchar>(i * scale);

		for (int j = 0; j < col; j++)
		{
			ptr_dst[j * 3] = ptr_src[j * 3];
			ptr_dst[j * 3 + 1] = ptr_src[j * 3 + 1];
			ptr_dst[j * 3 + 2] = ptr_src[j * 3 + 2];
		}
	}

	for (int i = 0; i < img_up_hor_BL.rows - 2; i++)
	{
		uchar* ptr_src1 = img_up_hor_BL.ptr<uchar>(i);
		uchar* ptr_src2 = img_up_hor_BL.ptr<uchar>(i + 2);
		uchar* ptr_dst = img_up_ver_BL.ptr<uchar>(i * scale + 3);
		for (int j = 0; j < img_up_hor_BL.cols - 1; j++)
		{
			ptr_dst[j * 3] = (ptr_src1[j * 3] + ptr_src2[j * 3]) / 2;
			ptr_dst[j * 3 + 1] = (ptr_src1[j * 3 + 1] + ptr_src2[j * 3 + 1]) / 2;
			ptr_dst[j * 3 + 2] = (ptr_src1[j * 3 + 2] + ptr_src2[j * 3 + 2]) / 2;
		}
	}

	cv::imshow("Image with Bilinear Interpolation", img_up_ver_BL);

	//// Bicubic interpolation

	// 1. Horizontal interpolation

	// Make an empty Mat object for storing horizontally interpolated image
	// Should add some padding which are 2 cols for left side and 3 cols for right side
	cv::Mat img_up_hor_BC = cv::Mat::zeros(img_orig.rows, col + 5, CV_8UC3);

	// Copy image into empty object
	for (int i = 0; i < img_orig.rows; i++)
	{
		uchar* ptr_src = img_orig.ptr<uchar>(i);
		uchar* ptr_dst = img_up_hor_BC.ptr<uchar>(i);

		for (int j = 0; j < img_orig.cols; j++)
		{
			ptr_dst[j * scale * 3 + 6] = ptr_src[j * 3];
			ptr_dst[j * scale * 3 + 7] = ptr_src[j * 3 + 1];
			ptr_dst[j * scale * 3 + 8] = ptr_src[j * 3 + 2];
		}
	}

	// Fill the empty pixel with Bicubic interpolation

	for (int i = 0; i < img_orig.rows; i++)
	{
		uchar* ptr = img_up_hor_BC.ptr<uchar>(i);

		for (int j = 0; j < img_orig.cols; j++)
		{
			ptr[j * scale * 3 + 9] = getBicubic(ptr[j * scale * 3], ptr[j * scale * 3 + 6], ptr[j * scale * 3 + 12], ptr[j * scale * 3 + 18], 1);	// b
			ptr[j * scale * 3 + 10] = getBicubic(ptr[j * scale * 3 + 1], ptr[j * scale * 3 + 7], ptr[j * scale * 3 + 13], ptr[j * scale * 3 + 19], 1);	// g
			ptr[j * scale * 3 + 11] = getBicubic(ptr[j * scale * 3 + 2], ptr[j * scale * 3 + 8], ptr[j * scale * 3 + 14], ptr[j * scale * 3 + 20], 1);	// r

		}
	}

	// 2. Vertical interpolation

	// Make an empty Mat objects for storing image
	// Should add some padding which are 2 cols for left side and top side, 3 cols for right side and bottom side
	cv::Mat img_up_ver_BC = cv::Mat::zeros(row + 5, col + 5, CV_8UC3);

	// Copy image into empty image
	for (int i = 0; i < img_orig.rows; i++)
	{
		uchar* ptr_src = img_up_hor_BC.ptr<uchar>(i);
		uchar* ptr_dst = img_up_ver_BC.ptr<uchar>((i + 2) * scale);

		for (int j = 0; j < col + 5; j++)
		{
			ptr_dst[j * 3] = ptr_src[j * 3];
			ptr_dst[j * 3 + 1] = ptr_src[j * 3 + 1];
			ptr_dst[j * 3 + 2] = ptr_src[j * 3 + 2];
		}
	}

	//Fill the empty pixel with Bicubic interpolation
	for (int i = 0; i < img_up_hor_BC.rows; i++)
	{
		uchar* ptr_dst = img_up_ver_BC.ptr<uchar>(i * scale + 3);

		uchar* ptr_src1 = img_up_ver_BC.ptr<uchar>(i * scale);
		uchar* ptr_src2 = img_up_ver_BC.ptr<uchar>(i * scale + 2);
		uchar* ptr_src3 = img_up_ver_BC.ptr<uchar>(i * scale + 4);
		uchar* ptr_src4 = img_up_ver_BC.ptr<uchar>(i * scale + 6);

		for (int j = 0; j < img_up_ver_BC.cols - 3; j++)
		{
			ptr_dst[j * 3 + 6] = getBicubic(ptr_src1[j * 3 + 6], ptr_src2[j * 3 + 6], ptr_src3[j * 3 + 6], ptr_src4[j * 3 + 6], 1);
			ptr_dst[j * 3 + 7] = getBicubic(ptr_src1[j * 3 + 7], ptr_src2[j * 3 + 7], ptr_src3[j * 3 + 7], ptr_src4[j * 3 + 7], 1);
			ptr_dst[j * 3 + 8] = getBicubic(ptr_src1[j * 3 + 8], ptr_src2[j * 3 + 8], ptr_src3[j * 3 + 8], ptr_src4[j * 3 + 8], 1);
		}
	}

	cv::imshow("Image with Bicubic interpolation", img_up_ver_BC);

	cv::waitKey();
	cv::destroyAllWindows();

	return 0;
}

int getBicubic(int p0, int p1, int p2, int p3, int x)
{
	return static_cast<int>(
		(((-0.5) * p0) + (1.5 * p1) + (-1.5 * p2) + (0.5 * p3)) * (std::pow(x, 3))
		+ (p0 + (-2.5 * p1) + (2 * p2) + (-0.5 * p3)) * (std::pow(x, 2))
		+ ((0.5 * p2) + (-0.5 * p0)) * x
		+ p1
		);

}
