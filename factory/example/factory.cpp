#include "factory.h"
#include "entity.h"

using namespace std;

using parent_t = BFactory::parent_t;

template <>
const std::string parent_t::optName("test");
template <>
const std::string parent_t::usagePrefix("");

template <>
std::map<std::string, parent_t::createFun> parent_t::contGen{};
template <>
std::map<std::string, std::string> parent_t::contUsage{};


void BFactory::init()
{
	// TODO: register classes here
	registerClass<D1>("D1");
	registerClass<D2>("D2");
}

