#ifndef DONUT_H
#define DONUT_H
#include <map>
#include <string>
#include <algorithm>
#include <stdexcept>

class Donut
{
public:
    enum icingType
    {
        CHOCOLATEICING,
        CARAMELICING,
        MAPLE,
        VANILLA,
        GLAZE,
        SPECIALICE,
        NOICE
    };
    enum toppingType
    {
        RAINBOWSPR,
        CHOCOLATESPR,
        PEANUTS,
        COCONUT,
        OREO,
        BACON,
        GRAHAM,
        FRUITYPEBBLES,
        REESESPIECES,
        MMS,
        CANDYBAR,
        CHOCOLATECHIPS,
        SEASALT,
        CINSUGAR,
        POWDSUGAR,
        NOTOP
    };
    enum drizzleType
    {
        CARAMELDRIZZLE,
        CHOCOLATEDRIZZLE,
        PEANUTBUTTER,
        RASPBERRY,
        SPECIALDRIZZLE,
        NODRIZZLE
    };
    static std::map<toppingType, std::string> topToStr;
    static std::map<icingType, std::string> iceToStr;
    static std::map<drizzleType, std::string> drizzleToStr;
    static std::map<std::string, toppingType> strToTop;
    static std::map<std::string, icingType> strToIce;
    static std::map<std::string, drizzleType> strToDrizzle;
    // Donut(icingType = NOICE, toppingType = NOTOP, drizzleType = NODRIZZLE);
    Donut(std::string, std::string, std::string);
    icingType getIcing() const;
    toppingType getTopping() const;
    drizzleType getDrizzle() const;
    std::string toString() const;
    void setIcing(std::string);
    void setTopping(std::string);
    void setDrizzle(std::string);
    friend std::ostream &operator<<(std::ostream &, const Donut &);
    bool operator>(const Donut &);
    bool operator<(const Donut &);
    bool operator>=(const Donut &);
    bool operator<=(const Donut &);
    bool operator==(const Donut &);
    bool operator!=(const Donut &);

private:
    toppingType topping;
    icingType icing;
    drizzleType drizzle;
};

#endif