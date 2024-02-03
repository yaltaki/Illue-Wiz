#ifndef LED_MODULE_H
#define LED_MODULE_H

#include <QString>

class LED_Module
{
private:
    const QString &name;
    const QString &code;
    const QString &manufacturer;
    const unsigned If[3];
    const double LF_I[3];
    const double V_I[3];

public:
    // Constructors
    LED_Module( // 6 arg Constructor
        QString &name,
        QString &code,
        QString &manufacturer,
        unsigned int If[3],
        double LF_I[3],
        double V_I[3]);
    // LED_Module(const LED_Module &source); // Copy Constructor &module1 = module2
    // LED_Module(LED_Module &&source);      // Move Constructor LedModule module_1 = new LedModule()
    // ~LED_Module();                        // Destructor

    // ========================================================================
    // Getters
    QString get_name() const;
    QString get_code() const;
    QString get_manufacturer() const;
    unsigned get_If_min() const;
    unsigned get_If_rated() const;
    unsigned get_If_max() const;
    double get_V_min() const; // return calc_voltage(If[0])
    double get_V_max() const; // return calc_voltage(If[2])

    // Display methods
    QString get_current_limits() const;
    QString get_voltage_limits() const;

    // Methods in LedModule
    double calc_flux(unsigned const &current) const; // unit: Lumen (lm)
    double calc_voltage(unsigned const &current) const;
    double calc_power(unsigned const &current) const;
    double calc_efficiency(unsigned const &current) const; // unit: Lumen/Watt (lm/W)
};
#endif // LED_MODULE_H
