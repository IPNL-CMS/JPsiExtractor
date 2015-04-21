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
    listFile = crabFolder.strip("crab_")  
    if listFile.startswith("MC_"):
        listFile = listFile.strip("MC_")
    if listFile.startswith("Data_"):
        listFile = listFile.strip("Data_")
    listFile = listFile.strip("Extracted_")
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
