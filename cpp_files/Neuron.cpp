#include "Neuron.h"

Neuron::Neuron()
{
	int i;

	V = 0;
	RefrState = 0; // Refractory state counter

	TimeLastSpike = -10000; // time of the last emitted spike (for NMDA saturation)
	PTimeLastSpike = -10000;
	
	CA = 0; //concentracion de calcio

	for (i=0;i<MAX_RECEPTORS;i++){
		LS[i] = 0;
		ExtS[i] = 0;
		ExtMuS[i] = 0;
		ExtSigmaS[i] = 0;
		FreqExt[i] = 0;
	}

	this->Naxonals = 0;
}

Neuron::~Neuron()
{
	if (Naxonals>0){
		for (long i = 0; i<Naxonals;i++)
			delete Axonals[i];

		delete[] Axonals;
	}
}

int Neuron::loadAxonals(const short connId[], const short tNeuron[], const float tEfficacyMod[], const char stpcode[], const char stfcode[],const char stdcode[], const float initLastCond[]){
	long j;

	Axonals = new SynapsePtr[Naxonals];

	for (j=0; j<Naxonals; j++) {
		if (stpcode[j]==char(0) && stfcode[j]==char(0) && stdcode[j]==char(0) && initLastCond[j]==-1.0){
			Axonals[j] = new SynapseBase();
		}
		
		
		
		if (stpcode[j]==char(0) && stfcode[j]==char(1) && stdcode[j]==char(0) && initLastCond[j]==-1.0){
			Axonals[j] = new Synapse_STF();
		}
		if (stpcode[j]==char(0) && stfcode[j]==char(0) && stdcode[j]==char(1) && initLastCond[j]==-1.0){
			Axonals[j] = new Synapse_STD();
		}
		if (stpcode[j]==char(0) && stfcode[j]==char(1) && stdcode[j]==char(1) && initLastCond[j]==-1.0){
			Axonals[j] = new Synapse_STD_STF();
		}

        if (stpcode[j]==char(1) && initLastCond[j]==-1.0){
			Axonals[j] = new Synapse_STP(); //Ojo, por ahora solo implementado para canales no NMDA
		}


		if (stfcode[j]==char(0) && stdcode[j]==char(0) && initLastCond[j]!=-1.0){
			Axonals[j] = new SynapseNMDA(initLastCond[j]);
		}
		if (stfcode[j]==char(1) && stdcode[j]==char(0) && initLastCond[j]!=-1.0){
			Axonals[j] = new SynapseNMDA_STF(initLastCond[j]);
		}
		if (stfcode[j]==char(0) && stdcode[j]==char(1) && initLastCond[j]!=-1.0){
			Axonals[j] = new SynapseNMDA_STD(initLastCond[j]);
		}
		if (stfcode[j]==char(1) && stdcode[j]==char(1) && initLastCond[j]!=-1.0){
			Axonals[j] = new SynapseNMDA_STD_STF(initLastCond[j]);
		}



/*		if (stfcode[j]==char(1))
			Axonals[j].STF=(float)0.0;
		else
			Axonals[j].STF=(float)1.0; //dynamic variable of facilitation
*/
		Axonals[j]->connectionId = connId[j];
		Axonals[j]->TargetNeuron = tNeuron[j];
		

		Axonals[j]->EfficacyMod = tEfficacyMod[j];
	
		//Axonals[j].STD=(float)1.0; //dynamic variable of depression
	
		//Axonals[j].LastConductance=initLastCond[j];
	}

	return 0;
}

void Neuron::resetAfterSpike(const float Time, const float ResetPot, const int refrState){
	this->V=ResetPot;
	this->PTimeLastSpike=this->TimeLastSpike;
	this->TimeLastSpike=Time;

	this->V=0.; // spike! (temporary)

	this->RefrState=refrState;
	// this->RefrState=int(this->RefPeriod/dt);
}

long Neuron::calculateMemory(){
	long res = 0;
	
	res += sizeof(Neuron)+sizeof(Synapse *)*Naxonals;
	for(int i=0;i<Naxonals;i++){
		res += Axonals[i]->calculateMemory();
	}

	return res;
}

