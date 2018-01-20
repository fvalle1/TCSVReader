//call with root -l -e sample.C

void sample(){
  TCSVReader *reader=new TCSVReader("test.csv");
  TGraph *g=reader->GetTGraphErrors();
  g->Draw();
  return;
}
