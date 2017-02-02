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

# What is this?
# Various tests go in here
#

import pixl
import PIL
import time
from PIL import Image

def pillow():
	IN 	= '../images/bird.jpg'
	PIXL_OUT = '../bin/bird_scl_pixl.jpg'
	PILLOW_OUT = '../bin/bird_scl_pillow.jpg'

	TARGET_WIDTH = 500
	TARGET_HEIGHT = 333

	# pixl
	start = time.time()
	image = pixl.Image(IN)
	#image.resize(TARGET_WIDTH, TARGET_HEIGHT, pixl.ResizeMethod.BILINEAR)
	image.convolution([0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0], 1.0).invert().grayscale()
	
	image.save(PIXL_OUT)
	print('pixl:', time.time()-start, "s")

	# pillow
	start = time.time()
	image = Image.open(IN)
	image = image.resize((TARGET_WIDTH, TARGET_HEIGHT), PIL.Image.BILINEAR)
	image.save(PILLOW_OUT)
	print('pillow:', time.time()-start, "s")


if __name__ == '__main__':
	pillow()