#include "Connection.h"

Connection::Connection(){
	targetPopulation = -1;
	targetReceptor = -1; // 0=AMPA, 1=NMDA, 2=GABA
	Connectivity = 0; 
	Efficacy = 0;
	stfcode = char(0);
	stdcode = char(0);
	stdalfa = 0;
	stdtau = 0; 
	stfalfa = 0;
	stftau = 0;
	stp_code = char(0);
	stp_U = 0;
	stp_tauf = 0;
	stp_taud = 0;
	
}

Connection::~Connection(){
}
