#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>
#include <string>

#include "utils.h"
#include "Network.h"
#include "Protocol.h"

#include "randgen.hpp"
#include "r250.hpp"

R250 *r250;

using namespace std;

extern int flagverbose; //extern significa que la variable se declaro en otro archivo.
int NumberOfTrials;
int NumberOfTraces;

void parseArguments(int argc, char **argv);

int main(int argc, char **argv) {
	double dt = 5e-2;
	int delay_in_dt = 5;
	float nextTimeEvent;

	flagverbose = 0;

	cout << fixed;
	cout << setprecision(6);

	parseArguments(argc, argv);

	// Print type sizes.
	std::cout << "Printing type sizes..." << endl << endl;
	std::cout << "Type\tSize" << endl;
	std::cout << "----------------------" << endl;
	std::cout << "bool\t" << sizeof(char) << endl;
	std::cout << "char\t" << sizeof(char) << endl;
	std::cout << "short\t" << sizeof(short) << endl;
	std::cout << "int\t" << sizeof(int) << endl;
	std::cout << "long\t" << sizeof(long) << endl;
	std::cout << "float\t" << sizeof(float) << endl;
	std::cout << "double\t" << sizeof(double) << endl << endl;

	// Print own classes sizes.
	std::cout << "Synapse\t" << sizeof(Synapse) << endl;
	std::cout << "Receptor\t" << sizeof(Receptor) << endl;
	std::cout << "Neuron\t" << sizeof(Neuron) << endl;
	std::cout << "Population\t" << sizeof(Population) << endl;
	
	string test_string("esta oracion tiene 32 caracteres");
	std::cout << "Test string\t" << sizeof(test_string) << endl;
	std::cout << "Test string cap\t" << test_string.capacity() << endl;
	

	stringstream networkconfFileName;
	networkconfFileName<<"network.conf";

	stringstream networkproFileName;
	networkproFileName<<"network.pro";

	long int mySeed = time(0);
	r250 = new R250(mySeed);
	std::cout << "R250 initialized" << endl;

	Network net(networkconfFileName.str(),dt);
	
	std::cout << "Number of Populations\t" << net.Npop << endl;
	for (int i=0;i<net.Npop;i++){
		std::cout << "Number of cells in population " << i << ": \t" << net.Pop[i].Ncells << endl;
	}	

	net.connectPopulations(delay_in_dt);
	
	Protocol protocol(networkproFileName.str());
	protocol.parseProtocol(net);
	protocol.parseProtocol2("events.diff",net);
	protocol.sortEvents();
	
	stringstream RatesFileName;
	RatesFileName << "popfreqs_mem.dat";
	net.openSpikesFreqFile(RatesFileName.str());

	protocol.resetEventIndex();
	nextTimeEvent = protocol.getNextTimeEvent();

	std::cout << "Size after creating EVERYTHING: " << net.calculateMemory() << endl;

	//while(1);
	net.closeSpikesFreqFile();

	delete r250;

	closeReport();
	return EXIT_SUCCESS;
}


void parseArguments(int argc, char **argv){
    int argumentT=1;
    int argumentS=1;
	if(argc>1) {

		do {
			if(strncmp(argv[argc-1],"-v",2)==0) { flagverbose=1; argc--; continue; }

			if(strncmp(argv[argc-1],"-h",2)==0) {
				cout << "realsimu - Ver. 0.8\n Usage:\n-h  : this help\n-v  : verbose mode\n-t# : number of saved traces per population" << endl;
				cout << "-T# : number of trials (the network is the same for each trial, the realization of the ext noise changes)" << endl;
				cout << "-ns : spikes and traces are not saved. Only the mean frequencies are saved for each trial" << endl;
				exit(EXIT_SUCCESS);
			}

			if(strncmp(argv[argc-1],"-t",2)==0) { 
				NumberOfTraces=atoi(&argv[argc-1][2]);
				cout << "Number of saved traces: " << NumberOfTraces << endl;
				argc--; continue;
			}

			if(strncmp(argv[argc-1],"-s",2)==0) {
				int rseed=atoi(&argv[argc-1][2]);
                argumentS=0;//ariel
				srand49(rseed);
				cout << "Seed for random generator: " << rseed << endl;
				argc--; continue;
			}

/*			if(strncmp(argv[argc-1],"-ns",3)==0) {
				FlagSaveAllSpikes=0;
				NumberOfTraces=0;
				cout << "Spikes are not saved" << endl;
				argc--; continue;
			}
*/
			if(strncmp(argv[argc-1],"-T",2)==0) {
				NumberOfTrials=atoi(&argv[argc-1][2]);
				cout << "Number of trials: " << NumberOfTrials << endl;
                argumentT=0;//ariel
				argc--; continue;
			}
			cout << "ERROR: unrecognized option: " << argv[argc] << endl;
			argc--;
		} while(argc>1);
	}
    //ariel
    if (argumentT==1) NumberOfTrials=1; //ariel
    if (argumentS==1) {
         srand((unsigned)time(0)); 
         srand49(rand());
    }
    //fin ariel
}
