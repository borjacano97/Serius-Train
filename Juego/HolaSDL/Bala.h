#ifndef H_BALA_H
#define H_BALA_H

#include "Objeto.h"
class Bala : public Objeto
{
public:
	Bala(Game* juego, Game::Texturas_t text, float x, float y, int mira, Game::Bala_t b);
	~Bala(){}
	void update(Uint32 delta);
	Objeto_t getId() { return Objeto_t::OBala; }
private:
	int dir;
	float vel;
	Game::Bala_t tipo;
	//struct para tipos de bala(arma)
};

#endif