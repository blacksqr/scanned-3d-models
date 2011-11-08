#ifndef POLYGON_UTILS_H
#define POLYGON_UTILS_H

#include <math.h>


#define MAX_VERTICES 8000 // Max number of vertices (for each object)
#define MAX_POLYGONS 8000 // Max number of polygons (for each object)


// holds the normal value
typedef struct{
	float x,y,z;
}vector;


// Our vertex type
typedef struct{
    float x,y,z;
	vector normal;
}vertex;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    int a,b,c;
	vector normal;
}polygon;


// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}mapcoord;

// The object type
typedef struct {
	char name[20];
    
	int vertices_qty;
    int polygons_qty;

    vertex vertex[MAX_VERTICES]; 
    polygon polygon[MAX_POLYGONS];
    mapcoord mapcoord[MAX_VERTICES];
    int id_texture;
} object, *object_ptr;



void modifyObjectToFitScreen(object*, int);
void calculateVertexNormals(object_ptr);

#endif