#include "Vagon.h"
#include <string>



Vagon::Vagon(Game* juego, Game::Texturas_t text, float x, float y, std::string t)
{
	juegootp = juego;
	Ttextura = text;

	alto = 201;
	ancho = 120;

	pos.set(x, y);

	tipo = t;
}

void Vagon::update(Uint32 delta) {
	//hacer uso de la variable TIPO
}