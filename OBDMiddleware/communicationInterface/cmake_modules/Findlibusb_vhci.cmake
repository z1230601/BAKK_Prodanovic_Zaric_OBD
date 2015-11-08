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
	  libusb_vhci
  )

  find_library(LIBUSB_VHCI_LIBRARY
    NAMES
      usb_vhci 
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
      message(STATUS "Found libusb_vhci:")
	  message(STATUS " - Includes: ${LIBUSB_VHCI_INCLUDE_DIRS}")
	  message(STATUS " - Libraries: ${LIBUSB_VHCI_LIBRARIES}")
    endif (NOT LIBUSB_VHCI_FIND_QUIETLY)
  else (LIBUSB_VHCI_FOUND)
    if (LIBUSB_VHCI_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find libusb_vhci")
    endif (LIBUSB_VHCI_FIND_REQUIRED)
  endif (LIBUSB_VHCI_FOUND)

  # show the LIBUSB_VHCI_INCLUDE_DIRS and LIBUSB_VHCI_LIBRARIES variables only in the advanced view
  mark_as_advanced(LIBUSB_VHCI_INCLUDE_DIRS LIBUSB_VHCI_LIBRARIES)

endif (LIBUSB_VHCI_LIBRARIES AND LIBUSB_VHCI_INCLUDE_DIRS)
