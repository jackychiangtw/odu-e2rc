#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "du_e2sm_rc_handler.h"
#include "RICcontrolRequest.h"
#include "RICcontrolHeader.h"
#include "RICcontrolMessage.h"
#include "E2SM-RC-ControlHeader.h"
#include "E2SM-RC-ControlHeader-Format1.h"
#include "E2SM-RC-ControlMessage.h"
#include "E2SM-RC-ControlMessage-Format1.h"
#include "E2SM-RC-ControlMessage-Format1-Item.h"
#include "RANParameter-ValueType.h"
#include "RANParameter-Value.h"
#include "RANParameter-STRUCTURE.h"
#include "RANParameter-STRUCTURE-Item.h"
#include "RANParameter-ValueType-Choice-Structure.h"
#include "RANParameter-ValueType-Choice-ElementFalse.h"

// Function to insert a node at the beginning of the linked list
void paraID_push(paraID** head_ref, int new_data) {
    paraID* new_node = (paraID*)malloc(sizeof(paraID));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Function to print the linked list
void print_paraID_List(paraID* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int procE2rcRanStructItem(RANParameter_STRUCTURE_Item_t *ranStructItem, paraID *paraIdLinkList){
	printf("\nINFO  -->  E2SM_RC handler : RAN Parameter ID = %ld\n", ranStructItem->ranParameter_ID);
	paraID_push(&paraIdLinkList, ranStructItem->ranParameter_ID);

	if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_ElementTrue){
		printf("\nERROR  -->  E2SM_RC handler : Control Message Element True Item isn't supported\n");
		return -1;
	}
	else if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_ElementFalse){
		procE2rcRanElemFalse(ranStructItem->ranParameter_valueType->choice.ranP_Choice_ElementFalse, paraIdLinkList);
	}
	else if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_Structure){
		procE2rcRanStruct(ranStructItem->ranParameter_valueType->choice.ranP_Choice_Structure, paraIdLinkList);
	}
	else if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_List){
		printf("\nERROR  -->  E2SM_RC handler : Control Message Element List Item isn't supported\n");
		return -1;
	}
	else{
		printf("\nERROR  -->  E2SM_RC handler : Unknown Control Message Element Item\n");
		return -1;
	}

}

int procE2rcRanStruct(RANParameter_ValueType_Choice_Structure_t *ranParaChoiceStruct, paraID *paraIdLinkList){
	RANParameter_STRUCTURE_t *ranParaStruct = ranParaChoiceStruct->ranParameter_Structure;
	//xer_fprint(stdout, &asn_DEF_RANParameter_STRUCTURE, ranParaStruct);
	for(int i=0;i<ranParaStruct->sequence_of_ranParameters->list.count;i++){
		procE2rcRanStructItem(ranParaStruct->sequence_of_ranParameters->list.array[i], paraIdLinkList);
	}
}

int procE2rcRanElemFalse(RANParameter_ValueType_Choice_ElementFalse_t *ranParaChoiceElementFalse, paraID *paraIdLinkList){
	RANParameter_Value_t *ranParaValue = ranParaChoiceElementFalse->ranParameter_value;
	switch(ranParaValue->present){
		case RANParameter_Value_PR_valueOctS:
			printf("Parameter ID: ");
			print_paraID_List(paraIdLinkList);
			printf("Value: ");
			for(int i=0;i<ranParaValue->choice.valueOctS.size;i++){
				printf("%x ", ranParaValue->choice.valueOctS.buf[i]);
			}
			printf("\n");
			break;
		default:
			printf("\nERROR  -->  E2SM_RC handler : Value type isn't supported\n");
			return -1;
			break;
	}
}

int procE2rcMessageFrmt1Item(E2SM_RC_ControlMessage_Format1_Item_t *ctrlFrmt1, paraID *paraIdLinkList){
	printf("\nINFO  -->  E2SM_RC handler : RAN Parameter ID = %ld\n", ctrlFrmt1->ranParameter_ID);
	paraID_push(&paraIdLinkList, ctrlFrmt1->ranParameter_ID);

	if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_ElementTrue){
		printf("\nERROR  -->  E2SM_RC handler : Control Message Element True Item isn't supported\n");
		return -1;
	}
	else if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_ElementFalse){
		procE2rcRanElemFalse(ctrlFrmt1->ranParameter_valueType.choice.ranP_Choice_ElementFalse, paraIdLinkList);
	}
	else if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_Structure){
		procE2rcRanStruct(ctrlFrmt1->ranParameter_valueType.choice.ranP_Choice_Structure, paraIdLinkList);
	}
	else if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_List){
		printf("\nERROR  -->  E2SM_RC handler : Control Message Element List Item isn't supported\n");
    	return -1;
	}
	else{
		printf("\nERROR  -->  E2SM_RC handler : Unknown Control Message Element Item\n");
		return -1;
	}

}

int procE2rcMessageFrmt1List(E2SM_RC_ControlMessage_Format1_t *ctrlFrmt1_list){
	paraID* paraIdHead = NULL;
	for(int i=0;i<ctrlFrmt1_list->ranP_List.list.count;i++){
		procE2rcMessageFrmt1Item(ctrlFrmt1_list->ranP_List.list.array[i], paraIdHead);
	}
}

void procE2rcCtrlHeader(RICcontrolHeader_t *ricControlHeader){
    asn_dec_rval_t  rval;
	E2SM_RC_ControlHeader_t *ctrlHeader = (E2SM_RC_ControlHeader_t*)calloc(1, sizeof(E2SM_RC_ControlHeader_t));;

	printf("\nINFO   -->  E2SM_RC handler : Process RIC Control Header<<<<\n");
    rval = aper_decode(0, &asn_DEF_E2SM_RC_ControlHeader, (void **)&ctrlHeader, ricControlHeader->buf, ricControlHeader->size, 0, 0);

    xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlHeader, ctrlHeader);

    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
   	{
      printf("\nERROR  -->  E2SM_RC handler : Control Header ASN decode failed\n");
   	}

    printf("\nINFO  -->  E2SM_RC Handler : Header Format = %d", ctrlHeader->ric_controlHeader_formats.present);
    printf("\nINFO  -->  E2SM_RC Handler : RIC Style Type = %ld", ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_Style_Type);
    printf("\nINFO  -->  E2SM_RC Handler : RIC Control Action ID = %ld", ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_ControlAction_ID);
}


void procE2rcCtrlMessage(RICcontrolMessage_t *ricControlMessage){
    asn_dec_rval_t  rval;
    E2SM_RC_ControlMessage_t *ctrlMessage = (E2SM_RC_ControlMessage_t*)calloc(1, sizeof(E2SM_RC_ControlMessage_t));

    printf("\nINFO   -->  E2SM_RC handler : Process RIC Control Message<<<<\n");
    rval = aper_decode(0, &asn_DEF_E2SM_RC_ControlMessage, (void **)&ctrlMessage, ricControlMessage->buf, ricControlMessage->size, 0, 0);

    xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlMessage, ctrlMessage);
    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
    {
	    printf("\nERROR  -->  E2SM_RC handler : Control Message ASN decode failed %d, %ld\n", rval.code, rval.consumed);
	  	return -1;
    }

    if(ctrlMessage->ric_controlMessage_formats.present == E2SM_RC_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format2){
    	printf("\nERROR  -->  E2SM_RC handler : Control Message format 2 isn't supported\n");
    	return -1;
    }
    else{
    	procE2rcMessageFrmt1List(ctrlMessage->ric_controlMessage_formats.choice.controlMessage_Format1);
    }
    

}
