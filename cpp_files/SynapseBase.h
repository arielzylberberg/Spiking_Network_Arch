#ifndef SYNAPSE_BASE_H_
#define SYNAPSE_BASE_H_

#include "Synapse.h"

#pragma pack(push,1)

class SynapseBase : public Synapse
{
public:
	SynapseBase() : Synapse() { } ;
	~SynapseBase() {};

	inline void decayPlasticity(double deltaTime, const Connection & conn) { return; };
	inline void updatePlasticity(const Connection& conn) { return; };

	inline float getLSsumand() { return 1.0; };

	// Only for NMDA axonals.
	inline void updateConductance() {return;};
	inline void decayConductance(float deltaTime, const Receptor &receptor) {return;};

	long calculateMemory() { return sizeof(this); };


};

#pragma pack(pop)

#endif
