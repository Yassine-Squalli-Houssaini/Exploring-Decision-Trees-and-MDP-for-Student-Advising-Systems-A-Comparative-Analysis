#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <limits>

// Struct for storing data records
struct Data {
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
};

// Struct for representing a node in the decision tree
struct TreeNode {
    std::string attribute;
    std::map<std::string, TreeNode*> children;
    std::string predictedAction;
};

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


// Function to read the CSV file and populate the data
std::vector<Data> readCSV(const std::string& filename) {
    std::vector<Data> data;
    std::ifstream file(filename);
    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;

        Data record;

        std::getline(ss, item, ',');
        record.student_id = std::stoi(item);

        std::getline(ss, item, ',');
        record.semester = std::stoi(item);

        std::getline(ss, item, ',');
        record.academic_load = std::stof(item);

        std::getline(ss, item, ',');
        record.current_grade_average = std::stof(item);

        std::getline(ss, item, ',');
        record.time_of_semester = std::stoi(item);

        std::getline(ss, item, ',');
        record.mental_state = item;

        std::getline(ss, item, ',');
        record.study_time = std::stof(item);

        std::getline(ss, item, ',');
        record.break_time = std::stof(item);

        std::getline(ss, item, ',');
        record.sleep_time = std::stof(item);

        std::getline(ss, item, ',');
        record.social_time = std::stof(item);

        std::getline(ss, item, ',');
        record.actions = item;

        data.push_back(record);
    }

    return data;
}

// Function to split the data into train and test sets
std::pair<std::vector<Data>, std::vector<Data>> trainTestSplit(const std::vector<Data>& data, float testRatio) {
    std::vector<Data> trainData;
    std::vector<Data> testData;

    int testSize = static_cast<int>(data.size() * testRatio);
    for (int i = 0; i < data.size(); ++i) {
        if (i < testSize) {
            testData.push_back(data[i]);
        } else {
            trainData.push_back(data[i]);
        }
    }

    return {trainData, testData};
}

// Function to calculate accuracy of the decision tree
float calculateAccuracy(const std::vector<Data>& testData, TreeNode* root) {
    int correctPredictions = 0;

    for (const Data& data : testData) {
        TreeNode* currentNode = root;
        while (!currentNode->children.empty()) {
            const std::string& attributeValue = data.actions;
            if (currentNode->children.count(attributeValue) == 0) {
                // No matching child node, use the most common action
                break;
            }
            currentNode = currentNode->children[attributeValue];
        }
        if (currentNode->predictedAction == data.actions) {
            ++correctPredictions;
        }
    }

    return static_cast<float>(correctPredictions) / testData.size();
}


// Function to calculate entropy
float calculateEntropy(float positiveProbability, float negativeProbability) {
    if (positiveProbability == 0.0 || negativeProbability == 0.0) {
        return 0.0;
    }

    float entropy = -positiveProbability * std::log2(positiveProbability)
                    - negativeProbability * std::log2(negativeProbability);
    return entropy;
}

// Function to calculate information gain
float calculateInformationGain(const std::vector<Data>& data, const std::string& attribute) {
    std::map<std::string, int> attributeValueCountMap;
    std::map<std::string, int> attributeValueActionCountMap;

    int totalCount = data.size();

    for (const Data& d : data) {
        attributeValueCountMap[d.actions]++;
        attributeValueActionCountMap[d.actions]++;
    }

    float parentEntropy = calculateEntropy(static_cast<float>(attributeValueCountMap["Increase Break Time"]) / totalCount,
                                           static_cast<float>(attributeValueCountMap["Increase Study Time"]) / totalCount);

    float weightedEntropySum = 0.0;
    for (const auto& pair : attributeValueActionCountMap) {
        float attributeProbability = static_cast<float>(attributeValueCountMap[pair.first]) / totalCount;
        float positiveProbability = static_cast<float>(pair.second) / attributeValueCountMap[pair.first];
        float negativeProbability = 1.0 - positiveProbability;

        float entropy = calculateEntropy(positiveProbability, negativeProbability);
        weightedEntropySum += attributeProbability * entropy;
    }

    return parentEntropy - weightedEntropySum;
}

// Function to get the best attribute for splitting
std::string getBestAttribute(const std::vector<Data>& data, const std::vector<std::string>& attributes) {
    float maxInformationGain = -std::numeric_limits<float>::max();
    std::string bestAttribute;

    for (const std::string& attribute : attributes) {
        float informationGain = calculateInformationGain(data, attribute);
        if (informationGain > maxInformationGain) {
            maxInformationGain = informationGain;
            bestAttribute = attribute;
        }
    }

    return bestAttribute;
}

// Function to get the most common action in the data
std::string getMostCommonAction(const std::vector<Data>& data) {
    std::map<std::string, int> actionCountMap;
    for (const Data& d : data) {
        actionCountMap[d.actions]++;
    }

    int maxCount = 0;
    std::string mostCommonAction;
    for (const auto& pair : actionCountMap) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostCommonAction = pair.first;
        }
    }

    return mostCommonAction;
}

// Function to build the decision tree
TreeNode* buildDecisionTree(const std::vector<Data>& data, const std::vector<std::string>& attributes) {
    if (data.empty()) {
        return nullptr;
    }

    std::string commonAction = getMostCommonAction(data);
    if (attributes.empty()) {
        TreeNode* leafNode = new TreeNode;
        leafNode->predictedAction = commonAction;
        return leafNode;
    }

    std::string bestAttribute = getBestAttribute(data, attributes);
    std::vector<std::string> remainingAttributes = attributes;
    remainingAttributes.erase(std::remove(remainingAttributes.begin(), remainingAttributes.end(), bestAttribute), remainingAttributes.end());

    TreeNode* rootNode = new TreeNode;
    rootNode->attribute = bestAttribute;

    std::map<std::string, std::vector<Data>> attributeValueDataMap;
    for (const Data& d : data) {
        attributeValueDataMap[d.actions].push_back(d);
    }

    for (const auto& pair : attributeValueDataMap) {
        std::string attributeValue = pair.first;
        const std::vector<Data>& attributeData = pair.second;

        TreeNode* childNode = buildDecisionTree(attributeData, remainingAttributes);
        rootNode->children[attributeValue] = childNode;
    }

    return rootNode;
}

// Function to delete the decision tree
void deleteDecisionTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    for (auto& pair : node->children) {
        deleteDecisionTree(pair.second);
    }

    delete node;
}

int main() {
    std::vector<Data> data = readCSV("dataaa.csv");

    // Split the data into train and test sets
    float testRatio = 0.2; // 20% of the data will be used for testing
    std::pair<std::vector<Data>, std::vector<Data>> trainTest = trainTestSplit(data, testRatio);
    std::vector<Data> trainData = trainTest.first;
    std::vector<Data> testData = trainTest.second;

    // Define the attributes for building the decision tree
    std::vector<std::string> attributes = {"IncreaseStudyTime", "DecreaseStudyTime", "DecreaseBreakTime", "IncreaseBreakTime", "IncreaseSleepTime"};

    // Build the decision tree
    TreeNode* root = buildDecisionTree(trainData, attributes);

    // Calculate accuracy on test data
    float accuracy = calculateAccuracy(testData, root);
    std::cout << "Accuracy: " << accuracy << std::endl;

    // Cleanup
    deleteDecisionTree(root);

    return 0;
}
