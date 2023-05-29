CXX := c++
CXXFLAGS := -g

obj :=  graph.o

Project: $(obj)
	$(CXX) $(obj) main.cpp -o cpe400
	
graph.o: graph.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c graph.cpp -o graph.o

	
.PHONY: clean
clean: 
	-rm $(obj) cpe400