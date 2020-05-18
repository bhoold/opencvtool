#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2\imgproc\types_c.h"
using namespace cv;
using namespace std;



class Copencv
{
public:
	Copencv();
	Copencv(CString file);
	~Copencv();
	static vector<ColorConversionCodes> Copencv::getColor();
	BOOL loadImg(CString file);
	BOOL loadImg(CString file, CImage *pCimg);
	BOOL outImg(CImage *pCimg);
	BOOL empty();
	BOOL gray();
	BOOL inverted();
	BOOL inverted(CImage *pCimg);
	BOOL inverted(CString file, CImage *pCimg);
	BOOL threshold(double thresh, double maxval, int type);
	BOOL threshold(CImage *pCimg, double thresh, double maxval, int type);
private:
	Mat m_img;
public:
	BOOL getFile(CString &oldFile);
private:
	CString m_file;
	Mat m_originalImg;
public:
	BOOL resetImg();
	BOOL cvtcolor(ColorConversionCodes colorVal);
};

