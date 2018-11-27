#include "Game.h"
#include "Trump.h"

Game::Game()
{
	std::cout << "########## ブラックジャック ##########" << std::endl;

	// 初期化
	Trump trump = {};	// トランプケースを用意
	trump.Create();		// トランプを用意
	trump.Shuffle();	// トランプをシャッフル
	

}

Game::~Game()
{

}
