data = dlmread ('/tmp/geneticExperiments::Experiment04.csv','\t',[0,1,2147483646,1]);
data(~any(~isnan(data), 2),:)=[];
meanResult = mean(data);
deviResult = std(data);
meanResult
deviResult
# Subtracts 
# data2 = arrayfun(@(x) x-5, data);
# data2 = arrayfun(@(x) (2^(-2*((x-0.1)/0.9)^2))*(sin(5*pi*x))^6, data);
# Removes any nan values