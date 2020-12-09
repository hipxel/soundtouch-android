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

#include <SoundTouch.h>

#include <jni.h>

using namespace soundtouch;

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
	return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_hipxel_soundtouch_SoundTouch_create(JNIEnv *env, jobject thiz) {
	SoundTouch *st = new SoundTouch();
	return env->NewDirectByteBuffer(static_cast<void *>(st), sizeof(st));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_release(JNIEnv *env, jobject thiz, jobject pointer) {
	SoundTouch *st = static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer));
	delete st;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setRate(JNIEnv *env, jobject thiz, jobject pointer,
                                              jdouble newRate) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setRate(newRate);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setTempo(JNIEnv *env, jobject thiz, jobject pointer,
                                               jdouble newTempo) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setTempo(newTempo);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setRateChange(JNIEnv *env, jobject thiz, jobject pointer,
                                                    jdouble newRate) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setRateChange(newRate);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setTempoChange(JNIEnv *env, jobject thiz, jobject pointer,
                                                     jdouble newTempo) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setTempoChange(newTempo);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setPitch(JNIEnv *env, jobject thiz, jobject pointer,
                                               jdouble newPitch) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setPitch(newPitch);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setPitchOctaves(JNIEnv *env, jobject thiz, jobject pointer,
                                                      jdouble newPitch) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setPitchOctaves(newPitch);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setPitchSemiTonesI(JNIEnv *env, jobject thiz, jobject pointer,
                                                         jint newPitch) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setPitchSemiTones(newPitch);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setPitchSemiTonesD(JNIEnv *env, jobject thiz, jobject pointer,
                                                         jdouble newPitch) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setPitchSemiTones(newPitch);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setChannels(JNIEnv *env, jobject thiz, jobject pointer,
                                                  jint numChannels) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setChannels(numChannels);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setSampleRate(JNIEnv *env, jobject thiz, jobject pointer,
                                                    jint sampleRate) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setSampleRate(sampleRate);
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_hipxel_soundtouch_SoundTouch_getInputOutputSampleRatio(JNIEnv *env, jobject thiz,
                                                                jobject pointer) {
	return static_cast<SoundTouch *>(env->GetDirectBufferAddress(
			pointer))->getInputOutputSampleRatio();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_flush(JNIEnv *env, jobject thiz, jobject pointer) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->flush();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_putSamples(JNIEnv *env, jobject thiz, jobject pointer,
                                                 jbyteArray bytes, jint offsetBytes,
                                                 jint numSamples) {
	if (numSamples <= 0)
		return;

	jbyte *jniBuffer = env->GetByteArrayElements(bytes, 0);

	jbyte *offsetJniBuffer = jniBuffer + offsetBytes;

	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->putSamples(
			(SAMPLETYPE *) offsetJniBuffer, numSamples);

	env->ReleaseByteArrayElements(bytes, jniBuffer, 0);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_hipxel_soundtouch_SoundTouch_receiveSamplesBII(JNIEnv *env, jobject thiz, jobject pointer,
                                                        jbyteArray bytes, jint offsetBytes,
                                                        jint maxSamples) {
	jbyte *jniBuffer = env->GetByteArrayElements(bytes, 0);

	jbyte *offsetJniBuffer = jniBuffer + offsetBytes;

	jint ret = static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->receiveSamples(
			(SAMPLETYPE *) offsetJniBuffer, maxSamples);

	env->ReleaseByteArrayElements(bytes, jniBuffer, 0);

	return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_hipxel_soundtouch_SoundTouch_receiveSamplesBI(JNIEnv *env, jobject thiz, jobject pointer,
                                                       jint maxSamples) {
	return static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->receiveSamples(
			maxSamples);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hipxel_soundtouch_SoundTouch_clear(JNIEnv *env, jobject thiz, jobject pointer) {
	static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->clear();
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_hipxel_soundtouch_SoundTouch_setSetting(JNIEnv *env, jobject thiz, jobject pointer,
                                                 jint settingId, jint value) {
	return (jboolean) static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->setSetting(
			settingId, value);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_hipxel_soundtouch_SoundTouch_getSetting(JNIEnv *env, jobject thiz, jobject pointer,
                                                 jint settingId) {
	return static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->getSetting(settingId);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_hipxel_soundtouch_SoundTouch_numUnprocessedSamples(JNIEnv *env, jobject thiz,
                                                            jobject pointer) {
	return static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->numUnprocessedSamples();
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_hipxel_soundtouch_SoundTouch_numSamples(JNIEnv *env, jobject thiz, jobject pointer) {
	return static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->numSamples();
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_hipxel_soundtouch_SoundTouch_numChannels(JNIEnv *env, jobject thiz, jobject pointer) {
	return static_cast<SoundTouch *>(env->GetDirectBufferAddress(pointer))->numChannels();
}
