package pecsn.simulations;

import pecsn.User;
import pecsn.Oracle;

network Floorplan
{
	parameters:
		int userCount = default(60);
		int indexStartingNode = default(intuniform(0, userCount-1));
		double sizeX @unit(m) = default(200m);
		double sizeY @unit(m) = default(200m);
		@display("bgb=$sizeX,$sizeY");
		@statistic[collisionCount](source="collisions";record=count);
		@statistic[coveredUsers](source="infected";record=count);
		@statistic[totalBroadcastTime](source="time";record=max);
		@statistic[quantileBroadcastTime](source="quantileTime";record=min);
	submodules:
		user[userCount]: User {
			posX = default(uniform(0m, sizeX));
			posY = default(uniform(0m, sizeY));
		};
		oracle: Oracle;
}
