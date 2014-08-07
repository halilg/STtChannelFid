import FWCore.ParameterSet.Config as cms

dpath="/tmp/halil/"
ifile="skim_007E248B-54F2-E311-A601-848F69FD4586.root"

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:'+dpath+ifile
    )
)

process.demo = cms.EDAnalyzer('STtChannelFid'
)


process.p = cms.Path(process.demo)
