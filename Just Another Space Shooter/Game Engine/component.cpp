#include "component.h"
#include <stdio.h>


component::component(unsigned int mtype)
{
	mpowner = NULL;
	this->mtype = mtype;
}


component::~component()
{
}

