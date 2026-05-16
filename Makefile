CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
LIBS = -lmysqlcppconn

all:
	$(CXX) $(CXXFLAGS) src/*.cpp -o galaxy $(LIBS)
	@echo "Done! Run the app with: ./galaxy"

clean:
	rm -f galaxy
	@echo "Program deleted."