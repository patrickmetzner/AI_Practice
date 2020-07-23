#include "pch.h"
#include "NeuralNetwork.h"
#include <iostream>
#include <time.h>				// time(0)
#include <fstream>

const int numberOfInputNeurons = 6 + BIAS;
const int numberOfHiddenLayers = 3;
const int numberOfHiddenNeurons = 4 + BIAS;
const int numberOfOutputNeurons = 2;

int sizeOfHiddenWeightsArray = ((numberOfHiddenLayers - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + numberOfInputNeurons * numberOfHiddenNeurons;
int sizeOfOutputWeightsArray = numberOfOutputNeurons * numberOfHiddenNeurons;
int sizeOfNeuralNetwork = sizeOfHiddenWeightsArray + sizeOfOutputWeightsArray;

double NeuralNetwork_HiddenWeights[((numberOfHiddenLayers - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + numberOfInputNeurons * numberOfHiddenNeurons];
double NeuralNetwork_OutputWeights[numberOfOutputNeurons * numberOfHiddenNeurons];

void WriteSequenceToArray(double* Array, int size) {
	for (int i = 0; i < size; i++) {
		Array[i] = i;
	}
}

void ClearArray(double* Array, int size) {
	for (int i = 0; i < size; i++) {
		Array[i] = 0;
	}
}

TEST(TestNeuralNetwork, TestArraysAndFiles) {
	bool passedTest = true;
	
	WriteSequenceToArray(NeuralNetwork_HiddenWeights, sizeOfHiddenWeightsArray);
	WriteSequenceToArray(NeuralNetwork_OutputWeights, sizeOfOutputWeightsArray);

	NeuralNetwork_CopyArraysToFile("OutputSequence.txt", numberOfInputNeurons, numberOfHiddenLayers, numberOfHiddenNeurons, numberOfOutputNeurons, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

	ClearArray(NeuralNetwork_HiddenWeights, sizeOfHiddenWeightsArray);
	ClearArray(NeuralNetwork_OutputWeights, sizeOfOutputWeightsArray);

	NeuralNetwork_CopyFileToArrays("OutputSequence.txt", numberOfInputNeurons, numberOfHiddenLayers, numberOfHiddenNeurons, numberOfOutputNeurons, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

	for (int i = 0; i < sizeOfHiddenWeightsArray; i++) {
		if (NeuralNetwork_HiddenWeights[i] != i) {
			passedTest = false;
			EXPECT_TRUE(passedTest);
			break;
		}
	}

	for (int i = 0; i < sizeOfOutputWeightsArray; i++) {
		if (NeuralNetwork_OutputWeights[i] != i) {
			passedTest = false;
			EXPECT_TRUE(passedTest);
			break;
		}
	}

	EXPECT_TRUE(passedTest);
}

TEST(TestNeuralNetwork, TestArraysAndNeuralNetwork) {
	bool passedTest = true; 
	
	NeuralNetwork* myNeuralNetwork = NeuralNetwork_CreateNeuralNetwork(numberOfInputNeurons, numberOfHiddenLayers, numberOfHiddenNeurons, numberOfOutputNeurons);

	WriteSequenceToArray(NeuralNetwork_HiddenWeights, sizeOfHiddenWeightsArray);
	WriteSequenceToArray(NeuralNetwork_OutputWeights, sizeOfOutputWeightsArray);

	NeuralNetwork_CopyArraysToNeuralNetwork(myNeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

	ClearArray(NeuralNetwork_HiddenWeights, sizeOfHiddenWeightsArray);
	ClearArray(NeuralNetwork_OutputWeights, sizeOfOutputWeightsArray);

	NeuralNetwork_CopyNeuralNetworkToArrays(myNeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

	for (int i = 0; i < sizeOfHiddenWeightsArray; i++) {
		if (NeuralNetwork_HiddenWeights[i] != i) {
			passedTest = false;
			EXPECT_TRUE(passedTest);
			break;
		}
	}

	for (int i = 0; i < sizeOfOutputWeightsArray; i++) {
		if (NeuralNetwork_OutputWeights[i] != i) {
			passedTest = false;
			EXPECT_TRUE(passedTest);
			break;
		}
	}

	EXPECT_TRUE(passedTest);
}

TEST(TestNeuralNetwork, TestRandomMutations) {
	srand((int)time(0));

	NeuralNetwork* myNeuralNetwork = NeuralNetwork_CreateNeuralNetwork(numberOfInputNeurons, numberOfHiddenLayers, numberOfHiddenNeurons, numberOfOutputNeurons);

	WriteSequenceToArray(NeuralNetwork_HiddenWeights, sizeOfHiddenWeightsArray);
	WriteSequenceToArray(NeuralNetwork_OutputWeights, sizeOfOutputWeightsArray);

	NeuralNetwork_CopyArraysToNeuralNetwork(myNeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

	NeuralNetwork_RandomMutations(myNeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

	int numberOfMutations = ceil(learningRate * (double)(sizeOfNeuralNetwork));
	std::cout << "Number of expected mutations:	" << numberOfMutations << std::endl;

	int k = 0;
	int mutationCounter = 0;
	while (k<10) {
		
		for (int i = 0; i < sizeOfHiddenWeightsArray; i++) {
			if (NeuralNetwork_HiddenWeights[i] != i) {
				mutationCounter++;
			}
		}
		for (int i = 0; i < sizeOfOutputWeightsArray; i++) {
			if (NeuralNetwork_OutputWeights[i] != i) {
				mutationCounter++;
			}
		}

		if (mutationCounter == numberOfMutations) {
			std::cout << "Number of mutations:		" << mutationCounter << std::endl; 
			break;
		}
		else {
			std::cout << "Number of mutations:		" << mutationCounter << std::endl;

			WriteSequenceToArray(NeuralNetwork_HiddenWeights, sizeOfHiddenWeightsArray);
			WriteSequenceToArray(NeuralNetwork_OutputWeights, sizeOfOutputWeightsArray);

			NeuralNetwork_CopyArraysToNeuralNetwork(myNeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

			NeuralNetwork_RandomMutations(myNeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

			mutationCounter = 0;
		}

		k++;
	}

	EXPECT_EQ(numberOfMutations, mutationCounter);
}


