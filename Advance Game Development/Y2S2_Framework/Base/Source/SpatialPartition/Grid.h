#pragma once

#include <vector>
#include "..\SceneGraph\SceneNode.h"

using namespace std;

class CGrid
{
public:
	// Constructor
	CGrid(void);
	// Destructor
	~CGrid(void);

	// Init
	void Init(const int index_x, const int index_y, const int xSize, const int ySize);

	// Set a Mesh to this grid
	void SetMesh(Mesh* theGridMesh);
	// Add a new object to this grid
	void AddObject(CSceneNode* theObject);
	// Get list of objects in this grid
	vector<CSceneNode*> GetListOfObject(void);
	// Delete object from this grid
	void DeleteObjects(void);

	// Render the grid
	void Render(void);
	// RenderObjects
	void RenderObjects(const int RESOLUTION);	
	// Update the grid
	void Update(void);

	// PrintSelf
	void PrintSelf();

	// Mesh for this Grid
	Mesh* theGridMesh;
	// List of objects in this grid
	vector<CSceneNode*> ListOfObjects;
	// The x-axis index of this Grid in the Spatial Partition array.
	int index_x;
	// The y-axis index of this Grid in the Spatial Partition array.
	int index_y;
	// The size of this grid in the x-axis
	int xSize;
	// The size of this grid in the y-axis
	int ySize;
};
