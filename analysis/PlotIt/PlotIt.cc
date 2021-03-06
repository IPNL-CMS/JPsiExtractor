//#define PlotIt_cc

#include "PlotIt.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TMath.h"

#include "TText.h"
#include "TLatex.h"
#include <TROOT.h>
#include <TBrowser.h>

#include "TVirtualFitter.h"
#include "TMinuit.h"

using std::cout;
using std::endl;
using std::vector;

using namespace std;

bool PlotIt::checkHisto( TH1* histo)
{
  if ( histo == NULL )
  {
    cout << "L'histo n'existe pas" << endl;
    return false; 
  }
  else return true;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Double_t fitqcd(Double_t* x, Double_t* par)
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
{
  Double_t val = par[0] * TMath::Power(x[0],par[1]);
  return val;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
double expo_er(double x, double * par, double *matrix)
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
{
  const int npar = 2;

  double derivate[npar]  =
  {
    exp(par[0]+par[1]*x),
    x*exp(par[0]+par[1]*x)
  } ;

  float er=0.;
  for(int i=0; i<npar;i++)
  {
    for(int j=0; j<npar;j++)
    {
      er =er+derivate[i]*( *(matrix+npar*i+j) )*derivate[j];
    }
  }
  // cout<<er<<endl;
  return sqrt(er);

};

//==========================================================================================================

// ... Global attributes go here ...
void global_style() {

  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetFrameBorderMode(0);

  gStyle->SetTitleColor(1);   // 0
  gStyle->SetTitleBorderSize(1);
  gStyle->SetTitleX(0.10);
  gStyle->SetTitleY(0.94);
  gStyle->SetTitleW(0.5);
  gStyle->SetTitleH(0.06);

  gStyle->SetLabelOffset(1e-04);
  gStyle->SetLabelSize(0.2);

  gStyle->SetStatColor(0);
  gStyle->SetStatBorderSize(1);
  gStyle->SetStatX(0.90);
  gStyle->SetStatY(0.90);
  gStyle->SetStatW(0.30);
  gStyle->SetStatH(0.10);

  gStyle->SetErrorX(0.0);   // Horizontal error bar size
  //   gStyle->SetPaperSize(10.,12.);   // Printout size
}

// ... Canvas attributes ...
void canvas_style(TCanvas *c,
    float left_margin=0.15,
    float right_margin=0.05,
    float top_margin=0.10,
    float bottom_margin=0.15,
    int canvas_color=0,
    int frame_color=0) {

  c->SetLeftMargin(left_margin);
  c->SetRightMargin(right_margin);
  c->SetTopMargin(top_margin);
  c->SetBottomMargin(bottom_margin);
  c->SetFillColor(canvas_color);
  c->SetFrameFillColor(frame_color);

  c->SetBorderMode(0);
  c->SetBorderSize(1);
  c->SetFrameBorderMode(0);
}

// ... 1D histogram attributes; (2D to come) ...
void h1_style(TH1 *h,
    int line_width=3,
    int line_color=1,
    int line_style=1, 
    int fill_style=1001,
    int fill_color=50,
    float y_min=-1111.,
    float y_max=-1111.,
    int ndivx=510,
    int ndivy=510,
    int marker_style=20,
    int marker_color=1,
    float marker_size=1.2,
    int optstat=0) {

  h->SetLineWidth(line_width);
  h->SetLineColor(line_color);
  h->SetLineStyle(line_style);
  h->SetFillColor(fill_color);
  h->SetFillStyle(fill_style);
  h->SetMaximum(y_max);
  h->SetMinimum(y_min);
  h->GetXaxis()->SetNdivisions(ndivx);
  h->GetYaxis()->SetNdivisions(ndivy);

  h->SetMarkerStyle(marker_style);
  h->SetMarkerColor(marker_color);
  h->SetMarkerSize(marker_size);
  h->SetStats(optstat);

  h->SetLabelFont(62,"X");       // 42
  h->SetLabelFont(62,"Y");       // 42
  h->SetLabelOffset(0.01,"X");  // D=0.005
  h->SetLabelOffset(0.01,"Y");  // D=0.005
  h->SetLabelSize(0.045,"X");
  h->SetLabelSize(0.045,"Y");
  h->SetTitleOffset(1.0,"X");
  h->SetTitleOffset(1.2,"Y");
  h->SetTitleSize(0.06,"X");
  h->SetTitleSize(0.06,"Y");
  h->SetTitle(0);
}

//==============================================================================
PlotIt::~PlotIt()
  //==============================================================================
{
  cout << "PlotIt::~PlotIt() : Finished" << endl;
}

//==============================================================================
PlotIt::PlotIt(const TString& inputFile, const Float_t& lumi, const Float_t& efficiency)
  //==============================================================================
{
  cout << "PlotIt::PlotIt" << endl;

  // Initialize private variable :
  _inputFile = inputFile;
  _lumi = lumi;
  _efficiency = efficiency;

  if ( _efficiency != 1. ) {
    _lumi *= _efficiency;
    cout << " Integrated luminosity mutiplied by : " << _efficiency << endl;
    cout << " New Integrated luminosity          = " << _lumi       << endl;
  }

  _hdata = 0;
  _hmc   = 0;
  _hsig  = 0;
  _hqcd  = 0;

  _hstack = 0;
  _httd   = 0;
  _htts   = 0;
  _htth   = 0;
  _hsto   = 0;
  _hwln   = 0;
  _hzll   = 0;
  _hdib   = 0;

  // Call the init function which read the input file

  init();

}

//==============================================================================
PlotIt::PlotIt(const TString& inputFile)
  //==============================================================================
{
  _inputFile = inputFile;
  _lumi   = 1200;
  _efficiency = 1.;

  _hdata = 0;
  _hmc   = 0;
  _hsig  = 0;
  _hqcd  = 0;

  _hstack = 0;
  _httd   = 0;
  _htts   = 0;
  _htth   = 0;
  _hsto   = 0;
  _hwln   = 0;
  _hzll   = 0;
  _hdib   = 0;

  // Call the init function which read the input file

  init();

}

//==============================================================================
bool PlotIt::init()
  //==============================================================================
{
  cout << "PlotIt::init()" << endl;

  _hdata = 0;
  _hmc = 0;
  _hsig = 0;

  _ymin = -1111;
  _ymax = -1111;

  // Initialize d0style :
  //_____________________

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  global_style();

  // Open input file :
  //__________________

  cout << _inputFile.Data() << endl;

  ifstream inputFile(_inputFile.Data());
  if (inputFile.bad()) {
    cout << "Impossible to open : " << _inputFile << endl;
    return false;
  }

  // Read the input file :
  //______________________

  std::ostream* aStream = &cout;

  MyInput anInput; 
  int counter = 0;
  cout << "######################################################################################################" << endl;
  while (!inputFile.eof()) {
    counter++;    
    TString first;
    inputFile >> first;
    if (first == "end") break;
    anInput.fileName = first;
    inputFile >> anInput.type >> anInput.ngen >> anInput.xsec >> anInput.kfactor;

    anInput.xsec *= anInput.kfactor;
    anInput.tfile = new TFile(anInput.fileName);
    anInput.subtype = "none";
    if      ( anInput.fileName.Contains("TTbar-semilep")        ) anInput.subtype = "ttsemi";
    if      ( anInput.fileName.Contains("TTbar-dilep")          ) anInput.subtype = "ttdile";
    if      ( anInput.fileName.Contains("TTbar-hadron")         ) anInput.subtype = "tthadr";
    if      ( anInput.fileName.Contains("W1Jets")               ) anInput.subtype = "wjets";
    if      ( anInput.fileName.Contains("W2Jets")               ) anInput.subtype = "wjets";
    if      ( anInput.fileName.Contains("W3Jets")               ) anInput.subtype = "wjets";
    if      ( anInput.fileName.Contains("W4Jets")               ) anInput.subtype = "wjets";
    if      ( anInput.fileName.Contains("WJets")                ) anInput.subtype = "wjets";
    if      ( anInput.fileName.Contains("WbbJets")                ) anInput.subtype = "wjets";
    if      ( anInput.fileName.Contains("T_s-channel")          ) anInput.subtype = "s-top";
    if      ( anInput.fileName.Contains("T_t-channel")          ) anInput.subtype = "s-top";
    if      ( anInput.fileName.Contains("T_tW-channel")         ) anInput.subtype = "s-top";
    if      ( anInput.fileName.Contains("Tbar_s-channel")       ) anInput.subtype = "s-top";
    if      ( anInput.fileName.Contains("Tbar_t-channel")       ) anInput.subtype = "s-top";
    if      ( anInput.fileName.Contains("Tbar_tW-channel")      ) anInput.subtype = "s-top";
    if      ( anInput.fileName.Contains("WW")                   ) anInput.subtype = "dibo";
    if      ( anInput.fileName.Contains("WZ")                   ) anInput.subtype = "dibo";
    if      ( anInput.fileName.Contains("ZZ")                   ) anInput.subtype = "dibo";
    if      ( anInput.fileName.Contains("DYJetsToLL")           ) anInput.subtype = "zjets";

    aStream->width(12);		*aStream << "Opening : "; 		
    aStream->width(40);		*aStream << anInput.fileName;
    aStream->width(8);		*aStream << anInput.type;
    aStream->width(8);		*aStream << anInput.subtype;
    aStream->width(10);		*aStream << anInput.ngen;
    aStream->width(12);
    aStream->precision(6);	*aStream << anInput.xsec;
    aStream->width(8);	
    aStream->precision(6);	*aStream << anInput.kfactor;
    *aStream << endl;

    _inputs.push_back(anInput);
  }
  cout << "######################################################################################################" << endl;

  return true;
}

//==============================================================================
void PlotIt::plot(const TString& histo,Int_t rebin, TString xtitle, TString legpos)
  //==============================================================================
{
  plotbase(histo);

  if (rebin != 1) {
    if (_hdata != 0) _hdata->Rebin(rebin);
    if (_hmc   != 0) _hmc  ->Rebin(rebin);
    if (_hsig  != 0) _hsig ->Rebin(rebin);
  }

  if (_hdata != 0) h1_style(_hdata,3,38,1,3001,38,_ymin,_ymax,510,510,20,38,1.,1);
  if (_hmc   != 0) h1_style(_hmc,  2,28,1,3001,28,_ymin,_ymax,510,510,22,28,1.,1);
  if (_hsig  != 0) h1_style(_hsig, 2,50,2,3001,50,_ymin,_ymax,510,510,23,50,1.,1);

  if (xtitle != "dummy") _hdata->GetXaxis()->SetTitle(xtitle.Data());

  Float_t inter = _hdata->GetXaxis()->GetXmax() - _hdata->GetXaxis()->GetXmin();
  Float_t num   = (inter/(Float_t)_hdata->GetXaxis()->GetNbins());
  TString ytitle;
  if (1000.*num<1.) ytitle = TString::Format("Events / %0.4f", num);
  else {if (100.*num<1.) ytitle = TString::Format("Events / %0.3f", num);
    else {if (10.*num<1.) ytitle = TString::Format("Events / %0.2f", num);
      else {if (num<1.) ytitle = TString::Format("Events / %0.1f", num);
        else ytitle = TString::Format("Events / %1.0f", num);} } }
        _hdata->GetYaxis()->SetTitle(ytitle.Data());

        TCanvas *c1 = new TCanvas("c1"," ",700,600);
        canvas_style(c1);

        Stat_t max = _hmc->GetMaximum()*1.20;
        _hmc->SetMaximum(max);
        max = _hdata->GetMaximum()*1.20;
        if ( max > _hmc->GetMaximum() )  _hmc->SetMaximum(max);

        if (_hdata != 0) _hdata->SetStats(kFALSE);
        if (_hmc   != 0) _hmc  ->SetStats(kFALSE);
        if (_hsig  != 0) _hsig ->SetStats(kFALSE);

        _hdata->Draw("e4s");
        _hmc->Draw("e4same");
        if (_hsig != 0 ) _hsig->Draw("e4same");

        Double_t x1=0.63; Double_t y1 = 0.63;
        Double_t x2=0.93; Double_t y2 = 0.88;
        if (legpos != "right") {
          x1=0.1; y1 = 0.63;
          x2=0.4; y2 = 0.88;
        }

        TLegend *leg = new TLegend(x1,y1,x2,y2,NULL,"brNDC");
        leg->SetTextSize(0.04);
        leg->SetFillStyle(1);
        leg->SetFillColor(10);
        leg->SetTextFont(52);
        leg->SetTextAlign(32);

        leg->AddEntry(_hdata,"Data","f");
        leg->AddEntry(_hmc  ,"Sig. + bkgd. (CMS)","f");
        if ( _hsig != 0 ) leg->AddEntry(_hsig ,"Signal (Pythia6)","f");

        leg->Draw();

        gPad->Update();
        _hdata->Draw("axissame");

}

//==============================================================================
void PlotIt::plotsub(const TString& histo,Int_t rebin, TString xtitle, TString legpos)
  //==============================================================================
{
  std::ostream* aStream = &cout;

  // Loop over input file for MC :
  //______________________________

  if (_hdata  != 0 ) _hdata->Delete();
  if (_hmc    != 0 ) _hmc->Delete();
  if (_httd   != 0 ) _httd->Delete();
  if (_htts   != 0 ) _htts->Delete();
  if (_hsig   != 0 ) _hsig->Delete();

  Ntotdata = 0.;
  Ntotmc   = 0.; ErrNtotmc  = 0.;
  Ntotsig  = 0.; ErrNtotsig = 0.;
  float ErrNttd = 0.; 
  float ErrNtts = 0.;

  int nmc   = 0;
  int ndata = 0;
  int nttd  = 0;
  int ntts  = 0;
  int nsig  = 0;

  for (int i=0; i< (int)_inputs.size(); i++) {

    // Process data
    if (_inputs[i].type == "data") {
      TH1F* tempdata = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if ( !checkHisto(tempdata) ) return;
      if (ndata == 0) {
        _hdata = (TH1F*)tempdata->Clone("HDATA");
        _hdata->Reset();
      }
      _hdata->Add(tempdata);
      _inputs[i].Nexp    = (Float_t)tempdata->Integral();
      _inputs[i].ErrNexp = 0.;
      Ntotdata += _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp << endl;

      ndata++;
    }

    // Process  backgrounds :
    if (_inputs[i].type == "mc") {
      TH1F* tempmc = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      //checkHisto(tempmc);
      if (nmc == 0) {
        _hmc = (TH1F*)tempmc->Clone("HMC");
        _hmc->Reset();
      }
      Float_t intlumi = _lumi;
      Float_t Factor   = intlumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempmc->Integral();

      _inputs[i].Nexp    = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries*(1. - nentries/(Float_t)_inputs[i].ngen));;

      Ntotmc    += _inputs[i].Nexp;
      ErrNtotmc += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      _inputs[i].Eff    = nentries/(Float_t)_inputs[i].ngen;
      _inputs[i].ErrEff = 0.;
      if ( _inputs[i].Nexp ) _inputs[i].ErrEff = _inputs[i].Eff * _inputs[i].ErrNexp / _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrNexp;
      *aStream << " | ";
      aStream->width(10);  *aStream << _inputs[i].Eff;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrEff << endl;

      _hmc->Add(tempmc,Factor);

      if ( _inputs[i].fileName.Contains("TTbar-dilep") ) {
        if ( nttd == 0 ) { _httd = (TH1F*)tempmc->Clone("HTTD"); _httd->Reset(); }
        _httd->Add(tempmc,Factor);
        ++nttd;
        ErrNttd = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("TTbar-semilep") ) {
        if ( ntts == 0 ) { _htts = (TH1F*)tempmc->Clone("HTTS"); _htts->Reset(); }
        _htts->Add(tempmc,Factor);
        ++ntts;
        ErrNtts = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }


      ++nmc;
    }

    // Process Signal (Pythia6)
    if (_inputs[i].type == "sig") {
      TH1F* tempsig = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if (nsig == 0) {
        _hsig = (TH1F*)tempsig->Clone("HSIG");
        _hsig->Reset();
      }
      Float_t Factor   = _lumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempsig->Integral();

      _inputs[i].Nexp    = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries *(1. - nentries/(Float_t)_inputs[i].ngen));

      Ntotsig    += _inputs[i].Nexp;
      ErrNtotsig += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      _inputs[i].Eff    = nentries/(Float_t)_inputs[i].ngen;
      _inputs[i].ErrEff = 0.;
      if (_inputs[i].Nexp) _inputs[i].ErrEff = _inputs[i].Eff * _inputs[i].ErrNexp / _inputs[i].Nexp;

      aStream->width(40); *aStream << _inputs[i].fileName;
      aStream->width(10); *aStream << _inputs[i].Nexp;
      aStream->width(5);  *aStream << " +/- ";
      aStream->width(10); *aStream << _inputs[i].ErrNexp;
      *aStream << " | ";
      aStream->width(10); *aStream << _inputs[i].Eff;
      aStream->width(5);  *aStream << " +/- ";
      aStream->width(10); *aStream << _inputs[i].ErrEff << endl;

      _hsig->Add(tempsig,Factor);

      nsig++;
    }

  } // end loop

  ErrNtotmc  = sqrt(ErrNtotmc);
  ErrNtotsig = sqrt(ErrNtotsig);
  ErrNttd = sqrt(ErrNttd);
  ErrNtts = sqrt(ErrNtts);

  cout << "########################################################################################" << endl;
  cout << " data               : " << Ntotdata << endl;
  cout << " sig. + bkgd. (CMS) : " << Ntotmc   << " +/- " << ErrNtotmc  << endl;
  cout << " signal (Py6)       : " << Ntotsig  << " +/- " << ErrNtotsig << endl;
  cout << "########################################################################################" << endl;
  if ( _httd != 0 ) cout << " ttbar dilepton  = " << _httd->Integral() << " +/- " << ErrNttd  << endl;
  if ( _htts != 0 ) cout << " ttbar semi-lep  = " << _htts->Integral() << " +/- " << ErrNtts  << endl;
  cout << "########################################################################################" << endl;

  _hdata = (TH1F*)_hdata->Clone("HDATA");

  if (rebin != 1) {
    if (_hdata != 0) _hdata->Rebin(rebin);
    if (_hmc   != 0) _hmc  ->Rebin(rebin);
    if (_httd  != 0) _httd ->Rebin(rebin);
    if (_htts  != 0) _htts ->Rebin(rebin);
    if (_hsig  != 0) _hsig ->Rebin(rebin);
  }

  if (xtitle != "dummy") _hdata->GetXaxis()->SetTitle(xtitle.Data());

  Float_t inter = _hdata->GetXaxis()->GetXmax() - _hdata->GetXaxis()->GetXmin();
  Float_t num   = (inter/(Float_t)_hdata->GetXaxis()->GetNbins());
  TString ytitle;
  if (1000.*num<1.) ytitle = TString::Format("Events / %0.4f", num);
  else {if (100.*num<1.) ytitle = TString::Format("Events / %0.3f", num);
    else {if (10.*num<1.) ytitle = TString::Format("Events / %0.2f", num);
      else {if (num<1.) ytitle = TString::Format("Events / %0.1f", num);
        else ytitle = TString::Format("Events / %1.0f", num);} } }
        _hdata->GetYaxis()->SetTitle(ytitle.Data());

        TCanvas *c1 = new TCanvas("c1"," ",700,600);
        canvas_style(c1);

        _hdata->Add(_hmc,-1.);
        _hdata->Add(_httd,1.);
        _hdata->Add(_htts,1.);
        h1_style(_hdata,3,38,1,3001,38,_ymin,_ymax,510,510,20,38,1.,1);
        _hdata->SetStats(kFALSE);
        _hdata->Draw("e4s");

        _hsig->SetStats(kFALSE);
        h1_style(_hsig,3,50,1,3002,50,_ymin,_ymax,510,510,20,50,1.,1);
        _hsig->Draw("samee4s");

        Double_t x1=0.55; Double_t y1 = 0.75;
        Double_t x2=0.93; Double_t y2 = 0.88;
        if (legpos != "right") {
          x1=0.17; y1 = 0.63;
          x2=0.37; y2 = 0.88;
        }

        TLegend *leg = new TLegend(x1,y1,x2,y2,NULL,"brNDC");
        leg->SetTextSize(0.04);
        leg->SetFillStyle(1);
        leg->SetFillColor(10);
        leg->SetLineColor(kWhite);
        leg->SetTextFont(52);
        leg->SetTextAlign(32);
        leg->AddEntry(_hdata,"t#bar{t} signal within data","f");
        leg->AddEntry(_hsig,"Pythia 6 t#bar{t} signal","f");
        leg->Draw();

        gPad->Update();

        _hdata->Draw("axissame");

        if (histo.Contains("TOP_M_RECO_ALL")) {
          TString filename = "MJpsil_data_Py6_";
          TString leg_header;
          if (_inputFile.Contains("mu")){ 
            filename += "mu";
            leg_header = "Muons channel";
          }
          if (_inputFile.Contains("el")){
            filename += "el";
            leg_header = "Electrons channel";
          }
          _hdata->GetXaxis()->SetTitle("M_{J/#psi+l} (GeV/c^{2})");  
          leg->SetTextFont(62);
          leg->SetTextAlign(12);
          leg->SetHeader(leg_header);
          c1->Update();  
          c1->SaveAs(filename+".jpg");
          c1->SaveAs(filename+".eps");
          c1->SaveAs(filename+".C");
          c1->SaveAs(filename+".pdf");
          TFile output(filename+".root","recreate");
          output.cd();
          _hdata->SetName("M_JPSIL");
          _hdata->Write();
          output.Close();
          cout << filename+".root created." << endl;
        }
}


//==============================================================================
void PlotIt::plotbase(const TString& histo)
  //==============================================================================
{
  std::ostream* aStream = &cout;

  // Loop over input file for MC :
  //______________________________

  if (_hdata != 0) _hdata->Delete();
  if (_hmc   != 0) _hmc  ->Delete();
  if (_hsig  != 0) _hsig ->Delete();

  Ntotdata = 0.;
  Ntotmc   = 0.; ErrNtotmc  = 0.;
  Ntotsig  = 0.; ErrNtotsig = 0.;

  int nmc   = 0;
  int ndata = 0;
  int nsig  = 0;

  for (int i=0; i< (int)_inputs.size(); i++) {

    // Process data
    if (_inputs[i].type == "data") {
      TH1F* tempdata = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if ( !checkHisto(tempdata) ) return;
      if (ndata == 0) {
        _hdata = (TH1F*)tempdata->Clone("HDATA");
        _hdata->Reset();
      }
      _hdata->Add(tempdata);
      _inputs[i].Nexp    = (Float_t)tempdata->Integral();
      _inputs[i].ErrNexp = 0.;
      Ntotdata += _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp << endl;

      ++ndata;
    }

    // Process  backgrounds :
    if (_inputs[i].type == "mc") {
      TH1F* tempmc = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if ( !checkHisto(tempmc) ) return;
      if (nmc == 0) {
        _hmc = (TH1F*)tempmc->Clone("HMC");
        _hmc->Reset();
      }
      Float_t intlumi = _lumi;
      Float_t Factor   = intlumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempmc->Integral();

      _inputs[i].Nexp    = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries*(1. - nentries/(Float_t)_inputs[i].ngen));;

      Ntotmc    += _inputs[i].Nexp;
      ErrNtotmc += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      _inputs[i].Eff    = nentries/(Float_t)_inputs[i].ngen;
      _inputs[i].ErrEff = 0.;
      if ( _inputs[i].Nexp ) _inputs[i].ErrEff = _inputs[i].Eff * _inputs[i].ErrNexp / _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrNexp;
      *aStream << " | ";
      aStream->width(10);  *aStream << _inputs[i].Eff;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrEff << endl;

      _hmc->Add(tempmc,Factor);

      ++nmc;
    }

    // Process Signal Pythia 6 :
    if (_inputs[i].type == "sig") {
      TH1F* tempsig = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if ( !checkHisto(tempsig) ) return;
      if (nsig == 0) {
        _hsig = (TH1F*)tempsig->Clone("HSIG");
        _hsig->Reset();
      }
      Float_t Factor   = _lumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempsig->Integral();

      _inputs[i].Nexp    = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries *(1. - nentries/(Float_t)_inputs[i].ngen));;

      Ntotsig    += _inputs[i].Nexp;
      ErrNtotsig += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      _inputs[i].Eff    = nentries/(Float_t)_inputs[i].ngen;
      _inputs[i].ErrEff = 0.;
      if ( _inputs[i].Nexp ) _inputs[i].ErrEff = _inputs[i].Eff * _inputs[i].ErrNexp / _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrNexp;
      *aStream << " | ";
      aStream->width(10);  *aStream << _inputs[i].Eff;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrEff << endl;

      _hsig->Add(tempsig,Factor);

      ++nsig;
    }
  } // end loop

  ErrNtotmc = sqrt(ErrNtotmc);
  ErrNtotsig = sqrt(ErrNtotsig);

  cout << "############################################################################" << endl;
  cout << " data               : " << Ntotdata << endl;
  cout << " sig. + bkgd. (CMS) : " << Ntotmc   << " +/- " << ErrNtotmc  << endl;
  cout << " signal (Py6)       : " << Ntotsig  << " +/- " << ErrNtotsig << endl;
  cout << "############################################################################" << endl;

}

//==============================================================================
void PlotIt::plotstack(const TString& histo,Int_t rebin, Int_t mode, TString xtitle, TString legpos)
  //==============================================================================
{
  std::ostream* aStream = &cout;

  // Loop over input file for MC :
  //______________________________

  if (_hdata  != 0 ) _hdata->Delete();
  if (_hmc    != 0 ) _hmc->Delete();
  if (_hsig   != 0 ) _hsig->Delete();

  if ( _httd   != 0 ) _httd->Delete();
  if ( _htts   != 0 ) _htts->Delete();
  if ( _htth   != 0 ) _htth->Delete();

  if ( _hstack !=0 ) _hstack->Delete();

  Ntotdata = 0.;
  Ntotmc   = 0.; ErrNtotmc  = 0.;
  Ntotsig  = 0.; ErrNtotsig = 0.;
  float ErrNttd = 0.; 
  float ErrNtts = 0.;
  float ErrNtth = 0.;

  int nmc   = 0;
  int ndata = 0;
  int nsig  = 0;

  int nttd = 0;
  int ntts = 0;
  int ntth = 0;

  for (int i=0; i< (int)_inputs.size(); i++) {

    // Process data
    if (_inputs[i].type == "data") {
      TH1F* tempdata = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if ( !checkHisto(tempdata) ) return;
      if (ndata == 0) {
        _hdata = (TH1F*)tempdata->Clone("HDATA");
        _hdata->Reset();
      }
      _hdata->Add(tempdata);
      _inputs[i].Nexp    = (Float_t)tempdata->Integral();
      _inputs[i].ErrNexp = 0.;
      Ntotdata += _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp << endl;

      ndata++;
    }

    // Process Signal Pythia6 :
    if (_inputs[i].type == "sig") {
      TH1F* tempsig = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      //checkHisto(tempsig);
      if (nsig == 0) {
        _hsig = (TH1F*)tempsig->Clone("HSIG");
        _hsig->Reset();
      }
      Float_t Factor   = _lumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempsig->Integral();

      _inputs[i].Nexp    = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries *(1. - nentries/(Float_t)_inputs[i].ngen));;

      Ntotsig    += _inputs[i].Nexp;
      ErrNtotsig += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      _inputs[i].Eff    = nentries/(Float_t)_inputs[i].ngen;
      _inputs[i].ErrEff = 0.;
      if ( _inputs[i].Nexp ) _inputs[i].ErrEff = _inputs[i].Eff * _inputs[i].ErrNexp / _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrNexp;
      *aStream << " | ";
      aStream->width(10);  *aStream << _inputs[i].Eff;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrEff << endl;

      _hsig->Add(tempsig,Factor);

      nsig++;
    }
  } // end loop data + sig

  for (int i=0; i< (int)_inputs.size(); i++) {
    // Process  backgrounds :
    if (_inputs[i].type == "mc") {
      TH1F* tempmc = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      //checkHisto(tempmc);
      if (nmc == 0) {
        _hmc = (TH1F*)tempmc->Clone("HMC");
        _hmc->Reset();
      }
      Float_t intlumi = _lumi;
      Float_t Factor   = intlumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempmc->Integral();

      _inputs[i].Nexp    = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries*(1. - nentries/(Float_t)_inputs[i].ngen));;

      Ntotmc    += _inputs[i].Nexp;
      ErrNtotmc += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      _inputs[i].Eff    = nentries/(Float_t)_inputs[i].ngen;
      _inputs[i].ErrEff = 0.;
      if ( _inputs[i].Nexp ) _inputs[i].ErrEff = _inputs[i].Eff * _inputs[i].ErrNexp / _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrNexp;
      *aStream << " | ";
      aStream->width(10);  *aStream << _inputs[i].Eff;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrEff << endl;

      _hmc->Add(tempmc,Factor);

      if ( _inputs[i].fileName.Contains("TTbar-hadron") ) {
        if (_hsig !=0)  _hsig->Add(tempmc,Factor);
      }

     if ( _inputs[i].fileName.Contains("TTbar-dilep") ) {
        if ( nttd == 0 ) { _httd = (TH1F*)tempmc->Clone("HTTD"); _httd->Reset(); }
        _httd->Add(tempmc,Factor);
        ++nttd;
        ErrNttd = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("TTbar-semilep") ) {
        if ( ntts == 0 ) { _htts = (TH1F*)tempmc->Clone("HTTS"); _htts->Reset(); }
        _htts->Add(tempmc,Factor);
        ++ntts;
        ErrNtts = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("TTbar-hadron") ) {
        if ( ntth == 0 ) { _htth = (TH1F*)tempmc->Clone("HTTH"); _htth->Reset(); }
        _htth->Add(tempmc,Factor);
        ++ntth;
        ErrNtth = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      ++nmc;
    }


  } // end loop back.

  ErrNtotmc = sqrt(ErrNtotmc);
  ErrNtotsig = sqrt(ErrNtotsig);
  ErrNttd = sqrt(ErrNttd);
  ErrNtts = sqrt(ErrNtts);
  ErrNtth = sqrt(ErrNtth);

  cout << "########################################################################################" << endl;
  if (_hdata != 0) cout << " data               : " << Ntotdata << endl;
  if (_hmc   != 0) cout << " sig. + bkgd. (CMS) : " << Ntotmc   << " +/- " << ErrNtotmc  << endl;
  if (_hsig  != 0) cout << " signal (Pythia 6)  : " << Ntotsig  << " +/- " << ErrNtotsig << endl;
  cout << "########################################################################################" << endl;
  if ( _httd != 0 ) cout << " ttbar dilepton  = " << _httd->Integral() << " +/- " << ErrNttd  << endl;
  if ( _htts != 0 ) cout << " ttbar semi-lep  = " << _htts->Integral() << " +/- " << ErrNtts  << endl;
  if ( _htth != 0 ) cout << " ttbar hadronic  = " << _htth->Integral() << " +/- " << ErrNtth  << endl;
  cout << "########################################################################################" << endl;

  // Hstack :
  //_________

  if (rebin != 1) {
    if (_hdata != 0) _hdata->Rebin(rebin);
    if (_hmc   != 0) _hmc  ->Rebin(rebin);
    if (_hsig  != 0) _hsig ->Rebin(rebin);
    if (_httd  != 0) _httd ->Rebin(rebin);
    if (_htts  != 0) _htts ->Rebin(rebin);
    if (_htth  != 0) _htth ->Rebin(rebin);
  }

  if (mode != 1 && _hsig != 0 && _hmc != 0) _hsig->Add(_hmc);

  if (_hdata != 0) h1_style(_hdata,3,4,1,1001,50,_ymin,_ymax,510,510,20,1,1.,1);
  if (_hmc   != 0) h1_style(_hmc,  2,1,1,-1111,10,_ymin,_ymax,510,510,20,1,1.,1);

  if ( _hsig != 0 ) {
    if ( mode == 1 ) h1_style(_hsig, 3,1,2,-1111,0,_ymin,_ymax,510,510, 5,1,1.,1);
    else             h1_style(_hsig, 2,1,2,3645, 1,_ymin,_ymax,510,510, 5,1,1.,1);
  }
  if ( _httd != 0 ) h1_style(_httd,  2,  3,1,1001,  3,_ymin,_ymax,510,510,20,1,1.,1);
  if ( _htts != 0 ) h1_style(_htts,  2,  2,1,1001,  2,_ymin,_ymax,510,510,20,1,1.,1);
  if ( _htth != 0 ) h1_style(_htth,  2,  4,1,1001,  4,_ymin,_ymax,510,510,20,1,1.,1);

  _hstack = new THStack("hs","test stacked histograms");
  if ( _htth != 0 ) _hstack->Add(_htth);
  if ( _httd != 0 ) _hstack->Add(_httd);
  if ( _htts != 0 ) _hstack->Add(_htts);

  if (xtitle != "dummy" ) {
    if (_hdata != 0) _hdata->GetXaxis()->SetTitle(xtitle.Data());
    else { 
      if (_hmc !=0)  _hmc->GetXaxis()->SetTitle(xtitle.Data());
      else if (_hsig !=0)  _hsig->GetXaxis()->SetTitle(xtitle.Data());
    }
  }

  Float_t inter = 0; Float_t num = 0;
  if (_hdata != 0) {
    inter = _hdata->GetXaxis()->GetXmax() - _hdata->GetXaxis()->GetXmin();
    num   = (Float_t)(inter/(Float_t)_hdata->GetXaxis()->GetNbins());
  }
  else { 
    if (_hmc !=0) {
      inter = _hmc->GetXaxis()->GetXmax() - _hmc->GetXaxis()->GetXmin();
      num   = (Float_t)(inter/(Float_t)_hmc->GetXaxis()->GetNbins());
    }
    else if (_hsig !=0) {
      inter = _hsig->GetXaxis()->GetXmax() - _hsig->GetXaxis()->GetXmin();
      num   = (Float_t)(inter/(Float_t)_hsig->GetXaxis()->GetNbins());
    } 
  }
  TString ytitle;
  if (1000.*num<1.) ytitle = TString::Format("Events / %0.4f", num);
  else {
    if (100.*num<1.) ytitle = TString::Format("Events / %0.3f", num);
    else {
      if (10.*num<1.) ytitle = TString::Format("Events / %0.2f", num);
      else {
        if (num<1.) ytitle = TString::Format("Events / %0.1f", num);
        else ytitle = TString::Format("Events / %1.0f", num);
      } 
    } 
  }
  if (_hdata != 0) _hdata->GetYaxis()->SetTitle(ytitle.Data());
  else { 
    if (_hmc !=0)  _hmc->GetYaxis()->SetTitle(ytitle.Data());
    else if (_hsig !=0)  _hsig->GetYaxis()->SetTitle(ytitle.Data());
  }

  TCanvas *c1 = new TCanvas("c1"," ",700,600);
  canvas_style(c1);

  if ( _ymax < 0. ) {
    Stat_t max1 = 0.;
    if (_hdata != 0)  max1 = _hdata->GetMaximum()*1.20;
    Stat_t max2 = 0.;
    if (_hmc != 0)    max2 = _hmc->GetMaximum()*1.20;
    Stat_t max3 = 0.;
    if ( _hsig != 0 ) max3 = _hsig->GetMaximum()*1.20;
    Stat_t max = max1;
    if ( max2 > max ) max = max2;
    if ( max3 > max ) max = max3;
    if (_hdata != 0) _hdata->SetMaximum(max);
    if (_hsig  != 0) _hsig->SetMaximum(max);
    if (_hmc   != 0) _hmc->SetMaximum(max);
  } else {
    if (_hdata != 0) _hdata->SetMaximum(_ymax);
    if (_hsig  != 0) _hsig->SetMaximum(_ymax);
    if (_hmc   != 0) _hmc->SetMaximum(_ymax);
  }
  if ( _ymin > 0. ) {
    if (_hdata != 0) _hdata->SetMinimum(_ymin);
    if (_hsig  != 0) _hsig->SetMinimum(_ymin);
    if (_hmc   != 0) _hmc->SetMinimum(_ymin);
  }

  if (_hdata != 0) _hdata->SetStats(kFALSE);
  if (_hmc   != 0) _hmc->SetStats(kFALSE);
  if ( _hsig != 0 ) _hsig->SetStats(kFALSE);

  if ( mode == 1 ) {
    if (_hdata != 0) {
      _hdata->Draw("e");
      if (_hmc != 0) {
        _hmc->Draw("histsame");
        _hstack->Draw("histsame");
      }
      if ( _hsig != 0 ) _hsig->Draw("histsame");
    } else {
      if (_hmc != 0) {
        _hmc->Draw("hist");
        _hstack->Draw("histsame");
        if ( _hsig != 0 ) _hsig->Draw("histsame");
      }
      else if (_hsig != 0) _hsig->Draw("hist");
    }
  } 
  if (_hdata != 0) _hdata->Draw("axissame");
  else if (_hmc != 0) _hmc->Draw("axissame");

  if (_hstack != 0) {
    _hstack->GetHistogram()->SetLabelFont(62,"X");       // 42
    _hstack->GetHistogram()->SetLabelFont(62,"Y");       // 42
    _hstack->GetHistogram()->SetLabelOffset(0.01,"X");  // D=0.005
    _hstack->GetHistogram()->SetLabelOffset(0.01,"Y");  // D=0.005
    _hstack->GetHistogram()->SetLabelSize(0.045,"X");
    _hstack->GetHistogram()->SetLabelSize(0.045,"Y");
    _hstack->GetHistogram()->SetTitleOffset(1.0,"X");
    _hstack->GetHistogram()->SetTitleOffset(1.2,"Y");
    _hstack->GetHistogram()->SetTitleSize(0.06,"X");
    _hstack->GetHistogram()->SetTitleSize(0.06,"Y");
    _hstack->GetHistogram()->SetTitle(0);
  }

  //  Double_t x1=0.65; Double_t y1 = 0.41;
  //  Double_t x2=0.95; Double_t y2 = 0.9;
  Double_t x1=0.65; Double_t y1 = 0.61; ////////////////////////////////
  Double_t x2=0.945; Double_t y2 = 0.895; //////////////////////////////
  if (legpos != "right") {
    x1=0.17; y1 = 0.61;
    //    x2=0.37; y2 = 0.88;
    x2=0.47; y2 = 0.895;
  }

  TLegend *leg = new TLegend(x1,y1,x2,y2,NULL,"brNDC");
  leg->SetTextSize(0.03);
  //  leg->SetFillStyle(1);
  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetLineColor(kWhite); ///////////////////////////////////////////
  leg->SetTextFont(52);
  //  leg->SetTextAlign(32);
  //  leg->SetTextFont(62);
  leg->SetTextAlign(12);
  leg->SetBorderSize(1);

  if (_hdata != 0 )  leg->AddEntry(_hdata,"Data","P");

  if ( _hsig != 0 )  leg->AddEntry(_hsig,"#splitline{Pythia 6 t#bar{t} signal}{+ background}","l");

  if ( _htts != 0 )  leg->AddEntry(_htts,"t#bar{t} semi-lept.","f");
  if ( _httd != 0 )  leg->AddEntry(_httd,"t#bar{t} dilept.","f");
  if ( _htth != 0 )  leg->AddEntry(_htth,"t#bar{t} hadronic","f");

  leg->Draw();

  gPad->Update();

}

//==============================================================================
void PlotIt::GetBinContent(const TString& histo, const Int_t& ibin, bool print)
  //==============================================================================
{
  std::ostream* aStream = &cout;

  // Loop over input file for MC :
  //______________________________

  if (_hdata != 0) _hdata->Delete();
  if (_hmc   != 0) _hmc  ->Delete();
  if (_hsig  != 0) _hsig ->Delete();

  Ntotdata = 0.;
  Ntotmc   = 0.; ErrNtotmc  = 0.;
  Ntotsig  = 0.; ErrNtotsig = 0.;

  int nmc   = 0;
  int ndata = 0;
  int nsig  = 0;

  for (int i=0; i< (int)_inputs.size(); i++) {

    // Process data
    if (_inputs[i].type == "data") {
      TH1F* tempdata = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if (ndata == 0) {
        _hdata = (TH1F*)tempdata->Clone("HDATA");
        _hdata->Reset();
      }
      _hdata->Add(tempdata);
      _inputs[i].Nexp    = (Float_t)tempdata->GetBinContent(ibin);
      _inputs[i].ErrNexp = 0.;
      Ntotdata += _inputs[i].Nexp;

      if ( print ) {
        aStream->width(25);  *aStream << _inputs[i].fileName;
        aStream->width(10);  *aStream << _inputs[i].Nexp << endl;
      }
      ndata++;
    }

    // Process  backgrounds :
    if (_inputs[i].type == "mc") {
      TH1F* tempmc = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if (nmc == 0) {
        _hmc = (TH1F*)tempmc->Clone("HMC");
        _hmc->Reset();
      }
      Float_t intlumi = _lumi;
      Float_t Factor   = intlumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempmc->GetBinContent(ibin);

      _inputs[i].Nexp    = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries*(1. - nentries/(Float_t)_inputs[i].ngen));;

      Ntotmc    += _inputs[i].Nexp;
      ErrNtotmc += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      if ( print ) {
        aStream->width(25);  *aStream << _inputs[i].fileName;
        aStream->width(10);  *aStream << _inputs[i].Nexp;
        aStream->width(5);   *aStream << " +/- ";
        aStream->width(10);  *aStream << _inputs[i].ErrNexp << endl;
      }

      _hmc->Add(tempmc,Factor);

      nmc++;
    }

    // Process Signal Pythia 6 :
    if (_inputs[i].type == "sig") {
      TH1F* tempsig = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if (nsig == 0) {
        _hsig = (TH1F*)tempsig->Clone("HSIG");
        _hsig->Reset();
      }
      Float_t Factor   = _lumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempsig->GetBinContent(ibin);

      _inputs[i].Nexp    = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries *(1. - nentries/(Float_t)_inputs[i].ngen));;

      Ntotsig    += _inputs[i].Nexp;
      ErrNtotsig += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      _inputs[i].Eff    = nentries/(Float_t)_inputs[i].ngen;
      _inputs[i].ErrEff = 0.;
      if ( _inputs[i].Nexp ) _inputs[i].ErrEff = _inputs[i].Eff * _inputs[i].ErrNexp / _inputs[i].Nexp;

      if ( print ) {
        aStream->width(25);  *aStream << _inputs[i].fileName;
        aStream->width(10);  *aStream << _inputs[i].Nexp;
        aStream->width(5);   *aStream << " +/- ";
        aStream->width(10);  *aStream << _inputs[i].ErrNexp;
        *aStream << " | ";
        aStream->width(10);  *aStream << _inputs[i].Eff;
        aStream->width(5);   *aStream << " +/- ";
        aStream->width(10);  *aStream << _inputs[i].ErrEff << endl;
      }

      _hsig->Add(tempsig,Factor);

      nsig++;
    }

  } // end loop

  ErrNtotmc = sqrt(ErrNtotmc);
  ErrNtotsig = sqrt(ErrNtotsig);

  if ( print ) {
    cout << "############################################################################" << endl;
    cout << " data               : " << Ntotdata << endl;
    cout << " sig. + bkgd. (CMS) : " << Ntotmc   << " +/- " << ErrNtotmc  << endl;
    cout << " signal (Py6)       : " << Ntotsig  << " +/- " << ErrNtotsig << endl;
    cout << "############################################################################" << endl;
  }
}


//==============================================================================
void PlotIt::plotratio()
  //==============================================================================
{
  _hdata->Divide(_hmc);
  TCanvas *c2 = new TCanvas("c2"," ",700,600);
  canvas_style(c2);

  _hdata->SetMaximum(2.);
  _hdata->SetMinimum(0.);

  _hdata->Draw("e");

}

//==============================================================================
void PlotIt::plotstackratio(const TString& histo,Int_t rebin, Int_t mode, TString xtitle, TString legpos)
  //==============================================================================
{
  std::ostream* aStream = &cout;

  // Loop over input file for MC :
  //______________________________

  if (_hdata  != 0 ) _hdata->Delete();
  if (_hmc    != 0 ) _hmc->Delete();
  if (_hsig   != 0 ) _hsig->Delete();
  if (_hqcd   != 0 ) _hqcd->Delete();

  if ( _httd   != 0 ) _httd->Delete();
  if ( _htts   != 0 ) _htts->Delete();
  if ( _htth   != 0 ) _htth->Delete();
  if ( _hsto   != 0 ) _hsto->Delete();
  if ( _hwln   != 0 ) _hwln->Delete();
  if ( _hzll   != 0 ) _hzll->Delete();
  if ( _hdib   != 0 ) _hdib->Delete();

  if ( _hstack !=0 ) _hstack->Delete();

  Ntotdata = 0.;
  Ntotmc   = 0.; ErrNtotmc  = 0.;
  Ntotsig  = 0.; ErrNtotsig = 0.;
  float ErrNttd = 0.; 
  float ErrNtts = 0.;
  float ErrNtth = 0.;
  float ErrNsto = 0.;
  float ErrNwln = 0.;
  float ErrNzll = 0.;
  float ErrNdib = 0.;
  float ErrNqcd = 0.;

  int nmc   = 0;
  int ndata = 0;
  int nsig  = 0;

  int nttd = 0;
  int ntts = 0;
  int ntth = 0;
  int nwln = 0;
  int ndib = 0;
  int nsto = 0;
  int nzll = 0;
  int nqcd = 0;

  for (int i=0; i< (int)_inputs.size(); i++) {
    //    cout << _inputs[i].fileName << endl;

    // Process data
    if (_inputs[i].type == "data") {
      TH1F* tempdata = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      if ( !checkHisto(tempdata) ) return;
      if (ndata == 0) {
        _hdata = (TH1F*)tempdata->Clone("HDATA");
        _hdata->Reset();
      }
      _hdata->Add(tempdata);
      _inputs[i].Nexp	 = (Float_t)tempdata->Integral();
      _inputs[i].ErrNexp = 0.;
      Ntotdata += _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp << endl;

      ndata++;
    }

    // Process Signal Pythia 6 :
    if (_inputs[i].type == "sig") {
      TH1F* tempsig = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      //checkHisto(tempsig);
      if (nsig == 0) {
        _hsig = (TH1F*)tempsig->Clone("HSIG");
        _hsig->Reset();
      }
      Float_t Factor   = _lumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempsig->Integral();

      _inputs[i].Nexp	 = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries *(1. - nentries/(Float_t)_inputs[i].ngen));;

      Ntotsig	 += _inputs[i].Nexp;
      ErrNtotsig += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      _inputs[i].Eff	= nentries/(Float_t)_inputs[i].ngen;
      _inputs[i].ErrEff = 0.;
      if ( _inputs[i].Nexp ) _inputs[i].ErrEff = _inputs[i].Eff * _inputs[i].ErrNexp / _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrNexp;
      *aStream << " | ";
      aStream->width(10);  *aStream << _inputs[i].Eff;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrEff << endl;

      _hsig->Add(tempsig,Factor);

      nsig++;
    }
  } // end loop data + sig

  for (int i=0; i< (int)_inputs.size(); i++) {

    // Process  backgrounds :
    if (_inputs[i].type == "mc") {
      TH1F* tempmc = (TH1F*)_inputs[i].tfile->Get(histo.Data());
      //checkHisto(tempmc);
      if (nmc == 0) {
        _hmc = (TH1F*)tempmc->Clone("HMC");
        _hmc->Reset();
      }
      Float_t intlumi = _lumi;
      Float_t Factor   = intlumi * _inputs[i].xsec / (Float_t)_inputs[i].ngen;
      Float_t nentries = (Float_t)tempmc->Integral();

      _inputs[i].Nexp	 = nentries * Factor;
      _inputs[i].ErrNexp = Factor * Factor * (nentries*(1. - nentries/(Float_t)_inputs[i].ngen));;

      Ntotmc	+= _inputs[i].Nexp;
      ErrNtotmc += _inputs[i].ErrNexp;

      _inputs[i].ErrNexp = sqrt(_inputs[i].ErrNexp);

      _inputs[i].Eff	= nentries/(Float_t)_inputs[i].ngen;
      _inputs[i].ErrEff = 0.;
      if ( _inputs[i].Nexp ) _inputs[i].ErrEff = _inputs[i].Eff * _inputs[i].ErrNexp / _inputs[i].Nexp;

      aStream->width(40);  *aStream << _inputs[i].fileName;
      aStream->width(10);  *aStream << _inputs[i].Nexp;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrNexp;
      *aStream << " | ";
      aStream->width(10);  *aStream << _inputs[i].Eff;
      aStream->width(5);   *aStream << " +/- ";
      aStream->width(10);  *aStream << _inputs[i].ErrEff << endl;

      _hmc->Add(tempmc,Factor);

      if (_inputs[i].fileName.Contains("W1Jets") ||
          _inputs[i].fileName.Contains("W2Jets") ||
          _inputs[i].fileName.Contains("W3Jets") ||
          _inputs[i].fileName.Contains("W4Jets") ||
          _inputs[i].fileName.Contains("WbbJets") ||
          _inputs[i].fileName.Contains("WJets") ||
          _inputs[i].fileName.Contains("DYJetsToLL") ||
          _inputs[i].fileName.Contains("TTbar-hadron") ||
          _inputs[i].fileName.Contains("T_s-channel")	 ||
          _inputs[i].fileName.Contains("T_t-channel")	 ||
          _inputs[i].fileName.Contains("T_tW-channel")   ||
          _inputs[i].fileName.Contains("Tbar_s-channel") ||
          _inputs[i].fileName.Contains("Tbar_t-channel") ||
          _inputs[i].fileName.Contains("Tbar_tW-channel") ||
          _inputs[i].fileName.Contains("WW") ||
          _inputs[i].fileName.Contains("WZ") || 
          _inputs[i].fileName.Contains("ZZ") ||
          _inputs[i].fileName.Contains("QCD") ) {
        if (_hsig !=0)  _hsig->Add(tempmc,Factor);
      }

      if ( _inputs[i].fileName.Contains("W1Jets") ||
          _inputs[i].fileName.Contains("W2Jets") ||
          _inputs[i].fileName.Contains("W3Jets") ||
          _inputs[i].fileName.Contains("W4Jets") ||
          _inputs[i].fileName.Contains("WbbJets") ||
          _inputs[i].fileName.Contains("WJets") ) {
        if ( nwln == 0 ) { _hwln = (TH1F*)tempmc->Clone("HWLN"); _hwln->Reset(); }
        _hwln->Add(tempmc,Factor);
        ++nwln;
        ErrNwln = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("DYJetsToLL") ) {
        if ( nzll == 0 ) { _hzll = (TH1F*)tempmc->Clone("HZLL"); _hzll->Reset(); }
        _hzll->Add(tempmc,Factor);
        ++nzll;
        ErrNzll = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("TTbar-dilep") ) {
        if ( nttd == 0 ) { _httd = (TH1F*)tempmc->Clone("HTTD"); _httd->Reset(); }
        _httd->Add(tempmc,Factor);
        ++nttd;
        ErrNttd = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("TTbar-semilep") ) {
        if ( ntts == 0 ) { _htts = (TH1F*)tempmc->Clone("HTTS"); _htts->Reset(); }
        _htts->Add(tempmc,Factor);
        ++ntts;
        ErrNtts = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("TTbar-hadron") ) {
        if ( ntth == 0 ) { _htth = (TH1F*)tempmc->Clone("HTTH"); _htth->Reset(); }
        _htth->Add(tempmc,Factor);
        ++ntth;
        ErrNtth = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("T_s-channel")    ||
          _inputs[i].fileName.Contains("T_t-channel")    ||
          _inputs[i].fileName.Contains("T_tW-channel")   ||
          _inputs[i].fileName.Contains("Tbar_s-channel") ||
          _inputs[i].fileName.Contains("Tbar_t-channel") ||
          _inputs[i].fileName.Contains("Tbar_tW-channel") ) {
        if ( nsto == 0 ) { _hsto = (TH1F*)tempmc->Clone("HSTO"); _hsto->Reset(); }
        _hsto->Add(tempmc,Factor);
        ++nsto;
        ErrNsto = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("WW") ||
          _inputs[i].fileName.Contains("WZ") || 
          _inputs[i].fileName.Contains("ZZ") ) {
        if ( ndib == 0 ) { _hdib = (TH1F*)tempmc->Clone("HDIB"); _hdib->Reset(); }
        _hdib->Add(tempmc,Factor);
        ++ndib;
        ErrNdib = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      if ( _inputs[i].fileName.Contains("QCD") ) {
        if ( nqcd == 0 ) { _hqcd = (TH1F*)tempmc->Clone("HQCD"); _hqcd->Reset(); }
        _hqcd->Add(tempmc,Factor);
        ++nqcd;
        ErrNqcd = _inputs[i].ErrNexp*_inputs[i].ErrNexp;
      }

      ++nmc;
    }

  } // end loop background

  ErrNtotmc = sqrt(ErrNtotmc);
  ErrNtotsig = sqrt(ErrNtotsig);
  ErrNttd = sqrt(ErrNttd);
  ErrNtts = sqrt(ErrNtts);
  ErrNtth = sqrt(ErrNtth);
  ErrNsto = sqrt(ErrNsto);
  ErrNwln = sqrt(ErrNwln);
  ErrNzll = sqrt(ErrNzll);
  ErrNdib = sqrt(ErrNdib);
  ErrNqcd = sqrt(ErrNqcd);

  cout << "########################################################################################" << endl;
  cout << " data               : " << Ntotdata << endl;
  cout << " sig. + bkgd. (CMS) : " << Ntotmc   << " +/- " << ErrNtotmc  << endl;
  cout << " signal (Pythia 6)  : " << Ntotsig  << " +/- " << ErrNtotsig << endl;
  cout << "########################################################################################" << endl;
  if ( _httd != 0 ) cout << " ttbar dilepton  = " << _httd->Integral() << " +/- " << ErrNttd  << endl;
  if ( _htts != 0 ) cout << " ttbar semi-lep  = " << _htts->Integral() << " +/- " << ErrNtts  << endl;
  if ( _htth != 0 ) cout << " ttbar hadronic  = " << _htth->Integral() << " +/- " << ErrNtth  << endl;
  if ( _hsto != 0 ) cout << " single top      = " << _hsto->Integral() << " +/- " << ErrNsto  << endl;
  if ( _hwln != 0 ) cout << " W+jets          = " << _hwln->Integral() << " +/- " << ErrNwln  << endl;
  if ( _hzll != 0 ) cout << " Z+jets          = " << _hzll->Integral() << " +/- " << ErrNzll  << endl;
  if ( _hdib != 0 ) cout << " Dibos.          = " << _hdib->Integral() << " +/- " << ErrNdib  << endl;
  if ( _hqcd != 0 ) cout << " QCD             = " << _hqcd->Integral() << " +/- " << ErrNqcd  << endl;
  cout << "########################################################################################" << endl;

  // Hstack :
  //_________

  if (rebin != 1) {
    if (_hdata != 0) _hdata->Rebin(rebin);
    if (_hmc   != 0) _hmc  ->Rebin(rebin);
    if (_hsig  != 0) _hsig ->Rebin(rebin);
    if (_hwln  != 0) _hwln ->Rebin(rebin);
    if (_hzll  != 0) _hzll ->Rebin(rebin);
    if (_httd  != 0) _httd ->Rebin(rebin);
    if (_htts  != 0) _htts ->Rebin(rebin);
    if (_htth  != 0) _htth ->Rebin(rebin);
    if (_hsto  != 0) _hsto ->Rebin(rebin);
    if (_hdib  != 0) _hdib ->Rebin(rebin);
    if (_hqcd  != 0) _hqcd ->Rebin(rebin);
  }

  if (mode != 1 && _hsig != 0 && _hmc != 0) _hsig->Add(_hmc);

  h1_style(_hdata,3,4,1,1001,50,_ymin,_ymax,510,510,20,1,1.,1);
  h1_style(_hmc,  2,1,1,-1111,10,_ymin,_ymax,510,510,20,1,1.,1);

  if ( _hsig != 0 ) {
    if ( mode == 1 ) h1_style(_hsig, 3,1,2,-1111,0,_ymin,_ymax,510,510, 5,1,1.,1);
    else	     h1_style(_hsig, 2,1,2,3645, 1,_ymin,_ymax,510,510, 5,1,1.,1);
  }

  if ( _httd != 0 ) h1_style(_httd,  2,  3,1,1001,  3,_ymin,_ymax,510,510,20,1,1.,1);
  if ( _htts != 0 ) h1_style(_htts,  2,  2,1,1001,  2,_ymin,_ymax,510,510,20,1,1.,1);
  if ( _htth != 0 ) h1_style(_htth,  2,  4,1,1001,  4,_ymin,_ymax,510,510,20,1,1.,1);
  if ( _hsto != 0 ) h1_style(_hsto,  2, 28,1,1001, 28,_ymin,_ymax,510,510,20,1,1.,1);
  if ( _hwln != 0 ) h1_style(_hwln,  2, 33,1,1001, 33,_ymin,_ymax,510,510,20,1,1.,1);
  if ( _hzll != 0 ) h1_style(_hzll,  2,870,1,1001,870,_ymin,_ymax,510,510,20,1,1.,1);
  if ( _hdib != 0 ) h1_style(_hdib,  2,  5,1,1001,  5,_ymin,_ymax,510,510,20,1,1.,1);
  if ( _hqcd != 0 ) h1_style(_hqcd,  2,801,1,1001,801,_ymin,_ymax,510,510,20,1,1.,1);

  _hstack = new THStack("hs","test stacked histograms");
  if ( _hqcd != 0 ) _hstack->Add(_hqcd);
  if ( _hwln != 0 ) _hstack->Add(_hwln);
  if ( _hzll != 0 ) _hstack->Add(_hzll);
  if ( _hdib != 0 ) _hstack->Add(_hdib);
  if ( _hsto != 0 ) _hstack->Add(_hsto);
  if ( _htth != 0 ) _hstack->Add(_htth);
  if ( _httd != 0 ) _hstack->Add(_httd);
  if ( _htts != 0 ) _hstack->Add(_htts);

  if (xtitle != "dummy") _hdata->GetXaxis()->SetTitle(xtitle.Data());

  Float_t inter = _hdata->GetXaxis()->GetXmax() - _hdata->GetXaxis()->GetXmin();
  Float_t num   = (inter/(Float_t)_hdata->GetXaxis()->GetNbins());
  TString ytitle;
  if (1000.*num<1.) ytitle = TString::Format("Events / %0.4f", num);
  else {if (100.*num<1.) ytitle = TString::Format("Events / %0.3f", num);
    else {if (10.*num<1.) ytitle = TString::Format("Events / %0.2f", num);
      else {if (num<1.) ytitle = TString::Format("Events / %0.1f", num);
        else ytitle = TString::Format("Events / %1.0f", num);} } }
        _hdata->GetYaxis()->SetTitle(ytitle.Data());

        TCanvas *c1 = new TCanvas("c1"," ",700,750);
        canvas_style(c1);
        c1->cd();
        TPad* pad_hi = new TPad("pad_hi", "", 0., 0.25, 0.99, 0.99);
        pad_hi->Draw();
        pad_hi->SetLeftMargin(0.18);
        pad_hi->SetRightMargin(0.04);
        pad_hi->SetBottomMargin(0.18);
        pad_hi->SetTopMargin(0.05);
        TPad* pad_lo = new TPad("pad_lo", "", 0., 0., 0.99, 0.28);
        pad_lo->Draw();
        pad_lo->SetLeftMargin(0.18);
        pad_lo->SetRightMargin(0.04);
        pad_lo->SetTopMargin(0.05);
        pad_lo->SetBottomMargin(0.17);


        pad_hi->cd();

        if ( _ymax < 0. ) {
          Stat_t max1 = _hdata->GetMaximum()*1.20;
          Stat_t max2 = _hmc->GetMaximum()*1.20;
          Stat_t max3 = 0.;
          if ( _hsig != 0 ) max3 = _hsig->GetMaximum()*1.20;
          Stat_t max = max1;
          if ( max2 > max ) max = max2;
          if ( max3 > max ) max = max3;
          _hdata->SetMaximum(max);
        } else {
          _hdata->SetMaximum(_ymax);
        }
        if ( _ymin > 0. ) _hdata->SetMinimum(_ymin);

        _hdata->SetStats(kFALSE);
        _hmc->SetStats(kFALSE);
        if ( _hsig != 0 ) _hsig->SetStats(kFALSE);

        if ( mode == 1 ) {
          _hdata->Draw("e");
          _hmc->Draw("histsame");
          _hstack->Draw("histsame");
          if ( _hsig != 0 ) _hsig->Draw("histsame");
          _hdata->Draw("esame");
        } else {
          _hdata->Draw("e");
          _hmc->Draw("histsame");
          if ( _hsig != 0 ) _hsig->Draw("histsame");
          _hstack->Draw("histsame");
          _hdata->Draw("esame");
        }

        _hstack->GetHistogram()->SetLabelFont(62,"X");       // 42
        _hstack->GetHistogram()->SetLabelFont(62,"Y");       // 42
        _hstack->GetHistogram()->SetLabelOffset(0.01,"X");  // D=0.005
        _hstack->GetHistogram()->SetLabelOffset(0.01,"Y");  // D=0.005
        _hstack->GetHistogram()->SetLabelSize(0.045,"X");
        _hstack->GetHistogram()->SetLabelSize(0.045,"Y");
        _hstack->GetHistogram()->SetTitleOffset(1.0,"X");
        _hstack->GetHistogram()->SetTitleOffset(1.2,"Y");
        _hstack->GetHistogram()->SetTitleSize(0.06,"X");
        _hstack->GetHistogram()->SetTitleSize(0.06,"Y");
        _hstack->GetHistogram()->SetTitle(0);

        Double_t x1=0.699; Double_t y1 = 0.509;
        Double_t x2=0.999; Double_t y2 = 0.999;
        if (legpos != "right") {
          x1=0.1; y1 = 0.50;
          x2=0.4; y2 = 0.88;
        }

        TLegend *leg = new TLegend(x1,y1,x2,y2,NULL,"brNDC");
        leg->SetTextSize(0.03);
        leg->SetFillStyle(1001);
        //  leg->SetFillStyle(1);
        leg->SetFillColor(10);
        leg->SetTextFont(52);
        //  leg->SetTextAlign(32);
        leg->SetTextAlign(12);
        leg->SetBorderSize(1);

        leg->AddEntry(_hdata,"Data","P");

        if ( _hsig != 0 )  leg->AddEntry(_hsig,"#splitline{Pythia 6 t#bar{t} signal}{+ CMS background}","l");

        if ( _htts != 0 )  leg->AddEntry(_htts,"t#bar{t} semi-lept.","f");
        if ( _httd != 0 )  leg->AddEntry(_httd,"t#bar{t} dilept.","f");
        if ( _htth != 0 )  leg->AddEntry(_htth,"t#bar{t} hadronic","f");
        if ( _hsto != 0 )  leg->AddEntry(_hsto,"single-top","f");
        if ( _hdib != 0 )  leg->AddEntry(_hdib,"WW,WZ,ZZ","f");
        if ( _hzll != 0 )  leg->AddEntry(_hzll,"Z+jets","f");
        if ( _hwln != 0 )  leg->AddEntry(_hwln,"W#rightarrow l#nu + jets","f");
        if ( _hqcd != 0 )  leg->AddEntry(_hqcd,"QCD","f");

        leg->Draw();

        gPad->Update();

        pad_hi->Update();
        pad_hi->Modified();

        pad_lo->cd();
        pad_lo->SetGridx();
        pad_lo->SetGridy();

        TH1F* _hdata_ratio=(TH1F*) _hdata->Clone("HDATA_RATIO");
        TH1F* _hmc_ratio=(TH1F*) _hmc->Clone("HMC_RATIO");

        _hdata_ratio->Divide(_hmc_ratio);


        _hdata_ratio->SetMaximum(2.);
        _hdata_ratio->SetMinimum(0.);

        _hdata_ratio->Draw("e");

        ((TH1*)((TPad*) c1->GetPrimitive("pad_lo"))->GetPrimitive("HDATA_RATIO"))->SetXTitle("");
        ((TH1*)((TPad*) c1->GetPrimitive("pad_lo"))->GetPrimitive("HDATA_RATIO"))->SetYTitle("Data/MC ratio");
        ((TH1*)((TPad*) c1->GetPrimitive("pad_lo"))->GetPrimitive("HDATA_RATIO"))->GetYaxis()->SetTitleSize(0.135);
        ((TH1*)((TPad*) c1->GetPrimitive("pad_lo"))->GetPrimitive("HDATA_RATIO"))->GetYaxis()->SetTitleOffset(0.45);
        ((TH1*)((TPad*) c1->GetPrimitive("pad_lo"))->GetPrimitive("HDATA_RATIO"))->GetYaxis()->SetLabelSize(0.1);
        ((TH1*)((TPad*) c1->GetPrimitive("pad_lo"))->GetPrimitive("HDATA_RATIO"))->GetXaxis()->SetLabelSize(0.1);
        ((TH1*)((TPad*) c1->GetPrimitive("pad_lo"))->GetPrimitive("HDATA_RATIO"))->GetYaxis()->SetNdivisions(503);

        pad_lo->Update();
        pad_lo->Modified();
}
