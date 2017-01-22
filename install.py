#!/usr/bin/env python3

import os
import sys
import shutil
import platform

INSTALL_LIBRARY_DIR = "/usr/lib"
INSTALL_INCLUDE_DIR = "/usr/include/pixl/"
PIXL_SHARED_LIB = "libpixl.so"
PIXL_SOURCES = "src/pixl"

# -----------------------------------------------------------------------------
def install_lib():
	# check if include dir exsists
	if not os.path.exists(INSTALL_INCLUDE_DIR):
		os.mkdir(INSTALL_INCLUDE_DIR)

	# install header files
	for file in os.listdir(PIXL_SOURCES):
		if file.endswith(".h"):
			header = os.path.join(PIXL_SOURCES, file)
			print("Installing header:", header, "->", INSTALL_INCLUDE_DIR + file)
			shutil.copy(header, INSTALL_INCLUDE_DIR)

	# install shared library
	print("Installing library", PIXL_SHARED_LIB)
	shutil.copy(PIXL_SHARED_LIB, INSTALL_LIBRARY_DIR)

# -----------------------------------------------------------------------------
def install_tool():
	print("not implemented yet")

# -----------------------------------------------------------------------------
def print_help():
	print("Usage: install.py [lib/tool]")

# =============================================================================
# =============================================================================
if __name__ == '__main__':
	# check if linux
	if not "linux" in platform.platform().lower():
		print("Ooops, this works only for Linux for now.")
		exit()

	# check args
	args = sys.argv[1:]
	if len(args) != 1:
		print_help()
		exit()

	target = args[0]
	if target == "lib":
		install_lib()
	elif target == "tool":
		install_tool()
	else:
		print_help()