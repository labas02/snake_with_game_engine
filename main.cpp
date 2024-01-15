#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

bool movement_allowed(sf::Vector2f,sf::Vector2f);
void render_apples();
sf::Vector2f vector_arr[10];


int main(int argc, char** argv) {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    sf::RenderWindow window(sf::VideoMode(1920, 1080),"SFML OpenGL", sf::Style::Fullscreen, settings);
    window.setActive(true);
    glEnable(GL_TEXTURE_2D);

    float speed = 0.5f;
    float posX = 0.0f, posY = 0.0f;
    sf::Vector2f velocity(0.0f, 0.0f); // Start with no movement

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::W:
                            velocity.x = 0.0f;
                            velocity.y = speed;
                            break;
                        case sf::Keyboard::S:
                            velocity.x = 0.0f;
                            velocity.y = -speed;
                            break;
                        case sf::Keyboard::A:
                            velocity.x = -speed;
                            velocity.y = 0.0f;
                            break;
                        case sf::Keyboard::D:
                            velocity.x = speed;
                            velocity.y = 0.0f;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        // Update position based on velocity
        posX += velocity.x * dt;
        posY += velocity.y * dt;

        // Check if movement is allowed
        if (movement_allowed(sf::Vector2f(posX, posY),sf::Vector2f(window.getSize().x,window.getSize().y))) {
            window.close();
        }

        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
        glOrtho(-1.0, 1.0, -1.0 * window.getSize().y / window.getSize().x, 1.0 * window.getSize().y / window.getSize().x, -1.0, 1.0);
        // Draw the square
        glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
        glTranslatef(posX, posY, 0.0f);

        glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.05f, 0.05f);
        glVertex2f(-0.05f, 0.05f);
        glVertex2f(-0.05f, -0.05f);
        glVertex2f(0.05f, -0.05f);
        glEnd();
        glPopMatrix();


	render_apples();
        // Display the rendered content
        window.display();
    }

    return 0;
}

bool movement_allowed(sf::Vector2f pos, sf::Vector2f border) {
    if (pos.x > border.x/1000 || pos.x <  -border.x/1000 || pos.y > border.y/1000 || pos.y < -border.y/1000) {
       std::cout << "true\n x: " << border.x/1000 << "\nY: " << border.y/1000;
        return true;
    }
    std::cout << "false\n x: " << border.x/1000 << "\nY: " << border.y/1000;
    return false;
}

void collect_apple(){

}

void render_apples(){

vector_arr[1] = sf::Vector2f(0.8,0.9);
 //std::cout<<"yello: " <<vector_arr[1].x<<"\n";
 //std::cout<<"yello: " <<vector_arr[1].y<<"\n";

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(vector_arr[1].x,vector_arr[1].y, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex2f(0.02f, 0.02f);
        glVertex2f(-0.02f, 0.02f);
        glVertex2f(-0.02f, -0.02f);
        glVertex2f(0.02f, -0.02f);
	glEnd();
	glPopMatrix();
}

