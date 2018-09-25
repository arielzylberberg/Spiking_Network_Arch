function [] = config_protocol(a,p,ev,endtime)

if ~isempty(ev)
    times = [ev.time];
    [b,ord]=sort(times);
    ev=ev(ord);
    
    for i=1:length(ev)
        for j=1:length(ev(i).popu)
            fprintf(a,'EventTime %d\n',ev(i).time);
            fprintf(a,'\n');
            fprintf(a,'Type=%s\n',ev(i).type);
            fprintf(a,'Label=%s\n',ev(i).label);
            
            if isnumeric(ev(i).popu)
                fprintf(a,'Population: %s\n', p(ev(i).popu(j)).name);
            else
                fprintf(a,'Population: %s\n', ev(i).popu(j));
            end
            
            fprintf(a,'Receptor:%s\n',ev(i).recept);
            fprintf(a,'FreqExt=%2.3f\n',ev(i).freq);
            
            if strcmp(ev(i).type,'ChangeExtFreqGauss')
                if isempty(ev(i).stdev)
                    disp('Carefull, empty standard deviation for a Gaussian input')
                else
                    fprintf(a,'StdDevExt=%2.3f\n',ev(i).stdev);
                end
            end
            
            if strcmp(ev(i).type,'ChangeExtFreqInside') || strcmp(ev(i).type,'ChangeExtFreqGauss')
                if isempty(ev(i).targetCells)
                    disp('Carefull, empty targetCells for ChangeExtFreqInside')
                    return
                else
                    ss=num2str(ev(i).targetCells(1));
                    for j=2:length(ev(i).targetCells)
                        ss=[ss ',' num2str(ev(i).targetCells(j))];
                    end
                    fprintf(a,'CellNumbers:%s\n',ss);
                end
            end
            
            fprintf(a,'\n');
            fprintf(a,'EndEvent\n');
            fprintf(a,'\n');
            fprintf(a,'%% -----------------\n');
            fprintf(a,'\n');
        end
    end
end

%endTrial
fprintf(a,'EventTime %d\n',endtime);
fprintf(a,'\n');
fprintf(a,'Type=EndTrial\n');
fprintf(a,'Label=End of Trial\n');
fprintf(a,'\n');
fprintf(a,'EndEvent\n');

