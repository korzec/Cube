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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/tests.o \
	${OBJECTDIR}/Compressor.o \
	${OBJECTDIR}/cube_codec.o \
	${OBJECTDIR}/CubeIO.o \
	${OBJECTDIR}/SubcubeIndex.o \
	${OBJECTDIR}/WaveletTransform.o \
	${OBJECTDIR}/Picture.o \
	${OBJECTDIR}/SubbandList.o \
	${OBJECTDIR}/Subcube.o \
	${OBJECTDIR}/Encoder.o \
	${OBJECTDIR}/PictureIO.o \
	${OBJECTDIR}/CubeTransform.o \
	${OBJECTDIR}/CoeffCube.o \
	${OBJECTDIR}/Packet.o \
	${OBJECTDIR}/PictureBuffer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-fopenmp
CXXFLAGS=-fopenmp

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cube

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cube: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cube ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/tests.o: tests.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/tests.o tests.cpp

${OBJECTDIR}/Compressor.o: Compressor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Compressor.o Compressor.cpp

${OBJECTDIR}/cube_codec.o: cube_codec.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/cube_codec.o cube_codec.cpp

${OBJECTDIR}/CubeIO.o: CubeIO.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/CubeIO.o CubeIO.cpp

${OBJECTDIR}/SubcubeIndex.o: SubcubeIndex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/SubcubeIndex.o SubcubeIndex.cpp

${OBJECTDIR}/WaveletTransform.o: WaveletTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/WaveletTransform.o WaveletTransform.cpp

${OBJECTDIR}/Picture.o: Picture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Picture.o Picture.cpp

${OBJECTDIR}/SubbandList.o: SubbandList.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/SubbandList.o SubbandList.cpp

${OBJECTDIR}/Subcube.o: Subcube.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Subcube.o Subcube.cpp

${OBJECTDIR}/Encoder.o: Encoder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Encoder.o Encoder.cpp

${OBJECTDIR}/PictureIO.o: PictureIO.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/PictureIO.o PictureIO.cpp

${OBJECTDIR}/CubeTransform.o: CubeTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/CubeTransform.o CubeTransform.cpp

${OBJECTDIR}/CoeffCube.o: CoeffCube.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/CoeffCube.o CoeffCube.cpp

${OBJECTDIR}/Packet.o: Packet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Packet.o Packet.cpp

${OBJECTDIR}/PictureBuffer.o: PictureBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/PictureBuffer.o PictureBuffer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cube

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
