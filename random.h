#ifndef RANDOM_H_
#define RANDOM_H_
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <time.h>
using std::cout;
using std::endl;
using std::cin;

void readEnemies(std::vector<std::string>& enemyList){
    std::ifstream inFile;
    inFile.open("Enemy_List.txt");
    
    while(!inFile.eof())
    {
        std::string enemyName;
        inFile >> enemyName;
        enemyList.push_back(enemyName);
    }
}

void userParameters(std::vector<std::string>& enemyList, std::vector<std::string>& waveList)
{
    int maxEnemies;
    
    std::vector<std::string> selectedEnemyList;
    // A dictionary that contains the key (the enemy name) and the value (a boolean).
    // These will all be set to false for now. Used to check for duplicates.
    std::map<std::string, bool> enemyMap;

    for(auto& name: enemyList){
        enemyMap[name] = false;
    }

    cout << "Max number of enemies: " << endl;
    cin >> maxEnemies;

   
    // Use numEnemyTypes as an iterator to grab items in enemyList. If there is a duplicate enemy
    // in selectedEnemyList, use a dictionary to check this
    
    srand(time(NULL));
    int numEnemyTypes;
    int index;
    for(int i = 1; i < 102; ++i){
        numEnemyTypes = (rand() % 3) + 1;
        //numEnemyTypes = 1;
        index = 0;
        while(index != (numEnemyTypes)){
            int randomNum = rand() % (enemyList.size() - 1);
            std::string enemy = enemyList[randomNum];
            if(enemyMap[enemy] == false){
                selectedEnemyList.push_back(enemy);
                enemyMap[enemy] = true;
                index++;
            }
        }
        for(auto& name: enemyList){
        enemyMap[name] = false;
        }
       // for(auto& name: selectedEnemyList){
        //cout << name << endl;
        //}

        // Create a loop that continues to append to a string for each enemy in the selectedEnemyList.  
        std::string waveNum = std::to_string(i);
        std::string wave = "+m_WaveData=(WaveNum=" + waveNum + ", Enemies=(";
        std::string completeEnemyString;

        if(numEnemyTypes == 1){
           //int firstEnemySize = (rand() % maxEnemies) + 1;
           int firstEnemySize = 10;
           std::string firstEnemySizeString = std::to_string(firstEnemySize);
           std::string enemy1 = "(EnemyName=" + selectedEnemyList[0] + ", Num=" + firstEnemySizeString + ")))"; 
           completeEnemyString = wave + enemy1;
        }
        else if(numEnemyTypes == 2){
            int firstEnemySize = (rand() % (maxEnemies - 1)) + 1;
            std::string firstEnemySizeString = std::to_string(firstEnemySize);

            int remainingEnemySize = maxEnemies - firstEnemySize;
            std::string remainingEnemySizeString = std::to_string(remainingEnemySize);
            std::string enemy1 = "(EnemyName=" + selectedEnemyList[0] + ", Num=" + firstEnemySizeString + ")";
            std::string enemy2 = ",(EnemyName=" + selectedEnemyList[1] + ", Num=" + remainingEnemySizeString + ")))";
            completeEnemyString = wave + enemy1 + enemy2;
        }
        else if(numEnemyTypes == 3){
            int firstEnemySize = (rand() % (maxEnemies - 2)) + 1;
            std::string firstEnemySizeString = std::to_string(firstEnemySize);
            int remainingEnemySize = maxEnemies - firstEnemySize;
            int secondEnemySize = (rand() % (remainingEnemySize - 1)) + 1;
            remainingEnemySize -= secondEnemySize;
            
            std::string secondEnemySizeStr = std::to_string(secondEnemySize);
            std::string remainingEnemySizeStr = std::to_string(remainingEnemySize);
            std::string enemy1 = "(EnemyName=" + selectedEnemyList[0] + ", Num=" + firstEnemySizeString + ")";
            std::string enemy2 = ",(EnemyName=" + selectedEnemyList[1] + ", Num=" + secondEnemySizeStr + ")";
            std::string enemy3 = ",(EnemyName=" + selectedEnemyList[2] + ", Num=" + remainingEnemySizeStr + ")))";
            completeEnemyString = wave + enemy1 + enemy2 + enemy3;
        }
        else if(numEnemyTypes == 4){
            int firstEnemySize = (rand() % (maxEnemies - 3)) + 1;
            std::string firstEnemySizeString = std::to_string(firstEnemySize);
            cout << "first: " << firstEnemySize << endl;
            int remainingEnemySize = maxEnemies - firstEnemySize;
            int secondEnemySize = (rand() % (remainingEnemySize - 1)) + 1;

            if(firstEnemySize + secondEnemySize == 9){
                if(firstEnemySize > secondEnemySize){
                    firstEnemySize -= 1;
                    remainingEnemySize -= 1;
                }
                else{
                    secondEnemySize -= 1;
                    remainingEnemySize -= 1;
                   }
                int thirdEnemySize = 1;
                int remainingEnemySize = 1;
            }
            else if(firstEnemySize + secondEnemySize == 8){
                int thirdEnemySize = 1;
                int remainingEnemySize = 1;
            }
            cout << "second: " << secondEnemySize << endl;
            remainingEnemySize -= secondEnemySize;
            int thirdEnemySize = (rand() % (remainingEnemySize - 1)) + 1;
            cout << "third: " << thirdEnemySize << endl;
            remainingEnemySize -= thirdEnemySize;

               std::string secondEnemySizeStr = std::to_string(secondEnemySize);
               std::string thirdEnemySizeStr = std::to_string(thirdEnemySize);
               std::string remainingEnemySizeStr = std::to_string(remainingEnemySize);
            std::string enemy1 = "(EnemyName=" + selectedEnemyList[0] + ", Num=" + firstEnemySizeString + ")";
            std::string enemy2 = ",(EnemyName=" + selectedEnemyList[1] + ", Num=" + secondEnemySizeStr + ")";
            std::string enemy3 = ",(EnemyName=" + selectedEnemyList[2] + ", Num=" + thirdEnemySizeStr + ")";
            std::string enemy4 = ",(EnemyName=" + selectedEnemyList[3] + ", Num=" + remainingEnemySizeStr + ")))";
            completeEnemyString = wave + enemy1 + enemy2 + enemy3 + enemy4;
        }
        //cout << completeEnemyString << endl;
        waveList.push_back(completeEnemyString);
        selectedEnemyList.clear();
    }


        
}
        
#endif
