import FWCore.ParameterSet.Config as cms

dpath="/tmp/halil/"
ifile1="skim_007E248B-54F2-E311-A601-848F69FD4586.root"
ifile2="skim_0062D09E-79F2-E311-B681-7845C4FC39DA.root"

process = cms.Process("SingleTopAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( -1) )

process.TFileService = cms.Service("TFileService", 
      fileName = cms.string("histos.root"),
)

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:'+dpath+ifile1,
        'file:'+dpath+ifile2
        )
)

process.SingleTopAnalysis = cms.EDAnalyzer('STtChannelFid')


process.p = cms.Path(process.SingleTopAnalysis)
