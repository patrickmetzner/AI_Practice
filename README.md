# AI_Practice

This is a project that started in 14/06/2020 with the intention of learning more about **AI** (artificial intelligence) and **neural networks**.

**Author**: 	Patrick Metzner Morais.

**Partner**: 	Maria Claudia Regio.


# About the project

The goal of this project is to use **AI** and **machine learning** to make a virtual representation of a Formula SAE car race around a racetrack.

The chosen racetrack is **ECPA** (Piracicaba-SP-BR), used for the endurance event of the **2019 Brazilian FSAE competition**. The data about the track and specific points where obstacles (cones) are positioned, will be taken from the telemetry files logged with **betaLogger**, the team's data logger, during the competition. [The repository about the data logger project can be found here](https://github.com/patrickmetzner/betaLogger). 

# Milestones

This project will be divided into **5 Milestones**:

**Milestone 1:** Create a simple "game", with minimalistic graphics, where a car should drive, **controlled by AI**, in a **straight road, avoiding obstacles** (rectangles) placed randomly through the road. 

**Milestone 2:** Create a simple "game", with minimalistic graphics, where a car should drive, **controlled by AI**, around **simple tracks** (circular, oval and rectangular), **avoiding hitting the walls**. This milestone is inspired by [this video](https://www.youtube.com/watch?v=gnfkfUQvKDw&list=PLPWikzi38KIwwQdolewJb_Ei1NAb4BSFg&index=3).

**Milestone 3:** Recreate the "game" from the previous milestone, but implement the **ECPA racetrack** instead of the simple tracks used previously.

**Milestone 4:** Recreate the "game" from the previous milestone, but **implement physics** to make the modeled car behave like a more realistic car. The idea is to implement some kind of system like the one found at the **[SimulinkPractice repository](https://github.com/patrickmetzner/SimulinkPractice)**.

**Milestone 5:** Optimize the code to get a **neural network** that can find the **fastest way** around the racetrack after physics are implemented. The expectation is that the **AI controlled car** will choose to follow what it is known as **"racing line"**, trying to minimize the radius of the turns, so it can carry more speed into the corners. 




The inspiration for this project is [this playlist](https://www.youtube.com/watch?v=NZlIYr1slAk&list=PLPWikzi38KIwwQdolewJb_Ei1NAb4BSFg).

The files on [Victor Dias Github](https://github.com/JVictorDias) will be used as guidelines for Milestone 2 and 3.