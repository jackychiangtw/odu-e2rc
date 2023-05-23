/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "O-RAN.WG3.E2SM-KPM-v202v300.asn1"
 * 	`asn1c -pdu=auto -fcompound-names -fno-include-deps -findirect-choice -gen-PER -gen-OER -no-gen-example`
 */

#include "E2SM-KPM-IndicationHeader-Format1-v300.h"

static const int permitted_alphabet_table_3[256] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 1, 0, 0, 0, 0, 0, 0, 2, 3, 4, 0, 5, 6, 7, 8, 9,	/* .      '() +,-./ */
10,11,12,13,14,15,16,17,18,19,20, 0, 0,21, 0,22,	/* 0123456789:  = ? */
 0,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,	/*  ABCDEFGHIJKLMNO */
38,39,40,41,42,43,44,45,46,47,48, 0, 0, 0, 0, 0,	/* PQRSTUVWXYZ      */
 0,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,	/*  abcdefghijklmno */
64,65,66,67,68,69,70,71,72,73,74, 0, 0, 0, 0, 0,	/* pqrstuvwxyz      */
};
static const int permitted_alphabet_code2value_3[74] = {
32,39,40,41,43,44,45,46,47,48,49,50,51,52,53,54,
55,56,57,58,61,63,65,66,67,68,69,70,71,72,73,74,
75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,
97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,
113,114,115,116,117,118,119,120,121,122,};


static int check_permitted_alphabet_3(const void *sptr) {
	const int *table = permitted_alphabet_table_3;
	/* The underlying type is PrintableString */
	const PrintableString_t *st = (const PrintableString_t *)sptr;
	const uint8_t *ch = st->buf;
	const uint8_t *end = ch + st->size;
	
	for(; ch < end; ch++) {
		uint8_t cv = *ch;
		if(!table[cv]) return -1;
	}
	return 0;
}

static const int permitted_alphabet_table_4[256] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 1, 0, 0, 0, 0, 0, 0, 2, 3, 4, 0, 5, 6, 7, 8, 9,	/* .      '() +,-./ */
10,11,12,13,14,15,16,17,18,19,20, 0, 0,21, 0,22,	/* 0123456789:  = ? */
 0,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,	/*  ABCDEFGHIJKLMNO */
38,39,40,41,42,43,44,45,46,47,48, 0, 0, 0, 0, 0,	/* PQRSTUVWXYZ      */
 0,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,	/*  abcdefghijklmno */
64,65,66,67,68,69,70,71,72,73,74, 0, 0, 0, 0, 0,	/* pqrstuvwxyz      */
};
static const int permitted_alphabet_code2value_4[74] = {
32,39,40,41,43,44,45,46,47,48,49,50,51,52,53,54,
55,56,57,58,61,63,65,66,67,68,69,70,71,72,73,74,
75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,
97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,
113,114,115,116,117,118,119,120,121,122,};


static int check_permitted_alphabet_4(const void *sptr) {
	const int *table = permitted_alphabet_table_4;
	/* The underlying type is PrintableString */
	const PrintableString_t *st = (const PrintableString_t *)sptr;
	const uint8_t *ch = st->buf;
	const uint8_t *end = ch + st->size;
	
	for(; ch < end; ch++) {
		uint8_t cv = *ch;
		if(!table[cv]) return -1;
	}
	return 0;
}

static const int permitted_alphabet_table_5[256] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 1, 0, 0, 0, 0, 0, 0, 2, 3, 4, 0, 5, 6, 7, 8, 9,	/* .      '() +,-./ */
10,11,12,13,14,15,16,17,18,19,20, 0, 0,21, 0,22,	/* 0123456789:  = ? */
 0,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,	/*  ABCDEFGHIJKLMNO */
38,39,40,41,42,43,44,45,46,47,48, 0, 0, 0, 0, 0,	/* PQRSTUVWXYZ      */
 0,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,	/*  abcdefghijklmno */
64,65,66,67,68,69,70,71,72,73,74, 0, 0, 0, 0, 0,	/* pqrstuvwxyz      */
};
static const int permitted_alphabet_code2value_5[74] = {
32,39,40,41,43,44,45,46,47,48,49,50,51,52,53,54,
55,56,57,58,61,63,65,66,67,68,69,70,71,72,73,74,
75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,
97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,
113,114,115,116,117,118,119,120,121,122,};


static int check_permitted_alphabet_5(const void *sptr) {
	const int *table = permitted_alphabet_table_5;
	/* The underlying type is PrintableString */
	const PrintableString_t *st = (const PrintableString_t *)sptr;
	const uint8_t *ch = st->buf;
	const uint8_t *end = ch + st->size;
	
	for(; ch < end; ch++) {
		uint8_t cv = *ch;
		if(!table[cv]) return -1;
	}
	return 0;
}

static const int permitted_alphabet_table_6[256] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 1, 0, 0, 0, 0, 0, 0, 2, 3, 4, 0, 5, 6, 7, 8, 9,	/* .      '() +,-./ */
10,11,12,13,14,15,16,17,18,19,20, 0, 0,21, 0,22,	/* 0123456789:  = ? */
 0,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,	/*  ABCDEFGHIJKLMNO */
38,39,40,41,42,43,44,45,46,47,48, 0, 0, 0, 0, 0,	/* PQRSTUVWXYZ      */
 0,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,	/*  abcdefghijklmno */
64,65,66,67,68,69,70,71,72,73,74, 0, 0, 0, 0, 0,	/* pqrstuvwxyz      */
};
static const int permitted_alphabet_code2value_6[74] = {
32,39,40,41,43,44,45,46,47,48,49,50,51,52,53,54,
55,56,57,58,61,63,65,66,67,68,69,70,71,72,73,74,
75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,
97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,
113,114,115,116,117,118,119,120,121,122,};


static int check_permitted_alphabet_6(const void *sptr) {
	const int *table = permitted_alphabet_table_6;
	/* The underlying type is PrintableString */
	const PrintableString_t *st = (const PrintableString_t *)sptr;
	const uint8_t *ch = st->buf;
	const uint8_t *end = ch + st->size;
	
	for(; ch < end; ch++) {
		uint8_t cv = *ch;
		if(!table[cv]) return -1;
	}
	return 0;
}

static int
memb_fileFormatversion_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const PrintableString_t *st = (const PrintableString_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size <= 15)
		 && !check_permitted_alphabet_3(st)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int asn_PER_MAP_fileFormatversion_3_v2c(unsigned int value) {
	if(value >= sizeof(permitted_alphabet_table_3)/sizeof(permitted_alphabet_table_3[0]))
		return -1;
	return permitted_alphabet_table_3[value] - 1;
}
static int asn_PER_MAP_fileFormatversion_3_c2v(unsigned int code) {
	if(code >= sizeof(permitted_alphabet_code2value_3)/sizeof(permitted_alphabet_code2value_3[0]))
		return -1;
	return permitted_alphabet_code2value_3[code];
}
static int
memb_senderName_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const PrintableString_t *st = (const PrintableString_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size <= 400)
		 && !check_permitted_alphabet_4(st)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int asn_PER_MAP_senderName_4_v2c(unsigned int value) {
	if(value >= sizeof(permitted_alphabet_table_4)/sizeof(permitted_alphabet_table_4[0]))
		return -1;
	return permitted_alphabet_table_4[value] - 1;
}
static int asn_PER_MAP_senderName_4_c2v(unsigned int code) {
	if(code >= sizeof(permitted_alphabet_code2value_4)/sizeof(permitted_alphabet_code2value_4[0]))
		return -1;
	return permitted_alphabet_code2value_4[code];
}
static int
memb_senderType_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const PrintableString_t *st = (const PrintableString_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size <= 8)
		 && !check_permitted_alphabet_5(st)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int asn_PER_MAP_senderType_5_v2c(unsigned int value) {
	if(value >= sizeof(permitted_alphabet_table_5)/sizeof(permitted_alphabet_table_5[0]))
		return -1;
	return permitted_alphabet_table_5[value] - 1;
}
static int asn_PER_MAP_senderType_5_c2v(unsigned int code) {
	if(code >= sizeof(permitted_alphabet_code2value_5)/sizeof(permitted_alphabet_code2value_5[0]))
		return -1;
	return permitted_alphabet_code2value_5[code];
}
static int
memb_vendorName_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const PrintableString_t *st = (const PrintableString_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size <= 32)
		 && !check_permitted_alphabet_6(st)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int asn_PER_MAP_vendorName_6_v2c(unsigned int value) {
	if(value >= sizeof(permitted_alphabet_table_6)/sizeof(permitted_alphabet_table_6[0]))
		return -1;
	return permitted_alphabet_table_6[value] - 1;
}
static int asn_PER_MAP_vendorName_6_c2v(unsigned int code) {
	if(code >= sizeof(permitted_alphabet_code2value_6)/sizeof(permitted_alphabet_code2value_6[0]))
		return -1;
	return permitted_alphabet_code2value_6[code];
}
static asn_oer_constraints_t asn_OER_memb_fileFormatversion_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(0..MAX)) */};
static asn_per_constraints_t asn_PER_memb_fileFormatversion_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 7,  7,  32,  122 }	/* (32..122) */,
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  4,  4,  0,  15 }	/* (SIZE(0..15,...)) */,
	asn_PER_MAP_fileFormatversion_3_v2c,	/* Value to PER code map */
	asn_PER_MAP_fileFormatversion_3_c2v	/* PER code to value map */
};
static asn_oer_constraints_t asn_OER_memb_senderName_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(0..MAX)) */};
static asn_per_constraints_t asn_PER_memb_senderName_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 7,  7,  32,  122 }	/* (32..122) */,
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  9,  9,  0,  400 }	/* (SIZE(0..400,...)) */,
	asn_PER_MAP_senderName_4_v2c,	/* Value to PER code map */
	asn_PER_MAP_senderName_4_c2v	/* PER code to value map */
};
static asn_oer_constraints_t asn_OER_memb_senderType_constr_5 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(0..MAX)) */};
static asn_per_constraints_t asn_PER_memb_senderType_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 7,  7,  32,  122 }	/* (32..122) */,
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  4,  4,  0,  8 }	/* (SIZE(0..8,...)) */,
	asn_PER_MAP_senderType_5_v2c,	/* Value to PER code map */
	asn_PER_MAP_senderType_5_c2v	/* PER code to value map */
};
static asn_oer_constraints_t asn_OER_memb_vendorName_constr_6 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(0..MAX)) */};
static asn_per_constraints_t asn_PER_memb_vendorName_constr_6 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 7,  7,  32,  122 }	/* (32..122) */,
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  6,  6,  0,  32 }	/* (SIZE(0..32,...)) */,
	asn_PER_MAP_vendorName_6_v2c,	/* Value to PER code map */
	asn_PER_MAP_vendorName_6_c2v	/* PER code to value map */
};
asn_TYPE_member_t asn_MBR_E2SM_KPM_IndicationHeader_Format1_v300_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct E2SM_KPM_IndicationHeader_Format1_v300, colletStartTime),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimeStamp_v300,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"colletStartTime"
		},
	{ ATF_POINTER, 4, offsetof(struct E2SM_KPM_IndicationHeader_Format1_v300, fileFormatversion),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PrintableString,
		0,
		{ &asn_OER_memb_fileFormatversion_constr_3, &asn_PER_memb_fileFormatversion_constr_3,  memb_fileFormatversion_constraint_1 },
		0, 0, /* No default value */
		"fileFormatversion"
		},
	{ ATF_POINTER, 3, offsetof(struct E2SM_KPM_IndicationHeader_Format1_v300, senderName),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PrintableString,
		0,
		{ &asn_OER_memb_senderName_constr_4, &asn_PER_memb_senderName_constr_4,  memb_senderName_constraint_1 },
		0, 0, /* No default value */
		"senderName"
		},
	{ ATF_POINTER, 2, offsetof(struct E2SM_KPM_IndicationHeader_Format1_v300, senderType),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PrintableString,
		0,
		{ &asn_OER_memb_senderType_constr_5, &asn_PER_memb_senderType_constr_5,  memb_senderType_constraint_1 },
		0, 0, /* No default value */
		"senderType"
		},
	{ ATF_POINTER, 1, offsetof(struct E2SM_KPM_IndicationHeader_Format1_v300, vendorName),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PrintableString,
		0,
		{ &asn_OER_memb_vendorName_constr_6, &asn_PER_memb_vendorName_constr_6,  memb_vendorName_constraint_1 },
		0, 0, /* No default value */
		"vendorName"
		},
};
static const int asn_MAP_E2SM_KPM_IndicationHeader_Format1_v300_oms_1[] = { 1, 2, 3, 4 };
static const ber_tlv_tag_t asn_DEF_E2SM_KPM_IndicationHeader_Format1_v300_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_E2SM_KPM_IndicationHeader_Format1_v300_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* colletStartTime */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* fileFormatversion */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* senderName */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* senderType */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* vendorName */
};
asn_SEQUENCE_specifics_t asn_SPC_E2SM_KPM_IndicationHeader_Format1_v300_specs_1 = {
	sizeof(struct E2SM_KPM_IndicationHeader_Format1_v300),
	offsetof(struct E2SM_KPM_IndicationHeader_Format1_v300, _asn_ctx),
	asn_MAP_E2SM_KPM_IndicationHeader_Format1_v300_tag2el_1,
	5,	/* Count of tags in the map */
	asn_MAP_E2SM_KPM_IndicationHeader_Format1_v300_oms_1,	/* Optional members */
	4, 0,	/* Root/Additions */
	5,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_E2SM_KPM_IndicationHeader_Format1_v300 = {
	"E2SM-KPM-IndicationHeader-Format1-v300",
	"E2SM-KPM-IndicationHeader-Format1-v300",
	&asn_OP_SEQUENCE,
	asn_DEF_E2SM_KPM_IndicationHeader_Format1_v300_tags_1,
	sizeof(asn_DEF_E2SM_KPM_IndicationHeader_Format1_v300_tags_1)
		/sizeof(asn_DEF_E2SM_KPM_IndicationHeader_Format1_v300_tags_1[0]), /* 1 */
	asn_DEF_E2SM_KPM_IndicationHeader_Format1_v300_tags_1,	/* Same as above */
	sizeof(asn_DEF_E2SM_KPM_IndicationHeader_Format1_v300_tags_1)
		/sizeof(asn_DEF_E2SM_KPM_IndicationHeader_Format1_v300_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_E2SM_KPM_IndicationHeader_Format1_v300_1,
	5,	/* Elements count */
	&asn_SPC_E2SM_KPM_IndicationHeader_Format1_v300_specs_1	/* Additional specs */
};

