#include "Condition.h"
#include <assert.h>
#include <stack>
#include <map>

static std::map<int, ConditionBase*> sConditions;


void ParseFormula(ConditionBase* pCondition, const char* pSrc = "(100&101|(102&103)&(104|(105&106)))")
{
	size_t len = ::strlen(pSrc) + 1;
	char* p = new char[len];
	::memcpy(p, pSrc, len);
	char* q = p;

	std::stack<ConditionBase**> stk;
	ConditionBase** pCond = &pCondition;
	char c;
	int nId;

	while (*p)
	{
		if (*p == '(')
		{
			ConditionBinary* pBinary = new ConditionBinary;
			stk.push(pCond);
			(*pCond)->pNext = pBinary;
			pCond = &pBinary->pSibling;
		}
		else if (*p == ')')
		{
			pCond = stk.top();
			stk.pop();
		}
		else if (*p == '&')
		{
			(*pCond)->op = E_ConditionOp_AND;
			pCond = &(*pCond)->pNext;
		}
		else if (*p == '|')
		{
			(*pCond)->op = E_ConditionOp_OR;
			pCond = &(*pCond)->pNext;
		}
		else if (*p >= '0' && *p <= '9')
		{
			q = p;
			while (++p && *p >= '0' && *p <= '9');
			c = *p;
			*p = 0;
			nId = ::atoi(q);
			*p = c;
			--p;

			ConditionUnary* pUnary = new ConditionUnary;
			pUnary->id = nId;
			(*pCond)->pNext = pUnary;
			pCond = &(*pCond)->pNext;
		}
		else
		{
			assert(false);
		}
	}

	delete[] p;
	assert(stk.empty());
}

bool Check(int id)
{
	return rand() % 100 >= 50;
}

void InnerCheck(const ConditionBase* pCondition, std::stack<ConditionBase*>& stk, bool& bRet, ConditionOp op)
{
	if (pCondition == nullptr)
	{
		return;
	}

	bool ret = false;
	int type = pCondition->type;

	if (type == E_ConditionType_UNARY)
	{
		const ConditionUnary* pUnary = dynamic_cast<const ConditionUnary*>(pCondition);
		if (pUnary == nullptr)
		{
			assert(false);
			return;
		}

		ret = Check(pUnary->id);
	}
	else
	{
		const ConditionBinary* pBinary = dynamic_cast<const ConditionBinary*>(pCondition);
		if (pBinary == nullptr)
		{
			assert(false);
			return;
		}

		InnerCheck(pBinary->pSibling, stk, ret, E_ConditionOp_AND);
	}

	if (op == E_ConditionOp_AND)
	{
		bRet = bRet && ret;
	}
	else
	{
		bRet = bRet || ret;
	}

	// check if can jump next
	while (pCondition->pNext != nullptr &&
		((ret && (pCondition->op == E_ConditionOp_OR))
		|| (!ret && (pCondition->op == E_ConditionOp_AND))))
	{
		pCondition = pCondition->pNext;
	}

	if (pCondition->pNext != nullptr)
	{
		InnerCheck(pCondition->pNext, stk, bRet, pCondition->op);
	}
	
}

bool CheckCondition(ConditionBase* pCondition)
{
	const ConditionBase* pCond = pCondition;
	std::stack<ConditionBase*> stk;
	bool bRet = false;

	InnerCheck(pCondition, stk, bRet, E_ConditionOp_AND);
	return bRet;
}

void TestCondition()
{

}