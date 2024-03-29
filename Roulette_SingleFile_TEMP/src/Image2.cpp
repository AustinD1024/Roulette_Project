//#include "image.h"
//
//#include <SDL.h>   
//
//#include <atomic>
//
//extern std::atomic<bool> quit2;
//
//void Image2(int argc, char** argv)
//{
//	//bool quit = false;
//	SDL_Event event2;
//
//	SDL_Init( SDL_INIT_VIDEO );
//
//	SDL_Window* window2 = SDL_CreateWindow( "SDL2 Roulette Betting Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 600, 0 );
//
//	SDL_Renderer* renderer2 = SDL_CreateRenderer( window2, -1, 0 );
//	//SDL_Surface* image = SDL_LoadBMP( "../resources/Roulette_Wheel_Image.bmp" );  //this depends on where you run the binary file
//	SDL_Surface* image2 = SDL_LoadBMP("Roulette_Betting_Board.bmp");
//	SDL_Texture* texture2 = SDL_CreateTextureFromSurface( renderer2, image2 );
//
//	while (!quit2) {
//		while (SDL_PollEvent(&event2)) {
//			switch (event2.type) {
//			case SDL_QUIT:
//				quit2 = true;
//				break;
//			default:
//				break;
//			}
//		}
//
//		SDL_RenderCopy(renderer2, texture2, NULL, NULL);
//		SDL_RenderPresent( renderer2 );
//	}
//
//
//	SDL_DestroyTexture( texture2 );
//	SDL_FreeSurface( image2 );
//	SDL_DestroyRenderer( renderer2 );
//	SDL_DestroyWindow(window2);
//
//	SDL_Quit();
//
//}
