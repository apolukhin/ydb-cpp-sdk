RESOURCES_LIBRARY() 
 
OWNER( 
    g:contrib 
    g:yatool 
) 
 
INCLUDE(${ARCADIA_ROOT}/build/platform/python/resources.inc) 
 
IF (OS_LINUX) 
    DECLARE_EXTERNAL_RESOURCE(EXTERNAL_PYTHON38 ${PYTHON38_LINUX})
ELSEIF (OS_DARWIN) 
    DECLARE_EXTERNAL_RESOURCE(EXTERNAL_PYTHON38 ${PYTHON38_DARWIN})
    IF (ARCH_ARM64)
        DECLARE_EXTERNAL_RESOURCE(EXTERNAL_PYTHON38 ${PYTHON38_DARWIN_ARM64})
    ELSEIF(ARCH_X86_64)
        DECLARE_EXTERNAL_RESOURCE(EXTERNAL_PYTHON38 ${PYTHON38_DARWIN})
    ENDIF()
ELSEIF (OS_WINDOWS) 
    DECLARE_EXTERNAL_RESOURCE(EXTERNAL_PYTHON38 ${PYTHON38_WINDOWS})
ENDIF() 
 
END() 
