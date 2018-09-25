
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

% number of neurons
N = [1,1000];

 
p = [];
p = NeuronGroup(p,'exc',N(1),cellParsE);
p = NeuronGroup(p,'inh',N(2),cellParsI);


p = ExternalConnection(p,1,'AMPA',2,0,gE.AMPAext,4,800);
p = ExternalConnection(p,2,'AMPA',2,0,gI.AMPAext,3,800);


% p = ConnectFull(p,1,1,'AMPA',gE.AMPA);
% p = ConnectFull(p,1,1,'NMDA',gE.NMDA);
p = ConnectFull(p,1,2,'AMPA',0);
p = ConnectFull(p,2,1,'GABA',gE.GABA);
p = ConnectFull(p,2,2,'GABA',gI.GABA);

%% Conf file
a = fopen('network.conf', 'wt');
configNet(a,p);
fclose(a);

%% Writes Protocol file
EndTime = 2000;

ev = [];

%write file
a = fopen('network.pro', 'wt');
config_protocol(a,p,ev,EndTime);
fclose(a);


%% run
!./az.out -T1 -t1

%% plot
p = load('popfreqs0.dat');
figure()
subplot(1,2,1);
plot(p(:,1),p(:,2:end))
xlabel('Time (ms)')
ylabel('Firing Rate (Hz)')
set(gca,'box','off')

subplot(1,2,2);
a = importdata('trial0_traces_V.dat');
plot(a.data(:,1),a.data(:,2))
hold all
plot(a.data(:,1),a.data(:,3))
xlabel('Time (ms)')
ylabel('Voltage (mV)');



