#include "Protocol.h"

Protocol::Protocol(const std::string &f){
	event_file_name = f;
	trialDuration = 0;
}

int Protocol::parseProtocol(const Network& net) {
	int eventflag=0;
	//int currentEvent;
	int line,auxi,currentpop=-1;
	string buffer;
	ifstream file;

	char temporal[10];

/*	report("-----------------------------\nParsing protocol... Counting Events number\n");

	// Read number of events 
	NEvents=0;
	file.open(event_file_name.c_str());
	while(!file.eof()) {
		getline(file,buffer);
		removeComments(trim(buffer));

		if(buffer.compare(0,8,"EndEvent")==0)
			NEvents++;
	}
	file.close();

	Events = new Event[NEvents];
*/
	report("-------------------------------------------------\nParsing protocol...\n");
	
	file.clear();
	file.open(event_file_name.c_str());
	if(!file.is_open()) { report("ERROR:  Unable to read protocol file\n"); return PARSE_ERROR;}

	line = -1; currentEvent=0;
	while(!file.eof()) {
		getline(file,buffer);
		removeComments(trim(buffer));
		line++;
		
		// commands for defining a new event
		if(buffer.compare(0,9,"EventTime")==0)	{
			Event* ev = new Event;
			eventflag=1;
			stringstream(buffer.substr(9,string::npos)) >> ev->ETime;

			if(ev->ETime < 0.) {
				printf("ERROR: Invalid event time, line %d\n",line);
				delete ev;
				return PARSE_ERROR;
			} 
			this->Events.push_back(ev);

			report("Event %d: time %f ms\n",currentEvent,Events[currentEvent]->ETime);
			continue;
		}

		if(buffer.compare(0,8,"EndEvent")==0) {
			eventflag=0;
			currentEvent++;
			continue;
		}

		if(buffer.compare(0,5,"Type=")==0) {
			trim(buffer = buffer.substr(5,string::npos));

			if(buffer.compare(0,13,"ChangeExtFreq")==0) {
				Events[currentEvent]->Type=CHANGE_EXT_FREQ;
			}

			if(buffer.compare(0,19,"ChangeExtFreqInside")==0) {
				Events[currentEvent]->Type=CHANGE_EXT_FREQ_INSIDE;
			}

			if(buffer.compare(0,18,"ChangeExtFreqGauss")==0) {
				Events[currentEvent]->Type=CHANGE_EXT_FREQ_GAUSS_DELTA;
			}

			if(buffer.compare(0,17,"ChangeDummyOutput")==0) {
				Events[currentEvent]->Type=CHANGE_DUMMY_OUTPUT;
			}

			if(buffer.compare(0,8,"EndTrial")==0) {
				Events[currentEvent]->Type=END_OF_TRIAL;
				trialDuration = Events[currentEvent]->ETime;
			}
			continue;
		}

		if(buffer.compare(0,8,"FreqExt=")==0) {
			stringstream(buffer.substr(8,string::npos)) >> Events[currentEvent]->FreqExt;
			report("  New external frequency: %f Hz\n",Events[currentEvent]->FreqExt);
			continue;
		}

		if(buffer.compare(0,11,"OutputRate=")==0) {
			stringstream(buffer.substr(11,string::npos)) >> Events[currentEvent]->DummyOutput;
			report("  New dummy output frequency: %f Hz\n",Events[currentEvent]->DummyOutput);
			continue;
		}

		if(buffer.compare(0,6,"Label=")==0) {
			Events[currentEvent]->Label = buffer.substr(6,string::npos);
			report("   Label: [%s]\n",Events[currentEvent]->Label.c_str());
			continue;
		}

		if(buffer.compare(0,11,"Population:")==0 && eventflag) {
			buffer = buffer.substr(11,string::npos);
			currentpop = net.PopulationCode(trim(buffer));
			if(currentpop==INVALID_POPULATION_CODE) { printf("ERROR: Unknown population: line %d\n",line); return PARSE_ERROR;}
			Events[currentEvent]->PopNumber=currentpop;
			report("  Population code: %d\n",currentpop);
			continue;
		}

		if(buffer.compare(0,12,"CellNumbers:")==0) {
			buffer = buffer.substr(12,string::npos);
			
			stringstream sss(buffer);
			while (sss.getline(temporal, 10, ',' ))
 		    {
				Events[currentEvent]->ETargetCells.push_back(atoi(temporal));
		    }
		}

		if(buffer.compare(0,10,"StdDevExt=")==0) {
			stringstream(buffer.substr(10,string::npos)) >> Events[currentEvent]->StdDevExt;
			report("  Standard Deviation: %f [deg normalized to 0-1]\n",Events[currentEvent]->StdDevExt);
			continue;
		}



		if(buffer.compare(0,9,"Receptor:")==0 && eventflag) {
			buffer=buffer.substr(9,string::npos);
			auxi=net.Pop[currentpop].ReceptorCode(trim(buffer));
			if(auxi==-1) { printf("ERROR: Unknown receptor, line %d\n",line); return PARSE_ERROR; }
			Events[currentEvent]->ReceptorNumber=auxi;
			report("  Receptor code:%d\n",auxi);
		}
	} // end while

	file.close();

	return PARSE_OK;
}

int Protocol::parseProtocol2(const string& fileName, const Network& net){
	int eventflag=0;
	size_t currEvent;
	int line,auxi,currentpop=-1;
	string buffer;
	ifstream file;
   
  report("-------------------------------------------------\nParsing protocol2...\n");
  file.open(fileName.c_str());
    //if(devprot==NULL) {printf("WARNING:  Unable to read protocol file 2 \n"); return 0;}
  if(!(file.is_open() && file.good())) {return 0;}

  line=-1; 
  currEvent=this->Events.size();
  while(!file.eof()) {      
		getline(file,buffer);
		removeComments(trim(buffer));

       // commands for defining a new event
		if(buffer.compare(0,9,"EventTime")==0) {
			eventflag=1;
			Event* ev = new Event;
			ev->Type=EVENT_2;
			stringstream(buffer.substr(9,string::npos)) >> ev->ETime;
			if(ev->ETime<0.) {
				report("ERROR: Invalid event time, line %d\n",line);
				delete ev;
				return PARSE_ERROR;
			}
			this->Events.push_back(ev);
			continue;
		}

		if(buffer.compare(0,8,"EndEvent")==0) {
			eventflag=0;
			currEvent++;
			continue;
		}

		if(buffer.compare(0,8,"FreqExt=")==0) {
			stringstream(buffer.substr(8,string::npos)) >> Events[currEvent]->FreqExt;
			continue;
		}
      
		if(buffer.compare(0,11,"Population:")==0) {
			buffer = buffer.substr(11,string::npos);
			currentpop=net.PopulationCode(trim(buffer));
			if(currentpop==INVALID_POPULATION_CODE) { printf("ERROR: Unknown population: line %d\n",line); return PARSE_ERROR;}
			Events[currEvent]->PopNumber=currentpop;
	
			report("  Population code: %d\n",currentpop);
			continue;
		}

		if(buffer.compare(0,9,"Receptor:")==0 && eventflag) {
			buffer = buffer.substr(9,string::npos);
			auxi=net.Pop[currentpop].ReceptorCode(trim(buffer));
			if(auxi==INVALID_RECEPTOR_CODE) { printf("ERROR: Unknown receptor, line %d\n",line); return PARSE_ERROR; }
			Events[currEvent]->ReceptorNumber=auxi;
			report("  Receptor code:%d\n",auxi);
			continue;
		}

    } // end while

	return PARSE_OK;
}

Protocol::~Protocol(){
	unsigned int i;

	for (i =0;i<Events.size();i++)
		delete Events[i];
}

void Protocol::sortEvents(){

	sort (Events.begin(),Events.end(),Event::compareEvents);
}
