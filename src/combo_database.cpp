#include "combo_database.hpp"

#include "combo_serializer.hpp"

bool ComboDatabase::fetch(std::istream &stream)
{
	std::vector<Combo> combos;

	if(!ComboSerializer(database_).deserialize(stream, combos))
		return false;

	// TODO

	return true;
}
