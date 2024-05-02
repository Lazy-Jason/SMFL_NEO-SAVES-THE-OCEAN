// GEngine.cpp
#include "GEngine.h"
#include "../GameMenu/MainMenu/LMenu_Hud.h"
#include "../GameMenu/MainMenu/LMainMenu_Screen.h"

GEngine* GEngine::Instance = nullptr;

GEngine::GEngine(int WindowWidth_px, int WindowHeight_px, const std::string& GameWindowTitle)
:GameVideoMode(WindowWidth_px, WindowHeight_px)
{
    this->GameWindowSize = {static_cast<unsigned>(WindowWidth_px), static_cast<unsigned>(WindowHeight_px)};
    this->GameWindowTitle = GameWindowTitle;
}

GEngine::~GEngine() = default;

GEngine& GEngine::Build(int WindowWidth_px, int WindowHeight_px, const std::string& GameWindowTitle)
{
    if ( Instance != nullptr )
    {
        throw std::runtime_error("you are not allowed to build the engine twice!");
    }
    Instance = new GEngine(WindowWidth_px, WindowHeight_px, GameWindowTitle);
    Instance->MenuHud = new LMenu_Hud();
    Instance->MainMenuScreen = new LMainMenu_Screen();
    return *Instance;
}


GEngine& GEngine::GetInstance()
{
    if (Instance == nullptr)
    {
        throw std::runtime_error("engine was not started");
        //Instance = new GEngine();
    }
    return *Instance;
}

void GEngine::SetCurrentGameLevelState(GameLevelState state)
{
    CurrentGameLevelState = state;
}

void GEngine::UpdateGame()
{
    UpdateGamePoolEvents();
    UpdateGameLogic();

    // Call registered update functions
    for (const auto& updateFunction : UpdateFunctions)
    {
        updateFunction();
    }
}

void GEngine::RenderGame() const
{
    GameWindow->clear(sf::Color(190, 190, 190));
    RenderMenuHUD(); 

    // Call registered render functions
    for (const auto& renderFunction : RenderFunctions)
    {
        renderFunction();
    }

    GameWindow->display();
}

void GEngine::RegisterUpdateFunction(const std::function<void()>& updateFunction)
{
    UpdateFunctions.push_back(updateFunction);
}

void GEngine::RegisterRenderFunction(const std::function<void()>& renderFunction)
{
    RenderFunctions.push_back(renderFunction);
}

void GEngine::InitWindow()
{
    GameWindow = new sf::RenderWindow(GameVideoMode, GameWindowTitle, sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
}

void GEngine::UpdateGameLogic()
{
    // Add your game logic update code here
}

void GEngine::RenderMenuHUD() const
{
    MenuHud->DrawToWindow(*GameWindow);
}

void GEngine::RecalculateMouseMove() const
{
    switch (CurrentGameLevelState)
    {
    case GameLevelState::Menu_Level:
        MenuHud->OnMouseButtonMove(*GameWindow);
        break;
    case GameLevelState::GameLevel:
        // Handle mouse move in the game level
        break;
    }
}

void GEngine::RecalculateMousePressed() const
{
    switch (CurrentGameLevelState)
    {
    case GameLevelState::Menu_Level:
        MenuHud->OnMouseButtonAction(sf::Mouse::Left);
        MenuHud->OnMouseButtonAction(sf::Mouse::Right);
        break;
    case GameLevelState::GameLevel:
        // Handle mouse button press in the game level
            break;
    }
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
        case sf::Event::KeyReleased:
            if (GameWindowEvent.key.code == sf::Keyboard::Escape)
                GameWindow->close();
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