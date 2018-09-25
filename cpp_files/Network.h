#ifndef NETWORK_H_
#define NETWORK_H_

#include <cmath> 
#include <cassert> 
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <iomanip> 
#include <vector>

#include "PopulationDescr.h"
#include "Population.h"
#include "rando2.h"
#include "utils.h"

extern R250 *r250;

using namespace std;

class Population;

#pragma pack(push,1)

/** The Network class represents the whole network. It includes the populations, and connections between them. */
class Network {
public:
	string network_conf_fileName;
	string network_pro_fileName;

	/** Network constructor. 
		\param ncfn is network description file name.
		\param dt is the time step used to advance network simulation. */
	Network(const string& ncfn, const double dt = 1e-1);

	/** Network destructor.*/
	~Network();

	/** Number of populations. Maximum value is sizeof(short): 32764. */
	short Npop;
	//vector<PopulationDescr*> PopD;
	
	/** Population array. Created during construction.*/
	PopulationPtr Pop;
	/** Function to retrieve Population index from name.
		\param s is the Population name to look for.
		\return Population index.*/
	int PopulationCode(const std::string& s) const;

	/** This function loads the network description from network description file. This file was passed by argument to the constructor. After calling loadNetworkDescription() you should call connectPopulations() to generate the corresponding interconnection. 
		\return An int with error code.*/
	int loadNetworkDescription() ;
	
	/** After loading the network description calling loadNetworkDescription(), connectPopulations() must be called. This function generates the corresponding interconnection taking into acount the connections defined and the conectivity. A random number is used to decide wether two neurons are conected. Once connected, a Synapse instance is created.
		\return An int with error code.*/
	int connectPopulations(const char delay_in_dt);

	/** Open file for saving spikes frequencies. This is an average calculation. For detailed spikes saving, see openDetailedSpikesFile. \return boolean value indicating success. */
	bool openSpikesFreqFile(const string& freqsFileName);
	/** Closes spikes frequencies file. */
	void closeSpikesFreqFile();
	/** Save spikes frequencies on file. Must be opened first. */
	void saveSpikesFreq(const float Time);
	/** Send spikes frequencies to ostream. Output is intended to be for screen. */
	void printSpikesFreq(const float Time, ostream& out);

	/** Open file for saving detailed spikes behaviour. \return boolean value indicating success. */
	bool openDetailedSpikesFile(const string& spikesFileName);
	/** Closes detailed spikes file. */
	void closeDetailedSpikesFile();
	/** Save detailed spikes on file. Must be opened first. */
	void saveDetailedSpikes(const float Time);

	/** Open file for saving traces of V (potential, in volts). \return boolean value indicating success. 
		\param freqsFileName is the file name. 
		\param numberOfTraces is the number of traces to be saved. Be carefull, many traces makes it unreadable, too much information. */
	bool openTracesVFile(const string& freqsFileName, const int numberOfTraces);
	/** Closes V traces file. */
	void closeTracesVFile();
	/** Save numberOfTraces V traces on file. Must be opened first. \param Time is the current time. \param numberOfTraces is the number of traces to be saved. Be carefull, many traces makes it unreadable, too much information. */
	void saveTracesV(const float Time, const int numberOfTraces);

	//bool saveAllSpikes;
	/** File object for spikes frequencies. */
	ofstream freqsFile;
	/** File object for detailed spikes information. */
	ofstream spikesFile;
	/** File object for V traces. */
	ofstream tracesVFile;

	/** One step simulation function. This is the whole program. Once network and protocols are loaded, this function is called in order to simulate one time-step. \param Time is the current time. \return Returns a int number with the error code. */
	int SimulateOneTimeStep(const float Time);

	/** Time step. */
	double dt;

	/** Function used for debugging application. It tries to estimate the amount of memory needed. It sub-estimates a lot, so don't trust it. \return Returns a long with the estimated memory needed in bytes. */
	long calculateMemory();
};

#pragma pack(pop)

#endif /*NETWORK_H_*/
