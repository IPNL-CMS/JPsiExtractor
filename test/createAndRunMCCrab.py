#! /usr/bin/env python

import os, copy, datetime, pwd, re

from optparse import OptionParser
parser = OptionParser()
parser.add_option("", "--run", action="store_true", dest="run", default=False, help="run crab")
(options, args) = parser.parse_args()

datasets = [
    #["/Py8TTbar173_19Jun13-v1/ebouvier-TTbar173-Pythia8_26Jun13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar173-Pythia8_26Jun13"]
    #["/TTbar158_16Feb13-v1/ebouvier-TTbar158_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar158_18Apr13"],
    #["/TTbar163_16Feb13-v1/ebouvier-TTbar163_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar163_18Apr13"],
    #["/TTbar167_16Feb13-v1/ebouvier-TTbar167_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar167_18Apr13"],
    #["/TTbar169_17Feb13-v1/ebouvier-TTbar169_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar169_18Apr13"],
    #["/TTbar170_16Feb13-v1/ebouvier-TTbar170_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar170_18Apr13"],
    #["/TTbar171_17Feb13-v1/ebouvier-TTbar171_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar171_18Apr13"],
    #["/TTbar172_16Feb13-v1/ebouvier-TTbar172_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar172_18Apr13"],
    ["/TTbar173_16Feb13-v1/ebouvier-TTbar173_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar173_18Apr13"],
    #["/TTbar174_16Feb13-v1/ebouvier-TTbar174_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar174_18Apr13"],
    #["/TTbar175_17Feb13-v1/ebouvier-TTbar175_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar175_18Apr13"],
    #["/TTbar176_16Feb13-v1/ebouvier-TTbar176_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar176_18Apr13"],
    #["/TTbar177_17Feb13-v1/ebouvier-TTbar177_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar177_18Apr13"],
    #["/TTbar179_16Feb13-v1/ebouvier-TTbar179_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar179_18Apr13"],
    #["/TTbar183_16Feb13-v1/ebouvier-TTbar183_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar183_18Apr13"],
    #["/TTbar188_16Feb13-v1/ebouvier-TTbar188_18Apr13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar188_18Apr13"],

    #["/T_s-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-T_s-channel_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "T_s-channel_03May13"],
    #["/T_t-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-T_t-channel_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "T_t-channel_03May13"],
    #["/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/ebouvier-T_tW-channel_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "T_tW-channel_03May13"],
    #["/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-Tbar_s-channel_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "Tbar_s-channel_03May13"],
    #["/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-Tbar_t-channel_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "Tbar_t-channel_03May13"],
    #["/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/ebouvier-Tbar_tW-channel_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "Tbar_tW-channel_03May13"],

    #["/WW_TuneZ2star_8TeV_pythia6_tauola/ebouvier-WW-incl_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "WW-incl_03May13"],
    #["/WbbJetsToLNu_Massive_TuneZ2star_8TeV-madgraph-pythia6_tauola/ebouvier-WbbJets-lnu_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "WbbJets-lnu_03May13"],
    #["/WZ_TuneZ2star_8TeV_pythia6_tauola/ebouvier-WZ-incl_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "WZ-incl_03May13"],
    #["/ZZ_TuneZ2star_8TeV_pythia6_tauola/ebouvier-ZZ-incl_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "ZZ-incl_03May13"],

    #["/DYJetsToLL_M-10To50filter_8TeV-madgraph/ebouvier-DYJetsToLL_M-10To50_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "DYJetsToLL_M-10To50_03May13"],
    #["/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/ebouvier-DYJetsToLL_M-50_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "DYJetsToLL_M-50_03May13"],
    #["/W1JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W1JetsToLNu_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "W1JetsToLNu_03May13"],
    #["/W2JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W2JetsToLNu_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "W2JetsToLNu_03May13"],
    #["/W3JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W3JetsToLNu_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "W3JetsToLNu_03May13"],
    #["/W4JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W4JetsToLNu_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "W4JetsToLNu_03May13"],

    #["/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/ebouvier-WJetsToLNu_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "WJetsToLNu_03May13"],

    ["/TTJets_FullLeptMGDecays_8TeV-madgraph/ebouvier-TTbar-dilept_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar-dilept_03May13"],
    ["/TTJets_SemiLeptMGDecays_8TeV-madgraph/ebouvier-TTbar-semilept_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar-semilept_03May13"],
    ["/TTJets_HadronicMGDecays_8TeV-madgraph/ebouvier-TTbar-hadronic_03May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "TTbar-hadronic_03May13"],


    #["/QCD_Pt-1000_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_1000_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_1000_MuEnriched_07May13"],
    #["/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_120_170_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_120_170_MuEnriched_07May13"],
    #["/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_15_20_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_15_20_MuEnriched_07May13"],
    #["/QCD_Pt_170_250_EMEnriched_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_170_250_EMEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_170_250_EMEnriched_07May13"],
    #["/QCD_Pt-170to300_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_170_300_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_170_300_MuEnriched_07May13"],
    #["/QCD_Pt_20_30_EMEnriched_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_20_30_EMEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_20_30_EMEnriched_07May13"],
    #["/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_20_30_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_20_30_MuEnriched_07May13"],
    #["/QCD_Pt_250_350_EMEnriched_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_250_350_EMEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_250_350_EMEnriched_07May13"],
    #["/QCD_Pt-300to470_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_300_470_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_300_470_MuEnriched_07May13"],
    #["/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_30_50_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_30_50_MuEnriched_07May13"],
    #["/QCD_Pt_30_80_EMEnriched_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_30_80_EMEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_30_80_EMEnriched_07May13"],
    #["/QCD_Pt_350_EMEnriched_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_350_EMEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_350_EMEnriched_07May13"],
    #["/QCD_Pt-470to600_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_470_600_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_470_600_MuEnriched_07May13"],
    #["/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_50_80_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_50_80_MuEnriched_07May13"],
    #["/QCD_Pt-600to800_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_600_800_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_600_800_MuEnriched_07May13"],
    #["/QCD_Pt-800to1000_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_800_1000_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_800_1000_MuEnriched_07May13"],
    #["/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_80_120_MuEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_80_120_MuEnriched_07May13"],
    #["/QCD_Pt_80_170_EMEnriched_TuneZ2star_8TeV_pythia6/ebouvier-QCD_Pt_80_170_EMEnriched_07May13-v1-ab4dbf1efff2b71bb776a79dcd4a112c/USER", "QCD_Pt_80_170_EMEnriched_07May13"],

    ]

# Get email address
email = "%s@ipnl.in2p3.fr" % (pwd.getpwuid(os.getuid()).pw_name)

d = datetime.datetime.now().strftime("%d%b%y")

version = 1

print("Creating configs for crab. Today is %s, you are %s and it's version %d" % (d, email, version))
print("")

for dataset in datasets:

  dataset_name = dataset[1]
  dataset_path = dataset[0]

  ui_working_dir = ("crab_MC_%s") % (dataset_name)
  output_file = "crab_MC_%s.cfg" % (dataset_name)
  output_dir = ("Extracted_step2/%s/%s" % (d, dataset_name))

  print("Creating config file for '%s'" % (dataset_path))
  print("\tName: %s" % dataset_name)
  print("")

  os.system("sed -e \"s#@datasetname@#%s#\" -e \"s#@uiworkingdir@#%s#g\" -e \"s#@outputdir@#%s#g\" -e \"s#@email@#%s#g\" crab_MC.cfg.template.ipnl > %s" % (dataset_path, ui_working_dir, output_dir, email, output_file))

  cmd = "crab -create -submit -cfg %s" % (output_file)
  if options.run:
    os.system(cmd)

