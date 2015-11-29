Full documentation is here: https://goo.gl/s4Y3pa

###How to use:
1. Clone this repository on your computer.
2. Open Visual Studio project in your Visual Studio.
3. Compile the project.
4. Follow the Instructions.

###Instructions:
#####Launch build file with this parameters:
  1. '-help' - standard help information.
  2. '-check <path_to_file>' - scan file or directory. The result of scan will be written to the log-file.
  3. '-checksys' - scan system directories. The result of scan will be written to the log-file.
  4. '-info' - show information about the program build.

###Instructions for developers:
  1. Import 'antivirus.h', 'yara.h', 'libyara32.lib' and full folder 'yara'.
  2. Include 'antivirus.h' in your code
  3. Create antivirus object
  4. Launch "YourAntivirusObject.ToScan( PATH_TO_FILE )". PATH_TO_FILE - string with path to scan file or folder. Result of scan write in std::stream::cout
