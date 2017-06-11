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
	if(!fFilename.Contains("csv"))fFilename.Append(extension);
	myfile.open(fFilename.Data(), ios::out);
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
		Double_t valueBuffer=atof(token.c_str());
		fValueVector.push_back(valueBuffer);
	}

	fNumOfData=fValueVector.size()/4;
	myfile.close();
}

void TCSVReader::FillTree(){
	fTree=new TTree();
	Double_t valueBuffer[2][2];
	fTree->Branch("x",&valueBuffer[0][0]);
	fTree->Branch("y",&valueBuffer[1][0]);
	fTree->Branch("sx",&valueBuffer[0][1]);
	fTree->Branch("sy",&valueBuffer[1][1]);

	for(Int_t i=0, j=0;i<fNumOfValues();i+=4){
		valueBuffer[0][0]=fValueVector[i];
		valueBuffer[1][0]=fValueVector[i+1];
		valueBuffer[0][1]=fValueVector[i+2];
		valueBuffer[1][1]=fValueVector[i+3];
		fTree->Fill();
	}


}

void TCSVReader::SaveTree(){
	this->FillTree();
	TFile *file=new TFile(fFilename.Append(".root"),"RECREATE");

	file->cd();
	fTree->Write("TreeData",TObject::kOverwrite);

	file->Close();
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
