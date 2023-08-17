#include <iostream>
#include <opencv2/highgui.hpp>

cv::Mat cvtGray(cv::Mat src_img);

int main()
{
	cv::Mat img_orig = cv::imread("Lenna.png");

	// Original Image
	cv::imshow("Original Image", img_orig);

	// Grayscale Image
	cv::Mat img_gray = cvtGray(img_orig);
	cv::imshow("Grayscale Image", img_gray);

	// Define scale factors
	int scale = 4;
	int row = static_cast<int>(img_orig.rows / scale);
	int col = static_cast<int>(img_orig.cols / scale);

	// 1. without LPF
	cv::Mat img_downsampled_woLPF(row, col, CV_8UC1);

<<<<<<< HEAD
	for (int i = 0; i < img_gray.rows; i+=scale)
=======
	for (int i = 0; i < img_gray.rows; i += scale)
>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	{
		uchar* ptr_gray = img_gray.ptr<uchar>(i);
		uchar* ptr_downsampled = img_downsampled_woLPF.ptr<uchar>(static_cast<int>(i / scale));

<<<<<<< HEAD
		for (int j = 0; j < img_gray.cols; j+=scale)
=======
		for (int j = 0; j < img_gray.cols; j += scale)
>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
		{
			ptr_downsampled[static_cast<int>(j / scale)] = ptr_gray[j];
		}
	}
	cv::namedWindow("Downsampled Image", cv::WINDOW_NORMAL);
<<<<<<< HEAD
	cv::resizeWindow("Downsampled Image", img_orig.rows ,img_orig.cols);
=======
	cv::resizeWindow("Downsampled Image", img_orig.rows, img_orig.cols);
>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	cv::imshow("Downsampled Image", img_downsampled_woLPF);

	// 2. with box kernel
	cv::Mat img_downsampled_box(row, col, CV_8UC1);
	cv::Mat img_temp_bk = cv::Mat::zeros(row + 2, col + 2, CV_8UC1);
<<<<<<< HEAD
	
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	// Make a image with zero-padding
	for (int i = 0; i < img_downsampled_woLPF.rows; i++)
	{
		uchar* ptr_src = img_downsampled_woLPF.ptr<uchar>(i);
		uchar* ptr_dst = img_temp_bk.ptr<uchar>(i + 1);
<<<<<<< HEAD
		
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
		for (int j = 0; j < img_downsampled_woLPF.cols; j++)
		{
			ptr_dst[j + 1] = ptr_src[j];
		}

	}

	// Define box filter
<<<<<<< HEAD
	int box_filter[3][3] = { 
								{1, 1, 1},
								{1, 1, 1},
								{1, 1, 1}
						   };
=======
	int box_filter[3][3] = {
								{1, 1, 1},
								{1, 1, 1},
								{1, 1, 1}
	};
>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	int sum;

	// Apply 2D-convolution with Box kernel
	for (int y = 0; y < img_temp_bk.rows - 2; y++)
	{
		uchar* ptr_dst = img_downsampled_box.ptr<uchar>(y);
		for (int x = 0; x < img_temp_bk.cols - 2; x++)
		{
			sum = 0;
			for (int i = 0; i < 3; i++)
			{
				uchar* ptr_src = img_temp_bk.ptr<uchar>(y + i);

				for (int j = 0; j < 3; j++)
				{
					sum += (ptr_src[x + j] * box_filter[i][j]);
				}
			}
			ptr_dst[x] = static_cast<int>(sum / 9);
		}
	}
	cv::namedWindow("Image Filtered By Box Kernel", cv::WINDOW_NORMAL);
	cv::resizeWindow("Image Filtered By Box Kernel", img_orig.rows, img_orig.cols);
	cv::imshow("Image Filtered By Box Kernel", img_downsampled_box);

	// 3. with Gaussian kernel
<<<<<<< HEAD
	
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	// Make empty Mat objects that will be stored image filtered by gaussian kernel
	cv::Mat img_downsampled_gs(row, col, CV_8UC1);

	// Copy image and add padding
	cv::Mat img_temp_gs = cv::Mat::zeros(row + 2, col + 2, CV_8UC1);
	for (int i = 0; i < img_downsampled_woLPF.rows; i++)
	{
		uchar* ptr_src = img_downsampled_woLPF.ptr<uchar>(i);
		uchar* ptr_dst = img_temp_gs.ptr<uchar>(i + 1);

		for (int j = 0; j < img_downsampled_woLPF.cols; j++)
		{
			ptr_dst[j + 1] = ptr_src[j];
		}
	}

	// Define gaussian filter
	int gs_filter[3][3] = {
								{1, 2, 1},
								{2, 4, 2},
								{1, 2, 1}
<<<<<<< HEAD
						  };
	
=======
	};

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	// Apply 2D-convolution by Gaussian kernel
	for (int y = 0; y < img_temp_gs.rows - 2; y++)
	{
		uchar* ptr_dst = img_downsampled_gs.ptr<uchar>(y);

		for (int x = 0; x < img_temp_gs.cols - 2; x++)
		{
			sum = 0;

			for (int i = 0; i < 3; i++)
			{
				uchar* row_cur = img_temp_gs.ptr<uchar>(y + i);

				for (int j = 0; j < 3; j++)
				{
					sum += (row_cur[x + j] * gs_filter[i][j]);
				}
			}

			ptr_dst[x] = static_cast<int>(sum / 16);
		}
	}

	cv::namedWindow("Image Filtered By Gaussian Kernel", cv::WINDOW_NORMAL);
	cv::resizeWindow("Image Filtered By Gaussian Kernel", img_orig.rows, img_orig.cols);
	cv::imshow("Image Filtered By Gaussian Kernel", img_downsampled_gs);


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
<<<<<<< HEAD
	
=======

>>>>>>> 93e37a31cd4142ef6dd8f524bccbd11452ffab46
	return dst_img;
}
