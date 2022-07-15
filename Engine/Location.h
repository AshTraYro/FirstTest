#pragma once

class  Location
{
public:
	void Add(const Location& val)
	{
		x = x + val.x;
		y = y + val.y;
	}

	bool operator ==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator !=(const Location& rhs1) const
	{
		return x != rhs1.x && y != rhs1.y;
	}

	int x;
	int y;
};