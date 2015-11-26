#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <glcm.h>
#include <sstream>
#include <iostream>
#include <math.h>
#include "singleton.h"
#include "imgfeatures.h"
#include <arboretum/stUserLayerUtil.h>
#include <arboretum/stTypes.h>
#include <arboretum/stUtil.h>

class Image
{
public:
    Image();
    Image(string datos, int size, int nivel, int angulo);
    Image(string nombre, string ruta, int nivel);
    void GenerateFeatures(Mat m, int nivel, int angulo);
    void GenerateFeaturesAverage(Mat m, int nivel);
    const string & GetName()const{
       return nombre;
    }
    stSize GetSerializedSize(){
       return (sizeof(double) * 13) + sizeof(int) + nombre.length();
    }
    Image * Clone(){
       return new Image(nombre,"", nivel);
    }

    int GetSize(){
        return 13;
    }
    double Get(int i){
        return features[i];
    }
    bool IsEqual(Image *obj){
        for(int i = 0; i<13;i++){
            if(Get(i) != obj->Get(i))return false;
        }
        return true;
    }
    const stByte * Serialize();
    void Unserialize (const stByte *data, stSize datasize);
    string nombre;
    int nivel;
    double * features;
    stByte * Serialized;
};

ostream & operator << (ostream & out, Image & image);
#endif // IMAGE_H
