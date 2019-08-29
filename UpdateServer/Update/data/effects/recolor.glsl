#version 110

#ifdef VERTEX_SHADER
uniform mat4 ProjectionMatrix;

attribute vec2 InPosition;
attribute vec4 InColor;
attribute vec2 InTexCoord;

varying vec4 Color;
varying vec2 TexCoord;

void main( void )
{
	gl_Position = ProjectionMatrix * vec4( InPosition, 0.0, 1.0 );
	Color = InColor;
	TexCoord = InTexCoord;
}
#endif

#ifdef FRAGMENT_SHADER
uniform sampler2D ColorMap;

varying vec4 Color;
varying vec2 TexCoord;

vec3 u_Color1 = vec3( 0.95, 0.91, 0.73 );
vec3 u_Color2 = vec3( 0.11, 0.65, 0.21 ); 
vec3 u_Color3 = vec3( 0.84, 0.23, 0.10 );

float Max( float a, float b, float c )
{
    return max ( max ( a, b ), c );
}

float Min ( float a, float b, float c )
{
    return min ( min ( a, b ), c );
}

void main ( )
{
    gl_FragColor = texture2D ( ColorMap, TexCoord );
    
    float maxcolor = Max ( gl_FragColor.r, gl_FragColor.g, gl_FragColor.b );
    float mincolor = Min ( gl_FragColor.r, gl_FragColor.g, gl_FragColor.b );
    float saturation = ( maxcolor - mincolor ) / maxcolor;
    vec3 luminance = vec3 ( maxcolor );
    vec3 newcolor = u_Color1 * gl_FragColor.r + 
                    u_Color2 * gl_FragColor.g + 
                    u_Color3 * gl_FragColor.b;
    gl_FragColor.rgb = mix ( luminance, newcolor, saturation );
    
    gl_FragColor *= Color;
}

#endif
