#include "Game.h"
#include "Trump.h"

Game::Game()
{
	std::cout << "########## �u���b�N�W���b�N ##########" << std::endl;

	// ������
	Trump trump = {};	// �g�����v�P�[�X��p��
	trump.Create();		// �g�����v��p��
	trump.Shuffle();	// �g�����v���V���b�t��
	

}

Game::~Game()
{

}
