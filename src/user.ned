package pecsn;

simple User
{
	parameters:
		double posX @unit(m) = default(0m);
		double posY @unit(m) = default(0m);
		double broadcastRadius @unit(m) = default(40m);
		double slotDuration @unit(s) = default(1s);
		int hearWindow = default(5);
		volatile int relayDelay = default(intuniform(0, 3));
		int maxCopies = default(3);
		bool sendOnStart = default(false);
		@signal[collisions](type=long);
        @statistic[collisionCount](source = "collisions"; record = count;);
	@display("p=$posX,$posY;b=5,5,rect,#808080");
	gates:
	    input in @directIn;
}
