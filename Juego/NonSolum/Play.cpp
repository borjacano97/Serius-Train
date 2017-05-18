﻿#include "Play.h"
#include "Bala.h"
#include "Enemigo.h"
#include "Vagon.h"
#include "FinNivel.h"
#include "Trigger.h"

#include <string>
#include <stdlib.h> // para nºs aleatorios
#include <time.h>


Play::Play(Game * j) : Estado(j)
{
	//srand(time(NULL));
	//ptsjuego = j;
	initObjects();
	killed = 0;

	font = new Texturas(/*80, 80, 50, 50*/);
	font->loadFuente("../fonts/fuenteNumbers.ttf", 200);

	/*sonido = new Sound;
	sonido->playMusic("../sounds/prueba.mp3", 3, 20);
	/*soundLoss = new Sound;
	soundWon = new Sound;*/

	fontColor.r = 218;
	fontColor.g = 165;
	fontColor.b = 32;
	
	textTut = new Texturas();
	textTut->loadFuente("../fonts/fuenteNumbers.ttf", 200);


	fin = false;

	j->sound->playEffect("../sounds/trainEffect.mp3", -1, 15, 1);
}


Play::~Play()
{
	freeObjects();
	
}

bool Play::initObjects() { // creaci�n de los objetos dando un puntero, una textura y una posici�n (constructora de objs)
	h = new Hud(ptsjuego, this,  -10, -20, Game::Hud_t::Hud1);
	if (!ptsjuego->survival) {
		tray = new Hud(ptsjuego, this, 1200, 0, Game::Hud_t::Trayecto);
		locom = new Hud(ptsjuego, this, 1223, 280, Game::Hud_t::Tren);
	}	
	tg = new Trigger(ptsjuego, NULL, 530, -20);
	player = new Personaje(ptsjuego, Game::TPersonaje, 650, 500);
	TrainHp = new barraHP(ptsjuego, Game::TBarra, 123, 14);
	tren.emplace_back(new Vagon(ptsjuego, this, 580, -50, Game::Vagon_t::Locom));
	
	switch (ptsjuego->getNivel())
	{
	case(1) :
	case(2) :
	case(3) :
			if (ptsjuego->survival)esc = new Escenario(ptsjuego, Game::Texturas_t::TFondo, 0, -4280);
			else  esc = new Escenario(ptsjuego, Game::Texturas_t::TPradera, 0, -4280);
		break;
	case(4) :
	case(5) :
	case(6) :
		     if (ptsjuego->survival)esc = new Escenario(ptsjuego, Game::Texturas_t::TFondo, 0, -4280);
		     else  esc = new Escenario(ptsjuego, Game::Texturas_t::TDesierto, 0, -4280);
		break;
	case(7) :
	case(8) :
	case(9) :
		     esc = new Escenario(ptsjuego, Game::Texturas_t::TFondo, 0, -4280);			
		break;
	case(10) :
	case(11) :
	case(12) :
		     if (ptsjuego->survival)esc = new Escenario(ptsjuego, Game::Texturas_t::TFondo, 0, -4280);
	         else  esc = new Escenario(ptsjuego, Game::Texturas_t::TPradera, 0, -4280);
		break;
	case(13) :
	case(14) :
	case(15) :
			 if (ptsjuego->survival)esc = new Escenario(ptsjuego, Game::Texturas_t::TFondo, 0, -4280);
			 else  esc = new Escenario(ptsjuego, Game::Texturas_t::TFondo, 0, -4280);
		break;
	default:
		break;

	
	}


	TTF_Init();
	
	return Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1;
}

void Play::freeObjects() {
	// c++11
	TTF_Quit();
	for (auto o : tren) {
		delete o;
	}
	for (auto o : enems) {
		delete o;
	}
	for (auto b : balas) {
		delete b;
	}
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1;
}
void Play::draw() {
	esc->draw();	

	for (auto i : tren) {
		i->draw();
	}
	for (auto i : enems) {
		if (i != nullptr) {
			i->draw();
		}
	}
	for (auto i : balas) {
		if (i != nullptr) {
			i->draw();
		}
	}

	player->draw();
	h->draw();

	if (!ptsjuego->survival) {
		switch (ptsjuego->getNivel())
		{
		case(10):
		case(11):
		case(12):
			if (!ptsjuego->survival) ptsjuego->texts[43]->draw(ptsjuego->pRender, nullptr, nullptr);//nocheeeeeeeeeeee
			break;
		default:
			break;
		}
	}
	if (ptsjuego->extrem) ptsjuego->texts[43]->draw(ptsjuego->pRender, nullptr, nullptr);
	if (tray!=nullptr) tray->draw();
	if (locom != nullptr) locom->draw();
	TrainHp->draw();
	if (armaActual != nullptr) armaActual->draw(); // quitar comprobación de nullptr si se traslada al modo Historia
	if (!ptsjuego->survival){
		font->loadFromText(ptsjuego->pRender, "$ " + std::to_string(ptsjuego->coins), fontColor);
		if (ptsjuego->bigHP)font->draw(ptsjuego->pRender, nullptr, &font->myFont.setRect(40, 50, 170, 46));
		else font->draw(ptsjuego->pRender, nullptr, &font->myFont.setRect(40, 50, 170, 53));
	}

	if (!ptsjuego->survival && !tutorial && ptsjuego->getNivel() == 1){
		if (ptsjuego->spanish && enem < 1) {
			textTut->loadFromText(ptsjuego->pRender, "Muevete con WASD!!", fontColor);
			textTut->draw(ptsjuego->pRender, nullptr, &font->myFont.setRect(35, 350, 50, 170));
		}
		if (ptsjuego->spanish && enem >= 1 && enem < 3) {
			textTut->loadFromText(ptsjuego->pRender, "Dispara con el raton!!", fontColor);
			textTut->draw(ptsjuego->pRender, nullptr, &font->myFont.setRect(35, 350, 50, 170));
		}

		if (!ptsjuego->spanish && enem < 1) {
			textTut->loadFromText(ptsjuego->pRender, "Move with WASD!!", fontColor);
			textTut->draw(ptsjuego->pRender, nullptr, &font->myFont.setRect(35, 350, 50, 170));
		}
		if (!ptsjuego->spanish && enem >= 1 && enem < 3) {
			textTut->loadFromText(ptsjuego->pRender, "Shoot with the mouse!", fontColor);
			textTut->draw(ptsjuego->pRender, nullptr, &font->myFont.setRect(35, 350, 50, 170));
		}
	}
	
}


void Play::update(Uint32 delta) {

	if (locom != nullptr) locom->update(delta);
	esc->update(delta);
	for (auto i : tren) {
		i->update(delta);
	}

	for (auto i : balas) {
		if (i != nullptr) {
			i->update(delta);
		}
	}

	//if (tg->collision(player))	player->update(delta); //fuck, no va por la fucking move que tenemos de player
	player->update(delta);
	TrainHp->update(delta);

	if (TrainHp->getDest()) {
			ptsjuego->changeState(new FinNivel(ptsjuego, false));
		soundLoss->playMusic("../sounds/lossLevel.mp3", -1, 20);
	}
	else if (fin){
			if (contWin >= 2000){
				ptsjuego->incrNivel();
				ptsjuego->changeState(new FinNivel(ptsjuego, true));
				soundWon->playMusic("../sounds/wonLevel.mp3", -1, 20);
			}
			else contWin += delta;
	}
	

	else {
		for (unsigned int i = 0; i < enems.size(); i++) {

			if (enems[i] != nullptr) {
				
				if (tg->collision(enems[i])) {
					
					TrainHp->damage(Game::EnemyDmg_t::Simple);
					enems[i]->parar();
					esc->ralentizar(delta);
				}
				
				enems[i]->update(delta);
			}
			if (enems[i] != nullptr && enems[i]->getDest()) {
				if (!ptsjuego->survival) ptsjuego->addCoins(enems[i]->getPoints());
				delete enems[i];
				enems[i] = nullptr;
				killed++;
			}
		}
		for (unsigned int j = 0; j < balas.size(); j++) {

			if (balas[j] != nullptr && balas[j]->getDest()) {
				delete balas[j];
				balas[j] = nullptr;
			}
		}
	}
	Estado::update(delta);
}
void Play::move(char c) {
	player->move(c); // El Dios de la programaci�n quiere suicidarse. Pero no puede, es inmortal.
}