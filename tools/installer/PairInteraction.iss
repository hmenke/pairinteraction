#define MyAppName "PairInteraction"

#ifndef MyAppVersion
  #define MyAppVersion "0.0.0"
#endif

#ifndef MyAppSourceDir
  #error MyAppSourceDir is not defined
#endif

#ifndef MyAppOutputDir
  #error MyAppOutputDir is not defined
#endif

[Setup]
AppId=org.pairinteraction.PairInteraction
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher=PairInteraction Developers
DefaultDirName={localappdata}\Programs\{#MyAppName}
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
OutputDir={#MyAppOutputDir}
OutputBaseFilename=PairInteraction-{#MyAppVersion}-windows-x86_64-Setup
Compression=lzma2
SolidCompression=yes
WizardStyle=modern
PrivilegesRequired=lowest
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
UninstallDisplayIcon={app}\PairInteraction.exe

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "Create a desktop shortcut"; GroupDescription: "Additional icons:"

[Files]
Source: "{#MyAppSourceDir}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\PairInteraction.exe"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\PairInteraction.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\PairInteraction.exe"; Description: "Launch {#MyAppName}"; Flags: nowait postinstall skipifsilent
