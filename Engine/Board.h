#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	enum class CellContent
	{
		empty,
		food,
		obstacle,
		poison
	};
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBoarder();
	CellContent CheckCellContent(const Location& loc) const;
	void EmptyCellContent(const Location& loc);
	void SpawnContent(std::mt19937& rng, const class Snake& snake, CellContent Content);
	void DrawCellContent();	

private:
	
	static constexpr int dimension = 20;
	static constexpr int width = 25;
	static constexpr int height = 25;
	static constexpr int x = 100;
	static constexpr int y = 40; 
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 1;
	static constexpr Color boardColor = Colors::Magenta;
	static constexpr Color foodColor = Colors::Red;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color poisonColor = Colors::Magenta;
	CellContent ContentOfCells[height * width] = { CellContent::empty };

	Graphics& gfx;
};