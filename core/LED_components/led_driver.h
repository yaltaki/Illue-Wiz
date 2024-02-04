#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <QString>

class LED_Driver
{
private:
    const QString &name;
    const QString &code;
    const QString &manufacturer;
    const unsigned int Vf[2];
    const unsigned int If[3];
    const unsigned int P_out[2];
    bool bDualChannel;
    const double C_N[3];
    const double C_PF[3];
public:
    LED_Driver(
        QString &name,
        QString &code,
        QString &manufacturer,
        unsigned int Vf[2],
        unsigned int If[3],
        unsigned int P_out[2],
        bool bDualChannel,
        double C_N[3],
        double C_PF[3]
    );
    LED_Driver(const LED_Driver &source);   // Copy
    LED_Driver(LED_Driver &&source);        // Move
    ~LED_Driver();                          // Destruct

    // ========================================================================
    // Getters
    QString get_name() const;
    QString get_code() const;
    QString get_manufacturer() const;
    unsigned int get_If_min() const;
    unsigned int get_If_max() const;
    unsigned int get_V_min() const;
    unsigned int get_V_max() const;
    unsigned int get_P_1() const;
    unsigned int get_P_2() const;

    // Display methods
    QString get_current_limits() const;
    QString get_voltage_limits() const;
    QString get_power_limits() const;

    // Class Functions
    double calc_efficiency(double const &power) const;
    double calc_powerfactor(double const &power) const;
};

#endif // LED_DRIVER_H
