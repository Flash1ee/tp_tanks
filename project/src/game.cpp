#include <SFML/Graphics.hpp>

#include "game_map.hpp"

#include "objects.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tanks");

    PlayerTank playerTank("../textures/pltank.bmp", 100, 100, 2, 2, 29, 29);
    Map map("../maps/1.txt", "../textures/sprites.png");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        playerTank.actions();

        window.clear();
        map.drawMap(window);
        window.draw(playerTank.getSprite());
        window.display();
    }
}
