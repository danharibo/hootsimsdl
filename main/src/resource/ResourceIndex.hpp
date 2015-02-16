#ifndef _RESOURCEINDEX_HPP_
#define _RESOURCEINDEX_HPP_

#include <string>
#include <map>

class ResourceIndex
{
public:
	
	struct FileInfo
	{
		/// The "true" on disk filename.
		std::string realFileName;
		/// Lowercased filename
		std::string lowerName;
		/// Directory that contains this file
		std::string directory;
	};
	
	ResourceIndex();
	
	void indexDirectory(const std::string& directory);

	/**
	 * Populates info with the file identified by name, if it can be found.
	 * If the file is not found, false is returned, otherwise true.
	 */
	bool findFileInfo(const std::string& name, FileInfo& info);
	
private:
	std::map<std::string, FileInfo> files;
};

#endif