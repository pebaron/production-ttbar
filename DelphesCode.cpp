#include "DelphesTree.h"

#include "HistoMaker.h"

#include <TH2.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "MyConsts.h"


// __________________________________________________________________


bool DelphesTree::IsBtaggedPtclLevel(double jpt, double jeta, double jphi, double jm)
{

  double DR = -1;
  TLorentzVector jet;
  jet.SetPtEtaPhiM(jpt, jeta, jphi, jm);    TLorentzVector bhad;
  for (int ib = 0; ib < GenBhadrons_size; ++ib)  {
    bhad.SetPtEtaPhiM(GenBhadrons_PT[ib], GenBhadrons_Eta[ib], GenBhadrons_Phi[ib], GenBhadrons_Mass[ib]);
    if (bhad.Pt() < 5.) // c.f. ATLAS paper!
      continue;
    DR = jet.DeltaR(bhad);
    if (DR < 0.4 )
      return true;
    
  }
  return false;
  
}

// __________________________________________________________________

double JEScorr(double eta, double pt)
{
  return sqrt( pow(3.0 - 0.2*(abs(eta)), 2) / pt + 1.0 );
}


// __________________________________________________________________

bool IsTopTagged(double mass, double tau32)
{	
	return ( (fabs(mass - kmt) < kTopMassWindow) && tau32 < kTau32Cut);
	
}

// __________________________________________________________________

bool IsWTagged(double mass, double tau21)
{	
	return ( (fabs(mass - kmW) < kWMassWindow) && tau21 < kTau21Cut);
	
}

// __________________________________________________________________


// __________________________________________________________________

vector<TMyLorentzVector*> DelphesTree::MakeGenTops(double ptcut, double etacut) 
{


   vector<TMyLorentzVector*> gentops;
   /*
   cout << "=== in DelphesTree::MakeGenTops ===" << endl;
   cout << " Parton tops: " << GenTop_size << endl;
   for (unsigned int i = 0; i < GenTop_size; ++i) {
     cout << "GenTop " << i << " status " << GenTop_Status[i] << " pdgid: " << GenTop_PID[i] << " pT: " << GenTop_PT[i] << endl;
    // before FSR:
     //     if (GenTop_Status[i] < 29) {
     //       TMyLorentzVector *gentop = new TMyLorentzVector(GenTop_PT[i], GenTop_Eta[i], GenTop_Phi[i], GenTop_Mass[i], 0., 0.);
     //       gentops.push_back(gentop);
     //}
   }
   */
  // take last tops in chain:
   int i = GenTop_size - 2;
   int j = GenTop_size - 1;
   if (GenTop_size > 1) {
     if (GenTop_PT[i] > ptcut && GenTop_PT[j] > ptcut && fabs(GenTop_Eta[i]) < etacut && fabs(GenTop_Eta[j]) < etacut )  {
       TMyLorentzVector *gentop1 = new TMyLorentzVector(GenTop_PT[i], GenTop_Eta[i], GenTop_Phi[i], GenTop_Mass[i], 0., 0.);
       gentops.push_back(gentop1);
       TMyLorentzVector *gentop2 = new TMyLorentzVector(GenTop_PT[j], GenTop_Eta[j], GenTop_Phi[j], GenTop_Mass[j], 0., 0.);
       gentops.push_back(gentop2);
     }
   }
   
    return gentops;

}


// __________________________________________________________________

vector<TMyLorentzVector*> DelphesTree::MakeGenDijets(vector<TMyLorentzVector*> GenTops) 
{
   
   
   vector<TMyLorentzVector*> gendijets;
   
   if (GenTop_size > 1) {
     TMyLorentzVector *mygendijet = new TMyLorentzVector(*GenTops[0]);
     (*mygendijet)  += *GenTops[1];
     gendijets.push_back(mygendijet);
   }
    return gendijets;
}


// __________________________________________________________________

vector<TMyLorentzVector*> DelphesTree::MakeJets(bool DetLevel, bool LJets, double ptcut, double etacut, bool CorrectJES, kSelection Selection) 
{

  int nn = 0;
  if (LJets)
    nn = DetLevel ? LJetJES_size : GenLJet_size;
  else
    nn = DetLevel ? JetJES_size : GenJet_size; 
  
  vector<TMyLorentzVector*> topjets;
  vector<TMyLorentzVector*> wjets;
  vector<TMyLorentzVector*> smalljets;

  if (Selection == kBoostedTop || Selection == kSemiBoosted || Selection == kBoostedW || Selection == kResolved) {
    // loop over jets
  
    for (int ijet = 0; ijet < nn; ++ijet) {
      double jesc = 1.;
      if (CorrectJES && DetLevel) {
        if (LJets)
          jesc = JEScorr(LJet_Eta[ijet], LJet_PT[ijet]);
        else
          jesc = JEScorr(Jet_Eta[ijet], Jet_PT[ijet]);
      }

      double Pt, Eta, Phi, M, tau32, tau21;
      bool btag = false;

      if (LJets) {
	Pt = (DetLevel ? jesc*LJetJES_PT[ijet] : GenLJet_PT[ijet]);
	// E = (DetLevel ? jesc*LJetJES_T[ijet] : GenLJet_T[ijet]);
	Eta = (DetLevel ? LJetJES_Eta[ijet] : GenLJet_Eta[ijet]);
	Phi = (DetLevel ? LJetJES_Phi[ijet] : GenLJet_Phi[ijet]);
	M = (DetLevel ? jesc*LJetJES_Mass[ijet] : GenLJet_Mass[ijet]);
	tau32 = (DetLevel ? LJetJES_Tau[ijet][2] / LJetJES_Tau[ijet][1] : GenLJet_Tau[ijet][2] / GenLJet_Tau[ijet][1]);
	tau21 = (DetLevel ? LJetJES_Tau[ijet][1] / LJetJES_Tau[ijet][0] : GenLJet_Tau[ijet][1] / GenLJet_Tau[ijet][0]);
	if (DetLevel) {
	  btag = LJetJES_BTag[ijet];
	} else {
	  btag = IsBtaggedPtclLevel(GenLJet_PT[ijet], GenLJet_Eta[ijet], GenLJet_Phi[ijet], GenLJet_Mass[ijet]);
	}
      } else {
	Pt = (DetLevel ? jesc*JetJES_PT[ijet] : GenJet_PT[ijet]);
	// E = (DetLevel ? jesc*JetJES_T[ijet] : GenJet_T[ijet]);
	Eta = (DetLevel ? JetJES_Eta[ijet] : GenJet_Eta[ijet]);
	Phi = (DetLevel ? JetJES_Phi[ijet] : GenJet_Phi[ijet]);
	M = (DetLevel ? jesc*JetJES_Mass[ijet] : GenJet_Mass[ijet]);
	tau32 = (DetLevel ? JetJES_Tau[ijet][2] / JetJES_Tau[ijet][1] : GenJet_Tau[ijet][2] / GenJet_Tau[ijet][1]);
	tau21 = (DetLevel ? JetJES_Tau[ijet][1] / JetJES_Tau[ijet][0] : GenJet_Tau[ijet][1] / GenJet_Tau[ijet][0]);
	if (DetLevel) {
	  btag = JetJES_BTag[ijet];
	} else {
	  btag = IsBtaggedPtclLevel(GenJet_PT[ijet], GenJet_Eta[ijet], GenJet_Phi[ijet], GenJet_Mass[ijet]);
	}
      }
    
      //cout << "  Pt=" << Pt << " Eta=" << Eta << " Phi=" << Phi << " M=" << M << " tau32=" << tau32 << " tau21=" << tau21 << endl;
	
      if ( (Pt > ptcut) && (fabs(Eta) < etacut) ) {
      
	if (IsTopTagged(M, tau32)) {
	  TMyLorentzVector *jet = new TMyLorentzVector(Pt, Eta, Phi, M, tau32, tau21);
	  topjets.push_back(jet);
	}
      
	if (IsWTagged(M, tau21)) {
	  TMyLorentzVector *jet = new TMyLorentzVector(Pt, Eta, Phi, M, tau32, tau21);
	  wjets.push_back(jet);
	}
	
	if (!LJets) {
	  TMyLorentzVector *jet = new TMyLorentzVector(Pt, Eta, Phi, M, 0., 0., btag);
	  //	  if (!DetLevel)
	  //	    cout << " ........ptcl jet " << ijet << " :: Pt=" << Pt << " Eta=" << Eta << " Phi=" << Phi << " M=" << M << " btag=" <<  btag  << endl;
	  smalljets.push_back(jet);
	}
	//cout << "  jet Pt,Eta,Phi,M: " << jet->Pt() << " " <<  jet->Eta() << " " <<  jet->Phi() << " " <<  jet->M() << " " <<  endl;
      }
  
      //cout << "  Created " << jets.size() << " jets." << endl;

    
	
    }

  } else {
    // NOT SUPPORTED!!!
    
  }
 
  // TODO: resort all arrays by pT!?

  switch (Selection) {

  case kBoostedTop:
    // will later check 2 large-R jets top tagged
    return topjets;
    break;

  case kBoostedW:
    // will later check for 2 large-R jets W tagged
    return wjets;
    break;

  case kSemiBoosted:
    {
      // one large-R jet top tagged, other W tagged
      vector<TMyLorentzVector*> jets;
      // use the leading top jet and leading W jet:
      if (wjets.size() > 0) 
	jets.push_back(wjets[0]);
      if (topjets.size() > 0) 
	jets.push_back(topjets[0]);
      return jets;
    }
    break;

  case kNONE:
    {
      for (auto wjet : wjets) {
	topjets.push_back(wjet);
      }
      return topjets;
    }
    break;
    
  case kResolved:
    return smalljets;
    break;

  } // switch
  
  return smalljets;
}

// __________________________________________________________________

void DelphesTree::Loop(TString outtag)
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();

  TFile *outfile = new TFile("analyzed_histos_" + outtag + ".root", "recreate");

//  TH1D *h_NLJetsHighPt = new TH1D("NLJetsHighPt", "n_{LJets}^{det} at high p_{T}", 25, 0, 25);
//  TH1D *h_NGenLJetsHighPt = new TH1D("NGenLJetsHighPt", "n_{LJets}^{gen} at high p_{T}", 25, 0, 25);


  TString LastCutName = "PtNjetsTau32MassCut";

	HistoMaker *hmaker_ptcl = new HistoMaker("Particle");
	hmaker_ptcl -> AddCutLevel("NoCuts");
	hmaker_ptcl -> AddCutLevel("PtCut");
	hmaker_ptcl -> AddCutLevel("PtNjetsCut");
	hmaker_ptcl -> AddCutLevel("PtNjetsTau32Cut");
	hmaker_ptcl -> AddCutLevel(LastCutName);
	hmaker_ptcl -> MakeAllJetHistos();	
  hmaker_ptcl -> MakeDijetHistos(LastCutName);	  
  
	HistoMaker *hmaker_det = new HistoMaker("Detector");
  hmaker_det -> AddCutLevel("NoCuts");
	hmaker_det -> AddCutLevel("PtCut");
	hmaker_det -> AddCutLevel("PtNjetsCut");
	hmaker_det -> AddCutLevel("PtNjetsTau32Cut");
	hmaker_det -> AddCutLevel(LastCutName);
	hmaker_det -> MakeAllJetHistos();
  hmaker_det -> MakeDijetHistos(LastCutName);	    

// TODO: add parton distributions after reco and particle cuts!

	HistoMaker *hmaker_det_parton = new HistoMaker("Detector_parton");
  hmaker_det_parton -> AddCutLevel(LastCutName);
	hmaker_det_parton -> MakeAllJetHistos();
  hmaker_det_parton -> MakeDijetHistos(LastCutName);	    


  //binned in ptcl quantities
  HistoMaker *hmaker_detptcl_ptcl = new HistoMaker("DetectorAndParticle_ptcl");
  hmaker_detptcl_ptcl -> AddCutLevel(LastCutName);  
  hmaker_detptcl_ptcl -> MakeAllJetHistos();
  hmaker_detptcl_ptcl -> MakeDijetHistos(LastCutName);	    
  
  //binned in det quantities
  HistoMaker *hmaker_detptcl_det = new HistoMaker("DetectorAndParticle_det");
  hmaker_detptcl_det -> AddCutLevel(LastCutName);  
  hmaker_detptcl_det -> MakeAllJetHistos();
  hmaker_detptcl_det -> MakeDijetHistos(LastCutName);	    
  
  // migrations particle-detector
  HistoMaker *hmaker_migra_ptcl = new HistoMaker("Migrations_ptcl_det");
  hmaker_migra_ptcl -> AddCutLevel(LastCutName);  
  hmaker_migra_ptcl -> MakeMigrations(LastCutName, "Particle", "Detector");	  
 
  // migrations parton-detector
  HistoMaker *hmaker_migra_parton = new HistoMaker("Migrations_parton_det");
  hmaker_migra_parton -> AddCutLevel(LastCutName);  
  hmaker_migra_parton -> MakeMigrations(LastCutName, "Parton", "Detector");	  
 
  // migrations parton-particle
  HistoMaker *hmaker_migra_partonptcl = new HistoMaker("Migrations_parton_ptcl");
  hmaker_migra_partonptcl -> AddCutLevel(LastCutName);  
  hmaker_migra_partonptcl -> MakeMigrations(LastCutName, "Parton", "Particle");	  
 
 
  int verbose = 10000;
  int ToRunOver = nentries;		
  // HACK! 
  // ToRunOver = 10000;		
  int debug = 0;
      
  Long64_t nbytes = 0, nb = 0;
  
  cout << "Will loop over " << ToRunOver << " events." << endl;
  
  for (Long64_t jentry=0; jentry<ToRunOver;jentry++) {

	double EventWeight = 1.;

    if (jentry % verbose == 0) {
      cout << "Processing " << jentry << "/" << nentries << endl;
    }
    if (debug > 0) cout << "Event " << jentry << endl;	

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    // STEERING!!!
	  bool CorrectJES = false;
   
    // CUTS!
    double etacut = 2.0;
    double ptcut = 200.;
    double tau32cut = 0.75;
    double masscut = 100.;

    bool passedDetector = false;
    bool passedParticle = false;

  // +------------------------+
  // |  Parton level cuts     |
  // +------------------------+
  // none for the moment
  if (debug > 1) cout << "  ok, making parton tops1" << endl;	
  vector<TMyLorentzVector*> partonTops = MakeGenTops(0., 999.);
  if (debug > 1) cout << "  ok, making parton tops2" << endl;	
  vector<TMyLorentzVector*> partonDijets = MakeGenDijets(partonTops);
  if (debug > 1) cout << "  ok, making parton tops3" << endl;	
  vector<TMyLorentzVector*> dummyjets;

  // +------------------------+
  // |  Detector level cuts   |
  // +------------------------+
          
  // no pT cut, detector jets:
	vector<TMyLorentzVector*>  alldetLjets = MakeJets(1, 1, 0., etacut, CorrectJES);
  vector<TMyLorentzVector*>  alldetjets  = MakeJets(1, 0, 0., etacut, CorrectJES);
	if (debug > 1) cout << "  got " << alldetLjets.size() << " jets." << endl;
	hmaker_det -> FillJetHistos("NoCuts", "LJet", alldetLjets, EventWeight, kallJets, 1);
	hmaker_det -> FillJetHistos("NoCuts", "Jet", alldetjets, EventWeight, kallJets, 0);
	
	// pt cuts on all jets, get the collection of those passing:
	vector<TMyLorentzVector*> detLjets    = MakeJets(1, 1, ptcut, etacut, CorrectJES);
  vector<TMyLorentzVector*> detjets     = MakeJets(1, 0, ptcut, etacut, CorrectJES);
	if (debug > 1) cout << "  got " << detLjets.size() << " jets in pt eta acceptance." << endl;	
	hmaker_det -> FillJetHistos("PtCut", "LJet", detLjets, EventWeight, kallJets, 1);
  hmaker_det -> FillJetHistos("PtCut", "Jet", detjets, EventWeight, kallJets, 0);
	
  vector<TMyLorentzVector*> detDijets; 
  
	if (detLjets.size() > 1) {
		if (debug > 1) cout << "  first jet pt: " << detLjets[0]->Pt() << endl;	
		if (debug > 1) cout << "  ok, passed njets cut" << endl;	
		hmaker_det -> FillJetHistos("PtNjetsCut", "LJet", detLjets, EventWeight, kallJets, 1);	
    hmaker_det -> FillJetHistos("PtNjetsCut", "Jet", detjets, EventWeight, kallJets, 0);	
	
		// now mass cut on the two leading jets:
	  // TODO: make this TopTag
  	if ( (detLjets[0]->Tau32() < tau32cut) && (detLjets[1]->Tau32() < tau32cut) ) {
			if (debug > 1) cout << "  ok, passed tau cut" << endl;	
			hmaker_det -> FillJetHistos("PtNjetsTau32Cut", "LJet", detLjets, EventWeight, kallJets, 1);	
      hmaker_det -> FillJetHistos("PtNjetsTau32Cut", "Jet", detjets, EventWeight, kallJets, 0);	
		
    
    // TODO: make this SemiBoostedTag
      if ( (detLjets[0]->M() > masscut) && (detLjets[1]->M() < masscut) ) {
	if (debug > 1) cout << "  ok, passed mass cut" << endl;	
	hmaker_det -> FillJetHistos(LastCutName, "LJet", detLjets, EventWeight, kallJets, 1);	
	hmaker_det -> FillJetHistos(LastCutName, "Jet", detjets, EventWeight, kallJets, 0);	
      
      TLorentzVector Dijet = (*detLjets[0] + *detLjets[1]).GetTLorentzVector();
      detDijets.push_back(new TMyLorentzVector(Dijet));
      hmaker_det -> FillJetHistos(LastCutName, "Dijet", detDijets, EventWeight, kallJets, 0);	
     
      passedDetector = true;
        
      // fill migrations: parton-detector:
      hmaker_migra_parton -> FillMigrations(LastCutName, partonTops, dummyjets, partonDijets, detLjets, detjets, detDijets, EventWeight);	  
        
       hmaker_det_parton -> FillJetHistos(LastCutName, "LJet", partonTops, EventWeight, kallJets, 1);	
       hmaker_det_parton -> FillJetHistos(LastCutName, "Dijet", partonDijets, EventWeight, kallJets, 0);	
		}
    
  } // tau32
    // make this resolved?
    
  } // njets


  // +------------------------+
  // |  Particle level cuts   |
  // +------------------------+
  
  CorrectJES = 0;
  
  // no pT cut, detector jets:
	vector<TMyLorentzVector*>  allptclLjets = MakeJets(0, 1, 0., etacut, CorrectJES);
  vector<TMyLorentzVector*>  allptcljets  = MakeJets(0, 0, 0., etacut, CorrectJES);
  if (debug > 1) cout << "  got ptcl " << allptclLjets.size() << " jets." << endl;
  hmaker_ptcl -> FillJetHistos("NoCuts", "LJet", allptclLjets, EventWeight, kallJets, 1);
  hmaker_ptcl -> FillJetHistos("NoCuts", "Jet", allptcljets, EventWeight, kallJets, 0);
  
  // pt cuts on all jets, get the collection of those passing:
  vector<TMyLorentzVector*> ptclLjets    = MakeJets(0, 1, ptcut, etacut, CorrectJES);
  vector<TMyLorentzVector*> ptcljets     = MakeJets(0, 0, ptcut, etacut, CorrectJES);
  if (debug > 1) cout << "  got " << ptclLjets.size() << " jets in pt eta acceptance." << endl;	
  hmaker_ptcl -> FillJetHistos("PtCut", "LJet", ptclLjets, EventWeight, kallJets, 1);
  hmaker_ptcl -> FillJetHistos("PtCut", "Jet", ptcljets, EventWeight, kallJets, 0);
  
  vector<TMyLorentzVector*> ptclDijets; 
  	
  if (ptclLjets.size() > 1) {
    if (debug > 1) cout << "  first jet pt: " << ptclLjets[0]->Pt() << endl;	
    if (debug > 1) cout << "  ok, passed ptcl njets cut" << endl;	
    hmaker_ptcl -> FillJetHistos("PtNjetsCut", "LJet", ptclLjets, EventWeight, kallJets, 1);	
    hmaker_ptcl -> FillJetHistos("PtNjetsCut", "Jet", ptcljets, EventWeight, kallJets, 0);	
	
    // now mass cut on the two leading jets:
    if ( (ptclLjets[0]->Tau32() < tau32cut) && (ptclLjets[1]->Tau32() < tau32cut) ) {
      if (debug > 1) cout << "  ok, passed ptcl tau cut" << endl;	
      hmaker_ptcl -> FillJetHistos("PtNjetsTau32Cut", "LJet", ptclLjets, EventWeight, kallJets, 1);	
      hmaker_ptcl -> FillJetHistos("PtNjetsTau32Cut", "Jet", ptcljets, EventWeight, kallJets, 0);	
		
      if ( (ptclLjets[0]->M() > masscut) && (ptclLjets[1]->M() < masscut) ) {
	if (debug > 1) cout << "  ok, passed ptcl mass cut" << endl;	
	hmaker_ptcl -> FillJetHistos(LastCutName, "LJet", ptclLjets, EventWeight, kallJets, 1);	
	hmaker_ptcl -> FillJetHistos(LastCutName, "Jet", ptcljets, EventWeight, kallJets, 0);	
      
      TLorentzVector Dijet = (*ptclLjets[0] + *ptclLjets[1]).GetTLorentzVector();
      ptclDijets.push_back(new TMyLorentzVector(Dijet));
      hmaker_ptcl -> FillJetHistos(LastCutName, "Dijet", ptclDijets, EventWeight, kallJets, 0);	
      
      passedParticle = true;
      
      // fill migrations: parton-particle:
      hmaker_migra_partonptcl -> FillMigrations(LastCutName, partonTops, dummyjets, partonDijets, ptclLjets, ptcljets, ptclDijets, EventWeight);	  
      
      
      
		}
    
    } // tau32 cut
  } // njets
    
    
    if (passedDetector && passedParticle ) {
      
      // fill migrations: particle-detector:
      hmaker_migra_ptcl -> FillMigrations(LastCutName, ptclLjets, ptcljets, ptclDijets, detLjets, detjets, detDijets, EventWeight);	  
      
      // fill 1D histos binned in Detector:
      hmaker_detptcl_det -> FillJetHistos(LastCutName, "LJet", detLjets, EventWeight, kallJets, 0);	
      hmaker_detptcl_det -> FillJetHistos(LastCutName, "Jet", detjets, EventWeight, kallJets, 0);	
      hmaker_detptcl_det -> FillJetHistos(LastCutName, "Dijet", detDijets, EventWeight, kallJets, 0);	
      // fill 1D histos binned in Particle:
      hmaker_detptcl_ptcl -> FillJetHistos(LastCutName, "LJet", ptclLjets, EventWeight, kallJets, 0);	
      hmaker_detptcl_ptcl -> FillJetHistos(LastCutName, "Jet", ptcljets, EventWeight, kallJets, 0);	
      hmaker_detptcl_ptcl -> FillJetHistos(LastCutName, "Dijet", ptclDijets, EventWeight, kallJets, 0);	
      
    }
    
  
  // clean up:
  for (auto jet : detjets) {
		delete jet;
  }
  for (auto jet : alldetjets) {
		delete jet;
  }
 for (auto jet : detDijets) {
		delete jet;
  }
 for (auto jet : ptclDijets) {
		delete jet;
  }
 for (auto jet : partonTops) {
		delete jet;
 }
 for (auto jet : partonDijets) {
		delete jet;
 }
  
  
  
}

outfile->Write();

}
