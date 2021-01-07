package pecsn.simulations;

import pecsn.User;
import pecsn.Oracle;

network Floorplan
{
	parameters:
		@display("bgb=$sizeX,$sizeY");

		int userCount = default(100);
		double sizeX @unit(m) = default(150m);
		double sizeY @unit(m) = default(150m);
		int indexStartingNode = default(intuniform(0, userCount-1));

		@statistic[collisions](source=collisionsSig; unit=collisions; record=histogram,sum);
		@statistic[totalCollisions](source=totalCollisionsSig; unit=collisions; record=vector,histogram,sum);
		@statistic[copies](source=copiesSig; unit=messages; record=histogram);
		@statistic[reachedUsers](source=reachedUsersSig; unit=users; record=histogram,sum);
		@statistic[activityTime](source=activityTimeSig; unit=seconds; record=last);
		@statistic[coveredUsers](source=coveredUsersSig; unit=users; record=vector,sum);
		@statistic[msgsPerSlot](source=msgsPerSlotSig; unit=messages; record=vector,histogram,sum);

	submodules:
		user[userCount]: User {
			posX = default(uniform(0m, sizeX));
			posY = default(uniform(0m, sizeY));
		};
		oracle: Oracle;
}
