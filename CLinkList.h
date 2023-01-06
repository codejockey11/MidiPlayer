#pragma once

#include "framework.h"

#include "CLinkListNode.h"
#include "CString.h"

class CLinkList
{
public:

	CLinkListNode* list;

	int count;

	CLinkList();

	~CLinkList();

	void Clear();

	void Add(void* n, const char* k);

	void Add(void* n, int k);

	CLinkListNode* Delete(CLinkListNode* n);

	CLinkListNode* Search(const CHAR* k);

	CLinkListNode* Search(int k);
};
