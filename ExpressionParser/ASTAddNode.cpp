#include "ASTAddNode.h"
#include "ASTMinusTermNode.h"
#include "ExpressionException.h"

ASTAddNode::ASTAddNode(int i) : SimpleNode(i) {
}

ASTAddNode::~ASTAddNode() {
}

string ASTAddNode::infixString(int lang, NameScope* nameScope)
{
	string buffer("(");
	for (int i = 0;i < jjtGetNumChildren(); i ++){
		ASTMinusTermNode* pointer = dynamic_cast<ASTMinusTermNode*>(jjtGetChild(i));
		if (pointer){
			buffer += jjtGetChild(i)->infixString(lang, nameScope);
		}else{
			if (i>0) 
				buffer += " + ";
			buffer += jjtGetChild(i)->infixString(lang, nameScope);
		}
	}
	buffer += ")";

	return buffer;
}

void ASTAddNode::getStackElements(vector<StackElement>& elements) {
	for (int i = 0;i < jjtGetNumChildren(); i ++){
		jjtGetChild(i)->getStackElements(elements);
		if (i>0) 
			elements.push_back(StackElement(TYPE_ADD));
	}
}

double ASTAddNode::evaluate(int evalType, double* values) {

	double sum = 0;
	for (int i=0;i<jjtGetNumChildren();i++){
		sum += jjtGetChild(i)->evaluate(evalType, values);
	}
	return sum;	 
}