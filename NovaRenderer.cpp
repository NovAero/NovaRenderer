
#include "Application.h"

int main() {

    Application* app = new Application();

    if (app->Initialise() == true) {
        while (app->Run() == true) {
            app->Draw();
        }
        app->Exit();
    }
    
    delete app;
    
    return 0;
}