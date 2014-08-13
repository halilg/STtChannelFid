import FWCore.ParameterSet.Config as cms

dpath="/tmp/halil/"
ifile="skim_007E248B-54F2-E311-A601-848F69FD4586.root"

process = cms.Process("SingleTopAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.TFileService = cms.Service("TFileService", 
      fileName = cms.string("histos.root"),
      closeFileFast = cms.untracked.bool(True)
)

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:'+dpath+ifile
    )
)

process.SingleTopAnalysis = cms.EDAnalyzer('STtChannelFid'
)


process.p = cms.Path(process.SingleTopAnalysis)
