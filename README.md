Utility to simply generate a TGraph or TGraph error from a .csv file

## Example
TCSVReader *reader=new TCSVReader("test");
TGraph *g=reader->GetTGraph();
