#ifndef H_TEXTURAS_H
#define H_TEXTURAS_H

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include "Font.h"

class Texturas
{
public:
	Texturas();
	~Texturas();
	//m�todos p�blicos para cargar y pintar
	bool load(SDL_Renderer*prender, std::string const& nombArch);
	void draw(SDL_Renderer*prender, SDL_Rect* const &rect2, SDL_Rect* const& rect);

	//Para la fuente
	Font myFont;

	bool loadFuente(std::string fuente, int tama�o);
	bool loadFromText(SDL_Renderer* pRender, const std::string texture, SDL_Color color);

private:
	SDL_Texture* ptext;
	SDL_Surface* pSurface;

	int alto; // en principio las texturas han de ser cuadradas
	int ancho;
};

#endif