/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "e2sm-kpm-v02.03.asn1"
 * 	`asn1c -pdu=auto -fcompound-names -fno-include-deps -findirect-choice -gen-PER -gen-OER -no-gen-example`
 */

#include "DistMeasurementBinRangeList.h"

#include "DistMeasurementBinRangeItem.h"
static asn_oer_constraints_t asn_OER_type_DistMeasurementBinRangeList_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..65535)) */};
asn_per_constraints_t asn_PER_type_DistMeasurementBinRangeList_constr_1 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 16,  16,  1,  65535 }	/* (SIZE(1..65535)) */,
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_DistMeasurementBinRangeList_1[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_DistMeasurementBinRangeItem,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_DistMeasurementBinRangeList_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
asn_SET_OF_specifics_t asn_SPC_DistMeasurementBinRangeList_specs_1 = {
	sizeof(struct DistMeasurementBinRangeList),
	offsetof(struct DistMeasurementBinRangeList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
asn_TYPE_descriptor_t asn_DEF_DistMeasurementBinRangeList = {
	"DistMeasurementBinRangeList",
	"DistMeasurementBinRangeList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_DistMeasurementBinRangeList_tags_1,
	sizeof(asn_DEF_DistMeasurementBinRangeList_tags_1)
		/sizeof(asn_DEF_DistMeasurementBinRangeList_tags_1[0]), /* 1 */
	asn_DEF_DistMeasurementBinRangeList_tags_1,	/* Same as above */
	sizeof(asn_DEF_DistMeasurementBinRangeList_tags_1)
		/sizeof(asn_DEF_DistMeasurementBinRangeList_tags_1[0]), /* 1 */
	{ &asn_OER_type_DistMeasurementBinRangeList_constr_1, &asn_PER_type_DistMeasurementBinRangeList_constr_1, SEQUENCE_OF_constraint },
	asn_MBR_DistMeasurementBinRangeList_1,
	1,	/* Single element */
	&asn_SPC_DistMeasurementBinRangeList_specs_1	/* Additional specs */
};

