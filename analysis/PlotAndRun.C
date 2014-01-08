void PlotAndRun(TString channel, bool print = true) {  

  if (print) gROOT->SetBatch(true); //Speeds things up by not displaying plots in canvas
  gROOT->ProcessLine(".L ../PlotIt/PlotIt_cc.so");

  if ( channel.Contains("mu") || channel.Contains("Mu") ) 
    PlotIt toto("../PlotIt/input_mu.list",19771,1.);
  if ( channel.Contains("el") || channel.Contains("El") ) 
    PlotIt toto("../PlotIt/input_el.list",19767,1.);

  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);

  toto.plotstack("X_E_JPSI_BHAD",1,1,"E_{J/#psi}/E_{B-hadron}","right");
  c1->Modified();
  latex->DrawLatex(toto._hmc->GetXaxis()->GetXmin(),1.04*toto._hmc->GetMaximum(),header); 
  latex2->DrawLatex(0.1,0.9*toto._hmc->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/X_E_JPSI_BHAD_GEN.pdf");
    c1->Print("Plots/X_E_JPSI_BHAD_GEN.eps");
    c1->Print("Plots/X_E_JPSI_BHAD_GEN.jpg");
    c1->Print("Plots/X_E_JPSI_BHAD_GEN.C");
  }

  toto.plotstack("X_E_JPSI_BQUARK",1,1,"E_{J/#psi}/E_{b-quark}","right");
  c1->Modified();
  latex->DrawLatex(toto._hmc->GetXaxis()->GetXmin(),1.04*toto._hmc->GetMaximum(),header); 
  latex2->DrawLatex(0.1,0.9*toto._hmc->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/X_E_JPSI_BQUARK_GEN.pdf");
    c1->Print("Plots/X_E_JPSI_BQUARK_GEN.eps");
    c1->Print("Plots/X_E_JPSI_BQUARK_GEN.jpg");
    c1->Print("Plots/X_E_JPSI_BQUARK_GEN.C");
  }

  toto.plotstack("X_E_BHAD_BQUARK",1,1,"E_{B-hadron}/E_{b-quark}","right");
  c1->Modified();
  latex->DrawLatex(toto._hmc->GetXaxis()->GetXmin(),1.04*toto._hmc->GetMaximum(),header); 
  latex2->DrawLatex(0.1,0.9*toto._hmc->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/X_E_BHAD_BQUARK_GEN.pdf");
    c1->Print("Plots/X_E_BHAD_BQUARK_GEN.eps");
    c1->Print("Plots/X_E_BHAD_BQUARK_GEN.jpg");
    c1->Print("Plots/X_E_BHAD_BQUARK_GEN.C");
  }

  toto.plotstack("X_PT_JPSI_BHAD",1,1,"p_{T,J/#psi}/p_{T,B-hadron}","right");
  c1->Modified();
  latex->DrawLatex(toto._hmc->GetXaxis()->GetXmin(),1.04*toto._hmc->GetMaximum(),header); 
  latex2->DrawLatex(0.1,0.9*toto._hmc->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/X_PT_JPSI_BHAD_GEN.pdf");
    c1->Print("Plots/X_PT_JPSI_BHAD_GEN.eps");
    c1->Print("Plots/X_PT_JPSI_BHAD_GEN.jpg");
    c1->Print("Plots/X_PT_JPSI_BHAD_GEN.C");
  }

  toto.plotstack("X_PT_JPSI_BQUARK",1,1,"p_{T,J/#psi}/p_{T,b-quark}","right");
  c1->Modified();
  latex->DrawLatex(toto._hmc->GetXaxis()->GetXmin(),1.04*toto._hmc->GetMaximum(),header); 
  latex2->DrawLatex(0.1,0.9*toto._hmc->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/X_PT_JPSI_BQUARK_GEN.pdf");
    c1->Print("Plots/X_PT_JPSI_BQUARK_GEN.eps");
    c1->Print("Plots/X_PT_JPSI_BQUARK_GEN.jpg");
    c1->Print("Plots/X_PT_JPSI_BQUARK_GEN.C");
  }

  toto.plotstack("X_PT_BHAD_BQUARK",1,1,"p_{T,B-hadron}/p_{T,b-quark}","right");
  c1->Modified();
  latex->DrawLatex(toto._hmc->GetXaxis()->GetXmin(),1.04*toto._hmc->GetMaximum(),header); 
  latex2->DrawLatex(0.1,0.9*toto._hmc->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/X_PT_BHAD_BQUARK_GEN.pdf");
    c1->Print("Plots/X_PT_BHAD_BQUARK_GEN.eps");
    c1->Print("Plots/X_PT_BHAD_BQUARK_GEN.jpg");
    c1->Print("Plots/X_PT_BHAD_BQUARK_GEN.C");
  }

  toto.plotstack("BHAD_ID",1,1,"pdgId(B-hadron)","right");
  c1->Modified();
  latex->DrawLatex(toto._hmc->GetXaxis()->GetXmin(),1.04*toto._hmc->GetMaximum(),header); 
  latex2->DrawLatex(-5000,0.9*toto._hmc->GetMaximum(),textchannel); 
  c1->Modified();
  int offset = 5601;
  int sign[2] = {-1,1};
  //toto._hmc->GetXaxis()->SetBinLabel(offset,"0");
  for (unsigned int i=0; i<2; i++) {
    // charmed mesons
    if (toto._hmc->GetBinContent(offset+sign[i]*411) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*411,"D^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*421) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*421,"D^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10411) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10411,"D_{0}*(2400)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10421) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10421,"D_{0}*(2400)^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*413) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*413,"D*(2010)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*423) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*423,"D*(2007)^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10413) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10413,"D_{1}(2420)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10423) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10423,"D_{1}(2420)^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*20413) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20413,"D_{1}(H)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*20423) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20423,"D_{1}(2430)^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*415) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*415,"D_{2}*(2460)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*425) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*425,"D_{2}*(2460)^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*431) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*431,"D_{s}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10431) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10431,"D_{s0}*(2317)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*433) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*433,"D_{s}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10433) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10433,"D_{s1}(2536)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*20433) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20433,"D_{s1}(2460)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*435) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*435,"D_{s2}*(2573)^{+}");
    // bottom mesons
    if (toto._hmc->GetBinContent(offset+sign[i]*511) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*511,"B^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*521) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*521,"B^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10511) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10511,"B_{0}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10521) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10521,"B_{0}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*513) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*513,"B*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*523) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*523,"B*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10513) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10513,"B_{1}(L)^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10523) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10523,"B_{1}(L)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*20513) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20513,"B_{1}(H)^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*20523) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20523,"B_{1}(H)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*515) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*515,"B_{2}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*525) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*525,"B_{2}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*531) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*531,"B_{s}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10531) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10531,"B_{s0}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*533) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*533,"B_{s}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10533) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10533,"B_{s1}(L)^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*20533) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20533,"B_{s1}(H)^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*535) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*535,"B_{s2}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*541) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*541,"B_{c}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10541) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10541,"B_{c0}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*543) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*543,"B_{c}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*10543) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10543,"B_{c1}(L)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*20543) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20543,"B_{c1}(H)^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*545) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*545,"B_{c2}*^{+}");
    // ccbar mesons
    if (toto._hmc->GetBinContent(offset+sign[i]*441) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*441,"#eta_{c}(1S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*10441) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10441,"#chi_{c0}(1P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*100441) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*100441,"#eta_{c}(2S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*443,"J/#psi(1S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*10443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10443,"h_{c}(1P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*20443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20443,"#chi_{c1}(1P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*100443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*100443,"#psi(2S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*sign[i]*30443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*30443,"#psi(3770)");
    if (toto._hmc->GetBinContent(offset+sign[i]*9000443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*9000443,"#psi(4040)");
    if (toto._hmc->GetBinContent(offset+sign[i]*9010443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*9010443,"#psi(4160)");
    if (toto._hmc->GetBinContent(offset+sign[i]*9020443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*9020443,"#psi(4415)");
    if (toto._hmc->GetBinContent(offset+sign[i]*445) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*445,"#chi_{c2}(1P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*100445) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*100445,"#chi_{c2}(2P)");
    // bbbar mesons
    if (toto._hmc->GetBinContent(offset+sign[i]*551) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*551,"#eta_{b}(1S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*10551) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10551,"#chi_{b0}(1P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*100551) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*100551,"#eta_{b}(2S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*110551) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*110551,"#chi_{b0}(2P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*200551) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*200551,"#eta_{b}(3S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*210551) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*210551,"#chi_{b0}(3P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*553,"#upsilon(1S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*10553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10553,"h_{b}(1P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*20553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20553,"#chi_{b1}(1P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*30553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*30553,"#upsilon_{1}(1D)");
    if (toto._hmc->GetBinContent(offset+sign[i]*100553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*100553,"#upsilon(2S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*110553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*110553,"h_{b}(2P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*120553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*120553,"#chi_{b1}(2P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*130553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*130553,"#upsilon_{1}(2D)");
    if (toto._hmc->GetBinContent(offset+sign[i]*200553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*200553,"#upsilon(3S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*210553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*210553,"h_{b}(3P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*220553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*220553,"#chi_{b1}(3P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*300553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*30553,"#upsilon(4S)");
    if (toto._hmc->GetBinContent(offset+sign[i]*9000553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*9000553,"#upsilon(10860)");
    if (toto._hmc->GetBinContent(offset+sign[i]*9010553) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*9010553,"#upsilon(11020)");
    if (toto._hmc->GetBinContent(offset+sign[i]*555) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*555,"#chi_{b2}(1P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*10555) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*10555,"#eta_{b2}(1D)");
    if (toto._hmc->GetBinContent(offset+sign[i]*20555) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*20555,"#upsilon_{2}(1D)");
    if (toto._hmc->GetBinContent(offset+sign[i]*100555) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*100555,"#chi_{b2}(2P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*110555) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*110555,"#eta_{b2}(2D)");
    if (toto._hmc->GetBinContent(offset+sign[i]*120555) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*120555,"#upsilon_{2}(2D)");
    if (toto._hmc->GetBinContent(offset+sign[i]*200555) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*200555,"#chi_{b2}(3P)");
    if (toto._hmc->GetBinContent(offset+sign[i]*557) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*557,"#upsilon_{3}(1D)");
    if (toto._hmc->GetBinContent(offset+sign[i]*100557) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*100557,"#upsilon_{3}(2D)");
    // charmed baryons
    if (toto._hmc->GetBinContent(offset+sign[i]*4122) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4122,"#Lambda_{c}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4222) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4222,"#Sigma_{c}^{++}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4212) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4212,"#Sigma_{c}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4112) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4112,"#Sigma_{c}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4224) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4224,"#Sigma_{c}*^{++}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4214) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4214,"#Sigma_{c}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4114) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4114,"#Sigma_{c}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4232) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4232,"#Xi_{c}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4132) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4132,"#Xi_{c}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4322) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4322,"#Xi_{c}'^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4312) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4312,"#Xi_{c}'^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4324) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4324,"#Xi_{c}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4314) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4314,"#Xi_{c}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4332) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4332,"#Omega_{c}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4334) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4334,"#Omega_{c}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4412) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4412,"#Xi_{cc}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4422) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4422,"#Xi_{cc}^{++}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4414) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4414,"#Xi_{cc}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4424) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4424,"#Xi_{cc}*^{++}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4432) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4432,"#Omega_{cc}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4434) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4434,"#Omega_{cc}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*4444) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*4444,"#Omega_{ccc}^{++}");
    // bottom baryons
    if (toto._hmc->GetBinContent(offset+sign[i]*5122) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5122,"#Lambda_{b}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5112) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5112,"#Sigma_{b}^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5212) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5212,"#Sigma_{b}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5222) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5222,"#Sigma_{b}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5114) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5114,"#Sigma_{b}*^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5214) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5214,"#Sigma_{b}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5224) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5224,"#Sigma_{b}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5132) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5132,"#Xi_{b}^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5232) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5232,"#Xi_{b}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5312) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5312,"#Xi_{b}'^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5322) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5322,"#Xi_{b}'^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5314) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5314,"#Xi_{b}*^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5324) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5324,"#Xi_{b}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5332) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5332,"#Omega_{b}^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5334) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5334,"#Omega_{b}*^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5142) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5142,"#Xi_{bc}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5242) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5242,"#Xi_{bc}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5412) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5412,"#Xi_{bc}'^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5422) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5422,"#Xi_{bc}'^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5414) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5414,"#Xi_{bc}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5424) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5424,"#Xi_{bc}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5342) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5342,"#Omega_{bc}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5432) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5432,"#Omega_{bc}'^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5434) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5434,"#Omega_{bc}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5442) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5442,"#Omega_{bcc}^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5444) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5444,"#Omega_{bcc}*^{+}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5512) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5512,"#Xi_{bb}^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5522) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5522,"#Xi_{bb}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5514) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5514,"#Xi_{bb}*^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5524) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5524,"#Xi_{bb}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5532) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5532,"#Omega_{bb}^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5534) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5534,"#Omega_{bb}*^{-}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5542) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5542,"#Omega_{bbc}^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5544) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5544,"#Omega_{bbc}*^{0}");
    if (toto._hmc->GetBinContent(offset+sign[i]*5554) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+sign[i]*5554,"#Omega_{bbb}^{-}");
  }
  c1->Modified();
  if (print) {
    c1->Print("Plots/BHAD_ID_GEN.pdf");
    c1->Print("Plots/BHAD_ID_GEN.eps");
    c1->Print("Plots/BHAD_ID_GEN.jpg");
    c1->Print("Plots/BHAD_ID_GEN.C");
  }

  toto.plotstack("DR_BHAD_BQUARK",1,1,"#DeltaR(B-hadron,b-quark)","right");
  toto._hmc->GetXaxis()->SetRangeUser(0,0.099);
  c1->Modified();
  latex->DrawLatex(toto._hmc->GetXaxis()->GetXmin(),1.04*toto._hmc->GetMaximum(),header); 
  latex2->DrawLatex(0.005,0.9*toto._hmc->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/DR_BHAD_BQUARK.pdf");
    c1->Print("Plots/DR_BHAD_BQUARK.eps");
    c1->Print("Plots/DR_BHAD_BQUARK.jpg");
    c1->Print("Plots/DR_BHAD_BQUARK.C");
  }

  toto.plotstack("DR_BHAD_BQUARK_1",1,1,"#DeltaR(B-hadron,b-quark)","right");
  toto._hmc->GetXaxis()->SetRangeUser(0,0.099);
  c1->Modified();
  latex->DrawLatex(toto._hmc->GetXaxis()->GetXmin(),1.04*toto._hmc->GetMaximum(),header); 
  latex2->DrawLatex(0.005,0.9*toto._hmc->GetMaximum(),textchannel); 
  TString nb = "Events with #frac{E_{T,B-hadron}}{E_{T,b-quark}} > 1";
  TLatex *latex3 = new TLatex();
  latex3->SetTextSize(0.04);
  latex3->SetTextFont(62);
  latex3->SetTextAlign(12);
  latex3->SetTextColor(1);
  latex3->DrawLatex(0.05,0.4*toto._hmc->GetMaximum(),nb); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/DR_BHAD_BQUARK_1.pdf");
    c1->Print("Plots/DR_BHAD_BQUARK_1.eps");
    c1->Print("Plots/DR_BHAD_BQUARK_1.jpg");
    c1->Print("Plots/DR_BHAD_BQUARK_1.C");
  }


}
