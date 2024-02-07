QT += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Game/client.cpp \
    Game/game.cpp \
    LoginClasses/forgotpassword.cpp \
    LoginClasses/login.cpp \
    LoginClasses/signup.cpp \
    Menu/menu.cpp \
    MyClasses/card.cpp \
    MyClasses/deck.cpp \
    MyClasses/king.cpp \
    MyClasses/my_exception.cpp \
    main.cpp

HEADERS += \
    Game/client.h \
    Game/game.h \
    LoginClasses/forgotpassword.h \
    LoginClasses/login.h \
    LoginClasses/signup.h \
    Menu/menu.h \
    MyClasses/card.h \
    MyClasses/deck.h \
    MyClasses/king.h \
    MyClasses/my_exception.h

FORMS += \
    Game/client.ui \
    Game/game.ui \
    LoginClasses/forgotpassword.ui \
    LoginClasses/login.ui \
    LoginClasses/signup.ui \
    Menu/menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

DISTFILES += \
    Pictures/Cards/Map1.png \
    Pictures/Cards/Map10.png \
    Pictures/Cards/Map11.png \
    Pictures/Cards/Map2.png \
    Pictures/Cards/Map3.png \
    Pictures/Cards/Map4.png \
    Pictures/Cards/Map5.png \
    Pictures/Cards/Map6.png \
    Pictures/Cards/Map7.png \
    Pictures/Cards/Map8.png \
    Pictures/Cards/Map9.png \
    Pictures/Cards/Parrot1.png \
    Pictures/Cards/Parrot10.png \
    Pictures/Cards/Parrot11.png \
    Pictures/Cards/Parrot2.png \
    Pictures/Cards/Parrot3.png \
    Pictures/Cards/Parrot4.png \
    Pictures/Cards/Parrot5.png \
    Pictures/Cards/Parrot6.png \
    Pictures/Cards/Parrot7.png \
    Pictures/Cards/Parrot8.png \
    Pictures/Cards/Parrot9.png \
    Pictures/Cards/Pirate.png \
    Pictures/Cards/PirateFlag1.png \
    Pictures/Cards/PirateFlag10.png \
    Pictures/Cards/PirateFlag11.png \
    Pictures/Cards/PirateFlag2.png \
    Pictures/Cards/PirateFlag3.png \
    Pictures/Cards/PirateFlag4.png \
    Pictures/Cards/PirateFlag5.png \
    Pictures/Cards/PirateFlag6.png \
    Pictures/Cards/PirateFlag7.png \
    Pictures/Cards/PirateFlag8.png \
    Pictures/Cards/PirateFlag9.png \
    Pictures/Cards/Queen.png \
    Pictures/Cards/SkullKing.png \
    Pictures/Cards/Treasure1.png \
    Pictures/Cards/Treasure10.png \
    Pictures/Cards/Treasure11.png \
    Pictures/Cards/Treasure12.png \
    Pictures/Cards/Treasure2.png \
    Pictures/Cards/Treasure3.png \
    Pictures/Cards/Treasure4.png \
    Pictures/Cards/Treasure5.png \
    Pictures/Cards/Treasure6.png \
    Pictures/Cards/Treasure7.png \
    Pictures/Cards/Treasure8.png \
    Pictures/Cards/Treasure9.png \
    Pictures/Game/Background.png \
    Pictures/Game/GameIcon.png \
    Pictures/Game/GameName.png \
    Pictures/Game/GameName1.png \
    Pictures/Game/SkullMark.png \
    Pictures/Game/cursor.png \
    Pictures/Game/green-grunge-texture-background_1409-1374 (1).avif \
    Pictures/Game/loginBG.jpg \
    Pictures/Game/logoutBG.jpg \
    Pictures/Game/menuBG.jpg \
    Pictures/Game/numbers.png \
    Pictures/Game/score.png \
    Pictures/Game/serverclientBG.jpg \
    Pictures/Game/skull-with-flower-design-it.jpg \
    Pictures/Game/startgameBG.jpg \
    Pictures/Icons/arrow-right-from-bracket-solid.svg \
    Pictures/Icons/clock-rotate-left-solid.svg \
    Pictures/Icons/door-open-solid.svg \
    Pictures/Icons/file-signature-solid.svg \
    Pictures/Icons/gamepad-solid.svg \
    Pictures/Icons/key-solid.svg \
    Pictures/Icons/play-solid.svg \
    Pictures/Icons/server-solid.svg \
    Pictures/Icons/stop-solid.svg \
    Pictures/Icons/tower-broadcast-solid.svg \
    Pictures/Icons/user-plus-solid.svg \
    Pictures/Icons/user-solid.svg
