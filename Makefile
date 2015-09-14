all: driver.cpp hash3.cpp graph.cpp
	g++ driver.cpp -o driver hash3.cpp graph.cpp
	g++ shortestPathTest.cpp -o shortestPathTest -lrt graph.cpp
	g++ MCSTbfsTest.cpp -o MCSTbfsTest -lrt graph.cpp
	g++ MCSTdfsTest.cpp -o MCSTdfsTest -lrt graph.cpp
