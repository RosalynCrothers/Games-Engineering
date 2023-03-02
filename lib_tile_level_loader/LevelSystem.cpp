#include "LevelSystem.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

std::unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t _width;
size_t height;
Vector2f LevelSystem::_offset(Vector2f(0.0f, 0.0f));

float LevelSystem::_tilesize(100.0f);
vector<std::unique_ptr<RectangleShape>> LevelSystem::_sprites;

std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours{ {WALL, Color::White}, END, Color::Red }};

sf::Color LevelSystem::getColour(LevelSystem::TILE t) {
	auto it = _colours.find(t);
	if (it == _colours.end()) {
		_colours[t] = Color::Transparent;
	}
	return _colours[t];
}

void LevelSystem::setColour(LevelSystem::TILE t, Color c) {
	_colours[t] = c;
}

size_t LevelSystem::getHeight() {
	return _height;
}

size_t LevelSystem::getWidth() {
	return _width;
}





void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
	_tilesize = tileSize;
	size_t w = 0, h = 0;
	string buffer;

	ifstream f(path);
	if (f.good()) {
		f.seekg(0, std::ios::end);
		buffer.resize(f.tellg());
		f.seekg(0);
		f.read(&buffer[0], buffer.size());
		f.close();
	}
	else
	{
		throw string("Couldn't open level file: ") + path;
	}

	std::vector<TILE> temp_tiles;
	for (int i = 0; i < buffer.size(); i++) {
		const char c = buffer[i];
		
		switch (c) {

		case 'w':
			temp_tiles.push_back(WALL);
			break;

		case 's':
			temp_tiles.push_back(START);
			break;

		case 'e':
			temp_tiles.push_back(END);
			break;

		case ' ':
			temp_tiles.push_back(EMPTY);
			break;

		case '+':
			temp_tiles.push_back(WAYPOINT);
			break;

		case 'n':
			temp_tiles.push_back(ENEMY);
			break;
			
		case '\n':
			if (w == 0) {
				w = i;
			}
			h++;
			break;

		default:
			cout << c << endl; //unknown tile type
		}
	}

	if (temp_tiles.size() != (w * h)) {
		throw string("Can't parse level file: ") + path;
	}

	_tiles = std::make_unique<TILE[]>(w * h);
	_width = w;
	_height = h;
	
	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);

	cout << "LEVEL " << path << " Loaded. " << w << " x " << h << std::endl;

	buildSprites();
}