#pragma once
#include "../Glity/Glity-All.h"

class TextureParaSetter : public virtual Component, public virtual IUpdate
{
public:
    explicit TextureParaSetter(GameObject& obj);

    std::string Name() override;
    void Update(GameObject& obj) override;
};

