//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

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

    scheduleAt(simTime(), slotMessage); // start slotting now
}

void Oracle::handleMessage(cMessage *msg)
{
    if (!msg->isSelfMessage())
           return;

    if(timer == 0)
        endSimulation(); //if no events arrived before the timer the simulation ends
    timer--; //no events arrived
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
