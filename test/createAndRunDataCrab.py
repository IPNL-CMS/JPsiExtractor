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

version = 6
    
datasets = [
    ["/MuHad/ebouvier-MuHad_Run2012A-22Jan2013_15Apr01-v1-0a0811ab37aa24280a978161285f4b48/USER", "MuHad_Run2012A", "100"],
    ["/ElectronHad/ebouvier-ElectronHad_Run2012A-22Jan2013_15Apr01-v1-0a0811ab37aa24280a978161285f4b48/USER", "ElectronHad_Run2012A","140"],
    ["/SingleMu/ebouvier-SingleMu_Run2012B-22Jan2013_15Apr01-v1-0a0811ab37aa24280a978161285f4b48/USER", "SingleMu_Run2012B", "20"],
    ["/SingleElectron/ebouvier-SingleElectron_Run2012B-22Jan2013_15Apr01-v1-0a0811ab37aa24280a978161285f4b48/USER", "SingleElectron_Run2012B", "30"],
    ["/SingleMu/ebouvier-SingleMu_Run2012C-22Jan2013_15Apr01-v1-0a0811ab37aa24280a978161285f4b48/USER", "SingleMu_Run2012C", "20"],
    ["/SingleElectron/ebouvier-SingleElectron_Run2012C-22Jan2013_15Apr01-v1-0a0811ab37aa24280a978161285f4b48/USER", "SingleElectron_Run2012C", "30"],
    ["/SingleMu/ebouvier-SingleMu_Run2012D-22Jan2013_15Apr01-v1-0a0811ab37aa24280a978161285f4b48/USER","SingleMu_Run2012D", "20"],
    ["/SingleElectron/ebouvier-SingleElectron_Run2012D-22Jan2013_15Apr01-v1-0a0811ab37aa24280a978161285f4b48/USER","SingleElectron_Run2012D", "30"]
    ]

print("Creating configs for crab. Today is %s, you are %s and it's version %d" % (d, user_name, version))
print("")

if not os.path.exists(d):
    os.mkdir(d)

pset_name = "\'Extractor_jpsi.py\'"
out_name = "\'extracted.root\'"

for dataset in datasets:

    dataset_path = "\'"+dataset[0]+"\'"
    dataset_name = dataset[1]
    dataset_quanta = dataset[2]

    task_name = ("\'Data_Extracted_%s\'") % (dataset_name)
    publish_name = "\'%s_%s-v%d\'" % (dataset_name, d, version)
    output_file = "%s/crab_Data_Extracted_%s.py" % (d, dataset_name)
    output_dir = ("\'crab_tasks/%s\'") % (d)

    print("\tCreating config file for %s" % (dataset_path))
    print("\t\tName: \'%s\'" % dataset_name)
    print("\t\tPublishing name: %s" % publish_name)
    print("")

    os.system("sed -e \"s#@datasetname@#%s#g\" -e \"s#@taskname@#%s#g\" -e \"s#@outputdir@#%s#g\" -e \"s#@username@#%s#g\" -e \"s#@psetname@#%s#g\" -e \"s#@outname@#%s#g\" -e \"s#@datasetquanta@#%s#g\" -e \"s#@publishname@#%s#g\" crab_data.cfg.template.ipnl > %s" % (dataset_path, task_name, output_dir, user_name, pset_name, out_name, dataset_quanta, publish_name, output_file))

    cmd = "crab submit %s" % (output_file)
    if options.run:
        os.system(cmd)
