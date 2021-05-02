#include "bp_random.h"
#include <windows.h>

int main()
{
    //char filename[] = "\\DmC Devil May Cry\\DevilGame\\Config\\DevilGame.txt";
    //char fullFileName[MAX_PATH];

    //GetFullPathName(filename, MAX_PATH, fullFileName, nullptr);

    //cout << fullFileName << endl;

    std::vector<std::string> enemyList;
    std::vector<std::string> bossList;
    std::vector<std::string> waveList;
    readEnemies(enemyList);
    readBosses(bossList);
    std::map<int, std::string> bossDictionary = selectBosses(bossList);
    userParameters(enemyList, bossDictionary, waveList);
    writeWavesToFile(waveList);

    //getBossWaveNumbers(bossList);
}
