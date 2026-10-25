// Created by Giuliana Silva on 10/2/24.
//

#include "AVL.h"


//checks if name input is valid
bool AVLTree::checkName(const std::string& name){
    return std::regex_match(name, std::regex("^[a-zA-Z\\s]+$"));
}

//checks if ID input is valid
bool AVLTree::checkUFID(const std::string& ufid){
    return std::regex_match(ufid, std::regex("^[0-9]{8}$"));
}


int AVLTree::getHeight(Node* node) {
    if (!node) return 0;
    return std::max(node->leftHeight, node->rightHeight) + 1;
}


int AVLTree::getBalanceFactor(Node* currentRoot){
    if(currentRoot == nullptr) {
        return 0;
    }
    else {
        return getHeight(currentRoot->left) - getHeight(currentRoot->right);
    }
}

//roatation functions
//code retrived from Stepik Solutions in Canvas Files Module5_solutions.pdf
Node* AVLTree::rotateLeft(Node* node){
    Node* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;

    //updating heights
    node->leftHeight = getHeight(node->left);
    node->rightHeight = getHeight(node->right);
    rightChild->leftHeight = getHeight(rightChild->left);
    rightChild->rightHeight = getHeight(rightChild->right);

    return rightChild;
}

//code retrived from Stepik Solutions in Canvas Files Module5_solutions.pdf
Node* AVLTree::rotateRight(Node* node){
    //your code here?
    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;

    //updating heights
    node->leftHeight = getHeight(node->left);
    node->rightHeight = getHeight(node->right);
    leftChild->leftHeight = getHeight(leftChild->left);
    leftChild->rightHeight = getHeight(leftChild->right);

    return leftChild;
}

//code retrived from Stepik Solutions in Canvas Files Module5_solutions.pdf
Node* AVLTree::rotateLeftRight(Node* node){
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

//code inspired by Stepik Solutions in Canvas Files Module5_solutions.pdf
Node* AVLTree::rotateRightLeft(Node* node){
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}




//Based off code and Pseudocode provided in slides 4 - Balanced Trees.pdf found in Canvas Files.
Node* AVLTree::insertHelper(Node* newNode, Node* currentRoot) {
    if (currentRoot == nullptr) {
        nodeCount++;
        return newNode;
    }


    if (newNode->ufid > currentRoot->ufid) {
        currentRoot->right = insertHelper(newNode, currentRoot->right);
    } else if (newNode->ufid < currentRoot->ufid) {
        currentRoot->left = insertHelper(newNode, currentRoot->left);
    } else {
        std::cout << "unsuccessful" << std::endl;
        return currentRoot;
    }


    currentRoot->leftHeight = getHeight(currentRoot->left);
    currentRoot->rightHeight = getHeight(currentRoot->right);

    // get balance factor
    int balFactor = getBalanceFactor(currentRoot);
    currentRoot->balanceFactor = balFactor;

    // left-heavy
    if (balFactor > 1) {
        if (getBalanceFactor(currentRoot->left) < 0) {
            // left-right
            currentRoot->left = rotateLeft(currentRoot->left);
        }
        //left-left
        return rotateRight(currentRoot);
    }
    //right-heavy
    if (balFactor < -1) {
        //right-left
        if (getBalanceFactor(currentRoot->right) > 0) {
            currentRoot->right = rotateRight(currentRoot->right);
        }
        //right-right
        return rotateLeft(currentRoot);
    }
    return currentRoot;
}




void AVLTree::insertNAMEID(std::string& name, std::string& ufid) {
    if (checkName(name) && checkUFID(ufid)) {
        if (trackUFIDs.insert(ufid).second) {
            Node *newNode = new Node(name, ufid);
            this->root = insertHelper(newNode, (this->root));
            std::cout << "successful" << std::endl;

        } else {
            //sets do not allow duplicate values, so if .second returned
            //false the ufid entered already exists in the set and in the tree.
            std::cout << "unsuccessful" << std::endl;
        }
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

//code for preorder, postorder, and inorder functions all
// loosely inspired by Stepik Solutions in Canvas Files Module5_solutions.pdf
void AVLTree::inorderHelper(Node* currentRoot, std::vector<std::string>& v) {
    if (currentRoot == nullptr)
        return;

    inorderHelper(currentRoot->left, v);
    v.push_back(currentRoot->name);
    inorderHelper(currentRoot->right, v);
}

void AVLTree::inorderHelperUFID(Node* currentRoot, std::vector<std::string>& v) {
    if (currentRoot == nullptr)
        return;

    inorderHelper(currentRoot->left, v);
    v.push_back(currentRoot->ufid);
    inorderHelper(currentRoot->right, v);
}

void AVLTree::printInorder() {
    std::vector<std::string> v;
    inorderHelper(this->root, v);

    if (!v.empty()) {
        for (size_t i = 0; i < v.size(); ++i) {
            std::cout << v[i];
            if (i < v.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}


void AVLTree::preorderHelper(Node* currentRoot, std::vector<std::string>& v) {
    if (currentRoot == nullptr)
        return;

    v.push_back(currentRoot->name);
    preorderHelper(currentRoot->left, v);
    preorderHelper(currentRoot->right, v);
}

void AVLTree::printPreorder() {
    std::vector<std::string> v;
    preorderHelper(this->root, v);

    if (!v.empty()) {
        for (size_t i = 0; i < v.size(); ++i) {
            std::cout << v[i];
            if (i < v.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

void AVLTree::postorderHelper(Node* currentRoot, std::vector<std::string>& v) {
    if (currentRoot == nullptr)
        return;

    postorderHelper(currentRoot->left, v);
    postorderHelper(currentRoot->right, v);
    v.push_back(currentRoot->name);
}

void AVLTree::printPostorder() {
    std::vector<std::string> v;
    postorderHelper(this->root, v);

    if (!v.empty()) {
        for (size_t i = 0; i < v.size(); ++i) {
            std::cout << v[i];
            if (i < v.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

void AVLTree::destructorHelper(Node*& currentPtr){
    if (currentPtr != nullptr){
        destructorHelper(currentPtr->left);
        destructorHelper(currentPtr->right);
        delete currentPtr;
        currentPtr = nullptr;
    }
}

void AVLTree::printLevelCount() {
    if (this->root == nullptr) {
        std::cout << "0" << std::endl;
        return;
    }else{
        int levelCount = std::max(root->leftHeight, root->rightHeight) + 1;
        std::cout << levelCount << std::endl;
    }
}

Node* AVLTree::searchIDHelper(Node* currentRoot, std::string& ufid){
    if (currentRoot == nullptr) {
        return currentRoot;
    }

    if(currentRoot->ufid == ufid){
        return currentRoot;
    }
    if(currentRoot->ufid < ufid){
        return searchIDHelper(currentRoot->right, ufid);
    }
    else{
        return searchIDHelper(currentRoot->left, ufid);

    }
}

void AVLTree::searchID(std::string& ufid){
    if(!checkUFID(ufid)){
        std::cout << "unsuccessful" << std::endl;
        return;
    }else{
        Node* node = searchIDHelper(this->root, ufid);
        if(node == nullptr){
            std::cout << "unsuccessful" << std::endl;
            return;
        }else{

            std::cout << node->name << std::endl;
        }
    }
}

void AVLTree::searchNameHelper(Node* currentRoot, const std::string& name, std::vector<std::string>& IDs) {
    if (currentRoot == nullptr) {
        return;
    }
    if (currentRoot->name == name) {
        IDs.push_back(currentRoot->ufid);
    }
    searchNameHelper(currentRoot->left, name, IDs);
    searchNameHelper(currentRoot->right, name, IDs);
}

std::string AVLTree:: returnUFID(const std::string& name) {
    std::string ID;
    std::vector<std::string> IDs;
    searchNameHelper(this->root, name, IDs);

//    if (IDs.empty()) {
//        std::cout << "unsuccessful" << std::endl;
//
//    } else {
        for (int i = 0; i < IDs.size(); ++i) {
            ID = IDs[i];
            //std::cout << IDs[i] << std::endl;
        }
        return ID;
    //}

}

void AVLTree::searchNAME(const std::string& name) {

    std::vector<std::string> IDs;
    searchNameHelper(this->root, name, IDs);


    if (IDs.empty()) {
        std::cout << "unsuccessful" << std::endl;

    } else {
        for (int i = 0; i < IDs.size(); ++i) {
            returnUFID(IDs[i]);
            std::cout << IDs[i] << std::endl;
        }
    }
}




Node* AVLTree::getMin(Node* currentRoot){
    Node* currentNode = currentRoot;

    while(currentNode->left != nullptr){
        currentNode = currentNode->left;
    }
    return currentNode;

}

Node* AVLTree::removeHelper(Node* currentRoot, std::string& ufid) {
    if (currentRoot == nullptr) {
        return currentRoot;
    }

    if (ufid < currentRoot->ufid) {
        currentRoot->left = removeHelper(currentRoot->left, ufid);
    } else if (ufid > currentRoot->ufid) {
        currentRoot->right = removeHelper(currentRoot->right, ufid);
    } else {
        // case 1 no children
        if (currentRoot->left == nullptr && currentRoot->right == nullptr) {
            delete currentRoot;
            return nullptr;
        }
            // case 2 one child
        else if (currentRoot->left == nullptr) {
            Node* temp = currentRoot->right;
            delete currentRoot;
            return temp;
        }
            // case 3 two children
        else if (currentRoot->right == nullptr) {
            Node* temp = currentRoot->left;
            delete currentRoot;
            return temp;
        }

        else {
            Node* successor = getMin(currentRoot->right);
            currentRoot->name = successor->name;
            currentRoot->ufid = successor->ufid;
            currentRoot->right = removeHelper(currentRoot->right, successor->ufid);
        }
    }

    return currentRoot;
}

bool AVLTree::UFIDinSet(std::string ufid){
    return (trackUFIDs.find(ufid) != trackUFIDs.end());
}

void AVLTree::removeID(std::string& ufid){

    if(!checkUFID(ufid) || !UFIDinSet(ufid)){

        std::cout << "unsuccessful" << std::endl;
        return;
    }
    this->root = removeHelper(this->root, ufid);
    trackUFIDs.erase(ufid);
    std::cout<<"successful" <<std::endl;

}



void AVLTree::removeInorderN(int N) {
    std::vector<std::string> v;
    inorderHelperUFID(this->root, v);

    if(v.empty()) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    if (N >= 0 && N < v.size()) {
        std::string nameToRemove = v[N];

        std::string ufidToRemove = returnUFID(nameToRemove);
        removeID(ufidToRemove);
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}
