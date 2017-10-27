#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

namespace core
{

class Screen
{
public:
	static const int SCREEN_WIDTH 	= 800;
	static const int SCREEN_HEIGHT = 600;

private:
	SDL_Window 		*m_window;
	SDL_Renderer 	*m_renderer;
	SDL_Texture 	*m_texture;
	Uint32 			*m_buffer1;
	Uint32 			*m_buffer2;
	SDL_Event 		m_event;

public:
	Screen();
	virtual ~Screen();

	bool init();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void boxBlur();
	void clear();
	bool processEvents();
	void close();
};

} /* namespace core */

#endif /* SCREEN_H_ */
