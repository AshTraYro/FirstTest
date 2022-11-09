#include "Board.h"
#include <assert.h>
#include "Snake.h"
#include "Goal.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim(loc.x * dimension + off_x+cellPadding, loc.y * dimension + off_y+cellPadding, dimension-2*cellPadding, dimension-cellPadding, c);

}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

void Board::DrawBoarder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dimension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimension;

	gfx.DrawRect(left, top, right, top + borderWidth,boardColor);

	gfx.DrawRect(left, bottom, right, bottom - borderWidth, boardColor);

	gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, boardColor);

	gfx.DrawRect(right, top + borderWidth, right - borderWidth, bottom - borderWidth, boardColor);
}

bool Board::checkForObstacles(const Location& loc) const
{
	return hasObstacles[loc.y*width+loc.x];
}

void Board::SpawnObstacles(std::mt19937& rng, const Snake& snake, const Goal& goal)
{
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);
	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTileAll(newLoc) || checkForObstacles(newLoc) || goal.GetLocation() == newLoc);

	hasObstacles[newLoc.y * width + newLoc.x] = true;
}

void Board::DrawObstacle()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (checkForObstacles({ x,y }))
			{
				DrawCell({ x,y }, obstacleColor);
			}
		}
	}


}
