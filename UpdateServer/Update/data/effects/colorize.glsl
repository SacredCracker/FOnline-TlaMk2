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

varying vec4 Color;
varying vec2 TexCoord;
varying vec2 TexEggCoord;

// colorize
void main ( )
{
    gl_FragColor = texture2D ( ColorMap, TexCoord );
 
    float maxcolor = max ( max ( gl_FragColor.r, gl_FragColor.g ), gl_FragColor.b );
    float mincolor = min ( min ( gl_FragColor.r, gl_FragColor.g ), gl_FragColor.b );
    vec3 luminance = vec3 ( maxcolor );
    float saturation = ( maxcolor - mincolor ) / maxcolor;
    
    gl_FragColor.rgb = mix ( luminance, Color.rgb * luminance, saturation );
    gl_FragColor.a *= Color.a;
}

#endif
