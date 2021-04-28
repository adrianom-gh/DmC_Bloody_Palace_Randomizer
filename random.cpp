#include "random.h"

int main()
{
    std::vector<std::string> enemyList;
    std::vector<std::string> waveList;
    readEnemies(enemyList);
    userParameters(enemyList, waveList);
}
