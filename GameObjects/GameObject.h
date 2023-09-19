#pragma once

class GameObject
{
public:
	virtual void UpdateLogic() = 0;
	virtual void UpdateRender() = 0;
};
