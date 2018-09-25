function [] = configNet(a,p)

for i=1:length(p)
    NeuralPopulation(a,p(i).name);
    ty=p(i).cellParams.type;
    
    CellProps(a,p(i).N,p(i).cellParams.C,p(i).cellParams.tau,p(i).cellParams.restPot,p(i).cellParams.resetPot,p(i).cellParams.threshold,p(i).cellParams.refractPeriod);
    
    %if p(i).dummy(1)==1
    %    DummyPop(a,p(i).dummy);%not checked
    %end
    
    if isfield(p(i),'SFA') && ~isempty(p(i).SFA)
        sf=[p(i).SFA.SFACode p(i).SFA.CA p(i).SFA.dCA p(i).SFA.tca p(i).SFA.gAHP p(i).SFA.Vk];
        SpikeFreqAd(a,sf);
    end
    
    rece=[0 0 0];%AMPA, GABA, NMDA
    for j=1:length(p(i).ExtConn)
        Recept(a,p(i).ExtConn(j).recept, p(i).ExtConn(j).tau, p(i).ExtConn(j).revPot, ...
            p(i).ExtConn(j).Freq, p(i).ExtConn(j).Eff, p(i).ExtConn(j).nConn);
        if strcmp(p(i).ExtConn(j).recept,'AMPA'); rece(1)=1; end
        if strcmp(p(i).ExtConn(j).recept,'GABA'); rece(2)=1; end
        if strcmp(p(i).ExtConn(j).recept,'NMDA'); rece(3)=1; end
    end
    
    %Ext defaults
    if rece(2)==0
        Recept(a,'GABA', 5, -70, 0, 0, 0);
    end
    if rece(3)==0
        Recept(a,'NMDA', 100, 0, 0, 0, 0);
    end
    fprintf(a,'\n');
    
    if isfield(p(i),'stdp') && ~isempty(p(i).stdp)
        stdp(a,p(i).stdp);
    end
    

    
    if isfield(p(i),'connection')
        for j=1:length(p(i).connection)
            Connect(a,p,p(i).connection(j));
        end     
    end
    EndNeuralPopulation(a);
end

function[]=stdp(a,struc)
    
fprintf(a,'stdpAplus=%2.8f\n',struc.Aplus);
fprintf(a,'stdpAmin=%2.8f\n',struc.Amin);
fprintf(a,'stdpTau=%2.8f\n',struc.Tau);
fprintf(a,'stdpGmax=%2.8f\n',struc.Gmax);
    
    
function[]=CellProps(a,cellnumber,C,tau,restpot,resetpot,threshold,refract)

fprintf(a,'N=%5.0f%s\n',cellnumber,' % number of neurons');
fprintf(a,'C=%2.2f%s\n',C,' % capacitance (nF)');
fprintf(a,'Taum=%d%s\n',tau,' % membrane time constant');
fprintf(a,'RestPot=%d%s\n',restpot,' % Resting potential (mV)');
fprintf(a,'ResetPot=%d%s\n',resetpot,' % Reset potential (mV)');
fprintf(a,'Threshold=%d%s\n',threshold,' % Threshold for emitting a spike (mV)');
fprintf(a,'RefPeriod=%d%s\n',refract,' % refractory period');
fprintf(a,'\n');

function[] = Connect(a,p,s)

fprintf(a,'TargetPopulation:%s\n', p(s.con).name);
if isfield(s,'conProb') && not(isempty(s.conProb))
    fprintf(a,'Connectivity=%1.3f\n', s.conProb);
end
fprintf(a,'TargetReceptor=%s\n', s.recept);
fprintf(a,'ConnectivityCode=%5.0f\n', s.conntype);

if s.conntype > 1
    fprintf(a,'Jplus=%2.7f\n', s.plus);
    fprintf(a,'Jmin=%2.7f\n', s.minus);
    fprintf(a,'Sigma=%2.7f\n', s.sigma);
end

if isfield(s,'stdpCode') && not(isempty(s.stdpCode))
    fprintf(a,'stdpCode=%2.0f\n', s.stdpCode);
else
    fprintf(a,'stdpCode=%2.0f\n', 0);
end

fprintf(a,'MeanEff=%1.7f\n', s.eff);

if isfield(s,'stp_U') && not(isempty(s.stp_U))
    fprintf(a,'stp_U=%2.4f\n',s.stp_U);
    fprintf(a,'stp_tauf=%2.4f\n',s.stp_tauf);
    fprintf(a,'stp_taud=%2.4f\n',s.stp_taud);
end

if isfield(s,'stf') && not(isempty(s.stf))
    fprintf(a,'stfalfa=%2.4f\n',s.stf.alfa);
    fprintf(a,'stftau=%4.1f\n',s.stf.tau);
end
if isfield(s,'std') && not(isempty(s.std))
    fprintf(a,'stdalfa=%2.4f\n',s.std.alfa);
    fprintf(a,'stdtau=%4.1f\n',s.std.tau);
end

fprintf(a,'EndTargetPopulation\n');
fprintf(a,'\n');



function[]=DummyPop(a,dummy)
        
fprintf(a,'Dummy=%d%s\n',dummy(1),' % dummy population');
fprintf(a,'DummyOutputRate=%3.3f%s\n',dummy(2),' % dummy population ouput rate');
fprintf(a,'\n');

function[]=EndNeuralPopulation(a)
fprintf(a,'EndNeuralPopulation\n');
fprintf(a,'\n');

function [] = NeuralPopulation(a,name)
fprintf(a,'NeuralPopulation:%s\n',name);
fprintf(a,'%s\n','%--------------------------------------');
fprintf(a,'\n');

function [] = Recept(a,name,tau,revpot,freqExt,conductance,conNumber)

fprintf(a,'Receptor:%s\n', name);
fprintf(a,'Tau=%5.0f\n', tau);
fprintf(a,'RevPot=%d\n', revpot);
fprintf(a,'FreqExt=%3.5f\n',freqExt);
fprintf(a,'MeanExtEff=%3.4f\n', conductance);
fprintf(a,'MeanExtCon=%5.0f\n',conNumber);
fprintf(a,'EndReceptor\n');
fprintf(a,'\n');

function[]=SpikeFreqAd(a,sf)

fprintf(a,'SFACode=%d\n',sf(1));
fprintf(a,'CA=%2.6f\n', sf(2));
fprintf(a,'dCA=%2.6f\n', sf(3));
fprintf(a,'tca=%5.0f\n', sf(4));
fprintf(a,'gAHP=%2.4f\n', sf(5));
fprintf(a,'Vk=%d\n', sf(6));
fprintf(a,'\n');


    
    
