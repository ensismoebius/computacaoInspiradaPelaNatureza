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
#include "../lib/NeuralNetwork.cpp"

namespace neuralExperiments {
	class Experiment01 {
		public:
			static void perform() {
				unsigned int inputSize = 4;
				unsigned int outputSize = 3;
				unsigned int innerLayerSize = 2;
				unsigned int amountOfInnerLayers = 3;

				float arrDesiredOutput[] = { 0, 0, 0 };
				float arrInput[] = { 5.1, 3.5, 1.4, 0.2 };

				NeuralNetwork* n = new NeuralNetwork(inputSize, outputSize, amountOfInnerLayers, innerLayerSize);

				n->pushDesiredResults(arrDesiredOutput);
				n->pushInputs(arrInput);

				std::cout << std::fixed;
				std::cout << std::setprecision(6);

				for (int i = 0; i < 10000; i++) {
					n->iterate();

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
				delete n;
			}
	};
}

#endif /* SRC_NEURALEXPERIMENTS_EXPERIMENT01_H_ */
