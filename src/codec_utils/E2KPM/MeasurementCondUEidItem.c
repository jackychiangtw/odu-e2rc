/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "O-RAN.WG3.E2SM-KPM-v202v300.asn1"
 * 	`asn1c -pdu=auto -fcompound-names -fno-include-deps -findirect-choice -gen-PER -gen-OER -no-gen-example`
 */

#include "MeasurementCondUEidItem.h"

#include "MatchingUEidList.h"
asn_TYPE_member_t asn_MBR_MeasurementCondUEidItem_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementCondUEidItem, measType),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_MeasurementType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementCondUEidItem, matchingCond),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MatchingCondList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"matchingCond"
		},
	{ ATF_POINTER, 1, offsetof(struct MeasurementCondUEidItem, matchingUEidList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MatchingUEidList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"matchingUEidList"
		},
};
static const int asn_MAP_MeasurementCondUEidItem_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_MeasurementCondUEidItem_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_MeasurementCondUEidItem_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measType */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* matchingCond */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* matchingUEidList */
};
asn_SEQUENCE_specifics_t asn_SPC_MeasurementCondUEidItem_specs_1 = {
	sizeof(struct MeasurementCondUEidItem),
	offsetof(struct MeasurementCondUEidItem, _asn_ctx),
	asn_MAP_MeasurementCondUEidItem_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_MeasurementCondUEidItem_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_MeasurementCondUEidItem = {
	"MeasurementCondUEidItem",
	"MeasurementCondUEidItem",
	&asn_OP_SEQUENCE,
	asn_DEF_MeasurementCondUEidItem_tags_1,
	sizeof(asn_DEF_MeasurementCondUEidItem_tags_1)
		/sizeof(asn_DEF_MeasurementCondUEidItem_tags_1[0]), /* 1 */
	asn_DEF_MeasurementCondUEidItem_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasurementCondUEidItem_tags_1)
		/sizeof(asn_DEF_MeasurementCondUEidItem_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_MeasurementCondUEidItem_1,
	3,	/* Elements count */
	&asn_SPC_MeasurementCondUEidItem_specs_1	/* Additional specs */
};

