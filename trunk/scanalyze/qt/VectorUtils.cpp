#include "VectorUtils.h"

vector subtract(vertex u, vertex v)
{
	vector result;
	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;
	return result;

}

vector add(vector u, vector v, vector w)
{
	vector result;
	result.x = u.x + v.x + w.x;
	result.y = u.y + v.y + w.y;
	result.z = u.z + v.z + w.z;
	return result;
}

vector crossProduct(vector u, vector v)
{
	vector res;
	res.x = (u.y * v.z) - (u.z * v.y);
	res.y = (u.z * v.x) - (u.x * v.z);
	res.z = (u.x * v.y) - (u.y * v.x);
	return res;
}

float dotProduct(vector u, vector v)
{
	float res = u.x*v.x + u.y*v.y + u.z*v.z;
	return res;
}

vector normalize(vector vec)
{
	float magnitude = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);

	vector normalizedVector;
	normalizedVector.x = (vec.x/magnitude);
	normalizedVector.y = (vec.y/magnitude);
	normalizedVector.z = (vec.z/magnitude);

	return normalizedVector;
}


vector averageNormals(polygon* polygons, int count)
{
	float sumx = 0.0, sumy = 0.0, sumz = 0.0;
	for(int i = 0; i < count; i++)
	{
		sumx += polygons[i].normal.x;
		sumy += polygons[i].normal.y;
		sumz += polygons[i].normal.z;
	}

	vector average;
	average.x = sumx / count;
	average.y = sumy / count;
	average.z = sumz / count;

	return average;
}

vector sumNormals(polygon* polygons, int count)
{
	float sumx = 0.0, sumy = 0.0, sumz = 0.0;
	for(int i = 0; i < count; i++)
	{
		sumx += polygons[i].normal.x;
		sumy += polygons[i].normal.y;
		sumz += polygons[i].normal.z;
	}

	vector sum;
	sum.x = sumx;
	sum.y = sumy;
	sum.z = sumz;

	return sum;
}