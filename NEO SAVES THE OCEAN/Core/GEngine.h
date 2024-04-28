// GEngine.h
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../GameMenu/MainMenu/LMainMenu_Screen.h"
#include "../GameMenu/MainMenu/LMenu_Hud.h"

/**
 * @brief Represents the current state of the game level.
 */
enum class GameLevelState
{
    Menu_Level,  ///< The game is in the menu level.
    GameLevel    ///< The game is in a playable level.
};

/**
 * @brief The game engine class that manages the game loop, rendering, and game state.
 */
class GEngine
{
private:
    static GEngine* Instance;  ///< The singleton instance of the game engine.

    sf::RenderWindow* GameWindow = nullptr;  ///< The game window.
    sf::VideoMode GameVideoMode;             ///< The video mode of the game window.
    sf::Event GameWindowEvent;               ///< The event associated with the game window.
    sf::String GameWindowTitle;              ///< The title of the game window.
    sf::Vector2i GameWindowSize;             ///< The size of the game window.
    sf::Font MenuFont;                       ///< The font used for the menu.
    LMenu_Hud Menu_Hud;                      ///< The menu HUD object.
    LMainMenu_Screen Main_Menu_Screen;       ///< The main menu screen object.

    /**
     * @brief Keeps track of the current level of the game, e.g., if the game is on the menu or in a playable level.
     */
    GameLevelState Current_GameLeveState = GameLevelState::Menu_Level;

public:
    /**
     * @brief Constructs a GEngine object with the specified window size and title.
     * @param WindowWidth_px The width of the game window in pixels (default is 1920).
     * @param WindowHeight_px The height of the game window in pixels (default is 1080).
     * @param GameWindowTitle The title of the game window (default is "Default Title").
     */
    GEngine(int WindowWidth_px = 1920, int WindowHeight_px = 1080, sf::String GameWindowTitle = "Default Title");

    /**
     * @brief Destroys the GEngine object and its associated resources.
     */
    virtual ~GEngine();

    /**
     * @brief Returns the singleton instance of the GEngine class.
     * @return The singleton instance of the GEngine class.
     */
    static GEngine& GetInstance();

    /**
     * @brief Returns a reference to the game window.
     * @return A reference to the game window.
     */
    sf::RenderWindow& GetGameWindow() const { return *GameWindow; }

    /**
     * @brief Returns the video mode of the game window.
     * @return The video mode of the game window.
     */
    sf::VideoMode GetGameVideoMode() const { return GameVideoMode; }

    /**
     * \brief Returns if the game window is open or not.
     * \return The window's open state.
     */
    bool GetGameWindowOpen() const { return GameWindow->isOpen(); }

    /**
     * @brief Returns the event associated with the game window.
     * @return The event associated with the game window.
     */
    sf::Event GetGameWindowEvent() const { return GameWindowEvent; }

    /**
     * @brief Returns the title of the game window.
     * @return The title of the game window.
     */
    sf::String GetGameWindowTitle() const { return GameWindowTitle; }

    /**
     * @brief Returns the size of the game window.
     * @return The size of the game window.
     */
    sf::Vector2i GetGameWindowSize() const { return GameWindowSize; }

    /**
     * @brief Returns a reference to the menu font.
     * @return A reference to the menu font.
     */
    sf::Font& GetMenuFont() { return MenuFont; }

    /**
     * @brief Returns a reference to the menu HUD object.
     * @return A reference to the menu HUD object.
     */
    LMenu_Hud& GetMenu_Hud() { return Menu_Hud; }

    /**
     * @brief Returns a reference to the main menu screen object.
     * @return A reference to the main menu screen object.
     */
    LMainMenu_Screen& GetMain_Menu_Screen() { return Main_Menu_Screen; }

    /**
     * @brief Returns the current game level state.
     * @return The current game level state.
     */
    GameLevelState GetCurrent_GameLeveState() const { return Current_GameLeveState; }

    /**
     * @brief Updates the game loop.
     */
    void UpdateGame();

    /**
     * @brief Renders the game.
     */
    void RenderGame();

private:
    /**
     * @brief Initializes the game window.
     */
    void InitWindow();

    /**
     * @brief Updates the game logic.
     */
    void UpdateGameLogic();

    /**
     * @brief Renders the menu HUD.
     */
    void RenderMenuHUD();

    /**
     * @brief Recalculates the mouse move event based on the current game level state.
     */
    void RecalculateMouseMove();

    /**
     * @brief Recalculates the mouse pressed event based on the current game level state.
     */
    void RecalculateMousePressed();

    /**
     * @brief Updates the game pool events.
     */
    void UpdateGamePoolEvents();
};