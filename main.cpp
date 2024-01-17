#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include<ctime>

bool movement_allowed(sf::Vector2f);
void render_apples(sf::Vector2f);
void collect_apple();
void draw_snake();

sf::Clock timer;
sf::Vector2f apple_arr[10];
sf::Vector2f position[99];
sf::Vector2f size =sf::Vector2f(0.05f,0.05f);
time_t start = time(0);
int body_block_count = 3;
int apples_existing = 0;
int set_time = 1;
int move_time = 1;
float speed = 0.09f;


int main(int argc, char** argv) {

	for(int i = 0; i<6;i++){
	
		position[i].x = (float)i/speed;
		position[i].y = 0.0f; 
	
	}


    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    sf::RenderWindow window(sf::VideoMode(1920, 1080),"SFML OpenGL", sf::Style::Default, settings);
    window.setActive(true);
    glEnable(GL_TEXTURE_2D);

    sf::Vector2f velocity(speed, 0.0f); 

    sf::Clock clock;

    while (window.isOpen()) {

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
	if(timer.getElapsedTime().asMilliseconds() >= 200){
		for(int i = body_block_count;i>0;i--){
		position[i].x = position[i-1].x;
		position[i].y = position[i-1].y;
		}
        position[0].x += velocity.x;
	position[0].y += velocity.y;
	timer.restart();
	}
       
        if (movement_allowed(sf::Vector2f(window.getSize().x,window.getSize().y))) {
            window.close();
        }
 	
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
        glOrtho(-1.0, 1.0, -1.0 * window.getSize().y / window.getSize().x, 1.0 * window.getSize().y / window.getSize().x, -1.0, 1.0);
       
	draw_snake();


	render_apples(sf::Vector2f(window.getSize().x,window.getSize().y));
        // Display the rendered content
        window.display();
    }

    return 0;
}

bool movement_allowed(sf::Vector2f border) {
    if (position[0].x >= border.x/1000+0.1 || position[0].x <=  -border.x/1000-0.1 || position[0].y >= border.y/1000+0.1 || position[0].y <= -border.y/1000-0.1) {
    return true;
    }
	for(int i = 0;i<=body_block_count;i++){
		for(int j = 0;j<=body_block_count;j++){
			//std::cout<<position[i].x<<position[j].x<<"x \n";
			//std::cout<<position[i].y<<position[j].y<<"y \n";
			if(position[i].x == position[j].x && position[i].y == position[j].y && i != j){
				//std::cout<<"its a match!!!!!\n";
				return true;
			}
		}
		//std::cout<<"********************\n";
	}
return false;
}



void render_apples(sf::Vector2f border){
time_t now = time(0);
time_t diff = now - start;
bool minus_apples = false;
	for(int i = 0; i<apples_existing;i++){
 	   if(apple_arr[i].x < position[0].x + size.x && apple_arr[i].x > position[0].x - size.x && apple_arr[i].y < position[0].y + size.y && apple_arr[i].y > position[0].y - size.y){
		   body_block_count++;
		apple_arr[i].x = apple_arr[apples_existing - 1].x;
		apple_arr[i].y = apple_arr[apples_existing - 1].y;
		apple_arr[apples_existing - 1].x = 9.0f;
		apple_arr[apples_existing - 1].y = 9.0f;
		minus_apples = true;
	   }
	   if(minus_apples){
	   	   apples_existing--;
		   minus_apples = false;
	   }
	  //std::cout<<vector_arr[1].x<<"vector X\n";
	  //std::cout<<position[0].x<<"position X\n";
	  //std::cout<<position[0].y<<"position Y\n";
	  //std::cout<<vector_arr[1].y<<"vector Y\n";
	}

if(diff > set_time && apples_existing < 5){
set_time += 2;
srand(time(NULL));
 float random_x = (rand() / (float)RAND_MAX) * 20 - 9;
 float random_y = (rand() / (float)RAND_MAX) * 20 - 9;
 for(int i = 0;i < body_block_count;i++){
 if(position[i].x == (int)random_x*speed && position[i].y == (int)random_y*speed){
while(position[i].x == (int)random_x*speed && position[i].y == (int)random_y*speed){
     srand(time(NULL));
 	 random_x = (rand() / (float)RAND_MAX) * 20 - 9;
	 random_y = (rand() / (float)RAND_MAX) * 20 - 9;
	 }
 }
 }
apple_arr[apples_existing] = sf::Vector2f((int)random_x*speed ,(int)random_y*speed);
 //std::cout<<"yello: " <<vector_arr[1].x<<"\n";
 //std::cout<<"yello: " <<vector_arr[1].y<<"\n";
 apples_existing++;

}

for(int i = 0;i < apples_existing;i++){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(apple_arr[i].x,apple_arr[i].y, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex2f(0.02f, 0.02f);
        glVertex2f(-0.02f, 0.02f);
        glVertex2f(-0.02f, -0.02f);
        glVertex2f(0.02f, -0.02f);
	glEnd();
	glPopMatrix();
	}
}

void draw_snake(){

	for(int i = 0; i<body_block_count;i++){

        glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
        glTranslatef(position[i].x,position[i].y, 0.0f);

        glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(size.x, size.y);
        glVertex2f(-size.x, size.y);
        glVertex2f(-size.x, -size.y);
        glVertex2f(size.x, -size.y);
        glEnd();
        glPopMatrix();
	}
}
