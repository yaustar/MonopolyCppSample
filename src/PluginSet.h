#ifndef PLUGIN_SET_H
#define PLUGIN_SET_H

#include <istream>
#include "PluginBase.h"

class PluginSet : public PluginBase
{
public:
	DECLARE_PLUGIN_META_DATA;

	PluginSet( BoardSquare * pParentSquare, std::istream & dataStream );
	virtual ~PluginSet();

	virtual void PrintInfo() const;

	inline int GetSetId() const;

private:
	PluginSet();

	int mSetId;
};

int PluginSet::GetSetId() const
{
	return mSetId;
}

#endif // PLUGIN_SET_H
