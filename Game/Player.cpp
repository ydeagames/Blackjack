#include "Player.h"
#include "Card.h"
#include "User.h"
#include "Blackjack.h"

// 持ってるカード情報を表示
void Player::Show(const std::shared_ptr<Player>& player, int draw_num)
{
	// Aを含む場合の最小候補
	int total_min = GetPoint(player, true);
	// Aを含む場合の最大候補
	int total = GetPoint(player);
	// ?を含まない本当の数
	int total_real = GetPoint(nullptr);
	std::cout << GetUser()->GetName() << "の手札(";
	// Aがあれば候補表示
	if (total_min != total)
		std::cout << total - 10 << "/";
	std::cout << total;
	// ?があれば+?表示
	if (total != total_real)
		std::cout << "+?";
	std::cout << "pt";

	// 状態表示
	bool bust = IsBust();
	bool blackjack = IsBlackjack();
	if (bust)
		std::cout << "[BUST]";
	if (blackjack)
		std::cout << "[BLACKJACK]";
	std::cout << "): ";

	// カード情報
	bool start = true;
	int i = static_cast<int>(cards.size());
	for (auto& card : cards)
		if (card)
		{
			// 最初以外セミコロンを付ける
			if (start)
				start = false;
			else
				std::cout << ", ";
			if (i <= draw_num)
			{
				PlaySound(TEXT("Resources/Audio/card_send.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
			}
			card->Show((bust || blackjack) ? nullptr : player);
			if (i <= draw_num)
				Sleep(400);
			i--;
		}
	std::cout << std::endl;
}

// 所持カード合計の強さ
int Player::GetPoint(const std::shared_ptr<Player>& owner, bool min_flag)
{
	int num_pending = 0;
	int total = 0;
	for (auto& card : cards)
	{
		// 見えるカードの中で
		if (card->IsVisible(owner))
		{
			int point = card->GetPoint(nullptr);
			// Aは保留
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
		// Aを11と扱っても足してBUSTしなかいなら11として扱う
		if (total > 10 || min_flag)
			total += 1;
		else
			total += 11;
	}

	return total;
}

// カードを持っているか
bool Player::HasCard(const std::shared_ptr<Player>& player, int point)
{
	for (auto& card : cards)
		if (card->GetPoint(player) == point)
			return true;
	return false;
}

// バストしているか
bool Player::IsBust()
{
	return GetPoint(nullptr) > Blackjack::BUST_POINT;
}

// ブラックジャックか
bool Player::IsBlackjack()
{
	return GetPoint(nullptr) == Blackjack::BUST_POINT;
}

// BET金額設定
void Player::SetBet(int chip)
{
	bet = chip;
}

// BET金額追加
void Player::AddBet(int chip)
{
	bet += chip;
}

// BETする
void Player::Bet(int chip)
{
	auto user = GetUser();
	user->AddChip(-chip);
	AddBet(chip);
}

// BET金額取得
int Player::GetBet()
{
	return bet;
}

// ユーザー取得
std::shared_ptr<User> Player::GetUser()
{
	return user;
}

// カードを追加
void Player::AddCard(std::unique_ptr<Card>&& newcard)
{
	// オーナーをセット
	newcard->SetOwner(shared_from_this());
	// カードを移動
	cards.push_back(std::move(newcard));
}

// ディーラーのAI
Choice DealerPlayer::Choose(const std::shared_ptr<Player>& dealerPlayer)
{
	// 16以下だったらHITする
	if (GetPoint(nullptr) <= 16)
		return Choice::HIT;
	return Choice::STAND;
}

// ディーラーかどうか
bool DealerPlayer::IsDealer()
{
	return true;
}

std::shared_ptr<Player> DealerPlayer::Split()
{
	throw std::logic_error("ディーラーはSplitできません");
}

// 勝利
void DealerPlayer::OnWin()
{
}

// 引き分け
void DealerPlayer::OnDraw()
{
}

// 負け
void DealerPlayer::OnLose()
{
}

// プレイヤーの選択
Choice NormalPlayer::Choose(const std::shared_ptr<Player>& dealerPlayer)
{
	// ブラックジャックならSTAND決定
	if (IsBlackjack())
		return Choice::STAND;

	// フラグ
	bool flag_begin = cards.size() == 2;
	bool flag_enough = GetUser()->GetChip() >= GetBet();
	bool flag_double = flag_begin && flag_enough;
	bool flag_split = flag_begin && flag_enough && !splited && (cards.front()->GetPoint(nullptr) == cards.back()->GetPoint(nullptr));
	bool flag_insurance = flag_begin && !insuranced && dealerPlayer->HasCard(shared_from_this(), -1);

	// 選択肢
	struct Choose
	{
		char input;
		std::string name;
		Choice choice;
	};
	// 選択肢一覧
	std::vector<Choose> chooses;

	// 選択肢表示
	char input = '1';
	chooses.push_back({ input++, "STAND", Choice::STAND });
	chooses.push_back({ input++, "HIT", Choice::HIT });
	if (flag_double)
		chooses.push_back({ input++, "DOUBLE", Choice::DOUBLE });
	if (flag_split && !splited)
		chooses.push_back({ input++, "SPLIT", Choice::SPLIT });
	if (flag_insurance)
		chooses.push_back({ input++, "INSURANCE", Choice::INSURANCE });

	// 情報表示
	std::cout << "    ";
	std::cout << GetUser()->GetName() << "の賭け: (チップ: " << GetUser()->GetChip() << ", BET: " << GetBet() << ")" << std::endl;
	std::cout << "    ";
	for (Choose choose : chooses)
		std::cout << "[" << choose.input << ": " << choose.name << "] ";
	std::cout << std::endl;
	std::cout << "    ";
	std::cout << "> ";

	// 選択
	while (true)
	{
		char input = static_cast<char>(_getch());
		for (Choose choose : chooses)
			// 選択肢にあればreturnする
			if (input == choose.input)
			{
				std::cout << "[" << choose.input << ": " << choose.name << "]" << std::endl;
				return choose.choice;
			}
	}
}

// ディーラーかどうか
bool NormalPlayer::IsDealer()
{
	return false;
}

// SPLIT
std::shared_ptr<Player> NormalPlayer::Split()
{
	// 複製
	auto cloned = std::make_shared<NormalPlayer>(GetUser());
	// カードを分割
	auto split = std::move(cards.back());
	cards.pop_back();
	// オーナーをリセット
	split->SetOwner(nullptr);
	// カードをクローンに追加
	cloned->AddCard(std::move(split));
	cloned->splited = true;
	// サイドBET
	cloned->SetBet(0);
	cloned->Bet(GetBet());
	// フラグ
	splited = true;
	return cloned;
}

// 勝利
void NormalPlayer::OnWin()
{
	// ブラックジャックは2.5倍
	if (IsBlackjack())
		GetUser()->AddChip(bet * 5 / 2);
	// BET分が2倍になって帰ってくる
	else
		GetUser()->AddChip(bet * 2);
}

// 引き分け
void NormalPlayer::OnDraw()
{
	// BET分が帰ってくる
	GetUser()->AddChip(bet);
}

// 負け
void NormalPlayer::OnLose()
{
	// None
}
