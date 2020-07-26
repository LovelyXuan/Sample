#pragma once



enum ConditionOp
{
	E_ConditionOp_AND,
	E_ConditionOp_OR,
};

enum ConditionType
{
	E_ConditionType_UNARY,
	E_ConditionType_BINARY,
};

struct ConditionBase 
{
	ConditionBase()
		: type(E_ConditionType_UNARY)
		, op(E_ConditionOp_AND)
		, pNext(nullptr)
	{

	}

	virtual ~ConditionBase() = 0;

	ConditionType type;
	ConditionOp op;
	ConditionBase* pNext;
};

inline ConditionBase::~ConditionBase()
{
	delete pNext;
}

struct ConditionUnary : public ConditionBase
{
	ConditionUnary() : id(0)
	{
		type = E_ConditionType_UNARY;
	}

	int id;
};

struct ConditionBinary : public ConditionBase 
{
	ConditionBinary() : pSibling(nullptr)
	{
		type = E_ConditionType_BINARY;
	}

	virtual ~ConditionBinary()
	{
		delete pSibling;
	}

	ConditionBase* pSibling;
};



