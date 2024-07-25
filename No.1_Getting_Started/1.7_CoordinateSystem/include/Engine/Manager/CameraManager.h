#pragma once
#include "Engine/Basic/Camera.h"
    
class CameraManager {
public:
    CameraManager(float SCR_WIDTH, float SCR_HEIGHT) {
        main_camera = new CameraPerspective(SCR_WIDTH / SCR_HEIGHT);
    }
    ~CameraManager(){
        delete main_camera;
    }
    
public:
    Camera* main_camera;
};