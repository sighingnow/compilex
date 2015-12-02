#include <map>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "pl0_ast.hpp"

using namespace std;

class RegisterAllocator
{
protected:
    static const int N = 6;
    pl0_env<LOC> & env;
    struct IOOut & out;
    int & dist;
    // %eax, %ecx, %edx, %ebx, %esi, %edi
    std::string regs[N] = {"eax", "ecx", "edx", "ebx", "esi", "edi"};
    std::map<std::string, bool> used;
    std::map<std::string, std::string> record;
public:
    RegisterAllocator(pl0_env<LOC> &, struct IOOut &, int &);
    virtual std::string alloc(std::string) = 0;
    virtual void remap(std::string, std::string) = 0;
    virtual void release(std::string, bool) = 0;
    virtual std::string load(std::string, std::string) = 0;
    virtual void spill(std::string) = 0;
    virtual void store(std::string) = 0;
    virtual std::string locate(std::string) = 0;
    virtual std::string addr(std::string) = 0;
    int random() {
        std::srand(std::time(0));
        return std::rand() % N;
    }
    string exist(std::string name) {
        if (name == "~ret") { return "eax"; }
        for (auto && x: record) {
            if (x.second == name) {
                return x.first;
            }
        }
        return "";
    }
    void dump() {
        cout << ";; ------------ register mapping ----------------" << endl;
        for (auto && x: record) {
            cout << ";; "<< x.first << " : " << x.second << endl;
        }
        cout << ";; ----------------------------------------------" << endl;
    }
};

class SimpleAllocator: public RegisterAllocator {
public:
    SimpleAllocator(pl0_env<LOC> &, struct IOOut &, int &);
    std::string alloc(std::string);
    void remap(std::string, std::string);
    void release(std::string, bool);
    std::string load(std::string, std::string);
    void spill(std::string);
    void store(std::string);
    std::string locate(std::string);
    std::string addr(std::string);
};




