#include "NeuralNetwork.h"
#include <iostream>
#include <cstdlib>				// malloc & free
#include <fstream>				// read and create files
#pragma warning(disable : 4996)	// fopen and sprintf


double relu(double X) {
	if (X < 0) {
		return 0;
	}
	else {
		if (X < 10000) {
			return X;
		}
		else {
			return 10000;
		}
	}
}

void NeuralNetwork_CreateNeuron(Neuron* neuron, int numberOfConnections) {

	neuron->numberOfConnections = numberOfConnections;
	neuron->weight = (double*)malloc(numberOfConnections * sizeof(double));

	for (int i = 0; i < numberOfConnections; i++) {
		neuron->weight[i] = (double)(rand() % 2000 - (double)1000) / 1000;
	}

	neuron->error = 0;
	neuron->output = initialOutput;
}

NeuralNetwork* NeuralNetwork_CreateNeuralNetwork(int numberOfInputNeurons, int numberOfHiddenLayers, int numberOfHiddenNeurons, int numberOfOutputNeurons) {

	NeuralNetwork* myNeuralNetwork = (NeuralNetwork*)malloc(sizeof(NeuralNetwork));

	myNeuralNetwork->inputLayer.numberOfNeurons = numberOfInputNeurons;
	myNeuralNetwork->inputLayer.neurons = (Neuron*)malloc(numberOfInputNeurons * sizeof(Neuron));

	for (int i = 0; i < numberOfInputNeurons; i++) {
		myNeuralNetwork->inputLayer.neurons[i].output = 1.0; 
	}

	myNeuralNetwork->numberOfHiddenLayers = numberOfHiddenLayers;
	myNeuralNetwork->hiddenLayer = (Layer*)malloc(numberOfHiddenLayers * sizeof(Layer));

	for (int i = 0; i < numberOfHiddenLayers; i++) {
		myNeuralNetwork->hiddenLayer[i].numberOfNeurons = numberOfHiddenNeurons;
		myNeuralNetwork->hiddenLayer[i].neurons = (Neuron*)malloc(numberOfHiddenNeurons * sizeof(Neuron));

		for (int j = 0; j < numberOfHiddenNeurons; j++) {
			if (i == 0) {
				NeuralNetwork_CreateNeuron(&myNeuralNetwork->hiddenLayer[i].neurons[j], numberOfInputNeurons);
			}
			else {
				NeuralNetwork_CreateNeuron(&myNeuralNetwork->hiddenLayer[i].neurons[j], numberOfHiddenNeurons);
			}
		}
	}

	myNeuralNetwork->outputLayer.numberOfNeurons = numberOfOutputNeurons;
	myNeuralNetwork->outputLayer.neurons = (Neuron*)malloc(numberOfOutputNeurons * sizeof(Neuron));

	for (int i = 0; i < numberOfOutputNeurons; i++) {
		NeuralNetwork_CreateNeuron(&myNeuralNetwork->outputLayer.neurons[i], numberOfHiddenNeurons);
	}

	return myNeuralNetwork;
}

void NeuralNetwork_DestroyNeuralNetwork(NeuralNetwork* myNeuralNetwork) {

	free(myNeuralNetwork->inputLayer.neurons);

	for (int i = 0; i < myNeuralNetwork->numberOfHiddenLayers; i++) {
		for (int j = 0; j < myNeuralNetwork->hiddenLayer[i].numberOfNeurons; j++) {
			free(myNeuralNetwork->hiddenLayer[i].neurons[j].weight);
		}
		free(myNeuralNetwork->hiddenLayer[i].neurons);
	}
	free(myNeuralNetwork->hiddenLayer);

	for (int i = 0; i < myNeuralNetwork->outputLayer.numberOfNeurons; i++) {
		free(myNeuralNetwork->outputLayer.neurons[i].weight);
	}
	free(myNeuralNetwork->outputLayer.neurons);

	free(myNeuralNetwork);
}

void NeuralNetwork_CopyFileToArrays(const char* fileName, const int numberOfInputNeurons, const int numberOfHiddenLayers, const int numberOfHiddenNeurons, const int numberOfOutputNeurons,
	double* NeuralNetwork_HiddenWeights, double* NeuralNetwork_OutputWeights) {

	std::ifstream dataFile(fileName);

	for (int i = 0; i < ((numberOfHiddenLayers - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + numberOfInputNeurons * numberOfHiddenNeurons; i++) {
		dataFile >> NeuralNetwork_HiddenWeights[i];
	}

	for (int i = 0; i < numberOfOutputNeurons * numberOfHiddenNeurons; i++) {
		dataFile >> NeuralNetwork_OutputWeights[i];
	}

	int latestArrayPosition;
	for (int k = 0; k < numberOfHiddenLayers; k++) {
		for (int i = 0; i < numberOfHiddenNeurons; i++) {
			if (k == 0) {
				for (int j = 0; j < numberOfInputNeurons; j++) {
					std::cout << NeuralNetwork_HiddenWeights[(i * numberOfInputNeurons) + j] << '	';
					latestArrayPosition = 1 + (i * numberOfInputNeurons) + j;
				}
			}
			else {
				for (int j = 0; j < numberOfHiddenNeurons; j++) {
					std::cout << NeuralNetwork_HiddenWeights[latestArrayPosition + ((k - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + (i * numberOfHiddenNeurons) + j] << '	';
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < numberOfOutputNeurons; i++) {
		for (int j = 0; j < numberOfHiddenNeurons; j++) {
			std::cout << NeuralNetwork_OutputWeights[(i * numberOfHiddenNeurons) + j] << "	";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "file read" << std::endl;
	std::cout << std::endl;

	dataFile.close();
}

void NeuralNetwork_CopyArraysToFile(const char* fileName, const int numberOfInputNeurons, const int numberOfHiddenLayers, const int numberOfHiddenNeurons, const int numberOfOutputNeurons,
	double* NeuralNetwork_HiddenWeights, double* NeuralNetwork_OutputWeights) {

	FILE* temp = fopen(fileName, "w");
	fclose(temp);

	std::ofstream dataFile(fileName);

	int latestArrayPosition;
	for (int k = 0; k < numberOfHiddenLayers; k++) {
		for (int i = 0; i < numberOfHiddenNeurons; i++) {
			if (k == 0) {
				for (int j = 0; j < numberOfInputNeurons; j++) {
					dataFile << NeuralNetwork_HiddenWeights[(i * numberOfInputNeurons) + j] << '	';
					std::cout << NeuralNetwork_HiddenWeights[(i * numberOfInputNeurons) + j] << '	';
					latestArrayPosition = 1 + (i * numberOfInputNeurons) + j;
				}
			}
			else {
				for (int j = 0; j < numberOfHiddenNeurons; j++) {
					dataFile << NeuralNetwork_HiddenWeights[latestArrayPosition + ((k - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + (i * numberOfHiddenNeurons) + j] << '	';
					std::cout << NeuralNetwork_HiddenWeights[latestArrayPosition + ((k - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + (i * numberOfHiddenNeurons) + j] << '	';
				}
			}
			dataFile << std::endl;
			std::cout << std::endl;
		}
		dataFile << std::endl;
		std::cout << std::endl;
	}
	dataFile << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < numberOfOutputNeurons; i++) {
		for (int j = 0; j < numberOfHiddenNeurons; j++) {
			dataFile << NeuralNetwork_OutputWeights[(i * numberOfHiddenNeurons) + j] << "	";
			std::cout << NeuralNetwork_OutputWeights[(i * numberOfHiddenNeurons) + j] << "	";
		}
		dataFile << std::endl;
		std::cout << std::endl;
	}
	dataFile << std::endl;
	std::cout << std::endl;

	dataFile << "-----------------" << std::endl;
	dataFile << "Neural Network structure:" << std::endl;
	dataFile << numberOfInputNeurons - BIAS << " Input Neurons + BIAS" << std::endl;
	dataFile << numberOfHiddenLayers << " Hidden Layers" << std::endl;
	dataFile << numberOfHiddenNeurons - BIAS << " Hidden Neurons + BIAS" << std::endl;
	dataFile << numberOfOutputNeurons << " Output Neurons" << std::endl;

	dataFile.close();

	std::cout << "file saved" << std::endl;
}

void NeuralNetwork_CopyArraysToNeuralNetwork(NeuralNetwork* myNeuralNetwork, double* NeuralNetwork_HiddenWeights, double* NeuralNetwork_OutputWeights) {
	
	int numberOfInputNeurons = myNeuralNetwork->inputLayer.numberOfNeurons;
	int numberOfHiddenLayers = myNeuralNetwork->numberOfHiddenLayers;
	int numberOfHiddenNeurons = myNeuralNetwork->hiddenLayer[0].numberOfNeurons;
	int numberOfOutputNeurons = myNeuralNetwork->outputLayer.numberOfNeurons;
	
	int latestArrayPosition=0;
	for (int k = 0; k < numberOfHiddenLayers; k++) {
		for (int i = 0; i < numberOfHiddenNeurons; i++) {
			if (k == 0) {
				for (int j = 0; j < numberOfInputNeurons; j++) {
					myNeuralNetwork->hiddenLayer[k].neurons[i].weight[j] = NeuralNetwork_HiddenWeights[(i * numberOfInputNeurons) + j];
					latestArrayPosition = 1 + (i * numberOfInputNeurons) + j;
				}
			}
			else {
				for (int j = 0; j < numberOfHiddenNeurons; j++) {
					myNeuralNetwork->hiddenLayer[k].neurons[i].weight[j] = NeuralNetwork_HiddenWeights
						[latestArrayPosition + ((k - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + (i * numberOfHiddenNeurons) + j];
				}
			}
		}
	}

	for (int i = 0; i < numberOfOutputNeurons; i++) {
		for (int j = 0; j < numberOfHiddenNeurons; j++) {
			myNeuralNetwork->outputLayer.neurons[i].weight[j] = NeuralNetwork_OutputWeights[(i * numberOfHiddenNeurons) + j];
		}
	}
}

void NeuralNetwork_CopyNeuralNetworkToArrays(NeuralNetwork* myNeuralNetwork, double* NeuralNetwork_HiddenWeights, double* NeuralNetwork_OutputWeights) {

	int numberOfInputNeurons = myNeuralNetwork->inputLayer.numberOfNeurons;
	int numberOfHiddenLayers = myNeuralNetwork->numberOfHiddenLayers;
	int numberOfHiddenNeurons = myNeuralNetwork->hiddenLayer[0].numberOfNeurons;
	int numberOfOutputNeurons = myNeuralNetwork->outputLayer.numberOfNeurons;

	int latestArrayPosition = 0;
	for (int k = 0; k < numberOfHiddenLayers; k++) {
		for (int i = 0; i < numberOfHiddenNeurons; i++) {
			if (k == 0) {
				for (int j = 0; j < numberOfInputNeurons; j++) {
					NeuralNetwork_HiddenWeights[(i * numberOfInputNeurons) + j] = myNeuralNetwork->hiddenLayer[k].neurons[i].weight[j];
					latestArrayPosition = 1 + (i * numberOfInputNeurons) + j;
				}
			}
			else {
				for (int j = 0; j < numberOfHiddenNeurons; j++) {
					NeuralNetwork_HiddenWeights[latestArrayPosition + ((k - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + (i * numberOfHiddenNeurons) + j]
						= myNeuralNetwork->hiddenLayer[k].neurons[i].weight[j];
				}
			}
		}
	}

	for (int i = 0; i < numberOfOutputNeurons; i++) {
		for (int j = 0; j < numberOfHiddenNeurons; j++) {
			NeuralNetwork_OutputWeights[(i * numberOfHiddenNeurons) + j] = myNeuralNetwork->outputLayer.neurons[i].weight[j];
		}
	}
}

void NeuralNetwork_CalculateOutput(NeuralNetwork* myNeuralNetwork, double* NeuralNetwork_InputArray, double* NeuralNetwork_OutputArray) {

	int numberOfInputNeurons = myNeuralNetwork->inputLayer.numberOfNeurons;
	int numberOfHiddenLayers = myNeuralNetwork->numberOfHiddenLayers;
	int numberOfHiddenNeurons = myNeuralNetwork->hiddenLayer[0].numberOfNeurons;
	int numberOfOutputNeurons = myNeuralNetwork->outputLayer.numberOfNeurons;
	double weightsSumProduct = 0;

	for (int i = 0; i < numberOfInputNeurons; i++) {
		myNeuralNetwork->inputLayer.neurons[i].output = NeuralNetwork_InputArray[i];
	}

	for (int k = 0; k < numberOfHiddenLayers; k++) {
		for (int j = 0; j < numberOfHiddenNeurons; j++) {
			if (k == 0) {
				weightsSumProduct = 0;
				for (int i = 0; i < numberOfInputNeurons; i++) {
					weightsSumProduct += myNeuralNetwork->inputLayer.neurons[i].output * myNeuralNetwork->hiddenLayer[k].neurons[j].weight[i];
				}
				myNeuralNetwork->hiddenLayer[k].neurons[j].output = relu(weightsSumProduct);
			}
			else {
				weightsSumProduct = 0;
				for (int i = 0; i < numberOfHiddenNeurons; i++) {
					weightsSumProduct += myNeuralNetwork->hiddenLayer[k-1].neurons[i].output * myNeuralNetwork->hiddenLayer[k].neurons[j].weight[i];
				}
				myNeuralNetwork->hiddenLayer[k].neurons[j].output = relu(weightsSumProduct);
			}
		}
	}

	for (int j = 0; j < numberOfOutputNeurons; j++) {
		weightsSumProduct = 0;
		for (int i = 0; i < numberOfHiddenNeurons; i++) {
			weightsSumProduct += myNeuralNetwork->hiddenLayer[numberOfHiddenLayers - 1].neurons[i].output * myNeuralNetwork->outputLayer.neurons[j].weight[i];
		}
		myNeuralNetwork->outputLayer.neurons[j].output = relu(weightsSumProduct);
	}

	for (int i = 0; i < numberOfOutputNeurons; i++) {
		NeuralNetwork_OutputArray[i] = myNeuralNetwork->outputLayer.neurons[i].output;
	}
}

void NeuralNetwork_RandomMutations(NeuralNetwork* myNeuralNetwork, double* NeuralNetwork_HiddenWeights, double* NeuralNetwork_OutputWeights) {

	int numberOfInputNeurons = myNeuralNetwork->inputLayer.numberOfNeurons;
	int numberOfHiddenLayers = myNeuralNetwork->numberOfHiddenLayers;
	int numberOfHiddenNeurons = myNeuralNetwork->hiddenLayer[0].numberOfNeurons;
	int numberOfOutputNeurons = myNeuralNetwork->outputLayer.numberOfNeurons;
	int sizeOfHiddenWeightsArray = ((numberOfHiddenLayers - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + numberOfInputNeurons * numberOfHiddenNeurons;
	int sizeOfOutputWeightsArray = numberOfOutputNeurons * numberOfHiddenNeurons;
	int sizeOfNeuralNetwork = sizeOfHiddenWeightsArray + sizeOfOutputWeightsArray;

	NeuralNetwork_CopyNeuralNetworkToArrays(myNeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

	int numberOfMutations = ceil(learningRate * (double)(sizeOfNeuralNetwork));
	int mutationPosition = 0;
	for (int i = 0; i < numberOfMutations; i++) {
		mutationPosition = rand() % sizeOfNeuralNetwork;

		if (mutationPosition < sizeOfHiddenWeightsArray) {
			NeuralNetwork_HiddenWeights[mutationPosition] = (double)(rand() % 2000 - (double)1000) / 1000;
		}
		else {
			NeuralNetwork_OutputWeights[mutationPosition - sizeOfHiddenWeightsArray] = (double)(rand() % 2000 - (double)1000) / 1000;
		}
	}

	NeuralNetwork_CopyArraysToNeuralNetwork(myNeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);
}
