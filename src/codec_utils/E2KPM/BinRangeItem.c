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

#include "BinRangeItem.h"

asn_TYPE_member_t asn_MBR_BinRangeItem_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct BinRangeItem, binIndex),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BinIndex,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"binIndex"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct BinRangeItem, startValue),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_BinRangeValue,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"startValue"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct BinRangeItem, endValue),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_BinRangeValue,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"endValue"
		},
};
static const ber_tlv_tag_t asn_DEF_BinRangeItem_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_BinRangeItem_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* binIndex */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* startValue */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* endValue */
};
asn_SEQUENCE_specifics_t asn_SPC_BinRangeItem_specs_1 = {
	sizeof(struct BinRangeItem),
	offsetof(struct BinRangeItem, _asn_ctx),
	asn_MAP_BinRangeItem_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_BinRangeItem = {
	"BinRangeItem",
	"BinRangeItem",
	&asn_OP_SEQUENCE,
	asn_DEF_BinRangeItem_tags_1,
	sizeof(asn_DEF_BinRangeItem_tags_1)
		/sizeof(asn_DEF_BinRangeItem_tags_1[0]), /* 1 */
	asn_DEF_BinRangeItem_tags_1,	/* Same as above */
	sizeof(asn_DEF_BinRangeItem_tags_1)
		/sizeof(asn_DEF_BinRangeItem_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_BinRangeItem_1,
	3,	/* Elements count */
	&asn_SPC_BinRangeItem_specs_1	/* Additional specs */
};

