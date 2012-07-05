#ifndef IMAGEMANAGER_H_
#define IMAGEMANAGER_H_

#include <SFML/Graphics.hpp>
#include "RessourceManager.h"

class ImageManager : public ResourceManager< sf::Image > {
private:
protected:
	virtual sf::Image* load( const std::string& strId );
public:
};

#endif /* IMAGEMANAGER_H_ */
