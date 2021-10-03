cmake_minimum_required(VERSION 3.5)
project(cin2019
        VERSION 1.0
        DESCRIPTION "Nature Inspired Computation"
        LANGUAGES CXX)  

set(CMAKE_VERBOSE_MAKEFILE OFF)

###############################################
###############################################
### Executable and libraries configuration  ###
###############################################
###############################################

# Executables and its objects
add_executable(cin2019
src/main.cpp

src/acoExperiments/Experiment01.cpp

src/geneticExperiments/Experiment01.cpp
src/geneticExperiments/Experiment02.cpp
src/geneticExperiments/Experiment03.cpp
src/geneticExperiments/Experiment04.cpp
src/geneticExperiments/GeneticExperience.cpp

src/hillClimbingAnnealingExperiments/Experiment01.cpp
src/hillClimbingAnnealingExperiments/Experiment02.cpp
src/hillClimbingAnnealingExperiments/Experiment03.cpp
src/hillClimbingAnnealingExperiments/Experiment04.cpp
src/hillClimbingAnnealingExperiments/Experiment05.cpp


src/lib/ACOAnt.cpp
src/lib/ACOMap.cpp
src/lib/ACOPoint.cpp
src/lib/annealing.cpp
src/lib/fileWriter.cpp
src/lib/gaussianRandom.cpp
src/lib/Gen.cpp
src/lib/geometry.cpp
src/lib/hillClimbing.cpp
src/lib/NeuralNetwork.cpp
src/lib/Neuron.cpp
src/lib/PSO.cpp
src/lib/PSOLimits.cpp
src/lib/PSONeighborhood.cpp
src/lib/PSOParticle.cpp
src/lib/SquareMatrix.cpp
src/lib/stochasticProbability.cpp
src/lib/variables.cpp

src/neuralExperiments/Experiment01.cpp
src/neuralExperiments/Experiment02.cpp
src/neuralExperiments/Experiment03.cpp
src/neuralExperiments/Experiment04.cpp
src/neuralExperiments/Experiment05.cpp
src/neuralExperiments/Experiment06.cpp
src/neuralExperiments/Experiment07.cpp
src/neuralExperiments/Experiment08.cpp

src/psoExperiments/Experiment01.cpp
)

# User libraries
target_include_directories(cin2019 
	PUBLIC src/lib
)

# System libraries (python)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(cin2019 ${PYTHON_LIBRARIES})

# C++ version
target_compile_features(cin2019 PRIVATE cxx_std_20)
