#include "UI.hpp"
#include "UIImage.hpp"
#include "World.hpp"
#include <iostream>
int main(){
    UI ui;
    ui.addComponent(new UIImage("kotik.bmp",0,0));

    ui.runEventLoop();
    return 0;
} 
