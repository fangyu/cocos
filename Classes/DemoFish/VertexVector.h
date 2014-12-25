#ifndef VERTEXVECTOR_H_
#define VERTEXVECTOR_H_

#include "cocos2d.h"
#include "Noise.h"
#include "3d/CCMesh.h"
NS_CC_BEGIN 
//�����ʽ
struct VertexColorCoord1
{
    Vec3 position;
    Vec4 color;

    float u;
    float v;
    VertexColorCoord1():color(1.0f, 1.0f, 1.0f, 1.0f), u(0.0f), v(0.0f)
    {
    }
};

//��������
class VertexVector
{
public:
	//����
	VertexVector( bool bIndex = false, unsigned int initialCapacity = 128, unsigned int growSize = 128);
	//����
    ~VertexVector();
	//��ʼ��
    void init();
    //ȡ�ö�������������
	unsigned int getVertexCapacity() const
	{
		return m_VertexCapacity;
	}
	//���ö�������������
	void setVertexCapacity(unsigned int capacity);
	//ȡ����������������
	unsigned int getIndexCapacity() const
	{
		return m_IndexCapacity;
	}
	//������������������
    void setIndexCapacity(unsigned int capacity);

	// ���Ӷ��������
	void add(const unsigned char* vertices, unsigned int vertexCount);
	void add(const unsigned char* vertices, unsigned int vertexCount, const unsigned short* indices, unsigned int indexCount);

	void addVertex( const unsigned char* vertices, unsigned int vertexCount );
	void addIndex( const unsigned short* indices, unsigned int indexCount, unsigned int vertexOffset );

	// ȡ�ö�������
	unsigned char* getVertices(void) const
	{
		return m_Vertices;
	}
	//ȡ�ö�������
	unsigned int  getVerticesCount() 
	{
		return m_VertexCount;
	}
	//ȡ������
	unsigned short* getIndices(void) const
	{
		return m_Indices;
	}
	//ȡ����������
	unsigned int  getIndexCount()
	{
		return m_IndexCount;
	}
	//���
	void clear();
	//����
	void draw();

private:

	//���ö�����������
    bool resizeVertex(unsigned int capacity);
	//����������������
    bool resizeIndex(unsigned int capacity);

	//
    unsigned int	m_GrowSize;	
    unsigned int	m_VertexCapacity;	
    unsigned int	m_VertexCount;	
    unsigned char*	m_Vertices;	
    unsigned char*	m_VerticesPtr;	

    bool			m_bUseIndex;
    unsigned int	m_IndexCapacity;
    unsigned short* m_Indices;
    unsigned short* m_IndicesPtr;
    unsigned int	m_IndexCount;

};

NS_CC_END
#endif
