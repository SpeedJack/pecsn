package pecsn;

simple Oracle
{
	parameters:
		@display("i=block/cogwheel;is=vs");

		double slotDuration @unit(s) = default(1s);
		int timeout = default(9); // usually, max(user.hearWindow + user.relayDelay) + 1

		@signal[activityTimeSig](type="double");
		@signal[coveredUsersSig](type="unsigned long");
		@signal[msgsPerSlotSig](type="unsigned long");
}
