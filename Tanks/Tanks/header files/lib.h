#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "ShaderMaker.h"
#include "geometry.h"
#include "VAO_manager.h"
#include "shape_reader.h"
#include "hermite.h"
#include "entities.h"
 
using namespace glm;
using namespace std;