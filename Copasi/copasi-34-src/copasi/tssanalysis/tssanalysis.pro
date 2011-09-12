# Begin CVS Header
#   $Source: /fs/turing/cvs/copasi_dev/copasi/tssanalysis/tssanalysis.pro,v $
#   $Revision: 1.11.2.2 $
#   $Name: Build-33 $
#   $Author: shoops $
#   $Date: 2010/11/13 16:56:01 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

LIB = tssanalysis
DISTFILES = tssanalysis.pro

# Input
HEADERS += CILDMMethod.h \
           CILDMModifiedMethod.h \
	         CTSSAMethod.h \
           CTSSAProblem.h \
           CTSSATask.h \
           CCSPMethod.h

SOURCES += CILDMMethod.cpp \
           CILDMModifiedMethod.cpp \
	         CTSSAMethod.cpp \
           CTSSAProblem.cpp \
           CTSSATask.cpp \
           CCSPMethod.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)

           
