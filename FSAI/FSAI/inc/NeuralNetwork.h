#pragma once

#define learningRate	(0.1)
#define initialWeight	(1.0) 
#define BIAS			1

typedef struct neuron {

	double* weight;
	double	error;
	double	output;

	int		numberOfConnections;

} Neuron;

typedef struct layer {

	Neuron* neurons;

	int		numberOfNeurons;

} Layer;

typedef struct neuralNetwork {

	Layer	inputLayer;
	Layer*	hiddenLayer;
	Layer	outputLayer;

	int		numberOfHiddenLayers;

} NeuralNetwork;


double relu(double X);

void NeuralNetwork_CreateNeuron(Neuron* neuron, int numberOfConnections);

NeuralNetwork* NeuralNetwork_CreateNeuralNetwork(int numberOfInputNeurons, int numberOfHiddenLayers, int numberOfHiddenNeurons, int numberOfOutputNeurons);

void NeuralNetwork_DestroyNeuralNetwork(NeuralNetwork* myNeuralNetwork); 

void NeuralNetwork_CopyFileToArrays(const char* fileName, const int numberOfInputNeurons, const int numberOfHiddenLayers, const int numberOfHiddenNeurons, const int numberOfOutputNeurons,
	double* NeuralNetwork_HiddenWeights, double* NeuralNetwork_OutputWeights);

void NeuralNetwork_CopyArraysToFile(const char* fileName, const int numberOfInputNeurons, const int numberOfHiddenLayers, const int numberOfHiddenNeurons, const int numberOfOutputNeurons,
	double* NeuralNetwork_HiddenWeights, double* NeuralNetwork_OutputWeights);

void NeuralNetwork_CopyArraysToNeuralNetwork(NeuralNetwork* myNeuralNetwork, double* NeuralNetwork_HiddenWeights, double* NeuralNetwork_OutputWeights);

void NeuralNetwork_CopyNeuralNetworkToArrays(NeuralNetwork* myNeuralNetwork, double* NeuralNetwork_HiddenWeights, double* NeuralNetwork_OutputWeights);

void NeuralNetwork_RandomMutations(NeuralNetwork* myNeuralNetwork);
