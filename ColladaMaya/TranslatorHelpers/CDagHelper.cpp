/*
	Copyright (C) 2005-2007 Feeling Software Inc.
	Portions of the code are:
	Copyright (C) 2005-2007 Sony Computer Entertainment America
	Copyright (C) 2004-2005 Alias Systems Corp.
	
	MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "StdAfx.h"

#include "CDagHelper.h"
#include <maya/MFnAttribute.h>
#include <maya/MFnComponentListData.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnMatrixData.h>
#include <maya/MFnNumericData.h>
#include <maya/MFnSet.h>
#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MFnSkinCluster.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MDGModifier.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnStringArrayData.h>

MObject CDagHelper::GetNodeConnectedTo(const MObject& node, const MString& attribute)
//
// Find a node connected to a node's attribute
//
{
	MPlug plug;
	if (GetPlugConnectedTo(node, attribute, plug))
	{
		return plug.node();
	}
	else
	{
		return MObject::kNullObj;
	}
}

MObject	CDagHelper::GetSourceNodeConnectedTo(const MObject& node, const MString& attribute)
{
	MStatus status;
	MFnDependencyNode dgFn(node);
	MPlug plug = dgFn.findPlug(attribute, &status);
	if (status == MS::kSuccess && plug.isConnected())
	{
		// Get the connection - there can be at most one input to a plug
		//
		MPlugArray connections;
		plug.connectedTo(connections, true, false);
		if (connections.length() > 0)
		{
			return connections[0].node();
		}
	}
	return MObject::kNullObj;
}

MObject CDagHelper::GetSourceNodeConnectedTo(const MPlug& inPlug)
{
	MStatus status;
	MPlugArray connections;
	inPlug.connectedTo(connections, true, false);
	if (connections.length() > 0)
	{
		return connections[0].node();
	}
	return MObject::kNullObj;
}

bool CDagHelper::GetPlugConnectedTo(const MObject& node, const MString& attribute, MPlug& connectedPlug)
{
	MStatus status;
	MFnDependencyNode dgFn(node);
	MPlug plug = dgFn.findPlug(attribute, &status);
	if (status == MS::kSuccess && plug.isConnected())
	{
		// Get the connection - there can be at most one input to a plug
		//
		MPlugArray connections;
		plug.connectedTo(connections, true, true);
		if (connections.length() > 0)
		{
			connectedPlug = connections[0];
			return true;
		}
	}
	return false;
}

bool CDagHelper::GetPlugConnectedTo(const MPlug& inPlug, MPlug& plug)
{
	MStatus status;

	MPlugArray connections;
	inPlug.connectedTo(connections, true, true);
	if (connections.length() > 0)
	{
		plug = connections[0];
		return true;
	}

	return false;
}

MObject CDagHelper::GetNodeConnectedTo(const MPlug& plug)
//
// Get the node connected to a plug
//
{
	MStatus status;
	MPlugArray connections;
	plug.connectedTo(connections, true, true, &status);
	if (status != MStatus::kSuccess) return MObject::kNullObj;
	if (connections.length() <= 0) return MObject::kNullObj;
	return connections[0].node();
}

//
// Find a node connected to a node's array attribute
//
bool CDagHelper::GetPlugArrayConnectedTo(const MObject& node, const MString& attribute, MPlug& connectedPlug)
{
	MStatus status;
	MFnDependencyNode dgFn(node);
	MPlug plug = dgFn.findPlug(attribute, &status);
	if (status != MS::kSuccess)
	{
		MGlobal::displayWarning(MString("couldn't find plug on attribute ") + 
			attribute + MString(" on object ") + dgFn.name());
		return false;
	}

	if (plug.numElements() < 1)
	{
		MGlobal::displayWarning(MString("plug array doesn't have any connection on attribute ") + 
			attribute + MString(" on object ") + dgFn.name());
		return false;
	}

	MPlug firstElementPlug = plug.connectionByPhysicalIndex(0);

	// Get the connection - there can be at most one input to a plug
	//
	MPlugArray connections;
	firstElementPlug.connectedTo(connections, true, true);
	if (connections.length() == 0)
	{
		MGlobal::displayWarning(MString("plug connected to an empty array on attribute ") + 
			attribute + MString(" on object ") + dgFn.name());
		return false;
	}

	connectedPlug = connections[0];
	return true;
}

bool CDagHelper::Connect(const MObject& source, const MString& sourceAttribute, const MObject& destination, const MString& destinationAttribute)
{
	MStatus status;
	MFnDependencyNode srcFn(source);
	MFnDependencyNode destFn(destination);

	MPlug src = srcFn.findPlug(sourceAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	MPlug dest = destFn.findPlug(destinationAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	MDGModifier modifier;
	modifier.connect(src, dest);
	status = modifier.doIt();

	return status == MStatus::kSuccess;
}

bool CDagHelper::Connect(const MObject& source, const MString& sourceAttribute, const MPlug& destination)
{
	MStatus status;
	MFnDependencyNode srcFn(source);

	MPlug src = srcFn.findPlug(sourceAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	MDGModifier modifier;
	modifier.connect(src, destination);
	status = modifier.doIt();

	return status == MStatus::kSuccess;
}

bool CDagHelper::Connect(const MPlug& source, const MObject& destination, const MString& destinationAttribute)
{
	MStatus status;
	MFnDependencyNode destFn(destination);

	MPlug dst = destFn.findPlug(destinationAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	MDGModifier modifier;
	status = modifier.connect(source, dst);
	if (status != MStatus::kSuccess) return false;
	status = modifier.doIt();

	return status == MStatus::kSuccess;
}

bool CDagHelper::Connect(const MPlug& source, const MPlug& destination)
{
	MDGModifier modifier;
	modifier.connect(source, destination);
	MStatus status = modifier.doIt();

	return status == MStatus::kSuccess;
}

bool CDagHelper::ConnectToList(const MObject& source, const MString& sourceAttribute, const MObject& destination, const MString& destinationAttribute, int* index)
{
	MStatus status;
	MFnDependencyNode srcFn(source);

	MPlug src = srcFn.findPlug(sourceAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	return ConnectToList(src, destination, destinationAttribute, index);
}

bool CDagHelper::ConnectToList(const MPlug& source, const MObject& destination, const MString& destinationAttribute, int* _index)
{
	MStatus status;
	MFnDependencyNode destFn(destination);
	MPlug dest = destFn.findPlug(destinationAttribute, &status);
	if (status != MStatus::kSuccess) return false;
	if (!dest.isArray()) return false;

	int index = (_index != NULL) ? *_index : -1;
	if (index < 0)
	{
		index = GetNextAvailableIndex(dest, (int) dest.evaluateNumElements());
		if (_index != NULL) *_index = index;
	}

	MPlug d = dest.elementByLogicalIndex(index);
	MDGModifier modifier;
	modifier.connect(source, d);
	status = modifier.doIt();
	return status == MStatus::kSuccess;
}

int CDagHelper::GetNextAvailableIndex(const MObject& object, const MString& attribute, int startIndex)
{
	MPlug p = MFnDependencyNode(object).findPlug(attribute);
	if (p.node().isNull()) return -1;
	return GetNextAvailableIndex(p, startIndex);
}

int CDagHelper::GetNextAvailableIndex(const MPlug& p, int startIndex)
{
	if (startIndex < 0) startIndex = 0;

	// Look for the next available plug
	for (uint i = (uint) startIndex; i < (uint) startIndex + 100; ++i)
	{
		MPlug possibleDestination = p.elementByLogicalIndex(i);
		if (!CDagHelper::HasConnection(possibleDestination))
		{
			return i;
		}
	}
	return -1;
}

bool CDagHelper::HasConnection(const MPlug& plug, bool asSource, bool asDestination)
{
	MPlugArray plugs;
	plug.connectedTo(plugs, asDestination, asSource);
	if (plugs.length() > 0) return true;

	return plug.numConnectedChildren() > 0;
}

// Retrieve the bind pose for a controller/joint pair
//
MMatrix CDagHelper::GetBindPoseInverse(const MObject& controller, const MObject& influence)
{
	MStatus status;
	if (controller.apiType() == MFn::kSkinClusterFilter)
	{
		MFnSkinCluster controllerFn(controller);

		// Find the correct index for the pre-bind matrix
		uint index = controllerFn.indexForInfluenceObject(MDagPath::getAPathTo(influence), &status);
		if (status != MStatus::kSuccess) return MMatrix::identity;

		MPlug preBindMatrixPlug = controllerFn.findPlug("bindPreMatrix", &status);
		preBindMatrixPlug = preBindMatrixPlug.elementByLogicalIndex(index, &status);
		if (status != MStatus::kSuccess) return MMatrix::identity;

		// Get the plug's matrix
		MMatrix ret;
		if (!CDagHelper::GetPlugValue(preBindMatrixPlug, ret)) return MMatrix::identity;
		return ret;
	}
	else if (controller.apiType() == MFn::kJointCluster)
	{
		MMatrix ret;
		CDagHelper::GetPlugValue(influence, "bindPose", ret);
		return ret.inverse();
	}
	else return MMatrix::identity;
}

// set the bind pose for a transform
//
MStatus CDagHelper::SetBindPoseInverse(const MObject& node, const MMatrix& bindPoseInverse)
{
	MStatus status;
	MFnDependencyNode dgFn(node);
	MPlug bindPosePlug = dgFn.findPlug("bindPose", &status);
	if (status != MS::kSuccess)
	{
		MGlobal::displayWarning(MString("No bindPose found on node ") + dgFn.name());
		return status;
	}

	MFnMatrixData matrixFn;
	MObject val = matrixFn.create(bindPoseInverse.inverse(), &status);
	MObject invval = matrixFn.create(bindPoseInverse, &status);
	if (status != MS::kSuccess)
	{
		MGlobal::displayWarning(MString("Error setting bindPose on node ") + dgFn.name());
		return status;
	}

	// set the bind pose on the joint itself
	//
	bindPosePlug.setValue(val);

	// Now, perhaps more significantly, see if there's a
	// skinCluster using this bone and update its bind
	// pose (as the joint bind pose is not connected to
	// the skin - it's set at bind time from the joint's
	// current position, and our importer may not want to
	// disturb the current scene state just to put bones
	// in a bind position before creating skin clusters)
	//
	MObject _node(node);
	MItDependencyGraph it(_node, MFn::kSkinClusterFilter);
	while (!it.isDone())
	{
		MPlug plug = it.thisPlug();
		unsigned int idx = plug.logicalIndex();
		MFnDependencyNode skinFn(plug.node());
		MPlug skinBindPosePlug = skinFn.findPlug("bindPreMatrix", &status);
		if (status == MS::kSuccess)
		{
			// The skinCluster stores inverse inclusive matrix
			// so notice we use invval (the MObject created off
			// the inverse matrix here)
			//
			skinBindPosePlug = skinBindPosePlug.elementByLogicalIndex(idx);
			skinBindPosePlug.setValue(invval);
		}
		it.next();
	}

	return status;
}

MPlug CDagHelper::GetChildPlug(const MPlug& parent, const MString& name, MStatus* rc)
{
	MStatus st;
	uint childCount = parent.numChildren(&st);
	if (st != MStatus::kSuccess) { if (rc != NULL) *rc = st; return parent; }

	// Check shortNames first
	for (uint i = 0; i < childCount; ++i)
	{
		MPlug child = parent.child(i, &st);
		if (st != MStatus::kSuccess) { if (rc != NULL) *rc = st; return parent; }

		MFnAttribute attributeFn(child.attribute());
		MString n = attributeFn.shortName();
		if (n == name)
		{
			if (rc != NULL) *rc = MStatus::kSuccess;
			return child;
		}
	}

	// Check longNames second, use shortNames!
	for (uint i = 0; i < childCount; ++i)
	{
		MPlug child = parent.child(i, &st);
		if (st != MStatus::kSuccess) { if (rc != NULL) *rc = st; return parent; }

		MFnAttribute attributeFn(child.attribute());
		MString n = attributeFn.name();
		if (n == name)
		{
			if (rc != NULL) *rc = MStatus::kSuccess;
			return child;
		}
	}

	if (rc != NULL) *rc = MStatus::kNotFound;
	return parent;
}

int CDagHelper::GetChildPlugIndex(const MPlug& parent, const MString& name, MStatus* rc)
{
	MStatus st;
	uint childCount = parent.numChildren(&st);
	CHECK_MSTATUS_AND_RETURN(st, -1);

	// Check shortNames first
	for (uint i = 0; i < childCount; ++i)
	{
		MPlug child = parent.child(i, &st);
		CHECK_MSTATUS_AND_RETURN(st, -1);

		MFnAttribute attributeFn(child.attribute());
		MString n = attributeFn.shortName();
		if (n == name)
		{
			if (rc != NULL) *rc = MStatus::kSuccess;
			return i;
		}
	}

	// Check longNames second, use shortNames!
	for (uint i = 0; i < childCount; ++i)
	{
		MPlug child = parent.child(i, &st);
		CHECK_MSTATUS_AND_RETURN(st, -1);

		MFnAttribute attributeFn(child.attribute());
		MString n = attributeFn.name();
		if (n == name)
		{
			if (rc != NULL) *rc = MStatus::kSuccess;
			return i;
		}
	}

	if (rc != NULL) *rc = MStatus::kNotFound;
	return -1;
}

bool CDagHelper::GetPlugValue(const MObject& node, const char *attributeName, double &value)
{
	MStatus status;
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, &status);
	if (status != MStatus::kSuccess) return false;

	status = plug.getValue(value);
	return status == MStatus::kSuccess;
}

bool CDagHelper::GetPlugValue(const MObject& node, const char *attributeName, float &value)
{
	MStatus status;
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, &status);
	if (status != MStatus::kSuccess) return false;

	status = plug.getValue(value);
	return status == MStatus::kSuccess;
}

bool CDagHelper::GetPlugValue(const MPlug& plug, float& x)
{
	MStatus status;
	status = plug.getValue(x);
	return status == MStatus::kSuccess;
}

bool CDagHelper::GetPlugValue(const MPlug& plug, int& value)
{
	MStatus status;
	status = plug.getValue(value);
	return status == MStatus::kSuccess;
}

bool CDagHelper::GetPlugValue(const MPlug& plug, uint32& value)
{
	MStatus status;
	int temp;
	status = plug.getValue(temp);
	value = static_cast<uint32>(temp);
	return status == MStatus::kSuccess;
}

bool CDagHelper::GetPlugValue(const MPlug& plug, short& value)
{
	MStatus status;
	status = plug.getValue(value);
	return status == MStatus::kSuccess;
}

bool CDagHelper::GetPlugValue(const MPlug& plug, uint16& value)
{
	MStatus status;
	short temp;
	status = plug.getValue(temp);
	value = static_cast<uint16>(temp);
	return status == MStatus::kSuccess;
}

bool CDagHelper::GetPlugValue(const MPlug& plug, char& value)
{
	MStatus status;
	status = plug.getValue(value);
	return status == MStatus::kSuccess;
}

bool CDagHelper::GetPlugValue(const MPlug& plug, uint8& value)
{
	MStatus status;
	char temp;
	status = plug.getValue(temp);
	value = static_cast<uint8>(temp);
	return status == MStatus::kSuccess;
}

bool CDagHelper::GetPlugValue(const MObject& node, const char* attributeName, MEulerRotation& value)
{
	MStatus status;
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, &status);
	if (status != MStatus::kSuccess) return false;

	if (plug.isCompound() && plug.numChildren() >= 3)
	{
		status = plug.child(0).getValue(value.x);
		if (status != MStatus::kSuccess) return false;

		status = plug.child(1).getValue(value.y);
		if (status != MStatus::kSuccess) return false;

		status = plug.child(2).getValue(value.z);
		if (status != MStatus::kSuccess) return false;

		return true;
	}
	else return false;
}

bool CDagHelper::GetPlugValue(const MObject& node, const char* attributeName, bool& value)
{
	MStatus status;
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, &status);
	if (status != MStatus::kSuccess) return false;

	status = plug.getValue(value);
	if (status != MStatus::kSuccess) return false;
	return true;
}

bool CDagHelper::GetPlugValue(const MPlug& plug, bool& value)
{
	MStatus status;
	status = plug.getValue(value);
	if (status != MStatus::kSuccess) return false;
	return true;
}

bool CDagHelper::GetPlugValue(const MObject& node, const char* attributeName, int& value)
{
	MStatus status;
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, &status);
	if (status != MStatus::kSuccess) return false;

	status = plug.getValue(value);
	if (status != MStatus::kSuccess) return false;
	return true;
}

bool CDagHelper::GetPlugValue(const MObject& node, const char* attributeName, MMatrix& value)
{
	MStatus status;
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, &status);
	if (status != MStatus::kSuccess) return false;

	return GetPlugValue(plug, value);
}

bool CDagHelper::GetPlugValue(const MPlug& plug, MMatrix& value)
{
	MStatus status;

	MFnMatrixData mxData;
	MObject o = mxData.create();
	status = plug.getValue(o);
	if (status != MStatus::kSuccess) return false;

	mxData.setObject(o);

//	MFnMatrixData mxData(o, &status);
	if (status != MStatus::kSuccess) return false;
	value = mxData.matrix();
	return true;
}

bool CDagHelper::GetPlugValue(const MObject& node, const char* attributeName, MColor& value)
{
	MStatus status;
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, &status);
	if (status != MStatus::kSuccess) return false;

	return GetPlugValue(plug, value);
}

bool CDagHelper::GetPlugValue(const MPlug& plug, MColor& value)
{
	MStatus status;
	if (plug.isCompound() && plug.numChildren() >= 3)
	{
		status = plug.child(0).getValue(value.r);
		if (status != MStatus::kSuccess) return false;

		status = plug.child(1).getValue(value.g);
		if (status != MStatus::kSuccess) return false;

		status = plug.child(2).getValue(value.b);
		if (status != MStatus::kSuccess) return false;

		if (plug.numChildren() >= 4)
		{
			status = plug.child(3).getValue(value.a);
			if (status != MStatus::kSuccess) return false;
		}
		else value.a = 1.0f;

		return true;
	}
	else return false;
}

bool CDagHelper::GetPlugValue(const MObject& node, const char* attributeName, MString& value)
{
	MStatus status;
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, &status);
	if (status != MStatus::kSuccess) return false;
	
	return plug.getValue(value);
}

void CDagHelper::GetPlugValue(const MObject& node, const char* attributeName, MStringArray& output, MStatus* ReturnStatus)
{
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, ReturnStatus);
	GetPlugValue(plug, output, ReturnStatus);
}

void CDagHelper::GetPlugValue(const MPlug& plug, MStringArray& output, MStatus* ReturnStatus)
{
	MObject str_obj;
	plug.getValue(str_obj);
	MFnStringArrayData f_astr(str_obj, ReturnStatus);
	unsigned int len = f_astr.length();
	for (unsigned int i = 0; i < len; ++i)
	{
		const MString& val = f_astr[i];
		output.append(val);
	}
}

bool CDagHelper::GetPlugValue(const MPlug& plug, float& x, float& y)
{
	MObject obj;
	plug.getValue(obj);
	MStatus status;
	MFnNumericData fcolor(obj, &status);
	if (!status) return 0;
	fcolor.getData (x , y);
	return 1;
}

bool CDagHelper::GetPlugValue(const MPlug& plug, float& x, float& y, float& z)
{
	MObject obj;
	plug.getValue(obj);
	MStatus status;
	MFnNumericData fcolor(obj, &status);
	if (!status) return 0;
	fcolor.getData (x , y , z);
	return 1;
}

//static 
bool CDagHelper::GetPlugValue(const MObject& node, const char* attributeName, MVector& value)
{
	MStatus status;
	MPlug plug = MFnDependencyNode(node).findPlug(attributeName, &status);
	if (status != MStatus::kSuccess) return false;
	
	return GetPlugValue(plug, value);
}

//static 
bool CDagHelper::GetPlugValue(const MPlug& plug, MVector& value)
{
	MObject obj;
	plug.getValue(obj);
	
	MStatus status = plug.getValue(obj);
	FUAssert(status, return false);
	MFnNumericData data(obj);
	
	double x, y, z;
	status = data.getData(x, y, z);
	FUAssert(status, return false);
	value = MVector(x,y,z);

	return true;
}

bool CDagHelper::SetPlugValue(MPlug& plug, const MVector& value)
{
	MStatus status;
	MFnNumericData dataCreator;

	MObject float3Data = dataCreator.create(MFnNumericData::k3Float, &status);
	if (status != MStatus::kSuccess) return false;
	dataCreator.setData((float)value.x, (float)value.y, (float)value.z);

	status = plug.setValue(float3Data);
	if (status != MStatus::kSuccess) return false;

	return true;
}

bool CDagHelper::SetPlugValue(MPlug& plug, const MColor& value)
{
	MStatus status;
	if (plug.isCompound() && plug.numChildren() >= 3)
	{
		MPlug rPlug = plug.child(0, &status);
		if (status != MStatus::kSuccess) return false;
		status = rPlug.setValue(value.r);
		if (status != MStatus::kSuccess) return false;

		MPlug gPlug = plug.child(1, &status);
		if (status != MStatus::kSuccess) return false;
		status = gPlug.setValue(value.g);
		if (status != MStatus::kSuccess) return false;

		MPlug bPlug = plug.child(2, &status);
		if (status != MStatus::kSuccess) return false;
		status = bPlug.setValue(value.b);
		if (status != MStatus::kSuccess) return false;

		if (plug.numChildren() >= 4)
		{
			MPlug aPlug = plug.child(3, &status);
			if (status != MStatus::kSuccess) return false;
			status = aPlug.setValue(value.a);
			if (status != MStatus::kSuccess) return false;
		}
	}

	return true;
}

bool CDagHelper::SetPlugValue(MPlug& plug, const MMatrix& value)
{
	MStatus status;
	MFnMatrixData dataCreator;

	MObject matrixData = dataCreator.create(value, &status);
	if (status != MStatus::kSuccess) return false;

	status = plug.setValue(matrixData);
	if (status != MStatus::kSuccess) return false;

	return true;
}

bool CDagHelper::SetPlugValue(MPlug& plug, const fm::string& value)
{
	MStatus status;
	status = plug.setValue(value.c_str());
	return status == MStatus::kSuccess;
}

#ifdef UNICODE
bool CDagHelper::SetPlugValue(MPlug& plug, const fstring& value)
{
	MStatus status;
	status = plug.setValue(MString(value.c_str()));
	return status == MStatus::kSuccess;
}
#endif // UNICODE

bool CDagHelper::SetPlugValue(MPlug& plug, float value)
{
	MStatus status;
	status = plug.setValue(value);
	return status == MStatus::kSuccess;
}

bool CDagHelper::SetPlugValue(MPlug& plug, double value)
{
	MStatus status;
	status = plug.setValue(value);
	return status == MStatus::kSuccess;
}

bool CDagHelper::SetPlugValue(MPlug& plug, float x, float y)
{
	MFnNumericData data;
	MObject obj = data.create(MFnNumericData::k2Float);
	data.setData(x, y);
	return plug.setValue(obj);
}

bool CDagHelper::SetPlugValue(MPlug& plug, int value)
{
	MStatus status;
	status = plug.setValue(value);
	return status == MStatus::kSuccess;
}

bool CDagHelper::SetPlugValue(MPlug& plug, bool value)
{
	MStatus status;
	status = plug.setValue(value);
	return status == MStatus::kSuccess;
}

bool CDagHelper::SetPlugValue(MPlug& plug, MStringArray& stringArray)
{
	MObject obj;
	MFnStringArrayData fstr;
	obj = fstr.create(stringArray);
	return plug.setValue(obj);
}

void CDagHelper::SetArrayPlugSize(MPlug& plug, uint size)
{
    if (plug.node().isNull()) return;
        
#if MAYA_API_VERSION >= 800
	CHECK_MSTATUS(plug.setNumElements(size));
#else
	MObject node = plug.node();
	MString plugPath = plug.info();
	if (node.hasFn(MFn::kDagNode))
	{
		MFnDagNode dagFn(node);
		int dot = plugPath.index('.');
		plugPath = dagFn.fullPathName() + plugPath.substring(dot, plugPath.length());
	}
	MString command = MString("setAttr -s ") + size + " \"" + plugPath + "\";";
	MGlobal::executeCommand(command);
#endif // MAYA 8.00+
}

// Creates a typed attribute. Used for maya "notes" attributes.
MObject CDagHelper::CreateAttribute(const MObject& node, const char* attributeName, const char* attributeShortName, MFnNumericData::Type type, const char *value)
{
	// Before creating a new attribute: verify that an old one doesn't already exist
	MStatus status;
	MObject attribute;
	MFnDependencyNode nodeFn(node);
	MPlug plug = nodeFn.findPlug(attributeShortName, status);
	if (status != MStatus::kSuccess)
	{
		MFnNumericAttribute attr;
		MStatus status;
		attribute = attr.create(attributeName,attributeShortName,type,0,&status);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
		attr.setStorable(true);
		attr.setKeyable(false);
		attr.setCached(true);
		attr.setReadable(true);
		attr.setWritable(true);

		status = nodeFn.addAttribute(attribute, MFnDependencyNode::kLocalDynamicAttr);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
		plug = nodeFn.findPlug(attribute, &status);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
	}

	status = plug.setValue(value);
	if (status != MStatus::kSuccess) return MObject::kNullObj;
	return attribute;
}

MObject CDagHelper::CreateAttribute(const MObject& node, const char* attributeName, const char* attributeShortName, MFnData::Type type, const char *value)
{
	// Before creating a new attribute: verify that an old one doesn't already exist
	MStatus status;
	MObject attribute;
	MFnDependencyNode nodeFn(node);
	MPlug plug = nodeFn.findPlug(attributeShortName, status);
	if (status != MStatus::kSuccess)
	{
		MFnTypedAttribute attr;
		MStatus status;
		attribute = attr.create(attributeName,attributeShortName,type,&status);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
		attr.setStorable(true);
		attr.setKeyable(false);
		attr.setCached(true);
		attr.setReadable(true);
		attr.setWritable(true);

		status = nodeFn.addAttribute(attribute, MFnDependencyNode::kLocalDynamicAttr);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
		plug = nodeFn.findPlug(attribute, &status);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
	}

	status = plug.setValue(value);
	if (status != MStatus::kSuccess) return MObject::kNullObj;
	return attribute;
}

MPlug CDagHelper::AddAttribute(const MObject& node, const MObject& attribute)
{
	MPlug plug;
	MFnAttribute attributeFn(attribute);
	MFnDependencyNode depFn(node);
	MStatus status = depFn.addAttribute(attribute, MFnDependencyNode::kLocalDynamicAttr);
	if (status == MStatus::kSuccess)
	{
		plug = depFn.findPlug(attribute);
	}
	return plug;
}

// Get a dag path or node from a string
MDagPath CDagHelper::GetShortestDagPath(const MObject& node)
{
	MDagPathArray paths;
	MDagPath::getAllPathsTo(node, paths);
	MDagPath shortestPath;
	if (paths.length() > 0)
	{
		shortestPath = paths[0];
		for (uint i = 1; i < paths.length(); ++i)
		{
			if (shortestPath.length() > paths[i].length())
			{
				shortestPath = paths[i];
			}
		}
	}
	return shortestPath;
}

MObject CDagHelper::GetNode(const MString& name)
{
	MSelectionList selection;
	selection.add(name);
	
	MObject o;
	selection.getDependNode(0, o);
	return o;
}

void CDagHelper::GroupConnect(MPlug& source, const MObject& destination, const MObject& finalMesh)
{
	MFnDependencyNode destinationFn(destination);
	MFnDagNode finalMeshFn(finalMesh);

	// Create the set which will hold the connected components
	MFnSet objectSetFn;
	MSelectionList clusterComponentList;
	MObject objectSet = objectSetFn.create(clusterComponentList, MFnSet::kVerticesOnly, false);
	objectSetFn.setName(destinationFn.name() + "set");

	// Connect the set to the destination and the finalMesh
	CDagHelper::ConnectToList(destination, "message", objectSet, "usedBy");

	// Create the groupId node
	MFnDependencyNode groupId;
	groupId.create("groupId");
	CDagHelper::SetPlugValue(groupId.object(), "isHistoricallyInteresting", 0);

	// Create the groupParts node
	MFnDependencyNode groupParts;
	groupParts.create("groupParts");
	CDagHelper::SetPlugValue(groupParts.object(), "isHistoricallyInteresting", 0);

	// Tell the groupParts to connect all the vertices of the mesh
	MFnSingleIndexedComponent allVerticesComponent;
	MObject allVerticesObject = allVerticesComponent.create(MFn::kMeshVertComponent);
	allVerticesComponent.setComplete(true);
	MFnComponentListData componentListData;
	MObject componentList = componentListData.create();
	componentListData.add(allVerticesObject);
	MPlug inputComponentsPartsPlug = groupParts.findPlug("inputComponents");
	inputComponentsPartsPlug.setValue(componentList);

	// Tell the ouput node to expect the groupId
	MPlug instanceObjectGroupsPlug = finalMeshFn.findPlug("instObjGroups");
	instanceObjectGroupsPlug = instanceObjectGroupsPlug.elementByLogicalIndex(0);
	MPlug objectGroupsPlug = CDagHelper::GetChildPlug(instanceObjectGroupsPlug, "og"); // "objectGroups"
	MPlug objectGroupPlug = objectGroupsPlug.elementByLogicalIndex(objectGroupsPlug.numElements());
	MPlug groupIdPlug = CDagHelper::GetChildPlug(objectGroupPlug, "gid"); // "objectGroupId"
	CDagHelper::Connect(groupId.object(), "id", groupIdPlug);

	// Tell the groupId about the set to implied in the connection
	CDagHelper::ConnectToList(groupId.object(), "msg", objectSetFn.object(), "gn");

	// Connect up the set and the groupId implication within the final mesh
	MPlug groupColorPlug = CDagHelper::GetChildPlug(objectGroupPlug, "gco"); // "objectGrpColor"
	CDagHelper::Connect(objectSet, "memberWireframeColor", groupColorPlug);
	CDagHelper::ConnectToList(objectGroupPlug, objectSet, "dagSetMembers");

	// Connect the output with the groupParts
	MPlug inputGlobalPlug = destinationFn.findPlug("input");
	inputGlobalPlug = inputGlobalPlug.elementByLogicalIndex(inputGlobalPlug.numElements());
	MPlug inputGeometryPlug = CDagHelper::GetChildPlug(inputGlobalPlug, "ig"); // "inputGeometry"
	CDagHelper::Connect(groupParts.object(), "og", inputGeometryPlug);

	// Connect the output with the groupId
	groupIdPlug = CDagHelper::GetChildPlug(inputGlobalPlug, "gi"); // "groupId"
	CDagHelper::Connect(groupId.object(), "id", groupIdPlug);

	// Connect the input with the groupParts
	MObject sourceNode = source.node();
	MString sourceName;
	if (!sourceNode.hasFn(MFn::kDagNode)) sourceName = source.info();
	else
	{
		MFnDagNode sourceNodeFn(source.node());
		MFnDagNode parentNodeFn(sourceNodeFn.parent(0));
		sourceName = parentNodeFn.fullPathName() + "|" + source.info();
	}
	MGlobal::executeCommand(MString("connectAttr ") + sourceName +  " " + groupParts.name() + ".inputGeometry;");

	// Connect the groupId and the groupParts together
	CDagHelper::Connect(groupId.object(), "id", groupParts.object(), "groupId");
}

bool CDagHelper::Disconnect(const MPlug& source, const MPlug& destination)
{
	MDGModifier mod;
	mod.disconnect(source, destination);
	MStatus s = mod.doIt();
	return !s.error();
}

bool CDagHelper::Disconnect(const MPlug& plug, bool sources, bool destinations)
{
	MDGModifier mod;
	MPlugArray connectedPlugs;
	if (sources)
	{
		if (plug.connectedTo(connectedPlugs, sources, false))
		{
			for (uint i = 0; i < connectedPlugs.length(); ++i)
			{
				MPlug p = connectedPlugs[i];
				mod.disconnect(p, plug);
			}
		}
	}
	if (destinations)
	{
		if (plug.connectedTo(connectedPlugs, false, destinations))
		{
			for (uint i = 0; i < connectedPlugs.length(); ++i)
			{
				MPlug p = connectedPlugs[i];
				mod.disconnect(plug, p);
			}
		}
	}
	return mod.doIt() == MStatus::kSuccess;
}

// Create an animation curve for the given plug
MObject CDagHelper::CreateAnimationCurve(const MObject& node, const char* attributeName, const char* curveType)
{ MFnDependencyNode fn(node); return CreateAnimationCurve(fn.findPlug(attributeName), curveType); }
MObject CDagHelper::CreateAnimationCurve(const MPlug& plug, const char* curveType)
{
	MStatus rc;
	MFnDependencyNode curveFn;
	curveFn.create(curveType, &rc);
	if (rc == MStatus::kSuccess)
	{
		CDagHelper::Connect(curveFn.object(), "output", plug);
	}
	return curveFn.object();
}

MObject CDagHelper::CreateExpression(const MPlug& plug, const MString& expression)
{
	MFnDependencyNode expressionFn;
	MObject expressionObj = expressionFn.create("expression");
	CDagHelper::SetPlugValue(expressionObj, "expression", expression);

	MPlug output = expressionFn.findPlug("output");
	MPlug firstOutput = output.elementByLogicalIndex(0);
	CDagHelper::Connect(firstOutput, plug);
	return expressionObj;
}

bool CDagHelper::PlugHasAnimation(const MPlug& plug)
{
	MPlugArray connections;
	plug.connectedTo(connections, true, false);
	unsigned int connectionsCount = connections.length();
	for (unsigned int i = 0; i < connectionsCount; i++)
	{
		MPlug connectedToPlug = connections[i];
		MObject nodeObj = connectedToPlug.node();
		MFnDependencyNode nodeFn(nodeObj);
		MString typeName = nodeFn.typeName();
		if ((typeName == "animCurveTU") || (typeName == "animCurveTL")
				|| (typeName == "animCurveTA"))
		{
			return true;
		}
	}
	return false;
}

// get the first empty item in the named array plug
unsigned CDagHelper::GetFirstEmptyElementId(const MPlug& parent)
{
	unsigned num_element = 1;
	if (parent.numElements() > num_element) num_element = parent.numElements();
	for (unsigned i = 0; i< num_element; i++)
	{
		if (!parent.elementByLogicalIndex(i).isConnected()) return i;
	}
	return parent.numElements()+1;
}
