#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

// Enum for possible actions
enum Action {
    IncreaseStudyTime,
    DecreaseStudyTime,
    DecreaseBreakTime,
    IncreaseBreakTime,
    IncreaseSleepTime
};

// Struct for states
struct State {
    int student_id;
    int semester;
    float academic_load;
    float current_grade_average;
    int time_of_semester;
    std::string mental_state;
    float study_time;
    float break_time;
    float sleep_time;
    float social_time;
    std::string actions;

    bool operator<(const State& other) const {
        if (current_grade_average != other.current_grade_average) {
            return current_grade_average < other.current_grade_average;
        } else {
            return study_time < other.study_time;
        }
    }
};

// Function to calculate the reward
float calculateReward(State& state, Action action) {
    float reward = 0.0;
    switch (action) {
        case IncreaseStudyTime:
            reward = 0.1 * state.current_grade_average;
            break;
        case DecreaseStudyTime:
            reward = -0.1 * state.current_grade_average;
            break;
        case DecreaseBreakTime:
            reward = -0.1 * state.current_grade_average;
            break;
        case IncreaseBreakTime:
            reward = 0.1 * state.current_grade_average;
            break;
        case IncreaseSleepTime:
            reward = 0.05 * state.current_grade_average;
            break;
    }
    return reward;
}

// Function to calculate transition probabilities
std::map<State, float> calculateTransitionProbabilities(State& state, Action action) {
    std::map<State, float> transitionProbabilities;

    State nextState = state;
    switch (action) {
        case IncreaseStudyTime:
            nextState.study_time += 0.5;
            break;
        case DecreaseStudyTime:
            nextState.study_time -= 0.5;
            break;
        case DecreaseBreakTime:
            nextState.break_time -= 0.5;
            break;
        case IncreaseBreakTime:
            nextState.break_time += 0.5;
            break;
        case IncreaseSleepTime:
            nextState.sleep_time += 0.5;
            break;
    }

    transitionProbabilities[nextState] = 1.0;

    return transitionProbabilities;
}

// Function to perform an action
State performAction(State& state, Action action) {

    std::map<State, float> transitionProbabilities = calculateTransitionProbabilities(state, action);

    // Choose next state based on transition probabilities
    float randNum = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);  // generate a random float between 0 and 1
    float sum = 0;
    for (auto& [nextState, probability] : transitionProbabilities) {
        sum += probability;
        if (randNum <= sum) {
            return nextState;
        }
    }

    return state;  // return current state if no transition occurred
}

// Function to select an action based on current state and Q-table
Action selectAction(State& state, std::map<std::pair<State, Action>, float>& Q_table) {

    float maxQ = -std::numeric_limits<float>::max();
    Action bestAction = IncreaseStudyTime;  // default action

    for (Action action : {IncreaseStudyTime, DecreaseStudyTime, DecreaseBreakTime, IncreaseBreakTime, IncreaseSleepTime}) {
        float q = Q_table[{state, action}];
        if (q > maxQ) {
            maxQ = q;
            bestAction = action;
        }
    }

    return bestAction;
}

// Function to get max Q value for a state
float getMaxQValue(State& state, std::map<std::pair<State, Action>, float>& Q_table) {
    float maxQ = -std::numeric_limits<float>::max();

    for (Action action : {IncreaseStudyTime, DecreaseStudyTime, DecreaseBreakTime, IncreaseBreakTime, IncreaseSleepTime}) {
        float q = Q_table[{state, action}];
        if (q > maxQ) {
            maxQ = q;
        }
    }

    return maxQ;
}

// Helper function to check if a string is a valid float
bool isValidFloat(const std::string& s) {
    std::istringstream iss(s);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}

// Helper function to check if a string is a valid integer
bool isValidInteger(const std::string& s) {
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
 
    char * p;
    strtol(s.c_str(), &p, 10);
 
    return (*p == 0);
}

// Function to convert mental_state to numerical representation
int convertToNumericalMentalState(const std::string& str) {
    if (str == "Good") {
        return 2; // Assigning "Good" as 2
    } else if (str == "Average") {
        return 1; // Assigning "Average" as 1
    } else if (str == "Poor") {
        return 0; // Assigning "Poor" as 0
    } else {
        return -1; // Return -1 for unknown values
    }
}

// Function to read CSV
std::vector<State> readCSV(std::string filename) {
    std::vector<State> states;
    std::ifstream file(filename);

    std::string line;
    // Skip the header row
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;

        State state;

        // Parse student_id
        std::getline(ss, item, ',');
        if (isValidInteger(item)) {
            state.student_id = std::stoi(item);
        } else {
            std::cerr << "Error: could not convert '" << item << "' to an integer\n";
            // Handle error
            continue;
        }

        // Parse semester
        std::getline(ss, item, ',');
        if (isValidInteger(item)) {
            state.semester = std::stoi(item);
        } else {
            std::cerr << "Error: could not convert '" << item << "' to an integer\n";
            // Handle error
            continue;
        }

        // Parse academic_load
        std::getline(ss, item, ',');
        if (isValidFloat(item)) {
            state.academic_load = std::stof(item);
        } else {
            std::cerr << "Error: could not convert '" << item << "' to a float\n";
            // Handle error
            continue;
        }

        // Parse current_grade_average
        std::getline(ss, item, ',');
        if (isValidFloat(item)) {
            state.current_grade_average = std::stof(item);
        } else {
            std::cerr << "Error: could not convert '" << item << "' to a float\n";
            // Handle error
            continue;
        }

        // Parse time_of_semester
        std::getline(ss, item, ',');
        if (isValidInteger(item)) {
            state.time_of_semester = std::stoi(item);
        } else {
            std::cerr << "Error: could not convert '" << item << "' to an integer\n";
            // Handle error
            continue;
        }

        // Parse mental_state
        std::getline(ss, item, ',');
        state.mental_state = item;

        // Parse study_time
        std::getline(ss, item, ',');
        if (isValidFloat(item)) {
            state.study_time = std::stof(item);
        } else {
            std::cerr << "Error: could not convert '" << item << "' to a float\n";
            // Handle error
            continue;
        }

        // Parse break_time
        std::getline(ss, item, ',');
        if (isValidFloat(item)) {
            state.break_time = std::stof(item);
        } else {
            std::cerr << "Error: could not convert '" << item << "' to a float\n";
            // Handle error
            continue;
        }

        // Parse sleep_time
        std::getline(ss, item, ',');
        if (isValidFloat(item)) {
            state.sleep_time = std::stof(item);
        } else {
            std::cerr << "Error: could not convert '" << item << "' to a float\n";
            // Handle error
            continue;
        }

        // Parse social_time
        std::getline(ss, item, ',');
        if (isValidFloat(item)) {
            state.social_time = std::stof(item);
        } else {
            std::cerr << "Error: could not convert '" << item << "' to a float\n";
            // Handle error
            continue;
        }

        // Parse actions
        std::getline(ss, item, ',');
        state.actions = item;

        states.push_back(state);
    }

    return states;
}

// Function to get the "correct" action for a state
Action getCorrectAction(State& state) {
    if (state.actions == "Decrease Study Time") {
        return DecreaseStudyTime;
    } else if (state.actions == "Decrease Break Time") {
        return DecreaseBreakTime;
    } else if (state.actions == "Increase Sleep Time") {
        return IncreaseSleepTime;
    } else {
        return IncreaseStudyTime;
    }
}

// Function to predict an action for a state using the Q-table
Action predictAction(State& state, std::map<std::pair<State, Action>, float>& Q_table) {
    return selectAction(state, Q_table);  // use the policy derived from the Q-table
}

int main() {
    srand((unsigned int)time(NULL));  // seed random number generator

    std::vector<State> states = readCSV("dataaa.csv");

    // Split the data into training and test sets (80% for training, 20% for testing)
    std::vector<State> trainingSet(states.begin(), states.begin() + static_cast<int>(0.8 * states.size()));
    std::vector<State> testSet(states.begin() + static_cast<int>(0.8 * states.size()), states.end());

    std::map<std::pair<State, Action>, float> Q_table;

    // Initialize Q-table
    for (State& state : trainingSet) {
        for (Action action : {IncreaseStudyTime, DecreaseStudyTime, DecreaseBreakTime, IncreaseBreakTime, IncreaseSleepTime}) {
            Q_table[{state, action}] = 0.0;
        }
    }

    float alpha = 0.5;  // learning rate
    float gamma = 0.9;  // discount factor

    // Run Q-learning
    for (int episode = 0; episode < 1000; ++episode) {  // number of episodes
        State state = trainingSet[0];  // start state

        for (int timestep = 0; timestep < 1000; ++timestep) {  // number of timesteps
            Action action = selectAction(state, Q_table);
            State new_state = performAction(state, action);
            float reward = calculateReward(state, action);

            float old_value = Q_table[{state, action}];
            float max_new_value = getMaxQValue(new_state, Q_table);

            Q_table[{state, action}] = old_value + alpha * (reward + gamma * max_new_value - old_value);

            state = new_state;
        }
    }

    // Calculate accuracy on the test set
    int numCorrect = 0;
    for (State& state : testSet) {
        Action correctAction = getCorrectAction(state);
        Action predictedAction = predictAction(state, Q_table);
        if (correctAction == predictedAction) {
            ++numCorrect;
        }
    }
    float accuracy = static_cast<float>(numCorrect) / (testSet.size());

    std::cout << "Accuracy: " << accuracy << std::endl;

    return 0;
}
