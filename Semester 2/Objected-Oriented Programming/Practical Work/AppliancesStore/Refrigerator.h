#include "Appliance.h"

class Refrigerator : public Appliance {
private:
    string usage;
    bool freezer;
public:
    Refrigerator(string id, string usage, bool freezer);
    double consumedElectricity() override;
    string toString() override;
};
