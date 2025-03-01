/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "lua/functions/items/imbuement_functions.hpp"

#include "items/weapons/weapons.hpp"
#include "creatures/players/imbuements/imbuements.hpp"

int ImbuementFunctions::luaCreateImbuement(lua_State* L) {
	// Imbuement(id)
	const uint16_t imbuementId = getNumber<uint16_t>(L, 2);
	Imbuement* imbuement = g_imbuements().getImbuement(imbuementId);

	if (imbuement) {
		pushUserdata<Imbuement>(L, imbuement);
		setMetatable(L, -1, "Imbuement");
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ImbuementFunctions::luaImbuementGetName(lua_State* L) {
	// imbuement:getName()
	const auto* imbuement = getUserdata<Imbuement>(L, 1);
	if (imbuement) {
		pushString(L, imbuement->getName());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ImbuementFunctions::luaImbuementGetId(lua_State* L) {
	// imbuement:getId()
	const auto* imbuement = getUserdata<Imbuement>(L, 1);
	if (imbuement) {
		lua_pushnumber(L, imbuement->getID());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ImbuementFunctions::luaImbuementGetItems(lua_State* L) {
	// imbuement:getItems()
	const auto* imbuement = getUserdata<Imbuement>(L, 1);
	if (!imbuement) {
		lua_pushnil(L);
		return 1;
	}

	const auto items = imbuement->getItems();

	lua_createtable(L, items.size(), 0);
	for (const auto &itm : items) {
		lua_createtable(L, 0, 2);
		setField(L, "itemid", itm.first);
		setField(L, "count", itm.second);
		lua_rawseti(L, -2, itm.first);
	}

	return 1;
}

int ImbuementFunctions::luaImbuementGetBase(lua_State* L) {
	// imbuement:getBase()
	const auto* imbuement = getUserdata<Imbuement>(L, 1);
	if (!imbuement) {
		lua_pushnil(L);
		return 1;
	}

	const BaseImbuement* baseImbuement = g_imbuements().getBaseByID(imbuement->getBaseID());
	if (!baseImbuement) {
		lua_pushnil(L);
		return 1;
	}

	lua_createtable(L, 0, 7);
	setField(L, "id", baseImbuement->id);
	setField(L, "name", baseImbuement->name);
	setField(L, "price", baseImbuement->price);
	setField(L, "protection", baseImbuement->protectionPrice);
	setField(L, "percent", baseImbuement->percent);
	setField(L, "removeCost", baseImbuement->removeCost);
	setField(L, "duration", baseImbuement->duration);
	return 1;
}

int ImbuementFunctions::luaImbuementGetCategory(lua_State* L) {
	// imbuement:getCategory()
	const auto* imbuement = getUserdata<Imbuement>(L, 1);
	if (!imbuement) {
		lua_pushnil(L);
		return 1;
	}
	const uint16_t categoryId = imbuement->getCategory();
	const CategoryImbuement* categoryImbuement = g_imbuements().getCategoryByID(categoryId);

	if (categoryImbuement) {
		lua_createtable(L, 0, 2);
		setField(L, "id", categoryImbuement->id);
		setField(L, "name", categoryImbuement->name);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int ImbuementFunctions::luaImbuementIsPremium(lua_State* L) {
	// imbuement:isPremium()
	const auto* imbuement = getUserdata<Imbuement>(L, 1);
	if (!imbuement) {
		lua_pushnil(L);
		return 1;
	}

	pushBoolean(L, imbuement->isPremium());
	return 1;
}

int ImbuementFunctions::luaImbuementGetElementDamage(lua_State* L) {
	// imbuement:getElementDamage()
	const auto* imbuement = getUserdata<Imbuement>(L, 1);
	if (imbuement) {
		lua_pushnumber(L, imbuement->elementDamage);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ImbuementFunctions::luaImbuementGetCombatType(lua_State* L) {
	// imbuement:getCombatType()
	const auto* imbuement = getUserdata<Imbuement>(L, 1);
	if (imbuement) {
		lua_pushnumber(L, imbuement->combatType);
	} else {
		lua_pushnil(L);
	}
	return 1;
}
