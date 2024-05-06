#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    sf::Texture texture;
    sf::Sprite sprite;
    texture.setSmooth(true);

    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].position = sf::Vector2f(10.f, 10.f);
    triangle[1].position = sf::Vector2f(100.f, 10.f);
    triangle[2].position = sf::Vector2f(100.f, 100.f);

    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Green;
    triangle[2].color = sf::Color::Blue;

    if (!texture.loadFromFile("C:/Users/jacke/Documents/Dev/SFML/FirstProject/cmake-sfml-project/NewtonDetail.png"))
    {
        std::cerr << "could not load file";
    }

    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
       
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.draw(triangle);
        window.display();
    }
}