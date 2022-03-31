#include "Button.h"
#include <string>

// Constructor, applies default values to sf::RectangleShape base
Button::Button(const std::string labelText, const int initValue, sf::Font& f)
{
	font = &f;

	// Initialize label
	label.setString(labelText);
	label.setFillColor(sf::Color::Black);
	label.setLetterSpacing(1.1);


	if (!font->loadFromFile("ARCADECLASSIC.ttf"))
	{
		// Error
	}

	label.setFont(*font);
	label.setCharacterSize(36);

	// Initialize value
	value = initValue;

	// Initialize base
	base.setFillColor(sf::Color::White);
	base.setSize(sf::Vector2f(400.f, 50.f));
	

	// Center the label
	sf::FloatRect labelSize = label.getLocalBounds();
	float labelX = base.getPosition().x + ((base.getSize().x - labelSize.width) / 2);
	float labelY = base.getPosition().y + ((base.getSize().y - labelSize.height) / 2);

	label.setPosition(labelX, labelY - (.25 * base.getSize().y));
}

// Constructor for customizing sf::RectangleShape base
Button::Button(const std::string labelText, const int initValue, sf::Font& f, const sf::RectangleShape initRect)
	: Button(labelText, initValue, f)
{
	// Initialize base
	base = initRect;

	// Recenter the label
	sf::FloatRect labelSize = label.getLocalBounds();
	float labelX = base.getPosition().x + ((base.getSize().x - labelSize.width) / 2);
	float labelY = base.getPosition().y + ((base.getSize().y - labelSize.height) / 2);

	label.setPosition(labelX, labelY - (.25 * base.getSize().y));
}

Button::Button(const std::string labelText, const int initValue, sf::Font& f, const int fontSize) : Button(labelText,initValue,f)
{
	label.setCharacterSize(fontSize);
	
	sf::FloatRect labelSize = label.getLocalBounds();
	float labelX = base.getPosition().x + ((base.getSize().x - labelSize.width) / 2);
	float labelY = base.getPosition().y + ((base.getSize().y - labelSize.height) / 2);

	label.setPosition(labelX, labelY - (.25 * base.getSize().y));
}

Button::Button(const std::string labelText, const int initValue, sf::Font& f, const sf::RectangleShape initRect, const int fontSize) : Button(labelText, initValue, f, initRect)
{
	label.setCharacterSize(fontSize);

	sf::FloatRect labelSize = label.getLocalBounds();
	float labelX = base.getPosition().x + ((base.getSize().x - labelSize.width) / 2);
	float labelY = base.getPosition().y + ((base.getSize().y - labelSize.height) / 2);

	label.setPosition(labelX, labelY - (.33 * base.getSize().y));
}

Button::~Button()
{

}

// Gets called by window.draw(MenuButton)
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform();

	target.draw(base, states);
	target.draw(label, states);
}

// Returns a FloatRect containing base, used to detect clicks
sf::FloatRect Button::getBounds()
{
	return getTransform().transformRect(base.getGlobalBounds());
}

// Returns the button's value
int Button::getValue()
{
	return value;
}

void Button::setColor(sf::Color color)
{
	base.setFillColor(color);
}