OWNER(g:ymake) 
 
INCLUDE(ya.make.prebuilt) 
 
IF (NOT PREBUILT) 
    MESSAGE(FATAL_ERROR Unsupported host platform for prebuilt event2cpp tool) 
ENDIF() 
