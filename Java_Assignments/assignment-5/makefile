# Find all Java source files and list them in sources.txt
connect:
	find -name "*.java" > sources.txt

# Compile all Java files listed in sources.txt, output to build directory
build:
	javac -d build @sources.txt

# Run the main class with optional arguments, log errors to errors.log
run:
	java -cp build Main.Main $(ARGS) 2>errors.log

# Delete build directory and sources.txt
delete:
	rm -rf build sources.txt

# Clean build directory, all .class files, and sources.txt
clean:
	rm -rf build
	rm -f *.class
	rm -f sources.txt

# Clean, then find sources, then build everything
all: clean connect build

# Usage:
# make run ARGS="configuration.txt"
