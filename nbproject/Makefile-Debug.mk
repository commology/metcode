#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=cc
CCC=CC
CXX=CC
FC=f95
AS=as

# Macros
CND_PLATFORM=OracleSolarisStudio-Solaris-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ITA.o \
	${OBJECTDIR}/FMCode.o \
	${OBJECTDIR}/StreamWriter.o \
	${OBJECTDIR}/FMCodeFM12.o \
	${OBJECTDIR}/Bulletin.o \
	${OBJECTDIR}/Helper.o \
	${OBJECTDIR}/Message.o \
	${OBJECTDIR}/IOException.o \
	${OBJECTDIR}/FMCodeAny.o \
	${OBJECTDIR}/StreamReader.o \
	${OBJECTDIR}/BulletinTAC.o \
	${OBJECTDIR}/Exception.o \
	${OBJECTDIR}/MessageITA2.o \
	${OBJECTDIR}/MessageAWSS.o \
	${OBJECTDIR}/MessageITA5.o \
	${OBJECTDIR}/Processor.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libMetCode.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libMetCode.so: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -G -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libMetCode.so -KPIC -norunpath -h libMetCode.so ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/ITA.o: ITA.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -g -KPIC  -o ${OBJECTDIR}/ITA.o ITA.c

${OBJECTDIR}/FMCode.o: FMCode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/FMCode.o FMCode.cpp

${OBJECTDIR}/StreamWriter.o: StreamWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/StreamWriter.o StreamWriter.cpp

${OBJECTDIR}/FMCodeFM12.o: FMCodeFM12.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/FMCodeFM12.o FMCodeFM12.cpp

${OBJECTDIR}/Bulletin.o: Bulletin.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Bulletin.o Bulletin.cpp

${OBJECTDIR}/Helper.o: Helper.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Helper.o Helper.cpp

${OBJECTDIR}/Message.o: Message.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Message.o Message.cpp

${OBJECTDIR}/IOException.o: IOException.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/IOException.o IOException.cpp

${OBJECTDIR}/FMCodeAny.o: FMCodeAny.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/FMCodeAny.o FMCodeAny.cpp

${OBJECTDIR}/StreamReader.o: StreamReader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/StreamReader.o StreamReader.cpp

${OBJECTDIR}/BulletinTAC.o: BulletinTAC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/BulletinTAC.o BulletinTAC.cpp

${OBJECTDIR}/Exception.o: Exception.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Exception.o Exception.cpp

${OBJECTDIR}/MessageITA2.o: MessageITA2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/MessageITA2.o MessageITA2.cpp

${OBJECTDIR}/MessageAWSS.o: MessageAWSS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/MessageAWSS.o MessageAWSS.cpp

${OBJECTDIR}/MessageITA5.o: MessageITA5.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/MessageITA5.o MessageITA5.cpp

${OBJECTDIR}/Processor.o: Processor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Processor.o Processor.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libMetCode.so
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
