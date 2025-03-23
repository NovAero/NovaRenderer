#pragma once
#include "Application.h"
#include "Utilities.h"
#include <iostream>

#include "src/GLFWCallbacks.h"

int main() {
    //TODO
    //Add object class that handles the texture loading for its mesh
    //Add lighting

    unsigned int width = 1280;
    unsigned int height = 720;

    Application* app = new Application();

    if (app->Initialise(width, height)) {

        glfwSetWindowSizeCallback(app->GetWindow(), WindowResizeCallback);

        while (app->Update()) {
            app->Draw();
        }
        app->Exit(); 
    }

    delete app;
    
    return 0;
}