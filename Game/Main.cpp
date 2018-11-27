#include "Trump.h"
#include "Card.h"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	Trump trump = {};
	trump.ShowTrump();
	trump.Create();
	trump.ShowTrump();
	trump.Shuffle();
	trump.ShowTrump();
	{
		std::cout << "Drawed: ";
		Card* card = trump.DrawCard();
		if (card)
			card->ShowCard();
		else
			std::cout << "empty" << std::endl;
		std::cout << std::endl;
	}
	trump.ShowTrump();

	std::cin.get();
}