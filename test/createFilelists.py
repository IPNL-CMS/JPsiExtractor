#! /usr/bin/env python

import os, copy, datetime, pwd, re

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-d", "--date", dest="date", type="string", default=False, help="date when crab tasks were created")
(options, args) = parser.parse_args()

dir = os.path.join(os.getcwd(), "crab_tasks")    
if not options.date or not os.path.isdir(os.path.join(dir, options.date)):
    parser.error("you must specify a valid date")
dir = os.path.join(dir, options.date) 

dirList = os.path.join(dir, "Filelists")
if not os.path.isdir(dirList):
    os.mkdir(dirList)

crabFolders = [name for name in os.listdir(dir) if (os.path.isdir(os.path.join(dir, name)) and name.startswith("crab_"))]
for crabFolder in crabFolders:
    listFile = crabFolder[5:]  
    if listFile.startswith("MC_"):
        listFile = listFile[13:]
    if listFile.startswith("Data_"):
        listFile = listFile[15:]
    listFile += ".list"
    listFile = os.path.join(dirList, listFile)
    list = open(listFile, 'w')
    crabFolder = os.path.join(dir, crabFolder)
    crabFolder = os.path.join(crabFolder, "results")
    rootFiles = [name for name in os.listdir(crabFolder) if name.endswith(".root")]
    for rootFile in rootFiles:
        rootFile = os.path.join(crabFolder, rootFile)
        list.write(rootFile+"\n")
    list.close()    

dirMu = os.path.join(dirList, "MuonicDatasets")
if not os.path.isdir(dirMu):
    os.mkdir(dirMu)
listFiles = [name for name in os.listdir(dirList) if (name.lower().count("muhad") or name.lower().count("singlemu"))]
for listFile in listFiles:
    cmd = "less "+os.path.join(dirList, listFile)+" >> "+os.path.join(dirList, "MuHadASingleMuBCD.list")
    os.system(cmd)
    cmd = "mv "+os.path.join(dirList, listFile)+" "+dirMu
    os.system(cmd)
dirEl = os.path.join(dirList, "ElectronicDatasets")
if not os.path.isdir(dirEl):
    os.mkdir(dirEl)
listFiles = [name for name in os.listdir(dirList) if (name.lower().count("electronhad") or name.lower().count("singleelectron"))]
for listFile in listFiles:
    cmd = "less "+os.path.join(dirList, listFile)+" >> "+os.path.join(dirList, "ElectronHadASingleElectronBCD.list")
    os.system(cmd)
    cmd = "mv "+os.path.join(dirList, listFile)+" "+dirEl
    os.system(cmd)

print dirList[len(os.getcwd())+1:]+" has been created"

