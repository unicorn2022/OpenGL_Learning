#pragma once
#include <vector>
#include "ShaderManager.h"
#include "Engine/Object/Square.h"


class ObjectManager {
public:
    ObjectManager(){
        objects.push_back(new Square());
    }
    ~ObjectManager() {
        for (Object* object : objects) {
            delete object;
        }
    }

public:
    void DrawAllByBasicShader(ShaderManager* shader_manager){
        for (Object* object : objects) {
            object->Draw(shader_manager->GetBasicShader());
        }
    }

private:
    std::vector<Object*> objects;
};