#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>

// Define a simple structure for nodes
struct Node {
    int visits;
    double value;
    Node* parent;
    std::vector<Node*> children;

    Node(Node* parent = nullptr) : visits(0), value(0), parent(parent) {}

    bool isFullyExpanded() const {
        // Allow more children for better exploration
        return children.size() >= 5; // Allow up to 5 children for better branching
    }

    bool isTerminal() const {
        // Check if node is terminal by limiting depth or checking visits
        return visits >= 10; // Consider a node terminal after 10 visits for simplicity
    }

    void addChild(Node* child) {
        children.push_back(child);
    }
};

// Selection - Uses Upper Confidence Bound for Trees (UCT)
Node* select(Node* root) {
    Node* current = root;
    while (!current->children.empty()) {
        Node* bestChild = nullptr;
        double bestValue = -std::numeric_limits<double>::infinity();
        for (Node* child : current->children) {
            double uctValue = child->value / (child->visits + 1e-6) +
                             1.414 * std::sqrt(std::log(current->visits + 1) / (child->visits + 1e-6)); // Increased exploration coefficient
            if (uctValue > bestValue) {
                bestValue = uctValue;
                bestChild = child;
            }
        }
        current = bestChild;
    }
    return current;
}

// Expansion - Adds a child node
void expand(Node* node) {
    if (!node->isFullyExpanded()) {
        Node* newChild = new Node(node);
        node->addChild(newChild);
    }
}

// Simulation - Simulate a random playthrough
double simulate(Node* node) {
    // Random outcome for simplicity, imagine simulating the actual game here
    return rand() % 2 == 0 ? 1.0 : 0.0;
}

// Backpropagation - Update the value and visits
void backpropagate(Node* node, double reward) {
    Node* current = node;
    while (current != nullptr) {
        current->visits++;
        current->value += reward;
        current = current->parent;
    }
}

// MCTS Function - Combines the steps
Node* MCTS(Node* root, int iterations) {
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < iterations; ++i) {
        Node* selectedNode = select(root);
        if (!selectedNode->isTerminal()) {
            expand(selectedNode);
        }
        Node* expandedNode = selectedNode->children.empty() ? selectedNode : selectedNode->children.back();
        double reward = simulate(expandedNode);
        backpropagate(expandedNode, reward);
    }
    return root;
}

int main() {
    Node* root = new Node();
    MCTS(root, 1000);
    std::cout << "Root visits: " << root->visits << ", value: " << root->value << std::endl;
    for (Node* child : root->children) {
        std::cout << "Child visits: " << child->visits << ", value: " << child->value << std::endl;
    }
    return 0;
}