#include "Core/GEngine.h"

int main()
{
    // Create a new GEngine instance
    GEngine& GameEngine = GEngine::Build(1920, 1080, "Neo Saves The Ocean");
    GameEngine.InitWindow();
    
    while (GameEngine.IsGameWindowOpen())
    {
        // Update the game loop
        GameEngine.UpdateGame();

        // Render the game to the screen
        GameEngine.RenderGame();
    }

    return 0;
}