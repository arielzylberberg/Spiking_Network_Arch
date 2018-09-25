#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <cmath> 
#include <cassert> 
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Event.h"
#include "Network.h"
#include "PopulationDescr.h"
#include "Population.h"
#include "rando2.h"
#include "utils.h"

using namespace std;

class Protocol {
public:
	Protocol(const string& f);
	~Protocol();
	string event_file_name;
	vector<Event*> Events;
	float trialDuration;

	int parseProtocol(const Network&);
	int parseProtocol2(const string& file, const Network& net);
	void sortEvents();

	//int getEventIndex() {return currentEvent;}
	void resetEventIndex() {currentEvent = 0;}
	bool advanceEventIndex() {currentEvent++; return (currentEvent<Events.size());}
	Event& getCurrentEvent() {return *Events[currentEvent];}
	float getNextTimeEvent() {return Events[currentEvent]->ETime;}
private:
	size_t currentEvent;

};

#endif /*NETWORK_H_*/
