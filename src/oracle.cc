#include "oracle.h"

namespace pecsn
{

Define_Module(Oracle);

Oracle::Oracle() : cSimpleModule()
 {
    registeredUsers = 0;
    infectedUsers = 0;
    receivedMessages = 0;
    sentMessages = 0;
    slotMessage =  nullptr;
 }

void Oracle::initialize()
{
    timeout = par("timeout").intValue();
    slotDuration = par("slotDuration").doubleValue();

    activityTime = registerSignal("activityTimeSig");
    coveredUsers = registerSignal("coveredUsersSig");
    rcvMsgsPerSlot = registerSignal("rcvMsgsPerSlotSig");
    sntMsgsPerSlot = registerSignal("sntMsgsPerSlotSig");

    slotMessage = new cMessage();
    slotMessage->setSchedulingPriority(1000);
    scheduleAt(simTime(), slotMessage); // slotting
}

void Oracle::handleMessage(cMessage *msg)
{
    if (!msg->isSelfMessage()) {
	   delete msg;
           return;
    }

    if (infectedUsers > 0)
	    emit(coveredUsers, infectedUsers);
    emit(rcvMsgsPerSlot, receivedMessages);
    emit(sntMsgsPerSlot, sentMessages);
    if (receivedMessages > 0 || sentMessages > 0) {
	    emit(activityTime, simTime().dbl());
	    timeout = par("timeout").intValue(); //reset the timer
    }
    if(timeout == 0) {
	EV << "[ORACLE] NO ACTIVITY: Reached timeout. (SimTime: " << simTime().dbl() << ")" << endl;
        endSimulation();
    }
    timeout--;
    receivedMessages = 0;
    sentMessages = 0;
    infectedUsers = 0;
    scheduleAt(simTime() + slotDuration, slotMessage);
}

void Oracle::registerUser()
{
    registeredUsers++;
    EV << "[ORACLE] Registered a new user. (current: " << registeredUsers << ")" << endl;
}

void Oracle::registerMsgRcv()
{
    receivedMessages++;
    EV << "[ORACLE] User signals a new message received. (total in current slot: " << receivedMessages << ")" << endl;
}

void Oracle::registerMsgSnt()
{
    sentMessages++;
    EV << "[ORACLE] User signals a new message sent. (total in current slot: " << sentMessages << ")" << endl;
}

void Oracle::registerInfection()
{
    infectedUsers++;
    EV << "[ORACLE] New user infected. (current: " << infectedUsers << "/" << registeredUsers << ")" << endl;
}

Oracle::~Oracle()
{
    cancelAndDelete(slotMessage);
}

}
