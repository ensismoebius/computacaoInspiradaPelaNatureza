# Use the gnu plot graphics toolkit because it is more powerfull
graphics_toolkit gnuplot;

# Loads the data stating by row 0 and column 0 (0,0)
# then loads 2147483646 rows (this is the maximum) and 
# ends at column 0
data = dlmread ('/tmp/hillClimbingAnnealingExperiments::Experiment04.csv','\t',[0,0,2147483646,0]);

# Get worst fitness (this will be the upper limit of graph)
worstFitness = max(data);

# Get best fitness (this will be the lower limit of graph)
bestFitness = min(data);

# Plot the graph using logaritm scale
loglog(data);
#plot(data); <- use this for stochastic Hill Climbing

# Sets the graph size to previous defined limits (Optional)
# axis([1,size(data,1),bestFitness,worstFitness]);



