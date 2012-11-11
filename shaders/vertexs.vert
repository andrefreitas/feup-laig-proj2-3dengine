uniform float normScale;
uniform sampler2D secondImage;

void main() 
{

// generate texture coords
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 v =vec4(gl_Vertex);
	
	vec4 offset= texture2D(secTexture, gl_TexCoord[0].st);
	v.y = 3.0*offset.r+3.0*offset.g+3.0*offset.b;
	
	/*if(v.x<0.0){
	v.x=0.0;
	}*/
	
	// Set the position of the current vertex 
	gl_Position = gl_ModelViewProjectionMatrix * v;

}