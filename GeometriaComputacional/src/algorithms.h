#pragma once
#include <vector>

using namespace std;

void swap(vector<double>* vec, int indexA, int indexB);
int partition(vector<double>* vec, int startIndex, int endIndex);
void quickSortStep(vector<double>* vec, int startIndex, int endIndex);
void quickSort(vector<double>* vec);
void merge(vector<double>* vec, vector<double>* leftVec, vector<double>* rightVec);
void mergeSort(vector<double>* vec);