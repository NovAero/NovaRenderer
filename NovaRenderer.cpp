
#include "Application.h"
#include "Utilities.h"
#include <iostream>

int main() {

    Application* app = new Application();

    if (app->Initialise()) {
        while (app->Update()) {
            app->Draw();
        }
        app->Exit(); 
    }
    
    delete app;
    
    return 0;
}