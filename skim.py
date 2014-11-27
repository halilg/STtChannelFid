import FWCore.ParameterSet.Config as cms

#CMSSW configuration file to skim aMC@NLO t-channel data

dpathi="root://xrootd.unl.edu//store/mc/Summer12_DR53X/TToLeptons_t-channel_Pythia8_8TeV-aMCatNLO/AODSIM/PU_S10_START53_V19-v1/00000/"
#dpatho="/tmp/halil/"
dpatho="/afs/cern.ch/user/h/halil/st/"

idpatho="/afs/cern.ch/user/h/halil/scratch0/st/"

ifname="041C8FE6-7DF2-E311-80C1-00266CF271E8.root"
#ifname="02FA8963-70F2-E311-AB14-008CFA002ED8.root"
#ifname="02E58178-78F2-E311-A3F4-00266CFAE074.root"
#ifname="02C56ABD-C9F2-E311-9C4F-848F69FD2D6F.root"
#ifname="02BB3B65-C9F2-E311-A264-00266CFAE050.root"
#ifname="00E5E931-DBF2-E311-85D7-7845C4FC3B57.root"
#ifname="00D54F7B-6EF2-E311-BF04-F04DA275BF11.root"
#ifname="008F0604-84F2-E311-863F-00266CF9B630.root"	
#ifname="007E248B-54F2-E311-A601-848F69FD4586.root"
#ifname="0062D09E-79F2-E311-B681-7845C4FC39DA.root"
ofname="skim_"+ifname

print "Input:", dpathi+ifname
print "Output:",dpatho+ofname

#set up a process , for e.g. RECO in this case
processName = "SKIM"
process = cms.Process(processName)

# this inputs the input files
process.source = cms.Source ("PoolSource",
			     fileNames=cms.untracked.vstring(dpathi+ifname)
        		    )


# tell the process to only run over 100 events (-1 would mean run over
#  everything
process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32 (-1)

)


# talk to output module
process.out = cms.OutputModule("PoolOutputModule",
                fileName = cms.untracked.string(dpatho+ofname),
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

