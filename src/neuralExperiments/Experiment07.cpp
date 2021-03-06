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

#ifndef SRC_NEURALEXPERIMENTS_EXPERIMENt07_H_
#define SRC_NEURALEXPERIMENTS_EXPERIMENt07_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "../lib/fileWriter.h"
#include "../lib/NeuralNetwork.cpp"

namespace neuralExperiments {
	class Experiment07 {
		public:

			static void perform() {

				openFile("/tmp/neuralExperiments_Experiment07_errors.csv");

				std::string line;
				std::cout << std::fixed;
				std::cout << std::setprecision(6);

				float bias = 1;
				float learningRate = 0.9;
				unsigned int maxIt = 1000000;
				unsigned int inputSize = 13;
				unsigned int outputSize = 3;
				unsigned int innerLayerSize = 7;
				unsigned int amountOfInnerLayers = 0;

				float** arrInput = new float*[123];
				float** arrDesiredOutput = new float*[123];

				NeuralNetwork* n = new NeuralNetwork(inputSize, outputSize, amountOfInnerLayers, innerLayerSize, bias, learningRate);

				// Training network
				std::cout << "Reading training file... \n";
				std::ifstream infileTraining("/home/ensis/workspaces/c-workspace/CIN2019/dataSets/wineDataSet/wineTraining.data");
				unsigned int fileItemNumber = 0;
				while (readFile(infileTraining, line, arrInput, arrDesiredOutput, fileItemNumber, outputSize, inputSize)) {
					fileItemNumber++;
				}
				infileTraining.close();

				writeCharsToFile("Training errors\n");

				std::cout << "Training... \n";
				for (unsigned int i = 0; i < maxIt; i++) {

					double totalError = 0;

					for (unsigned int j = 0; j < fileItemNumber; j++) {
						n->pushDesiredResults(arrDesiredOutput[j]);
						n->pushInputs(arrInput[j]);
						n->iterate(1);

						// write all errors to file
						for (unsigned int k = 0; k < outputSize; k++) {
							totalError += pow(n->arrErrorValues[k], 2) / 2;
						}
					}

					writeNumberToFile(totalError);
				}

				closeFile();

				openFile("/tmp/neuralExperiments_Experiment07_results.csv");

				// Validating network
				writeCharsToFile("Validating results\n");

				std::cout << "Reading validating file... \n";
				std::ifstream infileValidating("/home/ensis/workspaces/c-workspace/CIN2019/dataSets/wineDataSet/wineValidating.data");
				fileItemNumber = 0;
				while (readFile(infileValidating, line, arrInput, arrDesiredOutput, fileItemNumber, outputSize, inputSize)) {
					fileItemNumber++;
				}
				infileValidating.close();

				// Validating
				std::cout << "Validating... \n";
				for (unsigned int j = 0; j < fileItemNumber; j++) {
					n->pushInputs(arrInput[j]);
					n->iterate();
					compareResults(arrDesiredOutput[j], n->getOutputLayer(), outputSize);
				}

				// Testing network
				writeCharsToFile("Testing results\n");

				std::cout << "Reading testing file... \n";
				std::ifstream infileTesting("/home/ensis/workspaces/c-workspace/CIN2019/dataSets/wineDataSet/wineTest.data");
				fileItemNumber = 0;
				while (readFile(infileTesting, line, arrInput, arrDesiredOutput, fileItemNumber, outputSize, inputSize)) {
					fileItemNumber++;
				}
				infileTesting.close();

				// Validating
				std::cout << "Testing... \n";
				for (unsigned int j = 0; j < fileItemNumber; j++) {
					n->pushInputs(arrInput[j]);
					n->iterate();
					compareResults(arrDesiredOutput[j], n->getOutputLayer(), outputSize);
				}

				delete n;
				delete[] arrInput;
				delete[] arrDesiredOutput;

				infileTraining.close();
				closeFile();
			}

		private:

			static const char* getDataName(float* arrData) {
				if (arrData[0] == 1 && arrData[1] == 0 && arrData[2] == 0) {
					return "1";
				}
				if (arrData[0] == 0 && arrData[1] == 1 && arrData[2] == 0) {
					return "2";
				}
				if (arrData[0] == 0 && arrData[1] == 0 && arrData[2] == 1) {
					return "3";
				}
				return "";
			}

			static char readFile(std::ifstream& infile, std::string& line, float**& arrInputs, float**& arrDesiredOutput, unsigned int pos, unsigned int outputSize, unsigned int inputSize) {

				if (std::getline(infile, line)) {
					std::istringstream iss(line);
					float v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13;
					char comma;
					float label;
					if (!(iss >> label >> comma >> v1 >> comma >> v2 >> comma >> v3 >> comma >> v4 >> comma >> v5 >> comma >> v6 >> comma >> v7 >> comma >> v8 >> comma >> v9 >> comma >> v10 >> comma >> v11 >> comma >> v12 >> comma >> v13)) {
						return 0;
					}

					arrInputs[pos] = new float[inputSize];
					arrDesiredOutput[pos] = new float[outputSize];

					arrInputs[pos][0] = v1;
					arrInputs[pos][1] = v2;
					arrInputs[pos][2] = v3;
					arrInputs[pos][3] = v4;
					arrInputs[pos][4] = v5;
					arrInputs[pos][5] = v6;
					arrInputs[pos][6] = v7;
					arrInputs[pos][7] = v8;
					arrInputs[pos][8] = v9;
					arrInputs[pos][9] = v10;
					arrInputs[pos][10] = v11;
					arrInputs[pos][11] = v12;
					arrInputs[pos][12] = v13;

					// normalizing the data
					double sum = 0;
					for (int i = 0; i < 13; i++) {
						sum += arrInputs[pos][i];
					}
					for (int i = 0; i < 13; i++) {
						arrInputs[pos][i] /= sum;
					}

					if (label == 1) {
						arrDesiredOutput[pos][0] = 1;
						arrDesiredOutput[pos][1] = 0;
						arrDesiredOutput[pos][2] = 0;
						return 1;
					}
					if (label == 2) {
						arrDesiredOutput[pos][0] = 0;
						arrDesiredOutput[pos][1] = 1;
						arrDesiredOutput[pos][2] = 0;
						return 1;
					}
					if (label == 3) {
						arrDesiredOutput[pos][0] = 0;
						arrDesiredOutput[pos][1] = 0;
						arrDesiredOutput[pos][2] = 1;
						return 1;
					}

					return 0;
				}
				return 0;
			}

			static char compareResults(float* arrDesiredOutput, Neuron** networkOutput, unsigned int outputSize) {

				float maxValue = -2;
				float* arrActual = new float[outputSize];

				for (unsigned int i = 0; i < outputSize; i++) {
					if (maxValue < networkOutput[i]->value) {
						maxValue = networkOutput[i]->value;
					}
				}

				for (unsigned int i = 0; i < outputSize; i++) {
					if (networkOutput[i]->value < maxValue) {
						arrActual[i] = 0;
					} else {
						arrActual[i] = 1;
					}
				}

				// target
				writeCharsToFile(getDataName(arrDesiredOutput));
				writeCharsToFile("\t");
				std::cout << getDataName(arrDesiredOutput) << "\t";

				// result
				writeCharsToFile(getDataName(arrActual));
				writeCharsToFile("\t");
				std::cout << getDataName(arrActual) << "\t";

				for (unsigned int i = 0; i < outputSize; i++) {
					if (arrDesiredOutput[i] != arrActual[i]) {
						writeCharsToFile("Fail\n");
						std::cout << "Fail!!!\n";
						return false;
					}
				}
				writeCharsToFile("Success\n");
				std::cout << "Success!!!\n";
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

#endif /* SRC_NEURALEXPERIMENTS_EXPERIMENt07_H_ */
