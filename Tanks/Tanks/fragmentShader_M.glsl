#version 330 core
in vec4 color;
out vec4 fragColor;

uniform vec2 resolution;
uniform int background;
uniform vec3 color1;
uniform vec3 color2;
uniform float time;

bool isInRectangle(float left, float right, float bottom, float top, float thickness, float x, float y)
{
	bool result = true;
	float animationValue = thickness;
	if (!(x > left - cos(time) * animationValue - thickness && x < right + cos(time) * animationValue + thickness))
		result = false;
	if (!(y > bottom - cos(time) * animationValue - thickness && y < top + cos(time) * animationValue + thickness))
		result = false;
	if (result && (x > left && x < right) && (y > bottom && y < top))
		result = false;
	return result;
}
   
void main()
{
	float numberOfStripes = 40.0f;
	if (background == 0)
		fragColor = color;
	else
	{
		vec2 ndc = vec2 ((gl_FragCoord.x / resolution.x- 0.5) * 2, (gl_FragCoord.y / resolution.y - 0.5) * 2);
		float step = 1 / numberOfStripes;
		for (int i = 0; i < numberOfStripes; i+=2)
		{
			if (isInRectangle(-i * step, i * step, -i * step, i * step, step, ndc.x, ndc.y))
			{
				fragColor = vec4(color1, 1.0f);
				break;
			}
			else
				fragColor = vec4(color2, 1.0f);
		}
	}
}