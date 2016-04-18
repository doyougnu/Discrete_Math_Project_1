/*******************************************************************************
 * Tools.cpp
 *
 * Tanner Gower
 * 3/4/2016
 *
 * An object with primarily static "helper" functions. It's basically full
 * of basic algorithms to do basic stuff that I don't want to write over
 * and over.
 *
*******************************************************************************/

#include "Tools.h"
#include <sstream>

using namespace std;

// ------------------------------------------------------------------------
// sortNonIncreasing: sorts a vector of ints in descending order or
//                    non-increasing order
// data: array to sort
// size: size of the input array
// ------------------------------------------------------------------------
void Tools::sortNonIncreasing(vector<int> &data, int size)
{
  int max,
      temp;

  for (int i = 0; i < size - 1; i++)
  {
    // Start with the first element as the maximum
    max = i;

    // Loop through elements and check for an element greater than max
    for (int j = i + 1; j < size; j++)
      if (data[j] > data[max])
        max = j;

    // If the maximum element is NOT what we started with, we must swap
    if (max != i)
    {
      temp = data[i];
      data[i] = data[max];
      data[max] = temp;
    }
  }
}

// ------------------------------------------------------------------------
// sortNonDecreasing: sorts a vector of ints in ascending order or
//                    non-decreasing order
// data: array to sort
// size: size of the input array
// ------------------------------------------------------------------------
void Tools::sortNonDecreasing(vector<int> &data, int size)
{
  int max,
      temp;

  for (int i = 0; i < size - 1; i++)
  {
    // Start with the first element as the maximum
    max = i;

    // Loop through elements and check for an element less than max
    for (int j = i + 1; j < size; j++)
      if (data[j] < data[max])
        max = j;

    // If the maximum element is NOT what we started with, we must swap
    if (max != i)
    {
      temp = data[i];
      data[i] = data[max];
      data[max] = temp;
    }
  }
}

// ------------------------------------------------------------------------
// onlyZeros: Loops through an array of ints and checks for any non-zero
//            value. Returns false if one is found, true otherwise.
// data: array to check
// size: size of the input array
// returns a bool
// ------------------------------------------------------------------------
bool Tools::onlyZeros(vector<int> data, const int size)
{
  if (size == 0) // If there's nothing then there is no zeros
    return false;
  // Loop through elements
  for (int i = 0; i < size; i++)
    if (data[i] != 0) // Check for any non zeros
      return false;
  return true; // We would have found them by now if they existed
}

// ------------------------------------------------------------------------
// anyNegatives: Loops through an array of ints and checks for any non-zero
//               value. Returns false if one is found, true otherwise.
// data: array to check
// size: size of the input array
// returns a bool
// ------------------------------------------------------------------------
bool Tools::anyNegatives(vector<int> data, const int size)
{
  if (size == 0) // If there's nothing then there is no negatives
    return false;
  // Loop through elements
  for (int i = 0; i < size; i++)
    if (data[i] < 0) // Check for any negatives
      return true;
  return false; // If we didn't find any by now, we wont
}

// ------------------------------------------------------------------------
// countZeros: Simply counts the number of zeros in an array of ints
// data: array to process
// size: size of the input array
// returns an int
// ------------------------------------------------------------------------
int Tools::countZeros(vector<int> data, const int size)
{
  int count = 0;
  // Loop through elements
  for (int i = 0; i < size; i++)
    if (data[i] == 0) // if we encounter a zero
      count++; // increment count
  return count;
}

// ------------------------------------------------------------------------
// countNonZeros: Simply counts the number of nonzeros in an array of ints
// data: array to process
// size: size of the input array
// returns an int
// ------------------------------------------------------------------------
int Tools::countNonZeros(vector<int> data, const int size)
{
  int count = 0;
  // Loop through elements
  for (int i = 0; i < size; i++)
    if (data[i] != 0) // if we encounter anything that's not a zero
      count++; // increment count
  return count;
}

// ------------------------------------------------------------------------
// countNonZeros: Returns the sum of all integers in the array
// data: array to process
// size: size of the input array
// returns an int
// ------------------------------------------------------------------------
int Tools::sumOfAllElements(vector<int> data, const int size)
{
  int sum = 0;
  // Loop through elements
  for (int i = 0; i < size; i++)
    sum += data[i]; // add up all elements
  return sum;
}

// ------------------------------------------------------------------------
// findMax: Returns the max value in the array of ints
// data: array to search
// size: size of the input array
// returns an int
// ------------------------------------------------------------------------
int Tools::findMax(vector<int> data, const int size)
{
  if (data.size() > 0)
  {
    int max = data[0]; // max is the first element
    for (int i = 1; i < size; i++)
      if (data[i] > max) // if we encount an element greater than max
        max = data[i]; // replace max with that element

    return max;
  }
  return -1;
}

// ------------------------------------------------------------------------
// findMin: Returns the min value in the array of ints
// data: array to search
// size: size of the input array
// returns an int
// ------------------------------------------------------------------------
int Tools::findMin(vector<int> data, const int size)
{
  if (data.size() > 0)
  {
    int min = data[0]; // max is the first element
    for (int i = 1; i < size; i++)
      if (data[i] < min) // if we encount an element less than min
        min = data[i]; // replace min with that element

    return min;
  }
  return -1;
}

// ------------------------------------------------------------------------
// findAverage: Returns the average of all integers, this assumes that the
//          average will always be a whole number, as it should in a graph
// data: array to average
// size: size of the input array
// returns an int
// ------------------------------------------------------------------------
int Tools::findAverage(vector<int> data, const int size)
{
  if (data.size() > 0)
    return sumOfAllElements(data, size) / size; // pretty self explanatory
  return -1;
}

// ------------------------------------------------------------------------
// getVectorAsString: Builds a string representing the array
// data: array to build from
// size: size of the input array
// returns a string
// ------------------------------------------------------------------------
string Tools::getVectorAsString(vector<int> data, int size)
{
  if (data.size() > 0)
  {
    stringstream ss;
    for (int i = 0; i < size; i++)
    {
      stringstream f_mem;
      f_mem << data[i];
      if (ss.gcount() + f_mem.gcount() >= 60)
        ss << endl;
      ss << data[i] << " ";
    }
    return ss.str();
  }

  return "Null Sequence \n";
}
