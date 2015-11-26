#include "image.h"

Image::Image()
{
    features = new double[13];
    nivel = 0;
    nombre = "";
    Serialized = NULL;
}

Image::Image(string datos, int size, int nivel, int angulo)
{
    Serialized = NULL;
    //std::string s = "63 62 70 110 50 40 120 110 12 135 150 175 180 152 200 220";
    Mat m =Mat_<uchar>(size,size);
    std::istringstream is( datos );
    int n;
    int c = 0;
    while( is >> n ) {
        m.at<uchar>((int)(c/size), (c%size)) = n;
        c++;
    }
    m = GLCM::quantify(m, nivel);
    features = new double[13];
    GenerateFeatures(m, nivel,angulo);

}

void Image::GenerateFeatures(Mat m , int nivel , int angulo){
    if(angulo<4){
        m = GLCM::GLCMear(m,nivel,angulo * 45);
        std::cout<<m<<std::endl;
        m = GLCM::simetrizar(m);
        m = GLCM::normalizar(m);
        this->features[0] += ImgFeatures::AngularSecondMoment(m);
        this->features[1] += ImgFeatures::Contrast(m);
        this->features[2] += ImgFeatures::Correlation(m);
        this->features[3] += ImgFeatures::Variance(m);
        this->features[4] += ImgFeatures::InverseDifferenceMoment(m);
        this->features[5] += ImgFeatures::SumAverage(m);
        this->features[6] += ImgFeatures::SumEntropy(m);
        this->features[7] += ImgFeatures::SumVariance(m);
        this->features[8] += ImgFeatures::Entropy(m);
        this->features[9] += ImgFeatures::DifferenceVariance(m);
        this->features[10] += ImgFeatures::DifferenceEntropy(m);
        this->features[11] += ImgFeatures::F12(m);
        this->features[12] += ImgFeatures::F13(m);
    }else{
        GenerateFeaturesAverage(m,nivel);
    }
}

void Image::GenerateFeaturesAverage(Mat m, int nivel){
    Mat maux = m;
    double * val = new double[13];
    for(int g=0; g<=135; g = g+45){
        maux = GLCM::GLCMear(m,nivel,g);
        maux = GLCM::simetrizar(maux);
        maux = GLCM::normalizar(maux);
        val[0] += ImgFeatures::AngularSecondMoment(maux);
        val[1] += ImgFeatures::Contrast(maux);
        val[2] += ImgFeatures::Correlation(maux);
        val[3] += ImgFeatures::Variance(maux);
        val[4] += ImgFeatures::InverseDifferenceMoment(maux);
        val[5] += ImgFeatures::SumAverage(maux);
        val[6] += ImgFeatures::SumEntropy(maux);
        val[7] += ImgFeatures::SumVariance(maux);
        val[8] += ImgFeatures::Entropy(maux);
        val[9] += ImgFeatures::DifferenceVariance(maux);
        val[10] += ImgFeatures::DifferenceEntropy(maux);
        val[11] += ImgFeatures::F12(maux);
        val[12] += ImgFeatures::F13(maux);
    }
    this->features[0] = val[0]/4;
    this->features[1] = val[1]/4;
    this->features[2] = val[2]/4;
    this->features[3] = val[3]/4;
    this->features[4] = val[4]/4;
    this->features[5] = val[5]/4;
    this->features[6] = val[6]/4;
    this->features[7] = val[7]/4;
    this->features[8] = val[8]/4;
    this->features[9] = val[9]/4;
    this->features[10] = val[10]/4;
    this->features[11] = val[11]/4;
    this->features[12] = val[12]/4;
}

Image::Image(string nombre, string ruta, int nivel)
{
    Serialized = NULL;
    this->nivel = nivel;
    this->nombre = nombre;
    features = new double[13];
    Mat m = imread(Singleton::instance()->getRuta()+ nombre,0);
    double * val = new double[13];
    for(int i = 0; i<13; i++){
        val[i]= 0;
    }
    //Mat m = (Mat_<uchar>(5,5) << 255,125,135,68,235,12,36,36,96,56,89,253,195,175,165,13,125,154,48,69,156,23,66,159,125);
    m = GLCM::quantify(m, nivel);
    //cout<<m<<endl;
    GenerateFeaturesAverage(m,nivel);
}

const stByte * Image::Serialize(){
   double * d;
   if (Serialized == NULL){
      Serialized = new stByte[GetSerializedSize()];
      d = (double *) Serialized;
      for(int i = 0; i< 13;i++){
          d[i] = features[i];
      }
      memcpy(Serialized + (sizeof(double) * 13), &nivel, sizeof(int));
      memcpy(Serialized + (sizeof(double) * 13)+sizeof(int), nombre.c_str(), nombre.length());
   }
   return Serialized;
}

void Image::Unserialize(const stByte *data, stSize datasize){
   double * d;
   stSize strl;
   d = (double *) data;
   for(int i = 0; i< 13;i++){
      features[i] =  d[i] ;
   }
   nivel = *((int *)(data + (sizeof(double) * 13)));
   strl = datasize - (sizeof(double) * 13 +sizeof(int));
   nombre.assign((char *)(data + (sizeof(double) * 13)+sizeof(int)), strl);
   if (Serialized != NULL){
      delete [] Serialized;
      Serialized = NULL;
   }
}

ostream & operator << (ostream & out, Image & image){

   out << "Nombre= " << image.GetName();
   for(int i = 0 ; i< 13 ; i++){
       out<<"f"<<i<<"= "<<image.Get(i)<<endl;
   }
   return out;
}

