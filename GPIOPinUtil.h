
/**********************************************************
 * GPIOPinUtil.h                                          *
 *                                                        *
 * Author: Manuel Schoch <info@manuel-schoch.net>         *
 *                                                        *
 **********************************************************/

#ifndef GPIOPINUTIL_H
#define GPIOPINUTIL_H

class GPIOPin {
public:
    virtual ~GPIOPin() = default;
    virtual bool isOn() = 0;
    virtual void on(bool) = 0;
protected:
    GPIOPin(int pin);
    int pin_;
};

class NoPin : public GPIOPin {
public:
    NoPin();
    bool isOn() override;
    void on(bool on) override;
};

class ActiveHighPin : public GPIOPin {
public:
    ActiveHighPin(int pin);
    bool isOn() override;
    void on(bool on) override;
};

class ActiveLowPin : public GPIOPin {
public:
    ActiveLowPin(int pin);
    bool isOn() override;
    void on(bool on) override;
};

#endif // GPIOPINUTIL_H
