// GEngine.cpp
#include "GEngine.h"
#include <chrono>
#include "../GameMenu/MainMenu/LMenu_Hud.h"
#include "../GameMenu/MainMenu/LMainMenu_Screen.h"
#include "Levels/Children/LMainMenu_Level.h"
#include "LSpawnableObject.h"
#include "Levels/LLevel.h"

GEngine* GEngine::Instance = nullptr;

GEngine::GEngine(int WindowWidth_px, int WindowHeight_px, const std::string& GameWindowTitle)
    : GameVideoMode(WindowWidth_px, WindowHeight_px), GameWindowEvent()
{
    this->GameWindowSize = {static_cast<unsigned>(WindowWidth_px), static_cast<unsigned>(WindowHeight_px)};
    this->GameWindowTitle = GameWindowTitle;
}

GEngine::~GEngine()
{
    delete Instance;
}

GEngine& GEngine::Build(int WindowWidth_px, int WindowHeight_px, const std::string& GameWindowTitle)
{
    if ( Instance != nullptr ) throw std::runtime_error("you are not allowed to build the engine twice!");
    
    Instance = new GEngine(WindowWidth_px, WindowHeight_px, GameWindowTitle);
    Instance->LoadLevel( new LMainMenu_Level() );
    return *Instance;
}

GEngine& GEngine::GetInstance()
{
    if (Instance == nullptr) throw std::runtime_error("engine was not started");

    return *Instance;
}

void GEngine::SetCurrentGameLevelState(GameLevelState state)
{
    CurrentGameLevelState = state;
}

void GEngine::LoadLevel(LLevel* newLevel)
{
    if(newLevel == nullptr) return;
    
    ActiveLevel.reset(newLevel);
    ActiveLevel->Init();
}

void GEngine::UpdateGame()
{
    const auto currentTime = std::chrono::system_clock::now();
    const std::chrono::duration<float> elapsedSeconds = currentTime - Last_Frame_Time;
    DeltaTime = elapsedSeconds.count();
    Last_Frame_Time = currentTime;
    
    UpdateGamePoolEvents();

    if( ActiveLevel == nullptr ) throw std::runtime_error("No active level, a level must be initialised");

    ActiveLevel->Update(DeltaTime);
}

void GEngine::RenderGame() const
{
    GameWindow->clear(sf::Color(190, 190, 190));

    if( ActiveLevel == nullptr ) throw std::runtime_error("No active level, a level must be initialised");

    ActiveLevel->Render(*GameWindow);
    GameWindow->display();
}

void GEngine::InitWindow()
{
    GameWindow = new sf::RenderWindow(GameVideoMode, GameWindowTitle, sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
}

void GEngine::RecalculateMouseMove() const
{
    if( ActiveLevel == nullptr ) return;

    ActiveLevel->OnMouseButtonMove(*GameWindow);
}

void GEngine::RecalculateMousePressed() const
{
    if( ActiveLevel == nullptr ) return;
    
    ActiveLevel->OnMouseButtonAction(sf::Mouse::Left);
    ActiveLevel->OnMouseButtonAction(sf::Mouse::Right);
}

void GEngine::UpdateGamePoolEvents()
{
    while (GameWindow->pollEvent(GameWindowEvent))
    {
        switch (GameWindowEvent.type)
        {
        case sf::Event::Closed:
            GameWindow->close();
            break;
        case sf::Event::KeyPressed:
            if( ActiveLevel == nullptr ) return;

            ActiveLevel->OnKeyPressed(GameWindowEvent.key.code);
            break;
        case sf::Event::KeyReleased:
            if( ActiveLevel == nullptr ) return;

            ActiveLevel->OnKeyReleased(GameWindowEvent.key.code);
            break;
        case sf::Event::MouseMoved:
            RecalculateMouseMove();
            break;
        case sf::Event::MouseButtonPressed:
            RecalculateMousePressed();
            break;
        default: ;
        }
    }
}