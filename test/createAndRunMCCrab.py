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

version = 2

datasets = [
    # Standard ttbar
    ["/TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola/ebouvier-TTJets_SemiLeptMGDecays_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_SemiLeptMGDecays", "1"],
    ["/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/ebouvier-TTJets_FullLeptMGDecays_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_FullLeptMGDecays", "1"],
    ["/TTJets_HadronicMGDecays_8TeV-madgraph/ebouvier-TTJets_HadronicMGDecays_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTJets_HadronicMGDecays", "25"],
    # W + jets
    #["", "WJetsToLNu", ""],
    ["/W1JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W1JetsToLNu_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "W1JetsToLNu", "2"],
    ["/W2JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W2JetsToLNu_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "W2JetsToLNu", "2"],
    ["/W3JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W3JetsToLNu_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "W3JetsToLNu", "2"],
    ["/W4JetsToLNu_TuneZ2Star_8TeV-madgraph/ebouvier-W4JetsToLNu_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "W4JetsToLNu", "1"],
    # Z + jets
    #["", "DYJetsToLL_M-10To50", ""],
    #["", "DYJetsToLL_M-50", ""],
    ["/DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/ebouvier-DY1JetsToLL_M-50_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DY1JetsToLL_M-50", "1"],
    ["/DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/ebouvier-DY2JetsToLL_M-50_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DY2JetsToLL_M-50", "1"],
    ["/DY3JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/ebouvier-DY3JetsToLL_M-50_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DY3JetsToLL_M-50", "1"],
    ["/DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/ebouvier-DY4JetsToLL_M-50_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "DY4JetsToLL_M-50", "1"],
    # diboson
    ["/WW_TuneZ2star_8TeV_pythia6_tauola/ebouvier-WW-incl_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "WW-incl", "2"],
    ["/ZZ_TuneZ2star_8TeV_pythia6_tauola/ebouvier-ZZ-incl_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "WZ-incl", "2"],
    ["/WZ_TuneZ2star_8TeV_pythia6_tauola/ebouvier-WZ-incl_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "ZZ-incl", "2"],
    # ttbar other
    ["/TTWJets_8TeV-madgraph/ebouvier-TTWJets_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTWJets", "1"],
    ["/TTWWJets_8TeV-madgraph/ebouvier-TTWWJets_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTWWJets", "1"],
    ["/TTZJets_8TeV-madgraph_v2/ebouvier-TTZJets_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "TTZJets", "1"],
    # single top 
    ## central
    ["/T_s-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-T_s-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "T_s-channel", "2"],
    ["/T_t-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-T_t-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "T_t-channel", "2"],
    ["/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/ebouvier-T_tW-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "T_tW-channel", "1"],
    ["/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-Tbar_s-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "Tbar_s-channel", "2"],
    ["/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/ebouvier-Tbar_t-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "Tbar_t-channel", "2"],
    ["/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/ebouvier-Tbar_tW-channel_15Apr01-v1-e6007310307bd4a37c1ea3682357ad52/USER", "Tbar_tW-channel", "1"], 
    ## single top t-chanel, top mass variations
    #["", "TToLeptons_t-channel_mass166_5", ""],
    #["", "TToLeptons_t-channel_mass169_5", ""],
    #["", "TToLeptons_t-channel_mass171_5", ""],
    #["", "TToLeptons_t-channel_mass173_5", ""],
    #["", "TToLeptons_t-channel_mass175_5", ""],
    #["", "TToLeptons_t-channel_mass178_5", ""],
    #["", "TBarToLeptons_t-channel_mass166_5", ""],
    #["", "TBarToLeptons_t-channel_mass169_5", ""],
    #["", "TBarToLeptons_t-channel_mass171_5", ""],
    #["", "TBarToLeptons_t-channel_mass173_5", ""],
    #["", "TBarToLeptons_t-channel_mass175_5", ""],
    #["", "TBarToLeptons_t-channel_mass178_5", ""],
    ## 166.5
    #["", "TBarToLeptons_s-channel_mass166_5", ""],
    #["", "TBarToLeptons_t-channel_mass166_5", ""],
    #["", "TBarToTlepWhad_tW-channel-DR_mass166_5", ""],
    #["", "TBarToThadWlep_tW-channel-DR_mass166_5", ""],
    #["", "TBarToDilepton_tW-channel-DR_mass166_5", ""],
    #["", "TToLeptons_s-channel_mass166_5", ""],
    #["", "TToLeptons_t-channel_mass166_5", ""],
    #["", "TToTlepWhad_tW-channel-DR_mass166_5", ""],
    #["", "TToThadWlep_tW-channel-DR_mass166_5", ""],
    #["", "TToDilepton_tW-channel-DR_mass166_5", ""],
    ## 178.5
    #["", "TBarToLeptons_s-channel_mass178_5", ""],
    #["", "TBarToLeptons_t-channel_mass178_5", ""],
    #["", "TBarToTlepWhad_tW-channel-DR_mass178_5", ""],
    #["", "TBarToThadWlep_tW-channel-DR_mass178_5", ""],
    #["", "TBarToDilepton_tW-channel-DR_mass178_5", ""],
    #["", "TToLeptons_s-channel_mass178_5", ""],
    #["", "TToLeptons_t-channel_mass178_5", ""],
    #["", "TToTlepWhad_tW-channel-DR_mass178_5", ""],
    #["", "TToThadWlep_tW-channel-DR_mass178_5", ""],
    #["", "TToDilepton_tW-channel-DR_mass178_5", ""],
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

