#ifndef SIGNALLER_H
#define SIGNALLER_H

#include "../Int/int_signals.h"
#include "../Int/my_int.h"
class Int;

class Signals_default_handler {
  public:
  	virtual void signal(const Int& sender, const Int_signal int_signal) {};

    virtual void signal(const Int& sender, const Int_signal int_signal, const Int& other) {};
};

#endif