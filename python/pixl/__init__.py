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

import enum
import ctypes

libpixl = ctypes.cdll.LoadLibrary('libpixl.so')

class IMAGE(ctypes.Structure):
	_fields_ = [('width', ctypes.c_uint),
				('height', ctypes.c_uint),
				('__handle', ctypes.c_void_p)]

libpixl.pixl_load_image.argtypes = [ctypes.c_char_p]
libpixl.pixl_load_image.restype = ctypes.POINTER(IMAGE)

PIXL_THREADS = 1

class Orientation(enum.Enum):
	VERTICAL = 0
	HORIZONTAL = 1

class Image():
	def __init__(self, path):
		self.__IMAGE = libpixl.pixl_load_image(ctypes.c_char_p(path.encode()))

	def destroy(self):
		libpixl.pixl_destroy_image(self.__IMAGE)

	def width(self):
		return self.__IMAGE.contents.width

	def height(self):
		return self.__IMAGE.contents.height

def test():
	libpixl.pixl_say_hello()