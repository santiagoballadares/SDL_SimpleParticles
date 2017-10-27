#include <iostream>
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace core;

int main(int argc, char* args[]) {
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL Init failed." << endl;
		return 1;
	}

	Screen screen;

	if (!screen.init()) {
		cout << "SDL Screen initialisation failed." << endl;
	}

	Swarm swarm;

	Particle particle;
	int x, y, elapse;
	unsigned char red, green, blue;

	while (true) {
		elapse 	= SDL_GetTicks();

		// update particles
		swarm.update(elapse);

		// draw particles
		const Particle * const pParticles = swarm.getParticles();

		red 	= (unsigned char) ((1 + sin(elapse * 0.0001)) * 128);
		green 	= (unsigned char) ((1 + sin(elapse * 0.0003)) * 128);
		blue 	= (unsigned char) ((1 + sin(elapse * 0.0005)) * 128);

		for (int i=0; i<Swarm::NPARTICLES; ++i) {
			particle = pParticles[i];

			x = (particle.m_x + 1) * Screen::SCREEN_WIDTH/2;
			y = particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

		// draw the screen
		screen.update();

		// check for events
		if (!screen.processEvents()) {
			break;
		}
	}

	return 0;
}




