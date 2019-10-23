#include <Application.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <PrefabDispenser.hpp>
#include <iostream>
#include <GameObject.hpp>

int main()
{
    PrefabDispenser pd;
    pd.addPrefab("yamaha", []() {
        return new SceneObject();
    });
    auto obj1 = pd.getPrefab<SceneObject>("yamaha");
    std::cout << obj1->getCategory();

    pd.addPrefab("owo", []() {
        return new GameObject(nullptr, nullptr, nullptr, Category::GameObject);
    });
    auto obj2 = pd.getPrefab<GameObject>("owo");
    std::cout << obj2->getCategory();

    Application app;
    app.run();
}
