#include "DelphesTree.h"
#include "KinemUtils.h"

// JK 2017

#include "HistoMaker.h"

#include <TH2.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "MyConsts.h"

// __________________________________________________________________

vector<TMyLorentzVector*>  DelphesTree::RemoveParticleJetsOverlapWithLeadLepton(kLjets ljets, vector<TMyLorentzVector*>& jets, double ptcut, bool debug)
{
  double dr;
  vector<TMyLorentzVector*> leptons;

  if (debug) cout << "*** DelphesTree::RemoveParticleJetsOverlapWithLeadLepton :  original jets: " << jets.size() << endl;

  int imu = -1;
  double maxpt = -kInfty;
  int nn = (ljets == kEjets ? GenElectron_size : GenMuon_size);
  for (int i = 0; i < nn; ++i) {
    TMyLorentzVector* lepton = (ljets == kEjets ? new TMyLorentzVector(GenMuon_PT[i], GenMuon_Eta[i], GenMuon_Phi[i], 0., 0., 0.) : new TMyLorentzVector(GenElectron_PT[i], GenElectron_Eta[i], GenElectron_Phi[i], 0., 0., 0.) );
    leptons.push_back(lepton);
    if (lepton->Pt() > maxpt && lepton -> Pt() > ptcut) {
      imu = i;
      maxpt = lepton->Pt();
    }
  }
  if (imu < 0)
    return jets;
  
  vector<int> ijettoremove;
  int ij = -1;
  for (auto jet : jets) {
    ij++;
    int im = -1;
    for (auto lepton : leptons) {
      im++;
      if (im != imu)
	continue;
      if (lepton->Pt() < ptcut)
	continue;
      dr = jet->DeltaR(*lepton);
      if (dr < 0.2) // c.f. ATLAS paper at 13 TeV
	ijettoremove.push_back(ij);
    } // leptons
  } // jets

  if (debug) cout << "OK! Scheduled jets to remove: " << ijettoremove.size() << "!!!" << endl;
  vector<TMyLorentzVector*> filtjets;
  ij = -1;
  for (auto jet : jets) {
    ij++;
    bool keep = true;
    for (auto iR : ijettoremove) {
      if (ij == iR) {
	keep = false;
	break;
      }
    }
    if (keep)
      filtjets.push_back(jet);
  }
  
  if (debug) cout << "  original jets: " << jets.size() << endl;
  if (debug) cout << "  filtered jets: " << filtjets.size() << endl;

  // clean
  for (auto lepton : leptons) {
    delete lepton;
  }
 

  return filtjets;
 
}

// __________________________________________________________________
bool DelphesTree::CheckOverlap(double eta, double phi, vector<TMyLorentzVector*>& jets, bool debug)
{

  // HACK! -- we don't use this method neither at detector not particle; see RemoveParticleJetsOverlapWithLeadLepton needed for the particle level!
  return true;

  

  double dr;
  TMyLorentzVector lep;
  lep.SetPtEtaPhiM(100*kGeV, eta, phi, 0.);
  
  if (debug) cout << "*** In DelphesTree::CheckOverlap" << endl;
  for (auto jet : jets) {
    if (debug) cout << "Jet pT: " << jet->Pt() << endl;
    dr = jet->DeltaR(lep);
    if (debug) cout << "dr=" << dr << endl;
    if (dr < 0.4)
      return false;
  }

  return true;
}

// __________________________________________________________________
void DelphesTree::MakePout(kPseudotop &pst) {

  // out-of-plane momentum Pout
  TVector3 top1 = pst.pseudotophadron.Vect();
  TVector3 top2 = pst.pseudotoplepton.Vect();
  
  TVector3 zUnit(0., 0., 1.);
  TVector3 perp1 = zUnit.Cross( top1 );
  TVector3 perp2 = zUnit.Cross( top2 );
  
  double pout1 = top2.Dot( perp1 ) / perp1.Mag();
  double pout2 = top1.Dot( perp2 ) / perp2.Mag();

  pst.Pout[0] = pout1;
  pst.Pout[1] = pout2;

  TVector3 boostVec = - (pst.pseudottbar.BoostVector()); // boost back to the original frame
  TMyLorentzVector TopLCMS = pst.pseudotoplepton;
  TopLCMS.Boost(0., 0., boostVec.Z());
  TMyLorentzVector TopHCMS = pst.pseudotophadron;
  TopHCMS.Boost(0., 0., boostVec.Z());
  pst.CosThetaStar[0] = cos(TopLCMS.Theta());
  pst.CosThetaStar[1] = cos(TopHCMS.Theta());
  // opening angle between top quarks in lab frame:
  pst.deltattbar = fabs(pst.pseudotophadron.Angle(pst.pseudotoplepton.Vect()));
  // delta phi:
  pst.DeltaPhi = fabs(pst.pseudotophadron.DeltaPhi(pst.pseudotoplepton));
  
  // const double ystar    =  0.5 * ( topH_y - topL_y );
  pst.Chittbar = exp( fabs( pst.pseudotoplepton.Rapidity() - pst.pseudotophadron.Rapidity() ) );
  pst.Yboost = 0.5*(TMath::Abs(pst.pseudotoplepton.Rapidity() + pst.pseudotophadron.Rapidity() ) );
  
  return;
}

// __________________________________________________________________
int DelphesTree::CheckPstMatching( kPseudotop pptcl, kPseudotop pdet)
{

  // check the leptons match
  if (pptcl.lepton.DeltaR(pdet.lepton) > 0.02) {
    return -1;
  }
  // check the W jets match, allow for the swap in order:
  double dr11 = pptcl.j1.DeltaR(pdet.j1);
  double dr22 = pptcl.j2.DeltaR(pdet.j2);
  double dr12 = pptcl.j1.DeltaR(pdet.j2);
  double dr21 = pptcl.j2.DeltaR(pdet.j1);
  double rcut = 0.35;
  if ( ! ( ( dr11 < rcut && dr22 < rcut) ||  ( dr12 < rcut && dr21 < rcut) ) ) {
    return -2;
  }
  
  

  dr11 = pptcl.bhadron.DeltaR(pdet.bhadron);
  dr11 = pptcl.blepton.DeltaR(pdet.blepton);

  dr12 = pptcl.blepton.DeltaR(pdet.bhadron);
  dr21 = pptcl.bhadron.DeltaR(pdet.blepton);

  if (! (m_PseudotopType == kBestBsAndNu) ) {
    // check the bjets match, no swap allowed:
    if ( dr11 > rcut ) {
      return -3;
    }
    if ( dr22 > rcut ) {
      return -4;
    }
  } else {
    // check the b-jets match, but do allow their swap!
    if ( ! ( ( dr11 < rcut && dr22 < rcut) ||  ( dr12 < rcut && dr21 < rcut) ) ) {
      return -5;
    }
  }
  
  return 0;
  
  
}


// __________________________________________________________________


TMyLorentzVector DelphesTree::DressByPhotons(TMyLorentzVector lep)
{
  
  TMyLorentzVector dressed = lep;
  for (int ig = 0; ig < GenPhoton_size; ++ig) {
    TMyLorentzVector gamma;
    gamma.SetPtEtaPhiM(GenPhoton_PT[ig], GenPhoton_Eta[ig], GenPhoton_Phi[ig], 0.);
    if (lep.DeltaR(gamma) < 0.1) {
      dressed = dressed + gamma;
    }
  }
  
  return dressed;
  
}

// __________________________________________________________________

bool DelphesTree::MakeLepton(bool DetLevel, vector<TMyLorentzVector*>& jets)
{

  switch(m_ljets) {

  case kEjets:
    {

      // TO CHECK :: the overlap treatment!!! Seems like it is needed only at detector level!

      if (DetLevel) {
	int ie = -1;
	  double maxpt = -999;
	  double lpt;
	  for (int i  = 0; i < Electron_size; ++i) {
	    lpt = Electron_PT[i];
	    if (lpt > maxpt && lpt > 25. && fabs(Electron_Eta[i]) < 2.5 && this -> CheckOverlap(Electron_Eta[i], Electron_Phi[i], jets) ) {
	      maxpt = Electron_PT[i];
	      ie = i;
	    }
	  } // loop over electrons
	  if (ie >= 0) {
	    m_pseudo_det.lepton.SetPtEtaPhiM(Electron_PT[ie], Electron_Eta[ie], Electron_Phi[ie], 0.);
	    return true;
	  } else return false;
	      
      } else {
	  // particle level
	  int ie = -1;
	  double maxpt = -999;
	  double lpt;
	  for (int i  = 0; i < GenElectron_size; ++i) {
	    lpt = GenElectron_PT[i];
	    if (lpt > maxpt && lpt > 25. && fabs(GenElectron_Eta[i]) < 2.5) { //  && this -> CheckOverlap(GenElectron_Eta[i], GenElectron_Phi[i], jets) ) {
	      maxpt = GenElectron_PT[i];
	      ie = i;
	    } 
	  } // loop over electrons
	  if (ie >= 0) {
	    // dress by photons
	    m_pseudo_ptcl.lepton.SetPtEtaPhiM(GenElectron_PT[ie], GenElectron_Eta[ie], GenElectron_Phi[ie], 0.);
	    m_pseudo_ptcl.lepton = this -> DressByPhotons(m_pseudo_ptcl.lepton);
	    return true;
	  } else return false;
      }
	    
    }
    break;

    case kMujets:
      {
	

	if (DetLevel) {
	int ie = -1;
	  double maxpt = -999;
	  double lpt;
	  for (int i  = 0; i < Muon_size; ++i) {
	    lpt = Muon_PT[i];
	    if (lpt > maxpt && lpt > 25. && fabs(Muon_Eta[i]) < 2.5  && this -> CheckOverlap(Muon_Eta[i], Muon_Phi[i], jets) ) {
	      maxpt = Muon_PT[i];
	      ie = i;
	    }
	  } // loop over muons
	  if (ie >= 0) {
	    m_pseudo_det.lepton.SetPtEtaPhiM(Muon_PT[ie], Muon_Eta[ie], Muon_Phi[ie], 0.);
	    return true;
	  } else return false;
	      
	} else {
	  // particle level
	  int ie = -1;
	  double maxpt = -999;
	  double lpt;
	  for (int i  = 0; i < GenMuon_size; ++i) {
	    lpt = GenMuon_PT[i];
	    // cout << "=======> Lepton pT: " << lpt << endl;
	    if (lpt > maxpt && lpt > 25. && fabs(GenMuon_Eta[i]) < 2.5) { // && this -> CheckOverlap(GenMuon_Eta[i], GenMuon_Phi[i], jets  ) ) {
	      maxpt = GenMuon_PT[i];
	      ie = i;
	      }
	  } // loop over muons
		
	  if (ie >= 0) {
	    // dress by photons
	    m_pseudo_ptcl.lepton.SetPtEtaPhiM(GenMuon_PT[ie], GenMuon_Eta[ie], GenMuon_Phi[ie], 0.);
	    m_pseudo_ptcl.lepton = this -> DressByPhotons(m_pseudo_ptcl.lepton);
	    return true;
	  } else return false;
	}
	    



      }
      break;
      
      
  } // switch
  
  return false;

} // MakeLepton
    


// __________________________________________________________________
	  
bool DelphesTree::MakeNeutrino(bool DetLevel, bool SwapBs)
{

  double pz = 0;
  double metx;
  double mety;
  double discriminant = 0.;
  // make sure its x ... cos and y ... sin?
  if (DetLevel) {
    metx = MissingET_MET[0] * cos( MissingET_Phi[0] );
    mety = MissingET_MET[0] * sin( MissingET_Phi[0] );
  } else {
    metx = GenMissingET_MET[0] * cos( GenMissingET_Phi[0] );
    mety = GenMissingET_MET[0] * sin( GenMissingET_Phi[0] );
  }

  TMyLorentzVector pseudotophadron;
  TMyLorentzVector neutrino0;
  TMyLorentzVector neutrino1;
  TMyLorentzVector pseudotoplepton0;
  TMyLorentzVector pseudotoplepton1;
  
  switch(m_PseudotopType) {
    
  case kOldWhad:
  case kStandard:
    {
      if (DetLevel) {
	pz = computeneutrinoz(m_pseudo_det.lepton,  metx, mety, 0, m_pseudo_det.DmW);
      } else {
	pz = computeneutrinoz(m_pseudo_ptcl.lepton,  metx, mety, 0, m_pseudo_ptcl.DmW);
      }
    }
    break;
    
  case kCloseMt:
  case kBestBsAndNu:
    {
      if (DetLevel) {
	
	double pz0 = computeneutrinoz(m_pseudo_det.lepton,  metx, mety, 0, m_pseudo_det.DmW);
	double pz1 = computeneutrinoz(m_pseudo_det.lepton,  metx, mety, 1, m_pseudo_det.DmW);
	// now build the pseudotops and compare mthad and mtlep!!!
	if (SwapBs)
	  pseudotophadron = m_pseudo_det.j1 +  m_pseudo_det.j2 + m_pseudo_det.blepton;
	else
	  pseudotophadron = m_pseudo_det.j1 +  m_pseudo_det.j2 + m_pseudo_det.bhadron;
	neutrino0.SetPxPyPzE(metx, mety, pz0, sqrt( sqr(metx) + sqr(mety) + sqr(pz0)) );
	neutrino1.SetPxPyPzE(metx, mety, pz1, sqrt( sqr(metx) + sqr(mety) + sqr(pz1)) );
	if (SwapBs) {
	  pseudotoplepton0 = neutrino0 + m_pseudo_det.lepton + m_pseudo_det.bhadron;
	  pseudotoplepton1 = neutrino1 + m_pseudo_det.lepton + m_pseudo_det.bhadron;
	} else {
	  pseudotoplepton0 = neutrino0 + m_pseudo_det.lepton + m_pseudo_det.blepton;
	  pseudotoplepton1 = neutrino1 + m_pseudo_det.lepton + m_pseudo_det.blepton;
	}
 	if ( fabs(pseudotoplepton0.M() - pseudotophadron.M())  < fabs(pseudotoplepton1.M() - pseudotophadron.M()) ) 
	  pz = pz0;
	else
	  pz = pz1;
	
      } else {
	double pz0 = computeneutrinoz(m_pseudo_ptcl.lepton,  metx, mety, 0, m_pseudo_ptcl.DmW);
	double pz1 = computeneutrinoz(m_pseudo_ptcl.lepton,  metx, mety, 1, m_pseudo_ptcl.DmW);

	// now build the pseudotops and compare mthad and mtlet!!!
	if (SwapBs)
	  pseudotophadron = m_pseudo_ptcl.j1 +  m_pseudo_ptcl.j2 + m_pseudo_ptcl.blepton;
	else
	  pseudotophadron = m_pseudo_ptcl.j1 +  m_pseudo_ptcl.j2 + m_pseudo_ptcl.bhadron;
	neutrino0.SetPxPyPzE(metx, mety, pz0, sqrt( sqr(metx) + sqr(mety) + sqr(pz0)) );
	neutrino1.SetPxPyPzE(metx, mety, pz1, sqrt( sqr(metx) + sqr(mety) + sqr(pz1)) );
	if (SwapBs) {
	  pseudotoplepton0 = neutrino0 + m_pseudo_ptcl.lepton + m_pseudo_ptcl.bhadron;
	  pseudotoplepton1 = neutrino1 + m_pseudo_ptcl.lepton + m_pseudo_ptcl.bhadron;
	} else {
	  pseudotoplepton0 = neutrino0 + m_pseudo_ptcl.lepton + m_pseudo_ptcl.blepton;
	  pseudotoplepton1 = neutrino1 + m_pseudo_ptcl.lepton + m_pseudo_ptcl.blepton;
	}
	 
 	if ( fabs(pseudotoplepton0.M() - pseudotophadron.M())  < fabs(pseudotoplepton1.M() - pseudotophadron.M()) ) 
	  pz = pz0;
	else
	  pz = pz1;

      }

    }
    break;
    
  case kSameMt:
    {
      
      if (DetLevel) {
	TMyLorentzVector pseudotophadron = m_pseudo_det.j1 +  m_pseudo_det.j2 + m_pseudo_det.bhadron;
	pz = computeneutrinoz_from_mt(pseudotophadron.M(), m_pseudo_det.lepton, m_pseudo_det.blepton,  metx, mety, 0, m_pseudo_det.Dmt);
      } else {
	TMyLorentzVector pseudotophadron = m_pseudo_ptcl.j1 +  m_pseudo_ptcl.j2 + m_pseudo_ptcl.bhadron;
	pz = computeneutrinoz_from_mt(pseudotophadron.M(), m_pseudo_ptcl.lepton, m_pseudo_ptcl.blepton,  metx, mety, 0, m_pseudo_ptcl.Dmt);
      }

    }
    break;


  case kTwoStep:
    {
      
    }
    break;
    
    
  case kTwoStepII:
    {
      
    }
    break;

 
}

  if (DetLevel) {
    m_pseudo_det.neutrino.SetPxPyPzE(metx, mety, pz, sqrt(pow(metx,2) + pow(mety,2) + pow(pz,2)) );
  } else {
    m_pseudo_ptcl.neutrino.SetPxPyPzE(metx, mety, pz, sqrt(pow(metx,2) + pow(mety,2) + pow(pz,2)) );
  }
      
  return true;

}


// __________________________________________________________________

bool DelphesTree::MakeWjets( bool DetLevel, vector<TMyLorentzVector*>& jets)
{

  int ii = -1;
  int jj = -1;

  // Check also the old Whad definition of taking two highest pT non-b-tagged jets:
  double pTmax1 = -kInfty;
  double pTmax2 = -2*kInfty;
  double jetpt;
  int iimax = -1;
  int jjmax = -1;
    
  TMyLorentzVector j1, j2;
  // Default: find jets with mjj closest to W mass:
  double mdiff = kInfty;


  for (int i = 0; i < jets.size(); ++i) {
    if (jets[i]->Btag())
      continue;
    jetpt = jets[i]->Pt();
    if (jetpt > pTmax1) {
      pTmax2 = pTmax1;
      pTmax1 = jetpt;
      jjmax = iimax;
      iimax = i;
    } else if (jetpt > pTmax2) {
      pTmax2 = jetpt;
      jjmax = i;
    }

    j1.SetPtEtaPhiM(jets[i]->Pt(), jets[i]->Eta(), jets[i]->Phi(), jets[i]->M());
    for (int j = 0; j < i; ++j) {
      if (jets[j]->Btag())
	continue;	
      j2.SetPtEtaPhiM(jets[j]->Pt(), jets[j]->Eta(), jets[j]->Phi(), jets[j]->M());
      double diff = fabs( (j1+j2).M() - kmW);
      if (diff < mdiff) {
	ii = i;
	jj = j;
	mdiff = diff;
      }
      
      
    } // i
  } // j

  if (m_PseudotopType == kOldWhad) {
    ii = iimax;
    jj = jjmax;
  } 

  if (ii >= 0 && jj >= 0 && ii != jj) {
    if (DetLevel) {
      m_pseudo_det.j1.SetPtEtaPhiM(jets[ii]->Pt(), jets[ii]->Eta(), jets[ii]->Phi(), jets[ii]->M());
      m_pseudo_det.j2.SetPtEtaPhiM(jets[jj]->Pt(), jets[jj]->Eta(), jets[jj]->Phi(), jets[jj]->M());
    } else {
      m_pseudo_ptcl.j1.SetPtEtaPhiM(jets[ii]->Pt(), jets[ii]->Eta(), jets[ii]->Phi(), jets[ii]->M());
      m_pseudo_ptcl.j2.SetPtEtaPhiM(jets[jj]->Pt(), jets[jj]->Eta(), jets[jj]->Phi(), jets[jj]->M());
    }
    //    cout <<        "ii=" << ii << " jj=" << jj << endl;
    return true;
  }
  return false;
}


  // __________________________________________________________________

bool DelphesTree::MakeBs(bool DetLevel, TMyLorentzVector lepton, vector<TMyLorentzVector*>& jets)
{

  // find highest pT b-jets
  
  TMyLorentzVector b1, b2;
  
  int ib1 = -1;
  int ib2 = -1;
  double maxpt = -kInfty;
  for (int i = 0; i < jets.size(); ++i) {
    if (jets[i]->Btag() && jets[i]->Pt() > maxpt) {
      ib1 = i;
      maxpt = jets[i]->Pt();
    }
  }
  
  if (ib1 >= 0) {

    // find the 2nd highest pT b-jet    
    maxpt = -kInfty;
    for (int i = 0; i < jets.size(); ++i) {
      if (i == ib1)
	continue;
      if (jets[i]->Btag() && jets[i]->Pt() > maxpt) {
	ib2 = i;
	maxpt = jets[i]->Pt();
      }
    }
    
  }


  if (ib1 >= 0 && ib2 >= 0) {
    
    // assign to blep and bhad those closer or farer from lepton
    b1.SetPtEtaPhiM(jets[ib1]->Pt(), jets[ib1]->Eta(), jets[ib1]->Phi(), jets[ib1]->M());
    b2.SetPtEtaPhiM(jets[ib2]->Pt(), jets[ib2]->Eta(), jets[ib2]->Phi(), jets[ib2]->M());
 
    if ( b1.DeltaR(lepton) < b2.DeltaR(lepton)) {
      if (DetLevel) {
	m_pseudo_det.bhadron = b2;
	m_pseudo_det.blepton = b1;
      } else {
	m_pseudo_ptcl.bhadron = b2;
	m_pseudo_ptcl.blepton = b1;
      }
    } else {
      if (DetLevel) {
	m_pseudo_det.bhadron = b1;
	m_pseudo_det.blepton = b2;
      } else {
	m_pseudo_ptcl.bhadron = b1;
	m_pseudo_ptcl.blepton = b2;
      }
    }

    return true;

  } 

  return false;
  
}



// __________________________________________________________________
    
 bool DelphesTree::MakePseudotops(bool DetLevel, vector<TMyLorentzVector*>& jets)
{

  int ldebug = 0;
  if (!DetLevel)
    ldebug = 0;


  bool allok = true;
  if (ldebug > 1) cout << "...making lepton, allok=" << allok << endl;
  allok = allok && this -> MakeLepton(DetLevel, jets);
  if (ldebug > 1) cout << "...making Ws, allok=" << allok << endl;
  allok = allok && this -> MakeWjets(DetLevel, jets);


  // this is effectivelly also a cut on >= 2bjets present in event;)
  if (ldebug > 1) cout << "...making Bs, allok=" << allok << endl;
  allok = allok && this -> MakeBs(DetLevel, (DetLevel ? m_pseudo_det.lepton : m_pseudo_ptcl.lepton) , jets);
  
  if (ldebug > 1) cout << "...making hadronic part if possible, allok=" << allok << endl;
  if (allok) {

    TMyLorentzVector pseudotophadronSwap;
    
    if (DetLevel) {
      m_pseudo_det.pseudoWhadron = m_pseudo_det.j1 +  m_pseudo_det.j2;
      m_pseudo_det.pseudotophadron = m_pseudo_det.pseudoWhadron + m_pseudo_det.bhadron;
      pseudotophadronSwap = m_pseudo_det.pseudoWhadron + m_pseudo_det.blepton;
    } else {
      // particle
      m_pseudo_ptcl.pseudoWhadron = m_pseudo_ptcl.j1 +  m_pseudo_ptcl.j2;
      m_pseudo_ptcl.pseudotophadron = m_pseudo_ptcl.pseudoWhadron + m_pseudo_ptcl.bhadron;
      pseudotophadronSwap = m_pseudo_ptcl.pseudoWhadron + m_pseudo_ptcl.blepton;
    }
    
    if (ldebug > 1) cout << "...making neutrino, allok=" << allok << endl;
    allok = allok && this -> MakeNeutrino(DetLevel, false);
  
    if (ldebug > 1) cout << "...making lepton, allok=" << allok << endl;
    if (allok) {
      if (DetLevel) {
	// detector
	if (ldebug > 1) cout << "...making leptonic detector part, allok=" << allok << endl;
	m_pseudo_det.pseudoWlepton = m_pseudo_det.neutrino + m_pseudo_det.lepton;
	m_pseudo_det.pseudotoplepton = m_pseudo_det.pseudoWlepton + m_pseudo_det.blepton;
	
	if (m_PseudotopType == kBestBsAndNu) {
	  // save original results:
	  TMyLorentzVector pseudotopleptonStd = m_pseudo_det.pseudotoplepton;
	  TMyLorentzVector pseudotophadronStd = m_pseudo_det.pseudotophadron;
	  // now try best mt but with swapped b-jets!
	  this -> MakeNeutrino(DetLevel, true); 
	  m_pseudo_det.pseudoWlepton = m_pseudo_det.neutrino + m_pseudo_det.lepton;
	  m_pseudo_det.pseudotoplepton = m_pseudo_det.pseudoWlepton + m_pseudo_det.bhadron;
	  TMyLorentzVector pseudotopleptonSwap = m_pseudo_det.pseudotoplepton;

	  if ( fabs(pseudotophadronStd.M() - pseudotopleptonStd.M()) < fabs( pseudotophadronSwap.M() - pseudotopleptonSwap.M()) ) {
	    // ok, bjets swap did not help
	    // refit the standard non-swap case, restore results:
	    this -> MakeNeutrino(DetLevel, false); 
	    m_pseudo_det.pseudoWlepton = m_pseudo_det.neutrino + m_pseudo_det.lepton;
	    m_pseudo_det.pseudotoplepton = m_pseudo_det.pseudoWlepton + m_pseudo_det.blepton;
	  } else {
	    // OK, bjets swap won, keep last results
	    // BUT really swap the bjets now, too:)
	    TMyLorentzVector bjetTmp = m_pseudo_det.blepton;
	    m_pseudo_det.blepton = m_pseudo_det.bhadron;
	    m_pseudo_det.bhadron = bjetTmp;
	  }
	  
	} // try the bjest swap

	// finish the ttbar system:
	m_pseudo_det.pseudottbar = m_pseudo_det.pseudotophadron + m_pseudo_det.pseudotoplepton;
	// compute Pout and other ttbar system quantities:
	this -> MakePout(m_pseudo_det);
	
      } else {
	// particle
	if (ldebug > 1) cout << "...making leptonic particle part, allok=" << allok << endl;
	m_pseudo_ptcl.pseudoWlepton = m_pseudo_ptcl.neutrino + m_pseudo_ptcl.lepton;
	m_pseudo_ptcl.pseudotoplepton = m_pseudo_ptcl.pseudoWlepton + m_pseudo_ptcl.blepton;
	
	if (m_PseudotopType == kBestBsAndNu) {
	  // save original results:
	  TMyLorentzVector pseudotopleptonStd = m_pseudo_ptcl.pseudotoplepton;
	  TMyLorentzVector pseudotophadronStd = m_pseudo_ptcl.pseudotophadron;
	  // now try best mt but with swapped b-jets!
	  this -> MakeNeutrino(DetLevel, true); 
	  m_pseudo_ptcl.pseudoWlepton = m_pseudo_ptcl.neutrino + m_pseudo_ptcl.lepton;
	  m_pseudo_ptcl.pseudotoplepton = m_pseudo_ptcl.pseudoWlepton + m_pseudo_ptcl.bhadron;
	  TMyLorentzVector pseudotopleptonSwap = m_pseudo_ptcl.pseudotoplepton;
	  
	  if ( fabs(pseudotophadronStd.M() - pseudotopleptonStd.M()) < fabs( pseudotophadronSwap.M() - pseudotopleptonSwap.M()) ) {
	    // ok, bjets swap did not help
	    // refit the standard non-swap case, restore results:
	    this -> MakeNeutrino(DetLevel, false); 
	    m_pseudo_ptcl.pseudoWlepton = m_pseudo_ptcl.neutrino + m_pseudo_ptcl.lepton;
	    m_pseudo_ptcl.pseudotoplepton = m_pseudo_ptcl.pseudoWlepton + m_pseudo_ptcl.blepton;
	  } else {
	    // OK, bjets swap won, keep last results
	    // BUT really swap the bjets now, too:)
	    TMyLorentzVector bjetTmp = m_pseudo_ptcl.blepton;
	    m_pseudo_ptcl.blepton = m_pseudo_ptcl.bhadron;
	    m_pseudo_ptcl.bhadron = bjetTmp;
	  }
	  
	} // try the bjest swap
	
	// finish the ttbar system:
	m_pseudo_ptcl.pseudottbar = m_pseudo_ptcl.pseudotophadron + m_pseudo_ptcl.pseudotoplepton;
	// compute Pout and other ttbar system quantities:
	this -> MakePout(m_pseudo_ptcl);

      }
    
    }

  }
  return allok;
}
    

// __________________________________________________________________


void DelphesTree::Loop_ljets(TString outtag, TString channel, TString pseudo)
{
  if (fChain == 0) return;

  m_ljets = kUndef;
  if (channel == "ejets")
    m_ljets = kEjets;
  else if (channel == "mujets")
    m_ljets = kMujets;
  
  m_PseudotopType = kNonePseudo;
  if (pseudo == "Standard")
    m_PseudotopType = kStandard;
  else if (pseudo == "OldWhad")
    m_PseudotopType = kOldWhad;
  else if (pseudo == "CloseMt")
    m_PseudotopType = kCloseMt;
  else if (pseudo == "SameMt")
    m_PseudotopType = kSameMt;
  else if (pseudo == "TwoStep")
    m_PseudotopType = kTwoStep;
  else if (pseudo == "TwoStepII")
    m_PseudotopType = kTwoStepII;
  else if (pseudo == "BestBsAndNu")
    m_PseudotopType = kBestBsAndNu;


  Long64_t nentries = fChain->GetEntries();

  TFile *outfile = new TFile("analyzed_histos_" + outtag + "_" + channel + "_" + pseudo + ".root", "recreate");

  outfile -> cd();
  TH1D *h_yields = new TH1D("Passed", "Passed", 5, 0, 5);
  h_yields -> GetXaxis() -> SetBinLabel(1, "Parton");
  h_yields -> GetXaxis() -> SetBinLabel(2, "Particle");
  h_yields -> GetXaxis() -> SetBinLabel(3, "Detector");
  h_yields -> GetXaxis() -> SetBinLabel(4, "Detector && particle");
  h_yields -> GetXaxis() -> SetBinLabel(5, "Detector && particle && match");
  
  TString LastCutName = "AllCuts";

  HistoMaker *hmaker_ptcl = new HistoMaker("Particle");
  hmaker_ptcl -> AddCutLevel("NoCuts");
  hmaker_ptcl -> AddCutLevel(LastCutName);
  hmaker_ptcl -> MakeLjetHistos(LastCutName);	
  hmaker_ptcl -> MakeControlHistos();	

  
  HistoMaker *hmaker_det = new HistoMaker("Detector");
  hmaker_det -> AddCutLevel("NoCuts");
  hmaker_det -> AddCutLevel(LastCutName);
  hmaker_det -> MakeLjetHistos(LastCutName);
  hmaker_det -> MakeControlHistos();	

  //binned in ptcl quantities
  HistoMaker *hmaker_detptcl_ptcl = new HistoMaker("DetectorAndParticle_ptcl");
  hmaker_detptcl_ptcl -> AddCutLevel(LastCutName);  
  hmaker_detptcl_ptcl -> MakeLjetHistos(LastCutName);	    
  
  //binned in det quantities
  HistoMaker *hmaker_detptcl_det = new HistoMaker("DetectorAndParticle_det");
  hmaker_detptcl_det -> AddCutLevel(LastCutName);  
  hmaker_detptcl_det -> MakeLjetHistos(LastCutName);

  // passing particle and detector:

  //binned in ptcl quantities, matched
  HistoMaker *hmaker_detptclmatch_ptcl = new HistoMaker("DetectorAndParticleMatched_ptcl");
  hmaker_detptclmatch_ptcl -> AddCutLevel(LastCutName);  
  hmaker_detptclmatch_ptcl -> MakeLjetHistos(LastCutName);	    
  
  //binned in det quantities, matched
  HistoMaker *hmaker_detptclmatch_det = new HistoMaker("DetectorAndParticleMatched_det");
  hmaker_detptclmatch_det -> AddCutLevel(LastCutName);  
  hmaker_detptclmatch_det -> MakeLjetHistos(LastCutName);
 
  
  //binned in ptcl quantities, NOT matched
  HistoMaker *hmaker_detptclnomatch_ptcl = new HistoMaker("DetectorAndParticleNotMatched_ptcl");
  hmaker_detptclnomatch_ptcl -> AddCutLevel(LastCutName);  
  hmaker_detptclnomatch_ptcl -> MakeLjetHistos(LastCutName);	    
  
  //binned in det quantities, NOT matched
  HistoMaker *hmaker_detptclnomatch_det = new HistoMaker("DetectorAndParticleNotMatched_det");
  hmaker_detptclnomatch_det -> AddCutLevel(LastCutName);  
  hmaker_detptclnomatch_det -> MakeLjetHistos(LastCutName);
 

 
  // migrations particle-detector
  HistoMaker *hmaker_migra_ptcl = new HistoMaker("Migrations_ptcl_det");
  hmaker_migra_ptcl -> AddCutLevel(LastCutName);  
  hmaker_migra_ptcl -> MakeLjetMigrations(LastCutName, "Particle", "Detector");	  
  hmaker_migra_ptcl -> MakeJESHistos(LastCutName);


  // migrations particle-detector, matched!
  HistoMaker *hmaker_migra_ptcl_match = new HistoMaker("Migrations_ptcl_det_match");
  hmaker_migra_ptcl_match -> AddCutLevel(LastCutName);  
  hmaker_migra_ptcl_match -> MakeLjetMigrations(LastCutName, "ParticleMatch", "DetectorMatch");	  

  

  // migrations particle-detector, diagonal in sign of determinat
  HistoMaker *hmaker_migra_ptcl_diag = new HistoMaker("Migrations_ptcl_det_diag");
  hmaker_migra_ptcl_diag -> AddCutLevel(LastCutName);  
  hmaker_migra_ptcl_diag -> MakeLjetMigrations(LastCutName, "ParticleDiag", "DetectorDiag");	  

  // migrations particle-detector, off diagonal in sign of determinat, case 1
  HistoMaker *hmaker_migra_ptcl_negpos = new HistoMaker("Migrations_ptcl_det_negpos");
  hmaker_migra_ptcl_negpos -> AddCutLevel(LastCutName);  
  hmaker_migra_ptcl_negpos -> MakeLjetMigrations(LastCutName, "ParticleNegPos", "DetectorNegPos");	  

  // migrations particle-detector, off diagona in sign of determinat, case 2
  HistoMaker *hmaker_migra_ptcl_posneg = new HistoMaker("Migrations_ptcl_det_posneg");
  hmaker_migra_ptcl_posneg -> AddCutLevel(LastCutName);  
  hmaker_migra_ptcl_posneg -> MakeLjetMigrations(LastCutName, "ParticlePosNeg", "DetectorPosNeg");	  
  
  
  // migrations parton-detector
  HistoMaker *hmaker_migra_parton_det = new HistoMaker("Migrations_parton_det");
  hmaker_migra_parton_det -> AddCutLevel(LastCutName);  
  hmaker_migra_parton_det -> MakeLjetMigrations(LastCutName, "Parton", "Detector");	  
  
  // migrations parton-particle
  HistoMaker *hmaker_migra_parton_ptcl = new HistoMaker("Migrations_parton_ptcl");
  hmaker_migra_parton_ptcl -> AddCutLevel(LastCutName);  
  hmaker_migra_parton_ptcl -> MakeLjetMigrations(LastCutName, "Parton", "Particle");	  

  // spectra parton, no cuts!
  HistoMaker *hmaker_parton = new HistoMaker("Parton");
  hmaker_parton -> AddCutLevel("NoCuts");
  hmaker_parton -> MakeLjetHistos("NoCuts");


  HistoMaker *hmaker_det_parton = new HistoMaker("Parton_det");
  hmaker_det_parton -> AddCutLevel(LastCutName);
  hmaker_det_parton -> MakeLjetHistos(LastCutName);

  HistoMaker *hmaker_ptcl_parton = new HistoMaker("Parton_ptcl");
  hmaker_ptcl_parton -> AddCutLevel(LastCutName);
  hmaker_ptcl_parton -> MakeLjetHistos(LastCutName);



  // let's study here only migrations from detector to parton, for the cases of the
  // discriminant sign at particle and detector levels below:
  // (we could also study migrations from particle to parton, but that's becoming a bit too much...
  // plus one often unfolds from detector to parton directly...so is it actually worth it looking at
  // such migrations from detector to parton, conditioned by the particle?? Seems that not much, really...JK 21.9.2017, Braga)
  
  // migrations parton-detector, diagonal in sign of determinat
  HistoMaker *hmaker_migra_parton_diag = new HistoMaker("Migrations_parton_ptcl_det_diag");
  hmaker_migra_parton_diag -> AddCutLevel(LastCutName);  
  hmaker_migra_parton_diag -> MakeLjetMigrations(LastCutName, "Parton_ParticleDiag", "DetectorDiag");	  

  // migrations parton-detector, off diagonal in sign of determinat, case 1
  HistoMaker *hmaker_migra_parton_negpos = new HistoMaker("Migrations_parton_ptcl_det_negpos");
  hmaker_migra_parton_negpos -> AddCutLevel(LastCutName);  
  hmaker_migra_parton_negpos -> MakeLjetMigrations(LastCutName, "Parton_ParticleNegPos", "DetectorNegPos");	  

  // migrations parton-detector, off diagona in sign of determinat, case 2
  HistoMaker *hmaker_migra_parton_posneg = new HistoMaker("Migrations_parton_ptcl_det_posneg");
  hmaker_migra_parton_posneg -> AddCutLevel(LastCutName);  
  hmaker_migra_parton_posneg -> MakeLjetMigrations(LastCutName, "Parton_ParticlePosNeg", "DetectorPosNeg");	  

  
  int verbose = 10000;
  int ToRunOver = nentries;		
  // HACK! 
  // ToRunOver = 10000;		
  int debug = 0;
      
  Long64_t nbytes = 0, nb = 0;
  
  cout << "Will loop over " << ToRunOver << " events." << endl;
  
  int NpassedDetector = 0;
  int NpassedParticle = 0;
  int NpassedParton = 0;
  int NpassedParticleAndDetector = 0;
  int NpassedParticleAndDetectorMatched = 0;
    

  for (Long64_t jentry=0; jentry<ToRunOver;jentry++) {

    double EventWeight = 1.;

    if (jentry % verbose == 0) {
      cout << "Processing " << jentry << "/" << nentries << endl;
    }
    if (debug > 0) cout << "Event " << jentry << endl;	

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;


    // NEW weights fix!!! 3.6.2019
    if (Event_Weight[0] < 1.e-20)
      continue;
    
    // STEERING!!!
    bool CorrectJES = false;
   
    // CUTS!
    double etacut = 2.5;
    double ptcut = 25.;
    double tau32cut = kInfty;
    double masscut = kInfty;

    bool passedDetector = false;
    bool passedParticle = false;
    bool passedParton = false;


    // +------------------------+
    // |  Parton level cuts     |
    // +------------------------+
    // none for the moment, i.e. the full phase space!
    if (debug > 2) cout << "  ok, making parton tops1" << endl;	
    vector<TMyLorentzVector*> partontops = this -> MakeGenTops(0., 999.);
    if (debug > 2) cout << "  ok, making parton tops2" << endl;	
    vector<TMyLorentzVector*> partonttbar = this -> MakeGenDijets(partontops);
    if (debug > 2) cout << "  ok, making parton tops3" << endl;	
    // for the moment, a random association:
    if (partontops.size() > 1) {
      passedParton = true;
      NpassedParton++;
      m_pseudo_parton.pseudotoplepton = *partontops[0];
      m_pseudo_parton.pseudotophadron = *partontops[1];
      m_pseudo_parton.pseudottbar = m_pseudo_parton.pseudotoplepton + m_pseudo_parton.pseudotophadron;
      this -> MakePout(m_pseudo_parton);
      hmaker_parton -> FillLjetHistos("NoCuts", m_pseudo_parton, EventWeight);
    }

    // +------------------------+
    // |  Detector level cuts   |
    // +------------------------+
          
    // no pT cut, detector jets:
    vector<TMyLorentzVector*>  alldetjets  = MakeJets(1, 0, 0., etacut, CorrectJES, kResolved);
    //    if (debug > 1) cout << "  got " << alldetLjets.size() << " jets." << endl;
	
    // pt cuts on all jets, get the collection of those passing:
    vector<TMyLorentzVector*> detjets     = MakeJets(1, 0, ptcut, etacut, CorrectJES, kResolved);
    if (debug > 0) cout << " Got " << detjets.size() << " det jets in pt eta acceptance." << endl;	

    passedDetector =  false;
    if (detjets.size() >= 4) {
      if (debug > 1) cout << "  OK, passed >=4j cut, making det pseudotops..." << endl;
      passedDetector = this -> MakePseudotops(1, detjets);
      if (debug > 1) cout << "   first jet pt: " << detjets[0]->Pt() << endl;	
      if (debug > 1) cout << "   ok, passed njets cut" << endl;	
      if (passedDetector) {
	NpassedDetector++;
	hmaker_det -> FillLjetHistos(LastCutName, m_pseudo_det, EventWeight);
	hmaker_det -> FillJetHistos(LastCutName, "Jets", detjets, EventWeight, kallJets);
	hmaker_det -> FillJetHistos(LastCutName, "bJets", detjets, EventWeight, kbJets);
	hmaker_det -> FillJetHistos(LastCutName, "nonbJets", detjets, EventWeight, knonbJets);
	hmaker_det -> FillSingleObjectHistos(LastCutName, "Lepton", m_pseudo_det.lepton, EventWeight);
	hmaker_det -> FillSingleObjectHistos(LastCutName, "Neutrino", m_pseudo_det.neutrino, EventWeight);
	
	
	if (debug > 1) cout << "   Detector pseudotop masses: (had,lep) = (" 
			    << m_pseudo_det.pseudotophadron.M() << ","
			    << m_pseudo_det.pseudotoplepton.M() << ")" << endl;		
	if (debug > 1) cout << "   Detector pseudoW masses: (had,lep) = (" 
			    << m_pseudo_det.pseudoWhadron.M() << ","
			    << m_pseudo_det.pseudoWlepton.M() << ")" << endl;		
	
	// fill migrations: parton-detector:
	if (passedParton) {
	  hmaker_migra_parton_det -> FillLjetMigrationsParton(LastCutName, m_pseudo_parton, m_pseudo_det, EventWeight);	  
	  // fill 1D parton, passing det cuts
	  hmaker_det_parton -> FillLjetHistos(LastCutName, m_pseudo_parton, EventWeight);	
	} // parton
	
      }
    } // njets


    // +------------------------+
    // |  Particle level cuts   |
    // +------------------------+
  
    CorrectJES = 0;
      // no pT cut, detector jets:
    vector<TMyLorentzVector*>  allptcljets  = MakeJets(0, 0, 0., etacut, CorrectJES, kResolved);
    //    if (debug > 1) cout << "   got ptcl " << allptclLjets.size() << " jets." << endl;
    // TODO    hmaker_ptcl -> FillLjetHistos("NoCuts", "LJet", allptclLjets, EventWeight, 1);
    // TODO    hmaker_ptcl -> FillLjetHistos("NoCuts", "Jet", allptcljets, EventWeight, 0);
    
    // pt cuts on all jets, get the collection of those passing:
    vector<TMyLorentzVector*> ptcljets     = MakeJets(0, 0, ptcut, etacut, CorrectJES, kResolved);
    if (debug > 1) cout << "   got " << ptcljets.size() << " ptcl jets in pt eta acceptance." << endl;	
    ////    if (m_ljets == kMujets) {
      // need to remove particle jets which are actually muons!
      int norig = ptcljets.size();
      
      vector<TMyLorentzVector*> newptcljets = RemoveParticleJetsOverlapWithLeadLepton(m_ljets, ptcljets, ptcut);
      ptcljets = newptcljets;
      int nfilt = ptcljets.size();
      //cout << "     DIFF: " << norig - nfilt << endl;
      // clean allocated yet isolation removed jets:
      for (auto jet : ptcljets) {
	bool found = false;
	for (auto newjet : newptcljets) {
	  if (jet == newjet) {
	    found = true;
	    break;
	  }
	}
	if (!found)
	  delete jet;
      } // ptcljets
      

      ////}

    passedParticle =  false;
    if (ptcljets.size() >= 4) {
      if (debug > 1) cout << "  OK, passed >=4j cut, making ptcl pseudotops..." << endl;
      passedParticle = this -> MakePseudotops(0, ptcljets);
      if (debug > 1) cout << "   first jet pt: " << ptcljets[0]->Pt() << endl;	
      if (debug > 1) cout << "   ok, passed njets cut" << endl;	
      if (passedParticle) {
	NpassedParticle++;
	hmaker_ptcl -> FillLjetHistos(LastCutName, m_pseudo_ptcl, EventWeight);
	hmaker_ptcl -> FillJetHistos(LastCutName, "Jets", ptcljets, EventWeight, kallJets);
	hmaker_ptcl -> FillJetHistos(LastCutName, "bJets", ptcljets, EventWeight, kbJets);
	hmaker_ptcl -> FillJetHistos(LastCutName, "nonbJets", detjets, EventWeight, knonbJets);
	hmaker_ptcl -> FillSingleObjectHistos(LastCutName, "Lepton", m_pseudo_ptcl.lepton, EventWeight);
	hmaker_ptcl -> FillSingleObjectHistos(LastCutName, "Neutrino", m_pseudo_ptcl.neutrino, EventWeight);

	if (debug > 1) cout << "  Particle pseudotop masses: (had,lep) = (" 
			    << m_pseudo_ptcl.pseudotophadron.M() << ","
			    << m_pseudo_ptcl.pseudotoplepton.M() << ")" << endl;		
	if (debug > 1) cout << "  Particle pseudoW masses: (had,lep) = (" 
			    << m_pseudo_ptcl.pseudoWhadron.M() << ","
			    << m_pseudo_ptcl.pseudoWlepton.M() << ")" << endl;		
	
	if (passedParton) {
	  // fill migrations: parton-particle:
	  hmaker_migra_parton_ptcl -> FillLjetMigrationsParton(LastCutName, m_pseudo_parton, m_pseudo_ptcl, EventWeight);	  
	  // fill 1D parton, passing ptcl cuts
	  hmaker_ptcl_parton -> FillLjetHistos(LastCutName, m_pseudo_parton, EventWeight);	
	} // parton
      }
    } // njets

    if (passedDetector && passedParticle ) {
      NpassedParticleAndDetector++;
      
      // fill migrations: particle-detector:
      hmaker_migra_ptcl -> FillLjetMigrations(LastCutName, m_pseudo_ptcl, m_pseudo_det, EventWeight);
      // fill 1D histos binned in Detector:
      hmaker_detptcl_det -> FillLjetHistos(LastCutName, m_pseudo_det, EventWeight);	
      // fill 1D histos binned in Particle:
      hmaker_detptcl_ptcl -> FillLjetHistos(LastCutName, m_pseudo_ptcl, EventWeight);	


      // now check the matching:
      int imatch = this -> CheckPstMatching( m_pseudo_det, m_pseudo_ptcl);
      if (imatch == 0) {
	NpassedParticleAndDetectorMatched++;
	// fill passing particle and detector as well as the matching!
	hmaker_migra_ptcl_match -> FillLjetMigrations(LastCutName, m_pseudo_ptcl, m_pseudo_det, EventWeight);
	// fill 1D histos binned in Detector:
	hmaker_detptclmatch_det -> FillLjetHistos(LastCutName, m_pseudo_det, EventWeight);	
	// fill 1D histos binned in Particle:
	hmaker_detptclmatch_ptcl -> FillLjetHistos(LastCutName, m_pseudo_ptcl, EventWeight);	
      } else {
	// fill passing particle and detector but not the matching!
	// fill 1D histos binned in Detector:
	hmaker_detptclnomatch_det -> FillLjetHistos(LastCutName, m_pseudo_det, EventWeight);	
	// fill 1D histos binned in Particle:
	hmaker_detptclnomatch_ptcl -> FillLjetHistos(LastCutName, m_pseudo_ptcl, EventWeight);	
      }


      // now the correspondence of the sign of the discriminant:
      double Ddet = 0;
      double Dptcl = 0;
	  
      if (m_PseudotopType == kStandard || m_PseudotopType == kCloseMt || m_PseudotopType == kOldWhad) {
	Ddet = m_pseudo_det.DmW;
	Dptcl = m_pseudo_ptcl.DmW;
      } else if (m_PseudotopType == kSameMt) {
	Ddet = m_pseudo_det.Dmt;
	Dptcl = m_pseudo_ptcl.Dmt;
      }


      // Fill also parton level histograms! TODO!!!
      
      if (Ddet*Dptcl > 0) {
	// diagonal
	hmaker_migra_ptcl_diag -> FillLjetMigrations(LastCutName, m_pseudo_ptcl, m_pseudo_det, EventWeight);
	hmaker_migra_parton_diag -> FillLjetMigrations(LastCutName, m_pseudo_parton, m_pseudo_det, EventWeight);
      } else if (Ddet*Dptcl < 0 && Dptcl < 0) {
	// offdiag negative (particle) and positive (detector) discriminants
	hmaker_migra_ptcl_negpos -> FillLjetMigrations(LastCutName, m_pseudo_ptcl, m_pseudo_det, EventWeight);
	hmaker_migra_parton_negpos -> FillLjetMigrations(LastCutName, m_pseudo_parton, m_pseudo_det, EventWeight);
      } else if (Ddet*Dptcl < 0 && Dptcl > 0) {
	//  offdiag positive (particle) and negative (detector) discriminants
	hmaker_migra_ptcl_posneg -> FillLjetMigrations(LastCutName, m_pseudo_ptcl, m_pseudo_det, EventWeight);
	hmaker_migra_parton_posneg -> FillLjetMigrations(LastCutName, m_pseudo_parton, m_pseudo_det, EventWeight);
      } 


    } // passed det and particle
    
  
    // JES!
    hmaker_migra_ptcl -> FillJESHistos(LastCutName, ptcljets, detjets, true); // closure!

    // clean up:
    for (auto jet : detjets) {
      delete jet;
    }
    for (auto jet : alldetjets) {
      delete jet;
    }
 
    // clean up:
    for (auto jet : ptcljets) {
      delete jet;
    }
    for (auto jet : allptcljets) {
      delete jet;
    }
   
    for (auto jet : partontops) {
      delete jet;
    }
    for (auto jet : partonttbar) {
      delete jet;
    }
      
  
  } // event loop

  cout << "END of the event loop!" << endl;
  cout << "--------------------------------------------------------------------" << endl;
  cout << "Some statistics:" << endl;
  cout << " Total entries                         : " << nentries << endl;
  cout << " Requested entries                     : " << ToRunOver << endl;
  cout << " passed Parton                         : " << NpassedParton << endl 
       << " passed Particle                       : " << NpassedParticle << endl 
       << " passed Detector                       : " << NpassedDetector << endl 
       << " passed Particle && Detector           : " << NpassedParticleAndDetector << endl 
       << " passed Particle && Detector, matched  : " << NpassedParticleAndDetectorMatched << endl 
       << endl;
  cout << "--------------------------------------------------------------------" << endl;
  cout << " Matching efficiency    :    " << NpassedParticleAndDetectorMatched / (1.*NpassedParticleAndDetector) << endl;
  cout << " Parton efficiency      :    " << NpassedParton / (1.*ToRunOver) << endl;
  cout << " Particle efficiency    :    " << NpassedParticle / (1.*ToRunOver) << endl;
  cout << " Detector efficiency    :    " << NpassedDetector / (1.*ToRunOver) << endl;
  cout << "--------------------------------------------------------------------" << endl;
  cout << "Writing output file..." << endl;

  // fill yield histos:
  h_yields -> SetBinContent(1,  NpassedParton);
  h_yields -> SetBinContent(2,  NpassedParticle);
  h_yields -> SetBinContent(3,  NpassedDetector);
  h_yields -> SetBinContent(4,  NpassedParticleAndDetector);
  h_yields -> SetBinContent(5,  NpassedParticleAndDetectorMatched); 

  outfile->Write();

  cout << "ALL DONE!" << endl;

}
