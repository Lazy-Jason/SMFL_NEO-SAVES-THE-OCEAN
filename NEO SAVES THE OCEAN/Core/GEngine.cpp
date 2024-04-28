// GEngine.cpp
#include "GEngine.h"

// Initialize the static member variable
GEngine* GEngine::Instance = nullptr;  // Global instance of the GEngine class

// Constructor
GEngine::GEngine(int WindowWidth_px, int WindowHeight_px, sf::String GameWindowTitle)
{
    this->GameWindowSize.x = WindowWidth_px;  // Set the game window width
    this->GameWindowSize.y = WindowHeight_px;  // Set the game window height
    this->GameWindowTitle = GameWindowTitle;  // Set the game window title
    this->GameVideoMode = sf::VideoMode(GameWindowSize.x, GameWindowSize.y);  // Set the video mode
    InitWindow();  // Initialize the game window
}

// Destructor
GEngine::~GEngine()
{
    delete GameWindow;  // Delete the game window
    delete Instance;  // Delete the instance of the GEngine class
}

// Get the instance of the GEngine class
GEngine& GEngine::GetInstance()
{
    return *Instance;
}

// Initialize the game window
void GEngine::InitWindow()
{
    // Create the game window
    this->GameWindow = new sf::RenderWindow(GameVideoMode, GameWindowTitle, sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize); 
}

// Update the game logic
void GEngine::UpdateGameLogic()
{
    // Add your game logic update code here
}

// Update the game pool events
void GEngine::UpdateGamePoolEvents()
{
    while (GameWindow->pollEvent(GameWindowEvent))
    {  // Poll events from the game window
        switch (GameWindowEvent.type)
        {
            case sf::Event::Closed:
                // Close the game window
                GameWindow->close();
                break;
            case sf::Event::KeyReleased:
                if (GameWindowEvent.key.code == sf::Keyboard::Escape)
                    // Close the game window if the Escape key is released
                    GameWindow->close();
                break;
            case sf::Event::MouseMoved:
                // Recalculate mouse move
                RecalculateMouseMove();
                break;
            case sf::Event::MouseButtonPressed:
                // Recalculate mouse button pressed
                RecalculateMousePressed();
                break;
        }
    }
}

// Update the game
void GEngine::UpdateGame()
{
    UpdateGamePoolEvents();  // Update the game pool events
    // Add other game loop update code here
}

// Render the menu HUD
void GEngine::RenderMenuHUD()
{
    Menu_Hud.DrawToWindow(*GameWindow);  // Draw the menu HUD to the game window
}

// Recalculate mouse move
void GEngine::RecalculateMouseMove()
{
    switch (Current_GameLeveState)
    {
        case GameLevelState::Menu_Level:
            Menu_Hud.OnMouseButtonMove(*GameWindow);  // Handle mouse move in the menu level
            break;
        case GameLevelState::GameLevel:
            // Handle mouse move in the game level
            break;
    }
}

// Recalculate mouse button pressed
void GEngine::RecalculateMousePressed()
{
    switch (Current_GameLeveState)
    {
        case GameLevelState::Menu_Level:
            Menu_Hud.OnMouseButtonAction(sf::Mouse::Left);  // Handle left mouse button press in the menu level
            Menu_Hud.OnMouseButtonAction(sf::Mouse::Right);  // Handle right mouse button press in the menu level
            break;
        case GameLevelState::GameLevel:
            // Handle mouse button press in the game level
            break;
    }
}

// Render the game
void GEngine::RenderGame()
{
    GameWindow->clear(sf::Color(110.0f, 110.0f, 110.0f));  // Clear the game window with a light gray color
    RenderMenuHUD();  // Render the menu HUD
    GameWindow->display();  // Display the game window
}