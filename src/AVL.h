
////
//// Created by Giuliana Silva on 10/2/24.
////
//
#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H


#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <unordered_set>
#include <set>


struct Node{
    //node attributes
    std::string name;
    std::string ufid;
    int balanceFactor;
    unsigned int leftHeight;
    unsigned int rightHeight;
    Node* left;
    Node* right;


    Node(std::string name, std::string ufid){
        this->name = name;
        this->ufid = ufid;
        this->left = nullptr;
        this->right = nullptr;
        this->balanceFactor = 0;
        this->leftHeight = 0;
        this->rightHeight = 0;
    }
};


//contains functions
class AVLTree{

private:

    Node* root;
    std::unordered_set<std::string> trackUFIDs;
    int nodeCount = 0;
    Node* insertHelper(Node* newNode, Node* currentRoot);

    bool checkName(const std::string& name);
    bool checkUFID(const std::string& ufid);
    int getHeight(Node* node);
    Node* rotateLeft(Node *node);
    Node* rotateRight(Node *node);
    Node* rotateLeftRight(Node *node);
    Node* rotateRightLeft(Node *node);
    void inorderHelper(Node* currentRoot, std::vector<std::string>& v);

    // method that was not in last submission that caused code to not compile
    void inorderHelperUFID(Node* currentRoot, std::vector<std::string>& v);

    std::string returnUFID(const std::string& name);
    bool UFIDinSet(std::string ufid);
    int getBalanceFactor(Node* root);
    void preorderHelper(Node* currentRoot, std::vector<std::string>& v);
    void postorderHelper(Node* currentRoot, std::vector<std::string>& v);
    Node* searchIDHelper(Node* currentRoot, std::string& ufid);
    void searchNameHelper(Node* currentRoot, const std::string& name, std::vector<std::string>& IDs);
    void destructorHelper(Node*& currentPtr);
    Node* removeHelper(Node* currentRoot, std::string &ufid );
    Node* getMin(Node* currentRoot);

    //manditory functions public
public:

    AVLTree(){
        root = nullptr;
    }

    ~AVLTree();

    void insertNAMEID(std::string& name, std::string& ufid);
    void searchID(std::string& ufid);
    void searchNAME(const std::string& name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeID(std::string& ufid);
    void removeInorderN(int N);







};

#endif //PROJECT1_AVL_H
