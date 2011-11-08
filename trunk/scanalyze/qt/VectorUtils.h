#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H
#include "PolygonUtils.h"
#include <math.h>


vector subtract(vertex, vertex);
vector crossProduct(vector, vector);
float dotProduct(vector, vector);
vector normalize(vector);
vector averageNormals(polygon*, int);
vector sumNormals(polygon*, int);


#endif