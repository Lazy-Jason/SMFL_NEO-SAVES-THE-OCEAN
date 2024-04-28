// Generic_Modal_Menu.cpp
#include "Generic_Modal_Menu.h"

Generic_Modal_Menu::Generic_Modal_Menu(const std::string& Title, const std::string& Message, sf::Color BackgroudColor)
    : YesButton("Yes", {200, 50}, 20, sf::Color::Transparent, sf::Color::White, GetDefaultFont(), sf::Color::Red, sf::Color::White),  // Initialize Yes button
      NoButton("No", {200, 50}, 20, sf::Color::Transparent, sf::Color::White, GetDefaultFont(), sf::Color::Red, sf::Color::White)     // Initialize No button
{
    ModalShape.setSize(ModalSize);
    ModalShape.setFillColor(BackgroudColor);
    ModalBounds.setSize(BoundSize);
    ModalBounds.setFillColor(sf::Color(sf::Color::Black.r, sf::Color::Black.g, sf::Color::Black.b, sf::Uint8(215)));

    TitleTextBlock.setString(Title);
    MessageTextBlock.setString(Message);
    MessageTextBlock.setFont(GetDefaultFont());
    TitleTextBlock.setFont(GetDefaultFont());
    TitleTextBlock.setCharacterSize(FontSize);
    MessageTextBlock.setCharacterSize(FontSize);

    YesButton.OnReleasedEnvoy = [this] { if(OnYes_Button_Released) OnYes_Button_Released(); };
    NoButton.OnReleasedEnvoy = [this] { if(OnNo_Button_Released) OnNo_Button_Released(); };
}

void Generic_Modal_Menu::DrawToWindow(sf::RenderWindow& Render_Window)
{
    CalculateObjectPositions(Render_Window);
    Render_Window.draw(ModalBounds);
    Render_Window.draw(ModalShape);
    Render_Window.draw(TitleTextBlock);
    Render_Window.draw(MessageTextBlock);
    YesButton.DrawToWindow(Render_Window);
    NoButton.DrawToWindow(Render_Window);
}

bool Generic_Modal_Menu::IsMouseButtonOver(sf::RenderWindow& Render_Window) const
{
    return true;
}

void Generic_Modal_Menu::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    YesButton.OnMouseButtonMove(Render_Window);
    NoButton.OnMouseButtonMove(Render_Window);
}

void Generic_Modal_Menu::OnMouseButtonAction(sf::Mouse::Button MouseAction)
{
    YesButton.OnMouseButtonAction(MouseAction);
    NoButton.OnMouseButtonAction(MouseAction);
}

void Generic_Modal_Menu::CalculateObjectPositions(const sf::RenderWindow& Render_Window)
{
    // Position the modal bounds in the center of the screen
    ModalShape.setPosition(Render_Window.getView().getCenter() - ModalShape.getSize() / 2.f);
    ModalBounds.setPosition(Render_Window.getView().getCenter() - ModalBounds.getSize() / 2.f);

    // Position the title text block at the top-left of the modal bounds with a margin
    TitleTextBlock.setPosition(ModalShape.getPosition().x + TitleMargin, ModalShape.getPosition().y + TitleMargin);

    // Position the message text block in the center of the modal bounds
    const sf::FloatRect messageBounds = MessageTextBlock.getGlobalBounds();
    MessageTextBlock.setPosition(ModalShape.getPosition().x + (ModalShape.getSize().x - messageBounds.width) / 2.f,
                                 ModalShape.getPosition().y + (ModalShape.getSize().y - messageBounds.height) / 2.f);

    // Position the Yes and No buttons at the bottom center of the modal bounds with spacing
    const float buttonY = ModalShape.getPosition().y + ModalShape.getSize().y - YesButton.GetButtonLocalBounds().height - Button_YOffSet;
    const float buttonX = ModalShape.getPosition().x + (ModalShape.getSize().x - YesButton.GetButtonLocalBounds().width - NoButton.GetButtonLocalBounds().width - Button_SpaceBetween) / 2.f;
    YesButton.SetButtonPosition({buttonX, buttonY});
    NoButton.SetButtonPosition({buttonX + YesButton.GetButtonLocalBounds().width + Button_SpaceBetween, buttonY});
}
