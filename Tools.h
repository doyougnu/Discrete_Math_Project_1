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
#include <set>
#include <algorithm> //for a standard sort

class Tools
{
 public:
   // Helper static functions
   static void sortNonIncreasing(std::vector<int>&, int);
   static void sortNonDecreasing(std::vector<int>&, int);
   static bool onlyZeros(std::vector<int>, const int);
   static bool anyNegatives(std::vector<int>, const int);
   static int countZeros(std::vector<int>, const int);
   static int countNonZeros(std::vector<int>, const int);
   static int sumOfAllElements(std::vector<int>, const int);
   static int findMax(std::vector<int>, const int);
   static int findMin(std::vector<int>, const int);
   static int findAverage(std::vector<int>, const int);
   static std::string getVectorAsString(std::vector<int>, int);
   static unsigned long long factorial(int);
   static std::set<std::vector<int> > noDupCartesianProduct
     (std::vector<int>, std::vector<int>);
};

#endif // TOOLS_H
