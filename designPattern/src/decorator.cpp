/***
* @Author: 
* @Date: 2024-12-26 14:34:03
* @LastEditTime: 2024-12-27 10:36:04
* @Description: 装饰者模式
 */

#include <iostream>
enum Size{TALL, GRANDE, VENTI};
class Beverage{
public:
    virtual double cost() = 0;
    virtual std::string getDescription(){       // 必须加virtual关键字。
        return description;
    }
    virtual Size getSize(){                      // 加入大中小杯选择
        return size; 
    }
    virtual ~Beverage(){}
protected:
    
    std::string description = "Unknown Beverage";
    Size size = TALL;
};

class CondimentDecorator : public Beverage{
public:
    virtual std::string getDescription() = 0;
};


class Espresso : public Beverage{          
public:
    Espresso(){
        description = "Espresso";
    }
    Espresso(Size size){            // 只在该类加入大小杯选择， 若想要在其它类加入大小杯选择，则其它类也需加入构造函数
        description = "Espresso";
        this->size = size;
    }
    double cost(){
        return 1.99;
    }
};


class HouseBlend : public Beverage{
public:
    HouseBlend(){
        description = "House Blend Coffee";
    }
    double cost(){
        return 0.89;
    }
};

class DarkRoast : public Beverage{
public:
    DarkRoast(){
        description = "Dark Roast Coffee";
    }
    double cost(){
        return 0.99;
    }
};

class Mocha : public CondimentDecorator{
public:
    Mocha(Beverage* beverage){
        this->beverage = beverage;
    }
    std::string getDescription() override{
        return beverage->getDescription() + ", Mocha";
    }
    double cost(){
        return 0.20 + beverage->cost();
    }

private:
    Beverage* beverage;
};

class Whip : public CondimentDecorator{
public:
    Whip(Beverage* beverage){
        this->beverage = beverage;
    }
    std::string getDescription() override{
        return beverage->getDescription() + ", Whip";
    }
    double cost() override{
        return 0.10 + beverage->cost();
    }

private:
    Beverage* beverage;
};

class Soy : public CondimentDecorator{
public:
    Soy(Beverage* beverage){
        this->beverage = beverage;
    }

    std::string getDescription() override{
        return beverage->getDescription() + ", Soy";
    }
    Size getSize(){
        return beverage->getSize();
    }
    double cost() override{
        double cost = beverage->cost();
        switch(beverage->getSize()){
            case TALL:
                cost += 0.10;
                break;
            case GRANDE:
                cost += 0.15;
                break;
            case VENTI:
                cost += 0.20;
                break;
        }
        return cost;
    }

private:
    Beverage* beverage;
};




int main(){
    Beverage* beverage = new Espresso();
    std::cout << beverage->getDescription() << " $" << beverage->cost() << std::endl;

    Beverage* beverage2 = new DarkRoast();
    beverage2 = new Mocha(beverage2);
    beverage2 = new Mocha(beverage2);
    beverage2 = new Whip(beverage2);
    std::cout <<beverage2->getDescription() << " $" << beverage2->cost() << std::endl;

    Beverage* beverage3 = new HouseBlend();
    beverage3 = new Soy(beverage3);
    beverage3 = new Mocha(beverage3);
    beverage3 = new Whip(beverage3);
    std::cout << beverage3->getDescription() << " $" << beverage3->cost() << std::endl;

    // 大小杯选择
    Beverage* beverage4 = new Espresso(Size::GRANDE);
    beverage4 = new Soy(beverage4);
    std::cout << beverage4->getDescription() << " $" << beverage4->cost() << std::endl;
}