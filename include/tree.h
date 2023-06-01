// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

class Tree {
    struct Node {
        char value;
        std::vector<Node*> children;
    };

    std::vector<char> result;
    Node* root = nullptr;

    void create(std::vector<char> elements, Node* current) {
        for (auto element : elements) {
            if (element == current->value) {
                elements.erase(std::remove(elements.begin(), elements.end(), element),
                               elements.end());
                for (auto childValue : elements) {
                    Node* child = new Node;
                    child->value = childValue;
                    current->children.push_back(child);
                }
            }
        }
        for (auto child : current->children) {
            create(elements, child);
        }
    }

    void generatePermutations(Node* current) {
        if (current->children.empty()) {
            result.push_back(current->value);
            permutations.push_back(result);
            result.clear();
        }
        for (auto child : current->children) {
            result.push_back(current->value);
            generatePermutations(child);
        }
    }

public:
    std::vector<std::vector<char>> permutations;

    explicit Tree(std::vector<char> elements) {
        root = new Node;
        root->value = ' ';
        for (auto element : elements) {
            Node* child = new Node;
            child->value = element;
            root->children.push_back(child);
        }
        for (auto child : root->children) {
            create(elements, child);
            generatePermutations(child);
            result.clear();
        }
    }
};

#endif  // INCLUDE_TREE_H_
