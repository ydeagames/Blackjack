#include "Game.h"

int main()
{
	// 今回はC言語のrand関数を使用
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// ゲームを初期化
	Game game = {};
	// ゲームを開始
	game.Start();

	// F5終了防止
	std::cin.get();

	return 0;
}