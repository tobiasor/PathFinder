#include <iostream>
#include "findpath.h"

void testRun1();
void testRun2();
void testRun3();

int main()
{
  testRun1();
  testRun2();
  testRun3();

  return 0;
}

void testRun1()
{
  int mapWidth = 4;
  int mapHeight = 3;
  unsigned char pMap[] =
  {1, 1, 1, 1,
   0, 1, 0, 1,
   0, 1, 1, 1};
  int pOutBuffer[12];
  int nNumSteps = FindPath(0, 0, 1, 2, pMap, mapWidth, mapHeight, pOutBuffer, 12);

  std::cout << "Num steps: " << nNumSteps << std::endl;

  for(int i = 0; i < nNumSteps; ++i)
  {
    pMap[pOutBuffer[i]] = 2;
  }
  int index = 0;
  for(int i = 0; i < mapHeight; ++i)
  {
    for(int j = 0; j < mapWidth; ++j)
    {
      std::cout << (int)pMap[index];
      index++;
    }
    std::cout << std::endl;
  }
}

void testRun2()
{
  int mapWidth = 3;
  int mapHeight = 3;

  unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
  int pOutBuffer[7];
  int nNumSteps = FindPath(2, 0, 0, 2, pMap, mapWidth, mapHeight, pOutBuffer, 7);

  std::cout << "Num steps: " << nNumSteps << std::endl;

  for(int i = 0; i < nNumSteps; ++i)
  {
    pMap[pOutBuffer[i]] = 2;
  }
  int index = 0;
  for(int i = 0; i < mapHeight; ++i)
  {
    for(int j = 0; j < mapWidth; ++j)
    {
      std::cout << (int)pMap[index];
      index++;
    }
    std::cout << std::endl;
  }
}

void testRun3()
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
  int pOutBuffer[100];
  int nNumSteps = FindPath(0, 0, 9, 6, pMap, mapWidth, mapHeight, pOutBuffer, 100);

  std::cout << "Num steps: " << nNumSteps << std::endl;
  for(int i = 0; i < nNumSteps; ++i)
  {
    pMap[pOutBuffer[i]] = 2;
  }
  int index = 0;
  for(int i = 0; i < mapHeight; ++i)
  {
    for(int j = 0; j < mapWidth; ++j)
    {
      std::cout << (int)pMap[index];
      index++;
    }
    std::cout << std::endl;
  }
}
