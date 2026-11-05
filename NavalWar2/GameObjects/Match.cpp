#include "../stdafx.h"
#include "Match.h"

Match::Match(GameManager& gm, Base& playerBase, Base& enemyBase, const Font& font)
	: gm_(gm)
	, playerBase_(playerBase)
	, enemyBase_(enemyBase)
	, font_(font)
	, phase_(Phase::Playing)
{
	logicId_ = gm_.registerLogic([this]() { this->Evaluate(); });
}

Match::~Match()
{
	gm_.unregisterLogic(logicId_);
}

void Match::Evaluate()
{
	if (phase_ != Phase::Playing)
	{
		return;
	}
	if (enemyBase_.GetHp() <= 0.0)
	{
		phase_ = Phase::Won;
	}
	else if (playerBase_.GetHp() <= 0.0)
	{
		phase_ = Phase::Lost;
	}
}

void Match::Reset()
{
	phase_ = Phase::Playing;
}

RectF Match::RestartRect() const
{
	return RectF{ Scene::Center().x - 150.0, Scene::Center().y + 24.0, 300.0, 72.0 };
}

void Match::DrawOverlay() const
{
	if (phase_ == Phase::Playing)
	{
		return;
	}

	RectF{ 0, 0, Scene::Width(), Scene::Height() }.draw(ColorF{ 0.05, 0.12, 0.2, 0.55 });
	const bool won = phase_ == Phase::Won;
	const String title = won ? U"勝利" : U"敗北";
	const String detail = won ? U"敵拠点を撃破した" : U"味方拠点が沈んだ";
	font_(title).drawAt(72, Scene::Center().movedBy(0, -70), won ? Palette::Gold : Palette::Orangered);
	font_(detail).drawAt(28, Scene::Center().movedBy(0, -8), Palette::White);

	const RectF button = RestartRect();
	button.draw(Palette::White);
	button.drawFrame(3, Palette::Black);
	font_(U"再出撃").drawAt(36, button.center(), Palette::Black);
}

bool Match::RestartClicked() const
{
	return phase_ != Phase::Playing && RestartRect().leftClicked();
}
