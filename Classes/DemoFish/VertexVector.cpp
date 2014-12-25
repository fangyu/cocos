#include "VertexVector.h"
USING_NS_CC;

VertexVector::VertexVector(bool bIndex, unsigned int initialCapacity, unsigned int growSize):
	/*, _primitiveType(primitiveType)*/
	m_GrowSize(growSize)
	, m_VertexCapacity(initialCapacity*4)
	, m_VertexCount(0)
	, m_Vertices(NULL)
	, m_VerticesPtr(NULL)
	, m_Indices(NULL)
	, m_IndicesPtr(NULL)
	, m_IndexCount(0)
	, m_IndexCapacity( initialCapacity*6 )
{
	//_primitiveType = primitiveType;
	//_vertexFormat = new C3DVertexFormat(vertexFormat);
    m_bUseIndex = bIndex;
	//resizeVertex(_vertexCapacity * 4);
	//if ( _bUseIndex )
	{
	//	resizeIndex( /*_indexCapacity*/ _vertexCapacity * 6 );
	}
}

VertexVector::~VertexVector()
{
    CC_SAFE_DELETE_ARRAY(m_Vertices);
    CC_SAFE_DELETE_ARRAY(m_Indices);

	m_VerticesPtr = NULL;
	m_IndicesPtr = NULL;
}
    
void VertexVector::init()
{
    resizeVertex( m_VertexCapacity );
    resizeIndex( m_IndexCapacity );
    
}

void VertexVector::setVertexCapacity(unsigned int capacity)
{
	resizeVertex( capacity );
}

void VertexVector::setIndexCapacity(unsigned int capacity)
{
    resizeIndex(capacity);
}

bool VertexVector::resizeVertex(unsigned int capacity)
{
    if (capacity == 0)
	{
		return false;
	}

    if (capacity == m_VertexCapacity && m_VerticesPtr != NULL )
	{
		return true;
	}

    unsigned char* oldVertices = m_Vertices;

    // Allocate new data and reset pointers
    unsigned int voffset = m_VerticesPtr - m_Vertices;
    unsigned int vBytes = capacity * sizeof(VertexColorCoord1);
    m_Vertices = new unsigned char[vBytes];
    if (voffset >= vBytes)
	{
        voffset = vBytes - 1;
	}
    m_VerticesPtr = m_Vertices + voffset;

    // Copy old data back in
    if (oldVertices)
	{
        memcpy(m_Vertices, oldVertices, std::min(m_VertexCapacity, capacity) * sizeof(VertexColorCoord1));
	}

	CC_SAFE_DELETE_ARRAY(oldVertices);

    // Assign new capacities
    m_VertexCapacity = capacity;

    return true;
}

bool VertexVector::resizeIndex(unsigned int capacity)
{
    if (m_bUseIndex == false)
        return false;
    
    if (capacity == 0)
	{
		return false;
	}
    
    if (capacity == m_IndexCapacity && m_IndicesPtr != NULL )
	{
		return true;
	}
    
   
    
    unsigned short* oldIndex = m_Indices;
    unsigned int voffset = m_IndicesPtr - m_Indices;

    m_Indices = new unsigned short[capacity];

    m_IndicesPtr = m_Indices + voffset;

    if (oldIndex)
    {
        if (voffset)
        {
            memcpy(m_Indices, oldIndex, std::min(m_IndexCapacity, capacity) * sizeof(m_Indices[0]) );
        }

        CC_SAFE_DELETE_ARRAY(oldIndex);
    }
    m_IndexCapacity = capacity;
    

    return true;
}
void VertexVector::add(const unsigned char* vertices, unsigned int vertexCount)
{
	addVertex( vertices, vertexCount );
}

void VertexVector::add(const unsigned char* vertices, unsigned int vertexCount, const unsigned short* indices, unsigned int indexCount)
{
	unsigned int vertexOffset = m_VertexCount;
	addVertex( vertices, vertexCount );
	addIndex( indices, indexCount, vertexOffset );
}

void VertexVector::addVertex( const unsigned char* vertices, unsigned int vertexCount )
{
	unsigned int newVertexCount = m_VertexCount + vertexCount;

	if (newVertexCount > m_VertexCapacity)
	{
		if (m_GrowSize == 0)
		{
			return;
		}

		unsigned int capacity( m_VertexCapacity );
		while ( newVertexCount > capacity )
		{
			capacity += m_GrowSize;
		}

		if ( !resizeVertex( capacity ) )
		{
			return;
		}
	}

	unsigned int vBytes = vertexCount * sizeof(VertexColorCoord1);
	memcpy(m_VerticesPtr, vertices, vBytes);

	m_VerticesPtr += vBytes;
	m_VertexCount = newVertexCount;
}

void VertexVector::addIndex( const unsigned short* indices, unsigned int indexCount, unsigned int vertexOffset )
{
	unsigned int newIndexCount = m_IndexCount + indexCount;

	if (newIndexCount > m_IndexCapacity)
	{
		if (m_GrowSize == 0)
		{
			return;
		}

		unsigned int capacity( m_IndexCapacity );
		while ( newIndexCount > capacity )
		{
			capacity += m_GrowSize;
		}

		if (!resizeIndex( capacity ) )
		{
			return;
		}
	}

	for (unsigned int i = 0; i < indexCount; ++i)
	{
		*m_IndicesPtr = indices[i] + vertexOffset;
		++m_IndicesPtr;
	}
	m_IndexCount = newIndexCount;
}

void VertexVector::clear()
{
    m_VertexCount = 0;
    m_VerticesPtr = m_Vertices;
    m_IndicesPtr = m_Indices;
    m_IndexCount = 0;
}
