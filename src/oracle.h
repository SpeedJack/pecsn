#ifndef __PECSN_ORACLE_H_
#define __PECSN_ORACLE_H_

#include <omnetpp.h>

using namespace omnetpp;

namespace pecsn
{

class Oracle : public cSimpleModule
{
private:
	cMessage *slotMessage;

	simsignal_t activityTime;
	simsignal_t coveredUsers;
	simsignal_t rcvMsgsPerSlot;
	simsignal_t sntMsgsPerSlot;

	unsigned long registeredUsers;
	unsigned long infectedUsers;
	unsigned long receivedMessages;
	unsigned long sentMessages;

	int timeout;
	double slotDuration;
protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
public:
	Oracle();
	~Oracle();
	void registerUser();
	void registerMsgRcv();
	void registerMsgSnt();
	void registerInfection();
};

}

#endif
