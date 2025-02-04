#include "Nivel6.h"
#include "Enemigo.h"



Nivel6::Nivel6(Game * j, std::vector <Game::Vagon_t> v, Game::Bala_t a) : Play(j)
{
	enem = 0;
	emax = 20 + 5 * ptsjuego->getNivel();
	for (unsigned int i = 0; i < 4; i++) {
		tren.emplace_back(new Vagon(ptsjuego, this, 580, 100 + 150 * i, v[i]));
	}
	arma = a;
	shootTimer = 0;
	spawnTimer = 0;
	//Falta por completar conforme se implementen las nuevas clases y me da palo hacerlo para nada ^^'
	switch (a)
	{

	case Game::Piedra: cadencia = 800;//0'8s || 800 ms 
		break;
	case Game::Escopeta: cadencia = 700;
		break;
	case Game::Pistola: cadencia = 600;//0'6s || 600 ms 
		break;
	case Game::Metralleta: cadencia = 200;
		break;
	case Game::Sniper: cadencia = 1000;
		break;
	case Game::Minigun: cadencia = 100;
		break;
	case Game::Canon: cadencia = 1700;
		break;
	default:
		break;
	}
	enemsNivel = emax;
	if (ptsjuego->getNivel() == 18) enemsNivel -= 2;
	spawnRonda = 2400 - (50 * ptsjuego->getNivel());
	
}

void Nivel6::update(Uint32 delta) {

	if (!ptsjuego->paused) {
		shootTimer += delta;
		spawnTimer += delta;

		if (disparando && shootTimer >= cadencia) {
			balas.emplace_back(new Bala(ptsjuego, this, player->getPos().x, player->getPos().y + 10, player->getMira(), arma));
			shootTimer = 0;
		}

		if (enem < enemsNivel) {
			
			if (spawnTimer >= spawnRonda) {

				if (rand() % 2 == 0) {
					if (rand() % 2 == 0) {
						if (rand() % 2 == 0) enems.emplace_back(new Enemigo(ptsjuego, this, 0, (rand() % 500) + 320, Game::Enemigo_t::Normal));
						else  enems.emplace_back(new Enemigo(ptsjuego, this, 1300, (rand() % 500) + 320, Game::Enemigo_t::Normal));
					}
					else {
						if (rand() % 2 == 0){
							if (rand() % 2 == 0)enems.emplace_back(new Enemigo(ptsjuego, this, 0, (rand() % 550) + 100, Game::Enemigo_t::Rapido));
							else enems.emplace_back(new Enemigo(ptsjuego, this, 1300, (rand() % 550) + 100, Game::Enemigo_t::Rapido));
						}
						else {
							if (rand() % 2 == 0) enems.emplace_back(new Enemigo(ptsjuego, this, 0, (rand() % 550) + 280, Game::Enemigo_t::Invisible));
							else  enems.emplace_back(new Enemigo(ptsjuego, this, 1300, (rand() % 550) + 280, Game::Enemigo_t::Invisible));
						}
					}
					enem++;
				}
				else {
					if (rand() % 2 == 0) {
						if (rand() % 2 == 0) {
							if (rand() % 2 == 0)enems.emplace_back(new Enemigo(ptsjuego, this, 0, (rand() % 500) + 230, Game::Enemigo_t::Tocho));
							else enems.emplace_back(new Enemigo(ptsjuego, this, 1300, (rand() % 500) + 230, Game::Enemigo_t::Tocho));
						}
						else {
							if (rand() % 2 == 0)enems.emplace_back(new Enemigo(ptsjuego, this, 0, (rand() % 500) + 300, Game::Enemigo_t::Tank));
							else enems.emplace_back(new Enemigo(ptsjuego, this, 1300, (rand() % 500) + 300, Game::Enemigo_t::Tank));
						}						
					}
					else {
						if (rand() % 2 == 0) enems.emplace_back
							(new Enemigo(ptsjuego, this, 0, (rand() % 550) + 80, Game::Enemigo_t::Enano));
						else enems.emplace_back
							(new Enemigo(ptsjuego, this, 1300, (rand() % 550) + 80, Game::Enemigo_t::Enano));
					}
					enem++;
				}
				spawnTimer = 0;
			}
		}		
		else {		
			if (!created && (ptsjuego->getNivel() == 18)){
				enems.emplace_back(new Enemigo(ptsjuego, this, 0, 300, Game::Enemigo_t::Boss));
				enems.emplace_back(new Enemigo(ptsjuego, this, 1300, 300, Game::Enemigo_t::Boss));
				enem += 2;
				created = true;
			}			
		}
		if (emax == Play::getKilled()) {
			Play::finish();
		}

		Play::update(delta);
	}
}