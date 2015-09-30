# - Try to find libusb-1.0
# Once done this will define
#
#  LIBUSB_VHCI_FOUND - system has libusb
#  LIBUSB_VHCI_INCLUDE_DIRS - the libusb include directory
#  LIBUSB_VHCI_LIBRARIES - Link these to use libusb
#  LIBUSB_VHCI_DEFINITIONS - Compiler switches required for using libusb
#
#  Adapted from cmake-modules Google Code project
#
#  Copyright (c) 2006 Andreas Schneider <mail@cynapses.org>
#
#  (Changes for libusb) Copyright (c) 2008 Kyle Machulis <kyle@nonpolynomial.com>
#
# Redistribution and use is allowed according to the terms of the New BSD license.
#
# CMake-Modules Project New BSD License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
#
# * Neither the name of the CMake-Modules Project nor the names of its
#   contributors may be used to endorse or promote products derived from this
#   software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#


if (LIBUSB_VHCI_LIBRARIES AND LIBUSB_VHCI_INCLUDE_DIRS)
  # in cache already
  set(LIBUSB_FOUND TRUE)
else (LIBUSB_VHCI_LIBRARIES AND LIBUSB_VHCI_INCLUDE_DIRS)
  find_path(LIBUSB_VHCI_INCLUDE_DIR
    NAMES
	libusb_vhci.h
    PATHS
      /usr/include
      /usr/local/include
      /opt/local/include
      /sw/include
	PATH_SUFFIXES
	  libusb-vhci
  )

  find_library(LIBUSB_VHCI_LIBRARY
    NAMES
      usb-vhci usb
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
  )

  set(LIBUSB_VHCI_INCLUDE_DIRS
    ${LIBUSB_VHCI_INCLUDE_DIR}
  )
  set(LIBUSB_VHCI_LIBRARIES
    ${LIBUSB_VHCI_LIBRARY}
)

  if (LIBUSB_VHCI_INCLUDE_DIRS AND LIBUSB_VHCI_LIBRARIES)
     set(LIBUSB_VHCI_FOUND TRUE)
  endif (LIBUSB_VHCI_INCLUDE_DIRS AND LIBUSB_VHCI_LIBRARIES)

  if (LIBUSB_VHCI_FOUND)
    if (NOT LIBUSB_VHCI_FIND_QUIETLY)
      message(STATUS "Found libusb-1.0:")
	  message(STATUS " - Includes: ${LIBUSB_VHCI_INCLUDE_DIRS}")
	  message(STATUS " - Libraries: ${LIBUSB_VHCI_LIBRARIES}")
    endif (NOT LIBUSB_VHCI_FIND_QUIETLY)
  else (LIBUSB_VHCI_FOUND)
    if (LIBUSB_VHCI_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find libusb")
    endif (LIBUSB_VHCI_FIND_REQUIRED)
  endif (LIBUSB_VHCI_FOUND)

  # show the LIBUSB_VHCI_INCLUDE_DIRS and LIBUSB_VHCI_LIBRARIES variables only in the advanced view
  mark_as_advanced(LIBUSB_VHCI_INCLUDE_DIRS LIBUSB_VHCI_LIBRARIES)

endif (LIBUSB_VHCI_LIBRARIES AND LIBUSB_VHCI_INCLUDE_DIRS)
