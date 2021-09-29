#include "SOP_ChoiceGenFunc.h"

#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <PRM/PRM_SpareData.h>
#include <CH/CH_LocalVariable.h>
#include <UT/UT_Interrupt.h>
#include <UT/UT_Ramp.h>
#include <SYS/SYS_Math.h>
#include <hboost/format.hpp>

void
newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(new OP_Operator(
			"choicegenfunc",                   // Internal name
			"Choice Generator Function",       // UI name
			SOP_ChoiceGenFunc::myConstructor,  // How to build the SOP
			SOP_ChoiceGenFunc::myTemplateList, // My parameters
			1,                                 // Min # of sources
			1                                  // Max # of sources
			));
}

void
SOP_ChoiceGenFunc::choiceMenuBuilder(void *data, PRM_Name *theMenu, int theMaxSize, const PRM_SpareData *, PRM_Parm *)
{
	printf("SOP_ChoiceGenFunc::choiceMenuBuilder()\n");
	{
		SOP_ChoiceGenFunc* sop = reinterpret_cast<SOP_ChoiceGenFunc*>(data);
		if( sop )
		{
			int index=0;

			theMenu[index].setToken("auto");
			theMenu[index].setLabel("Auto Detect");
			index++;
			theMenu[index].setToken("fp16");
			theMenu[index].setLabel("16bit Float");
			index++;
			theMenu[index].setToken("fp32");
			theMenu[index].setLabel("Float");
			index++;
			theMenu[index].setToken("fp64");
			theMenu[index].setLabel("Double");
			index++;

			theMenu[index].setToken(0);
			theMenu[index].setLabel(0);

		}
		else
		{
			theMenu[0].setToken(0);
			theMenu[0].setLabel(0);
		}
	}
}

static PRM_ChoiceList generatedBitDepthMenu(PRM_CHOICELIST_SINGLE, (PRM_ChoiceGenFunc)SOP_ChoiceGenFunc::choiceMenuBuilder);
static PRM_Name choiceName("choices", "My Choices");

int SOP_ChoiceGenFunc::choiceCallbackFunc(void *data, int index, fpreal t, const PRM_Template *tplate)
{
	printf("SOP_ChoiceGenFunc::choiceCallbackFunc()\n");
	/*
	SOP_ChoiceGenFunc* ptr = reinterpret_cast<SOP_ChoiceGenFunc*>(data);
	if (ptr)
		ptr->helloWorld();
		*/
	printf("index = %d\n",index);
	printf("t = %f\n",t);
	return 0; // Return 1 to refresh the UI ?
}

PRM_Template
SOP_ChoiceGenFunc::myTemplateList[] = {
		PRM_Template(PRM_ORD, 1, &choiceName, 0, &generatedBitDepthMenu, 0, &SOP_ChoiceGenFunc::choiceCallbackFunc),
		PRM_Template(),
};

OP_Node *
SOP_ChoiceGenFunc::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
	return new SOP_ChoiceGenFunc(net, name, op);
}

SOP_ChoiceGenFunc::SOP_ChoiceGenFunc(OP_Network *net, const char *name, OP_Operator *op)
: SOP_Node(net, name, op)
{
	printf("SOP_ChoiceGenFunc constructor\n");
}

SOP_ChoiceGenFunc::~SOP_ChoiceGenFunc()
{
	printf("SOP_ChoiceGenFunc destructor\n");
}

void SOP_ChoiceGenFunc::helloWorld() const
{
	printf("SOP_ChoiceGenFunc::helloWorld()\n");
}

OP_ERROR SOP_ChoiceGenFunc::cookMySop(OP_Context &context)
{
	printf("SOP_ChoiceGenFunc::cookMySop()\n");
	return error();
}
