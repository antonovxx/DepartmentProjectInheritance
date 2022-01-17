#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, unsigned int age //Принимаемые переметры конструктора Human
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
        //cout << "HConstructor:\t" << this << endl;
    }
    virtual ~Human()
    {
        //cout << "HDestructor:\t" << this << endl;
    }

    //                Methods:
    virtual ostream& print(ostream& os)const // Вывод в консоль
    {
        //return os << last_name << " " << first_name << " " << age << " лет" << endl;
        os << "|| Name: " ;
        os.width(12);
        os << left;
        
        os << last_name << " ";
        os.width(12);
        os << first_name << "|";
       // os.width(5);
        os << "| Age: ";
        os.width(5);
        os << age << " years |";
        return os;
    }
    virtual ofstream& print(ofstream& os)const // Вывод в файл
    {
        //return os << last_name << " " << first_name << " " << age << " лет" << endl;
        os.width(10); // метод в классе ios_base. Измеряется в знакопозициях
        os << left; // манипулятор вывода
        os << last_name;
        os.width(15);
        os << first_name;
        os.width(5);
        os << age;
        return os;
    }
    
    virtual istream& input (istream& is) // Ввод в консоль
    {
        cout << "Last name:  ";
        is >> last_name;
        cout << "First name: ";
        is >> first_name;
        cout << "Age:        ";
        is >> age;
        return is;
    }
};

// Overload operator << in order to print data using cout:
ostream& operator<<(ostream& os, const Human& obj)
{
    return obj.print(os);
    //return os << obj.get_last_name() << " " << obj.get_first_name() << " " << obj.get_age() << " ages.";
}
istream& operator>>(istream& is, Human& obj)
{
    return obj.input(is);
}
ofstream& operator<<(ofstream& os, const Human& obj)
{
    return obj.print(os);
}



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
        //cout << "EConstructor: tab" << this << endl;
    }
    ~Employee()
    {
        //cout << "EDestrustor: tab" << this << endl;
    }
//    void print()const
//    {
//        Human::print(); // показываем, что print находится в именованном пространстве имен.
//        cout << position << endl;
//    }
    ostream& print(ostream& os)const
    {
        Human::print(os); // показываем, что print находится в именованном пространстве имен.
        os.width(10);
        os << left;
        os << "| Position: " << position << " |";
        return os;
    }
    ofstream& print(ofstream& os)const
    {
        Human::print(os);
        os.width(10);
        os << left;
        os << position;
        return os;
    }
    
    istream& input(istream& is)
    {
        Human::input(is);
        cout << "Position: ";
        return is >> position;
    }
};

//ostream& operator<<(ostream& os, const Employee& obj)
//{
//    os << (Human)obj;
//    return os << obj.get_position() << endl;
//}

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
        //cout << "PEConstructor:tab" << this << endl;
    }
    ~PermanentEmployee()
    {
        //cout << "PEDestructor: \t" << this << endl;
    }
    
    ostream& print(ostream& os)const
    {
        Employee::print(os);
        os.width(10);
        os << left;
        os << "| Salary: " << salary << " ||";
        return os;
    }
    ofstream& print(ofstream& os)const
    {
        Employee::print(os);
        os.width(10);
        os << salary;
        return os;
    }
    istream& input(istream& is)
    {
        Employee::input(is);
        cout << "Salary: ";
        return is >> salary;
    }
};

//ostream& operator<<(ostream& os, const PermanentEmployee& obj)
//{
//    return os << (Employee&)obj << " " << obj.get_salary();
//}

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
        //cout << "HEConstructor: \t" << this << endl;
    }
    ~HourlyEmployee()
    {
        //cout << "HEDestructor: \t" << this << endl;
    
    }
    ostream& print(ostream& os) const
    {
        Employee::print(os) << " ";
        os << left;
        os.width(10);
        os << "|| Rate: " << rate << " |";
        os.width(10);
        os << "| Worked out: " << hours << " hours |";
        os.width(10);
        os << "| Salary: " << get_salary() << " ||";
        return os;
    }
    ofstream& print(ofstream& os) const
    {
        Employee::print(os);
        os << right;
        os.width(5);
        os << rate;
        os.width(10);
        os << hours;
        os.width(10);
        os << get_salary();
        return os;
    }
    istream& input(istream& is)
    {
        Employee::input(is);
        cout << "Rate:    ";
        is >> rate >> hours;
        return is;
    }
};
//ostream& operator<<(ostream& os, const HourlyEmployee& obj)
//{
//    return os << (Employee&)obj << " " << "Rate: " << obj.get_rate() << "hоurs: " << obj.get_hours() << "total: " << obj.get_salary(); // Вывод с рейтингом, часами и зарплатой
//}

//#define SAVE_TO_FILE

int main(int argc, const char * argv[])
{
#ifdef SAVE_TO_FILE
    /*
    // Generalisation
    Employee* department[] =
    {
        new PermanentEmployee("Chester", "Bennington", 35, "singer", 20000),
        new PermanentEmployee("Mike", "Shinoda", 34, "pianist", 19000),
        new PermanentEmployee("Joe", "Hahn", 38, "sampler", 15000),
        new HourlyEmployee("David", "Farrell", 38, "guitarist", 1000, 8),
    };
    
    // INPUT
    for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
    {
        //cout << "Введите работника " << typeid(*department[i]).name() << ":";
        cin >> *department[i];
    }
    
    double total_salary = 0;
    
    
    // sizeof(department) / sizeof(Employee*) Делим размер массива в байтах на размер одного указателя и таким образом получаем размер массива в элементах
    
    
    // OUPUT
    for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
    {
        cout << "\n_______________________" << endl;
        
        cout << *department[i] << endl;

//        if (typeid(*department[i]) == typeid(PermanentEmployee))
//        {
//            cout << *department[i] << endl;
//        }
//        if (typeid(*department[i]) == typeid(HourlyEmployee))
//        {
//            cout << *department[i] << endl;
//        }
        
//        // Specialisation (DOWNCAST)
//        if (typeid(*department[i]) == typeid(PermanentEmployee)) // Определяем тип работника и выводим определенный вывод под этого работника, или только с зарплатой или с зарплатой и часами
//        {
//            cout << *dynamic_cast<PermanentEmployee*>(department[i]) << endl;
//        }
//        if (typeid(*department[i]) == typeid(HourlyEmployee))
//        {
//            cout << dynamic_cast<HourlyEmployee*>(department[i]) << endl;
//        }
        
        // dynamic_cast<DerivedClass*>(BaseClass*); преобразует указатель на базовый класс в указатель на дочерний класс т.е. позволяет выполнить даункаст
        
        total_salary += department[i] -> get_salary();
    }
    
    
    cout << "\n_______________________" << endl;
    cout << "Common salary of the whole department: " << total_salary << endl;
    cout << "\n_______________________" << endl;
    
    // OUTPUT IN FILE
    ofstream fout("/Users/antonkurin/Documents/Cplusplus/DepartmentProjectInheritance/file.txt");
    for (int i = 0; i < sizeof(department) /sizeof(Employee*); ++i) {
        fout.width(25);
        fout << left;
        fout << string(typeid(*department[i]).name()) + ":";
        fout << *department[i] << endl;
    }
    fout.close();
    
    system("more /Users/antonkurin/Documents/Cplusplus/DepartmentProjectInheritance/file.txt");
    
    // CLEAR MEMORY
    
    for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
    {
        delete department[i];
    }
    
     */
#endif //SAVE_TO_FILE
    
    
    
    
    
    
    return 0;
}




