#include <iostream>
#include <string>
#include <memory>
using namespace std;


//1. Builder design Pattern
/*
 * The Builder Creational Pattern is used to separate the construction of a complex object from its
 * representation so that the same construction
 * process can create different objects representations.

Problem
    We want to construct a complex object, however we do not want to have a
    complex constructor member or one that would need many arguments.

Solution
    Define an intermediate object whose member functions define the desired object part by part
    before the object is available to the client.
    Builder Pattern lets us defer the construction of the object until all
    the options for creation have been specified.
 */
// "Product"
class Pizza
{
public:
    void setDough(const string& dough)
    {
        m_dough = dough;
    }
    void setSauce(const string& sauce)
    {
        m_sauce = sauce;
    }
    void setTopping(const string& topping)
    {
        m_topping = topping;
    }
    void open() const
    {
        cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and "
             << m_topping << " topping. Mmm." << endl;
    }
private:
    string m_dough;
    string m_sauce;
    string m_topping;
};

// "Abstract Builder"
class PizzaBuilder
{
public:
    virtual ~PizzaBuilder() {};

    Pizza* getPizza()
    {
        return m_pizza.get();
    }
    void createNewPizzaProduct()
    {
        m_pizza = make_unique<Pizza>();
    }
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
protected:
    unique_ptr<Pizza> m_pizza;
};

//----------------------------------------------------------------

class HawaiianPizzaBuilder : public PizzaBuilder
{
public:
    virtual ~HawaiianPizzaBuilder() {};

    virtual void buildDough()
    {
        m_pizza->setDough("cross");
    }
    virtual void buildSauce()
    {
        m_pizza->setSauce("mild");
    }
    virtual void buildTopping()
    {
        m_pizza->setTopping("ham+pineapple");
    }
};

class SpicyPizzaBuilder : public PizzaBuilder
{
public:
    virtual ~SpicyPizzaBuilder() {};

    virtual void buildDough()
    {
        m_pizza->setDough("pan baked");
    }
    virtual void buildSauce()
    {
        m_pizza->setSauce("hot");
    }
    virtual void buildTopping()
    {
        m_pizza->setTopping("pepperoni+salami");
    }
};

//----------------------------------------------------------------

class Cook
{
public:
    void openPizza()
    {
        m_pizzaBuilder->getPizza()->open();
    }
    void makePizza(PizzaBuilder* pb)
    {
        m_pizzaBuilder = pb;
        m_pizzaBuilder->createNewPizzaProduct();
        m_pizzaBuilder->buildDough();
        m_pizzaBuilder->buildSauce();
        m_pizzaBuilder->buildTopping();
    }
private:
    PizzaBuilder* m_pizzaBuilder;
};

//---------------------------BUILDER ENDS -------------------------------------

/*
 * 2. Factory Method
 *
 *Definition: It defines an interface for creating an object,
 * but leaves the choice of its type to the subclasses, creation being deferred at run-time.
 * It refers to the newly created object through a common interface. Factory Method is similar
 * to Abstract Factory but without the emphasis on families.

  Problem: A framework needs to standardize the architectural model for a range of applications,
  but allow for individual applications to define their own domain objects and provide for their instantiation.


/* Abstract base class declared by framework */
class Document
{
public:
    Document(char *fn)
    {
        strcpy(name, fn);
    }
    virtual void Open() = 0;
    virtual void Close() = 0;
    char *GetName()
    {
        return name;
    }
private:
    char name[20];
};

/* Concrete derived class defined by client */
class MyDocument: public Document
{
public:
    MyDocument(char *fn): Document(fn){}
    void Open()
    {
        cout << "   MyDocument: Open()" << endl;
    }
    void Close()
    {
        cout << "   MyDocument: Close()" << endl;
    }
};

/* Framework declaration */
class Application
{
public:
    Application(): _index(0)
    {
        cout << "Application: ctor" << endl;
    }
    /* The client will call this "entry point" of the framework */
    void NewDocument(char *name)
    {
        cout << "Application: NewDocument()" << endl;
        /* Framework calls the "hole" reserved for client customization */
        _docs[_index] = CreateDocument(name);
        _docs[_index++]->Open();
    }
    void OpenDocument(){}
    void ReportDocs();
    /* Framework declares a "hole" for the client to customize */
    virtual Document *CreateDocument(char*) = 0;
private:
    int _index;
    /* Framework uses Document's base class */
    Document *_docs[10];
};

void Application::ReportDocs()
{
    cout << "Application: ReportDocs()" << endl;
    for (int i = 0; i < _index; i++)
        cout << "   " << _docs[i]->GetName() << endl;
}

/* Customization of framework defined by client */
class MyApplication: public Application
{
public:
    MyApplication()
    {
        cout << "MyApplication: ctor" << endl;
    }
    /* Client defines Framework's "hole" */
    Document *CreateDocument(char *fn)
    {
        cout << "   MyApplication: CreateDocument()" << endl;
        return new MyDocument(fn);
    }
};

//---------------------------FACTORY METHOD ENDS-------------------------

/* ABSTRACT FACTORY
 *Definition: A utility class that creates an instance of several families of classes.
 * It can also return a factory for a certain group.
    The Factory Design Pattern is useful in a situation that requires the creation of many different types
    of objects, all derived from a common base type. The Factory Method defines a method for creating the objects,
    which subclasses can then override to specify the derived type that will be created. Thus, at run time,
    the Factory Method can be passed a description of a desired object (e.g., a string read from user input) and
    return a base class pointer to a new instance of that object. The pattern works best when a well-designed
    interface is used for the base class, so there is no need to cast the returned object.

Problem
    We want to decide at run time what object is to be created based on some configuration or application parameter.
    When we write the code, we do not know what class should be instantiated.

Solution
    Define an interface for creating an object, but let subclasses decide which class to instantiate.
    Factory Method lets a class defer instantiation to subclasses.

In the following example, a factory method is used to create laptop or desktop computer objects at run time.
 */

class Shape {
public:
    Shape() {
        id_ = total_++;
    }
    virtual void draw() = 0;
protected:
    int id_;
    static int total_;
};
int Shape::total_ = 0;

class Circle : public Shape {
public:
    void draw() {
        cout << "circle " << id_ << ": draw" << endl;
    }
};
class Square : public Shape {
public:
    void draw() {
        cout << "square " << id_ << ": draw" << endl;
    }
};
class Ellipse : public Shape {
public:
    void draw() {
        cout << "ellipse " << id_ << ": draw" << endl;
    }
};
class Rectangle : public Shape {
public:
    void draw() {
        cout << "rectangle " << id_ << ": draw" << endl;
    }
};

class Factory {
public:
    virtual Shape* createCurvedInstance() = 0;
    virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public Factory {
public:
    Shape* createCurvedInstance() {
        return new Circle;
    }
    Shape* createStraightInstance() {
        return new Square;
    }
};
class RobustShapeFactory : public Factory {
public:
    Shape* createCurvedInstance()   {
        return new Ellipse;
    }
    Shape* createStraightInstance() {
        return new Rectangle;
    }
};
//---------------------------ABSTRACT FACTORY ENDS-------------------------

// Difference between Abstract and Factory methods
/*
•	Factory Method is used to create one product only but Abstract Factory is about creating families of related or
    dependent products.
•	Factory Method depends on inheritance to decide which product to be created, while Abstract Factory,
    there’s a separate class dedicated to create a family of related/dependent Products and
    its (any concrete subclass factory) object can be passed to the client which uses it (composition).
•	Factory Method is just a method while Abstract Factory is an object.
•	Abstract Factory is one level higher in abstraction than Factory Method.
    Factory Method abstracts the way objects are created, while Abstract Factory also abstracts
    the way factories are created which in turn abstracts the way objects are created.
•	As Abstract Factory is at a higher level in abstraction, it often uses Factory Method to create the products in factories.

 */
int main()
{
    //Builder starts-------------
    cout<<"\n----------------BUILDER ---------------------------"<<endl;
    Cook cook;
    HawaiianPizzaBuilder hawaiianPizzaBuilder;
    SpicyPizzaBuilder    spicyPizzaBuilder;

    cook.makePizza(&hawaiianPizzaBuilder);
    cook.openPizza();

    cook.makePizza(&spicyPizzaBuilder);
    cook.openPizza();
    //Builder ends-----------

    // Factory Method
    cout<<"\n----------------FACTORY METHOD ---------------------------"<<endl;
    MyApplication myApp;

    myApp.NewDocument("foo");
    myApp.NewDocument("bar");
    myApp.ReportDocs();
    // Factory method ends

    // Abstract factory

    cout<<"\n----------------ABSTRACT FACTORY ---------------------------"<<endl;

    Factory* factory = new SimpleShapeFactory;
    //Factory* factory = new RobustShapeFactory;
    Shape* shapes[3];

    shapes[0] = factory->createCurvedInstance();   // shapes[0] = new Ellipse;
    shapes[1] = factory->createStraightInstance(); // shapes[1] = new Rectangle;
    shapes[2] = factory->createCurvedInstance();   // shapes[2] = new Ellipse;

    for (int i=0; i < 3; i++) {
        shapes[i]->draw();
    }

    // Abstract factory ends

    return 0;
}
