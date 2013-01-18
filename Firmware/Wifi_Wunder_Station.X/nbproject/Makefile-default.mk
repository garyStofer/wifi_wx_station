#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Wifi_Wunder_Station.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Wifi_Wunder_Station.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/CustomHTTPApp.o ${OBJECTDIR}/src/UARTConfig.o ${OBJECTDIR}/src/NistTimeClient.o ${OBJECTDIR}/src/RTCC.o ${OBJECTDIR}/src/Main.o ${OBJECTDIR}/src/WunderHttpClient.o ${OBJECTDIR}/src/APP_cfg.o ${OBJECTDIR}/src/WX_perm_data.o ${OBJECTDIR}/src/I2C1.o ${OBJECTDIR}/src/HP03_Baro.o ${OBJECTDIR}/src/WF_Config.o ${OBJECTDIR}/src/HIH_6130.o ${OBJECTDIR}/src/Mail_Alarm.o ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o ${OBJECTDIR}/_ext/1711518555/WFConsole.o ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o ${OBJECTDIR}/_ext/1711518555/WFInit.o ${OBJECTDIR}/_ext/1711518555/WFMac.o ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o ${OBJECTDIR}/_ext/1711518555/WFScan.o ${OBJECTDIR}/_ext/1711518555/WFTxPower.o ${OBJECTDIR}/_ext/1711518555/WF_Eint.o ${OBJECTDIR}/_ext/1711518555/WF_Spi.o ${OBJECTDIR}/_ext/1302463167/Announce.o ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o ${OBJECTDIR}/_ext/1302463167/ARP.o ${OBJECTDIR}/_ext/1302463167/AutoIP.o ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o ${OBJECTDIR}/_ext/1302463167/BigInt.o ${OBJECTDIR}/_ext/1302463167/Delay.o ${OBJECTDIR}/_ext/1302463167/DHCP.o ${OBJECTDIR}/_ext/1302463167/DHCPs.o ${OBJECTDIR}/_ext/1302463167/DNS.o ${OBJECTDIR}/_ext/1302463167/DNSs.o ${OBJECTDIR}/_ext/1302463167/DynDNS.o ${OBJECTDIR}/_ext/1302463167/FileSystem.o ${OBJECTDIR}/_ext/1302463167/FTP.o ${OBJECTDIR}/_ext/1302463167/Hashes.o ${OBJECTDIR}/_ext/1302463167/Helpers.o ${OBJECTDIR}/_ext/1302463167/HTTP2.o ${OBJECTDIR}/_ext/1302463167/ICMP.o ${OBJECTDIR}/_ext/1302463167/IP.o ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o ${OBJECTDIR}/_ext/1302463167/MPFS2.o ${OBJECTDIR}/_ext/1302463167/NBNS.o ${OBJECTDIR}/_ext/1302463167/Random.o ${OBJECTDIR}/_ext/1302463167/Reboot.o ${OBJECTDIR}/_ext/1302463167/RSA.o ${OBJECTDIR}/_ext/1302463167/SMTP.o ${OBJECTDIR}/_ext/1302463167/SNMP.o ${OBJECTDIR}/_ext/1302463167/SNMPv3.o ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o ${OBJECTDIR}/_ext/1302463167/SNTP.o ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o ${OBJECTDIR}/_ext/1302463167/SPIFlash.o ${OBJECTDIR}/_ext/1302463167/SPIRAM.o ${OBJECTDIR}/_ext/1302463167/SSL.o ${OBJECTDIR}/_ext/1302463167/StackTsk.o ${OBJECTDIR}/_ext/1302463167/TCP.o ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o ${OBJECTDIR}/_ext/1302463167/Telnet.o ${OBJECTDIR}/_ext/1302463167/TFTPc.o ${OBJECTDIR}/_ext/1302463167/Tick.o ${OBJECTDIR}/_ext/1302463167/UART.o ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o ${OBJECTDIR}/_ext/1302463167/UDP.o ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o ${OBJECTDIR}/src/wind_rain_cnt.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/CustomHTTPApp.o.d ${OBJECTDIR}/src/UARTConfig.o.d ${OBJECTDIR}/src/NistTimeClient.o.d ${OBJECTDIR}/src/RTCC.o.d ${OBJECTDIR}/src/Main.o.d ${OBJECTDIR}/src/WunderHttpClient.o.d ${OBJECTDIR}/src/APP_cfg.o.d ${OBJECTDIR}/src/WX_perm_data.o.d ${OBJECTDIR}/src/I2C1.o.d ${OBJECTDIR}/src/HP03_Baro.o.d ${OBJECTDIR}/src/WF_Config.o.d ${OBJECTDIR}/src/HIH_6130.o.d ${OBJECTDIR}/src/Mail_Alarm.o.d ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.d ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.d ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.d ${OBJECTDIR}/_ext/1711518555/WFConsole.o.d ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.d ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.d ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.d ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.d ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.d ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.d ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.d ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.d ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.d ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.d ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.d ${OBJECTDIR}/_ext/1711518555/WFInit.o.d ${OBJECTDIR}/_ext/1711518555/WFMac.o.d ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.d ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.d ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.d ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.d ${OBJECTDIR}/_ext/1711518555/WFScan.o.d ${OBJECTDIR}/_ext/1711518555/WFTxPower.o.d ${OBJECTDIR}/_ext/1711518555/WF_Eint.o.d ${OBJECTDIR}/_ext/1711518555/WF_Spi.o.d ${OBJECTDIR}/_ext/1302463167/Announce.o.d ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.d ${OBJECTDIR}/_ext/1302463167/ARP.o.d ${OBJECTDIR}/_ext/1302463167/AutoIP.o.d ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.d ${OBJECTDIR}/_ext/1302463167/BigInt.o.d ${OBJECTDIR}/_ext/1302463167/Delay.o.d ${OBJECTDIR}/_ext/1302463167/DHCP.o.d ${OBJECTDIR}/_ext/1302463167/DHCPs.o.d ${OBJECTDIR}/_ext/1302463167/DNS.o.d ${OBJECTDIR}/_ext/1302463167/DNSs.o.d ${OBJECTDIR}/_ext/1302463167/DynDNS.o.d ${OBJECTDIR}/_ext/1302463167/FileSystem.o.d ${OBJECTDIR}/_ext/1302463167/FTP.o.d ${OBJECTDIR}/_ext/1302463167/Hashes.o.d ${OBJECTDIR}/_ext/1302463167/Helpers.o.d ${OBJECTDIR}/_ext/1302463167/HTTP2.o.d ${OBJECTDIR}/_ext/1302463167/ICMP.o.d ${OBJECTDIR}/_ext/1302463167/IP.o.d ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.d ${OBJECTDIR}/_ext/1302463167/MPFS2.o.d ${OBJECTDIR}/_ext/1302463167/NBNS.o.d ${OBJECTDIR}/_ext/1302463167/Random.o.d ${OBJECTDIR}/_ext/1302463167/Reboot.o.d ${OBJECTDIR}/_ext/1302463167/RSA.o.d ${OBJECTDIR}/_ext/1302463167/SMTP.o.d ${OBJECTDIR}/_ext/1302463167/SNMP.o.d ${OBJECTDIR}/_ext/1302463167/SNMPv3.o.d ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.d ${OBJECTDIR}/_ext/1302463167/SNTP.o.d ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.d ${OBJECTDIR}/_ext/1302463167/SPIFlash.o.d ${OBJECTDIR}/_ext/1302463167/SPIRAM.o.d ${OBJECTDIR}/_ext/1302463167/SSL.o.d ${OBJECTDIR}/_ext/1302463167/StackTsk.o.d ${OBJECTDIR}/_ext/1302463167/TCP.o.d ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.d ${OBJECTDIR}/_ext/1302463167/Telnet.o.d ${OBJECTDIR}/_ext/1302463167/TFTPc.o.d ${OBJECTDIR}/_ext/1302463167/Tick.o.d ${OBJECTDIR}/_ext/1302463167/UART.o.d ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.d ${OBJECTDIR}/_ext/1302463167/UDP.o.d ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.d ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.d ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.d ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.d ${OBJECTDIR}/src/wind_rain_cnt.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/CustomHTTPApp.o ${OBJECTDIR}/src/UARTConfig.o ${OBJECTDIR}/src/NistTimeClient.o ${OBJECTDIR}/src/RTCC.o ${OBJECTDIR}/src/Main.o ${OBJECTDIR}/src/WunderHttpClient.o ${OBJECTDIR}/src/APP_cfg.o ${OBJECTDIR}/src/WX_perm_data.o ${OBJECTDIR}/src/I2C1.o ${OBJECTDIR}/src/HP03_Baro.o ${OBJECTDIR}/src/WF_Config.o ${OBJECTDIR}/src/HIH_6130.o ${OBJECTDIR}/src/Mail_Alarm.o ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o ${OBJECTDIR}/_ext/1711518555/WFConsole.o ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o ${OBJECTDIR}/_ext/1711518555/WFInit.o ${OBJECTDIR}/_ext/1711518555/WFMac.o ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o ${OBJECTDIR}/_ext/1711518555/WFScan.o ${OBJECTDIR}/_ext/1711518555/WFTxPower.o ${OBJECTDIR}/_ext/1711518555/WF_Eint.o ${OBJECTDIR}/_ext/1711518555/WF_Spi.o ${OBJECTDIR}/_ext/1302463167/Announce.o ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o ${OBJECTDIR}/_ext/1302463167/ARP.o ${OBJECTDIR}/_ext/1302463167/AutoIP.o ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o ${OBJECTDIR}/_ext/1302463167/BigInt.o ${OBJECTDIR}/_ext/1302463167/Delay.o ${OBJECTDIR}/_ext/1302463167/DHCP.o ${OBJECTDIR}/_ext/1302463167/DHCPs.o ${OBJECTDIR}/_ext/1302463167/DNS.o ${OBJECTDIR}/_ext/1302463167/DNSs.o ${OBJECTDIR}/_ext/1302463167/DynDNS.o ${OBJECTDIR}/_ext/1302463167/FileSystem.o ${OBJECTDIR}/_ext/1302463167/FTP.o ${OBJECTDIR}/_ext/1302463167/Hashes.o ${OBJECTDIR}/_ext/1302463167/Helpers.o ${OBJECTDIR}/_ext/1302463167/HTTP2.o ${OBJECTDIR}/_ext/1302463167/ICMP.o ${OBJECTDIR}/_ext/1302463167/IP.o ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o ${OBJECTDIR}/_ext/1302463167/MPFS2.o ${OBJECTDIR}/_ext/1302463167/NBNS.o ${OBJECTDIR}/_ext/1302463167/Random.o ${OBJECTDIR}/_ext/1302463167/Reboot.o ${OBJECTDIR}/_ext/1302463167/RSA.o ${OBJECTDIR}/_ext/1302463167/SMTP.o ${OBJECTDIR}/_ext/1302463167/SNMP.o ${OBJECTDIR}/_ext/1302463167/SNMPv3.o ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o ${OBJECTDIR}/_ext/1302463167/SNTP.o ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o ${OBJECTDIR}/_ext/1302463167/SPIFlash.o ${OBJECTDIR}/_ext/1302463167/SPIRAM.o ${OBJECTDIR}/_ext/1302463167/SSL.o ${OBJECTDIR}/_ext/1302463167/StackTsk.o ${OBJECTDIR}/_ext/1302463167/TCP.o ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o ${OBJECTDIR}/_ext/1302463167/Telnet.o ${OBJECTDIR}/_ext/1302463167/TFTPc.o ${OBJECTDIR}/_ext/1302463167/Tick.o ${OBJECTDIR}/_ext/1302463167/UART.o ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o ${OBJECTDIR}/_ext/1302463167/UDP.o ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o ${OBJECTDIR}/src/wind_rain_cnt.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Wifi_Wunder_Station.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ128GA010
MP_LINKER_FILE_OPTION=,-Tp24FJ128GA010.gld
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
${OBJECTDIR}/src/CustomHTTPApp.o: src/CustomHTTPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/CustomHTTPApp.o.d 
	@${RM} ${OBJECTDIR}/src/CustomHTTPApp.o.ok ${OBJECTDIR}/src/CustomHTTPApp.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/CustomHTTPApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/CustomHTTPApp.o.d" -o ${OBJECTDIR}/src/CustomHTTPApp.o src/CustomHTTPApp.c    
	
${OBJECTDIR}/src/UARTConfig.o: src/UARTConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/UARTConfig.o.d 
	@${RM} ${OBJECTDIR}/src/UARTConfig.o.ok ${OBJECTDIR}/src/UARTConfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/UARTConfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/UARTConfig.o.d" -o ${OBJECTDIR}/src/UARTConfig.o src/UARTConfig.c    
	
${OBJECTDIR}/src/NistTimeClient.o: src/NistTimeClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/NistTimeClient.o.d 
	@${RM} ${OBJECTDIR}/src/NistTimeClient.o.ok ${OBJECTDIR}/src/NistTimeClient.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/NistTimeClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/NistTimeClient.o.d" -o ${OBJECTDIR}/src/NistTimeClient.o src/NistTimeClient.c    
	
${OBJECTDIR}/src/RTCC.o: src/RTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/RTCC.o.d 
	@${RM} ${OBJECTDIR}/src/RTCC.o.ok ${OBJECTDIR}/src/RTCC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/RTCC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/RTCC.o.d" -o ${OBJECTDIR}/src/RTCC.o src/RTCC.c    
	
${OBJECTDIR}/src/Main.o: src/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Main.o.d 
	@${RM} ${OBJECTDIR}/src/Main.o.ok ${OBJECTDIR}/src/Main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/Main.o.d" -o ${OBJECTDIR}/src/Main.o src/Main.c    
	
${OBJECTDIR}/src/WunderHttpClient.o: src/WunderHttpClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/WunderHttpClient.o.d 
	@${RM} ${OBJECTDIR}/src/WunderHttpClient.o.ok ${OBJECTDIR}/src/WunderHttpClient.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/WunderHttpClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/WunderHttpClient.o.d" -o ${OBJECTDIR}/src/WunderHttpClient.o src/WunderHttpClient.c    
	
${OBJECTDIR}/src/APP_cfg.o: src/APP_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/APP_cfg.o.d 
	@${RM} ${OBJECTDIR}/src/APP_cfg.o.ok ${OBJECTDIR}/src/APP_cfg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/APP_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/APP_cfg.o.d" -o ${OBJECTDIR}/src/APP_cfg.o src/APP_cfg.c    
	
${OBJECTDIR}/src/WX_perm_data.o: src/WX_perm_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/WX_perm_data.o.d 
	@${RM} ${OBJECTDIR}/src/WX_perm_data.o.ok ${OBJECTDIR}/src/WX_perm_data.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/WX_perm_data.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/WX_perm_data.o.d" -o ${OBJECTDIR}/src/WX_perm_data.o src/WX_perm_data.c    
	
${OBJECTDIR}/src/I2C1.o: src/I2C1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/I2C1.o.d 
	@${RM} ${OBJECTDIR}/src/I2C1.o.ok ${OBJECTDIR}/src/I2C1.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/I2C1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/I2C1.o.d" -o ${OBJECTDIR}/src/I2C1.o src/I2C1.c    
	
${OBJECTDIR}/src/HP03_Baro.o: src/HP03_Baro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/HP03_Baro.o.d 
	@${RM} ${OBJECTDIR}/src/HP03_Baro.o.ok ${OBJECTDIR}/src/HP03_Baro.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/HP03_Baro.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/HP03_Baro.o.d" -o ${OBJECTDIR}/src/HP03_Baro.o src/HP03_Baro.c    
	
${OBJECTDIR}/src/WF_Config.o: src/WF_Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/WF_Config.o.d 
	@${RM} ${OBJECTDIR}/src/WF_Config.o.ok ${OBJECTDIR}/src/WF_Config.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/WF_Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/WF_Config.o.d" -o ${OBJECTDIR}/src/WF_Config.o src/WF_Config.c    
	
${OBJECTDIR}/src/HIH_6130.o: src/HIH_6130.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/HIH_6130.o.d 
	@${RM} ${OBJECTDIR}/src/HIH_6130.o.ok ${OBJECTDIR}/src/HIH_6130.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/HIH_6130.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/HIH_6130.o.d" -o ${OBJECTDIR}/src/HIH_6130.o src/HIH_6130.c    
	
${OBJECTDIR}/src/Mail_Alarm.o: src/Mail_Alarm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Mail_Alarm.o.d 
	@${RM} ${OBJECTDIR}/src/Mail_Alarm.o.ok ${OBJECTDIR}/src/Mail_Alarm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/Mail_Alarm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/Mail_Alarm.o.d" -o ${OBJECTDIR}/src/Mail_Alarm.o src/Mail_Alarm.c    
	
${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConnectionAlgorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.ok ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConnectionAlgorithm.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConnectionManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.ok ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConnectionManager.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConnectionProfile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.ok ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConnectionProfile.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsole.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsole.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsole.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsole.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsole.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsole.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsole.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsole.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsole.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleIfconfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleIfconfig.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleIwconfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleIwconfig.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleIwpriv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleIwpriv.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleMsgHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleMsgHandler.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleMsgs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleMsgs.c"    
	
${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFDataTxRx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.ok ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFDataTxRx.c"    
	
${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFDebugStrings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.ok ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFDebugStrings.c"    
	
${OBJECTDIR}/_ext/1711518555/WFDriverCom.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFDriverCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.ok ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFDriverCom.c"    
	
${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFDriverRaw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.ok ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFDriverRaw.c"    
	
${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFEasyConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.ok ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFEasyConfig.c"    
	
${OBJECTDIR}/_ext/1711518555/WFEventHandler.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFEventHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.ok ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFEventHandler.c"    
	
${OBJECTDIR}/_ext/1711518555/WFInit.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFInit.o.ok ${OBJECTDIR}/_ext/1711518555/WFInit.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFInit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFInit.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFInit.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFInit.c"    
	
${OBJECTDIR}/_ext/1711518555/WFMac.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMac.o.ok ${OBJECTDIR}/_ext/1711518555/WFMac.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFMac.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFMac.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFMac.c"    
	
${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFMgmtMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.ok ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFMgmtMsg.c"    
	
${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFMgmtMsgTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.ok ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFMgmtMsgTest.c"    
	
${OBJECTDIR}/_ext/1711518555/WFParamMsg.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFParamMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.ok ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFParamMsg.c"    
	
${OBJECTDIR}/_ext/1711518555/WFPowerSave.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFPowerSave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.ok ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFPowerSave.c"    
	
${OBJECTDIR}/_ext/1711518555/WFScan.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFScan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFScan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFScan.o.ok ${OBJECTDIR}/_ext/1711518555/WFScan.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFScan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFScan.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFScan.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFScan.c"    
	
${OBJECTDIR}/_ext/1711518555/WFTxPower.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFTxPower.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFTxPower.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFTxPower.o.ok ${OBJECTDIR}/_ext/1711518555/WFTxPower.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFTxPower.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFTxPower.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFTxPower.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFTxPower.c"    
	
${OBJECTDIR}/_ext/1711518555/WF_Eint.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WF_Eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WF_Eint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WF_Eint.o.ok ${OBJECTDIR}/_ext/1711518555/WF_Eint.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WF_Eint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WF_Eint.o.d" -o ${OBJECTDIR}/_ext/1711518555/WF_Eint.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WF_Eint.c"    
	
${OBJECTDIR}/_ext/1711518555/WF_Spi.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WF_Spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WF_Spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WF_Spi.o.ok ${OBJECTDIR}/_ext/1711518555/WF_Spi.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WF_Spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WF_Spi.o.d" -o ${OBJECTDIR}/_ext/1711518555/WF_Spi.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WF_Spi.c"    
	
${OBJECTDIR}/_ext/1302463167/Announce.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Announce.o.ok ${OBJECTDIR}/_ext/1302463167/Announce.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Announce.o.d" -o ${OBJECTDIR}/_ext/1302463167/Announce.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Announce.c"    
	
${OBJECTDIR}/_ext/1302463167/ARCFOUR.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ARCFOUR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.ok ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.d" -o ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ARCFOUR.c"    
	
${OBJECTDIR}/_ext/1302463167/ARP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ARP.o.ok ${OBJECTDIR}/_ext/1302463167/ARP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ARP.o.d" -o ${OBJECTDIR}/_ext/1302463167/ARP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ARP.c"    
	
${OBJECTDIR}/_ext/1302463167/AutoIP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/AutoIP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/AutoIP.o.ok ${OBJECTDIR}/_ext/1302463167/AutoIP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/AutoIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/AutoIP.o.d" -o ${OBJECTDIR}/_ext/1302463167/AutoIP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/AutoIP.c"    
	
${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.ok ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.d" -o ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/BerkeleyAPI.c"    
	
${OBJECTDIR}/_ext/1302463167/BigInt.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/BigInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/BigInt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/BigInt.o.ok ${OBJECTDIR}/_ext/1302463167/BigInt.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/BigInt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/BigInt.o.d" -o ${OBJECTDIR}/_ext/1302463167/BigInt.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/BigInt.c"    
	
${OBJECTDIR}/_ext/1302463167/Delay.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Delay.o.ok ${OBJECTDIR}/_ext/1302463167/Delay.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Delay.o.d" -o ${OBJECTDIR}/_ext/1302463167/Delay.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Delay.c"    
	
${OBJECTDIR}/_ext/1302463167/DHCP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DHCP.o.ok ${OBJECTDIR}/_ext/1302463167/DHCP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DHCP.o.d" -o ${OBJECTDIR}/_ext/1302463167/DHCP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DHCP.c"    
	
${OBJECTDIR}/_ext/1302463167/DHCPs.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DHCPs.o.ok ${OBJECTDIR}/_ext/1302463167/DHCPs.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DHCPs.o.d" -o ${OBJECTDIR}/_ext/1302463167/DHCPs.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DHCPs.c"    
	
${OBJECTDIR}/_ext/1302463167/DNS.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DNS.o.ok ${OBJECTDIR}/_ext/1302463167/DNS.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DNS.o.d" -o ${OBJECTDIR}/_ext/1302463167/DNS.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DNS.c"    
	
${OBJECTDIR}/_ext/1302463167/DNSs.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DNSs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DNSs.o.ok ${OBJECTDIR}/_ext/1302463167/DNSs.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DNSs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DNSs.o.d" -o ${OBJECTDIR}/_ext/1302463167/DNSs.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DNSs.c"    
	
${OBJECTDIR}/_ext/1302463167/DynDNS.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DynDNS.o.ok ${OBJECTDIR}/_ext/1302463167/DynDNS.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DynDNS.o.d" -o ${OBJECTDIR}/_ext/1302463167/DynDNS.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DynDNS.c"    
	
${OBJECTDIR}/_ext/1302463167/FileSystem.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/FileSystem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/FileSystem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/FileSystem.o.ok ${OBJECTDIR}/_ext/1302463167/FileSystem.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/FileSystem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/FileSystem.o.d" -o ${OBJECTDIR}/_ext/1302463167/FileSystem.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/FileSystem.c"    
	
${OBJECTDIR}/_ext/1302463167/FTP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/FTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/FTP.o.ok ${OBJECTDIR}/_ext/1302463167/FTP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/FTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/FTP.o.d" -o ${OBJECTDIR}/_ext/1302463167/FTP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/FTP.c"    
	
${OBJECTDIR}/_ext/1302463167/Hashes.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Hashes.o.ok ${OBJECTDIR}/_ext/1302463167/Hashes.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Hashes.o.d" -o ${OBJECTDIR}/_ext/1302463167/Hashes.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Hashes.c"    
	
${OBJECTDIR}/_ext/1302463167/Helpers.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Helpers.o.ok ${OBJECTDIR}/_ext/1302463167/Helpers.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Helpers.o.d" -o ${OBJECTDIR}/_ext/1302463167/Helpers.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Helpers.c"    
	
${OBJECTDIR}/_ext/1302463167/HTTP2.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/HTTP2.o.ok ${OBJECTDIR}/_ext/1302463167/HTTP2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/HTTP2.o.d" -o ${OBJECTDIR}/_ext/1302463167/HTTP2.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/HTTP2.c"    
	
${OBJECTDIR}/_ext/1302463167/ICMP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ICMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ICMP.o.ok ${OBJECTDIR}/_ext/1302463167/ICMP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ICMP.o.d" -o ${OBJECTDIR}/_ext/1302463167/ICMP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ICMP.c"    
	
${OBJECTDIR}/_ext/1302463167/IP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/IP.o.ok ${OBJECTDIR}/_ext/1302463167/IP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/IP.o.d" -o ${OBJECTDIR}/_ext/1302463167/IP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/IP.c"    
	
${OBJECTDIR}/_ext/1302463167/LCDBlocking.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/LCDBlocking.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.ok ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.d" -o ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/LCDBlocking.c"    
	
${OBJECTDIR}/_ext/1302463167/MPFS2.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/MPFS2.o.ok ${OBJECTDIR}/_ext/1302463167/MPFS2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/MPFS2.o.d" -o ${OBJECTDIR}/_ext/1302463167/MPFS2.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/MPFS2.c"    
	
${OBJECTDIR}/_ext/1302463167/NBNS.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/NBNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/NBNS.o.ok ${OBJECTDIR}/_ext/1302463167/NBNS.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/NBNS.o.d" -o ${OBJECTDIR}/_ext/1302463167/NBNS.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/NBNS.c"    
	
${OBJECTDIR}/_ext/1302463167/Random.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Random.o.ok ${OBJECTDIR}/_ext/1302463167/Random.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Random.o.d" -o ${OBJECTDIR}/_ext/1302463167/Random.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Random.c"    
	
${OBJECTDIR}/_ext/1302463167/Reboot.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Reboot.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Reboot.o.ok ${OBJECTDIR}/_ext/1302463167/Reboot.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Reboot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Reboot.o.d" -o ${OBJECTDIR}/_ext/1302463167/Reboot.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Reboot.c"    
	
${OBJECTDIR}/_ext/1302463167/RSA.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/RSA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/RSA.o.ok ${OBJECTDIR}/_ext/1302463167/RSA.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/RSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/RSA.o.d" -o ${OBJECTDIR}/_ext/1302463167/RSA.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/RSA.c"    
	
${OBJECTDIR}/_ext/1302463167/SMTP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SMTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SMTP.o.ok ${OBJECTDIR}/_ext/1302463167/SMTP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SMTP.o.d" -o ${OBJECTDIR}/_ext/1302463167/SMTP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SMTP.c"    
	
${OBJECTDIR}/_ext/1302463167/SNMP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMP.o.ok ${OBJECTDIR}/_ext/1302463167/SNMP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SNMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SNMP.o.d" -o ${OBJECTDIR}/_ext/1302463167/SNMP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SNMP.c"    
	
${OBJECTDIR}/_ext/1302463167/SNMPv3.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SNMPv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMPv3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMPv3.o.ok ${OBJECTDIR}/_ext/1302463167/SNMPv3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SNMPv3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SNMPv3.o.d" -o ${OBJECTDIR}/_ext/1302463167/SNMPv3.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SNMPv3.c"    
	
${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SNMPv3USM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.ok ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.d" -o ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SNMPv3USM.c"    
	
${OBJECTDIR}/_ext/1302463167/SNTP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNTP.o.ok ${OBJECTDIR}/_ext/1302463167/SNTP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SNTP.o.d" -o ${OBJECTDIR}/_ext/1302463167/SNTP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SNTP.c"    
	
${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.ok ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.d" -o ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SPIEEPROM.c"    
	
${OBJECTDIR}/_ext/1302463167/SPIFlash.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIFlash.o.ok ${OBJECTDIR}/_ext/1302463167/SPIFlash.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SPIFlash.o.d" -o ${OBJECTDIR}/_ext/1302463167/SPIFlash.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SPIFlash.c"    
	
${OBJECTDIR}/_ext/1302463167/SPIRAM.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SPIRAM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIRAM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIRAM.o.ok ${OBJECTDIR}/_ext/1302463167/SPIRAM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SPIRAM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SPIRAM.o.d" -o ${OBJECTDIR}/_ext/1302463167/SPIRAM.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SPIRAM.c"    
	
${OBJECTDIR}/_ext/1302463167/SSL.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SSL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SSL.o.ok ${OBJECTDIR}/_ext/1302463167/SSL.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SSL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SSL.o.d" -o ${OBJECTDIR}/_ext/1302463167/SSL.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SSL.c"    
	
${OBJECTDIR}/_ext/1302463167/StackTsk.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/StackTsk.o.ok ${OBJECTDIR}/_ext/1302463167/StackTsk.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/StackTsk.o.d" -o ${OBJECTDIR}/_ext/1302463167/StackTsk.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/StackTsk.c"    
	
${OBJECTDIR}/_ext/1302463167/TCP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TCP.o.ok ${OBJECTDIR}/_ext/1302463167/TCP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/TCP.o.d" -o ${OBJECTDIR}/_ext/1302463167/TCP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/TCP.c"    
	
${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/TCPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.ok ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.d" -o ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/TCPPerformanceTest.c"    
	
${OBJECTDIR}/_ext/1302463167/Telnet.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Telnet.o.ok ${OBJECTDIR}/_ext/1302463167/Telnet.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Telnet.o.d" -o ${OBJECTDIR}/_ext/1302463167/Telnet.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Telnet.c"    
	
${OBJECTDIR}/_ext/1302463167/TFTPc.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TFTPc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TFTPc.o.ok ${OBJECTDIR}/_ext/1302463167/TFTPc.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/TFTPc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/TFTPc.o.d" -o ${OBJECTDIR}/_ext/1302463167/TFTPc.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/TFTPc.c"    
	
${OBJECTDIR}/_ext/1302463167/Tick.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Tick.o.ok ${OBJECTDIR}/_ext/1302463167/Tick.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Tick.o.d" -o ${OBJECTDIR}/_ext/1302463167/Tick.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Tick.c"    
	
${OBJECTDIR}/_ext/1302463167/UART.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UART.o.ok ${OBJECTDIR}/_ext/1302463167/UART.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/UART.o.d" -o ${OBJECTDIR}/_ext/1302463167/UART.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/UART.c"    
	
${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/UART2TCPBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.ok ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.d" -o ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/UART2TCPBridge.c"    
	
${OBJECTDIR}/_ext/1302463167/UDP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UDP.o.ok ${OBJECTDIR}/_ext/1302463167/UDP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/UDP.o.d" -o ${OBJECTDIR}/_ext/1302463167/UDP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/UDP.c"    
	
${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/UDPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.ok ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.d" -o ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/UDPPerformanceTest.c"    
	
${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ZeroconfHelper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.ok ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.d" -o ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ZeroconfHelper.c"    
	
${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ZeroconfLinkLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.ok ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.d" -o ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ZeroconfLinkLocal.c"    
	
${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ZeroconfMulticastDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.ok ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.d" -o ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ZeroconfMulticastDNS.c"    
	
${OBJECTDIR}/src/wind_rain_cnt.o: src/wind_rain_cnt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/wind_rain_cnt.o.d 
	@${RM} ${OBJECTDIR}/src/wind_rain_cnt.o.ok ${OBJECTDIR}/src/wind_rain_cnt.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/wind_rain_cnt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/wind_rain_cnt.o.d" -o ${OBJECTDIR}/src/wind_rain_cnt.o src/wind_rain_cnt.c    
	
else
${OBJECTDIR}/src/CustomHTTPApp.o: src/CustomHTTPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/CustomHTTPApp.o.d 
	@${RM} ${OBJECTDIR}/src/CustomHTTPApp.o.ok ${OBJECTDIR}/src/CustomHTTPApp.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/CustomHTTPApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/CustomHTTPApp.o.d" -o ${OBJECTDIR}/src/CustomHTTPApp.o src/CustomHTTPApp.c    
	
${OBJECTDIR}/src/UARTConfig.o: src/UARTConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/UARTConfig.o.d 
	@${RM} ${OBJECTDIR}/src/UARTConfig.o.ok ${OBJECTDIR}/src/UARTConfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/UARTConfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/UARTConfig.o.d" -o ${OBJECTDIR}/src/UARTConfig.o src/UARTConfig.c    
	
${OBJECTDIR}/src/NistTimeClient.o: src/NistTimeClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/NistTimeClient.o.d 
	@${RM} ${OBJECTDIR}/src/NistTimeClient.o.ok ${OBJECTDIR}/src/NistTimeClient.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/NistTimeClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/NistTimeClient.o.d" -o ${OBJECTDIR}/src/NistTimeClient.o src/NistTimeClient.c    
	
${OBJECTDIR}/src/RTCC.o: src/RTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/RTCC.o.d 
	@${RM} ${OBJECTDIR}/src/RTCC.o.ok ${OBJECTDIR}/src/RTCC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/RTCC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/RTCC.o.d" -o ${OBJECTDIR}/src/RTCC.o src/RTCC.c    
	
${OBJECTDIR}/src/Main.o: src/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Main.o.d 
	@${RM} ${OBJECTDIR}/src/Main.o.ok ${OBJECTDIR}/src/Main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/Main.o.d" -o ${OBJECTDIR}/src/Main.o src/Main.c    
	
${OBJECTDIR}/src/WunderHttpClient.o: src/WunderHttpClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/WunderHttpClient.o.d 
	@${RM} ${OBJECTDIR}/src/WunderHttpClient.o.ok ${OBJECTDIR}/src/WunderHttpClient.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/WunderHttpClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/WunderHttpClient.o.d" -o ${OBJECTDIR}/src/WunderHttpClient.o src/WunderHttpClient.c    
	
${OBJECTDIR}/src/APP_cfg.o: src/APP_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/APP_cfg.o.d 
	@${RM} ${OBJECTDIR}/src/APP_cfg.o.ok ${OBJECTDIR}/src/APP_cfg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/APP_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/APP_cfg.o.d" -o ${OBJECTDIR}/src/APP_cfg.o src/APP_cfg.c    
	
${OBJECTDIR}/src/WX_perm_data.o: src/WX_perm_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/WX_perm_data.o.d 
	@${RM} ${OBJECTDIR}/src/WX_perm_data.o.ok ${OBJECTDIR}/src/WX_perm_data.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/WX_perm_data.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/WX_perm_data.o.d" -o ${OBJECTDIR}/src/WX_perm_data.o src/WX_perm_data.c    
	
${OBJECTDIR}/src/I2C1.o: src/I2C1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/I2C1.o.d 
	@${RM} ${OBJECTDIR}/src/I2C1.o.ok ${OBJECTDIR}/src/I2C1.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/I2C1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/I2C1.o.d" -o ${OBJECTDIR}/src/I2C1.o src/I2C1.c    
	
${OBJECTDIR}/src/HP03_Baro.o: src/HP03_Baro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/HP03_Baro.o.d 
	@${RM} ${OBJECTDIR}/src/HP03_Baro.o.ok ${OBJECTDIR}/src/HP03_Baro.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/HP03_Baro.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/HP03_Baro.o.d" -o ${OBJECTDIR}/src/HP03_Baro.o src/HP03_Baro.c    
	
${OBJECTDIR}/src/WF_Config.o: src/WF_Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/WF_Config.o.d 
	@${RM} ${OBJECTDIR}/src/WF_Config.o.ok ${OBJECTDIR}/src/WF_Config.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/WF_Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/WF_Config.o.d" -o ${OBJECTDIR}/src/WF_Config.o src/WF_Config.c    
	
${OBJECTDIR}/src/HIH_6130.o: src/HIH_6130.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/HIH_6130.o.d 
	@${RM} ${OBJECTDIR}/src/HIH_6130.o.ok ${OBJECTDIR}/src/HIH_6130.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/HIH_6130.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/HIH_6130.o.d" -o ${OBJECTDIR}/src/HIH_6130.o src/HIH_6130.c    
	
${OBJECTDIR}/src/Mail_Alarm.o: src/Mail_Alarm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Mail_Alarm.o.d 
	@${RM} ${OBJECTDIR}/src/Mail_Alarm.o.ok ${OBJECTDIR}/src/Mail_Alarm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/Mail_Alarm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/Mail_Alarm.o.d" -o ${OBJECTDIR}/src/Mail_Alarm.o src/Mail_Alarm.c    
	
${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConnectionAlgorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.ok ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConnectionAlgorithm.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConnectionAlgorithm.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConnectionManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.ok ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConnectionManager.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConnectionManager.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConnectionProfile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.ok ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConnectionProfile.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConnectionProfile.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsole.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsole.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsole.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsole.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsole.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsole.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsole.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsole.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsole.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleIfconfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleIfconfig.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleIfconfig.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleIwconfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleIwconfig.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleIwconfig.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleIwpriv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleIwpriv.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleIwpriv.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleMsgHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgHandler.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleMsgHandler.c"    
	
${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFConsoleMsgs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.ok ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFConsoleMsgs.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFConsoleMsgs.c"    
	
${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFDataTxRx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.ok ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFDataTxRx.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFDataTxRx.c"    
	
${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFDebugStrings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.ok ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFDebugStrings.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFDebugStrings.c"    
	
${OBJECTDIR}/_ext/1711518555/WFDriverCom.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFDriverCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.ok ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFDriverCom.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFDriverCom.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFDriverCom.c"    
	
${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFDriverRaw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.ok ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFDriverRaw.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFDriverRaw.c"    
	
${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFEasyConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.ok ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFEasyConfig.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFEasyConfig.c"    
	
${OBJECTDIR}/_ext/1711518555/WFEventHandler.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFEventHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.ok ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFEventHandler.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFEventHandler.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFEventHandler.c"    
	
${OBJECTDIR}/_ext/1711518555/WFInit.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFInit.o.ok ${OBJECTDIR}/_ext/1711518555/WFInit.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFInit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFInit.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFInit.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFInit.c"    
	
${OBJECTDIR}/_ext/1711518555/WFMac.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMac.o.ok ${OBJECTDIR}/_ext/1711518555/WFMac.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFMac.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFMac.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFMac.c"    
	
${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFMgmtMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.ok ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFMgmtMsg.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFMgmtMsg.c"    
	
${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFMgmtMsgTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.ok ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFMgmtMsgTest.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFMgmtMsgTest.c"    
	
${OBJECTDIR}/_ext/1711518555/WFParamMsg.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFParamMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.ok ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFParamMsg.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFParamMsg.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFParamMsg.c"    
	
${OBJECTDIR}/_ext/1711518555/WFPowerSave.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFPowerSave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.ok ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFPowerSave.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFPowerSave.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFPowerSave.c"    
	
${OBJECTDIR}/_ext/1711518555/WFScan.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFScan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFScan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFScan.o.ok ${OBJECTDIR}/_ext/1711518555/WFScan.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFScan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFScan.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFScan.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFScan.c"    
	
${OBJECTDIR}/_ext/1711518555/WFTxPower.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WFTxPower.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFTxPower.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WFTxPower.o.ok ${OBJECTDIR}/_ext/1711518555/WFTxPower.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WFTxPower.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WFTxPower.o.d" -o ${OBJECTDIR}/_ext/1711518555/WFTxPower.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WFTxPower.c"    
	
${OBJECTDIR}/_ext/1711518555/WF_Eint.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WF_Eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WF_Eint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WF_Eint.o.ok ${OBJECTDIR}/_ext/1711518555/WF_Eint.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WF_Eint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WF_Eint.o.d" -o ${OBJECTDIR}/_ext/1711518555/WF_Eint.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WF_Eint.c"    
	
${OBJECTDIR}/_ext/1711518555/WF_Spi.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/WiFi/WF_Spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1711518555 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WF_Spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1711518555/WF_Spi.o.ok ${OBJECTDIR}/_ext/1711518555/WF_Spi.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1711518555/WF_Spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1711518555/WF_Spi.o.d" -o ${OBJECTDIR}/_ext/1711518555/WF_Spi.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/WiFi/WF_Spi.c"    
	
${OBJECTDIR}/_ext/1302463167/Announce.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Announce.o.ok ${OBJECTDIR}/_ext/1302463167/Announce.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Announce.o.d" -o ${OBJECTDIR}/_ext/1302463167/Announce.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Announce.c"    
	
${OBJECTDIR}/_ext/1302463167/ARCFOUR.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ARCFOUR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.ok ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ARCFOUR.o.d" -o ${OBJECTDIR}/_ext/1302463167/ARCFOUR.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ARCFOUR.c"    
	
${OBJECTDIR}/_ext/1302463167/ARP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ARP.o.ok ${OBJECTDIR}/_ext/1302463167/ARP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ARP.o.d" -o ${OBJECTDIR}/_ext/1302463167/ARP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ARP.c"    
	
${OBJECTDIR}/_ext/1302463167/AutoIP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/AutoIP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/AutoIP.o.ok ${OBJECTDIR}/_ext/1302463167/AutoIP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/AutoIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/AutoIP.o.d" -o ${OBJECTDIR}/_ext/1302463167/AutoIP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/AutoIP.c"    
	
${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.ok ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o.d" -o ${OBJECTDIR}/_ext/1302463167/BerkeleyAPI.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/BerkeleyAPI.c"    
	
${OBJECTDIR}/_ext/1302463167/BigInt.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/BigInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/BigInt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/BigInt.o.ok ${OBJECTDIR}/_ext/1302463167/BigInt.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/BigInt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/BigInt.o.d" -o ${OBJECTDIR}/_ext/1302463167/BigInt.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/BigInt.c"    
	
${OBJECTDIR}/_ext/1302463167/Delay.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Delay.o.ok ${OBJECTDIR}/_ext/1302463167/Delay.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Delay.o.d" -o ${OBJECTDIR}/_ext/1302463167/Delay.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Delay.c"    
	
${OBJECTDIR}/_ext/1302463167/DHCP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DHCP.o.ok ${OBJECTDIR}/_ext/1302463167/DHCP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DHCP.o.d" -o ${OBJECTDIR}/_ext/1302463167/DHCP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DHCP.c"    
	
${OBJECTDIR}/_ext/1302463167/DHCPs.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DHCPs.o.ok ${OBJECTDIR}/_ext/1302463167/DHCPs.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DHCPs.o.d" -o ${OBJECTDIR}/_ext/1302463167/DHCPs.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DHCPs.c"    
	
${OBJECTDIR}/_ext/1302463167/DNS.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DNS.o.ok ${OBJECTDIR}/_ext/1302463167/DNS.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DNS.o.d" -o ${OBJECTDIR}/_ext/1302463167/DNS.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DNS.c"    
	
${OBJECTDIR}/_ext/1302463167/DNSs.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DNSs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DNSs.o.ok ${OBJECTDIR}/_ext/1302463167/DNSs.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DNSs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DNSs.o.d" -o ${OBJECTDIR}/_ext/1302463167/DNSs.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DNSs.c"    
	
${OBJECTDIR}/_ext/1302463167/DynDNS.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/DynDNS.o.ok ${OBJECTDIR}/_ext/1302463167/DynDNS.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/DynDNS.o.d" -o ${OBJECTDIR}/_ext/1302463167/DynDNS.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/DynDNS.c"    
	
${OBJECTDIR}/_ext/1302463167/FileSystem.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/FileSystem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/FileSystem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/FileSystem.o.ok ${OBJECTDIR}/_ext/1302463167/FileSystem.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/FileSystem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/FileSystem.o.d" -o ${OBJECTDIR}/_ext/1302463167/FileSystem.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/FileSystem.c"    
	
${OBJECTDIR}/_ext/1302463167/FTP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/FTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/FTP.o.ok ${OBJECTDIR}/_ext/1302463167/FTP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/FTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/FTP.o.d" -o ${OBJECTDIR}/_ext/1302463167/FTP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/FTP.c"    
	
${OBJECTDIR}/_ext/1302463167/Hashes.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Hashes.o.ok ${OBJECTDIR}/_ext/1302463167/Hashes.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Hashes.o.d" -o ${OBJECTDIR}/_ext/1302463167/Hashes.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Hashes.c"    
	
${OBJECTDIR}/_ext/1302463167/Helpers.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Helpers.o.ok ${OBJECTDIR}/_ext/1302463167/Helpers.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Helpers.o.d" -o ${OBJECTDIR}/_ext/1302463167/Helpers.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Helpers.c"    
	
${OBJECTDIR}/_ext/1302463167/HTTP2.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/HTTP2.o.ok ${OBJECTDIR}/_ext/1302463167/HTTP2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/HTTP2.o.d" -o ${OBJECTDIR}/_ext/1302463167/HTTP2.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/HTTP2.c"    
	
${OBJECTDIR}/_ext/1302463167/ICMP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ICMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ICMP.o.ok ${OBJECTDIR}/_ext/1302463167/ICMP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ICMP.o.d" -o ${OBJECTDIR}/_ext/1302463167/ICMP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ICMP.c"    
	
${OBJECTDIR}/_ext/1302463167/IP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/IP.o.ok ${OBJECTDIR}/_ext/1302463167/IP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/IP.o.d" -o ${OBJECTDIR}/_ext/1302463167/IP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/IP.c"    
	
${OBJECTDIR}/_ext/1302463167/LCDBlocking.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/LCDBlocking.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.ok ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/LCDBlocking.o.d" -o ${OBJECTDIR}/_ext/1302463167/LCDBlocking.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/LCDBlocking.c"    
	
${OBJECTDIR}/_ext/1302463167/MPFS2.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/MPFS2.o.ok ${OBJECTDIR}/_ext/1302463167/MPFS2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/MPFS2.o.d" -o ${OBJECTDIR}/_ext/1302463167/MPFS2.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/MPFS2.c"    
	
${OBJECTDIR}/_ext/1302463167/NBNS.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/NBNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/NBNS.o.ok ${OBJECTDIR}/_ext/1302463167/NBNS.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/NBNS.o.d" -o ${OBJECTDIR}/_ext/1302463167/NBNS.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/NBNS.c"    
	
${OBJECTDIR}/_ext/1302463167/Random.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Random.o.ok ${OBJECTDIR}/_ext/1302463167/Random.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Random.o.d" -o ${OBJECTDIR}/_ext/1302463167/Random.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Random.c"    
	
${OBJECTDIR}/_ext/1302463167/Reboot.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Reboot.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Reboot.o.ok ${OBJECTDIR}/_ext/1302463167/Reboot.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Reboot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Reboot.o.d" -o ${OBJECTDIR}/_ext/1302463167/Reboot.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Reboot.c"    
	
${OBJECTDIR}/_ext/1302463167/RSA.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/RSA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/RSA.o.ok ${OBJECTDIR}/_ext/1302463167/RSA.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/RSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/RSA.o.d" -o ${OBJECTDIR}/_ext/1302463167/RSA.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/RSA.c"    
	
${OBJECTDIR}/_ext/1302463167/SMTP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SMTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SMTP.o.ok ${OBJECTDIR}/_ext/1302463167/SMTP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SMTP.o.d" -o ${OBJECTDIR}/_ext/1302463167/SMTP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SMTP.c"    
	
${OBJECTDIR}/_ext/1302463167/SNMP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMP.o.ok ${OBJECTDIR}/_ext/1302463167/SNMP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SNMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SNMP.o.d" -o ${OBJECTDIR}/_ext/1302463167/SNMP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SNMP.c"    
	
${OBJECTDIR}/_ext/1302463167/SNMPv3.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SNMPv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMPv3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMPv3.o.ok ${OBJECTDIR}/_ext/1302463167/SNMPv3.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SNMPv3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SNMPv3.o.d" -o ${OBJECTDIR}/_ext/1302463167/SNMPv3.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SNMPv3.c"    
	
${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SNMPv3USM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.ok ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o.d" -o ${OBJECTDIR}/_ext/1302463167/SNMPv3USM.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SNMPv3USM.c"    
	
${OBJECTDIR}/_ext/1302463167/SNTP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SNTP.o.ok ${OBJECTDIR}/_ext/1302463167/SNTP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SNTP.o.d" -o ${OBJECTDIR}/_ext/1302463167/SNTP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SNTP.c"    
	
${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.ok ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o.d" -o ${OBJECTDIR}/_ext/1302463167/SPIEEPROM.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SPIEEPROM.c"    
	
${OBJECTDIR}/_ext/1302463167/SPIFlash.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIFlash.o.ok ${OBJECTDIR}/_ext/1302463167/SPIFlash.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SPIFlash.o.d" -o ${OBJECTDIR}/_ext/1302463167/SPIFlash.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SPIFlash.c"    
	
${OBJECTDIR}/_ext/1302463167/SPIRAM.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SPIRAM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIRAM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SPIRAM.o.ok ${OBJECTDIR}/_ext/1302463167/SPIRAM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SPIRAM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SPIRAM.o.d" -o ${OBJECTDIR}/_ext/1302463167/SPIRAM.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SPIRAM.c"    
	
${OBJECTDIR}/_ext/1302463167/SSL.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SSL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/SSL.o.ok ${OBJECTDIR}/_ext/1302463167/SSL.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/SSL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/SSL.o.d" -o ${OBJECTDIR}/_ext/1302463167/SSL.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/SSL.c"    
	
${OBJECTDIR}/_ext/1302463167/StackTsk.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/StackTsk.o.ok ${OBJECTDIR}/_ext/1302463167/StackTsk.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/StackTsk.o.d" -o ${OBJECTDIR}/_ext/1302463167/StackTsk.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/StackTsk.c"    
	
${OBJECTDIR}/_ext/1302463167/TCP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TCP.o.ok ${OBJECTDIR}/_ext/1302463167/TCP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/TCP.o.d" -o ${OBJECTDIR}/_ext/1302463167/TCP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/TCP.c"    
	
${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/TCPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.ok ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o.d" -o ${OBJECTDIR}/_ext/1302463167/TCPPerformanceTest.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/TCPPerformanceTest.c"    
	
${OBJECTDIR}/_ext/1302463167/Telnet.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Telnet.o.ok ${OBJECTDIR}/_ext/1302463167/Telnet.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Telnet.o.d" -o ${OBJECTDIR}/_ext/1302463167/Telnet.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Telnet.c"    
	
${OBJECTDIR}/_ext/1302463167/TFTPc.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TFTPc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/TFTPc.o.ok ${OBJECTDIR}/_ext/1302463167/TFTPc.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/TFTPc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/TFTPc.o.d" -o ${OBJECTDIR}/_ext/1302463167/TFTPc.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/TFTPc.c"    
	
${OBJECTDIR}/_ext/1302463167/Tick.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/Tick.o.ok ${OBJECTDIR}/_ext/1302463167/Tick.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/Tick.o.d" -o ${OBJECTDIR}/_ext/1302463167/Tick.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/Tick.c"    
	
${OBJECTDIR}/_ext/1302463167/UART.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UART.o.ok ${OBJECTDIR}/_ext/1302463167/UART.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/UART.o.d" -o ${OBJECTDIR}/_ext/1302463167/UART.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/UART.c"    
	
${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/UART2TCPBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.ok ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o.d" -o ${OBJECTDIR}/_ext/1302463167/UART2TCPBridge.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/UART2TCPBridge.c"    
	
${OBJECTDIR}/_ext/1302463167/UDP.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UDP.o.ok ${OBJECTDIR}/_ext/1302463167/UDP.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/UDP.o.d" -o ${OBJECTDIR}/_ext/1302463167/UDP.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/UDP.c"    
	
${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/UDPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.ok ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o.d" -o ${OBJECTDIR}/_ext/1302463167/UDPPerformanceTest.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/UDPPerformanceTest.c"    
	
${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ZeroconfHelper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.ok ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o.d" -o ${OBJECTDIR}/_ext/1302463167/ZeroconfHelper.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ZeroconfHelper.c"    
	
${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ZeroconfLinkLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.ok ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o.d" -o ${OBJECTDIR}/_ext/1302463167/ZeroconfLinkLocal.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ZeroconfLinkLocal.c"    
	
${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o: C:/Documents\ and\ Settings/gary/My\ Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP\ Stack/ZeroconfMulticastDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1302463167 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.ok ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o.d" -o ${OBJECTDIR}/_ext/1302463167/ZeroconfMulticastDNS.o "C:/Documents and Settings/gary/My Documents/MPLAB_X_projects/PIC_WIFI_WX_STATION/TCPIP Stack/ZeroconfMulticastDNS.c"    
	
${OBJECTDIR}/src/wind_rain_cnt.o: src/wind_rain_cnt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/wind_rain_cnt.o.d 
	@${RM} ${OBJECTDIR}/src/wind_rain_cnt.o.ok ${OBJECTDIR}/src/wind_rain_cnt.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/wind_rain_cnt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -DCFG_INCLUDE_EX16_MRF24WB -I"../TCPIP Stack/Include" -I"src" -mlarge-code -MMD -MF "${OBJECTDIR}/src/wind_rain_cnt.o.d" -o ${OBJECTDIR}/src/wind_rain_cnt.o src/wind_rain_cnt.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Wifi_Wunder_Station.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/Wifi_Wunder_Station.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/Wifi_Wunder_Station.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Wifi_Wunder_Station.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Wifi_Wunder_Station.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
