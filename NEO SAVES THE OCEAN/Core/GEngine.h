// GEngine.h
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include <functional>

class LMenu_Hud;
class LMainMenu_Screen;

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
public:
    /**
     * @brief Constructs a GEngine object with the specified window size and title.
     * @param WindowWidth_px The width of the game window in pixels (default is 1920).
     * @param WindowHeight_px The height of the game window in pixels (default is 1080).
     * @param GameWindowTitle The title of the game window (default is "Default Title").
     */
    GEngine(int WindowWidth_px = 1920, int WindowHeight_px = 1080, const std::string& GameWindowTitle = "Default Title");

    /**
     * @brief Destroys the GEngine object and its associated resources.
     */
    ~GEngine();

    /**
     * @brief Returns the singleton instance of the GEngine class.
     * @return The singleton instance of the GEngine class.
     */
    static GEngine& GetInstance();

    static GEngine& Build(int WindowWidth_px, int WindowHeight_px, const std::string& GameWindowTitle);

    /**
    * @brief Initializes the game window.
    */
    void InitWindow();
 
    /**
     * @brief Returns a reference to the game window.
     * @return A reference to the game window.
     */
    sf::RenderWindow& GetGameWindow() const { return *GameWindow; }

    /**
     * @brief Returns the video mode of the game window.
     * @return The video mode of the game window.
     */
    const sf::VideoMode& GetGameVideoMode() const { return GameVideoMode; }

    /**
     * \brief Returns if the game window is open or not.
     * \return The window's open state.
     */
    bool IsGameWindowOpen() const { return GameWindow->isOpen(); }

    /**
     * @brief Returns the event associated with the game window.
     * @return The event associated with the game window.
     */
    const sf::Event& GetGameWindowEvent() const { return GameWindowEvent; }

    /**
     * @brief Returns the title of the game window.
     * @return The title of the game window.
     */
    const std::string& GetGameWindowTitle() const { return GameWindowTitle; }

    /**
     * @brief Returns the size of the game window.
     * @return The size of the game window.
     */
    const sf::Vector2u& GetGameWindowSize() const { return GameWindowSize; }

    /**
     * @brief Returns a reference to the menu font.
     * @return A reference to the menu font.
     */
    sf::Font& GetMenuFont() { return MenuFont; }

    /**
     * @brief Returns a reference to the menu HUD object.
     * @return A reference to the menu HUD object.
     */
    LMenu_Hud& GetMenu_Hud() const { return *MenuHud; }

    /**
     * @brief Returns a reference to the main menu screen object.
     * @return A reference to the main menu screen object.
     */
    LMainMenu_Screen& GetMain_Menu_Screen() const { return *MainMenuScreen; }

    /**
     * @brief Returns the current game level state.
     * @return The current game level state.
     */
    GameLevelState GetCurrent_GameLeveState() const { return CurrentGameLevelState; }

    /**
     * @brief Sets the current game level state.
     * @param state The new game level state.
     */
    void SetCurrentGameLevelState(GameLevelState state);

    /**
     * @brief Updates the game loop.
     */
    void UpdateGame();

    /**
     * @brief Renders the game.
     */
    void RenderGame() const;

    /**
     * @brief Registers a function to be called during the game update loop.
     * @param updateFunction The function to be called during the game update loop.
     */
    void RegisterUpdateFunction(const std::function<void()>& updateFunction);

    /**
     * @brief Registers a function to be called during the game rendering process.
     * @param renderFunction The function to be called during the game rendering process.
     */
    void RegisterRenderFunction(const std::function<void()>& renderFunction);

 

private:

    /**
     * @brief Updates the game logic.
     */
    static void UpdateGameLogic();

    /**
     * @brief Renders the menu HUD.
     */
    void RenderMenuHUD() const;

    /**
     * @brief Recalculates the mouse move event based on the current game level state.
     */
    void RecalculateMouseMove() const;

    /**
     * @brief Recalculates the mouse pressed event based on the current game level state.
     */
    void RecalculateMousePressed() const;

    /**
     * @brief Updates the game pool events.
     */
    void UpdateGamePoolEvents();

    sf::RenderWindow* GameWindow = nullptr;  ///< The game window.
    sf::VideoMode GameVideoMode;             ///< The video mode of the game window.
    sf::Event GameWindowEvent;               ///< The event associated with the game window.
    std::string GameWindowTitle;             ///< The title of the game window.
    sf::Vector2u GameWindowSize;             ///< The size of the game window.
    sf::Font MenuFont;                       ///< The font used for the menu.
    LMenu_Hud* MenuHud;      ///< The menu HUD object.
    LMainMenu_Screen* MainMenuScreen; ///< The main menu screen object.
    GameLevelState CurrentGameLevelState = GameLevelState::Menu_Level; ///< The current game level state.

    std::vector<std::function<void()>> UpdateFunctions; ///< A vector of functions to be called during the game update loop.
    std::vector<std::function<void()>> RenderFunctions; ///< A vector of functions to be called during the game rendering process.

    static GEngine* Instance; ///< The singleton instance of the game engine.
};