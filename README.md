Utility to simply generate a TGraph or TGraph error from a .csv file

# How to compile and run example

Clone this repo
`git clone https://github.com/fvalle1/TCSVReader.git`

run `root -l -e CompileReader.C` 

then 
`.x sample.C`

## root6
if you're running root6 use following commands:
- `root -l`
- `.L CompileReader()`
- `CompileReader()`
- `.x sample.C`


# Sample

```cpp
void sample(){
  TCSVReader *reader=new TCSVReader("test.csv");
  TGraph *g=reader->GetTGraphErrors();
  g->Draw();
  return;
}
```

this code is in [sample.C](sample.C)
