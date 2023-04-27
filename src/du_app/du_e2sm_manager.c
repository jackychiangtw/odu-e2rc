#include "du_e2sm_manager.h"


uint8_t smFillE2SetupReq(RANfunctions_List_t  *ranfun_list){
    uint8_t kpm_ranfunc_oid[] = "1.3.6.1.4.1.53148.1.2.2.2"; // RAN function service model OID
    uint8_t rc_ranfunc_oid[] = "1.4.2.1123.4.6.7";

    printf("\nINFO   -->  E2SM Manager : List all RAN functions<<<<\n");

    // E2SM-KPM RAN Function item in E2AP
    RANfunction_ItemIEs_t *ranfunc_item;
    ranfunc_item = (RANfunction_ItemIEs_t*)calloc(2, sizeof(RANfunction_ItemIEs_t));
    ranfunc_item->id = ProtocolIE_IDE2_id_RANfunction_Item;
    ranfunc_item->criticality = Criticality_reject;
    ranfunc_item->value.present = RANfunction_ItemIEs__value_PR_RANfunction_Item;
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionID = 1;
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionRevision = 2;

    ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.size = sizeof(kpm_ranfunc_oid);
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.buf = (uint8_t*)calloc(sizeof(kpm_ranfunc_oid), sizeof(uint8_t));
    memcpy(ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.buf, kpm_ranfunc_oid, ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.size);

    kpm(&ranfunc_item->value.choice.RANfunction_Item.ranFunctionDefinition);

    // E2SM-RC RAN Function in E2AP

    ranfunc_item[1].id = ProtocolIE_IDE2_id_RANfunction_Item;
    ranfunc_item[1].criticality = Criticality_reject;
    ranfunc_item[1].value.present = RANfunction_ItemIEs__value_PR_RANfunction_Item;
    ranfunc_item[1].value.choice.RANfunction_Item.ranFunctionID = 201;
    ranfunc_item[1].value.choice.RANfunction_Item.ranFunctionRevision = 3;

    ranfunc_item[1].value.choice.RANfunction_Item.ranFunctionOID.size = sizeof(rc_ranfunc_oid);
    ranfunc_item[1].value.choice.RANfunction_Item.ranFunctionOID.buf = (uint8_t*)calloc(sizeof(rc_ranfunc_oid), sizeof(uint8_t));
    memcpy(ranfunc_item[1].value.choice.RANfunction_Item.ranFunctionOID.buf, rc_ranfunc_oid, ranfunc_item[1].value.choice.RANfunction_Item.ranFunctionOID.size);

    rcFillE2SetupReq(&ranfunc_item[1].value.choice.RANfunction_Item.ranFunctionDefinition);

    xer_fprint(stderr, &asn_DEF_RANfunction_ItemIEs, ranfunc_item);
    xer_fprint(stderr, &asn_DEF_RANfunction_ItemIEs, ranfunc_item+1);

    // Fill in list of RAN funcion
    ASN_SEQUENCE_ADD(&ranfun_list->list, ranfunc_item);
    ASN_SEQUENCE_ADD(&ranfun_list->list, ranfunc_item+1);

}
