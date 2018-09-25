#ifndef SYNAPSE_NMDA_STD_H_
#define SYNAPSE_NMDA_STD_H_

#include "SynapseNMDA.h"

#pragma pack(push,1)

class SynapseNMDA_STD : public SynapseBase
{
public:
	SynapseNMDA_STD(float initLastcond) : SynapseBase() { this->LastConductance = initLastcond; this->STD=1.0;  };
	~SynapseNMDA_STD() {};

	inline float getLSsumand(){
		return  (float(1.0) - this->LastConductance) * NMDA_ALPHA * this->STD;
	}

	inline void updateConductance(){
		this->LastConductance += NMDA_ALPHA * ( float(1.0) - this->LastConductance) * this->STD; 
		//check this. Facilitation and Depression for NMDA channels
	}

	inline void decayConductance(float deltaTime, const Receptor &receptor){
		this->LastConductance *= exp(-float(deltaTime) / receptor.Tau);
	}

	inline void decayPlasticity(double deltaTime, const Connection& conn){
		STD = float(1.0) - (float(1.0)- STD) * exp(-float(deltaTime) / conn.stdtau);
	}

	inline void updatePlasticity(const Connection& conn) { this->STD *= conn.stdalfa; };

	float STD;
	float LastConductance; // synaptic conductance when the last spike was emitted (useful for NMDA saturation), -1 if not NMDA (and hence no saturation)

	long calculateMemory() { return sizeof(this); };
};

#pragma pack(pop)

#endif
