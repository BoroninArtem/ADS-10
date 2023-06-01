// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

class Tree {
    struct Node {
        char value;
        std::vector<Node*> subscriber;
    };

    std::vector<char> result;
    Node* root = nullptr;

    void create(std::vector<char> elem, Node* cur) {
        for (auto i : elem) {
            if (i == cur->value) {
                elem.erase(std::remove(elem.begin(),
                elem.end(), i), elem.end());
                for (auto subValue : elem) {
                    Node* sub = new Node;
                    sub->value = subValue;
                    cur->subscriber.push_back(sub);
                }
            }
        }
        for (auto sub : cur->subscriber) {
            create(elem, sub);
        }
    }

    void generateperm(Node* cur) {
        if (cur->subscriber.empty()) {
            result.push_back(cur->value);
            perm.push_back(result);
            result.clear();
        }
        for (auto sub : cur->subscriber) {
            result.push_back(cur->value);
            generateperm(sub);
        }
    }

 public:
    std::vector<std::vector<char>> perm;

    explicit Tree(std::vector<char> elem) {
        root = new Node;
        root->value = ' ';
        for (auto i : elem) {
            Node* sub = new Node;
            sub->value = i;
            root->subscriber.push_back(sub);
        }
        for (auto sub : root->subscriber) {
            create(elem, sub);
            generateperm(sub);
            result.clear();
        }
    }
};

#endif  // INCLUDE_TREE_H_
