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

#ifndef SRC_LIB_NEURALNETWORK_CPP_
#define SRC_LIB_NEURALNETWORK_CPP_

#include <stdexcept>
#include "Neuron.cpp"

/**
 * That's here where all happens
 * Here is where we push the values to
 * the neural network and get its results
 */
class NeuralNetwork {
	public:

		/**
		 * A list of neurons from previous layer
		 */
		Neuron** arrInputLayer;

		/**
		 * The size of the list from previous layer
		 */
		unsigned int inputLayerSize;

		/**
		 * Output layer size
		 */
		unsigned int outputLayerSize;

		/**
		 * Leaning rate
		 */
		float learningRate;

		/**
		 * The output layer
		 */
		Neuron** arrOutputLayer;

		/**
		 * Desired values for output layer
		 */
		float* arrDesiredOutputValues;

		/**
		 * Error from desired minus actual
		 * output layer value
		 */
		float* arrErrorValues;

		/**
		 * The amount of inner layers ( a.k.a hidden layers )
		 */
		unsigned int amountOfInnerLayers;

		/**
		 * The amount of neurons inner layers must have
		 */
		unsigned int innerLayersSize;

		/**
		 * The inner layers
		 */
		Neuron*** arrInnerLayers;

		/**
		 * Creates a neural network
		 * @param inputLayerSize - Amount of neurons at input
		 * @param outputLayerSize - Amount of neurons at output
		 * @param amountOfInnerLayers - Amount inner ( a.k.a hidden ) layers
		 * @param innerLayersSize - Amount of neurons at inner layers
		 */
		NeuralNetwork(unsigned int inputLayerSize, unsigned int outputLayerSize, unsigned int amountOfInnerLayers, unsigned int innerLayersSize, float bias, float learningRate) {
			buildInputLayer(inputLayerSize);
			buildInnerLayer(inputLayerSize, innerLayersSize, amountOfInnerLayers, bias);
			buildOutputLayer(inputLayerSize, innerLayersSize, amountOfInnerLayers, outputLayerSize, bias);

			this->learningRate = learningRate;
			this->arrErrorValues = new float[outputLayerSize];
			this->arrDesiredOutputValues = new float[outputLayerSize];
		}

		/**
		 * Push desired values into network.
		 * Used for network training
		 * @param arrDesiredResults
		 */
		void pushDesiredResults(float* arrDesiredResults) {
			for (unsigned int i = 0; i < this->outputLayerSize; i++) {
				this->arrDesiredOutputValues[i] = arrDesiredResults[i];
			}
		}

		/**
		 * Pushes the inputs values to input neurons
		 * @param arrInputValues
		 */
		void pushInputs(float* arrInputValues) {
			for (unsigned int i = 0; i < this->inputLayerSize; i++) {
				this->arrInputLayer[i]->setValue(arrInputValues[i]);
			}
		}

		/**
		 * Gets the neural network response
		 * It calculates the errors according to
		 * the actual neural network output
		 * @see pushInputs
		 * @see pushDesiredResults
		 */
		void iterate(char training = 0) {

			// recalculates the output and errors
			for (unsigned int i = 0; i < this->outputLayerSize; i++) {

				// Calculates the output
				float val = this->arrOutputLayer[i]->generateOutput();

				if (training) {
					// Calculates the error
					this->arrErrorValues[i] = this->arrDesiredOutputValues[i] - val;

					// Rectify the weights
					this->arrOutputLayer[i]->rectifyWeights(this->learningRate, this->arrErrorValues[i]);
				}
			}

//			sofMax(arrOutputLayer, this->outputLayerSize);
		}

		void sofMax(Neuron**& arrOutput, int outputSize) {

			double sum = 0;
			for (int i = 0; i < outputSize; i++) {
				sum += exp(arrOutput[i]->value);
			}
			for (int i = 0; i < outputSize; i++) {
				arrOutput[i]->value = exp(arrOutput[i]->value) / sum;
			}
		}

		/**
		 * Return the network errors values
		 * use iterate before
		 * @see iterate
		 * @return network errors values
		 */
		float* getErrors() {
			return this->arrErrorValues;
		}

		/**
		 * Return the network output values
		 * use iterate before
		 * @see iterate
		 * @return network output values
		 */
		Neuron** getOutputLayer() {
			return this->arrOutputLayer;
		}

		~NeuralNetwork() {

			// Cleans desired results
			delete[] this->arrDesiredOutputValues;

			// Cleans the error values
			delete[] this->arrErrorValues;

			// clears input layer
			for (unsigned int i = 0; i < this->inputLayerSize; i++) {
				delete this->arrInputLayer[i];
			}
			delete[] this->arrInputLayer;

			// clears output layer
			for (unsigned int i = 0; i < outputLayerSize; i++) {
				delete this->arrOutputLayer[i];
			}
			delete[] this->arrOutputLayer;

			// clears inner layers
			for (unsigned int ii = 0; ii < this->amountOfInnerLayers; ii++) {
				for (unsigned int ni = 0; ni < this->innerLayersSize; ni++) {
					delete this->arrInnerLayers[ii][ni];
				}
				delete[] this->arrInnerLayers[ii];
			}
			delete[] this->arrInnerLayers;
		}

	private:
		/**
		 * Builds input layer
		 * @param inputLayerSize
		 */
		void buildInputLayer(unsigned int inputLayerSize) {
			// building the input layer
			this->inputLayerSize = inputLayerSize;
			this->arrInputLayer = new Neuron*[inputLayerSize];
			for (unsigned int i = 0; i < inputLayerSize; i++) {
				this->arrInputLayer[i] = new Neuron();
			}
		}

		/**
		 * Builds inner layer
		 * @param innerLayersSize
		 * @param amountOfInnerLayers
		 * @param inputLayerSize
		 */
		void buildInnerLayer(unsigned int inputLayerSize, unsigned int innerLayersSize, unsigned int amountOfInnerLayers, float bias) {
			// building inner layers
			this->innerLayersSize = innerLayersSize;
			this->amountOfInnerLayers = amountOfInnerLayers;
			// creates the list of layers
			if (amountOfInnerLayers > 0) {
				this->arrInnerLayers = new Neuron**[amountOfInnerLayers];
			}
			// initializes and populate the inner layers
			// ii - Inner layer index
			// ni - Neuron index
			for (unsigned int ii = 0; ii < amountOfInnerLayers; ii++) {
				this->arrInnerLayers[ii] = new Neuron*[innerLayersSize];
				for (unsigned int ni = 0; ni < innerLayersSize; ni++) {
					// connects input layer to first inner layer
					if (ii == 0) {
						this->arrInnerLayers[ii][ni] = new Neuron(inputLayerSize, arrInputLayer, inputLayerSize, bias);
						continue;
					}
					// connects previous inner layer to next inner layer
					this->arrInnerLayers[ii][ni] = new Neuron(innerLayersSize, this->arrInnerLayers[ii - 1], innerLayersSize, bias);
				}
			}
		}

		/**
		 * Builds output layer
		 * @param amountOfInnerLayers
		 * @param outputLayerSize
		 * @param inputLayerSize
		 * @param innerLayersSize
		 */
		void buildOutputLayer(unsigned int inputLayerSize, unsigned int innerLayersSize, unsigned int amountOfInnerLayers, unsigned int outputLayerSize, float bias) {
			// No inner layer: Input is connected directly to output
			if (amountOfInnerLayers <= 0) {
				// building the output layer
				this->outputLayerSize = outputLayerSize;
				this->arrOutputLayer = new Neuron*[inputLayerSize];
				for (unsigned int i = 0; i < outputLayerSize; i++) {
					this->arrOutputLayer[i] = new Neuron(inputLayerSize, arrInputLayer, inputLayerSize, bias);
				}
				return;
			}
			// There is inner layers!!! Connect the last one to output.
			// building the output layer
			this->outputLayerSize = outputLayerSize;
			this->arrOutputLayer = new Neuron*[outputLayerSize];
			for (unsigned int i = 0; i < outputLayerSize; i++) {
				this->arrOutputLayer[i] = new Neuron(innerLayersSize, this->arrInnerLayers[amountOfInnerLayers - 1], innerLayersSize, bias);
			}
		}
};

#endif /* SRC_LIB_NEURALNETWORK_CPP_ */
