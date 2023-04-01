CC=g++
STD=-std=c++11
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) utrip.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: UTRIP/handlers.cpp UTRIP/handlers.hpp UTRIP/Functions.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c UTRIP/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/main.o: UTRIP/main.cpp UTRIP/handlers.cpp UTRIP/handlers.hpp UTRIP/Utrip.cpp UTRIP/Utrip.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c UTRIP/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Utrip.o: UTRIP/Utrip.cpp UTRIP/Utrip.hpp UTRIP/Functions.hpp UTRIP/StructsAndDefines.hpp UTRIP/Room.hpp UTRIP/Hotel.hpp UTRIP/Reserve.hpp UTRIP/Rating.hpp UTRIP/Sort.hpp
	$(CC) $(CF) -c UTRIP/Utrip.cpp -o $(BUILD_DIR)/Utrip.o

$(BUILD_DIR)/Room.o: UTRIP/Room.cpp UTRIP/Room.hpp UTRIP/StructsAndDefines.hpp
	$(CC) $(CF) -c UTRIP/Room.cpp -o $(BUILD_DIR)/Room.o

$(BUILD_DIR)/StructsAndDefines.o: UTRIP/StructsAndDefines.cpp UTRIP/StructsAndDefines.hpp UTRIP/Rating.hpp
	$(CC) $(CF) -c UTRIP/StructsAndDefines.cpp -o $(BUILD_DIR)/StructsAndDefines.o

$(BUILD_DIR)/Reserve.o: UTRIP/Reserve.cpp UTRIP/Reserve.hpp UTRIP/StructsAndDefines.hpp UTRIP/Room.hpp
	$(CC) $(CF) -c UTRIP/Reserve.cpp -o $(BUILD_DIR)/Reserve.o

$(BUILD_DIR)/Hotel.o: UTRIP/Hotel.cpp UTRIP/Hotel.hpp UTRIP/Reserve.hpp UTRIP/Room.hpp UTRIP/StructsAndDefines.hpp UTRIP/User.hpp
	$(CC) $(CF) -c UTRIP/Hotel.cpp -o $(BUILD_DIR)/Hotel.o

$(BUILD_DIR)/Filter.o: UTRIP/Filter.hpp UTRIP/Filter.cpp UTRIP/Hotel.hpp UTRIP/StructsAndDefines.hpp
	$(CC) $(CF) -c UTRIP/Filter.cpp -o $(BUILD_DIR)/Filter.o

$(BUILD_DIR)/User.o: UTRIP/User.cpp UTRIP/User.hpp UTRIP/Filter.hpp UTRIP/StructsAndDefines.hpp UTRIP/Reserve.hpp UTRIP/Functions.hpp
	$(CC) $(CF) -c UTRIP/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Functions.o: UTRIP/Functions.cpp UTRIP/Functions.hpp UTRIP/Hotel.hpp UTRIP/StructsAndDefines.hpp
	$(CC) $(CF) -c UTRIP/Functions.cpp -o $(BUILD_DIR)/Functions.o

$(BUILD_DIR)/CVSReader.o: UTRIP/CVSReader.cpp UTRIP/CVSReader.hpp UTRIP/StructsAndDefines.hpp UTRIP/Room.hpp UTRIP/Hotel.hpp
	$(CC) $(CF) -c UTRIP/CVSReader.cpp -o $(BUILD_DIR)/CVSReader.o

$(BUILD_DIR)/Rating.o: UTRIP/Rating.cpp UTRIP/Rating.hpp UTRIP/Functions.hpp UTRIP/StructsAndDefines.hpp
	$(CC) $(CF) -c UTRIP/Rating.cpp -o $(BUILD_DIR)/Rating.o

$(BUILD_DIR)/Sort.o: UTRIP/Sort.cpp UTRIP/Sort.hpp UTRIP/User.hpp UTRIP/Hotel.hpp UTRIP/StructsAndDefines.hpp
	$(CC) $(CF) -c UTRIP/Sort.cpp -o $(BUILD_DIR)/Sort.o

utrip.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/Utrip.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Sort.o $(BUILD_DIR)/Rating.o $(BUILD_DIR)/CVSReader.o $(BUILD_DIR)/Functions.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/Reserve.o $(BUILD_DIR)/StructsAndDefines.o
	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/Utrip.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Sort.o $(BUILD_DIR)/Rating.o $(BUILD_DIR)/CVSReader.o $(BUILD_DIR)/Functions.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/Reserve.o $(BUILD_DIR)/StructsAndDefines.o  -o utrip.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
