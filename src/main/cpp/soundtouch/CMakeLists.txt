#
# Copyright (C) 2020 Janusz Jankowski
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

cmake_minimum_required(VERSION 3.4.1)

set(ST_SOURCES
	AAFilter.cpp
	AndroidSTLNone.cpp
	cpu_detect_x86.cpp
	FIFOSampleBuffer.cpp
	FIRFilter.cpp
	InterpolateCubic.cpp
	InterpolateLinear.cpp
	InterpolateShannon.cpp
	mmx_optimized.cpp
	RateTransposer.cpp
	SoundTouch.cpp
	sse_optimized.cpp
	TDStretch.cpp
	)

add_library(SoundTouch STATIC ${ST_SOURCES})

set_property(TARGET SoundTouch PROPERTY CXX_STANDARD 98)
set_property(TARGET SoundTouch PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(SoundTouch PUBLIC include)

target_compile_definitions(SoundTouch PUBLIC
	ST_NO_EXCEPTION_HANDLING=1
	SOUNDTOUCH_INTEGER_SAMPLES=1
	SOUNDTOUCH_DISABLE_X86_OPTIMIZATIONS=1
	USE_MULTICH_ALWAYS=1
	ST_STL_NONE=1
	ST_JNI_EXTRA_METHODS=1
	)

target_compile_options(SoundTouch PRIVATE
	-fno-rtti
	-fno-exceptions
	-fvisibility=hidden
	-Ofast
	)
