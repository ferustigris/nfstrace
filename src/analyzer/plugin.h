//------------------------------------------------------------------------------
// Author: Pavel Karneliuk
// Description: Plugin which encapsulate all requests to shared object library.
// Copyright (c) 2013 EPAM Systems. All Rights Reserved.
//------------------------------------------------------------------------------
#ifndef PLUGIN_H
#define PLUGIN_H
//------------------------------------------------------------------------------
#include <string>

#include "../auxiliary/dynamic_load.h"
#include "analyzers/base_analyzer.h"
//------------------------------------------------------------------------------
using NST::analyzer::analyzers::BaseAnalyzer;
//------------------------------------------------------------------------------

namespace NST
{
namespace analyzer
{

class Plugin : private NST::auxiliary::DynamicLoad
{
protected:
    Plugin(const std::string& path);

private:
    Plugin(const Plugin&);            // undefiend
    Plugin& operator=(const Plugin&); // undefiend

protected:
    analyzers::plugin_usage_func   usage;
    analyzers::plugin_create_func  create;
    analyzers::plugin_destroy_func destroy;
};

class PluginUsage : private Plugin
{
public:
    PluginUsage(const std::string& path) : Plugin(path) {}

    inline const std::string get() const { return usage(); }
};

class PluginInstance : private Plugin
{
public:
    PluginInstance(const std::string& path, const std::string& args);
    ~PluginInstance();

    inline BaseAnalyzer* instance() const { return analyzer; }

private:
    BaseAnalyzer* analyzer;
};

} // namespace analyzer
} // namespace NST
//------------------------------------------------------------------------------
#endif//PLUGIN_H
//------------------------------------------------------------------------------