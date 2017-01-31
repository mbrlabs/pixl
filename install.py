#!/usr/bin/env python3

#
# Copyright (c) 2017 Marcus Brummer.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#


# This script installs libpixl and various other things.
# Usage: ./install [lib|py|tool] 
# 
# lib:
# Installs all headers and the shared library to common paths on a unix system.
# Must be run as sudo.
# 
# py:
# Installs the python bindings for the current user using pip
#
# tool:
# TODO
# 
# Note, that this script does not build anything. This has to be done by hand before 
# executing this script.

import os
import sys
import shutil
import platform
import subprocess

INSTALL_LIBRARY_DIR = '/usr/lib'
INSTALL_INCLUDE_DIR = '/usr/include/pixl/'
PIXL_SHARED_LIB = 'libpixl.so'
PIXL_SOURCES = 'src/pixl'
PYTHON_PACKAGE = 'python/'

# -----------------------------------------------------------------------------
def install_lib():
	# check if include dir exsists
	if not os.path.exists(INSTALL_INCLUDE_DIR):
		os.mkdir(INSTALL_INCLUDE_DIR)

	# install header files
	for file in os.listdir(PIXL_SOURCES):
		if file.endswith('.h'):
			header = os.path.join(PIXL_SOURCES, file)
			print('Installing header:', header, '->', INSTALL_INCLUDE_DIR + file)
			shutil.copy(header, INSTALL_INCLUDE_DIR)

	# install shared library
	print('Installing library', PIXL_SHARED_LIB)
	shutil.copy(PIXL_SHARED_LIB, INSTALL_LIBRARY_DIR)

# -----------------------------------------------------------------------------
def uninstall_lib():
	# delete headers
	if os.path.exists(INSTALL_INCLUDE_DIR):
		shutil.rmtree(INSTALL_INCLUDE_DIR)

	# delete lib
	lib = os.path.join(INSTALL_LIBRARY_DIR, PIXL_SHARED_LIB)
	if os.path.exists(lib):
		os.remove(lib)

# -----------------------------------------------------------------------------
def install_tool():
	print('not implemented yet')

# -----------------------------------------------------------------------------
def install_py_lib():
	subprocess.call(['pip3', 'install', '--user', '--upgrade', PYTHON_PACKAGE])

# -----------------------------------------------------------------------------
def print_help():
	print('Usage: install.py [lib|py|tool]')


# =============================================================================
# =============================================================================
if __name__ == '__main__':
	# check if linux
	if not 'linux' in platform.platform().lower():
		print('Ooops, this works only for Linux.')
		exit()

	# check args
	args = sys.argv[1:]
	if len(args) != 1:
		print_help()
		exit()

	target = args[0]
	if target == 'lib':
		install_lib()
	elif target == 'tool':
		install_tool()
	elif target == 'py':
		install_py_lib()
	else:
		print_help()