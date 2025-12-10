//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.
   Students must manage storage, pointers, and dynamic allocation.

   Requirements:
   1. Templated Tree class.
   2. Nodes stored dynamically.
   3. Each node has:
      - id
      - data
      - vector of children pointers
   4. Students must prevent memory leaks.
   5. Students must create createRoot, addNode, findNode, print functions, etc.
*/


template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    // Constructor
    Node(const string &nodeID, const U &value) {
    id = nodeID;
    data = value;
    }
};

template <typename T>
class Tree {
private:
    Node<T>* root;

public:
    Tree() {
        // Initialize root pointer to nullptr
        root = nullptr;
    }

    void createRoot(const string &id, const T &value) {
        // Allocate memory, assign id, assign data, set as root
        // Check if root already exists
        if (root != nullptr) {
            return;
        }

        // Create new node and set as root
        root = new Node<T>(id, value);
    }

    void addNode(const string &parentID, const string &childID, const T &value) {
        // Find parent node
        Node<T>* parent = findNode(parentID);
        if (parent == nullptr) {
            return;
        }
        // Check if child exists (Supports repeated children under multiple parents
        Node<T>* child = findNode(childID);
        if (child != nullptr) {
            // Link to existing child
            parent->children.push_back(child);
        } else {
            // Create new child node
            Node<T>* newChild = new Node<T>(childID, value);
            parent->children.push_back(newChild);
        }
    }

    Node<T>* findNode(const string &id) {
        // Use DFS or BFS to search tree
        if (root == nullptr) return nullptr;

        // DFS Stack
        vector<Node<T>*> stack;
        stack.push_back(root);

        while (!stack.empty()) {
            Node<T>* current = stack.back();
            stack.pop_back();

            if (current->id == id) {
                return current;
            }

            // Add children to stack
            for (Node<T>* child : current->children) {
                stack.push_back(child);
            }
        }

        return nullptr;
    }

    void printAll() {
        // Print entire structure in readable form
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }

        vector<Node<T>*> visited;
        vector<Node<T>*> stack;
        stack.push_back(root);

        while (!stack.empty()) {
            Node<T>* current = stack.back();
            stack.pop_back();

            // Check if already visited to handle shared children
            bool alreadyVisited = false;
            for (Node<T>* v : visited) {
                if (v == current) {
                    alreadyVisited = true;
                    break;
                }
            }

            if (alreadyVisited) continue;

            visited.push_back(current);

            // Print current node
            cout << "Node " << current->id << ": " << current->data << endl;

            // Print children
            if (current->children.empty()) {
                cout << "  Child -> (none)" << endl;
            } else {
                for (Node<T>* child : current->children) {
                    cout << "  Child -> " << child->id << endl;
                    stack.push_back(child);
                }
            }
            cout << endl;
        }
    }

    void playGame() {
        // 1. Start at the root node.
        if (root == nullptr) {
            cout << "Game cannot start - tree is empty!" << endl;
            return;
        }

        cout << "\n===== Begin Adventure =====\n" << endl;

        Node<T>* current = root;

        while (current != nullptr) {
            // 2. Display the current node's text.
            cout << current->data << endl;

            // Check if reached an ending
            // 5. Move to the selected child and continue until a node has no children.
            if (current->children.empty()) {
                // 6. Print an ending message.
                cout << "\n=== The End ===" << endl;
                cout << "Your adventure concludes here." << endl;
                break;
            }

            // 3. Display numbered options for each child.
            cout << "\nChoose your next action:" << endl;
            for (size_t i = 0; i < current->children.size(); i++) {
                cout << "  " << (i + 1) << ". Continue to path " << (i + 1) << endl;
            }

            // 4. Ask the user which path to take.
            cout << "\nEnter choice (1-" << current->children.size() << "): ";
            int choice;
            cin >> choice;

            // Validate input
            if (choice < 1 || choice > static_cast<int>(current->children.size())) {
                cout << "Invalid choice! Please try again." << endl;
                continue;
            }

            // 5. Move to the selected child and continue until a node has no children.
            current = current->children[choice - 1];
            cout << endl;
        }

        cout << "\n===== Adventure Complete =====\n" << endl;
    }

    ~Tree() {
    // Free all allocated memory
    if (root == nullptr) return;

    vector<Node<T>*> visited;
    vector<Node<T>*> stack;
    stack.push_back(root);

    while (!stack.empty()) {
        Node<T>* current = stack.back();
        stack.pop_back();

        // Check if already visited (shared children)
        bool wasVisited = false;
        for (Node<T>* v : visited) {
            if (v == current) {
                wasVisited = true;
                break;
            }
        }

        if (wasVisited) continue;

        visited.push_back(current);

        // Add children to stack
        for (Node<T>* child : current->children) {
            stack.push_back(child);
        }

        // Delete current node
        delete current;
    }
}

};

#endif //FA25EC3_TREE_H