function p = SpikeFreqAdapt(p,popid,CAinit,jumpCA,tca,gAHP,Vk)
%function p = SpikeFreqAdapt(p,popid,CAinit,jumpCA,tca,gAHP,Vk)
%popid: population that adapts, number or name
%CAinit: initial concentration, in microMol
%jumpCA: jump for every spike, in microMol
%tca: time constant of recovery of [CA2+]
%gAHP: conductance in nS
%Vk: K reversal potential in mV

    if (isnumeric(popid))
        popnum=popid;
    end

    p(popnum).SFA.SFACode=1;
    p(popnum).SFA.CA=CAinit;
    p(popnum).SFA.dCA=jumpCA;
    p(popnum).SFA.tca=tca;
    p(popnum).SFA.gAHP=gAHP;
    p(popnum).SFA.Vk=Vk;

end



