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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=drv/debug_uart.c drv/utils.c drv/usb.c drv/usb_audio.c main.c app_config.c app.c usb_descriptors.c tuner_control.c tuner_com.c tuner_audio.c tunnel.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/drv/debug_uart.o ${OBJECTDIR}/drv/utils.o ${OBJECTDIR}/drv/usb.o ${OBJECTDIR}/drv/usb_audio.o ${OBJECTDIR}/main.o ${OBJECTDIR}/app_config.o ${OBJECTDIR}/app.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/tuner_control.o ${OBJECTDIR}/tuner_com.o ${OBJECTDIR}/tuner_audio.o ${OBJECTDIR}/tunnel.o
POSSIBLE_DEPFILES=${OBJECTDIR}/drv/debug_uart.o.d ${OBJECTDIR}/drv/utils.o.d ${OBJECTDIR}/drv/usb.o.d ${OBJECTDIR}/drv/usb_audio.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/app_config.o.d ${OBJECTDIR}/app.o.d ${OBJECTDIR}/usb_descriptors.o.d ${OBJECTDIR}/tuner_control.o.d ${OBJECTDIR}/tuner_com.o.d ${OBJECTDIR}/tuner_audio.o.d ${OBJECTDIR}/tunnel.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/drv/debug_uart.o ${OBJECTDIR}/drv/utils.o ${OBJECTDIR}/drv/usb.o ${OBJECTDIR}/drv/usb_audio.o ${OBJECTDIR}/main.o ${OBJECTDIR}/app_config.o ${OBJECTDIR}/app.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/tuner_control.o ${OBJECTDIR}/tuner_com.o ${OBJECTDIR}/tuner_audio.o ${OBJECTDIR}/tunnel.o

# Source Files
SOURCEFILES=drv/debug_uart.c drv/utils.c drv/usb.c drv/usb_audio.c main.c app_config.c app.c usb_descriptors.c tuner_control.c tuner_com.c tuner_audio.c tunnel.c


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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128B
MP_LINKER_FILE_OPTION=
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
${OBJECTDIR}/drv/debug_uart.o: drv/debug_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/drv" 
	@${RM} ${OBJECTDIR}/drv/debug_uart.o.d 
	@${RM} ${OBJECTDIR}/drv/debug_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/drv/debug_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/drv/debug_uart.o.d" -o ${OBJECTDIR}/drv/debug_uart.o drv/debug_uart.c   
	
${OBJECTDIR}/drv/utils.o: drv/utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/drv" 
	@${RM} ${OBJECTDIR}/drv/utils.o.d 
	@${RM} ${OBJECTDIR}/drv/utils.o 
	@${FIXDEPS} "${OBJECTDIR}/drv/utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/drv/utils.o.d" -o ${OBJECTDIR}/drv/utils.o drv/utils.c   
	
${OBJECTDIR}/drv/usb.o: drv/usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/drv" 
	@${RM} ${OBJECTDIR}/drv/usb.o.d 
	@${RM} ${OBJECTDIR}/drv/usb.o 
	@${FIXDEPS} "${OBJECTDIR}/drv/usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/drv/usb.o.d" -o ${OBJECTDIR}/drv/usb.o drv/usb.c   
	
${OBJECTDIR}/drv/usb_audio.o: drv/usb_audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/drv" 
	@${RM} ${OBJECTDIR}/drv/usb_audio.o.d 
	@${RM} ${OBJECTDIR}/drv/usb_audio.o 
	@${FIXDEPS} "${OBJECTDIR}/drv/usb_audio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/drv/usb_audio.o.d" -o ${OBJECTDIR}/drv/usb_audio.o drv/usb_audio.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
${OBJECTDIR}/app_config.o: app_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_config.o.d 
	@${RM} ${OBJECTDIR}/app_config.o 
	@${FIXDEPS} "${OBJECTDIR}/app_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/app_config.o.d" -o ${OBJECTDIR}/app_config.o app_config.c   
	
${OBJECTDIR}/app.o: app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app.o.d 
	@${RM} ${OBJECTDIR}/app.o 
	@${FIXDEPS} "${OBJECTDIR}/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/app.o.d" -o ${OBJECTDIR}/app.o app.c   
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c   
	
${OBJECTDIR}/tuner_control.o: tuner_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tuner_control.o.d 
	@${RM} ${OBJECTDIR}/tuner_control.o 
	@${FIXDEPS} "${OBJECTDIR}/tuner_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/tuner_control.o.d" -o ${OBJECTDIR}/tuner_control.o tuner_control.c   
	
${OBJECTDIR}/tuner_com.o: tuner_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tuner_com.o.d 
	@${RM} ${OBJECTDIR}/tuner_com.o 
	@${FIXDEPS} "${OBJECTDIR}/tuner_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/tuner_com.o.d" -o ${OBJECTDIR}/tuner_com.o tuner_com.c   
	
${OBJECTDIR}/tuner_audio.o: tuner_audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tuner_audio.o.d 
	@${RM} ${OBJECTDIR}/tuner_audio.o 
	@${FIXDEPS} "${OBJECTDIR}/tuner_audio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/tuner_audio.o.d" -o ${OBJECTDIR}/tuner_audio.o tuner_audio.c   
	
${OBJECTDIR}/tunnel.o: tunnel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tunnel.o.d 
	@${RM} ${OBJECTDIR}/tunnel.o 
	@${FIXDEPS} "${OBJECTDIR}/tunnel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/tunnel.o.d" -o ${OBJECTDIR}/tunnel.o tunnel.c   
	
else
${OBJECTDIR}/drv/debug_uart.o: drv/debug_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/drv" 
	@${RM} ${OBJECTDIR}/drv/debug_uart.o.d 
	@${RM} ${OBJECTDIR}/drv/debug_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/drv/debug_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/drv/debug_uart.o.d" -o ${OBJECTDIR}/drv/debug_uart.o drv/debug_uart.c   
	
${OBJECTDIR}/drv/utils.o: drv/utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/drv" 
	@${RM} ${OBJECTDIR}/drv/utils.o.d 
	@${RM} ${OBJECTDIR}/drv/utils.o 
	@${FIXDEPS} "${OBJECTDIR}/drv/utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/drv/utils.o.d" -o ${OBJECTDIR}/drv/utils.o drv/utils.c   
	
${OBJECTDIR}/drv/usb.o: drv/usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/drv" 
	@${RM} ${OBJECTDIR}/drv/usb.o.d 
	@${RM} ${OBJECTDIR}/drv/usb.o 
	@${FIXDEPS} "${OBJECTDIR}/drv/usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/drv/usb.o.d" -o ${OBJECTDIR}/drv/usb.o drv/usb.c   
	
${OBJECTDIR}/drv/usb_audio.o: drv/usb_audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/drv" 
	@${RM} ${OBJECTDIR}/drv/usb_audio.o.d 
	@${RM} ${OBJECTDIR}/drv/usb_audio.o 
	@${FIXDEPS} "${OBJECTDIR}/drv/usb_audio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/drv/usb_audio.o.d" -o ${OBJECTDIR}/drv/usb_audio.o drv/usb_audio.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
${OBJECTDIR}/app_config.o: app_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_config.o.d 
	@${RM} ${OBJECTDIR}/app_config.o 
	@${FIXDEPS} "${OBJECTDIR}/app_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/app_config.o.d" -o ${OBJECTDIR}/app_config.o app_config.c   
	
${OBJECTDIR}/app.o: app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app.o.d 
	@${RM} ${OBJECTDIR}/app.o 
	@${FIXDEPS} "${OBJECTDIR}/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/app.o.d" -o ${OBJECTDIR}/app.o app.c   
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c   
	
${OBJECTDIR}/tuner_control.o: tuner_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tuner_control.o.d 
	@${RM} ${OBJECTDIR}/tuner_control.o 
	@${FIXDEPS} "${OBJECTDIR}/tuner_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/tuner_control.o.d" -o ${OBJECTDIR}/tuner_control.o tuner_control.c   
	
${OBJECTDIR}/tuner_com.o: tuner_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tuner_com.o.d 
	@${RM} ${OBJECTDIR}/tuner_com.o 
	@${FIXDEPS} "${OBJECTDIR}/tuner_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/tuner_com.o.d" -o ${OBJECTDIR}/tuner_com.o tuner_com.c   
	
${OBJECTDIR}/tuner_audio.o: tuner_audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tuner_audio.o.d 
	@${RM} ${OBJECTDIR}/tuner_audio.o 
	@${FIXDEPS} "${OBJECTDIR}/tuner_audio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/tuner_audio.o.d" -o ${OBJECTDIR}/tuner_audio.o tuner_audio.c   
	
${OBJECTDIR}/tunnel.o: tunnel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tunnel.o.d 
	@${RM} ${OBJECTDIR}/tunnel.o 
	@${FIXDEPS} "${OBJECTDIR}/tunnel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -MMD -MF "${OBJECTDIR}/tunnel.o.d" -o ${OBJECTDIR}/tunnel.o tunnel.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
