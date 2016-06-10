#ifndef CLASSES_GRINGO_HPP
#define CLASSES_GRINGO_HPP

#include <map>
#include <string.h>

using namespace std;

class Node {
public:
	virtual void accept(class Visitor *) = 0;
};

class Program : public Node {};

class ExpList : public Program {};

class Command : public ExpList {};

class IfElseIf : public Command{};

class Exp : public Command {};

class BinExpEqualDiff : public Exp {};

class BinExpLessGreater : public Exp {};

class BinExpPlusMinus : public Exp {};

class Factor: public Exp {};

class UnExp: public Factor {};

class Value : public UnExp {
public:
	enum Type {
		INT,
		DOUBLE,
		ID_VALUE
	};
	
	virtual Type getType() = 0;		 
private:
	Type type;
};

class Commands : public ExpList{
private:
	ExpList *expList;
	Command *command;
public:
	Commands(ExpList *eList, Command *c) : expList(eList), command(c){}	
	ExpList *getExpList();
	Command *getCommand();		
	void accept(Visitor *);	
};

class If: public IfElseIf{
private:
	Exp *exp;
	ExpList *expList;
public:
	If(Exp *e, ExpList *eList): exp(e), expList(eList){}
	Exp *getExp();
	ExpList *getExpList();
	void accept(Visitor *);
};

class IfElse: public IfElseIf{
private:
	Exp *exp;
	ExpList *expList;
	ExpList *expList_2;
public:
	IfElse(Exp *e, ExpList *eList, ExpList *eList_2): exp(e), expList(eList), expList_2(eList_2){}
	Exp *getExp();
	ExpList *getExpList();
	ExpList *getExpList_2();
	void accept(Visitor *);
};

class While: public Command {
private:
	Exp *exp;
	ExpList *expList;
public:
	While(Exp *e, ExpList *eList) : exp(e), expList(eList){}
	Exp *getExp();
	ExpList *getExpList();
	void accept(Visitor *);
};

class BinExpPlus: public BinExpPlusMinus {
private:
	Exp *exp;
	Factor *factor;

public:
	BinExpPlus(Exp *e, class Factor *f): exp(e), factor(f){} //construtor
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *);
};

class BinExpMinus: public BinExpPlusMinus {
private:
	Exp *exp;
	Factor *factor;
public:
	BinExpMinus(Exp *e,  class Factor *f): exp(e), factor(f){} //construtor
	Exp *getExp ();
	Factor *getFactor();
	void accept(Visitor *);
};

class BinExpLessThen : public BinExpLessGreater {
private:
	Exp *exp;
	Factor *factor;
public:
	BinExpLessThen(Exp *e, class Factor *f): exp(e), factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpLessEqualThen : public BinExpLessGreater {
private:
	Exp *exp;
	Factor *factor;
public:
	BinExpLessEqualThen(Exp *e, class Factor *f): exp(e), factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpGreaterThen : public BinExpLessGreater {
private:
	Exp *exp;
	Factor *factor;
public:
	BinExpGreaterThen(Exp *e, class Factor *f): exp(e), factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpGreaterEqualThen : public BinExpLessGreater {
private:
	Exp *exp;
	Factor *factor;
public:
	BinExpGreaterEqualThen(Exp *e, class Factor *f): exp(e), factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpEqual : public BinExpEqualDiff {
private:
	Exp *exp;
	Factor *factor;
public:
	BinExpEqual(Exp *e, class Factor *f): exp(e), factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpDiff : public BinExpEqualDiff {
private:
	Exp *exp;
	Factor *factor;
public:
	BinExpDiff(Exp *e, class Factor *f): exp(e), factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
};

class FactorMul: public Factor {
private:
	Factor *factor;
	UnExp *unExp;
public:
	FactorMul(Factor *f, UnExp *ue): factor(f), unExp(ue){} //construtor
	Factor *getFactor();
	UnExp *getUnExp();
	void accept(Visitor *);
};

class FactorDiv: public Factor {
private:
	Factor *factor;
	UnExp *unExp;
public:
	FactorDiv(Factor *f, UnExp *ue): factor(f), unExp(ue){} //construtor
	Factor *getFactor();
	UnExp *getUnExp();
	void accept(Visitor *);
};

class UnExpPlus : public UnExp {
private:	
	Value *value;
public:
	UnExpPlus(Value *v): value(v){} //construtor
	Value *getValue();
	void accept(Visitor *);
};

class UnExpMinus : public UnExp {
private:
	Value *value;
public:
	UnExpMinus(Value *v): value(v){} //construtor
	Value *getValue();
	void accept(Visitor *);
};

class UnExpLog : public UnExp {
private:
	Exp *exp;
public:
	UnExpLog(Exp *e): exp(e){} //construtor
	Exp *getExp();
	void accept(Visitor *);
};

class UnExpExp: public UnExp {
private:
	Exp *exp;
public:
	UnExpExp(Exp *e): exp(e){} //construtor
	Exp *getExp();
	void accept(Visitor *);
};

class IntValue: public Value {
private:
	int value;
public:
	IntValue(int value):value(value){} //construtor
	int getValue();
	virtual Type getType();
	void accept(Visitor *);
};

class DoubleValue: public Value {
private:
	double value;
public:
	DoubleValue(double value):value(value){} //construtor
	double getValue();
	virtual Type getType();
	void accept(Visitor *v);
};


class IdValue: public Value {
private:
	char *idValue;
public:
	IdValue(char *idvalue){ idValue = strdup(idvalue); } //construtor
	char *getValue();
	virtual Type getType();
	void accept(Visitor *);
};

class LparExpRpar : public UnExp {
private:
	Exp *exp;
public:
	LparExpRpar(Exp *e) : exp(e){} //construtor
	Exp *getExp();
	void accept(Visitor *);
};

class Assignment : public Command {
private:
	Exp *exp;
	IdValue *idValue;
public:
	Assignment(IdValue *id, Exp *e) : idValue(id), exp(e){} //construtor
	Exp *getExp();
	IdValue	*getIdValue();
	void accept(Visitor *);
}; 


class Context {
private:
	static Context *instance;
	Program *program;
	Context(){} //construtor	
public:
	typedef map<char *, Value *> TypeTable;
	static Context &getContext();
	
	TypeTable &getTable();
	void setProgram(Program *prog);
	Program *getProgram();
private:
	TypeTable table;	
};

#endif
