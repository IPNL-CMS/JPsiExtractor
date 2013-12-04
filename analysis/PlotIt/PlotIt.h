#ifndef PlotIt_h
#define PlotIt_h

#include <TROOT.h>
#include <TFile.h>
#include "TH2.h"
#include "THStack.h"
#include "TF1.h"

#include <vector>

struct MyInput
{
  TString fileName;
  TFile*  tfile;

  TString type;
  TString subtype;

  Int_t   ngen;
  Float_t xsec;
  Float_t kfactor;

  Float_t Nexp;
  Float_t ErrNexp;

  Float_t Eff;
  Float_t ErrEff;

};

class PlotIt
{
private:
  TString _inputFile;
  Float_t _lumi;
  Float_t _lumi2a;
  Float_t _lumi2b;
  Float_t _efficiency;
  std::vector<MyInput> _inputs;

public:

  TH1F*   _hdata;
  TH1F*   _hmc;
  TH1F*   _hsig;
  TH1F*   _hqcd;

  THStack* _hstack;
  TH1F*    _httd;
  TH1F*    _htts;
  TH1F*    _htth;
  TH1F*    _hsto;
  TH1F*    _hwln;
  TH1F*    _hzll;
  TH1F*    _hdib;

  Float_t Ntotdata;
  Float_t Ntotmc;  Float_t ErrNtotmc;
  Float_t Ntotsig; Float_t ErrNtotsig;

  Float_t _ymin;
  Float_t _ymax;

 ~PlotIt();
  PlotIt(const TString& inputFile, const Float_t& lumi, const Float_t& efficiency);
  PlotIt(const TString& inputFile);

  void SetIntputFile(const TString& inputFile) {_inputFile = inputFile;}
  void SetLumi(const Float_t& lumi) { _lumi = lumi;}
  void SetInefficiency(const Float_t& efficiency) { _efficiency = efficiency;}
  void SetYmin(const Float_t& ymin) { _ymin = ymin; }
  void SetYmax(const Float_t& ymax) { _ymax = ymax; }
  void ResetYminmax() { _ymin = -1111; _ymax = -1111; }
  bool checkHisto( TH1* histo);

  bool init();
  void plotbase(const TString& histo);
  void plot (const TString& histo,Int_t rebin=1,TString xtitle="dummy",TString legpos="right");
  void plotsub(const TString& histo,Int_t rebin=1,TString xtitle="dummy",TString legpos="right");
  void plotstack(const TString& histo,Int_t rebin=1,Int_t mode=1,TString xtitle="dummy",TString legpos="right");
  void plotstackratio(const TString& histo,Int_t rebin=1,Int_t mode=1,TString xtitle="dummy",TString legpos="right");
  void GetBinContent(const TString& histo,const Int_t& ibin,bool print=true);

  void plotratio();

  std::vector<MyInput> GetInputs() { return _inputs; }

};

#endif // #ifndef PlotIt_h
