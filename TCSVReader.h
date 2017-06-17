#ifndef TCSVREADER_H
#define TCSVREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> //atof
#include "TObject.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"


using std::cout;
using std::endl;
using std::flush;
using std::ifstream;
using std::ios;
using std::string;
using std::atof;
using std::vector;

struct Point{
  Double_t x;
  Double_t y;
  Double_t sx;
  Double_t sy;
};

class TCSVReader:public TObject{
private:
  TString fExtension;
  TString fFilename;
  TString fContainer;
  Int_t fNumberOfLines;
  vector<Double_t> fValueVector;
  TTree *fTree;
  Int_t fNumOfData;//one per point
  //Int_t fNumOfValues; //4*numOfData
  inline Int_t fNumOfValues() const{return 4*this->fNumOfData;};

  void ReadFile();
  void FillTree();
  void ReadTree();
  void SaveTree();

public:
  TCSVReader(const TString&);
  ~TCSVReader();

  Double_t *GetX();
  Double_t *GetY();
  Double_t *GetSigmaX();
  Double_t *GetSigmaY();

  inline TTree * GetTTree(){
    ReadTree();
    return fTree;
  };
  
  inline void Save(){SaveTree();};

  inline Int_t GetSize(){return fNumOfData;};

  TGraph *GetTGraphErrors();
  TGraph *GetTGraph();

  ClassDef(TCSVReader,0);
};

#endif
