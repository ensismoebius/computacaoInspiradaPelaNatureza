/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 15 de mai de 2019
 *
 *
 */

#ifndef SRC_NEURALEXPERIMENTS_EXPERIMENT01_H_
#define SRC_NEURALEXPERIMENTS_EXPERIMENT01_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include "../lib/NeuralNetwork.cpp"

namespace neuralExperiments {
	class Experiment01 {
		public:

			static void perform() {

				std::cout << "\n";

				std::string line;
				std::cout << std::fixed;
				std::cout << std::setprecision(6);

				float bias = 0.1;
				unsigned int maxIt = 10000;
				unsigned int inputSize = 4;
				unsigned int outputSize = 3;
				unsigned int innerLayerSize = 7;
				unsigned int amountOfInnerLayers = 1;

				float** arrInput = new float*[105];
				float** arrDesiredOutput = new float*[105];

				NeuralNetwork* n = new NeuralNetwork(inputSize, outputSize, amountOfInnerLayers, innerLayerSize, bias);

				// Training network
				std::cout << "Reading training file... \n";
//				std::ifstream infileTraining("/home/ensis/workspaces/c-workspace/CIN2019/dataSets/irisDataSet/irisSetosa.data");
				std::ifstream infileTraining("/home/ensis/workspaces/c-workspace/CIN2019/dataSets/irisDataSet/irisTraining.data");
				unsigned int fileItemNumber = 0;
				while (readFile(infileTraining, line, arrInput, arrDesiredOutput, fileItemNumber, outputSize)) {
					fileItemNumber++;
				}
				infileTraining.close();

				std::cout << "Training... \n";
				for (unsigned int i = 0; i < maxIt; i++) {
					for (unsigned int j = 0; j < fileItemNumber; j++) {
						n->pushDesiredResults(arrDesiredOutput[j]);
						n->pushInputs(arrInput[j]);
						n->iterate(1);
					}
				}

				// Validating network
				std::cout << "Reading validating file... \n";
				std::ifstream infileValidating("/home/ensis/workspaces/c-workspace/CIN2019/dataSets/irisDataSet/irisValidating.data");
//				std::ifstream infileValidating("/home/ensis/workspaces/c-workspace/CIN2019/dataSets/irisDataSet/irisSetosa.data");
				fileItemNumber = 0;
				while (readFile(infileValidating, line, arrInput, arrDesiredOutput, fileItemNumber, outputSize)) {
					fileItemNumber++;
				}
				infileValidating.close();

				// Validating
				std::cout << "Validating... \n";
				for (unsigned int j = 0; j < fileItemNumber; j++) {

					n->pushInputs(arrInput[j]);
					n->iterate();

					std::cout << "I want " << getDataName(arrDesiredOutput[j]) << ".";

					if (compareResults(arrDesiredOutput[j], n->getOutputLayer(), outputSize)) {
						std::cout << "Success!!!\n";
					} else {
						std::cout << "Fail!!!\n";
					}
				}

				// Is this smart? Lets see
				arrInput[0][0] = 5.0;
				arrInput[0][1] = 3.0;
				arrInput[0][2] = 1.6;
				arrInput[0][4] = 0.2;

				n->pushInputs(arrInput[0]);
				n->iterate();
				showResults(outputSize, n);

				delete n;
				delete[] arrInput;
				delete[] arrDesiredOutput;

				infileTraining.close();
			}

		private:

			static const char* getDataName(float* arrData) {
				if (arrData[0] == 1 && arrData[1] == 0 && arrData[2] == 0) {
					return "Iris-setosa";
				}
				if (arrData[0] == 0 && arrData[1] == 1 && arrData[2] == 0) {
					return "Iris-virginica";
				}
				if (arrData[0] == 0 && arrData[1] == 0 && arrData[2] == 1) {
					return "Iris-versicolor";
				}
			}

			static char readFile(std::ifstream& infile, std::string& line, float**& arrInputs, float**& arrDesiredOutput, unsigned int pos, unsigned int outputSize) {

				if (std::getline(infile, line)) {
					std::istringstream iss(line);
					float a, b, c, d;
					char comma;
					std::string name;
					if (!(iss >> a >> comma >> b >> comma >> c >> comma >> d >> comma >> name)) {
						return 0;
					}

					arrInputs[pos] = new float[outputSize];
					arrDesiredOutput[pos] = new float[outputSize];

					arrInputs[pos][0] = a;
					arrInputs[pos][1] = b;
					arrInputs[pos][2] = c;
					arrInputs[pos][3] = d;

					if (name.compare("Iris-setosa") == 0) {
						arrDesiredOutput[pos][0] = 1;
						arrDesiredOutput[pos][1] = 0;
						arrDesiredOutput[pos][2] = 0;
						return 1;
					}
					if (name.compare("Iris-virginica") == 0) {
						arrDesiredOutput[pos][0] = 0;
						arrDesiredOutput[pos][1] = 1;
						arrDesiredOutput[pos][2] = 0;
						return 1;
					}
					if (name.compare("Iris-versicolor") == 0) {
						arrDesiredOutput[pos][0] = 0;
						arrDesiredOutput[pos][1] = 0;
						arrDesiredOutput[pos][2] = 1;
						return 1;
					}

					return 0;
				}
				return 0;
			}

			static float translate(float value) {
				return value >= 0.5 ? 1 : 0;
			}

			static char compareResults(float* arrDesiredOutput, Neuron** output, unsigned int outputSize) {
				for (unsigned int i = 0; i < outputSize; i++) {
					if (arrDesiredOutput[i] != translate(output[i]->getValue())) {
						return false;
					}
				}
				return true;
			}

			static void showResults(unsigned int outputSize, NeuralNetwork*& n) {
				float* errors = n->getErrors();
				Neuron** out = n->getOutputLayer();

				std::cout << "Results: \n";

				for (unsigned int i = 0; i < outputSize; i++) {
					std::cout << out[i]->getValue() << " ";
				}

				std::cout << "\nErrors: \n";

				for (unsigned int i = 0; i < outputSize; i++) {
					std::cout << errors[i] << " ";
				}

				std::cout << "\n";
			}
	};
}

#endif /* SRC_NEURALEXPERIMENTS_EXPERIMENT01_H_ */
