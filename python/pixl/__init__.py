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

PIXL_THREADS = 1

class Orientation(enum.Enum):
	VERTICAL = 0
	HORIZONTAL = 1


class Image:
	def __init__(self, path):
		self.width = 0
		self.height = 0
		self.__handle = 0

	def destroy():
		pass


def resize(image, width, height, num_threads = PIXL_THREADS):
	# do some bound checks
	if width <= 0 or height <= 0:
		return false

	return true


def flip(image, orientation, num_threads = PIXL_THREADS):
	pass


def test():
	libpixl.pixl_say_hello()