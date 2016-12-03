#include"Ui.h"
#include <string>

//Coordinate interchange
Point Ui::chang_GL_to_map(Point& glpoint, TMXTiledMap* map)
{
	Point mappoint;
	mappoint.x = glpoint.x / map->GetTileSize().width;
	mappoint.y = (map->GetContentSize().height - glpoint.y) / map->GetTileSize().height;
	return mappoint;
}
//Coordinate interchange
Point Ui::chang_map_to_GL(Point& mappoint, TMXTiledMap* map)
{
	Point glpoint;
	glpoint.x = map->GetTileSize().width*mappoint.x;
	glpoint.y = map->GetContentSize().height - map->GetTileSize().height*(mappoint.y + 1);
	return glpoint;
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