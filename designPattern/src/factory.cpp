/***
* @Author: 
* @Date: 2024-12-27 14:38:25
* @LastEditTime: 2024-12-27 15:53:43
* @Description: 工厂模式
 */

#include <iostream>
#include <list>

class Pizza{
public:
    virtual void prepare(){
        std::cout << "prepare " << name << std::endl;
        std::cout << "Tossing dough..." << std::endl;
        std::cout << "Adding sauce..." << std::endl;
        std::cout << "Adding toppings..." << std::endl;
        for(auto& topping : toppings){
            std::cout << "  " << topping << std::endl;
        }
    }
    virtual void bake(){
        std::cout << "Bake for 25 minutes at 350" << std::endl;
    }
    virtual void cut(){
        std::cout << "Cutting the pizza into diagonal slices" << std::endl;
    }
    virtual void box(){
        std::cout << "Place pizza in official PizzaStore box" << std::endl;
    }
    virtual std::string getName(){
        return name;
    }
protected:
    std::string name;
    std::string dough;
    std::string sauce;
    std::list<std::string> toppings;
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

class NYStyleCheesePizza : public Pizza{
public:
    NYStyleCheesePizza(){
        name = "NY Style Sauce and Cheese Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings.push_back("Grated Reggiano Cheese");
    }
};



class NYStyleVeggiePizza : public Pizza{
public:
    NYStyleVeggiePizza(){
        name = "NY Style Veggie Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings.push_back("Grated Reggiano Cheese");
    }
};

class NYStyleClamPizza : public Pizza{
public:
    NYStyleClamPizza(){
        name = "NY Style Clam Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings.push_back("Grated Reggiano Cheese");
    }
};

class NYStylePepperoniPizza : public Pizza{
public:
    NYStylePepperoniPizza(){
        name = "NY Style Pepperoni Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings.push_back("Grated Reggiano Cheese");
    }
};

class ChicagoStyleCheesePizza : public Pizza{
public:
    ChicagoStyleCheesePizza(){
        name = "Chicago Style Deep Dish Cheese Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings.push_back("Shredded Mozzarella Cheese");
    }
    void cut() override{
        std::cout << "Cutting the pizza into square slices" << std::endl;
    }
};

class ChicagoStyleClamPizza : public Pizza{
public:
    ChicagoStyleClamPizza(){
        name = "Chicago Style Deep Dish Clam Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings.push_back("Shredded Mozzarella Cheese");
        toppings.push_back("FrozenClams from Chesapeake Bay");
    }
};

class ChicagoStylePepperoniPizza : public Pizza{
public:
    ChicagoStylePepperoniPizza(){
        name = "Chicago Style Deep Dish Pepperoni Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings.push_back("Shredded Mozzarella Cheese");
        toppings.push_back("Black Olives");
    }
};

class ChicagoStyleVeggiePizza : public Pizza{
public:
    ChicagoStyleVeggiePizza(){
        name = "Chicago Style Deep Dish Veggie Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings.push_back("Shredded Mozzarella Cheese");
        toppings.push_back("Black Olives");
    }
};

class NYPizzaStore : public PizzaStore{
protected:
    Pizza* createPizza(std::string type) override{
        if(type == "cheese"){
            return new NYStyleCheesePizza();
        }else if(type == "veggie"){
            return new NYStyleVeggiePizza();
        }else if(type == "clam"){
            return new NYStyleClamPizza();
        }else if(type == "pepperoni"){
            return new NYStylePepperoniPizza();
        }
        return nullptr;
    }
};
class ChicagoPizzaStore : public PizzaStore{
protected:
    Pizza* createPizza(std::string type) override{
        if(type == "cheese"){
            return new ChicagoStyleCheesePizza();
        }else if(type == "veggie"){
            return new ChicagoStyleVeggiePizza();
        }else if(type == "clam"){
            return new ChicagoStyleClamPizza();
        }else if(type == "pepperoni"){
            return new ChicagoStylePepperoniPizza();
        }
        return nullptr;
    }
};

int main(){
    PizzaStore* nyStore = new NYPizzaStore();
    PizzaStore* chicagoStore = new ChicagoPizzaStore();

    Pizza* pizza = nyStore->orderPizza("cheese");
    std::cout << "Ethan ordered a " << pizza->getName() << std::endl;

    pizza = chicagoStore->orderPizza("cheese");
    std::cout << "Joel ordered a " << pizza->getName() << std::endl;
    return 0;
}