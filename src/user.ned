package pecsn;

simple User
{
	parameters:
		int posX = default(0);
		int posY = default(0);
		int broadcastRadius = default(40);
		int slotTime = default(10);
		int slotDelay = default(5);
		int trickleRelayCopies = default(3);
		bool sendOnStart = default(false);
	@display("p=$posX,$posY;r=$broadcastRadius");
	gates:
	    input in @directIn;
}
