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
	simsignal_t msgsPerSlot;

	unsigned long registeredUsers;
	unsigned long infectedUsers;
	unsigned long sentMessages;

	int timeout;
	double slotDuration;
protected:
	virtual void initialize() override;
	virtual void handleMessage(cMessage *msg) override;
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
