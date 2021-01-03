package pecsn;

simple Oracle
{
    parameters:   	
		double slotDuration @unit(s) = default(1s);
		int maxWaitTime = default(8); // sum of hearWindow + relayDelay
		double quantile = default(0.9);
	    @signal[quantileTime](type="double");
	    @display("i=block/cogwheel;is=vs");
}
