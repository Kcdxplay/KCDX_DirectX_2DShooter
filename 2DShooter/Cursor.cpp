#include "Cursor.h"
#include "Map.h"

Cursor * Cursor::Instance()
{
	static Cursor instance;
	return &instance;
}

void Cursor::Update(RECT windowRect)
{
	GetCursorPos(&mousePoint);

	PaintPos.x = mousePoint.x - windowRect.left;
	PaintPos.y = mousePoint.y - windowRect.top;

	Map::Instance()->GetMapPos(PaintPos.x, PaintPos.y, &MapPos.x, &MapPos.y);
}