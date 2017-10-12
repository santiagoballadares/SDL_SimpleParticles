#include "Swarm.h"

namespace core {

Swarm::Swarm() : lastTime(0) {
	m_pParticles = new Particle[NPARTICLES];
}

Swarm::~Swarm() {
	delete [] m_pParticles;
}

void Swarm::update(int elapseTime) {
	int deltaTime = elapseTime - lastTime;

	for (int i=0; i<NPARTICLES; ++i) {
		m_pParticles[i].update(deltaTime);
	}

	lastTime = elapseTime;
}

} /* namespace core */
