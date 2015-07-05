from Extractor_common_jpsi import *

process = createExtractorProcess(True, True, useShiftCorrectedMET = True, globalTag = "START53_V27")

# To build Transient Tracks
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

process.PATextraction.jet_PF.useGlobalTagForJEC = True

process.source.fileNames = cms.untracked.vstring(
    #'file:../../../PatTopFilteredProduction/test/patTupleForExtractorTests_1lepton_2jets_1noisomu_ttbarslPV.root'
    'file:../../../PatTopFilteredProduction/crab_tasks/15Jun30/crab_MC_PF2PAT_TTJets_MCatNLO/results/patTuple_1.root'
    )
process.maxEvents.input = -1
