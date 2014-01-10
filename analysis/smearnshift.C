void latex_style(TLatex *latex,
    double text_size = 0.035,
    int text_font = 62,
    int text_align = 22,
    int text_color = 1) {
  latex->SetTextSize(text_size);
  latex->SetTextFont(text_font);
  latex->SetTextAlign(text_align);
  latex->SetTextColor(text_color);
  latex->SetNDC();
}

void leg_style(TLegend *leg,
    double text_size = 0.035,
    int text_font = 62,
    int text_align = 22,
    int fill_style = 1,
    int fill_color = 10,
    int border_size = 1) {
  leg->SetTextSize(text_size);
  leg->SetTextFont(text_font);
  leg->SetTextAlign(text_align);
  leg->SetFillStyle(fill_style);
  leg->SetFillColor(fill_color);
  leg->SetBorderSize(border_size);
}

void h1_style(TH1 *h,
    int line_width=2,
    int line_color=1,
    int line_style=1, 
    int fill_color=50,
    int fill_style=1001,
    float y_min=-1111.,
    float y_max=-1111.,
    int ndivx=510,
    int ndivy=510,
    int marker_style=20,
    int marker_color=1,
    float marker_size=1.2,
    int optstat=0,
    const char* title="",
    const char* xtitle="",
    const char* ytitle="") {

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
  h->SetLabelSize(0.05,"X");
  h->SetLabelSize(0.05,"Y");
  h->SetTitleOffset(1.0,"X");
  h->SetTitleOffset(1.0,"Y");
  h->SetTitleSize(0.045,"X");
  h->SetTitleSize(0.045,"Y");
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  h->SetTitle(title);
}

void grapherror_style(TGraphErrors *gr,
    const char* name="",
    int line_width=2,
    int line_color=1,
    int line_style=1, 
    int fill_color=50,
    int fill_style=1001,
    float y_min=-1111.,
    float y_max=-1111.,
    int ndivx=510,
    int ndivy=510,
    int marker_style=20,
    int marker_color=1,
    float marker_size=1.2,
    const char* title="",
    const char* xtitle="",
    const char* ytitle="") {

  gr->SetLineWidth(line_width);
  gr->SetLineColor(line_color);
  gr->SetLineStyle(line_style);
  gr->SetFillColor(fill_color);
  gr->SetFillStyle(fill_style);
  gr->SetMaximum(y_max);
  gr->SetMinimum(y_min);
  gr->GetXaxis()->SetNdivisions(ndivx);
  gr->GetYaxis()->SetNdivisions(ndivy);

  gr->SetMarkerStyle(marker_style);
  gr->SetMarkerColor(marker_color);
  gr->SetMarkerSize(marker_size);

  gr->GetXaxis()->SetLabelFont(62);	// 42
  gr->GetYaxis()->SetLabelFont(62);	// 42
  gr->GetXaxis()->SetLabelOffset(0.01);  // D=0.005
  gr->GetYaxis()->SetLabelOffset(0.01);  // D=0.005
  gr->GetXaxis()->SetLabelSize(0.05);
  gr->GetYaxis()->SetLabelSize(0.05);
  gr->GetXaxis()->SetTitleOffset(1.0);
  gr->GetYaxis()->SetTitleOffset(1.0);
  gr->GetXaxis()->SetTitleSize(0.045);
  gr->GetYaxis()->SetTitleSize(0.045);
  gr->GetXaxis()->SetTitle(xtitle);
  gr->GetYaxis()->SetTitle(ytitle);
  gr->SetTitle(title);
  gr->SetName(name);

}

double *step(double inf,double sup, TString mtl_s, TString weight_s, TTree *tree, bool control) {


  //---- Variables
  RooRealVar mtl(mtl_s, "M_{J/#psi+l}", 0., 250., "GeV/c^{2}");
  RooRealVar weight(weight_s, "weight", 0., 2.);


  //---- Fit for all
  RooDataSet *dataset = new RooDataSet("dataset", "dataset for gen events", RooArgSet(mtl, weight), Import(*tree), WeightVar(weight));

  dataset->Print();

  RooRealVar mean("mean", "mass",90.,50.,130.) ;
  RooRealVar width("width", "width",25.,10.,40.) ;

  RooGaussian pdf("pdf","pdf",mtl,mean,width);

  pdf.fitTo(*dataset,Range(inf,sup));

  if(control) {
    TCanvas *cn_roofit = new TCanvas("cn_roofit","all pairing",700,500);
    cn_roofit->cd();
    RooPlot* massframe = mtl.frame(Title("Mass of the combination of the J/#psi and the isolated lepton")) ;
    dataset->plotOn(massframe,Binning(50)) ;
    pdf.plotOn(massframe,Range(inf,sup)) ;
    massframe->Draw();

    gPad->Update();
    getchar();
  }
  //----------------------------- Fit parameters

  double *mean_err = new double[2];
  mean_err[0]=mean.getVal();
  mean_err[1]=mean.getError();

  return mean_err;
}

int smearnshift(TString channel, TString date="140109", int rebin=10, bool tosave=false, bool control=false){

  gSystem->Load("libRooFit");
  using namespace RooFit ;

  //rebin in 2,5,10,17

  vector<TString> inputfilename; 
  inputfilename.push_back("_2jets40_chi5_mudist105_drjet03_ctausup_shiftd_smear1_140109/TTbar173.root");
  inputfilename.push_back("_2jets40_chi5_mudist105_drjet03_ctausup_shift1_smear2_140109/TTbar173.root");
  inputfilename.push_back("_2jets40_chi5_mudist105_drjet03_ctausup_shift2_smear4_140109/TTbar173.root");
  inputfilename.push_back("_2jets40_chi5_mudist105_drjet03_ctausup_shift3_smear6_140109/TTbar173.root");
  inputfilename.push_back("_2jets40_chi5_mudist105_drjet03_ctausup_shift4_smear8_140109/TTbar173.root");
  inputfilename.push_back("_2jets40_chi5_mudist105_drjet03_ctausup_shift5_smear10_140109/TTbar173.root");
  vector<TString> leg_shift_s; vector<double> x_shift;
  x_shift.push_back(0);
  leg_shift_s.push_back("0.5 GeV/c"); x_shift.push_back(0.5);
  leg_shift_s.push_back("1 GeV/c"); x_shift.push_back(1);
  leg_shift_s.push_back("2 GeV/c"); x_shift.push_back(2);
  leg_shift_s.push_back("3 GeV/c"); x_shift.push_back(3);
  leg_shift_s.push_back("4 GeV/c"); x_shift.push_back(4);
  leg_shift_s.push_back("5 GeV/c"); x_shift.push_back(5);
  vector<TString> leg_smear_s; vector<double> x_smear;
  x_smear.push_back(0);
  leg_smear_s.push_back("1 GeV/c"); x_smear.push_back(1);
  leg_smear_s.push_back("2 GeV/c"); x_smear.push_back(2);
  leg_smear_s.push_back("4 GeV/c"); x_smear.push_back(4);
  leg_smear_s.push_back("6 GeV/c"); x_smear.push_back(6);
  leg_smear_s.push_back("8 GeV/c"); x_smear.push_back(8);
  leg_smear_s.push_back("10 GeV/c"); x_smear.push_back(10);
  vector<TString> leg_both_s;
  leg_both_s.push_back("#splitline{p_{T}(J/#psi) shifted of 0.5 GeV/c,}{smeared by 1 GeV/c}");
  leg_both_s.push_back("#splitline{p_{T}(J/#psi) shifted of 1 GeV/c,}{smeared by 2 GeV/c}");
  leg_both_s.push_back("#splitline{p_{T}(J/#psi) shifted of 2 GeV/c,}{smeared by 4 GeV/c}");
  leg_both_s.push_back("#splitline{p_{T}(J/#psi) shifted of 3 GeV/c,}{smeared by 6 GeV/c}");
  leg_both_s.push_back("#splitline{p_{T}(J/#psi) shifted of 4 GeV/c,}{smeared by 8 GeV/c}");
  leg_both_s.push_back("#splitline{p_{T}(J/#psi) shifted of 5 GeV/c,}{smeared by 10 GeV/c}");

  TString outname = "_";

  double xxmin = 30.;
  double xxmax = 110.;

  if ( channel.Contains("mu") || channel.Contains("Mu") ) {
    channel = "Muons channel";
    //outname = outname + "Mu_Py6l_";
    outname = outname + "Mu_PY6l_";
    for (unsigned int i = 0; i < inputfilename.size(); i++) {
      inputfilename[i] = "Plots_Mu" + inputfilename[i]; 
    }
  }
  else if ( channel.Contains("el") || channel.Contains("El") ) {
    channel = "Electrons channel";
    //outname = outname + "El_Py6l_";
    outname = outname + "El_PY6l_";
    for (unsigned int i = 0; i < inputfilename.size(); i++) {
      inputfilename[i] = "Plots_El" + inputfilename[i]; 
    }
  }

  TCanvas *cn_shift = new TCanvas("cn_shift", "cn_shift",700,500);
  TCanvas *cn_smear = new TCanvas("cn_smear", "cn_smear",700,500);
  TCanvas *cn_both  = new TCanvas("cn_both", "cn_both",700,500);

  TCanvas *cn_smear2 = new TCanvas("cn_smear2", "cn_smear2",700,500);
  TLegend *leg_smear2 = new TLegend(0.7,0.5,0.9,0.9,NULL,"brNDC");
  leg_smear2->SetHeader("p_{T}(J/#psi) smeared by");

  TLegend *leg_shift = new TLegend(0.7,0.5,0.9,0.9,NULL,"brNDC");
  leg_shift->SetHeader("p_{T}(J/#psi) shifted of");
  TLegend *leg_smear = new TLegend(0.7,0.5,0.9,0.9,NULL,"brNDC");
  leg_smear->SetHeader("p_{T}(J/#psi) smeared by");
  TLegend *leg_both = new TLegend(0.54,0.24,0.9,0.9,NULL,"brNDC");

  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);

  vector<double> y_shift;
  vector<double> ey_shift;
  vector<double> y_smear;
  vector<double> ey_smear;

  for (unsigned int i = 0; i < inputfilename.size(); i++) {
    TFile *inputfile = TFile::Open(inputfilename[i]);
    //cout << "File " << inputfilename[i] << " loaded" << endl;
    if (i == 0) {
      TH1F *nothing = inputfile->Get("TOP_M_RECO_ALL");
      nothing->Rebin(rebin);
      Float_t inter = nothing->GetXaxis()->GetXmax() - nothing->GetXaxis()->GetXmin();
      Float_t num   = (inter/(Float_t)nothing->GetXaxis()->GetNbins());
      TString ytitle;
      if (1000.*num<1.) ytitle = TString::Format("Events / (%0.4f GeV/c^{2})", num);
      else {
        if (100.*num<1.) ytitle = TString::Format("Events / (%0.3f GeV/c^{2})", num);
        else {
          if (10.*num<1.) ytitle = TString::Format("Events / (%0.2f GeV/c^{2})", num);
          else {
            if (num<1.) ytitle = TString::Format("Events / (%0.1f GeV/c^{2})", num);
            else ytitle = TString::Format("Events / (%1.0f GeV/c^{2})", num);
          } 
        } 
      }
      TTree *tree_nothing = (TTree*) inputfile->Get("M_RECO_ALL");
      double *mean_err_nothing = step(xxmin,xxmax,"mass","weight",tree_nothing,control); 
      y_shift.push_back(mean_err_nothing[0]); 
      ey_shift.push_back(mean_err_nothing[1]);
      y_smear.push_back(mean_err_nothing[0]); 
      ey_smear.push_back(mean_err_nothing[1]);
      /*
         y_shift.push_back(nothing->GetMaximumBin()*num); 
         ey_shift.push_back(num/2.);
         y_smear.push_back(nothing->GetMaximumBin()*num); 
         ey_smear.push_back(num/2.);
         */
      h1_style(nothing,2,1,1,1,0,-1111.,nothing->GetMaximum()*1.2,510,510,1,1,1,0,"Pythia6 leptonic t#bar{t} events","M_{J/#psi+l} (GeV/c^{2})",ytitle); 
      cn_shift->cd();
      nothing->Draw("hist");
      leg_shift->AddEntry(nothing,"0 GeV/c","l");
      cn_smear->cd();
      nothing->Draw("hist");
      leg_smear->AddEntry(nothing,"0 GeV/c","l");
      cn_both->cd();
      nothing->Draw("hist");
      leg_both->AddEntry(nothing,"not shifted, not smeared","l");

      TH1F *nothing2 = inputfile->Get("JPSI_PT");
      nothing2->Rebin(4);
      h1_style(nothing2,2,1,1,1,0,-1111.,nothing2->GetMaximum()*1.2,510,510,1,1,1,0,"Pythia6 leptonic t#bar{t} events","p_{T}(J/#psi+l) (GeV/c)",""); 
      cn_smear2->cd();
      nothing2->Draw("hist");
      leg_smear2->AddEntry(nothing2,"0 GeV/c","l");
    }

    TH1F *shift = inputfile->Get("TOP_M_RECO_ALL_SHIFT");
    shift->Rebin(rebin);
    shift->Scale(nothing->Integral()/shift->Integral());
    TTree *tree_shift = (TTree*) inputfile->Get("M_RECO_ALL_SHIFT");
    double *mean_err_shift = step(xxmin,xxmax,"mass_shift","weight_shift",tree_shift,control); 
    y_shift.push_back(mean_err_shift[0]); 
    ey_shift.push_back(mean_err_shift[1]);
    /*
       y_shift.push_back(shift->GetMaximumBin()*num); 
       ey_shift.push_back(num/2.);
       */
    h1_style(shift,2,30+3*i,1,30+3*i,0,-1111.,-1111.,510,510,1,30+3*i,1,0,"","",ytitle); 
    cn_shift->cd();
    leg_shift->AddEntry(shift,leg_shift_s[i],"l");
    shift->Draw("histsame");

    TH1F *smear = inputfile->Get("TOP_M_RECO_ALL_SMEAR");
    smear->Rebin(rebin);
    smear->Scale(nothing->Integral()/smear->Integral());
    TTree *tree_smear = (TTree*) inputfile->Get("M_RECO_ALL_SMEAR");
    double *mean_err_smear = step(xxmin,xxmax,"mass_smear","weight_smear",tree_smear,control); 
    y_smear.push_back(mean_err_smear[0]); 
    ey_smear.push_back(mean_err_smear[1]);
    /*
       y_smear.push_back(smear->GetMaximumBin()*num); 
       ey_smear.push_back(num/2.);
       */
    h1_style(smear,2,30+3*i,1,30+3*i,0,-1111.,-1111.,510,510,1,30+3*i,1,0,"","",ytitle); 
    cn_smear->cd();
    leg_smear->AddEntry(smear,leg_smear_s[i],"l");
    smear->Draw("histsame");

    TH1F *smear2 = inputfile->Get("JPSI_PT_SMEAR");
    smear2->Rebin(4);
    h1_style(smear2,2,30+3*i,1,30+3*i,0,-1111.,-1111.,510,510,1,30+3*i,1,0,"","",""); 
    cn_smear2->cd();
    leg_smear2->AddEntry(smear2,leg_smear_s[i],"l");
    smear2->Draw("histsame");

    TH1F *both  = inputfile->Get("TOP_M_RECO_ALL_BOTH");
    both->Rebin(rebin);
    both->Scale(nothing->Integral()/both->Integral());
    h1_style(both,2,30+3*i,1,30+3*i,0,-1111.,-1111.,510,510,1,30+3*i,1,0,"","",ytitle); 
    cn_both->cd();
    leg_both->AddEntry(both,leg_both_s[i],"l");
    both->Draw("histsame");
  }
  cn_shift->cd(); leg_style(leg_shift); leg_shift->Draw(); latex->DrawLatex(10,0.9*nothing->GetMaximum(),channel); 
  cn_smear->cd(); leg_style(leg_smear); leg_smear->Draw(); latex->DrawLatex(10,0.9*nothing->GetMaximum(),channel);
  cn_both->cd(); leg_style(leg_both); leg_both->Draw(); latex->DrawLatex(10,0.9*nothing->GetMaximum(),channel);

  cn_smear2->cd(); leg_style(leg_smear2); leg_smear2->Draw(); latex->DrawLatex(10,0.9*nothing2->GetMaximum(),channel);

  TCanvas *cn_shift_gr = new TCanvas("cn_shift_gr", "cn_shift_gr",700,500);
  TCanvas *cn_smear_gr = new TCanvas("cn_smear_gr", "cn_smear_gr",700,500);
  const unsigned int numberOfPoints = inputfilename.size() + 1;
  double tab_x_shift[numberOfPoints]; double tab_ex_shift[numberOfPoints];
  double tab_x_smear[numberOfPoints]; double tab_ex_smear[numberOfPoints];
  double tab_y_shift[numberOfPoints]; double tab_ey_shift[numberOfPoints];
  double tab_y_smear[numberOfPoints]; double tab_ey_smear[numberOfPoints];
  for (unsigned int i = 0; i < numberOfPoints; i++) {
    tab_x_shift[i] = x_shift[i]; tab_ex_shift[i] = 0.;
    tab_x_smear[i] = x_smear[i]; tab_ex_smear[i] = 0.;
    tab_y_shift[i] = y_shift[i]; tab_ey_shift[i] = ey_shift[i];
    tab_y_smear[i] = y_smear[i]; tab_ey_smear[i] = ey_smear[i];
  }
  TGraphErrors *gr_shift = new TGraphErrors(numberOfPoints,tab_x_shift,tab_y_shift,tab_ex_shift,tab_ey_shift);
  TGraphErrors *gr_smear = new TGraphErrors(numberOfPoints,tab_x_smear,tab_y_smear,tab_ex_smear,tab_ey_smear);
  cn_shift_gr->cd();
  //grapherror_style(gr_shift,"gr_shift",2,30,1,30,1001,70,80,510,510,21,36,1.,"Pythia6 leptonic t#bar{t} events","shift of p_{T}(J/#psi) (GeV/c)","#tilde{M}_{J/#psi+l} (GeV/c^{2})");
  grapherror_style(gr_shift,"gr_shift",2,30,1,30,1001,65,80,510,510,21,36,1.,"Pythia6 leptonic t#bar{t} events","shift of p_{T}(J/#psi) (GeV/c)","#tilde{M}_{J/#psi+l} (GeV/c^{2})");
  //grapherror_style(gr_shift,"gr_shift",2,30,1,30,1001,70,80,510,510,21,36,1.,"Pythia6 leptonic t#bar{t} events","shift of p_{T}(J/#psi) (GeV/c)","M_{J/#psi+l} maxmimum (GeV/c^{2})");
  TFitResultPtr fitptr_shift = gr_shift->Fit("pol1","FS","");
  TF1* fit_shift = gr_shift->GetFunction("pol1");
  Double_t slope_shift = fitptr_shift->Parameter(1);
  Double_t oal_shift = fitptr_shift->Parameter(0);
  TString text_shift = TString::Format("#tilde{M}_{J/#psi+l} = %0.1f + %0.1f p_{T}(J/#psi)", oal_shift, slope_shift);
  fit_shift->SetLineColor(30); fit_shift->SetLineWidth(2);
  gr_shift->Draw("AP");
 
  cn_smear_gr->cd();
  //grapherror_style(gr_smear,"gr_smear",2,30,1,30,1001,70,76,510,510,21,36,1.,"Pythia6 leptonic t#bar{t} events","smear of p_{T}(J/#psi) (GeV/c)","#tilde{M}_{J/#psi+l} maximum (GeV/c^{2})");
  grapherror_style(gr_smear,"gr_smear",2,30,1,30,1001,67,73,510,510,21,36,1.,"Pythia6 leptonic t#bar{t} events","smear of p_{T}(J/#psi) (GeV/c)","#tilde{M}_{J/#psi+l} maximum (GeV/c^{2})");
  //grapherror_style(gr_smear,"gr_smear",2,30,1,30,1001,70,76,510,510,21,36,1.,"Pythia6 leptonic t#bar{t} events","smear of p_{T}(J/#psi) (GeV/c)","M_{J/#psi+l} maximum (GeV/c^{2})");
  TFitResultPtr fitptr_smear = gr_smear->Fit("pol1","FS","");
  TF1* fit_smear = gr_smear->GetFunction("pol1");
  Double_t slope_smear = fitptr_smear->Parameter(1);
  Double_t oal_smear = fitptr_smear->Parameter(0);
  TString text_smear = TString::Format("#tilde{M}_{J/#psi+l} = %0.1f + %0.2f p_{T}(J/#psi)", oal_smear, slope_smear);
  fit_smear->SetLineColor(30); fit_smear->SetLineWidth(2);
  gr_smear->Draw("AP");
  
  cn_shift_gr->cd(); latex->DrawLatex(0.25,78,channel); latex->DrawLatex(2.5,69,text_shift); 
  cn_smear_gr->cd(); latex->DrawLatex(0.5,72,channel); latex->DrawLatex(5,68,text_smear);
  //cn_shift_gr->cd(); latex->DrawLatex(0.25,78,channel); latex->DrawLatex(2.5,72,text_shift); 
  //cn_smear_gr->cd(); latex->DrawLatex(0.5,75,channel); latex->DrawLatex(5,71,text_smear);

  if (rebin == 2) outname = outname + "rebin2_" + date;
  if (rebin == 5) outname = outname + "rebin5_" + date;
  if (rebin == 10) outname = outname + "rebin10_" + date;
  if (rebin == 17) outname = outname + "rebin17_" + date;

  if (tosave) {
    cn_shift->Print("Plots/Shift"+outname+".eps");
    cn_shift->Print("Plots/Shift"+outname+".jpg");
    cn_shift->Print("Plots/Shift"+outname+".pdf");
    cn_shift->Print("Plots/Shift"+outname+".C");
    cn_smear->Print("Plots/Smear"+outname+".eps");
    cn_smear->Print("Plots/Smear"+outname+".jpg");
    cn_smear->Print("Plots/Smear"+outname+".pdf");
    cn_smear->Print("Plots/Smear"+outname+".C");
    cn_both->Print("Plots/Both"+outname+".eps");
    cn_both->Print("Plots/Both"+outname+".jpg");
    cn_both->Print("Plots/Both"+outname+".pdf");
    cn_both->Print("Plots/Both"+outname+".C");
    cn_shift_gr->Print("Plots/Gr_Shift"+outname+".eps");
    cn_shift_gr->Print("Plots/Gr_Shift"+outname+".jpg");
    cn_shift_gr->Print("Plots/Gr_Shift"+outname+".pdf");
    cn_shift_gr->Print("Plots/Gr_Shift"+outname+".C");
    cn_smear_gr->Print("Plots/Gr_Smear"+outname+".eps");
    cn_smear_gr->Print("Plots/Gr_Smear"+outname+".jpg");
    cn_smear_gr->Print("Plots/Gr_Smear"+outname+".pdf");
    cn_smear_gr->Print("Plots/Gr_Smear"+outname+".C");
  }
}
