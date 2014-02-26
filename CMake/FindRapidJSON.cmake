#
# Try to find RapidJSON library and include path.
# Once done this will define
#
# RAPIDJSON_FOUND
# RAPIDJSON_INCLUDE_DIR
#

FIND_PATH(RAPIDJSON_INCLUDE_DIR rapidjson/rapidjson.h
        ${RAPIDJSON_ROOT_DIR}/include
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        DOC "The directory where rapidjson/rapidjson.h resides")

INCLUDE(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set RAPIDJSON_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(RAPIDJSON DEFAULT_MSG RAPIDJSON_INCLUDE_DIR)