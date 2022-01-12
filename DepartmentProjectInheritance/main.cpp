#include <iostream>
#include <string>
using namespace std;

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, unsigned int age    //Принимаемые переметры конструктора Human
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

#define EMPLOYEE_TAKE_PARAMETERS const std::string& position
#define EMPLOYEE_GIVE_PARAMETERS position

#define tab \t

class Human
{
    std::string last_name;
    std::string first_name;
    unsigned int age;
    
public:
    const std::string& get_last_name()const
    {
        return last_name;
    }
    const std::string& get_first_name()const
    {
        return first_name;
    }
    unsigned int get_age()const
    {
        return age;
    }
    void set_last_name(const std::string& last_name)
    {
        this->last_name = last_name;
    }
    void set_first_name(const std::string& first_name)
    {
        this->first_name = first_name;
    }
    void set_age(unsigned int age)
    {
        this->age = age;
    }

    //                    Constructors:
    Human(HUMAN_TAKE_PARAMETERS)
    {
        set_last_name(last_name);
        set_first_name(first_name);
        set_age(age);
        cout << "HConstructor:\t" << this << endl;
    }
    virtual ~Human()
    {
        cout << "HDestructor:\t" << this << endl;
    }

    //                Methods:
    virtual void print()const
    {
        cout << last_name << " " << first_name << " " << age << " лет" << endl;
    }
};

class Employee: public Human //НАСЛЕДОВАНИЕ. С каким максимальным уровнем доступа будут наследованы все остальные свойства класса.
{
    std::string position;
public:
    const std::string& get_position() const
    {
        return position;
    }
    void set_position(const std::string& position) // по константной ссылке принимаем и возвращаем, чтобы компилятор не создавал доп копию и не отнимал доп память
    {
        this -> position = position;
    }
    
    virtual double get_salary() const = 0;
    
    Employee(HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS) // ДЕЛЕГИРОВАНИЕ
    {
        set_position(position);
        cout << "EConstructor: tab" << this << endl;
    }
    ~Employee()
    {
        cout << "EDestrustor: tab" << this << endl;
    }
    void print()const
    {
        Human::print(); // показываем, что print находится в именованном пространстве имен.
        cout << position << endl;
    }
};

#define PERMANENT_EMPLOYEE_TAKE_PARAMETERS double salary
#define PERMANENT_EMPLOYEE_GIVE_PARAMETERS salary

class PermanentEmployee : public Employee
{
    double salary;
public:
    double get_salary()const
    {
        return salary;
    }
    void set_salary(double salary)
    {
        this -> salary = salary;
    }
    
    PermanentEmployee(HUMAN_TAKE_PARAMETERS,
                      EMPLOYEE_TAKE_PARAMETERS,
                      PERMANENT_EMPLOYEE_TAKE_PARAMETERS) :Employee(HUMAN_GIVE_PARAMETERS, EMPLOYEE_GIVE_PARAMETERS)
    {
        set_salary(salary);
        cout << "PEConstructor:tab" << this << endl;
    }
    ~PermanentEmployee()
    {
        cout << "PEDestructor: \t" << this << endl;
    }
    
    void print()const
    {
        Employee::print();
        cout << salary;
        cout << endl;
    }
};

#define HOURLY_EMPLOYEE_TAKE_PARAMETERS double rate, int hours
#define HOURLY_EMPLOYEE_GIVE_PARAMETERS rate, hours


class HourlyEmployee : public Employee
{
    double rate;   // Тариф (ставка в час)
    int hours;     // Кол-во отработанных часов
public:
    double get_rate() const
    {
        return rate;
    }
    int get_hours() const
    {
        return hours;
    }
    double get_salary() const
    {
        return rate * hours;
    }
    
    void set_rate(double rate)
    {
        this -> rate = rate;
    }
    void set_hours(int hours)
    {
        this -> hours = hours;
    }
    
    HourlyEmployee(HUMAN_TAKE_PARAMETERS,
                   EMPLOYEE_TAKE_PARAMETERS,
                   HOURLY_EMPLOYEE_TAKE_PARAMETERS) :
    Employee(HUMAN_GIVE_PARAMETERS, EMPLOYEE_GIVE_PARAMETERS)
    {
        set_rate(rate);
        set_hours(hours);
        cout << "HEConstructor: \t" << this << endl;
    }
    ~HourlyEmployee()
    {
        cout << "HEDestructor: \t" << this << endl;
    
    }
void print() const
    {
        Employee::print();
        cout << "Rate: " << rate << ". Worked out: " << hours << " hours. Salary: " << get_salary();
        cout << endl;
    }
};

int main(int argc, const char * argv[])
{
    
    Employee* department[] =
    {
        new PermanentEmployee("Chester", "Bennington", 35, "singer", 20000),
        new PermanentEmployee("Mike", "Shinoda", 34, "pianist", 19000),
        new PermanentEmployee("Joe", "Hahn", 38, "sampler", 15000),
        new HourlyEmployee("David", "Farrell", 38, "guitarist", 1000, 8),
    };
    
    double total_salary = 0;
    
    // sizeof(department) / sizeof(Employee*) Делим размер массива в байтах на размер одного указателя и таким образом получаем размер массива в элементах
    
    for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
    {
        cout << "\n_______________________" << endl;
        
        department[i] -> print();
        total_salary += department[i] -> get_salary();
    }
    cout << "\n_______________________" << endl;
    cout << "Common salary of the whole department of magic: " << total_salary << endl;
    cout << "\n_______________________" << endl;
    
    for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
    {
        delete department[i];
    }
    
    return 0;
}
