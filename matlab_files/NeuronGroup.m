function p = NeuronGroup(p,name,N,cellParams)
%function p = NeuronGroup(p,name,N,cellParams)
    siz=length(p)+1;
    p(siz).name=name;
    p(siz).N=N;
    p(siz).cellParams=cellParams;
end
    
    