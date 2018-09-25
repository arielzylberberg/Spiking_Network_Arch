#include "SynPopDescr.h"

SynPopDescr::SynPopDescr()
{
	Connectivity=0; // mean fraction of randomly connected target neurons
	TargetReceptor=0; // 0=AMPA, ...
	MeanEfficacy=0; // mean efficacy (for initialization) 
	  
	  stfcode=char(0); //takes value 1 if facilitation included for the population
	  stdcode=char(0); //takes value 1 if depression included for the population
	  stdalfa=0; //depression parameter
	  stdtau=0; //depression parameter
	  stfalfa=0; //facilitation parameter
	  stftau=0; //facilitation parameter
	  STF=0;
	  STD=0;
}

SynPopDescr::~SynPopDescr()
{
}
