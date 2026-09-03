CXX = g++

CXXFLAGS = -I/opt/homebrew/opt/glfw/include \
           -DGL_SILENCE_DEPRECATION

LDFLAGS = -L/opt/homebrew/opt/glfw/lib \
          -lglfw \
          -framework OpenGL \
          -framework Cocoa \
          -framework IOKit \
          -framework CoreVideo

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@.out $(LDFLAGS)