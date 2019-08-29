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
uniform sampler2D EggMap;

uniform float Random1Effect;
uniform float Random2Effect;
uniform float Random3Effect;
uniform float Random1Pass;

varying vec4 Color;
varying vec2 TexCoord;
varying vec2 TexEggCoord;

uniform float TimeGame;

void main( void )
{
	vec4 texColor = texture2D( ColorMap, TexCoord );
	
	gl_FragColor.rgb = ( texColor.rgb * Color.rgb ) * 2.0;
	gl_FragColor.a = texColor.a * Color.a;
	if( TexEggCoord.x != 0.0 )
		gl_FragColor.a *= texture2D( EggMap, TexEggCoord ).a;
		
	float v = ( TexCoord.y - Color.y ) / ( Color.w - Color.y ) * 0.4 * Random3Effect;
	v += -1.0 + mod( TimeGame, 2.0 );
	if( v > 1.0 )
			v = 2.0 - v;
	else if( v < 0.0 )
		v = -v;
		
	gl_FragColor.rgb += v * 0.60 - 0.30;
	gl_FragColor.rgb = clamp( gl_FragColor.rgb, 0.0, 1.0 );
	
	if( gl_FragColor.r > 0.3 || gl_FragColor.b > 0.3 || gl_FragColor.g > 0.4 )
	{
		gl_FragColor.rgb = 1.0 - gl_FragColor.rgb;
		gl_FragColor.r *= 0.3 * Random1Effect;
		gl_FragColor.b *= 0.3 * Random2Effect;
		gl_FragColor.g *= 1.0 + Random1Pass;
	}
	
	if( gl_FragColor.r < 0.3 && gl_FragColor.b < 0.3 && gl_FragColor.g < 0.4 )
		gl_FragColor.a = 0.0;
}
#endif
