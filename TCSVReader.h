#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> //atof
#include "TObject.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TString.h"


using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::string;
using std::atof;
using std::vector;

class TCSVReader:public TObject{
private:
	TString fExtension;
	TString fFilename;
	Int_t fNumberOfLines;
	vector<double> fValueVector;
	Int_t fNumOfData;//one per point
	Int_t fNumOfValues; //4*numOfData
	
	void readFile();
public:
	TCSVReader(const TString&);
    ~TCSVReader(){};
    
	double *GetX();
	double *GetY();
	double *GetSigmaX();
	double *GetSigmaY();
    inline Int_t GetSize(){return fNumOfData;};
	
	TGraphErrors *GetTGraphErrors();
    TGraph *GetTGraph();
    
    ClassDef(TCSVReader,0);
};
