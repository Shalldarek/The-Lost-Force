CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
LIBS = -lmysqlcppconn

all:
	$(CXX) $(CXXFLAGS) src/*.cpp -o galaxy $(LIBS)
	@echo "Hotovo! Spustíš pomocí: ./galaxy"

clean:
	rm -f galaxy
	@echo "Program smazán."