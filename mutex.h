/**
	CS 446 Assignment 3
	mutex.h
	Purpose: Contains the class for the mutex lock object

	@author Braeden J Richards
*/

class Mutex{
public:
  Mutex(); //Constructor

  bool LockMutex(); //Attempts to lock the mutex
  bool UnlockMutex(); //Attempts to unlock the mutex
  bool IsLocked(); //Checks if mutex is available
private:
  bool m_mutex; //Holds whether the mutex is locked or not. True == not locked
};

/**
	Constructor of a Mutex object. Sets the m_mutex variable to true

	@params void
	@return void
*/
Mutex::Mutex()
{
  m_mutex = true;

  return;
}

/**
	Locks the Mutex Object by changing the m_mutex variable to false

	@params void
	@return true if mutex is lockable aka is currently unclocked
*/
bool Mutex::LockMutex()
{
  if(m_mutex)
  {
    m_mutex = false;
    return true;
  }
  else
    return false;
}

/**
	Unlocks the Mutex Object by changing the m_mutex variable to true

	@params void
	@return true if the mutex is successfully unlocked
*/
bool Mutex::UnlockMutex()
{
  if(!m_mutex)
  {
    m_mutex = true;
    return true;
  }
  else
    return false;
}

/**
	Locks the Mutex Object by changing the m_mutex variable to false

	@params void
	@return true if the mutex is locked. False if unlocked
*/
bool Mutex::IsLocked()
{
  if(m_mutex)
    return false;
  else
    return true;
}
