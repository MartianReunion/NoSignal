#include <SFML/Graphics.hpp>
#include "log/logger.hpp"
int main()
{
    Log::LogManager::start();
    Log::Logger logger("main");
    logger.debug("This is a debug message");
    logger.info("This is an info message");
    logger.success("This is a success message");
    logger.warning("This is a warning message");
    logger.error("This is an error message");
    logger.fatal("This is a fatal message");

    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }
    Log::LogManager::stop();
    return 0;
}