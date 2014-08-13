#ifndef STTCHANNELFID_H
#define STTCHANNELFID_H

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//
// class declaration
//
#include "TH1.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/Candidate/interface/Particle.h"
#include "TopPhysics/STtChannelFid/interface/pdg.h"


void printCandidate(const reco::Candidate &);

class STtChannelFid : public edm::EDAnalyzer {
   public:
      explicit STtChannelFid(const edm::ParameterSet&);
      ~STtChannelFid();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      std::map<std::string, TH1D *> histosD;
      std::map<std::string, TH1F *> histosF;
      std::map<std::string, TH1I *> histosI;
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void analyzeGEN(const edm::Event&, const edm::EventSetup& );
      //const reco::Candidate * getFinalState(const edm::Event& , const edm::EventSetup&);
      double getMass2(const reco::Candidate * , const reco::Candidate *);
      void book_histograms();
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      size_t nevttau;
      size_t nEvents;
      // ----------member data ---------------------------
};

#endif