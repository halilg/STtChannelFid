#include "TopPhysics/STtChannelFid/interface/STtChannelFid.h"



#define FSSIZE    10   // size of MyFinalState
enum MyFinalState {HSTOPF, HSTOPL, HSB, HSRECOIL, TOPB, TOPWF, TOPWL, WL, WNU};


//const reco::Candidate *
//STtChannelFid::getFinalState(const edm::Event& iEvent, const edm::EventSetup& iSetup)
//{
//    using namespace std;
//    const reco::Candidate * final_state[FSSIZE];
//    for (size_t i = 0; i<FSSIZE; i++) final_state[i] = NULL;
//    return final_state;
//}

void
STtChannelFid::analyzeGEN(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace std;
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
       
    std::cout << ngenjets << ", weight: " << weightsign << std::endl;
   
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
//        int st = p.status();
        if (id == 21) continue; // skip gluons  
         
        if (p.numberOfMothers() == 2 && i < 10) {
            if (abs(id) == 6 ){
                if ( final_state[HSTOPF] == NULL ) {
                    final_state[HSTOPF] = & p;
                    printCandidate(p);

                }
            }else if (abs(id) == 5){
                if ( final_state[HSB] == NULL ) {
                    final_state[HSB] = & p;
                    printCandidate(p);
                }
            }else {
                if (final_state[HSRECOIL] == NULL) {
                    final_state[HSRECOIL] = & p;
                    printCandidate(p);
                }
            }
        }
        
        if ( final_state[HSTOPF] != NULL && final_state[TOPWF] == NULL && final_state[TOPB] == NULL){
            cout << "!top is found\n";
            printCandidate(*final_state[HSTOPF]);
            final_state[HSTOPL]=final_state[HSTOPF];
            while (true){
                for (size_t j=0; j < final_state[HSTOPL]->numberOfDaughters(); j++){
                    cout << "*";
                    printCandidate(*final_state[HSTOPL]->daughter(j));
                    if ( abs(final_state[HSTOPL]->daughter(j)->pdgId()) == 6){
                        final_state[HSTOPL]=final_state[HSTOPL]->daughter(j);
                    }else{
                        if ( abs(final_state[HSTOPL]->daughter(j)->pdgId()) == 24 && final_state[TOPWF] == NULL){
                            cout << "!found W\n";
                            final_state[TOPWF]=final_state[HSTOPL]->daughter(j);
                            printCandidate(*final_state[TOPWF]);
                        } else if ( abs(final_state[HSTOPL]->daughter(j)->pdgId()) == 5 && final_state[TOPB] == NULL){
                            cout << "!found b\n";
                            final_state[TOPB]=final_state[HSTOPL]->daughter(j);
                            printCandidate(*final_state[TOPB]);
                        }
                    }
                }
                if (final_state[TOPWF] != NULL && final_state[TOPB] != NULL) {
                    cout << "top decay study complete\n";
                    break;
                }
            }
        }
        
        if ( final_state[TOPWF] != NULL && final_state[WL] == NULL && final_state[WNU] == NULL){
            cout << "studying W decay\n";
            printCandidate(*final_state[TOPWF]);
            final_state[TOPWL]=final_state[TOPWF];
            while (true){
                for (size_t j=0; j < final_state[TOPWL]->numberOfDaughters(); j++){
                    cout << "*"; printCandidate(*final_state[TOPWL]->daughter(j));
                    if ( abs(final_state[TOPWL]->daughter(j)->pdgId()) == 24){
                        final_state[TOPWL]=final_state[TOPWL]->daughter(j);
                    }else{
                        int idg = abs(final_state[TOPWL]->daughter(j)->pdgId());
                        if (  (idg == 11 || idg == 13) && final_state[WL] == NULL){
                            cout << "!found lepton\n";
                            final_state[WL]=final_state[TOPWL]->daughter(j);
                            printCandidate(*final_state[WL]);
                        } else if ( (idg == 12 || idg == 14) && final_state[WNU] == NULL){
                            cout << "!found neutrino\n";
                            final_state[WNU]=final_state[TOPWL]->daughter(j);
                            printCandidate(*final_state[WNU]);
                        } else if ( (idg == 13 || idg == 15) ){ // tau event
                            cout << "tau event, skipping\n";
                             ++nevttau;
                            return;
                        }
                    }
                }
                if (final_state[WL] != NULL && final_state[WNU] != NULL) {
                    cout << "W decay study analysis is now complete\n";
                    break;
                }
            }
        }
        
        /*
        if ( abs(id)==24 && abs(p.mother()->pdgId()) == 6 ){
            cout << "found W\n";
            break;
            final_state[TOPWF]= & p;
            printCandidate(p);
            if (p.numberOfDaughters() == 1){
                final_state[WL]=p.daughter(0)->daughter(0);
                final_state[WNU]=p.daughter(0)->daughter(1);
            }else if (p.numberOfDaughters() == 2){
                final_state[WL]=p.daughter(0);
                final_state[WNU]=p.daughter(1);
            }
            cout << "W decay:" << pdg::particleName(final_state[WL]->pdgId()) << endl;
            printCandidate(*final_state[WL]);
            cout << "W decay:" << pdg::particleName(final_state[WNU]->pdgId()) << endl;
            printCandidate(*final_state[WNU]);
        }*/
    }
    /*
        if ( abs(id)==5 && abs(p.mother()->pdgId()) == 6 ){
            cout << "found b\n";
            final_state[TOPB]= & p;
            printCandidate(p);
        }
    */
    
    // Make sure everything has been found
    assert(final_state[HSTOPF] !=NULL && final_state[HSB] !=NULL && final_state[HSRECOIL] !=NULL
            && final_state[TOPB]!=NULL && final_state[TOPWF] !=NULL
            && final_state[WNU] !=NULL && final_state[WL] !=NULL );
    
    assert(abs(final_state[WL]->pdgId()) == 11 || abs(final_state[WL]->pdgId()) == 13 ); // lepton (e/mu) check
    assert(abs(final_state[WNU]->pdgId()) == 12 || abs(final_state[WNU]->pdgId()) == 14 ); // lepton (nue/numu) check
    cout << fabs(getMass2(final_state[WNU], final_state[WL]) - final_state[TOPWF]->mass()*final_state[TOPWF]->mass()) << endl;
    assert( fabs(getMass2(final_state[WNU], final_state[WL]) - final_state[TOPWL]->mass()*final_state[TOPWL]->mass()) < 0.5); // W mass check
    cout << fabs(getMass2(final_state[TOPWF], final_state[TOPB]) - final_state[HSTOPL]->mass()*final_state[HSTOPL]->mass()) << endl;
    assert( fabs(getMass2(final_state[TOPWF], final_state[TOPB]) - final_state[HSTOPL]->mass()*final_state[HSTOPL]->mass()) < 0.5); // top mass check

    histosF["TopPT"]->Fill(0.0, weightsign);
    histosF["TopETA"]->Fill(0.0, weightsign);
    histosF["BbarPT"]->Fill(0.0, weightsign);
    histosF["BbarETA"]->Fill(0.0, weightsign);
    histosF["TagJetPT"]->Fill(0.0, weightsign);
    histosF["TagJetETA"]->Fill(0.0, weightsign);
    histosF["bTopPT"]->Fill(0.0, weightsign);
    histosF["bTopETA"]->Fill(0.0, weightsign);
    histosF["W-PT"]->Fill(0.0, weightsign);
    histosF["W-ETA"]->Fill(0.0, weightsign);
    histosF["lepPT"]->Fill(0.0, weightsign);
    histosF["lepETA"]->Fill(0.0, weightsign);
    histosF["nuPT"]->Fill(0.0, weightsign);
    histosF["nuETA"]->Fill(0.0, weightsign);
    histosF["lTopPT"]->Fill(0.0, weightsign);
    histosF["lTopETA"]->Fill(0.0, weightsign);
    histosF["reTm"]->Fill(0.0, weightsign);
    histosF["tTm"]->Fill(0.0, weightsign);
    histosF["Tm"]->Fill(0.0, weightsign);
    histosF["WRm"]->Fill(0.0, weightsign);
    histosF["rWm"]->Fill(0.0, weightsign);
    histosF["Wm"]->Fill(0.0, weightsign);
    histosF["wldeltaeta"]->Fill(0.0, weightsign);
    histosF["wldeltaphi"]->Fill(0.0, weightsign);
    histosF["bbartdeltaeta"]->Fill(0.0, weightsign);
    histosF["bbartdeltaphi"]->Fill(0.0, weightsign);
    histosF["tagtdeltaeta"]->Fill(0.0, weightsign);
    histosF["tagtdeltaphi"]->Fill(0.0, weightsign);
    histosF["Wnuedeltaeta"]->Fill(0.0, weightsign);
    histosF["Wnuedeltaphi"]->Fill(0.0, weightsign);
    histosF["ltWdeltaeta"]->Fill(0.0, weightsign);
    histosF["ltWdeltaphi"]->Fill(0.0, weightsign);
    histosF["ltBdeltaeta"]->Fill(0.0, weightsign);
    histosF["ltBdeltaphi"]->Fill(0.0, weightsign);
    histosF["lepCutPt"]->Fill(0.0, weightsign);
    histosF["lepCutEta"]->Fill(0.0, weightsign);
   
}