#ifndef _E2SM_
#define _E2SM_
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
#include "TimeStamp.h"
#include "constr_TYPE.h"
#include "OCTET_STRING.h"
#include "asn_application.h"
#include "E2SM-KPM-RANfunction-Description.h"
#include "du_e2sm_kpm_handler.h"
#include "du_e2sm_rc_handler.h"

#define SIZE_OF_SERVICE_MODEL 3
#define USING_SERVICE_MODEL 3

#define INDEX_OF_KPM_V2 2
#define INDEX_OF_KPM_V3 0
#define INDEX_OF_RC 1

uint8_t smFillE2SetupReq(RANfunctions_List_t  *ranfun_list);
uint8_t smProcEventTrigDefinition(RICeventTriggerDefinition_t *eventTrigDefini, uint32_t ranFuncId, long reqId, long instanceId);
uint8_t smProcActionDefinition(RICactionDefinition_t *acitiondifin, uint32_t ranFuncId, long reqId, long instanceId);
uint8_t smProcRicCtrlHeader(RICcontrolHeader_t *ricCtrlHdr, uint32_t ranFuncId, long reqId, long instanceId);
uint8_t smProcRicCtrlMessage(RICcontrolMessage_t *ricCtrlMsg, uint32_t ranFuncId, long reqId, long instanceId);

typedef struct ran_func_info {
    long ranFunctionId;
    long ranFunctionRev;
    uint8_t ranFunctionOId[30];
    uint8_t (*fillRanFuncDescription)(RANfunctionDefinition_t*);
    uint8_t (*decapEventTrigDefinition)(RICeventTriggerDefinition_t*);
    uint8_t (*decapActionDefinition)(RICactionDefinition_t*);
    uint8_t (*procRicCtrlMessage)(RICcontrolMessage_t*);
    uint8_t (*procRicCtrlHeader)(RICcontrolHeader_t*);
}RanFuncInfo;

RanFuncInfo ranFuncInfo[SIZE_OF_SERVICE_MODEL];

#endif
