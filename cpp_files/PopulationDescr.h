#ifndef POPULATIONDESCR_H_
#define POPULATIONDESCR_H_

#include <string>
#include <vector>

#include "constants.h"
#include "SynPopDescr.h"

using namespace std;

/** The PopulationDescr is used for parsing input data files. Instances of this class
is used as temporary storage of parameters describing population. */
class PopulationDescr {
public:
	/** PopulationDescr constructor. \param l is the label asigned to the Population being read. */
	PopulationDescr(const string &l);
	/** PopulationDescr destructor. Nothing to destroy. */
	virtual ~PopulationDescr();
	
	/** Population label. */
	string Label;

	/** Number of receptors available in this population. */
	int Nreceptors;
	/** Receptors labels. */
	string ReceptorLabel[MAX_RECEPTORS];

	/** This function returns the code of the receptor with name s for pop p 
	\return Code of the receptor. -1 in case of error */
	int ReceptorCode(const string& s){
		for(int r=0;r<Nreceptors;r++) {
			if (ReceptorLabel[r].compare(s)==0) 
	  			return r;
		}
		return -1;
	}
};

#endif /*POPULATIONDESCR_H_*/
