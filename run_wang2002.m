
%%
clear
addpath('matlab_files/')

%% Auxiliares
gE = struct('AMPAext',2.1,'AMPA',0.05,'NMDA',0.165,'GABA',1.3);
gI = struct('AMPAext',1.62,'AMPA',0.04, 'NMDA', 0.13, 'GABA', 1.0);

%% Poblaciones
% Membrane and cell properties
cellParsE = Cell(1,0.5,20,-70,-55,-50,2);
cellParsI = Cell(2,0.2,10,-70,-55,-50,1);

Nt = 2000;
w1=1.7;  f=0.15;  w2=1-f*(w1-1)/(1-f);
N = [f*0.8*Nt,f*0.8*Nt,0.8*(1-2*f)*Nt,0.2*Nt];

% init
p = [];

% define neuronal groups
p = NeuronGroup(p,'selective1',N(1),cellParsE);
p = NeuronGroup(p,'selective2',N(2),cellParsE);
p = NeuronGroup(p,'non_selective',N(3),cellParsE);
p = NeuronGroup(p,'inhibitory',N(4),cellParsI);

% set external inputs ('noise')
p = ExternalConnection(p,1,'AMPA',2,0,gE.AMPAext,3,800);
p = ExternalConnection(p,2,'AMPA',2,0,gE.AMPAext,3,800);
p = ExternalConnection(p,3,'AMPA',2,0,gE.AMPAext,3,800);
p = ExternalConnection(p,4,'AMPA',2,0,gI.AMPAext,3,800);

% set connections
w_exc = [w1,w2,1,0;w2,w1,1,0;w2,w2,1,0;0,0,0,0];
for i=1:3 % exc populations
    for j=1:3
        p = ConnectFull(p,i,j,'AMPA',w_exc(i,j) * gE.AMPA);
        p = ConnectFull(p,i,j,'NMDA',w_exc(i,j) * gE.NMDA);
    end
end
for i=1:3
    % to inhibitory
    p = ConnectFull(p,i,4,'AMPA',gI.AMPA);
    p = ConnectFull(p,i,4,'NMDA',gI.NMDA);
    
    % from inhibitory
    p = ConnectFull(p,4,i,'GABA',gE.GABA);
end
p = ConnectFull(p,4,4,'GABA',gI.GABA);


%% Conf file
a = fopen('network.conf', 'wt');
configNet(a,p);
fclose(a);

%% Writes Protocol file (external events)

EndTime = 3000;

ev = [];

coh = 6.4;

% %estimulo
evnt.type='ChangeExtFreq';
evnt.time=1000;
evnt.label='Stimulus Onset';
evnt.popu=1;
evnt.recept='AMPA';
evnt.freq =3 + 0.05 + 0.05/100*coh;
if exist('ev','var') && not(isempty(ev)); ev(length(ev)+1)=evnt; else ev=evnt; end

evnt.type='ChangeExtFreq';
evnt.time=1000;
evnt.label='Stimulus Onset';
evnt.popu=2;
evnt.recept='AMPA';
evnt.freq =3 + 0.05 - 0.05/100*coh;
if exist('ev','var') && not(isempty(ev)); ev(length(ev)+1)=evnt; else ev=evnt; end

evnt.type='ChangeExtFreq';
evnt.time=2000;
evnt.label='Stimulus Onset';
evnt.popu=1;
evnt.recept='AMPA';
evnt.freq=3;
if exist('ev','var') && not(isempty(ev)); ev(length(ev)+1)=evnt; else ev=evnt; end

evnt.type='ChangeExtFreq';
evnt.time=2000;
evnt.label='Stimulus Onset';
evnt.popu=2;
evnt.recept='AMPA';
evnt.freq=3;
if exist('ev','var') && not(isempty(ev)); ev(length(ev)+1)=evnt; else ev=evnt; end


%write file
a = fopen('network.pro', 'wt');

config_protocol(a,p,ev,EndTime);

fclose(a);


%% run
!./az.out -T1 -t1

%% plot
p = load('popfreqs0.dat');
figure()
plot(p(:,1),p(:,2:end))
xlabel('Time (ms)')
ylabel('Firing Rate (Hz)')
set(gca,'box','off')





