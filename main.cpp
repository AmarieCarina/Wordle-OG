#include <SFML/Graphics.hpp>
#include "GridCell.h"
#include <iostream>
int main() {
    //ferestra
    sf::RenderWindow window(sf::VideoMode({800,800}), "WORDLE");

    //font
    sf::Font font;
    if (!font.openFromFile("assets/Roboto.ttf")) {
        std::cout<<"Eroare la incarcarea fontului";
    }

    //gridcells
    const int cols = 5;
    const int rows = 6;
    const float cell_size = 50.0f;
    const float margin = 10.0f;
    std::vector<GridCell> grid;
    for (int r = 0; r< rows; r++) {
        for (int c = 0; c < cols; c++) {
            float x = 150.0f + c * (cell_size + margin);
            float y = 150.0f + r * (cell_size + margin);
            grid.emplace_back(x,y,cell_size, font);
            grid[c].setState(CellState::Default);
        }
    }


    while (window.isOpen()) {

        while (const std::optional event=window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        ////chestii care se repeta la infinit
        for (auto& celula:grid) {
            celula.draw(window);
        }

        window.display();
    }
    return 0;
}