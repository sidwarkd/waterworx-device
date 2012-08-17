#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/build.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/build.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360919890/app.o ${OBJECTDIR}/_ext/35432207/NVMem.o ${OBJECTDIR}/_ext/2048433900/simpledelay.o ${OBJECTDIR}/_ext/66270815/cJSON.o ${OBJECTDIR}/_ext/1798975146/FSIO.o ${OBJECTDIR}/_ext/1798975146/SD-SPI.o ${OBJECTDIR}/_ext/66509721/rtcc_helper.o ${OBJECTDIR}/_ext/66509721/rtcc_tests.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360919890/app.o.d ${OBJECTDIR}/_ext/35432207/NVMem.o.d ${OBJECTDIR}/_ext/2048433900/simpledelay.o.d ${OBJECTDIR}/_ext/66270815/cJSON.o.d ${OBJECTDIR}/_ext/1798975146/FSIO.o.d ${OBJECTDIR}/_ext/1798975146/SD-SPI.o.d ${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d ${OBJECTDIR}/_ext/66509721/rtcc_tests.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360919890/app.o ${OBJECTDIR}/_ext/35432207/NVMem.o ${OBJECTDIR}/_ext/2048433900/simpledelay.o ${OBJECTDIR}/_ext/66270815/cJSON.o ${OBJECTDIR}/_ext/1798975146/FSIO.o ${OBJECTDIR}/_ext/1798975146/SD-SPI.o ${OBJECTDIR}/_ext/66509721/rtcc_helper.o ${OBJECTDIR}/_ext/66509721/rtcc_tests.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/build.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=,--script="..\sd_btl_ex16.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360919890/app.o: ../app/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360919890 
	@${RM} ${OBJECTDIR}/_ext/1360919890/app.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360919890/app.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/1360919890/app.o.d" -o ${OBJECTDIR}/_ext/1360919890/app.o ../app/app.c  
	
${OBJECTDIR}/_ext/35432207/NVMem.o: ../modules/bootldr/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/35432207 
	@${RM} ${OBJECTDIR}/_ext/35432207/NVMem.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/35432207/NVMem.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/35432207/NVMem.o.d" -o ${OBJECTDIR}/_ext/35432207/NVMem.o ../modules/bootldr/NVMem.c  
	
${OBJECTDIR}/_ext/2048433900/simpledelay.o: ../modules/delay/simpledelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048433900 
	@${RM} ${OBJECTDIR}/_ext/2048433900/simpledelay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048433900/simpledelay.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/2048433900/simpledelay.o.d" -o ${OBJECTDIR}/_ext/2048433900/simpledelay.o ../modules/delay/simpledelay.c  
	
${OBJECTDIR}/_ext/66270815/cJSON.o: ../modules/json/cJSON.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66270815 
	@${RM} ${OBJECTDIR}/_ext/66270815/cJSON.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66270815/cJSON.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/66270815/cJSON.o.d" -o ${OBJECTDIR}/_ext/66270815/cJSON.o ../modules/json/cJSON.c  
	
${OBJECTDIR}/_ext/1798975146/FSIO.o: ../modules/mdd/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1798975146 
	@${RM} ${OBJECTDIR}/_ext/1798975146/FSIO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1798975146/FSIO.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/1798975146/FSIO.o.d" -o ${OBJECTDIR}/_ext/1798975146/FSIO.o ../modules/mdd/FSIO.c  
	
${OBJECTDIR}/_ext/1798975146/SD-SPI.o: ../modules/mdd/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1798975146 
	@${RM} ${OBJECTDIR}/_ext/1798975146/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1798975146/SD-SPI.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/1798975146/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/1798975146/SD-SPI.o ../modules/mdd/SD-SPI.c  
	
${OBJECTDIR}/_ext/66509721/rtcc_helper.o: ../modules/rtcc/rtcc_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66509721 
	@${RM} ${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d" -o ${OBJECTDIR}/_ext/66509721/rtcc_helper.o ../modules/rtcc/rtcc_helper.c  
	
${OBJECTDIR}/_ext/66509721/rtcc_tests.o: ../modules/rtcc/rtcc_tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66509721 
	@${RM} ${OBJECTDIR}/_ext/66509721/rtcc_tests.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66509721/rtcc_tests.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/66509721/rtcc_tests.o.d" -o ${OBJECTDIR}/_ext/66509721/rtcc_tests.o ../modules/rtcc/rtcc_tests.c  
	
else
${OBJECTDIR}/_ext/1360919890/app.o: ../app/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360919890 
	@${RM} ${OBJECTDIR}/_ext/1360919890/app.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360919890/app.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/1360919890/app.o.d" -o ${OBJECTDIR}/_ext/1360919890/app.o ../app/app.c  
	
${OBJECTDIR}/_ext/35432207/NVMem.o: ../modules/bootldr/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/35432207 
	@${RM} ${OBJECTDIR}/_ext/35432207/NVMem.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/35432207/NVMem.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/35432207/NVMem.o.d" -o ${OBJECTDIR}/_ext/35432207/NVMem.o ../modules/bootldr/NVMem.c  
	
${OBJECTDIR}/_ext/2048433900/simpledelay.o: ../modules/delay/simpledelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048433900 
	@${RM} ${OBJECTDIR}/_ext/2048433900/simpledelay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048433900/simpledelay.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/2048433900/simpledelay.o.d" -o ${OBJECTDIR}/_ext/2048433900/simpledelay.o ../modules/delay/simpledelay.c  
	
${OBJECTDIR}/_ext/66270815/cJSON.o: ../modules/json/cJSON.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66270815 
	@${RM} ${OBJECTDIR}/_ext/66270815/cJSON.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66270815/cJSON.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/66270815/cJSON.o.d" -o ${OBJECTDIR}/_ext/66270815/cJSON.o ../modules/json/cJSON.c  
	
${OBJECTDIR}/_ext/1798975146/FSIO.o: ../modules/mdd/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1798975146 
	@${RM} ${OBJECTDIR}/_ext/1798975146/FSIO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1798975146/FSIO.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/1798975146/FSIO.o.d" -o ${OBJECTDIR}/_ext/1798975146/FSIO.o ../modules/mdd/FSIO.c  
	
${OBJECTDIR}/_ext/1798975146/SD-SPI.o: ../modules/mdd/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1798975146 
	@${RM} ${OBJECTDIR}/_ext/1798975146/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1798975146/SD-SPI.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/1798975146/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/1798975146/SD-SPI.o ../modules/mdd/SD-SPI.c  
	
${OBJECTDIR}/_ext/66509721/rtcc_helper.o: ../modules/rtcc/rtcc_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66509721 
	@${RM} ${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d" -o ${OBJECTDIR}/_ext/66509721/rtcc_helper.o ../modules/rtcc/rtcc_helper.c  
	
${OBJECTDIR}/_ext/66509721/rtcc_tests.o: ../modules/rtcc/rtcc_tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66509721 
	@${RM} ${OBJECTDIR}/_ext/66509721/rtcc_tests.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66509721/rtcc_tests.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/HardlySoftware/projects/waterworx/skink/app" -I"D:/HardlySoftware/projects/waterworx/skink/modules" -I"D:/HardlySoftware/projects/waterworx/skink/modules/base" -MMD -MF "${OBJECTDIR}/_ext/66509721/rtcc_tests.o.d" -o ${OBJECTDIR}/_ext/66509721/rtcc_tests.o ../modules/rtcc/rtcc_tests.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/build.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/build.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=2048
else
dist/${CND_CONF}/${IMAGE_TYPE}/build.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/build.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/build.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
