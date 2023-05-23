/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "O-RAN.WG3.E2SM-KPM-v202v300.asn1"
 * 	`asn1c -pdu=auto -fcompound-names -fno-include-deps -findirect-choice -gen-PER -gen-OER -no-gen-example`
 */

#include "MeasurementCondItem-v300.h"

#include "BinRangeDefinition.h"
asn_TYPE_member_t asn_MBR_MeasurementCondItem_v300_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementCondItem_v300, measType),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_MeasurementType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementCondItem_v300, matchingCond),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MatchingCondList_v300,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"matchingCond"
		},
	{ ATF_POINTER, 1, offsetof(struct MeasurementCondItem_v300, binRangeDef),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BinRangeDefinition,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"binRangeDef"
		},
};
static const int asn_MAP_MeasurementCondItem_v300_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_MeasurementCondItem_v300_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_MeasurementCondItem_v300_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measType */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* matchingCond */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* binRangeDef */
};
asn_SEQUENCE_specifics_t asn_SPC_MeasurementCondItem_v300_specs_1 = {
	sizeof(struct MeasurementCondItem_v300),
	offsetof(struct MeasurementCondItem_v300, _asn_ctx),
	asn_MAP_MeasurementCondItem_v300_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_MeasurementCondItem_v300_oms_1,	/* Optional members */
	0, 1,	/* Root/Additions */
	2,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_MeasurementCondItem_v300 = {
	"MeasurementCondItem-v300",
	"MeasurementCondItem-v300",
	&asn_OP_SEQUENCE,
	asn_DEF_MeasurementCondItem_v300_tags_1,
	sizeof(asn_DEF_MeasurementCondItem_v300_tags_1)
		/sizeof(asn_DEF_MeasurementCondItem_v300_tags_1[0]), /* 1 */
	asn_DEF_MeasurementCondItem_v300_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasurementCondItem_v300_tags_1)
		/sizeof(asn_DEF_MeasurementCondItem_v300_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_MeasurementCondItem_v300_1,
	3,	/* Elements count */
	&asn_SPC_MeasurementCondItem_v300_specs_1	/* Additional specs */
};

