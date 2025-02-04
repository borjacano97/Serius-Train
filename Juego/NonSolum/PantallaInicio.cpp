#include "PantallaInicio.h"
#include "Menu.h"


PantallaInicio::PantallaInicio(Game* juego) : Estado(juego)
{
	ptsjuego = juego;

	fondo = new Hud(ptsjuego, NULL, 0, 0, Game::Hud_t::Fondo, Game::Fondo_t::FondoInicio);
	logo = new Hud(ptsjuego, NULL, 600, 400, Game::Hud_t::Logo, Game::Fondo_t::FondoInicio);
	sangre = new Hud(ptsjuego, NULL, 280, 150, Game::Hud_t::Sangre, Game::Fondo_t::FondoInicio);

	initLibraries();
	iniSound = new Sound;
	iniSound->playMusic("../sounds/iniSound.mp3",-1,17);
}


void PantallaInicio::draw() {
	fondo->draw();
	if (cont >= 5000) sangre->draw();
	logo->draw();
	
	if (cont >= 6500) {
		ptsjuego->texts[43]->setColor(255-(cont - 6500) / 2, 255-(cont - 6500) / 2, 255-(cont - 6500) / 2);
		ptsjuego->texts[43]->setColor((cont-6500)/2);
		ptsjuego->texts[43]->draw(ptsjuego->pRender, nullptr, nullptr);
	}

	Estado::draw();
}

void PantallaInicio::update(Uint32 delta) {
	logo->update(delta);
	cont+= delta;
	if (cont >= 7000) {
		iniSound->stopMusic();
		ptsjuego->estados.push(new Menu(ptsjuego));
	}
}

bool PantallaInicio::initLibraries() {

	TTF_Init();

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}
	return true;
}
