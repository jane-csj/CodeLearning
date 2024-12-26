/***
* @Author: 
* @Date: 2024-12-26 14:34:03
* @LastEditTime: 2024-12-26 14:54:03
* @Description: 行为型模式
 */



#include <iostream>

class FlyBehavior{
public:
    virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior{
public:
    void fly(){
        std::cout << "fly with wings" << std::endl;
    }
};

class FlyNoWay : public FlyBehavior{
public:
    void fly(){
        std::cout << "fly no way" << std::endl;
    }
};

class QuackBehavior{
public:
    virtual void quack() = 0;
};

class Quack : public QuackBehavior{
public:
    void quack(){
        // 呱呱叫
        std::cout << "quack" << std::endl;
    }
};
class Squeak : public QuackBehavior{
public:
    void quack(){
        // 吱吱叫
        std::cout << "squeak" << std::endl;
    }
};
class MuteQuack : public QuackBehavior{
public:
    void quack(){
        // 静音
        std::cout << "mute quack" << std::endl;
    }
};



class Duck{
protected:
    FlyBehavior* flyBehavior;
    QuackBehavior* quackBehavior;
public:
    Duck(){
        
    }
    void performQuack(){
        quackBehavior->quack();
    }
    void performFly(){
        flyBehavior->fly();
    }
    virtual void display() = 0;
    void setFlyBehavior(FlyBehavior* fb){
        flyBehavior = fb;
    }
    void setQuackBehavior(QuackBehavior* qb){
        quackBehavior = qb;
    }
    virtual void swim(){
        std::cout << "All ducks float, even decoys!" << std::endl;
    }
};

class MallardDuck : public Duck{
public:
    MallardDuck(){
        quackBehavior = new Quack();
        flyBehavior = new FlyWithWings();
    }
    void display(){
        std::cout << "I'm a Mallard duck" << std::endl;
    }
};

int main(){
    MallardDuck* mallard = new MallardDuck();
    mallard->display();
    mallard->swim();
    mallard->performQuack();
    mallard->performFly();
    mallard->setFlyBehavior(new FlyNoWay());
    mallard->performFly();
    mallard->setQuackBehavior(new Squeak());
    mallard->performQuack();
    return 0;
}

