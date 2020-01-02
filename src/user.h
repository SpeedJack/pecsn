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

	simsignal_t collisionCount;

	const char* color;
	bool showRadius;

	double posX;
	double posY;

	int remainingWaitSlots;
	int copiesCount;
	bool windowOpen;
	bool collision;
	bool relayed;

	bool sendOnStart;
	double slotDuration;
	int hearWindow;
	int relayDelay;
	double broadcastRadius;

	void relayMessage();
	void handleSlotMessage(cMessage* msg);
	void handleUserMessage(cMessage* msg);
protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
	virtual void refreshDisplay() const;
	virtual void finish();
public:
	User();
	~User();
};
}

#endif
