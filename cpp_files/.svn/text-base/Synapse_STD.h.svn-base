#ifndef SYNAPSE_STD_H_
#define SYNAPSE_STD_H_

#include <cmath>
using namespace std;

#pragma pack(push,1)

class Synapse_STD : public SynapseBase
{
public:
	Synapse_STD() : SynapseBase() { this->STD = 1.0; };
	~Synapse_STD() {};

	inline void decayPlasticity(double deltaTime, const Connection& conn){
		STD = float(1.0) - (float(1.0)- STD) * exp(-float(deltaTime) / conn.stdtau);
	}

	inline void updatePlasticity(const Connection& conn) { this->STD *= conn.stdalfa; };

	inline float getLSsumand() { return this->STD; };

	// Only for NMDA axonals.
	inline void updateConductance() { };
	inline void decayConductance(float deltaTime, const Receptor &receptor) { };


	float STD;

	long calculateMemory() { return sizeof(this); };
};

#pragma pack(pop)

#endif
