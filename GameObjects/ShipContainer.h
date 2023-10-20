#include "Ship.h"

class ShipContainer
{
private:
	GameManager& gm_;
	RectF rect_;
	const Font& font_;
	int index_;
	int logicId_;
	int renderId_;
	std::vector<std::unique_ptr<Ship>> ships_;

public:
	ShipContainer(GameManager& gm, RectF rect, const Font& font, int index)
		: gm_(gm), rect_(rect), index_(index), font_(font)
	{
		// Register functions and save their IDs
		logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
		renderId_ = gm_.registerRender([this]() { this->UpdateRender(); });
	}

	~ShipContainer()
	{
		// Unregister the callbacks in the destructor
		Print << U"Destruct SortieButton";
		gm_.unregisterLogic(logicId_);
		gm_.unregisterRender(renderId_);

}

	void UpdateLogic();
	void UpdateRender();
};
