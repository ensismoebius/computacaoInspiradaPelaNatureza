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

#ifndef SRC_LIB_NEURON_CPP_
#define SRC_LIB_NEURON_CPP_

#include <cmath>
#include "gaussianRandom.h"

/**
 * Holds the data, weights, activation function
 * and calculates his values and errors.
 * This is the heart (or brain? XD) of the neural network
 */
class Neuron {
	private:
		/**
		 * Values must be between [1,-1]
		 */
		float value;

		float* arrWeights;
		unsigned int arrWeightsSize;

		Neuron** arrInputsNeurons;
		unsigned int arrInputsNeuronsSize;

	public:

		static const unsigned int CONST_INVALID_NEURON_VALUE = 2;

		/**
		 * When this is just an input neuron, it are not
		 * going to have any weights or activation functions
		 * because it will just provide to next layer
		 * @param value
		 */
		Neuron() {

			// Populate with an invalid value
			// the actual value pushed after
			this->value = CONST_INVALID_NEURON_VALUE;

			// points all weights and inputs to null
			this->arrWeights = 0;
			this->arrWeightsSize = 0;
			this->arrInputsNeurons = 0;
			this->arrInputsNeuronsSize = 0;
		}

		Neuron(unsigned int arrWeightsSize, Neuron** arrInputsNeurons, unsigned int arrInputNeuronsSize) {

			// Populate with an invalid value
			// the actual value will be calculated
			// after
			this->value = CONST_INVALID_NEURON_VALUE;

			// build random weights
			this->arrWeightsSize = arrWeightsSize;
			this->arrWeights = new float[arrWeightsSize];
			this->initializeWeights(this->arrWeights, arrWeightsSize);

			// connects to input neurons
			this->arrInputsNeurons = arrInputsNeurons;
			this->arrInputsNeuronsSize = arrInputNeuronsSize;
		}

		~Neuron() {
			delete[] this->arrWeights;
		}

		void setValue(float value) {
			this->value = value;
		}

		float getValue() {
			return this->value;
		}

		float generateOutput() {

			// this is just an input neuron
			if (this->arrWeightsSize == 0) {
				return this->value;
			}

			// this is a regular neuron, you
			// MUST calculate the output
			double sum = this->calculateNeuronSum();
			this->value = (float) this->activationFunction(sum);
			return value;
		}

		void rectifyWeights(float alpha, float error) {
			for (unsigned int i = 0; i < this->arrWeightsSize; i++) {
				this->arrWeights[i] += this->arrInputsNeurons[i]->getValue() * alpha * error;
				this->arrInputsNeurons[i]->rectifyWeights(alpha, error);
			}
			//for (unsigned int i = 0; i < this->arrInputsNeuronsSize; i++) {
			//}
		}

	private:

		void initializeWeights(float*& arrWeights, unsigned int arrWeightsSize) {
			while (arrWeightsSize--) {
				arrWeights[arrWeightsSize] = getGaussionRandomPertubation();
			}
		}

		double activationFunction(double value) {
			return (2.0 / (1.0 + exp(value))) - 1;
		}

		double calculateNeuronSum() {
			double sum = 0;
			for (unsigned int i = 0; i < this->arrWeightsSize; i++) {
				sum += this->arrWeights[i] * this->arrInputsNeurons[i]->generateOutput();
			}
			return sum;
		}

};

#endif /* SRC_LIB_NEURON_CPP_ */