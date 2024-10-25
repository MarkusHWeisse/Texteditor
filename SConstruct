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
env = Environment(CPPPATH=r'C:\SFML\SFML-2.6.1\include');
#env.Append(CCFLAGS=["-std=c++11"]); #C:\mingw-w64\mingw64\bin    C:\TDM-GCC-64\bin
env.Append(CCFLAGS=["-fmodules-ts"]);
#env.Append(CCFLAGS=["-pipes"]);
env['ENV']['PATH'] = [r'C:\mingw64\bin']
env['CXX'] = 'g++'
env.Append(LIBS = ["sfml-graphics","sfml-window","sfml-system"]);
env.Append(LIBPATH = r"C:\SFML\SFML-2.6.1\lib");
env.Program(target = "Sovieditor.exe", source = matches)