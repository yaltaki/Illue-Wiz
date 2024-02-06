#include "led_driver.h"

LED_Driver::LED_Driver( // 6 args constructor
    QString &name,
    QString &code,
    QString &manufacturer,
    unsigned int Vf[2],
    unsigned int If[3],
    unsigned int P_out[2],
    bool bDualChannel,
    double C_N[3],
    double C_PF[3])
    : name{name}, code{code}, manufacturer{manufacturer},
      Vf{Vf[0], Vf[1]},
      If{If[0], If[1], If[2]},
      P_out{P_out[0], P_out[1]},
      bDualChannel{bDualChannel},
      C_N{C_N[0], C_N[1], C_N[2]},
      C_PF{C_PF[0], C_PF[1], C_PF[2]}
{
}

// Getters
QString LED_Driver::get_name() const { return this->name; }
QString LED_Driver::get_code() const { return this->code; }
QString LED_Driver::get_manufacturer() const { return this->manufacturer; }
unsigned int LED_Driver::get_If_min() const { return this->If[0]; }
unsigned int LED_Driver::get_If_max() const { return this->If[2]; }
unsigned int LED_Driver::get_V_max() const { return this->Vf[1]; }
unsigned int LED_Driver::get_V_min() const { return this->Vf[0]; }
unsigned int LED_Driver::get_P_1() const { return this->P_out[0]; }
unsigned int LED_Driver::get_P_2() const { return this->P_out[1]; }

QString LED_Driver::get_current_limits() const
{
    return QString("%1 / %2")
        .arg(this->get_If_min())
        .arg(this->get_If_max());
}
QString LED_Driver::get_voltage_limits() const
{
    return QString("%1 / %2")
        .arg(QString::number(this->get_V_min(), 'f', 1))
        .arg(QString::number(this->get_V_max(), 'f', 1));
}
QString LED_Driver::get_power_limits() const
{
    if (this->bDualChannel)
        return QString("%1 / %2")
            .arg(QString::number(this->get_P_1(), 'f', 1))
            .arg(QString::number(this->get_P_2(), 'f', 1));

    return QString::number(this->get_P_1(), 'f', 1);
}

double LED_Driver::calc_powerfactor(double const &power) const
{
    return ((power * power * C_PF[0]) + (power * C_PF[1]) + (C_PF[2]));
}
double LED_Driver::calc_efficiency(double const &power) const
{
    return ((power * power * C_N[0]) + (power * C_N[1]) + (C_N[2]));
}
