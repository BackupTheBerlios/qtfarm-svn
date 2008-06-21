This readme will be translated later on.

Dieses Projekt basiert auf C++ und Qt 4.4. Zus�tzlich wird wwWidgets ben�tigt.

-------------------------------
- Wie erzeuge ich das Makefile?
-------------------------------

[MAC_OS_X]
Einfaches Makefile:	qmake -makefile -spec macx-g++ <QtConfig.pro>
Xcode-Makefile:		qmake -makefile -o Makefile <QtConfig.pro>
Xcode-Project:		qmake <QtConfig.pro>

[Andere Systeme]
Einfaches makefile:	qmake -makefile -o Makefile <QtConfig.pro>

[Windows]
Hier gibt es die M�glichkeit Visual Studio Projekte anzulegen.
Entsprechend die "Spec" angeben.


-------------------------------
- Wo bekomm ich wwWidgets her?
-------------------------------

[Webseite] http://www.wysota.eu.org/wwwidgets

[Installation]
Wie in der Anleitung "qmake", "make" und "install" ausf�hren.


-------------------------------
- !! HINWEISE !!
-------------------------------

Solltest du dich an diesem Projekt beteiligen, m�ssen einige Regeln beachtet werden:
-  Als Zeichenkodierung wird (UTF-8, ISO 8859-1, ... (wird noch festgelegt) ) verwendet.
-  Make it as simple as possible but not simpler. 
   Das hei�t also: Alle SVN-Kommentare kurz & pr�gnant.
- ALLE �nderungen, die eingecheckt werden, m�ssen dokumentiert werden!!