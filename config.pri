CONFIG(debug , debug|release) {
   DESTDIR=../../debug

} else {
    DESTDIR=../../release
}

CONFIG += c++11
BUILD = DYNAMIC
INCP = ..
