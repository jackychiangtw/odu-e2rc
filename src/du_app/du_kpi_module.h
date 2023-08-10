#ifndef _KPI_MODULE_H_
#define _KPI_MODULE_H_
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

#ifdef O1_ENABLE

#include "AlarmInterface.h"
#include "CmInterface.h"
#include "PmInterface.h"
#endif 


uint8_t calcSmoMetric();
void kpiModuleInit();
void kpmStoreCellRlcMetric(CellPmList* cellMetricList);
void kpmStoreSliceRlcMetric(SlicePmList* sliceMetricList);
void kpmStoreMacMetric(MacPrbPm* macPrbPm);
uint8_t kpmCalcCellMetric();
uint8_t kpmCalcSliceMetric();

#define SIZE_OF_MACDB 10240
#define SIZE_OF_RLCDB 512
#define MAX_SIZE_OF_SLICE 3
#define SMO_REPORT_PERIOD 15


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
  int numOfMacPm; // replaced by indexOfCellMacPm
  KpmCellMacPm eachMacPm[SIZE_OF_MACDB];
  int numOfRlcPm; // replaced by indexOfCellRlcPm
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
  int numOfMacPm; // replaced by indexOfSliceMacPm
  KpmSliceMacPmList eachMacPm[SIZE_OF_MACDB];
  int numOfRlcPm; // replaced by indexOfSliceRlcPm
  KpmSliceRlcPmList eachRlcPm[SIZE_OF_RLCDB];
  int numOfSlice;
  Snssai snssai[MAX_SIZE_OF_SLICE];
  int avgUsedPrb[MAX_SIZE_OF_SLICE];
  int avgThpDl[MAX_SIZE_OF_SLICE];
  int smo_avgUsedPrb[MAX_SIZE_OF_SLICE];
  int smo_avgThpDl[MAX_SIZE_OF_SLICE];
}KpmSlicePmDb;

KpmCellPmDb  kpmCellPmDb;
KpmSlicePmDb kpmSlicePmDb;

int32_t indicationRlcCellCount, indicationRlcSliceCount, indicationMacCellCount, indicationMacSliceCount;
int indexOfSliceRlcPm, indexOfSliceMacPm, indexOfCellRlcPm, indexOfCellMacPm;
bool kpmCellIndicationEnable;
bool kpmSliceIndicationEnable;
int32_t smoRlcSliceCount, smoMacSliceCount;

#endif

