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


uint8_t smFillE2SetupReq(RANfunctions_List_t  *ranfun_list);



#endif
