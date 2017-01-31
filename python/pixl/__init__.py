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

"""

TODO package docstring

"""

import enum
from ctypes import *

# load the shared library
_LIBPIXL = cdll.LoadLibrary('libpixl.so')

class IMAGE(Structure):
	_fields_ = [('width', c_uint),
				('height', c_uint),
				('__handle', c_void_p)]

# extern c: pixl_load_image
_LIBPIXL.pixl_load_image.argtypes = [c_char_p]
_LIBPIXL.pixl_load_image.restype = POINTER(IMAGE)

# extern c: pixl_save_image
_LIBPIXL.pixl_save_image.argtypes = [POINTER(IMAGE), c_char_p, c_int]

#extern c: pixl_flip
_LIBPIXL.pixl_flip.argtypes = [POINTER(IMAGE), c_int]

#extern c: pixl_resize
_LIBPIXL.pixl_resize.argtypes = [POINTER(IMAGE), c_uint, c_uint, c_int]

class Orientation(enum.Enum):
	VERTICAL = 0
	HORIZONTAL = 1

class ResizeMethod(enum.Enum):
	NEAREST = 0
	BILINEAR = 1

class Image():
	def __init__(self, path):
		self._IMAGE = _LIBPIXL.pixl_load_image(c_char_p(path.encode()))

	def destroy(self):
		_LIBPIXL.pixl_destroy_image(self._IMAGE)

	def width(self):
		return self._IMAGE.contents.width

	def height(self):
		return self._IMAGE.contents.height


def flip(image, orientation = Orientation.HORIZONTAL):
	_LIBPIXL.pixl_flip(image._IMAGE, orientation.value)

def resize(image, width, height, method=ResizeMethod.NEAREST):
	_LIBPIXL.pixl_resize(image._IMAGE, int(width), int(height), method.value)

def save_image(path, image, quality=75):
	_LIBPIXL.pixl_save_image(image._IMAGE, c_char_p(path.encode()), quality)