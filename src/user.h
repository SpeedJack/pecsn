#ifndef __PECSN_USER_H_
#define __PECSN_USER_H_

#include <omnetpp.h>

using namespace omnetpp;

class User: public cSimpleModule
{
private:
	cMessage* message;
	cMessage* slot;

	int remainingWaitSlots;
	int copiesCount;

	void sendMessageToNeighbors();
	void handleSlotMessage(cMessage* msg);
	void handleUserMessage(cMessage* msg);
protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
};

#endif
