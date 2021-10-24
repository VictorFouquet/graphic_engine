#include "tileSheetLayer.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "core.h"

static const uint32_t _tileMapWidth = 24;
static const char* _tileMap = 
"bbbbbbbbbbbbbbbbbbbbbbbb"
"aaaaaaaaaaaaaaaaaaaaaaaa"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"fffffffffffffffffffhAAAA"
"ggggggggggggnnnnnnniAAAA"
"AAAAAAAAAAAAAnnnnnniAAAA"
"AAAAAAAAAAAAAAlllkniAAAA"
"cccccccccdAAAAAAAmniAAAA"
"bbbbbbbbbeAAAAAAAmniAAAA";

static const char* _building = 
"000000000000000000000000"
"000000000000000000000000"
"000000000000000000000000"
"000000000000000000000000"
"000000000000DE0000000000"
"000000000000DE0000000000"
"00000000000FBCG000000000"
"000000000000000000000000"
"000000000000000000000000";

static const char* _buildingDetails = 
"000000000000000000000000"
"000000000000000000000000"
"000000000000JM0000000000"
"00000000000PILS000000000"
"000000000YXOHKR000000000"
"00000000000N0UQVVW000000"
"000000000000T00000000000"
"000000000000000000000000"
"000000000000000000000000";

static const char* _trees = 
"000000000000000000000000"
"000000000000000000000q00"
"000v000000000000s0v0qrp0"
"00000q00000000000000r0o0"
"000p0ru0pp00000000000q00"
"000op0t0oo00000p0000ur0p"
"0000o0000000000op000t0po"
"00000000000s0000o000s0o0"
"00000000000000v000000000";


TileSheetLayer::TileSheetLayer()
    : GraphicEngine::Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f, true)
{

}

void TileSheetLayer::onAttach() 
{
    _spriteSheet = GraphicEngine::Texture2D::create("client/assets/RPGpack_sheet_2X.png");
    _textureStairs = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 7.0f, 6.0f }, { 128.0f, 128.0f });
    _textureBarrel = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 8.0f, 2.0f }, { 128.0f, 128.0f });
    _textureTree = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 2.0f, 1.0f }, { 128.0f, 128.0f }, { 1, 2 });

    _textureMap['A'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 1.0f, 11.0f }, { 128.0f, 128.0f });
    _textureMap['B'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 1.0f, 9.0f }, { 128.0f, 128.0f });
    _textureMap['C'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 3.0f, 9.0f }, { 128.0f, 128.0f });
    _textureMap['D'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 4.0f, 9.0f }, { 128.0f, 128.0f });
    _textureMap['E'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 6.0f, 9.0f }, { 128.0f, 128.0f });
    _textureMap['F'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 7.0f, 9.0f }, { 128.0f, 128.0f });
    _textureMap['G'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 8.0f, 9.0f }, { 128.0f, 128.0f });

    _textureMap['H'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 2.0f, 4.0f }, { 128.0f, 128.0f });
    _textureMap['I'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 2.0f, 5.0f }, { 128.0f, 128.0f });
    _textureMap['J'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 2.0f, 6.0f }, { 128.0f, 128.0f });
    _textureMap['K'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 3.0f, 4.0f }, { 128.0f, 128.0f });
    _textureMap['L'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 3.0f, 5.0f }, { 128.0f, 128.0f });
    _textureMap['M'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 3.0f, 6.0f }, { 128.0f, 128.0f });

    _textureMap['N'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 0.0f, 4.0f }, { 128.0f, 128.0f });
    _textureMap['O'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 0.0f, 5.0f }, { 128.0f, 128.0f });
    _textureMap['P'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 0.0f, 6.0f }, { 128.0f, 128.0f });
    _textureMap['Q'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 1.0f, 4.0f }, { 128.0f, 128.0f });
    _textureMap['R'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 1.0f, 5.0f }, { 128.0f, 128.0f });
    _textureMap['S'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 1.0f, 6.0f }, { 128.0f, 128.0f });

    _textureMap['T'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 14.0f, 0.0f }, { 128.0f, 128.0f });
    _textureMap['U'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 10.0f, 3.0f }, { 128.0f, 128.0f });

    _textureMap['V'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 6.0f, 2.0f }, { 128.0f, 128.0f });
    _textureMap['W'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 7.0f, 2.0f }, { 128.0f, 128.0f });
    _textureMap['X'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 6.0f, 1.0f }, { 128.0f, 128.0f });
    _textureMap['Y'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 7.0f, 1.0f }, { 128.0f, 128.0f });

    _textureMap['a'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 11.0f, 10.0f }, { 128.0f, 128.0f }); 
    _textureMap['b'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 11.0f, 11.0f }, { 128.0f, 128.0f }); 
    _textureMap['c'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 11.0f, 12.0f }, { 128.0f, 128.0f }); 
    _textureMap['d'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 12.0f, 12.0f }, { 128.0f, 128.0f }); 
    _textureMap['e'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 12.0f, 11.0f }, { 128.0f, 128.0f }); 

    _textureMap['f'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 6.0f, 12.0f }, { 128.0f, 128.0f }); 
    _textureMap['g'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 6.0f, 10.0f }, { 128.0f, 128.0f });
    _textureMap['h'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 7.0f, 12.0f }, { 128.0f, 128.0f });
    _textureMap['i'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 7.0f, 11.0f }, { 128.0f, 128.0f });
    _textureMap['j'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 5.0f, 11.0f }, { 128.0f, 128.0f });
    _textureMap['k'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 2.0f, 12.0f }, { 128.0f, 128.0f });
    _textureMap['l'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 1.0f, 12.0f }, { 128.0f, 128.0f });
    _textureMap['m'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 2.0f, 11.0f }, { 128.0f, 128.0f });
    _textureMap['n'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 6.0f, 11.0f }, { 128.0f, 128.0f });

    _textureMap['o'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 0.0f, 1.0f }, { 128.0f, 128.0f });
    _textureMap['p'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 0.0f, 2.0f }, { 128.0f, 128.0f });
    _textureMap['q'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 1.0f, 2.0f }, { 128.0f, 128.0f });
    _textureMap['r'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 1.0f, 1.0f }, { 128.0f, 128.0f });
    _textureMap['s'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 0.0f, 3.0f }, { 128.0f, 128.0f });
    _textureMap['t'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 2.0f, 1.0f }, { 128.0f, 128.0f });
    _textureMap['u'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 2.0f, 2.0f }, { 128.0f, 128.0f });
    _textureMap['v'] = GraphicEngine::SubTexture2D::createFromCoords(_spriteSheet, { 2.0f, 3.0f }, { 128.0f, 128.0f });

    _mapWidth = _tileMapWidth;
    _mapHeight = strlen(_tileMap) / _mapWidth;

    _cameraController.setZoomLevel(8.0f);
}

void TileSheetLayer::onDetach() 
{
    
}

void TileSheetLayer::onUpdate(GraphicEngine::Timestep timestep)
{
    _cameraController.onUpdate(timestep);

    GraphicEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    GraphicEngine::RenderCommand::clear();

    GraphicEngine::Renderer2D::beginScene(_cameraController.getCamera());

    for (uint32_t y = 0; y < _mapHeight; y++)
    {
        for (uint32_t x = 0; x < _mapWidth; x++)
        {
            char tileType =  _tileMap[x + y * _mapWidth];
            GraphicEngine::Ref<GraphicEngine::SubTexture2D> texture;
            if (_textureMap.find(tileType) != _textureMap.end())
                texture = _textureMap[tileType];
            else
               texture = _textureBarrel;
            GraphicEngine::Renderer2D::drawQuad({x - _mapWidth / 2.0f, _mapHeight - y - _mapHeight / 2.0f, 0.0f}, { 1.0f, 1.0f }, texture);

            tileType = _building[x + y * _mapWidth];
            if (tileType != '0') {
                if (_textureMap.find(tileType) != _textureMap.end())
                    texture = _textureMap[tileType];
                else
                texture = _textureBarrel;
                GraphicEngine::Renderer2D::drawQuad({x - _mapWidth / 2.0f, _mapHeight - y - _mapHeight / 2.0f, 0.1f}, { 1.0f, 1.0f }, texture);
            }

            tileType = _buildingDetails[x + y * _mapWidth];
            if (tileType != '0') {
                if (_textureMap.find(tileType) != _textureMap.end())
                    texture = _textureMap[tileType];
                else
                texture = _textureBarrel;
                GraphicEngine::Renderer2D::drawQuad({x - _mapWidth / 2.0f, _mapHeight - y - _mapHeight / 2.0f, 0.2f}, { 1.0f, 1.0f }, texture);
            }

            tileType = _trees[x + y * _mapWidth];
            if (tileType != '0') {
                if (_textureMap.find(tileType) != _textureMap.end())
                    texture = _textureMap[tileType];
                else
                texture = _textureBarrel;
                GraphicEngine::Renderer2D::drawQuad({x - _mapWidth / 2.0f, _mapHeight - y - _mapHeight / 2.0f, 0.3f}, { 1.0f, 1.0f }, texture);
            }
        }
    }

    GraphicEngine::Renderer2D::endScene();
}

void TileSheetLayer::onEvent(GraphicEngine::Event& event) 
{
    _cameraController.onEvent(event);
}

void TileSheetLayer::onImGuiRender() 
{
    ImGui::Begin("Settings");
        
    ImGui::ColorEdit3("Color", glm::value_ptr(_lightBlueColor));

    ImGui::End();
}
