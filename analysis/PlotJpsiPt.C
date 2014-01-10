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

int PlotJpsiPt(TString channel, TString date="140109", bool tosave=false) {

  vector<TString> inputfilename; 
  inputfilename.push_back("_2jets40_chi5_mudist105_drjet03_ctausup_shift2_smear4_140109/TTbar173.root");
  inputfilename.push_back("_2jets40_chi5_mudist105_drjet03_ctausup_shift4_smear8_140109/TTbar173.root");
  
  TString outname = "JpsiPt_";

  if ( channel.Contains("mu") || channel.Contains("Mu") ) {
    channel = "Muons channel";
    outname = outname + "Mu_PY6l_rebin4_" + date;
    for (unsigned int i = 0; i < inputfilename.size(); i++) {
      inputfilename[i] = "Plots_Mu" + inputfilename[i]; 
    }
  }
  else if ( channel.Contains("el") || channel.Contains("El") ) {
    channel = "Electrons channel";
    outname = outname + "El_PY6l_rebin4_" + date;
    for (unsigned int i = 0; i < inputfilename.size(); i++) {
      inputfilename[i] = "Plots_El" + inputfilename[i]; 
    }
  }

  TCanvas *cn = new TCanvas("cn", "cn",700,500);
  TString leg_header;
  TLegend *leg = new TLegend(0.5,0.65,0.9,0.9,NULL,"brNDC");
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);

  TFile *fishift = TFile::Open(inputfilename[1]);
  TFile *fismear = TFile::Open(inputfilename[0]);
  TH1F *nothing = (TH1F*) fishift->Get("JPSI_PT"); 
  TH1F *shift = (TH1F*) fishift->Get("JPSI_PT_SHIFT"); 
  TH1F *smear = (TH1F*) fismear->Get("JPSI_PT_SMEAR"); 
  nothing->Rebin(4);
  shift->Rebin(4);
  smear->Rebin(4);
  Float_t inter = nothing->GetXaxis()->GetXmax() - nothing->GetXaxis()->GetXmin();
  Float_t num   = (inter/(Float_t)nothing->GetXaxis()->GetNbins());
  TString ytitle;
  if (1000.*num<1.) ytitle = TString::Format("Events / (%0.4f GeV/c)", num);
  else {
    if (100.*num<1.) ytitle = TString::Format("Events / (%0.3f GeV/c)", num);
    else {
      if (10.*num<1.) ytitle = TString::Format("Events / (%0.2f GeV/c)", num);
      else {
        if (num<1.) ytitle = TString::Format("Events / (%0.1f GeV/c)", num);
        else ytitle = TString::Format("Events / (%1.0f GeV/c)", num);
      } 
    } 
  }
  h1_style(nothing,2,30,1,30,0,-1111.,nothing->GetMaximum()*1.2,510,510,1,30,1,0,"Pythia6 leptonic t#bar{t} events","p_{T}(J/#psi) (GeV/c)",ytitle); 
  h1_style(shift,2,38,1,38,0,-1111.,-1111.,510,510,1,38,1,0,"","",ytitle); 
  h1_style(smear,2,46,1,46,0,-1111.,-1111.,510,510,1,46,1,0,"","",ytitle); 
  cn->cd(); 
  nothing->Draw("hist");
  shift->Draw("histsame");
  smear->Draw("histsame");
  leg->AddEntry(nothing,"Pythia6 leptonic t#bar{t} events","l"); 
  leg->AddEntry(shift,"p_{T}(J/#psi) shifted of 4 GeV/c","l");
  leg->AddEntry(smear,"p_{T}(J/#psi) smeared by 4 GeV/c","l");
  leg_style(leg);
  leg->Draw();
  latex->DrawLatex(120,200,channel);
  nothing->GetXaxis()->SetRangeUser(0,200);
  cn->Modified();
  gPad->Update();

  if (tosave==true) {
    cn->Print("Plots/"+outname+".eps");
    cn->Print("Plots/"+outname+".jpg");
    cn->Print("Plots/"+outname+".pdf");
    cn->Print("Plots/"+outname+".C");
  }
}
