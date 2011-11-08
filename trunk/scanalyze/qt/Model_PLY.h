#ifndef MODEL_PLY_H
#define MODEL_PLY_H

class Model_PLY 
{
public:
	int Model_PLY::Load(char *filename);
	void Model_PLY::Draw();
	float* Model_PLY::calculateNormal( float *coord1, float *coord2, float *coord3 );
	Model_PLY();
 
    float* Faces_Triangles;
    float* Faces_Quads;
	float* Vertex_Buffer;
	float* Normals;
 
	int TotalConnectedTriangles;	
	int TotalConnectedQuads;	
	int TotalConnectedPoints;
	int TotalFaces;
 
 
};


#endif