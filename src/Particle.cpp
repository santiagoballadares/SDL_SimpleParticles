#include "Particle.h"
#include <stdlib.h>
#include <math.h>

namespace core {

Particle::Particle() : m_x(0), m_y(0) {
	init();
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::init() {
	m_x = 0;
	m_y = 0;
	m_direction = (2.0 * M_PI * rand()) / RAND_MAX;
	m_speed = (0.04 * rand()) / RAND_MAX;
	m_speed *= m_speed;
}

void Particle::update(int deltaTime) {
	m_direction += deltaTime * 0.0003;

	double xDelta = m_speed * cos(m_direction);
	double yDelta = m_speed * sin(m_direction);

	m_x += xDelta * deltaTime;
	m_y += yDelta * deltaTime;

	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		init();
	}

	if (rand() < RAND_MAX/100) {
		init();
	}
}

} /* namespace core */
