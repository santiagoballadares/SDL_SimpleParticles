#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace core {

class Particle {
public:
	double m_x;
	double m_y;

private:
	double m_speed;
	double m_direction;

public:
	Particle();
	virtual ~Particle();

	void update(int deltaTime);

private:
	void init();
};

} /* namespace core */

#endif /* PARTICLE_H_ */
