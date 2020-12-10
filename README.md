# Android binding library for SoundTouch
This library allows to use SoundTouch in real-time processing mode.
It has also few Android-specific changes for SoundTouch:
1. Reduced binary size from ~300KB to 15KB per arch -> by using only features
needed for processing of frames (no BPM/PeakFinder etc) you can get to ~80KB.
However ~60KB is wasted by the fact that NDK by default uses c++\_static STL
and doesn't remove all unused symbols. SoundTouch doesn't use C++ STL (just C),
so we can use system STL, but this one is deprecated, so it's better to use
none STL and provide ::new and ::delete operators. This way we can get down to
15KB with few minor inconveniences.
2. Added JNI variant for put/receive methods, that can reduce overhead
of calling native methods from JVM side.

## Licensing
Check LICENSE.txt.


NOTICE: I am not a lawyer and this is not legal advice.

How it should work in practice for Android project ->
Most of C++ files are LGPL-licensed and other files are Apache-licensed,
what means that ".so" file needs to satisfy LGPL requirements (f.e. provide
sources of ".so" file so user can rebuild it and replace in final product).

Because ".so" file is dynamically loaded/linked, the rest of ".apk" may keep
its license, however sources of this library have to be provided/linked
in the application, so user can, compile lib and replace it in ".apk".
