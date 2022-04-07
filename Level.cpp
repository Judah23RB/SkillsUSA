#include "Level.h"
#include <sstream>
#include <cstdlib>

Level::Level()
{

}
//data is stored in platform file in order: xvalue, yvalue, length, plat Type
void Level::loadLevel(std::string num)
{
	int tempx, tempy, tempL, tempP; //used for platforms
	int tempiX, tempiY, tempiP; //used for items
	std::ifstream fhandle;
	std::string fileName = "LevelData/" + num + "/platData.txt";
	
	fhandle.open(fileName);
	if (fhandle.is_open())
	{
		std::string line;
		while (std::getline(fhandle,line))//fhandle >> temp)
		{
			std::istringstream ss(line);
			ss >> tempx >> tempy >> tempL >> tempP;
			xvals.push_back(tempx);
			yvals.push_back(tempy);
			length.push_back(tempL);
			platTypes.push_back(tempP);
		}
		fhandle.close();
	}

	fileName = "LevelData/" + num + "/itemData.txt";
	fhandle.open(fileName);
	{
		if (fhandle.is_open())
		{
			std::string line;
			while (std::getline(fhandle, line))//fhandle >> temp)
			{
				std::istringstream ss(line);
				ss >> tempiX >> tempiY >> tempiP;
				itemNum++;
				iXVals.push_back(tempiX);
				iYVals.push_back(tempiY);
				iType.push_back(tempiP);
			}
			fhandle.close();
		}
	}
	
	for (auto x : xvals)
	{
		platNum++;
		//std::cout << x << std::endl;
	}
	initLevel();
	
}


Level::~Level()
{
	endPlat = nullptr;
	delete[] leveldata;
	delete[] itemData;
	itemData = nullptr;
	leveldata = nullptr;
}

void Level::initLevel()
{
	std::cout << "PLEASE GOD WORK" << std::endl;
	leveldata = new Platforms[platNum];
	
	for (int x = 0; x < platNum; x++)
	{
		leveldata[x].setSize(length.at(x));
		leveldata[x].setPos(xvals.at(x), yvals.at(x));
		leveldata[x].setType(platTypes.at(x));
	}
	itemData = new Item[itemNum];
	for (int x = 0; x < itemNum; x++)
	{
		itemData[x].setPos(iXVals.at(x), iYVals.at(x));
		itemData[x].setType(iType.at(x));
	}
}



int Level::getPlatNum()
{
	return platNum;
}


void Level::drawLevel(sf::RenderWindow& w)
{
	for (int x = 0; x < platNum; x++)
	{
		w.draw(leveldata[x].getPlatSprite());
	}
	for (int x = 0; x < itemNum; x++)
	{
		w.draw(itemData[x].getSprite());
	}
}


//handles platform collision, special platform collision, item collision
//reads in player bounding box, int by reference to store plat type
//if player is colliding with platform, return type of platform so collision can be handled in game
bool Level::collision(sf::FloatRect p, int &platType)
{
	for (int x = 0; x < platNum; x++)
	{
		if (leveldata[x].getPlatBounds().contains(p.left, p.top + p.height) || leveldata[x].getPlatBounds().contains(p.left + p.width, p.top + p.height))
		{
			switch (leveldata[x].getType())
			{
			case 1: //default
				platType = 1;
				return true;
				break;
			case 2: //broken
				platType = 2;
				animateBrokePlat(leveldata[x]);
				return false;
				break;
				
			case 3: //tread left
				platType = 3;
				return true;
				break;
			case 4: //tread right
				platType = 4;
				return true;
				break;
			case 5: //spike
				platType = 5;
				return true;
			case 6: //end plat
				platType = 6;
				return true;
				break;
			default:
				break;
			}
		}
	}
	platType = 0;
	return false;
}

bool Level::itemCollision(sf::FloatRect p, int& itemType)
{
	for (int x = 0; x < itemNum; x++)
	{
		if (itemData[x].getBounds().intersects(p))
		{
			switch (itemData[x].getType())
			{
			case 1:
				itemType = 1;
				itemData[x].clearSprite();
				return true;
				break;
			case 2:
				itemType = 2;
				itemData[x].clearSprite();
				return true;
				break;
			case 3:
				itemType = 3;
				itemData[x].clearSprite();
				return true;
				break;
			
			case 4:
				itemType = 4;
				itemData[x].clearSprite();
				return true;
				break;
			default:
				break;
			}
		}
	}
		
	
	itemType = 0;
	return false;
}


void Level::scrollLevel(sf::RenderWindow &w)
{
	levelProgression();
	
	if (slowItem)
	{
		scrollSpeed += .1;
		slowItem = false;
	}
	
	for (int x = 0; x < platNum; x++)
		leveldata[x].scroll(scrollSpeed);
	for (int x = 0; x < itemNum; x++)
		itemData[x].scroll(scrollSpeed);
	drawLevel(w);
}

void Level::changeScrollSpeed(double speed)
{
	scrollSpeed = speed;
}

void Level::levelProgression()
{
	if (leveldata[0].getPos().y < 100)
		changeScrollSpeed(-.25);
	if (leveldata[0].getPos().y < 0)
		changeScrollSpeed(-.5);
	if (leveldata[0].getPos().y <-100)
		changeScrollSpeed(-.75);
}

void Level::slowItemEffect()
{
	slowItem = true;
}

//0 is platforms, 1 items, in texts vector
//1 is basic, 2 is fake, 3 is tread R, 4 is tread L, 5 is spike, 6 is end for PLATFORMS
//1 is score, 2 is health, 3 is slow Fall, 4 is end Flag
void Level::loadTexture(std::vector<const sf::Texture*> texts)
{
	textureVect = texts;

	for (int x = 0; x < platNum; x++)
		leveldata[x].setTexture(texts.at(0));
	
	for (int x = 0; x < itemNum; x++)
		itemData[x].setTexture(*texts.at(1));

	setTextures();
}

//resets platform (and item) positions to original
void Level::resetLevel()
{
	scrollSpeed = -.25;
	delete[] leveldata;
	delete[] itemData;

	leveldata = new Platforms[platNum];
	itemData = new Item[itemNum];

	for (int x = 0; x < platNum; x++)
	{
		leveldata[x].setPos(xvals.at(x), yvals.at(x));
		leveldata[x].setSize(length.at(x));
		leveldata[x].setPos(xvals.at(x), yvals.at(x));
		leveldata[x].setType(platTypes.at(x));

		//reset broke plat texture
		sf::IntRect brokePlat(0, 0, 80, 10);
		if (leveldata[x].getType() == 2)
			leveldata[x].setTextureRect(brokePlat);
	}
	for (int x = 0; x < itemNum; x++)
	{
		itemData[x].setPos(iXVals.at(x), iYVals.at(x));
		itemData[x].setType(iType.at(x));
	}
	reLoadTextures();
	setTextures();

}

//leveldata is deleted and reset, requiring textures to be reloaded using copy of vector created when loading textures
void Level::reLoadTextures()
{
	for (int x = 0; x < platNum; x++)
		leveldata[x].setTexture(textureVect.at(0));

	for (int x = 0; x < itemNum; x++)
		itemData[x].setTexture(*textureVect.at(1));

	setTextures();
}

void Level::setTextures()
{
	sf::IntRect basePlat(135, 0, 80, 10);
	sf::IntRect brokePlat(0, 0, 80, 10);
	sf::IntRect endPlat(135, 21, 80, 20);

	sf::IntRect spikePlat(220, 0, 80, 19);
	sf::IntRect treadRPlat(306, 0, 80, 10);
	sf::IntRect treadLPlat(306, 15, 80, 10);

	sf::IntRect blueD(3, 6, 24, 18);
	sf::IntRect greenD(32, 3, 26, 25);
	sf::IntRect redD(67, 3, 16, 24);
	sf::IntRect healthPack(91, 3, 29, 23);
	sf::IntRect slowFall(123, 1, 24, 28);
	sf::IntRect endFlag(154, 1, 22, 28);


	for (int x = 0; x < platNum; x++)
	{
		switch (leveldata[x].getType())
		{
		case 1:
			leveldata[x].setTextureRect(basePlat);
			break;
		case 2:
			leveldata[x].setTextureRect(brokePlat);
			break;
		case 3:
			leveldata[x].setTextureRect(treadRPlat); //switch to tread plat
			break;
		case 4:
			leveldata[x].setTextureRect(treadLPlat); //switch to tread plat
			break;
		case 5:
			leveldata[x].setTextureRect(spikePlat); //switch to spike plat
			break;
		case 6:
			leveldata[x].setTextureRect(basePlat); //switch to end plat
			break;
		default:
			leveldata[x].setTextureRect(basePlat);
			break;
		}

	}

	for (int x = 0; x < itemNum; x++)
	{
		int randomColor = rand() % 3 + 1;
		switch (itemData[x].getType())
		{
		case 1: //set to random score item texture

			if (randomColor == 1)
				itemData[x].setTextureRect(blueD);
			if (randomColor == 2)
				itemData[x].setTextureRect(greenD);
			if (randomColor == 3)
				itemData[x].setTextureRect(redD);
			break;
		case 2: //set to health pack
			itemData[x].setTextureRect(healthPack);
			break;
		case 3:
			itemData[x].setTextureRect(slowFall);
			break;
		case 4:
			itemData[x].setTextureRect(endFlag);
			break;
		default:
			break;
		}

	}
}

void Level::animateBrokePlat(Platforms& plat)
{
	sf::Clock clock;

	sf::IntRect firstFrame(0, 15, 80, 10);
	sf::IntRect secFrame(0, 30, 80, 10);

	plat.setTextureRect(firstFrame);
	if (clock.getElapsedTime().asSeconds() > .5)
		plat.setTextureRect(secFrame);
}

double Level::getScrollSpeed()
{
	return scrollSpeed;
}
