#pragma once
#ifndef __BOSSFINALDATA__H__
#define __BOSSFINALDATA__H__

class BossFinal;
class BossFinalState;

class BossFinalData
{
public:
	BossFinalData();
	~BossFinalData();

	BossFinal* bossFinal;
	BossFinalState* bossFinalState;

};

#endif // !__BOSSFINALDATA__H__
