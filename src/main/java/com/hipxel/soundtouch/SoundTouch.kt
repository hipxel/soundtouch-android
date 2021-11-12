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

import java.nio.ByteBuffer

/**
 * Wrapper class for calling SoundTouch library.
 * Methods descriptions are in native implementation (SoundTouch.cpp).
 */
class SoundTouch {
	private val _pointer: ByteBuffer

	private var released = false

	private val pointer: ByteBuffer
		get() = if (released) throw IllegalStateException() else _pointer

	init {
		if (!Loader.loadNative())
			throw IllegalStateException("native library is not loaded")

		_pointer = create() ?: throw IllegalStateException("native create failed")
	}

	fun release() {
		release(pointer)
		released = true
	}

	fun setRate(newRate: Double) {
		setRate(pointer, newRate)
	}

	fun setTempo(newTempo: Double) {
		setTempo(pointer, newTempo)
	}

	fun setRateChange(newRate: Double) {
		setRateChange(pointer, newRate)
	}

	fun setTempoChange(newTempo: Double) {
		setTempoChange(pointer, newTempo)
	}

	fun setPitch(newPitch: Double) {
		setPitch(pointer, newPitch)
	}

	fun setPitchOctaves(newPitch: Double) {
		setPitchOctaves(pointer, newPitch)
	}

	fun setPitchSemiTones(newPitch: Int) {
		setPitchSemiTonesI(pointer, newPitch)
	}

	fun setPitchSemiTones(newPitch: Double) {
		setPitchSemiTonesD(pointer, newPitch)
	}

	fun setChannels(numChannels: Int) {
		setChannels(pointer, numChannels)
	}

	fun setSampleRate(sampleRate: Int) {
		setSampleRate(pointer, sampleRate)
	}

	fun getInputOutputSampleRatio(): Double {
		return getInputOutputSampleRatio(pointer)
	}

	fun flush() {
		flush(pointer)
	}

	fun putSamples(bytes: ByteArray, offsetBytes: Int, numSamples: Int) {
		putSamples(pointer, bytes, offsetBytes, numSamples)
	}

	fun receiveSamples(bytes: ByteArray, offsetBytes: Int, maxSamples: Int): Int {
		return receiveSamplesBII(pointer, bytes, offsetBytes, maxSamples)
	}

	fun receiveSamples(maxSamples: Int): Int {
		return receiveSamplesBI(pointer, maxSamples)
	}

	fun clear() {
		clear(pointer)
	}

	fun setSetting(setting: Setting, value: Int): Boolean {
		return setSetting(pointer, setting.value, value)
	}

	fun setTDStretchParameters(sampleRate: Int, sequenceMs: Int, seekWindowMs: Int, overlapMs: Int) {
		setTDStretchParameters(pointer, sampleRate, sequenceMs, seekWindowMs, overlapMs)
	}

	fun getSetting(setting: Setting): Int {
		return getSetting(pointer, setting.value)
	}

	fun numUnprocessedSamples(): Int {
		return numUnprocessedSamples(pointer)
	}

	fun numSamples(): Int {
		return numSamples(pointer)
	}

	fun numChannels(): Int {
		return numChannels(pointer)
	}

	private external fun create(): ByteBuffer?

	private external fun release(pointer: ByteBuffer)

	private external fun setRate(pointer: ByteBuffer, newRate: Double)

	private external fun setTempo(pointer: ByteBuffer, newTempo: Double)

	private external fun setRateChange(pointer: ByteBuffer, newRate: Double)

	private external fun setTempoChange(pointer: ByteBuffer, newTempo: Double)

	private external fun setPitch(pointer: ByteBuffer, newPitch: Double)

	private external fun setPitchOctaves(pointer: ByteBuffer, newPitch: Double)

	private external fun setPitchSemiTonesI(pointer: ByteBuffer, newPitch: Int)

	private external fun setPitchSemiTonesD(pointer: ByteBuffer, newPitch: Double)

	private external fun setChannels(pointer: ByteBuffer, numChannels: Int)

	private external fun setSampleRate(pointer: ByteBuffer, sampleRate: Int)

	private external fun getInputOutputSampleRatio(pointer: ByteBuffer): Double

	private external fun flush(pointer: ByteBuffer)

	private external fun putSamples(pointer: ByteBuffer, bytes: ByteArray, offsetBytes: Int, numSamples: Int)

	private external fun receiveSamplesBII(pointer: ByteBuffer, bytes: ByteArray, offsetBytes: Int, maxSamples: Int): Int

	private external fun receiveSamplesBI(pointer: ByteBuffer, maxSamples: Int): Int

	private external fun clear(pointer: ByteBuffer)

	private external fun setSetting(pointer: ByteBuffer, settingId: Int, value: Int): Boolean

	private external fun setTDStretchParameters(pointer: ByteBuffer, sampleRate: Int, sequenceMs: Int, seekWindowMs: Int, overlapMs: Int)

	private external fun getSetting(pointer: ByteBuffer, settingId: Int): Int

	private external fun numUnprocessedSamples(pointer: ByteBuffer): Int

	private external fun numSamples(pointer: ByteBuffer): Int

	private external fun numChannels(pointer: ByteBuffer): Int

	private object Loader {
		private val loaded by lazy {
			try {
				System.loadLibrary("HipxelSoundTouch")
				true
			} catch (t: Throwable) {
				t.printStackTrace()
				false
			}
		}

		fun loadNative(): Boolean {
			return loaded
		}
	}
}