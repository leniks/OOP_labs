#include <vector>

#include "figures.hpp"

int main() {
    int command = 1;
    Figures figuresArr;
    std::cout << "Command:" << std::endl <<
    "1 - create new figure;" << std::endl <<
    "2 - delete the figure;" << std::endl <<
    "3 - print the coordinates;" << std::endl <<
    "4 - calculate the square of the figures;" << std::endl <<
    "5 - calculate the center of the figure;" << std::endl <<
    "6 - calculate the total area of figures;" << std::endl <<
    "0 - exit." << std::endl;
    while (command) { 
        std::cin >> command;
        if (command > 6 || command < 0) {
            std::cout << "Wrong command" << std::endl;
        }
        switch (command) {
        case 1:
            std::cout << "Figures:" << std::endl <<
                "1 - Trapezoid" << std::endl <<
                "2 - Rhombus" << std::endl <<
                "3 - Pentagon" << std::endl;
                int figureCommand;
                std::cin >> figureCommand;
                Figure *f;
                if (figureCommand == 1) {
                    f = new Trapezoid(std::cin);
                } else if (figureCommand == 2) {
                    f = new Rhombus(std::cin);
                } else if (figureCommand == 3) {
                    f = new Pentagon(std::cin);
                } else {
                    std::cout << "Wrong command" << std::endl;
                }
                figuresArr.addFigure(f);
                break;
            case 2:
                std::cout << "Enter the index" << std::endl;
                int indexComand;
                std::cin >> indexComand;
                figuresArr.deleteFigure(indexComand);
                break;
            case 3:
                for (size_t i = 0; i < figuresArr.getSize(); ++i) {
                    Figure* f = figuresArr.getFigure(i);
                    std::cout << "Coordinates: ";
                    f->print(std::cout);
                }
                break;
            case 4:
                for (size_t i = 0; i < figuresArr.getSize(); ++i) {
                    Figure* f = figuresArr.getFigure(i);
                    std::cout << "Area: " << f->square() << std::endl;
                }
                break;
            case 5:
                for (size_t i = 0; i < figuresArr.getSize(); ++i) {
                    Figure* f = figuresArr.getFigure(i);
                    std::cout << "Center: " << f->center() << std::endl;
                }
                break;
            case 6:
                std::cout << "Total area: " << figuresArr.totalArea() << std::endl;
                break;
        }
    }
    return 0;
}
