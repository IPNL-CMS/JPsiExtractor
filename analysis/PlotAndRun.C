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
  // charmed mesons
  if (toto._hmc->GetBinContent(offset+411) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+411,"D^{+}");
  if (toto._hmc->GetBinContent(offset+421) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+421,"D^{0}");
  if (toto._hmc->GetBinContent(offset+10411) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10411,"D_{0}*(2400)^{+}");
  if (toto._hmc->GetBinContent(offset+10421) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10421,"D_{0}*(2400)^{0}");
  if (toto._hmc->GetBinContent(offset+413) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+413,"D*(2010)^{+}");
  if (toto._hmc->GetBinContent(offset+423) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+423,"D*(2007)^{0}");
  if (toto._hmc->GetBinContent(offset+10413) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10413,"D_{1}(2420)^{+}");
  if (toto._hmc->GetBinContent(offset+10423) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10423,"D_{1}(2420)^{0}");
  if (toto._hmc->GetBinContent(offset+20413) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+20413,"D_{1}(H)^{+}");
  if (toto._hmc->GetBinContent(offset+20423) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+20423,"D_{1}(2430)^{0}");
  if (toto._hmc->GetBinContent(offset+415) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+415,"D_{2}*(2460)^{+}");
  if (toto._hmc->GetBinContent(offset+425) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+425,"D_{2}*(2460)^{0}");
  if (toto._hmc->GetBinContent(offset+431) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+431,"D_{s}^{+}");
  if (toto._hmc->GetBinContent(offset+10431) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10431,"D_{s0}*(2317)^{+}");
  if (toto._hmc->GetBinContent(offset+433) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+433,"D_{s}*^{+}");
  if (toto._hmc->GetBinContent(offset+10433) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10433,"D_{s1}(2536)^{+}");
  if (toto._hmc->GetBinContent(offset+20433) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+20433,"D_{s1}(2460)^{+}");
  if (toto._hmc->GetBinContent(offset+435) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+435,"D_{s2}*(2573)^{+}");
  // bottom mesons
  if (toto._hmc->GetBinContent(offset+511) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+511,"B^{0}");
  if (toto._hmc->GetBinContent(offset+521) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+521,"B^{+}");
  if (toto._hmc->GetBinContent(offset+10511) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10511,"B_{0}*^{0}");
  if (toto._hmc->GetBinContent(offset+10521) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10521,"B_{0}*^{+}");
  if (toto._hmc->GetBinContent(offset+513) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+513,"B*^{0}");
  if (toto._hmc->GetBinContent(offset+523) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+523,"B*^{+}");
  if (toto._hmc->GetBinContent(offset+10513) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10513,"B_{1}(L)^{0}");
  if (toto._hmc->GetBinContent(offset+10523) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10523,"B_{1}(L)^{+}");
  if (toto._hmc->GetBinContent(offset+20513) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+20513,"B_{1}(H)^{0}");
  if (toto._hmc->GetBinContent(offset+20523) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+20523,"B_{1}(H)^{+}");
  if (toto._hmc->GetBinContent(offset+515) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+515,"B_{2}*^{0}");
  if (toto._hmc->GetBinContent(offset+525) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+525,"B_{2}*^{+}");
  if (toto._hmc->GetBinContent(offset+531) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+531,"B_{s}^{0}");
  if (toto._hmc->GetBinContent(offset+10531) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10531,"B_{s0}*^{0}");
  if (toto._hmc->GetBinContent(offset+533) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+533,"B_{s}*^{0}");
  if (toto._hmc->GetBinContent(offset+10533) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10533,"B_{s1}(L)^{0}");
  if (toto._hmc->GetBinContent(offset+20533) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+20533,"B_{s1}(H)^{0}");
  if (toto._hmc->GetBinContent(offset+535) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+535,"B_{s2}*^{0}");
  if (toto._hmc->GetBinContent(offset+541) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+541,"B_{c}^{+}");
  if (toto._hmc->GetBinContent(offset+10541) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10541,"B_{c0}*^{+}");
  if (toto._hmc->GetBinContent(offset+543) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+543,"B_{c}*^{+}");
  if (toto._hmc->GetBinContent(offset+10543) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10543,"B_{c1}(L)^{+}");
  if (toto._hmc->GetBinContent(offset+20543) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+20543,"B_{c1}(H)^{+}");
  if (toto._hmc->GetBinContent(offset+545) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+545,"B_{c2}*^{+}");
  // ccbar mesons
  if (toto._hmc->GetBinContent(offset+441) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+441,"#eta_{c}(1S)");
  if (toto._hmc->GetBinContent(offset+10441) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10441,"#chi_{c0}(1P)");
  if (toto._hmc->GetBinContent(offset+100441) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+100441,"#eta_{c}(2S)");
  if (toto._hmc->GetBinContent(offset+443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+443,"J/#psi(1S)");
  if (toto._hmc->GetBinContent(offset+10443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+10443,"h_{c}(1P)");
  if (toto._hmc->GetBinContent(offset+20443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+20443,"#chi_{c1}(1P)");
  if (toto._hmc->GetBinContent(offset+100443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+100443,"#psi(2S)");
  if (toto._hmc->GetBinContent(offset+30443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+30443,"#psi(3770)");
  if (toto._hmc->GetBinContent(offset+9000443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+9000443,"#psi(4040)");
  if (toto._hmc->GetBinContent(offset+9010443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+9010443,"#psi(4160)");
  if (toto._hmc->GetBinContent(offset+9020443) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+9020443,"#psi(4415)");
  if (toto._hmc->GetBinContent(offset+445) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+445,"#chi_{c2}(1P)");
  if (toto._hmc->GetBinContent(offset+100445) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+100445,"#chi_{c2}(2P)");
  // bbbar mesons
  // charmed baryons
  // bottom baryons
  if (toto._hmc->GetBinContent(offset+5122) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5122,"#Lambda_{b}^{0}");
  if (toto._hmc->GetBinContent(offset+5112) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5112,"#Sigma_{b}^{-}");
  if (toto._hmc->GetBinContent(offset+5212) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5212,"#Sigma_{b}^{0}");
  if (toto._hmc->GetBinContent(offset+5222) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5222,"#Sigma_{b}^{+}");
  if (toto._hmc->GetBinContent(offset+5114) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5114,"#Sigma_{b}*^{-}");
  if (toto._hmc->GetBinContent(offset+5214) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5214,"#Sigma_{b}*^{0}");
  if (toto._hmc->GetBinContent(offset+5224) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5224,"#Sigma_{b}*^{+}");
  if (toto._hmc->GetBinContent(offset+5132) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5132,"#Xi_{b}^{-}");
  if (toto._hmc->GetBinContent(offset+5232) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5232,"#Xi_{b}^{0}");
  if (toto._hmc->GetBinContent(offset+5312) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5312,"#Xi_{b}'^{-}");
  if (toto._hmc->GetBinContent(offset+5322) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5322,"#Xi_{b}'^{0}");
  if (toto._hmc->GetBinContent(offset+5314) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5314,"#Xi_{b}*^{-}");
  if (toto._hmc->GetBinContent(offset+5324) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5324,"#Xi_{b}*^{0}");
  if (toto._hmc->GetBinContent(offset+5332) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5332,"#Omega_{b}^{-}");
  if (toto._hmc->GetBinContent(offset+5334) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5334,"#Omega_{b}*^{-}");
  if (toto._hmc->GetBinContent(offset+5142) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5142,"#Xi_{bc}^{0}");
  if (toto._hmc->GetBinContent(offset+5242) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5242,"#Xi_{bc}^{+}");
  if (toto._hmc->GetBinContent(offset+5412) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5412,"#Xi_{bc}'^{0}");
  if (toto._hmc->GetBinContent(offset+5422) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5422,"#Xi_{bc}'^{+}");
  if (toto._hmc->GetBinContent(offset+5414) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5414,"#Xi_{bc}*^{0}");
  if (toto._hmc->GetBinContent(offset+5424) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5424,"#Xi_{bc}*^{+}");
  if (toto._hmc->GetBinContent(offset+5342) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5342,"#Omega_{bc}^{0}");
  if (toto._hmc->GetBinContent(offset+5432) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5432,"#Omega_{bc}'^{0}");
  if (toto._hmc->GetBinContent(offset+5434) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5434,"#Omega_{bc}*^{0}");
  if (toto._hmc->GetBinContent(offset+5442) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5442,"#Omega_{bcc}^{+}");
  if (toto._hmc->GetBinContent(offset+5444) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5444,"#Omega_{bcc}*^{+}");
  if (toto._hmc->GetBinContent(offset+5512) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5512,"#Xi_{bb}^{-}");
  if (toto._hmc->GetBinContent(offset+5522) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5522,"#Xi_{bb}^{0}");
  if (toto._hmc->GetBinContent(offset+5514) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5514,"#Xi_{bb}*^{-}");
  if (toto._hmc->GetBinContent(offset+5524) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5524,"#Xi_{bb}*^{0}");
  if (toto._hmc->GetBinContent(offset+5532) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5532,"#Omega_{bb}^{-}");
  if (toto._hmc->GetBinContent(offset+5534) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5534,"#Omega_{bb}*^{-}");
  if (toto._hmc->GetBinContent(offset+5542) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5542,"#Omega_{bbc}^{0}");
  if (toto._hmc->GetBinContent(offset+5544) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5544,"#Omega_{bbc}*^{0}");
  if (toto._hmc->GetBinContent(offset+5554) != 0) toto._hmc->GetXaxis()->SetBinLabel(offset+5554,"#Omega_{bbb}^{-}");
  c1->Modified();
  if (print) {
    c1->Print("Plots/BHAD_ID_GEN.pdf");
    c1->Print("Plots/BHAD_ID_GEN.eps");
    c1->Print("Plots/BHAD_ID_GEN.jpg");
    c1->Print("Plots/BHAD_ID_GEN.C");
  }


}
