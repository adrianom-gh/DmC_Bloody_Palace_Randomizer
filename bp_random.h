#ifndef BP_RANDOM_H_
#define BP_RANDOM_H_
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <time.h>
#include <algorithm>
#include <random>

using std::cout;
using std::endl;
using std::cin;

// Select a random wave number for each of the six bosses in the game.
// Return a dictionary where:
// key == wave Number
// value == boss name
std::map<int, std::string> selectBosses(std::vector<std::string>& bossList){
    std::vector<int> waveNumList;
    std::map<int, std::string> bossDictionary;
    for(int i = 2; i < 101; ++i){
        waveNumList.push_back(i);
    }
    srand(time(NULL));
    for(int i = 0; i < 5; ++i){
        int key = waveNumList[rand() % waveNumList.size()];
        //remove(waveNumList.begin(), waveNumList.end() - 1, key);
        while(!bossDictionary[key].empty() || key == 15 || key == 35 || key == 55 || key == 75 || key == 95){
            key = waveNumList[rand() % waveNumList.size()];
        }
        if(bossDictionary[key].empty()){
            bossDictionary[key] = bossList[i];
        }
        //cout << "Key: " << key << '\n' << "Value: " << bossList[i] << endl;
        
    }
    return bossDictionary;
}

void readEnemies(std::vector<std::string>& enemyList){
    std::ifstream inFile;
    bool ok = false;
    char choice;
    do{
        cout << "Include colored enemies? y or n" << endl;    
        cin >> choice;
        switch(choice){
            case 'y': case 'Y':
                inFile.open("input/Enemy_List_Colored.txt");
                ok = true;
                break;
            case 'n': case 'N':
                inFile.open("input/Enemy_List_No_Colored.txt");
                ok = true;
                break;
            default:
                cout << "Include colored enemies? y or n" << endl;
                break;
        }
    }while(ok == false);
    
    while(!inFile.eof())
    {
        std::string enemyName;
        inFile >> enemyName;
        enemyList.push_back(enemyName);
        cout << enemyName << endl;
    }
    inFile.close();
}

void readBosses(std::vector<std::string>& bossList){
    std::ifstream inFile;
    inFile.open("input/Boss_List.txt");
    
    while(!inFile.eof())
    {
        std::string bossName;
        inFile >> bossName;
        bossList.push_back(bossName);
    }
    inFile.close();
}

std::string setEnemyWave(int i, std::vector<std::string>& enemyList, std::map<std::string, bool> enemyMap, std::vector<std::string> selectedEnemyList){
    int numEnemyTypes = (rand() % 3) + 1;
    int index = 0;
    cout << enemyList.size() << endl;
    while(index != (numEnemyTypes)){
        int randomNum = rand() % enemyList.size();
        std::string enemy = enemyList[randomNum];
        if(enemyMap[enemy] == false){
            selectedEnemyList.push_back(enemy);
            enemyMap[enemy] = true;
            index++;
        }
    }
    // Reset the enemyMap to false for the next wave of enemies.
    for(auto& name: enemyList){
        enemyMap[name] = false;
    }

    // Create a loop that continues to append to a string for each enemy in the selectedEnemyList.  
    std::string waveNum = std::to_string(i);
    std::string wave = "+m_WaveData=(WaveNum=" + waveNum + ", Enemies=(";
    std::string completeEnemyString;

    int firstEnemySize = (rand() % 5) + 1;
    std::string firstEnemySizeStr = std::to_string(firstEnemySize);

    if(numEnemyTypes == 1){
        std::string enemy1 = "(EnemyName=" + selectedEnemyList[0] + ", Num=" + firstEnemySizeStr + ")))"; 
           completeEnemyString = wave + enemy1;
    }
    else if(numEnemyTypes == 2){
        int secondEnemySize = (rand() % 5) + 1;
        std::string secondEnemySizeStr = std::to_string(secondEnemySize);

        std::string enemy1 = "(EnemyName=" + selectedEnemyList[0] + ", Num=" + firstEnemySizeStr + ")";
        std::string enemy2 = ",(EnemyName=" + selectedEnemyList[1] + ", Num=" + secondEnemySizeStr + ")))";
        completeEnemyString = wave + enemy1 + enemy2;
    }
    else if(numEnemyTypes == 3){
        int secondEnemySize = (rand() % 5) + 1;
        std::string secondEnemySizeStr = std::to_string(secondEnemySize);

        int thirdEnemySize = (rand() % 5) + 1;
        std::string thirdEnemySizeStr = std::to_string(thirdEnemySize);

        std::string enemy1 = "(EnemyName=" + selectedEnemyList[0] + ", Num=" + firstEnemySizeStr + ")";
        std::string enemy2 = ",(EnemyName=" + selectedEnemyList[1] + ", Num=" + secondEnemySizeStr + ")";
        std::string enemy3 = ",(EnemyName=" + selectedEnemyList[2] + ", Num=" + thirdEnemySizeStr + ")))";
        completeEnemyString = wave + enemy1 + enemy2 + enemy3;
    }
    else if(numEnemyTypes == 4){
        int secondEnemySize = (rand() % 5) + 1;
        std::string secondEnemySizeStr = std::to_string(secondEnemySize);

        int thirdEnemySize = (rand() % 5) + 1;
        std::string thirdEnemySizeStr = std::to_string(thirdEnemySize);

        int fourthEnemySize = (rand() % 5) + 1;
        std::string fourthEnemySizeStr = std::to_string(fourthEnemySize);

        std::string enemy1 = "(EnemyName=" + selectedEnemyList[0] + ", Num=" + firstEnemySizeStr + ")";
        std::string enemy2 = ",(EnemyName=" + selectedEnemyList[1] + ", Num=" + secondEnemySizeStr + ")";
        std::string enemy3 = ",(EnemyName=" + selectedEnemyList[2] + ", Num=" + thirdEnemySizeStr + ")";
        std::string enemy4 = ",(EnemyName=" + selectedEnemyList[3] + ", Num=" + fourthEnemySizeStr + ")))";
        completeEnemyString = wave + enemy1 + enemy2 + enemy3 + enemy4;
    }
    return completeEnemyString;
}

std::string setBossWave(int i, std::map<int, std::string>& bossDictionary){
    // Create a loop that continues to append to a string for each enemy in the selectedEnemyList.  
    std::string waveNum = std::to_string(i);
    std::string completeBossString = "+m_WaveData=(WaveNum=" + waveNum + ", Enemies=((EnemyName=" + bossDictionary[i] + ", Num=1)))";
    return completeBossString;
}

void userParameters(std::vector<std::string>& enemyList, std::map<int, std::string>& bossDictionary, std::vector<std::string>& waveList)
{
    //int maxEnemies;
    
    std::vector<std::string> selectedEnemyList;

    // A dictionary that contains the key (the enemy name) and the value (a boolean).
    // These will all be set to false for now. Used to check for duplicates.
    std::map<std::string, bool> enemyMap;

    for(auto& name: enemyList){
        enemyMap[name] = false;
    }

    //cout << "Max number of enemies per wave? " << endl;
    //cin >> maxEnemies;

   
    // Use numEnemyTypes as an iterator to grab items in enemyList. If there is a duplicate enemy
    // in selectedEnemyList, use a dictionary to check this
    
    srand(time(NULL));
    std::string completeEnemyString;
    for(int i = 1; i < 101; ++i){
        if(!bossDictionary[i].empty()){
           completeEnemyString = setBossWave(i, bossDictionary);
        }
        else{
            completeEnemyString = setEnemyWave(i, enemyList, enemyMap, selectedEnemyList);
        }
        
        waveList.push_back(completeEnemyString);
        selectedEnemyList.clear();
    }
    std::string vergilBossString = "+m_WaveData=(WaveNum=101, Enemies=((EnemyName=Vergil, Num=1)))";
    waveList.push_back(vergilBossString);
}

void writeWavesToFile(std::vector<std::string>& waveList){
    std::ofstream outFile;
    outFile.open("DevilGame.ini");
    
    outFile << "[NTEngine.NTDownloadableContentManager]\n";
    outFile << "+DLCManifests=(DLCID=\"BloodyPalace\",bChangesMainMenu=true,bToggledByUser=false)\n\n\n";
    outFile << "[NTGameFramework.NTPlayerStart]\n";
    outFile << "+CharacterDescriptors=(FriendlyName=\"BloodyPalaceDante\", TargetPlayerControllerClass=\"DevilGame.DvPlayerController_Dante\", Tags=\"BloodyPalace; Normal; NoCoat; WhiteHairPatch; WhiteHair; Costume\", ModCompatibility=\"Dante\", ReplacementPlayerControllerClass=\"DevilGame.DvPlayerController_Dante\", ReplacementCharacterTemplate=\"Dante_Archetypes.DanteCharacterTemplate\")\n";
    outFile << "+CharacterMods=(FriendlyName=\"BPDanteGameplay\", Tags=\"BloodyPalace\", ModCompatibility=\"Dante\", ApplicationOrder=-10, TargetPropertyPath=\"Gameplay\", ReplacementObjectPath=\"Dante_BP_Archetypes.DanteGameplayTemplate_BP\")\n\n\n";
    outFile << "[BPalaceDLC.DVBloodyPalaceParam]\n";
    for(auto& wave: waveList){
        outFile << wave << '\n';
    }
    
    outFile << '\n';
    outFile << "[BPalaceDLC.DVGFxContainer_MissionRankScreen_BP]\n";
    outFile << ("CompleteTime_RankSSS=3600\n" "CompleteTime_RankSS=3000\n" "CompleteTime_RankS=2400\n" "CompleteTime_RankA=1800\n" "CompleteTime_RankB=900\n" "CompleteTime_RankC=360\n" "CompleteTime_RankD=120\n\n\n");
    outFile << ("CompleteStyle_RankSSS=6500000\n" "CompleteStyle_RankSS=6000000\n"  "CompleteStyle_RankS=5000000\n"
    "CompleteStyle_RankA=3750000\n" "CompleteStyle_RankB=2500000\n" "CompleteStyle_RankC=1500000\n" "CompleteStyle_RankD=800000\n\n\n");
    outFile << ("OrbBonus_RankSSS=10000\n" "OrbBonus_RankSS=5000\n" "OrbBonus_RankS=2500\n" "OrbBonus_RankA=1250\n" 
"OrbBonus_RankB=600\n" "OrbBonus_RankC=300\n" "OrbBonus_RankD=150\n\n\n");
    outFile << ("LevelsCompleted_RankSSS=51\n" "LevelsCompleted_RankSS=45\n" "LevelsCompleted_RankS=40\n" "LevelsCompleted_RankA=30\n" "LevelsCompleted_RankB=20\n" "LevelsCompleted_RankC=10\n" "LevelsCompleted_RankD=0\n\n\n");
    outFile << ("CompleteFinal_RankSSS=52028800\n" "CompleteFinal_RankSS=42021000\n" "CompleteFinal_RankS=30014400\n" "CompleteFinal_RankA=20009000\n" "CompleteFinal_RankB=12003600\n" "CompleteFinal_RankC=4501080\n" "CompleteFinal_RankD=1600240");
    outFile.close();  
}

void menu(std::vector<std::string>& enemyList, std::vector<std::string>& bossList, std::vector<std::string>& waveList){
    cout << "//////////////////////////////////////////\n"; 
    cout << "// KnightNC's Super Cool BP Randomizer! //\n";
    cout << "///////////// (version 1.12) /////////////\n";
    cout << "//////////////////////////////////////////\n\n"; 

    readEnemies(enemyList);
    readBosses(bossList);
    std::map<int, std::string> bossDictionary = selectBosses(bossList);
    userParameters(enemyList, bossDictionary, waveList);
    writeWavesToFile(waveList);
}

#endif
