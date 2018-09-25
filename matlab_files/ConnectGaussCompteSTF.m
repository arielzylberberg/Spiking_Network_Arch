function p = ConnectGaussCompteSTF(p,fromid,toid,recept,eff,conProb,plus,minus,sigma,stfalfa,stftau)
%p = ConnectGaussCompteSTF(p,fromid,toid,recept,eff,conProb,plus,minus,sigma,stf_alta,stf_tau)

if isnumeric(fromid)
    from=fromid;
end
if isnumeric(toid)
    to=toid;
end

if length(from)~=length(to) && length(from)>1 && length(to)>1
    display('Error en el tama�o de las conexiones')
elseif length(from)~=length(to)
    if length(from)<length(to)
        from=repmat(from,1,size(to,2));
    else
        to=repmat(to,1,size(from,2));
    end
end

if length(eff)<length(to)
    eff=repmat(eff,1,size(to,2));
end

if length(plus)<length(to)
    plus=repmat(plus,1,length(to));
end

if length(minus)<length(to)
    minus=repmat(minus,1,length(to));
end

if length(sigma)<length(to)
    sigma=repmat(sigma,1,length(to));
end

if length(conProb)<length(conProb)
    conProb=repmat(conProb,1,length(to));
end

if not(iscell(recept))
    recept={recept};
end
if length(recept)<length(to)
    recept=repmat(recept,1,length(to));
end

for i=1:length(from)
   if not(isfield(p(from(i)),'connection'))
       p(from(i)).connection=[];
   end
   len=length(p(from(i)).connection);
   p(from(i)).connection(len+1).con=to(i);
   p(from(i)).connection(len+1).conntype=2;
   p(from(i)).connection(len+1).recept=recept{i};
   p(from(i)).connection(len+1).eff=eff(i);
   p(from(i)).connection(len+1).conProb=conProb(i);
   p(from(i)).connection(len+1).plus=plus(i);
   p(from(i)).connection(len+1).minus=minus(i);
   p(from(i)).connection(len+1).sigma=sigma(i);
   
   p(from(i)).connection(len+1).stf.alfa = stfalfa;
   p(from(i)).connection(len+1).stf.tau = stftau;
end


