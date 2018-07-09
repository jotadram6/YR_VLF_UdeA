/*
 * VLFTwoMuonsChannel.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 *      VLF implementation: Jose Ruiz
 */

#include "interface/VLFTwoMuonsChannel.h"

float deltaPhi(float phi1, float phi2) {
  float PHI = phi1-phi2;
  if (PHI >= 3.14159265)
    PHI -= 2*3.14159265;
  else if (PHI < -3.14159265)
    PHI += 2*3.14159265;
 
  return PHI;
}

float MTlnu(float lpt, float metpt, float lphi, float metphi) {
  return TMath::Sqrt(2*lpt*metpt*(1-TMath::Cos(deltaPhi(metphi,lphi))));
}

float MTlnumin(float l1pt, float l2pt, float metpt, float l1phi, float l2phi, float metphi) {
  return TMath::Min(MTlnu(l1pt,metpt,l1phi,metphi),MTlnu(l2pt,metpt,l2phi,metphi));
}

float MTllmet(float l1pt, float l2pt, float metpt, float l1phi, float l2phi, float metphi) { 
  //Trying to generalize two body MT https://arxiv.org/pdf/hep-ph/9906349.pdf
  return TMath::Sqrt(2*l1pt*l2pt*metpt*(1-TMath::Cos(deltaPhi(metphi,deltaPhi(l1phi,l2phi)))));
}

/*float SetPxPyPzTFromPtEtaPhiT(float pt, float eta, float phi, float time) {
  
  return TMath::Sqrt((((pt*TMath::Cos(phi))*(pt*TMath::Cos(phi)))+((pt*TMath::Sin(phi))*(pt*TMath::Sin(phi)))+((pt*TMath::Sinh(phi))*(pt*TMath::Sinh(phi))))+(mass*mass));
  }*/

//Should we consider an extra variable like http://iopscience.iop.org/article/10.1088/1126-6708/2009/11/096/pdf ?????

void VLFTwoMuonsChannel::analyze(size_t childid /* this info can be used for printouts */){

	/*
	 * This skeleton analyser runs directly on the Delphes output.
	 * It can be used to create histograms directly or a skim.
	 * If a skim is created, a new input configuration will be written automatically
	 * and stored in the output directory together with the ntuples.
	 * The skim can contain delphes objects again or can be flat. This is up
	 * to the user.
	 * Examples for both are given here.
	 *
	 * The same skeleton can be used to read the skim. Please refer to the comments
	 * marked with "==SKIM=="
	 *
	 * These parts are commented, since the code is supposed to work as an example without
	 * modifications on Delphes output directly.
	 */



	/*
	 * Define the branches that are to be considered for the analysis
	 * This branch handler (notice the "d")
	 * is used to run directly in Delphes output.
	 * For skimmed ntuples, see below
	 */
	d_ana::dBranchHandler<Electron> elecs(tree(),"Electron");
	/*
	 * Other branches might be the following
	 * (for a full list, please inspect the Delphes sample root file with root)
	 * For the Delphes class description, see $DELPHES_PATH/classes/DelphesClasses.h
	 */
	//
	d_ana::dBranchHandler<HepMCEvent>  event(tree(),"Event");
	d_ana::dBranchHandler<GenParticle> genpart(tree(),"Particle");
	d_ana::dBranchHandler<Jet>         genjet(tree(),"GenJet");
	d_ana::dBranchHandler<Jet>         jet(tree(),"JetPUPPI");
	d_ana::dBranchHandler<Muon>        muontight(tree(),"MuonTight");
	d_ana::dBranchHandler<Muon>        muonloose(tree(),"MuonLoose");
	d_ana::dBranchHandler<Photon>      photon(tree(),"Photon");
	d_ana::dBranchHandler<MissingET>   met(tree(),"PuppiMissingET");


	/* ==SKIM==
	 *
	 * If a skim of the Delphes outout was created in a way indicated
	 * further below, use the tBranchHandler (please notive the "t")
	 * to access vectors of objects...
	 *
	 */
	// d_ana::tBranchHandler<std::vector<Electron> > electrons(tree(),"Electrons");

	/*==SKIM==
	 *
	 * Or an object directly
	 *
	 */
	//d_ana::tBranchHandler<MissingET> met(tree(),"MET");



	/*
	 * Always use this function to add a new histogram (can also be 2D)!
	 * Histograms created this way are automatically added to the output file
	 */
	TH1* histo=addPlot(new TH1D("histoname1","histotitle1",100,0,100),"p_{T} [GeV]","N_{e}");


	/*
	 * If (optionally) a skim or a flat ntuple is to be created, please use the following function to initialize
	 * the tree.
	 * The output files will be written automatically, and a config file will be created.
	 */
	TTree* myskim=addTree();
	/*
	 * Add a simple branch to the skim
	 */
	//Double_t elecPt=0;
	//myskim->Branch("elecPt", &elecPt);
	myskim->Branch("NTightMuons", &NTightMuons);
	myskim->Branch("muon1Pt", &muon1Pt);
	myskim->Branch("muon2Pt", &muon2Pt);
	myskim->Branch("muon1Eta", &muon1Eta);
	myskim->Branch("muon2Eta", &muon2Eta);
	myskim->Branch("muon1Phi", &muon1Phi);
	myskim->Branch("muon2Phi", &muon2Phi);
	myskim->Branch("muon1Charge", &muon1Charge);
	myskim->Branch("muon2Charge", &muon2Charge);
	myskim->Branch("muon1JetsMuon0p4PtRatio", &muon1JetsMuon0p4PtRatio);
	myskim->Branch("muon2JetsMuon0p4PtRatio", &muon2JetsMuon0p4PtRatio);
 	myskim->Branch("minDeltaRJetsmuon1", &minDeltaRJetsmuon1);
	myskim->Branch("minDeltaRJetsmuon2", &minDeltaRJetsmuon2);
	myskim->Branch("isMuon1DuplicatedOnJets", &isMuon1DuplicatedOnJets);
	myskim->Branch("isMuon2DuplicatedOnJets", &isMuon2DuplicatedOnJets);
	myskim->Branch("NTightIso0p2Muons", &NTightIso0p2Muons);
	myskim->Branch("Iso0p2muon1Pt", &Iso0p2muon1Pt);
	myskim->Branch("Iso0p2muon2Pt", &Iso0p2muon2Pt);
	myskim->Branch("Iso0p2muon1Eta", &Iso0p2muon1Eta);
	myskim->Branch("Iso0p2muon2Eta", &Iso0p2muon2Eta);
	myskim->Branch("Iso0p2muon1Phi", &Iso0p2muon1Phi);
	myskim->Branch("Iso0p2muon2Phi", &Iso0p2muon2Phi);
	myskim->Branch("NTightIso0p4Muons", &NTightIso0p4Muons);
	myskim->Branch("Iso0p4muon1Pt", &Iso0p4muon1Pt);
	myskim->Branch("Iso0p4muon2Pt", &Iso0p4muon2Pt);
	myskim->Branch("Iso0p4muon1Eta", &Iso0p4muon1Eta);
	myskim->Branch("Iso0p4muon2Eta", &Iso0p4muon2Eta);
	myskim->Branch("Iso0p4muon1Phi", &Iso0p4muon1Phi);
	myskim->Branch("Iso0p4muon2Phi", &Iso0p4muon2Phi);
	myskim->Branch("mostIsomuon1Pt", &mostIsomuon1Pt);
	myskim->Branch("mostIsomuon2Pt", &mostIsomuon2Pt);
	myskim->Branch("mostIsomuon1Eta", &mostIsomuon1Eta);
	myskim->Branch("mostIsomuon2Eta", &mostIsomuon2Eta);
	myskim->Branch("mostIsomuon1Phi", &mostIsomuon1Phi);
	myskim->Branch("mostIsomuon2Phi", &mostIsomuon2Phi);
	myskim->Branch("mostIsomuon1Charge", &mostIsomuon1Charge);
	myskim->Branch("mostIsomuon2Charge", &mostIsomuon2Charge);
	myskim->Branch("TwoMuonSystemMass", &TwoMuonSystemMass);
	myskim->Branch("TwoMuonSystemPt", &TwoMuonSystemPt);
	myskim->Branch("TwoMuonSystemEta", &TwoMuonSystemEta);
	myskim->Branch("TwoMuonSystemPhi", &TwoMuonSystemPhi);
	myskim->Branch("TwoIso0p2MuonSystemMass", &TwoIso0p2MuonSystemMass);
	myskim->Branch("TwoIso0p2MuonSystemPt", &TwoIso0p2MuonSystemPt);
	myskim->Branch("TwoIso0p2MuonSystemEta", &TwoIso0p2MuonSystemEta);
	myskim->Branch("TwoIso0p2MuonSystemPhi", &TwoIso0p2MuonSystemPhi);
	myskim->Branch("TwoIso0p4MuonSystemMass", &TwoIso0p4MuonSystemMass);
	myskim->Branch("TwoIso0p4MuonSystemPt", &TwoIso0p4MuonSystemPt);
	myskim->Branch("TwoIso0p4MuonSystemEta", &TwoIso0p4MuonSystemEta);
	myskim->Branch("TwoIso0p4MuonSystemPhi", &TwoIso0p4MuonSystemPhi);
	myskim->Branch("mostIsoTwoMuonSystemMass", &mostIsoTwoMuonSystemMass);
	myskim->Branch("mostIsoTwoMuonSystemPt", &mostIsoTwoMuonSystemPt);
	myskim->Branch("mostIsoTwoMuonSystemEta", &mostIsoTwoMuonSystemEta);
	myskim->Branch("mostIsoTwoMuonSystemPhi", &mostIsoTwoMuonSystemPhi);
	myskim->Branch("NTight0p4PtIsoMuons", &NTight0p4PtIsoMuons);
	myskim->Branch("MET", &MET);
	myskim->Branch("METPhi", &METPhi);
	myskim->Branch("MT1", &MT1);
	myskim->Branch("MT2", &MT2);
	myskim->Branch("MTmin", &MTmin);
	myskim->Branch("MT12", &MT12);
	myskim->Branch("NJets", &NJets);
	myskim->Branch("NbJets", &NbJets);
	myskim->Branch("jet1Pt", &jet1Pt);
	myskim->Branch("jet2Pt", &jet2Pt);
	myskim->Branch("jet3Pt", &jet3Pt);
	myskim->Branch("jet1Eta", &jet1Eta);
	myskim->Branch("jet2Eta", &jet2Eta);
	myskim->Branch("jet3Eta", &jet3Eta);
	myskim->Branch("jet1Phi", &jet1Phi);
	myskim->Branch("jet2Phi", &jet2Phi);
	myskim->Branch("jet3Phi", &jet3Phi);
	myskim->Branch("jet1Mass", &jet1Mass);
	myskim->Branch("jet2Mass", &jet2Mass);
	myskim->Branch("jet3Mass", &jet3Mass);

	/*
	 * Or store a vector of objects (also possible to store only one object)
	 */
	//std::vector<Electron> skimmedelecs;
	//myskim->Branch("Electrons",&skimmedelecs);
	//To be included
	std::vector<Jet> skimmedjets;
	//myskim->Branch("Jets",&skimmedjets);



	size_t nevents=tree()->entries();
	if(isTestMode())
		nevents/=100;
	for(size_t eventno=0;eventno<nevents;eventno++){
		/*
		 * The following two lines report the status and set the event link
		 * Do not remove!
		 */
		reportStatus(eventno,nevents);
		tree()->setEntry(eventno);



		/*
		 * Begin the event-by-event analysis
		 */
		//for(size_t i=0;i<elecs.size();i++){
		//	histo->Fill(elecs.at(i)->PT);
		//}

		/*
		 * Or to fill the skim
		 */
		//if (met.at(0)->MET<100) continue;
		//if (jet.at(0)->PT < 100) continue;
		//if (muontight.size()<2 || muontight.size()>2) continue;
		if (muontight.size()<2) continue;
		//if ((muontight.at(0)->Charge*muontight.at(1)->Charge)>0) continue;
		NTightMuons=muontight.size();
		muon1Pt=muontight.at(0)->PT;
		muon2Pt=muontight.at(1)->PT;
		muon1Eta=muontight.at(0)->Eta;
		muon2Eta=muontight.at(1)->Eta;
		muon1Phi=muontight.at(0)->Phi;
		muon2Phi=muontight.at(1)->Phi;
		muon1Charge=muontight.at(0)->Charge;
		muon2Charge=muontight.at(1)->Charge;

		TLorentzVector Muon1;
		TLorentzVector Muon2;
		Muon1.SetPtEtaPhiM(muon1Pt,muon1Eta,muon1Phi,mass_mu);
		Muon2.SetPtEtaPhiM(muon2Pt,muon2Eta,muon2Phi,mass_mu);
		//Muon1.SetPx(muon1Pt*TMath::Cos(muon1Phi)); Muon1.SetPy(muon1Pt*TMath::Sin(muon1Phi)); Muon1.SetPz(muon1Pt*TMath::SinH(muon1Phi)); Muon1.SetT(muontight.at(0)->T);
		//Muon2.SetPx(muon2Pt*TMath::Cos(muon2Phi)); Muon2.SetPy(muon2Pt*TMath::Sin(muon2Phi)); Muon2.SetPz(muon2Pt*TMath::SinH(muon2Phi)); Muon2.SetT(muontight.at(1)->T);
		TLorentzVector TwoMuonSystem=Muon1+Muon2;

		//Studying muon isolation from jets
		double minDeltaRmuon1=20;
		double minDeltaRmuon2=20;
		double JetMuon1PtSum=muon1Pt;
		double JetMuon2PtSum=muon2Pt;
		isMuon1DuplicatedOnJets=0;
		isMuon2DuplicatedOnJets=0;
		bool JetIsMuon=false;
		skimmedjets.clear();
		for (size_t i=0;i<jet.size();i++){
		  TLorentzVector JET;
		  JET.SetPtEtaPhiM(jet.at(i)->PT,jet.at(i)->Eta,jet.at(i)->Phi,jet.at(i)->Mass);
		  if (JET.Pt()==muon1Pt || TMath::Abs(muon1Eta-JET.Eta())<0.01) {
		    //std::cout << "DUPLICATE FOUND!!!!!!!!!!!!!!!" << std::endl;
		    //std::cout << "Jet pt=" << JET.Pt() << "; Jet position=" << i << "; Muon pt=" << muon1Pt << "; Leading muon" << std::endl;
		    //std::cout << "Jet eta=" << JET.Eta() << "; Muon eta=" << muon1Eta << std::endl;
		    //std::cout << "Jet phi=" << JET.Phi() << "; Muon phi=" << muon1Phi << std::endl;
		    isMuon1DuplicatedOnJets=1;
		  }
		  if (JET.Pt()==muon2Pt || TMath::Abs(muon1Eta-JET.Eta())<0.01) {
		    //std::cout << "Jet pt=" << JET.Pt() << "; Jet position=" << i << "; Muon pt=" << muon2Pt << "; Subleading muon" << std::endl;
		    isMuon2DuplicatedOnJets=1;
		  }
		  
		  for (size_t j=0;j<muontight.size();j++){
		    if (muontight.at(j)->PT==JET.Pt() || TMath::Abs(muontight.at(j)->Eta-JET.Eta())<0.01){
		      JetIsMuon=true;
		    }
		  }
		  if (!JetIsMuon) {skimmedjets.push_back(*jet.at(i));}

		  if (minDeltaRmuon1>JET.DeltaR(Muon1) && !JetIsMuon){
		    minDeltaRmuon1=JET.DeltaR(Muon1);
		  }
		  if (minDeltaRmuon2>JET.DeltaR(Muon2) && !JetIsMuon){
		    minDeltaRmuon2=JET.DeltaR(Muon2);
		  }

		  if (JET.DeltaR(Muon1)<0.4 && JET.Pt()>=1 && !JetIsMuon){
		    JetMuon1PtSum+=JET.Pt();
		  }
		  if (JET.DeltaR(Muon2)<0.4 && JET.Pt()>=1 && !JetIsMuon){
		    JetMuon2PtSum+=JET.Pt();
		  }
		}
		minDeltaRJetsmuon1=minDeltaRmuon1;
		minDeltaRJetsmuon2=minDeltaRmuon2;
		muon1JetsMuon0p4PtRatio=muon1Pt/JetMuon1PtSum;
		muon2JetsMuon0p4PtRatio=muon2Pt/JetMuon2PtSum;

		//Size of cleaed jet collection
		//std::cout << "New jet collection size=" << skimmedjets.size() << ", from total jet collection size=" << jet.size() << std::endl;

		//if (TwoMuonSystem.M()>60 and TwoMuonSystem.M()<120) continue;
		TwoMuonSystemMass=TwoMuonSystem.M();
		TwoMuonSystemPt=TwoMuonSystem.Pt();
		TwoMuonSystemEta=TwoMuonSystem.Eta();
		TwoMuonSystemPhi=TwoMuonSystem.Phi();

		//Isolated Muons part////////////////////////////////////////////////////////////////////////////
		Iso0p2muon1Pt=0; Iso0p2muon1Eta=0; Iso0p2muon1Phi=0; Iso0p2muon1Charge=0;
		Iso0p2muon2Pt=0; Iso0p2muon2Eta=0; Iso0p2muon2Phi=0; Iso0p2muon2Charge=0;
		Iso0p4muon1Pt=0; Iso0p4muon1Eta=0; Iso0p4muon1Phi=0; Iso0p4muon1Charge=0;
		Iso0p4muon2Pt=0; Iso0p4muon2Eta=0; Iso0p4muon2Phi=0; Iso0p4muon2Charge=0;

		int Iso0p2Muons=0;
		int Iso0p4Muons=0;
		int Iso0p4PtMuons=0;
		//Double_t PtSumPerMuon[muontight.size()];
		std::vector<double> PtSumPerMuon; PtSumPerMuon.clear();
		Double_t PtSumPerMuonD=0.0;
		for (size_t i=0;i<muontight.size();i++){
		  TLorentzVector MUON;
		  MUON.SetPtEtaPhiM(muontight.at(i)->PT,muontight.at(i)->Eta,muontight.at(i)->Phi,mass_mu);
		  double Iso0p2=false;
		  double Iso0p4=false;
		  int JetCounter=0;
		  PtSumPerMuonD=muontight.at(i)->PT;
		  for (size_t j=0;j<skimmedjets.size();j++){
		    if (skimmedjets.at(j).PT < 1) continue;
		    JetCounter++;
		    TLorentzVector JET;
		    JET.SetPtEtaPhiM(skimmedjets.at(j).PT,skimmedjets.at(j).Eta,skimmedjets.at(j).Phi,skimmedjets.at(j).Mass);
		    if (JET.DeltaR(MUON)<0.2) {
		      Iso0p2=false;
		    }
		    else {Iso0p2=true;}
		    if (JET.DeltaR(MUON)<0.4) {
		      Iso0p4=false;
		    }
		    else {Iso0p4=true;}
		    //Most Isolated muons
		    if (muontight.at(i)->PT==JET.Pt() || TMath::Abs(muontight.at(i)->Eta-JET.Eta())<0.01) continue;
		    if (JET.DeltaR(MUON)<0.4 && JET.Pt()>=1 && !JetIsMuon){
		      PtSumPerMuonD+=JET.Pt();
		    }
		  }
		  PtSumPerMuon.push_back(muontight.at(i)->PT/PtSumPerMuonD);
		  if (muontight.at(i)->PT/PtSumPerMuonD>0.4) {Iso0p4PtMuons++;}
		  if (JetCounter==0) {Iso0p2=true; Iso0p4=true;}
		  //0p2 Isolation
		  if (Iso0p2 && Iso0p2Muons==0)
		    {
		      Iso0p2Muons++;
		      Iso0p2muon1Pt=muontight.at(i)->PT; Iso0p2muon1Eta=muontight.at(i)->Eta; Iso0p2muon1Phi=muontight.at(i)->Phi; Iso0p2muon1Charge=muontight.at(i)->Charge;
		      Iso0p2=false;
		    }
		  if (Iso0p2 && Iso0p2Muons==1)
		    {
		      Iso0p2Muons++;
		      Iso0p2muon2Pt=muontight.at(i)->PT; Iso0p2muon2Eta=muontight.at(i)->Eta; Iso0p2muon2Phi=muontight.at(i)->Phi; Iso0p2muon2Charge=muontight.at(i)->Charge;
		      Iso0p2=false;
		    }
		  if (Iso0p2 && Iso0p2Muons>=2) {Iso0p2Muons++; Iso0p2=false;}
		  //0p4 Isolation
		  if (Iso0p4 && Iso0p4Muons==0)
		    {
		      Iso0p4Muons++;
		      Iso0p4muon1Pt=muontight.at(i)->PT; Iso0p4muon1Eta=muontight.at(i)->Eta; Iso0p4muon1Phi=muontight.at(i)->Phi; Iso0p4muon1Charge=muontight.at(i)->Charge;
		      Iso0p4=false;
		    }
		  if (Iso0p4 && Iso0p4Muons==1)
		    {
		      Iso0p4Muons++;
		      Iso0p4muon2Pt=muontight.at(i)->PT; Iso0p4muon2Eta=muontight.at(i)->Eta; Iso0p4muon2Phi=muontight.at(i)->Phi; Iso0p4muon2Charge=muontight.at(i)->Charge;
		      Iso0p4=false;
		    }
		  if (Iso0p4 && Iso0p4Muons>=2) {Iso0p4Muons++; Iso0p4=false;}
		}

		NTightIso0p2Muons=Iso0p2Muons;
		NTightIso0p4Muons=Iso0p4Muons;
		NTight0p4PtIsoMuons=Iso0p4PtMuons;

		//if (Iso0p2Muons<2 || Iso0p2Muons>2) continue;

		TLorentzVector Iso0p2Muon1;
		TLorentzVector Iso0p2Muon2;
		Iso0p2Muon1.SetPtEtaPhiM(Iso0p2muon1Pt,Iso0p2muon1Eta,Iso0p2muon1Phi,mass_mu);
		Iso0p2Muon2.SetPtEtaPhiM(Iso0p2muon2Pt,Iso0p2muon2Eta,Iso0p2muon2Phi,mass_mu);
		TLorentzVector TwoIso0p2MuonSystem=Iso0p2Muon1+Iso0p2Muon2;
		TwoIso0p2MuonSystemMass=TwoIso0p2MuonSystem.M();
		TwoIso0p2MuonSystemPt=TwoIso0p2MuonSystem.Pt();
		TwoIso0p2MuonSystemEta=TwoIso0p2MuonSystem.Eta();
		TwoIso0p2MuonSystemPhi=TwoIso0p2MuonSystem.Phi();
		
		TLorentzVector Iso0p4Muon1;
		TLorentzVector Iso0p4Muon2;
		Iso0p4Muon1.SetPtEtaPhiM(Iso0p4muon1Pt,Iso0p4muon1Eta,Iso0p4muon1Phi,mass_mu);
		Iso0p4Muon2.SetPtEtaPhiM(Iso0p4muon2Pt,Iso0p4muon2Eta,Iso0p4muon2Phi,mass_mu);
		TLorentzVector TwoIso0p4MuonSystem=Iso0p4Muon1+Iso0p4Muon2;
		TwoIso0p4MuonSystemMass=TwoIso0p4MuonSystem.M();
		TwoIso0p4MuonSystemPt=TwoIso0p4MuonSystem.Pt();
		TwoIso0p4MuonSystemEta=TwoIso0p4MuonSystem.Eta();
		TwoIso0p4MuonSystemPhi=TwoIso0p4MuonSystem.Phi();

		int iMax=0;
		int iSubMax=1;
		//double Max=PtSumPerMuon.at(0); double SubMax=PtSumPerMuon.at(0);
		double Max=0.0; double SubMax=0.0;

		for (size_t i=0;i<PtSumPerMuon.size();i++){
		  if (PtSumPerMuon.at(i) > Max) {
		    Max=PtSumPerMuon.at(i);
		    iMax=i;
		  }
		  if (PtSumPerMuon.at(i) > SubMax && PtSumPerMuon.at(i) < Max) {
		    SubMax=PtSumPerMuon.at(i);
		    iSubMax=i;
		  }
		}
		
		/*if (muontight.size()==3) {
		  std::cout << "Sizes:" << std::endl;
		  std::cout << PtSumPerMuon.size() << " " << muontight.size()<< std::endl;
		  std::cout << "iMax, Max, iSubMax, SubMax " << std::endl;
		  std::cout << iMax << " " << Max << " " << iSubMax << " " << SubMax << std::endl;
		  std::cout << "Max->ptsum, Submax->ptsum " << std::endl;
		  std::cout << PtSumPerMuon.at(iMax) << " " << PtSumPerMuon.at(iSubMax) << std::endl;
		  }*/

		mostIsomuon1Pt=muontight.at(iMax)->PT; mostIsomuon1Eta=muontight.at(iMax)->Eta; mostIsomuon1Phi=muontight.at(iMax)->Phi; mostIsomuon1Charge=muontight.at(iMax)->Charge;
		mostIsomuon2Pt=muontight.at(iSubMax)->PT; mostIsomuon2Eta=muontight.at(iSubMax)->Eta; mostIsomuon2Phi=muontight.at(iSubMax)->Phi; mostIsomuon2Charge=muontight.at(iSubMax)->Charge;
		TLorentzVector mostIsoMuon1;
		TLorentzVector mostIsoMuon2;
		mostIsoMuon1.SetPtEtaPhiM(mostIsomuon1Pt,mostIsomuon1Eta,mostIsomuon1Phi,mass_mu);
		mostIsoMuon2.SetPtEtaPhiM(mostIsomuon2Pt,mostIsomuon2Eta,mostIsomuon2Phi,mass_mu);
		TLorentzVector mostIsoTwoMuonSystem=mostIsoMuon1+mostIsoMuon2;
		mostIsoTwoMuonSystemMass=mostIsoTwoMuonSystem.M();
		mostIsoTwoMuonSystemPt=mostIsoTwoMuonSystem.Pt();
		mostIsoTwoMuonSystemEta=mostIsoTwoMuonSystem.Eta();
		mostIsoTwoMuonSystemPhi=mostIsoTwoMuonSystem.Phi();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////

		MET=met.at(0)->MET;
		METPhi=met.at(0)->Phi;

		MT1=MTlnu(muon1Pt,MET,muon1Phi,METPhi);
		MT2=MTlnu(muon2Pt,MET,muon2Phi,METPhi);
		MTmin=MTlnumin(muon1Pt,muon2Pt,MET,muon1Phi,muon2Phi,METPhi);
		MT12=MTllmet(muon1Pt,muon2Pt,MET,muon1Phi,muon2Phi,METPhi);
		
		Int_t GoodJetCounter=0;
		int CurrentCounter = 0;
		int bJetCounter = 0;
		
		jet1Pt=0.0; jet1Eta=0.0; jet1Phi=0.0; jet1Mass=0.0;
		jet2Pt=0.0; jet2Eta=0.0; jet2Phi=0.0; jet2Mass=0.0;
		jet3Pt=0.0; jet3Eta=0.0; jet3Phi=0.0; jet3Mass=0.0;

		for (size_t i=0;i<skimmedjets.size();i++){
		  if (skimmedjets.at(i).PT < 30) continue; 
		  //skimmedjets.push_back(*jet.at(i));
		  GoodJetCounter++;
		  if (skimmedjets.at(i).BTag) {
		    bJetCounter++;
		  }
		  if (CurrentCounter==0){
		    CurrentCounter++;
		    jet1Pt=skimmedjets.at(i).PT; jet1Eta=skimmedjets.at(i).Eta; jet1Phi=skimmedjets.at(i).Phi; jet1Mass=skimmedjets.at(i).Mass; 
		  }
		  else if (CurrentCounter==1){
		    CurrentCounter++;
		    jet2Pt=skimmedjets.at(i).PT; jet2Eta=skimmedjets.at(i).Eta; jet2Phi=skimmedjets.at(i).Phi; jet2Mass=skimmedjets.at(i).Mass; 
		  }
		  else if (CurrentCounter==2){
		    CurrentCounter++;
		    jet3Pt=skimmedjets.at(i).PT; jet3Eta=skimmedjets.at(i).Eta; jet3Phi=skimmedjets.at(i).Phi; jet3Mass=skimmedjets.at(i).Mass; 
		  }
		}

		NbJets=bJetCounter;
		if (NbJets!=0) continue;

		NJets=GoodJetCounter;
		if (NJets<1) continue;

		//skimmedelecs.clear();
		//for(size_t i=0;i<elecs.size();i++){
			//flat info
		//	elecPt=elecs.at(i)->PT;
		//	if(elecs.at(i)->PT < 20) continue;
			//or objects
		//	skimmedelecs.push_back(*elecs.at(i));
		//}

		myskim->Fill();


		/*==SKIM==
		 * Access the branches of the skim
		 */
		//std::vector<Electron> * skimelecs=electrons.content();
		//for(size_t i=0;i<skimelecs->size();i++){
		//	histo->Fill(skimelecs->at(i).PT);
		//}
	}


	/*
	 * Must be called in the end, takes care of thread-safe writeout and
	 * call-back to the parent process
	 */
	processEndFunction();
}



void VLFTwoMuonsChannel::postProcess(){
	/*
	 * This function can be used to analyse the output histograms, e.g. extract a signal contribution etc.
	 * The function can also be called directly on an output file with the histograms, if
	 * RunOnOutputOnly = true
	 * is set in the analyser's config file
	 *
	 * This function also represents an example of how the output of the analyser can be
	 * read-back in an external program.
	 * Just include the sampleCollection.h header and follow the procedure below
	 *
	 */

	/*
	 * Here, the input file to the extraction of parameters from the histograms is the output file
	 * of the parallelised analysis.
	 * The sampleCollection class can also be used externally for accessing the output consistently
	 */
	d_ana::sampleCollection samplecoll;
	samplecoll.readFromFile(getOutPath());

	std::vector<TString> alllegends = samplecoll.listAllLegends();

	/*
	 * Example how to process the output.
	 * Usually, one would define the legendname of the histogram to be used here
	 * by hand, e.g. "signal" or "background".
	 * To make this example run in any case, I am using alllegends.at(0), which
	 * could e.g. be the signal legend.
	 *
	 * So in practise, the following would more look like
	 * samplecoll.getHistos("signal");
	 */
	if(alllegends.size()>0){
		d_ana::histoCollection histos=samplecoll.getHistos(alllegends.at(0));

		/*
		 * here, the histogram created in the analyze() function is selected and evaluated
		 * The histoCollection maintains ownership (you don't need to delete the histogram)
		 */
		const TH1* myplot=histos.getHisto("histoname1");

		std::cout << "(example output): the integral is " << myplot->Integral() <<std::endl;

		/*
		 * If the histogram is subject to changes, please clone it and take ownership
		 */

		TH1* myplot2=histos.cloneHisto("histoname1");

		/*
		 * do something with the histogram
		 */

		delete myplot2;
	}

	/*
	 * do the extraction here.
	 */



}



