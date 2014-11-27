import FWCore.ParameterSet.Config as cms

#dpath="/afs/cern.ch/user/h/halil/scratch0/st/"
dpath="/afs/cern.ch/user/h/halil/st/"
ifile1="skim_008F0604-84F2-E311-863F-00266CF9B630.root" #skim_007E248B-54F2-E311-A601-848F69FD4586.root"
ifile2="skim_0062D09E-79F2-E311-B681-7845C4FC39DA.root"

skipEvents=0
maxEvents=-1


process = cms.Process("SingleTopAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxEvents ) )

process.TFileService = cms.Service("TFileService", 
      fileName = cms.string("histos.root"),
)

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:'+dpath+ifile1,
        'file:'+dpath+ifile2
        ),
    skipEvents=cms.untracked.uint32(skipEvents)
)

process.SingleTopAnalysis = cms.EDAnalyzer('STtChannelFid')


process.p = cms.Path(process.SingleTopAnalysis)
