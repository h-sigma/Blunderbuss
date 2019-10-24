//
// Created by harshdeep on 23/10/19.
//

#ifndef BLUNDERBUSS_TESTSCENE_HPP
#define BLUNDERBUSS_TESTSCENE_HPP

#include <Scene.hpp>
#include <GameObject.hpp>
#include <Purlox.hpp>

class TestScene : public Scene<TestScene>
{
public:
    TestScene() = delete;
    static void setup(PrefabDispenser& dispenser)
    {
        dispenser.addPrefab("root", []{
            return new SceneObject();
        });

        dispenser.addPrefab("Purlox", []{
            return new GameObject(new PurloxInput(), new PurloxPhysics, new PurloxGraphics(), Category::Player);
        });
    }
    static Ptr get(const PrefabDispenser& dispenser)
    {
        auto root = dispenser.getPrefab<SceneObject>("root");
        auto purlox = dispenser.getPrefab<GameObject>("Purlox");
        purlox->setPosition(50,50);
        purlox->setScale(0.5f, 0.5f);
        root->attachChild(std::move(purlox));
        return root;
    }
};

#endif //BLUNDERBUSS_TESTSCENE_HPP
