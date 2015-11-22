#ifndef SP_GRID
#define SP_GRID

#include "../SceneGraph/SceneNode.h"
#include <vector>

struct Cell
{
	//std::vector<CSceneNode*> nodeList;
	std::vector<CGameObject*> GOList;
};

class Grid
{
public:
	Grid();
	Grid(int width, int height, int cellSize);
	~Grid();

	//Add a game object and determine which cell is it from
	void addNode(CGameObject* go);
	//Add a game object to the specific cell
	void addNode(CGameObject* go, Cell* cell);


	Cell* getCell(int x, int z);
	Cell* getCell(Vector3 pos);
	Cell* getCell(CGameObject* go);

	void removeGOFromCell(CGameObject* go);
	void clearList();

	std::vector<Cell> m_cells;
	int m_cellSize;
	int m_width;
	int m_height;

	int m_numXCells;
	int m_numZCells;
};

#endif