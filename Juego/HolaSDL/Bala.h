#ifndef H_BALA_H
#define H_BALA_H

#include "Objeto.h"
class Play;
class Bala : public Objeto
{
public:
	Bala(Game* juego, Play*pl, Game::Texturas_t text, float x, float y, int mira, Game::Bala_t b);
	~Bala() {}
	void update(Uint32 delta);
private:
	int dir, cont, dmg;
	float vel;
	Game::Bala_t tipo;
	Play*p;
};

#endif