#ifndef H_NIVEL2_H
#define H_NIVEL2_H

#include "play.h"
class Nivel2 :
	public Play
{
public:
	Nivel2(Game * j, std::vector <Game::Vagon_t> v, Game::Bala_t a);
	~Nivel2(){ sound->stopMusic(); }
	void onClick();
	void update(Uint32 delta);
private:
	int  enem, emax, shootTimer, spawnTimer, cadencia;
	Game::Bala_t arma;
	Sound* sound;
	bool initLibraries();
};


#endif