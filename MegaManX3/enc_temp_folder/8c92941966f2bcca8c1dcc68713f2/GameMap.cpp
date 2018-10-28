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

void GameMap::LoadMap(char* filePath)
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

		GameSprite *sprite = new GameSprite(MAP_PATH);

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

					sourceRECT.top = y * tileHeight;
					sourceRECT.bottom = sourceRECT.top + tileHeight;
					sourceRECT.left = x * tileWidth;
					sourceRECT.right = sourceRECT.left + tileWidth;

                    //tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
                    //dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
                    D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

					VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());

					VT2 translation = VT2(-cameraPosition.x, -cameraPosition.y);

					VT3 inPosition = Viewport::GetInstance()->GetPositionInViewport(VT3(x * tileWidth, y * tileHeight, 0));

					sprite->Draw(VT3(x * tileWidth, y * tileHeight, 0), VT2(0, 0), VT3(0, 0, 0), sourceRECT);
                }
            }
        }
    }    
}