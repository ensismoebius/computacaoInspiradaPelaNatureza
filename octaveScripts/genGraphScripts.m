# Use the gnu plot graphics toolkit because it is more powerfull
graphics_toolkit gnuplot;

# Loads the data stating by row 0 and column 0 (0,0)
# then loads 2147483646 rows (this is the maximum) and 
# ends at column 0
data = dlmread ('/tmp/geneticExperiments::Experiment04.csv','\t',[0,0,2147483646,1]);

# Get worst fitness (this will be the upper limit of graph)
worstFitness = max(data);
worstFitness = worstFitness(2);

# Get best fitness (this will be the lower limit of graph)
bestFitness = min(data);
bestFitness = bestFitness(2);

# Plot the graph using logaritm scale
loglog(data);

# Sets the graph size to previous defined limits (Optional)
axis([1,size(data,1),bestFitness,worstFitness]);


