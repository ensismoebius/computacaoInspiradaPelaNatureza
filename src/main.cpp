#include "lib/gaussianRandom.h"

/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 14 de mai de 2019
 *
 */

class Neuron {
	public:
		float value;

		float* arrWeights;
		unsigned int arrWeightsSize;

		float* arrInputs;
		unsigned int arrInputsSize;

		Neuron(float value) {
			this->value = value;

			this->arrWeights = 0;
			this->arrWeightsSize = 0;

			this->arrInputs = 0;
			this->arrInputsSize = 0;
		}

		Neuron(float value, float* arrWeights, unsigned int arrWeightsSize, float* arrInputs, unsigned int arrInputsSize) {
			this->value = value;

			this->arrWeights = arrWeights;
			this->arrWeightsSize = arrWeightsSize;

			this->arrInputs = arrInputs;
			this->arrInputsSize = arrInputsSize;
		}
};

class NeuralNetwork {
	public:
		NeuralNetwork(unsigned int inputSize, unsigned int innerLayersSize, unsigned int layersSize, unsigned int outputSize) {
			float* arrWeights = new float[inputSize];
			this->initializeWeights(arrWeights, inputSize);
		}

	private:
		void initializeWeights(float*& arrWeights, unsigned int arrWeightsSize) {
			while (arrWeightsSize--) {
				arrWeights[arrWeightsSize] = getGaussionRandomPertubation();
			}
		}
};

int main() {
	NeuralNetwork* n = new NeuralNetwork(100);
}

