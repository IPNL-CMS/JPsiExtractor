from Extractor_common_jpsi import *

process = createExtractorProcess(False, True, useShiftCorrectedMET = True, globalTag = "FT53_V21A_AN6")

# To build Transient Tracks
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

process.PATextraction.jet_PF.useGlobalTagForJEC = False

process.source.fileNames = cms.untracked.vstring(
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_9.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_90.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_91.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_92.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_93.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_94.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_95.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_96.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_97.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_98.root',
        'file:../../../PatTopFilteredProduction/crab_tasks/15Apr01/crab_Data_PF2PAT_MuHad_Run2012A-22Jan2013/results/patTuple_99.root',
    )
process.maxEvents.input = -1
