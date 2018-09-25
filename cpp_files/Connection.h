#ifndef __CONNECTION_H
#define __CONNECTION_H

#pragma pack(push,1)


/** This class represents a connection between neurons. 
  * Neurons from the same population share some of the parameters of the connection.
  * These are saved in this class. */
class Connection {
public:
	/** Connection constructor. No parameters needed. */
	Connection();
	/** Connection destructor. Nothing to be done. */
	~Connection();

	/** Target population. This connection represents some of 
	the parameters between neuron in two population */
	short targetPopulation;
	/** Target receptors. Options are: AMPA (0), NMDA (1) and GABA (2). */
	char targetReceptor;
	/** Each connection has a connectivity factor. Used for random number
	to decide what neuron to connect. */
	float Connectivity; 

	short int connectivityCode;

	/** Change in the conductance due to a single spike (nS) (hence it is always 
	positive, IPSP come out from rev pots) */
	float Efficacy; 

	float jplus; //Compte vars
	float jmin;
	float sigma;

	/** Takes value 1 if facilitation included for the population */
	char stfcode; 
	/** Takes value 1 if depression included for the population */
	char stdcode; 
	/** Depression parameter */
	float stdalfa;
	/** Depression parameter */
	float stdtau; 
	/** Facilitation parameter */
	float stfalfa;
	/** Facilitation parameter */
	float stftau;
	/** Plasticity parameters - Tsodyks model */
	char stp_code;
	float stp_U;
	float stp_tauf;
	float stp_taud;
};

#pragma pack(pop)


#endif
