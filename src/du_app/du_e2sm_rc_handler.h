#ifndef _RC_H_
#define _RC_H_
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "RICcontrolRequest.h"
#include "RICcontrolHeader.h"
#include "RICcontrolMessage.h"
#include "E2SM-RC-ControlHeader.h"
#include "E2SM-RC-ControlHeader-Format1.h"
#include "E2SM-RC-ControlMessage.h"
#include "E2SM-RC-ControlMessage-Format1.h"


void procE2rcCtrlHeader(RICcontrolHeader_t *RICcontrolHeader);
void procE2rcCtrlMessage(RICcontrolMessage_t *RICcontrolMessage);

#endif
