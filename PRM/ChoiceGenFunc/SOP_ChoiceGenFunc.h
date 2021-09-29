#pragma once

#include <SOP/SOP_Node.h>

class SOP_ChoiceGenFunc : public SOP_Node
{
public:
	static OP_Node *myConstructor(OP_Network*, const char *,
			OP_Operator *);

	/// Stores the description of the interface of the SOP in Houdini.
	/// Each parm template refers to a parameter.
	static PRM_Template myTemplateList[];

	void helloWorld() const;

	static int choiceCallbackFunc(void *data, int index, fpreal t, const PRM_Template *tplate);
	static void
	choiceMenuBuilder(void *data, PRM_Name *theMenu, int theMaxSize, const PRM_SpareData *, PRM_Parm *);

protected:
	SOP_ChoiceGenFunc(OP_Network *net, const char *name, OP_Operator *op);
	~SOP_ChoiceGenFunc() override;

	OP_ERROR            cookMySop(OP_Context &context) override;

private:
};
