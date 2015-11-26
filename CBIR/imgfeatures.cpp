#include "imgfeatures.h"

ImgFeatures::ImgFeatures()
{

}

double ImgFeatures::px(Mat m, int i){
    //i = i-1;
    double n = 0;
    for (int j = 0; j < m.cols; j++) {
            n += m.at<float>(i, j);
    }
    return n;
}

double ImgFeatures::py(Mat m, int j ){
    //j = j-1;
    double n = 0;
    for (int i = 0; i < m.cols; i++) {
            n += m.at<float>(i, j);
     }

    return n;
}
double ImgFeatures::u(Mat m){

    return (ux(m)+uy(m))/2;
}

double ImgFeatures::ux(Mat m){
    double n = 0;
//    for (int i = 0; i < m.cols; i++) {
//            n +=  i * px(m,i);
//    }
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            n += i * m.at<float>(i, j);
         }
    }
    return n;
}

double ImgFeatures::uy(Mat m){
    double n = 0;
//    for (int i = 0; i < m.cols; i++) {
//            n +=  i * py(m,i);
//    }
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            n += j * m.at<float>(i, j);
         }
    }
    return n;
}

double ImgFeatures::ox(Mat m){
    double n = 0;
    double U = u(m);
//    for (int i = 1; i <= m.cols; i++) {
//            n += px(m,i) * pow(i-ux(m),2);
//    }
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            n += pow(i - U, 2) * m.at<float>(i, j);
         }
    }

    return sqrt(n);
}

double ImgFeatures::oy(Mat m){
    double n = 0;
    double U = u(m);
//    for (int i = 1; i <= m.cols; i++) {
//            n += py(m,i) * pow(i-uy(m),2);
//    }
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            n += pow(j - U, 2) * m.at<float>(i, j);
         }
    }
    return sqrt(n);
}

double ImgFeatures::pxy(Mat m, int k ){
    double n= 0;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if(i+j+2 == k){
                //std::cout<<k<<"-"<<k*k + m.at<float>(i, j)<<std::endl;
                n += m.at<float>(i, j);
            }
         }
    }
    return n;
}
double ImgFeatures::px_y(Mat m, int k){
    double n = 0;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if(abs(i-j) == k){
                //std::cout<<k<<"-"<<k*k + m.at<float>(i, j)<<std::endl;
                n += m.at<float>(i, j);
            }
         }
    }
    return n;
}


double ImgFeatures::HXY(Mat m){
    double n = 0;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if(m.at<float>(i, j) != 0){
                n += m.at<float>(i, j)*log(m.at<float>(i, j));
            }
         }
    }
    return -n;
}

double ImgFeatures::HXY1(Mat m){
    double n = 0;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if(px(m,i)* px(m,j) != 0){
                n += m.at<float>(i, j)*log(px(m,i)*py(m,j));
            }
         }
    }
    return -n;
}

double ImgFeatures::HXY2(Mat m){
    double n = 0;
    double lg = 0;
    double lg1 = 0;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if(py(m,j)* py(m,j) != 0){
            lg = px(m,i)* py(m,j);
            lg1 = log(py(m,j)*py(m,j));
            //std::cout<<"1.-"<<lg<<std::endl;
            //std::cout<<"2.-"<<lg1<<std::endl;
            n += lg * lg1;
            }
         }
    }
    return -n;
}

double ImgFeatures::Q(Mat m, int i, int j ){
    double n = 0;
    for (int k = 0; k < m.rows; k++) {
        n += m.at<float>(i, k) * m.at<float>(j, k) / px(m,i)/ py(m,j);
    }
    return n;
}

double ImgFeatures::HX(Mat m){
    double n = 0;
    for(int i = 0; i < m.rows; i++){
        if(px(m,i)!=0){
            //std::cout<<"px: "<<px(m,1)<<std::endl;
            n +=px(m,i)* log(px(m,i));
        }
    }
    return -n;
}

double ImgFeatures::HY(Mat m){
    double n = 0;
    for(int i = 0; i < m.rows; i++){
        //if(py(m,i)!=0){
            n +=py(m,i)+ log(py(m,i));
        //}
    }
    return -n;
}

double ImgFeatures::AngularSecondMoment(Mat m ){
    double n = 0;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            //std::cout<<m.at<float>(i, j)*m.at<float>(i, j)<<std::endl;
                n += m.at<float>(i, j)*m.at<float>(i, j);
         }
    }
    //std::cout<<"final: "<<n<<std::endl;
    return n;
}

double ImgFeatures::Contrast(Mat m ){
    double n = 0;
    for(int k = 0; k < m.rows; k++){
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                if(abs(i-j) == k){
                    //std::cout<<k<<"-"<<k*k + m.at<float>(i, j)<<std::endl;
                    n += k*k * m.at<float>(i, j);
                }
             }
        }
    }
    return n;
}

double ImgFeatures::Correlation (Mat m){
    double n = 0;
    double Ux = ux(m);
    double Uy = uy(m);
    double Ox = ox(m);
    double Oy = oy(m);
    //std::cout<<"Ux:"<<Ux<<std::endl;
    //std::cout<<"Uy:"<<Uy<<std::endl;
    //std::cout<<"Ox:"<<Ox<<std::endl;
    //std::cout<<"Oy:"<<Oy<<std::endl;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            n += (i - Ux) * (j - Uy) * m.at<float>(i, j) / Ox / Oy;

         }
    }
    return n;
}

double ImgFeatures::Variance (Mat m){
    double n = 0;
    double U = u(m);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            n += m.at<float>(i, j) * pow(i-U,2);

         }
    }
    return n;
}

double ImgFeatures::InverseDifferenceMoment(Mat m ){
    double n = 0;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
                n += m.at<float>(i, j)/(1+(i-j)*(i-j));
         }
    }
    return n;
}

double ImgFeatures::SumAverage (Mat m){
    double n = 0;
    for(int k = 2; k <= 2 * m.rows;k++){
        n += k * pxy(m,k);
        //std::cout<<"px+y1: "<<pxy(m,k)<<std::endl;
    }
    return n;
}

double ImgFeatures::SumVariance (Mat m){
    double n = 0;
    double f6 = SumEntropy(m);
    for(int k = 2; k <= 2 * m.rows;k++){
        n += (k-f6) * pxy(m,k);
        //std::cout<<"px+y2: "<<pxy(m,k)<<std::endl;
    }
    return n;
}

double ImgFeatures::SumEntropy (Mat m){
    double n = 0;
    for(int k = 2; k <= 2 * m.rows;k++){
        if(pxy(m,k) != 0){
        n += pxy(m,k)*log(pxy(m,k)) ;
        }
    }
    return -n;
}

double ImgFeatures::Entropy (Mat m){
    double n = 0;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if(m.at<float>(i, j) != 0){
                n += m.at<float>(i, j)* log(m.at<float>(i, j));
            }
         }
    }
    return -n;
}

double ImgFeatures::DifferenceVariance (Mat m){
    double n = 0;
    double mn = 0;
    for (int i = 0; i < m.cols; i++) {
        mn += i*px_y(m,i);
     }
    for (int i = 0; i < m.rows; i++) {
        n+= (i-mn)*(i-mn)*px_y(m,i);
    }
    return n;
}

double ImgFeatures::DifferenceEntropy (Mat m){
    double n = 0;
    for(int k = 0; k < m.rows;k++){
        if(px_y(m,k) != 0){
        n += px_y(m,k)*log(px_y(m,k)) ;
        }
    }
    return -n;
}

double ImgFeatures::F12 (Mat m){
    double n = 0;
    double f9 = Entropy(m);
   // std::cout<<"entriopia:"<<f9<<std::endl;
    //std::cout<<"HXY1:"<<HXY1(m)<<std::endl;
    //std::cout<<"HX:"<<HX(m)<<std::endl;
    n = (f9 - HXY1(m))/HX(m);
    //n = (HXY(m) - HXY1(m))/max(HX(m),HY(m));
    return n;
}

double ImgFeatures::F13 (Mat m){
    double n = 0;
    double f9 = Entropy(m);
    //std::cout<<"HXY2(m):"<<HXY2(m)<<std::endl;
    n = sqrt(1-exp((-2) * (HXY2(m)-f9)));
    //n = pow(1 - exp((-2) *(HXY2(m)- HXY(m))),(1/2));
    return n;
}
