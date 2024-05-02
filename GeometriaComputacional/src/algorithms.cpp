#include <algorithm>
#include <iostream>
#include "algorithms.h"


using namespace std;


template <typename T> void swap(vector<T>* vec, int indexA, int indexB) {
    if (indexA == indexB) return;
    T temp = vec->at(indexA);
    vec->at(indexA) = vec->at(indexB);
    vec->at(indexB) = temp;
}

int partition(vector<double>* vec, int startIndex, int endIndex) {
    int pivot = vec->at(endIndex);
    int i = startIndex - 1;
    for (int j = startIndex; j < endIndex; j++) {
        if (vec->at(j) < pivot) {
            i += 1;
            swap(vec, i, j);
        }
    }
    i += 1;
    swap(vec, i, endIndex);
    return i;
}


void quickSortStep(vector<double>* vec, int startIndex, int endIndex) {
    if (endIndex <= startIndex) return; // recursion f0 case

    int pivotIndex = partition(vec, startIndex, endIndex);
    quickSortStep(vec, startIndex, pivotIndex - 1);
    quickSortStep(vec, pivotIndex + 1, endIndex);
}


void quickSort(vector<double>* vec) {
    quickSortStep(vec, 0, vec->size() - 1);
}


void merge(vector<double>* vec, vector<double>* leftVec, vector<double>* rightVec) {
    vector<double> vecCopy;
    int size = vec->size();
    int leftSize = size / 2;
    int rightSize = size - leftSize;
    int l = 0;
    int r = 0;
    int step = 0;
    while (l < leftSize && r < rightSize) {
        if (leftVec->at(l) < rightVec->at(r)) {
            vec->at(step) = leftVec->at(l);
            l += 1;
        }
        else {
            vec->at(step) = rightVec->at(r);
            r += 1;
        }
        step++;
    }
    while (l < leftSize) {
        vec->at(step) = leftVec->at(l);
        l += 1;
        step++;
    }
    while (r < rightSize) {
        vec->at(step) = rightVec->at(r);
        r += 1;
        step++;
    }
}


void mergeSort(vector<double>* vec) {
    int subVecSize = vec->size();
    if (subVecSize < 2) return; //already sorted

    //two subvectors split in half
    int half = subVecSize / 2; // int division = floor

    vector<double> leftSubVec;
    for (int i = 0; i <= half - 1; i++) {
        leftSubVec.push_back(vec->at(i));
    }
    vector<double> rightSubVec;
    for (int i = half; i < subVecSize; i++) {
        rightSubVec.push_back(vec->at(i));
    }
    mergeSort(&leftSubVec);
    mergeSort(&rightSubVec);
    merge(vec, &leftSubVec, &rightSubVec);
}

//Diego
//Sorting algorithms for vec2s.

int partitionVec2(vector<vec2>* points, int startIndex, int endIndex, const char& parameter) {
    if (parameter == 'x') {
        double pivot = points->at(endIndex).x;
        int i = startIndex - 1;
        for (int j = startIndex; j < endIndex; j++) {
            if (points->at(j).x < pivot) {
                i += 1;
                swap(points, i, j);
            }
        }
        i += 1;
        swap(points, i, endIndex);
        return i;
    }
    else if (parameter == 'y') {
        double pivot = points->at(endIndex).y;
        int i = startIndex - 1;
        for (int j = startIndex; j < endIndex; j++) {
            if (points->at(j).y < pivot) {
                i += 1;
                swap(points, i, j);
            }
        }
        i += 1;
        swap(points, i, endIndex);
        return i;
    }
    else {
        runtime_error("Invalid Parameter!");
    }
}

void quickSortStepVec2(vector<vec2>* vec, int startIndex, int endIndex, const char& parameter) {
    if ((parameter == 'x') or (parameter == 'y')) {
        if (endIndex <= startIndex) return; // recursion f0 case

        int pivotIndex = partitionVec2(vec, startIndex, endIndex, parameter);
        quickSortStepVec2(vec, startIndex, pivotIndex - 1, parameter);
        quickSortStepVec2(vec, pivotIndex + 1, endIndex, parameter);
    }
    else {
        runtime_error("Invalid Parameter!");
    }
}

void quickSortVec2x(vector<vec2>* points) {
    quickSortStepVec2(points, 0, points->size() - 1, 'x');
}

void quickSortVec2y(vector<vec2>* points) {
    quickSortStepVec2(points, 0, points->size() - 1, 'y');
}