#include <iostream>
#include <SFML/Graphics.hpp>
#include <LayeredDraw.hpp>
#include <TileManager.hpp>
#include <Parallax.hpp>
#include <FixedRingBuffer.hpp>
#include <DynamicRingBuffer.hpp>
#include <random>

int main()
{
    sf::Vector2u windowSize(1280u, 800u);
	sf::RenderWindow mWindow(sf::VideoMode(windowSize.x ,windowSize.y), "Blunderbuss", sf::Style::Default);

	LayeredDraw ld;
	//TileManager tm(&ld, "Media/Levels/LevelTut/LayerGroup.txt");

	sf::Texture texture;
	texture.loadFromFile("Media/TileSet/BoxMan.png");
	sf::Sprite player(texture);
	auto rect = player.getTextureRect();
	player.setOrigin(player.getOrigin() + sf::Vector2f( rect.width, rect.height ) / 2.f);

	ld.addDrawable(player, 200);

	sf::Clock clock;
	sf::Time dt = clock.restart();
	std::cout << std::boolalpha;
	while (mWindow.isOpen())
	{
		sf::Event event = sf::Event();
		sf::Vector2f offset;
		while (mWindow.pollEvent(event))
		{
			offset = { 0.f , 0.f };
			if (event.type == sf::Event::Closed)
				mWindow.close();
			else if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					mWindow.close();
					break;
				case sf::Keyboard::Right:
					offset.x += 1.f;
					break;
				case sf::Keyboard::Left:
					offset.x -= 1.f;
					break;
				case sf::Keyboard::Up:
					offset.y -= 1.f;
					break;
				case sf::Keyboard::Down:
					offset.y += 1.f;
					break;
				}
			}
		}
		auto defview = mWindow.getView();
		defview.move(offset);
		mWindow.setView(defview);

		par.update(sf::Vector2i(player.getPosition()), sf::Vector2i(mWindow.getSize()));
		player.setPosition(defview.getCenter());

		mWindow.clear();
		mWindow.draw(ld);
		mWindow.display();
	}
}
