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
	sf::RenderWindow mWindow(sf::VideoMode(640, 480), "Blunderbuss", sf::Style::Default);

	LayeredDraw ld;
	//TileManager tm(&ld, "Media/Levels/LevelTut/LayerGroup.txt");

	sf::Texture texture;
	texture.loadFromFile("Media/TileSet/BoxMan.png");
	sf::Sprite player(texture);
	auto rect = player.getTextureRect();
	player.setOrigin(player.getOrigin() + sf::Vector2f( rect.width, rect.height ) / 2.f);

	ld.addDrawable(player, 200);

	Parallax::ParallaxHolder holder;
	holder.load(Parallax::ParallaxEnum::Cyberpunk_back, "Media/Parallax/Cyberpunk/back-buildings.png");
	holder.load(Parallax::ParallaxEnum::Cyberpunk_far, "Media/Parallax/Cyberpunk/far-buildings.png");
	holder.load(Parallax::ParallaxEnum::Cyberpunk_fore, "Media/Parallax/Cyberpunk/foreground.png");

	Parallax par(&holder, &ld);
	par.addLayer(Parallax::ParallaxEnum::Cyberpunk_back, -199, 4.f, 50.f, 0.f, 0.f);
	par.addLayer(Parallax::ParallaxEnum::Cyberpunk_far, -200, 1.5f, 5.f, 0.f, 0.f);
	par.addLayer(Parallax::ParallaxEnum::Cyberpunk_fore, -198, 1.0f, 1.0f, 0.f, 0.f);
	par.setScale(Parallax::ParallaxEnum::Cyberpunk_back, 3.f, 3.f);
	par.setScale(Parallax::ParallaxEnum::Cyberpunk_far, 3.f, 3.f);
	par.setScale(Parallax::ParallaxEnum::Cyberpunk_fore, 3.f, 3.f);


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

	DynamicRingBuffer<int> buf(3);

	std::random_device rd;
	std::mt19937 eng(rd());
    std::uniform_int_distribution<int> dist(0,2);
    std::uniform_int_distribution<int> dist2(1, 15);
    for(int i = 0; i < 20; i++)
    {
        int action = dist(eng);
        int res_push;
        std::optional<int> res_pop;
        switch(action)
        {
            case 0:
                res_push = dist2(eng);
                buf.push(res_push);
                std::cout << "Pushed: " << res_push << " = > ";
                for(auto item : buf)
                    std::cout << item << " ";
                std::cout << "\n";
                break;
            case 1:
                res_pop = buf.pop();
                std::cout << "Popped: " << res_pop.value_or(-1) << " = > ";
                for(auto item : buf)
                    std::cout << item << " ";
                std::cout << "\n";
                break;
            case 2:
                res_push = dist2(eng);
                buf.emplace(res_push);
                std::cout << "Emplaced: " << res_push << " = > ";
                for(auto item : buf)
                    std::cout << item << " ";
                std::cout << "\n";
                break;
            case 3:
                break;
            default:
                break;
        }
    }
}



//
//DynamicRingBuffer<std::pair<int,int>> buf(3);
//auto res = buf.pop();
//if(!res)    //optional
//std::cout << "Empty\n";
//std::cout << buf.capacity() << "\n";
//buf.push({2,3});
//buf.push({1,2});
//buf.push({4,5});
//buf.push({3,3});
//for(auto item = buf.pop(); item ; item = buf.pop() )
//std::cout << item.value().first << "," << item.value().second << "  ";
//std::cout << "\n";
//std::cout << buf.capacity() << "\n";
//
//for(int i = 0 ; i < 8 ; i++)
//buf.push({2,2});
//
//auto& res3 = buf.emplace(3,4);
//std::cout << res3.first << "," << res3.second << "\n";
//buf.pop();
//buf.pop();
//for(auto item = buf.pop(); item ; item = buf.pop() )
//std::cout << item.value().first << "," << item.value().second << "  ";
//std::cout << "\n";
//std::cout << buf.capacity() << "\n";
//buf.pop();
//buf.pop();
//buf.pop();
//auto& resres = buf.emplace(2,5);
//resres.first = 6;
//resres.second = 9;
//for(auto item = buf.pop(); item ; item = buf.pop() )
//std::cout << item.value().first << "," << item.value().second << "  ";
//std::cout << "\n";