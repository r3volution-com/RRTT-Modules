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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Animation.o \
	${OBJECTDIR}/Boss.o \
	${OBJECTDIR}/Bullet.o \
	${OBJECTDIR}/Button.o \
	${OBJECTDIR}/Coordinate.o \
	${OBJECTDIR}/Enemy.o \
	${OBJECTDIR}/Entity.o \
	${OBJECTDIR}/Font.o \
	${OBJECTDIR}/Game.o \
	${OBJECTDIR}/HUD.o \
	${OBJECTDIR}/Hitbox.o \
	${OBJECTDIR}/InterpolatedCoordinate.o \
	${OBJECTDIR}/Level.o \
	${OBJECTDIR}/Map.o \
	${OBJECTDIR}/Menu.o \
	${OBJECTDIR}/NPC.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/Sprite.o \
	${OBJECTDIR}/Text.o \
	${OBJECTDIR}/Texture.o \
	${OBJECTDIR}/menuTest/main.o


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
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libsfml-graphics.so /usr/lib/x86_64-linux-gnu/libsfml-system.so /usr/lib/x86_64-linux-gnu/libsfml-window.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rrttmodules

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rrttmodules: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rrttmodules: /usr/lib/x86_64-linux-gnu/libsfml-system.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rrttmodules: /usr/lib/x86_64-linux-gnu/libsfml-window.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rrttmodules: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rrttmodules ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Animation.o: Animation.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Animation.o Animation.cpp

${OBJECTDIR}/Boss.o: Boss.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Boss.o Boss.cpp

${OBJECTDIR}/Bullet.o: Bullet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Bullet.o Bullet.cpp

${OBJECTDIR}/Button.o: Button.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Button.o Button.cpp

${OBJECTDIR}/Coordinate.o: Coordinate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Coordinate.o Coordinate.cpp

${OBJECTDIR}/Enemy.o: Enemy.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Enemy.o Enemy.cpp

${OBJECTDIR}/Entity.o: Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Entity.o Entity.cpp

${OBJECTDIR}/Font.o: Font.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Font.o Font.cpp

${OBJECTDIR}/Game.o: Game.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game.o Game.cpp

${OBJECTDIR}/HUD.o: HUD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HUD.o HUD.cpp

${OBJECTDIR}/Hitbox.o: Hitbox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hitbox.o Hitbox.cpp

${OBJECTDIR}/InterpolatedCoordinate.o: InterpolatedCoordinate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InterpolatedCoordinate.o InterpolatedCoordinate.cpp

${OBJECTDIR}/Level.o: Level.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Level.o Level.cpp

${OBJECTDIR}/Map.o: Map.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Map.o Map.cpp

${OBJECTDIR}/Menu.o: Menu.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Menu.o Menu.cpp

${OBJECTDIR}/NPC.o: NPC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NPC.o NPC.cpp

${OBJECTDIR}/Player.o: Player.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/Sprite.o: Sprite.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sprite.o Sprite.cpp

${OBJECTDIR}/Text.o: Text.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Text.o Text.cpp

${OBJECTDIR}/Texture.o: Texture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Texture.o Texture.cpp

${OBJECTDIR}/menuTest/main.o: menuTest/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/menuTest
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/menuTest/main.o menuTest/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rrttmodules

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
