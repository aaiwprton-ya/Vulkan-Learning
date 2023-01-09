CFLAGS = -std=c++11 -g
LDFLAGS = -lvulkan -lglfw -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
path := bin
srcs := vklglm.cpp vklglfw.cpp vklvk.cpp vklvk_allocator.cpp vklvk_resource_manager.cpp
objs := $(srcs:.cpp=.o)
objs_path := $(addprefix $(path)/,$(srcs:.cpp=.o))

$(path):
	mkdir -p $@

vulkan_test: test.cpp $(objs) | $(path)
	g++ $(CFLAGS) -o $(path)/$@ $< $(objs_path) $(LDFLAGS)
	
vklglm.o: vklglm.cpp vklglm.h | $(path)
	g++ $(CFLAGS) -c -o $(path)/$@ $<

vklglfw.o: vklglfw.cpp vklglfw.h | $(path)
	g++ $(CFLAGS) -c -o $(path)/$@ $<

vklvk.o: vklvk.cpp vklvk.h vklvk_requireds.h | $(path)
	g++ $(CFLAGS) -c -o $(path)/$@ $<

vklvk_allocator.o: vklvk_allocator.cpp vklvk_allocator.h | $(path)
	g++ $(CFLAGS) -c -o $(path)/$@ $<

vklvk_resource_manager.o: vklvk_resource_manager.cpp vklvk_resource_manager.h | $(path)
	g++ $(CFLAGS) -c -o $(path)/$@ $<

.PHONY: test clean

test: vulkan_test
	./$(path)/vulkan_test

clean:
	rm -rf $(path)
