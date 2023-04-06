/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "e2sm-kpm-v02.03.asn1"
 * 	`asn1c -pdu=auto -fcompound-names -fno-include-deps -findirect-choice -gen-PER -gen-OER -no-gen-example`
 */

#include "MeasurementType.h"

static asn_oer_constraints_t asn_OER_type_MeasurementType_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_MeasurementType_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  1,  1,  0,  1 }	/* (0..1,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_MeasurementType_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementType, choice.measName),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasurementTypeName,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measName"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementType, choice.measID),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasurementTypeID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measID"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_MeasurementType_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measName */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* measID */
};
asn_CHOICE_specifics_t asn_SPC_MeasurementType_specs_1 = {
	sizeof(struct MeasurementType),
	offsetof(struct MeasurementType, _asn_ctx),
	offsetof(struct MeasurementType, present),
	sizeof(((struct MeasurementType *)0)->present),
	asn_MAP_MeasurementType_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0,
	2	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_MeasurementType = {
	"MeasurementType",
	"MeasurementType",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_MeasurementType_constr_1, &asn_PER_type_MeasurementType_constr_1, CHOICE_constraint },
	asn_MBR_MeasurementType_1,
	2,	/* Elements count */
	&asn_SPC_MeasurementType_specs_1	/* Additional specs */
};

