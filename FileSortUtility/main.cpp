
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <list>

#include "Windows.h"


int main()
{
	std::locale::global(std::locale("en_US.UTF-8"));
	std::wcout.imbue(std::locale());
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	std::filesystem::path m_path = L"F:\\downloads";
	const std::filesystem::path new_path_base(L"F:\\n_downloads");

	std::unordered_map<std::wstring, std::list<std::filesystem::path>> FilesMap;
	

	for (auto& entry : std::filesystem::directory_iterator(m_path))
	{
		try
		{
			if (entry.is_regular_file() && entry.path().has_filename() && entry.path().has_extension())
			{
				FilesMap[entry.path().filename().extension()].push_back(entry.path());
			}
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cout << "\n\n\n err: " << e.what() << "\n\n\n" << std::endl;
		}
	}

	if (!std::filesystem::exists(new_path_base))
		std::filesystem::create_directory(new_path_base);

	for (auto& [ext, entry_list] : FilesMap)
	{
		auto new_path = std::filesystem::path(new_path_base) /= ext.substr(1);

		if (!std::filesystem::exists(new_path))
			std::filesystem::create_directory(new_path);

		std::wcout << "\n" << ext << "\n";

		for (auto& entry : entry_list)
		{
			std::filesystem::path new_path_with_filename(new_path);
			new_path_with_filename /= entry.filename();
			std::filesystem::rename(entry, new_path_with_filename);
		}
	}

	return 0;
}
