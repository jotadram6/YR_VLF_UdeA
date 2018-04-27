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
};





#endif /* VLFTwoMuonsChannel_H_ */
