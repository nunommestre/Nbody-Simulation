#include "Nbody.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//default constructor
CelestialBody::CelestialBody(){
}
//constructor that intializes all data members and draws the image/makes sprite
CelestialBody::CelestialBody(double xpos, double ypos, double xvel, double yvel, double mass, string filename):xposition(xpos), yposition(ypos), xvelocity(xvel), yvelocity(yvel), input_mass(mass), input_file(filename){
	begin_draw();
	
}
//overload to make celestialbody drawable
void CelestialBody::draw(RenderTarget& target, RenderStates states) const{
	target.draw(input_sprite, states); 	
}
//draw function to make constructor cleaner
void CelestialBody::begin_draw(){
        input_image.loadFromFile("nbody/" + input_file);
        input_texture.loadFromImage(input_image);
        input_sprite.setTexture(input_texture);
}
//overloaded extraction operator to read in file data to the celestial body
istream& operator>>(istream& in, CelestialBody& right){
	in >> right.xposition;
	in >> right.yposition;
        in >> right.xvelocity;
        in >> right.yvelocity;
        in >> right.input_mass;
	in >> right.input_file;
	right.begin_draw();
	return in;
}
//Scales the images to the universes radius
void CelestialBody::transform(double radius){
	double scale = 500;
	double xscale = xposition / (radius * 2) * scale + 0.5 * scale;
	double yscale = yposition / (radius * 2) * scale + 0.5 * scale;
	input_sprite.setPosition(xscale,yscale);	
}
//Accesor Functions (getter functions)
double CelestialBody::get_xposition(){
	return xposition;
}
double CelestialBody::get_yposition(){
	return yposition;
}
double CelestialBody::get_xvelocity(){
	return xvelocity;
}
double CelestialBody::get_yvelocity(){
	return yvelocity;
}
double CelestialBody::get_input_mass(){
	return input_mass;
}
string CelestialBody::get_input_file(){
	return input_file;
}
//Mutator or "Setter" functions
void CelestialBody::set_xposition(double value){
	xposition = value;
}
void CelestialBody::set_yposition(double value){
	yposition = value;
}
void CelestialBody::set_xvelocity(double value){
	xvelocity = value;
}
void CelestialBody::set_yvelocity(double value){
	yvelocity = value;
}
//creates all of the celestial bodies and stores a vector of pointers to them. Whem cin >> *b is called then the overloaded extraction operator loads the file data into the bodies
void Universe::create_celestial_body(){
	int n;
	double r;
	cin >> n;
	cin >> r;
	radius = r;
	for(int i = 0; i < n; i++){
		CelestialBody* b = new CelestialBody;
		cin >> *b;
		body.push_back(b);
	}
}
//call this before you draw the bodies to ensure they are scaled to the universe radius
void Universe::displayUniverse(){
	for(CelestialBody* b :body){
		b->transform(radius);
	}
}
void Universe::step(double seconds){
		double new_radius;
		double Force;
		double new_xvelocity;
		double new_yvelocity;
		double new_xposition;
		double new_yposition;
		double xForce;
		double yForce;
		double xAcceleration;
		double yAcceleration;
		for(unsigned int i = 0; i < body.size(); i++){
                        xForce = 0;
                        yForce = 0;
               		for(unsigned int j = 0; j < body.size(); j++){
				if(i == j){
					continue;
				}
				new_radius = sqrt(pow(body[j]->get_xposition() - body[i]->get_xposition(), 2) + pow(body[j]->get_yposition() - body[i]->get_yposition(), 2));
                		Force = (6.67e-11) * (body[j]->get_input_mass() * body[i]->get_input_mass()) / pow(new_radius, 2);
                		xForce += Force * ((body[j]->get_xposition() - body[i]->get_xposition()) / new_radius);
                		yForce += Force * ((body[j]->get_yposition() - body[i]->get_yposition()) / new_radius);
	 
			}

			xAcceleration = xForce / body[i]->get_input_mass();
               		yAcceleration = yForce / body[i]->get_input_mass();

			new_xvelocity = body[i]->get_xvelocity() - (seconds * xAcceleration);
			new_yvelocity = body[i]->get_yvelocity() - (seconds * yAcceleration);
			
			body[i]->set_xvelocity(new_xvelocity);
			body[i]->set_yvelocity(new_yvelocity);
			
			new_xposition = body[i]->get_xposition() - (seconds * body[i]->get_xvelocity());
			new_yposition = body[i]->get_yposition() - (seconds * body[i]->get_yvelocity());
			
			body[i]->set_xposition(new_xposition);
			body[i]->set_yposition(new_yposition);		
		}
	return;
}

