#ifndef SYNAPSE_NMDA_STD_STF_H_
#define SYNAPSE_NMDA_STD_STF_H_

#include "SynapseNMDA.h"

#pragma pack(push,1)

class SynapseNMDA_STD_STF : public SynapseBase
{
public:
	SynapseNMDA_STD_STF(float initLastcond) : SynapseBase() { this->LastConductance = initLastcond; this->STD=1.0; this->STF=0.0; };
	~SynapseNMDA_STD_STF() {};

	inline float getLSsumand(){
		return  (float(1.0) - this->LastConductance) * NMDA_ALPHA * this->STD * this->STF;
	}

	inline void updateConductance(){
		this->LastConductance += NMDA_ALPHA * ( float(1.0) - this->LastConductance) * this->STD * this->STF;
		//check this. Facilitation and Depression for NMDA channels
	}

	inline void decayConductance(float deltaTime, const Receptor &receptor){
		this->LastConductance *= exp(-(deltaTime) / receptor.Tau);
	}

	inline void decayPlasticity(double deltaTime, const Connection& conn){
		STF *= exp( - float(deltaTime) / conn.stftau);
		STD = float(1.0) - (float(1.0)- STD) * exp(-(float(deltaTime)) / conn.stdtau);
	}

	inline void updatePlasticity(const Connection& conn) { 
		this->STD *= conn.stdalfa;
		this->STF += conn.stfalfa * ( float(1.0) - this->STF);
	};

	float STD;
	float STF;
	float LastConductance; // synaptic conductance when the last spike was emitted (useful for NMDA saturation), -1 if not NMDA (and hence no saturation)

	long calculateMemory() { return sizeof(this); };
};

#pragma pack(pop)

#endif
