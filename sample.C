void sample(){
  TCSVReader *reader=new TCSVReader("test");
  TGraph *g=reader->GetTGraphErrors();
  g->Draw();
  return;
}
