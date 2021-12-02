#ifndef NBODY_H
#define NBODY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
class CelestialBody : public Drawable {
	public:
		CelestialBody();
		CelestialBody(double xpos, double ypos, double xvel, double yvel, double mass, string filename); 
		void begin_draw();
		friend istream& operator>> (istream&, CelestialBody&);
		void transform(double);
		double get_xposition();
		double get_yposition();
		double get_xvelocity();
		double get_yvelocity();
		double get_input_mass();
		void set_xposition(double value);
		void set_yposition(double value);
		void set_xvelocity(double value);
		void set_yvelocity(double value);
		string get_input_file();
	private:
		double xposition;
		double yposition;
		double xvelocity;
		double yvelocity;
		double input_mass;
		string input_file; 
		Texture input_texture;
		Image input_image;
		Sprite input_sprite;
		virtual void draw(RenderTarget&, RenderStates) const;
};
class Universe{
	public:
		vector<CelestialBody*> body;
		void create_celestial_body();
		void displayUniverse();
		void step(double seconds);
	private:
		double radius;
};
#endif
