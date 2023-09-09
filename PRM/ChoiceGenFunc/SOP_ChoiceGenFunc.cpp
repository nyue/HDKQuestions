#include "SOP_ChoiceGenFunc.h"

// This is an automatically generated header file based on theDsFile, below,
// to provide SOP_StarParms, an easy way to access parameter values from
// SOP_StarVerb::cook with the correct type.
#include "SOP_ChoiceGenFunc.proto.h"

#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <PRM/PRM_SpareData.h>
#include <CH/CH_LocalVariable.h>
#include <UT/UT_Interrupt.h>
#include <UT/UT_Ramp.h>
#include <SYS/SYS_Math.h>
#include <OP/OP_AutoLockInputs.h>
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
		int index=0;
		if (sop)
		{
			for (ChoiceMapType::const_iterator iter = sop->choiceMap().begin();
					iter != sop->choiceMap().end();
					++iter,index++)
			{
				theMenu[index].setToken(iter->second.c_str());
				theMenu[index].setLabel(iter->second.c_str());
			}
		}
		theMenu[index].setToken(0); // Terminator
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
		PRM_Template(PRM_STRING, 1, &choiceName, 0, &generatedBitDepthMenu, 0, &SOP_ChoiceGenFunc::choiceCallbackFunc),
		PRM_Template(),
};

const SOP_ChoiceGenFunc::ChoiceMapType& SOP_ChoiceGenFunc::choiceMap() const
{
	return _choices;
}

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

	_choices.clear();
	size_t _choice_index=0;

	OP_AutoLockInputs inputs(this);
	if (inputs.lock(context) >= UT_ERROR_ABORT)
		return error();

	fpreal now = context.getTime();

	duplicateSource(0, context);

	setCurGdh(0, myGdpHandle);

	const GA_AttributeDict &attribDict = gdp->getAttributeDict(GA_ATTRIB_POINT);
	for (GA_AttributeDict::iterator iter = attribDict.begin();
			iter!=attribDict.end();
			++iter,_choice_index++)
	{
		GA_Attribute *detail_attrib = iter.attrib();
		_choices.insert(ChoiceMapType::value_type(_choice_index,detail_attrib->getName().c_str()));
	}

	return error();
}
