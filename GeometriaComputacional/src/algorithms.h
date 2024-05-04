#pragma once
#include <vector>
#include <stdexcept>
#include <cmath>
#include "vmath.h"

using namespace std;

void swap(vector<double>* vec, int indexA, int indexB);
int partition(vector<double>* vec, int startIndex, int endIndex);
int partitionVec2(vector<vec2>* points, int startIndex, int endIndex, const char& parameter);
void quickSortStep(vector<double>* vec, int startIndex, int endIndex);
void quickSortStepVec2(vector<vec2>* vec, int startIndex, int endIndex, const char& parameter);
void quickSort(vector<double>* vec);
void merge(vector<double>* vec, vector<double>* leftVec, vector<double>* rightVec);
void mergeSort(vector<double>* vec);
void quickSortVec2x(vector<vec2>* points);
void quickSortVec2y(vector<vec2>* points);
bool rotationIndexPosition(vector<vec2>* points, const vec2& q);