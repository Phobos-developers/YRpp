#ifndef DCODER_H
#define DCODER_H

#include <hash_map>
// macros DCoder uses and pd dislikes :)

// for exportfuncs, repeating stuff is annoying :P
#define GET(clsname, var, reg) clsname var = (clsname )R->get_ ## reg ();

#define RET_UNLESS(expr) if(!(expr)) { return 0; }
#define RETZ_UNLESS(expr) if(!(expr)) { return ; }

// please don't mix the two hashmaps in one class

// hashmap of pointers
#define EXT_P_DEFINE(clsname) \
	static stdext::hash_map<clsname*, clsname ## Data*> Ext_p; \

#define EXT_P_DECLARE(clsname) \
	typedef stdext::hash_map<clsname*, clsname ## Ext::clsname ## Data*> hashext_p; \
	typedef clsname ## Ext::clsname ## Data ExtData;    \
	hashext_p clsname ## Ext :: Ext_p;

#define EXT_CTOR(clsname) \
	void __stdcall clsname ## Ext::Create(clsname* pThis)

#define EXT_DTOR(clsname) \
	void __stdcall clsname ## Ext::Delete(clsname* pThis)

#define EXT_LOAD(clsname) \
	void __stdcall clsname ## Ext::Load(clsname* pThis, IStream* pStm)

#define EXT_SAVE(clsname) \
	void __stdcall clsname ## Ext::Save(clsname* pThis, IStream* pStm)

#define EXT_LOAD_INI(clsname) \
	void __stdcall clsname ## Ext::LoadFromINI(clsname* pThis, CCINIClass* pINI)

// hashmap of structures
#define EXT_V_DEFINE(clsname) \
	static stdext::hash_map<clsname*, clsname ## Data > Ext_v;\

#define EXT_V_DECLARE(clsname) \
	typedef stdext::hash_map<clsname*, clsname ## Ext::clsname ## Data > hashext_v; \
	typedef clsname ## Ext::clsname ## Data ExtData;    \
	hashext_v clsname ## Ext :: Ext_v;

#define EXT_FUNCS(clsname) \
	static void __stdcall Create(clsname*);                    \
	static void __stdcall Delete(clsname*);                    \
	static void __stdcall Load(clsname*, IStream*);            \
	static void __stdcall Save(clsname*, IStream*);

#define EXT_INI_FUNCS(clsname) \
	static void __stdcall LoadFromINI(clsname*, CCINIClass*);

#define BIND_CALLBACKS(clsname) \
		clsname ## Callback::Create		=	clsname ## Ext::Create;          \
		clsname ## Callback::Delete		=	clsname ## Ext::Delete;          \
		clsname ## Callback::Load			=	clsname ## Ext::Load;            \
		clsname ## Callback::Save			=	clsname ## Ext::Save;

#define BIND_INI_CALLBACKS(clsname) \
		clsname ## Callback::LoadFromINI	=	clsname ## Ext::LoadFromINI;

// I'm lazy, so sue me
#define CONTAINS(var, ptr) \
	(var.find(ptr) != var.end())

#define ALLOC(clsname, ptr) \
	clsname *ptr = new clsname();

#define DEALLOC(var, ptr) \
	delete var[ptr]; \
	var.erase(var.find(ptr));

#define ARRAY_ITERATE(clsname, pINI) \
	if(clsname ## Callback::LoadFromINI) {                                   \
		for(int i = 0; i < clsname::Array->get_Count(); ++i) {                 \
			clsname ## Callback::LoadFromINI(clsname::Array->GetItem(i), pINI);  \
		} \
	}

// parse ini faster! harder! stronger!

#define PARSE_BUF() \
	char buffer[256];

/*
 * warning: all further funcs depend on
 * const char *section = <section_name_to_read_from>
 * being declared. Since you are not supposed to read from a gajillion sections at once, deal with it.
 */

// find items
#define PARSE_VAR_OBJ(key, var, cls) \
	if(pINI->ReadString(section, key, "", buffer, 256) > 0) \
		var = cls::Find(buffer);

#define PARSE_WH(key, var) \
	PARSE_VAR_OBJ(key, var, WarheadTypeClass);

#define PARSE_WEAP(key, var) \
	PARSE_VAR_OBJ(key, var, WeaponTypeClass);

#define PARSE_TECHNO(key, var) \
	PARSE_VAR_OBJ(key, var, TechnoTypeClass);

#define PARSE_AIRCRAFT(key, var) \
	PARSE_VAR_OBJ(key, var, AircraftTypeClass);

#define PARSE_VEHICLE(key, var) \
	PARSE_VAR_OBJ(key, var, UnitTypeClass);

#define PARSE_INFANTRY(key, var) \
	PARSE_VAR_OBJ(key, var, InfantryTypeClass);

#define PARSE_BUILDING(key, var) \
	PARSE_VAR_OBJ(key, var, BuildingTypeClass);

#define PARSE_ANIM(key, var) \
	PARSE_VAR_OBJ(key, var, AnimTypeClass);

#define PARSE_SW(key, var) \
	PARSE_VAR_OBJ(key, var, SuperWeaponTypeClass);


// find indices
#define PARSE_VAR_IDX(key, var, cls) \
	if(pINI->ReadString(section, key, "", buffer, 256) > 0) \
		var = cls::FindIndex(buffer);

#define PARSE_SND(key, var) \
	PARSE_VAR_IDX(key, var, VocClass);

#define PARSE_EVA(key, var) \
	PARSE_VAR_IDX(key, var, VoxClass);

#define PARSE_WH_IDX(key, var) \
	PARSE_VAR_IDX(key, var, WarheadTypeClass);

#define PARSE_WEAP_IDX(key, var) \
	PARSE_VAR_IDX(key, var, WeaponTypeClass);

#define PARSE_TECHNO_IDX(key, var) \
	PARSE_VAR_IDX(key, var, TechnoTypeClass);

#define PARSE_AIRCRAFT_IDX(key, var) \
	PARSE_VAR_IDX(key, var, AircraftTypeClass);

#define PARSE_VEHICLE_IDX(key, var) \
	PARSE_VAR_IDX(key, var, UnitTypeClass);

#define PARSE_INFANTRY_IDX(key, var) \
	PARSE_VAR_IDX(key, var, InfantryTypeClass);

#define PARSE_BUILDING_IDX(key, var) \
	PARSE_VAR_IDX(key, var, BuildingTypeClass);

#define PARSE_ANIM_IDX(key, var) \
	PARSE_VAR_IDX(key, var, AnimTypeClass);

#define PARSE_SW_IDX(key, var) \
	PARSE_VAR_IDX(key, var, SuperWeaponTypeClass);

// read colors
#define PARSE_COLOR(key, var, buf) \
		buf = var; \
		pINI->ReadColor(&buf, section, key, &var); \
		var = buf;

// swizzle shorthand
#define SWIZZLE(var) \
	SwizzleManagerClass::SwizzleManager()->Swizzle((void **)&var);

#endif
