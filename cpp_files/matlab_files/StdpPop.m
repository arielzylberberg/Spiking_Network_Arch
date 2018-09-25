function p = StdpPop(p,popid,stdpAplus,stdpAmin,stdpTau,stdpGmax)
%function p = StdpPop(p,popid,stdpAplus,stdpAmin,stdpTau,stdpGmax)

    if (isnumeric(popid))
        popnum=popid;
    end
    
    p(popnum).stdp.Aplus=stdpAplus;
    p(popnum).stdp.Amin=stdpAmin;
    p(popnum).stdp.Tau=stdpTau;
    p(popnum).stdp.Gmax=stdpGmax;
    
end
