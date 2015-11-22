#include "SP_Grid.h"



Grid::Grid()
{

}

Grid::Grid(int width, int height, int cellSize):
	m_width(width),
	m_height(height),
	m_cellSize(cellSize)
{
	m_numXCells = ceil((float) m_width / m_cellSize);
	m_numZCells = ceil((float) m_height / m_cellSize);

	//Allocate all the cells
	m_cells.resize(m_numZCells * m_numXCells);
}

Grid::~Grid()
{
}

//void Grid::addNode(Vector3 pos, CSceneNode* node)
//{
//	Cell* cell = getCell(pos);
//	cell->nodeList.push_back(node);
//	node->ownerCell = cell;
//	node->cellVectorIndex = cell->nodeList.size() - 1;
//}

void Grid::addNode(CGameObject* go)
{
	Cell* cell = getCell(go->getPos());
	cell->GOList.push_back(go);
	go->getNode()->ownerCell = cell;
	go->getNode()->cellVectorIndex = cell->GOList.size() - 1;
}

//void Grid::addNode(CSceneNode* node, Cell* cell)
//{
//	cell->nodeList.push_back(node);
//	node->ownerCell = cell;
//	node->cellVectorIndex = cell->nodeList.size() - 1;
//}

void Grid::addNode(CGameObject* go, Cell* cell)
{
	cell->GOList.push_back(go);
	go->getNode()->ownerCell = cell;
	go->getNode()->cellVectorIndex = cell->GOList.size() - 1;
}

Cell* Grid::getCell(int x, int z)
{
	if (x < 0)
	{
		x = 0;
		std::cout << "X is less than 0" << std::endl;
	}

	if (x >= m_numXCells)
	{
		x = m_numXCells - 1;
	}

	if (z < 0)
	{
		z = 0;
		std::cout << "z is less than 0" << std::endl;
	}

	if (z >= m_numZCells)
	{
		z = m_numZCells - 1;
	}

	return &m_cells[z * m_numXCells + x];
}

Cell* Grid::getCell(Vector3 pos)
{
	int cellX = (int)(pos.x / m_cellSize);
	int cellZ = (int)(pos.z / m_cellSize);

	return getCell(cellX, cellZ);
}

Cell* Grid::getCell(CGameObject* go)
{
	int cellX = static_cast<int>(go->getPos().x / m_cellSize);
	int cellZ = static_cast<int>(go->getPos().z / m_cellSize);

	return getCell(cellX, cellZ);
}

//void Grid::removeNodeFromCell(CSceneNode* node)
//{
//	std::vector<CSceneNode*>& nodes = node->ownerCell->nodeList;
//
//	//Vector swap
//	nodes[node->cellVectorIndex] = nodes.back();
//	nodes.pop_back();
//
//	//Update vector index
//	if(node->cellVectorIndex < nodes.size())
//		nodes[node->cellVectorIndex]->cellVectorIndex = node->cellVectorIndex;
//
//	//Set index to -1;
//	node->cellVectorIndex = -1;
//	node->ownerCell = nullptr;
//}
void Grid::removeGOFromCell(CGameObject* go)
{
	std::vector<CGameObject*>& GOList = go->getNode()->ownerCell->GOList;

	//Vector swap
	GOList[go->getNode()->cellVectorIndex] = GOList.back();
	GOList.pop_back();

	//Update Vector index
	if (go->getNode()->cellVectorIndex < GOList.size())
	{
		GOList[go->getNode()->cellVectorIndex]->getNode()->cellVectorIndex = go->getNode()->cellVectorIndex;
	}

	//Set index to -1;
	go->getNode()->cellVectorIndex = -1;
	go->getNode()->ownerCell = nullptr;
}

void Grid::clearList()
{
	for (unsigned a = 0; a < m_cells.size(); ++a)
	{
		m_cells[a].GOList.clear();
	}
}