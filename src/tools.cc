#include "TopPhysics/STtChannelFid/interface/STtChannelFid.h"
#include <iostream>

void printCandidate(const reco::Candidate & p){
    using namespace std;
    cout.precision(4);
    cout << "   pdg:"      << setw(12) << pdg::particleName(p.pdgId())
         << " ("           << setw(6)  << p.pdgId() << ")"
         << " - status:"   << setw(2)  << p.status()
         << " - #mothers:" << setw(1)  << p.numberOfMothers()
         << " - #daug..s:" << setw(2)  << p.numberOfDaughters()
         << " - pt (GeV):"       << setw(10)  << p.pt()
         << " - eta:"      << setw(10)  << p.eta()
         << " - mass (GeV):"     << setw(10)  << p.mass()
                     << std::endl;
}

double STtChannelFid::getMass2(const reco::Candidate * p1, const reco::Candidate * p2){
    return (p1->energy() + p2->energy())*(p1->energy() + p2->energy())
              - ( p1->px() + p2->px() ) * ( p1->px() + p2->px() )
              - ( p1->py() + p2->py() ) * ( p1->py() + p2->py() )
              - ( p1->pz() + p2->pz() ) * ( p1->pz() + p2->pz() );
}