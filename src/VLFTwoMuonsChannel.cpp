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
	myskim->Branch("muon1Pt", &muon1Pt);
	myskim->Branch("muon2Pt", &muon2Pt);
	myskim->Branch("muon1Eta", &muon1Eta);
	myskim->Branch("muon2Eta", &muon2Eta);
	myskim->Branch("muon1Phi", &muon1Phi);
	myskim->Branch("muon2Phi", &muon2Phi);
	myskim->Branch("muon1Charge", &muon1Charge);
	myskim->Branch("muon2Charge", &muon2Charge);
	myskim->Branch("TwoMuonSystemMass", &TwoMuonSystemMass);
	myskim->Branch("TwoMuonSystemPt", &TwoMuonSystemPt);
	myskim->Branch("TwoMuonSystemEta", &TwoMuonSystemEta);
	myskim->Branch("TwoMuonSystemPhi", &TwoMuonSystemPhi);
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
	//std::vector<Jet> skimmedjets;
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
		if (muontight.size()<2 || muontight.size()>2) continue;
		if ((muontight.at(0)->Charge*muontight.at(1)->Charge)>0) continue;
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
		if (TwoMuonSystem.M()>60 and TwoMuonSystem.M()<120) continue;
		TwoMuonSystemMass=TwoMuonSystem.M();
		TwoMuonSystemPt=TwoMuonSystem.Pt();
		TwoMuonSystemEta=TwoMuonSystem.Eta();
		TwoMuonSystemPhi=TwoMuonSystem.Phi();

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

		for (size_t i=0;i<jet.size();i++){
		  if (jet.at(i)->PT < 30) continue; 
		  //skimmedjets.push_back(*jet.at(i));
		  GoodJetCounter++;
		  if (CurrentCounter==0){
		    CurrentCounter++;
		    jet1Pt=jet.at(i)->PT; jet1Eta=jet.at(i)->Eta; jet1Phi=jet.at(i)->Phi; jet1Mass=jet.at(i)->Mass; 
		  }
		  else if (CurrentCounter==1){
		    CurrentCounter++;
		    jet2Pt=jet.at(i)->PT; jet2Eta=jet.at(i)->Eta; jet2Phi=jet.at(i)->Phi; jet2Mass=jet.at(i)->Mass; 
		  }
		  else if (CurrentCounter==2){
		    CurrentCounter++;
		    jet3Pt=jet.at(i)->PT; jet3Eta=jet.at(i)->Eta; jet3Phi=jet.at(i)->Phi; jet3Mass=jet.at(i)->Mass; 
		  }
		  if (abs(jet.at(i)->Eta) < 2.4 && jet.at(i)->BTag==1){
		    bJetCounter++;
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



