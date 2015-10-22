#include <cmath>
#include <iostream>
#include "a.h"
#include "gridnode.h"
#include "findpath.h"
int main()
{
  {
    int mapHeight = 3;
    int mapWidth = 4;
    unsigned char pMap[] =
    {1, 1, 1, 1,
     0, 1, 0, 1,
     0, 1, 1, 1};
    int pOutBuffer[12];
    int nNumSteps = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

    std::cout << "Num steps: " << nNumSteps << std::endl;

    for(int i = 0; i < nNumSteps; ++i) {
      pMap[pOutBuffer[i]] = 2;
    }
    int index = 0;
    for(int i = 0; i < mapHeight; ++i) {
      for(int j = 0; j < mapWidth; ++j) {
        std::cout << (int)pMap[index];
        index++;
      }
      std::cout << std::endl;
    }
  }
  {
    int mapHeight = 3;
    int mapWidth = 3;

    unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
    int pOutBuffer[7];
    int nNumSteps = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);

    std::cout << "Num steps: " << nNumSteps << std::endl;

    for(int i = 0; i < nNumSteps; ++i) {
      pMap[pOutBuffer[i]] = 2;
    }
    int index = 0;
    for(int i = 0; i < mapHeight; ++i) {
      for(int j = 0; j < mapWidth; ++j) {
        std::cout << (int)pMap[index];
        index++;
      }
      std::cout << std::endl;
    }
  }
  {
    int mapWidth = 10;
    int mapHeight = 10;
    unsigned char pMap[] =
    {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
      0, 1, 0, 0, 0, 1, 1, 1, 1, 1,
      1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 0, 1, 1, 1, 1, 0, 0,
      1, 1, 1, 0, 1, 1, 1, 0, 0, 1,
      1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };
    int pOutBuffer[256];
    int nNumSteps = FindPath(0, 0, 9, 6, pMap, mapWidth, mapHeight, pOutBuffer, 256);

    std::cout << "Num steps: " << nNumSteps << std::endl;
    for(int i = 0; i < nNumSteps; ++i) {
      pMap[pOutBuffer[i]] = 2;
    }
    int index = 0;
    for(int i = 0; i < mapHeight; ++i) {
      for(int j = 0; j < mapWidth; ++j) {
        std::cout << (int)pMap[index];
        index++;
      }
      std::cout << std::endl;
    }
  }
  return 0;
}

