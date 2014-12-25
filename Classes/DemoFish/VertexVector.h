#ifndef VERTEXVECTOR_H_
#define VERTEXVECTOR_H_

#include "cocos2d.h"
#include "Noise.h"
#include "3d/CCMesh.h"
NS_CC_BEGIN 
//顶点格式
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

//顶点容器
class VertexVector
{
public:
	//构造
	VertexVector( bool bIndex = false, unsigned int initialCapacity = 128, unsigned int growSize = 128);
	//析构
    ~VertexVector();
	//初始化
    void init();
    //取得顶点容器的容量
	unsigned int getVertexCapacity() const
	{
		return m_VertexCapacity;
	}
	//设置顶点容器的容量
	void setVertexCapacity(unsigned int capacity);
	//取得索引容器的容器
	unsigned int getIndexCapacity() const
	{
		return m_IndexCapacity;
	}
	//设置索引容器的容量
    void setIndexCapacity(unsigned int capacity);

	// 增加顶点和索引
	void add(const unsigned char* vertices, unsigned int vertexCount);
	void add(const unsigned char* vertices, unsigned int vertexCount, const unsigned short* indices, unsigned int indexCount);

	void addVertex( const unsigned char* vertices, unsigned int vertexCount );
	void addIndex( const unsigned short* indices, unsigned int indexCount, unsigned int vertexOffset );

	// 取得顶点数量
	unsigned char* getVertices(void) const
	{
		return m_Vertices;
	}
	//取得顶点数量
	unsigned int  getVerticesCount() 
	{
		return m_VertexCount;
	}
	//取得索引
	unsigned short* getIndices(void) const
	{
		return m_Indices;
	}
	//取得索引数量
	unsigned int  getIndexCount()
	{
		return m_IndexCount;
	}
	//清空
	void clear();
	//绘制
	void draw();

private:

	//重置顶点容器容量
    bool resizeVertex(unsigned int capacity);
	//重置索引容器容量
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
