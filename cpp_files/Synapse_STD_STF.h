#ifndef SYNAPSE_STD_STF_H_
#define SYNAPSE_STD_STF_H_

#include "Synapse.h"
#include "Synapse_STD.h"
#include "Synapse_STF.h"

#pragma pack(push,1)

class Synapse_STD_STF : public SynapseBase
{
public:
	Synapse_STD_STF() : SynapseBase() { STF = 0.0; STD=1.0; };
	~Synapse_STD_STF() {};

	inline void decayPlasticity(double deltaTime, const Connection& conn) {
		STF *= exp( - float(deltaTime) / conn.stftau);
		STD = float(1.0) - (float(1.0)- STD) * exp(-float(deltaTime) / conn.stdtau);
	}

	inline void updatePlasticity(const Connection & conn) {
		this->STD *= conn.stdalfa;
		this->STF += conn.stfalfa * ( float(1.0) - this->STF);
	};

	inline float getLSsumand() {return STD*STF;} ;

	// Only for NMDA axonals.
	inline void updateConductance() {return;};
	inline void decayConductance(float deltaTime, const Receptor &receptor) {return;};

	float STF;
	float STD;

	long calculateMemory() { return sizeof(this); };
};

#pragma pack(pop)

#endif
