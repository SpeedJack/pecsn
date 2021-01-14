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

		@statistic[collisions](title="Number of collisions registered by the users"; source=collisionsSig; unit=collisions; record=histogram,sum);
		@statistic[totalCollisions](title="Total number of colliding messages registered by the users in each slot"; source=totalCollisionsSig; unit=collisions; record=vector,histogram,sum);
		@statistic[copies](title="Number of copies of a message successfully heard"; source=copiesSig; unit=messages; record=histogram);
		@statistic[reachedUsers](title="Number of reached users by a relayed message"; source=reachedUsersSig; unit=users; record=histogram,sum);
		@statistic[activityTime](title="Last time of activity of the network"; source=activityTimeSig; unit=seconds; record=last);
		@statistic[coveredUsers](title="Number of infected users at every time of the simulation"; source=coveredUsersSig; unit=users; record=vector,sum);
		@statistic[msgsPerSlot](title="Number of messages sent in every slot"; source=msgsPerSlotSig; unit=messages; record=vector,histogram,sum);

	submodules:
		user[userCount]: User {
			posX = default(uniform(0m, sizeX));
			posY = default(uniform(0m, sizeY));
		};
		oracle: Oracle;
}
