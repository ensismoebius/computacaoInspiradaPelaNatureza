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
		 * The bias for this neuron
		 */
		float bias;

		/**
		 * The weights for the connection with input neurons
		 */
		float* arrWeights;
		unsigned int arrWeightsSize;

		/**
		 * The input neurons
		 */
		Neuron** arrInputsNeurons;
		unsigned int arrInputsNeuronsSize;

	public:
		/**
		 * Values must be between [1,-1]
		 */
		float value;

		/**
		 * Used to initialize a neurons without value
		 * that are going to be updated after some iteration
		 */
		static const unsigned int CONST_INVALID_NEURON_VALUE = 2;

		/**
		 * When this is just an input neuron, it are not
		 * going to have any weights or activation functions
		 * because it will just provide to next layer
		 * @param value
		 */
		Neuron() {

			// bias for input layer
			this->bias = 1;

			// Populate with an invalid value
			// the actual value pushed after
			this->value = CONST_INVALID_NEURON_VALUE;

			// points all weights and inputs to null
			this->arrWeights = 0;
			this->arrWeightsSize = 0;
			this->arrInputsNeurons = 0;
			this->arrInputsNeuronsSize = 0;
		}

		Neuron(unsigned int arrWeightsSize, Neuron** arrInputsNeurons, unsigned int arrInputNeuronsSize, float bias) {

			// custom bias for another types of neurons
			this->bias = bias;

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

		/**
		 * If it is just an input neuron returns its
		 * current value, otherwise, do a bunch of
		 * calculations (including in the neurons
		 * linked) and, just after this, returns
		 * the calculated value
		 * @return the neuron value
		 */
		float generateOutput() {

			// this is just an input neuron
			if (this->arrWeightsSize == 0) {
				return this->value;
			}

			// this is a regular neuron, you
			// MUST calculate the output
			double sum = this->calculateNeuronSum() + this->bias;

			// update the neuron value
			this->value = (float) this->activationFunction(sum);

			return value;
		}

		/**
		 * Updates the weights between the neurons and
		 * the linked ones
		 * @param alpha
		 * @param error
		 */
		void rectifyWeights(float alpha, float error) {
			this->bias += alpha * error;

			for (unsigned int i = 0; i < this->arrWeightsSize; i++) {
				this->arrWeights[i] += this->arrInputsNeurons[i]->value * alpha * error;
				this->arrInputsNeurons[i]->rectifyWeights(alpha, error);
			}
		}

	private:

		/**
		 * Initializes the weights between the current
		 * neurons and the linked ones
		 * @param arrWeights
		 * @param arrWeightsSize
		 */
		void initializeWeights(float*& arrWeights, unsigned int arrWeightsSize) {
			while (arrWeightsSize--) {
				arrWeights[arrWeightsSize] = getGaussionRandomPertubation();
			}
		}

		/**
		 * The activation function
		 * @param net
		 * @return calculated value
		 */
		double activationFunction(double net) {
			return (1.0 / (1.0 + exp(-net)));
		}

		/**
		 * Sum up the inputs with their respective weights
		 * @return
		 */
		double calculateNeuronSum() {
			double sum = 0;
			for (unsigned int i = 0; i < this->arrWeightsSize; i++) {
				sum += this->arrWeights[i] * this->arrInputsNeurons[i]->generateOutput();
			}
			return sum;
		}
};
#endif /* SRC_LIB_NEURON_CPP_ */
