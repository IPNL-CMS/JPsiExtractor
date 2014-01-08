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

void graphasymerror_style(TGraphAsymmErrors *gr,
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

double *step(string name,double inf,double sup) {

  TFile *res = TFile::Open(name.c_str());

  //---- Variables
  RooRealVar mtl("mass_gen_bhadl", "M_{B+l}^{gen}", 0., 250., "GeV/c^{2}");
  RooRealVar weight("weight_gen_hadl", "weight", 0., 2.);


  //---- Fit for all
  TTree *M_GEN_BHADL = (TTree*)res->Get("M_GEN_BHADL");

  RooDataSet *dataset = new RooDataSet("dataset", "dataset for gen events", RooArgSet(mtl, weight), Import(*M_GEN_BHADL), WeightVar(weight));

  dataset->Print();

  RooRealVar mean("mean", "mass",90.,50.,130.) ;
  RooRealVar width("width", "width",25.,10.,40.) ;

  RooGaussian pdf("pdf","pdf",mtl,mean,width);

  pdf.fitTo(*dataset,Range(inf,sup));

  TCanvas *cn = new TCanvas("cn","all pairing (gen)",700,500);
  cn->cd();
  RooPlot* massframe = mtl.frame(Title("Mass of the combination of the gen B-hadron and the gen isolated lepton")) ;
  dataset->plotOn(massframe,Binning(50)) ;
  pdf.plotOn(massframe,Range(inf,sup)) ;
  massframe->Draw();

    
      TLatex *text = new TLatex();
      text->SetTextFont(62);
      text->SetTextColor(1);
      text->SetTextAlign(22);
      text->SetTextSize(0.05);
      TString tempo;
      cin >> tempo;
      TString text_text = "M_{t} = "+tempo+" GeV/c^{2}";
      text->DrawLatex(200,150,text_text); 
      
  gPad->Update();
  //getchar();
  TString namesave = "PlotsCalib/"+name;
  cn->SaveAs(namesave+".pdf");
  cn->SaveAs(namesave+".jpg");
  cn->SaveAs(namesave+".eps");
  cn->SaveAs(namesave+".C");

  //----------------------------- Fit parameters
  // cout << "Reco all         : " << mean.getVal() << " +/- "<< mean.getError() << endl;

  double *mean_err = new double[2];
  mean_err[0]=mean.getVal();
  mean_err[1]=mean.getError();

  return mean_err;
}


int calib_gen(TString channel) {

  gROOT->SetStyle("Plain");
  gSystem->Load("libRooFit");
  using namespace RooFit ;

  TString leg_header;
  TString calibname;

  if ( channel.Contains("mu") || channel.Contains("Mu") ) {
    channel = "Muons";
    leg_header = "Muons channel";
    calibname = "Calib_mu_gen";
  }

  if ( channel.Contains("el") || channel.Contains("El") ) {
    channel = "Electrons";
    leg_header = "Electrons channel";
    calibname = "Calib_el_gen";
  }

  double xxmin = 50.;
  double xxmax = 140.;

  //----- Fit des samples Pythia et courbe de calibration

  vector<TString> vecMassMC;
  vecMassMC.push_back("158"); vecMassMC.push_back("163"); vecMassMC.push_back("167");
  vecMassMC.push_back("169"); vecMassMC.push_back("170"); vecMassMC.push_back("171");
  vecMassMC.push_back("172"); vecMassMC.push_back("173"); vecMassMC.push_back("174");
  vecMassMC.push_back("175"); vecMassMC.push_back("176"); vecMassMC.push_back("177");
  vecMassMC.push_back("179"); vecMassMC.push_back("183"); vecMassMC.push_back("188");

  vector<double> vecMass;
  vecMass.push_back(158); vecMass.push_back(163); vecMass.push_back(167);
  vecMass.push_back(169); vecMass.push_back(170); vecMass.push_back(171);
  vecMass.push_back(172); vecMass.push_back(173); vecMass.push_back(174);
  vecMass.push_back(175); vecMass.push_back(176); vecMass.push_back(177);
  vecMass.push_back(179); vecMass.push_back(183); vecMass.push_back(188);

  if (vecMassMC.size()!=vecMass.size()) break;

  const unsigned int numberOfPoints = vecMass.size();
  double x[numberOfPoints]; double exl[numberOfPoints]; double exr[numberOfPoints];
  double y[numberOfPoints]; double ey[numberOfPoints];

  for (unsigned int ind=0; ind<numberOfPoints; ind++) { 
    string name_TTbar = "TTbar"+vecMassMC[ind]+".root";
    cout << "Open file " << name_TTbar << endl;
    double *mean_err_TTbar = step(name_TTbar,xxmin,xxmax);
    y[ind] = mean_err_TTbar[0];
    ey[ind] = mean_err_TTbar[1];
    x[ind] = vecMass[ind];
    exl[ind] = 0.;
    exr[ind] = 0.;
  }

  cout << "=============== " << channel <<" channel ================= \n" <<endl;

  for (unsigned int ind=0; ind<numberOfPoints; ind++){
    cout << "File TTbar"<< x[ind] << " : " << y[ind] << " +/- "<< ey[ind] << endl;
  }    

  TGraphAsymmErrors *gr = new TGraphAsymmErrors(numberOfPoints,x,y,exl,exr,ey,ey);
  TFitResultPtr fitptr = gr->Fit("pol1","FS","");
  TF1* fit = gr->GetFunction("pol1");
  Double_t slope = fitptr->Parameter(1);
  Double_t err = fitptr->ParError(1);
  TString leg_title = TString::Format("Calibration curve : slope of %0.2f #pm %0.2f",slope,err);
  cout << leg_title << endl;
  TString leg_title2 = TString::Format("ordonnee a l'origine of %0.2f #pm %0.2f",fitptr->Parameter(0),fitptr->ParError(0));
  cout << leg_title2 << endl;
  Double_t chi2 = fitptr->Chi2();
  Double_t ndf = fitptr->Ndf();
  cout << "Chi2/NDF = " << chi2/ndf << endl;

  Double_t err_up[numberOfPoints];
  Double_t err_down[numberOfPoints];
  Double_t errval[numberOfPoints];
  fitptr->GetConfidenceIntervals(numberOfPoints,1,1,x,errval,0.68);

  for(int i=0; i<numberOfPoints; ++i) {
    double error = errval[i];
    err_up[i] = fit->Eval(x[i])+error;
    err_down[i] = fit->Eval(x[i])-error;
  }

  TGraph *gr_up = new TGraph(numberOfPoints,x,err_up);
  gr_up->Fit("pol2","FQ","");
  TF1 *fit_up = gr_up->GetFunction("pol2");
  TGraph *gr_down = new TGraph(numberOfPoints,x,err_down);
  gr_down->Fit("pol2","FQ","");
  TF1 *fit_down = gr_down->GetFunction("pol2");  

  TLegend *leg_calib = new TLegend(0.14,0.75,0.67,0.88,NULL,"brNDC");
  leg_calib->AddEntry(gr,leg_title,"lp");
  leg_calib->SetHeader(leg_header);

  TCanvas *cn_calib = new TCanvas("cn_calib", "cn_calib",700,500);
  cn_calib->cd();
  graphasymerror_style(gr,"gr",2,30,1,30,1001,80,110,510,510,21,36,1.,"Calibration curve based on MC truth","M_{t} (GeV/c^{2})","M_{B+l}^{gen} (GeV/c^{2})");
  gr->Draw("AP");
  cn_calib->Update();
  fit->SetLineColor(30);
  fit_up->SetLineColor(29); fit_up->SetLineStyle(2); fit_up->SetLineWidth(2);
  fit_up->Draw("same");
  fit_down->SetLineColor(29); fit_down->SetLineStyle(2); fit_down->SetLineWidth(2);
  fit_down->Draw("same");
  leg_style(leg_calib);
  leg_calib->Draw();  

  cn_calib->SaveAs("PlotsCalib/"+calibname+".jpg");
  cn_calib->SaveAs("PlotsCalib/"+calibname+".eps");
  cn_calib->SaveAs("PlotsCalib/"+calibname+".C");
  cn_calib->SaveAs("PlotsCalib/"+calibname+".pdf");

  return 0;
}
