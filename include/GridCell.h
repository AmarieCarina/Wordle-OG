#ifndef POO2_GRIDCELL_H
#define POO2_GRIDCELL_H
#include "UI.h"
enum class CellState {
    Default,
    Absent,
    Present,
    Correct
};

class GridCell : public UI {
private:
    sf::RectangleShape box; //container-ul in sine al celulei
    sf::Text letter;
public:
    //constructori
    GridCell(float x, float y, float size, const sf::Font& font);
    ~GridCell() override = default;

    //setters
    void setLetter(char c);
    void setState(CellState state); //culoarea

    //redefinim functia virtuala de desenare
    void draw(sf::RenderWindow& window) override;
};
#endif //POO2_GRIDCELL_H