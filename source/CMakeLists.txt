add_executable(q3plot
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    q3plot.cpp
    q3plot.ui
    q3plotviewport.cpp
    q3plotframe.cpp
    q3plotview.cpp
    q3plotscene.cpp
    q3plotitem.cpp
)

qt5_use_modules(q3plot Widgets)
