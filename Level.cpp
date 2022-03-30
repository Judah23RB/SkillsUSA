#include "Level.h"


Level::Level()
{

}

void Level::loadLevel(std::string num)
{
	int temp;
	std::ifstream fhandle;
	std::string fileName = "LevelData/" + num + "/xval.txt";
	
	fhandle.open(fileName);
	if (fhandle.is_open())
	{
		while (fhandle >> temp)
		{
			platNum++;
			xvals.push_back(temp);
		}
		fhandle.close();
	}
	
	fileName = "LevelData/" + num + "/yval.txt";
	fhandle.open(fileName);
	if (fhandle.is_open())
	{
		while (fhandle >> temp)
		{
			yvals.push_back(temp);
		}
		fhandle.close();
	}
	
	fileName = "LevelData/" + num + "/length.txt";
	fhandle.open(fileName);
	if (fhandle.is_open())
	{
		while (fhandle >> temp)
		{
			length.push_back(temp);
		}
		fhandle.close();
	}
	
	fileName = "LevelData/" + num + "/platType.txt";
	fhandle.open(fileName);
	if (fhandle.is_open())
	{
		while (fhandle >> temp)
		{
			platTypes.push_back(temp);
		}
		fhandle.close();
	}
	
	initLevel();
	
}


Level::~Level()
{
	delete[] leveldata;
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

	endPlat = &leveldata[platNum - 1]; //final platform is end
	endPlat->setType(5); //end plat will have separate sprite
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
}


//handles platform collision, special platform collision, item collision
//reads in player bounding box
//playerSprite necessary for updating player Position
bool Level::collision(sf::FloatRect p, Player* player)
{
	for (int x = 0; x < platNum; x++)
	{
		switch (leveldata[x].getType())
		{
		case 1: //default
			if (leveldata[x].getPlatBounds().contains(p.left, p.top + p.height) || leveldata[x].getPlatBounds().contains(p.left + p.width, p.top + p.height))
				return true;
			break;
		case 2: //broken
			//add that it changes texture
			return false;
			break;
		case 3: //tread left
			//moves player to the left
			break;
		case 4: //tread right
			//moves player to the right
			break;
		default:
			break;
		}
	}
	return false;
}

Platforms* Level::getEndPlat()
{
	Platforms* temp = endPlat;
	return temp;
}

void Level::scrollLevel(sf::RenderWindow &w)
{
	levelProgression();
	for (int x = 0; x < platNum; x++)
		leveldata[x].scroll(scrollSpeed);
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

void Level::loadTexture(const sf::Texture* textr)
{
	for (int x = 0; x < platNum; x++)
		leveldata[x].setTexture(textr);
}

//0 is platforms, 1 items, 2 enemies in texts vector
//1 is basic, 2 is fake, 3 is tread left, 4 is tread right, 5 is end
void Level::loadTexture(std::vector<const sf::Texture*> texts)
{
	for (int x = 0; x < platNum; x++)
		leveldata[x].setTexture(texts.at(0));
	
	sf::IntRect basePlat(135, 0, 100, 10);
	sf::IntRect brokePlat(0, 0, 80, 10);
	sf::IntRect movePlat(300, 1, 110, 10);
	
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
			leveldata[x].setTextureRect(movePlat);
			break;
		default:
			leveldata[x].setTextureRect(basePlat);
		}

	}
		
}

double Level::getScrollSpeed()
{
	return scrollSpeed;
}
