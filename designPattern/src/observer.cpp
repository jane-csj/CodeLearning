/***
* @Author: 
* @Date: 2024-12-26 15:33:42
* @LastEditTime: 2024-12-26 16:17:32
* @Description: 观察者模式
 */


#include <iostream>
#include <list>
class Observer{
public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};
class Subject{
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

class DisplayElement{
public:
    virtual void display() = 0;
};

class WeatherData : public Subject{
public:
    void registerObserver(Observer* observer) override{
        observers.push_back(observer);
    }
    void removeObserver(Observer* observer) override{
        observers.remove(observer);
    }
    void notifyObservers() override{
        for(auto observer : observers){
            observer->update(temperature, humidity, pressure);
        }
    }
    void MeasurementsChanged(){
        notifyObservers();
    }
    void setMeasurements(float temp, float humidity, float pressure){
        this->temperature = temp;
        this->humidity = humidity;
        this->pressure = pressure;
        MeasurementsChanged();
    }
private:
    std::list<Observer*> observers;
    float temperature;
    float humidity;
    float pressure;
};

class CurrentConditionsDisplay : public Observer, public DisplayElement{
public:
    CurrentConditionsDisplay(Subject* weatherData){
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }
    void update(float temp, float humidity, float pressure) override{
        this->temperature = temp;
        this->humidity = humidity;
        display();
    }
    void display() override{
        std::cout << "Current conditions: " << temperature << "F degrees and " << humidity << "% humidity" << std::endl;
    }
private:
    float temperature;
    float humidity;
    Subject* weatherData;
};


int main(){
    WeatherData* weatherData = new WeatherData();
    CurrentConditionsDisplay* currentDisplay = new CurrentConditionsDisplay(weatherData);
    weatherData->setMeasurements(80, 65, 30.4f);
    weatherData->setMeasurements(82, 70, 29.2f);
    weatherData->setMeasurements(78, 90, 29.2f);
   return 0;
}