/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
<<<<<<< Updated upstream
 * 	found in "O-RAN.WG3.E2SM-KPM-v202v300.asn1"
=======
 * 	found in "O-RAN.WG3.E2SM-KPM-v202v300-modified.asn1"
>>>>>>> Stashed changes
 * 	`asn1c -pdu=auto -fcompound-names -fno-include-deps -findirect-choice -gen-PER -gen-OER -no-gen-example`
 */

#include "MeasurementRecordItem.h"

static int
integer_2_constraint(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	
	/* Constraint check succeeded */
	return 0;
}

/*
 * This type is implemented using NativeInteger,
 * so here we adjust the DEF accordingly.
 */
static int
memb_integer_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	
	/* Constraint check succeeded */
	return 0;
}

static asn_oer_constraints_t asn_OER_type_integer_constr_2 CC_NOTUSED = {
	{ 4, 1 }	/* (0..4294967295) */,
	-1};
static asn_per_constraints_t asn_PER_type_integer_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 32, -1,  0,  4294967295 }	/* (0..4294967295) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_integer_constr_2 CC_NOTUSED = {
	{ 4, 1 }	/* (0..4294967295) */,
	-1};
static asn_per_constraints_t asn_PER_memb_integer_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 32, -1,  0,  4294967295 }	/* (0..4294967295) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_MeasurementRecordItem_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_MeasurementRecordItem_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  2,  2,  0,  2 }	/* (0..2,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_specifics_t asn_SPC_integer_specs_2 = {
	0,	0,	0,	0,	0,
	0,	/* Native long size */
	1	/* Unsigned representation */
};
static const ber_tlv_tag_t asn_DEF_integer_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (2 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_integer_2 = {
	"integer",
	"integer",
	&asn_OP_NativeInteger,
	asn_DEF_integer_tags_2,
	sizeof(asn_DEF_integer_tags_2)
		/sizeof(asn_DEF_integer_tags_2[0]) - 1, /* 1 */
	asn_DEF_integer_tags_2,	/* Same as above */
	sizeof(asn_DEF_integer_tags_2)
		/sizeof(asn_DEF_integer_tags_2[0]), /* 2 */
	{ &asn_OER_type_integer_constr_2, &asn_PER_type_integer_constr_2, integer_2_constraint },
	0, 0,	/* No members */
	&asn_SPC_integer_specs_2	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_MeasurementRecordItem_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementRecordItem, choice.integer),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_integer_2,
		0,
		{ &asn_OER_memb_integer_constr_2, &asn_PER_memb_integer_constr_2,  memb_integer_constraint_1 },
		0, 0, /* No default value */
		"integer"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementRecordItem, choice.real),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeReal,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"real"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementRecordItem, choice.noValue),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"noValue"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_MeasurementRecordItem_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* integer */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* real */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* noValue */
};
asn_CHOICE_specifics_t asn_SPC_MeasurementRecordItem_specs_1 = {
	sizeof(struct MeasurementRecordItem),
	offsetof(struct MeasurementRecordItem, _asn_ctx),
	offsetof(struct MeasurementRecordItem, present),
	sizeof(((struct MeasurementRecordItem *)0)->present),
	asn_MAP_MeasurementRecordItem_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0,
	3	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_MeasurementRecordItem = {
	"MeasurementRecordItem",
	"MeasurementRecordItem",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_MeasurementRecordItem_constr_1, &asn_PER_type_MeasurementRecordItem_constr_1, CHOICE_constraint },
	asn_MBR_MeasurementRecordItem_1,
	3,	/* Elements count */
	&asn_SPC_MeasurementRecordItem_specs_1	/* Additional specs */
};

