#include "stdafx.h"
#include "Copencv.h"



void MatToCImage(Mat &mat, CImage &cImage)
{
	//create new CImage
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy(); //clear
	cImage.Create(width, height, 8 * channels); //默认图像像素单通道占用1个字节

	//copy values
	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); //A pointer to the bitmap buffer
	int step = cImage.GetPitch();

	for (int i = 0; i < height; ++i)
	{
		ps = (mat.ptr<uchar>(i));
		for (int j = 0; j < width; ++j)
		{
			if (channels == 1) //gray
			{
				*(pimg + i * step + j) = ps[j];
			}
			else if (channels == 3) //color
			{
				for (int k = 0; k < 3; ++k)
				{
					*(pimg + i * step + j * 3 + k) = ps[j * 3 + k];
				}
			}
		}
	}
}







Copencv::Copencv()
{
}

Copencv::Copencv(CString file)
{
	loadImg(file);
}

Copencv::~Copencv()
{
}

vector<ColorConversionCodes> Copencv::getColor()
{
	vector<ColorConversionCodes> colors;
	for (ColorConversionCodes color = COLOR_BGR2BGRA; color < COLOR_COLORCVT_MAX; color = (ColorConversionCodes)(color + 1)) {
		colors.push_back(color);
	}
	return colors;
}




BOOL Copencv::loadImg(CString file)
{
	m_file = file;
	m_originalImg = imread(file.GetString());
	m_originalImg.copyTo(m_img);
	return TRUE;
}
BOOL Copencv::loadImg(CString file, CImage *pCimg)
{
	Mat img = imread(file.GetString());
	MatToCImage(m_img, *pCimg);
	return TRUE;
}

BOOL Copencv::outImg(CImage *pCimg)
{
	MatToCImage(m_img, *pCimg);
	return TRUE;
}

BOOL Copencv::empty()
{
	Mat img;
	img.copyTo(m_originalImg);
	img.copyTo(m_img);
	img.release();
	return TRUE;
}

BOOL Copencv::getFile(CString &oldFile)
{
	oldFile = m_file;
	return TRUE;
}


BOOL Copencv::resetImg()
{
	m_originalImg.copyTo(m_img);
	return TRUE;
}



BOOL Copencv::gray()
{
	cvtColor(m_img, m_img, COLOR_RGB2GRAY);
	return TRUE;
}

BOOL Copencv::inverted()
{
	m_img = ~m_img;
	return TRUE;
}
BOOL Copencv::inverted(CImage *pCimg)
{
	m_img = ~m_img;
	MatToCImage(m_img, *pCimg);
	return TRUE;
}
BOOL Copencv::inverted(CString file, CImage *pCimg)
{
	Mat img = imread(file.GetString());
	img = ~img;
	MatToCImage(img, *pCimg);
	return TRUE;
}

BOOL Copencv::threshold(double thresh, double maxval, int type)
{
	cv::threshold(m_img, m_img, thresh, maxval, type);
	return TRUE;
}
BOOL Copencv::threshold(CImage *pCimg, double thresh, double maxval, int type)
{
	cv::threshold(m_img, m_img, 100, 255, THRESH_BINARY);
	MatToCImage(m_img, *pCimg);
	return TRUE;
}

BOOL Copencv::cvtcolor(ColorConversionCodes colorVal)
{
	cvtColor(m_img, m_img, colorVal);
	return TRUE;
}
