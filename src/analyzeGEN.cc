#include "TopPhysics/STtChannelFid/interface/STtChannelFid.h"



#define FSSIZE    10   // size of MyFinalState
enum MyFinalState {HSTOPF, HSTOPL, HSB, HSRECOIL, TOPB, TOPWF, TOPWL, WL, WNU};


void
STtChannelFid::analyzeGEN(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace std;
    size_t DEBUG = 0;
    ++nEvents;
    cout.precision(4);
    const reco::Candidate * final_state[FSSIZE];
    for (size_t i = 0; i<FSSIZE; i++) final_state[i] = NULL;
    edm::Handle<reco::GenParticleCollection> genParticles;
    edm::Handle<reco::GenJetCollection> genJets;
    edm::Handle<LHEEventProduct > lhes;
    iEvent.getByLabel("source", lhes);   
    iEvent.getByLabel("genParticles", genParticles);
    iEvent.getByLabel("ak5GenJets", genJets);
    //size_t nparticles=genParticles->size();
    size_t ngenjets=genJets->size();
    //size_t ngenjconst=genJetConstituents.size();
    
    float weightsign = lhes->hepeup().XWGTUP;
    weightsign = weightsign / fabs(weightsign);
       
    if (DEBUG) std::cout << ngenjets << ", weight: " << weightsign << std::endl;
   
   /*
   for(size_t i = 0; i < genJets->size(); ++ i) {
        const reco::GenJet & gj = (*genJets)[i];
        //genJetConstituents=gj.getGenConstituents();
        vector<const reco::Candidate*> theJetConstituents = gj.getGenConstituents();
        if (i==0) cout << theJetConstituents.size() << endl;
   }
   */
   
    for(size_t i = 0; i < genParticles->size(); ++ i) {
        const reco::Candidate & p = (*genParticles)[i];
        int id = p.pdgId();
        if (id == 21) continue; // skip gluons  
         
        if (p.numberOfMothers() == 2 && i < 10) {
            if (abs(id) == 6 ){
                if ( final_state[HSTOPF] == NULL ) {
                    final_state[HSTOPF] = & p;
                    if (DEBUG) printCandidate(p);

                }
            }else if (abs(id) == 5){
                if ( final_state[HSB] == NULL ) {
                    final_state[HSB] = & p;
                    if (DEBUG) printCandidate(p);
                }
            }else {
                if (final_state[HSRECOIL] == NULL) {
                    final_state[HSRECOIL] = & p;
                    if (DEBUG) printCandidate(p);
                }
            }
        }
        
        if ( final_state[HSTOPF] != NULL && final_state[TOPWF] == NULL && final_state[TOPB] == NULL){
            if (DEBUG) cout << "!top is found\n";
            if (DEBUG) printCandidate(*final_state[HSTOPF]);
            final_state[HSTOPL]=final_state[HSTOPF];
            while (true){
                for (size_t j=0; j < final_state[HSTOPL]->numberOfDaughters(); j++){
                    cout << "*";
                    if (DEBUG) printCandidate(*final_state[HSTOPL]->daughter(j));
                    if ( abs(final_state[HSTOPL]->daughter(j)->pdgId()) == 6){
                        final_state[HSTOPL]=final_state[HSTOPL]->daughter(j);
                    }else{
                        if ( abs(final_state[HSTOPL]->daughter(j)->pdgId()) == 24 && final_state[TOPWF] == NULL){
                            if (DEBUG) cout << "!found W\n";
                            final_state[TOPWF]=final_state[HSTOPL]->daughter(j);
                            if (DEBUG) printCandidate(*final_state[TOPWF]);
                        } else if ( abs(final_state[HSTOPL]->daughter(j)->pdgId()) == 5 && final_state[TOPB] == NULL){
                            if (DEBUG) cout << "!found b\n";
                            final_state[TOPB]=final_state[HSTOPL]->daughter(j);
                            if (DEBUG) printCandidate(*final_state[TOPB]);
                        }
                    }
                }
                if (final_state[TOPWF] != NULL && final_state[TOPB] != NULL) {
                    if (DEBUG) cout << "top decay study complete\n";
                    break;
                }
            }
        }
        
        if ( final_state[TOPWF] != NULL && final_state[WL] == NULL && final_state[WNU] == NULL){
            if (DEBUG) cout << "studying W decay\n";
            if (DEBUG) printCandidate(*final_state[TOPWF]);
            final_state[TOPWL]=final_state[TOPWF];
            while (true){
                for (size_t j=0; j < final_state[TOPWL]->numberOfDaughters(); j++){
                    if (DEBUG) cout << "*"; if (DEBUG) printCandidate(*final_state[TOPWL]->daughter(j));
                    if ( abs(final_state[TOPWL]->daughter(j)->pdgId()) == 24){
                        final_state[TOPWL]=final_state[TOPWL]->daughter(j);
                    }else{
                        int idg = abs(final_state[TOPWL]->daughter(j)->pdgId());
                        if (  (idg == 11 || idg == 13) && final_state[WL] == NULL){
                            if (DEBUG) cout << "!found lepton\n";
                            final_state[WL]=final_state[TOPWL]->daughter(j);
                            if (DEBUG) printCandidate(*final_state[WL]);
                        } else if ( (idg == 12 || idg == 14) && final_state[WNU] == NULL){
                            if (DEBUG) cout << "!found neutrino\n";
                            final_state[WNU]=final_state[TOPWL]->daughter(j);
                            if (DEBUG) printCandidate(*final_state[WNU]);
                        } else if ( (idg == 13 || idg == 15) ){ // tau event
                            if (DEBUG) cout << "tau event, skipping\n";
                             ++nevttau;
                            return;
                        }
                    }
                }
                if (final_state[WL] != NULL && final_state[WNU] != NULL) {
                    if (DEBUG) cout << "W decay study analysis is now complete\n";
                    break;
                }
            }
        }
    }    
    
    // Make sure all final state particles have been found
    assert(final_state[HSTOPF] !=NULL && final_state[HSB] !=NULL && final_state[HSRECOIL] !=NULL
            && final_state[TOPB]!=NULL && final_state[TOPWF] !=NULL
            && final_state[WNU] !=NULL && final_state[WL] !=NULL );
    
    assert(abs(final_state[WL]->pdgId()) == 11 || abs(final_state[WL]->pdgId()) == 13 ); // lepton (e/mu) check
    assert(abs(final_state[WNU]->pdgId()) == 12 || abs(final_state[WNU]->pdgId()) == 14 ); // lepton (nue/numu) check
    //cout << fabs(getMass2(final_state[WNU], final_state[WL]) - final_state[TOPWF]->mass()*final_state[TOPWF]->mass()) << endl;
    assert( fabs(getMass2(final_state[WNU], final_state[WL]) - final_state[TOPWL]->mass()*final_state[TOPWL]->mass()) < 0.5); // W mass check
    //cout << fabs(getMass2(final_state[TOPWF], final_state[TOPB]) - final_state[HSTOPL]->mass()*final_state[HSTOPL]->mass()) << endl;
    assert( fabs(getMass2(final_state[TOPWF], final_state[TOPB]) - final_state[HSTOPL]->mass()*final_state[HSTOPL]->mass()) < 0.5); // top mass check

    histosF["TopPT"]->Fill(final_state[HSTOPF]->pt(), weightsign);
    histosF["TopETA"]->Fill(final_state[HSTOPF]->eta(), weightsign);
    histosF["BbarPT"]->Fill(final_state[HSB]->pt(), weightsign);
    histosF["BbarETA"]->Fill(final_state[HSB]->eta(), weightsign);
    histosF["TagJetPT"]->Fill(final_state[HSRECOIL]->pt(), weightsign);
    histosF["TagJetETA"]->Fill(final_state[HSRECOIL]->eta(), weightsign);
    histosF["bTopPT"]->Fill(final_state[TOPB]->pt(), weightsign);
    histosF["bTopETA"]->Fill(final_state[TOPB]->eta(), weightsign);
    histosF["W-PT"]->Fill(final_state[TOPWF]->pt(), weightsign);
    histosF["W-ETA"]->Fill(final_state[TOPWF]->eta(), weightsign);
    histosF["lepPT"]->Fill(final_state[WL]->pt(), weightsign);
    histosF["lepETA"]->Fill(final_state[WL]->eta(), weightsign);
    histosF["nuPT"]->Fill(final_state[WNU]->pt(), weightsign);
    histosF["nuETA"]->Fill(final_state[WNU]->eta(), weightsign);
    histosF["lTopPT"]->Fill(final_state[HSTOPL]->pt(), weightsign);
    histosF["lTopETA"]->Fill(final_state[HSTOPL]->eta(), weightsign);
    /*histosF["reTm"]->Fill(final_state[]->(), weightsign);
    histosF["tTm"]->Fill(final_state[]->(), weightsign);
    histosF["Tm"]->Fill(final_state[]->(), weightsign);
    histosF["WRm"]->Fill(final_state[]->(), weightsign);
    histosF["rWm"]->Fill(final_state[]->(), weightsign);
    histosF["Wm"]->Fill(final_state[]->(), weightsign);
    histosF["wldeltaeta"]->Fill(final_state[]->(), weightsign);
    histosF["wldeltaphi"]->Fill(final_state[]->(), weightsign);
    histosF["bbartdeltaeta"]->Fill(final_state[]->(), weightsign);
    histosF["bbartdeltaphi"]->Fill(final_state[]->(), weightsign);
    histosF["tagtdeltaeta"]->Fill(final_state[]->(), weightsign);
    histosF["tagtdeltaphi"]->Fill(final_state[]->(), weightsign);
    histosF["Wnuedeltaeta"]->Fill(final_state[]->(), weightsign);
    histosF["Wnuedeltaphi"]->Fill(final_state[]->(), weightsign);
    histosF["ltWdeltaeta"]->Fill(final_state[]->(), weightsign);
    histosF["ltWdeltaphi"]->Fill(final_state[]->(), weightsign);
    histosF["ltBdeltaeta"]->Fill(final_state[]->(), weightsign);
    histosF["ltBdeltaphi"]->Fill(final_state[]->(), weightsign);
    histosF["lepCutPt"]->Fill(final_state[]->(), weightsign);
    histosF["lepCutEta"]->Fill(final_state[]->(), weightsign);
   */
}