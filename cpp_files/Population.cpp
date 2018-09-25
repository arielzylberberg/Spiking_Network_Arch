#include "Population.h"
#include "Network.h"

Population::Population()
{
	int i,j;

	// Initialize every variable to 0.
	Dummy = false;
	DummyOutputRate = 0.0;

	meanFreqs = 0;
	meanFreqsBetweenEvents = 0;
	Ncells = 0;
	for (i = 0;i<MAXDELAYINDT;i++) {
		NTableofSpikes[i] = 0;
		for (j=0;j<MAXSPIKESINDT;j++)
			TableofSpikes[i][j]=0;
	}
	CTableofSpikes = 0;
	DTableofSpikes = 0;

	C = 0; // capacitance in nF
	OneOverC = 0; //for computational efficency
	Taum = 0; // membrane time constant
	OneOverTaum = 0; //for computational efficency
	RestPot = 0; // Resting potential
	ResetPot = 0; // reset potential
	Threshold = 0; // threhsold
	RefPeriod = 0; //periodo refractario

	SFACode = false; //0 si no hay SFA, 1 si si hay.
	//dCA = 0; //concentracion de calcio
	tca = 0; //constante de tiempo decaimiento de la concentracion de calcio intracelular
	ExpConstantTca = 0; //for computational efficency
	gAHP = 0; //conductancia de potasio. Notar que gAHP*CA es la conductancia efectiva.
	Vk = 0; //potencial de reversion del potasio

	Nreceptors = 0;

	conn.resize(0);
	Label.resize(100);
}

Population::~Population()
{
	delete[] Cell;
}

int Population::reserveMemory(){
	int result;

	Cell= new Neuron[Ncells];
	result = (Cell!=NULL);
	
	return (Cell!=NULL);
}

float Population::getMeanFreqBetweenEvents(){
	int TempPointer;

	TempPointer=this->CTableofSpikes-1;
	if(TempPointer<0) TempPointer=MAXDELAYINDT-1;

	return float(this->NTableofSpikes[TempPointer])/float(this->Ncells);
}

/*bool Population::openSpikesFile(const string& fileName){
	spikesFile.open(fileName.c_str());
	return (spikesFile.is_open() && spikesFile.good());
}

void Population::closeSpikesFile(){
	spikesFile.close();
}
*/
void Population::saveAllSpikes(ostream &spikesFile, const int popID, const float Time){
	int i, TempPointer;
	TempPointer=CTableofSpikes-1;
	if(TempPointer<0) TempPointer=MAXDELAYINDT-1;

	for(i=0;i<this->NTableofSpikes[TempPointer];i++) {
		spikesFile << Time << "\t" << popID << "\t" << this->TableofSpikes[TempPointer][i] << endl;
	}
}

void Population::updateFreqs(const float dt){
	int TempPointer;

	TempPointer=CTableofSpikes-1;
	if(TempPointer<0) TempPointer=MAXDELAYINDT-1;

	this->meanFreqsBetweenEvents += float(NTableofSpikes[TempPointer])/float(Ncells)/float(dt)*float(1000.);
	this->meanFreqs += float(dt)/float(TIMEWINDOWFORFREQ)*(-meanFreqs+float(NTableofSpikes[TempPointer])/float(Ncells)/float(dt)*float(1000.)); // compute mean freq in Hz on a time window of 10 ms
}


int Population::loadPopulation(const Network& net, std::istream &in){
	bool finish = false;

	int currentreceptorflag = 0;
	int currentreceptor = -1;
	string buffer;

	float tempCA;


	while (!finish){
		
		getline(in,buffer);
		removeComments(trim(buffer));

		if (buffer.compare(0,19,"EndNeuralPopulation")==0){
			finish = true;
			continue;
		}

		// paramters for the population
		if (buffer.compare(0,2,"N=")==0) {
			stringstream ss(buffer.substr(2,string::npos));
			ss >> this->Ncells;
			report("  N=%d\n", this->Ncells);
			//assert(this->Ncells<MAX_NUMBER_CELLS);
			continue;
		}
		if (buffer.compare(0,2, "C=")==0) {
			stringstream ss(buffer.substr(2,string::npos));
			ss >> this->C;

			/// Variable for optimization
			this->OneOverC = float(1.0) / this->C;

			report("  C=%f nF\n", double(this->C));
			continue;
		}
		if (buffer.compare(0,5, "Taum=")==0) {
			stringstream ss(buffer.substr(5,string::npos));
			ss >> this->Taum;
			this->OneOverTaum = float(1.0) / this->Taum;
			report("  Membrane time constant=%f ms\n", double(this->Taum));
			continue;
		}
		if (buffer.compare(0,8, "RestPot=")==0) {
			stringstream ss(buffer.substr(8,string::npos));
			ss >> this->RestPot;
			report("  Resting potential=%f mV\n", double(this->RestPot));
			continue;
		}
		if (buffer.compare(0,9, "ResetPot=")==0) {
			stringstream ss(buffer.substr(9,string::npos));
			ss >> this->ResetPot;
			report("  Reset potential=%f mV\n", double(this->ResetPot));
			continue;
		}
		if (buffer.compare(0,10, "Threshold=")==0) {
			stringstream ss(buffer.substr(10,string::npos));
			ss >> this->Threshold;
			report("  Threshold =%f mV\n", double(this->Threshold));
			continue;
		}
		if (buffer.compare(0,10, "RefPeriod=")==0) {
			stringstream ss(buffer.substr(10,string::npos));
			ss >> this->RefPeriod;
			report("  RefPeriod =%f ms\n", double(this->RefPeriod));
			continue;
		}
		//SFA vars
		if (buffer.compare(0,8, "SFACode=")==0) {
			stringstream ss(buffer.substr(8,string::npos));
			ss >> this->SFACode;
			report("  SFACode =%d \n", double(this->SFACode));
			continue;
		}
		if (buffer.compare(0,3, "CA=")==0 ) {
			stringstream ss(buffer.substr(3,string::npos));
			ss >> tempCA;
			report("  CA =%f \n", double(tempCA));
			continue;
		}
		if (buffer.compare(0,4,"dCA=")==0) {
			stringstream ss(buffer.substr(4,string::npos));
			ss >> this->dCA;
			report("  dCA =%f \n", double(this->dCA));
			continue;
		}
		if (buffer.compare(0,4,"tca=")==0) {
			stringstream ss(buffer.substr(4,string::npos));
			ss >> this->tca;

			/// Variable for optimization
			this->ExpConstantTca = exp(-float(net.dt)/this->tca);
			
			report("  tca =%f \n", double(this->tca));
			continue;
		}
		if (buffer.compare(0,5,"gAHP=")==0) {
			stringstream ss(buffer.substr(5,string::npos));
			ss >> this->gAHP;
			report("  gAHP =%f \n", double(this->gAHP));
			continue;
		}
		if (buffer.compare(0,3, "Vk=")==0) {
			stringstream ss(buffer.substr(3,string::npos));
			ss >> this->Vk;
			report("  Vk =%f \n", double(this->Vk));
			continue;
		}
		if (buffer.compare(0,6, "Dummy=")==0) {
			char dum;
			stringstream ss(buffer.substr(6,string::npos));
			ss >> this->Dummy;
			continue;
		}
		if (buffer.compare(0,16,"DummyOutputRate=")==0) {
			stringstream ss(buffer.substr(16,string::npos));
			ss >> this->DummyOutputRate;
			report("DummyOutputRate =%f\n",double(this->DummyOutputRate));
			continue;
		}

		// receptor parameters
		if (buffer.compare(0,9, "Receptor:")==0) {
			currentreceptorflag=1;
			string sub_buffer = buffer.substr(9,string::npos);
			removeComments(trim(sub_buffer));
			
			currentreceptor = this->ReceptorCode(sub_buffer);
			if (currentreceptor==-1) {
				printf("ERROR: Unknown receptor type\n");
				return LOAD_NETWORK_ERROR;
			}

			if (sub_buffer.compare(0,4, "NMDA")==0) { // activate magnesium block for NMDA type
				this->receptor[currentreceptor].MgFlag=1;
			} else
				this->receptor[currentreceptor].MgFlag=0;
			
			report("Receptor %d: %s (Mg block: %d)\n", currentreceptor, this->receptor[currentreceptor].receptorLabel.c_str(),this->receptor[currentreceptor].MgFlag);
			continue;
		}

		if (buffer.compare(0,11, "EndReceptor")==0) {
			currentreceptorflag=0;
			continue;
		}

		if (buffer.compare(0,4, "Tau=")==0 && currentreceptorflag) {
			stringstream ss(buffer.substr(4,string::npos));
			ss >> this->receptor[currentreceptor].Tau;
			
			// Variables for optimization.
			this->receptor[currentreceptor].ExpConstantTau = exp(-float(net.dt)/this->receptor[currentreceptor].Tau);
			this->receptor[currentreceptor].SqrtConstantTau = sqrt( float(net.dt * 2.)	/ this->receptor[currentreceptor].Tau);
			this->receptor[currentreceptor].OneOverTau = float(1.0) / this->receptor[currentreceptor].Tau;

			report("  Tau=%f ms\n",	double(this->receptor[currentreceptor].Tau));
			continue;
		}
		if (buffer.compare(0,7,"RevPot=")==0 && currentreceptorflag) {
			stringstream ss(buffer.substr(7,string::npos));
			ss >> this->receptor[currentreceptor].RevPots;
			report("  Reversal potential=%f mV\n", double(this->receptor[currentreceptor].RevPots));
			continue;
		}

		if (buffer.compare(0,8,"FreqExt=")==0 && currentreceptorflag) {
			stringstream ss(buffer.substr(8,string::npos));
			ss >> this->receptor[currentreceptor].FreqExtIni;
			report("  Ext frequency=%f Hz\n", double(this->receptor[currentreceptor].FreqExtIni));
			
			continue;
		}
		if (buffer.compare(0,11, "MeanExtEff=")==0 && currentreceptorflag) {
			stringstream ss(buffer.substr(11,string::npos));
			ss >> this->receptor[currentreceptor].MeanExtEff;
			report("  Ext efficacy=%f nS\n", double(this->receptor[currentreceptor].MeanExtEff));
			continue;
		}
		if (buffer.compare(0,11,"MeanExtCon=")==0 && currentreceptorflag) {
			stringstream ss(buffer.substr(11,string::npos));
			ss >> this->receptor[currentreceptor].MeanExtCon;
			report("  Ext connections=%f\n", double(this->receptor[currentreceptor].MeanExtCon));
			continue;
		}

		// target populations

		if (buffer.compare(0,17, "TargetPopulation:")==0) {
			int currentTarget;
			string targetPop = buffer.substr(17,string::npos);
			currentTarget=net.PopulationCode(trim(targetPop));
			if (currentTarget==INVALID_POPULATION_CODE) {
				printf("Unknown target population: popularion %s\n", this->Label.c_str());
				return LOAD_NETWORK_ERROR;
			}

			this->CreateConnection(net, in, currentTarget);
		
			continue;
		}

	}

	// Initialize everything inside this population.

	// Create neurons and initialize them.
	Cell = new Neuron[Ncells];
	for (int i=0; i<this->Ncells; i++) {
		// single neuron parameters
		if (this->SFACode==1) {
			Cell[i].CA=tempCA;
		} else {
			Cell[i].CA= 0.0;
			this->dCA=0.0;
			this->tca=1.0; //to avoid division by 0
			this->ExpConstantTca=exp(-float(net.dt)/ this->tca);
			this->gAHP=0.0;
			this->Vk=0.0;
		}

		// init
		Cell[i].V = this->RestPot;
	}

	for (int i=0; i<this->Ncells; i++) {
		for (int rd=0; rd<Nreceptors; rd++) {
			
			this->Cell[i].FreqExt[rd] = receptor[rd].FreqExtIni; 

			// external input: compute first the asymptoic mu and sigma (m,s in nphys notation) of the conductances
			this->Cell[i].ExtMuS[rd] = receptor[rd].FreqExtIni * float(.001)
				* receptor[rd].MeanExtEff * receptor[rd].MeanExtCon * receptor[rd].Tau;
			this->Cell[i].ExtSigmaS[rd] = sqrt( receptor[rd].Tau * float(.5)	* receptor[rd].FreqExtIni * float(.001) 
				* receptor[rd].MeanExtEff * receptor[rd].MeanExtEff * receptor[rd].MeanExtCon);
		}
	}
	
	// report just one cell
	for (int rd=0; rd<Nreceptors; rd++) {
		report("Pop (%s) Conductance: %d m=%f nS s=%f nS\n", this->Label.c_str(), rd,
			this->Cell[0].ExtMuS[rd], this->Cell[0].ExtSigmaS[rd]);
	}


	return LOAD_POPULATION_OK;
}

	  // returns the code of the receptor with name s for pop p (-1 in case of error)
int Population::ReceptorCode(const string& s){
	  	for(int r=0;r<Nreceptors;r++)
	  	{
			if (this->receptor[r].receptorLabel.compare(s)==0) 
	  			return r;
	  	}
	  	return -1;
}

int Population::CreateConnection(const Network& net, istream &in, const int currentTarget){
	bool finish = false;
	string buffer;

	// Add size for the new connection.
	size_t cn = conn.size();
	this->conn.resize(cn+1);
	
	// Set target population.
	conn[cn].targetPopulation = currentTarget;
	

	while (!finish){
		// Load connection parameters from file.
		getline(in,buffer);
		removeComments(trim(buffer));

		if (buffer.compare(0,19,"EndTargetPopulation")==0){
			finish=true;
			continue;
		}

		if (buffer.compare(0,13, "Connectivity=")==0) {
			stringstream ss(buffer.substr(13,string::npos));
			ss >> conn[cn].Connectivity;
			report("  Connectivity=%f\n", double(conn[cn].Connectivity));
			continue;
		}
		if (buffer.compare(0,15, "TargetReceptor=")==0) {
			string sub_buffer = buffer.substr(15,string::npos);
			int targetReceptor = net.Pop[currentTarget].ReceptorCode(trim(sub_buffer));
			if (targetReceptor==-1) {
				printf("Unknown target receptor\n");
				return LOAD_NETWORK_ERROR;
			}
			conn[cn].targetReceptor = targetReceptor;
			report("  Target receptor code=%d\n", targetReceptor);
			continue;
		}

		if (buffer.compare(0,17, "ConnectivityCode=")==0) {
			stringstream ss(buffer.substr(17,string::npos));
			ss >> conn[cn].connectivityCode;
			report("Connectivity Code=%f\n", conn[cn].connectivityCode);
			continue;
		}
		
		if (buffer.compare(0,6, "Jplus=")==0) {
			stringstream ss(buffer.substr(6,string::npos));
			ss >> conn[cn].jplus;
			report("Jplus=%f\n", conn[cn].jplus);
			continue;
		}
		
		if (buffer.compare(0,5, "Jmin=")==0) {
			stringstream ss(buffer.substr(5,string::npos));
			ss >> conn[cn].jmin;
			report("Jmin=%f\n", conn[cn].jmin);
			continue;
		}

		if (buffer.compare(0,6, "Sigma=")==0) {
			stringstream ss(buffer.substr(6,string::npos));
			ss >> conn[cn].sigma;
			report("Sigma=%f\n", conn[cn].sigma);
			continue;
		}

		if (buffer.compare(0,8, "MeanEff=")==0) {
			stringstream ss(buffer.substr(8,string::npos));
			ss >> conn[cn].Efficacy;
			report("Mean efficacy=%f\n", double(conn[cn].Efficacy));
			continue;
		}

        if (buffer.compare(0,6, "stp_U=")==0) {
			conn[cn].stp_code = char(1);// stp_U "prende" el STP 
			report("ShortTermPlasticity ON\n");
			stringstream ss(buffer.substr(6,string::npos));
			ss >> conn[cn].stp_U;
			report("STP U=%f\n", double(conn[cn].stp_U));
			continue;
		}
        
        if (buffer.compare(0,9, "stp_tauf=")==0) {
			report("STP Tau Facilit\n");
			stringstream ss(buffer.substr(9,string::npos));
			ss >> conn[cn].stp_tauf;
			report("STP TauF=%f\n", double(conn[cn].stp_tauf));
			continue;
		}
        
        if (buffer.compare(0,9, "stp_taud=")==0) {
			report("STP Tau Depression\n");
			stringstream ss(buffer.substr(9,string::npos));
			ss >> conn[cn].stp_taud;
			report("STP TauD=%f\n", double(conn[cn].stp_taud));
			continue;
		}

		if (buffer.compare(0,8, "stdalfa=")==0) {
			conn[cn].stdcode = char(1);
			report("Depression ON\n");
			stringstream ss(buffer.substr(8,string::npos));
			ss >> conn[cn].stdalfa;
			report("Depression Strength=%f\n", double(conn[cn].stdalfa));
			continue;
		}

		if (buffer.compare(0,7, "stdtau=")==0) {
			stringstream ss(buffer.substr(7,string::npos));
			ss >> conn[cn].stdtau;
			report("Depression Time Constant=%f\n", double(conn[cn].stdtau));
			continue;
		}

		if (buffer.compare(0,8, "stfalfa=")==0) {
			conn[cn].stfcode = char(1);
			report("Facilitation ON\n");
			stringstream ss(buffer.substr(8,string::npos));
			ss >> conn[cn].stfalfa;
			report("Facilitation Strength=%f\n", double(conn[cn].stfalfa));
			continue;
		}

		if (buffer.compare(0,7,"stftau=")==0) {
			stringstream ss(buffer.substr(7,string::npos));
			ss >> conn[cn].stftau;
			report("Facilitation Time Constant=%f\n", double(conn[cn].stftau));
			continue;
		}
		
	}
	return LOAD_NETWORK_OK;	
}

long Population::calculateMemory(){
	long res = 0;

	res += sizeof(Population) + Label.capacity();
	res += sizeof(Connection)*conn.size();
	for (int i = 0; i<Nreceptors;i++)
		res += receptor[i].receptorLabel.capacity();
	res += sizeof(Connection)*conn.size();
	for (int i = 0; i<Ncells;i++)
		res += Cell[i].calculateMemory();

	return res;
}

void Population::saveTracesV(ostream &tracesFile, const int numberOfTraces){
	for (int j = 0 ; j < numberOfTraces;j++){
		tracesFile << "\t" << Cell[j].V;
	}
}
