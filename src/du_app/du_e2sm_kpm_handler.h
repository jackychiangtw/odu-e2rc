#ifndef _KPM_H_
#define _KPM_H_
#include "common_def.h"
#include "lrg.h"
#include "lkw.x"
#include "lrg.x"
#include "legtp.h"
#include "du_app_mac_inf.h"
#include "du_app_rlc_inf.h"
#include "du_cfg.h"
#include "du_mgr_main.h"
#include "du_mgr.h"
#include "du_utils.h"
#include "E2SM-KPM-RANfunction-Description.h"
#include "RIC-EventTriggerStyle-Item.h"
#include "RIC-ReportStyle-Item.h"
#include "MeasurementInfo-Action-Item.h"
#include "ProtocolIE-Field.h"
#include "RANfunction-Item.h"
#include "E2SM-KPM-ActionDefinition.h"
#include "E2SM-KPM-ActionDefinition-Format1.h"
#include "E2SM-KPM-ActionDefinition-Format3.h"
#include "MeasurementDataItem.h"
#include "E2SM-KPM-IndicationMessage.h"
#include "E2SM-KPM-IndicationMessage-Format1.h"
#include "E2SM-KPM-IndicationMessage-Format2.h"
#include "E2SM-KPM-IndicationHeader.h"
#include "E2SM-KPM-IndicationHeader-Format1.h"
#include "TimeStamp.h"
#include "constr_TYPE.h"
#include "OCTET_STRING.h"
#include "asn_application.h"
#include "E2SM-KPM-IndicationMessage.h"
#include "E2SM-KPM-IndicationHeader-Format1.h"
#include "E2SM-KPM-EventTriggerDefinition.h"
#include "E2SM-KPM-EventTriggerDefinition-Format1.h"
#include "E2SM-KPM-IndicationHeader.h"
#include "MeasurementInfoItem.h"
#include "MeasurementCondItem.h"
#include "LabelInfoItem.h"
#include "E2AP-PDU.h"
#include "RICsubscriptionRequest.h"
#include "RICsubscriptionResponse.h"
#include "RICactionType.h"
#include "ProtocolIE-SingleContainer.h"
#include "InitiatingMessage.h"
#include "E2setupRequest.h"
#include "RANfunctionOID.h"
#include "GlobalE2node-gNB-ID.h"
#include "ProtocolIE-FieldE2.h"
#include "InitiatingMessageE2.h"
#include "SuccessfulOutcomeE2.h"
#include "odu_common_codec.h"
#include "E2nodeComponentInterfaceF1.h"
#include "MeasurementRecordItem.h"
#include "MeasurementCondUEidList.h"
#include "MeasurementCondUEidItem.h"
#include "MatchingCondItem.h"
#include "du_e2ap_msg_hdl.h"
#include "du_app_mac_inf.h"
#include "MatchingUEidList.h"

// Extend for KPM v3
#include "E2SM-KPM-RANfunction-Description-v300.h"
#include "RIC-ReportStyle-Item-v300.h"
#include "MeasurementInfo-Action-Item-v300.h"
#include "E2SM-KPM-ActionDefinition-v300.h"
#include "E2SM-KPM-ActionDefinition-Format1-v300.h"
#include "E2SM-KPM-ActionDefinition-Format3-v300.h"
#include "E2SM-KPM-IndicationMessage-v300.h"
#include "E2SM-KPM-IndicationMessage-Format1-v300.h"
#include "E2SM-KPM-IndicationMessage-Format2-v300.h"
#include "MeasurementInfoItem-v300.h"
#include "MeasurementCondItem-v300.h"
#include "LabelInfoItem-v300.h"
#include "MeasurementCondUEidList-v300.h"
#include "MeasurementCondUEidItem-v300.h"
#include "MatchingCondItem-v300.h"
<<<<<<< Updated upstream
=======
#include "E2SM-KPM-IndicationHeader-v300.h"
#include "E2SM-KPM-IndicationHeader-Format1-v300.h"

>>>>>>> Stashed changes

#define INDICATION_MSG_FMRT1 1
#define INDICATION_MSG_FMRT2 1
#define MAX_SIZE_OF_SLICE 3
#define NUM_OF_CELL_METRIC 4
#define NUM_OF_SLICE_METRIC 2
#define SIZE_OF_MACDB 1024
#define SIZE_OF_RLCDB 64
#define SIZE_OF_MAX_INDICATION_INFO 4



typedef void (*SubscriptionCallback)(E2AP_PDU_t*);
uint8_t kpmInit();
uint8_t kpmEnableIndication(bool *flag);
<<<<<<< Updated upstream
uint8_t fillRanFunctionName(RANfunction_Name_t *ranfunc_name);
=======
uint8_t fillRanFunctionName(RANfunction_Name_t *ranfunc_name, uint8_t kpmVersion);
>>>>>>> Stashed changes
uint8_t fillTriggerStyleItem(RIC_EventTriggerStyle_Item_t *trigger_style);
uint8_t fillTriggerStyleList(struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List *triggerStyleList);
uint8_t fillTriggerStyleListV3(struct E2SM_KPM_RANfunction_Description_v300__ric_EventTriggerStyle_List *triggerStyleList);
uint8_t fillReportStyleItemStyle1(RIC_ReportStyle_Item_t *report_style);
uint8_t fillReportStyleItemStyle1V3(RIC_ReportStyle_Item_v300_t *report_style);
uint8_t fillReportStyleItemStyle2(RIC_ReportStyle_Item_t *report_style);
uint8_t fillReportStyleItemStyle2V3(RIC_ReportStyle_Item_v300_t *report_style);
uint8_t fillReportStyleList(struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List *reportStyleList);
uint8_t kpmFreeRanFuncName(RANfunction_Name_t *ranfunc_name);
uint8_t kpmFreeEventTrigStyleList(struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List *eventTrigStyleList);
uint8_t kpmFreeReportStyleList(struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List *reportStyleList);
uint8_t kpmFreeRanFuncDesc(E2SM_KPM_RANfunction_Description_t *ranfunc_desc);
uint8_t kpmRanFuncDescription(RANfunctionDefinition_t  *ranFunDefinition);
uint8_t kpmRanFuncDescriptionV3(RANfunctionDefinition_t  *ranFunDefinition);
uint8_t fillMeasInfoItem(MeasurementInfoItem_t *measInfoItem, uint8_t *measName, int size);
uint8_t decapActionDefinitionFmt1(E2SM_KPM_ActionDefinition_Format1_t *actionDefinFormat1);
uint8_t decapActionDefinitionFmt3(E2SM_KPM_ActionDefinition_Format3_t *actionDefinFormat3);
uint8_t decapEventTrigDefinitionFormat1(RICeventTriggerDefinition_t *defini);
int actionFmt1measNameIsSupport(uint8_t *measNameBuf);
int actionFmt3measNameIsSupport(uint8_t *measNameBuf);
uint8_t kpmDecapActionDefinition(RICactionDefinition_t *ricdifin);
uint8_t decapActionDefinitionFmt1V3(E2SM_KPM_ActionDefinition_Format1_v300_t *actionDefinFormat1);
uint8_t decapActionDefinitionFmt3V3(E2SM_KPM_ActionDefinition_Format3_v300_t *actionDefinFormat3);
uint8_t kpmDecapActionDefinitionV3(RICactionDefinition_t *ricdifin);
uint8_t kpmFreeIndicationHeader(E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1);
uint8_t fillIndicationHeaderFormat1Optional(E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1);
uint8_t fillIndicationHeaderFormat1(E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1);
uint8_t fillRicIndicationHeader(RICindicationHeader_t *ricIndicationHeader);
<<<<<<< Updated upstream
=======
uint8_t fillIndicationHeaderFormat1OptionalV3(E2SM_KPM_IndicationHeader_Format1_v300_t *indicaHeaderFormat1);
uint8_t fillIndicationHeaderFormat1V3(E2SM_KPM_IndicationHeader_Format1_v300_t *indicaHeaderFormat1);
uint8_t fillRicIndicationHeaderV3(RICindicationHeader_t *ricIndicationHeader);
>>>>>>> Stashed changes
uint8_t fillSliceMeasDataItem(MeasurementDataItem_t *measDataItem, unsigned long intValue);
uint8_t fillMeasDataItem(MeasurementDataItem_t *item, MeasurementRecordItem_PR present, int integer, double real);
uint8_t fillIndicationMessageFormat1(E2SM_KPM_IndicationMessage_Format1_t *indicaMessageFormat1);
uint8_t fillMeasCondItem(MeasurementCondUEidItem_t *measCondItem, char measureName[], Snssai snssai);
uint8_t fillIndicationMessageFormat2(E2SM_KPM_IndicationMessage_Format2_t *indicaMessageFormat2);
uint8_t kpmFreeMeasInfoList(MeasurementInfoList_t *measInfoList);
uint8_t kpmFreeRicIndicationMessageFmt1(E2SM_KPM_IndicationMessage_Format1_t *indicaMessageFormat1);
uint8_t kpmFreeRicIndicationMessageFmt1V3(E2SM_KPM_IndicationMessage_Format1_v300_t *indicaMessageFormat1);
uint8_t fillRicindicationMessageFmt1(RICindicationMessage_t *ricIndicaMsg);
uint8_t kpmFreeMeasData(MeasurementData_t *measData);
uint8_t kpmFreeMeasLabel(MeasurementLabel_t *measLabel);
uint8_t kpmFreeMeasLabelV3(MeasurementLabel_v300_t *measLabel);
uint8_t kpmFreeMeasInfoListV3(MeasurementInfoList_v300_t *measInfoList);
uint8_t kpmFreeCondUEidList(MeasurementCondUEidList_t *measCondUEidList);
uint8_t kpmFreeRicIndicationMessageFmt2(E2SM_KPM_IndicationMessage_Format2_t *indicaMessageFormat2);
uint8_t kpmFreeRicIndicationMessageFmt2V3(E2SM_KPM_IndicationMessage_Format2_v300_t *indicaMessageFormat2);
uint8_t fillRicindicationMessageFmt2(RICindicationMessage_t *ricIndicaMsg);
uint8_t kpmFreeOctetString(OCTET_STRING_t *octetString);
void kpmSendSliceMetric();
void kpmSendCellMetric();
uint8_t kpmCalcCellMetric();
uint8_t kpmCalcSliceMetric();
void kpmStoreCellRlcMetric(CellPmList* cellMetricList);
void kpmStoreSliceRlcMetric(SlicePmList* sliceMetricList);
void kpmStoreMacMetric(MacPrbPm* macPrbPm);
bool kpmCellIndicationEnable;
bool kpmSliceIndicationEnable;
bool kpmIndicationV3Enable;

/*Pm Metric for NW Slicing from RLC to DUAPP*/
typedef struct kpmCellMacPm
{
  int usedPrb;
  int totalPrb;
}KpmCellMacPm;

typedef struct kpmCellRlcPm
{
  int ThpDl;
}KpmCellRlcPm;

typedef struct kpmCellPmDb
{ 
  long numOfMacPm;
  KpmCellMacPm eachMacPm[SIZE_OF_MACDB];
  long numOfRlcPm;
  KpmCellRlcPm eachRlcPm[SIZE_OF_RLCDB];
  int avgUsedPrb;
  int avgTotalPrb;
  float avgUsagePrb;
  int avgThpDl;
}KpmCellPmDb;

typedef struct kpmSliceMacPm
{
  int usedPrb;
}KpmSliceMacPm;

typedef struct kpmSliceMacPmList
{
  int numOfSlice;
  KpmSliceMacPm sliceRecord[MAX_SIZE_OF_SLICE];
}KpmSliceMacPmList;

typedef struct kpmSliceRlcPm
{
  int ThpDl;
}KpmSliceRlcPm;

typedef struct kpmSliceRlcPmList
{
  int numOfSlice;
  KpmSliceRlcPm sliceRecord[MAX_SIZE_OF_SLICE];
}KpmSliceRlcPmList;

typedef struct kpmSlicePmDb
{ 
  long numOfMacPm;
  KpmSliceMacPmList eachMacPm[SIZE_OF_MACDB];
  long numOfRlcPm;
  KpmSliceRlcPmList eachRlcPm[SIZE_OF_RLCDB];
  int numOfSlice;
  Snssai snssai[MAX_SIZE_OF_SLICE];
  int avgUsedPrb[MAX_SIZE_OF_SLICE];
  int avgThpDl[MAX_SIZE_OF_SLICE];
}KpmSlicePmDb;

KpmCellPmDb  kpmCellPmDb;
KpmSlicePmDb kpmSlicePmDb;

extern RICindicationMessage_t *ricIndicationMessage;

uint32_t reportingPeriodFmt1, reportingPeriodFmt3, reportingPeriod;
uint32_t indicationCountFmt1, indicationCountFmt3;
<<<<<<< Updated upstream
uint8_t indicationMeasNameFmt1 [SIZE_OF_MAX_INDICATION_INFO][25], indicationMeasNameFmt3 [SIZE_OF_MAX_INDICATION_INFO][25];
=======
uint8_t indicationMeasNameFmt1[SIZE_OF_MAX_INDICATION_INFO][25], indicationMeasNameFmt3[SIZE_OF_MAX_INDICATION_INFO][25];
>>>>>>> Stashed changes
int sizeOfMeasNameFmt1, sizeOfMeasNameFmt3;


#endif
