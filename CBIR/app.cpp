#include <iostream>
#pragma hdrstop
#include "app.h"

#pragma package(smart_init)

void TApp::CreateTree(){
   SlimTree = new mySlimTree(PageManager);
}

void TApp::CreateDiskPageManager(){
   PageManager = new stPlainDiskPageManager("SlimTree.dat",1024 * 1024);
}



//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->SlimTree != NULL){
      delete this->SlimTree;
   }
   if (this->PageManager != NULL){
      delete this->PageManager;
   }

   for (unsigned int i = 0; i < queryObjects.size(); i++){
      delete (queryObjects.at(i));
   }
}

void TApp::LoadTree(const char * fileName, int nivel){
   ifstream in(fileName);
   char imageName[200];
   //int TCity::Cantidad = cant;
   Image * image = new Image();

   if (SlimTree!=NULL){
      if (in.is_open()){
         cout << "\nLoading objects ";
         while(in.getline(imageName, 200, '\t')){
            image = new Image(imageName, "",nivel);
            in.ignore();
            cout<<image->GetName()<<endl;
            SlimTree->Add(image);
            cout<<image->GetName()<<endl;
            delete image;
         }
         cout << " Added " << SlimTree->GetNumberOfObjects() << " objects ";
         in.close();
      }else{
         cout << "\nProblem to open the file.";
      }//end if
   }else{
      cout << "\n Zero object added!!";
   }
}

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(const char * fileName, int nivel){
   ifstream in(fileName);
   char imageName[200];
   queryObjects.clear();

   if (in.is_open()){
      cout << "\nLoading query objects "<<endl;
      while(in.getline(imageName, 200, '\t')){
          in.ignore();
          queryObjects.push_back(new Image(imageName, "",nivel));
          //this->queryObjects.insert(queryObjects.end(), new Image(imageName, "/home/santiago/ProyectoFinal/database/clases/",nivel));
      }
      cout << " Added " << queryObjects.size() << " query objects "<<endl;
      in.close();
   }else{
      cout << "\nProblem to open the query file."<<endl;
      cout << "\n Zero object added!!\n"<<endl;
   }
}


vector<string> TApp::PerformRangeQuery(int index , double range ){
    vector<string> v;
   myResult * result;
   stDistance radius;
   clock_t start, end;
   unsigned int size;
   unsigned int i;

   if (SlimTree){
      size = queryObjects.size();
      // reset the statistics
      PageManager->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
         result = SlimTree->RangeQuery(queryObjects[index], range);
         for (int i = 0; i< result->GetNumOfEntries();i++){
             cout<<result->operator [](i).GetObject ()->GetName()<<endl;
            v.push_back(result->operator [](i).GetObject ()->GetName());
         }
         delete result;
      end = clock();
      cout << "\nTotal Time: " << ((double )end-(double )start) / 1000.0 << "(s)";
      // is divided for queryObjects to get the everage
      cout << "\nAvg Disk Accesses: " << (double )PageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << "\nAvg Distance Calculations: " <<
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size;
   }//end if
    return v;
}


vector<string> TApp::PerformNearestQuery(int index, int cantidad){
    vector<string> v(cantidad,"error");
   myResult * result;
   clock_t start, end;
   unsigned int size;

   if (SlimTree){
      size = queryObjects.size();
      PageManager->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();

         result = SlimTree->NearestQuery(queryObjects[index], cantidad);
         for (int i = 0; i< result->GetNumOfEntries();i++){
             cout<<result->operator [](i).GetObject ()->GetName()<<endl;
             v[i] = result->operator [](i).GetObject ()->GetName();
         }
         delete result;

      end = clock();
      cout << "\nTotal Time: " << ((double )end-(double )start) / 1000.0 << "(s)";
      // is divided for queryObjects to get the everage
      cout << "\nAvg Disk Accesses: " << (double )PageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << "\nAvg Distance Calculations: " <<
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size;
   }//end if
   return v;
}

