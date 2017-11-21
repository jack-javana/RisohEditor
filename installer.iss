; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{AF7494D1-406F-4D04-A8FE-8F9DAB97F611}
AppName=RisohEditor
AppVerName=RisohEditor 1.5
AppPublisher=Katayama Hirofumi MZ
AppPublisherURL=http://katahiromz.web.fc2.com/
AppSupportURL=http://katahiromz.web.fc2.com/
AppUpdatesURL=http://katahiromz.web.fc2.com/
DefaultDirName=C:\RisohEditor
DefaultGroupName=RisohEditor
AllowNoIcons=yes
LicenseFile=LICENSE.txt
OutputDir=.
OutputBaseFilename=risoheditor-1.5-setup
SetupIconFile=src\res\RisohEditor.ico
Compression=lzma
SolidCompression=yes
UninstallDisplayIcon={app}\RisohEditor.exe
VersionInfoCompany=Katayama Hirofumi MZ
VersionInfoCopyright=Copyright (C) 2017 Katayama Hirofumi MZ.
VersionInfoDescription=Win32API Resource Editor
VersionInfoProductName=RisohEditor
VersionInfoProductTextVersion=1.5
VersionInfoProductVersion=1.5
VersionInfoVersion=1.5

[Languages]
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "README.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "READMEJP.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "LICENSE.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\RisohEditor.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "src\resource.h"; DestDir: "{app}"; Flags: ignoreversion
Source: "data\Constants.txt"; DestDir: "{app}\data"; Flags: ignoreversion
Source: "data\bin\cpp.exe"; DestDir: "{app}\data\bin"; Flags: ignoreversion
Source: "data\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}\data\bin"; Flags: ignoreversion
Source: "data\bin\libgmp-10.dll"; DestDir: "{app}\data\bin"; Flags: ignoreversion
Source: "data\bin\libwinpthread-1.dll"; DestDir: "{app}\data\bin"; Flags: ignoreversion
Source: "data\bin\windres.exe"; DestDir: "{app}\data\bin"; Flags: ignoreversion
Source: "data\bin\zlib1.dll"; DestDir: "{app}\data\bin"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\cc1.exe"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\libgcc_s_dw2-1.dll"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\libgmp-10.dll"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\libwinpthread-1.dll"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\zlib1.dll"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\include\commctrl.h"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0\include"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\include\dlgs.h"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0\include"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\include\windows.h"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0\include"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\include\winnt.h"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0\include"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\include\winresrc.h"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0\include"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\include\winuser.h"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0\include"; Flags: ignoreversion
Source: "data\lib\gcc\i686-w64-mingw32\7.1.0\include\winver.h"; DestDir: "{app}\data\lib\gcc\i686-w64-mingw32\7.1.0\include"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\RisohEditor"; Filename: "{app}\RisohEditor.exe"
Name: "{group}\README.txt"; Filename: "{app}\README.txt"
Name: "{group}\READMEJP.txt"; Filename: "{app}\READMEJP.txt"
Name: "{group}\LICENSE.txt"; Filename: "{app}\LICENSE.txt"
Name: "{group}\{cm:ProgramOnTheWeb,RisohEditor}"; Filename: "http://katahiromz.web.fc2.com"
Name: "{group}\{cm:UninstallProgram,RisohEditor}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\RisohEditor 1.5"; Filename: "{app}\RisohEditor.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\RisohEditor.exe"; Description: "{cm:LaunchProgram,RisohEditor}"; Flags: nowait postinstall skipifsilent
