
#ifndef HW1_WET_CARMODEL_H
#define HW1_WET_CARMODEL_H

#include "DSW.h"

class CarModel {
private:
    UInt _model_id;
    int _rate;
    UInt _sales;
    UInt _type_id;

public:
    CarModel(UInt model_id, UInt type_id);
    CarModel(const CarModel&  other) = default;
    CarModel& operator=(const CarModel& other) = default;
    ~CarModel() = default;
    UInt getSales() const;
    UInt getModelID() const;
    UInt getTypeID() const;
    int getRate() const;
    void sell();
    void complaint(UInt t);
    bool operator==(const CarModel& other) const;
    bool operator!=(const CarModel& other) const;

};


#endif //HW1_WET_CARMODEL_H
