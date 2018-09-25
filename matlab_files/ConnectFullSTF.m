function p = ConnectFullSTF(p,fromid,toid,recept,eff,stfalfa,stftau)
%p = ConnectFullSTF(p,from,to,recept,eff,stfalfa,stftau)

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

for i=1:length(from)
   if not(isfield(p(from(i)),'connection'))
       p(from(i)).connection=[];
   end
   len=length(p(from(i)).connection);
   p(from(i)).connection(len+1).con=to(i);
   p(from(i)).connection(len+1).conntype=1;
   p(from(i)).connection(len+1).recept=recept;
   p(from(i)).connection(len+1).eff=eff(i);
   p(from(i)).connection(len+1).conProb=1;
   
   p(from(i)).connection(len+1).stf.alfa = stfalfa;
   p(from(i)).connection(len+1).stf.tau = stftau;
   
end


