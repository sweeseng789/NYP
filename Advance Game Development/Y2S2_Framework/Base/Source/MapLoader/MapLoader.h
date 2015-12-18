#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class MapLoader
{
private:

	std::string FILE_LOCATION;

public:
	MapLoader();
	~MapLoader();

	unsigned int map_height; // Y Axis
	unsigned int map_width; // X and Z Axis

	float worldSize;
	float worldHeight;
	float cellSize;

	bool fileExists(std::string file);
	bool loadMap(std::string file);
	bool saveMap(std::string file);
	std::vector<std::vector<std::string>> map_data;
};
#endif