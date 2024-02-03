#include <QDebug>

#include "led_module.h"

LED_Module::LED_Module( // 6 args constructor
    QString &name,
    QString &code,
    QString &manufacturer,
    unsigned int If[3],
    double LF_I[3],
    double V_I[3]) : name{name}, code{code}, manufacturer{manufacturer},
                     If{If[0], If[1], If[2]},
                     LF_I{LF_I[0], LF_I[1], LF_I[2]},
                     V_I{V_I[0], V_I[1], V_I[2]}
{
    qDebug() << "LED Module " << this->name << " initialised.";
    qDebug() << "If: \t" << If[0] << ", " << If[1] << ", " << If[2] << " mA";
    qDebug() << "LF_I: \t" << LF_I[0] << ", " << LF_I[1] << ", " << LF_I[2];
    qDebug() << "V_I: \t" << V_I[0] << ", " << V_I[1] << ", " << V_I[2];
}

// LED_Module::LED_Module(const LED_Module &source) // Copy Constructor
// {
//     this->name = source.name;
//     this->code = source.code;
//     this->manufacturer = source.manufacturer;
//     this->If[0] = source.If[0];
//     this->If[1] = source.If[1];
//     this->If[2] = source.If[2];
//     this->LF_I[0] = source.LF_I[0];
//     this->LF_I[1] = source.LF_I[1];
//     this->LF_I[2] = source.LF_I[2];
//     this->V_I[0] = source.V_I[0];
//     this->V_I[1] = source.V_I[1];
//     this->V_I[2] = source.V_I[2];
// }

// LED_Module::LED_Module(LED_Module &&source) // Move Constructor
// {
//     this->name = std::move(source.name);
//     this->code = std::move(source.code);
//     this->manufacturer = std::move(source.manufacturer);
//     this->If[0] = std::move(source.If[0]);
//     this->If[1] = std::move(source.If[1]);
//     this->If[2] = std::move(source.If[2]);
//     this->LF_I[0] = std::move(source.LF_I[0]);
//     this->LF_I[1] = std::move(source.LF_I[1]);
//     this->LF_I[2] = std::move(source.LF_I[2]);
//     this->V_I[0] = std::move(source.V_I[0]);
//     this->V_I[1] = std::move(source.V_I[1]);
//     this->V_I[2] = std::move(source.V_I[2]);
// }

// Getters
QString LED_Module::get_name() const
{
    return this->name;
}
QString LED_Module::get_code() const { return this->code; }
QString LED_Module::get_manufacturer() const { return this->manufacturer; }

unsigned LED_Module::get_If_min() const { return this->If[0]; }
unsigned LED_Module::get_If_rated() const { return this->If[1]; }
unsigned LED_Module::get_If_max() const { return this->If[2]; }

double LED_Module::get_V_max() const
{
    return this->calc_voltage(this->get_If_max());
}
double LED_Module::get_V_min() const
{
    return this->calc_voltage(this->get_If_min());
}

QString LED_Module::get_current_limits() const
{
    QString output;
    output = QString::number(this->get_If_min());
    output += " / ";
    output += QString::number(this->get_If_max());
    return output;
}

QString LED_Module::get_voltage_limits() const
{
    QString output;
    output = QString::number(this->get_V_min(), 'f', 1);
    output += " / ";
    output += QString::number(this->get_V_max(), 'f', 1);
    return output;
}

double LED_Module::calc_flux(unsigned const &current) const
{
    double _1 = this->LF_I[0] * current * current;
    double _2 = this->LF_I[1] * current;
    double _3 = this->LF_I[2];

    return _1 + _2 + _3;
}
double LED_Module::calc_voltage(unsigned const &current) const
{
    double _1 = this->V_I[0] * current * current;
    double _2 = this->V_I[1] * current;
    double _3 = this->V_I[2];

    return _1 + _2 + _3;
}
double LED_Module::calc_power(unsigned const &current) const
{
    return this->calc_voltage(current) * current / 1000;
}
double LED_Module::calc_efficiency(unsigned const &current) const
{
    double flux = this->calc_flux(current);
    double power = this->calc_power(current);

    if (not power)
        return 0;

    return flux / power;
}
