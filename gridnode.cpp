#include "gridnode.h"


GridState::GridState(int x, int y)
  : m_x(x)
  , m_y(y) { }

int GridState::getX() const {
  return m_x;
}

int GridState::getY() const {
  return m_y;
}

bool GridState::operator<(const GridState& other) const {
  if(m_x != other.m_x)
    return m_x < other.m_x;
  return m_y < other.m_y;
}

bool GridState::operator==(const GridState& other) const {
  if(m_x != other.m_x)
    return false;
  if(m_y != other.m_y)
    return false;
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

GridNode::~GridNode() { }

GridNode::GridNode(const GridState& state, const unsigned char* board, int boardWidth, int boardHeight)
  : AI::Node<GridState, int>(state)
  , m_board(board)
  , m_boardWidth(boardWidth)
  , m_boardHeight(boardHeight) { }

std::vector<AI::Node<GridState, int>::SharedPtr> GridNode::getChildren() const {
  //Populates the cildren vector with the possible moves from this state.
  //The nodes are allocated using the new keyword. A memory pool might be a
  //better choice. I do not want to use a third party library and dont have
  //the time to implement my own at the moment.
  std::vector<AI::Node<GridState, int>::SharedPtr> children;

  int x = this->getState().getX();
  int y = this->getState().getY();

  //Try step to the right.
  if(boardAt(x+1, y)) {
     children.push_back(AI::Node<GridState, int>::SharedPtr(new GridNode(GridState(x+1, y), m_board, m_boardWidth, m_boardHeight)));
  }

  //Try step to the left.
  if(boardAt(x-1, y)) {
    children.push_back(AI::Node<GridState, int>::SharedPtr(new GridNode(GridState(x-1, y), m_board, m_boardWidth, m_boardHeight)));
  }

  //Try step to the south.
  if(boardAt(x, y+1)) {
    children.push_back(AI::Node<GridState, int>::SharedPtr(new GridNode(GridState(x, y+1), m_board, m_boardWidth, m_boardHeight)));
  }

  //Try step to the north.
  if(boardAt(x, y-1)) {
    children.push_back(AI::Node<GridState, int>::SharedPtr(new GridNode(GridState(x, y-1), m_board, m_boardWidth, m_boardHeight)));
  }
  return children;
}

AI::Node<GridState, int>*  GridNode::clone() const {
  return new GridNode(*this);
}

int GridNode::calculateAndGetG(const GridState& , int parentG) const {
  return parentG + 1;
}

int GridNode::calculateAndGetH(const GridState& goalState) const {
  //Manhattan distance
  int dx =  abs(this->getState().getX() - goalState.getX());
  int dy =  abs(this->getState().getY() - goalState.getY());
  return dx + dy;
}

unsigned char GridNode::boardAt(int x, int y) const {
  if(x < 0 || x >= m_boardWidth) {
    return 0;
  }
  if(y < 0 || y >= m_boardHeight) {
    return 0;
  }
  return m_board[y*m_boardWidth + x];
}
