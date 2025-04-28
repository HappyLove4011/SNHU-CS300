//============================================================================
// Name        : Project2.cpp
// Author      : Huan Ai
// Version     : 1.0
// Copyright   : Copyright   2023 SNHU COCE
// Description : CS-300 Project 2 Submission, based on BST
//============================================================================


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


// ==================================================================
// COURSE STRUCTURE
// ==================================================================

// Course structure to hold course information

struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// ==================================================================
// BINARY SEARCH TREE IMPLEMENTATION
// ==================================================================

// Node structure for binary search tree

struct Node {
    Course course;
    Node* left;
    Node* right;

    // Constructor
    Node(Course c) {
        course = c;
        left = right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    // Helper function for in-order traversal
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseNumber << ", " << node->course.title << endl;
            inOrder(node->right);
        }
    }

    // Helper function to insert a node
    void insertNode(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course);
        }
        else if (course.courseNumber < node->course.courseNumber) {
            insertNode(node->left, course);
        }
        else if (course.courseNumber > node->course.courseNumber) {
            insertNode(node->right, course);
        }
    }

    // Helper function to search for a course
    Node* searchNode(Node* node, const string& courseNumber) {
        if (node == nullptr) {
            return nullptr;
        }

        if (courseNumber == node->course.courseNumber) {
            return node;
        }
        else if (courseNumber < node->course.courseNumber) {
            return searchNode(node->left, courseNumber);
        }
        else {
            return searchNode(node->right, courseNumber);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Insert a course into the BST
    void Insert(Course course) {
        insertNode(root, course);
    }

    // Search for a course in the BST
    Course* Search(const string& courseNumber) {
        Node* foundNode = searchNode(root, courseNumber);
        if (foundNode != nullptr) {
            return &(foundNode->course);
        }
        return nullptr;
    }

    // Print all courses in alphanumeric order
    void PrintAllCourses() {
        cout << "Here is a sample schedule:" << endl << endl;
        inOrder(root);
        cout << endl;
    }
};

// Function to trim whitespace from a string
// Remove leading/trailing whitespace from string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Function to split a string by delimiter
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    size_t start = 0;
    size_t end = s.find(delimiter);

    // Iterate through delimited values
    while (end != string::npos) {
        token = trim(s.substr(start, end - start));
        if (!token.empty()) {
            tokens.push_back(token);
        }
        start = end + 1;
        end = s.find(delimiter, start);
    }

    // Handle last token after final delimiter
    token = trim(s.substr(start));
    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

// Function to load courses from a file into the BST
void loadCourses(const string& filePath, BinarySearchTree* bst) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filePath << endl;
        return;
    }

    cout << "Loading data from " << filePath << "..." << endl;

    string line;
    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        vector<string> tokens = split(line, ',');

        // At least course number and title should be present
        if (tokens.size() < 2) {
            cout << "Warning: Invalid line format - " << line << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];

        // Add prerequisites if they exist
        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        bst->Insert(course);
    }

    file.close();
    cout << "Data loaded successfully." << endl << endl;
}

// Function to display course information
void displayCourse(Course* course) {
    if (course != nullptr) {
        cout << course->courseNumber << ", " << course->title << endl;
        if (!course->prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course->prerequisites.size(); ++i) {
                cout << course->prerequisites[i];
                if (i != course->prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
    cout << endl;
}

// Function to display the menu
void displayMenu() {
    cout << "Welcome to the course planner." << endl << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl << endl;
}


// ==================================================================
// MAIN PROGRAM
// ==================================================================



int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    string filePath;
    int choice = 0;

    cout << "Welcome to the ABCU Advising Program!" << endl << endl;

    while (choice != 9) {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        // Handle non-integer input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl << endl;
            continue;
        }

        switch (choice) {
        case 1: {
            cin.ignore(); // Clear the newline character
            cout << "Enter file path [default: CS 300 ABCU_Advising_Program_Input]: ";
            getline(cin, filePath);
            if (filePath.empty()) {
                filePath = "CS 300 ABCU_Advising_Program_Input.csv";
            }
            loadCourses(filePath, bst);
            break;
        }
        case 2: {
            bst->PrintAllCourses();
            break;
        }
        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;

            // Convert to uppercase for case-insensitive search
            transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

            Course* course = bst->Search(courseNumber);
            displayCourse(course);
            break;
        }
        case 9: {
            cout << "Thank you for using the course planner!" << endl;
            break;
        }
        default: {
            cout << choice << " is not a valid option." << endl << endl;
            break;
        }
        }
    }

    delete bst;
    return 0;
}