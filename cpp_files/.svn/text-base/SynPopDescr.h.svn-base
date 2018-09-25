#ifndef SYNPOPDESCR_H_
#define SYNPOPDESCR_H_

class SynPopDescr
{
public:
	SynPopDescr();
	virtual ~SynPopDescr();

	float Connectivity; // mean fraction of randomly connected target neurons
	  int TargetReceptor; // 0=AMPA, ...
	  float MeanEfficacy; // mean efficacy (for initialization) 
	  
	  char stfcode; //takes value 1 if facilitation included for the population
	  char stdcode; //takes value 1 if depression included for the population
	  float stdalfa; //depression parameter
	  float stdtau; //depression parameter
	  float stfalfa; //facilitation parameter
	  float stftau; //facilitation parameter
	  float STF;
	  float STD;

};

#endif /*SYNPOPDESCR_H_*/
