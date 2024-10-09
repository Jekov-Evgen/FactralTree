#include <SFML/Graphics.hpp>

int height = 600;
int width = 600;

void lineDrawing(sf::RenderWindow& simulationWindow, int branchNumber, sf::Vector2f startPosition, float angle, int limitation) {
    if (branchNumber > limitation) {
        return;
    }

    sf::RectangleShape branch(sf::Vector2f(5, 50));
    branch.setFillColor(sf::Color::Black);
    branch.setOrigin(2.5, 50);

    branch.setPosition(startPosition);
    branch.setRotation(angle);

    simulationWindow.draw(branch);

    float radians = angle * 3.14159265 / 180;
    sf::Vector2f endPosition = startPosition + sf::Vector2f(50 * sin(radians), -50 * cos(radians));

    float leftAngle = angle - 30;
    float rightAngle = angle + 30;

    lineDrawing(simulationWindow, branchNumber + 1, endPosition, leftAngle, limitation);
    lineDrawing(simulationWindow, branchNumber + 1, endPosition, rightAngle, limitation);
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(height, width), "SFML works!");
    sf::View view(sf::FloatRect(0, 0, 500, 500));
    window.setView(view);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {

                if (event.mouseWheelScroll.delta > 0) {
                    view.zoom(1.5);
                }
                else {
                    view.zoom(1.4);
                }

                window.setView(view);
            }
        }

        window.clear(sf::Color::White);

        lineDrawing(window, 0, sf::Vector2f(width / 2, height - 20), 360, 16);

        window.display();
    }

    return 0;
}