#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

class DB
{
    string name;

public:
    DB(string name) : name(name)
    {
        cout << "Created: " << name << endl;
    }
    void getDBName()
    {
        cout << name << endl;
    }
};

class DBConnection
{
private:
    static DB *connection;
    static inline mutex mtx;

public:
    static DB *createDBConnection(string name)
    {

        if (connection == nullptr)
        { // first check

            lock_guard<mutex> lock(mtx);

            if (connection == nullptr)
            { // second check
                connection = new DB(name);
            }
        }

        return connection;
    }
};

DB *DBConnection::connection = nullptr;

int main()
{

    thread t1([]()
              { DBConnection::createDBConnection("DB 1")->getDBName(); });

    thread t2([]()
              { DBConnection::createDBConnection("DB 2")->getDBName(); });
              

    t1.join();
    t2.join();

    return 0;
}