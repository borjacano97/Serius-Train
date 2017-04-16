#ifndef H_TIENDA_H
#define H_TIENDA_H

#include "Estado.h"
#include "ObjetoTienda.h"
#include "Selector.h"

class Tienda :
	public Estado
{
public:
	Tienda(Game* juego);
	~Tienda(){}
	char getEst(){  return 'T';}
	void draw();
	void onClick();
	void comprar(ObjetoTienda*o) { o->desbloquear(); ptsjuego->buy(o->getPrecio()); }
	void select(Uint32 n);
	void colocarVagon(Game::Vagon_t v) { vagonesNivel[seleccionado] = v; std::cout << seleccionado;	}
private:
	static void recolocar(Game * jg);
	static void jugar(Game * jg);

	Texturas* font;
	SDL_Color fontColor;

	Selector* sel;
	
	std::vector <ObjetoTienda*> objs; // armas y vagones del nivel
	std::vector <Game::Vagon_t> vagonesNivel; // va a contener los tipos de vagones que pasar�n a cada nvl sin locomotora
	int seleccionado = 0;
};

#endif