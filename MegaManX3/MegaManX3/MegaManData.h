#pragma once
#ifndef __MEGAMANDATA__H__
#define __MEGAMANDATA__H__

class MegaManCharacters;
class MegaManState;

class MegaManData
{
public:
	MegaManData();
	~MegaManData();

	MegaManCharacters* megaMan;
	MegaManState* megaManState;
};

#endif // !__MEGAMANDATA__H__