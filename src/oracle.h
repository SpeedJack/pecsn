#ifndef __PECSN_ORACLE_H_
#define __PECSN_ORACLE_H_

#include <omnetpp.h>
#include "user.h"

using namespace omnetpp;

namespace pecsn {

class Oracle : public cSimpleModule
{
  private:
    int total; //number of users
    int timer;
    int count; //infected users
    cMessage* slotMessage;
    double slotDuration;
    simsignal_t quantileTime;
    double quantile;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  public:
    void registerUser();
    void registerActivity();
    void infectedUser();
    Oracle();
    ~Oracle();
};

}

#endif
