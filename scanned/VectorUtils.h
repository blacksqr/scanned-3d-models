#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H
#include "PolygonUtils.h"
#include <math.h>


vector subtract(Vertex, Vertex);
vector crossProduct(vector, vector);
float dotProduct(vector, vector);
vector normalize(vector);
vector averageNormals(Polygon*, int);
vector sumNormals(Polygon*, int);


#endif

