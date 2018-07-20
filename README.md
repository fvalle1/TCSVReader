# TCSVReader
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f7e7e23902804aefba9c1b2380a567d2)](https://www.codacy.com/app/fvalle1/TCSVReader?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=fvalle1/TCSVReader&amp;utm_campaign=Badge_Grade)

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
