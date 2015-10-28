#include "findpath.h"
#include "a.h"
#include "gridnode.h"



int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize) {

  //Setup the start and goal (target)
  GridNode::SharedPtr start = GridNode::SharedPtr(new GridNode(GridState(nStartX, nStartY), pMap, nMapWidth, nMapHeight));
  GridNode::SharedPtr goal = GridNode::SharedPtr(new GridNode(GridState(nTargetX, nTargetY), pMap, nMapWidth, nMapHeight));

  //Run the path finder and put the data into the paradox.kattis format.
  int numSteps = 0;
  for(GridState gs : AI::A<GridState, int>::findPath(start, goal)) {
    if(numSteps > nOutBufferSize) {
      return -1;
    }
    if(numSteps > 0) {
      pOutBuffer[numSteps-1] = (gs.getX() + gs.getY() * nMapWidth);
    }
    numSteps++;
  }
  return numSteps-1;
}

