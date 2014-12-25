#ifndef LIGHTLINERENDER_H
#define LIGHTLINERENDER_H

#include "cocos2d.h"
#include "VertexVector.h"

NS_CC_BEGIN 
#define C3D_Max(a,b)            (((a) > (b)) ? (a) : (b))
#define C3D_Min(a,b)            (((a) < (b)) ? (a) : (b))
	

class C3DPerlinNoise;
enum LineType
{
	LT_Direct,		// 直线
	LT_Random,		// 随机抖动
	LT_PerlinNosie,	// 柏林噪声曲线
};

//闪电链显示类
class LightLineRender : public  cocos2d::Layer
{
public:
	//线段点的类型
	enum StepType
	{
		ST_Begin,	// 开始
		ST_End,		// 结束
		ST_Other,	// 其它
	};

public:
	struct Line
	{
		Line( Vec3 lBegin, Vec3 lEnd )
			:lineBegin( lBegin )
			,lineEnd( lEnd )
			,beginOffset( 0.0 )
		{
		}
		Line( Vec3 lBegin, Vec3 lEnd, float offset )
			:lineBegin( lBegin )
			,lineEnd( lEnd )
			,beginOffset( offset )
		{
		}

		Vec3 lineBegin;
		Vec3 lineEnd;
		float beginOffset;
	};

public:
	//构造
	LightLineRender();
	//析构
	~LightLineRender(void);

	//初始化
    virtual bool init();  
	//创建
    CREATE_FUNC(LightLineRender);
	//重载绘制处理函数
	virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
	//取得构成链条的线段容器
	const std::vector<Line>& getLines() const
	{
		return m_Lines;
	}
	//设置构成链条的线段容器
	void setLines( const std::vector<Line>& lines );
	//设置宽度
	void setWidth( float f )
	{
		m_Width = f;
	}
	float getWidth(void) const
	{
		return m_Width;
	}
	//设置单个面片网格长，越小曲线越平滑，数值过于小可能带来效率问题
	void setStep( float f )
	{
		m_Step = f;
	}
	float getStep(void) const
	{
		return m_Step;
	}
	//单张纹理长度，调整这个数值可以避免纹理过度拉伸或挤压
	void setTextueLength( float f )
	{
		m_TextureLength = f;
	}
	float getTextureLength(void) const
	{
		return m_TextureLength;
	}
	// 设置振幅1
	void setAmplitude0( float f )
	{
		m_Amplitude0 = f;
	}
	float getAmplitude0(void)
	{
		return m_Amplitude0;
	}
	// 设置振幅2
	void setAmplitude1( float f )
	{
		m_Amplitude1 = f;
	}
	float getAmplitude1(void)
	{
		return m_Amplitude1;
	}
	// 设置频率1
	void setFrequency0( float f )
	{
		m_Frequency0 = f;
	}
	float getFrequency0(void)
	{
		return m_Frequency0;
	}
	// 设置频率2
	void setFrequency1( float f )
	{
		m_Frequency1 = f;
	}
	float getFrequency1(void)
	{
		return m_Frequency1;
	}
	// 设置是否强制纹理循环
	void setForceTexLoop( bool b )
	{
		m_ForceTexLoop = b;
	}
	bool getForceTexLoop(void) const
	{
		return m_ForceTexLoop;
	}
	//设置产生噪音的时间系数
	void setTimeFactor( float f )
	{
		m_TimeFactor = f;
	}

	float getTimeFactor(void) const
	{
		return m_TimeFactor;
	}
	//设置头尾振幅衰减
	void setAttenuation( float f )
	{
		m_Attenuation = f;
	}
	float getAttenuation(void) const
	{
		return m_Attenuation;
	}
	//设置线段类型
	void setLineType( LineType lineType )
	{
		m_LineType = lineType;
	}
	LineType getLineType(void)
	{
		return m_LineType;
	}
	//设置色彩
	void setColor( const Vec4& color )
	{
		m_Color = color;
	}
	Vec4 getColor(void)
	{
		return m_Color;
	}
	//设置是否强制更新
	void setForceUpdate( bool b )
	{
		m_ForceUpdate = b;
	}

	bool getForceUpdate(void) const
	{
		return m_ForceUpdate;
	}
	//慢慢消隐
	void OpenAlphaToZero(float fTime)
	{
		m_fLeaveAlphaToZeroTime = m_fTotalAlphaToZeroTime = fTime;
	}
private:
	//初始化
	void init( const std::string& materialPath );
	//更新
	void updateMesh(void);
	//增加一个新的片段
	void addOneStep( VertexVector* mesh, Vec3 lineBegin, Vec3 lineEnd,
							Vec3 widthOffset/*One, Vec3 widthOffsetTwo,
							float halfWidth*/, float uvBegin, float uvEnd, StepType stepType, Vec4 color );

	Vec3 getCenter(void);


private:

	bool						 m_ForceTexLoop;	// 是否强制纹理循环
	bool						 m_Dirty;			// 是否需要重建模型
	bool						 m_ForceUpdate;		// 是否强制重建模型

	float						 m_Time;			// 秒
	float						 m_Width;			// 宽
	float						 m_Step;			// 单个面片网格长，越小曲线越平滑，数值过于小可能带来效率问题
	float						 m_TextureLength;	// 单张纹理长度，调整这个数值可以避免纹理过度拉伸或挤压
	float						 m_Amplitude0;		// 振幅
	float						 m_Amplitude1;		// 振幅
	float						 m_Frequency0;		// 频率
	float						 m_Frequency1;		// 频率
	float						 m_TimeFactor;
	float						 m_fTotalAlphaToZeroTime;// 总计消隐的时间
	float						 m_fLeaveAlphaToZeroTime; // 当前消隐的时间
	float						 m_Attenuation;		// 头尾振幅衰减，距离起止点的_attenuation距离内带收敛为三角
	Vec4						 m_Color;			// 颜色，具体作用为 _color*纹理颜色
	LineType					 m_LineType;		// 类型
	std::vector<Line>			 m_Lines;			// 线段容器

	GLProgramState*			     m_ProgramState;	//Shader管理器
	BlendFunc					 m_BlendFunc;		//渲染状态
	Texture2D*				     m_Texture;			//纹理
	VertexVector*				 m_VertexVector;	//顶点与索引存储容器
	Mesh*						 m_RenderMesh;		//渲染模型
	timeval						 m_LastTime;		//时间
	MeshCommand*				 m_pMeshCommand;	//渲染队列
	static PerlinNoise			 m_PerlinNoise;		//噪音
};
NS_CC_END
#endif	//#define LightLineRender_H