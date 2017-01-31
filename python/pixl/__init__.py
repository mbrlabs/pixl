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

Python3 bindings for the pixl image processing library.

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
		"""Loads the image, located at path."""
		self._IMAGE = _LIBPIXL.pixl_load_image(c_char_p(path.encode()))

	def destroy(self):
		""" 
		Frees the allocated memory of the native image object.
		The method must be called when the image is no longer needed. After calling this
		method, the the image object can no longer be used.
		"""
		_LIBPIXL.pixl_destroy_image(self._IMAGE)

	def width(self):
		"""Returns the width of the image."""
		return self._IMAGE.contents.width

	def height(self):
		"""Returns the height of the image."""
		return self._IMAGE.contents.height

	def flip(self, orientation = Orientation.HORIZONTAL):
		"""
		Flips the image along the provided orientation.
		Returns self for chaining.
		"""
		_LIBPIXL.pixl_flip(self._IMAGE, orientation.value)
		return self

	def resize(self, width, height, method=ResizeMethod.NEAREST):
		"""
		Resizes the image using the provided method.
		Returns self for chaining.
		"""
		_LIBPIXL.pixl_resize(self._IMAGE, int(width), int(height), method.value)
		return self

	def save(self, path, quality=75):
		"""
		Saves the image at the provided path.
		You can also specify the output quality of the image (1-100).
		"""
		_LIBPIXL.pixl_save_image(self._IMAGE, c_char_p(path.encode()), quality)