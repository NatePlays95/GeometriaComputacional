#include <algorithm>
#include <iostream>
#include "algorithms.h"


using namespace std;

#define PI 3.14159265

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

////Diego
bool rotationIndexPosition(vector<vec2>* points, const vec2& q) {
    //Points is a vector of polygon's vertices, e.g, for a square, we have p0, p1, p2, p3.

    vector<double> angles{};
    
    for (int i = 0; i < points->size(); i++) {
        //We'll need -> vec2(p_i - q) and (P_i+1 - q) -> We gonna call vec2(a) and vec2(b)
        //Extra Case: In the last loop, we gonna have -> vec(p_max - q) and vec2(p_0 - q)

        vec2 a;
        vec2 b;

        //Check if it's an Extra case or not
        if (i != (points->size() - 1)) {
            //Normal Case
            a = points->at(i) - q;
            b = points->at(i + 1) - q;
        }
        else {
            //Extra Case
            a = points->at(i) - q;
            b = points->at(0) - q;
        }

        //The angle between a and b = arc cos((a . b) / (|a| |b|))
        double teta = acos((a.dot(b)) / (a.mag() * b.mag()));
        teta = teta * 180.0 / PI; //Rad -> Degrees

        angles.push_back(teta);
    }

    double sum = 0;

    for (int i = 0; i < angles.size(); i++) {
        sum += angles.at(i);
    }

    //I will tolerate an error of up to 1e-3
    //+-1 -> Inside -> True
    if (((1 <= sum / 360) and (sum / 360 <= 1 + 1e-3)) or ((- 1 >= sum / 360) and (sum / 360 >= -1 - 1e-3))) {
        return true;
    }
    else {
        return false;
    }
}


bool pointInShapeRaycast(vector<vec2>* shapeVertices, const vec2& point) {
    // Points is a vector of polygon's vertices, e.g, for a square, we have p0, p1, p2, p3.
    // We cast a ray from point, towards positive X. see how many times it crosses an edge
    // even number of crossings, it's outside; odd, it's inside.

    int crossingCount = 0;
    int size = shapeVertices->size();
    vec2 v1, v2;


    for (int index = 0; index < size; index++) {
        v1 = shapeVertices->at(index);
        if (index == size - 1) {
            v2 = shapeVertices->at(0);
        }
        else {
            v2 = shapeVertices->at(index + 1);
        }
        
        // First condition: at least one of the vertices should be to the right of point
        //if ((point.x >= v1.x) && (point.x >= v2.x)) continue;

        // Second condition: point.y is between v1 and v2
        if ((point.y > v1.y) == (point.y > v2.y)) continue;

        // Check Collision
        // all the points in (v1, v2) can be obtained from v1 + (v2-v1)*t, 0 <= t <= 1.
        // all the points in our raycast can be obtained with point + u*<1, 0>, with u >= 0.

        // collision = v1 + (v2 - v1)*(point.y - v1.y)/(v2.y - v1.y)
        vec2 collisionPoint = v1 + (v2 - v1) * ((point.y - v1.y) / (v2.y - v1.y));
        if (collisionPoint.x >= point.x) { // if collision is to the right
            crossingCount += 1;
            //cout << "collided" << v1 << v2 << endl;
        }
    }
    //cout << crossingCount << endl;
    return !(crossingCount % 2 == 0);
}

bool doSegmentsCross(const vec2& a, const vec2& b, const vec2& c, const vec2& d) {
    //(AB x AC) (AB x AD) < 0
    bool step1 = (b - a).cross(c - a) * (b - a).cross(d - a);
    if (step1 >= 0) return false;
    
    //(CD x CA) (CD x CB) < 0
    bool step2 = (d - c).cross(a - c) * (d - c).cross(b - c);
    if (step2 >= 0) return false;

    return true;
}

double orientedArea(vector<vec2>* convexShape) {
    double sum = 0;
    int size = convexShape->size();
    for (int index = 0; index < size; index++) {
        vec2 p1, p2;
        p1 = convexShape->at(index);
        if (index == size - 1) {
            convexShape->at(0);
        }
        else {
            convexShape->at(index+1);
        }

        double step = p1.cross(p2);
        sum += step;
    }
    return sum / 2;
}

double pseudoAngleBetween(vec2 a, vec2 b) {
    return b.toPseudoAngle() - a.toPseudoAngle();
}