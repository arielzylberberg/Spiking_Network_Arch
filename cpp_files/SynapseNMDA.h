#ifndef SYNAPSE_NMDA_H_
#define SYNAPSE_NMDA_H_

#include "Receptor.h"

#pragma pack(push,1)

#define NMDA_ALPHA float(0.6332)

class SynapseNMDA : public SynapseBase
{
public:
	SynapseNMDA(float initLastcond) : SynapseBase() { this->LastConductance = initLastcond; };
	~SynapseNMDA() {};

	float LastConductance; // synaptic conductance when the last spike was emitted (useful for NMDA saturation), -1 if not NMDA (and hence no saturation)

	inline float getLSsumand(){
		return  (float(1.0) - this->LastConductance) * NMDA_ALPHA ;
	}

	inline void updateConductance(){
		this->LastConductance += NMDA_ALPHA * ( float(1.0) - this->LastConductance) ; 
		//check this. Facilitation and Depression for NMDA channels
	}

	inline void decayConductance(float deltaTime, const Receptor &receptor){
		this->LastConductance *= exp(-(deltaTime) / receptor.Tau);
	}

	inline void decayPlasticity(double deltaTime, const Connection & conn) { return; };
	inline void updatePlasticity(const Connection & conn) { return; };
	long calculateMemory() { return sizeof(this); };

};

#pragma pack(pop)

#endif
