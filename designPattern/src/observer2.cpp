/***
* @Author: 
* @Date: 2024-12-27 00:53:53
* @LastEditTime: 2024-12-27 01:23:18
* @Description: 观察者模式
 */
#include <iostream>
#include <list>

class Observerable;

class Observer{
public:
    virtual void update(Observerable* o, void* arg) = 0;
    
};

class Observerable{
public:
    virtual ~Observerable(){} // 虚函数表支持RTTI
    void addObserver(Observer* observer){
        observers.push_back(observer);
    }
    void deleteObserver(Observer* observer){
        observers.remove(observer);
    }
    void notifyObservers(void* arg=nullptr){
        if(change){
            for(auto &obs : observers){
                obs->update(this, arg);
            }
        }
    }
    void setChanged(){
        change = true;
    }
private:
    std::list<Observer*> observers;
    bool change;
};

class DisplayElement{
public:
    virtual void display() = 0;
};

class WeatherData : public Observerable{
public:
    WeatherData() = default;
    void measurementsChanged(){
        setChanged();
        notifyObservers();
    }
    void setMeasurements(float temperature, float humidity, float pressure){
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }
    float getTemperatur(){
        return temperature;
    }
    float getHumidity(){
        return humidity;
    }
    float getPressure(){
        return pressure;
    }
private:
    float temperature;
    float humidity;
    float pressure;
    
};


class CurrentConditionsDisplay : public Observer, public DisplayElement{

public:
    CurrentConditionsDisplay(Observerable *observerable){
        this->observer = observerable;
        observer->addObserver(this);
    }

    void update(Observerable* obs, void* arg){
        if(isWeatherData(obs)){
            auto weatherData = dynamic_cast<WeatherData*>(obs);
            temperature = weatherData->getTemperatur();
            humidity = weatherData->getHumidity();
            display();
        }
    }
    void display() override{
        std::cout << "Current conditions: "  + std::to_string(temperature) + 
        "F degress and " + std::to_string(humidity) + "% humidity" << std::endl; 
    }
private:
    bool isWeatherData(Observerable* obs){
        auto o = dynamic_cast<WeatherData*>(obs);
        return o != nullptr;
    }
private:
    Observerable* observer;
    float temperature;
    float humidity;
};

int main(){
    WeatherData* weatherData = new WeatherData();
    CurrentConditionsDisplay* currentDisplay = new CurrentConditionsDisplay(weatherData);
    weatherData->setMeasurements(80, 65, 30.4f);
    weatherData->setMeasurements(82, 70, 29.2f);
    weatherData->setMeasurements(78, 90, 29.2f);
}