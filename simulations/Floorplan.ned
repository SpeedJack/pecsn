package pecsn.simulations;

network Floorplan
{
    parameters:
        int userCount = default(30);
        //int indexSendingNode = default(intuniform(0, userCount));
        int sizeX = default(200);
        int sizeY = default(200);
        user[0].sendOnStart = true;
        @display("bgb=$sizeX,$sizeY");
    submodules:
        user[userCount]: pecsn.User {
            posX = default(intuniform(0, sizeX));
            posY = default(intuniform(0, sizeY));
        };
}
