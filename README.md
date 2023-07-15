![my-Exploring Decision Trees and Markov Decision Processes for Enhanced Student Advising Systems_ A Comparative Analysis](https://github.com/Yassine-Squalli-Houssaini/Exploring-Decision-Trees-and-MDP-for-Student-Advising-Systems-A-Comparative-Analysis/assets/127676452/c824856f-5751-4e80-87a0-6c35b82b937d)

# Table of Contents

- [Abstract](#abstract)
- [Introduction](#introduction)
- [Literature Review](#literature-review)
- [Concepts Overview](#concepts-overview)
    - [Q-Learning Algorithm](#q-learning-algorithm)
    - [Bellman Equation](#bellman-equation)
- [MDP Framework Design](#mdp-framework-design)
- [Model evaluation](#Model-Evaluation)
- [Comparison of the Results](#comparison-of-the-results)
- [Comparison of Benefits](#comparison-of-benefits)
- [Effects of KB Based on MDP on Student Satisfaction and Academic Achievement](#effects-of-kb-based-on-mdp-on-student-satisfaction-and-academic-achievement)


## Abstract
This research aims to compare the performance of decision tree-based and Markov Decision Process (MDP)-based student time management advising systems. The study includes the generation of a synthetic dataset to represent student profiles and the implementation of an MDP framework. The MDP framework incorporates knowledge representation and decision-making components, enabling the system to provide personalized time management recommendations. The findings contribute to understanding the advantages of MDPs in student advising systems and their impact on student satisfaction and academic achievement.

## Introduction
Effective time management is crucial for students to optimize their academic performance and overall well- being. This research investigates the use of decision tree- based and MDP-based systems for student time management advising. The study compares their performance in terms of decision-making accuracy, adaptability, and customized recommendations. The research aims to enhance student satisfaction and improve academic achievement by providing personalized time management guidance.

## Literature Review
- __Knowledge representation__ methods involve structuring and organizing information to support reasoning and decision- making. Different approaches like logic-based methods, semantic networks, ontologies, and probabilistic models are used for this purpose.

- __Markov Decision Processes (MDPs)__ are mathematical frameworks used to model decision-making in uncertain environments. They include states, actions, transition probabilities, and rewards. MDPs are commonly used in reinforcement learning to model sequential decision-making tasks, enabling agents to make optimal decisions based on expected rewards and future states.

- __Decision trees__ are widely used for knowledge representation and machine learning. They provide a visual representation of decisions and their outcomes. Decision trees offer simplicity, interpretability, and the ability to handle various types of data. They are also capable of handling missing values and are computationally efficient.

- However, __decision trees__ have limitations. They can be sensitive to small changes in the data, leading to different tree structures and instability. Overfitting, where the tree memorizes training data and performs poorly on new data, is also a concern. Decision trees may struggle to capture complex relationships and interactions among variables.

- Employing __MDPs__ in student advising programs brings several advantages. MDPs can model the sequential nature of student decision-making, allowing for personalized and adaptive recommendations based on individual characteristics, preferences, and learning styles. They account for uncertainty and dynamics, considering factors like changing academic contexts and evolving student goals.

- __MDPs__ provide a framework for optimizing long-term outcomes, balancing immediate rewards with future benefits. By using reinforcement learning algorithms with MDPs, student advising systems can continuously learn and improve their recommendations over time.

- It's important to recognize that the specific advantages and disadvantages of using __MDPs__ in student advising may vary based on the context, implementation, and unique challenges of the advising domain. A thorough literature review will provide a deeper understanding of the current research, practical considerations, and the state-of-the-art in knowledge representation methods, __MDPs__, and student advising programs.

>The use of __Markov Decision Processes (MDPs)__ especially with __Q-learning policy__ in student advising systems represents an innovative approach to improving decision-making and providing personalized recommendations.

> This literature overview explores studies that have utilized MDPs and Q- learning in educational contexts, focusing on the optimization of student advising systems.

-- [Using Reinforcement Learning for Personalized Education" (Year:
2015) Authors: Ramírez, P. P., Geffner, H., & Infantes, G.](https://www.researchgate.net/publication/340564580_Reinforcement_learning_for_personalization_A_systematic_literature_review)

-- [Reinforcement Learning in Educational Technology" (Year: 2016) Authors: Papamitsiou, Z., & Economides, A. A.](https://scholar.google.com/citations?user=gmWRFH8AAAAJ&hl=en)

-- [A Reinforcement Learning Framework for Intelligent Tutoring
Systems" (Year: 2017) Authors: Zouaq, A., Nkambou, R., & Mizoguchi, R.](https://www.researchgate.net/publication/268992454_Advances_in_Intelligent_Tutoring_Systems)

>These references provide a starting point for understanding the application of MDPs and Q-learning in student advising systems and personalized recommendation and help us building our work of Time management advising system

## Concepts Overview

### Q-Learning Algorithm

Q-Learning is a Reinforcement learning policy that will find the next best action, given a current state. It chooses this action at random and aims to maximize the reward.
Q-learning is a model-free, off-policy reinforcement learning that will find the best course of action, given the current state of the agent. Depending on where the agent is in the environment, it will decide the next action to be taken.
The objective of the model is to find the best course of action given its current state. To do this, it may come up with rules of its own or it may operate outside the policy given to it to follow. This means that there is no actual need for a policy, hence we call it off-policy.

<img width="664" alt="Screenshot 2023-07-15 at 17 10 03" src="https://github.com/Yassine-Squalli-Houssaini/Exploring-Decision-Trees-and-MDP-for-Student-Advising-Systems-A-Comparative-Analysis/assets/127676452/01caa87c-b4e9-465a-b2b8-97c27ba75dfd">

### Important Terms in Q-Learning :
1.States: The State, S, represents the current position of an agent in an environment.
2.Action: The Action, A, is the step taken by the agent when it is in a particular state.
3.Rewards: For every action, the agent will get a positive or negative reward.
4.Episodes: When an agent ends up in a terminating state and can’t take a new action.
5.Q-Values: Used to determine how good an Action, A, taken at a particular state, S, is. Q (A, S).
6.Temporal Difference: A formula used to find the Q-Value by using the value of current state and action and previous state and action.

### Bellman Equation

The Bellman Equation is used to determine the value of a particular state and deduce how good it is to be in/take that state. The optimal state will give us the highest optimal value.
The equation is given below. It uses the current state, and the reward associated with that state, along with the maximum expected reward and a discount rate, which determines its importance to the current state, to find the next state of our agent. The learning rate determines how fast or slow, the model will be learning.

![image](https://github.com/Yassine-Squalli-Houssaini/Exploring-Decision-Trees-and-MDP-for-Student-Advising-Systems-A-Comparative-Analysis/assets/127676452/d4004b03-dcb2-4032-83c2-69516934e784)



## MDP Framework Design
The MDP framework incorporates the state space, action space, transition probabilities, and rewards. The state space comprises features such as academic load, current grade average, time of semester, mental state, sleep time, and break time. Actions are defined as changes to study time, break time, sleep time, and social time. Transition probabilities are calculated based on the dataset, representing the likelihood of transitioning between states. Rewards are determined to reflect the desirability of state-action pairs.

<img width="678" alt="Screenshot 2023-07-15 at 17 13 10" src="https://github.com/Yassine-Squalli-Houssaini/Exploring-Decision-Trees-and-MDP-for-Student-Advising-Systems-A-Comparative-Analysis/assets/127676452/5710ee70-0c0e-4e27-bd3c-e3362988ffcb">




## Model evaluation

The model's performance is evaluated using a testing dataset. For each test sample, the model predicts an optimal action based on the state and compares it with the expected action. The accuracy of the model in predicting the correct action is calculated, and the rewards associated with the optimal actions are recorded. The evaluation measures the system's decision-making accuracy and its ability to provide appropriate recommendations.

<img width="453" alt="Screenshot 2023-07-15 at 17 14 58" src="https://github.com/Yassine-Squalli-Houssaini/Exploring-Decision-Trees-and-MDP-for-Student-Advising-Systems-A-Comparative-Analysis/assets/127676452/38586133-3019-45e1-9a91-c3c76144b880">



## Comparison of Benefits
_ In terms of decision optimality, MDPs outperform conventional decision trees. By modeling the sequential nature of student time management decisions and considering long-term rewards, MDPs can generate optimal decision policies that maximize student productivity and academic success. This is in contrast to decision trees, which typically focus on individual decisions without considering their long-term impact.

_ Regarding personalized recommendations, MDPs excel due to their ability to adapt decision policies based on individual student attributes and preferences. By considering factors such as learning style, workload, and personal goals, MDP-based time management advising systems can provide tailored recommendations that cater to the unique needs of each student. Decision trees, on the other hand, offer a more generalized approach and may not account for individual variations.

## Effects of KB Based on MDP on STUDENT SATISFACTION AND ACADEMIC ACHIEVEMENT

Using MDPs for knowledge representation in student time management advising can have positive effects on student satisfaction and academic achievement. MDPs capture the complex relationships between various student attributes (e.g., workload, study habits, social commitments) and their impact on time management decisions. By providing personalized and adaptive recommendations, MDP-based systems can help students optimize their time allocation, reduce stress, and improve overall satisfaction. Furthermore, MDPs can guide students towards effective study strategies, leading to enhanced academic achievement.


<img width="459" alt="Screenshot 2023-07-15 at 17 16 53" src="https://github.com/Yassine-Squalli-Houssaini/Exploring-Decision-Trees-and-MDP-for-Student-Advising-Systems-A-Comparative-Analysis/assets/127676452/efa6336b-6438-4d54-b398-1f8d92ebaaaa">

