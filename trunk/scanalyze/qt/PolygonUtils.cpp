#include "PolygonUtils.h"
#include "VectorUtils.h"
#include <stdio.h>


void scaleObject(object*, float);
void shiftObject(object*, float, float, float);


/**
 *  This function will take an existing object and modify it so that it is centered
 *  on the scene and scale  [bigger/smaller] it so that it takes up the entire 
 *  clipping region
 **/
void modifyObjectToFitScreen(object* object, int screenDimension)
{
	float minx, maxx, miny, maxy, minz, maxz = 0;
	minx = maxx = object->vertex[0].x;
	miny = maxy = object->vertex[0].y;
	minz = maxz = object->vertex[0].z;

	// First, we need to calculate the min/max in each direction so that we know
	// how much to scale, translate the object
	for(int i = 0; i < object->vertices_qty; i++)
	{
		if(object->vertex[i].x > maxx)  maxx = object->vertex[i].x;
		else if(object->vertex[i].x < minx)  minx = object->vertex[i].x;

		if(object->vertex[i].y > maxy)  maxy = object->vertex[i].y;
		else if(object->vertex[i].y < miny)  miny = object->vertex[i].y;

		if(object->vertex[i].z > maxz)  maxz = object->vertex[i].z;
		else if(object->vertex[i].z < minx)  minz = object->vertex[i].z;
	}

	
	// Shift the object so that it is centered
	float shiftx = minx + (maxx-minx)/2;
	float shifty = miny + (maxy-miny)/2;
	float shiftz = minz + (maxz-minz)/2;
	shiftObject(object, shiftx, shifty, shiftz);



	// Scale the object [bigger/smaller] so that it takes up the entire
	// clipping region
	float percentDifferenceX = (float)screenDimension/(maxx - minx);
	float percentDifferenceY = (float)screenDimension/(maxy - miny);
	float percentDifferenceZ = (float)screenDimension/(maxz - minz);

	float scaleAmount = (percentDifferenceX < percentDifferenceY)?percentDifferenceX:percentDifferenceY;
	scaleAmount = (scaleAmount < percentDifferenceZ)?scaleAmount:percentDifferenceZ;
	scaleObject(object, scaleAmount);
}


void shiftObject(object* object, float shiftx, float shifty, float shiftz)
{
	for(int i = 0; i < object->vertices_qty; i++)
	{
		object->vertex[i].x = object->vertex[i].x - shiftx;
		object->vertex[i].y = object->vertex[i].y - shifty;
		object->vertex[i].z = object->vertex[i].z - shiftz;
	}
}


void scaleObject(object* object, float scaleAmount)
{
	for(int i = 0; i < object->vertices_qty; i++)
	{
		object->vertex[i].x = object->vertex[i].x * scaleAmount;
		object->vertex[i].y = object->vertex[i].y * scaleAmount;
		object->vertex[i].z = object->vertex[i].z * scaleAmount;
	}
}

/**
 *  Calculates the vertex normals for every vertex in the object.  It does this
 *  by taking two edges of the polygon (creating vectors) and using the right-hand
 *  coordinate system, take the cross product of those vectors.  
 *
 *  As the polygon normals are calculated, these values are saved with the vertex (summed up).
 *  Finally, we normalize the vector sums to get the vertex normal.
 **/
void calculateVertexNormals(object_ptr object)
{
	int i;
	vertex vert1,vert2,vert3;
	vector vect1,vect2,normal; 
	int connections_qty[MAX_VERTICES];

    // initalizing vertex normal
	for (i=0; i<object->vertices_qty; i++)
	{
		object->vertex[i].normal.x = 0.0;
		object->vertex[i].normal.y = 0.0;
		object->vertex[i].normal.z = 0.0;
		connections_qty[i]=0;
	}
	
	// summing up polygon normals
	for (i=0; i<object->polygons_qty; i++)
	{
        vert1.x = object->vertex[object->polygon[i].a].x;
        vert1.y = object->vertex[object->polygon[i].a].y;
        vert1.z = object->vertex[object->polygon[i].a].z;
        vert2.x = object->vertex[object->polygon[i].b].x;
        vert2.y = object->vertex[object->polygon[i].b].y;
        vert2.z = object->vertex[object->polygon[i].b].z;
        vert3.x = object->vertex[object->polygon[i].c].x;
        vert3.y = object->vertex[object->polygon[i].c].y;
        vert3.z = object->vertex[object->polygon[i].c].z;         
  
        // This is how we calculate the polygon normal
		vect1 = subtract(vert2, vert1);
		vect2 = subtract(vert3, vert1);
        normal = crossProduct (vect1, vect2); 
        normal = normalize (normal); 

		connections_qty[object->polygon[i].a]+=1; 
		connections_qty[object->polygon[i].b]+=1;
		connections_qty[object->polygon[i].c]+=1;

		object->vertex[object->polygon[i].a].normal.x+=normal.x; 
		object->vertex[object->polygon[i].a].normal.y+=normal.y;
		object->vertex[object->polygon[i].a].normal.z+=normal.z;
		object->vertex[object->polygon[i].b].normal.x+=normal.x;
		object->vertex[object->polygon[i].b].normal.y+=normal.y;
		object->vertex[object->polygon[i].b].normal.z+=normal.z;
		object->vertex[object->polygon[i].c].normal.x+=normal.x;
		object->vertex[object->polygon[i].c].normal.y+=normal.y;
		object->vertex[object->polygon[i].c].normal.z+=normal.z;	
	}	
	
	// normalize the normal vectors.
    for (i=0; i<object->vertices_qty; i++)
	{
		if (connections_qty[i]>0)
		{
			object->vertex[i].normal = normalize(object->vertex[i].normal);
		}
	}
}