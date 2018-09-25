#include "Event.h"

Event::Event(void){}

Event::~Event(void){}

void Event::handleEvent(Network& net){
	int p,r,i,j,neuron;
	float std,distanceMod;
	float neuronpos,targetpos,normDist;

	//event-type that changes the external input to the whole population
	if(this->Type==CHANGE_EXT_FREQ) {
		p=this->PopNumber;
		r=this->ReceptorNumber;

		for (i=0;i<net.Pop[p].Ncells;i++)
		{
			net.Pop[p].Cell[i].FreqExt[r] = this->FreqExt;
			net.Pop[p].Cell[i].ExtMuS[r] = net.Pop[p].Cell[i].FreqExt[r] * 
									float(.001) * net.Pop[p].receptor[r].MeanExtEff * 
									net.Pop[p].receptor[r].MeanExtCon * net.Pop[p].receptor[r].Tau;

			net.Pop[p].Cell[i].ExtSigmaS[r] = sqrt(net.Pop[p].receptor[r].Tau * 
									float(.5) * net.Pop[p].Cell[i].FreqExt[r] * 
									float(.001) * net.Pop[p].receptor[r].MeanExtEff * 
									net.Pop[p].receptor[r].MeanExtEff * net.Pop[p].receptor[r].MeanExtCon);
		}
	}
	

	if(this->Type==CHANGE_EXT_FREQ_INSIDE) {
		p=this->PopNumber;
		r=this->ReceptorNumber;

		for (j=0;j<this->ETargetCells.size();j++){
			i=this->ETargetCells[j];
			net.Pop[p].Cell[i].FreqExt[r] = this->FreqExt;
			net.Pop[p].Cell[i].ExtMuS[r] = net.Pop[p].Cell[i].FreqExt[r] * 
									float(.001) * net.Pop[p].receptor[r].MeanExtEff * 
									net.Pop[p].receptor[r].MeanExtCon * net.Pop[p].receptor[r].Tau;

			net.Pop[p].Cell[i].ExtSigmaS[r] = sqrt(net.Pop[p].receptor[r].Tau * 
									float(.5) * net.Pop[p].Cell[i].FreqExt[r] * 
									float(.001) * net.Pop[p].receptor[r].MeanExtEff * 
									net.Pop[p].receptor[r].MeanExtEff * net.Pop[p].receptor[r].MeanExtCon);
		}
	}
	
	if(this->Type==CHANGE_EXT_FREQ_GAUSS_DELTA) {
		p=this->PopNumber;
		r=this->ReceptorNumber;
		std=this->StdDevExt;
		neuron=this->ETargetCells[0];//there should be only one element en ETargetCells
		neuronpos = (float) neuron/net.Pop[p].Ncells;
		
		for (i=0;i<net.Pop[p].Ncells;i++)
		{
			targetpos = (float) i/net.Pop[p].Ncells;
			normDist = min((float)abs(targetpos-neuronpos),(float)1.0-abs(targetpos-neuronpos));
			distanceMod = exp((float) -1.0*(normDist*normDist)/(std*std));
			
			//carefull! This event does not erases the previous FreqExt but increases it by the indicated amount !
			net.Pop[p].Cell[i].FreqExt[r] += this->FreqExt * distanceMod;
			
			net.Pop[p].Cell[i].ExtMuS[r] = net.Pop[p].Cell[i].FreqExt[r] * 
									float(.001) * net.Pop[p].receptor[r].MeanExtEff * 
									net.Pop[p].receptor[r].MeanExtCon * net.Pop[p].receptor[r].Tau;

			net.Pop[p].Cell[i].ExtSigmaS[r] = sqrt(net.Pop[p].receptor[r].Tau * 
									float(.5) * net.Pop[p].Cell[i].FreqExt[r] * 
									float(.001) * net.Pop[p].receptor[r].MeanExtEff * 
									net.Pop[p].receptor[r].MeanExtEff * net.Pop[p].receptor[r].MeanExtCon);
		}

	}


	

	if(this->Type==CHANGE_DUMMY_OUTPUT) {
		p=this->PopNumber;
		net.Pop[p].DummyOutputRate=this->DummyOutput;
		//printf("%7.1f ------------------ Event: %s ----------------\n",Time,Events[CEvent].Label);
		//printf("------------------ Event: %s ----------------\n",this->Label.c_str());
	}

	if(this->Type==EVENT_2) {
		float FreqE;
		p=this->PopNumber;
		r=this->ReceptorNumber;
		
		for (i=0;i<net.Pop[p].Ncells;i++)
		{
			FreqE = net.Pop[p].Cell[i].FreqExt[r] + this->FreqExt;

			net.Pop[p].Cell[i].ExtMuS[r] = FreqE * float(.001) * net.Pop[p].receptor[r].MeanExtEff * 
									net.Pop[p].receptor[r].MeanExtCon * net.Pop[p].receptor[r].Tau;

			net.Pop[p].Cell[i].ExtSigmaS[r] = sqrt(net.Pop[p].receptor[r].Tau * float(.5) * FreqE * float(.001)
										* net.Pop[p].receptor[r].MeanExtEff *
										net.Pop[p].receptor[r].MeanExtEff * net.Pop[p].receptor[r].MeanExtCon);
		}


	}

}
