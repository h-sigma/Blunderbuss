//
// Created by harshdeep on 19/10/19.
//

#ifndef BLUNDERBUSS_PURLOX_HPP
#define BLUNDERBUSS_PURLOX_HPP

#include <InputComponent.hpp>

class PurloxInput : public InputComponent
{
public:
    ~PurloxInput() override = default;
    void update(class GameObject&, sf::Time, class World&) override;
private:
    void handleMovement(class GameObject&, class World &) ;
private:
    //state variables

};

#endif //BLUNDERBUSS_PURLOX_HPP
