/*
 * VLFTwoMuonsChannel.h
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#ifndef VLFTwoMuonsChannel_H_
#define VLFTwoMuonsChannel_H_

#include "interface/basicAnalyzer.h"
#include "interface/sampleCollection.h"
#include "classes/DelphesClasses.h"
#include "TMath.h"

class VLFTwoMuonsChannel: public d_ana::basicAnalyzer{
public:
	VLFTwoMuonsChannel():d_ana::basicAnalyzer(){}
	~VLFTwoMuonsChannel(){}


private:
	void analyze(size_t id);

	void postProcess();

	//Variables for skimming branches
	Double_t muon1Pt=0;
	Double_t muon2Pt=0;
	Double_t muon1Eta=0;
	Double_t muon2Eta=0;
	Double_t muon1Phi=0;
	Double_t muon2Phi=0;
	Double_t muon1Charge=0;
	Double_t muon2Charge=0;
	Double_t TwoMuonSystemMass=0;
	Double_t TwoMuonSystemPt=0;
	Double_t TwoMuonSystemEta=0;
	Double_t TwoMuonSystemPhi=0;
	Double_t MET=0;
	Double_t METPhi=0;
	Double_t MT1=0;
	Double_t MT2=0;
	Double_t MTmin=0;
	Double_t MT12=0;
	Int_t NJets=0;
	Double_t jet1Pt=0;
	Double_t jet2Pt=0;
	Double_t jet3Pt=0;
	Double_t jet1Eta=0;
	Double_t jet2Eta=0;
	Double_t jet3Eta=0;
	Double_t jet1Phi=0;
	Double_t jet2Phi=0;
	Double_t jet3Phi=0;
	Double_t jet1Mass=0;
	Double_t jet2Mass=0;
	Double_t jet3Mass=0;

	static constexpr double mass_mu = .105658;

};





#endif /* VLFTwoMuonsChannel_H_ */
