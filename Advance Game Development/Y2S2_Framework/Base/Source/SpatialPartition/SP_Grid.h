#ifndef SP_GRID
#define SP_GRID

#include "../SceneGraph/SceneNode.h"
#include <vector>

struct Cell
{
	std::vector<CSceneNode*> nodeList;
};

class Grid
{
public:
	Grid();
	Grid(int width, int height, int cellSize);
	~Grid();

	//Add a node and determine which cell is it from
	void addNode(Vector3 pos, CSceneNode* node);
	//Add a ball to the specific cell
	void addNode(CSceneNode* node, Cell* cell);


	Cell* getCell(int x, int z);
	Cell* getCell(Vector3 pos);

	void removeNodeFromCell(CSceneNode* node);

	std::vector<Cell> m_cells;
	int m_cellSize;
	int m_width;
	int m_height;

	int m_numXCells;
	int m_numZCells;
};

#endif