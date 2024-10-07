import math
import random

class Node:
    def __init__(self, parent=None):
        self.visits = 0
        self.value = 0.0
        self.parent = parent
        self.children = []

    def is_fully_expanded(self):
        # Allow up to 5 children for better branching
        return len(self.children) >= 5

    def is_terminal(self):
        # Consider a node terminal after 10 visits for simplicity
        return self.visits >= 10

    def add_child(self, child):
        self.children.append(child)

# Selection - Uses Upper Confidence Bound for Trees (UCT)
def select(node):
    current = node
    while current.children:
        best_child = None
        best_value = -float('inf')
        for child in current.children:
            uct_value = (child.value / (child.visits + 1e-6) +
                         1.414 * math.sqrt(math.log(current.visits + 1) / (child.visits + 1e-6)))
            if uct_value > best_value:
                best_value = uct_value
                best_child = child
        current = best_child
    return current

# Expansion - Adds a child node
def expand(node):
    if not node.is_fully_expanded():
        new_child = Node(parent=node)
        node.add_child(new_child)

# Simulation - Simulate a random playthrough
def simulate(node):
    # Random outcome for simplicity, imagine simulating the actual game here
    return 1.0 if random.randint(0, 1) == 0 else 0.0

# Backpropagation - Update the value and visits
def backpropagate(node, reward):
    current = node
    while current is not None:
        current.visits += 1
        current.value += reward
        current = current.parent

# MCTS Function - Combines the steps
def MCTS(root, iterations):
    random.seed()
    for _ in range(iterations):
        selected_node = select(root)
        if not selected_node.is_terminal():
            expand(selected_node)
        expanded_node = selected_node if not selected_node.children else selected_node.children[-1]
        reward = simulate(expanded_node)
        backpropagate(expanded_node, reward)
    return root

if __name__ == "__main__":
    root = Node()
    MCTS(root, 1000)
    print(f"Root visits: {root.visits}, value: {root.value}")
    for child in root.children:
        print(f"Child visits: {child.visits}, value: {child.value}")