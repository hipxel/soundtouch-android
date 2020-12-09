/*
 * Copyright (C) 2020 Janusz Jankowski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.hipxel.soundtouch

enum class Setting(val value: Int) {
	USE_AA_FILTER(0),
	AA_FILTER_LENGTH(1),
	USE_QUICKSEEK(2),
	SEQUENCE_MS(3),
	SEEKWINDOW_MS(4),
	OVERLAP_MS(5),
	NOMINAL_INPUT_SEQUENCE(6),
	NOMINAL_OUTPUT_SEQUENCE(7),
	INITIAL_LATENCY(8)
}