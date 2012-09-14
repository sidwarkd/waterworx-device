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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/waterworx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/waterworx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360919890/app.o ${OBJECTDIR}/_ext/2048433900/simpledelay.o ${OBJECTDIR}/_ext/66509721/rtcc_helper.o ${OBJECTDIR}/_ext/1410781165/diskio.o ${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o ${OBJECTDIR}/_ext/1410781165/ff.o ${OBJECTDIR}/_ext/1410781165/sdcard.o ${OBJECTDIR}/_ext/1410781165/sdcard_helper.o ${OBJECTDIR}/_ext/1410781165/ccsbcs.o ${OBJECTDIR}/_ext/1985307369/WF_Eint.o ${OBJECTDIR}/_ext/1985307369/WF_Spi.o ${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o ${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o ${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o ${OBJECTDIR}/_ext/1985307369/WFConsole.o ${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o ${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o ${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o ${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o ${OBJECTDIR}/_ext/1985307369/WFDriverCom.o ${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o ${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o ${OBJECTDIR}/_ext/1985307369/WFEventHandler.o ${OBJECTDIR}/_ext/1985307369/WFInit.o ${OBJECTDIR}/_ext/1985307369/WFMac.o ${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o ${OBJECTDIR}/_ext/1985307369/WFParamMsg.o ${OBJECTDIR}/_ext/1985307369/WFPowerSave.o ${OBJECTDIR}/_ext/1985307369/WFScan.o ${OBJECTDIR}/_ext/1985307369/WFTxPower.o ${OBJECTDIR}/_ext/1447902105/Announce.o ${OBJECTDIR}/_ext/1447902105/ARP.o ${OBJECTDIR}/_ext/1447902105/AutoIP.o ${OBJECTDIR}/_ext/1447902105/BigInt.o ${OBJECTDIR}/_ext/1447902105/DHCP.o ${OBJECTDIR}/_ext/1447902105/DHCPs.o ${OBJECTDIR}/_ext/1447902105/DNS.o ${OBJECTDIR}/_ext/1447902105/DNSs.o ${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o ${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o ${OBJECTDIR}/_ext/1447902105/Helpers.o ${OBJECTDIR}/_ext/1447902105/ICMP.o ${OBJECTDIR}/_ext/1447902105/IP.o ${OBJECTDIR}/_ext/1447902105/NBNS.o ${OBJECTDIR}/_ext/1447902105/StackTsk.o ${OBJECTDIR}/_ext/1447902105/TCP.o ${OBJECTDIR}/_ext/1447902105/Tick.o ${OBJECTDIR}/_ext/1447902105/UDP.o ${OBJECTDIR}/_ext/2063154737/tcpip.o ${OBJECTDIR}/_ext/2063154737/WF_Config.o ${OBJECTDIR}/_ext/252269054/serial_usb.o ${OBJECTDIR}/_ext/252269054/usb_descriptors.o ${OBJECTDIR}/_ext/252269054/usb_device.o ${OBJECTDIR}/_ext/252269054/usb_function_cdc.o ${OBJECTDIR}/_ext/733900163/server.o ${OBJECTDIR}/_ext/733900163/static.o ${OBJECTDIR}/_ext/2063154737/wifi.o ${OBJECTDIR}/_ext/733900163/networks.o ${OBJECTDIR}/_ext/733900163/utilities.o ${OBJECTDIR}/_ext/66270815/cJSON.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360919890/app.o.d ${OBJECTDIR}/_ext/2048433900/simpledelay.o.d ${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d ${OBJECTDIR}/_ext/1410781165/diskio.o.d ${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o.d ${OBJECTDIR}/_ext/1410781165/ff.o.d ${OBJECTDIR}/_ext/1410781165/sdcard.o.d ${OBJECTDIR}/_ext/1410781165/sdcard_helper.o.d ${OBJECTDIR}/_ext/1410781165/ccsbcs.o.d ${OBJECTDIR}/_ext/1985307369/WF_Eint.o.d ${OBJECTDIR}/_ext/1985307369/WF_Spi.o.d ${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o.d ${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o.d ${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o.d ${OBJECTDIR}/_ext/1985307369/WFConsole.o.d ${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o.d ${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o.d ${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o.d ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o.d ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o.d ${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o.d ${OBJECTDIR}/_ext/1985307369/WFDriverCom.o.d ${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o.d ${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o.d ${OBJECTDIR}/_ext/1985307369/WFEventHandler.o.d ${OBJECTDIR}/_ext/1985307369/WFInit.o.d ${OBJECTDIR}/_ext/1985307369/WFMac.o.d ${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o.d ${OBJECTDIR}/_ext/1985307369/WFParamMsg.o.d ${OBJECTDIR}/_ext/1985307369/WFPowerSave.o.d ${OBJECTDIR}/_ext/1985307369/WFScan.o.d ${OBJECTDIR}/_ext/1985307369/WFTxPower.o.d ${OBJECTDIR}/_ext/1447902105/Announce.o.d ${OBJECTDIR}/_ext/1447902105/ARP.o.d ${OBJECTDIR}/_ext/1447902105/AutoIP.o.d ${OBJECTDIR}/_ext/1447902105/BigInt.o.d ${OBJECTDIR}/_ext/1447902105/DHCP.o.d ${OBJECTDIR}/_ext/1447902105/DHCPs.o.d ${OBJECTDIR}/_ext/1447902105/DNS.o.d ${OBJECTDIR}/_ext/1447902105/DNSs.o.d ${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o.d ${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o.d ${OBJECTDIR}/_ext/1447902105/Helpers.o.d ${OBJECTDIR}/_ext/1447902105/ICMP.o.d ${OBJECTDIR}/_ext/1447902105/IP.o.d ${OBJECTDIR}/_ext/1447902105/NBNS.o.d ${OBJECTDIR}/_ext/1447902105/StackTsk.o.d ${OBJECTDIR}/_ext/1447902105/TCP.o.d ${OBJECTDIR}/_ext/1447902105/Tick.o.d ${OBJECTDIR}/_ext/1447902105/UDP.o.d ${OBJECTDIR}/_ext/2063154737/tcpip.o.d ${OBJECTDIR}/_ext/2063154737/WF_Config.o.d ${OBJECTDIR}/_ext/252269054/serial_usb.o.d ${OBJECTDIR}/_ext/252269054/usb_descriptors.o.d ${OBJECTDIR}/_ext/252269054/usb_device.o.d ${OBJECTDIR}/_ext/252269054/usb_function_cdc.o.d ${OBJECTDIR}/_ext/733900163/server.o.d ${OBJECTDIR}/_ext/733900163/static.o.d ${OBJECTDIR}/_ext/2063154737/wifi.o.d ${OBJECTDIR}/_ext/733900163/networks.o.d ${OBJECTDIR}/_ext/733900163/utilities.o.d ${OBJECTDIR}/_ext/66270815/cJSON.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360919890/app.o ${OBJECTDIR}/_ext/2048433900/simpledelay.o ${OBJECTDIR}/_ext/66509721/rtcc_helper.o ${OBJECTDIR}/_ext/1410781165/diskio.o ${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o ${OBJECTDIR}/_ext/1410781165/ff.o ${OBJECTDIR}/_ext/1410781165/sdcard.o ${OBJECTDIR}/_ext/1410781165/sdcard_helper.o ${OBJECTDIR}/_ext/1410781165/ccsbcs.o ${OBJECTDIR}/_ext/1985307369/WF_Eint.o ${OBJECTDIR}/_ext/1985307369/WF_Spi.o ${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o ${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o ${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o ${OBJECTDIR}/_ext/1985307369/WFConsole.o ${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o ${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o ${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o ${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o ${OBJECTDIR}/_ext/1985307369/WFDriverCom.o ${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o ${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o ${OBJECTDIR}/_ext/1985307369/WFEventHandler.o ${OBJECTDIR}/_ext/1985307369/WFInit.o ${OBJECTDIR}/_ext/1985307369/WFMac.o ${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o ${OBJECTDIR}/_ext/1985307369/WFParamMsg.o ${OBJECTDIR}/_ext/1985307369/WFPowerSave.o ${OBJECTDIR}/_ext/1985307369/WFScan.o ${OBJECTDIR}/_ext/1985307369/WFTxPower.o ${OBJECTDIR}/_ext/1447902105/Announce.o ${OBJECTDIR}/_ext/1447902105/ARP.o ${OBJECTDIR}/_ext/1447902105/AutoIP.o ${OBJECTDIR}/_ext/1447902105/BigInt.o ${OBJECTDIR}/_ext/1447902105/DHCP.o ${OBJECTDIR}/_ext/1447902105/DHCPs.o ${OBJECTDIR}/_ext/1447902105/DNS.o ${OBJECTDIR}/_ext/1447902105/DNSs.o ${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o ${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o ${OBJECTDIR}/_ext/1447902105/Helpers.o ${OBJECTDIR}/_ext/1447902105/ICMP.o ${OBJECTDIR}/_ext/1447902105/IP.o ${OBJECTDIR}/_ext/1447902105/NBNS.o ${OBJECTDIR}/_ext/1447902105/StackTsk.o ${OBJECTDIR}/_ext/1447902105/TCP.o ${OBJECTDIR}/_ext/1447902105/Tick.o ${OBJECTDIR}/_ext/1447902105/UDP.o ${OBJECTDIR}/_ext/2063154737/tcpip.o ${OBJECTDIR}/_ext/2063154737/WF_Config.o ${OBJECTDIR}/_ext/252269054/serial_usb.o ${OBJECTDIR}/_ext/252269054/usb_descriptors.o ${OBJECTDIR}/_ext/252269054/usb_device.o ${OBJECTDIR}/_ext/252269054/usb_function_cdc.o ${OBJECTDIR}/_ext/733900163/server.o ${OBJECTDIR}/_ext/733900163/static.o ${OBJECTDIR}/_ext/2063154737/wifi.o ${OBJECTDIR}/_ext/733900163/networks.o ${OBJECTDIR}/_ext/733900163/utilities.o ${OBJECTDIR}/_ext/66270815/cJSON.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/waterworx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=,--script="..\app\skink.ld"
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
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360919890/app.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1360919890/app.o.d" -o ${OBJECTDIR}/_ext/1360919890/app.o ../app/app.c  
	
${OBJECTDIR}/_ext/2048433900/simpledelay.o: ../modules/delay/simpledelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048433900 
	@${RM} ${OBJECTDIR}/_ext/2048433900/simpledelay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048433900/simpledelay.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/2048433900/simpledelay.o.d" -o ${OBJECTDIR}/_ext/2048433900/simpledelay.o ../modules/delay/simpledelay.c  
	
${OBJECTDIR}/_ext/66509721/rtcc_helper.o: ../modules/rtcc/rtcc_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66509721 
	@${RM} ${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d" -o ${OBJECTDIR}/_ext/66509721/rtcc_helper.o ../modules/rtcc/rtcc_helper.c  
	
${OBJECTDIR}/_ext/1410781165/diskio.o: ../modules/sdcard/src/diskio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/diskio.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/diskio.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/diskio.o.d" -o ${OBJECTDIR}/_ext/1410781165/diskio.o ../modules/sdcard/src/diskio.c  
	
${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o: ../modules/sdcard/src/fatfs_mmc_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o.d" -o ${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o ../modules/sdcard/src/fatfs_mmc_spi.c  
	
${OBJECTDIR}/_ext/1410781165/ff.o: ../modules/sdcard/src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/ff.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/ff.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/ff.o.d" -o ${OBJECTDIR}/_ext/1410781165/ff.o ../modules/sdcard/src/ff.c  
	
${OBJECTDIR}/_ext/1410781165/sdcard.o: ../modules/sdcard/src/sdcard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/sdcard.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/sdcard.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/sdcard.o.d" -o ${OBJECTDIR}/_ext/1410781165/sdcard.o ../modules/sdcard/src/sdcard.c  
	
${OBJECTDIR}/_ext/1410781165/sdcard_helper.o: ../modules/sdcard/src/sdcard_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/sdcard_helper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/sdcard_helper.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/sdcard_helper.o.d" -o ${OBJECTDIR}/_ext/1410781165/sdcard_helper.o ../modules/sdcard/src/sdcard_helper.c  
	
${OBJECTDIR}/_ext/1410781165/ccsbcs.o: ../modules/sdcard/src/ccsbcs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/ccsbcs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/ccsbcs.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/ccsbcs.o.d" -o ${OBJECTDIR}/_ext/1410781165/ccsbcs.o ../modules/sdcard/src/ccsbcs.c  
	
${OBJECTDIR}/_ext/1985307369/WF_Eint.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WF_Eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WF_Eint.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WF_Eint.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WF_Eint.o.d" -o ${OBJECTDIR}/_ext/1985307369/WF_Eint.o "../modules/tcpip/TCPIP Stack/wifi_src/WF_Eint.c"  
	
${OBJECTDIR}/_ext/1985307369/WF_Spi.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WF_Spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WF_Spi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WF_Spi.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WF_Spi.o.d" -o ${OBJECTDIR}/_ext/1985307369/WF_Spi.o "../modules/tcpip/TCPIP Stack/wifi_src/WF_Spi.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConnectionAlgorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConnectionAlgorithm.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConnectionManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConnectionManager.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConnectionProfile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConnectionProfile.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsole.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsole.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsole.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsole.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsole.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsole.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsole.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleIfconfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleIfconfig.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleIwconfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleIwconfig.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleIwpriv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleIwpriv.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleMsgHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleMsgHandler.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleMsgs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleMsgs.c"  
	
${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFDataTxRx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o "../modules/tcpip/TCPIP Stack/wifi_src/WFDataTxRx.c"  
	
${OBJECTDIR}/_ext/1985307369/WFDriverCom.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFDriverCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFDriverCom.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFDriverCom.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFDriverCom.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFDriverCom.o "../modules/tcpip/TCPIP Stack/wifi_src/WFDriverCom.c"  
	
${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFDriverRaw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o "../modules/tcpip/TCPIP Stack/wifi_src/WFDriverRaw.c"  
	
${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFEasyConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o "../modules/tcpip/TCPIP Stack/wifi_src/WFEasyConfig.c"  
	
${OBJECTDIR}/_ext/1985307369/WFEventHandler.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFEventHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFEventHandler.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFEventHandler.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFEventHandler.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFEventHandler.o "../modules/tcpip/TCPIP Stack/wifi_src/WFEventHandler.c"  
	
${OBJECTDIR}/_ext/1985307369/WFInit.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFInit.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFInit.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFInit.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFInit.o "../modules/tcpip/TCPIP Stack/wifi_src/WFInit.c"  
	
${OBJECTDIR}/_ext/1985307369/WFMac.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFMac.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFMac.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFMac.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFMac.o "../modules/tcpip/TCPIP Stack/wifi_src/WFMac.c"  
	
${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFMgmtMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o "../modules/tcpip/TCPIP Stack/wifi_src/WFMgmtMsg.c"  
	
${OBJECTDIR}/_ext/1985307369/WFParamMsg.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFParamMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFParamMsg.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFParamMsg.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFParamMsg.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFParamMsg.o "../modules/tcpip/TCPIP Stack/wifi_src/WFParamMsg.c"  
	
${OBJECTDIR}/_ext/1985307369/WFPowerSave.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFPowerSave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFPowerSave.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFPowerSave.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFPowerSave.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFPowerSave.o "../modules/tcpip/TCPIP Stack/wifi_src/WFPowerSave.c"  
	
${OBJECTDIR}/_ext/1985307369/WFScan.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFScan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFScan.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFScan.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFScan.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFScan.o "../modules/tcpip/TCPIP Stack/wifi_src/WFScan.c"  
	
${OBJECTDIR}/_ext/1985307369/WFTxPower.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFTxPower.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFTxPower.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFTxPower.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFTxPower.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFTxPower.o "../modules/tcpip/TCPIP Stack/wifi_src/WFTxPower.c"  
	
${OBJECTDIR}/_ext/1447902105/Announce.o: ../modules/tcpip/TCPIP\ Stack/src/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/Announce.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/Announce.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/Announce.o.d" -o ${OBJECTDIR}/_ext/1447902105/Announce.o "../modules/tcpip/TCPIP Stack/src/Announce.c"  
	
${OBJECTDIR}/_ext/1447902105/ARP.o: ../modules/tcpip/TCPIP\ Stack/src/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/ARP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/ARP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/ARP.o.d" -o ${OBJECTDIR}/_ext/1447902105/ARP.o "../modules/tcpip/TCPIP Stack/src/ARP.c"  
	
${OBJECTDIR}/_ext/1447902105/AutoIP.o: ../modules/tcpip/TCPIP\ Stack/src/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/AutoIP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/AutoIP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/AutoIP.o.d" -o ${OBJECTDIR}/_ext/1447902105/AutoIP.o "../modules/tcpip/TCPIP Stack/src/AutoIP.c"  
	
${OBJECTDIR}/_ext/1447902105/BigInt.o: ../modules/tcpip/TCPIP\ Stack/src/BigInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/BigInt.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/BigInt.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/BigInt.o.d" -o ${OBJECTDIR}/_ext/1447902105/BigInt.o "../modules/tcpip/TCPIP Stack/src/BigInt.c"  
	
${OBJECTDIR}/_ext/1447902105/DHCP.o: ../modules/tcpip/TCPIP\ Stack/src/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/DHCP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/DHCP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/DHCP.o.d" -o ${OBJECTDIR}/_ext/1447902105/DHCP.o "../modules/tcpip/TCPIP Stack/src/DHCP.c"  
	
${OBJECTDIR}/_ext/1447902105/DHCPs.o: ../modules/tcpip/TCPIP\ Stack/src/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/DHCPs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/DHCPs.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/DHCPs.o.d" -o ${OBJECTDIR}/_ext/1447902105/DHCPs.o "../modules/tcpip/TCPIP Stack/src/DHCPs.c"  
	
${OBJECTDIR}/_ext/1447902105/DNS.o: ../modules/tcpip/TCPIP\ Stack/src/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/DNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/DNS.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/DNS.o.d" -o ${OBJECTDIR}/_ext/1447902105/DNS.o "../modules/tcpip/TCPIP Stack/src/DNS.c"  
	
${OBJECTDIR}/_ext/1447902105/DNSs.o: ../modules/tcpip/TCPIP\ Stack/src/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/DNSs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/DNSs.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/DNSs.o.d" -o ${OBJECTDIR}/_ext/1447902105/DNSs.o "../modules/tcpip/TCPIP Stack/src/DNSs.c"  
	
${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o: ../modules/tcpip/TCPIP\ Stack/src/ETHPIC32ExtPhy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o.d" -o ${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o "../modules/tcpip/TCPIP Stack/src/ETHPIC32ExtPhy.c"  
	
${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o: ../modules/tcpip/TCPIP\ Stack/src/ETHPIC32IntMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o.d" -o ${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o "../modules/tcpip/TCPIP Stack/src/ETHPIC32IntMac.c"  
	
${OBJECTDIR}/_ext/1447902105/Helpers.o: ../modules/tcpip/TCPIP\ Stack/src/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/Helpers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/Helpers.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/Helpers.o.d" -o ${OBJECTDIR}/_ext/1447902105/Helpers.o "../modules/tcpip/TCPIP Stack/src/Helpers.c"  
	
${OBJECTDIR}/_ext/1447902105/ICMP.o: ../modules/tcpip/TCPIP\ Stack/src/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/ICMP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/ICMP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/ICMP.o.d" -o ${OBJECTDIR}/_ext/1447902105/ICMP.o "../modules/tcpip/TCPIP Stack/src/ICMP.c"  
	
${OBJECTDIR}/_ext/1447902105/IP.o: ../modules/tcpip/TCPIP\ Stack/src/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/IP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/IP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/IP.o.d" -o ${OBJECTDIR}/_ext/1447902105/IP.o "../modules/tcpip/TCPIP Stack/src/IP.c"  
	
${OBJECTDIR}/_ext/1447902105/NBNS.o: ../modules/tcpip/TCPIP\ Stack/src/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/NBNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/NBNS.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/NBNS.o.d" -o ${OBJECTDIR}/_ext/1447902105/NBNS.o "../modules/tcpip/TCPIP Stack/src/NBNS.c"  
	
${OBJECTDIR}/_ext/1447902105/StackTsk.o: ../modules/tcpip/TCPIP\ Stack/src/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/StackTsk.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/StackTsk.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/StackTsk.o.d" -o ${OBJECTDIR}/_ext/1447902105/StackTsk.o "../modules/tcpip/TCPIP Stack/src/StackTsk.c"  
	
${OBJECTDIR}/_ext/1447902105/TCP.o: ../modules/tcpip/TCPIP\ Stack/src/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/TCP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/TCP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/TCP.o.d" -o ${OBJECTDIR}/_ext/1447902105/TCP.o "../modules/tcpip/TCPIP Stack/src/TCP.c"  
	
${OBJECTDIR}/_ext/1447902105/Tick.o: ../modules/tcpip/TCPIP\ Stack/src/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/Tick.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/Tick.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/Tick.o.d" -o ${OBJECTDIR}/_ext/1447902105/Tick.o "../modules/tcpip/TCPIP Stack/src/Tick.c"  
	
${OBJECTDIR}/_ext/1447902105/UDP.o: ../modules/tcpip/TCPIP\ Stack/src/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/UDP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/UDP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/UDP.o.d" -o ${OBJECTDIR}/_ext/1447902105/UDP.o "../modules/tcpip/TCPIP Stack/src/UDP.c"  
	
${OBJECTDIR}/_ext/2063154737/tcpip.o: ../modules/tcpip/tcpip.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2063154737 
	@${RM} ${OBJECTDIR}/_ext/2063154737/tcpip.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2063154737/tcpip.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/2063154737/tcpip.o.d" -o ${OBJECTDIR}/_ext/2063154737/tcpip.o ../modules/tcpip/tcpip.c  
	
${OBJECTDIR}/_ext/2063154737/WF_Config.o: ../modules/tcpip/WF_Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2063154737 
	@${RM} ${OBJECTDIR}/_ext/2063154737/WF_Config.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2063154737/WF_Config.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/2063154737/WF_Config.o.d" -o ${OBJECTDIR}/_ext/2063154737/WF_Config.o ../modules/tcpip/WF_Config.c  
	
${OBJECTDIR}/_ext/252269054/serial_usb.o: ../modules/usb/src/serial_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/252269054 
	@${RM} ${OBJECTDIR}/_ext/252269054/serial_usb.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252269054/serial_usb.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/252269054/serial_usb.o.d" -o ${OBJECTDIR}/_ext/252269054/serial_usb.o ../modules/usb/src/serial_usb.c  
	
${OBJECTDIR}/_ext/252269054/usb_descriptors.o: ../modules/usb/src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/252269054 
	@${RM} ${OBJECTDIR}/_ext/252269054/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252269054/usb_descriptors.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/252269054/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/252269054/usb_descriptors.o ../modules/usb/src/usb_descriptors.c  
	
${OBJECTDIR}/_ext/252269054/usb_device.o: ../modules/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/252269054 
	@${RM} ${OBJECTDIR}/_ext/252269054/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252269054/usb_device.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/252269054/usb_device.o.d" -o ${OBJECTDIR}/_ext/252269054/usb_device.o ../modules/usb/src/usb_device.c  
	
${OBJECTDIR}/_ext/252269054/usb_function_cdc.o: ../modules/usb/src/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/252269054 
	@${RM} ${OBJECTDIR}/_ext/252269054/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252269054/usb_function_cdc.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/252269054/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/252269054/usb_function_cdc.o ../modules/usb/src/usb_function_cdc.c  
	
${OBJECTDIR}/_ext/733900163/server.o: ../modules/http_server/server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/733900163 
	@${RM} ${OBJECTDIR}/_ext/733900163/server.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/733900163/server.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/733900163/server.o.d" -o ${OBJECTDIR}/_ext/733900163/server.o ../modules/http_server/server.c  
	
${OBJECTDIR}/_ext/733900163/static.o: ../modules/http_server/static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/733900163 
	@${RM} ${OBJECTDIR}/_ext/733900163/static.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/733900163/static.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/733900163/static.o.d" -o ${OBJECTDIR}/_ext/733900163/static.o ../modules/http_server/static.c  
	
${OBJECTDIR}/_ext/2063154737/wifi.o: ../modules/tcpip/wifi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2063154737 
	@${RM} ${OBJECTDIR}/_ext/2063154737/wifi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2063154737/wifi.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/2063154737/wifi.o.d" -o ${OBJECTDIR}/_ext/2063154737/wifi.o ../modules/tcpip/wifi.c  
	
${OBJECTDIR}/_ext/733900163/networks.o: ../modules/http_server/networks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/733900163 
	@${RM} ${OBJECTDIR}/_ext/733900163/networks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/733900163/networks.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/733900163/networks.o.d" -o ${OBJECTDIR}/_ext/733900163/networks.o ../modules/http_server/networks.c  
	
${OBJECTDIR}/_ext/733900163/utilities.o: ../modules/http_server/utilities.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/733900163 
	@${RM} ${OBJECTDIR}/_ext/733900163/utilities.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/733900163/utilities.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/733900163/utilities.o.d" -o ${OBJECTDIR}/_ext/733900163/utilities.o ../modules/http_server/utilities.c  
	
${OBJECTDIR}/_ext/66270815/cJSON.o: ../modules/json/cJSON.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66270815 
	@${RM} ${OBJECTDIR}/_ext/66270815/cJSON.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66270815/cJSON.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/66270815/cJSON.o.d" -o ${OBJECTDIR}/_ext/66270815/cJSON.o ../modules/json/cJSON.c  
	
else
${OBJECTDIR}/_ext/1360919890/app.o: ../app/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360919890 
	@${RM} ${OBJECTDIR}/_ext/1360919890/app.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360919890/app.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1360919890/app.o.d" -o ${OBJECTDIR}/_ext/1360919890/app.o ../app/app.c  
	
${OBJECTDIR}/_ext/2048433900/simpledelay.o: ../modules/delay/simpledelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048433900 
	@${RM} ${OBJECTDIR}/_ext/2048433900/simpledelay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048433900/simpledelay.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/2048433900/simpledelay.o.d" -o ${OBJECTDIR}/_ext/2048433900/simpledelay.o ../modules/delay/simpledelay.c  
	
${OBJECTDIR}/_ext/66509721/rtcc_helper.o: ../modules/rtcc/rtcc_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66509721 
	@${RM} ${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/66509721/rtcc_helper.o.d" -o ${OBJECTDIR}/_ext/66509721/rtcc_helper.o ../modules/rtcc/rtcc_helper.c  
	
${OBJECTDIR}/_ext/1410781165/diskio.o: ../modules/sdcard/src/diskio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/diskio.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/diskio.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/diskio.o.d" -o ${OBJECTDIR}/_ext/1410781165/diskio.o ../modules/sdcard/src/diskio.c  
	
${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o: ../modules/sdcard/src/fatfs_mmc_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o.d" -o ${OBJECTDIR}/_ext/1410781165/fatfs_mmc_spi.o ../modules/sdcard/src/fatfs_mmc_spi.c  
	
${OBJECTDIR}/_ext/1410781165/ff.o: ../modules/sdcard/src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/ff.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/ff.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/ff.o.d" -o ${OBJECTDIR}/_ext/1410781165/ff.o ../modules/sdcard/src/ff.c  
	
${OBJECTDIR}/_ext/1410781165/sdcard.o: ../modules/sdcard/src/sdcard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/sdcard.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/sdcard.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/sdcard.o.d" -o ${OBJECTDIR}/_ext/1410781165/sdcard.o ../modules/sdcard/src/sdcard.c  
	
${OBJECTDIR}/_ext/1410781165/sdcard_helper.o: ../modules/sdcard/src/sdcard_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/sdcard_helper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/sdcard_helper.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/sdcard_helper.o.d" -o ${OBJECTDIR}/_ext/1410781165/sdcard_helper.o ../modules/sdcard/src/sdcard_helper.c  
	
${OBJECTDIR}/_ext/1410781165/ccsbcs.o: ../modules/sdcard/src/ccsbcs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1410781165 
	@${RM} ${OBJECTDIR}/_ext/1410781165/ccsbcs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1410781165/ccsbcs.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1410781165/ccsbcs.o.d" -o ${OBJECTDIR}/_ext/1410781165/ccsbcs.o ../modules/sdcard/src/ccsbcs.c  
	
${OBJECTDIR}/_ext/1985307369/WF_Eint.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WF_Eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WF_Eint.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WF_Eint.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WF_Eint.o.d" -o ${OBJECTDIR}/_ext/1985307369/WF_Eint.o "../modules/tcpip/TCPIP Stack/wifi_src/WF_Eint.c"  
	
${OBJECTDIR}/_ext/1985307369/WF_Spi.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WF_Spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WF_Spi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WF_Spi.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WF_Spi.o.d" -o ${OBJECTDIR}/_ext/1985307369/WF_Spi.o "../modules/tcpip/TCPIP Stack/wifi_src/WF_Spi.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConnectionAlgorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConnectionAlgorithm.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConnectionAlgorithm.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConnectionManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConnectionManager.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConnectionManager.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConnectionProfile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConnectionProfile.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConnectionProfile.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsole.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsole.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsole.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsole.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsole.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsole.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsole.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleIfconfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleIfconfig.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleIfconfig.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleIwconfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleIwconfig.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleIwconfig.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleIwpriv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleIwpriv.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleIwpriv.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleMsgHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgHandler.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleMsgHandler.c"  
	
${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFConsoleMsgs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFConsoleMsgs.o "../modules/tcpip/TCPIP Stack/wifi_src/WFConsoleMsgs.c"  
	
${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFDataTxRx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFDataTxRx.o "../modules/tcpip/TCPIP Stack/wifi_src/WFDataTxRx.c"  
	
${OBJECTDIR}/_ext/1985307369/WFDriverCom.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFDriverCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFDriverCom.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFDriverCom.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFDriverCom.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFDriverCom.o "../modules/tcpip/TCPIP Stack/wifi_src/WFDriverCom.c"  
	
${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFDriverRaw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFDriverRaw.o "../modules/tcpip/TCPIP Stack/wifi_src/WFDriverRaw.c"  
	
${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFEasyConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFEasyConfig.o "../modules/tcpip/TCPIP Stack/wifi_src/WFEasyConfig.c"  
	
${OBJECTDIR}/_ext/1985307369/WFEventHandler.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFEventHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFEventHandler.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFEventHandler.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFEventHandler.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFEventHandler.o "../modules/tcpip/TCPIP Stack/wifi_src/WFEventHandler.c"  
	
${OBJECTDIR}/_ext/1985307369/WFInit.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFInit.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFInit.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFInit.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFInit.o "../modules/tcpip/TCPIP Stack/wifi_src/WFInit.c"  
	
${OBJECTDIR}/_ext/1985307369/WFMac.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFMac.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFMac.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFMac.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFMac.o "../modules/tcpip/TCPIP Stack/wifi_src/WFMac.c"  
	
${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFMgmtMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFMgmtMsg.o "../modules/tcpip/TCPIP Stack/wifi_src/WFMgmtMsg.c"  
	
${OBJECTDIR}/_ext/1985307369/WFParamMsg.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFParamMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFParamMsg.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFParamMsg.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFParamMsg.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFParamMsg.o "../modules/tcpip/TCPIP Stack/wifi_src/WFParamMsg.c"  
	
${OBJECTDIR}/_ext/1985307369/WFPowerSave.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFPowerSave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFPowerSave.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFPowerSave.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFPowerSave.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFPowerSave.o "../modules/tcpip/TCPIP Stack/wifi_src/WFPowerSave.c"  
	
${OBJECTDIR}/_ext/1985307369/WFScan.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFScan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFScan.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFScan.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFScan.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFScan.o "../modules/tcpip/TCPIP Stack/wifi_src/WFScan.c"  
	
${OBJECTDIR}/_ext/1985307369/WFTxPower.o: ../modules/tcpip/TCPIP\ Stack/wifi_src/WFTxPower.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1985307369 
	@${RM} ${OBJECTDIR}/_ext/1985307369/WFTxPower.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1985307369/WFTxPower.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1985307369/WFTxPower.o.d" -o ${OBJECTDIR}/_ext/1985307369/WFTxPower.o "../modules/tcpip/TCPIP Stack/wifi_src/WFTxPower.c"  
	
${OBJECTDIR}/_ext/1447902105/Announce.o: ../modules/tcpip/TCPIP\ Stack/src/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/Announce.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/Announce.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/Announce.o.d" -o ${OBJECTDIR}/_ext/1447902105/Announce.o "../modules/tcpip/TCPIP Stack/src/Announce.c"  
	
${OBJECTDIR}/_ext/1447902105/ARP.o: ../modules/tcpip/TCPIP\ Stack/src/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/ARP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/ARP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/ARP.o.d" -o ${OBJECTDIR}/_ext/1447902105/ARP.o "../modules/tcpip/TCPIP Stack/src/ARP.c"  
	
${OBJECTDIR}/_ext/1447902105/AutoIP.o: ../modules/tcpip/TCPIP\ Stack/src/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/AutoIP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/AutoIP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/AutoIP.o.d" -o ${OBJECTDIR}/_ext/1447902105/AutoIP.o "../modules/tcpip/TCPIP Stack/src/AutoIP.c"  
	
${OBJECTDIR}/_ext/1447902105/BigInt.o: ../modules/tcpip/TCPIP\ Stack/src/BigInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/BigInt.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/BigInt.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/BigInt.o.d" -o ${OBJECTDIR}/_ext/1447902105/BigInt.o "../modules/tcpip/TCPIP Stack/src/BigInt.c"  
	
${OBJECTDIR}/_ext/1447902105/DHCP.o: ../modules/tcpip/TCPIP\ Stack/src/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/DHCP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/DHCP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/DHCP.o.d" -o ${OBJECTDIR}/_ext/1447902105/DHCP.o "../modules/tcpip/TCPIP Stack/src/DHCP.c"  
	
${OBJECTDIR}/_ext/1447902105/DHCPs.o: ../modules/tcpip/TCPIP\ Stack/src/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/DHCPs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/DHCPs.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/DHCPs.o.d" -o ${OBJECTDIR}/_ext/1447902105/DHCPs.o "../modules/tcpip/TCPIP Stack/src/DHCPs.c"  
	
${OBJECTDIR}/_ext/1447902105/DNS.o: ../modules/tcpip/TCPIP\ Stack/src/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/DNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/DNS.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/DNS.o.d" -o ${OBJECTDIR}/_ext/1447902105/DNS.o "../modules/tcpip/TCPIP Stack/src/DNS.c"  
	
${OBJECTDIR}/_ext/1447902105/DNSs.o: ../modules/tcpip/TCPIP\ Stack/src/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/DNSs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/DNSs.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/DNSs.o.d" -o ${OBJECTDIR}/_ext/1447902105/DNSs.o "../modules/tcpip/TCPIP Stack/src/DNSs.c"  
	
${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o: ../modules/tcpip/TCPIP\ Stack/src/ETHPIC32ExtPhy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o.d" -o ${OBJECTDIR}/_ext/1447902105/ETHPIC32ExtPhy.o "../modules/tcpip/TCPIP Stack/src/ETHPIC32ExtPhy.c"  
	
${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o: ../modules/tcpip/TCPIP\ Stack/src/ETHPIC32IntMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o.d" -o ${OBJECTDIR}/_ext/1447902105/ETHPIC32IntMac.o "../modules/tcpip/TCPIP Stack/src/ETHPIC32IntMac.c"  
	
${OBJECTDIR}/_ext/1447902105/Helpers.o: ../modules/tcpip/TCPIP\ Stack/src/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/Helpers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/Helpers.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/Helpers.o.d" -o ${OBJECTDIR}/_ext/1447902105/Helpers.o "../modules/tcpip/TCPIP Stack/src/Helpers.c"  
	
${OBJECTDIR}/_ext/1447902105/ICMP.o: ../modules/tcpip/TCPIP\ Stack/src/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/ICMP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/ICMP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/ICMP.o.d" -o ${OBJECTDIR}/_ext/1447902105/ICMP.o "../modules/tcpip/TCPIP Stack/src/ICMP.c"  
	
${OBJECTDIR}/_ext/1447902105/IP.o: ../modules/tcpip/TCPIP\ Stack/src/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/IP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/IP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/IP.o.d" -o ${OBJECTDIR}/_ext/1447902105/IP.o "../modules/tcpip/TCPIP Stack/src/IP.c"  
	
${OBJECTDIR}/_ext/1447902105/NBNS.o: ../modules/tcpip/TCPIP\ Stack/src/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/NBNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/NBNS.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/NBNS.o.d" -o ${OBJECTDIR}/_ext/1447902105/NBNS.o "../modules/tcpip/TCPIP Stack/src/NBNS.c"  
	
${OBJECTDIR}/_ext/1447902105/StackTsk.o: ../modules/tcpip/TCPIP\ Stack/src/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/StackTsk.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/StackTsk.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/StackTsk.o.d" -o ${OBJECTDIR}/_ext/1447902105/StackTsk.o "../modules/tcpip/TCPIP Stack/src/StackTsk.c"  
	
${OBJECTDIR}/_ext/1447902105/TCP.o: ../modules/tcpip/TCPIP\ Stack/src/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/TCP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/TCP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/TCP.o.d" -o ${OBJECTDIR}/_ext/1447902105/TCP.o "../modules/tcpip/TCPIP Stack/src/TCP.c"  
	
${OBJECTDIR}/_ext/1447902105/Tick.o: ../modules/tcpip/TCPIP\ Stack/src/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/Tick.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/Tick.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/Tick.o.d" -o ${OBJECTDIR}/_ext/1447902105/Tick.o "../modules/tcpip/TCPIP Stack/src/Tick.c"  
	
${OBJECTDIR}/_ext/1447902105/UDP.o: ../modules/tcpip/TCPIP\ Stack/src/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1447902105 
	@${RM} ${OBJECTDIR}/_ext/1447902105/UDP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1447902105/UDP.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/1447902105/UDP.o.d" -o ${OBJECTDIR}/_ext/1447902105/UDP.o "../modules/tcpip/TCPIP Stack/src/UDP.c"  
	
${OBJECTDIR}/_ext/2063154737/tcpip.o: ../modules/tcpip/tcpip.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2063154737 
	@${RM} ${OBJECTDIR}/_ext/2063154737/tcpip.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2063154737/tcpip.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/2063154737/tcpip.o.d" -o ${OBJECTDIR}/_ext/2063154737/tcpip.o ../modules/tcpip/tcpip.c  
	
${OBJECTDIR}/_ext/2063154737/WF_Config.o: ../modules/tcpip/WF_Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2063154737 
	@${RM} ${OBJECTDIR}/_ext/2063154737/WF_Config.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2063154737/WF_Config.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/2063154737/WF_Config.o.d" -o ${OBJECTDIR}/_ext/2063154737/WF_Config.o ../modules/tcpip/WF_Config.c  
	
${OBJECTDIR}/_ext/252269054/serial_usb.o: ../modules/usb/src/serial_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/252269054 
	@${RM} ${OBJECTDIR}/_ext/252269054/serial_usb.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252269054/serial_usb.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/252269054/serial_usb.o.d" -o ${OBJECTDIR}/_ext/252269054/serial_usb.o ../modules/usb/src/serial_usb.c  
	
${OBJECTDIR}/_ext/252269054/usb_descriptors.o: ../modules/usb/src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/252269054 
	@${RM} ${OBJECTDIR}/_ext/252269054/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252269054/usb_descriptors.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/252269054/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/252269054/usb_descriptors.o ../modules/usb/src/usb_descriptors.c  
	
${OBJECTDIR}/_ext/252269054/usb_device.o: ../modules/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/252269054 
	@${RM} ${OBJECTDIR}/_ext/252269054/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252269054/usb_device.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/252269054/usb_device.o.d" -o ${OBJECTDIR}/_ext/252269054/usb_device.o ../modules/usb/src/usb_device.c  
	
${OBJECTDIR}/_ext/252269054/usb_function_cdc.o: ../modules/usb/src/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/252269054 
	@${RM} ${OBJECTDIR}/_ext/252269054/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252269054/usb_function_cdc.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/252269054/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/252269054/usb_function_cdc.o ../modules/usb/src/usb_function_cdc.c  
	
${OBJECTDIR}/_ext/733900163/server.o: ../modules/http_server/server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/733900163 
	@${RM} ${OBJECTDIR}/_ext/733900163/server.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/733900163/server.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/733900163/server.o.d" -o ${OBJECTDIR}/_ext/733900163/server.o ../modules/http_server/server.c  
	
${OBJECTDIR}/_ext/733900163/static.o: ../modules/http_server/static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/733900163 
	@${RM} ${OBJECTDIR}/_ext/733900163/static.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/733900163/static.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/733900163/static.o.d" -o ${OBJECTDIR}/_ext/733900163/static.o ../modules/http_server/static.c  
	
${OBJECTDIR}/_ext/2063154737/wifi.o: ../modules/tcpip/wifi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2063154737 
	@${RM} ${OBJECTDIR}/_ext/2063154737/wifi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2063154737/wifi.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/2063154737/wifi.o.d" -o ${OBJECTDIR}/_ext/2063154737/wifi.o ../modules/tcpip/wifi.c  
	
${OBJECTDIR}/_ext/733900163/networks.o: ../modules/http_server/networks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/733900163 
	@${RM} ${OBJECTDIR}/_ext/733900163/networks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/733900163/networks.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/733900163/networks.o.d" -o ${OBJECTDIR}/_ext/733900163/networks.o ../modules/http_server/networks.c  
	
${OBJECTDIR}/_ext/733900163/utilities.o: ../modules/http_server/utilities.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/733900163 
	@${RM} ${OBJECTDIR}/_ext/733900163/utilities.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/733900163/utilities.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/733900163/utilities.o.d" -o ${OBJECTDIR}/_ext/733900163/utilities.o ../modules/http_server/utilities.c  
	
${OBJECTDIR}/_ext/66270815/cJSON.o: ../modules/json/cJSON.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/66270815 
	@${RM} ${OBJECTDIR}/_ext/66270815/cJSON.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/66270815/cJSON.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../modules/tcpip" -I"../app" -I"../modules/base" -I"../modules" -I"../modules/http_server" -I"../modules/usb" -I"../modules/delay" -I"../modules/tcpip/TCPIP Stack" -I"../modules/sdcard" -I"../modules/rtcc" -MMD -MF "${OBJECTDIR}/_ext/66270815/cJSON.o.d" -o ${OBJECTDIR}/_ext/66270815/cJSON.o ../modules/json/cJSON.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/waterworx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/waterworx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=8192,-L"..",-Map="${DISTDIR}/waterworx.X.${IMAGE_TYPE}.map"
else
dist/${CND_CONF}/${IMAGE_TYPE}/waterworx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/waterworx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=8192,-L"..",-Map="${DISTDIR}/waterworx.X.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/waterworx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
