cmake_minimum_required(VERSION 3.20)

project(ee205_lab14a_animal_farm_4
        VERSION 4.0
        DESCRIPTION "All animals are equal, but some animals are more equal than others"
        LANGUAGES CXX )

message( STATUS "CMAKE_SOURCE_DIR = [${CMAKE_SOURCE_DIR}]" )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE off)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

set(DOC_BUILD_DIR "${PROJECT_BINARY_DIR}/generated_docs")

find_package(Doxygen
        REQUIRED dot
        OPTIONAL_COMPONENTS mscgen dia)

if (DOXYGEN_FOUND)
   message(STATUS "Generating documentation using Doxygen")

   set(DOXYGEN_PROJECT_NUMBER ${CMAKE_PROJECT_VERSION})
   set(DOXYGEN_PROJECT_BRIEF ${PROJECT_DESCRIPTION})
   set(DOXYGEN_GENERATE_HTML YES)
   set(DOXYGEN_PROJECT_LOGO "images/animal_farm_logo.jpg")
   set(DOXYGEN_GENERATE_TREEVIEW YES)
   set(DOXYGEN_DISABLE_INDEX NO)
   set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
   set(DOXYGEN_MULTILINE_CPP_IS_BRIEF YES)
   set(DOXYGEN_TAB_SIZE 3)
   set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
   set(DOXYGEN_ALIASES "pattern=@par Design Pattern:^^")
   set(DOXYGEN_SORT_MEMBERS_CTORS_1ST YES)
   set(DOXYGEN_IMAGE_PATH images/)
   set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
   set(DOXYGEN_CLANG_ASSISTED_PARSING NO)
   set(DOXYGEN_EXTRACT_PRIVATE YES)
   set(DOXYGEN_EXTRACT_PRIV_VIRTUAL YES)
   set(DOXYGEN_EXTRACT_PACKAGE YES)
   set(DOXYGEN_EXTRACT_STATIC YES)
   set(DOXYGEN_EXTRACT_LOCAL_METHODS YES)
   set(DOXYGEN_INTERNAL_DOCS YES)
   set(DOXYGEN_QUIET YES)
   set(DOXYGEN_HTML_TIMESTAMP YES)
   set(DOXYGEN_PAPER_TYPE letter)
   set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
   set(DOXYGEN_HAVE_DOT YES)
   set(DOXYGEN_UML_LOOK YES)
   set(DOXYGEN_UML_LIMIT_NUM_FIELDS 100)
   set(DOXYGEN_DOT_UML_DETAILS YES)
   set(DOXYGEN_DOT_WRAP_THRESHOLD 80)
   set(DOXYGEN_TEMPLATE_RELATIONS YES)
   set(DOXYGEN_DOT_GRAPH_MAX_NODES 100)
   set(DOXYGEN_DOT_TRANSPARENT YES)
   set(DOXYGEN_CALL_GRAPH YES)
   set(DOXYGEN_CALLER_GRAPH YES)
   set(DOXYGEN_DOT_IMAGE_FORMAT svg)
   set(DOXYGEN_INTERACTIVE_SVG YES)
   set(DOXYGEN_WARN_AS_ERROR FAIL_ON_WARNINGS)
   set(DOXYGEN_STRIP_CODE_COMMENTS NO)
   set(DOXYGEN_SOURCE_BROWSER NO)
   set(DOXYGEN_VERBATIM_HEADERS YES)
   set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/generated_docs)

   message(STATUS "DOXYGEN_OUTPUT_DIRECTORY = [${DOXYGEN_OUTPUT_DIRECTORY}]")

   doxygen_add_docs(doc
           ${CMAKE_SOURCE_DIR}/src
           ${CMAKE_SOURCE_DIR}/README.md
           ${CMAKE_SOURCE_DIR}/CONTRIBUTE.md
           ALL
           COMMENT "Generating doxygen documentation for ${PROJECT_NAME} to ${DOXYGEN_OUTPUT_DIRECTORY}"
           )

   add_custom_command(TARGET doc
           PRE_BUILD
           COMMAND rsync --recursive --mkpath --checksum --update --delete ${CMAKE_SOURCE_DIR}/images ${DOXYGEN_OUTPUT_DIRECTORY}/html
           COMMENT "Update images directory"
           )

#   set_property(DIRECTORY ${DOXYGEN_OUTPUT_DIRECTORY}
#          APPEND
#          PROPERTY ADDITIONAL_CLEAN_FILES
#          )

   add_custom_command(TARGET doc
           POST_BUILD
           COMMAND rsync --recursive --update --delete --checksum --compress --stats ${DOXYGEN_OUTPUT_DIRECTORY}/html/ marknels@uhunix.hawaii.edu:~/public_html/ee205/${CMAKE_PROJECT_NAME}
           COMMENT "Push files to UHUnix"
           )

else (DOXYGEN_FOUND)
   message("Doxygen needs to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

message(STATUS "PROJECT_BINARY_DIR = [${PROJECT_BINARY_DIR}]")

add_subdirectory(tests)

add_executable(ee205_lab14a_animal_farm_4 src/config.h src/main.cpp src/Node.h src/List.h src/List.cpp src/SinglyLinkedList.h src/SinglyLinkedList.cpp src/DoublyLinkedList.h src/DoublyLinkedList.cpp src/Gender.h src/Color.h src/Weight.h src/Weight.cpp src/Animal.h src/Animal.cpp src/Mammal.h src/Mammal.cpp src/Cat.h src/Cat.cpp)
