#ifndef appH
#define appH

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stMetricTree.h>
#include <arboretum/stDBMTree.h>
#include <arboretum/stBasicMetricEvaluators.h>

#include "image.h"
#include <string.h>
#include <fstream>

class TApp{
   public:
      typedef stResult < Image > myResult;
      typedef stMetricTree < Image, stBasicCanberraMetricEvaluator< Image> > MetricTree;
      typedef stSlimTree < Image, stBasicCanberraMetricEvaluator< Image>  > mySlimTree;


      TApp(){
         PageManager = NULL;
         SlimTree = NULL;
      }//end TApp

      void Init(){
         CreateDiskPageManager();
         CreateTree();
      }
      void Done();
      void LoadTree(const char * fileName, int nivel);
      void LoadVectorFromFile(const char * fileName, int nivel);
      vector<string> PerformNearestQuery(int index, int cantidad);
      vector<string> PerformRangeQuery(int index, double range);


   private:
      stPlainDiskPageManager * PageManager;
      mySlimTree * SlimTree;
      vector <Image *> queryObjects;
      void CreateDiskPageManager();
      void CreateTree();
};

#endif //end appH
