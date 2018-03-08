#pragma once
#include "../FactoryTemplate.hpp"
#include "entity.h"

struct BFactory: public FactoryTemplate<B>{
	using parent_t = FactoryTemplate<B>;

	static void init();
};

