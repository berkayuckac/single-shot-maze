#ifndef  ONE_SHOT_MAZE_LEVEL_DATA_HPP
#define  ONE_SHOT_MAZE_LEVEL_DATA_HPP

#pragma once

#include <vector>

class LevelData
{
public:
	std::vector<std::vector<int>> maze_tiles(int levelno);
	int lifecount(int levelno);
	int timelimit(int levelno);
};

#endif