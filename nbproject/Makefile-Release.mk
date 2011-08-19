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
	${OBJECTDIR}/tests2.o \
	${OBJECTDIR}/general.o \
	${OBJECTDIR}/SubcubeIndex.o \
	${OBJECTDIR}/CubeStream.o \
	${OBJECTDIR}/CubeIO.o \
	${OBJECTDIR}/WaveletTransform.o \
	${OBJECTDIR}/Picture.o \
	${OBJECTDIR}/Subcube.o \
	${OBJECTDIR}/SubbandList.o \
	${OBJECTDIR}/Encoder.o \
	${OBJECTDIR}/PictureIO.o \
	${OBJECTDIR}/CubeTransform.o \
	${OBJECTDIR}/minilzo/minilzo.o \
	${OBJECTDIR}/CoeffCube.o \
	${OBJECTDIR}/Packet.o \
	${OBJECTDIR}/PictureBuffer.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3

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

${OBJECTDIR}/tests2.o: tests2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/tests2.o tests2.cpp

${OBJECTDIR}/general.o: general.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/general.o general.cpp

${OBJECTDIR}/SubcubeIndex.o: SubcubeIndex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/SubcubeIndex.o SubcubeIndex.cpp

${OBJECTDIR}/CubeStream.o: CubeStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/CubeStream.o CubeStream.cpp

${OBJECTDIR}/CubeIO.o: CubeIO.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/CubeIO.o CubeIO.cpp

${OBJECTDIR}/WaveletTransform.o: WaveletTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/WaveletTransform.o WaveletTransform.cpp

${OBJECTDIR}/Picture.o: Picture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Picture.o Picture.cpp

${OBJECTDIR}/Subcube.o: Subcube.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Subcube.o Subcube.cpp

${OBJECTDIR}/SubbandList.o: SubbandList.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/SubbandList.o SubbandList.cpp

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

${OBJECTDIR}/minilzo/minilzo.o: minilzo/minilzo.c 
	${MKDIR} -p ${OBJECTDIR}/minilzo
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/minilzo/minilzo.o minilzo/minilzo.c

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

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/CompressorTestClass.o ${TESTDIR}/tests/CompressorTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lcppunit -lcppunit 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/CubeIOTestClass.o ${TESTDIR}/tests/CubeIOTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lcppunit -lcppunit 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/PictureTestClass.o ${TESTDIR}/tests/PictureTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lcppunit 


${TESTDIR}/tests/CompressorTestClass.o: tests/CompressorTestClass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CompressorTestClass.o tests/CompressorTestClass.cpp


${TESTDIR}/tests/CompressorTestRunner.o: tests/CompressorTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CompressorTestRunner.o tests/CompressorTestRunner.cpp


${TESTDIR}/tests/CubeIOTestClass.o: tests/CubeIOTestClass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CubeIOTestClass.o tests/CubeIOTestClass.cpp


${TESTDIR}/tests/CubeIOTestRunner.o: tests/CubeIOTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CubeIOTestRunner.o tests/CubeIOTestRunner.cpp


${TESTDIR}/tests/PictureTestClass.o: tests/PictureTestClass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/PictureTestClass.o tests/PictureTestClass.cpp


${TESTDIR}/tests/PictureTestRunner.o: tests/PictureTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/PictureTestRunner.o tests/PictureTestRunner.cpp


${OBJECTDIR}/tests_nomain.o: ${OBJECTDIR}/tests.o tests.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tests.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/tests_nomain.o tests.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/tests.o ${OBJECTDIR}/tests_nomain.o;\
	fi

${OBJECTDIR}/Compressor_nomain.o: ${OBJECTDIR}/Compressor.o Compressor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Compressor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Compressor_nomain.o Compressor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Compressor.o ${OBJECTDIR}/Compressor_nomain.o;\
	fi

${OBJECTDIR}/cube_codec_nomain.o: ${OBJECTDIR}/cube_codec.o cube_codec.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cube_codec.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cube_codec_nomain.o cube_codec.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cube_codec.o ${OBJECTDIR}/cube_codec_nomain.o;\
	fi

${OBJECTDIR}/tests2_nomain.o: ${OBJECTDIR}/tests2.o tests2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tests2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/tests2_nomain.o tests2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/tests2.o ${OBJECTDIR}/tests2_nomain.o;\
	fi

${OBJECTDIR}/general_nomain.o: ${OBJECTDIR}/general.o general.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/general.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/general_nomain.o general.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/general.o ${OBJECTDIR}/general_nomain.o;\
	fi

${OBJECTDIR}/SubcubeIndex_nomain.o: ${OBJECTDIR}/SubcubeIndex.o SubcubeIndex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SubcubeIndex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SubcubeIndex_nomain.o SubcubeIndex.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SubcubeIndex.o ${OBJECTDIR}/SubcubeIndex_nomain.o;\
	fi

${OBJECTDIR}/CubeStream_nomain.o: ${OBJECTDIR}/CubeStream.o CubeStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CubeStream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CubeStream_nomain.o CubeStream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CubeStream.o ${OBJECTDIR}/CubeStream_nomain.o;\
	fi

${OBJECTDIR}/CubeIO_nomain.o: ${OBJECTDIR}/CubeIO.o CubeIO.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CubeIO.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CubeIO_nomain.o CubeIO.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CubeIO.o ${OBJECTDIR}/CubeIO_nomain.o;\
	fi

${OBJECTDIR}/WaveletTransform_nomain.o: ${OBJECTDIR}/WaveletTransform.o WaveletTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/WaveletTransform.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/WaveletTransform_nomain.o WaveletTransform.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/WaveletTransform.o ${OBJECTDIR}/WaveletTransform_nomain.o;\
	fi

${OBJECTDIR}/Picture_nomain.o: ${OBJECTDIR}/Picture.o Picture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Picture.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Picture_nomain.o Picture.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Picture.o ${OBJECTDIR}/Picture_nomain.o;\
	fi

${OBJECTDIR}/Subcube_nomain.o: ${OBJECTDIR}/Subcube.o Subcube.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Subcube.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Subcube_nomain.o Subcube.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Subcube.o ${OBJECTDIR}/Subcube_nomain.o;\
	fi

${OBJECTDIR}/SubbandList_nomain.o: ${OBJECTDIR}/SubbandList.o SubbandList.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SubbandList.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SubbandList_nomain.o SubbandList.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SubbandList.o ${OBJECTDIR}/SubbandList_nomain.o;\
	fi

${OBJECTDIR}/Encoder_nomain.o: ${OBJECTDIR}/Encoder.o Encoder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Encoder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Encoder_nomain.o Encoder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Encoder.o ${OBJECTDIR}/Encoder_nomain.o;\
	fi

${OBJECTDIR}/PictureIO_nomain.o: ${OBJECTDIR}/PictureIO.o PictureIO.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/PictureIO.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/PictureIO_nomain.o PictureIO.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/PictureIO.o ${OBJECTDIR}/PictureIO_nomain.o;\
	fi

${OBJECTDIR}/CubeTransform_nomain.o: ${OBJECTDIR}/CubeTransform.o CubeTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CubeTransform.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CubeTransform_nomain.o CubeTransform.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CubeTransform.o ${OBJECTDIR}/CubeTransform_nomain.o;\
	fi

${OBJECTDIR}/minilzo/minilzo_nomain.o: ${OBJECTDIR}/minilzo/minilzo.o minilzo/minilzo.c 
	${MKDIR} -p ${OBJECTDIR}/minilzo
	@NMOUTPUT=`${NM} ${OBJECTDIR}/minilzo/minilzo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/minilzo/minilzo_nomain.o minilzo/minilzo.c;\
	else  \
	    ${CP} ${OBJECTDIR}/minilzo/minilzo.o ${OBJECTDIR}/minilzo/minilzo_nomain.o;\
	fi

${OBJECTDIR}/CoeffCube_nomain.o: ${OBJECTDIR}/CoeffCube.o CoeffCube.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CoeffCube.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CoeffCube_nomain.o CoeffCube.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CoeffCube.o ${OBJECTDIR}/CoeffCube_nomain.o;\
	fi

${OBJECTDIR}/Packet_nomain.o: ${OBJECTDIR}/Packet.o Packet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Packet.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Packet_nomain.o Packet.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Packet.o ${OBJECTDIR}/Packet_nomain.o;\
	fi

${OBJECTDIR}/PictureBuffer_nomain.o: ${OBJECTDIR}/PictureBuffer.o PictureBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/PictureBuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Wall -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/PictureBuffer_nomain.o PictureBuffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/PictureBuffer.o ${OBJECTDIR}/PictureBuffer_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cube

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
