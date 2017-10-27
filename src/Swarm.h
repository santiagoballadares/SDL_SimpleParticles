#ifndef SWARM_H_
#define SWARM_H_

#include "particle.h"

namespace core {

class Swarm {
public:
	const static int NPARTICLES = 3000;

private:
	Particle *m_pParticles;
	int lastTime;

public:
	Swarm();
	virtual ~Swarm();

	void update(int elapseTime);
	const Particle * const getParticles() { return m_pParticles; }
};

} /* namespace core */

#endif /* SWARM_H_ */
