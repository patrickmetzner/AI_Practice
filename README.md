# AI_Practice

**Latest running version: FSAI - Milestone 1** (description below).

This is a project that started in 14/06/2020 with the intention of learning more about **AI** (artificial intelligence) and **neural networks**.


# About the project

The goal of this project is to use **AI** and **machine learning** to make a virtual representation of a Formula SAE car race around a racetrack.

The chosen racetrack is **ECPA** (Piracicaba-SP-BR), used for the endurance event of the **2019 Brazilian FSAE competition**. The data about the track and specific points where obstacles (cones) are positioned, will be taken from the telemetry files logged with **betaLogger**, the team's data logger, during the competition. [The repository about the data logger project can be found here](https://github.com/patrickmetzner/betaLogger). 

# Milestones

This project will be divided into **5 Milestones**:

## Milestone 1: [Ready on July 25th, 2020]. 

Simple "game", with minimalistic graphics, where a car should drive, **controlled by AI**, on a straight road, avoiding obstacles placed randomly through the road. 

To run the project, download the folder **FSAI - Milestone 1** and run the **FSAI - Milestone 1\FSAI\FSAI** application file. The cars will start to train their **Neural Network** to avoid the obstacles. The weights of the best **Neural Network** of each training cycle will be saved in a .txt file in the **FSAI - Milestone 1\FSAI\trainingFiles** folder. Two GIFs can be found below, showing the beginning and the end of the **Neural Network** training.  

Each car has a **Multilayer Neural Network** with **7** (+1 BIAS) input neurons, **2** hidden layers with **4** (+1 BIAS) neurons each hidden layer and **2** output neurons.

<img src="https://github.com/patrickmetzner/AI_Practice/blob/master/FSAI%20-%20Milestone%201/FSAI/images/FSAI_Training.gif" width=200>			<img src="https://github.com/patrickmetzner/AI_Practice/blob/master/FSAI%20-%20Milestone%201/FSAI/images/FSAI_Trained.gif" width=200>


## Milestone 2:

Goal: Create a simple "game", with minimalistic graphics, where a car should drive, **controlled by AI**, around **simple tracks** (circular, oval and rectangular), **avoiding hitting the walls**. This milestone is inspired by [this video](https://www.youtube.com/watch?v=gnfkfUQvKDw&list=PLPWikzi38KIwwQdolewJb_Ei1NAb4BSFg&index=3).

## Milestone 3:

Goal: Recreate the "game" from the previous milestone, but implement the **ECPA racetrack** instead of the simple tracks used previously.

## Milestone 4: 

Goal: Recreate the "game" from the previous milestone, but **implement physics** to make the modeled car behave like a more realistic car. The idea is to implement some kind of system like the one found at the **[SimulinkPractice repository](https://github.com/patrickmetzner/SimulinkPractice)**.

## Milestone 5: 

Goal: Optimize the code to get a **neural network** that can find the **fastest way** around the racetrack after physics are implemented. The expectation is that the **AI controlled car** will choose to follow what it is known as **"racing line"**, trying to minimize the radius of the turns, so it can carry more speed into the corners. 




The inspiration for this project is [this playlist](https://www.youtube.com/watch?v=NZlIYr1slAk&list=PLPWikzi38KIwwQdolewJb_Ei1NAb4BSFg).

The files on [Victor Dias Github](https://github.com/JVictorDias) will be used as guidelines for Milestone 2 and 3.
