/**
  CS 446 Assignment 3
  metadata.cpp
  Purpose: Contains the function included in class MetaData

  @author Braeden J Richards
*/

#include "metadata.h"

MetaData::MetaData()
{
  return;
}

/**
  Opens file, reads in data and saves it in a linked list

  @params file_name
  @return 0 if successful, 2 if not
*/
int MetaData::LoadMetaFile(std::string file_name)
{
  std::ifstream in_file(file_name.c_str());
  std::string temp_string;

  if(in_file.is_open())
  {
    std::string temp;
    std::getline(in_file, temp, ';');

    // Obtains only the data we need, no extra unneeded characters
    temp.erase(std::remove(temp.begin(), temp.end(), ';'), temp.end());
    temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
    temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());

    data.AddNode(temp);

    //Checks for start of meta data
    for(int i = 0; i < 26; i++)
    {
      temp_string += data.head->data[i];
    }

    // IF NO START OF META DATA FILE
    if(!(temp_string.compare("StartProgramMeta-DataCode:") == 0))
      return 2;
    data.head->data.erase(0,26);

    while(!in_file.eof())
    {
      std::string temp;
      std::getline(in_file, temp, ';');

      // Obtains only the data we need, no extra unneeded characters
      temp.erase(std::remove(temp.begin(), temp.end(), ';'), temp.end());
      temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
      temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());

      data.AddNode(temp);
    }
    node *temp_node = data.head;
    while(temp_node != NULL)
    {
      BreakUpData(temp_node);
      temp_node = temp_node->next;
    }

    return 0;
  }
  else
  {
    return 2;
  }
}

/**
  Prints all data in the linked list to the monitor

  @params void
  @return void
*/
void MetaData::PrintAllData()
{
  node *temp;
  temp = data.head;

  std::cout << "Meta File Data" << std::endl;

  while(temp->next != NULL)
  {
    std::cout << temp->data_code << '{' << temp->data_descriptor << '}' << temp->number_of_cycles << std::endl;
    temp = temp->next;
  }
}

/**
  Breaks the data into smaller pieces in the node

  @params node
  @return void
*/
void MetaData::BreakUpData(node *nodeForThis)
{
  std::string temp;

  //Gets meta data code
  nodeForThis->data_code = nodeForThis->data[0];

  int i = 2;
  while(nodeForThis->data[i] != '}')
  {
    nodeForThis->data_descriptor += nodeForThis->data[i];
    i++;
  }
  i++;

  while(nodeForThis->data[i] != '\0')
  {
    temp += nodeForThis->data[i];
    i++;
  }
  std::stringstream typ_int(temp);
  typ_int >> i;
  nodeForThis->number_of_cycles = i;

  return;
}

/**
  Sorts the data into either FIFO, PS, or SJF

  @params string sort_type
  @return void
*/
void MetaData::SortData(std::string sort_type)
{
  if(sort_type.compare("FIFO") == 0)
  {

  }
  else if(sort_type.compare("PS") == 0)
  {

  }
  else if(sort_type.compare("SJF") == 0)
  {
    
  }

  return;
}
