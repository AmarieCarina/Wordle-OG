#include "../include/UI.h"

//constructori
UI::UI(float x, float y): position{x,y}, isVisible{true}{}
UI::~UI()=default;

//getters, setters pentru vizibilitate
inline void UI::setVisible(bool visible) {isVisible=visible;}
inline bool UI::getVisible() const {return isVisible;}

//setter pentru vizibilitate
inline void UI::setPosition(sf::Vector2f pos){position=pos;}