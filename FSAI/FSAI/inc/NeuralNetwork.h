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

void NeuralNetwork_CopyLayersToArray(NeuralNetwork* myNeuralNetwork, double& myNeuralNetwork_Array);

void NeuralNetwork_SaveNeuralNetwork(NeuralNetwork* myNeuralNetwork, char* fileName);

void NeuralNetwork_randomMutations(NeuralNetwork* myNeuralNetwork);







/*

#include <iostream>
#include <fstream>

int main()
{
	///////////////////////
	//	Read data from file
	///////////////////////

	std::ifstream fileData("NeuralNetwork.txt");

	double fileWeight;

	const int numberOfInputNeurons = 3;
	const int numberOfHiddenLayers = 1; 	//implementar isso
	const int numberOfHiddenNeurons = 3;
	const int numberOfOutputNeurons = 2;

	double NeuralNetwork_InputWeights[numberOfInputNeurons][numberOfHiddenNeurons];
	double NeuralNetwork_HiddenWeights[numberOfHiddenNeurons][numberOfOutputNeurons];

	for (int i = 0; i < numberOfInputNeurons; i++) {
		for (int j = 0; j < numberOfHiddenNeurons; j++) {
			fileData >> fileWeight;
			NeuralNetwork_InputWeights[i][j] = fileWeight;
		}
	}

	for (int i = 0; i < numberOfHiddenNeurons; i++) {
		for (int j = 0; j < numberOfOutputNeurons; j++) {
			fileData >> fileWeight;
			NeuralNetwork_HiddenWeights[i][j] = fileWeight;
		}
	}

	for (int i = 0; i < numberOfInputNeurons; i++) {
		for (int j = 0; j < numberOfHiddenNeurons; j++) {
			std::cout << NeuralNetwork_InputWeights[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < numberOfHiddenNeurons; i++) {
		for (int j = 0; j < numberOfOutputNeurons; j++) {
			std::cout << NeuralNetwork_HiddenWeights[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "file read" << std::endl;
	std::cout << std::endl;

	fileData.close();


	/////////////////////
	//	Save data to file
	/////////////////////

	std::ofstream NN_File("NN_File.txt");

	for (int i = 0; i < numberOfInputNeurons; i++) {
		for (int j = 0; j < numberOfHiddenNeurons; j++) {
			NN_File <<  NeuralNetwork_InputWeights[i][j];
			NN_File << " ";
		}
		NN_File << std::endl;
	}
	NN_File << std::endl;

	for (int i = 0; i < numberOfHiddenNeurons; i++) {
		for (int j = 0; j < numberOfOutputNeurons; j++) {
			NN_File << NeuralNetwork_HiddenWeights[i][j];
			NN_File << " ";
		}
		NN_File << std::endl;
	}
	NN_File << std::endl;

	NN_File.close();

	std::cout << "file saved" << std::endl;


	std::cin.get();
	return 0;
}




*/