# include <Siv3D.hpp> // Siv3D v0.6.16

#include "GameManager.h"
#include "GameObjects/Base.h"
#include "GameObjects/BattleBalance.h"
#include "GameObjects/Currency.h"
#include "GameObjects/EnemySpawner.h"
#include "GameObjects/IncomeButton.h"
#include "GameObjects/Match.h"
#include "GameObjects/ShipContainer.h"
#include "GameObjects/SortieButton.h"
#include "GameObjects/UnitCatalog.h"
#include <algorithm>

void Main()
{
	constexpr int windowWidth = 1920;
	constexpr int windowHeight = 1080;
	constexpr double shipAreaRatio = 3.0 / 5.0;
	constexpr double buttonAreaRatio = 2.0 / 5.0;
	constexpr double buttonSize = 164.0;
	constexpr double buttonGap = 16.0;

	if constexpr (windowWidth * 9 != windowHeight * 16)
	{
		throw Error(U"You should set the resolution to 16:9");
	}
	Window::Resize(windowWidth, windowHeight);
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetBackground(Palette::Lightblue);

	GameManager gm;
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
	Currency currency(gm, font, BattleBalance::StartingMoney, BattleBalance::IncomePerSecond);
	Base playerBase(gm, font, Faction::Player, BattleBalance::PlayerBaseHp);
	Base enemyBase(gm, font, Faction::Enemy, BattleBalance::EnemyBaseHp);
	Match match(gm, playerBase, enemyBase, font);
	ShipContainer shipContainer(
		gm,
		RectF{ 0, 0, Scene::Width(), shipAreaRatio * Scene::Height() },
		font,
		0,
		playerBase,
		enemyBase,
		match);
	EnemySpawner enemySpawner(gm, shipContainer, match);

	const double buttonsTop = shipAreaRatio * Scene::Height();
	const double panelHeight = buttonAreaRatio * Scene::Height();
	std::vector<UnitStats> sortieTypes = PlayerUnitTypes();
	std::stable_sort(sortieTypes.begin(), sortieTypes.end(), [](const UnitStats& a, const UnitStats& b)
	{
		return a.cost < b.cost;
	});
	const int slotCount = static_cast<int>(sortieTypes.size()) + 1;
	const double rowWidth = slotCount * buttonSize + (slotCount - 1) * buttonGap;
	const double originX = (Scene::Width() - rowWidth) * 0.5;
	const double originY = buttonsTop + (panelHeight - buttonSize) * 0.5;

	std::vector<std::unique_ptr<SortieButton>> buttons;
	buttons.reserve(sortieTypes.size());
	for (int i = 0; i < static_cast<int>(sortieTypes.size()); ++i)
	{
		const RectF rect{
			originX + i * (buttonSize + buttonGap),
			originY,
			buttonSize,
			buttonSize };
		buttons.push_back(std::make_unique<SortieButton>(
			gm, shipContainer, currency, rect, font, sortieTypes[static_cast<size_t>(i)]));
	}
	const RectF incomeRect{
		originX + sortieTypes.size() * (buttonSize + buttonGap),
		originY,
		buttonSize,
		buttonSize };
	auto income = std::make_unique<IncomeButton>(gm, currency, incomeRect, font);

	while (System::Update())
	{
		RectF{ 0, buttonsTop, Scene::Width(), buttonAreaRatio * Scene::Height() }.draw(Palette::Lightslategray);

		currency.SetActive(match.IsPlaying());
		if (match.IsPlaying())
		{
			for (auto& button : buttons)
			{
				button->Click();
			}
			if (income)
			{
				income->Click();
			}
		}
		else if (match.RestartClicked())
		{
			playerBase.Reset();
			enemyBase.Reset();
			shipContainer.Clear();
			currency.Reset(BattleBalance::StartingMoney, BattleBalance::IncomePerSecond);
			for (auto& button : buttons)
			{
				button->ResetCooldown();
			}
			if (income)
			{
				income->Reset();
			}
			enemySpawner.Reset();
			match.Reset();
			currency.SetActive(true);
		}

		gm.updateLogic();
		gm.updateRender();
		match.DrawOverlay();
	}
}
