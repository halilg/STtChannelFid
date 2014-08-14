#include "TopPhysics/STtChannelFid/interface/STtChannelFid.h"

void STtChannelFid::book_histograms(){
    edm::Service<TFileService> fs;
    //histosD["pt"] = fs->make<TH1D>( "pt"  , "p_{t}", 100,  0., 100. );
    histosF["TopPT"] = fs->make<TH1F>("TopPT","TOP Pt;P\\_{t} (GeV);Events/2GeV",150,0,300) ;
    histosF["TopETA"] = fs->make<TH1F>("TopETA","TOP eta; #eta;Events",60,0,6) ;
    histosF["BbarPT"] = fs->make<TH1F>("BbarPT","\\_${b}$ Pt;P\\_{t} (GeV);Events/2GeV",100,0,200) ;
    histosF["BbarETA"] = fs->make<TH1F>("BbarETA","\\_${b}$ eta; #eta;Events",60,0,6) ;
    histosF["TagJetPT"] = fs->make<TH1F>("TagJetPT","Tagging Jet Pt;P\\_{t} (GeV);Events/2GeV",100,0,200) ;
    histosF["TagJetETA"] = fs->make<TH1F>("TagJetETA","Tagging Jet eta; #eta;Events",60,0,6) ;
    histosF["bTopPT"] = fs->make<TH1F>("bTopPT","B Pt;P\\_{t} (GeV);Arbitrary Units",100,0,200) ;
    histosF["bTopETA"] = fs->make<TH1F>("bTopETA","B Eta; #eta;Arbitrary Units",60,0,6) ;
    histosF["W-PT"] = fs->make<TH1F>("W-PT","W Pt;P\\_{t} (GeV);Arbitrary Units",150,0,300) ;
    histosF["W-ETA"] = fs->make<TH1F>("W-ETA","W-Boson eta; #eta;Arbitrary Units",60,0,6) ;
    histosF["lepPT"] = fs->make<TH1F>("lepPT","Lepton Pt;P\\_{t} (GeV);Events/2GeV",100,0,200) ;
    histosF["lepETA"] = fs->make<TH1F>("lepETA","Lepton eta; #eta;Events",60,0,6) ;
    histosF["nuPT"] = fs->make<TH1F>("nuPT","Neutrino Pt;P\\_{t} (GeV);Events/2GeV",100,0,200);
    histosF["nuETA"] = fs->make<TH1F>("nuETA","Neutrino eta; #eta;Events",60,0,6);
    histosF["lTopPT"] = fs->make<TH1F>("lTopPT","Last Top Pt;P\\_{t} (GeV);Events/2GeV",150,0,300);
    histosF["lTopETA"] = fs->make<TH1F>("lTopETA","Last Top eta; #eta;Events",60,-6,6);
    histosF["reTm"] = fs->make<TH1F>("reTm","Reconstructed Top Mass ; Mass (GeV);Events/0.5GeV",100,150,200);
    histosF["tTm"] = fs->make<TH1F>("tTm","Reconstructed Top Mass from its Energy Momentum; Mass (GeV);Events/0.5GeV",100,150,200);
    histosF["Tm"] = fs->make<TH1F>("Tm","Real Top Mass; Mass (GeV);Events/0.5GeV",100,150,200);
    histosF["WRm"] = fs->make<TH1F>("WRm","Reconstructed W Mass ; Mass (GeV);Events/0.5GeV",160,40,120);
    histosF["rWm"] = fs->make<TH1F>("rWm","Reconstructed W Mass ; Mass (GeV);Events/0.5GeV",160,40,120);
    histosF["Wm"] = fs->make<TH1F>("Wm","Real W Mass; Mass (GeV);Events/0.5GeV",160,40,120);
    histosF["genMetTrue"] = fs->make<TH1F>("genMetTrue","Missing ET (GEN);E\\_{t}MISS (GeV);Events/2GeV",100,0,200) ;
    
    histosF["wldeltaeta"] = fs->make<TH1F>("wldeltaeta","W-lepton Delta Eta; Delta Eta (rad);Events",50,0,5);
    histosF["wldeltaphi"] = fs->make<TH1F>("wldeltaphi","W-lepton Delta Phi; Delta Phi (rad);Events",50,0,5);
    histosF["bbartdeltaeta"] = fs->make<TH1F>("bbartdeltaeta","BBar-Top Delta Eta; Delta Eta (rad);Events",50,0,5);
    histosF["bbartdeltaphi"] = fs->make<TH1F>("bbartdeltaphi","BBar-Top Phi; Delta Phi (rad);Events",50,0,5);
    histosF["tagtdeltaeta"] = fs->make<TH1F>("tagtdeltaeta","Tag-Top Delta Eta; Delta Eta (rad);Events",50,0,5);
    histosF["tagtdeltaphi"] = fs->make<TH1F>("tagtdeltaphi","Tag-Top Delta Phi; Delta Phi (rad);Events",50,0,5);
    histosF["Wnuedeltaeta"] = fs->make<TH1F>("Wnuedeltaeta","W-Neutrino Delta Eta; Delta Eta (rad);Events",50,0,5);
    histosF["Wnuedeltaphi"] = fs->make<TH1F>("Wnuedeltaphi","W-Neutrino Delta Phi; Delta Phi (rad);Events",50,0,5);
    histosF["ltWdeltaeta"] = fs->make<TH1F>("ltWdeltaeta","Last Top - W Delta Eta; Delta Eta (rad);Events",50,0,5);
    histosF["ltWdeltaphi"] = fs->make<TH1F>("ltWdeltaphi","Last Top - W Delta Phi; Delta Phi (rad);Events",50,0,5);
    histosF["ltBdeltaeta"] = fs->make<TH1F>("ltBdeltaeta","Last Top - B Delta Eta; Delta Eta (rad);Events",50,0,5);
    histosF["ltBdeltaphi"] = fs->make<TH1F>("ltBdeltaphi","Last Top - B Delta Phi; Delta Phi (rad);Events",50,0,5);
    histosF["lepCutPt"] = fs->make<TH1F>("lepCutPt","lepCutPt; P\\_{t};Events",250,0,500);
    histosF["lepCutEta"] = fs->make<TH1F>("lepCutEta","lepCutEta; #eta ;Events",160,-8,8);
}