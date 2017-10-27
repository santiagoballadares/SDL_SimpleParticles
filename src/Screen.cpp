#include "Screen.h"

namespace core {

Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(
				NULL) {
	// TODO Auto-generated constructor stub
}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}

bool Screen::init() {
	m_window = SDL_CreateWindow("Particle Fire Explosion",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == NULL) {
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_texture == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	clear();

	return true;
}

void Screen::update() {
	SDL_UpdateTexture(m_texture, NULL, m_buffer1,
			SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;

	// RGBA
	Uint32 colour = 0;

	colour += red;
	colour <<= 8;
	colour += green;
	colour <<= 8;
	colour += blue;
	colour <<= 8;
	colour += 0xFF;

	m_buffer1[(y * SCREEN_WIDTH) + x] = colour;
}

void Screen::boxBlur() {
	// Swap buffers
	Uint32 *tempBuffer = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = tempBuffer;

	int currentX = 0;
	int currentY = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	Uint32 pixelColour = 0;
	Uint8 pixelRed = 0;
	Uint8 pixelGreen = 0;
	Uint8 pixelBlue = 0;

	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			red = 0;
			green = 0;
			blue = 0;

			for (int row = -1; row <= 1; ++row) {
				for (int col = -1; col <= 1; ++col) {
					currentX = x + col;
					currentY = y + row;

					if (currentX >= 0 && currentX < SCREEN_WIDTH
							&& currentY >= 0 && currentY < SCREEN_HEIGHT) {
						pixelColour = m_buffer2[currentY * SCREEN_WIDTH
								+ currentX];

						pixelRed = pixelColour >> 24;
						pixelGreen = pixelColour >> 16;
						pixelBlue = pixelColour >> 8;

						red += pixelRed;
						green += pixelGreen;
						blue += pixelBlue;
					}
				}
			}

			pixelRed = red / 9;
			pixelGreen = green / 9;
			pixelBlue = blue / 9;

			setPixel(x, y, pixelRed, pixelGreen, pixelBlue);
		}
	}
}

void Screen::clear() {
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
}

bool Screen::processEvents() {
	while (SDL_PollEvent(&m_event)) {
		if (m_event.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

void Screen::close() {
	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

} /* namespace core */
