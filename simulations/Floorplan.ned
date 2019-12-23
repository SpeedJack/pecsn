package pecsn.simulations;

import pecsn.User;

network Floorplan
{
    parameters:
        int userCount = default(10);
        int indexStartingNode = default(intuniform(0, userCount-1));
        int sizeX = default(50);
        int sizeY = default(50);
        @display("bgb=$sizeX,$sizeY");
    submodules:
       user[userCount]: User {
           posX = default(intuniform(0, sizeX));
           posY = default(intuniform(0, sizeY));
       };
}
