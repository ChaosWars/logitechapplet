FIND_PATH( LIBG15_INCLUDE_DIR libg15.h /usr/include /usr/local/include )

FIND_LIBRARY( LIBG15_LIBRARY NAMES g15 PATH /usr/lib /usr/local/lib )

IF( LIBG15_INCLUDE_DIR AND LIBG15_LIBRARY )
   SET( LIBG15_FOUND TRUE )
ENDIF( LIBG15_INCLUDE_DIR AND LIBG15_LIBRARY )


IF( LIBG15_FOUND )
   IF( NOT libg15_FIND_QUIETLY )
      MESSAGE( STATUS "Found libg15: ${LIBG15_LIBRARY}" )
   ENDIF( NOT libg15_FIND_QUIETLY )
ELSE( LIBG15_FOUND )
   IF( libg15_FIND_REQUIRED )
      MESSAGE( FATAL_ERROR "Could not find libg15" )
   ENDIF( libg15_FIND_REQUIRED )
ENDIF( LIBG15_FOUND ) 