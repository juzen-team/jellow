# - Try to find GSASL 
# Find GSASL headers, libraries and the answer to all questions.
#
#  GSASL_FOUND               True if libgsasl got found
#  GSASL_INCLUDE_DIRS        Location of libgsasl headers 
#  GSASL_LIBRARIES           List of libaries to use libgsasl 
#
# Copyright (c) 2009 Nigmatullin Ruslan <euroelessar@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if( WIN32 )
	FIND_PATH( GSASL_INCLUDE_DIRS gsasl.h $ENV{INCLUDE} )
	FIND_LIBRARY( GSASL_LIBRARIES libgsasl-7 $ENV{LIB} )
else( )
	FIND_PACKAGE(PkgConfig)
	PKG_SEARCH_MODULE(GSASL REQUIRED libgsasl)
endif( )

if( GSASL_LIBRARIES AND ( GSASL_INCLUDE_DIRS OR GSASL_INCLUDEDIR ) )
	message( STATUS "Found libgsasl: ${GSASL_LIBRARIES}" )
	set( GSASL_FOUND true )
else()
	message( STATUS "Could NOT find libgsasl" )
endif()
