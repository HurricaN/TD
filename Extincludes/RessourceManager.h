#ifndef RESSOURCEMANAGER_H_
#define RESSOURCEMANAGER_H_

#include <string>
#include <map>

template< class T >
class ResourceManager {
public:
	typedef std::pair< std::string, T* >    Resource;
	typedef std::map< std::string, T* >     ResourceMap;

private:
		ResourceMap m_resource;

	T* find( const std::string& strId ) {
		T* resource = NULL;
		typename ResourceMap::iterator it = m_resource.find( strId );
		if( it != m_resource.end() ) {
			resource = it->second;
		}

		return resource;
	}

protected:
		virtual T* load( const std::string& strId ) = 0;

public:
	ResourceManager() {
	}

	virtual ~ResourceManager() {
		releaseAllResources();
	}

	T* getResource( const std::string& strId ) {
		T* resource = find( strId );
		if( resource == NULL ) {
			resource = load( strId );
			// If the resource loaded successfully, add it do the resource map
			if( resource != NULL )
				m_resource.insert( Resource( strId, resource ) );
		}
		return resource;
	}

	void releaseResource( const std::string& strId ) {
		T* resource = find( strId );
		if( resource != NULL ) {
			delete resource;
			m_resource.erase( m_resource.find( strId ) );
		}
	}

	void releaseAllResources() {
		while( m_resource.begin() != m_resource.end() ) {
			delete m_resource.begin()->second;
			m_resource.erase( m_resource.begin() );
		}
	}
};


#endif /* RESSOURCEMANAGER_H_ */
