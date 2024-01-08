#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

void render(sf::Window& window) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.0, 1.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-1.0, -1.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(1.0, -1.0);
    glEnd();

    glFlush();
    window.display();
}

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    sf::Window window(sf::VideoMode(800, 600), "SFML OpenGL", sf::Style::Default, settings);

    window.setActive(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        render(window);
    }

    return 0;
}

