# Makefile for compiling and running the embedded system application

# Find all Java source files and save their paths to sources.txt
connect:
	find -name "*.java" > sources.txt

# Compile all Java files listed in sources.txt and output to build directory
build:
	javac -d build @sources.txt


# Run the compiled program with specified configuration file, log directory, and input file
# Standard error is redirected to errors.log
run:
# first case:
	java -cp build Main.Main  $(CONFIG_FILE) $(LOG_DIR) 2>errors.log

# second case:
# java -cp build Main.Main $(CONFIG_FILE) $(LOG_DIR) < $(INPUT) 2>errors.log


# Remove build directory and sources.txt file
delete:
	rm -rf build sources.txt

# Clean up all generated files (build directory, class files, sources.txt)
clean:
	rm -rf build
	rm -f *.class
	rm -f sources.txt

# Complete build process: clean previous build, find source files, and compile
all: clean connect build


# print to output1.txt:
# make run CONFIG_FILE=configuration.txt LOG_DIR=./logRecords <scenario1.txt> output1.txt

# print to terminal:
# make run CONFIG_FILE=configuration.txt LOG_DIR=./logRecords <scenario1.txt

# Example usage (for second case):
# make run CONFIG_FILE=configuration.txt LOG_DIR=./logRecords INPUT="scenario1.txt"

# JAVADOC:
# javadoc -d doc -sourcepath . -subpackages HWSystem