CFLAGS = -std=c++11 -g
LDFLAGS = -lvulkan -lglfw -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

vulkan_test: test.cpp vklglm.o vklglfw.o vklvk.o
	g++ $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
vklglm.o: vklglm.cpp vklglm.h
	g++ $(CFLAGS) -c -o $@ $<

vklglfw.o: vklglfw.cpp vklglfw.h
	g++ $(CFLAGS) -c -o $@ $<

vklvk.o: vklvk.cpp vklvk.h
	g++ $(CFLAGS) -c -o $@ $<

.PHONY: test clean

test: vulkan_test
	./vulkan_test

clean:
	rm -f vulkan_test *.o
