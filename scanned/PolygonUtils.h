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
}Vertex;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    int a,b,c;
	vector normal;
}Polygon;


// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}Mapcoord;

// The object type
typedef struct {
	char name[20];
    
	int vertices_qty;
    int polygons_qty;

    Vertex vertex[MAX_VERTICES]; 
    Polygon polygon[MAX_POLYGONS];
    Mapcoord mapcoord[MAX_VERTICES];
    int id_texture;
} object, *object_ptr;



void modifyObjectToFitScreen(object*, int);
void calculateVertexNormals(object_ptr);

#endif

