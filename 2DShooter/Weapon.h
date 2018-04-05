#pragma once
#include "GamePart.h"

class WP_ChargeRifle : public Weapon
{
private:

public:
	WP_ChargeRifle(){
		damage = 10;
		bulletSpeed = 2.0;
		fireRate = 0.15;

		rotateCenter = { 80,30 };
		gunLength = 95;
	};

	virtual void LoadTexture();

	virtual bool HandleMessage(const Telegram& msg);
	void SetPos(float x, float y);

	void RenderForPlayer();

	Graphic* GetGraphic() { return &graph;};
};