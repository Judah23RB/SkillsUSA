#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Button : public sf::Drawable, public sf::Transformable
{
public:
	Button(const std::string, const int, sf::Font&);
	Button(const std::string, const int, sf::Font&, const sf::RectangleShape);
	~Button();

	sf::FloatRect getBounds();
	int getValue();
	void setColor(sf::Color);
private:
	sf::RectangleShape base;
	sf::Font* font;
	sf::Text label;
	int value;

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

};

