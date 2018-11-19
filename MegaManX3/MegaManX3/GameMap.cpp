#include "GameMap.h"
#include "Viewport.h"
#include "Camera.h"


GameMap::GameMap(){
}

GameMap::~GameMap()
{
	delete map;

	for (size_t i = 0; i < vtStaticObject.size(); i++)
	{
		if (vtStaticObject[i])
			delete vtStaticObject[i];
	}
	vtStaticObject.clear();

	delete quadtree;
}

void GameMap::Init(char* filePath)
{
    LoadMap(filePath);
}


GameMap* GameMap::instance = NULL;
GameMap* GameMap::GetInstance() {
	if (!GameMap::instance) {
		GameMap::instance = new GameMap();
	}
	return GameMap::instance;
}

void GameMap::LoadMap(char *filePath)
{
    map = new Tmx::Map();
    map->ParseFile(filePath);
	
    Rect r;
    r.left = 0;
    r.top = this->GetHeight();
    r.right = this->GetWidth();
    r.bottom = 0;

	quadtree = new Quadtree(1, r);

    for (size_t i = 0; i < map->GetNumTilesets(); i++)
    {
        const Tmx::Tileset *tileset = map->GetTileset(i);

		GameSprite *sprite = new GameSprite(tileset->GetImage()->GetSource().c_str());

        listTileset.insert(std::pair<int, GameSprite*>(i, sprite));
    }

#pragma region -OBJECTGROUP, STATIC OBJECT-

	for (size_t i = 0; i < map->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);
		if (objectGroup->GetName() == "Static")
		{
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				//lay object group chu khong phai layer
				//object group se chua nhung body
				Tmx::Object *object = objectGroup->GetObjects().at(j);
				int posX = (object->GetX()) * 3;
				int posY = WORLD_Y - (object->GetY()) * 3;
				GameObject* staticObj = new GameObject();
				VT3 position(posX, posY, 0);
				staticObj->SetPosition(position);
				Rect StaticRect = {
					posY,
					posX,
					posY - object->GetHeight(),
					posX + object->GetWidth()
				};
				staticObj->SetRect(StaticRect);
				
				quadtree->InsertObject(staticObj);
			}
		}
	}
#pragma endregion
}

Tmx::Map* GameMap::GetMap()
{
    return map;
}

int GameMap::GetWidth()
{
    return map->GetWidth() * map->GetTileWidth();
}

int GameMap::GetHeight()
{
    return map->GetHeight() * map->GetTileHeight();
}

int GameMap::GetTileWidth()
{
    return map->GetTileWidth();
}

int GameMap::GetTileHeight()
{
    return map->GetTileHeight();
}

void GameMap::Draw()
{
    for (size_t i = 0; i < map->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer *layer = map->GetTileLayer(i);

        if (!layer->IsVisible())
        {
            continue;
        }

        int tileWidth = map->GetTileWidth();
        int tileHeight = map->GetTileHeight();

        for (size_t m = 0; m < layer->GetHeight(); m++)
        {
            for (size_t n = 0; n < layer->GetWidth(); n++)
            {
                int tilesetIndex = layer->GetTileTilesetIndex(n, m);

                if (tilesetIndex != -1)
                {
                    const Tmx::Tileset *tileSet = map->GetTileset(tilesetIndex);

                    int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
                    int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

                    GameSprite *sprite = listTileset[layer->GetTileTilesetIndex(n, m)];

                    //tile index
                    int tileID = layer->GetTileId(n, m);

                    int y = tileID / tileSetWidth;
                    int x = tileID - y * tileSetWidth;

					RECT sourceRECT;
					sourceRECT.top = y * tileHeight;
					sourceRECT.bottom = sourceRECT.top + tileHeight;
					sourceRECT.left = x * tileWidth;
					sourceRECT.right = sourceRECT.left + tileWidth;

					int posX = n * tileWidth * 3;
					int posY = WORLD_Y - m * tileHeight * 3;

                    D3DXVECTOR3 position(posX, posY, 0);

					VT3 positionInViewPort = Viewport::GetInstance()->GetPositionInViewport(position);
					VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());

					VT2 translation = VT2(-cameraPosition.x, -cameraPosition.y);

					sprite->Draw(positionInViewPort, translation, VT3(0, 0, 0), sourceRECT, VT2(3, 3));
                }
            }
        }
    } 
}

Quadtree* GameMap::GetQuadtree() {
	return quadtree;
}