#include "glcm.h"
#include <iostream>
#include "math.h"
GLCM::GLCM()
{

}

Mat GLCM::quantify( Mat image , int level){
    Mat C(image.rows,image.cols, CV_8UC1);
    for (int i = 0; i < image.cols; i++) {
        for (int j = 0; j < image.rows; j++) {
            C.at<uchar>(i, j) = floor(image.at<uchar>(i, j) * level / 256);
         }
    }
    return C;
}

Mat GLCM::simetrizar(Mat image){

    return image.t() + image;
}


Mat GLCM::GLCMear( Mat image , int level , int grado){
    Mat C = Mat::zeros(level,level,CV_32F);
    switch (grado) {
    case 0:
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols-1; j++) {
                    C.at<float>(image.at<uchar>(i, j), image.at<uchar>(i, j+1) ) += 1;
             }
        }
        break;
    case 45:
        for (int i = 1; i < image.rows; i++) {
            for (int j = 0; j < image.cols-1; j++) {
                    C.at<float>(image.at<uchar>(i, j), image.at<uchar>(i-1, j+1) ) += 1;
             }
        }
        break;
    case 90:
        for (int i = 1; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                    C.at<float>(image.at<uchar>(i, j), image.at<uchar>(i-1, j) ) += 1;
             }
        }
        break;
    case 135:
        for (int i = 1; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                    C.at<float>(image.at<uchar>(i, j), image.at<uchar>(i-1, j-1) ) += 1;
             }
        }
        break;
    default:
        break;
    }
    return C;
}

Mat GLCM::normalizar(Mat image){
    Mat C = Mat::zeros(image.rows,image.cols,CV_64F);
    float n = 0;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
                n += image.at<float>(i, j);
         }
    }

    C = image/n;
    return C;
}


