
template <typename State, typename HeuristicsType>
void A<State, HeuristicsType>::clear()
{
  //Prority ques cannot be cleared. Dont ask me why.
  while(!m_openPrioQue.empty())
  {
    m_openPrioQue.pop();
  }

  m_openMap.clear();
  m_closedMap.clear();
  m_path.clear();
}


template <typename State, typename HeuristicsType>
void A<State, HeuristicsType>::begin(
    typename Node<State, HeuristicsType>::SharedPtr start,
    typename Node<State, HeuristicsType>::SharedPtr goal)
{
  m_start = start;
  m_goal = goal;

  //Clear the open and closed containers and the path.
  clear();

  typename Node<State, HeuristicsType>::SharedPtr startClone = typename Node<State, HeuristicsType>::SharedPtr(start->clone());

  //Set the heurisic for the start Node.
  startClone->setG(start->calculateAndGetG(nullptr, start));
  startClone->setH(start->calculateAndGetH(nullptr, goal));
  startClone->setF(start->getG() + start->getH());

  //place start on open because we need one Node to be traversed at the begining.
  m_openMap.insert(startClone);
  m_openPrioQue.push(startClone);
}

template <typename State, typename HeuristicsType>
bool A<State, HeuristicsType>::next()
{
  if(!m_openMap.empty())
  {
    //Delete the entries marked for removal in the priority que.
    for(std::size_t i=0; i < m_openPrioQue.size(); ++i)
    {
      if(m_openPrioQue.top()->isDeleted())
      {
        m_openPrioQue.pop();
        ++i;
      }
    }
    //Get the best candidate. It will always be at the top
    //on openPrioQue because it is sorted on: f = g + h.
    typename Node<State, HeuristicsType>::SharedPtr current = m_openPrioQue.top();
    //Store the candidate on closed because we are about to expand the Node.
    m_closedMap.insert(current);

    m_openPrioQue.pop();
    m_openMap.erase(current);

    //If we found a match then return the path.
    if(current->getState() == m_goal->getState())
    {
      ///////////////////////////////////////////
      //Eureka!!!!!
      ///////////////////////////////////////////
      while(current)
      {
        m_path.push_front(current->getState());
        current = current->getParent();
      }
      return true;
    }
    else
    {
      //Expand the current Node's children.
      for(typename Node<State, HeuristicsType>::SharedPtr child : current->getChildren())
      {
        //Setup the child's properties.
        child->setParent(current);
        child->setG(child->calculateAndGetG(current, m_start));
        child->setH(child->calculateAndGetH(current, m_goal));
        child->setF(child->getG() + child->getH());

        //Search for the child in the open and closed containers.
        typename NodeSet::iterator inClosedMapIt = m_closedMap.find(child);
        typename NodeSet::iterator inOpenMapIt = m_openMap.find(child);

        //If the child is in open.
        if(inOpenMapIt != m_openMap.end())
        {
          //The child is not better then the node in open.
          //We call continue because we do not want the child to be
          //stored in the open vector.
          if((*inOpenMapIt)->getG() <= child->getG())
          {
            continue;
          }
        }
        //If the child is in closed.
        if(inClosedMapIt != m_closedMap.end())
        {
          //The child is not better then the node in closed.
          //We call continue because we do not want the child to be
          //moved to the open vector.
          if((*inClosedMapIt)->getG() <= child->getG())
          {
            continue;
          }
        }
        //Erase the child from the open and closed vectors
        //and add it to the open vector.
        if(inOpenMapIt != m_openMap.end())
        {
          //It is not possible to remove an object from a std::priority_queue without traversing the whole thing.
          //Because of that the node have a state that tells it to remove itself from the que. Not nice
          //but i prefer this solusion over writing my own priority que for now.
          (*inOpenMapIt)->setIsDeleted(true);
          m_openMap.erase(inOpenMapIt);
        }
        if(inClosedMapIt != m_closedMap.end())
        {
          m_closedMap.erase(inClosedMapIt);
        }
        m_openMap.insert(child);
        m_openPrioQue.push(child);
      }
    }
  }
  else
  {
    //We did not find a path but the search is over.
    return true;
  }
  //We have not found a solution to our problem yet.
  return false;
}
