#include "TCSVReader.h"

TCSVReader::TCSVReader(const TString &name):TObject(),fNumberOfLines(0),fFilename(name){
	this->ReadFile();
}

TCSVReader::~TCSVReader(){
	fValueVector.clear();
}


void TCSVReader::ReadFile(){
	ifstream myfile;
	TString extension(".csv");
	this->fExtension=extension;
	myfile.open((fFilename.Append(extension)).Data(), ios::out);
	if(!myfile.is_open())
	{
	cout << "File " << fFilename << " not found." << endl <<flush;
	return;
}

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
	fNumOfData=fValueVector.size()/4;
	myfile.close();
}

Double_t* TCSVReader::GetX(){
	Double_t *x=new Double_t[fNumOfData];
	for(Int_t i=0, j=0;i<fNumOfValues();i+=4){
		x[j++]=fValueVector[i];
	}
	return x;
}

Double_t* TCSVReader::GetY(){
	Double_t *y=new Double_t[fNumOfData];
	for(Int_t i=1,j=0;i<fNumOfValues();i+=4){
		y[j++]=fValueVector[i];
	}
	return y;
}

Double_t* TCSVReader::GetSigmaX(){
	Double_t *sx=new Double_t[fNumOfData];
	for(Int_t i=2,j=0;i<fNumOfValues();i+=4){
		sx[j++]=fValueVector[i];
	}
	return sx;
}

Double_t* TCSVReader::GetSigmaY(){
	Double_t *sy=new Double_t[fNumOfData];
	for(Int_t i=3,j=0;i<fNumOfValues();i+=4){
		sy[j++]=fValueVector[i];
	}
	return sy;
}

TGraph* TCSVReader::GetTGraphErrors(){
	return new TGraphErrors(fNumOfData,this->GetX(),this->GetY(),this->GetSigmaX(),this->GetSigmaY());
}

TGraph* TCSVReader::GetTGraph(){
    return new TGraph(fNumOfData,this->GetX(),this->GetY());
}
