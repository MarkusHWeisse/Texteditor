import fnmatch
import os

#Setup environment
file_match = "*.cpp"

#Recursive Glob method to find all source files
matches = []
for root, dirnames, filenames in os.walk("src/"):
    for filename in filenames:
        if fnmatch.fnmatch(filename, file_match):
            matches.append(os.path.join(root, filename))

#Compile the program
env = Environment(CPPPATH=r'C:\Users\marku\OneDrive\Dokumente\privat\SFML-2.6.1-sources\SFML-2.6.1\include');
#env.Append(CCFLAGS=["-m32"]);
env['ENV']['PATH'] = [r'C:\mingw-w64\mingw64\bin']
env['CXX'] = 'g++'
env.Append(LIBS = ["sfml-graphics","sfml-window","sfml-system"]);
env.Append(LIBPATH = r"C:\Users\marku\OneDrive\Dokumente\privat\SFML_mingw_w64\lib");
env.Program(target = "Sovieditor.exe", source = matches)