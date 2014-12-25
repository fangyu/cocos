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
	LT_Direct,		// ֱ��
	LT_Random,		// �������
	LT_PerlinNosie,	// ������������
};

//��������ʾ��
class LightLineRender : public  cocos2d::Layer
{
public:
	//�߶ε������
	enum StepType
	{
		ST_Begin,	// ��ʼ
		ST_End,		// ����
		ST_Other,	// ����
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
	//����
	LightLineRender();
	//����
	~LightLineRender(void);

	//��ʼ��
    virtual bool init();  
	//����
    CREATE_FUNC(LightLineRender);
	//���ػ��ƴ�����
	virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
	//ȡ�ù����������߶�����
	const std::vector<Line>& getLines() const
	{
		return m_Lines;
	}
	//���ù����������߶�����
	void setLines( const std::vector<Line>& lines );
	//���ÿ��
	void setWidth( float f )
	{
		m_Width = f;
	}
	float getWidth(void) const
	{
		return m_Width;
	}
	//���õ�����Ƭ���񳤣�ԽС����Խƽ������ֵ����С���ܴ���Ч������
	void setStep( float f )
	{
		m_Step = f;
	}
	float getStep(void) const
	{
		return m_Step;
	}
	//���������ȣ����������ֵ���Ա���������������ѹ
	void setTextueLength( float f )
	{
		m_TextureLength = f;
	}
	float getTextureLength(void) const
	{
		return m_TextureLength;
	}
	// �������1
	void setAmplitude0( float f )
	{
		m_Amplitude0 = f;
	}
	float getAmplitude0(void)
	{
		return m_Amplitude0;
	}
	// �������2
	void setAmplitude1( float f )
	{
		m_Amplitude1 = f;
	}
	float getAmplitude1(void)
	{
		return m_Amplitude1;
	}
	// ����Ƶ��1
	void setFrequency0( float f )
	{
		m_Frequency0 = f;
	}
	float getFrequency0(void)
	{
		return m_Frequency0;
	}
	// ����Ƶ��2
	void setFrequency1( float f )
	{
		m_Frequency1 = f;
	}
	float getFrequency1(void)
	{
		return m_Frequency1;
	}
	// �����Ƿ�ǿ������ѭ��
	void setForceTexLoop( bool b )
	{
		m_ForceTexLoop = b;
	}
	bool getForceTexLoop(void) const
	{
		return m_ForceTexLoop;
	}
	//���ò���������ʱ��ϵ��
	void setTimeFactor( float f )
	{
		m_TimeFactor = f;
	}

	float getTimeFactor(void) const
	{
		return m_TimeFactor;
	}
	//����ͷβ���˥��
	void setAttenuation( float f )
	{
		m_Attenuation = f;
	}
	float getAttenuation(void) const
	{
		return m_Attenuation;
	}
	//�����߶�����
	void setLineType( LineType lineType )
	{
		m_LineType = lineType;
	}
	LineType getLineType(void)
	{
		return m_LineType;
	}
	//����ɫ��
	void setColor( const Vec4& color )
	{
		m_Color = color;
	}
	Vec4 getColor(void)
	{
		return m_Color;
	}
	//�����Ƿ�ǿ�Ƹ���
	void setForceUpdate( bool b )
	{
		m_ForceUpdate = b;
	}

	bool getForceUpdate(void) const
	{
		return m_ForceUpdate;
	}
	//��������
	void OpenAlphaToZero(float fTime)
	{
		m_fLeaveAlphaToZeroTime = m_fTotalAlphaToZeroTime = fTime;
	}
private:
	//��ʼ��
	void init( const std::string& materialPath );
	//����
	void updateMesh(void);
	//����һ���µ�Ƭ��
	void addOneStep( VertexVector* mesh, Vec3 lineBegin, Vec3 lineEnd,
							Vec3 widthOffset/*One, Vec3 widthOffsetTwo,
							float halfWidth*/, float uvBegin, float uvEnd, StepType stepType, Vec4 color );

	Vec3 getCenter(void);


private:

	bool						 m_ForceTexLoop;	// �Ƿ�ǿ������ѭ��
	bool						 m_Dirty;			// �Ƿ���Ҫ�ؽ�ģ��
	bool						 m_ForceUpdate;		// �Ƿ�ǿ���ؽ�ģ��

	float						 m_Time;			// ��
	float						 m_Width;			// ��
	float						 m_Step;			// ������Ƭ���񳤣�ԽС����Խƽ������ֵ����С���ܴ���Ч������
	float						 m_TextureLength;	// ���������ȣ����������ֵ���Ա���������������ѹ
	float						 m_Amplitude0;		// ���
	float						 m_Amplitude1;		// ���
	float						 m_Frequency0;		// Ƶ��
	float						 m_Frequency1;		// Ƶ��
	float						 m_TimeFactor;
	float						 m_fTotalAlphaToZeroTime;// �ܼ�������ʱ��
	float						 m_fLeaveAlphaToZeroTime; // ��ǰ������ʱ��
	float						 m_Attenuation;		// ͷβ���˥����������ֹ���_attenuation�����ڴ�����Ϊ����
	Vec4						 m_Color;			// ��ɫ����������Ϊ _color*������ɫ
	LineType					 m_LineType;		// ����
	std::vector<Line>			 m_Lines;			// �߶�����

	GLProgramState*			     m_ProgramState;	//Shader������
	BlendFunc					 m_BlendFunc;		//��Ⱦ״̬
	Texture2D*				     m_Texture;			//����
	VertexVector*				 m_VertexVector;	//�����������洢����
	Mesh*						 m_RenderMesh;		//��Ⱦģ��
	timeval						 m_LastTime;		//ʱ��
	MeshCommand*				 m_pMeshCommand;	//��Ⱦ����
	static PerlinNoise			 m_PerlinNoise;		//����
};
NS_CC_END
#endif	//#define LightLineRender_H