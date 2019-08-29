#version 110

#ifdef VERTEX_SHADER
uniform mat4 ProjectionMatrix;

attribute vec2 InPosition;
attribute vec2 InTexCoord;
attribute vec2 InTexEggCoord;

varying vec2 TexCoord;
varying vec2 TexEggCoord;

void main( void )
{
	gl_Position = ProjectionMatrix * vec4( InPosition, 0.0, 1.0 );
	TexCoord = InTexCoord;
	TexEggCoord = InTexEggCoord;
}
#endif

#ifdef FRAGMENT_SHADER
uniform sampler2D ColorMap;
uniform sampler2D EggMap;

varying vec2 TexCoord;
varying vec2 TexEggCoord;

void main( void )
{
	gl_FragColor = texture2D( ColorMap, TexCoord );
	
	gl_FragColor.rgb = vec3( ( gl_FragColor.r + gl_FragColor.g + gl_FragColor.b ) / 3.0 );
	gl_FragColor.r=0.0;
	if(gl_FragColor.b < 0.2) gl_FragColor.b = 0.0; else gl_FragColor.b = 0.3;
	if( TexEggCoord.x != 0.0 )
		gl_FragColor.a *= texture2D( EggMap, TexEggCoord ).a;
}
#endif
