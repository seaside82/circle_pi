##---------------------------------------------------------------------------
## Author:      SaltyPaws aka. Walbert Schulpen Omer CAKIR
## Copyright:
## License:     wxWidgets License
##---------------------------------------------------------------------------

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(circle_pi)

SET(PACKAGE_NAME circle_pi)
SET(VERBOSE_NAME circle)
SET(TITLE_NAME circle)
SET(CPACK_PACKAGE_CONTACT "Omer CAKIR")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")

#SET(CMAKE_BUILD_TYPE Debug)

INCLUDE("cmake/PluginConfigure.cmake")

SET(SRC_circle
            src/circle_pi.h
            src/circle_pi.cpp
            src/icons.h
            src/icons.cpp
	    src/circlegui.h
	    src/circlegui.cpp
	    src/circlegui_impl.cpp
	    src/circlegui_impl.h
	    src/NavFunc.h
	    src/NavFunc.cpp
	)

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_circle} )

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
