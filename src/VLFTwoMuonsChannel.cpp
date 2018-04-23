/*
 * VLFTwoMuonsChannel.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 *      VLF implementation: Jose Ruiz
 */

#include "interface/VLFTwoMuonsChannel.h"



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
	d_ana::dBranchHandler<Jet>         jet(tree(),"Jet");
	d_ana::dBranchHandler<Muon>        muontight(tree(),"MuonTight");
	d_ana::dBranchHandler<Muon>        muonloose(tree(),"MuonLoose");
	d_ana::dBranchHandler<Photon>      photon(tree(),"Photon");
	d_ana::dBranchHandler<MissingET>   met(tree(),"MissingET");


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
	Double_t muon1Pt=0;
	Double_t muon2Pt=0;
	Double_t muon1Eta=0;
	Double_t muon2Eta=0;
	Double_t muon1Phi=0;
	Double_t muon2Phi=0;
	Double_t MET=0;	
	Double_t METPhi=0;
	myskim->Branch("muon1Pt", &muon1Pt);
	myskim->Branch("muon2Pt", &muon2Pt);
	myskim->Branch("muon1Eta", &muon1Eta);
	myskim->Branch("muon2Eta", &muon2Eta);
	myskim->Branch("muon1Phi", &muon1Phi);
	myskim->Branch("muon2Phi", &muon2Phi);
	myskim->Branch("MET", &MET);
	myskim->Branch("METPhi", &METPhi);
	/*
	 * Or store a vector of objects (also possible to store only one object)
	 */
	//std::vector<Electron> skimmedelecs;
	//myskim->Branch("Electrons",&skimmedelecs);
	std::vector<Jet> skimmedjets;



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
		if (met.at(0)->MET<100) continue;
		if (jet.at(0)->PT < 100) continue;
		if (muontight.size()<2 || muontight.size()>2) continue;
		muon1Pt=muontight.at(0)->PT;
		muon2Pt=muontight.at(1)->PT;
		muon1Eta=muontight.at(0)->Eta;
		muon2Eta=muontight.at(1)->Eta;
		muon1Phi=muontight.at(0)->Phi;
		muon2Phi=muontight.at(1)->Phi;

		MET=met.at(0)->MET;
		METPhi=met.at(0)->Phi;

		for (size_t i=0;i<jet.size();i++){
		  if (jet.at(i)->PT < 30) continue; 
		  skimmedjets.push_back(*jet.at(i));
		}

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



