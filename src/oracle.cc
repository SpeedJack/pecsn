#include "oracle.h"

namespace pecsn {

Define_Module(Oracle);

Oracle::Oracle() : cSimpleModule()
 {
    total = 0;
    count = 0;
    slotMessage = new cMessage();
 }

void Oracle::initialize()
{
    timer = par("maxWaitTime").intValue();
    slotDuration = par("slotDuration").doubleValue();
    quantile = par("quantile").doubleValue();

    quantileTime = registerSignal("quantileTime");

    scheduleAt(simTime(), slotMessage); // slotting
}

void Oracle::handleMessage(cMessage *msg)
{
    if (!msg->isSelfMessage())
           return;

    if(timer == 0)
        endSimulation();
    timer--;
    scheduleAt(simTime() + slotDuration, slotMessage);
}

void Oracle::registerUser()
{
    total++;
}

void Oracle::registerActivity()
{
    timer = par("maxWaitTime").intValue(); //reset the timer
}

void Oracle::infectedUser()
{
    if(total == 0)
        return;
    count++;
    double div = (double)count/total;
    if(div >= quantile)
        emit(quantileTime, simTime().dbl());
}

Oracle::~Oracle()
{
    cancelAndDelete(slotMessage);
}

}
