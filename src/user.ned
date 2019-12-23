package pecsn;

simple User
{
	parameters:
		int posX = default(0);
		int posY = default(0);
		int broadcastRadius = default(40);
		int slotDuration = default(2);
		int hearWindow = default(10);
		int maxRelayDelay = default(3);
		int maxCopies = default(3);
		bool sendOnStart = default(false);
	@display("p=$posX,$posY;b=5,5,rect,#808080");
	gates:
	    input in @directIn;
}
