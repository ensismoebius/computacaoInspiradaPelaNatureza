data = dlmread ('/tmp/hillClimbingAnnealingExperiments::Experiment02.csv','\t',[0,0,2147483646,0]);
data(~any(~isnan(data), 2),:)=[];
meanResult = mean(data2);
deviResult = std(data2);
meanResult
deviResult

