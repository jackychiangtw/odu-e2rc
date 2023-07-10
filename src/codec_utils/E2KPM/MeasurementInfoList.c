/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "O-RAN.WG3.E2SM-KPM-v202v300-modified.asn1"
 * 	`asn1c -pdu=auto -fcompound-names -fno-include-deps -findirect-choice -gen-PER -gen-OER -no-gen-example`
 */

#include "MeasurementInfoList.h"

#include "MeasurementInfoItem.h"
static asn_oer_constraints_t asn_OER_type_MeasurementInfoList_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..65535)) */};
asn_per_constraints_t asn_PER_type_MeasurementInfoList_constr_1 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 16,  16,  1,  65535 }	/* (SIZE(1..65535)) */,
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_MeasurementInfoList_1[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_MeasurementInfoItem,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_MeasurementInfoList_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
asn_SET_OF_specifics_t asn_SPC_MeasurementInfoList_specs_1 = {
	sizeof(struct MeasurementInfoList),
	offsetof(struct MeasurementInfoList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
asn_TYPE_descriptor_t asn_DEF_MeasurementInfoList = {
	"MeasurementInfoList",
	"MeasurementInfoList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_MeasurementInfoList_tags_1,
	sizeof(asn_DEF_MeasurementInfoList_tags_1)
		/sizeof(asn_DEF_MeasurementInfoList_tags_1[0]), /* 1 */
	asn_DEF_MeasurementInfoList_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasurementInfoList_tags_1)
		/sizeof(asn_DEF_MeasurementInfoList_tags_1[0]), /* 1 */
	{ &asn_OER_type_MeasurementInfoList_constr_1, &asn_PER_type_MeasurementInfoList_constr_1, SEQUENCE_OF_constraint },
	asn_MBR_MeasurementInfoList_1,
	1,	/* Single element */
	&asn_SPC_MeasurementInfoList_specs_1	/* Additional specs */
};

