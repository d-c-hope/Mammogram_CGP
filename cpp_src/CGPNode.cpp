#include <iostream>
#include "CGPNode.h"

using namespace std;

// ----------------------------------------------------------------------------
// CGPFunction
//
// constructor
// ----------------------------------------------------------------------------
CGPNode::CGPNode() {
	isValid = false;
	output = -1;
	function = 0;

} // --- CGPFunction ----------------------------------------------------------



// ----------------------------------------------------------------------------
// CGPFunction
//
// constructor
// ----------------------------------------------------------------------------
CGPNode::CGPNode(const CGPNode& node) {
	inputs = node.inputs;
	function = node.function;
	isValid = node.isValid;
	output = node.output;

} // --- CGPFunction ----------------------------------------------------------



CGPNode& CGPNode::operator= (const CGPNode& node) {
		inputs = node.inputs;
		function = node.function;
		isValid = node.isValid;
		output = node.output;
		return *this;

	}