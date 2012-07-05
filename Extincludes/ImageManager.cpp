#include <iostream>
#include "ImageManager.h"

using namespace std;

sf::Image* ImageManager::load( const std::string& strId ) {
	sf::Image* image = new sf::Image();
	
	// caca
	if( !image->LoadFromFile( strId ) ) {
		cout << "[WARN] ImageManager failed to load: " << strId << endl;
		delete image;
		image = NULL;
	}

	return image;
}
