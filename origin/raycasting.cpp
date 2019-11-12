#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <GL/glut.h>

void createTex3D(const char* path)
{
	data=new unsigned char[voxcelNum];
	ifstream file(path, ios::in | ios::binary);
	file.read((char*)data, voxcelNum*sizeof(unsigned char));
	file.close();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &VolumeTex3D);
	glBindTexture(GL_TEXTURE_3D, VolumeTex3D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_LUMINANCE, width,height,depth,0,
				GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
	useSamplerParameter(CgEffect, "VolumeTex3D", VolumeTex3D);
}

//生成bounding box的前后表面，作为GPU的参数
	glGenTextures(1, &BackTex2D);
	glBindTexture(GL_TEXTURE_2D, BackTex2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	useSamplerParameter(CgEffect, "BackTex2D", BackTex2D);
	glGenTextures(1, &FrontTex2D);
	glBindTexture(GL_TEXTURE_2D, FrontTex2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	useSamplerParameter(CgEffect, "FrontTex2D", FrontTex2D);

float4 RayCastingFS( vfConn input ) : COLOR0
{
	//把bounding box的坐标转换为0-1之间<br />
	float2 texCoord = ((input.texCoord.xy / input.texCoord.w) + 1.0) * 0.5;
	float3 front	= tex2D( FrontTex2D, texCoord ).xyz;	//前面表
	float3 back		= tex2D( Back
				if(LinePS[0]<=100)
				{
					//白色
					LinePD[0]=1.0;
					LinePD[1]=1.0;
					LinePD[2]=1.0;
					LinePD[3]=0.005;
				}
				else if(LinePS[0]<=200)
				{
					//红色
					LinePD[0]=1.0;
					LinePD[1]=0.0;
					LinePD[2]=0.0;
					LinePD[3]=0.015;
				}
				else
				{
					//黄色
					LinePD[0]=1.0;
					LinePD[1]=1.0;
					LinePD[2]=0.0;
					LinePD[3]=0.02;
				}
				LinePS++;
				LinePD+=4;
			}
				if(LinePS[0]<=100)
				{
					//白色
					LinePD[0]=1.0;
					LinePD[1]=1.0;
					LinePD[2]=1.0;
					LinePD[3]=0.005;
				}
				else if(LinePS[0]<=200)
				{
					//红色
					LinePD[0]=1.0;
					LinePD[1]=0.0;
					LinePD[2]=0.0;
					LinePD[3]=0.015;
				}
				else
				{
					//黄色
					LinePD[0]=1.0;
					LinePD[1]=1.0;
					LinePD[2]=0.0;
					LinePD[3]=0.02;
				}
				LinePS++;
				LinePD+=4;
			}Tex2D, texCoord ).xyz;		//后表面
	float3 dir		= normalize( back - front);		//获得方向
	float4 pos		= float4( front, 0 );
	float4 src		= float4(0.0, 0.0, 0.0, 0.0);

				if(LinePS[0]<=100)
				{
					//白色
					LinePD[0]=1.0;
					LinePD[1]=1.0;
					LinePD[2]=1.0;
					LinePD[3]=0.005;
				}
				else if(LinePS[0]<=200)
				{
					//红色
					LinePD[0]=1.0;
					LinePD[1]=0.0;
					LinePD[2]=0.0;
					LinePD[3]=0.015;
				}
				else
				{
					//黄色
					LinePD[0]=1.0;
					LinePD[1]=1.0;
					LinePD[2]=0.0;
					LinePD[3]=0.02;
				}
				LinePS++;
				LinePD+=4;
			}	float4 dst		= float4(0.0, 0.0, 0.0, 0.0);
	float  val		= 0.0;
	float3 step		= dir * 0.02;
	//raycasting 的主要部分，对每个体素进行混合并计算出最后的像素的值
	//这里alpha的值设置为0.5，取样步长为0.02
	for(int i = 0; i < 300; ++i)
	{
		val		= tex3D(VolumeTex3D, pos);
		src		= (float4)val;
		src.a	*= 0.5f;
		src.xyz *= src.a;
		dst = (1.0f - dst.a) * src + dst;
		if( 0.95f < dst.a)
				break;
			pos.xyz += step;
		if( 1.0f < pos.x || 1.0f < pos.y || 1.0f < pos.z )
				break;
	}
	return dst;
}
