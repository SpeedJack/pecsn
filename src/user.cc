#include "user.h"

Define_Module(User);

void User::initialize()
{
	int posX = par("posX").intValue();
	int posY = par("posY").intValue();
	EV << "My position is: " << posX << ", " << posY << "." << endl;
	slot = new cMessage();
	if (sendOnStart)
		sendMessageOnStart = true;
	scheduleAt(simTime(), slot);
}

void User::handleMessage(cMessage *msg)
{
	if (msg->isSelfMessage()) {
		handleSlotMessage(msg);
	} else {
		handleUserMessage(msg);
	}
}

void User::handleSlotMessage(cMessage* msg)
{
	if (simTime() == 0) {
		bool sendOnStart = par("sendOnStart").boolValue();
		if (sendOnStart) {
			message = new cMessage();
			sendMessageToNeighbors();
			message = nullptr;
		}
	}
	int slotTime = par("slotTime");
	scheduleAt(simTime() + slotTime, slot);
}

void User::handleUserMessage(cMessage* msg)
{
}

void User::sendMessageToNeighbors()
{
	bubble("SENDING MESSAGE!");
	int radius = par("broadcastRadius").intValue();
	for (int i = 0; i < 30; i++) {
		cModule* tmp = getParentModule()->getSubmodule("user", i);
		if (!tmp)
			continue;
		User* user = check_and_cast<User*>(tmp);
		if (user == this)
			continue;
		int posX1 = par("posX").intValue();
		int posY1 = par("posY").intValue();
		int posX2 = user->par("posX").intValue();
		int posY2 = user->par("posY").intValue();
		double distance = sqrt(pow(posX1 - posX2, 2) + pow(posY1 - posY2, 2));
		if (distance <= radius) {
			sendDirect(message->dup(), user, user->gateBaseId("in"));
		}
	}
}
