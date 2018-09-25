#ifndef __RECEPTOR_H
#define __RECEPTOR_H

#include <string>

#pragma pack(push,1)

/** This class represents a receptor. */
class Receptor {
public:
	/** Receptor constructor. */
	Receptor();
	/** Receptor destructor. */
	~Receptor();

	/** Receptor label. */
	std::string receptorLabel;


	//float ExtMuS; // nS/s 
	//float ExtSigmaS; // nS/s^2 

	/**  Tau for each conductance */
	float Tau;
	float ExpConstantTau;
	float SqrtConstantTau; 
	float OneOverTau;
	float RevPots;
	/** Magnesium blocking flag. 1 is magnesium block is active, 0 otherwise. */
	int   MgFlag; 

	// external input (externally defined)
	float MeanExtCon; // mean total number of external connections
	float MeanExtEff; // external mean efficacy
	//float FreqExt; // external frequency in Hz NOTE: transfered to "Cell"
	float FreqExtIni; // initial external frequency in Hz. Required for multi-trial simulations

};


#pragma pack(pop)

#endif
