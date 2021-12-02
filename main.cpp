#include "Nbody.h"
int main(int argc, char* argv[])
{
	Universe u;
	u.create_celestial_body();
	Vector2u size(512,512);
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "The Universe!");
   	sf::Image input_image;
    	sf::Texture input_texture;
   	sf::Sprite input_sprite;
	string path = "nbody/starfield.jpg";
	input_image.loadFromFile(path);
        input_texture.loadFromImage(input_image);
	input_sprite.setTexture(input_texture);
	double start_time = 0;
	double end_time = atof(argv[1]);
	double time_step = atof(argv[2]);
	double count = 0;
	sf::Music music;
	if (!music.openFromFile("nbody/2001.wav")){
    		return -1; // error
	}
	music.play();
	sf::Clock clock;
	sf::Text text;
	while (window.isOpen())
    	{
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	sf::Time elapsed1 = clock.getElapsedTime();
	cout << "Elapsed Time: " << elapsed1.asMicroseconds() << endl; 
	if( count >= 5){    //takes a mini gap between each step to see it better
		if (start_time >= end_time) {
                	window.close();
                	break;
            	}
            	start_time += time_step;
            	u.step(time_step);
            	count = 0;
	}
	count++;
	window.clear(Color::Black);
        u.displayUniverse();
        window.draw(input_sprite);
        for(CelestialBody *b :u.body){
                window.draw(*b);
        }
        window.display();
    }

    return 0;
}
