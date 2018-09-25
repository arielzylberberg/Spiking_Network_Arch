#ifndef SYNAPSE_NMDA_STF_H_
#define SYNAPSE_NMDA_STF_H_

#include "SynapseNMDA.h"

#pragma pack(push,1)

class SynapseNMDA_STF : public SynapseBase
{
public:
	SynapseNMDA_STF(float initLastcond) : SynapseBase() { this->LastConductance = initLastcond; this->STF=0.0; };
	~SynapseNMDA_STF() {};

	inline float getLSsumand(){
		return  (float(1.0) - this->LastConductance) * NMDA_ALPHA * this->STF;
	}

	inline void updateConductance(){
		this->LastConductance += NMDA_ALPHA * ( float(1.0) - this->LastConductance) * this->STF; 
		//check this. Facilitation and Depression for NMDA channels
	}

	inline void decayConductance(float deltaTime, const Receptor &receptor){
		this->LastConductance *= exp(-(deltaTime) / receptor.Tau);
	}

	inline void decayPlasticity(double deltaTime, const Connection & conn) { STF *= exp( - float(deltaTime) / conn.stftau); };
	inline void updatePlasticity(const Connection & conn) { this->STF += conn.stfalfa * ( float(1.0) - this->STF); };

	float STF;
	float LastConductance; // synaptic conductance when the last spike was emitted (useful for NMDA saturation), -1 if not NMDA (and hence no saturation)

	long calculateMemory() { return sizeof(this); };
};

#pragma pack(pop)

#endif
