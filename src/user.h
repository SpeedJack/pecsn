#ifndef __PECSN_USER_H_
#define __PECSN_USER_H_

#include <omnetpp.h>
#include "oracle.h"

using namespace omnetpp;

namespace pecsn
{

class User: public cSimpleModule
{
private:
	Oracle *oracle;

	cMessage *savedMessage;
	cMessage *receivedMessage;
	cMessage *slotMessage;

	simsignal_t collisions;
	simsignal_t totalCollisions;
	simsignal_t copies;
	simsignal_t reachedUsers;

	const char *color;
	bool showRadius;

	double posX;
	double posY;

	int remainingWaitSlots;
	unsigned long copiesCount;
	unsigned long collisionsCount;
	unsigned long slotCollisionsCount;
	bool windowOpen;
	bool collision;
	bool relayed;

	bool sendOnStart;
	double slotDuration;
	int hearWindow;
	int relayDelay;
	double broadcastRadius;

	void relayMessage();
	void handleSlotMessage(cMessage *msg);
	void handleUserMessage(cMessage *msg);
protected:
	virtual void initialize() override;
	virtual void handleMessage(cMessage *msg) override;
	virtual void finish() override;
	virtual void refreshDisplay() const override;
public:
	User();
	~User();
};

}

#endif
