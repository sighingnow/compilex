
#ifndef __PL0_AST_HPP__
#define __PL0_AST_HPP__

#include <iostream>
#include <string>
#include <vector>
#include "patch.hpp"
using namespace std;

struct pl0_ast_t;
struct pl0_ast_program;
struct pl0_ast_prog;
struct pl0_ast_const_stmt;
struct pl0_ast_const_define;
struct pl0_ast_constv;
struct pl0_ast_charseq;
struct pl0_ast_identify;
struct pl0_ast_var_stmt;
struct pl0_ast_var_define;
struct pl0_ast_type;
struct pl0_ast_primitive_type;
struct pl0_ast_executable;
struct pl0_ast_procedure_stmt;
struct pl0_ast_function_stmt;
struct pl0_ast_procedure_header;
struct pl0_ast_function_header;
struct pl0_ast_param_list;
struct pl0_ast_param_group;
struct pl0_ast_stmt;
struct pl0_ast_null_stmt;
struct pl0_ast_assign_stmt;
struct pl0_ast_function_id;
struct pl0_ast_expression;
struct pl0_ast_term;
struct pl0_ast_factor;
struct pl0_ast_call_func;
struct pl0_ast_arg_list;
struct pl0_ast_arg;
struct pl0_ast_addop;
struct pl0_ast_multop;
struct pl0_ast_condtion;
struct pl0_ast_comp_op;
struct pl0_ast_cond_stmt;
struct pl0_ast_case_stmt;
struct pl0_ast_case_term;
struct pl0_ast_for_stmt;
struct pl0_ast_call_proc;
struct pl0_ast_compound_stmt;
struct pl0_ast_read_stmt;
struct pl0_ast_write_stmt;
struct pl0_ast_alnum;

struct pl0_ast_program {
    pair<int, int> loc;
    struct pl0_ast_prog *program;
    pl0_ast_program(pair<int, int> loc, pl0_ast_prog *program): loc(loc), program(program) {}
};
struct pl0_ast_prog {
    pair<int, int> loc;
    struct pl0_ast_const_stmt *consts;
    struct pl0_ast_var_stmt *vars;
    std::vector<struct pl0_ast_executable *> exes;
    struct pl0_ast_compound_stmt *stmts;
    pl0_ast_prog(pair<int, int> loc, struct pl0_ast_const_stmt *consts,
        struct pl0_ast_var_stmt *vars,
        std::vector<struct pl0_ast_executable *> const & exes,
        struct pl0_ast_compound_stmt *stmts)
        : loc(loc), consts(consts), vars(vars), exes(exes), stmts(stmts) {
        // cout << "parser prog." << endl;
    }
};
struct pl0_ast_const_stmt {
    pair<int, int> loc;
    std::vector<struct pl0_ast_const_define *> stmt;
    pl0_ast_const_stmt(pair<int, int> loc, std::vector<pl0_ast_const_define *> const & stmt): loc(loc), stmt(stmt) {}
};
struct pl0_ast_const_define {
    pair<int, int> loc;
    struct pl0_ast_identify *id;
    struct pl0_ast_constv *val;
    pl0_ast_const_define(pair<int, int> loc, pl0_ast_identify *id, pl0_ast_constv *val): loc(loc), id(id), val(val) {}
};
struct pl0_ast_constv {
    pair<int, int> loc;
    int val;
    enum DTYPE { INT, CHAR } dt;
    pl0_ast_constv(pair<int, int> loc, int const val, DTYPE const dt): loc(loc), val(val), dt(dt) {}
};
struct pl0_ast_charseq {
    pair<int, int> loc;
    std::string val;
    pl0_ast_charseq(pair<int, int> loc, std::string const & val): loc(loc), val(val) {}
};
struct pl0_ast_identify {
    pair<int, int> loc;
    std::string id;
    pl0_ast_identify(pair<int, int> loc, std::string const & id): loc(loc), id(id) {}
};
struct pl0_ast_var_stmt {
    pair<int, int> loc;
    std::vector<struct pl0_ast_var_define *> stmt;
    pl0_ast_var_stmt(pair<int, int> loc, std::vector<pl0_ast_var_define *> const & stmt): loc(loc), stmt(stmt) {}
};
struct pl0_ast_var_define {
    pair<int, int> loc;
    struct pl0_ast_type *type;
    std::vector<struct pl0_ast_identify *> ids;
    pl0_ast_var_define(pair<int, int> loc, pl0_ast_type *type, std::vector<pl0_ast_identify *> const & ids): loc(loc), type(type), ids(ids) {}
};
struct pl0_ast_type {
    pair<int, int> loc;
    struct pl0_ast_primitive_type *type;
    int len; // if array, len = -1
    pl0_ast_type(pair<int, int> loc, pl0_ast_primitive_type *type, int len): loc(loc), type(type), len(len) {}
};
struct pl0_ast_primitive_type {
    pair<int, int> loc;
    std::string type;
    pl0_ast_primitive_type(pair<int, int> loc, std::string type): loc(loc), type(type) {}
};
struct pl0_ast_executable {
    pair<int, int> loc;
    string const name = "pl0 executable object.";
    enum type_t {
        PROCEDURE, FUNCTION
    };
    type_t t;
    struct pl0_ast_procedure_stmt *proc;
    struct pl0_ast_function_stmt *func;
    pl0_ast_executable(pair<int, int> loc, pl0_ast_procedure_stmt *proc): loc(loc), t(type_t::PROCEDURE), proc(proc), func(nullptr) {}
    pl0_ast_executable(pair<int, int> loc, pl0_ast_function_stmt *func): loc(loc), t(type_t::FUNCTION), proc(nullptr), func(func) {}
};
struct pl0_ast_procedure_stmt {
    pair<int, int> loc;
    std::vector<std::pair<struct pl0_ast_procedure_header *, struct pl0_ast_prog *>> procs;
    pl0_ast_procedure_stmt(pair<int, int> loc, std::vector<std::pair<pl0_ast_procedure_header *, pl0_ast_prog *>> const & procs): loc(loc), procs(procs) {}
};
struct pl0_ast_function_stmt {
    pair<int, int> loc;
    std::vector<std::pair<struct pl0_ast_function_header *, struct pl0_ast_prog *>> funcs;
    pl0_ast_function_stmt(pair<int, int> loc, std::vector<std::pair<pl0_ast_function_header *, pl0_ast_prog *>> const & funcs): loc(loc), funcs(funcs) {}
};
struct pl0_ast_procedure_header {
    pair<int, int> loc;
    struct pl0_ast_identify *id;
    struct pl0_ast_param_list *params;
    pl0_ast_procedure_header(pair<int, int> loc, pl0_ast_identify *id, pl0_ast_param_list *params): loc(loc), id(id), params(params) {}
};
struct pl0_ast_function_header {
    pair<int, int> loc;
    struct pl0_ast_identify *id;
    struct pl0_ast_param_list *params;
    struct pl0_ast_primitive_type *type;
    pl0_ast_function_header(pair<int, int> loc, pl0_ast_identify *id, pl0_ast_param_list *params, pl0_ast_primitive_type *type): loc(loc), id(id), params(params), type(type) {}
};
struct pl0_ast_param_list {
    pair<int, int> loc;
    std::vector<struct pl0_ast_param_group *> params;
    pl0_ast_param_list(pair<int, int> loc, vector<pl0_ast_param_group *> const & params): loc(loc), params(params) {}
};
struct pl0_ast_param_group {
    pair<int, int> loc;
    std::vector<struct pl0_ast_identify *> ids;
    struct pl0_ast_primitive_type *type;
    bool is_ref;
    pl0_ast_param_group(pair<int, int> loc, vector<pl0_ast_identify *> const & ids, pl0_ast_primitive_type *type, bool is_ref = false): loc(loc), ids(ids), type(type), is_ref(is_ref) {}
};
struct pl0_ast_stmt {
    pair<int, int> loc;
    enum type_t {
        STMT, ASSIGN_STMT, COND_STMT, CASE_STMT, CALL_PROC, COMPOUND_STMT, WRITE_STMT, READ_STMT, FOR_STMT, NULL_STMT, INHERIT
    };
    type_t t;
    // pl0_ast_stmt(): t(type_t::INHERIT), stmt(nullptr) {}
    pl0_ast_stmt(pair<int, int> loc, type_t const t): loc(loc), t(t) {}
    virtual ~pl0_ast_stmt() {}; // make pl0_ast_stmt polymorphic.
};
struct pl0_ast_null_stmt: pl0_ast_stmt {
    pl0_ast_null_stmt(pair<int, int> loc): pl0_ast_stmt(loc, type_t::NULL_STMT) {}
}; // empty statement, not in grammar.
struct pl0_ast_assign_stmt: pl0_ast_stmt {
    struct pl0_ast_identify *id;
    struct pl0_ast_expression *idx;
    struct pl0_ast_expression *val;
    pl0_ast_assign_stmt(pair<int, int> loc, pl0_ast_identify *id, pl0_ast_expression *idx, pl0_ast_expression *val): pl0_ast_stmt(loc, pl0_ast_stmt::type_t::ASSIGN_STMT), id(id), idx(idx), val(val) {}
};
struct pl0_ast_function_id {
    pair<int, int> loc;
    struct pl0_ast_identify *id;
    pl0_ast_function_id(pair<int, int> loc, pl0_ast_identify *id): loc(loc), id(id) {}
};
struct pl0_ast_expression {
    pair<int, int> loc;
    std::vector<std::pair<struct pl0_ast_addop *, struct pl0_ast_term *>> terms;
    pl0_ast_expression(pair<int, int> loc, std::vector<std::pair<struct pl0_ast_addop *, struct pl0_ast_term *>> const & terms): loc(loc), terms(terms) {}
};
struct pl0_ast_term {
    pair<int, int> loc;
    std::vector<std::pair<struct pl0_ast_multop *, struct pl0_ast_factor *>> factors;
    pl0_ast_term(pair<int, int> loc, std::vector<std::pair<pl0_ast_multop *, pl0_ast_factor *>> const & factors): loc(loc), factors(factors) {}
};
struct pl0_ast_factor {
    pair<int, int> loc;
    enum type_t {
        ID = 1, UNSIGNED = 2, EXPR = 3, CALL_FUNC = 4, ARRAY_E = 5
    };
    type_t t;
    union {
        struct pl0_ast_identify *id;
        struct pl0_ast_constv *unsignedn;
        struct pl0_ast_expression *expr;
        struct pl0_ast_call_func *call_func;
    } ptr;
    std::pair<struct pl0_ast_identify *, struct pl0_ast_expression *> arraye; // for array access.
    pl0_ast_factor(pair<int, int> loc, type_t t, void *ptr): loc(loc), t(t) {
        switch (this->t) {
            case type_t::ID: this->ptr.id = static_cast<pl0_ast_identify *>(ptr); break;
            case type_t::EXPR: this->ptr.expr = static_cast<pl0_ast_expression *>(ptr); break;
            case type_t::CALL_FUNC: this->ptr.call_func = static_cast<pl0_ast_call_func *>(ptr); break;
            case type_t::UNSIGNED: this->ptr.unsignedn = static_cast<pl0_ast_constv *>(ptr); break;
            default: cout << "unknown factor type: " << t << endl; throw(this->t);
        }
    }
    pl0_ast_factor(pair<int, int> loc, std::pair<struct pl0_ast_identify *, struct pl0_ast_expression *> const & arraye): loc(loc), t(type_t::ARRAY_E), arraye(arraye) {}
};
struct pl0_ast_call_func {
    pair<int, int> loc;
    struct pl0_ast_identify *fn;
    struct pl0_ast_arg_list *args;
    pl0_ast_call_func(pair<int, int> loc, pair<pl0_ast_identify *, pl0_ast_arg_list *> const & call): loc(loc), fn(call.first), args(call.second) {}
};
struct pl0_ast_arg_list {
    pair<int, int> loc;
    std::vector<struct pl0_ast_arg *> args;
    pl0_ast_arg_list(pair<int, int> loc, std::vector<struct pl0_ast_arg *> const & args): loc(loc), args(args) {}
};
struct pl0_ast_arg {
    pair<int, int> loc;
    struct pl0_ast_expression *arg;
    pl0_ast_arg(pair<int, int> loc, pl0_ast_expression *arg): loc(loc), arg(arg) {}
};
struct pl0_ast_addop {
    pair<int, int> loc;
    enum {
        ADD, MINUS
    } OP;
    char op;
    pl0_ast_addop(pair<int, int> loc, char const & op): loc(loc), op(op) {}
};
struct pl0_ast_multop {
    pair<int, int> loc;
    enum {
        MULT, DIV
    } OP;
    char op;
    pl0_ast_multop(pair<int, int> loc, char const & op): loc(loc), op(op) {}
};
struct pl0_ast_condtion {
    pair<int, int> loc;
    struct pl0_ast_expression *lhs;
    struct pl0_ast_comp_op *op;
    struct pl0_ast_expression *rhs;
    pl0_ast_condtion(pair<int, int> loc, pl0_ast_expression *lhs, pl0_ast_comp_op *op, pl0_ast_expression *rhs): loc(loc), lhs(lhs), op(op), rhs(rhs) {}
};
struct pl0_ast_comp_op {
    pair<int, int> loc;
    enum {
        LT, LE, GT, GE, EQ, NE
    } OP;
    string op;
    pl0_ast_comp_op(pair<int, int> loc, string const & op): loc(loc), op(op) {}
};
struct pl0_ast_cond_stmt: pl0_ast_stmt {
    struct pl0_ast_condtion *cond;
    struct pl0_ast_stmt *then_block, *else_block;
    pl0_ast_cond_stmt(pair<int, int> loc, pl0_ast_condtion *cond, pl0_ast_stmt *then_block, pl0_ast_stmt *else_block): pl0_ast_stmt(loc, pl0_ast_stmt::type_t::COND_STMT), cond(cond), then_block(then_block), else_block(else_block) {}
};
struct pl0_ast_case_stmt: pl0_ast_stmt {
    struct pl0_ast_expression *expr;
    std::vector<pl0_ast_case_term *> terms;
    pl0_ast_case_stmt(pair<int, int> loc, pl0_ast_expression *expr, std::vector<pl0_ast_case_term *> const & terms): pl0_ast_stmt(loc, pl0_ast_stmt::type_t::CASE_STMT), expr(expr), terms(terms) {}
};
struct pl0_ast_case_term {
    pair<int, int> loc;
    struct pl0_ast_constv *constv;
    struct pl0_ast_stmt *stmt;
    pl0_ast_case_term(pair<int, int> loc, pl0_ast_constv *constv, pl0_ast_stmt *stmt): loc(loc), constv(constv), stmt(stmt) {}
};
struct pl0_ast_for_stmt: pl0_ast_stmt {
    struct pl0_ast_identify *iter;
    struct pl0_ast_expression *initial, *end;
    struct pl0_ast_stmt *stmt;
    struct pl0_ast_constv *step;
    pl0_ast_for_stmt(pair<int, int> loc, pl0_ast_identify *iter, pl0_ast_expression *initial, pl0_ast_expression *end, pl0_ast_stmt *stmt, pl0_ast_constv *step): pl0_ast_stmt(loc, pl0_ast_stmt::type_t::FOR_STMT), iter(iter), initial(initial), end(end), stmt(stmt), step(step) {}
};
struct pl0_ast_call_proc: pl0_ast_stmt {
    struct pl0_ast_identify *id;
    struct pl0_ast_arg_list *args;
    pl0_ast_call_proc(pair<int, int> loc, pl0_ast_identify *id, pl0_ast_arg_list *args):  pl0_ast_stmt(loc, pl0_ast_stmt::type_t::CALL_PROC), id(id), args(args) {}
};
struct pl0_ast_compound_stmt: pl0_ast_stmt {
    std::vector<struct pl0_ast_stmt *> stmt;
    pl0_ast_compound_stmt(pair<int, int> loc, std::vector<struct pl0_ast_stmt *> const & stmt): pl0_ast_stmt(loc, pl0_ast_stmt::type_t::COMPOUND_STMT), stmt(stmt) {}
};
struct pl0_ast_read_stmt: pl0_ast_stmt {
    std::vector<struct pl0_ast_identify *> ids;
    pl0_ast_read_stmt(pair<int, int> loc, std::vector<struct pl0_ast_identify *> const & ids): pl0_ast_stmt(loc, pl0_ast_stmt::type_t::READ_STMT), ids(ids) {}
};
struct pl0_ast_write_stmt: pl0_ast_stmt {
    enum type_t {
        ONLY_STRING,
        ONLY_EXPR,
        STRING_AND_EXPR
    };
    type_t t;
    struct pl0_ast_charseq *str;
    struct pl0_ast_expression *expr;
    pl0_ast_write_stmt(pair<int, int> loc, pl0_ast_charseq *str): pl0_ast_stmt(loc, pl0_ast_stmt::type_t::WRITE_STMT), t(type_t::ONLY_STRING), str(str) {}
    pl0_ast_write_stmt(pair<int, int> loc, pl0_ast_expression *expr): pl0_ast_stmt(loc, pl0_ast_stmt::type_t::WRITE_STMT), t(type_t::ONLY_EXPR), expr(expr) {}
    pl0_ast_write_stmt(pair<int, int> loc, pl0_ast_charseq *str, pl0_ast_expression *expr): pl0_ast_stmt(loc, pl0_ast_stmt::type_t::WRITE_STMT), t(type_t::STRING_AND_EXPR), str(str), expr(expr) {}
};
struct pl0_ast_alnum {
    pair<int, int> loc;
    char val;
    pl0_ast_alnum(pair<int, int> loc, char val): loc(loc), val(val) {}
};

// TAC design
struct Value {
    enum TYPE { IMM, STR } t; // literal type: 1: immediate, 2: string.
    int iv;
    std::string sv, dt; // date type: 1: integer, 2: char.
    Value(int v, std::string dt): t(TYPE::IMM), iv(v), dt(dt) {};
    Value(std::string v, std::string dt): t(TYPE::STR), sv(v), dt(dt) {};
    std::string const str() const;
    bool operator == (Value const & v) const {
        bool res = t == v.t;
        if (res) {
            if (t == TYPE::IMM) {
                res = res && iv == v.iv;
            }
            else {
                res = res && sv == v.sv;
            }
        }
        return res;
    }
    bool operator < (Value const & other) const {
        return value() < other.value();
    }
    std::string value() const {
        if (this->t == TYPE::IMM) {
            return to_string(this->iv);
        }
        else {
            return this->sv;
        }
    }
};

struct TAC {
    std::string op;
    Value *rd, *rs, *rt;
    std::vector<pair<Value *, bool>> args;
    TAC(std::string op, Value *rd, vector<pair<Value *, bool>> & args, Value *rt = nullptr): op(op), rd(rd), rs(nullptr), rt(rt), args(args) {}
    TAC(std::string op, Value *rd, Value *rs = nullptr, Value *rt = nullptr): op(op), rd(rd), rs(rs), rt(rt) {}
    std::string str() const;
};

/* IR builder. */
struct IRBuilder {
public:
    int label = 0, tmp = 0, var = 0, ret = 0;
    std::vector<struct TAC> irs;
public:
    IRBuilder() {}
    void emitlabel(int label) { irs.emplace_back(TAC("label", new Value(label, "integer"))); }
    void emit(std::string op, Value *rd, Value *rs = nullptr, Value *rt = nullptr) { irs.emplace_back(TAC(op, rd, rs, rt)); }
    void emit(TAC c) { irs.emplace_back(c); }
    void emit(std::string op, std::string rd) { irs.emplace_back(TAC(op, new Value(rd, "string"))); }
    void emit(std::string op, std::string rd, std::string rdt, std::string rs, std::string rst) { irs.emplace_back(TAC(op, new Value(rd, rdt), new Value(rs, rst))); }
    void emit(std::string op, Value *rd, vector<pair<Value *, bool>> & args, Value *rt = nullptr) { irs.emplace_back(TAC(op, rd, args, rt)); }
    int makelabel();
    string const maketmp();
    string const makeret();
    void dump() const;
};

/* Symbol table */

// variable.
struct variable {
    std::string name;
    std::string dt, type;
    int len;
    variable(): name(""), dt(""), len(-1) {}
    variable(std::string, std::string dt, std::string type);
    variable(std::string, std::string dt, std::string type, int);
    std::string str() const {
        return string("variable ") + name + " " + type;
    }
};

// constant.
struct constant {
    std::string name;
    int val;
    std::string dt;
    constant(): name(""), val(0), dt("") {}
    constant(std::string, int, std::string dt);
    std::string str() const {
        return string("constant ") + name + " " + to_string(val) + " " + dt;
    }
};

// procedure.
struct proc {
    std::string name;
    std::vector<std::string> param_t;
    proc(): name("") {}
    proc(std::string, std::vector<std::string> &);
    std::string str() const {
        std::string res = name + " :: ";
        for (auto && p: param_t) {
            res = res + p + " -> ";
        }
        return res;
    }
};

// function.
struct func {
    std::string name, rettype;
    std::vector<std::string> param_t;
    func(): name(""), rettype("") {}
    func(std::string, std::string, std::vector<std::string> &);
    std::string str() const {
        std::string res = name + " :: ";
        for (auto && p: param_t) {
            res = res + p + " -> ";
        }
        return res + rettype;
    }
};

// location when generate assembly language code.
struct LOC {
    std::string name;
    std::string offset; // offset from variable's base address to ebp register.
    bool is_ref;
    bool in_mem; // true: in memory, false: in register;
    LOC(): name(""), offset(to_string(0x7fffffff)), is_ref(false), in_mem(false) {}
    LOC(string name, int offset, bool is_ref = false): name(name), is_ref(is_ref), in_mem(false) {
        this->offset = offset < 0 ? to_string(offset) : (string("+") + to_string(offset));
    }
    LOC(string name, std::string offset, bool is_ref = false): name(name), offset(offset), is_ref(is_ref), in_mem(false) {}
    std::string str() {
        return name + ": " + this->offset + " is_ref: " + to_string(is_ref) + " in_mem: " + to_string(in_mem);
    }
};

struct IOOut {
    string name = "out";
    void emit(string s) {
        cout << s << endl;
    }
    void emit(string s, TAC c) {
        cout << s << "\t\t;; " << c.str() << endl;
    }
};

template<typename T>
class pl0_env {
private:
    std::vector<T> tb;
    std::vector<int> tags;
public:
    pl0_env() { tags.emplace_back(0); }
    bool empty();
    bool find(std::string const &, bool);
    bool find(std::string const &, bool, T &);
    void push(T const &);
    void pop();
    void tag();
    void detag();
    int depth();
    int depth(std::string const &);
    void dump() {
        cout << ";; -----------------  Symbol Table  -------------------" << endl;
        for (auto && t: tb) {
            cout << ";; " << t.str() << endl;
        }
        cout << ";; -----------------------------------------------------" << endl;
    }
};

template<typename T>
bool pl0_env<T>::empty() { return this->tb.empty(); }

template<typename T>
bool pl0_env<T>::find(std::string const & name, bool cross, T & res) {
    if (this->empty()) { return false; }
    for (int i = this->tb.size()-1; i >= 0; --i) {
        if (!cross && i < this->tags.back()) {
            break;
        }
        if (this->tb[i].name == name || (this->tb[i].name.rfind('_') != this->tb[i].name.npos && this->tb[i].name.substr(this->tb[i].name.rfind('_')+1) == name)) {
            res = this->tb[i];
            return true;
        }
    }
    return false;
}

template<typename T>
bool pl0_env<T>::find(std::string const & name, bool cross) {
    if (this->empty()) { return false; }
    for (int i = this->tb.size()-1; i >= 0; --i) {
        if (!cross && i < this->tags.back()) {
            break;
        }
        if (this->tb[i].name == name || (this->tb[i].name.rfind('_') != this->tb[i].name.npos && this->tb[i].name.substr(this->tb[i].name.rfind('_')+1) == name)) {
            return true;
        }
    }
    return false;
}

template<typename T>
void pl0_env<T>::push(T const & e) { this->tb.emplace_back(e); }

template<typename T>
void pl0_env<T>::pop() { this->tb.pop_back(); }

template<typename T>
void pl0_env<T>::tag() { this->tags.emplace_back(this->tb.size()); }

template<typename T>
void pl0_env<T>::detag() {
    while (tb.size() > (size_t)tags.back()) { tb.pop_back(); }
    tags.pop_back();
}

template<typename T>
int pl0_env<T>::depth() {
    return this->tags.size()-1;
}

template<typename T>
int pl0_env<T>::depth(std::string const & name) {
    if (tb.empty()) { return -1; } // doesn't exist.
    for (int i = this->tb.size()-1; i >= 0; --i) {
        if (this->tb[i].name == name || (this->tb[i].name.rfind('_') != this->tb[i].name.npos && this->tb[i].name.substr(this->tb[i].name.rfind('_')+1) == name)) {
            for (int j = this->tags.size()-1; j >= 0; --j) {
                if (i >= this->tags[j]) {
                    return j;
                }
            }
        }
    }
    return -1; // NOT FOUND
}

#endif /* __PL0_AST_HPP__ */


