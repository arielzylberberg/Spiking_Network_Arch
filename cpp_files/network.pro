EventTime 500

Type=ChangeExtFreqGauss
Label=Stimulus Onset
Population: exc11
Receptor:AMPA
FreqExt=1.100
StdDevExt=0.056
CellNumbers:220

EndEvent

% -----------------

EventTime 1000

Type=ChangeExtFreq
Label=Stimulus Onset
Population: exc11
Receptor:AMPA
FreqExt=1.700

EndEvent

% -----------------

EventTime 1000

Type=EndTrial
Label=End of Trial

EndEvent
