using Random

mutable struct Node
    visits::Int
    value::Float64
    parent::Union{Node, Nothing}
    children::Vector{Node}

    Node(parent::Union{Node, Nothing}=nothing) = new(0, 0.0, parent, Node[])
end

function is_fully_expanded(node::Node)
    return length(node.children) >= 5
end

function is_terminal(node::Node)
    return node.visits >= 10
end

function add_child(node::Node, child::Node)
    push!(node.children, child)
end

# Selection - Uses Upper Confidence Bound for Trees (UCT)
function select(node::Node)
    current = node
    while !isempty(current.children)
        best_child = nothing
        best_value = -Inf
        for child in current.children
            uct_value = (child.value / (child.visits + 1e-6) +
                         1.414 * sqrt(log(current.visits + 1) / (child.visits + 1e-6)))
            if uct_value > best_value
                best_value = uct_value
                best_child = child
            end
        end
        current = best_child
    end
    return current
end

# Expansion - Adds a child node
function expand(node::Node)
    if !is_fully_expanded(node)
        new_child = Node(node)
        add_child(node, new_child)
    end
end

# Simulation - Simulate a random playthrough
function simulate(node::Node)
    return rand(Bool) ? 1.0 : 0.0
end

# Backpropagation - Update the value and visits
function backpropagate(node::Node, reward::Float64)
    current = node
    while current !== nothing
        current.visits += 1
        current.value += reward
        current = current.parent
    end
end

# MCTS Function - Combines the steps
function MCTS(root::Node, iterations::Int)
    Random.seed!()
    for _ in 1:iterations
        selected_node = select(root)
        if !is_terminal(selected_node)
            expand(selected_node)
        end
        expanded_node = isempty(selected_node.children) ? selected_node : selected_node.children[end]
        reward = simulate(expanded_node)
        backpropagate(expanded_node, reward)
    end
    return root
end

# Main execution
function main()
    root = Node()
    MCTS(root, 1000)
    println("Root visits: ", root.visits, ", value: ", root.value)
    for child in root.children
        println("Child visits: ", child.visits, ", value: ", child.value)
    end
end

main()