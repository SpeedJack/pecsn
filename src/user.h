#ifndef __PECSN_USER_H_
#define __PECSN_USER_H_

#include <omnetpp.h>

using namespace omnetpp;

namespace pecsn
{
class User: public cSimpleModule
{
private:
	cMessage* savedMessage;
	cMessage* receivedMessage;
	cMessage* slotMessage;

	int posX;
	int posY;

	int remainingWaitSlots;
	int copiesCount;
	bool relayed;
	bool collision;
	bool windowOpen;

	bool sendOnStart;
	int slotDuration;
	int hearWindow;
	int relayDelay;
	int maxRelayDelay;
	int broadcastRadius;

	void relayMessage();
	void handleSlotMessage(cMessage* msg);
	void handleUserMessage(cMessage* msg);
protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
	virtual void finish();
public:
	User();
	~User();
};
}

#endif
