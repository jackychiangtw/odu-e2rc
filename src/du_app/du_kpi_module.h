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
#define PHY_STUB_RATIO 2

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

/*Database for cell performance metrics*/
typedef struct kpmCellPmDb
{ 
  int numOfMacPm; // index of stored MAC performace metrics. replaced by indexOfCellMacPm, due to memory problem
  KpmCellMacPm eachMacPm[SIZE_OF_MACDB]; // perofrmance metrics in MAC
  int numOfRlcPm; // index of stored RLC performace metrics. replaced by indexOfCellRlcPm, due to memory problem
  KpmCellRlcPm eachRlcPm[SIZE_OF_RLCDB]; // perofrmance metrics in RLC
  int avgUsedPrb; // Avg performace metrics in Database
  int avgTotalPrb;
  float avgUsagePrb;
  int avgThpDl;
}KpmCellPmDb;

/*Data structure for storing slice performance metric in MAC*/
typedef struct kpmSliceMacPm
{
  int usedPrb;
}KpmSliceMacPm;

/*The list for storing all slice performance metric in MAC*/
typedef struct kpmSliceMacPmList
{
  int numOfSlice;
  KpmSliceMacPm sliceRecord[MAX_SIZE_OF_SLICE];
}KpmSliceMacPmList;

/*Data structure for storing slice performance metric in RLC*/
typedef struct kpmSliceRlcPm
{
  int ThpDl;
}KpmSliceRlcPm;

/*The list for storing all slice performance metric in RLC*/
typedef struct kpmSliceRlcPmList
{
  int numOfSlice;
  KpmSliceRlcPm sliceRecord[MAX_SIZE_OF_SLICE];
}KpmSliceRlcPmList;

/*Database for slice performance metrics*/
typedef struct kpmSlicePmDb
{ 
  int numOfMacPm; // index of stored MAC performace metrics. replaced by indexOfSliceMacPm, due to memory problem
  KpmSliceMacPmList eachMacPm[SIZE_OF_MACDB]; // performance metrics in MAC
  int numOfRlcPm; // index of stored RLC performace metrics. replaced by indexOfSliceRlcPm, due to memory problem
  KpmSliceRlcPmList eachRlcPm[SIZE_OF_RLCDB]; // perofrmance metrics in RLC
  int numOfSlice; // Number of slice
  Snssai snssai[MAX_SIZE_OF_SLICE]; // slice info
  int avgUsedPrb[MAX_SIZE_OF_SLICE]; // Avg performace metrics in Database
  int avgThpDl[MAX_SIZE_OF_SLICE];
  int smo_avgUsedPrb[MAX_SIZE_OF_SLICE];
  int smo_avgThpDl[MAX_SIZE_OF_SLICE];
}KpmSlicePmDb;

KpmCellPmDb  kpmCellPmDb; // Store cell performance metrics
KpmSlicePmDb kpmSlicePmDb; // Store slice performance metrics

int32_t indicationRlcCellCount, indicationRlcSliceCount, indicationMacCellCount, indicationMacSliceCount; // Size of stored performace metrics in this interval
int indexOfSliceRlcPm, indexOfSliceMacPm, indexOfCellRlcPm, indexOfCellMacPm; // Stored performace metrics in Database
bool kpmCellIndicationEnable;
bool kpmSliceIndicationEnable;
int32_t smoRlcSliceCount, smoMacSliceCount; // Size of stored performace metrics in this interval

#endif

