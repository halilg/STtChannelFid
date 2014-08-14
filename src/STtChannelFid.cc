// -*- C++ -*-
//
// Package:    STtChannelFid
// Class:      STtChannelFid
// 
/**\class STtChannelFid STtChannelFid.cc TopPhysics/STtChannelFid/src/STtChannelFid.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Halil Gamsizkan,,,
//         Created:  Wed Aug  6 13:49:22 CEST 2014
// $Id$
//
//


// system include files
#include <memory>
#include <iostream>
#include <vector>

#include "TopPhysics/STtChannelFid/interface/STtChannelFid.h"

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
STtChannelFid::STtChannelFid(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   nevttau=0; // tau events counter
   nEvents=0;  // all events counter
   nFiducial=0; // number of events in the fiducial volume
   nWevttau=0; // weighted event counters
   nWEvents=0;
   nWFiducial=0;

}


STtChannelFid::~STtChannelFid()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called for each event  ------------
void
STtChannelFid::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   analyzeGEN(iEvent, iSetup);
}


// ------------ method called once each job just before starting event loop  ------------
void 
STtChannelFid::beginJob()
{
   book_histograms();
}

// ------------ method called once each job just after ending the event loop  ------------
void 
STtChannelFid::endJob()
{
   float bremu=0.2132;
   std::cout << "Analysis complete.\n\n"
             << "Received a total of " << nEvents << " events, "
             << nevttau << " of which were tau lepton events.\n"
             << nFiducial << " events were in the fiducial volume.\n\n"
             << "Received a total of " << nWEvents << " weighted events, "
             << nWevttau << " of which were tau lepton events.\n"
             << nWFiducial << " events were in the fiducial volume.\n"
             << "Therefore for the e/mu branching ratio of " << bremu
             << ":\nepsilon=" << bremu * float(nWFiducial) / float(nWEvents-nWevttau) << std::endl;
}

// ------------ method called when starting to processes a run  ------------
void 
STtChannelFid::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
STtChannelFid::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
STtChannelFid::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
STtChannelFid::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
STtChannelFid::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(STtChannelFid);
