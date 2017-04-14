#include "TCSVReader.h"

TCSVReader::TCSVReader(const TString &name):TObject(),fNumberOfLines(0){
	fFilename=name;
	this->readFile();
}

void TCSVReader::readFile(){
	ifstream myfile;
	TString extension(".csv");
	this->fExtension=extension;
	myfile.open((fFilename.Append(extension)).Data(), ios::out);
	if(!myfile.is_open()) cout << "File " << fFilename << " not found." << endl;

	string line;
	/*
	 code help
	 https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c#14266139
	 */
	while(getline(myfile,line)){
		
		size_t pos = 0;
		std::string token;
		while ((pos = line.find(",")) != std::string::npos) {
			token = line.substr(0, pos);
			line.erase(0, pos + 1);
			fValueVector.push_back(atof(token.c_str()));
		}
		pos= line.find("\n");
		token = line.substr(0, pos);
		fValueVector.push_back(atof(token.c_str()));
	}
	fNumOfValues=fValueVector.size();
	fNumOfData=fNumOfValues/4;
	myfile.close();
}

double* TCSVReader::GetX(){
	double *x=new double[fNumOfData];
	for(int i=0, j=0;i<fNumOfValues;i+=4){
		x[j++]=fValueVector[i];
	}
	return x;
}

double* TCSVReader::GetY(){
	double *y=new double[fNumOfData];
	for(int i=1,j=0;i<fNumOfValues;i+=4){
		y[j++]=fValueVector[i];
	}
	return y;
}

double* TCSVReader::GetSigmaX(){
	double *sx=new double[fNumOfData];
	for(int i=2,j=0;i<fNumOfValues;i+=4){
		sx[j++]=fValueVector[i];
	}
	return sx;
}

double* TCSVReader::GetSigmaY(){
	double *sy=new double[fNumOfData];
	for(int i=3,j=0;i<fNumOfValues;i+=4){
		sy[j++]=fValueVector[i];
	}
	return sy;
}

TGraphErrors* TCSVReader::GetTGraphErrors(){
	return new TGraphErrors(fNumOfData,this->GetX(),this->GetY(),this->GetSigmaX(),this->GetSigmaY());
	
}

TGraph* TCSVReader::GetTGraph(){
    return new TGraphErrors(fNumOfData,this->GetX(),this->GetY());
}
