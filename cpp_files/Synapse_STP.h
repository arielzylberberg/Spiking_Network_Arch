#ifndef SYNAPSE_STP_H_
#define SYNAPSE_STP_H_

#include "Connection.h"

#include <cmath>
using namespace std;

#pragma pack(push,1)

class Synapse_STP : public SynapseBase
{
public:
	Synapse_STP() : SynapseBase() { x = 1.0; u = 0.2; };
	~Synapse_STP() {};

	inline void decayPlasticity(double deltaTime, const Connection& conn) {
	
        x = float(1.0) - (float(1.0) - x) * exp(-float(deltaTime) / conn.stp_taud);
	    u = conn.stp_U - (conn.stp_U - u) * exp(-float(deltaTime) / conn.stp_tauf);
	    
	}

	inline void updatePlasticity(const Connection & conn) {
		this->x *= (float(1.0) - this->u);
		this->u += conn.stp_U * ( float(1.0) - this->u);
	};

	inline float getLSsumand() {return x*u;} ;

	// Only for NMDA axonals.
	inline void updateConductance() {return;};
	inline void decayConductance(float deltaTime, const Receptor &receptor) {return;};

	float x;
	float u;

	long calculateMemory() { return sizeof(this); };
};

#pragma pack(pop)

#endif
