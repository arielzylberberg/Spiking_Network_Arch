#ifndef __CONSTANTS_H
#define __CONSTANTS_H

// Max MPI nodes for calculating seeds.
#define MAX_NODES 200

// Max buffer size for parsing.
#define MAX_LINE_BUFFER 2000

// When parsing network description we need to define the maximum number of populations
// and conections between them.
//#define MAX_POPULATIONS 100
#define MAX_TARGET_POP 100
//#define MAX_NUMBER_CELLS 1500

// Loading of network errors
#define LOAD_NETWORK_OK 0
#define LOAD_NETWORK_ERROR 1
#define LOAD_POPULATION_OK 0

// Constants for max number of population fields.
#define MAXDELAYINDT 50
#define MAXSPIKESINDT 10000

// types of receptors
#define MAX_RECEPTORS 3
#define AMPA 0
#define GABA 1
#define NMDA 2

// Constants for reserving memory for simulation.
// Max. number of target neurons
//#define MAX_TARGET_NEURONS (MAX_NUMBER_CELLS*MAX_TARGET_POP) 
// was previously 20000.

// Max. number of populations.
#define MAXP 80 
// Max. number of events.
#define MAXEVENTS 100
// Max. number of events (2nd type).
#define MAXEVENTS2 2000 // Added by AZ

// Constants for protocols.
#define END_OF_TRIAL 1
#define CHANGE_EXT_FREQ 2
#define CHANGE_EXT_FREQ_INSIDE 3
#define CHANGE_EXT_FREQ_GAUSS_DELTA 4
#define CHANGE_DUMMY_OUTPUT 5 
#define EVENT_2 5 


// Constants for DescribeNetwork
#define EXC 0
#define INH 1

// Constants for Generate Network
#define GENERATE_NETWORK_OK 0
#define ALLOCATE_YES 0
#define ALLOCATE_NO 1

// Return values for ParseProtocol (or ParseProtocol2)
#define PARSE_OK -2
#define PARSE_ERROR -1
#define PARSE_FILE_NOT_FOUND 0

// Return values for search operations.
#define INVALID_POPULATION_CODE -1
#define INVALID_RECEPTOR_CODE -1

// *** Constants for Data Analysis. ***
#define TIMEWINDOWFORFREQ 20.  // time window on which the mean pop frequency is estimated (in ms)
#define RASTERPLOTNEURONS 50   // number of neurons in the raster plot
#define STEPS_FOR_PRINTING_FREQS 500 // every ... step, the frequencies are printed
#define STEPS_FOR_SAVING_FREQS 40 // every ... step the frequencies are saved (not always, to save space)
#define STEPS_FOR_FLUSHING 80
#define STEPS_FOR_SAVING_EXT 50 //AZ every ... steps save external input (lambda) to each population
// File name for saving traces.
#define SAVE_TRACES_NAME "popTraces"
// number of visualized traces of V.
#define NUMBER_OF_TRACES 2 

#endif
