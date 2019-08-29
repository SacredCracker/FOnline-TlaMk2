#version 110

#ifdef VERTEX_SHADER
uniform mat4 ProjectionMatrix;

attribute vec2 InPosition;
attribute vec4 InColor;
attribute vec2 InTexCoord;
attribute vec2 InTexEggCoord;

varying vec4 Color;
varying vec2 TexCoord;
varying vec2 TexEggCoord;

void main( void )
{
	gl_Position = ProjectionMatrix * vec4( InPosition, 0.0, 1.0 );
	Color = InColor;
	TexCoord = InTexCoord;
	TexEggCoord = InTexEggCoord;
}
#endif

#ifdef FRAGMENT_SHADER
uniform sampler2D ColorMap;
uniform vec4 ColorMapSize;
uniform sampler2D EggMap;

varying vec4 Color;
varying vec2 TexCoord;
varying vec2 TexEggCoord;

const float LOG2 = 1.442695;
const float density = 0.0005;
	
uniform float TimeGame;
uniform float Time;;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec4 Screen (vec4 a, vec4 b)
{ 	
	vec4 r = 1.0 - (1.0 - a) * (1.0 - b);
	r.a = b.a;
	return r;
}

vec4 Darken (vec4 a, vec4 b)
{ 
	vec4 r = min(a, b);
	r.a = b.a;
	return r;
} 
//#InCritter::effect Ice
void main( void ) 
{
	vec4 texColor = texture2D( ColorMap, TexCoord );
	vec4 Fogcolor = vec4( 0.3, 0.3, 0.3, 1.0 );
	gl_FragColor = mix( Darken( Screen( texColor, Fogcolor ), Fogcolor ), texColor, 0.05 * rand( Time * TexCoord/ColorMapSize.xy ) );
	gl_FragColor.a = texColor.a * Color.a;		
}

#endif
