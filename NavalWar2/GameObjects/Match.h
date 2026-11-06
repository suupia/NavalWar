#pragma once
#include "../GameManager.h"
#include "Base.h"

/// 拠点の HP が 0 になった勝敗と、再出撃。
class Match
{
public:
	enum class Phase
	{
		Playing,
		Won,
		Lost,
	};

	Match(GameManager& gm, Base& playerBase, Base& enemyBase, const Font& font);
	~Match();

	Match(const Match&) = delete;
	Match& operator=(const Match&) = delete;

	bool IsPlaying() const { return phase_ == Phase::Playing; }
	Phase GetPhase() const { return phase_; }
	void Evaluate();
	void Reset();
	void DrawOverlay() const;
	bool RestartClicked() const;

private:
	GameManager& gm_;
	Base& playerBase_;
	Base& enemyBase_;
	const Font& font_;
	Phase phase_;
	int logicId_;

	RectF RestartRect() const;
};
