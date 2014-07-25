#include <SDL/SDL.h>

SDL_Surface* background = NULL;
SDL_Surface* sprites[9];
SDL_Surface* backbuffer = NULL;

bool IsRunning();
bool LoadImages();
void FreeImages();
SDL_Surface* getSprite();

int main(int argc, char* argv[]) {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL Initialization failed :(");
		SDL_Quit();
		return 0;
	}
	backbuffer = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption("You've Won Master Shake", NULL);
	if(!LoadImages()) {
		printf("Image resources failed to initalize");
		FreeImages();
		SDL_Quit();
		return 0;
	}
	SDL_BlitSurface(background, NULL, backbuffer, NULL);
	while (IsRunning()) {
		SDL_Rect spritePos;
		spritePos.x=rand()%400;
		spritePos.y=rand()%300;
		SDL_BlitSurface(getSprite(), NULL, backbuffer, &spritePos);
		SDL_Flip(backbuffer);
		SDL_Delay(750);
	}
	SDL_Quit();
	return 1;
}
bool IsRunning() {
	SDL_Event event;
	bool running = true;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT)
			running = false;
	}
	return running;
}
SDL_Surface* getSprite(){
	return sprites[rand()%8];
}
bool LoadImages() {
	background = SDL_LoadBMP("graphics/background.bmp");
	if(background == NULL)
		return false;
	sprites[0] = SDL_LoadBMP("graphics/sprite1.bmp");
	sprites[1] = SDL_LoadBMP("graphics/sprite2.bmp");
	sprites[2] = SDL_LoadBMP("graphics/sprite3.bmp");
	sprites[3] = SDL_LoadBMP("graphics/sprite4.bmp");
	sprites[4] = SDL_LoadBMP("graphics/sprite5.bmp");
	sprites[5] = SDL_LoadBMP("graphics/sprite6.bmp");
	sprites[6] = SDL_LoadBMP("graphics/sprite7.bmp");
	sprites[7] = SDL_LoadBMP("graphics/sprite8.bmp");
	sprites[8] = SDL_LoadBMP("graphics/sprite9.bmp");
	for(int i = 0; i < 9; i++) {
		if(sprites[i] == NULL)
			return false;
	}
	return true;
}
void FreeImages() {
	if(background != NULL) {
		SDL_FreeSurface(background);
		background = NULL;
	}
	if(sprites != NULL) {
		for(int i = 0; i < 9; i++) {
			SDL_FreeSurface(sprites[i]);
			sprites[i]=NULL;
		}
	}
}

