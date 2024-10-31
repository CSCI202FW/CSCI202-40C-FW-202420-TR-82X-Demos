#include "donut.h"

std::map<Donut::toppingType, std::string> Donut::topToStr = {
    {RAINBOWSPR, "Rainbow Sprinkles"},
    {CHOCOLATESPR, "Chocolate Sprinkles"},
    {PEANUTS, "Peanuts"},
    {COCONUT, "Coconut"},
    {OREO, "Oreo"},
    {BACON, "Bacon"},
    {GRAHAM, "Graham"},
    {FRUITYPEBBLES, "Fruity Pebbles"},
    {REESESPIECES, "Reeses Pieces"},
    {MMS, "M&Ms"},
    {CANDYBAR, "Candy Bar"},
    {CHOCOLATECHIPS, "Chocolate Chips"},
    {SEASALT, "Sea Salt"},
    {CINSUGAR, "Cinnamon Sugar"},
    {POWDSUGAR, "Powdered Sugar"},
    {NOTOP, "None"}};
std::map<Donut::icingType, std::string> Donut::iceToStr = {{CHOCOLATEICING, "Chocolate"},
                                                           {CARAMELICING, "Caramel"},
                                                           {MAPLE, "Maple"},
                                                           {VANILLA, "Vanilla"},
                                                           {GLAZE, "Glaze"},
                                                           {SPECIALICE, "Special"},
                                                           {NOICE, "None"}};
std::map<Donut::drizzleType, std::string> Donut::drizzleToStr = {{CARAMELDRIZZLE, "Caramel"},
                                                                 {CHOCOLATEDRIZZLE, "Chocolate"},
                                                                 {PEANUTBUTTER, "Peanut Butter"},
                                                                 {RASPBERRY, "Raspberry"},
                                                                 {SPECIALDRIZZLE, "Special"},
                                                                 {NODRIZZLE, "None"}};
std::map<std::string, Donut::toppingType> Donut::strToTop = {{"rainbow sprinkles", RAINBOWSPR}, {"chocolate sprinkles", CHOCOLATESPR}, {"peanuts", PEANUTS}, {"coconut", COCONUT}, {"oreo", OREO}, {"bacon", BACON}, {"graham cracker", GRAHAM}, {"fruity pebbles", FRUITYPEBBLES}, {"reeses pieces", REESESPIECES}, {"m&ms", MMS}, {"candy bar", CANDYBAR}, {"chocolate chips", CHOCOLATECHIPS}, {"sea salt", SEASALT}, {"cinnamon sugar", CINSUGAR}, {"powdered sugar", POWDSUGAR}, {"none", NOTOP}};
std::map<std::string, Donut::icingType> Donut::strToIce = {{"chocolate", CHOCOLATEICING},
                                                           {"caramel", CARAMELICING},
                                                           {"maple", MAPLE},
                                                           {"vanilla", VANILLA},
                                                           {"glaze", GLAZE},
                                                           {"special", SPECIALICE},
                                                           {"none", NOICE}};

std::map<std::string, Donut::drizzleType> Donut::strToDrizzle{{"caramel", CARAMELDRIZZLE},
                                                              {"chocolate", CHOCOLATEDRIZZLE},
                                                              {"peanut butter", PEANUTBUTTER},
                                                              {"raspberry", RASPBERRY},
                                                              {"special", SPECIALDRIZZLE},
                                                              {"none", NODRIZZLE}};
/* Donut::Donut(icingType i, toppingType topping, drizzleType d)
{
    icing = i;
    this->topping = topping;
    drizzle = d;
} */
Donut::Donut(std::string icing, std::string topping, std::string drizzle)
{

    setIcing(icing);
    setTopping(topping);
    setDrizzle(drizzle);
}

std::string Donut::toString() const
{
    std::string out;
    out = "Icing: " + iceToStr.at(icing) + " Topping: " + topToStr.at(topping) + " Drizzle: " + drizzleToStr.at(drizzle);
    return out;
}
void Donut::setIcing(std::string icing)
{
    std::string icingLower = icing;
    std::transform(icingLower.begin(), icingLower.end(), icingLower.begin(), ::tolower);
    if (strToIce.count(icingLower))
    {
        this->icing = strToIce.at(icingLower);
    }
    else
    {
        std::invalid_argument st(icing + " is not a valid icing type!");
        throw st;
    }
}

void Donut::setTopping(std::string topping)
{
    std::string toppingLower = topping;
    std::transform(toppingLower.begin(), toppingLower.end(), toppingLower.begin(), ::tolower);
    if (strToTop.count(toppingLower))
    {
        this->topping = strToTop.at(toppingLower);
    }
    else
    {
        std::invalid_argument st(topping + " is not a valid topping type!");
        throw st;
    }
}

void Donut::setDrizzle(std::string drizzle)
{
    std::string drizzleLower = drizzle;
    std::transform(drizzleLower.begin(), drizzleLower.end(), drizzleLower.begin(), ::tolower);
    if (strToDrizzle.count(drizzleLower))
    {
        this->drizzle = strToDrizzle.at(drizzleLower);
    }
    else
    {
        std::invalid_argument st(drizzle + " is not a valid drizzle type!");
        throw st;
    }
}
std::ostream &operator<<(std::ostream &out, const Donut &d)
{
    out << d.toString();
    return out;
}
Donut::icingType Donut::getIcing() const { return icing; }
Donut::toppingType Donut::getTopping() const { return topping; }
Donut::drizzleType Donut::getDrizzle() const { return drizzle; }

bool Donut::operator>(const Donut &right) const
{
    return false;
}
bool Donut::operator<(const Donut &right) const
{
    return false;
}
bool Donut::operator>=(const Donut &right) const
{
    return *this == right;
}
bool Donut::operator<=(const Donut &right) const
{
    return *this == right;
}
bool Donut::operator==(const Donut &right) const
{
    return this->topping == right.topping && this->drizzle == right.drizzle && this->icing == right.icing;
}
bool Donut::operator!=(const Donut &right) const
{
    return !(*this == right);
}