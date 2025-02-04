#ifndef H_PLAY_H
#define H_PLAY_H

#include "Estado.h"
#include "Personaje.h"
#include "Enemigo.h"
#include "Vagon.h"
#include "BarraHP.h"
#include "Trigger.h"
#include "Bala.h"
#include "Sound.h"
#include "Escenario.h"
#include "ArmaTienda.h"
#include "Hud.h"
#include "Button.h"
#include "Menu.h"

using namespace std;

class Play : public Estado
{
public:
	Play(Game * j);
	virtual ~Play();

	void onClick();
	void draw();
	void update(Uint32 delta);
	void move(char c);
	char getEst(){ return 'P'; }
	int getKilled() { return killed; }
	void finish() { fin = true;  }
	void pause() { if (ptsjuego->paused) ptsjuego->paused = false; else ptsjuego->paused = true; }

	vector <Bala*> balas;
	vector <Enemigo*> enems;
	vector <Vagon*> tren; 
	int killed;
	int emax, enem;

	Trigger* tg;
	barraHP* TrainHp;
	Personaje* player;
protected:
	Texturas* font;
	SDL_Color fontColor;
	SDL_Color fontColor2;
	SDL_Color fontColor3;
	Sound* soundLoss;
	Sound* soundWon;
	//Sound* sonido;
	ArmaTienda* armaActual;

	Button* b1;
	Button* b2;

	Uint32 d;
	int contWin = 0;
	int contTexto = 0;
	int textInit = 0;
	bool fin;
	bool tutorial = false;
	bool initObjects(); //crear y destruir los objetos del juego
	void freeObjects();

	static void reanudar(Game * jg) { jg->paused = false; }
	static void salir(Game * jg){
		jg->paused = false;
		if (jg->survival) {
			jg->sound->stopMusic();
			jg->survival = false;
			jg->extrem = false;
			jg->changeState(new Menu(jg));
		}		
		
		else jg->popState(); 
	}

	Escenario*esc;
	Hud* h;
	Hud* tray;
	Hud* locom;
	Hud* fondoP;

	bool roto = false;
	bool hist = false;
	bool newRonda = false;//para surv


	int alphaCont = 0;
	int contAlpha2 = 0;

	Texturas* textTut;
	SDL_Color color;
};


#endif