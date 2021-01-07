package pecsn;

simple User
{
	parameters:
		@display("p=$posX,$posY;b=5,5,rect,#808080");

		double posX @unit(m) = default(0m);
		double posY @unit(m) = default(0m);
		bool sendOnStart = default(false);
		double slotDuration @unit(s) = default(1s);
		double broadcastRadius @unit(m) = default(20m);
		int hearWindow = default(5);
		int maxCopies = default(3);
		volatile int relayDelay = default(intuniform(0, 3));

		@signal[collisionsSig](type="unsigned long");
		@signal[totalCollisionsSig](type="unsigned long");
		@signal[copiesSig](type="unsigned long");
		@signal[reachedUsersSig](type="unsigned long");

	gates:
		input in @directIn;
}
