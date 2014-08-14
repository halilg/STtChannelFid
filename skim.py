import FWCore.ParameterSet.Config as cms

dpath="/tmp/halil/"
ifname="007E248B-54F2-E311-A601-848F69FD4586.root"
ifname="0062D09E-79F2-E311-B681-7845C4FC39DA.root"
ofname="skim_"+ifname

#set up a process , for e.g. RECO in this case
processName = "SKIM"
process = cms.Process(processName)

# this inputs the input files
process.source = cms.Source ("PoolSource",
                        fileNames=cms.untracked.vstring(
                'file:'+dpath+ifname
        )
                )


# tell the process to only run over 100 events (-1 would mean run over
#  everything
process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32 (-1)

)


# talk to output module
process.out = cms.OutputModule("PoolOutputModule",
                fileName = cms.untracked.string(dpath+ofname),
                outputCommands = cms.untracked.vstring(
 		        'drop *',
                        'keep *_*_*_HLT',
			'keep *_genParticles_*_*',
                        'keep *_ak5GenJets_*_*', 
                        'keep *_genMetTrue_*_*',
                        'keep *_ak5PFJets_*_*',
                        'keep *_electrons_*_*',     
             		'keep *_muons_*_HLT',
                        'keep *_photons_*_*',
                        'keep *_pfMet_*_*',
                        'keep *_generator_*_*',
                        'keep *_globalMuons_*_*',
                        'keep LHEEventProduct_*_*_LHE'

		)			
)


# Defines which modules and sequences to run
#process.mypath = cms.Path(process.tracker*process.MyModule)


# A list of analyzers or output modules to be run after all paths have been run.
process.outpath = cms.EndPath(process.out)

