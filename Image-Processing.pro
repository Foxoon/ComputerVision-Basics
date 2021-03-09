QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    oPixel.cpp

HEADERS += \
    mainwindow.h \
    oConnectedComponent.h \
    oEditingFunctions \
    oFilters.h \
    oMorphFunctions.h \
    oPixel.h \
    oUtilityFunctions.h

FORMS += \
    mainwindow.ui



TRANSLATIONS += \
    Image-Processing_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH+=D:\\1-Softwares\\0-Prog-Tools\\opencv\\build\\include

LIBS+=-LD:\\1-Softwares\\0-Prog-Tools\\opencv-qt\\lib\\Debug\
-lopencv_calib3d451d\
-lopencv_core451d\
-lopencv_dnn451d\
-lopencv_features2d451d\
-lopencv_flann451d\
-lopencv_gapi451d\
-lopencv_highgui451d\
-lopencv_imgcodecs451d\
-lopencv_imgproc451d\
-lopencv_ml451d\
-lopencv_objdetect451d\
-lopencv_photo451d\
-lopencv_stitching451d\
-lopencv_ts451d\
-lopencv_video451d\
-lopencv_videoio451d

