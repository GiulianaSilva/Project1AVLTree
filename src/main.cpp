
//std::quoted(name) learned from https://en.cppreference.com/w/cpp/io/manip/quoted
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "AVL.h"


int main() {
    AVLTree *gatorAVL = new AVLTree();
    int commandCount;
    std::cin >> commandCount;
    std::cin.ignore();
    std::vector<std::string> commands;


    for (int i = 0; i < commandCount; ++i) {
        std::string input;
        std::getline(std::cin, input);
        commands.push_back(input);

    }

    for (const auto& command: commands) {
        std::istringstream iss(command);
        std::string commandType;
        iss >> commandType;


        if (commandType == "insert") {
            std::string name;
            std::string ufid;

            if (iss >> std::quoted(name) >> ufid) {
                gatorAVL->insertNAMEID(name, ufid);


            } else {
                std::cout << "unsuccessful" << std::endl;
            }



        } else if (commandType == "remove") {
            std::string argument;
            iss>>argument;
            gatorAVL->removeID(argument);




        }if (commandType == "search") {
            std::string argument;
            iss>>argument;


            if (!argument.empty() && argument.front() == '"' && argument.back() == '"') {
                // Remove  quotes
                argument = argument.substr(1, argument.length() - 2);
                gatorAVL->searchNAME(argument);
            } else {
                //seach using ufid
                gatorAVL->searchID(argument);
            }
        }

        if (commandType == "printInorder") {
            gatorAVL->printInorder();

        }
        if (commandType == "printPreorder") {
            gatorAVL->printPreorder();

        }
        if (commandType == "printPostorder") {
            gatorAVL->printPostorder();

        }
        if (commandType == "printLevelCount") {
            gatorAVL->printLevelCount();

        }
        else if (commandType == "removeInorder") {
            std::string argument;
            iss>>argument;
            gatorAVL->removeInorderN(stoi(argument));
        }





    }

    return 0;

}
