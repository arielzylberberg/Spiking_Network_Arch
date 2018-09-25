#ifndef SYNAPSE_STF_H_
#define SYNAPSE_STF_H_

#include "Connection.h"

#include <cmath>
using namespace std;

#pragma pack(push,1)

class Synapse_STF : public SynapseBase
{
public:
	Synapse_STF() : SynapseBase() { this->STF = 0.0; };
	~Synapse_STF() {};

	inline void decayPlasticity(double deltaTime, const Connection& conn){
		STF *= exp( - float(deltaTime) / conn.stftau);
	}

	inline void updatePlasticity(const Connection& conn) { this->STF += conn.stfalfa * ( float(1.0) - this->STF); } ;

	inline float getLSsumand() { return this->STF; };

	// Only for NMDA axonals.
	inline void updateConductance() { return; } ;
	inline void decayConductance(float deltaTime, const Receptor &receptor) { return; } ;

	float STF;

	long calculateMemory() { return sizeof(this); };
};

#pragma pack(pop)

#endif
