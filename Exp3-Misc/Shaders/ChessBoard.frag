#version 430 core
in vec4 color;
in vec3 modelPosition;
out vec4 fColor;

layout(location = 0) uniform mat4 projectMat;
layout(location = 1) uniform mat4 modelMat;
layout(location = 2) uniform vec3 sinTime;

float get_chessBoard(vec2 pos, float scale)
{
	// 棋盘格
	// 扩大, 然后向下取整
	vec2 scaledPos = 32 * pos;
	scaledPos.x = scaledPos.x - fract(scaledPos.x);
	scaledPos.y = scaledPos.y - fract(scaledPos.y);
	// 判断 x+y 奇偶性
	float white = scaledPos.x + scaledPos.y;
	return step(fract(white/2),0);
}

void main()
{
	vec2 pos = modelPosition.xy;
	pos = pos * pos;
	float dist = sqrt(pos.x + pos.y);
	vec4 black = vec4(.2, .2, .2, 1);
	if(dist>=.5 + 0.2 * sinTime.y)
	{
		fColor = black + vec4(modelPosition,1) * get_chessBoard(modelPosition.xy, 8);
	}
	else
	{
		vec2 mutatedPos = normalize(modelPosition.xy) * (dist * dist);
		fColor = black + vec4(modelPosition,1) * get_chessBoard(mutatedPos, 8);
	}
}

