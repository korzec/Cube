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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/cubecodec/Picture.o \
	${OBJECTDIR}/cubecodec/CubeIO.o \
	${OBJECTDIR}/cubecodec/PictureIO.o \
	${OBJECTDIR}/cubecodec/WaveletTransform.o \
	${OBJECTDIR}/cubecodec/Encoder.o \
	${OBJECTDIR}/cubecodec/CubeTransform.o \
	${OBJECTDIR}/cubecodec/general.o \
	${OBJECTDIR}/cubecodec/CompressorLZO.o \
	${OBJECTDIR}/cubecodec/PictureBuffer.o \
	${OBJECTDIR}/cubecodec/Decoder.o \
	${OBJECTDIR}/cubecodec/CompressorHuffman.o \
	${OBJECTDIR}/encoder/cube_encode.o \
	${OBJECTDIR}/cubecodec/SubbandList.o \
	${OBJECTDIR}/cubecodec/SubcubeIndex.o \
	${OBJECTDIR}/cubecodec/CubeStream.o \
	${OBJECTDIR}/cubecodec/CoeffCube.o \
	${OBJECTDIR}/minilzo/minilzo.o \
	${OBJECTDIR}/cubecodec/Subcube.o \
	${OBJECTDIR}/encoder/tests2.o \
	${OBJECTDIR}/encoder/cube_codec.o \
	${OBJECTDIR}/cubecodec/Packet.o \
	${OBJECTDIR}/cubecodec/CompressorAC.o \
	${OBJECTDIR}/encoder/tests.o \
	${OBJECTDIR}/encoder/cube_decode.o \
	${OBJECTDIR}/cubecodec/FrameBuffer.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f3

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cube

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cube: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cube ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/cubecodec/Picture.o: cubecodec/Picture.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Picture.o cubecodec/Picture.cpp

${OBJECTDIR}/cubecodec/CubeIO.o: cubecodec/CubeIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CubeIO.o cubecodec/CubeIO.cpp

${OBJECTDIR}/cubecodec/PictureIO.o: cubecodec/PictureIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/PictureIO.o cubecodec/PictureIO.cpp

${OBJECTDIR}/cubecodec/WaveletTransform.o: cubecodec/WaveletTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/WaveletTransform.o cubecodec/WaveletTransform.cpp

${OBJECTDIR}/cubecodec/Encoder.o: cubecodec/Encoder.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Encoder.o cubecodec/Encoder.cpp

${OBJECTDIR}/cubecodec/CubeTransform.o: cubecodec/CubeTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CubeTransform.o cubecodec/CubeTransform.cpp

${OBJECTDIR}/cubecodec/general.o: cubecodec/general.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/general.o cubecodec/general.cpp

${OBJECTDIR}/cubecodec/CompressorLZO.o: cubecodec/CompressorLZO.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CompressorLZO.o cubecodec/CompressorLZO.cpp

${OBJECTDIR}/cubecodec/PictureBuffer.o: cubecodec/PictureBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/PictureBuffer.o cubecodec/PictureBuffer.cpp

${OBJECTDIR}/cubecodec/Decoder.o: cubecodec/Decoder.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Decoder.o cubecodec/Decoder.cpp

${OBJECTDIR}/cubecodec/CompressorHuffman.o: cubecodec/CompressorHuffman.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CompressorHuffman.o cubecodec/CompressorHuffman.cpp

${OBJECTDIR}/encoder/cube_encode.o: encoder/cube_encode.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/cube_encode.o encoder/cube_encode.cpp

${OBJECTDIR}/cubecodec/SubbandList.o: cubecodec/SubbandList.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/SubbandList.o cubecodec/SubbandList.cpp

${OBJECTDIR}/cubecodec/SubcubeIndex.o: cubecodec/SubcubeIndex.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/SubcubeIndex.o cubecodec/SubcubeIndex.cpp

${OBJECTDIR}/cubecodec/CubeStream.o: cubecodec/CubeStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CubeStream.o cubecodec/CubeStream.cpp

${OBJECTDIR}/cubecodec/CoeffCube.o: cubecodec/CoeffCube.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CoeffCube.o cubecodec/CoeffCube.cpp

${OBJECTDIR}/minilzo/minilzo.o: minilzo/minilzo.c 
	${MKDIR} -p ${OBJECTDIR}/minilzo
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/minilzo/minilzo.o minilzo/minilzo.c

${OBJECTDIR}/cubecodec/Subcube.o: cubecodec/Subcube.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Subcube.o cubecodec/Subcube.cpp

${OBJECTDIR}/encoder/tests2.o: encoder/tests2.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/tests2.o encoder/tests2.cpp

${OBJECTDIR}/encoder/cube_codec.o: encoder/cube_codec.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/cube_codec.o encoder/cube_codec.cpp

${OBJECTDIR}/cubecodec/Packet.o: cubecodec/Packet.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Packet.o cubecodec/Packet.cpp

${OBJECTDIR}/cubecodec/CompressorAC.o: cubecodec/CompressorAC.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CompressorAC.o cubecodec/CompressorAC.cpp

${OBJECTDIR}/encoder/tests.o: encoder/tests.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/tests.o encoder/tests.cpp

${OBJECTDIR}/encoder/cube_decode.o: encoder/cube_decode.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/cube_decode.o encoder/cube_decode.cpp

${OBJECTDIR}/cubecodec/FrameBuffer.o: cubecodec/FrameBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/FrameBuffer.o cubecodec/FrameBuffer.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/CompressorTestClass.o ${TESTDIR}/tests/CompressorTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lcppunit 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/CubeIOTestClass.o ${TESTDIR}/tests/CubeIOTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lcppunit 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/CompressorHuffmanTestClass.o ${TESTDIR}/tests/CompressorHuffmanTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/PictureTestClass.o ${TESTDIR}/tests/PictureTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lcppunit 


${TESTDIR}/tests/CompressorTestClass.o: tests/CompressorTestClass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CompressorTestClass.o tests/CompressorTestClass.cpp


${TESTDIR}/tests/CompressorTestRunner.o: tests/CompressorTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CompressorTestRunner.o tests/CompressorTestRunner.cpp


${TESTDIR}/tests/CubeIOTestClass.o: tests/CubeIOTestClass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CubeIOTestClass.o tests/CubeIOTestClass.cpp


${TESTDIR}/tests/CubeIOTestRunner.o: tests/CubeIOTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CubeIOTestRunner.o tests/CubeIOTestRunner.cpp


${TESTDIR}/tests/CompressorHuffmanTestClass.o: tests/CompressorHuffmanTestClass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CompressorHuffmanTestClass.o tests/CompressorHuffmanTestClass.cpp


${TESTDIR}/tests/CompressorHuffmanTestRunner.o: tests/CompressorHuffmanTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CompressorHuffmanTestRunner.o tests/CompressorHuffmanTestRunner.cpp


${TESTDIR}/tests/PictureTestClass.o: tests/PictureTestClass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/PictureTestClass.o tests/PictureTestClass.cpp


${TESTDIR}/tests/PictureTestRunner.o: tests/PictureTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/PictureTestRunner.o tests/PictureTestRunner.cpp


${OBJECTDIR}/cubecodec/Picture_nomain.o: ${OBJECTDIR}/cubecodec/Picture.o cubecodec/Picture.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/Picture.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Picture_nomain.o cubecodec/Picture.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/Picture.o ${OBJECTDIR}/cubecodec/Picture_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/CubeIO_nomain.o: ${OBJECTDIR}/cubecodec/CubeIO.o cubecodec/CubeIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/CubeIO.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CubeIO_nomain.o cubecodec/CubeIO.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/CubeIO.o ${OBJECTDIR}/cubecodec/CubeIO_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/PictureIO_nomain.o: ${OBJECTDIR}/cubecodec/PictureIO.o cubecodec/PictureIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/PictureIO.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/PictureIO_nomain.o cubecodec/PictureIO.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/PictureIO.o ${OBJECTDIR}/cubecodec/PictureIO_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/WaveletTransform_nomain.o: ${OBJECTDIR}/cubecodec/WaveletTransform.o cubecodec/WaveletTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/WaveletTransform.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/WaveletTransform_nomain.o cubecodec/WaveletTransform.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/WaveletTransform.o ${OBJECTDIR}/cubecodec/WaveletTransform_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/Encoder_nomain.o: ${OBJECTDIR}/cubecodec/Encoder.o cubecodec/Encoder.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/Encoder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Encoder_nomain.o cubecodec/Encoder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/Encoder.o ${OBJECTDIR}/cubecodec/Encoder_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/CubeTransform_nomain.o: ${OBJECTDIR}/cubecodec/CubeTransform.o cubecodec/CubeTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/CubeTransform.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CubeTransform_nomain.o cubecodec/CubeTransform.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/CubeTransform.o ${OBJECTDIR}/cubecodec/CubeTransform_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/general_nomain.o: ${OBJECTDIR}/cubecodec/general.o cubecodec/general.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/general.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/general_nomain.o cubecodec/general.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/general.o ${OBJECTDIR}/cubecodec/general_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/CompressorLZO_nomain.o: ${OBJECTDIR}/cubecodec/CompressorLZO.o cubecodec/CompressorLZO.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/CompressorLZO.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CompressorLZO_nomain.o cubecodec/CompressorLZO.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/CompressorLZO.o ${OBJECTDIR}/cubecodec/CompressorLZO_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/PictureBuffer_nomain.o: ${OBJECTDIR}/cubecodec/PictureBuffer.o cubecodec/PictureBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/PictureBuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/PictureBuffer_nomain.o cubecodec/PictureBuffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/PictureBuffer.o ${OBJECTDIR}/cubecodec/PictureBuffer_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/Decoder_nomain.o: ${OBJECTDIR}/cubecodec/Decoder.o cubecodec/Decoder.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/Decoder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Decoder_nomain.o cubecodec/Decoder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/Decoder.o ${OBJECTDIR}/cubecodec/Decoder_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/CompressorHuffman_nomain.o: ${OBJECTDIR}/cubecodec/CompressorHuffman.o cubecodec/CompressorHuffman.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/CompressorHuffman.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CompressorHuffman_nomain.o cubecodec/CompressorHuffman.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/CompressorHuffman.o ${OBJECTDIR}/cubecodec/CompressorHuffman_nomain.o;\
	fi

${OBJECTDIR}/encoder/cube_encode_nomain.o: ${OBJECTDIR}/encoder/cube_encode.o encoder/cube_encode.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	@NMOUTPUT=`${NM} ${OBJECTDIR}/encoder/cube_encode.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/cube_encode_nomain.o encoder/cube_encode.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/encoder/cube_encode.o ${OBJECTDIR}/encoder/cube_encode_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/SubbandList_nomain.o: ${OBJECTDIR}/cubecodec/SubbandList.o cubecodec/SubbandList.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/SubbandList.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/SubbandList_nomain.o cubecodec/SubbandList.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/SubbandList.o ${OBJECTDIR}/cubecodec/SubbandList_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/SubcubeIndex_nomain.o: ${OBJECTDIR}/cubecodec/SubcubeIndex.o cubecodec/SubcubeIndex.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/SubcubeIndex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/SubcubeIndex_nomain.o cubecodec/SubcubeIndex.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/SubcubeIndex.o ${OBJECTDIR}/cubecodec/SubcubeIndex_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/CubeStream_nomain.o: ${OBJECTDIR}/cubecodec/CubeStream.o cubecodec/CubeStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/CubeStream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CubeStream_nomain.o cubecodec/CubeStream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/CubeStream.o ${OBJECTDIR}/cubecodec/CubeStream_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/CoeffCube_nomain.o: ${OBJECTDIR}/cubecodec/CoeffCube.o cubecodec/CoeffCube.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/CoeffCube.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CoeffCube_nomain.o cubecodec/CoeffCube.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/CoeffCube.o ${OBJECTDIR}/cubecodec/CoeffCube_nomain.o;\
	fi

${OBJECTDIR}/minilzo/minilzo_nomain.o: ${OBJECTDIR}/minilzo/minilzo.o minilzo/minilzo.c 
	${MKDIR} -p ${OBJECTDIR}/minilzo
	@NMOUTPUT=`${NM} ${OBJECTDIR}/minilzo/minilzo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/minilzo/minilzo_nomain.o minilzo/minilzo.c;\
	else  \
	    ${CP} ${OBJECTDIR}/minilzo/minilzo.o ${OBJECTDIR}/minilzo/minilzo_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/Subcube_nomain.o: ${OBJECTDIR}/cubecodec/Subcube.o cubecodec/Subcube.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/Subcube.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Subcube_nomain.o cubecodec/Subcube.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/Subcube.o ${OBJECTDIR}/cubecodec/Subcube_nomain.o;\
	fi

${OBJECTDIR}/encoder/tests2_nomain.o: ${OBJECTDIR}/encoder/tests2.o encoder/tests2.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	@NMOUTPUT=`${NM} ${OBJECTDIR}/encoder/tests2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/tests2_nomain.o encoder/tests2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/encoder/tests2.o ${OBJECTDIR}/encoder/tests2_nomain.o;\
	fi

${OBJECTDIR}/encoder/cube_codec_nomain.o: ${OBJECTDIR}/encoder/cube_codec.o encoder/cube_codec.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	@NMOUTPUT=`${NM} ${OBJECTDIR}/encoder/cube_codec.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/cube_codec_nomain.o encoder/cube_codec.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/encoder/cube_codec.o ${OBJECTDIR}/encoder/cube_codec_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/Packet_nomain.o: ${OBJECTDIR}/cubecodec/Packet.o cubecodec/Packet.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/Packet.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/Packet_nomain.o cubecodec/Packet.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/Packet.o ${OBJECTDIR}/cubecodec/Packet_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/CompressorAC_nomain.o: ${OBJECTDIR}/cubecodec/CompressorAC.o cubecodec/CompressorAC.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/CompressorAC.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/CompressorAC_nomain.o cubecodec/CompressorAC.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/CompressorAC.o ${OBJECTDIR}/cubecodec/CompressorAC_nomain.o;\
	fi

${OBJECTDIR}/encoder/tests_nomain.o: ${OBJECTDIR}/encoder/tests.o encoder/tests.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	@NMOUTPUT=`${NM} ${OBJECTDIR}/encoder/tests.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/tests_nomain.o encoder/tests.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/encoder/tests.o ${OBJECTDIR}/encoder/tests_nomain.o;\
	fi

${OBJECTDIR}/encoder/cube_decode_nomain.o: ${OBJECTDIR}/encoder/cube_decode.o encoder/cube_decode.cpp 
	${MKDIR} -p ${OBJECTDIR}/encoder
	@NMOUTPUT=`${NM} ${OBJECTDIR}/encoder/cube_decode.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/encoder/cube_decode_nomain.o encoder/cube_decode.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/encoder/cube_decode.o ${OBJECTDIR}/encoder/cube_decode_nomain.o;\
	fi

${OBJECTDIR}/cubecodec/FrameBuffer_nomain.o: ${OBJECTDIR}/cubecodec/FrameBuffer.o cubecodec/FrameBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/cubecodec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cubecodec/FrameBuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DDEBUG -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubecodec/FrameBuffer_nomain.o cubecodec/FrameBuffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cubecodec/FrameBuffer.o ${OBJECTDIR}/cubecodec/FrameBuffer_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
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
