#ifndef GRIDNODE_H
#define GRIDNODE_H
#include "a.h"

/**
 * @brief The GridState class represents a position in a rectangular grid.
 */
class GridState
{
public:
  GridState(int x, int y);

  int getX() const;

  int getY() const;

  bool operator<(const GridState& other) const;

  bool operator==(const GridState& other) const;

private:
  int m_x;
  int m_y;
};

/**
 * @brief The GridNode class represents a node used for navigation on a rectangular grid.
 */
class GridNode :  public AI::Node<GridState, int>
{
public:
  ~GridNode();

  GridNode(const GridState& state, const unsigned char* board, int boardWidth, int boardHeight);

private:
  std::vector<AI::Node<GridState, int>::SharedPtr> getChildren() const;

  AI::Node<GridState, int>*  clone() const;

  int calculateAndGetG(const GridState& parentState, int parentG) const;

  int calculateAndGetH(const GridState& goalState) const;

  unsigned char boardAt(int x, int y) const;

  const unsigned char* const m_board;
  int m_boardWidth;
  int m_boardHeight;
};

#endif // GRIDNODE_H
