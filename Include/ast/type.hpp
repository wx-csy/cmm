#include "common.h"

struct Statement {

};

struct ExprStatement : Statement {
    Expression expr;
};

struct CompoundStatement : Statement {
    vector<Variable> localvars;
    std::vector<Statement> statements;
};

struct ReturnStatement : Statement {
    
};

struct IfThenStatement : Statement {

};

struct IfThenElseStatement : Statement {

};

struct WhileStatement : Statement {

};


struct Type {
    int id;
    size_t size;
    std::string name;
};

struct Variable {
    std::string name;
    Type &type;
};

struct Structure : Type {
    vector<Variable> members;
};

struct Function {
    std::string name;
    vector<Variable> arglist;
    CompoundStatement statements;
};

extern std::unordered_map<std::string,
    std::variant<
        std::reference_wrapper<Variable>,
        std::reference_wrapper<Function>,
        std::reference_wrapper<Type>
    >> symtbl;

extern std::vector<Function> functions;
extern std::vector<Type> types;

