function p = StdpConn(p,fromid,toid,recept)
%function p = StdpConn(p,from,to,recept)

    if isnumeric(fromid)
        from=fromid;
    end
    if isnumeric(toid)
        to=toid;
    end
    
    for i=1:length(p(from).connection)
        if (p(from).connection(i).con==to && strcmp(p(fromid).connection(i).recept,recept))
            p(from).connection(i).stdpCode=1;
        end
    end
    
end
            
    




