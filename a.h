#ifndef A_H
#define A_H

#include <deque>
#include <queue>
#include <set>
#include <memory>

namespace AI
{

/**
    The Node is used by the path finding algorithm. A Node Must be able to expand it's children with the
    'getChildren' method. this means that it must return all the Nodes to where it is possible to walk from
    this Node.

    The Node must also be able to evaluate it's heuristic value. The heuristic must be calculated in the
    'calculateAndGetG' and 'calculateAndGetH' methods.

    The 'State' template parameter is the actual Node data. In a path finding search the State will be
    the agent's position. In a 8-puzzle search the 'State' will be the actual board.
    The State must implement the < operator and the == operator.

    The 'HeuristicsType' template parameter is the data type used for the heuristics calculations.
    */
template <typename State, typename HeuristicsType>
class Node {
public:
  template<class T, class U> friend class A;

  typedef std::shared_ptr<Node<State, HeuristicsType>> SharedPtr;

  virtual ~Node() {}

  bool operator==(Node<State, HeuristicsType>::SharedPtr other) const {
    return this->getState() == other->getState();
  }

  ///A node must be clonable.
  virtual Node*  clone() const = 0;

  ///Returns the sub Nodes.
  virtual std::vector<typename Node::SharedPtr> getChildren() const = 0;

  ///Returns the node's State.
  virtual State getState() const { return m_state; }

  ///Returns the node's depth in the tree. May be used to calculate g in some cases.
  int getDepth() const { return m_depth; }

  ///Returns the cost from start to this.
  HeuristicsType getG() const { return m_g; }

  ///Returns the cost between this and the goal.
  HeuristicsType getH() const { return m_h; }

  ///Returns the heuristic value.
  HeuristicsType getF() const { return m_f; }

protected:
  Node(const State& state)
    : m_state(state)
    , m_f(0.0)
    , m_h(0.0)
    , m_g(0.0)
    , m_depth(0)
    , m_isDeleted(false) {}

  ///The cost from start to this.
  virtual HeuristicsType calculateAndGetG(const State& parentState, HeuristicsType parentG) const = 0;

  ///The cost between this and the goal.
  virtual HeuristicsType calculateAndGetH(const State& goalState) const = 0;

  ///Returns the parent Node. Where this Node came from.
  Node::SharedPtr  getParent() const { return m_parent; }

  void setG(HeuristicsType g) { m_g = g;}
  void setH(HeuristicsType h) { m_h = h;}
  void setF(HeuristicsType f) { m_f = f;}
private:


  ///The actual state of the node.
  /**
      The state is typically a board in a board game, a triangle in a navmesh
      or maybe a position in a rectangular grid.
      */
  State m_state;
  ///f(n)=g(n)+h(n)
  HeuristicsType m_f;
  ///The heuristic estimate of the cost of going from n to the goal.
  HeuristicsType m_h;
  ///The cost of n from the start Node.
  HeuristicsType m_g;
  ///The depth of this node in the tree.
  int m_depth;
  ///Pointer to the parent node.
  typename Node::SharedPtr  m_parent;
  /**
      This is a state that tells the node to remove itself from a priority que.
      It is an ugly construct but needed because I refuse to write my own priority que
      that supports destruction of individual elements.
      */
  bool m_isDeleted;


  void setParent(typename Node::SharedPtr p) { if(!p) return; m_parent = p; m_depth = p->getDepth() + 1; }
  void setIsDeleted(bool isDeleted) { m_isDeleted = isDeleted; }
  bool isDeleted() const { return m_isDeleted; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
    Algorithm A is a heuristic search algorithm whose primary use is to find a
    path between two Nodes. The algorithm will work as long as it
    is possible to expand a current Node into it's sub Nodes and
    if it is possible to evaluate a heuristic value for the Nodes (f(n)=g(n)+h(n)).
    Where g(n) is cost of n from the start Node and h(n) is the heuristic
    estimate of the cost of going from n to the goal.

    If algoritm A is used with a h(n) which is less than or equal to
    the cost of the minimal path from n to the goal, the algorithm
    will find the shortest path and is called A*.

    The search is semi-asyncronyous. The user first call the method 'begin'.
    This call will tell the path finder that we want to find a path between
    two Nodes. Next the user have to run the method 'next' until it returns
    true. When the method returns true we can call 'getPath'. This makes it
    possible to calculate paths without stalling a simulation/game-loop.

    It would be easy to call 'next' for multiple agents in parallel during
    one simulation tick.
    */
template <typename State, typename HeuristicsType>
class A
{
  ///Used for priority que insertion.
  struct PrioQueCompare
  {
    bool operator()(typename Node<State, HeuristicsType>::SharedPtr a, typename Node<State, HeuristicsType>::SharedPtr b)
    {
      return a->getF() > b->getF();
    }
  };

  struct SetCompare
  {
    bool operator()(typename Node<State, HeuristicsType>::SharedPtr a, typename Node<State, HeuristicsType>::SharedPtr b)
    {
      return a->getState() < b->getState();
    }
  };

  typedef std::set<typename Node<State, HeuristicsType>::SharedPtr, SetCompare> NodeSet;
  typedef std::priority_queue<typename Node<State, HeuristicsType>::SharedPtr, std::deque<typename Node<State, HeuristicsType>::SharedPtr>, PrioQueCompare > NodePriorityQue;

public:
  A() {}
  void clear();

  ///Method that starts an iterative path finding.
  /**
      After Begin is called then call Next until it returns true. When
      Next returns true the a path is stored in m_path.
      */
  void begin(
      typename Node<State, HeuristicsType>::SharedPtr start,
      typename Node<State, HeuristicsType>::SharedPtr goal);

  ///Method that finds a path iterative.
  /**
      Next try to find the path declared with 'begin'.
      A path is found when 'next' returns true. 'next' must be called untill it returns true.
      */
  bool next();

  ///Returns the path.
  const std::deque< State >& getPath() const { return m_path; }

  ///Returns true if a path exist.
  bool havePath() const { return (m_path.size() > 0); }

  /**
    Helper function for getting a path between start and goal in one call.
   */
  static std::deque<State> findPath(typename Node<State, HeuristicsType>::SharedPtr start, typename Node<State, HeuristicsType>::SharedPtr goal) {
    A<State, HeuristicsType> a;

    a.begin(start, goal);
    while(!a.next()) {}
    return a.getPath();
  }

private:
  A(const A&);
  A& operator=(const A&);

  typename Node<State, HeuristicsType>::SharedPtr m_start;
  typename Node<State, HeuristicsType>::SharedPtr m_goal;
  std::deque<State> m_path;
  NodePriorityQue m_openPrioQue;
  NodeSet m_openMap;
  NodeSet m_closedMap;
};


#include "a.inl"
}

#endif
