#include "GameMap.h"
#include "Viewport.h"
#include "Camera.h"


GameMap::GameMap(char* filePath)
{
    LoadMap(filePath);
}

GameMap::~GameMap()
{
    delete map;
}

void GameMap::LoadMap(char *filePath)
{
    map = new Tmx::Map();
    map->ParseFile(filePath);

    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = this->GetWidth();
    r.bottom = this->GetHeight();

    for (size_t i = 0; i < map->GetNumTilesets(); i++)
    {
        const Tmx::Tileset *tileset = map->GetTileset(i);

		GameSprite *sprite = new GameSprite(tileset->GetImage()->GetSource().c_str());

        listTileset.insert(std::pair<int, GameSprite*>(i, sprite));
    }
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

        RECT sourceRECT;

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

					/*sourceRECT.top = y * tileHeight * 3;
					sourceRECT.bottom = sourceRECT.top + tileHeight * 3;
					sourceRECT.left = x * tileWidth * 3;
					sourceRECT.right = sourceRECT.left + tileWidth * 3;*/

					int posX = n * tileWidth * 3;
					int posY = WORLD_Y - m * tileHeight * 3;

                    D3DXVECTOR3 position(posX, posY, 0);

					sourceRECT.top = posY;
					sourceRECT.bottom = posY - tileHeight*3;
					sourceRECT.left = posX;
					sourceRECT.right = posX + tileSetWidth*3;


					VT3 positionInViewPort = Viewport::GetInstance()->GetPositionInViewport(position);
					VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());

					VT2 translation = VT2(-cameraPosition.x, -cameraPosition.y);

					sprite->Draw(positionInViewPort, translation, VT3(0, 0, 0), sourceRECT, VT2(3, 3));
                }
            }
        }
    }    
}