#define PBClass_cxx
#include "PBClass.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "TString.h"
#include "TEfficiency.h"
#include "math.h"
#include <iostream>
#include <vector>
using namespace std;

class MyLorentzVector : public TLorentzVector
{ 
    public: 
    Bool_t m_IsBTagged, m_PassedSelection;
    string m_Tag; 
    float m_Charge;
    MyLorentzVector():m_IsBTagged(0), m_PassedSelection(0), m_Tag(""), m_Charge(999) // MyLorentzVector :: MyLorentzVector():IsBTagged(0), IsOk(5), Bla(41)
    {
    }

    void SetIsBTagged(bool a) 
    { 
       m_IsBTagged = a; 
    }

    Bool_t GetIsBTagged() 
    { 
       return m_IsBTagged; 
    }

    void SetPassedSelection(bool a) 
    { 
       m_PassedSelection = a; 
    }

    Bool_t GetPassedSelection() 
    { 
       return m_PassedSelection; 
    }

    void SetTag(string a) 
    { 
       m_Tag = a; 
    }

    string GetTag() 
    { 
       return m_Tag; 
    }

    void SetCharge(float a) 
    { 
       m_Charge = a; 
    }

    float GetCharge() 
    { 
       return m_Charge; 
    }
}; 

class Event 
{ 
    public: 
    MyLorentzVector Lepton, Electron1, Electron2, Muon1, Muon2, Tauon1, Tauon2, WHadron, WLepton, BJet1, BJet2, Jet3, Jet4, PseudoTop, LeptonPseudotop, PseudoTopPair, Neutrino1, Neutrino2;
    bool m_Lepton, m_Electron1, m_Electron2, m_Muon1, m_Muon2, m_Tauon1, m_Tauon2, m_WHadron, m_WLepton, m_BJet1, m_BJet2, m_Jet3, m_Jet4, m_PseudoTop, m_LeptonPseudotop, m_PseudoTopPair, m_Neutrino1, m_Neutrino2;
    bool m_PreSelected, m_FinalSelected;

    Event():m_PreSelected(false), m_FinalSelected(false),m_Lepton(false), m_Electron1(false), m_Electron2(false), m_Muon1(false), m_Muon2(false), m_Tauon1(false), m_Tauon2(false), m_WHadron(false), m_WLepton(false), m_BJet1(false), m_BJet2(false), m_PseudoTop(false), m_LeptonPseudotop(false), m_PseudoTopPair(false), m_Neutrino1(false), m_Neutrino2(false) {
    }

    void Setm_PreSelected(bool a) 
    { 
       m_PreSelected = a; 
    }

    bool Getm_PreSelected()
    {
       return m_PreSelected;
    }

    void Setm_FinalSelected(bool a) 
     { 
        m_FinalSelected = a; 
     }
 
     bool Getm_FinalSelected()
     {
        return m_PreSelected;
     }

    void SetLepton(MyLorentzVector a) 
    { 
       Lepton = a; 
       m_Lepton = true;
    }

    MyLorentzVector GetLepton()
    {
       return Lepton;
    }


    void SetElectron1(MyLorentzVector a) 
    { 
       Electron1 = a; 
       m_Electron1 = true;
    }

    MyLorentzVector GetElectron1()
    {
       return Electron1;
    }

    void SetElectron2(MyLorentzVector a) 
     { 
        Electron2 = a; 
        m_Electron2 = true;
     }
     MyLorentzVector GetElectron2()
     {
        return Electron2;
     }
    
    void SetMuon1(MyLorentzVector a) 
    { 
       Muon1 = a; 
       m_Muon1 = true;
    }
    MyLorentzVector GetMuon1()
    {
       return Muon1;
    }
    void SetMuon2(MyLorentzVector a) 
    { 
       Muon2 = a; 
       m_Muon2 = true;
    }
    MyLorentzVector GetMuon2()
    {
       return Muon2;
    }
    void SetTauon1(MyLorentzVector a) 
    { 
       Tauon1 = a; 
       m_Tauon1 = true;
    }
    MyLorentzVector GetTauon1()
    {
       return Tauon1;
    }
    void SetTauon2(MyLorentzVector a) 
    { 
       Tauon2 = a; 
       m_Tauon2 = true;
    }
    MyLorentzVector GetTauon2()
    {
       return Tauon2;
    }
    void SetWHadron(MyLorentzVector a) 
    { 
       WHadron = a; 
       m_WHadron = true;
    }
    MyLorentzVector GetWHadron()
    {
       return WHadron;
    }
    void SetWLepton(MyLorentzVector a) 
    { 
       WLepton = a; 
       m_WLepton = true;
    }
    MyLorentzVector GetWLepton()
    {
       return WLepton;
    }

    void SetBJet1(MyLorentzVector a) 
    { 
       BJet1 = a; 
       m_BJet1 = true;
    }
    MyLorentzVector GetBJet1()
    {
       return BJet1;
    }
    void SetBJet2(MyLorentzVector a) 
    { 
       BJet2 = a; 
       m_BJet2 = true;
    }
    MyLorentzVector GetBJet2()
    {
       return BJet2;
    }

    void SetJet3(MyLorentzVector a) 
    { 
       Jet3 = a; 
       m_Jet3 = true;
    }
    MyLorentzVector GetJet3()
    {
       return Jet3;
    }
    void SetJet4(MyLorentzVector a) 
    { 
       Jet4 = a; 
       m_Jet4 = true;
    }
    MyLorentzVector GetJet4()
    {
       return Jet4;
    }

    void SetPseudoTop(MyLorentzVector a) 
    { 
       PseudoTop = a; 
       m_PseudoTop = true;
    }
    MyLorentzVector GetPseudoTop()
    {
       return PseudoTop;
    }
    void SetLeptonPseudotop(MyLorentzVector a) 
    { 
       LeptonPseudotop = a; 
       m_LeptonPseudotop = true;
    }
    MyLorentzVector GetLeptonPseudotop()
    {
       return LeptonPseudotop;
    }

    void SetPseudoTopPair(MyLorentzVector a) 
    { 
       PseudoTopPair = a; 
       m_PseudoTopPair = true;
    }
    MyLorentzVector GetPseudoTopPair()
    {
       return PseudoTopPair;
    }

   void SetNeutrino1(MyLorentzVector a) 
    { 
       Neutrino1 = a; 
       m_Neutrino1 = true;
    }
    MyLorentzVector GetNeutrino1()
    {
       return Neutrino1;
    }

   void SetNeutrino2(MyLorentzVector a) 
    { 
       Neutrino2 = a; 
       m_Neutrino2 = true;
    }
    MyLorentzVector GetNeutrino2()
    {
       return Neutrino2;
    }

    void Print()
    {
       cout << "----------- EVENT PRINT -------------" << endl;
       cout << "Electron1: " << "Pt: " << Electron1.Pt() << ", Mass: " << Electron1.M() << ", charge: "<< Electron1.GetCharge() << " ";
       Electron1.Print();
       cout << "Electron2: " << "Pt: " << Electron2.Pt() << ", Mass: " << Electron2.M() << ", charge: "<< Electron2.GetCharge() << " ";
       Electron2.Print();
       cout << "Muon1: " << "Pt: " << Muon1.Pt() << ", Mass: " << Muon1.M() << ", charge: "<< Muon1.GetCharge() << " ";
       Muon1.Print();
       cout << "Muon2: " << "Pt: " << Muon2.Pt() << ", Mass: " << Muon2.M() << ", charge: "<< Muon2.GetCharge() << " ";
       Muon2.Print();
       //cout << "Tauon1: ";
       //Tauon1.Print();
       //cout << "Tauon2: ";
       //Tauon2.Print();
       cout << "BJet1: " << "Pt: " << BJet1.Pt() << ", Mass: " << BJet1.M() << ", charge: "<< BJet1.GetCharge()<< ", b-tag: "<< BJet1.GetIsBTagged() << " ";
       BJet1.Print();
       cout << "BJet2: " << "Pt: " << BJet2.Pt() << ", Mass: " << BJet2.M() << ", charge: "<< BJet2.GetCharge()<< ", b-tag: "<< BJet2.GetIsBTagged() << " ";
       BJet2.Print();
       cout << "Jet3: " << "Pt: " << Jet3.Pt() << ", Mass: " << Jet3.M() << ", charge: "<< Jet3.GetCharge()<< ", b-tag: "<< Jet3.GetIsBTagged() << " ";
       Jet3.Print();
       cout << "Jet4: " << "Pt: " << Jet4.Pt() << ", Mass: " << Jet4.M() << ", charge: "<< Jet4.GetCharge()<< ", b-tag: "<< Jet4.GetIsBTagged() << " ";
       Jet4.Print();
       cout << "Lepton: " << "Pt: " << Lepton.Pt() << ", Mass: " << Lepton.M() << ", charge: "<< Lepton.GetCharge() << " ";
       Lepton.Print();
       cout << "W: " << "Pt: " << WHadron.Pt() << ", Mass: " << WHadron.M() << ", charge: "<< WHadron.GetCharge() << " ";
       WHadron.Print();
       cout << "PseudoTop: " << "Pt: " << PseudoTop.Pt() << ", Mass: " << PseudoTop.M() << ", charge: "<< PseudoTop.GetCharge() << " ";
       PseudoTop.Print();
       cout << "LeptonPseudotop: " << "Pt: " << LeptonPseudotop.Pt() << ", Mass: " << LeptonPseudotop.M() << ", charge: "<< LeptonPseudotop.GetCharge() << " ";
       LeptonPseudotop.Print();
       cout << "PseudoTopPair: " << "Pt: " << PseudoTopPair.Pt() << ", Mass: " << PseudoTopPair.M() << ", charge: "<< PseudoTopPair.GetCharge() << " ";
       PseudoTopPair.Print();
       cout << "Neutrino1: " << "Pt: " << Neutrino1.Pt() << ", Mass: " << Neutrino1.M() << ", charge: "<< Neutrino1.GetCharge() << " ";
       Neutrino1.Print();
       cout << "Neutrino2: " << "Pt: " << Neutrino2.Pt() << ", Mass: " << Neutrino2.M() << ", charge: "<< Neutrino2.GetCharge() << " ";
       Neutrino2.Print();
    }


}; 

MyLorentzVector MaxLepton(Event TestEvent){
   if ((TestEvent.Electron1.Pt() > TestEvent.Electron2.Pt()) && (TestEvent.Electron1.Pt() > TestEvent.Muon1.Pt()) && (TestEvent.Electron1.Pt() > TestEvent.Muon2.Pt())){
      return TestEvent.Electron1;
   }
   if ((TestEvent.Electron2.Pt() > TestEvent.Electron1.Pt()) && (TestEvent.Electron2.Pt() > TestEvent.Muon1.Pt()) && (TestEvent.Electron2.Pt() > TestEvent.Muon2.Pt())){
      return TestEvent.Electron2;
   }
   if ((TestEvent.Muon1.Pt() > TestEvent.Electron1.Pt()) && (TestEvent.Muon1.Pt() > TestEvent.Electron2.Pt()) && (TestEvent.Muon1.Pt() > TestEvent.Muon2.Pt())){
      return TestEvent.Muon1;
   }
   if ((TestEvent.Muon2.Pt() > TestEvent.Electron1.Pt()) && (TestEvent.Muon2.Pt() > TestEvent.Electron2.Pt()) && (TestEvent.Muon2.Pt() > TestEvent.Muon1.Pt())){
      return TestEvent.Muon2;
   } 
   MyLorentzVector a;
   return a;
}

double MinQuadraticEq(double a, double b, double c){
   double D = b*b - 4*a*c;
   if (D >= 0.0){
      double x1 = (-b + sqrt(D))/(2*a);
      double x2 = (-b - sqrt(D))/(2*a);
      double ax1 = abs(x1);
      double ax2 = abs(x2);
      if (ax1 < ax2){
         //cout << x1 << " "<< x2 << " ,returning x1." << endl;
         return x1;

      } else if (ax1 > ax2) {
         //cout << x1 << " "<< x2 << " ,returning x2." << endl;
         return x2;
      } else{
         return -b/(2*a);
         //cout << x1 << " "<< x2 << " ,returning both." << endl;
      }
   } else{
      return -b/(2*a);
      //`double Error = nan("1");
      //return Error;
   }

}


bool CheckPreSelected(Event TestEvent){
   if (((TestEvent.Electron1.GetTag() != "") || (TestEvent.Electron2.GetTag() != "") || (TestEvent.Muon1.GetTag() != "") || (TestEvent.Muon2.GetTag() != "")) && ((TestEvent.BJet1.GetTag() != "") && (TestEvent.BJet2.GetTag() != "") && (TestEvent.Jet3.GetTag() != "") && (TestEvent.Jet4.GetTag() != ""))) {
   //if (((TestEvent.Electron1.GetTag() != "") || (TestEvent.Electron2.GetTag() != "") ) && ((TestEvent.BJet1.GetTag() != "") && (TestEvent.BJet2.GetTag() != "") && (TestEvent.Jet3.GetTag() != "") && (TestEvent.Jet4.GetTag() != ""))) {
      return true;
      }
   else{
      return false;
   }
};

bool CheckPreSelectedLepton(Event TestEvent){
   if ((TestEvent.Electron1.GetTag() != "") || (TestEvent.Electron2.GetTag() != "") || (TestEvent.Muon1.GetTag() != "") || (TestEvent.Muon2.GetTag() != "") ) {
   //if (((TestEvent.Electron1.GetTag() != "") || (TestEvent.Electron2.GetTag() != "") ) && ((TestEvent.BJet1.GetTag() != "") && (TestEvent.BJet2.GetTag() != "") && (TestEvent.Jet3.GetTag() != "") && (TestEvent.Jet4.GetTag() != ""))) {
      return true;
      }
   else{
      return false;
   }
};


float DeltaR(MyLorentzVector a, MyLorentzVector b){
   return a.DeltaR(b);
   //return sqrt((a.Phi() - b.Phi())*(a.Phi() - b.Phi()) + (a.Eta() - b.Eta())*(a.Eta() - b.Eta()));
}

void PBClass::Loop(TString Output, TString Tag)
{
//   In a ROOT session, you can do:
//      root> .L PBClass.C
//      root> PBClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   cout << "SIGN: Start of the function Loop()." << endl;
   if (fChain == 0) return;
   TFile *outfile = new TFile(Output, "recreate");
   
   cout << "Output file is named: " << Output << endl;
   
   //BASIC HISTOGRAMS

   //Detector level
   TDirectory *Reco = outfile->mkdir("Reco");
   Reco->cd();
   TH1D *LjetMulti = new TH1D("LjetMulti", "LjetMulti; Number of large jets; Events", 15, 0, 15);
   TH1D *LjetEta = new TH1D("LjetEta", "LjetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *LjetPhi = new TH1D("LjetPhi", "LjetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *LjetPt = new TH1D("LjetPt", "LjetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *LjetMass = new TH1D("LjetMass", "LjetMass; Mass [GeV]; Events", 500, 0, 1000);
   
   TH1D *JetMulti = new TH1D("JetMulti", "JetMulti; Number of large jets; Events", 15, 0, 15);
   TH1D *JetEta = new TH1D("JetEta", "JetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *JetPhi = new TH1D("JetPhi", "JetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *JetPt = new TH1D("JetPt", "JetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *JetMass = new TH1D("JetMass", "JetMass; Mass [GeV]; Events", 500, 0, 1000);
   
   TH1D *LeadingLjetEta = new TH1D("LeadingLjetEta", "LeadingLjetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *LeadingLjetPhi = new TH1D("LeadingLjetPhi", "LeadingLjetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *LeadingLjetPt = new TH1D("LeadingLjetPt", "LeadingLjetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *LeadingLjetMass = new TH1D("LeadingLjetMass", "LeadingLjetMass; Mass [GeV]; Events", 500, 0, 1000);
   
   TH1D *LeadingJetEta = new TH1D("LeadingJetEta", "LeadingJetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *LeadingJetPhi = new TH1D("LeadingJetPhi", "LeadingJetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *LeadingJetPt = new TH1D("LeadingJetPt", "LeadingJetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *LeadingJetMass = new TH1D("LeadingJetMass", "LeadingJetMass; Mass [GeV]; Events", 500, 0, 1000);

   TH1D *SubLeadingLjetEta = new TH1D("SubLeadingLjetEta", "SubLeadingLjetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *SubLeadingLjetPhi = new TH1D("SubLeadingLjetPhi", "SubLeadingLjetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *SubLeadingLjetPt = new TH1D("SubLeadingLjetPt", "SubLeadingLjetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *SubLeadingLjetMass = new TH1D("SubLeadingLjetMass", "SubLeadingLjetMass; Mass [GeV]; Events", 500, 0, 1000);
   
   TH1D *SubLeadingJetEta = new TH1D("SubLeadingJetEta", "SubLeadingJetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *SubLeadingJetPhi = new TH1D("SubLeadingJetPhi", "SubLeadingJetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *SubLeadingJetPt = new TH1D("SubLeadingJetPt", "SubLeadingJetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *SubLeadingJetMass = new TH1D("SubLeadingJetMass", "SubLeadingJetMass; Mass [GeV]; Events", 500, 0, 1000);

   //electrons
   TH1D *ElectronEta = new TH1D("ElectronEta", "ElectronEta; #eta [-]; Events", 1000, -6.28, 6.28);
   TH1D *ElectronPT = new TH1D("ElectronPT", "ElectronPT; Electron p_{T} [GeV]; Events", 500, 0, 1000);


   //muons
   TH1D *MuonEta = new TH1D("MuonEta", "MuonEta; #eta [-]; Events", 1000, -6.28, 6.28);
   TH1D *MuonPT = new TH1D("MuonPT", "MuonPT; Muon p_{T} [GeV]; Events", 500, 0, 1000);

   // small jets
   TH1D *JetJESEta = new TH1D("JetJESEta", "JetJESEta; #eta [-]; Events", 1000, -6.28, 6.28);
   TH1D *JetJESPT = new TH1D("JetJESPT", "JetJESPT; JetJES p_{T} [GeV]; Events", 500, 0, 1000);

   //Top quarks
   TH1D *TopMass1 = new TH1D("TopMass1", "Hadron Top; Mass [GeV]; Events", 500, 0, 2000);
   TH1D *TopMass2 = new TH1D("TopMass2", "Leptonic Top; Mass [GeV]; Events", 500, 0, 2000);
   TH1D *WMass = new TH1D("WMass", "WMass; Mass [GeV]; Events", 50, 0, 1000);

   //Hitograms of interest
   TH1D *HadTopPt = new TH1D("HadTopPt", "HadTopPt; p_{T}^{t,had} [GeV]; Events", 1000, 0, 800);
   TH1D *HadTopEta = new TH1D("HadTopEta", "HadTopEta; #eta; Events", 1000, -6.28, 6.28);
   TH1D *TopPairPt = new TH1D("TopPairPt", "TopPairPt; p_{T}^{t,#bar{t}} [GeV]; Events", 1000, 0, 300);
   TH1D *TopPairMass = new TH1D("TopPairMass", "TopPairMass; Mass [GeV]; Events", 1000, 100, 2500);
   TH1D *TopPairEta = new TH1D("TopPairEta", "TopPairEta; #eta; Events", 1000, -6.28, 6.28);
   TH1D *TopPairDeltaPhi = new TH1D("TopPairDeltaPhi", "TopPairDeltaPhi; #phi; Events", 100, -6.28, 6.28);
   TH2D *WLeptonVsLeptonPseudoTop = new TH2D("WLeptonVsLeptonPseudoTop", "WLeptonVsLeptonPseudoTop; Mass Lepton Top [GeV]; Mass Lepton W [GeV]", 100, 0 , 500 , 100, 0, 500);
   TH2D *WLeptonVsNeutrinoPt = new TH2D("WLeptonVsNeutrinoPt", "WLeptonVsNeutrinoPt; Neutrino p_{T} [GeV]; Mass Lepton W [GeV]", 100, 0 , 500 , 100, 0, 500);
   TH2D *LeptonPseudoTopVsNeutrinoPt = new TH2D("LeptonPseudoTopVsNeutrinoPt", "LeptonPseudoTopVsNeutrinoPt; Neutrino p_{T} [GeV]; Mass Lepton Top [GeV]", 100, 0 , 500 , 100, 0, 500);
   TH2D *LeptonPseudoTopVsTopPairEta = new TH2D("LeptonPseudoTopVsTopPairEta", "LeptonPseudoTopVsTopPairEta; Lepton top #eta; Top pair #eta", 1000, -6.28, 6.28 , 1000, -6.28, 6.28);
   TH2D *HadronPseudoTopVsTopPairEta = new TH2D("HadronPseudoTopVsTopPairEta", "HadronPseudoTopVsTopPairEta; Hadron top #eta; Top pair #eta", 1000, -6.28, 6.28 , 1000, -6.28, 6.28);
   TH1D *LeptonPseudoTopDeltaMassLeptonW = new TH1D("LeptonPseudoTopDeltaMassLeptonW", "LeptonPseudoTopDeltaMassLeptonW; #Delta m [GeV]; Events", 100, 0, 500);


   TH2D *WHadronVsHadronPseudoTop = new TH2D("WHadronVsHadronPseudoTop", "WHadronVsHadronPseudoTop; Mass Hadron Top [GeV]; Mass Hadron W [GeV]", 100, 0 , 500 , 100, 0, 500);
   TH1D *HadronPseudoTopDeltaMassHadronW = new TH1D("HadronPseudoTopDeltaMassHadronW", "HadronPseudoTopDeltaMassHadronW; #Delta m [GeV]; Events", 100, 0, 500);

   //Particle level
   TDirectory *Particle = outfile->mkdir("Particle");
   Particle->cd();
   TH1D *GenLjetMulti = new TH1D("GenLjetMulti", "GenLjetMulti; Number of large jets; Events", 15, 0, 15);
   TH1D *GenLjetEta = new TH1D("GenLjetEta", "GenLjetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *GenLjetPhi = new TH1D("GenLjetPhi", "GenLjetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *GenLjetPt = new TH1D("GenLjetPt", "GenLjetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *GenLjetMass = new TH1D("GenLjetMass", "GenLjetMass; Mass [GeV]; Events", 500, 0, 1000);
   
   TH1D *GenJetMulti = new TH1D("GenJetMulti", "GenJetMulti; Number of large jets; Events", 15, 0, 15);
   TH1D *GenJetEta = new TH1D("GenJetEta", "GenJetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *GenJetPhi = new TH1D("GenJetPhi", "GenJetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *GenJetPt = new TH1D("GenJetPt", "GenJetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *GenJetMass = new TH1D("GenJetMass", "GenJetMass; Mass [GeV]; Events", 500, 0, 1000);

   TH1D *GenLeadingLjetEta = new TH1D("GenLeadingLjetEta", "GenLeadingLjetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *GenLeadingLjetPhi = new TH1D("GenLeadingLjetPhi", "GenLeadingLjetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *GenLeadingLjetPt = new TH1D("GenLeadingLjetPt", "GenLeadingLjetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *GenLeadingLjetMass = new TH1D("GenLeadingLjetMass", "GenLeadingLjetMass; Mass [GeV]; Events", 500, 0, 1000);
   
   TH1D *GenLeadingJetEta = new TH1D("GenLeadingJetEta", "GenLeadingJetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *GenLeadingJetPhi = new TH1D("GenLeadingJetPhi", "GenLeadingJetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *GenLeadingJetPt = new TH1D("GenLeadingJetPt", "GenLeadingJetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *GenLeadingJetMass = new TH1D("GenLeadingJetMass", "GenLeadingJetMass; Mass [GeV]; Events", 500, 0, 1000);

   TH1D *GenSubLeadingLjetEta = new TH1D("GenSubLeadingLjetEta", "GenSubLeadingLjetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *GenSubLeadingLjetPhi = new TH1D("GenSubLeadingLjetPhi", "GenSubLeadingLjetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *GenSubLeadingLjetPt = new TH1D("GenSubLeadingLjetPt", "GenSubLeadingLjetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *GenSubLeadingLjetMass = new TH1D("GenSubLeadingLjetMass", "GenSubLeadingLjetMass; Mass [GeV]; Events", 500, 0, 1000);
   
   TH1D *GenSubLeadingJetEta = new TH1D("GenSubLeadingJetEta", "GenSubLeadingJetEta; #eta [-]; Events", 100, -6.28, 6.28);
   TH1D *GenSubLeadingJetPhi = new TH1D("GenSubLeadingJetPhi", "GenSubLeadingJetPhi; #phi [-]; Events", 100, -6.28, 6.28);
   TH1D *GenSubLeadingJetPt = new TH1D("GenSubLeadingJetPt", "GenSubLeadingJetPt; p_{T} [GeV]; Events", 500, 0, 1000);
   TH1D *GenSubLeadingJetMass = new TH1D("GenSubLeadingJetMass", "GenSubLeadingJetMass; Mass [GeV]; Events", 500, 0, 1000);

      //electrons
   TH1D *MCElectronEta = new TH1D("MCElectronEta", "MCElectronEta; #eta [-]; Events", 1000, -6.28, 6.28);
   TH1D *MCElectronPT = new TH1D("MCElectronPT", "MCElectronPT; Electron p_{T} [GeV]; Events", 500, 0, 1000);


   //muons
   TH1D *MCMuonEta = new TH1D("MCMuonEta", "MCMuonEta; #eta [-]; Events", 1000, -6.28, 6.28);
   TH1D *MCMuonPT = new TH1D("MCMuonPT", "MCMuonPT; Muon p_{T} [GeV]; Events", 500, 0, 1000);

   // small jets
   TH1D *MCJetJESEta = new TH1D("MCJetJESEta", "MCJetJESEta; #eta [-]; Events", 1000, -6.28, 6.28);
   TH1D *MCJetJESPT = new TH1D("MCJetJESPT", "MCJetJESPT; JetJES p_{T} [GeV]; Events", 500, 0, 1000);

   //Top quarks
   TH1D *MCTopMass1 = new TH1D("MCTopMass1", "MCHadron Top; Mass [GeV]; Events", 500, 0, 2000);
   TH1D *MCTopMass2 = new TH1D("MCTopMass2", "MCLeptonic Top; Mass [GeV]; Events", 500, 0, 2000);
   TH1D *MCWMass = new TH1D("MCWMass", "MCWMass; Mass [GeV]; Events", 50, 0, 1000);

   //Hitograms of interest
   TH1D *MCHadTopPt = new TH1D("MCHadTopPt", "MCHadTopPt; p_{T}^{t,had} [GeV]; Events", 1000, 0, 800);
   TH1D *MCHadTopEta = new TH1D("MCHadTopEta", "MCHadTopEta; #eta; Events", 1000, -6.28, 6.28);
   TH1D *MCTopPairPt = new TH1D("MCTopPairPt", "MCTopPairPt; p_{T}^{t,#bar{t}} [GeV]; Events", 1000, 0, 300);
   TH1D *MCTopPairMass = new TH1D("MCTopPairMass", "MCTopPairMass; Mass [GeV]; Events", 1000, 100, 2500);
   TH1D *MCTopPairEta = new TH1D("MCTopPairEta", "MCTopPairEta; #eta; Events", 1000, -6.28, 6.28);
   TH1D *MCTopPairDeltaPhi = new TH1D("MCTopPairDeltaPhi", "MCTopPairDeltaPhi; #phi; Events", 100, -6.28, 6.28);
   TH2D *MCWLeptonVsLeptonPseudoTop = new TH2D("MCWLeptonVsLeptonPseudoTop", "MCWLeptonVsLeptonPseudoTop; Mass Lepton Top [GeV]; Mass Lepton W [GeV]", 100, 0 , 500 , 100, 0, 500);
   TH2D *MCWLeptonVsNeutrinoPt = new TH2D("MCWLeptonVsNeutrinoPt", "MCWLeptonVsNeutrinoPt; Neutrino p_{T} [GeV]; Mass Lepton W [GeV]", 100, 0 , 500 , 100, 0, 500);
   TH2D *MCLeptonPseudoTopVsNeutrinoPt = new TH2D("MCLeptonPseudoTopVsNeutrinoPt", "MCLeptonPseudoTopVsNeutrinoPt; Neutrino p_{T} [GeV]; Mass Lepton Top [GeV]", 100, 0 , 500 , 100, 0, 500);
   TH2D *MCLeptonPseudoTopVsTopPairEta = new TH2D("MCLeptonPseudoTopVsTopPairEta", "MCLeptonPseudoTopVsTopPairEta; Lepton top #eta; Top pair #eta", 1000, -6.28, 6.28 , 1000, -6.28, 6.28);
   TH2D *MCHadronPseudoTopVsTopPairEta = new TH2D("MCHadronPseudoTopVsTopPairEta", "MCHadronPseudoTopVsTopPairEta; Hadron top #eta; Top pair #eta", 1000, -6.28, 6.28 , 1000, -6.28, 6.28);
   TH1D *MCLeptonPseudoTopDeltaMassLeptonW = new TH1D("MCLeptonPseudoTopDeltaMassLeptonW", "MCLeptonPseudoTopDeltaMassLeptonW; #Delta m [GeV]; Events", 100, 0, 500);


   TH2D *MCWHadronVsHadronPseudoTop = new TH2D("MCWHadronVsHadronPseudoTop", "MCWHadronVsHadronPseudoTop; Mass Hadron Top [GeV]; Mass Hadron W [GeV]", 100, 0 , 500 , 100, 0, 500);
   TH1D *MCHadronPseudoTopDeltaMassHadronW = new TH1D("MCHadronPseudoTopDeltaMassHadronW", "MCHadronPseudoTopDeltaMassHadronW; #Delta m [GeV]; Events", 100, 0, 500);

   // DEFINE MIGRATION MATRICES
   TDirectory *Matrix = outfile->mkdir("Matrix");
   Matrix->cd();
   TH2D *MigraHadTopPt = new TH2D("MigraHadTopPt", "MigraHadTopPt; Detector level p_{T}^{t,had} [GeV]; Particle level p_{T}^{t,had} [GeV]", 1000, 0, 800, 1000, 0, 800);
   TH2D *MigraHadTopEta = new TH2D("MigraHadTopEta", "MigraHadTopEta; Detector level #eta; Particle level #eta", 1000, -6.28, 6.28, 1000, -6.28, 6.28);
   TH2D *MigraTopPairPt = new TH2D("MigraTopPairPt", "MigraTopPairPt; Detector level p_{T}^{t,#bar{t}} [GeV]; Particle level p_{T}^{t,#bar{t}} [GeV]", 1000, 0, 300, 1000, 0, 300);
   TH2D *MigraTopPairMass = new TH2D("MigraTopPairMass", "MigraTopPairMass; Detector level Mass [GeV]; Particle level Mass [GeV]", 1000, 100, 2500, 1000, 100, 2500);
   TH2D *MigraTopPairEta = new TH2D("MigraTopPairEta", "MigraTopPairEta; Detector level #eta; Particle level #eta", 1000, -6.28, 6.28, 1000, -6.28, 6.28);
   
   float Top1_Data_Pt;
   float Top1_Data_Eta;
   float Top1_Data_Phi;
   float Top1_Data_E;
   float Top1_Data_M;

   float Top1_Bjet_Data_Pt;
   float Top1_Bjet_Data_Eta;
   float Top1_Bjet_Data_Phi;
   float Top1_Bjet_Data_E;
   float Top1_Bjet_Data_M;

   float Top1_Wboson_Data_Pt;
   float Top1_Wboson_Data_Eta;
   float Top1_Wboson_Data_Phi;
   float Top1_Wboson_Data_E;
   float Top1_Wboson_Data_M;

   float Top2_Data_Pt;
   float Top2_Data_Eta;
   float Top2_Data_Phi;
   float Top2_Data_E;
   float Top2_Data_M;

   float Top2_Bjet_Data_Pt;
   float Top2_Bjet_Data_Eta;
   float Top2_Bjet_Data_Phi;
   float Top2_Bjet_Data_E;
   float Top2_Bjet_Data_M;

   float Top2_Lepton_Data_Pt;
   float Top2_Lepton_Data_Eta;
   float Top2_Lepton_Data_Phi;
   float Top2_Lepton_Data_E;
   float Top2_Lepton_Data_M;

   float Top2_Neutrino_Data_Pt;
   float Top2_Neutrino_Data_Eta;
   float Top2_Neutrino_Data_Phi;
   float Top2_Neutrino_Data_E;
   float Top2_Neutrino_Data_M;

   float Top1_MC_Pt;
   float Top1_MC_Eta;
   float Top1_MC_Phi;
   float Top1_MC_E;
   float Top1_MC_M;

   float Top1_Bjet_MC_Pt;
   float Top1_Bjet_MC_Eta;
   float Top1_Bjet_MC_Phi;
   float Top1_Bjet_MC_E;
   float Top1_Bjet_MC_M;

   float Top1_Wboson_MC_Pt;
   float Top1_Wboson_MC_Eta;
   float Top1_Wboson_MC_Phi;
   float Top1_Wboson_MC_E;
   float Top1_Wboson_MC_M;
   
   float Top2_MC_Pt;
   float Top2_MC_Eta;
   float Top2_MC_Phi;
   float Top2_MC_E;
   float Top2_MC_M;

   float Top2_Bjet_MC_Pt;
   float Top2_Bjet_MC_Eta;
   float Top2_Bjet_MC_Phi;
   float Top2_Bjet_MC_E;
   float Top2_Bjet_MC_M;

   float Top2_Lepton_MC_Pt;
   float Top2_Lepton_MC_Eta;
   float Top2_Lepton_MC_Phi;
   float Top2_Lepton_MC_E;
   float Top2_Lepton_MC_M;

   float Top2_Neutrino_MC_Pt;
   float Top2_Neutrino_MC_Eta;
   float Top2_Neutrino_MC_Phi;
   float Top2_Neutrino_MC_E;
   float Top2_Neutrino_MC_M;

   float ttbar_Data_Pt;
   float ttbar_Data_Eta;
   float ttbar_Data_Phi;
   float ttbar_Data_E;
   float ttbar_Data_M;

   float ttbar_MC_Pt;
   float ttbar_MC_Eta;
   float ttbar_MC_Phi;
   float ttbar_MC_E;
   float ttbar_MC_M;

   float check_variable1;
   float check_variable2;
   float check_variable3;
   float check_variable4;
   
   int int_Event_size;
   int int_GenLJet_size;
   int int_GenJet_size;
   int int_GenElectron_size;
   int int_GenMuon_size;
   int int_GenTop_size;
   int int_GenPhoton_size;
   int int_GenMissingET_size;
   int int_GenZPrime_size;
   int int_GenW_size;
   int int_GenBhadrons_size;
   int int_Jet_size;
   int int_LJet_size;
   int int_JetJES_size;
   int int_LJetJES_size;
   int int_Electron_size;
   int int_Photon_size;
   int int_Muon_size;
   int int_MissingET_size;
   int int_ScalarHT_size;

   TTree *tree_particle = new TTree("Tops_Particle","TLorenzVecors_of_tops_ljets_particle");
   tree_particle->Branch("Hadronic_Top_Data_Pt", &Top1_Data_Pt, "Top1_Data_Pt/F");
   tree_particle->Branch("Hadronic_Top_Data_Eta", &Top1_Data_Eta, "Top1_Data_Eta/F");
   tree_particle->Branch("Hadronic_Top_Data_Phi", &Top1_Data_Phi, "Top1_Data_Phi/F");
   tree_particle->Branch("Hadronic_Top_Data_E", &Top1_Data_E, "Top1_Data_E/F");
   tree_particle->Branch("Hadronic_Top_Data_M", &Top1_Data_M, "Top1_Data_M/F");

   tree_particle->Branch("Hadronic_Top_Bjet_Data_Pt", &Top1_Bjet_Data_Pt, "Top1_Bjet_Data_Pt/F");
   tree_particle->Branch("Hadronic_Top_Bjet_Data_Eta", &Top1_Bjet_Data_Eta, "Top1_Bjet_Data_Eta/F");
   tree_particle->Branch("Hadronic_Top_Bjet_Data_Phi", &Top1_Bjet_Data_Phi, "Top1_Bjet_Data_Phi/F");
   tree_particle->Branch("Hadronic_Top_Bjet_Data_E", &Top1_Bjet_Data_E, "Top1_Bjet_Data_E/F");
   tree_particle->Branch("Hadronic_Top_Bjet_Data_M", &Top1_Bjet_Data_M, "Top1_Bjet_Data_M/F");

   tree_particle->Branch("Hadronic_Top_Wboson_Data_Pt", &Top1_Wboson_Data_Pt, "Top1_Wboson_Data_Pt/F");
   tree_particle->Branch("Hadronic_Top_Wboson_Data_Eta", &Top1_Wboson_Data_Eta, "Top1_Wboson_Data_Eta/F");
   tree_particle->Branch("Hadronic_Top_Wboson_Data_Phi", &Top1_Wboson_Data_Phi, "Top1_Wboson_Data_Phi/F");
   tree_particle->Branch("Hadronic_Top_Wboson_Data_E", &Top1_Wboson_Data_E, "Top1_Wboson_Data_E/F");
   tree_particle->Branch("Hadronic_Top_Wboson_Data_M", &Top1_Wboson_Data_M, "Top1_Wboson_Data_M/F");

   tree_particle->Branch("Leptonic_Top_Data_Pt", &Top2_Data_Pt, "Top2_Data_Pt/F");
   tree_particle->Branch("Leptonic_Top_Data_Eta", &Top2_Data_Eta, "Top2_Data_Eta/F");
   tree_particle->Branch("Leptonic_Top_Data_Phi", &Top2_Data_Phi, "Top2_Data_Phi/F");
   tree_particle->Branch("Leptonic_Top_Data_E", &Top2_Data_E, "Top2_Data_E/F");
   tree_particle->Branch("Leptonic_Top_Data_M", &Top2_Data_M, "Top2_Data_M/F");

   tree_particle->Branch("Leptonic_Top_Bjet_Data_Pt", &Top2_Bjet_Data_Pt, "Top2_Bjet_Data_Pt/F");
   tree_particle->Branch("Leptonic_Top_Bjet_Data_Eta", &Top2_Bjet_Data_Eta, "Top2_Bjet_Data_Eta/F");
   tree_particle->Branch("Leptonic_Top_Bjet_Data_Phi", &Top2_Bjet_Data_Phi, "Top2_Bjet_Data_Phi/F");
   tree_particle->Branch("Leptonic_Top_Bjet_Data_E", &Top2_Bjet_Data_E, "Top2_Bjet_Data_E/F");
   tree_particle->Branch("Leptonic_Top_Bjet_Data_M", &Top2_Bjet_Data_M, "Top2_Bjet_Data_M/F");

   tree_particle->Branch("Leptonic_Top_Lepton_Data_Pt", &Top2_Lepton_Data_Pt, "Top2_Lepton_Data_Pt/F");
   tree_particle->Branch("Leptonic_Top_Lepton_Data_Eta", &Top2_Lepton_Data_Eta, "Top2_Lepton_Data_Eta/F");
   tree_particle->Branch("Leptonic_Top_Lepton_Data_Phi", &Top2_Lepton_Data_Phi, "Top2_Lepton_Data_Phi/F");
   tree_particle->Branch("Leptonic_Top_Lepton_Data_E", &Top2_Lepton_Data_E, "Top2_Lepton_Data_E/F");
   tree_particle->Branch("Leptonic_Top_Lepton_Data_M", &Top2_Lepton_Data_M, "Top2_Lepton_Data_M/F");

   tree_particle->Branch("Leptonic_Top_Neutrino_Data_Pt", &Top2_Neutrino_Data_Pt, "Top2_Neutrino_Data_Pt/F");
   tree_particle->Branch("Leptonic_Top_Neutrino_Data_Eta", &Top2_Neutrino_Data_Eta, "Top2_Neutrino_Data_Eta/F");
   tree_particle->Branch("Leptonic_Top_Neutrino_Data_Phi", &Top2_Neutrino_Data_Phi, "Top2_Neutrino_Data_Phi/F");
   tree_particle->Branch("Leptonic_Top_Neutrino_Data_E", &Top2_Neutrino_Data_E, "Top2_Neutrino_Data_E/F");
   tree_particle->Branch("Leptonic_Top_Neutrino_Data_M", &Top2_Neutrino_Data_M, "Top2_Neutrino_Data_M/F");

   tree_particle->Branch("ljets_ttbar_Data_Pt", &ttbar_Data_Pt, "ttbar_Data_Pt/F");
   tree_particle->Branch("ljets_ttbar_Data_Eta", &ttbar_Data_Eta, "ttbar_Data_Eta/F");
   tree_particle->Branch("ljets_ttbar_Data_Phi", &ttbar_Data_Phi, "ttbar_Data_Phi/F");
   tree_particle->Branch("ljets_ttbar_Data_E", &ttbar_Data_E, "ttbar_Data_E/F");
   tree_particle->Branch("ljets_ttbar_Data_M", &ttbar_Data_M, "ttbar_Data_M/F");

   tree_particle->Branch("Hadronic_Top_MC_Pt", &Top1_MC_Pt, "Top1_MC_Pt/F");
   tree_particle->Branch("Hadronic_Top_MC_Eta", &Top1_MC_Eta, "Top1_MC_Eta/F");
   tree_particle->Branch("Hadronic_Top_MC_Phi", &Top1_MC_Phi, "Top1_MC_Phi/F");
   tree_particle->Branch("Hadronic_Top_MC_E", &Top1_MC_E, "Top1_MC_E/F");
   tree_particle->Branch("Hadronic_Top_MC_M", &Top1_MC_M, "Top1_MC_M/F");

   tree_particle->Branch("Hadronic_Top_Bjet_MC_Pt", &Top1_Bjet_MC_Pt, "Top1_Bjet_MC_Pt/F");
   tree_particle->Branch("Hadronic_Top_Bjet_MC_Eta", &Top1_Bjet_MC_Eta, "Top1_Bjet_MC_Eta/F");
   tree_particle->Branch("Hadronic_Top_Bjet_MC_Phi", &Top1_Bjet_MC_Phi, "Top1_Bjet_MC_Phi/F");
   tree_particle->Branch("Hadronic_Top_Bjet_MC_E", &Top1_Bjet_MC_E, "Top1_Bjet_MC_E/F");
   tree_particle->Branch("Hadronic_Top_Bjet_MC_M", &Top1_Bjet_MC_M, "Top1_Bjet_MC_M/F");

   tree_particle->Branch("Hadronic_Top_Wboson_MC_Pt", &Top1_Wboson_MC_Pt, "Top1_Wboson_MC_Pt/F");
   tree_particle->Branch("Hadronic_Top_Wboson_MC_Eta", &Top1_Wboson_MC_Eta, "Top1_Wboson_MC_Eta/F");
   tree_particle->Branch("Hadronic_Top_Wboson_MC_Phi", &Top1_Wboson_MC_Phi, "Top1_Wboson_MC_Phi/F");
   tree_particle->Branch("Hadronic_Top_Wboson_MC_E", &Top1_Wboson_MC_E, "Top1_Wboson_MC_E/F");
   tree_particle->Branch("Hadronic_Top_Wboson_MC_M", &Top1_Wboson_MC_M, "Top1_Wboson_MC_M/F");

   tree_particle->Branch("Leptonic_Top_MC_Pt", &Top2_MC_Pt, "Top2_MC_Pt/F");
   tree_particle->Branch("Leptonic_Top_MC_Eta", &Top2_MC_Eta, "Top2_MC_Eta/F");
   tree_particle->Branch("Leptonic_Top_MC_Phi", &Top2_MC_Phi, "Top2_MC_Phi/F");
   tree_particle->Branch("Leptonic_Top_MC_E", &Top2_MC_E, "Top2_MC_E/F");
   tree_particle->Branch("Leptonic_Top_MC_M", &Top2_MC_M, "Top2_MC_M/F");

   tree_particle->Branch("Leptonic_Top_Bjet_MC_Pt", &Top2_Bjet_MC_Pt, "Top2_Bjet_MC_Pt/F");
   tree_particle->Branch("Leptonic_Top_Bjet_MC_Eta", &Top2_Bjet_MC_Eta, "Top2_Bjet_MC_Eta/F");
   tree_particle->Branch("Leptonic_Top_Bjet_MC_Phi", &Top2_Bjet_MC_Phi, "Top2_Bjet_MC_Phi/F");
   tree_particle->Branch("Leptonic_Top_Bjet_MC_E", &Top2_Bjet_MC_E, "Top2_Bjet_MC_E/F");
   tree_particle->Branch("Leptonic_Top_Bjet_MC_M", &Top2_Bjet_MC_M, "Top2_Bjet_MC_M/F");

   tree_particle->Branch("Leptonic_Top_Lepton_MC_Pt", &Top2_Lepton_MC_Pt, "Top2_Lepton_MC_Pt/F");
   tree_particle->Branch("Leptonic_Top_Lepton_MC_Eta", &Top2_Lepton_MC_Eta, "Top2_Lepton_MC_Eta/F");
   tree_particle->Branch("Leptonic_Top_Lepton_MC_Phi", &Top2_Lepton_MC_Phi, "Top2_Lepton_MC_Phi/F");
   tree_particle->Branch("Leptonic_Top_Lepton_MC_E", &Top2_Lepton_MC_E, "Top2_Lepton_MC_E/F");
   tree_particle->Branch("Leptonic_Top_Lepton_MC_M", &Top2_Lepton_MC_M, "Top2_Lepton_MC_M/F");

   tree_particle->Branch("Leptonic_Top_Neutrino_MC_Pt", &Top2_Neutrino_MC_Pt, "Top2_Neutrino_MC_Pt/F");
   tree_particle->Branch("Leptonic_Top_Neutrino_MC_Eta", &Top2_Neutrino_MC_Eta, "Top2_Neutrino_MC_Eta/F");
   tree_particle->Branch("Leptonic_Top_Neutrino_MC_Phi", &Top2_Neutrino_MC_Phi, "Top2_Neutrino_MC_Phi/F");
   tree_particle->Branch("Leptonic_Top_Neutrino_MC_E", &Top2_Neutrino_MC_E, "Top2_Neutrino_MC_E/F");
   tree_particle->Branch("Leptonic_Top_Neutrino_MC_M", &Top2_Neutrino_MC_M, "Top2_Neutrino_MC_M/F");

   tree_particle->Branch("ljets_ttbar_MC_Pt", &ttbar_MC_Pt, "ttbar_MC_Pt/F");
   tree_particle->Branch("ljets_ttbar_MC_Eta", &ttbar_MC_Eta, "ttbar_MC_Eta/F");
   tree_particle->Branch("ljets_ttbar_MC_Phi", &ttbar_MC_Phi, "ttbar_MC_Phi/F");
   tree_particle->Branch("ljets_ttbar_MC_E", &ttbar_MC_E, "ttbar_MC_E/F");
   tree_particle->Branch("ljets_ttbar_MC_M", &ttbar_MC_M, "ttbar_MC_M/F");
   ///////////////////////

   TTree *tree_reco = new TTree("Tops_Reco","TLorenzVecors_of_tops_ljets_reco");
   tree_reco->Branch("Hadronic_Top_Data_Pt", &Top1_Data_Pt, "Top1_Data_Pt/F");
   tree_reco->Branch("Hadronic_Top_Data_Eta", &Top1_Data_Eta, "Top1_Data_Eta/F");
   tree_reco->Branch("Hadronic_Top_Data_Phi", &Top1_Data_Phi, "Top1_Data_Phi/F");
   tree_reco->Branch("Hadronic_Top_Data_E", &Top1_Data_E, "Top1_Data_E/F");
   tree_reco->Branch("Hadronic_Top_Data_M", &Top1_Data_M, "Top1_Data_M/F");

   tree_reco->Branch("Hadronic_Top_Bjet_Data_Pt", &Top1_Bjet_Data_Pt, "Top1_Bjet_Data_Pt/F");
   tree_reco->Branch("Hadronic_Top_Bjet_Data_Eta", &Top1_Bjet_Data_Eta, "Top1_Bjet_Data_Eta/F");
   tree_reco->Branch("Hadronic_Top_Bjet_Data_Phi", &Top1_Bjet_Data_Phi, "Top1_Bjet_Data_Phi/F");
   tree_reco->Branch("Hadronic_Top_Bjet_Data_E", &Top1_Bjet_Data_E, "Top1_Bjet_Data_E/F");
   tree_reco->Branch("Hadronic_Top_Bjet_Data_M", &Top1_Bjet_Data_M, "Top1_Bjet_Data_M/F");

   tree_reco->Branch("Hadronic_Top_Wboson_Data_Pt", &Top1_Wboson_Data_Pt, "Top1_Wboson_Data_Pt/F");
   tree_reco->Branch("Hadronic_Top_Wboson_Data_Eta", &Top1_Wboson_Data_Eta, "Top1_Wboson_Data_Eta/F");
   tree_reco->Branch("Hadronic_Top_Wboson_Data_Phi", &Top1_Wboson_Data_Phi, "Top1_Wboson_Data_Phi/F");
   tree_reco->Branch("Hadronic_Top_Wboson_Data_E", &Top1_Wboson_Data_E, "Top1_Wboson_Data_E/F");
   tree_reco->Branch("Hadronic_Top_Wboson_Data_M", &Top1_Wboson_Data_M, "Top1_Wboson_Data_M/F");

   tree_reco->Branch("Leptonic_Top_Data_Pt", &Top2_Data_Pt, "Top2_Data_Pt/F");
   tree_reco->Branch("Leptonic_Top_Data_Eta", &Top2_Data_Eta, "Top2_Data_Eta/F");
   tree_reco->Branch("Leptonic_Top_Data_Phi", &Top2_Data_Phi, "Top2_Data_Phi/F");
   tree_reco->Branch("Leptonic_Top_Data_E", &Top2_Data_E, "Top2_Data_E/F");
   tree_reco->Branch("Leptonic_Top_Data_M", &Top2_Data_M, "Top2_Data_M/F");

   tree_reco->Branch("Leptonic_Top_Bjet_Data_Pt", &Top2_Bjet_Data_Pt, "Top2_Bjet_Data_Pt/F");
   tree_reco->Branch("Leptonic_Top_Bjet_Data_Eta", &Top2_Bjet_Data_Eta, "Top2_Bjet_Data_Eta/F");
   tree_reco->Branch("Leptonic_Top_Bjet_Data_Phi", &Top2_Bjet_Data_Phi, "Top2_Bjet_Data_Phi/F");
   tree_reco->Branch("Leptonic_Top_Bjet_Data_E", &Top2_Bjet_Data_E, "Top2_Bjet_Data_E/F");
   tree_reco->Branch("Leptonic_Top_Bjet_Data_M", &Top2_Bjet_Data_M, "Top2_Bjet_Data_M/F");

   tree_reco->Branch("Leptonic_Top_Lepton_Data_Pt", &Top2_Lepton_Data_Pt, "Top2_Lepton_Data_Pt/F");
   tree_reco->Branch("Leptonic_Top_Lepton_Data_Eta", &Top2_Lepton_Data_Eta, "Top2_Lepton_Data_Eta/F");
   tree_reco->Branch("Leptonic_Top_Lepton_Data_Phi", &Top2_Lepton_Data_Phi, "Top2_Lepton_Data_Phi/F");
   tree_reco->Branch("Leptonic_Top_Lepton_Data_E", &Top2_Lepton_Data_E, "Top2_Lepton_Data_E/F");
   tree_reco->Branch("Leptonic_Top_Lepton_Data_M", &Top2_Lepton_Data_M, "Top2_Lepton_Data_M/F");

   tree_reco->Branch("Leptonic_Top_Neutrino_Data_Pt", &Top2_Neutrino_Data_Pt, "Top2_Neutrino_Data_Pt/F");
   tree_reco->Branch("Leptonic_Top_Neutrino_Data_Eta", &Top2_Neutrino_Data_Eta, "Top2_Neutrino_Data_Eta/F");
   tree_reco->Branch("Leptonic_Top_Neutrino_Data_Phi", &Top2_Neutrino_Data_Phi, "Top2_Neutrino_Data_Phi/F");
   tree_reco->Branch("Leptonic_Top_Neutrino_Data_E", &Top2_Neutrino_Data_E, "Top2_Neutrino_Data_E/F");
   tree_reco->Branch("Leptonic_Top_Neutrino_Data_M", &Top2_Neutrino_Data_M, "Top2_Neutrino_Data_M/F");

   tree_reco->Branch("ljets_ttbar_Data_Pt", &ttbar_Data_Pt, "ttbar_Data_Pt/F");
   tree_reco->Branch("ljets_ttbar_Data_Eta", &ttbar_Data_Eta, "ttbar_Data_Eta/F");
   tree_reco->Branch("ljets_ttbar_Data_Phi", &ttbar_Data_Phi, "ttbar_Data_Phi/F");
   tree_reco->Branch("ljets_ttbar_Data_E", &ttbar_Data_E, "ttbar_Data_E/F");
   tree_reco->Branch("ljets_ttbar_Data_M", &ttbar_Data_M, "ttbar_Data_M/F");

   tree_reco->Branch("Hadronic_Top_MC_Pt", &Top1_MC_Pt, "Top1_MC_Pt/F");
   tree_reco->Branch("Hadronic_Top_MC_Eta", &Top1_MC_Eta, "Top1_MC_Eta/F");
   tree_reco->Branch("Hadronic_Top_MC_Phi", &Top1_MC_Phi, "Top1_MC_Phi/F");
   tree_reco->Branch("Hadronic_Top_MC_E", &Top1_MC_E, "Top1_MC_E/F");
   tree_reco->Branch("Hadronic_Top_MC_M", &Top1_MC_M, "Top1_MC_M/F");

   tree_reco->Branch("Hadronic_Top_Bjet_MC_Pt", &Top1_Bjet_MC_Pt, "Top1_Bjet_MC_Pt/F");
   tree_reco->Branch("Hadronic_Top_Bjet_MC_Eta", &Top1_Bjet_MC_Eta, "Top1_Bjet_MC_Eta/F");
   tree_reco->Branch("Hadronic_Top_Bjet_MC_Phi", &Top1_Bjet_MC_Phi, "Top1_Bjet_MC_Phi/F");
   tree_reco->Branch("Hadronic_Top_Bjet_MC_E", &Top1_Bjet_MC_E, "Top1_Bjet_MC_E/F");
   tree_reco->Branch("Hadronic_Top_Bjet_MC_M", &Top1_Bjet_MC_M, "Top1_Bjet_MC_M/F");

   tree_reco->Branch("Hadronic_Top_Wboson_MC_Pt", &Top1_Wboson_MC_Pt, "Top1_Wboson_MC_Pt/F");
   tree_reco->Branch("Hadronic_Top_Wboson_MC_Eta", &Top1_Wboson_MC_Eta, "Top1_Wboson_MC_Eta/F");
   tree_reco->Branch("Hadronic_Top_Wboson_MC_Phi", &Top1_Wboson_MC_Phi, "Top1_Wboson_MC_Phi/F");
   tree_reco->Branch("Hadronic_Top_Wboson_MC_E", &Top1_Wboson_MC_E, "Top1_Wboson_MC_E/F");
   tree_reco->Branch("Hadronic_Top_Wboson_MC_M", &Top1_Wboson_MC_M, "Top1_Wboson_MC_M/F");

   tree_reco->Branch("Leptonic_Top_MC_Pt", &Top2_MC_Pt, "Top2_MC_Pt/F");
   tree_reco->Branch("Leptonic_Top_MC_Eta", &Top2_MC_Eta, "Top2_MC_Eta/F");
   tree_reco->Branch("Leptonic_Top_MC_Phi", &Top2_MC_Phi, "Top2_MC_Phi/F");
   tree_reco->Branch("Leptonic_Top_MC_E", &Top2_MC_E, "Top2_MC_E/F");
   tree_reco->Branch("Leptonic_Top_MC_M", &Top2_MC_M, "Top2_MC_M/F");

   tree_reco->Branch("Leptonic_Top_Bjet_MC_Pt", &Top2_Bjet_MC_Pt, "Top2_Bjet_MC_Pt/F");
   tree_reco->Branch("Leptonic_Top_Bjet_MC_Eta", &Top2_Bjet_MC_Eta, "Top2_Bjet_MC_Eta/F");
   tree_reco->Branch("Leptonic_Top_Bjet_MC_Phi", &Top2_Bjet_MC_Phi, "Top2_Bjet_MC_Phi/F");
   tree_reco->Branch("Leptonic_Top_Bjet_MC_E", &Top2_Bjet_MC_E, "Top2_Bjet_MC_E/F");
   tree_reco->Branch("Leptonic_Top_Bjet_MC_M", &Top2_Bjet_MC_M, "Top2_Bjet_MC_M/F");

   tree_reco->Branch("Leptonic_Top_Lepton_MC_Pt", &Top2_Lepton_MC_Pt, "Top2_Lepton_MC_Pt/F");
   tree_reco->Branch("Leptonic_Top_Lepton_MC_Eta", &Top2_Lepton_MC_Eta, "Top2_Lepton_MC_Eta/F");
   tree_reco->Branch("Leptonic_Top_Lepton_MC_Phi", &Top2_Lepton_MC_Phi, "Top2_Lepton_MC_Phi/F");
   tree_reco->Branch("Leptonic_Top_Lepton_MC_E", &Top2_Lepton_MC_E, "Top2_Lepton_MC_E/F");
   tree_reco->Branch("Leptonic_Top_Lepton_MC_M", &Top2_Lepton_MC_M, "Top2_Lepton_MC_M/F");

   tree_reco->Branch("Leptonic_Top_Neutrino_MC_Pt", &Top2_Neutrino_MC_Pt, "Top2_Neutrino_MC_Pt/F");
   tree_reco->Branch("Leptonic_Top_Neutrino_MC_Eta", &Top2_Neutrino_MC_Eta, "Top2_Neutrino_MC_Eta/F");
   tree_reco->Branch("Leptonic_Top_Neutrino_MC_Phi", &Top2_Neutrino_MC_Phi, "Top2_Neutrino_MC_Phi/F");
   tree_reco->Branch("Leptonic_Top_Neutrino_MC_E", &Top2_Neutrino_MC_E, "Top2_Neutrino_MC_E/F");
   tree_reco->Branch("Leptonic_Top_Neutrino_MC_M", &Top2_Neutrino_MC_M, "Top2_Neutrino_MC_M/F");

   tree_reco->Branch("ljets_ttbar_MC_Pt", &ttbar_MC_Pt, "ttbar_MC_Pt/F");
   tree_reco->Branch("ljets_ttbar_MC_Eta", &ttbar_MC_Eta, "ttbar_MC_Eta/F");
   tree_reco->Branch("ljets_ttbar_MC_Phi", &ttbar_MC_Phi, "ttbar_MC_Phi/F");
   tree_reco->Branch("ljets_ttbar_MC_E", &ttbar_MC_E, "ttbar_MC_E/F");
   tree_reco->Branch("ljets_ttbar_MC_M", &ttbar_MC_M, "ttbar_MC_M/F");
   //////////////////////////////////////////////
   
   TTree *tree = new TTree("Tops","TLorenzVecors_of_tops_ljets");
   tree->Branch("Hadronic_Top_Data_Pt", &Top1_Data_Pt, "Top1_Data_Pt/F");
   tree->Branch("Hadronic_Top_Data_Eta", &Top1_Data_Eta, "Top1_Data_Eta/F");
   tree->Branch("Hadronic_Top_Data_Phi", &Top1_Data_Phi, "Top1_Data_Phi/F");
   tree->Branch("Hadronic_Top_Data_E", &Top1_Data_E, "Top1_Data_E/F");
   tree->Branch("Hadronic_Top_Data_M", &Top1_Data_M, "Top1_Data_M/F");

   tree->Branch("Hadronic_Top_Bjet_Data_Pt", &Top1_Bjet_Data_Pt, "Top1_Bjet_Data_Pt/F");
   tree->Branch("Hadronic_Top_Bjet_Data_Eta", &Top1_Bjet_Data_Eta, "Top1_Bjet_Data_Eta/F");
   tree->Branch("Hadronic_Top_Bjet_Data_Phi", &Top1_Bjet_Data_Phi, "Top1_Bjet_Data_Phi/F");
   tree->Branch("Hadronic_Top_Bjet_Data_E", &Top1_Bjet_Data_E, "Top1_Bjet_Data_E/F");
   tree->Branch("Hadronic_Top_Bjet_Data_M", &Top1_Bjet_Data_M, "Top1_Bjet_Data_M/F");

   tree->Branch("Hadronic_Top_Wboson_Data_Pt", &Top1_Wboson_Data_Pt, "Top1_Wboson_Data_Pt/F");
   tree->Branch("Hadronic_Top_Wboson_Data_Eta", &Top1_Wboson_Data_Eta, "Top1_Wboson_Data_Eta/F");
   tree->Branch("Hadronic_Top_Wboson_Data_Phi", &Top1_Wboson_Data_Phi, "Top1_Wboson_Data_Phi/F");
   tree->Branch("Hadronic_Top_Wboson_Data_E", &Top1_Wboson_Data_E, "Top1_Wboson_Data_E/F");
   tree->Branch("Hadronic_Top_Wboson_Data_M", &Top1_Wboson_Data_M, "Top1_Wboson_Data_M/F");

   tree->Branch("Leptonic_Top_Data_Pt", &Top2_Data_Pt, "Top2_Data_Pt/F");
   tree->Branch("Leptonic_Top_Data_Eta", &Top2_Data_Eta, "Top2_Data_Eta/F");
   tree->Branch("Leptonic_Top_Data_Phi", &Top2_Data_Phi, "Top2_Data_Phi/F");
   tree->Branch("Leptonic_Top_Data_E", &Top2_Data_E, "Top2_Data_E/F");
   tree->Branch("Leptonic_Top_Data_M", &Top2_Data_M, "Top2_Data_M/F");

   tree->Branch("Leptonic_Top_Bjet_Data_Pt", &Top2_Bjet_Data_Pt, "Top2_Bjet_Data_Pt/F");
   tree->Branch("Leptonic_Top_Bjet_Data_Eta", &Top2_Bjet_Data_Eta, "Top2_Bjet_Data_Eta/F");
   tree->Branch("Leptonic_Top_Bjet_Data_Phi", &Top2_Bjet_Data_Phi, "Top2_Bjet_Data_Phi/F");
   tree->Branch("Leptonic_Top_Bjet_Data_E", &Top2_Bjet_Data_E, "Top2_Bjet_Data_E/F");
   tree->Branch("Leptonic_Top_Bjet_Data_M", &Top2_Bjet_Data_M, "Top2_Bjet_Data_M/F");

   tree->Branch("Leptonic_Top_Lepton_Data_Pt", &Top2_Lepton_Data_Pt, "Top2_Lepton_Data_Pt/F");
   tree->Branch("Leptonic_Top_Lepton_Data_Eta", &Top2_Lepton_Data_Eta, "Top2_Lepton_Data_Eta/F");
   tree->Branch("Leptonic_Top_Lepton_Data_Phi", &Top2_Lepton_Data_Phi, "Top2_Lepton_Data_Phi/F");
   tree->Branch("Leptonic_Top_Lepton_Data_E", &Top2_Lepton_Data_E, "Top2_Lepton_Data_E/F");
   tree->Branch("Leptonic_Top_Lepton_Data_M", &Top2_Lepton_Data_M, "Top2_Lepton_Data_M/F");

   tree->Branch("Leptonic_Top_Neutrino_Data_Pt", &Top2_Neutrino_Data_Pt, "Top2_Neutrino_Data_Pt/F");
   tree->Branch("Leptonic_Top_Neutrino_Data_Eta", &Top2_Neutrino_Data_Eta, "Top2_Neutrino_Data_Eta/F");
   tree->Branch("Leptonic_Top_Neutrino_Data_Phi", &Top2_Neutrino_Data_Phi, "Top2_Neutrino_Data_Phi/F");
   tree->Branch("Leptonic_Top_Neutrino_Data_E", &Top2_Neutrino_Data_E, "Top2_Neutrino_Data_E/F");
   tree->Branch("Leptonic_Top_Neutrino_Data_M", &Top2_Neutrino_Data_M, "Top2_Neutrino_Data_M/F");

   tree->Branch("ljets_ttbar_Data_Pt", &ttbar_Data_Pt, "ttbar_Data_Pt/F");
   tree->Branch("ljets_ttbar_Data_Eta", &ttbar_Data_Eta, "ttbar_Data_Eta/F");
   tree->Branch("ljets_ttbar_Data_Phi", &ttbar_Data_Phi, "ttbar_Data_Phi/F");
   tree->Branch("ljets_ttbar_Data_E", &ttbar_Data_E, "ttbar_Data_E/F");
   tree->Branch("ljets_ttbar_Data_M", &ttbar_Data_M, "ttbar_Data_M/F");

   tree->Branch("Hadronic_Top_MC_Pt", &Top1_MC_Pt, "Top1_MC_Pt/F");
   tree->Branch("Hadronic_Top_MC_Eta", &Top1_MC_Eta, "Top1_MC_Eta/F");
   tree->Branch("Hadronic_Top_MC_Phi", &Top1_MC_Phi, "Top1_MC_Phi/F");
   tree->Branch("Hadronic_Top_MC_E", &Top1_MC_E, "Top1_MC_E/F");
   tree->Branch("Hadronic_Top_MC_M", &Top1_MC_M, "Top1_MC_M/F");

   tree->Branch("Hadronic_Top_Bjet_MC_Pt", &Top1_Bjet_MC_Pt, "Top1_Bjet_MC_Pt/F");
   tree->Branch("Hadronic_Top_Bjet_MC_Eta", &Top1_Bjet_MC_Eta, "Top1_Bjet_MC_Eta/F");
   tree->Branch("Hadronic_Top_Bjet_MC_Phi", &Top1_Bjet_MC_Phi, "Top1_Bjet_MC_Phi/F");
   tree->Branch("Hadronic_Top_Bjet_MC_E", &Top1_Bjet_MC_E, "Top1_Bjet_MC_E/F");
   tree->Branch("Hadronic_Top_Bjet_MC_M", &Top1_Bjet_MC_M, "Top1_Bjet_MC_M/F");

   tree->Branch("Hadronic_Top_Wboson_MC_Pt", &Top1_Wboson_MC_Pt, "Top1_Wboson_MC_Pt/F");
   tree->Branch("Hadronic_Top_Wboson_MC_Eta", &Top1_Wboson_MC_Eta, "Top1_Wboson_MC_Eta/F");
   tree->Branch("Hadronic_Top_Wboson_MC_Phi", &Top1_Wboson_MC_Phi, "Top1_Wboson_MC_Phi/F");
   tree->Branch("Hadronic_Top_Wboson_MC_E", &Top1_Wboson_MC_E, "Top1_Wboson_MC_E/F");
   tree->Branch("Hadronic_Top_Wboson_MC_M", &Top1_Wboson_MC_M, "Top1_Wboson_MC_M/F");

   tree->Branch("Leptonic_Top_MC_Pt", &Top2_MC_Pt, "Top2_MC_Pt/F");
   tree->Branch("Leptonic_Top_MC_Eta", &Top2_MC_Eta, "Top2_MC_Eta/F");
   tree->Branch("Leptonic_Top_MC_Phi", &Top2_MC_Phi, "Top2_MC_Phi/F");
   tree->Branch("Leptonic_Top_MC_E", &Top2_MC_E, "Top2_MC_E/F");
   tree->Branch("Leptonic_Top_MC_M", &Top2_MC_M, "Top2_MC_M/F");

   tree->Branch("Leptonic_Top_Bjet_MC_Pt", &Top2_Bjet_MC_Pt, "Top2_Bjet_MC_Pt/F");
   tree->Branch("Leptonic_Top_Bjet_MC_Eta", &Top2_Bjet_MC_Eta, "Top2_Bjet_MC_Eta/F");
   tree->Branch("Leptonic_Top_Bjet_MC_Phi", &Top2_Bjet_MC_Phi, "Top2_Bjet_MC_Phi/F");
   tree->Branch("Leptonic_Top_Bjet_MC_E", &Top2_Bjet_MC_E, "Top2_Bjet_MC_E/F");
   tree->Branch("Leptonic_Top_Bjet_MC_M", &Top2_Bjet_MC_M, "Top2_Bjet_MC_M/F");

   tree->Branch("Leptonic_Top_Lepton_MC_Pt", &Top2_Lepton_MC_Pt, "Top2_Lepton_MC_Pt/F");
   tree->Branch("Leptonic_Top_Lepton_MC_Eta", &Top2_Lepton_MC_Eta, "Top2_Lepton_MC_Eta/F");
   tree->Branch("Leptonic_Top_Lepton_MC_Phi", &Top2_Lepton_MC_Phi, "Top2_Lepton_MC_Phi/F");
   tree->Branch("Leptonic_Top_Lepton_MC_E", &Top2_Lepton_MC_E, "Top2_Lepton_MC_E/F");
   tree->Branch("Leptonic_Top_Lepton_MC_M", &Top2_Lepton_MC_M, "Top2_Lepton_MC_M/F");

   tree->Branch("Leptonic_Top_Neutrino_MC_Pt", &Top2_Neutrino_MC_Pt, "Top2_Neutrino_MC_Pt/F");
   tree->Branch("Leptonic_Top_Neutrino_MC_Eta", &Top2_Neutrino_MC_Eta, "Top2_Neutrino_MC_Eta/F");
   tree->Branch("Leptonic_Top_Neutrino_MC_Phi", &Top2_Neutrino_MC_Phi, "Top2_Neutrino_MC_Phi/F");
   tree->Branch("Leptonic_Top_Neutrino_MC_E", &Top2_Neutrino_MC_E, "Top2_Neutrino_MC_E/F");
   tree->Branch("Leptonic_Top_Neutrino_MC_M", &Top2_Neutrino_MC_M, "Top2_Neutrino_MC_M/F");

   tree->Branch("ljets_ttbar_MC_Pt", &ttbar_MC_Pt, "ttbar_MC_Pt/F");
   tree->Branch("ljets_ttbar_MC_Eta", &ttbar_MC_Eta, "ttbar_MC_Eta/F");
   tree->Branch("ljets_ttbar_MC_Phi", &ttbar_MC_Phi, "ttbar_MC_Phi/F");
   tree->Branch("ljets_ttbar_MC_E", &ttbar_MC_E, "ttbar_MC_E/F");
   tree->Branch("ljets_ttbar_MC_M", &ttbar_MC_M, "ttbar_MC_M/F");

   tree->Branch("check_variable1", &check_variable1, "check_variable1/F");
   tree->Branch("check_variable2", &check_variable2, "check_variable2/F");
   tree->Branch("check_variable3", &check_variable3, "check_variable3/F");
   tree->Branch("check_variable4", &check_variable4, "check_variable4/F");
   


   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   TLorentzVector MCTop1, MCTop2;
   TLorentzVector Top1, Top2;
   bool GotDataEvent = false;
   bool GotMCEvent = false;
   bool FoundNeutrino = false;
   bool MCFoundNeutrino = false;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      //cout << "Bingo " << jentry << " " << Event_Weight[0] << endl;
      if (jentry % 10000 == 0){
         cout << "Processing: " << jentry/10000 << " \%"<< endl;
      }
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      //cout << jentry << " " << Weight << endl;
      //if (jentry < 498429) continue;
      if (Event_Weight[0] < 1e-20) continue;

         //Basic historgams, no cuts applied
         LjetMulti->Fill(LJetJES_size);
         for ( int i = 0; i < kMaxLJetJES; i++ ){
            LjetEta->Fill(LJetJES_Eta[i]);
            LjetPhi->Fill(LJetJES_Phi[i]);
            LjetPt->Fill(LJetJES_PT[i]);
            LjetMass->Fill(LJetJES_Mass[i]);
            if (i == 0){
                  LeadingLjetEta->Fill(LJetJES_Eta[i]);
                  LeadingLjetPhi->Fill(LJetJES_Phi[i]);
                  LeadingLjetPt->Fill(LJetJES_PT[i]);
                  LeadingLjetMass->Fill(LJetJES_Mass[i]);    
            } else if (i == 1){
                  SubLeadingLjetEta->Fill(LJetJES_Eta[i]);
                  SubLeadingLjetPhi->Fill(LJetJES_Phi[i]);
                  SubLeadingLjetPt->Fill(LJetJES_PT[i]);
                  SubLeadingLjetMass->Fill(LJetJES_Mass[i]);    
            }
         }
         GenLjetMulti->Fill(GenLJet_size);
         for ( int i = 0; i < kMaxGenLJet; i++ ){
            GenLjetEta->Fill(GenLJet_Eta[i]);
            GenLjetPhi->Fill(GenLJet_Phi[i]);
            GenLjetPt->Fill(GenLJet_PT[i]);
            GenLjetMass->Fill(GenLJet_Mass[i]);
            if (i == 0){
                  GenLeadingLjetEta->Fill(GenLJet_Eta[i]);
                  GenLeadingLjetPhi->Fill(GenLJet_Phi[i]);
                  GenLeadingLjetPt->Fill(GenLJet_PT[i]);
                  GenLeadingLjetMass->Fill(GenLJet_Mass[i]);
            } else if (i ==1){
                  GenSubLeadingLjetEta->Fill(GenLJet_Eta[i]);
                  GenSubLeadingLjetPhi->Fill(GenLJet_Phi[i]);
                  GenSubLeadingLjetPt->Fill(GenLJet_PT[i]);
                  GenSubLeadingLjetMass->Fill(GenLJet_Mass[i]);
            }
         }

         JetMulti->Fill(JetJES_size);
         for ( int i = 0; i < kMaxJetJES; i++ ){
            JetEta->Fill(JetJES_Eta[i]);
            JetPhi->Fill(JetJES_Phi[i]);
            JetPt->Fill(JetJES_PT[i]);
            JetMass->Fill(JetJES_Mass[i]);
            if (i == 0){
               LeadingJetEta->Fill(JetJES_Eta[i]);
               LeadingJetPhi->Fill(JetJES_Phi[i]);
               LeadingJetPt->Fill(JetJES_PT[i]);
               LeadingJetMass->Fill(JetJES_Mass[i]);
            } else if (i == 1){
               SubLeadingJetEta->Fill(JetJES_Eta[i]);
               SubLeadingJetPhi->Fill(JetJES_Phi[i]);
               SubLeadingJetPt->Fill(JetJES_PT[i]);
               SubLeadingJetMass->Fill(JetJES_Mass[i]);
            }
         }
         GenJetMulti->Fill(GenJet_size);
         for ( int i = 0; i < kMaxGenJet; i++ ){
            GenJetEta->Fill(GenJet_Eta[i]);
            GenJetPhi->Fill(GenJet_Phi[i]);
            GenJetPt->Fill(GenJet_PT[i]);
            GenJetMass->Fill(GenJet_Mass[i]);
            if (i == 0){
                  GenLeadingJetEta->Fill(GenJet_Eta[i]);
                  GenLeadingJetPhi->Fill(GenJet_Phi[i]);
                  GenLeadingJetPt->Fill(GenJet_PT[i]);
                  GenLeadingJetMass->Fill(GenJet_Mass[i]);
            } else if (i == 1){
                  GenSubLeadingJetEta->Fill(GenJet_Eta[i]);
                  GenSubLeadingJetPhi->Fill(GenJet_Phi[i]);
                  GenSubLeadingJetPt->Fill(GenJet_PT[i]);
                  GenSubLeadingJetMass->Fill(GenJet_Mass[i]);
            }
         }

      //Define CUTS
      Event MyDataEvent;
      //leptons
      // electrons

      for ( int i = 0; i < Electron_size; i++ ){
            if ((abs(Electron_Eta[i]) < 1.35 || (abs(Electron_Eta[i]) > 1.52 && abs(Electron_Eta[i]) < 2.47)) && Electron_PT[i] > 27.0){
            //if (((abs(Electron_Eta[i]) < 1.35 || abs(Electron_Eta[i]) > 1.52) && (abs(Electron_Eta[i]) < 2.47)) || (Electron_PT[i] > 27.0)) {   
               ElectronEta->Fill(Electron_Eta[i]);
               ElectronPT->Fill(Electron_PT[i]);
               if (MyDataEvent.Electron1.GetTag() == ""){
                  MyDataEvent.Electron1.SetTag("Electron1");
                  MyDataEvent.Electron1.SetCharge(Electron_Charge[i]);
                  MyDataEvent.Electron1.SetPtEtaPhiE(Electron_PT[i],Electron_Eta[i],Electron_Phi[i], Electron_PT[i]/sin(2*atan(exp(-1.0*Electron_Eta[i]))));
                  //cout << "Electron1 E:" << Electron_PT[i]/sin(2*atan(exp(-1.0*Electron_Eta[i]))) << " " << abs(Electron_PT[i])*sqrt(1+1/((tan(2*atan(exp(-1.0*Electron_Eta[i]))))*(tan(2*atan(exp(-1.0*Electron_Eta[i])))))) << endl;
               }
               else if ((MyDataEvent.Electron2.GetTag() == "") && (MyDataEvent.Electron1.GetTag() == "Electron1")){
                  MyDataEvent.Electron2.SetTag("Electron2");
                  MyDataEvent.Electron2.SetCharge(Electron_Charge[i]);
                  MyDataEvent.Electron2.SetPtEtaPhiE(Electron_PT[i],Electron_Eta[i],Electron_Phi[i], Electron_PT[i]/sin(2*atan(exp(-1.0*Electron_Eta[i]))));
               }
               //cout << i << Electron_size << endl;
               
            }
      }

      // muons
      double MuonsSumPx, MuonsSumPy;
      MuonsSumPx = 0.0;
      MuonsSumPy = 0.0;
      for ( int i = 0; i < Muon_size; i++ ){
            MuonsSumPx += Muon_PT[i]*cos(Muon_Phi[i]);
            MuonsSumPy += Muon_PT[i]*sin(Muon_Phi[i]); 
            if ( (abs(Muon_Eta[i]) < 2.5) && (Muon_PT[i] > 27.0) ){   
               MuonEta->Fill(Muon_Eta[i]);
               MuonPT->Fill(Muon_PT[i]);
               if (MyDataEvent.Muon1.GetTag() == ""){
                  MyDataEvent.Muon1.SetTag("Muon1");
                  MyDataEvent.Muon1.SetCharge(Muon_Charge[i]);
                  MyDataEvent.Muon1.SetPtEtaPhiE(Muon_PT[i],Muon_Eta[i],Muon_Phi[i], Muon_PT[i]/sin(2*atan(exp(-1.0*Muon_Eta[i]))));
               }
               else if ((MyDataEvent.Muon2.GetTag() == "") && (MyDataEvent.Muon1.GetTag() == "Muon1")){
                  MyDataEvent.Muon2.SetTag("Muon2");
                  MyDataEvent.Muon2.SetCharge(Muon_Charge[i]);
                  MyDataEvent.Muon2.SetPtEtaPhiE(Muon_PT[i],Muon_Eta[i],Muon_Phi[i], Muon_PT[i]/sin(2*atan(exp(-1.0*Muon_Eta[i]))));
               }
            }

      }

      if (CheckPreSelectedLepton(MyDataEvent)){
         MyDataEvent.SetLepton(MaxLepton(MyDataEvent));
         MyLorentzVector HelpJetData;
         // small jets
         for ( int i = 0; i < JetJES_size; i++ ){
               HelpJetData.SetPtEtaPhiM(JetJES_PT[i],JetJES_Eta[i],JetJES_Phi[i], JetJES_Mass[i]);
               if ( (JetJES_size >= 4) && (JetJES_PT[i] > 25.0) && (abs(JetJES_Eta[i]) < 2.5) && ( DeltaR(HelpJetData,MyDataEvent.Lepton) > 0.2 )){   
                     JetJESEta->Fill(JetJES_Eta[i]);
                     JetJESPT->Fill(JetJES_PT[i]);
                     //cout << JetJES_Mass[i] << endl;
                     if ((MyDataEvent.BJet1.GetTag() == "") && (JetJES_BTag[i] == 1)){
                        MyDataEvent.BJet1.SetTag("BJet1");
                        MyDataEvent.BJet1.SetIsBTagged(true);
                        MyDataEvent.BJet1.SetCharge(JetJES_Charge[i]);
                        MyDataEvent.BJet1.SetPtEtaPhiM(JetJES_PT[i],JetJES_Eta[i],JetJES_Phi[i], JetJES_Mass[i]);
                        continue;
                     }
                     if ((MyDataEvent.BJet2.GetTag() == "") && (MyDataEvent.BJet1.GetTag() == "BJet1") && JetJES_BTag[i] == 1){
                        MyDataEvent.BJet2.SetTag("BJet2");
                        MyDataEvent.BJet2.SetIsBTagged(true);
                        MyDataEvent.BJet2.SetCharge(JetJES_Charge[i]);
                        MyDataEvent.BJet2.SetPtEtaPhiM(JetJES_PT[i],JetJES_Eta[i],JetJES_Phi[i], JetJES_Mass[i]);
                        continue;
                     }
                  
                     if (MyDataEvent.Jet3.GetTag() == ""){
                        MyDataEvent.Jet3.SetTag("Jet3");
                        MyDataEvent.Jet3.SetIsBTagged(false);
                        MyDataEvent.Jet3.SetCharge(JetJES_Charge[i]);
                        MyDataEvent.Jet3.SetPtEtaPhiM(JetJES_PT[i],JetJES_Eta[i],JetJES_Phi[i], JetJES_Mass[i]);
                        continue;
                     }
                     if ((MyDataEvent.Jet4.GetTag() == "") && (MyDataEvent.Jet3.GetTag() == "Jet3")){
                        MyDataEvent.Jet4.SetTag("Jet4");
                        MyDataEvent.Jet4.SetIsBTagged(false);
                        MyDataEvent.Jet4.SetCharge(JetJES_Charge[i]);
                        MyDataEvent.Jet4.SetPtEtaPhiM(JetJES_PT[i],JetJES_Eta[i],JetJES_Phi[i], JetJES_Mass[i]);
                        continue;
                     }                 
               } //if loop
         } // for loop
      } //if lepton loop

      for ( int i = 0; i < MissingET_size; i++ ){
                  if (MyDataEvent.Neutrino1.GetTag() == "") {
                     MyDataEvent.Neutrino1.SetTag("Neutrino1");
                     //MyDataEvent.Neutrino1.SetPtEtaPhiM(MissingET_MET[i],MissingET_Eta[i],MissingET_Phi[i], MissingET_MET[i]/sin(2*atan(exp(-1.0*MissingET_Eta[i]))));
                     continue;
                  }
                  //if ((MyDataEvent.Neutrino2.GetTag() == "") && (MyDataEvent.BJet1.GetTag() == "BJet1") && JetJES_BTag[i] == 1){
                  //   MyDataEvent.Neutrino2.SetTag("Neutrino2");
                  //   //MyDataEvent.Neutrino2.SetPtEtaPhiM(MissingET_MET[i],MissingET_Eta[i],MissingET_Phi[i], MissingET_MET[i]/sin(2*atan(exp(-1.0*MissingET_Eta[i]))));
                  //   continue;
                  //}
      
      }

      //CheckPreSelected(MyDataEvent);
      FoundNeutrino = false;
      if (CheckPreSelected(MyDataEvent)){
         //cout << "*********Preselected ********" << endl;
         //MyDataEvent.SetLepton(MaxLepton(MyDataEvent));
         TLorentzVector W = MyDataEvent.Jet3 + MyDataEvent.Jet4;
         MyLorentzVector Wboson;
         Wboson.SetPtEtaPhiE(W.Pt(),W.Eta(), W.Phi(), W.E());
         Wboson.SetCharge(MyDataEvent.Jet3.GetCharge()+MyDataEvent.Jet4.GetCharge());
         MyDataEvent.SetWHadron(Wboson);
         //TLorentzVector Top1, Top2;
         //ComputeNeutrinoPz();
         double Px, Py, Pz, E, k, a, b, c, MET;
         
         //double Px_old, Py_old, MET_old; // umaz old
         //Px_old = MissingET_MET[0]*cos(MissingET_Phi[0]);//puvodni kod
         //Py_old = MissingET_MET[0]*sin(MissingET_Phi[0]);//puvodni kod
         //MET_old = MissingET_MET[0]; // puvodni kod

         Px = MissingET_MET[0]*cos(MissingET_Phi[0]);
         Py = MissingET_MET[0]*sin(MissingET_Phi[0]);
         MET = MissingET_MET[0];
         // use Tag to choose only if max lepton type = muon
         
         if ((MyDataEvent.Lepton.GetTag()=="Muon1") || (MyDataEvent.Lepton.GetTag()=="Muon2")){
            //oprava verze 2
            Px = Px - MuonsSumPx; //MyDataEvent.Lepton.Px();//PB DEBUG SumAllMuons, SumAllMuonsPt>15 here last change
            Py = Py - MuonsSumPy; //MyDataEvent.Lepton.Py();//PB DEBUG SumAllMuons, SumAllMuonsPt>15 here last change
            MET = TMath::Sqrt(Px*Px + Py*Py);
            //oprava verze 1
            //Px = Px - MyDataEvent.Lepton.Px();
            //Py = Py - MyDataEvent.Lepton.Py();
            //MET = MyDataEvent.Lepton.Pt();
         }
         
         k = MyDataEvent.GetWHadron().M()*MyDataEvent.GetWHadron().M()/2.0 + MyDataEvent.Lepton.Pt()*MET;
         a = MyDataEvent.Lepton.Pt()*MyDataEvent.Lepton.Pt();
         b = -2*k*MyDataEvent.Lepton.Pz();
         c = MET*MET*MyDataEvent.Lepton.P()*MyDataEvent.Lepton.P() - k*k;
         Pz = MinQuadraticEq(a,b,c); // https://twiki.cern.ch/twiki/bin/view/Main/TopPairProduction
         if (Pz != nan("1")){
            E = sqrt(Px*Px + Py*Py + Pz*Pz);
            MyDataEvent.Neutrino1.SetPxPyPzE(Px,Py,Pz,E);   
            //MyDataEvent.Neutrino1.SetPtEtaPhiE(sqrt(Px*Px + Py*Py),MissingET_Eta[0],MissingET_Phi[0],sqrt(Px*Px + Py*Py)/sin(2*atan(exp(-1.0*MissingET_Eta[0]))));   
            FoundNeutrino = true;
         } else{
            std::cerr << "This should never happen !!!" << std::endl;
         }

         
         //E = sqrt(Px*Px + Py*Py + Pz*Pz);
         //MyDataEvent.Neutrino1.SetPxPyPzE(Px,Py,Pz,E);
         //MyDataEvent.Neutrino1.SetPtEtaPhiM(MyDataEvent.Neutrino1.Pt(), MyDataEvent.Neutrino1.Eta(), MyDataEvent.Neutrino1.Phi(), MyDataEvent.WHadron.M() );
         GotDataEvent = false;
         if (DeltaR(MyDataEvent.BJet1, MyDataEvent.Lepton) < DeltaR(MyDataEvent.BJet2, MyDataEvent.Lepton) && (FoundNeutrino == true)){
            Top1 = MyDataEvent.BJet2 + MyDataEvent.WHadron; 
            MyLorentzVector FTop1, FTop2;
            FTop1.SetPtEtaPhiE(Top1.Pt(),Top1.Eta(), Top1.Phi(), Top1.E());
            FTop1.SetCharge(MyDataEvent.BJet2.GetCharge() + MyDataEvent.WHadron.GetCharge());
            MyDataEvent.SetPseudoTop(FTop1);
            Top1_Bjet_Data_Pt = MyDataEvent.BJet2.Pt();
            Top1_Bjet_Data_Eta = MyDataEvent.BJet2.Eta();
            Top1_Bjet_Data_Phi = MyDataEvent.BJet2.Phi();
            Top1_Bjet_Data_E = MyDataEvent.BJet2.E();
            Top1_Bjet_Data_M = MyDataEvent.BJet2.M();

            Top1_Wboson_Data_Pt = MyDataEvent.WHadron.Pt();
            Top1_Wboson_Data_Eta = MyDataEvent.WHadron.Eta();
            Top1_Wboson_Data_Phi = MyDataEvent.WHadron.Phi();
            Top1_Wboson_Data_E = MyDataEvent.WHadron.E();
            Top1_Wboson_Data_M = MyDataEvent.WHadron.M();

            if (FoundNeutrino == true){
               TLorentzVector WLepton = MyDataEvent.Lepton + MyDataEvent.Neutrino1;
               MyLorentzVector WbosonLepton;
               WbosonLepton.SetPtEtaPhiE(WLepton.Pt(),WLepton.Eta(), WLepton.Phi(), WLepton.E());
               WbosonLepton.SetCharge(MyDataEvent.Lepton.GetCharge()+MyDataEvent.Neutrino1.GetCharge());
               MyDataEvent.SetWLepton(WbosonLepton);
               Top2 = MyDataEvent.BJet1 + MyDataEvent.Lepton + MyDataEvent.Neutrino1; 
               FTop2.SetPtEtaPhiE(Top2.Pt(),Top2.Eta(), Top2.Phi(), Top2.E());
               FTop2.SetCharge(MyDataEvent.BJet1.GetCharge() + MyDataEvent.Lepton.GetCharge());
               MyDataEvent.SetLeptonPseudotop(FTop2);

               Top2_Bjet_Data_Pt = MyDataEvent.BJet1.Pt();
               Top2_Bjet_Data_Eta = MyDataEvent.BJet1.Eta();
               Top2_Bjet_Data_Phi = MyDataEvent.BJet1.Phi();
               Top2_Bjet_Data_E = MyDataEvent.BJet1.E();
               Top2_Bjet_Data_M = MyDataEvent.BJet1.M();

               Top2_Lepton_Data_Pt = MyDataEvent.Lepton.Pt();
               Top2_Lepton_Data_Eta = MyDataEvent.Lepton.Eta();
               Top2_Lepton_Data_Phi = MyDataEvent.Lepton.Phi();
               Top2_Lepton_Data_E = MyDataEvent.Lepton.E();
               Top2_Lepton_Data_M = MyDataEvent.Lepton.M();

               Top2_Neutrino_Data_Pt = MyDataEvent.Neutrino1.Pt();
               Top2_Neutrino_Data_Eta = MyDataEvent.Neutrino1.Eta();
               Top2_Neutrino_Data_Phi = MyDataEvent.Neutrino1.Phi();
               Top2_Neutrino_Data_E = MyDataEvent.Neutrino1.E();
               Top2_Neutrino_Data_M = MyDataEvent.Neutrino1.M();

               GotDataEvent = true;
            }
            //cout << "dR1: " << DeltaR(MyDataEvent.BJet1, MyDataEvent.Lepton) << " < " << DeltaR(MyDataEvent.BJet2, MyDataEvent.Lepton) << endl;  
         } else if (FoundNeutrino == true) {
            Top1 = MyDataEvent.BJet1 + MyDataEvent.WHadron;
            MyLorentzVector FTop1, FTop2;
            FTop1.SetPtEtaPhiE(Top1.Pt(),Top1.Eta(), Top1.Phi(), Top1.E());
            FTop1.SetCharge(MyDataEvent.BJet1.GetCharge() + MyDataEvent.WHadron.GetCharge());
            MyDataEvent.SetPseudoTop(FTop1);

            Top1_Bjet_Data_Pt = MyDataEvent.BJet1.Pt();
            Top1_Bjet_Data_Eta = MyDataEvent.BJet1.Eta();
            Top1_Bjet_Data_Phi = MyDataEvent.BJet1.Phi();
            Top1_Bjet_Data_E = MyDataEvent.BJet1.E();
            Top1_Bjet_Data_M = MyDataEvent.BJet1.M();

            Top1_Wboson_Data_Pt = MyDataEvent.WHadron.Pt();
            Top1_Wboson_Data_Eta = MyDataEvent.WHadron.Eta();
            Top1_Wboson_Data_Phi = MyDataEvent.WHadron.Phi();
            Top1_Wboson_Data_E = MyDataEvent.WHadron.E();
            Top1_Wboson_Data_M = MyDataEvent.WHadron.M();
            if (FoundNeutrino == true){
               TLorentzVector WLepton = MyDataEvent.Lepton + MyDataEvent.Neutrino1;
               MyLorentzVector WbosonLepton;
               WbosonLepton.SetPtEtaPhiE(WLepton.Pt(),WLepton.Eta(), WLepton.Phi(), WLepton.E());
               WbosonLepton.SetCharge(MyDataEvent.Lepton.GetCharge()+MyDataEvent.Neutrino1.GetCharge());
               MyDataEvent.SetWLepton(WbosonLepton);
               Top2 = MyDataEvent.BJet2 + MyDataEvent.Lepton + MyDataEvent.Neutrino1; 
               FTop2.SetPtEtaPhiE(Top2.Pt(),Top2.Eta(), Top2.Phi(), Top2.E());
               FTop2.SetCharge(MyDataEvent.BJet2.GetCharge() + MyDataEvent.Lepton.GetCharge());
               MyDataEvent.SetLeptonPseudotop(FTop2);

               Top2_Bjet_Data_Pt = MyDataEvent.BJet2.Pt();
               Top2_Bjet_Data_Eta = MyDataEvent.BJet2.Eta();
               Top2_Bjet_Data_Phi = MyDataEvent.BJet2.Phi();
               Top2_Bjet_Data_E = MyDataEvent.BJet2.E();
               Top2_Bjet_Data_M = MyDataEvent.BJet2.M();

               Top2_Lepton_Data_Pt = MyDataEvent.Lepton.Pt();
               Top2_Lepton_Data_Eta = MyDataEvent.Lepton.Eta();
               Top2_Lepton_Data_Phi = MyDataEvent.Lepton.Phi();
               Top2_Lepton_Data_E = MyDataEvent.Lepton.E();
               Top2_Lepton_Data_M = MyDataEvent.Lepton.M();

               Top2_Neutrino_Data_Pt = MyDataEvent.Neutrino1.Pt();
               Top2_Neutrino_Data_Eta = MyDataEvent.Neutrino1.Eta();
               Top2_Neutrino_Data_Phi = MyDataEvent.Neutrino1.Phi();
               Top2_Neutrino_Data_E = MyDataEvent.Neutrino1.E();
               Top2_Neutrino_Data_M = MyDataEvent.Neutrino1.M();
               GotDataEvent = true;
            }
            //cout << "dR2: " << DeltaR(MyDataEvent.BJet1, MyDataEvent.Lepton) << " > " << DeltaR(MyDataEvent.BJet2, MyDataEvent.Lepton) << endl;
         };
         
         if ((FoundNeutrino == true)&&(GotDataEvent == true)){
         TLorentzVector TopPair;
         TopPair = Top1 + Top2;
         MyLorentzVector FTopPair;
         FTopPair.SetPtEtaPhiE(TopPair.Pt(),TopPair.Eta(), TopPair.Phi(), TopPair.E());
         FTopPair.SetCharge(MyDataEvent.PseudoTop.GetCharge()+MyDataEvent.LeptonPseudotop.GetCharge());
         MyDataEvent.SetPseudoTopPair(FTopPair);
         MyDataEvent.Setm_PreSelected(true);    

         TopMass2->Fill(MyDataEvent.LeptonPseudotop.M());
         TopMass1->Fill(MyDataEvent.PseudoTop.M());
         WMass->Fill(MyDataEvent.WHadron.M());
         HadTopPt->Fill(MyDataEvent.PseudoTop.Pt());
         HadTopEta->Fill(MyDataEvent.PseudoTop.Eta());
         TopPairPt->Fill(MyDataEvent.PseudoTopPair.Pt());
         TopPairMass->Fill(MyDataEvent.PseudoTopPair.M());
         TopPairEta->Fill(MyDataEvent.PseudoTopPair.Eta());
         TopPairDeltaPhi->Fill(MyDataEvent.LeptonPseudotop.Phi()-MyDataEvent.PseudoTop.Phi());
         WLeptonVsLeptonPseudoTop->Fill(MyDataEvent.LeptonPseudotop.M(),MyDataEvent.WLepton.M());
         WLeptonVsNeutrinoPt->Fill(MyDataEvent.Neutrino1.Pt(), MyDataEvent.WLepton.M());
         LeptonPseudoTopVsNeutrinoPt->Fill(MyDataEvent.Neutrino1.Pt(), MyDataEvent.LeptonPseudotop.M());
         WHadronVsHadronPseudoTop->Fill(MyDataEvent.PseudoTop.M(),MyDataEvent.WHadron.M());
         LeptonPseudoTopDeltaMassLeptonW->Fill(MyDataEvent.LeptonPseudotop.M()-MyDataEvent.WLepton.M());
         HadronPseudoTopDeltaMassHadronW->Fill(MyDataEvent.PseudoTop.M()-MyDataEvent.WHadron.M());
         LeptonPseudoTopVsTopPairEta->Fill(MyDataEvent.LeptonPseudotop.Eta(), MyDataEvent.PseudoTopPair.Eta());
         HadronPseudoTopVsTopPairEta->Fill(MyDataEvent.PseudoTop.Eta(), MyDataEvent.PseudoTopPair.Eta());
         MyDataEvent.Setm_FinalSelected(true);
         Top1_Data_Pt = Top1.Pt();
         Top1_Data_Eta = Top1.Eta();
         Top1_Data_Phi = Top1.Phi();
         Top1_Data_E = Top1.E();
         Top1_Data_M = Top1.M();
         Top2_Data_Pt = Top2.Pt();
         Top2_Data_Eta = Top2.Eta();
         Top2_Data_Phi = Top2.Phi();
         Top2_Data_E = Top2.E();
         Top2_Data_M = Top2.M();

         ttbar_Data_Pt = (Top1 + Top2).Pt();
         ttbar_Data_Eta = (Top1 + Top2).Eta();
         ttbar_Data_Phi = (Top1 + Top2).Phi();
         ttbar_Data_E = (Top1 + Top2).E();
         ttbar_Data_M = (Top1 + Top2).M();
         
         }
         }
      
      // PARTICLE LEVEL **************************************************

      Event MyMCEvent;
      //leptons
      // electrons

      for ( int i = 0; i < GenElectron_size; i++ ){
            if ((abs(GenElectron_Eta[i]) < 1.35 || (abs(GenElectron_Eta[i]) > 1.52 && abs(GenElectron_Eta[i]) < 2.47)) && GenElectron_PT[i] > 27.0){
               MCElectronEta->Fill(GenElectron_Eta[i]);
               MCElectronPT->Fill(GenElectron_PT[i]);
               if (MyMCEvent.Electron1.GetTag() == ""){
                  MyMCEvent.Electron1.SetTag("Electron1");
                  MyMCEvent.Electron1.SetCharge(GenElectron_Charge[i]);
                  MyMCEvent.Electron1.SetPtEtaPhiE(GenElectron_PT[i],GenElectron_Eta[i],GenElectron_Phi[i], GenElectron_PT[i]/sin(2*atan(exp(-1.0*GenElectron_Eta[i]))));
               }
               else if ((MyMCEvent.Electron2.GetTag() == "") && (MyMCEvent.Electron1.GetTag() == "Electron1")){
                  MyMCEvent.Electron2.SetTag("Electron2");
                  MyMCEvent.Electron2.SetCharge(GenElectron_Charge[i]);
                  MyMCEvent.Electron2.SetPtEtaPhiE(GenElectron_PT[i],GenElectron_Eta[i],GenElectron_Phi[i], GenElectron_PT[i]/sin(2*atan(exp(-1.0*GenElectron_Eta[i]))));
               }
               //cout << i << GenElectron_size << endl;
               
            }
      }

      // muons
      for ( int i = 0; i < GenMuon_size; i++ ){
            if ( (abs(GenMuon_Eta[i]) < 2.5) && (GenMuon_PT[i] > 27.0) ){   
               MCMuonEta->Fill(GenMuon_Eta[i]);
               MCMuonPT->Fill(GenMuon_PT[i]);
               if (MyMCEvent.Muon1.GetTag() == ""){
                  MyMCEvent.Muon1.SetTag("Muon1");
                  MyMCEvent.Muon1.SetCharge(GenMuon_Charge[i]);
                  MyMCEvent.Muon1.SetPtEtaPhiE(GenMuon_PT[i],GenMuon_Eta[i],GenMuon_Phi[i], GenMuon_PT[i]/sin(2*atan(exp(-1.0*GenMuon_Eta[i]))));
               }
               else if ((MyMCEvent.Muon2.GetTag() == "") && (MyMCEvent.Muon1.GetTag() == "Muon1")){
                  MyMCEvent.Muon2.SetTag("Muon2");
                  MyMCEvent.Muon2.SetCharge(GenMuon_Charge[i]);
                  MyMCEvent.Muon2.SetPtEtaPhiE(GenMuon_PT[i],GenMuon_Eta[i],GenMuon_Phi[i], GenMuon_PT[i]/sin(2*atan(exp(-1.0*GenMuon_Eta[i]))));
               }
            }

      }

      //check lepton preselected, at mam alespon jeden lepron
      if (CheckPreSelectedLepton(MyMCEvent)){
         MyMCEvent.SetLepton(MaxLepton(MyMCEvent));
         MyLorentzVector HelpJetMC;
      // small jets
         bool MCBTag;
         for ( int i = 0; i < GenJet_size; i++ ){
               HelpJetMC.SetPtEtaPhiM(GenJet_PT[i],GenJet_Eta[i],GenJet_Phi[i], GenJet_Mass[i]);
               if ( (GenJet_size >= 4) && (GenJet_PT[i] > 25.0) && (abs(GenJet_Eta[i]) < 2.5)&& ( DeltaR(HelpJetMC,MyMCEvent.Lepton) > 0.2 )){ 
                     MCJetJESEta->Fill(GenJet_Eta[i]);
                     MCJetJESPT->Fill(GenJet_PT[i]);
                     //if ((MyMCEvent.BJet1.GetTag() == "") && (GenJet_BTag[i] == 1)){
                     MCBTag = false;
                     if (MyMCEvent.BJet1.GetTag() == "") {
                        for (int j = 0; j < GenBhadrons_size; j++)
                        {
                           if ((sqrt((GenJet_Phi[i]-GenBhadrons_Phi[j])*(GenJet_Phi[i]-GenBhadrons_Phi[j]) + (GenJet_Eta[i]-GenBhadrons_Eta[j])*(GenJet_Eta[i]-GenBhadrons_Eta[j])) < 0.4) && (GenBhadrons_PT[j] > 5.0)){
                              MCBTag = true;
                           }       
                        }
                        if (MCBTag){
                        MyMCEvent.BJet1.SetTag("BJet1");
                        MyMCEvent.BJet1.SetIsBTagged(true);
                        MyMCEvent.BJet1.SetCharge(GenJet_Charge[i]);
                        MyMCEvent.BJet1.SetPtEtaPhiM(GenJet_PT[i],GenJet_Eta[i],GenJet_Phi[i], GenJet_Mass[i]);
                        continue;
                        }
                     }
                     //if ((MyMCEvent.BJet2.GetTag() == "") && (MyMCEvent.BJet1.GetTag() == "BJet1") && GenJet_BTag[i] == 1){
                     if ((MyMCEvent.BJet2.GetTag() == "") && (MyMCEvent.BJet1.GetTag() == "BJet1")){
                        for (int j = 0; j < GenBhadrons_size; j++)
                        {
                           if ((sqrt((GenJet_Phi[i]-GenBhadrons_Phi[j])*(GenJet_Phi[i]-GenBhadrons_Phi[j]) + (GenJet_Eta[i]-GenBhadrons_Eta[j])*(GenJet_Eta[i]-GenBhadrons_Eta[j])) < 0.4) && (GenBhadrons_PT[j] > 5.0)){
                              MCBTag = true;
                           }       
                        }
                        if (MCBTag){
                        MyMCEvent.BJet2.SetTag("BJet2");
                        MyMCEvent.BJet2.SetIsBTagged(true);
                        MyMCEvent.BJet2.SetCharge(GenJet_Charge[i]);
                        MyMCEvent.BJet2.SetPtEtaPhiM(GenJet_PT[i],GenJet_Eta[i],GenJet_Phi[i], GenJet_Mass[i]);
                        continue;
                        }
                     }
                  
                     if (MyMCEvent.Jet3.GetTag() == ""){
                        MyMCEvent.Jet3.SetTag("Jet3");
                        MyMCEvent.Jet3.SetIsBTagged(false);
                        MyMCEvent.Jet3.SetCharge(GenJet_Charge[i]);
                        MyMCEvent.Jet3.SetPtEtaPhiM(GenJet_PT[i],GenJet_Eta[i],GenJet_Phi[i], GenJet_Mass[i]);
                        continue;
                     }
                     if ((MyMCEvent.Jet4.GetTag() == "") && (MyMCEvent.Jet3.GetTag() == "Jet3")){
                        MyMCEvent.Jet4.SetTag("Jet4");
                        MyMCEvent.Jet4.SetIsBTagged(false);
                        MyMCEvent.Jet4.SetCharge(GenJet_Charge[i]);
                        MyMCEvent.Jet4.SetPtEtaPhiM(GenJet_PT[i],GenJet_Eta[i],GenJet_Phi[i], GenJet_Mass[i]);
                        continue;
                     }                 
                  
                  
               } //end if
         }//end for cycle
      }//end if lepton
      

      for ( int i = 0; i < GenMissingET_size; i++ ){
                  if (MyMCEvent.Neutrino1.GetTag() == "") {
                     MyMCEvent.Neutrino1.SetTag("Neutrino1");
                     //MyMCEvent.Neutrino1.SetPtEtaPhiM(MissingET_MET[i],MissingET_Eta[i],MissingET_Phi[i], MissingET_MET[i]/sin(2*atan(exp(-1.0*MissingET_Eta[i]))));
                     continue;
                  }
                  //if ((MyMCEvent.Neutrino2.GetTag() == "") && (MyMCEvent.BJet1.GetTag() == "BJet1") && GenJet_BTag[i] == 1){
                  //   MyMCEvent.Neutrino2.SetTag("Neutrino2");
                  //   //MyMCEvent.Neutrino2.SetPtEtaPhiM(MissingET_MET[i],MissingET_Eta[i],MissingET_Phi[i], MissingET_MET[i]/sin(2*atan(exp(-1.0*MissingET_Eta[i]))));
                  //   continue;
                  //}
      
      }

      
      //CheckPreSelected(MyMCEvent);
      MCFoundNeutrino = false;
      if (CheckPreSelected(MyMCEvent)){
         //cout << "*********Preselected ********" << endl;
         //MyMCEvent.SetLepton(MaxLepton(MyMCEvent));
         TLorentzVector MCW = MyMCEvent.Jet3 + MyMCEvent.Jet4;
         MyLorentzVector MCWboson;
         MCWboson.SetPtEtaPhiE(MCW.Pt(),MCW.Eta(), MCW.Phi(), MCW.E());
         MCWboson.SetCharge(MyMCEvent.Jet3.GetCharge()+MyMCEvent.Jet4.GetCharge());
         MyMCEvent.SetWHadron(MCWboson);
         //TLorentzVector MCTop1, MCTop2;
         //ComputeNeutrinoPz();
         double MCPx, MCPy, MCPz, MCE, MCk, MCa, MCb, MCc;
         MCPx = GenMissingET_MET[0]*cos(GenMissingET_Phi[0]);
         MCPy = GenMissingET_MET[0]*sin(GenMissingET_Phi[0]);
         MCk = MyMCEvent.GetWHadron().M()*MyMCEvent.GetWHadron().M()/2.0 + MyMCEvent.Lepton.Pt()*GenMissingET_MET[0];
         MCa = MyMCEvent.Lepton.Pt()*MyMCEvent.Lepton.Pt();
         MCb = -2*MCk*MyMCEvent.Lepton.Pz();
         MCc = GenMissingET_MET[0]*GenMissingET_MET[0]*MyMCEvent.Lepton.P()*MyMCEvent.Lepton.P() - MCk*MCk;
         MCPz = MinQuadraticEq(MCa,MCb,MCc); // https://twiki.cern.ch/twiki/bin/view/Main/TopPairProduction
         
         if (MCPz != nan("1")){
            MCE = sqrt(MCPx*MCPx + MCPy*MCPy + MCPz*MCPz);
            MyMCEvent.Neutrino1.SetPxPyPzE(MCPx,MCPy,MCPz,MCE);   
            //MyMCEvent.Neutrino1.SetPtEtaPhiE(sqrt(Px*Px + Py*Py),GenMissingET_Eta[0],GenMissingET_Phi[0],sqrt(Px*Px + Py*Py)/sin(2*atan(exp(-1.0*GenMissingET_Eta[0]))));   
            MCFoundNeutrino = true;
         } else{
            std::cerr << "This should never happen MC level!!!" << std::endl;
         }
         //E = sqrt(Px*Px + Py*Py + Pz*Pz);
         //MyMCEvent.Neutrino1.SetPxPyPzE(Px,Py,Pz,E);
         //MyMCEvent.Neutrino1.SetPtEtaPhiM(MyMCEvent.Neutrino1.Pt(), MyMCEvent.Neutrino1.Eta(), MyMCEvent.Neutrino1.Phi(), MyMCEvent.WHadron.M() );
         GotMCEvent = false;
         if (DeltaR(MyMCEvent.BJet1, MyMCEvent.Lepton) < DeltaR(MyMCEvent.BJet2, MyMCEvent.Lepton)){
            MCTop1 = MyMCEvent.BJet2 + MyMCEvent.WHadron; 
            MyLorentzVector MCFTop1, MCFTop2;
            MCFTop1.SetPtEtaPhiE(MCTop1.Pt(),MCTop1.Eta(), MCTop1.Phi(), MCTop1.E());
            MCFTop1.SetCharge(MyMCEvent.BJet2.GetCharge() + MyMCEvent.WHadron.GetCharge());
            MyMCEvent.SetPseudoTop(MCFTop1);

            Top1_Bjet_MC_Pt = MyMCEvent.BJet2.Pt();
            Top1_Bjet_MC_Eta = MyMCEvent.BJet2.Eta();
            Top1_Bjet_MC_Phi = MyMCEvent.BJet2.Phi();
            Top1_Bjet_MC_E = MyMCEvent.BJet2.E();
            Top1_Bjet_MC_M = MyMCEvent.BJet2.M();

            Top1_Wboson_MC_Pt = MyMCEvent.WHadron.Pt();
            Top1_Wboson_MC_Eta = MyMCEvent.WHadron.Eta();
            Top1_Wboson_MC_Phi = MyMCEvent.WHadron.Phi();
            Top1_Wboson_MC_E = MyMCEvent.WHadron.E();
            Top1_Wboson_MC_M = MyMCEvent.WHadron.M();

            if (MCFoundNeutrino == true){
               TLorentzVector MCWLepton = MyMCEvent.Lepton + MyMCEvent.Neutrino1;
               MyLorentzVector MCWbosonLepton;
               MCWbosonLepton.SetPtEtaPhiE(MCWLepton.Pt(),MCWLepton.Eta(), MCWLepton.Phi(), MCWLepton.E());
               MCWbosonLepton.SetCharge(MyMCEvent.Lepton.GetCharge()+MyMCEvent.Neutrino1.GetCharge());
               MyMCEvent.SetWLepton(MCWbosonLepton);
               MCTop2 = MyMCEvent.BJet1 + MyMCEvent.Lepton + MyMCEvent.Neutrino1; 
               MCFTop2.SetPtEtaPhiE(MCTop2.Pt(),MCTop2.Eta(), MCTop2.Phi(), MCTop2.E());
               MCFTop2.SetCharge(MyMCEvent.BJet1.GetCharge() + MyMCEvent.Lepton.GetCharge());
               MyMCEvent.SetLeptonPseudotop(MCFTop2);

               Top2_Bjet_MC_Pt = MyMCEvent.BJet1.Pt();
               Top2_Bjet_MC_Eta = MyMCEvent.BJet1.Eta();
               Top2_Bjet_MC_Phi = MyMCEvent.BJet1.Phi();
               Top2_Bjet_MC_E = MyMCEvent.BJet1.E();
               Top2_Bjet_MC_M = MyMCEvent.BJet1.M();

               Top2_Lepton_MC_Pt = MyMCEvent.Lepton.Pt();
               Top2_Lepton_MC_Eta = MyMCEvent.Lepton.Eta();
               Top2_Lepton_MC_Phi = MyMCEvent.Lepton.Phi();
               Top2_Lepton_MC_E = MyMCEvent.Lepton.E();
               Top2_Lepton_MC_M = MyMCEvent.Lepton.M();

               Top2_Neutrino_MC_Pt = MyMCEvent.Neutrino1.Pt();
               Top2_Neutrino_MC_Eta = MyMCEvent.Neutrino1.Eta();
               Top2_Neutrino_MC_Phi = MyMCEvent.Neutrino1.Phi();
               Top2_Neutrino_MC_E = MyMCEvent.Neutrino1.E();
               Top2_Neutrino_MC_M = MyMCEvent.Neutrino1.M();

               GotMCEvent = true;
            }
            //cout << "dR1: " << DeltaR(MyMCEvent.BJet1, MyMCEvent.Lepton) << " < " << DeltaR(MyMCEvent.BJet2, MyMCEvent.Lepton) << endl;  
         } else if (FoundNeutrino == true){
            MCTop1 = MyMCEvent.BJet1 + MyMCEvent.WHadron;
            MyLorentzVector MCFTop1, MCFTop2;
            MCFTop1.SetPtEtaPhiE(MCTop1.Pt(),MCTop1.Eta(), MCTop1.Phi(), MCTop1.E());
            MCFTop1.SetCharge(MyMCEvent.BJet1.GetCharge() + MyMCEvent.WHadron.GetCharge());
            MyMCEvent.SetPseudoTop(MCFTop1);

            Top1_Bjet_MC_Pt = MyMCEvent.BJet1.Pt();
            Top1_Bjet_MC_Eta = MyMCEvent.BJet1.Eta();
            Top1_Bjet_MC_Phi = MyMCEvent.BJet1.Phi();
            Top1_Bjet_MC_E = MyMCEvent.BJet1.E();
            Top1_Bjet_MC_M = MyMCEvent.BJet1.M();

            Top1_Wboson_MC_Pt = MyMCEvent.WHadron.Pt();
            Top1_Wboson_MC_Eta = MyMCEvent.WHadron.Eta();
            Top1_Wboson_MC_Phi = MyMCEvent.WHadron.Phi();
            Top1_Wboson_MC_E = MyMCEvent.WHadron.E();
            Top1_Wboson_MC_M = MyMCEvent.WHadron.M();

            if (MCFoundNeutrino == true){
               TLorentzVector MCWLepton = MyMCEvent.Lepton + MyMCEvent.Neutrino1;
               MyLorentzVector MCWbosonLepton;
               MCWbosonLepton.SetPtEtaPhiE(MCWLepton.Pt(),MCWLepton.Eta(), MCWLepton.Phi(), MCWLepton.E());
               MCWbosonLepton.SetCharge(MyMCEvent.Lepton.GetCharge()+MyMCEvent.Neutrino1.GetCharge());
               MyMCEvent.SetWLepton(MCWbosonLepton);
               MCTop2 = MyMCEvent.BJet2 + MyMCEvent.Lepton + MyMCEvent.Neutrino1; 
               MCFTop2.SetPtEtaPhiE(MCTop2.Pt(),MCTop2.Eta(), MCTop2.Phi(), MCTop2.E());
               MCFTop2.SetCharge(MyMCEvent.BJet2.GetCharge() + MyMCEvent.Lepton.GetCharge());
               MyMCEvent.SetLeptonPseudotop(MCFTop2);

               Top2_Bjet_MC_Pt = MyMCEvent.BJet2.Pt();
               Top2_Bjet_MC_Eta = MyMCEvent.BJet2.Eta();
               Top2_Bjet_MC_Phi = MyMCEvent.BJet2.Phi();
               Top2_Bjet_MC_E = MyMCEvent.BJet2.E();
               Top2_Bjet_MC_M = MyMCEvent.BJet2.M();

               Top2_Lepton_MC_Pt = MyMCEvent.Lepton.Pt();
               Top2_Lepton_MC_Eta = MyMCEvent.Lepton.Eta();
               Top2_Lepton_MC_Phi = MyMCEvent.Lepton.Phi();
               Top2_Lepton_MC_E = MyMCEvent.Lepton.E();
               Top2_Lepton_MC_M = MyMCEvent.Lepton.M();

               Top2_Neutrino_MC_Pt = MyMCEvent.Neutrino1.Pt();
               Top2_Neutrino_MC_Eta = MyMCEvent.Neutrino1.Eta();
               Top2_Neutrino_MC_Phi = MyMCEvent.Neutrino1.Phi();
               Top2_Neutrino_MC_E = MyMCEvent.Neutrino1.E();
               Top2_Neutrino_MC_M = MyMCEvent.Neutrino1.M();
               GotMCEvent = true;
            }
            //cout << "dR2: " << DeltaR(MyMCEvent.BJet1, MyMCEvent.Lepton) << " > " << DeltaR(MyMCEvent.BJet2, MyMCEvent.Lepton) << endl;
         };
         
         if ((MCFoundNeutrino == true)&&(GotMCEvent == true)){ // && (DeltaR(MyMCEvent.BJet1, MyMCEvent.Lepton) > 0.2) && (DeltaR(MyMCEvent.BJet2, MyMCEvent.Lepton) > 0.2) && (DeltaR(MyMCEvent.Jet3, MyMCEvent.Lepton) > 0.2) && (DeltaR(MyMCEvent.Jet4, MyMCEvent.Lepton) > 0.2)) {
         TLorentzVector MCTopPair;
         MCTopPair = MCTop1 + MCTop2;
         MyLorentzVector MCFTopPair;
         MCFTopPair.SetPtEtaPhiE(MCTopPair.Pt(),MCTopPair.Eta(), MCTopPair.Phi(), MCTopPair.E());
         MCFTopPair.SetCharge(MyMCEvent.PseudoTop.GetCharge()+MyMCEvent.LeptonPseudotop.GetCharge());
         MyMCEvent.SetPseudoTopPair(MCFTopPair);
         MyMCEvent.Setm_PreSelected(true);    

         MCTopMass2->Fill(MyMCEvent.LeptonPseudotop.M());
         MCTopMass1->Fill(MyMCEvent.PseudoTop.M());
         MCWMass->Fill(MyMCEvent.WHadron.M());
         MCHadTopPt->Fill(MyMCEvent.PseudoTop.Pt());
         MCHadTopEta->Fill(MyMCEvent.PseudoTop.Eta());
         MCTopPairPt->Fill(MyMCEvent.PseudoTopPair.Pt());
         MCTopPairMass->Fill(MyMCEvent.PseudoTopPair.M());
         MCTopPairEta->Fill(MyMCEvent.PseudoTopPair.Eta());
         MCTopPairDeltaPhi->Fill(MyMCEvent.LeptonPseudotop.Phi()-MyMCEvent.PseudoTop.Phi());
         MCWLeptonVsLeptonPseudoTop->Fill(MyMCEvent.LeptonPseudotop.M(),MyMCEvent.WLepton.M());
         MCWLeptonVsNeutrinoPt->Fill(MyMCEvent.Neutrino1.Pt(), MyMCEvent.WLepton.M());
         MCLeptonPseudoTopVsNeutrinoPt->Fill(MyMCEvent.Neutrino1.Pt(), MyMCEvent.LeptonPseudotop.M());
         MCWHadronVsHadronPseudoTop->Fill(MyMCEvent.PseudoTop.M(),MyMCEvent.WHadron.M());
         MCLeptonPseudoTopDeltaMassLeptonW->Fill(MyMCEvent.LeptonPseudotop.M()-MyMCEvent.WLepton.M());
         MCHadronPseudoTopDeltaMassHadronW->Fill(MyMCEvent.PseudoTop.M()-MyMCEvent.WHadron.M());
         //MCLeptonPseudoTopVsTopPairEta->Fill(MyMCEvent.LeptonPseudotop.Eta(), MyMCEvent.PseudoTopPair.Eta());
         //MCHadronPseudoTopVsTopPairEta->Fill(MyMCEvent.PseudoTop.Eta(), MyMCEvent.PseudoTopPair.Eta());
         MCLeptonPseudoTopVsTopPairEta->Fill(MyMCEvent.PseudoTop.Phi(), MyMCEvent.PseudoTop.Eta());
         MCHadronPseudoTopVsTopPairEta->Fill(MyMCEvent.LeptonPseudotop.Phi(), MyMCEvent.LeptonPseudotop.Eta());
         MyMCEvent.Setm_FinalSelected(true);
         //MyMCEvent.Print();
         Top1_MC_Pt = MCTop1.Pt();
         Top1_MC_Eta = MCTop1.Eta();
         Top1_MC_Phi = MCTop1.Phi();
         Top1_MC_E = MCTop1.E();
         Top1_MC_M = MCTop1.M();
         Top2_MC_Pt = MCTop2.Pt();
         Top2_MC_Eta = MCTop2.Eta();
         Top2_MC_Phi = MCTop2.Phi();
         Top2_MC_E = MCTop2.E();
         Top2_MC_M = MCTop2.M();

         ttbar_MC_Pt = (MCTop1 + MCTop2).Pt();
         ttbar_MC_Eta = (MCTop1 + MCTop2).Eta();
         ttbar_MC_Phi = (MCTop1 + MCTop2).Phi();
         ttbar_MC_E = (MCTop1 + MCTop2).E();
         ttbar_MC_M = (MCTop1 + MCTop2).M();

         }
         }

         if ((MyDataEvent.Getm_FinalSelected()) && (MyMCEvent.Getm_FinalSelected())){
            MigraHadTopPt->Fill(MyDataEvent.PseudoTop.Pt(),MyMCEvent.PseudoTop.Pt());
            MigraHadTopEta->Fill(MyDataEvent.PseudoTop.Eta(),MyMCEvent.PseudoTop.Eta());
            MigraTopPairPt->Fill(MyDataEvent.PseudoTopPair.Pt(),MyMCEvent.PseudoTopPair.Pt());
            MigraTopPairMass->Fill(MyDataEvent.PseudoTopPair.M(),MyMCEvent.PseudoTopPair.M());
            MigraTopPairEta->Fill(MyDataEvent.PseudoTopPair.Eta(),MyMCEvent.PseudoTopPair.Eta());
            int_Event_size = Event_size;
            int_GenLJet_size = GenLJet_size;
            int_GenJet_size = GenJet_size;
            int_GenElectron_size = GenElectron_size;
            int_GenMuon_size = GenMuon_size;
            int_GenTop_size = GenTop_size;
            int_GenPhoton_size = GenPhoton_size;
            int_GenMissingET_size = GenMissingET_size;
            int_GenZPrime_size = GenZPrime_size;
            int_GenW_size = GenW_size;
            int_GenBhadrons_size = GenBhadrons_size;
            int_Jet_size = Jet_size;
            int_LJet_size = LJet_size;
            int_JetJES_size = JetJES_size;
            int_LJetJES_size = LJetJES_size;
            int_Electron_size = Electron_size;
            int_Photon_size = Photon_size;
            int_Muon_size = Muon_size;
            int_MissingET_size = MissingET_size;
            int_ScalarHT_size = ScalarHT_size;

            tree->Fill();
            tree_particle->Fill();
            tree_reco->Fill();
         }


      //cout << jentry << endl;
      //if (jentry % 10000 == 0){
      //   cout << "Processing: " << jentry << endl;
      //}
   }
   tree->Write();
   vector <TCanvas*> CanVec;
   vector <TH1*> THVec;
   THVec.push_back(TopMass1);
   THVec.push_back(TopMass2);
   THVec.push_back(WMass);
   THVec.push_back(HadTopPt);
   THVec.push_back(HadTopEta);
   THVec.push_back(TopPairPt);
   THVec.push_back(TopPairMass);
   THVec.push_back(TopPairEta);
   THVec.push_back(TopPairDeltaPhi);
   THVec.push_back(WLeptonVsLeptonPseudoTop);
   THVec.push_back(WLeptonVsNeutrinoPt);
   THVec.push_back(LeptonPseudoTopVsNeutrinoPt);
   THVec.push_back(WHadronVsHadronPseudoTop);
   THVec.push_back(LeptonPseudoTopDeltaMassLeptonW);
   THVec.push_back(HadronPseudoTopDeltaMassHadronW);

   THVec.push_back(MCTopMass1);
   THVec.push_back(MCTopMass2);
   THVec.push_back(MCWMass);
   THVec.push_back(MCHadTopPt);
   THVec.push_back(MCHadTopEta);
   THVec.push_back(MCTopPairPt);
   THVec.push_back(MCTopPairMass);
   THVec.push_back(MCTopPairEta);
   THVec.push_back(MCTopPairDeltaPhi);
   THVec.push_back(MCWLeptonVsLeptonPseudoTop);
   THVec.push_back(MCWLeptonVsNeutrinoPt);
   THVec.push_back(MCLeptonPseudoTopVsNeutrinoPt);
   THVec.push_back(MCWHadronVsHadronPseudoTop);
   THVec.push_back(MCLeptonPseudoTopDeltaMassLeptonW);
   THVec.push_back(MCHadronPseudoTopDeltaMassHadronW);

   THVec.push_back(MigraHadTopPt);
   THVec.push_back(MigraHadTopEta);
   THVec.push_back(MigraTopPairPt);
   THVec.push_back(MigraTopPairMass);
   THVec.push_back(MigraTopPairEta);
   //THVec.push_back(LjetMulti);
   //THVec.push_back(LjetEta);
   //THVec.push_back(LjetPhi);
   //THVec.push_back(LjetPt);
   //THVec.push_back(LjetMass);
   //THVec.push_back(GenLjetMulti);
   //THVec.push_back(GenLjetEta);
   //THVec.push_back(GenLjetPhi);
   //THVec.push_back(GenLjetPt);
   //THVec.push_back(GenLjetMass);

   //THVec.push_back(JetMulti);
   //THVec.push_back(JetEta);
   //THVec.push_back(JetPhi);
   //THVec.push_back(JetPt);
   //THVec.push_back(JetMass);
   //THVec.push_back(GenJetMulti);
   //THVec.push_back(GenJetEta);
   //THVec.push_back(GenJetPhi);
   //THVec.push_back(GenJetPt);
   //THVec.push_back(GenJetMass);

   //THVec.push_back(LeadingLjetEta);
   //THVec.push_back(LeadingLjetPhi);
   //THVec.push_back(LeadingLjetPt);
   //THVec.push_back(LeadingLjetMass);
   //THVec.push_back(GenLeadingLjetEta);
   //THVec.push_back(GenLeadingLjetPhi);
   //THVec.push_back(GenLeadingLjetPt);
   //THVec.push_back(GenLeadingLjetMass);

   //THVec.push_back(LeadingJetEta);
   //THVec.push_back(LeadingJetPhi);
   //THVec.push_back(LeadingJetPt);
   //THVec.push_back(LeadingJetMass);
   //THVec.push_back(GenLeadingJetEta);
   //THVec.push_back(GenLeadingJetPhi);
   //THVec.push_back(GenLeadingJetPt);
   //THVec.push_back(GenLeadingJetMass);

   //THVec.push_back(ElectronEta);
   //THVec.push_back(ElectronPT);

   //THVec.push_back(MuonEta);
   //THVec.push_back(MuonPT);

   //THVec.push_back(JetJESEta);
   //THVec.push_back(JetJESPT);
   ////int NumberOfHistograms = THVec.size();
   ////cout << "size" << THVec.size() << endl;

   for ( unsigned int i=0; i < THVec.size(); i++ ){
      //TString CanvasName = Form("Canvas_%d", i);
      //cout << CanvasName << endl;
      TCanvas * can = new TCanvas(THVec.at(i)->GetName(), THVec.at(i)->GetName(), 400, 400);
      CanVec.push_back(can);
   }
   outfile->Write();
   for ( unsigned int i=0; i < THVec.size(); i++ ){
   CanVec.at(i)->cd();
   gStyle->SetOptStat(111111111);
   THVec.at(i)->Draw();
   }
   
}


// LIST OF VARIABLES
// LjetMulti
// LjetEta
// LjetPhi
// LjetPt
// LjetMass
// GenLjetMulti
// GenLjetEta
// GenLjetPhi
// GenLjetPt
// GenLjetMass