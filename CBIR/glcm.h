#ifndef GLCM_H
#define GLCM_H

#include <opencv2/opencv.hpp>

using namespace cv;
class GLCM
{
public:
    GLCM();
    static Mat quantify(Mat image,  int level);
    static Mat GLCMear(Mat image, int level, int grado);
    static Mat simetrizar(Mat image);
    static Mat normalizar(Mat image);
};

#endif // GLCM_H
