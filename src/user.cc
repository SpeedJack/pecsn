#include "user.h"

namespace pecsn
{
Define_Module(User);

User::User() : cSimpleModule()
{
	savedMessage = nullptr;
	receivedMessage = nullptr;
	slotMessage = nullptr;

	color = "#808080";
	showRadius = false;

	copiesCount = 0;
	relayed = false;
	collision = false;
	windowOpen = true;
}

void User::initialize()
{
	posX = par("posX").doubleValue();
	posY = par("posY").doubleValue();
	EV << "My position is: " << posX << ", " << posY << "." << endl;

	slotMessage = new cMessage();

	collisionCount = registerSignal("collisionCount");

	slotDuration = par("slotDuration").doubleValue();
	hearWindow = par("hearWindow").intValue();
	broadcastRadius = par("broadcastRadius").doubleValue();

	sendOnStart = par("sendOnStart").boolValue();
	int indexStartingNode = getParentModule()->par("indexStartingNode").intValue();
	if (indexStartingNode == getIndex())
		sendOnStart = true;
	if (sendOnStart) {
		EV << "sendOnStart=true." << endl;
		if (hasGUI())
			color = "blue";
	}

	scheduleAt(simTime(), slotMessage); // start slotting now
}

void User::handleMessage(cMessage *msg)
{
	if (hasGUI())
		showRadius = false;
	if (relayed) { // node stopped! do nothing
		if (!msg->isSelfMessage())
			delete msg;
		return;
	}

	if (msg->isSelfMessage()) // slotting
		handleSlotMessage(msg);
	else // real user message
		handleUserMessage(msg);
}

// handle slotting timer
void User::handleSlotMessage(cMessage* msg)
{
	if (sendOnStart) { // I'm the node that sends the first message
		savedMessage = new cMessage();
		relayMessage();
		scheduleAt(simTime() + slotDuration, slotMessage);
		return;
	}

	if (collision) {
		if (hasGUI()) {
			bubble("COLLISION!");
			color = "red";
		}
		emit(collisionCount, 1);
		EV << "Collision!" << endl;
	} else if (receivedMessage) {
		EV << "Correctly heard a message." << endl;
		if (!savedMessage)
			savedMessage = receivedMessage->dup();
	}

	if (savedMessage) {
		if (hasGUI())
			color = "blue";
		if (remainingWaitSlots == 0) {
			relayDelay = 0 - par("relayDelay").intValue();
			windowOpen = false;
		}
		if (remainingWaitSlots == relayDelay)
			relayMessage();
		remainingWaitSlots--; // when it reaches 0, the time window T is elapsed
	}

	// new slot
	collision = false;
	if (receivedMessage)
		delete receivedMessage;
	receivedMessage = nullptr;
	scheduleAt(simTime() + slotDuration, slotMessage);
}

// handle a user message
void User::handleUserMessage(cMessage* msg)
{
	if (!windowOpen) {
		delete msg;
		return;
	}

	if (receivedMessage) { // message already received in current slot
		collision = true;
		delete msg;
		return;
	}

	if (hasGUI())
		color = "#808080";
	receivedMessage = msg;
	copiesCount++; // count the number of message copies received in time window T
	EV << "copies count: " << copiesCount << endl;
	if (!savedMessage) // it's a new message
		remainingWaitSlots = hearWindow;
}

// broadcast message to all neighbors in range R
void User::relayMessage()
{
	relayed = true;
	if (hasGUI())
		color = "green";
	int maxCopies = par("maxCopies").intValue();
	if (copiesCount > maxCopies) {
		EV << "Too copies! Not relaying..." << endl;
		delete savedMessage;
		savedMessage = nullptr;
		return;
	}

	if (hasGUI()) {
		showRadius = true;
		bubble("SENDING MESSAGE!");
	}
	EV << "Relaying message..." << endl;
	cModule* parent = getParentModule();
	int userCount = parent->par("userCount").intValue();
	int neighborsCount = 0;
	for (int i = 0; i < userCount; i++) {
		cModule* tmp = parent->getSubmodule("user", i);
		if (!tmp)
			continue;
		User* user = check_and_cast<User*>(tmp);
		if (user == this)
			continue;

		// compute distance
		double userX = user->par("posX").doubleValue();
		double userY = user->par("posY").doubleValue();
		double Xdiff = posX - userX;
		double Ydiff = posY - userY;
		if (Xdiff * Xdiff + Ydiff * Ydiff <= (broadcastRadius * broadcastRadius)) {
			EV << "Relaying to " << user->getFullName() << "." << endl;
			neighborsCount++;
			// slotDuration/2 ensures that the message arrives in this slot
			sendDirect(savedMessage->dup(), slotDuration / 2, 0, user, user->gateBaseId("in"));
		}
	}
	EV << "Message relayed to " << neighborsCount << " users." << endl;
	delete savedMessage;
	savedMessage = nullptr;
}

void User::refreshDisplay() const
{
	cDisplayString& ds = getDisplayString();
	ds.setTagArg("b", 3, color);
	if (showRadius)
		ds.setTagArg("r", 0, broadcastRadius);
	else
		ds.removeTag("r");
}

void User::finish()
{
	// TODO: collect statistics
}

User::~User()
{
	if (receivedMessage)
		delete receivedMessage;
	if (savedMessage)
		delete savedMessage;
	cancelAndDelete(slotMessage);
}
}
