#include "NeuralNetwork.h"
#include <cstdlib>				// malloc & free
#include <fstream>				// read and create files


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
	neuron->output = 1;
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

NeuralNetwork* NeuralNetwork_LoadNeuralNetwork(char* fileName, const int numberOfInputNeurons, const int numberOfHiddenLayers, const int numberOfHiddenNeurons, const int numberOfOutputNeurons) {
	
	

	std::ifstream NeuralNetworkTxtFile(fileName);

	NeuralNetwork* NeuralNetwork_fromTxtFile;
	NeuralNetwork_fromTxtFile = NeuralNetwork_CreateNeuralNetwork(numberOfInputNeurons, numberOfHiddenLayers, numberOfHiddenNeurons, numberOfOutputNeurons);





	NeuralNetworkTxtFile.close();

	return NeuralNetwork_fromTxtFile;
}

void NeuralNetwork_CopyLayersToArray(NeuralNetwork* myNeuralNetwork, double& myNeuralNetwork_Array) {

}

void NeuralNetwork_SaveNeuralNetwork(NeuralNetwork* myNeuralNetwork, char* fileName) {

}

void NeuralNetwork_randomMutations(NeuralNetwork* myNeuralNetwork) {

}

