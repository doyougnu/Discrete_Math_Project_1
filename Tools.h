/*******************************************************************************
 * Tools.h
 *
 * Tanner Gower
 * 2/25/2016
 *
 * A class declaration of a Tools object.
 *
*******************************************************************************/
#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>

class Tools
{
 public:
   // Helper static functions
   static void sortNonIncreasing(vector<int>&, int);
   static void sortNonDecreasing(vector<int>&, int);
   static bool onlyZeros(vector<int>, const int);
   static bool anyNegatives(vector<int>, const int);
   static int countZeros(vector<int>, const int);
   static int countNonZeros(vector<int>, const int);
   static int sumOfAllElements(vector<int>, const int);
   static int findMax(vector<int>, const int);
   static int findMin(vector<int>, const int);
   static int findAverage(vector<int>, const int);
   static std::string getArrayAsString(vector<int>, int);
};

#endif // TOOLS_H
