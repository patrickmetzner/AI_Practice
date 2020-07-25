#include "pch.h"
#include "NeuralNetwork.h"
#include <iostream>
#include <time.h>				// time(0)
#include <fstream>

#define numberOfInputNeurons	(7 + BIAS)
#define numberOfHiddenLayers	(5)
#define numberOfHiddenNeurons	(6 + BIAS)
#define numberOfOutputNeurons	(2)

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

	NeuralNetwork_CopyArraysToFile("testFiles\\OutputSequence.txt", numberOfInputNeurons, numberOfHiddenLayers, numberOfHiddenNeurons, numberOfOutputNeurons, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

	ClearArray(NeuralNetwork_HiddenWeights, sizeOfHiddenWeightsArray);
	ClearArray(NeuralNetwork_OutputWeights, sizeOfOutputWeightsArray);

	NeuralNetwork_CopyFileToArrays("testFiles\\OutputSequence.txt", numberOfInputNeurons, numberOfHiddenLayers, numberOfHiddenNeurons, numberOfOutputNeurons, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

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

TEST(TestNeuralNetwork, TestInputAndOutput) {
	// First case
	NeuralNetwork* myNeuralNetwork_1 = NeuralNetwork_CreateNeuralNetwork(4, 2, 3, 2);

	double myNeuralNetwork_1_HiddenWeights[((2 - 1) * 3 * 3) + 4 * 3];
	double myNeuralNetwork_1_OutputWeights[2 * 3];
	double myNeuralNetwork_1_InputArray[4];
	double myNeuralNetwork_1_OutputArray[2];

	WriteSequenceToArray(myNeuralNetwork_1_HiddenWeights, 21);
	WriteSequenceToArray(myNeuralNetwork_1_OutputWeights, 6);
	WriteSequenceToArray(myNeuralNetwork_1_InputArray, 4);

	NeuralNetwork_CopyArraysToNeuralNetwork(myNeuralNetwork_1, myNeuralNetwork_1_HiddenWeights, myNeuralNetwork_1_OutputWeights);

	NeuralNetwork_CalculateOutput(myNeuralNetwork_1, myNeuralNetwork_1_InputArray, myNeuralNetwork_1_OutputArray);

	EXPECT_EQ(myNeuralNetwork_1_OutputArray[0], 6300);
	EXPECT_EQ(myNeuralNetwork_1_OutputArray[1], 10000);


	// Second case
	NeuralNetwork* myNeuralNetwork_2 = NeuralNetwork_CreateNeuralNetwork(6, 1, 4, 3);

	double myNeuralNetwork_2_HiddenWeights[((1 - 1) * 4 * 4) + 6 * 4];
	double myNeuralNetwork_2_OutputWeights[3 * 4];
	double myNeuralNetwork_2_InputArray[6];
	double myNeuralNetwork_2_OutputArray[3];

	WriteSequenceToArray(myNeuralNetwork_2_HiddenWeights, 24);
	WriteSequenceToArray(myNeuralNetwork_2_OutputWeights, 12);
	WriteSequenceToArray(myNeuralNetwork_2_InputArray, 6);

	NeuralNetwork_CopyArraysToNeuralNetwork(myNeuralNetwork_2, myNeuralNetwork_2_HiddenWeights, myNeuralNetwork_2_OutputWeights);

	NeuralNetwork_CalculateOutput(myNeuralNetwork_2, myNeuralNetwork_2_InputArray, myNeuralNetwork_2_OutputArray);

	EXPECT_EQ(myNeuralNetwork_2_OutputArray[0], 1590);
	EXPECT_EQ(myNeuralNetwork_2_OutputArray[1], 4630);
	EXPECT_EQ(myNeuralNetwork_2_OutputArray[2], 7670);
}
