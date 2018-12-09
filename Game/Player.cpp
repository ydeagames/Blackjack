#include "Player.h"
#include "Card.h"
#include "User.h"
#include "Blackjack.h"

void Player::Show(const std::shared_ptr<Player>& player)
{
	int total_min = GetPoint(player, true);
	int total = GetPoint(player);
	int total_real = GetPoint(nullptr);
	std::cout << GetUser()->GetName() << "の手札(";
	if (total_min != total)
		std::cout << total - 10 << "/";
	std::cout << total;
	if (total != total_real)
		std::cout << "+?";

	std::cout << "pt";
	bool bust = IsBust();
	bool blackjack = IsBlackjack();
	if (bust)
		std::cout << "[BUST]";
	if (blackjack)
		std::cout << "[BLACKJACK]";
	std::cout << "): ";
	bool start = true;
	for (auto& card : m_cards)
		if (card)
		{
			if (start)
				start = false;
			else
				std::cout << ", ";
			card->Show((bust || blackjack) ? nullptr : player);
		}
	std::cout << std::endl;
}

int Player::GetPoint(const std::shared_ptr<Player>& owner, bool min_flag)
{
	int num_pending = 0;
	int total = 0;
	for (auto& card : m_cards)
	{
		if (card->IsVisible(owner))
		{
			int point = card->GetPoint(nullptr);
			if (point < 0)
				num_pending++;
			else
				total += point;
		}
	}

	if (num_pending > 0) // Aが1枚以上だったら
	{
		if (num_pending > 1)  // Aが2枚以上だったら
		{
			total += num_pending - 1; // 1つを残してすべてのAを1として追加
			//num_pending = 1;  // Aは残り1枚
		}
		if (total > 10 || min_flag)
			total += 1;
		else
			total += 11;
	}

	return total;
}

bool Player::HasCard(const std::shared_ptr<Player>& player, int point)
{
	for (auto& card : m_cards)
		if (card->GetPoint(player) == point)
			return true;
	return false;
}

bool Player::IsBust()
{
	return GetPoint(nullptr) > Blackjack::BUST_POINT;
}

bool Player::IsBlackjack()
{
	return GetPoint(nullptr) == Blackjack::BUST_POINT;
}

void Player::SetBet(int chip)
{
	bet = chip;
}

void Player::AddBet(int chip)
{
	bet += chip;
}

void Player::Bet(int chip)
{
	auto user = GetUser();
	user->AddChip(-chip);
	AddBet(chip);
}

int Player::GetBet()
{
	return bet;
}

std::shared_ptr<User> Player::GetUser()
{
	return user;
}

void Player::AddCard(std::unique_ptr<Card>&& newcard)
{
	newcard->SetOwner(shared_from_this());
	m_cards.push_back(std::move(newcard));
}

Choice DealerPlayer::Choose(const std::shared_ptr<Player>& dealerPlayer)
{
	if (GetPoint(nullptr) <= 16)
		return Choice::HIT;
	return Choice::STAND;
}

bool DealerPlayer::IsDealer()
{
	return true;
}

std::shared_ptr<Player> DealerPlayer::Split()
{
	throw std::logic_error("ディーラーはSplitできません");
}

void DealerPlayer::OnWin()
{
}

void DealerPlayer::OnDraw()
{
}

void DealerPlayer::OnLose()
{
}

Choice NormalPlayer::Choose(const std::shared_ptr<Player>& dealerPlayer)
{
	if (IsBlackjack())
		return Choice::STAND;

	bool flag_begin = m_cards.size() == 2;
	bool flag_enough = GetUser()->GetChip() >= GetBet();
	bool flag_double = flag_begin && flag_enough;
	bool flag_split = flag_begin && flag_enough && !splited && (m_cards.front()->GetPoint(nullptr) == m_cards.back()->GetPoint(nullptr));
	bool flag_insurance = flag_begin && !insuranced && dealerPlayer->HasCard(shared_from_this(), -1);

	struct Choose
	{
		char input;
		std::string name;
		Choice choice;
	};
	std::vector<Choose> chooses;

	char input = '1';
	chooses.push_back({ input++, "STAND", Choice::STAND });
	chooses.push_back({ input++, "HIT", Choice::HIT });
	if (flag_double)
		chooses.push_back({ input++, "DOUBLE", Choice::DOUBLE });
	if (flag_split && !splited)
		chooses.push_back({ input++, "SPLIT", Choice::SPLIT });
	if (flag_insurance)
		chooses.push_back({ input++, "INSURANCE", Choice::INSURANCE });

	std::cout << "あなたのターンです(Chips: " << GetUser()->GetChip() << ", Bet: " << GetBet() << ")" << std::endl;
	for (Choose choose : chooses)
		std::cout << "[" << choose.input << ": " << choose.name << "] ";
	std::cout << std::endl;
	std::cout << "> ";

	while (true)
	{
		char input = static_cast<char>(_getch());
		for (Choose choose : chooses)
			if (input == choose.input)
			{
				std::cout << "[" << choose.input << ": " << choose.name << "]" << std::endl;
				return choose.choice;
			}
	}
}

bool NormalPlayer::IsDealer()
{
	return false;
}

std::shared_ptr<Player> NormalPlayer::Split()
{
	auto cloned = std::make_shared<NormalPlayer>(GetUser());
	auto split = std::move(m_cards.back());
	m_cards.pop_back();
	split->SetOwner(nullptr);
	cloned->AddCard(std::move(split));
	cloned->splited = true;
	cloned->SetBet(0);
	cloned->Bet(GetBet());
	splited = true;
	return cloned;
}

void NormalPlayer::OnWin()
{
	if (IsBlackjack())
		GetUser()->AddChip(bet * 5 / 2);
	else
		GetUser()->AddChip(bet * 2);
}

void NormalPlayer::OnDraw()
{
	GetUser()->AddChip(bet);
}

void NormalPlayer::OnLose()
{
	// None
}
