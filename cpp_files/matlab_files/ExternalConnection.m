function p = ExternalConnection(p,popid,recept,tau,revPot,extEff,extFreq,nConn)
%function p = ExternalConnection(p,popid,recept,tau,revPot,extEff,extFreq,nConn)

    if (isnumeric(popid))
        popnum=popid;
    end
    
    if not(isfield(p(popnum),'ExtConn'))
       p(popnum).ExtConn=[];
    end
    
    len=length(p(popnum).ExtConn);
    
    p(popnum).ExtConn(len+1).recept=recept;
    p(popnum).ExtConn(len+1).tau=tau;
    p(popnum).ExtConn(len+1).revPot=revPot;
    p(popnum).ExtConn(len+1).Eff=extEff;
    p(popnum).ExtConn(len+1).Freq=extFreq;
    p(popnum).ExtConn(len+1).nConn=nConn;
    
    
end
