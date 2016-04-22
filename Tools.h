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

#include "libs.h"

class Tools
{
 public:
   // Helper static functions
   static void sortNonIncreasing(std::vector<int>&, int);
   static void sortNonDecreasing(std::vector<int>&, int);
   static bool onlyZeros(std::vector<int>, const int);
   static bool anyNegatives(std::vector<int>, const int);
   static bool isInSet(std::vector<int>, int);
   static int countZeros(std::vector<int>, const int);
   static int countNonZeros(std::vector<int>, const int);
   static int sumOfAllElements(std::vector<int>, const int);
   static int findMax(std::vector<int>, const int);
   static int findMin(std::vector<int>, const int);
   static int findAverage(std::vector<int>, const int);
   static std::string getVectorAsString(std::vector<int>, int);
   static unsigned long long factorial(int);
};

#endif // TOOLS_H
