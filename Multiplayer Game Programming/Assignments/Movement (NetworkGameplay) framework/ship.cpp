#include "Ship.h"
#include <hge.h>
#include <hgeSprite.h>
#include <hgefont.h>

#define SHIPTYPE1 "ship1.png"
#define SHIPTYPE2 "ship2.png"
#define SHIPTYPE3 "ship3.png"
#define SHIPTYPE4 "ship4.png"

Ship::Ship(int type, float x, float y)
{
	std::cout << "Ship created at " << pos << std::endl;

#ifdef  INTERPOLATEMOVEMENT
	pos.x = serverPos.x = clientPos.x = x;
	pos.y = serverPos.y = clientPos.y = y;
#else
	pos.x = x;
	pos.y = y;
#endif //  INTERPOLATEMOVEMENT

	HGE* hge = hgeCreate(HGE_VERSION);

	switch (type)
	{
	case 2:
		textureID = hge->Texture_Load(SHIPTYPE2);
		type = 2;

	case 3:
		textureID = hge->Texture_Load(SHIPTYPE3);
		type = 3;

	case 4:
		textureID = hge->Texture_Load(SHIPTYPE4);
		type = 4;

	default:
		textureID = hge->Texture_Load(SHIPTYPE1);
		type = 1;
		break;
	}
	hge->Release();

	sprite.reset(new hgeSprite(textureID, 0, 0, 64, 64));

	font.reset(new hgeFont("font1.fnt"));
	font->SetScale(0.5);
	sprite->SetHotSpot(32, 32);
}


Ship::~Ship()
{
}
