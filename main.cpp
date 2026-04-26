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
#include "GE.h"


int main() {
////////FEREASTRA PRINCIPALA
    sf::RenderWindow window(sf::VideoMode({800,800}), "WORDLE");

///////FONT
    sf::Font font;
    if (!font.openFromFile("assets/Roboto.ttf")) {
        std::cout<<"Eroare la incarcarea fontului";
    }

///////GAME ENGINE
    GE engine(font);

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


//////////////////////////////////////////////////////////////////////////////////
////////////////// B U C L A   W H I L E /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

    while (window.isOpen()) {

        while (const std::optional event=window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            //INPUT MOUSE
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

                    auto& keyboard = engine.getKeyboard();
                    for (auto& k:keyboard) {
                        if (k.isMouseOver(mousePos)) {
                            k.click();
                            engine.addLetter(k.getLetter());
                        }
                    }

                }


            }

            //INPUT TASTATURA FIZICA (litere)
            if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                engine.addLetter(static_cast<char>(textEvent->unicode));

            }

            //INPUT TASTATURA FIZICA (enter+backspace)
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Enter) {
                    engine.checkGuess();
                }
                if (keyEvent->code == sf::Keyboard::Key::Backspace) {
                    engine.deleteLastLetter();
                }
            }
        }

        window.clear(sf::Color::Black);
        ////chestii care se repeta la infinit
        engine.draw(window);

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