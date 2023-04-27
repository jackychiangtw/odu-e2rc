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
#include "E2SM-KPM-RANfunction-Description.h"
#include "RIC-EventTriggerStyle-Item.h"
#include "RIC-ReportStyle-Item.h"
#include "MeasurementInfo-Action-Item.h"
#include "ProtocolIE-Field.h"
#include "RANfunction-Item.h"
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
#include "E2SM-KPM-RANfunction-Description.h"
#include "E2SM-KPM-IndicationHeader-Format1.h"
#include "E2SM-KPM-EventTriggerDefinition.h"
#include "E2SM-KPM-EventTriggerDefinition-Format1.h"
#include "E2SM-KPM-IndicationHeader.h"
#include "MeasurementInfoItem.h"
#include "MeasurementCondItem.h"
#include "LabelInfoItem.h"
#include "E2SM-KPM-ActionDefinition.h"
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
#include "MatchingCondItem-Choice.h"
#include "MatchingCondItem.h"
#include "du_e2ap_msg_hdl.h"
#include "du_app_mac_inf.h"

#define INDICATION_MSG_FMRT1 1
#define INDICATION_MSG_FMRT2 1
#define MAX_SIZE_OF_SLICE 2
#define NUM_OF_CELL_METRIC 4
#define NUM_OF_SLICE_METRIC 2
#define SIZE_OF_MACDB 512

typedef void (*SubscriptionCallback)(E2AP_PDU_t*);
uint8_t kpm(RANfunctionDefinition_t  *ranFunDefinition);
uint8_t fillActionDefinition(RICactionDefinition_t **ricdifin);
uint8_t fillEventTrigDefinitionFormat1(RICeventTriggerDefinition_t *eventTrigDefi);
uint8_t decapEventTrigDefinitionFormat1(RICeventTriggerDefinition_t *defini);
uint8_t decapActionDefinition(RICactionDefinition_t *ricdifin);
uint8_t fillIndicationHeaderFormat1(E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1);
uint8_t fillRicIndicationHeader(RICindicationHeader_t *ricIndicationHeader);
uint8_t fillMeasDataItem(MeasurementDataItem_t *item, MeasurementRecordItem_PR present, int integer, double real);
uint8_t fillIndicationMessageFormat1(E2SM_KPM_IndicationMessage_Format1_t *indicaMessageFormat1);
uint8_t fillRicindicationMessage(RICindicationMessage_t *ricIndicationMessage);


struct ran_func_info {
    long ranFunctionId;
    OCTET_STRING_t *ranFunctionDesc;
    long ranFunctionRev;
    PrintableString_t *ranFunctionOId;
  };

bool kpmCellIndicationEnable;
bool kpmSliceIndicationEnable;

/*Pm Metric for NW Slicing from RLC to DUAPP*/
typedef struct kpmSlicePm
{
  Snssai snssai;
  double ThpDl;
}KpmSlicePm;

typedef struct kpmSlicePmList{
  int numOfSlice;
  KpmSlicePm *sliceRecord;
}KpmSlicePmList;

typedef struct kpmMacPm{
  int usedPrb;
  int totalPrb;
  float usagePrb;
}KpmMacPm;

typedef struct kpmMacDb{
  int numOfMeas;
  KpmMacPm **macRecord;
}KpmMacDb;

KpmMacDb kpmMacDb;
KpmSlicePmList kpmSlicePmItem;

extern RICindicationMessage_t *ricIndicationMessage;

KpmMacPm kpmGetAvgMetric(KpmMacDb *kpmMacDb);
void kpmSendSliceMetric(SlicePmList* sliceMetricList);
void kpmSendCellMetric(CellPmList* cellMetricList);


#endif
