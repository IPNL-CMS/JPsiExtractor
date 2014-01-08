from Extractor_common_jpsi import *

process = createExtractorProcess(True, True, useShiftCorrectedMET = True, globalTag = "START53_V19PR")

# To build Transient Tracks
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

process.source.fileNames = cms.untracked.vstring(
    #'file:/gridgroup/cms/bouvier/data/test_extractor/patTuple_1_1_Uqw.root'
    #'file:/gridgroup/cms/bouvier/data/test_extractor/patTuple_10_1_Wtz.root'
    'file:/scratch/bouvier/TTbar173_1.root',
    'file:/scratch/bouvier/TTbar173_2.root',
    'file:/scratch/bouvier/TTbar173_3.root',
    'file:/scratch/bouvier/TTbar173_4.root',
    'file:/scratch/bouvier/TTbar173_5.root',
    'file:/scratch/bouvier/TTbar173_6.root',
    'file:/scratch/bouvier/TTbar173_7.root',
    'file:/scratch/bouvier/TTbar173_8.root',
    'file:/scratch/bouvier/TTbar173_9.root',
    'file:/scratch/bouvier/TTbar173_10.root',
    #'file:/scratch/bouvier/TTbar173_11.root',
    #'file:/scratch/bouvier/TTbar173_12.root',
    #'file:/scratch/bouvier/TTbar173_13.root',
    #'file:/scratch/bouvier/TTbar173_14.root',
    #'file:/scratch/bouvier/TTbar173_15.root',
    #'file:/scratch/bouvier/TTbar173_16.root',
    #'file:/scratch/bouvier/TTbar173_17.root',
    #'file:/scratch/bouvier/TTbar173_18.root'
    )
process.maxEvents.input = -1
