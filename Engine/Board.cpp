#include "Board.h"
#include <assert.h>
#include "Snake.h"

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

Board::CellContent Board::CheckCellContent(const Location& loc) const
{
	return ContentOfCells[loc.y*width+loc.x];
}

void Board::EmptyCellContent(const Location& loc)
{
	ContentOfCells[loc.y * width + loc.x] = CellContent::empty;
}


void Board::SpawnContent(std::mt19937& rng, const class Snake& snake, CellContent Content)
{
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);
	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTileAll(newLoc) || CheckCellContent(newLoc)!=CellContent::empty);

	ContentOfCells[newLoc.y * width + newLoc.x] = Content;
}

void Board::DrawCellContent()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (CheckCellContent({ x,y }) == CellContent::food)
			{
				DrawCell({ x,y }, foodColor);
			}

			else if (CheckCellContent({ x,y }) == CellContent::obstacle)
			{
				DrawCell({ x,y }, obstacleColor);
			}

			else if (CheckCellContent({ x,y }) == CellContent::poison)
			{
				DrawCell({ x,y }, poisonColor);
			}
		}
	}
}