package pecsn;

simple Oracle
{
	parameters:
		@display("i=block/cogwheel;is=vs");

		double slotDuration @unit(s) = default(1s);
		int timeout = default(8); // usually, user.hearWindow + max(user.relayDelay)

		@signal[activityTimeSig](type="double");
		@signal[coveredUsersSig](type="unsigned long");
		@signal[msgsPerSlotSig](type="unsigned long");
}
