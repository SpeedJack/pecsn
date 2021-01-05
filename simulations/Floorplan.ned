package pecsn.simulations;

import pecsn.User;
import pecsn.Oracle;

network Floorplan
{
	parameters:
		@display("bgb=$sizeX,$sizeY");

		int userCount = default(60);
		double sizeX @unit(m) = default(200m);
		double sizeY @unit(m) = default(200m);
		int indexStartingNode = default(intuniform(0, userCount-1));

		@statistic[collisions](source=collisionsSig; unit=collisions; record=stats,sum);
		@statistic[copies](source=copiesSig; unit=messages; record=stats);
		@statistic[reachedUsers](source=reachedUsersSig; unit=users; record=stats);
		@statistic[activityTime](source=activityTimeSig; unit=seconds; record=last);
		@statistic[coveredUsers](source=coveredUsersSig; unit=users; record=vector,sum);
		@statistic[rcvMsgsPerSlot](source=rcvMsgsPerSlotSig; unit=messages; record=vector,stats);
		@statistic[sntMsgsPerSlot](source=sntMsgsPerSlotSig; unit=messages; record=vector,stats,sum);

	submodules:
		user[userCount]: User {
			posX = default(uniform(0m, sizeX));
			posY = default(uniform(0m, sizeY));
		};
		oracle: Oracle;
}
