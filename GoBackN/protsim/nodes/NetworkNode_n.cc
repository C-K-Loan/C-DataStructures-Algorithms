//-----------------------------------------
//
// Generated by nedtool, version 3.3
// date: Thu Jul  2 22:42:54 2009
//
//-----------------------------------------


#include <math.h>
#include "omnetpp.h"

// NEDC version check
#define NEDC_VERSION 0x0303
#if (NEDC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedc: 'make clean' should help.
#endif

// Disable warnings about unused variables. For MSVC and BC only:
// GCC has no way to turn on its -Wunused option in a source file :(
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#endif
#ifdef __BORLANDC__
#  pragma warn -waus
#  pragma warn -wuse
#endif

static cModuleType *_getModuleType(const char *modname)
{
    cModuleType *modtype = findModuleType(modname);
    if (!modtype)
        throw new cRuntimeError("Module type definition %s not found (Define_Module() missing from C++ code?)", modname);
    return modtype;
}

static void _checkModuleVectorSize(int vectorsize, const char *mod)
{
    if (vectorsize<0)
        throw new cRuntimeError("Negative module vector size %s[%d]", mod, vectorsize);
}

static void _readModuleParameters(cModule *mod)
{
    int n = mod->params();
    for (int k=0; k<n; k++)
        if (mod->par(k).isInput())
            mod->par(k).read();
}

static int _checkModuleIndex(int index, int vectorsize, const char *modname)
{
    if (index<0 || index>=vectorsize)
        throw new cRuntimeError("Submodule index %s[%d] out of range, sizeof(%s) is %d", modname, index, modname, vectorsize);
    return index;
}

static cGate *_checkGate(cModule *mod, const char *gatename)
{
    cGate *g = mod->gate(gatename);
    if (!g)
        throw new cRuntimeError("%s has no gate named %s",mod->fullPath().c_str(), gatename);
    return g;
}

static cGate *_checkGate(cModule *mod, const char *gatename, int gateindex)
{
    cGate *g = mod->gate(gatename, gateindex);
    if (!g)
        throw new cRuntimeError("%s has no gate %s[%d]",mod->fullPath().c_str(), gatename, gateindex);
    return g;
}

static cGate *_getFirstUnusedParentModGate(cModule *mod, const char *gatename)
{
    int baseId = mod->findGate(gatename);
    if (baseId<0)
        throw new cRuntimeError("%s has no %s[] gate",mod->fullPath().c_str(), gatename);
    int n = mod->gate(baseId)->size();
    for (int i=0; i<n; i++)
        if (!mod->gate(baseId+i)->isConnectedInside())
            return mod->gate(baseId+i);
    throw new cRuntimeError("%s[] gates are all connected, no gate left for `++' operator",mod->fullPath().c_str(), gatename);
}

static cGate *_getFirstUnusedSubmodGate(cModule *mod, const char *gatename)
{
    int baseId = mod->findGate(gatename);
    if (baseId<0)
        throw new cRuntimeError("%s has no %s[] gate",mod->fullPath().c_str(), gatename);
    int n = mod->gate(baseId)->size();
    for (int i=0; i<n; i++)
        if (!mod->gate(baseId+i)->isConnectedOutside())
            return mod->gate(baseId+i);
    int newBaseId = mod->setGateSize(gatename,n+1);
    return mod->gate(newBaseId+n);
}

static cFunctionType *_getFunction(const char *funcname, int argcount)
{
    cFunctionType *functype = findFunction(funcname,argcount);
    if (!functype)
        throw new cRuntimeError("Function %s with %d args not found", funcname, argcount);
    return functype;
}

static cChannel *_createChannel(const char *channeltypename)
{
    cChannelType *channeltype = findChannelType(channeltypename);
    if (!channeltype)
        throw new cRuntimeError("Channel type %s not found", channeltypename);
    cChannel *channel = channeltype->create("channel");
    return channel;
}

static cChannel *_createNonTypedBasicChannel(double delay, double error, double datarate)
{
    cBasicChannel *channel = new cBasicChannel("channel");
    if (delay!=0) channel->setDelay(delay);
    if (error!=0) channel->setError(error);
    if (datarate!=0) channel->setDatarate(datarate);
    return channel;
}

static cXMLElement *_getXMLDocument(const char *fname, const char *pathexpr=NULL)
{
    cXMLElement *node = ev.getXMLDocument(fname, pathexpr);
    if (!node)
        throw new cRuntimeError(!pathexpr ? "xmldoc(\"%s\"): element not found" : "xmldoc(\"%s\", \"%s\"): element not found",fname,pathexpr);
    return node;
}

ModuleInterface(NetworkNode)
    // parameters:
    Parameter(nodeAddr, ParType_Numeric)
    Parameter(applicationType0, ParType_String)
    Parameter(applicationType1, ParType_String)
    Parameter(applicationType2, ParType_String)
    Parameter(applicationType3, ParType_String)
    Parameter(applicationType4, ParType_String)
    // gates:
    Gate(netIn[], GateDir_Input)
    Gate(netOut[], GateDir_Output)
EndInterface

Register_ModuleInterface(NetworkNode);

class NetworkNode : public cCompoundModule
{
  public:
    NetworkNode() : cCompoundModule() {}
  protected:
    virtual void doBuildInside();
};

Define_Module(NetworkNode);

void NetworkNode::doBuildInside()
{
    cModule *mod = this;

    // temporary variables:
    cPar tmpval;
    const char *modtypename;

    // submodules:
    cModuleType *modtype = NULL;
    int submodindex;

    //
    // submodule 'networkStack':
    //
    int networkStack_size = 1;
    modtype = _getModuleType("NetworkStack");
    cModule *networkStack_p = modtype->create("networkStack", mod);
    {
        cContextSwitcher __ctx(networkStack_p); // do the rest in this module's context

        // parameter assignments:

        // gatesizes:
        networkStack_p->setGateSize("netIn", (int)(mod->gateSize("netIn")));
        networkStack_p->setGateSize("netOut", (int)(mod->gateSize("netOut")));
        networkStack_p->setGateSize("fromAppl", (int)(5));
        networkStack_p->setGateSize("toAppl", (int)(5));

        _readModuleParameters(networkStack_p);
    }

    //
    // submodule 'interfaceQueue':
    //
    int interfaceQueue_size = (int)(mod->gateSize("netOut"));
    _checkModuleVectorSize(interfaceQueue_size,"interfaceQueue");
    cModule **interfaceQueue_p = new cModule *[interfaceQueue_size];
    if (interfaceQueue_size>0)
    {
        modtype = _getModuleType("InterfaceQueue");
    }
    for (submodindex=0; submodindex<interfaceQueue_size; submodindex++)
    {
        interfaceQueue_p[submodindex] = modtype->create("interfaceQueue", mod, interfaceQueue_size, submodindex);
        cContextSwitcher __ctx(interfaceQueue_p[submodindex]); // do the rest in this module's context

        _readModuleParameters(interfaceQueue_p[submodindex]);
    }

    //
    // submodule 'application0':
    //
    int application0_size = 1;
    modtypename = mod->par("applicationType0");
    modtype = _getModuleType(modtypename);
    cModule *application0_p = modtype->create("application0", mod);
    {
        cContextSwitcher __ctx(application0_p); // do the rest in this module's context

        _readModuleParameters(application0_p);
    }

    //
    // submodule 'application1':
    //
    int application1_size = 1;
    modtypename = mod->par("applicationType1");
    modtype = _getModuleType(modtypename);
    cModule *application1_p = modtype->create("application1", mod);
    {
        cContextSwitcher __ctx(application1_p); // do the rest in this module's context

        _readModuleParameters(application1_p);
    }

    //
    // submodule 'application2':
    //
    int application2_size = 1;
    modtypename = mod->par("applicationType2");
    modtype = _getModuleType(modtypename);
    cModule *application2_p = modtype->create("application2", mod);
    {
        cContextSwitcher __ctx(application2_p); // do the rest in this module's context

        _readModuleParameters(application2_p);
    }

    //
    // submodule 'application3':
    //
    int application3_size = 1;
    modtypename = mod->par("applicationType3");
    modtype = _getModuleType(modtypename);
    cModule *application3_p = modtype->create("application3", mod);
    {
        cContextSwitcher __ctx(application3_p); // do the rest in this module's context

        _readModuleParameters(application3_p);
    }

    //
    // submodule 'application4':
    //
    int application4_size = 1;
    modtypename = mod->par("applicationType4");
    modtype = _getModuleType(modtypename);
    cModule *application4_p = modtype->create("application4", mod);
    {
        cContextSwitcher __ctx(application4_p); // do the rest in this module's context

        _readModuleParameters(application4_p);
    }

    //
    // connections:
    //
    cGate *srcgate, *destgate;

    cChannel *channel;
    cPar *par;
    // for loop:
    {
        long start = (long)(0);
        long end = (long)((double)(mod->gateSize("netIn"))-(double)(1));
        for (long i_var=start; i_var<=end; i_var++)
        {
            // connection
            srcgate = _checkGate(mod, "netIn", (int)(i_var));
            destgate = _checkGate(networkStack_p, "netIn", (int)(i_var));
            srcgate->connectTo(destgate);

        }
    }
    // for loop:
    {
        long start = (long)(0);
        long end = (long)((double)(mod->gateSize("netOut"))-(double)(1));
        for (long i_var=start; i_var<=end; i_var++)
        {
            // connection
            srcgate = _checkGate(interfaceQueue_p[_checkModuleIndex((int)(i_var),interfaceQueue_size,"interfaceQueue")], "out");
            destgate = _checkGate(mod, "netOut", (int)(i_var));
            srcgate->connectTo(destgate);

            // connection
            srcgate = _checkGate(networkStack_p, "netOut", (int)(i_var));
            destgate = _checkGate(interfaceQueue_p[_checkModuleIndex((int)(i_var),interfaceQueue_size,"interfaceQueue")], "in");
            srcgate->connectTo(destgate);

        }
    }
    // connection
    srcgate = _checkGate(networkStack_p, "toAppl", (int)(0));
    destgate = _checkGate(application0_p, "in");
    srcgate->connectTo(destgate);

    // connection
    srcgate = _checkGate(application0_p, "out");
    destgate = _checkGate(networkStack_p, "fromAppl", (int)(0));
    srcgate->connectTo(destgate);

    // connection
    srcgate = _checkGate(networkStack_p, "toAppl", (int)(1));
    destgate = _checkGate(application1_p, "in");
    srcgate->connectTo(destgate);

    // connection
    srcgate = _checkGate(application1_p, "out");
    destgate = _checkGate(networkStack_p, "fromAppl", (int)(1));
    srcgate->connectTo(destgate);

    // connection
    srcgate = _checkGate(networkStack_p, "toAppl", (int)(2));
    destgate = _checkGate(application2_p, "in");
    srcgate->connectTo(destgate);

    // connection
    srcgate = _checkGate(application2_p, "out");
    destgate = _checkGate(networkStack_p, "fromAppl", (int)(2));
    srcgate->connectTo(destgate);

    // connection
    srcgate = _checkGate(networkStack_p, "toAppl", (int)(3));
    destgate = _checkGate(application3_p, "in");
    srcgate->connectTo(destgate);

    // connection
    srcgate = _checkGate(application3_p, "out");
    destgate = _checkGate(networkStack_p, "fromAppl", (int)(3));
    srcgate->connectTo(destgate);

    // connection
    srcgate = _checkGate(networkStack_p, "toAppl", (int)(4));
    destgate = _checkGate(application4_p, "in");
    srcgate->connectTo(destgate);

    // connection
    srcgate = _checkGate(application4_p, "out");
    destgate = _checkGate(networkStack_p, "fromAppl", (int)(4));
    srcgate->connectTo(destgate);

    // check all gates are connected:
    mod->checkInternalConnections();


    //
    // this level is done -- recursively build submodules too
    //
    networkStack_p->buildInside();
    for (submodindex=0; submodindex<interfaceQueue_size; submodindex++)
        interfaceQueue_p[submodindex]->buildInside();
    delete [] interfaceQueue_p;
    application0_p->buildInside();
    application1_p->buildInside();
    application2_p->buildInside();
    application3_p->buildInside();
    application4_p->buildInside();
}

