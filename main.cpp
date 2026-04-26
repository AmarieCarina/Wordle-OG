#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "GridCell.h"
#include "PopUp.h"
#include "UI.h"
#include "Button.h"
#include "Key.h"
#include "Label.h"


int main() {
////////FEREASTRA PRINCIPALA
    sf::RenderWindow window(sf::VideoMode({800,800}), "WORDLE");

///////FONT
    sf::Font font;
    if (!font.openFromFile("assets/Roboto.ttf")) {
        std::cout<<"Eroare la incarcarea fontului";
    }

///////GRIDCELL MATRIX
    const int cols = 5;
    const int rows = 6;
    const float cell_size = 50.0f;
    const float margin = 10.0f;
    const float window_size = 800.0f;

    const float totalWidth=(cols*cell_size)+((cols-1)*margin);
    const float totalHeight=(rows*cell_size)+((rows-1)*margin);

    const float startX = (window_size - totalWidth)/2.0f;
    const float startY = (window_size - totalHeight)/2.0f - float(100);

    std::vector<GridCell> grid;

    for (int r = 0; r< rows; r++) {
        for (int c = 0; c < cols; c++) {
            float x = startX + c * (cell_size + margin);
            float y = startY + r * (cell_size + margin);
            grid.emplace_back(x,y,cell_size, font);
        }
    }

////////POP UP INTRO + BUTON PLAY
    std::unique_ptr<UI> Intro = std::make_unique<PopUp>(150.f, 150.f, 500.f, 500.f);
    Button playButton(200.0f,200.0f,70.0f,40.0f,"Play",font);
    playButton.setOnClick([&Intro]() {
        if (Intro) {
            Intro->setVisible(false);
        }
    });

/////////POP UP INSTRUCTIUNI DE JOC + BUTON CLOSE
    auto Instr = std::make_unique<PopUp>(150.f, 150.f, 500.f, 500.f);
    Instr->addElement(std::make_unique<GridCell>(375.f, 350.f, 50.f, font));
    Instr->addElement(std::make_unique<Label>(400.f,200.f, "HOW TO PLAY", font, 30));

    Button closeButton(600.0f, 160.0f, 40.0f, 40.0f, "X", font);
    closeButton.setOnClick([&Instr]() {
        if (Instr) {
            Instr->setVisible(false);
        }
    });

//////////KEYBOARD
    std::vector<std::string> layout {
            "QWERTYUIOP",
            "ASDFGHJKL",
            "ZXCVBNM"
    };
    std::vector<Key> keyboard;

    float xInitial = 150.0f; //stanga
    const float yInitial = 550.0f; //jos
    const float offx = 50.0f; //distanta dintre taste sau randuri
    const float offy = 70.0f;
    const float kWidth = 40.0f;
    const float kHeight = 55.0f;
    float offset=1;

    for (int r=0; r < layout.size(); r++) {
        for (int c = 0; c < layout[r].size(); c++) {
            float x = xInitial + c * offx;
            float y = yInitial + r * offy;
            keyboard.emplace_back(x,y,kWidth, kHeight,layout[r][c],font);
        }
        xInitial += 20.0f * offset;
        offset *= 2.5;
    }


//////////////////////////////////////////////////////////////////////////////////
////////////////// B U C L A   W H I L E /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

    while (window.isOpen()) {

        while (const std::optional event=window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseBtn->button == sf::Mouse::Button::Left) {
                    //CLICK STANGA

                    //transformam pozitia mouse-ului in pixeli
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (Instr && Instr->getVisible() && closeButton.isMouseOver(mousePos)) {
                        closeButton.click();
                    }

                    if (Intro && Intro->getVisible() && playButton.isMouseOver(mousePos)) {
                        playButton.click();
                    }

                    for (auto& k:keyboard) {
                        if (k.isMouseOver(mousePos)) {
                            k.click();
                        }
                    }

                }
            }

        }

        window.clear(sf::Color::Black);
        ////chestii care se repeta la infinit
        for (auto& celula:grid) {
            celula.draw(window);
        }

        for (auto& k:keyboard) {
            k.draw(window);
        }

        if (Instr && Instr->getVisible()) {
            Instr->draw(window);
            closeButton.draw(window);
        }

        if (Intro && Intro->getVisible()) {
            Intro->draw(window);
            playButton.draw(window);
        }




        ///////////
        window.display();
    }
    return 0;
}