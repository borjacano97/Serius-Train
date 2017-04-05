#ifndef H_VAGON_H
#define H_VAGON_H

#include "Objeto.h"

class Play;

class Vagon :
	public Objeto
{
public:
	Vagon(Game* juego, Play*pl, Game::Texturas_t text, float x, float y, Game::Vagon_t t);
	~Vagon(){}
	void update(Uint32 delta);
	Objeto_t getId() { return Objeto_t::OVagon; }
private: 
	Uint32 cont;
	bool disparo;
	Game::Vagon_t tipo; //struct tbn
	Play*p;
};
#endif