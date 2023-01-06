#pragma once

#include "framework.h"

#include "CString.h"

class CLinkListNode
{
public:

	CLinkListNode* previous;
	CLinkListNode* next;

	CString* key;

	int ikey;

	bool deleteMe;

	void* element;

	CLinkListNode();

	~CLinkListNode();
};
