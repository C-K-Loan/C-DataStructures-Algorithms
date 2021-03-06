#
#  Makefile for userapps
#
#  ** This file was automatically generated by the command:
#  opp_makemake -f -n -c ../omnetppconfig -I../common
#

# Name of target to be created (-o option)
TARGET = userapps

# User interface (uncomment one) (-u option)
# USERIF_LIBS=$(CMDENV_LIBS)
USERIF_LIBS=$(TKENV_LIBS)

# .ned or .h include paths with -I
INCLUDE_PATH= -I../common

# misc additional object and library files to link
EXTRA_OBJS=

# object files from other directories to link with (wildcard needed to prevent "no such file *.o" errors)
EXT_DIR_OBJS=

# time stamps of other directories (used as dependency)
EXT_DIR_TSTAMPS= ../common/.tstamp

# Additional libraries (-L option -l option)
LIBS=

#------------------------------------------------------------------------------
# Import generic settings from ../omnetppconfig
include ../omnetppconfig

MSGCOPTS= $(INCLUDE_PATH)

#------------------------------------------------------------------------------

# subdirectories to recurse into
SUBDIRS= 

# object files in this directory
OBJS= GoBackNReceiver_n.o GoBackNSender_n.o PingPongAppl_n.o  GoBackNReceiver.o GoBackNSender.o PingPongAppl.o

# header files generated (from msg files)
GENERATEDHEADERS= 

#------------------------------------------------------------------------------

$(TARGET): $(OBJS) Makefile .tstamp
	@# do nothing

.tstamp: $(OBJS)
	echo>.tstamp

$(OBJS) : $(GENERATEDHEADERS)


purify: $(OBJS) $(EXTRA_OBJS) $(EXT_DIR_TSTAMPS) Makefile
	purify $(CXX) $(LDFLAGS) $(OBJS) $(EXTRA_OBJS) $(EXT_DIR_OBJS) $(LIBS) -L$(OMNETPP_LIB_DIR) $(KERNEL_LIBS) $(USERIF_LIBS) $(SYS_LIBS_PURE) -o $(TARGET).pure

$(EXT_DIR_TSTAMPS):
	@echo
	@echo Error: $@ does not exist.
	@echo This means that at least the above dependency directory has not been built.
	@echo Maybe you need to do a top-level make?
	@echo
	@exit 1

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

GoBackNReceiver_n.o: GoBackNReceiver_n.cc
	$(CXX) -c $(NEDCOPTS) GoBackNReceiver_n.cc

GoBackNReceiver_n.cc: GoBackNReceiver.ned
	$(NEDC) $(INCLUDE_PATH) GoBackNReceiver.ned

GoBackNSender_n.o: GoBackNSender_n.cc
	$(CXX) -c $(NEDCOPTS) GoBackNSender_n.cc

GoBackNSender_n.cc: GoBackNSender.ned
	$(NEDC) $(INCLUDE_PATH) GoBackNSender.ned

PingPongAppl_n.o: PingPongAppl_n.cc
	$(CXX) -c $(NEDCOPTS) PingPongAppl_n.cc

PingPongAppl_n.cc: PingPongAppl.ned
	$(NEDC) $(INCLUDE_PATH) PingPongAppl.ned

GoBackNReceiver.o: GoBackNReceiver.cc
	$(CXX) -c $(COPTS) GoBackNReceiver.cc

GoBackNSender.o: GoBackNSender.cc
	$(CXX) -c $(COPTS) GoBackNSender.cc

PingPongAppl.o: PingPongAppl.cc
	$(CXX) -c $(COPTS) PingPongAppl.cc


#doc: neddoc doxy

#neddoc:
#	opp_neddoc -a

#doxy: doxy.cfg
#	doxygen doxy.cfg

generateheaders: $(GENERATEDHEADERS)
	for i in $(SUBDIRS); do (cd $$i && $(MAKE) generateheaders) || exit 1; done

clean:
	rm -f *.o *_n.cc *_n.h *_m.cc *_m.h .tstamp
	rm -f *.vec *.sca
	for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean); done

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -- *.cc
	# $(MAKEDEPEND) $(INCLUDE_PATH) -fMakefile.in -- *.cc
	for i in $(SUBDIRS); do (cd $$i && $(MAKE) depend) || exit 1; done

makefiles:
	# recreate Makefile
	opp_makemake -f  -n -c ../omnetppconfig -I../common 
	for i in $(SUBDIRS); do (cd $$i && $(MAKE) makefiles) || exit 1; done

makefile-ins:
	# recreate Makefile.in
	opp_makemake -f -m  -n -c ../omnetppconfig -I../common 
	for i in $(SUBDIRS); do (cd $$i && $(MAKE) makefile-ins) || exit 1; done

# "re-makemake" and "re-makemake-m" are deprecated, historic names of the above two targets
re-makemake: makefiles
re-makemake-m: makefile-ins


# DO NOT DELETE THIS LINE -- make depend depends on it.
GoBackNReceiver.o: GoBackNReceiver.cc \
  GoBackNReceiver.h \
  ../common/protsim_defines.h \
  ../common/Application.h \
  ../common/NetworkStack.h \
  ../common/../support/ForwardingTable.h \
  ../common/../support/MetricFunc.h \
  ../common/../emulation/ProtSimSocketRTScheduler.h
GoBackNSender.o: GoBackNSender.cc \
  GoBackNSender.h \
  ../common/protsim_defines.h \
  ../common/Application.h \
  ../common/NetworkStack.h \
  ../common/../support/ForwardingTable.h \
  ../common/../support/MetricFunc.h \
  ../common/../emulation/ProtSimSocketRTScheduler.h
PingPongAppl.o: PingPongAppl.cc \
  ../common/protsim_defines.h \
  ../common/Application.h \
  ../common/NetworkStack.h \
  ../common/../support/ForwardingTable.h \
  ../common/../support/MetricFunc.h \
  ../common/../emulation/ProtSimSocketRTScheduler.h
