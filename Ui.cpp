#include"Ui.h"
#include <string>

//Coordinate interchange
Point Ui::chang_GL_to_map(Point& glPoint, TMXTiledMap* map)
{
	Point mapPoint;
	mapPoint.x = glPoint.x / map->GetTileSize().width;
	mapPoint.y = (map->GetContentSize().height - glPoint.y) / map->GetTileSize().height;
	return mapPoint;
}
//Coordinate interchange
Point Ui::chang_map_to_GL(Point& mapPoint, TMXTiledMap* map)
{
	Point glPoint;
	glPoint.x = map->GetTileSize().width*mapPoint.x;
	glPoint.y = map->GetContentSize().height - map->GetTileSize().height*(mapPoint.y + 1);
	return glPoint;
}
//string dealing
Vector<String*> Ui::SplitString(const char* srcStr, const char* sSep)
{
	Vector<String*> stringList;

	int size = strlen(srcStr);
	String* str = String::Create(srcStr);

	int startIndex = 0;
	int endIndex = 0;
	endIndex = str->_string.find(sSep);

	String* spliStr = NULL;

	while (endIndex > 0) {
		spliStr = String::Create("");
		spliStr->_string = str->_string.substr(startIndex, endIndex);
		stringList.PushBack(spliStr);
		str->_string = str->_string.substr(endIndex + 1, size);
		endIndex = str->_string.find(sSep);
	}
	if (str->_string.compare("") != 0) {
		stringList.PushBack(String::Create(str->_string));
	}

	return stringList;


}