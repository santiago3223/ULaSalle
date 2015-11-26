#ifndef IMGFEATURES_H
#define IMGFEATURES_H
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

class ImgFeatures
{
public:
    ImgFeatures();
    static double px(Mat m, int i);
    static double py(Mat m, int i);
    static double ux(Mat m);
    static double uy(Mat m);
    static double u(Mat m);
    static double ox(Mat m);
    static double oy(Mat m);
    static double pxy(Mat m, int k);
    static double px_y(Mat m, int k);
    static double HXY(Mat m);
    static double HXY1(Mat m);
    static double HXY2(Mat m);
    static double Q(Mat m, int i, int j);
    static double HX(Mat m);
    static double HY(Mat m);
    static double AngularSecondMoment (Mat m);
    static double Contrast (Mat m);
    static double Correlation (Mat m);
    static double Variance (Mat m);
    static double InverseDifferenceMoment (Mat m);
    static double SumAverage (Mat m);
    static double SumVariance (Mat m);
    static double SumEntropy (Mat m);
    static double Entropy (Mat m);
    static double DifferenceVariance (Mat m);
    static double DifferenceEntropy (Mat m);
    static double F12 (Mat m);
    static double F13 (Mat m);

};

#endif // FEATURES_H
