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

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//
// class declaration
//
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"

//#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/Candidate/interface/Particle.h"

class STtChannelFid : public edm::EDAnalyzer {
   public:
      explicit STtChannelFid(const edm::ParameterSet&);
      ~STtChannelFid();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
};

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
   using namespace std;
   edm::Handle<reco::GenParticleCollection> genParticles;
   edm::Handle<reco::GenJetCollection> genJets;
   
   //std::vector <const GenParticle*> genJetConstituents; //getGenConstituents () c
   
   
   iEvent.getByLabel("genParticles", genParticles);
   iEvent.getByLabel("ak5GenJets", genJets);
   
   size_t nparticles=genParticles->size();
   size_t ngenjets=genJets->size();
   //size_t ngenjconst=genJetConstituents.size();
      
   std::cout << ngenjets << std::endl;
   for(size_t i = 0; i < genJets->size(); ++ i) {
        const reco::GenJet & gj = (*genJets)[i];
        //genJetConstituents=gj.getGenConstituents();
        vector<const reco::GenParticle*> theJetConstituents = gj.getGenConstituents();
        if (i==0) cout << theJetConstituents.size() << endl;
   }
   
   
   for(size_t i = 0; i < genParticles->size(); ++ i) {
        const reco::GenParticle & p = (*genParticles)[i];
        /*
        int id = p.pdgId();
        int st = p.status();  
        const reco::Candidate * mom = p.mother();
        double pt = p.pt(), eta = p.eta(), phi = p.phi(), mass = p.mass();
        double vx = p.vx(), vy = p.vy(), vz = p.vz();
        int charge = p.charge();
        size_t n = p.numberOfDaughters();
        for(size_t j = 0; j < n; ++ j) {
          const reco::Candidate * d = p.daughter( j );
          int dauId = d->pdgId();
          // . . . 
        }
        // . . .
        */
   }

}


// ------------ method called once each job just before starting event loop  ------------
void 
STtChannelFid::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
STtChannelFid::endJob() 
{
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
