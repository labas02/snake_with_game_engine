#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char** argv) {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    sf::Window window(sf::VideoMode(1920, 1020), "SFML OpenGL", sf::Style::Default, settings);
    window.setActive(true);
    glEnable(GL_TEXTURE_2D); 
    float speed = 0.2f;
    float posX = 0.0f, posY = 0.0f;
    float velX = speed, velY = 0.0f; // Start moving right by default

    sf::Clock clock;

    while(window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {

            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::W:
                            velX = 0.0f;
                            velY = speed;
                            break;
                        case sf::Keyboard::S:
                            velX = 0.0f;
                            velY = -speed;
                            break;
                        case sf::Keyboard::A:
                            velX = -speed;
                            velY = 0.0f;
                            break;
                        case sf::Keyboard::D:
                            velX = speed;
                            velY = 0.0f;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        posX += velX * dt;
        posY += velY * dt;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(posX, posY, 0.0f);

        glBegin(GL_TRIANGLES);
        glVertex2f(0.0, 0.1);
        glVertex2f(-0.1, -0.1);
        glVertex2f(0.1, -0.1);
        glEnd();

        glFlush();
        window.display();
    }

    return 0;
}

