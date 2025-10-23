#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout");
    ImGui::SFML::Init(window);
    
    GameManager gameManager(&window);
    gameManager.initialize();

    sf::Clock clock;
    float deltaTime = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }



        deltaTime = clock.restart().asSeconds();
        ImGui::SFML::Update(window, sf::seconds(deltaTime));
        gameManager.update(deltaTime);

        ImGui::ShowDemoWindow();

        window.clear();
        gameManager.render();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
