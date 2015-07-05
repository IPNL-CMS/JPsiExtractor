#! /usr/bin/env python

import os, copy, datetime, pwd, re

from optparse import OptionParser
parser = OptionParser()
parser.add_option("", "--run", action="store_true", dest="run", default=False, help="run crab")
(options, args) = parser.parse_args()
    
# Get username address
#user_name = "\'/store/user/%s\'" % (pwd.getpwuid(os.getuid()).pw_name)
user_name = "\'/store/user/ebouvier\'" 

d = datetime.datetime.now().strftime("%y%b%d")
#d = "JECup" # caveat should have been JERup
#d = "JERdown"
#d = "JESup"
#d = "JESdown"

version = 2

datasets = [
    # Standard ttbar
    #["/TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola/ebouvier-TTJets_SemiLeptMGDecays_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_SemiLeptMGDecays", "20"],
    #["/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/ebouvier-TTJets_FullLeptMGDecays_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_FullLeptMGDecays", "20"],
    #["/TTJets_HadronicMGDecays_8TeV-madgraph/ebouvier-TTJets_HadronicMGDecays_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_HadronicMGDecays", "50"],
    # W + jets
    #["/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/ebouvier-WJetsToLNu_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "WJetsToLNu", "40"],
    #["/W1JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W1JetsToLNu_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "W1JetsToLNu", "40"],
    #["/W2JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W2JetsToLNu_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "W2JetsToLNu", "40"],
    #["/W3JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W3JetsToLNu_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "W3JetsToLNu", "40"],
    #["/W4JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W4JetsToLNu_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "W4JetsToLNu", "20"],
    # Z + jets
    #["/DYJetsToLL_M-10To50filter_8TeV-madgraph/ebouvier-DYJetsToLL_M-10To50_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DYJetsToLL_M-10To50", "20"],
    #["/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/ebouvier-DYJetsToLL_M-50_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DYJetsToLL_M-50", "20"],
    #["/DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/ebouvier-DY1JetsToLL_M-50_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DY1JetsToLL_M-50", "20"],
    #["/DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/ebouvier-DY2JetsToLL_M-50_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DY2JetsToLL_M-50", "20"],
    #["/DY3JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/ebouvier-DY3JetsToLL_M-50_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DY3JetsToLL_M-50", "20"],
    #["/DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/ebouvier-DY4JetsToLL_M-50_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DY4JetsToLL_M-50", "20"],
    # diboson
    #["/WW_TuneZ2star_8TeV_pythia6_tauola/ebouvier-WW-incl_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "WW-incl", "40"],
    #["/ZZ_TuneZ2star_8TeV_pythia6_tauola/ebouvier-ZZ-incl_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "WZ-incl", "40"],
    #["/WZ_TuneZ2star_8TeV_pythia6_tauola/ebouvier-WZ-incl_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "ZZ-incl", "40"],
    # ttbar other
    #["/TTWJets_8TeV-madgraph/ebouvier-TTWJets_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTWJets", "20"],
    #["/TTWWJets_8TeV-madgraph/ebouvier-TTWWJets_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTWWJets", "20"],
    #["/TTZJets_8TeV-madgraph_v2/ebouvier-TTZJets_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTZJets", "20"],
    # single top 
    ## central
    #["/T_s-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-T_s-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "T_s-channel", "40"],
    #["/T_t-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-T_t-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "T_t-channel", "40"],
    #["/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/ebouvier-T_tW-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "T_tW-channel", "20"],
    #["/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-Tbar_s-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "Tbar_s-channel", "40"],
    #["/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-Tbar_t-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "Tbar_t-channel", "40"],
    #["/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/ebouvier-Tbar_tW-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "Tbar_tW-channel", "20"], 
    ## single top t-chanel, top mass variations
    #["/TToLeptons_t-channel_mass166_5_8TeV-powheg-tauola/ebouvier-TToLeptons_t-channel_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToLeptons_t-channel_mass166_5", "40"],
    #["/TToLeptons_t-channel_mass169_5_8TeV-powheg-tauola/ebouvier-TToLeptons_t-channel_mass169_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToLeptons_t-channel_mass169_5", "40"],
    #["/TToLeptons_t-channel_mass171_5_8TeV-powheg-tauola/ebouvier-TToLeptons_t-channel_mass171_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToLeptons_t-channel_mass171_5", "40"],
    #["/TToLeptons_t-channel_mass173_5_8TeV-powheg-tauola/ebouvier-TToLeptons_t-channel_mass173_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToLeptons_t-channel_mass173_5", "40"],
    #["/TToLeptons_t-channel_mass175_5_8TeV-powheg-tauola/ebouvier-TToLeptons_t-channel_mass175_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToLeptons_t-channel_mass175_5", "40"],
    #["/TToLeptons_t-channel_mass178_5_8TeV-powheg-tauola/ebouvier-TToLeptons_t-channel_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToLeptons_t-channel_mass178_5", "40"],
    #["/TBarToLeptons_t-channel_mass166_5_8TeV-powheg-tauola/ebouvier-TBarToLeptons_t-channel_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToLeptons_t-channel_mass166_5", "40"],
    #["/TBarToLeptons_t-channel_mass169_5_8TeV-powheg-tauola/ebouvier-TBarToLeptons_t-channel_mass169_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToLeptons_t-channel_mass169_5", "40"],
    #["/TBarToLeptons_t-channel_mass171_5_8TeV-powheg-tauola/ebouvier-TBarToLeptons_t-channel_mass171_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToLeptons_t-channel_mass171_5", "40"],
    #["/TBarToLeptons_t-channel_mass173_5_8TeV-powheg-tauola/ebouvier-TBarToLeptons_t-channel_mass173_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToLeptons_t-channel_mass173_5", "40"],
    #["/TBarToLeptons_t-channel_mass175_5_8TeV-powheg-tauola/ebouvier-TBarToLeptons_t-channel_mass175_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToLeptons_t-channel_mass175_5", "40"],
    #["/TBarToLeptons_t-channel_mass178_5_8TeV-powheg-tauola/ebouvier-TBarToLeptons_t-channel_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToLeptons_t-channel_mass178_5", "40"],
    ## 166.5
    #["/TBarToLeptons_s-channel_mass166_5_8TeV-powheg-tauola/ebouvier-TBarToLeptons_s-channel_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToLeptons_s-channel_mass166_5", "40"],
    #["/TBarToTlepWhad_tW-channel-DR_mass166_5_8TeV-powheg-tauola/ebouvier-TBarToTlepWhad_tW-channel-DR_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToTlepWhad_tW-channel-DR_mass166_5", "20"],
    #["/TBarToThadWlep_tW-channel-DR_mass166_5_8TeV-powheg-tauola/ebouvier-TBarToThadWlep_tW-channel-DR_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToThadWlep_tW-channel-DR_mass166_5", "20"],
    #["/TBarToDilepton_tW-channel-DR_mass166_5_8TeV-powheg-tauola/ebouvier-TBarToDilepton_tW-channel-DR_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToDilepton_tW-channel-DR_mass166_5", "20"],
    #["/TToLeptons_s-channel_mass166_5_8TeV-powheg-tauola/ebouvier-TToLeptons_s-channel_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToLeptons_s-channel_mass166_5", "40"],
    #["/TToTlepWhad_tW-channel-DR_mass166_5_8TeV-powheg-tauola/ebouvier-TToTlepWhad_tW-channel-DR_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToTlepWhad_tW-channel-DR_mass166_5", "20"],
    #["/TToThadWlep_tW-channel-DR_mass166_5_8TeV-powheg-tauola/ebouvier-TToThadWlep_tW-channel-DR_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToThadWlep_tW-channel-DR_mass166_5", "20"],
    #["/TToDilepton_tW-channel-DR_mass166_5_8TeV-powheg-tauola/ebouvier-TToDilepton_tW-channel-DR_mass166_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToDilepton_tW-channel-DR_mass166_5", "20"],
    ## 178.5
    #["/TBarToLeptons_s-channel_mass178_5_8TeV-powheg-tauola/ebouvier-TBarToLeptons_s-channel_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToLeptons_s-channel_mass178_5", "40"],
    #["/TBarToTlepWhad_tW-channel-DR_mass178_5_8TeV-powheg-tauola/ebouvier-TBarToTlepWhad_tW-channel-DR_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToTlepWhad_tW-channel-DR_mass178_5", "20"],
    #["/TBarToThadWlep_tW-channel-DR_mass178_5_8TeV-powheg-tauola/ebouvier-TBarToThadWlep_tW-channel-DR_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToThadWlep_tW-channel-DR_mass178_5", "20"],
    #["/TBarToDilepton_tW-channel-DR_mass178_5_8TeV-powheg-tauola/ebouvier-TBarToDilepton_tW-channel-DR_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TBarToDilepton_tW-channel-DR_mass178_5", "20"],
    #["/TToLeptons_s-channel_mass178_5_8TeV-powheg-tauola/ebouvier-TToLeptons_s-channel_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToLeptons_s-channel_mass178_5", "40"],
    #["/TToTlepWhad_tW-channel-DR_mass178_5_8TeV-powheg-tauola/ebouvier-TToTlepWhad_tW-channel-DR_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToTlepWhad_tW-channel-DR_mass178_5", "20"],
    #["/TToThadWlep_tW-channel-DR_mass178_5_8TeV-powheg-tauola/ebouvier-TToThadWlep_tW-channel-DR_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToThadWlep_tW-channel-DR_mass178_5", "20"],
    #["/TToDilepton_tW-channel-DR_mass178_5_8TeV-powheg-tauola/ebouvier-TToDilepton_tW-channel-DR_mass178_5_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TToDilepton_tW-channel-DR_mass178_5", "20"],
    # Jpsi enriched ttbar
    #["/TTJets_MSDecays_JpsiFilter_1665_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_1665_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_166_5", "20"],
    #["/TTJets_MSDecays_JpsiFilter_1695_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_1695_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_169_5", "20"],
    #["/TTJets_MSDecays_JpsiFilter_1715_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_1715_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_171_5", "20"],
    ["/TTJets_MSDecays_JpsiFilter_central_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_1725_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_172_5", "20"],
    #["/TTJets_MSDecays_JpsiFilter_1735_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_1735_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_173_5", "20"],
    #["/TTJets_MSDecays_JpsiFilter_1755_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_1755_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_175_5", "20"],
    #["/TTJets_MSDecays_JpsiFilter_1785_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_1785_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_178_5", "20"],
    #["/TTJets_MSDecays_JpsiFilter_matchingdown_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_matchingdown_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_matchingdown", "20"],
    #["/TTJets_MSDecays_JpsiFilter_matchingup_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_matchingup_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_matchingup", "20"],
    #["/TTJets_MSDecays_JpsiFilter_scaledown_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_scaledown_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_scaledown", "20"],
    #["/TTJets_MSDecays_JpsiFilter_scaleup_TuneZ2star_8TeV-madgraph-tauola/ebouvier-TTJets_MSDecays_JpsiFilter_scaleup_15May10-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MSDecays_JpsiFilter_scaleup", "20"],
    # P11 ttbar
    ## central tune
    ["/TTJets_SemiLeptMGDecays_TuneP11_8TeV-madgraph-tauola/ebouvier-TTJets_SemiLeptMGDecays_TuneP11_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_SemiLeptMGDecays_TuneP11", "20"],
    ["/TTJets_FullLeptMGDecays_TuneP11_8TeV-madgraph-tauola/ebouvier-TTJets_FullLeptMGDecays_TuneP11_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_FullLeptMGDecays_TuneP11", "20"],
    ["/TTJets_HadronicMGDecays_TuneP11_8TeV-madgraph-tauola/ebouvier-TTJets_HadronicMGDecays_TuneP11_15Jul01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_HadronicMGDecays_TuneP11", "50"],
    ## mpiHi tune
    ["/TTJets_SemiLeptMGDecays_TuneP11mpiHi_8TeV-madgraph-tauola/ebouvier-TTJets_SemiLeptMGDecays_TuneP11mpiHi_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_SemiLeptMGDecays_TuneP11mpiHi", "20"],
    ["/TTJets_FullLeptMGDecays_TuneP11mpiHi_8TeV-madgraph-tauola/ebouvier-TTJets_FullLeptMGDecays_TuneP11mpiHi_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_FullLeptMGDecays_TuneP11mpiHi", "20"],
    ["/TTJets_HadronicMGDecays_TuneP11mpiHi_8TeV-madgraph-tauola/ebouvier-TTJets_HadronicMGDecays_TuneP11mpiHi_15Jul01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_HadronicMGDecays_TuneP11mpiHi", "50"],
    ## Tevatron tune
    ["/TTJets_SemiLeptMGDecays_TuneP11TeV_8TeV-madgraph-tauola/ebouvier-TTJets_SemiLeptMGDecays_TuneP11TeV_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_SemiLeptMGDecays_TuneP11TeV", "20"],
    ["/TTJets_FullLeptMGDecays_TuneP11TeV_8TeV-madgraph-tauola/ebouvier-TTJets_FullLeptMGDecays_TuneP11TeV_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_FullLeptMGDecays_TuneP11TeV", "20"],
    ["/TTJets_HadronicMGDecays_TuneP11TeV_8TeV-madgraph-tauola/ebouvier-TTJets_HadronicMGDecays_TuneP11TeV_15Jul01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_HadronicMGDecays_TuneP11TeV", "50"],
    ## noCR tune
    ["/TTJets_SemiLeptMGDecays_TuneP11noCR_8TeV-madgraph-tauola/ebouvier-TTJets_SemiLeptMGDecays_TuneP11noCR_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_SemiLeptMGDecays_TuneP11noCR", "20"],
    ["/TTJets_FullLeptMGDecays_TuneP11noCR_8TeV-madgraph-tauola/ebouvier-TTJets_FullLeptMGDecays_TuneP11noCR_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_FullLeptMGDecays_TuneP11noCR", "20"],
    ["/TTJets_HadronicMGDecays_TuneP11noCR_8TeV-madgraph-tauola/ebouvier-TTJets_HadronicMGDecays_TuneP11noCR_15Jul01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_HadronicMGDecays_TuneP11noCR", "50"],
    # POWHEG ttbar
    ["/TT_CT10_TuneZ2star_8TeV-powheg-tauola/ebouvier-TTJets_Powheg_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_Powheg", "20"],
    # MC@NLO
    ["/TT_8TeV-mcatnlo/ebouvier-TTJets_MCatNLO_15Jun30-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_MCatNLO", "20"],
    ]

print("Creating configs for crab. Today is %s, you are %s and it's version %d" % (d, user_name, version))
print("")

if not os.path.exists(d):
    os.mkdir(d)

pset_name = "\'Extractor_MC_jpsi.py\'"
out_name = "\'extracted_mc.root\'"

for dataset in datasets:

    dataset_path = "\'"+dataset[0]+"\'"
    dataset_name = dataset[1]
    dataset_quanta = dataset[2]

    task_name = ("\'MC_Extracted_%s\'") % (dataset_name)
    publish_name = "\'%s_%s-v%d\'" % (dataset_name, d, version)
    output_file = "%s/crab_MC_Extracted_%s.py" % (d, dataset_name)
    output_dir = ("\'crab_tasks/%s\'") % (d)

    print("\tCreating config file for %s" % (dataset_path))
    print("\t\tName: \'%s\'" % dataset_name)
    print("\t\tPublishing name: %s" % publish_name)
    print("")

    os.system("sed -e \"s#@datasetname@#%s#\" -e \"s#@taskname@#%s#g\" -e \"s#@outputdir@#%s#g\" -e \"s#@username@#%s#g\" -e \"s#@psetname@#%s#g\" -e \"s#@outname@#%s#g\" -e \"s#@publishname@#%s#g\" -e \"s#@datasetquanta@#%s#g\" crab_MC.cfg.template.ipnl > %s" % (dataset_path, task_name, output_dir, user_name, pset_name, out_name, publish_name, dataset_quanta, output_file))
    
    cmd = "crab submit %s" % (output_file)
    if options.run:
        os.system(cmd)

