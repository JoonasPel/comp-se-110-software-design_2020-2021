Group Unnamed
Assignment repository
==================================
Project is located inside 'COMPSE110_Unnamed_Group_Project' folder, 'Downloader' folder is redundant.

Open project file COMPSE110_Unnamed_Group_Project.pro and compile using eg. QtCreator and qmake/MinGW. 
**Required additional Qt libraries: QtCharts, Qt Network Authorization, Qt WebEngine**

------------------
File structure:
- main.cpp, contains 
- controller.h/.cpp, contains Controller class for software to handle user requests.
- model.h/.cpp, contains Model class to save and modify downloaded data for display.
- DownLoader.h/.cpp, contains DownLoader class that handles data downloads from internet sources.


- main.qml, contains qml application layout.
- ChartElement.qml, contains definition for View displaying graphs, based on QML ChartView
- GraphCheckBox.qml, contains definition for checkbox element used to control displayed graphs based on QML CheckBox.
- ControlRow.qml, contains definition for row element containing controllers for fetching data, based on QML Row.




