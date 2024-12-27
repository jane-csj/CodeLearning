/***
* @Author: 
* @Date: 2024-12-27 15:15:31
* @LastEditTime: 2024-12-27 16:22:38
* @Description: 抽象工厂模式
 */

#include <iostream>
#include <vector>
#include <sstream>
class Dough{
public:
    virtual ~Dough(){}
    virtual std::string toString(){
        return "Dough";
    }
};
class Sauce{
public:
    virtual ~Sauce(){}
    virtual std::string toString(){
        return "Sauce";
    }
};
class Cheese{
public:
    virtual ~Cheese(){}
    virtual std::string toString(){
        return "Cheese";
    }
};
class Veggies{
public:
    virtual ~Veggies(){}
    virtual std::string toString(){
        return "Veggies";
    }
};
class Pepperoni{
public:
    virtual ~Pepperoni(){}
    virtual std::string toString(){
        return "Pepperoni";
    }
};
class Clam{
public:
    virtual ~Clam(){}
    virtual std::string toString(){
        return "Clam";
    }
};

class Pizza {
public:
    virtual ~Pizza() {}
    virtual void prepare() = 0;
    virtual void bake(){
        std::cout << "Bake for 25 minutes at 350" << std::endl;
    }
    virtual void cut() {
        std::cout << "Cutting the pizza into diagonal slices" << std::endl;
    }
    virtual void box() {
        std::cout << "Place pizza in official PizzaStore box" << std::endl;
    }
    void setName(std::string name) {
        this->name = name;
    }
    std::string getName() {
        return name;
    }

    virtual std::string toString() {
        std::stringstream ss;
        ss << "---- " << name << " ----" << std::endl;
        ss << dough->toString() << std::endl;
        ss << sauce->toString() << std::endl;
        for (auto veggie : veggies) {
            ss << veggie->toString() << std::endl;
        }
        ss << cheese->toString() << std::endl;
        return ss.str();
    }
protected:
    std::string name;
    Dough* dough;
    Sauce* sauce;
    std::vector<Veggies*> veggies;
    Cheese* cheese;
    Pepperoni* pepperoni;
    Clam* clam;
};

class PizzaIngredientFactory {
public:
    virtual ~PizzaIngredientFactory() {}
    virtual Dough* createDough() = 0;
    virtual Sauce* createSauce() = 0;
    virtual Cheese* createCheese() = 0;
    virtual std::vector<Veggies*> createVeggies() = 0;
    virtual Pepperoni* createPepperoni() = 0;
    virtual Clam* createClam() = 0;
};

class ThinCrustDough : public Dough {
public:
    std::string toString() override {
        return "Thin Crust Dough";
    }
};

class MarinaraSauce : public Sauce {
public:
    std::string toString() override {
        return "Marinara Sauce";
    }
};

class ReggianoCheese : public Cheese {
public:
    std::string toString() override {
        return "Reggiano Cheese";
    }
};

class Garlic : public Veggies {
public:
    std::string toString() override {
        return "Garlic";
    }
};

class Onion : public Veggies {
public:
    std::string toString() override {
        return "Onion";
    }
};

class Mushroom : public Veggies {
public:
    std::string toString() override {
        return "Mushroom";
    }
};

class slicedPepperoni : public Pepperoni {
public:
    std::string toString() override {
        return "Sliced Pepperoni";
    }
};
class FreshClam : public Clam {
public:
    std::string toString() override {
        return "Fresh Clams from Long Island Sound";
    }
};
class NYPizzaIngredientFactory : public PizzaIngredientFactory {
public:
    Dough* createDough() override {
        return new ThinCrustDough();
    }

    Sauce* createSauce() override {
        return new MarinaraSauce();
    }

    Cheese* createCheese() override {
        return new ReggianoCheese();
    }

    std::vector<Veggies*> createVeggies() override {
       std::vector<Veggies*> veggies={new Garlic(), new Onion(), new Mushroom()};
       return veggies;
    }
    Pepperoni* createPepperoni(){
        return new slicedPepperoni();
    }
    Clam* createClam(){
        return new FreshClam();
    }
};



class CheesePizza : public Pizza {
public:
    CheesePizza(PizzaIngredientFactory* ingredientFactory) {
        this->ingredientFactory = ingredientFactory;
    }
    void prepare() override {
        std::cout << "Preparing " << name << std::endl;
        dough = ingredientFactory->createDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
    }
private:
    PizzaIngredientFactory* ingredientFactory;
};

class ClamPizza : public Pizza {
public:
    ClamPizza(PizzaIngredientFactory* ingredientFactory) {
        this->ingredientFactory = ingredientFactory;
    }
    void prepare() override {
        dough = ingredientFactory->createDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
        clam = ingredientFactory->createClam();
   }
private:
    PizzaIngredientFactory* ingredientFactory;
};

class PepperoniPizza : public Pizza {
public:
    PepperoniPizza(PizzaIngredientFactory* ingredientFactory) {
        this->ingredientFactory = ingredientFactory;
    }
    void prepare() override {
        dough = ingredientFactory->createDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
        pepperoni = ingredientFactory->createPepperoni();
   }
private:
    PizzaIngredientFactory* ingredientFactory;
};

class VeggiePizza : public Pizza
{
public:
    VeggiePizza(PizzaIngredientFactory* ingredientFactory)
    {
        this->ingredientFactory = ingredientFactory;
    }
    void prepare() override {
        dough = ingredientFactory->createDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
        veggies = ingredientFactory->createVeggies();
   }
private:
    PizzaIngredientFactory* ingredientFactory;
};

class PizzaStore{
public:
    Pizza *orderPizza(std::string type)
    {
        Pizza *pizza = createPizza(type);
        if (pizza)
        {
            pizza->prepare();
            pizza->bake();
            pizza->cut();
            pizza->box();
        }
        return pizza;
    }

protected:
    virtual Pizza* createPizza(std::string type) = 0;
};

class NYPizzaStore : public PizzaStore {
public:
    Pizza* createPizza(std::string type) override {
        Pizza* pizza = nullptr;
        PizzaIngredientFactory* ingredientFactory = new NYPizzaIngredientFactory();
        if (type == "cheese") {
            pizza =  new CheesePizza(ingredientFactory);
            pizza->setName("New York Style Clam Pizza");
        } else if (type == "clam") {
            pizza = new ClamPizza(ingredientFactory);
            pizza->setName("New York Style Clam Pizza");
        } else if(type == "pepperoni"){
            pizza = new PepperoniPizza(ingredientFactory);
            pizza->setName("New York Style Pepperoni Pizza");
        } else if(type == "veggie"){
            pizza =  new VeggiePizza(ingredientFactory);
            pizza->setName("New York Style Veggie Pizza");
        } 
        return pizza;
    }
};

int main(){
    PizzaStore* nyStore = new NYPizzaStore();
    
    Pizza* pizza = nyStore->orderPizza("cheese");
    std::cout << "Ethan ordered a " << pizza->getName() << std::endl;
    std::cout << pizza->toString() << std::endl;
    return 0;
}