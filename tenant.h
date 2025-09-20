#ifndef TENANT_H
#define TENANT_H

class Tenant
{
public:
    int id, water_cold_metric, water_hot_metric, electric_metric;

    Tenant(int id, int water_cold_metric, int water_hot_metric, int eletric_metric){
        this->id = id;
        this->water_cold_metric = water_cold_metric;
        this->water_hot_metric = water_hot_metric;
        this->electric_metric = eletric_metric;
    }
    float get_tenant_water_metric(){
        return this->water_cold_metric + this->water_hot_metric;
    }
    float get_my_cost(float water_rate, float electric_rate){
        float water_cost = this->get_tenant_water_metric() * water_rate;
        float electric_cost = this->electric_metric * electric_rate;
        return water_cost + electric_cost;
    }
private:


};
#endif // TENANT_H
