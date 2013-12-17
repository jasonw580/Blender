/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Contributor(s): Lukas Toenne
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file blender/makesrna/intern/rna_nparticle.c
 *  \ingroup RNA
 */

#include "DNA_nparticle_types.h"

#include "RNA_define.h"

#include "rna_internal.h"

#ifdef RNA_RUNTIME

#include "MEM_guardedalloc.h"

#include "BLI_listbase.h"
#include "BLI_math.h"
#include "BLI_pagedbuffer.h"

#include "BKE_nparticle.h"
#include "BKE_report.h"

#include "RNA_access.h"

static StructRNA *rna_NParticleAttributeState_refine(PointerRNA *ptr)
{
	NParticleAttributeState *attrstate = ptr->data;
	switch (attrstate->desc.datatype) {
		case PAR_ATTR_DATATYPE_FLOAT:
			return &RNA_NParticleAttributeStateFloat;
		case PAR_ATTR_DATATYPE_INT:
			return &RNA_NParticleAttributeStateInt;
		case PAR_ATTR_DATATYPE_BOOL:
			return &RNA_NParticleAttributeStateBool;
		case PAR_ATTR_DATATYPE_VECTOR:
			return &RNA_NParticleAttributeStateVector;
		case PAR_ATTR_DATATYPE_POINT:
			return &RNA_NParticleAttributeStatePoint;
		case PAR_ATTR_DATATYPE_NORMAL:
			return &RNA_NParticleAttributeStateNormal;
		case PAR_ATTR_DATATYPE_COLOR:
			return &RNA_NParticleAttributeStateColor;
		case PAR_ATTR_DATATYPE_MATRIX:
			return &RNA_NParticleAttributeStateMatrix;
		
		default:
			BLI_assert(false);	/* unknown data type, should never happen */
			return &RNA_NParticleAttributeState;
	}
}

static void rna_NParticleAttribute_datatype_set(PointerRNA *ptr, int value)
{
//	NParticleAttribute *attr = ptr->data;
	/* XXX TODO */
	BLI_assert(false);
}

static void rna_NParticleAttributeState_data_begin(CollectionPropertyIterator *iter, PointerRNA *ptr)
{
	NParticleAttributeState *state = ptr->data;
	bPagedBufferIterator *internal = MEM_callocN(sizeof(bPagedBufferIterator), "particle data iterator");
	BLI_pbuf_iter_init(&state->data, internal);
	
	iter->internal = internal;
	iter->valid = BLI_pbuf_iter_valid(&state->data, internal);
}

static void rna_NParticleAttributeState_data_next(CollectionPropertyIterator *iter)
{
	NParticleAttributeState *state = iter->ptr.data;
	bPagedBufferIterator *internal = iter->internal;
	BLI_pbuf_iter_next(&state->data, internal);
	iter->valid = BLI_pbuf_iter_valid(&state->data, internal);
}

static void rna_NParticleAttributeState_data_end(CollectionPropertyIterator *iter)
{
	MEM_freeN(iter->internal);
	iter->internal = NULL;
}

static PointerRNA rna_NParticleAttributeState_data_get(CollectionPropertyIterator *iter, StructRNA *data_srna)
{
	bPagedBufferIterator *internal = iter->internal;
	PointerRNA ptr;
	RNA_pointer_create(iter->ptr.id.data, data_srna, internal->data, &ptr);
	return ptr;
}

static int rna_NParticleAttributeState_data_length(PointerRNA *ptr)
{
	NParticleAttributeState *state = ptr->data;
	return state->data.totelem;
}

int rna_NParticleAttributeState_data_lookup_int(PointerRNA *ptr, int key, PointerRNA *r_ptr, StructRNA *data_srna)
{
	NParticleAttributeState *state = ptr->data;
	void *data = BLI_pbuf_get(&state->data, key);
	RNA_pointer_create(ptr->id.data, data_srna, data, r_ptr);
	return data != NULL;
}

int rna_NParticleAttributeState_data_assign_int(PointerRNA *ptr, int key, const PointerRNA *assign_ptr, StructRNA *data_srna)
{
	NParticleAttributeState *state = ptr->data;
	void *data = BLI_pbuf_get(&state->data, key);
	if (data) {
		memcpy(data, assign_ptr->data, state->data.elem_bytes);
		return true;
	}
	else
		return false;
}

#define DEF_ATTR_TYPE_FUNCS(lcase, ucase) \
static PointerRNA rna_NParticleAttributeState_data_get_##lcase (CollectionPropertyIterator *iter) \
{ return rna_NParticleAttributeState_data_get(iter, &RNA_NParticleData##ucase); } \
static int rna_NParticleAttributeState_data_lookup_int_##lcase (PointerRNA *ptr, int key, PointerRNA *r_ptr) \
{ return rna_NParticleAttributeState_data_lookup_int(ptr, key, r_ptr, &RNA_NParticleData##ucase); } \
static int rna_NParticleAttributeState_data_assign_int_##lcase (PointerRNA *ptr, int key, const PointerRNA *assign_ptr) \
{ return rna_NParticleAttributeState_data_assign_int(ptr, key, assign_ptr, &RNA_NParticleData##ucase); }

DEF_ATTR_TYPE_FUNCS(float, Float)
DEF_ATTR_TYPE_FUNCS(int, Int)
DEF_ATTR_TYPE_FUNCS(bool, Bool)
DEF_ATTR_TYPE_FUNCS(vector, Vector)
DEF_ATTR_TYPE_FUNCS(point, Point)
DEF_ATTR_TYPE_FUNCS(normal, Normal)
DEF_ATTR_TYPE_FUNCS(color, Color)
DEF_ATTR_TYPE_FUNCS(matrix, Matrix)

#undef DEF_ATTR_TYPE_FUNCS

static float rna_NParticleDataFloat_get(PointerRNA *ptr)
{
	return *(float *)ptr->data;
}

static void rna_NParticleDataFloat_set(PointerRNA *ptr, float value)
{
	*(float *)ptr->data = value;
}

static int rna_NParticleDataInt_get(PointerRNA *ptr)
{
	return *(int *)ptr->data;
}

static void rna_NParticleDataInt_set(PointerRNA *ptr, int value)
{
	*(int *)ptr->data = value;
}

static int rna_NParticleDataBool_get(PointerRNA *ptr)
{
	return *(bool *)ptr->data;
}

static void rna_NParticleDataBool_set(PointerRNA *ptr, int value)
{
	*(bool *)ptr->data = value;
}

static void rna_NParticleDataVector_get(PointerRNA *ptr, float *result)
{
	copy_v3_v3(result, (float *)ptr->data);
}

static void rna_NParticleDataVector_set(PointerRNA *ptr, const float *value)
{
	copy_v3_v3((float *)ptr->data, value);
}

static void rna_NParticleDataColor_get(PointerRNA *ptr, float *result)
{
	copy_v4_v4(result, (float *)ptr->data);
}

static void rna_NParticleDataColor_set(PointerRNA *ptr, const float *value)
{
	copy_v4_v4((float *)ptr->data, value);
}

static void rna_NParticleDataMatrix_get(PointerRNA *ptr, float *result)
{
	copy_m4_m4((float(*)[4])result, (float(*)[4])ptr->data);
}

static void rna_NParticleDataMatrix_set(PointerRNA *ptr, const float *value)
{
	copy_m4_m4((float(*)[4])ptr->data, (float(*)[4])value);
}


static void rna_NParticleState_attributes_begin(CollectionPropertyIterator *iter, PointerRNA *ptr)
{
	NParticleState *state = ptr->data;
	NParticleAttributeState *attrstate = state->attributes.first;
	
	iter->internal = attrstate;
	iter->valid = (attrstate != NULL);
}

static void rna_NParticleState_attributes_next(CollectionPropertyIterator *iter)
{
	NParticleAttributeState *attrstate = iter->internal;
	
	attrstate = attrstate->next;
	
	iter->internal = attrstate;
	iter->valid = (attrstate != NULL);
}

static void rna_NParticleState_attributes_end(CollectionPropertyIterator *iter)
{
	iter->internal = NULL;
}

static PointerRNA rna_NParticleState_attributes_get(CollectionPropertyIterator *iter)
{
	NParticleAttributeState *attrstate = iter->internal;
	PointerRNA ptr;
	RNA_pointer_create(iter->ptr.id.data, &RNA_NParticleAttributeState, attrstate, &ptr);
	return ptr;
}

static int rna_NParticleState_attributes_length(PointerRNA *ptr)
{
	NParticleState *state = ptr->data;
	return BLI_countlist(&state->attributes);
}

int rna_NParticleState_attributes_lookup_string(PointerRNA *ptr, const char *key, PointerRNA *r_ptr)
{
	NParticleState *state = ptr->data;
	NParticleAttributeState *attrstate = BKE_nparticle_state_find_attribute(state, key);
	RNA_pointer_create(ptr->id.data, &RNA_NParticleAttributeState, attrstate, r_ptr);
	return attrstate != NULL;
}


#if 0
static void rna_NParticleState_particles_begin(CollectionPropertyIterator *iter, PointerRNA *ptr)
{
	NParticleState *state = ptr->data;
	NParticleIterator *piter = MEM_callocN(sizeof(NParticleIterator), "particle iterator");
	
	BKE_nparticle_iter_init(state, piter);
	iter->internal = piter;
	iter->valid
}

static void rna_NParticleState_particles_next(CollectionPropertyIterator *iter)
{
	NParticleState *state = iter->ptr.data;
	NParticleIterator *piter = iter->internal;
	BKE_nparticle_iter_next(piter);
	iter->valid = BKE_nparticle_iter_valid(piter);
}

static void rna_NParticleState_particles_end(CollectionPropertyIterator *iter)
{
	MEM_freeN(iter->internal);
	iter->internal = NULL;
}

static PointerRNA rna_NParticleState_particles_get(CollectionPropertyIterator *iter)
{
	NParticleIterator *piter = iter->internal;
	PointerRNA ptr;
	RNA_pointer_create(iter->ptr.id.data, &RNA_NParticleIterator, piter, &ptr);
	return ptr;
}

static int rna_NParticleState_particles_length(PointerRNA *ptr)
{
	NParticleState *state = ptr->data;
	NParticleAttributeState *attrstate = BKE_nparticle_state_find_attribute(state, "id");
	if (attrstate)
		return attrstate->data.totelem;
	else
		return 0;
}

int rna_NParticleState_particles_lookup_int(PointerRNA *ptr, int key, PointerRNA *r_ptr)
{
	/* XXX this is a problem: we cannot return a particle iterator here because
	 * PointerRNA can only reference data that exists permanently in the DNA ...
	 */
	NParticleState *state = ptr->data;
	BKE_nparticle_iter_find_id(state, , NParticleID id)
	BKE_nparticle_
	void *data = BLI_pbuf_get(&state->data, key);
	RNA_pointer_create(ptr->id.data, data_srna, data, r_ptr);
	return true;
}
#endif

static int rna_NParticleState_find_particle(NParticleState *state, int id)
{
	return BKE_nparticle_find_index(state, (NParticleID)id);
}

static int rna_NParticleState_add_particle(NParticleState *state, int id)
{
	return BKE_nparticle_add(state, (NParticleID)id);
}

static void rna_NParticleState_remove_particle(NParticleState *state, int id)
{
	BKE_nparticle_remove(state, (NParticleID)id);
}


static NParticleAttribute *rna_NParticleSystem_attributes_new(NParticleSystem *psys, ReportList *reports, const char *name, int datatype)
{
	if (BKE_nparticle_attribute_find(psys, name)) {
		BKE_reportf(reports, RPT_ERROR_INVALID_INPUT, "Particle attribute with name %s already exists", name);
		return NULL;
	}
	return BKE_nparticle_attribute_new(psys, name, datatype);
}

static void rna_NParticleSystem_attributes_remove(NParticleSystem *psys, NParticleAttribute *attr)
{
	BKE_nparticle_attribute_remove(psys, attr);
}

static void rna_NParticleSystem_attributes_clear(NParticleSystem *psys)
{
	BKE_nparticle_attribute_remove_all(psys);
}

static void rna_NParticleSystem_attributes_move(NParticleSystem *psys, int from_index, int to_index)
{
	BKE_nparticle_attribute_move(psys, from_index, to_index);
}

#else

EnumPropertyItem nparticle_attribute_datatype_all[] = {
    {PAR_ATTR_DATATYPE_INTERNAL,    "INTERNAL",     0,  "Internal"      ""},
    {PAR_ATTR_DATATYPE_FLOAT,       "FLOAT",        0,  "Float"         ""},
    {PAR_ATTR_DATATYPE_INT,         "INT",          0,  "Int"           ""},
    {PAR_ATTR_DATATYPE_BOOL,        "BOOL",         0,  "Bool"          ""},
    {PAR_ATTR_DATATYPE_VECTOR,      "VECTOR",       0,  "Vector"        ""},
    {PAR_ATTR_DATATYPE_POINT,       "POINT",        0,  "Point"         ""},
    {PAR_ATTR_DATATYPE_NORMAL,      "NORMAL",       0,  "Normal"        ""},
    {PAR_ATTR_DATATYPE_COLOR,       "COLOR",        0,  "Color"         ""},
    {PAR_ATTR_DATATYPE_MATRIX,      "MATRIX",       0,  "Matrix"        ""},
    {0, NULL, 0, NULL, NULL}
};

EnumPropertyItem nparticle_attribute_datatype_user[] = {
    {PAR_ATTR_DATATYPE_FLOAT,       "FLOAT",        0,  "Float"         ""},
    {PAR_ATTR_DATATYPE_INT,         "INT",          0,  "Int"           ""},
    {PAR_ATTR_DATATYPE_BOOL,        "BOOL",         0,  "Bool"          ""},
    {PAR_ATTR_DATATYPE_VECTOR,      "VECTOR",       0,  "Vector"        ""},
    {PAR_ATTR_DATATYPE_POINT,       "POINT",        0,  "Point"         ""},
    {PAR_ATTR_DATATYPE_NORMAL,      "NORMAL",       0,  "Normal"        ""},
    {PAR_ATTR_DATATYPE_COLOR,       "COLOR",        0,  "Color"         ""},
    {PAR_ATTR_DATATYPE_MATRIX,      "MATRIX",       0,  "Matrix"        ""},
    {0, NULL, 0, NULL, NULL}
};

static void def_nparticle_attribute_description(StructRNA *srna)
{
	PropertyRNA *prop;

	prop = RNA_def_property(srna, "name", PROP_STRING, PROP_NONE);
	RNA_def_property_string_sdna(prop, NULL, "name");
	RNA_def_property_ui_text(prop, "Name", "Unique name");
	RNA_def_struct_name_property(srna, prop);

	prop = RNA_def_property(srna, "datatype", PROP_ENUM, PROP_NONE);
	RNA_def_property_enum_sdna(prop, NULL, "datatype");
	RNA_def_property_enum_items(prop, nparticle_attribute_datatype_all);
	RNA_def_property_enum_funcs(prop, NULL, "rna_NParticleAttribute_datatype_set", NULL);
	RNA_def_property_ui_text(prop, "Data Type", "Basic data type");
}

/* defines a subtype of NParticleAttribute with a specific collection property for actual data */
static void def_nparticle_attribute_state_type(BlenderRNA *brna,
                                               const char *state_structname, const char *data_structname,
                                               const char *get_func, const char *lookup_int_func, const char *assign_int_func)
{
	StructRNA *srna;
	PropertyRNA *prop;
	
	srna = RNA_def_struct(brna, state_structname, "NParticleAttributeState");
	RNA_def_struct_sdna(srna, "NParticleAttributeState");
	
	prop = RNA_def_property(srna, "data", PROP_COLLECTION, PROP_NONE);
	RNA_def_property_struct_type(prop, data_structname);
	RNA_def_property_ui_text(prop, "Data", "");
	RNA_def_property_collection_funcs(prop, "rna_NParticleAttributeState_data_begin", "rna_NParticleAttributeState_data_next",
	                                  "rna_NParticleAttributeState_data_end", get_func,
	                                  "rna_NParticleAttributeState_data_length", lookup_int_func,
	                                  NULL, assign_int_func);
}

static void rna_def_nparticle_attribute_state(BlenderRNA *brna)
{
	StructRNA *srna;
	PropertyRNA *prop;

	srna = RNA_def_struct(brna, "NParticleAttributeState", NULL);
	RNA_def_struct_sdna(srna, "NParticleAttributeState");
	RNA_def_struct_ui_text(srna, "Particle Attribute State", "Data for a particle attribute");
	RNA_def_struct_refine_func(srna, "rna_NParticleAttributeState_refine");

	/*** Subtypes for data access ***/
	
	/* VOID */
	srna = RNA_def_struct(brna, "NParticleDataVoid", NULL);
	RNA_def_struct_ui_text(srna, "Particle Data", "Unknown particle data type");

	/* FLOAT */
	srna = RNA_def_struct(brna, "NParticleDataFloat", NULL);
	RNA_def_struct_ui_text(srna, "Particle Float Data", "");

	prop = RNA_def_property(srna, "value", PROP_FLOAT, PROP_NONE);
	RNA_def_property_float_funcs(prop, "rna_NParticleDataFloat_get", "rna_NParticleDataFloat_set", NULL);
	RNA_def_property_ui_text(prop, "Value", "");

	/* INT */
	srna = RNA_def_struct(brna, "NParticleDataInt", NULL);
	RNA_def_struct_ui_text(srna, "Particle Int Data", "");

	prop = RNA_def_property(srna, "value", PROP_INT, PROP_NONE);
	RNA_def_property_int_funcs(prop, "rna_NParticleDataInt_get", "rna_NParticleDataInt_set", NULL);
	RNA_def_property_ui_text(prop, "Value", "");

	/* BOOL */
	srna = RNA_def_struct(brna, "NParticleDataBool", NULL);
	RNA_def_struct_ui_text(srna, "Particle Bool Data", "");

	prop = RNA_def_property(srna, "value", PROP_BOOLEAN, PROP_NONE);
	RNA_def_property_boolean_funcs(prop, "rna_NParticleDataBool_get", "rna_NParticleDataBool_set");
	RNA_def_property_ui_text(prop, "Value", "");

	/* VECTOR */
	srna = RNA_def_struct(brna, "NParticleDataVector", NULL);
	RNA_def_struct_ui_text(srna, "Particle Vector Data", "");

	prop = RNA_def_property(srna, "value", PROP_FLOAT, PROP_XYZ);
	RNA_def_property_array(prop, 3);
	RNA_def_property_float_funcs(prop, "rna_NParticleDataVector_get", "rna_NParticleDataVector_set", NULL);
	RNA_def_property_ui_text(prop, "Value", "");

	/* POINT */
	srna = RNA_def_struct(brna, "NParticleDataPoint", NULL);
	RNA_def_struct_ui_text(srna, "Particle Point Data", "");

	prop = RNA_def_property(srna, "value", PROP_FLOAT, PROP_TRANSLATION);
	RNA_def_property_array(prop, 3);
	RNA_def_property_float_funcs(prop, "rna_NParticleDataVector_get", "rna_NParticleDataVector_set", NULL);
	RNA_def_property_ui_text(prop, "Value", "");

	/* NORMAL */
	srna = RNA_def_struct(brna, "NParticleDataNormal", NULL);
	RNA_def_struct_ui_text(srna, "Particle Normal Data", "");

	prop = RNA_def_property(srna, "value", PROP_FLOAT, PROP_DIRECTION);
	RNA_def_property_array(prop, 3);
	RNA_def_property_float_funcs(prop, "rna_NParticleDataVector_get", "rna_NParticleDataVector_set", NULL);
	RNA_def_property_ui_text(prop, "Value", "");

	/* COLOR */
	srna = RNA_def_struct(brna, "NParticleDataColor", NULL);
	RNA_def_struct_ui_text(srna, "Particle Color Data", "");

	prop = RNA_def_property(srna, "value", PROP_FLOAT, PROP_COLOR);
	RNA_def_property_array(prop, 4);
	RNA_def_property_float_funcs(prop, "rna_NParticleDataColor_get", "rna_NParticleDataColor_set", NULL);
	RNA_def_property_ui_text(prop, "Value", "");

	/* MATRIX */
	srna = RNA_def_struct(brna, "NParticleDataMatrix", NULL);
	RNA_def_struct_ui_text(srna, "Particle Matrix Data", "");

	prop = RNA_def_property(srna, "value", PROP_FLOAT, PROP_MATRIX);
	RNA_def_property_array(prop, 16);
	RNA_def_property_float_funcs(prop, "rna_NParticleDataMatrix_get", "rna_NParticleDataMatrix_set", NULL);
	RNA_def_property_ui_text(prop, "Value", "");

#define DEF_ATTR_TYPE_RNA(lcase, ucase) \
	def_nparticle_attribute_state_type(brna, "NParticleAttributeState"#ucase, "NParticleData"#ucase, \
	                                   "rna_NParticleAttributeState_data_get_"#lcase, \
	                                   "rna_NParticleAttributeState_data_lookup_int_"#lcase, \
	                                   "rna_NParticleAttributeState_data_assign_int_"#lcase);

	DEF_ATTR_TYPE_RNA(float, Float)
	DEF_ATTR_TYPE_RNA(int, Int)
	DEF_ATTR_TYPE_RNA(bool, Bool)
	DEF_ATTR_TYPE_RNA(vector, Vector)
	DEF_ATTR_TYPE_RNA(point, Point)
	DEF_ATTR_TYPE_RNA(normal, Normal)
	DEF_ATTR_TYPE_RNA(color, Color)
	DEF_ATTR_TYPE_RNA(matrix, Matrix)

#undef DEF_ATTR_TYPE_RNA
}

static void rna_def_nparticle_iterator(BlenderRNA *brna)
{
	StructRNA *srna;
	PropertyRNA *prop;

	srna = RNA_def_struct(brna, "NParticleIterator", NULL);
	RNA_def_struct_ui_text(srna, "Particle Iterator", "Access iterator for individual particles");
}

static void rna_def_nparticle_state(BlenderRNA *brna)
{
	StructRNA *srna;
	FunctionRNA *func;
	PropertyRNA *prop, *parm;

	srna = RNA_def_struct(brna, "NParticleState", NULL);
	RNA_def_struct_ui_text(srna, "Particle State", "Data in a particle system for a specific frame");

	prop = RNA_def_property(srna, "attributes", PROP_COLLECTION, PROP_NONE);
	RNA_def_property_collection_funcs(prop, "rna_NParticleState_attributes_begin", "rna_NParticleState_attributes_next",
	                                  "rna_NParticleState_attributes_end", "rna_NParticleState_attributes_get",
	                                  "rna_NParticleState_attributes_length", NULL,
	                                  "rna_NParticleState_attributes_lookup_string", NULL);
	RNA_def_property_ui_text(prop, "Attributes", "Data layers associated to particles");
	RNA_def_property_struct_type(prop, "NParticleAttributeState");

#if 0
	prop = RNA_def_property(srna, "particles", PROP_COLLECTION, PROP_NONE);
	RNA_def_property_struct_type(prop, "NParticleIterator");
	RNA_def_property_ui_text(prop, "Particles", "");
	RNA_def_property_collection_funcs(prop, "rna_NParticleState_particles_begin", "rna_NParticleState_particles_next",
	                                  "rna_NParticleState_particles_end", "rna_NParticleState_particles_get",
	                                  "rna_NParticleState_particles_length", "rna_NParticleState_particles_lookup_int",
	                                  NULL, NULL);
#endif

	func = RNA_def_function(srna, "find_particle", "rna_NParticleState_find_particle");
	RNA_def_function_ui_description(func, "Get a particle's index");
	parm = RNA_def_int(func, "id", 0, INT_MIN, INT_MAX, "Identifier", "Unique identifier of the particle", INT_MIN, INT_MAX);
	RNA_def_property_flag(parm, PROP_REQUIRED);
	/* return value */
	parm = RNA_def_int(func, "index", 0, 0, INT_MAX, "Index", "Index of the particle in attribute states", 0, INT_MAX);
	RNA_def_function_return(func, parm);

	func = RNA_def_function(srna, "add_particle", "rna_NParticleState_add_particle");
	RNA_def_function_ui_description(func, "Add a particle");
	parm = RNA_def_int(func, "id", 0, INT_MIN, INT_MAX, "Identifier", "Unique identifier of the particle", INT_MIN, INT_MAX);
	RNA_def_property_flag(parm, PROP_REQUIRED);
	/* return value */
	parm = RNA_def_int(func, "index", 0, 0, INT_MAX, "Index", "Index of the particle in attribute states", 0, INT_MAX);
	RNA_def_function_return(func, parm);

	func = RNA_def_function(srna, "remove_particle", "rna_NParticleState_remove_particle");
	RNA_def_function_ui_description(func, "Remove a particle");
	parm = RNA_def_int(func, "id", 0, INT_MIN, INT_MAX, "Identifier", "Unique identifier of the particle", INT_MIN, INT_MAX);
	RNA_def_property_flag(parm, PROP_REQUIRED);
}


static void rna_def_nparticle_attribute(BlenderRNA *brna)
{
	StructRNA *srna;

	srna = RNA_def_struct(brna, "NParticleAttribute", NULL);
	RNA_def_struct_sdna(srna, "NParticleAttribute");
	RNA_def_struct_ui_text(srna, "Particle Attribute", "Attribute in a particle system");

	RNA_def_struct_sdna_from(srna, "NParticleAttributeDescription", "desc");
	def_nparticle_attribute_description(srna);
	RNA_def_struct_sdna_from(srna, "NParticleAttribute", NULL); /* reset */
}

static void rna_def_nparticle_system_attributes_api(BlenderRNA *brna, PropertyRNA *cprop)
{
	StructRNA *srna;
	PropertyRNA *parm;
	FunctionRNA *func;

	RNA_def_property_srna(cprop, "NParticleAttributes");
	srna = RNA_def_struct(brna, "NParticleAttributes", NULL);
	RNA_def_struct_sdna(srna, "NParticleSystem");
	RNA_def_struct_ui_text(srna, "Attributes", "Collection of particle attributes");

	func = RNA_def_function(srna, "new", "rna_NParticleSystem_attributes_new");
	RNA_def_function_ui_description(func, "Add a particle attribute");
	RNA_def_function_flag(func, FUNC_USE_REPORTS);
	parm = RNA_def_string(func, "name", "", 64, "Name", "");
	RNA_def_property_flag(parm, PROP_REQUIRED);
	parm = RNA_def_enum(func, "datatype", nparticle_attribute_datatype_user, PAR_ATTR_DATATYPE_FLOAT, "Data Type", "Base data type");
	RNA_def_property_flag(parm, PROP_REQUIRED);
	/* return value */
	parm = RNA_def_pointer(func, "attr", "NParticleAttribute", "", "Attribute");
	RNA_def_function_return(func, parm);

	func = RNA_def_function(srna, "remove", "rna_NParticleSystem_attributes_remove");
	RNA_def_function_ui_description(func, "Remove an attribute from the buffer");
	parm = RNA_def_pointer(func, "attr", "NParticleAttribute", "", "The attribute to remove");
	RNA_def_property_flag(parm, PROP_REQUIRED);

	func = RNA_def_function(srna, "clear", "rna_NParticleSystem_attributes_clear");
	RNA_def_function_ui_description(func, "Remove all attributes from the buffer");

	func = RNA_def_function(srna, "move", "rna_NParticleSystem_attributes_move");
	RNA_def_function_ui_description(func, "Move an attribute to another position");
	parm = RNA_def_int(func, "from_index", -1, 0, INT_MAX, "From Index", "Index of the attribute to move", 0, 10000);
	RNA_def_property_flag(parm, PROP_REQUIRED);
	parm = RNA_def_int(func, "to_index", -1, 0, INT_MAX, "To Index", "Target index for the attribute", 0, 10000);
	RNA_def_property_flag(parm, PROP_REQUIRED);
}

static void rna_def_nparticle_system(BlenderRNA *brna)
{
	StructRNA *srna;
	PropertyRNA *prop;

	srna = RNA_def_struct(brna, "NParticleSystem", NULL);
	RNA_def_struct_ui_text(srna, "Particle System", "Container for particles");

	prop = RNA_def_property(srna, "attributes", PROP_COLLECTION, PROP_NONE);
	RNA_def_property_collection_sdna(prop, NULL, "attributes", NULL);
	RNA_def_property_ui_text(prop, "Attributes", "Data layers associated to particles");
	RNA_def_property_struct_type(prop, "NParticleAttribute");
	rna_def_nparticle_system_attributes_api(brna, prop);

	prop = RNA_def_property(srna, "state", PROP_POINTER, PROP_NONE);
	RNA_def_property_pointer_sdna(prop, NULL, "state");
	RNA_def_property_struct_type(prop, "NParticleState");
	RNA_def_property_clear_flag(prop, PROP_EDITABLE);
	RNA_def_property_ui_text(prop, "State", "");
}

void RNA_def_nparticle(BlenderRNA *brna)
{
	rna_def_nparticle_attribute_state(brna);
	rna_def_nparticle_iterator(brna);
	rna_def_nparticle_state(brna);
	rna_def_nparticle_attribute(brna);
	rna_def_nparticle_system(brna);
}

#endif