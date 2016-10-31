#include"Ui.h"

//Coordinate interchange
Point Ui::chang_GL_to_map(Point& glpoint, TMXTiledMap* map)
{
	Point mappoint;
	mappoint.x = glpoint.x / map->getTileSize().width;
	mappoint.y = (map->getContentSize().height - glpoint.y) / map->getTileSize().height;
	return mappoint;
}
//Coordinate interchange
Point Ui::chang_map_to_GL(Point& mappoint, TMXTiledMap* map)
{
	Point glpoint;
	glpoint.x = map->getTileSize().width*mappoint.x;
	glpoint.y = map->getContentSize().height - map->getTileSize().height*(mappoint.y + 1);
	return glpoint;
}
//string dealing
Vector<String*> Ui::splitString(const char* srcStr, const char* sSep)
{
	Vector<String*> stringList;

	int size = strlen(srcStr);
	String* str = String::create(srcStr);

	int startIndex = 0;
	int endIndex = 0;
	endIndex = str->_string.find(sSep);

	String* spliStr = NULL;

	while (endIndex > 0) {
		spliStr = String::create("");
		spliStr->_string = str->_string.substr(startIndex, endIndex);
		stringList.pushBack(spliStr);
		str->_string = str->_string.substr(endIndex + 1, size);
		endIndex = str->_string.find(sSep);
	}
	if (str->_string.compare("") != 0) {
		stringList.pushBack(String::create(str->_string));
	}

	return stringList;


}