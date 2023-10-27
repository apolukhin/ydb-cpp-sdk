RESOURCES_LIBRARY()

IF(NEBIUS)
    DECLARE_EXTERNAL_HOST_RESOURCES_BUNDLE_BY_JSON(JDK21 jdk_nebius.json)
    SET_RESOURCE_URI_FROM_JSON(WITH_JDK21_URI jdk_nebius.json)
ELSE()
    DECLARE_EXTERNAL_HOST_RESOURCES_BUNDLE_BY_JSON(JDK21 jdk.json)
    SET_RESOURCE_URI_FROM_JSON(WITH_JDK21_URI jdk.json)
ENDIF()

IF (WITH_JDK21_URI)
    DECLARE_EXTERNAL_RESOURCE(WITH_JDK21 ${WITH_JDK21_URI})
ENDIF()

END()

IF (AUTOCHECK)
    RECURSE_FOR_TESTS(ut)
ENDIF()
IF(YA_IDE_IDEA)
    RECURSE_FOR_TESTS(ut)
ENDIF()
