#include <resource/ResourceIndex.hpp>
#include <algorithm>

#include <dirent.h>
#include <sys/types.h>

ResourceIndex::ResourceIndex()
{

}

void ResourceIndex::indexDirectory(const std::string &directory)
{
	DIR* dp = opendir(directory.c_str());
	dirent* ep;
	std::string realName;
	
	if ( dp == NULL ) {
		throw std::runtime_error("Unable to open directory: " + directory);
	}

	while( (ep = readdir(dp)) ) {
		realName = ep->d_name;
		std::string lowerRealName = realName;
		std::transform(lowerRealName.begin(), lowerRealName.end(), lowerRealName.begin(), ::tolower);
		if ( ep->d_type == DT_REG )
		{
			files[ lowerRealName ] = {
				realName,
				lowerRealName,
				directory
			};
		}
	}
}

bool ResourceIndex::findFileInfo(const std::string &name, ResourceIndex::FileInfo &info)
{
	auto iterator = files.find( name );
	
	if ( iterator == files.end() )
	{
		return false;
	}
	
	info = iterator->second;
	return true;
}
